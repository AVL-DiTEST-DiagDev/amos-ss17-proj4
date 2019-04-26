/** 
 * @file broadcast_receiver.h
 *
 */

#ifndef BROADCAST_RECEIVER_H
#define BROADCAST_RECEIVER_H

#include "isotp_receiver.h"
#include "uds_receiver.h"
#include "session_controller.h"
#include <string>

/// CAN address for broadcast messages like `TesterPresent`
static constexpr canid_t BROADCAST_ADDR = 0x000;

class BroadcastReceiver : public IsoTpReceiver
{
public:

    BroadcastReceiver();
    BroadcastReceiver(canid_t source,
                      const std::string& device,
                      UdsReceiver* udsRec);
    BroadcastReceiver(const BroadcastReceiver& orig) = default;
    BroadcastReceiver& operator =(const BroadcastReceiver& orig) = default;
    BroadcastReceiver(BroadcastReceiver&& orig) = default;
    BroadcastReceiver& operator =(BroadcastReceiver&& orig) = default;
    virtual ~BroadcastReceiver() = default;

    virtual void proceedReceivedData(const std::uint8_t* buffer,
                                     const std::size_t num_bytes) noexcept override;

private:
    UdsReceiver* pUdsReceiver_;

};

#endif /* BROADCAST_RECEIVER_H */

