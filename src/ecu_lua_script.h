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
#include "DoIPServer.h"

constexpr char REQ_ID_FIELD[] = "RequestId";
constexpr char RES_ID_FIELD[] = "ResponseId";
constexpr char BROADCAST_ID_FIELD[] = "BroadcastId";
constexpr char READ_DATA_BY_IDENTIFIER_TABLE[] = "ReadDataByIdentifier";
constexpr char READ_SEED[] = "Seed";
constexpr char RAW_TABLE[] = "Raw";
constexpr char LOGICAL_ADDRESS_FIELD[] = "LogicalAddress";
constexpr uint16_t DEFAULT_BROADCAST_ADDR = 0x7DF;

class EcuLuaScript
{
public:
    EcuLuaScript() = delete;
    EcuLuaScript(const std::string& ecuIdent, const std::string& luaScript, DoIPServer* server);
    EcuLuaScript(const EcuLuaScript& orig) = delete;
    EcuLuaScript& operator =(const EcuLuaScript& orig) = delete;
    EcuLuaScript(EcuLuaScript&& orig) noexcept;
    EcuLuaScript& operator =(EcuLuaScript&& orig) noexcept;
    virtual ~EcuLuaScript() = default;

    std::uint16_t getRequestId() const;
    std::uint16_t getResponseId() const;
    std::uint16_t getBroadcastId() const;
    std::uint16_t getLogicalAddress() const;
    std::string getSeed(std::uint8_t identifier) const;
    std::string getDataByIdentifier(const std::string& identifier) const;
    std::string getDataByIdentifier(const std::string& identifier, const std::string& session) const;
    std::string getRaw(const std::string& identStr) const;
    bool hasRaw(const std::string& identStr) const;
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
    std::uint16_t requestId_;
    std::uint16_t responseId_;
    std::uint16_t broadcastId_ = DEFAULT_BROADCAST_ADDR;
    std::uint16_t logicalAddress_;
    DoIPServer* registedServer = nullptr;

};

#endif /* ECU_LUA_SCRIPT_H */
