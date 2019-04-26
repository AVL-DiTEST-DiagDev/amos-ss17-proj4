/**
 * @file isotp_receiver.h
 *
 */

#ifndef ISOTP_RECEIVER_H
#define ISOTP_RECEIVER_H

#include <cstddef>
#include <string>
#include <linux/can.h>

class IsoTpReceiver
{
public:
    IsoTpReceiver();
    IsoTpReceiver(canid_t source, canid_t dest, const std::string& device);
    IsoTpReceiver(const IsoTpReceiver& orig) = default;
    IsoTpReceiver& operator =(const IsoTpReceiver& orig) = default;
    IsoTpReceiver(IsoTpReceiver&& orig) = default;
    IsoTpReceiver& operator =(IsoTpReceiver&& orig) = default;
    virtual ~IsoTpReceiver();

    int openReceiver() noexcept;
    void closeReceiver() noexcept;
    int readData() noexcept;

protected:
    virtual void proceedReceivedData(const std::uint8_t* buffer,
                                     const std::size_t num_bytes) noexcept;

private:
    canid_t source_;
    canid_t dest_;
    std::string device_;
    int receive_skt_ = -1;
    bool isOnExit_ = false;

};

#endif /* ISOTP_RECEIVER_H */
