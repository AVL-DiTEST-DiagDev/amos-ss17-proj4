/** 
 * @file uds_receiver.h
 *
 */

#ifndef UDS_RECEIVER_H
#define UDS_RECEIVER_H

#include "isotp_receiver.h"
#include "isotp_sender.h"
#include "ecu_lua_script.h"
#include "session_controller.h"
#include <memory>

class UdsReceiver : public IsoTpReceiver
{
    friend class BroadcastReceiver;

public:
    UdsReceiver() = delete;
    UdsReceiver(std::unique_ptr<EcuLuaScript> pEcuScript);
    UdsReceiver(canid_t source,
                canid_t dest,
                const std::string& device,
                std::unique_ptr<EcuLuaScript> pEcuScript,
                IsoTpSender* pSender,
                SessionController* pSesCtrl);
    UdsReceiver(const UdsReceiver& orig) = default;
    UdsReceiver& operator =(const UdsReceiver& orig) = default;
    UdsReceiver(UdsReceiver&& orig) noexcept;
    UdsReceiver& operator =(UdsReceiver&& orig) noexcept;
    virtual ~UdsReceiver() = default;

    static std::uint16_t generateSeed();
    virtual void proceedReceivedData(const uint8_t* buffer, const size_t num_bytes) noexcept override;
    std::vector<unsigned char> proceedDoIPData(const unsigned char* buffer, const size_t num_bytes) noexcept;

private:
    std::unique_ptr<EcuLuaScript> pEcuScript_;
    IsoTpSender* pIsoTpSender_ = nullptr;
    SessionController* pSessionCtrl_ = nullptr;
    std::uint8_t securityAccessType_ = 0x00;

    void readDataByIdentifier(const std::uint8_t* buffer, const std::size_t num_bytes) noexcept;
    void diagnosticSessionControl(const std::uint8_t* buffer, const std::size_t num_bytes);
    void securityAccess(const std::uint8_t* buffer, const std::size_t num_bytes) noexcept;

    std::string intToHexString(const uint8_t* buffer, const std::size_t num_bytes);
};

#endif /* UDS_RECEIVER_H */

