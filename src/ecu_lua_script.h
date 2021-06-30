/**
 * @file ecu_lua_script.h
 *
 */

#ifndef ECU_LUA_SCRIPT_H
#define ECU_LUA_SCRIPT_H

#include "selene.h"
#include "isotp_sender.h"
#include "session_controller.h"
#include <string>
#include <cstdint>
#include <vector>
#include <mutex>

constexpr char REQ_ID_FIELD[] = "RequestId";
constexpr char RES_ID_FIELD[] = "ResponseId";
constexpr char BROADCAST_ID_FIELD[] = "BroadcastId";
constexpr char READ_DATA_BY_IDENTIFIER_TABLE[] = "ReadDataByIdentifier";
constexpr char READ_SEED[] = "Seed";
constexpr char RAW_TABLE[] = "Raw";
constexpr char J1939_SOURCE_ADDRESS_FIELD[] = "J1939SourceAddress";
constexpr char J1939_PGN_TABLE[] = "PGNs";
constexpr char J1939_PGN_PAYLOAD[] = "payload";
constexpr char J1939_PGN_CYCLETIME[] = "cycleTime";
constexpr uint32_t DEFAULT_BROADCAST_ADDR = 0x7DF;

struct J1939PGNData
{
    unsigned int cycleTime;
    std::string payload;
};

class EcuLuaScript
{
public:
    EcuLuaScript() = delete;
    EcuLuaScript(const std::string& ecuIdent, const std::string& luaScript);
    EcuLuaScript(const EcuLuaScript& orig) = delete;
    EcuLuaScript& operator =(const EcuLuaScript& orig) = delete;
    EcuLuaScript(EcuLuaScript&& orig) noexcept;
    EcuLuaScript& operator =(EcuLuaScript&& orig) noexcept;
    virtual ~EcuLuaScript() = default;

    bool hasRequestId() const { return hasRequestId_; };
    std::uint32_t getRequestId() const;
    bool hasResponseId() const { return hasResponseId_; };
    std::uint32_t getResponseId() const;
    bool hasBroadcastId() const { return hasBroadcastId_; };
    std::uint32_t getBroadcastId() const;
    bool hasJ1939SourceAddress() const { return hasJ1939SourceAddress_; };
    std::uint8_t getJ1939SourceAddress() const;

    std::string getSeed(std::uint8_t identifier);
    std::string getDataByIdentifier(const std::string& identifier);
    std::string getDataByIdentifier(const std::string& identifier, const std::string& session);
    std::vector<std::string> getRawRequests();
    std::vector<std::string> getJ1939PGNs();
    J1939PGNData getJ1939PGNData(const std::string& pgn);

    std::string getRaw(const std::string& identStr);
    bool hasRaw(const std::string& identStr);
    static std::vector<std::uint8_t> literalHexStrToBytes(const std::string& hexString);

    static std::string ascii(const std::string& utf8_str) noexcept;
    static std::string getCounterByte(const std::string& msg) noexcept;
    static void getDataBytes(const std::string& msg) noexcept;
    static std::string createHash() noexcept;
    static std::string toByteResponse(std::uint32_t value, std::uint32_t len = sizeof(std::uint32_t)) noexcept;
    static void sleep(unsigned int ms) noexcept;
    void sendRaw(const std::string& response) const;
    std::uint8_t getCurrentSession() const;
    void switchToSession(int ses);

    void registerSessionController(SessionController* pSesCtrl) noexcept;
    void registerIsoTpSender(IsoTpSender* pSender) noexcept;

private:
    sel::State lua_state_{true};
    std::string ecu_ident_;
    SessionController* pSessionCtrl_ = nullptr;
    IsoTpSender* pIsoTpSender_ = nullptr;
    bool hasRequestId_ = false;
    std::uint32_t requestId_;
    bool hasResponseId_ = false;
    std::uint32_t responseId_;
    bool hasBroadcastId_ = false;
    std::uint32_t broadcastId_ = DEFAULT_BROADCAST_ADDR;
    bool hasJ1939SourceAddress_ = false;
    std::uint8_t j1939SourceAddress_;
    std::mutex luaLock_;
};

#endif /* ECU_LUA_SCRIPT_H */
