/**
 * @file ecu_lua_script.cpp
 *
 * This file contains the class which represents the corresponding Lua script.
 */

#include "ecu_lua_script.h"
#include "crcccitt.c"
#include "utilities.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <stdexcept>
#include <unistd.h>
#include <cassert>

using namespace std;

/// Look-up table for (uppercase) hexadecimal digits [0..F].
static constexpr char HEX_LUT[] = "0123456789ABCDEF";

/// Defines the maximum size of an UDS message in bytes.
static constexpr int MAX_UDS_SIZE = 4096;

static string receivedDataBytes = "";
/**
 * Constructor. Loads a Lua script and injects common used functions.
 *
 * @param ecuIdent: the identifier name for the ECU (e.g. "PCM")
 * @param luaScript: the path to the Lua script
 */
EcuLuaScript::EcuLuaScript(const string& ecuIdent, const string& luaScript, DoIPServer* server)
{
    if (utils::existsFile(luaScript))
    {
        
        registedServer = server;
        
        // inject the C++ functions into the Lua script
        lua_state_["ascii"] = &ascii;
        lua_state_["getCounterByte"] = &getCounterByte;
        lua_state_["getDataBytes"] = &getDataBytes;
        lua_state_["createHash"] = &createHash;
        lua_state_["toByteResponse"] = &toByteResponse;
        lua_state_["sleep"] = &sleep;
        // some lambda magic for the member functions 
        lua_state_["getCurrentSession"] = [this]() -> uint32_t { return this->getCurrentSession(); }; 
        lua_state_["switchToSession"] = [this](uint32_t ses) { this->switchToSession(ses); };
        lua_state_["sendRaw"] = [this](const string& msg) { this->sendRaw(msg); };
        
        //DoIP functions in Lua Script
        lua_state_["disconnect"] = [this](){registedServer->triggerDisconnection();};
        lua_state_["sendAnnouncement"] = [this] {registedServer->sendVehicleAnnouncement();};

        lua_state_.Load(luaScript);
        if (lua_state_[ecuIdent.c_str()].exists())
        {
            ecu_ident_ = ecuIdent;

            auto requId = lua_state_[ecu_ident_.c_str()][REQ_ID_FIELD];
            if (requId.exists())
            {
                requestId_ = int(requId);
            }
            else
            {
                throw invalid_argument("No 'RequestId'-field in the Lua ECU table!");
            }

            auto respId = lua_state_[ecu_ident_.c_str()][RES_ID_FIELD];
            if (respId.exists())
            {
                responseId_ = int(respId);
            }
            else
            {
                throw invalid_argument("No 'ResponseId'-field in the Lua ECU table!");
            }

            auto broadcastId = lua_state_[ecu_ident_.c_str()][BROADCAST_ID_FIELD];
            if (broadcastId.exists())
            {
                broadcastId_ = int(broadcastId);
            }
            
            auto logicalAddress = lua_state_[ecu_ident_.c_str()][LOGICAL_ADDRESS_FIELD];
            if (logicalAddress.exists()) 
            {
                logicalAddress_ = int(logicalAddress);
            }

            return;
        }
    }
    throw invalid_argument("No, or invalid Lua script!");
}

/**
 * Move constructor.
 * 
 * @param orig: the originating instance
 */
EcuLuaScript::EcuLuaScript(EcuLuaScript&& orig) noexcept
: lua_state_(move(orig.lua_state_))
, ecu_ident_(move(orig.ecu_ident_))
, pSessionCtrl_(orig.pSessionCtrl_)
, pIsoTpSender_(orig.pIsoTpSender_)
, requestId_(orig.requestId_)
, responseId_(orig.responseId_)
, broadcastId_(orig.broadcastId_)
, logicalAddress_(orig.logicalAddress_)
{
    orig.pSessionCtrl_ = nullptr;
    orig.pIsoTpSender_ = nullptr;
}

/**
 * Move-assignment operator.
 * 
 * @param orig: the originating instance
 * @return reference to the moved instance
 */
EcuLuaScript& EcuLuaScript::operator=(EcuLuaScript&& orig) noexcept
{
    assert(this != &orig);
    lua_state_ = move(orig.lua_state_);
    ecu_ident_ = move(orig.ecu_ident_);
    pSessionCtrl_ = orig.pSessionCtrl_;
    pIsoTpSender_ = orig.pIsoTpSender_;
    requestId_ = orig.requestId_;
    responseId_ = orig.responseId_;
    broadcastId_ = orig.broadcastId_;
    logicalAddress_ = orig.logicalAddress_;
    orig.pIsoTpSender_ = nullptr;
    orig.pSessionCtrl_ = nullptr;
    return *this;
};

/**
 * Gets the UDS request ID according to the loaded Lua script. Since this call
 * is very common, the value is cached at the instantiation to avoid expensive
 * access operations on the Lua file.
 *
 * @return the request ID or 0 on error
 */
uint16_t EcuLuaScript::getRequestId() const
{
    return requestId_;
}

/**
 * Gets the UDS response ID according to the loaded Lua script. Since this call
 * is very common, the value is cached at the instantiation to avoid expensive
 * access operations on the Lua file.
 *
 * @return the response ID or 0 on error
 */
uint16_t EcuLuaScript::getResponseId() const
{
    return responseId_;
}

/**
 * Gets the UDS broadcast address, which is `0x7DF` on default.
 *  
 * @return the specific broadcast address according to the Lua file or `0x7DF`
 *         on default
 */
uint16_t EcuLuaScript::getBroadcastId() const
{
    return broadcastId_;
}

/**
 * Gets the Logical Address to the ECU.
 * @return 
 */
uint16_t EcuLuaScript::getLogicalAddress() const 
{
    return logicalAddress_;
}

/**
 * Reads the data according to `ReadDataByIdentifier`-table in the Lua script.
 *
 * @param identifier: the identifier to access the field in the Lua table
 * @return the identifier field on success, otherwise an empty string
 */
string EcuLuaScript::getDataByIdentifier(const string& identifier) const
{
    auto val = lua_state_[ecu_ident_.c_str()][READ_DATA_BY_IDENTIFIER_TABLE][identifier];

    if (val.isFunction())
    {
        return val(identifier);
    }
    else
    {
        return val;
    }
}

/**
 * Overload with additional sessions handling.
 *
 * @param identifier: the identifier to access the field in the Lua table
 * @param session: the session as string (e.g. "Programming")
 * @return the identifier field on success, otherwise an empty string
 */
string EcuLuaScript::getDataByIdentifier(const string& identifier, const string& session) const
{
    auto val = lua_state_[ecu_ident_.c_str()][session][READ_DATA_BY_IDENTIFIER_TABLE][identifier];

    if (val.isFunction())
    {
        return val(identifier);
    }
    else
    {
        return val;
    }
}

string EcuLuaScript::getSeed(uint8_t seed_level) const
{
    auto val = lua_state_[ecu_ident_.c_str()][READ_SEED][seed_level];
    if (val.exists())
    {
        return val;
    }
    return "";
}

/**
 * Converts a literal hex string into a value vector.
 *
 * @param hexString: the literal hex string (e.g. "41 6f 54")
 * @return a vector with the byte values
 */
vector<uint8_t> EcuLuaScript::literalHexStrToBytes(const string& hexString)
{
    // make a working copy
    string tmpStr = hexString;
    // remove white spaces from string
    tmpStr.erase(remove(tmpStr.begin(), tmpStr.end(), ' '), tmpStr.end());
    vector<uint8_t> data;
    // plus `% 2` just in case of a "odd" byte number
    data.reserve(tmpStr.length() / 2 + (tmpStr.length() % 2));
    string byteString;
    uint8_t byte;
    for (size_t i = 0; i < tmpStr.length(); i += 2)
    {
        byteString = tmpStr.substr(i, 2);
        byte = static_cast<uint8_t> (strtol(byteString.c_str(), NULL, 16));
        data.push_back(byte);
    }
    return data;
}

/**
 * Convert the given string into another string that represents the hex bytes of
 * the input string. This is a convenience function to use ascii strings in
 * responses.
 *
 * Example:
 *     `ascii("Hello")` -> `" 48 65 6C 6C 6F "`
 *
 * @param utf8_str: the input string to convert
 * @return a literal string of hex bytes (e.g. " 12 4A FF ") or an empty string
 * on error
 *
 * @note To allow a seamless string concatenation, the returned string always
 * begins and ends with an whitespace.
 */
string EcuLuaScript::ascii(const string& utf8_str) noexcept
{
    const size_t len = utf8_str.length();
    if (len == 0)
    {
        return "";
    }

    string output;
    // str length * (1 whitespace + 2 characters per byte) + last whitespace
    output.reserve(len * 3 + 1);
    unsigned char c;
    for (size_t i = 0; i < len; ++i)
    {
        c = utf8_str[i];
        output.push_back(' ');
        output.push_back(HEX_LUT[c >> 4]);
        output.push_back(HEX_LUT[c & 0x0F]);
    }
    output.push_back(' ');
    return output;
}
/**
*Substrings the counter value of the message which is the second byte
**/
string EcuLuaScript::getCounterByte(const string& msg) noexcept
{
    // make a working copy
    string tmpStr = msg;
    // remove white spaces from string
    tmpStr.erase(remove(tmpStr.begin(), tmpStr.end(), ' '), tmpStr.end());
    string answer = tmpStr;
    answer = answer.substr(2,2);
    return answer;
}
/**
*Substrings the data bytes value of the message which is the second byte
**/
void EcuLuaScript::getDataBytes(const string& msg) noexcept
{
    // make a working copy
    string tmpStr = msg;
    // remove white spaces from string
    tmpStr.erase(remove(tmpStr.begin(), tmpStr.end(), ' '), tmpStr.end());
    string answer = tmpStr;
    //cut the first two bytes which indicate the request 
    answer = answer.substr(4,answer.length());
    //save the answer in global var, which is also available for createHash()
    receivedDataBytes = receivedDataBytes + answer;
}

string EcuLuaScript::createHash() noexcept
{
    vector <uint8_t> resp = literalHexStrToBytes(receivedDataBytes);
    uint16_t crc2 = crc_ccitt_ffff(resp.data(), resp.size());
    char hash[5];
    snprintf(hash, 5, "%X", crc2);
    string answer(hash);
    if(answer.length() % 2 != 0){
        answer = "0" + answer;
    }
    //reset the received Data variable
    receivedDataBytes = "";
    cout << answer << endl;
    return answer;
}

/**
 * Convert the given unsigned value into a hex byte string as used in requests
 * and responses. The parameter `len` [0..4096] gives the number of bytes that
 * gets returned. In case `len` equals 0, a empty string is returned.
 *
 * Examples:
 *     `toByteResponse(13248, 2)` -> `"33 C0"`
 *     `toByteResponse(13248, 3)` -> `"00 33 C0"`
 *     `toByteResponse(13248, 1)` -> `"C0"`
 *     `toByteResponse(13248)` -> `"00 00 00 00 00 00 33 C0"`
 *
 * @param value: the numeric value to send (e.g. `123`, `0xff`)
 * @param len: the length in bytes [default = 4]
 */
string EcuLuaScript::toByteResponse(uint32_t value,
                                    uint32_t len /* = 4 */) noexcept
{
    if (len > MAX_UDS_SIZE)
    {
        len = MAX_UDS_SIZE;
    }

    static constexpr int CHAR_SP = 3; // character space for 2 hex digits + 1 whitespace
    const int zeroFill = len - sizeof(value);

    if (zeroFill < 0)
    {
        // truncated value
        const size_t space = len * CHAR_SP;
        char str[space];
        for (size_t i = 0, j = (len * 2 - 1) * 4; i < space; i += CHAR_SP, j -= 8)
        {
            str[i] = HEX_LUT[(value >> j) & 0x0F];
            str[i + 1] = HEX_LUT[(value >> (j - 4)) & 0x0F];
            str[i + 2] = ' ';
        }
        str[space - 1] = '\0';
        return str;
    }
    else
    {
        // fill up wit zeros
        const size_t space = ((sizeof(value) + zeroFill) * CHAR_SP);
        const size_t valSpace = zeroFill * CHAR_SP;
        char str[space];
        for (size_t i = 0; i < valSpace; i += CHAR_SP)
        {
            str[i] = '0';
            str[i + 1] = '0';
            str[i + 2] = ' ';
        }

        // insert hex values
        for (size_t i = valSpace, j = (sizeof(value) * 2 - 1) * 4; i < space; i += CHAR_SP, j -= 8)
        {
            str[i] = HEX_LUT[(value >> j) & 0x0F];
            str[i + 1] = HEX_LUT[(value >> (j - 4)) & 0x0F];
            str[i + 2] = ' ';
        }
        str[space - 1] = '\0';
        return str;
    }
    return "";
}

/**
 * Sends the given response (string of hex bytes) immediately.
 *
 * @param response: the raw response message to send (e.g. "DE AD C0 DE")
 */
void EcuLuaScript::sendRaw(const string& response) const
{
    assert(pIsoTpSender_ != nullptr);

    vector<uint8_t> resp = literalHexStrToBytes(response);
    pIsoTpSender_->sendData(resp.data(), resp.size());
}

/**
 * Suspend the script for the given number of milliseconds.
 *
 * @param ms: time to sleep in milliseconds
 */
void EcuLuaScript::sleep(unsigned int ms) noexcept
{
    usleep(ms * 1000);
}

/**
 * Returns the currently active diagnostic session to be used in custom
 * functions.
 */
uint8_t EcuLuaScript::getCurrentSession() const
{
    assert(pSessionCtrl_ != nullptr);

    return pSessionCtrl_->getCurrentUdsSession();
}

/**
 * Switch to the given (numeric) diagnostic session.
 *
 * @param ses: the session ID (e.g. `0x01` = DEFAULT, `0x02` = PROGRAMMING)
 */
void EcuLuaScript::switchToSession(int ses)
{
    assert(pSessionCtrl_ != nullptr);

    pSessionCtrl_->setCurrentUdsSession(UdsSession(ses));
}

/**
 * Checks if the identifier is in the Raw-section of the lua script.
 *
 * @param identStr: the identifier string for the entry in the Lua "Raw"-table
 * @return true if identifier is in the raw section, false otherwise
 */
bool EcuLuaScript::hasRaw(const string& identStr) const
{
    auto val = lua_state_[ecu_ident_.c_str()][RAW_TABLE][identStr.c_str()];
    if(val.exists()==false){
        string identStrWorking = " ";
        //offset for the first byte
        int counter = 2;
        while(val.exists() == false && identStrWorking.length() < identStr.length()){
            //appends wildcard sign after the bytes that are tested
            identStrWorking = identStr.substr(0,counter).append(" *");
            val = lua_state_[ecu_ident_.c_str()][RAW_TABLE][identStrWorking.c_str()];
            //counter + blank + bytelength
            counter = counter + 3;
        }
    }
    return val.exists();
}

/**
 * Gets the raw data entries from the Lua "Raw"-Table.
 * The identifiers of the corresponding entries are literal hex byte strings
 * (e.g. "12 FF 00"). The entries are either strings or functions that need
 * to be called, with the identifier string as the default parameter.
 *
 * @param identStr: the identifier string for the entry in the Lua "Raw"-table
 * @return the raw data as literal hex byte string or an empty string on error
 */
string EcuLuaScript::getRaw(const string& identStr) const
{ 
    auto val = lua_state_[ecu_ident_.c_str()][RAW_TABLE][identStr.c_str()];
    if(val.exists() == true){
        
        if (val.isFunction())
        {
            return val(identStr);
        }
        else
        {
            return val; // will be cast into string
        } 
    }else{
        string identStrWorking = " ";
        //offset for the first byte
        int counter = 2;
        while(val.exists() == false && identStrWorking.length() < identStr.length()){
            //appends wildcard sign after the bytes that are tested
            identStrWorking = identStr.substr(0,counter).append(" *");
            val = lua_state_[ecu_ident_.c_str()][RAW_TABLE][identStrWorking.c_str()];
            //counter + blank + bytelength
            counter = counter + 3;
        }
        if (val.isFunction())
        {
            //call the function with the originally given argument
            return val(identStr);
        }
        else
        {
            return val; // will be cast into string
        } 
    }
    
}


/**
 * Sets the SessionController required for session handling.
 *
 * @param pSesCtrl: pointer to the orchestrating `SessionController`
 */
void EcuLuaScript::registerSessionController(SessionController* pSesCtrl) noexcept
{
    pSessionCtrl_ = pSesCtrl;
}

void EcuLuaScript::registerIsoTpSender(IsoTpSender* pSender) noexcept
{
    pIsoTpSender_ = pSender;
}

