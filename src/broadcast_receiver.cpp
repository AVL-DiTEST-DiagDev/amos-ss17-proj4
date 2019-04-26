/** 
 * @file broadcast_receiver.cpp
 * 
 * This file contains the broadcast receiver which handles messages like 
 * `TesterPresent`.
 */

#include "broadcast_receiver.h"
#include "service_identifier.h"
#include <iostream>

using namespace std;

/**
 *  Default Constructor which is used when simulation only DoIP
 */
BroadcastReceiver::BroadcastReceiver() { }

BroadcastReceiver::BroadcastReceiver(canid_t source,
                                     const string& device,
                                     UdsReceiver* pUdsRec)
: IsoTpReceiver(BROADCAST_ADDR, source, device)
, pUdsReceiver_(pUdsRec)
{
}

/**
 * Handles the broadcast messages (e.g. `TesterPresent`).
 * 
 * @param buffer: the buffer of the UDS message
 * @param num_bytes: the number of transmitted data in bytes
 */
void BroadcastReceiver::proceedReceivedData(const uint8_t* buffer,
                                            const size_t num_bytes) noexcept
{
    switch (buffer[0])
    {
        case TESTER_PRESENT_REQ:
        {
            if(buffer[1] == 0x80 && num_bytes >= 2)
            {
                pUdsReceiver_->pSessionCtrl_->reset();
            }
            else
            {
                // -> beware of arrows ->
                pUdsReceiver_->pSessionCtrl_->reset();
                constexpr array<uint8_t, 1> tp = {TESTER_PRESENT_RES};
                pUdsReceiver_->pIsoTpSender_->sendData(tp.data(), tp.size());
            }
            break;
        }
        default:
        {
            pUdsReceiver_->proceedReceivedData(buffer, num_bytes);
        }
    }
}
