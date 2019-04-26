/**
 * @file isotp_sender.h
 *
 */

#ifndef ISOTP_SENDER_H
#define ISOTP_SENDER_H

#include <cstddef>
#include <string>
#include <linux/can.h>

class IsoTpSender
{
public:
    IsoTpSender();
    IsoTpSender(canid_t source, canid_t dest, const std::string& device);
    IsoTpSender(const IsoTpSender& orig) = default;
    IsoTpSender& operator =(const IsoTpSender& orig) = default;
    IsoTpSender(IsoTpSender&& orig) = default;
    IsoTpSender& operator =(IsoTpSender&&) = default;
    virtual ~IsoTpSender();

    int openSender() noexcept;
    void closeSender() noexcept;
    int sendData(const void* buffer, std::size_t size) const noexcept;

private:
    canid_t source_;
    canid_t dest_;
    std::string device_;
    int send_skt_ = -1;
};

#endif /* ISOTP_SENDER_H */

