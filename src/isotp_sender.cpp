/**
 * @file isotp_sender.cpp
 * 
 * This file holds a basic sender class to transmit data over CAN using the 
 * ISO-TP protocol.
 */

#include "isotp_sender.h"
#include "can/isotp.h"
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

constexpr size_t MAX_UDS_MSG_SIZE = 4096; ///< max. 4096 bytes per UDS message

#define NUM_SEND_RETRIES 5

/**
 * Constructor. Opens the sender socket.
 * 
 * @param source: the source CAN address
 * @param dest: the destination CAN address
 * @param device: the device used for the transmission (e.g. "vcan0")
 */
IsoTpSender::IsoTpSender(canid_t source,
                         canid_t dest,
                         const string& device)
: source_(source)
, dest_(dest)
, device_(device)
{
    int err = openSender();
    if (err != 0)
    {
        throw exception();
    }
}

/**
 * Destructor. Closes the sender socket.
 */
IsoTpSender::~IsoTpSender()
{
}

/**
 * Opens the ISO_TP socket for sending.
 *
 * @return 0 on success, otherwise a negative value
 * @see IsoTpSender::closeSender()
 */
int IsoTpSender::openSender() noexcept
{
    struct sockaddr_can addr;
    cout << "sender: tx_id: " << source_ << " - ";
    addr.can_addr.tp.tx_id = source_;
    if(source_ > 0x7FFu) {
        cout << "29bit";
        addr.can_addr.tp.tx_id |= CAN_EFF_FLAG;
    }
    cout << endl;

    cout << "sender: rx_id: " << dest_ << " - ";
    addr.can_addr.tp.rx_id = dest_;
    if(dest_ > 0x7FFu) {
        cout << "29bit";
        addr.can_addr.tp.rx_id |= CAN_EFF_FLAG;
    }
    cout << endl;
    addr.can_family = AF_CAN;

    int skt = socket(PF_CAN, SOCK_DGRAM, CAN_ISOTP);
    if (skt < 0)
    {
        cerr << __func__ << "() socket: " << strerror(errno) << '\n';
        return -1;
    }

    static struct can_isotp_options opts;
    opts.flags |= (CAN_ISOTP_TX_PADDING | CAN_ISOTP_RX_PADDING);
    setsockopt(skt, SOL_CAN_ISOTP, CAN_ISOTP_OPTS, &opts, sizeof(opts));

    struct ifreq ifr;
    strncpy(ifr.ifr_name, device_.c_str(), device_.length() + 1);
    ioctl(skt, SIOCGIFINDEX, &ifr);
    addr.can_ifindex = ifr.ifr_ifindex;

    auto bind_res = bind(skt,
                         reinterpret_cast<struct sockaddr*> (&addr),
                         sizeof(addr));
    if (bind_res < 0)
    {
        cerr << __func__ << "() bind: " << strerror(errno) << '\n';
        close(skt);
        return -2;
    }
    send_skt_ = skt;

    return 0;
}

/**
 * Closes the ISO_TP socket for sending.
 * 
 * @see IsoTpSender::openSender()
 */
void IsoTpSender::closeSender() noexcept
{
    if (send_skt_ < 0)
    {
        cerr << __func__ << "() Sender socket is already closed!\n";
        return;
    }
    close(send_skt_);
    send_skt_ = -1;
}

/**
 * Send the given number of bytes located in the buffer. The sender socket
 * has to be opened first.
 * 
 * @param buffer: the pointer to the data buffer
 * @param size: the number of bytes to write in the socket
 * @return the number of sent bytes or a negative value on error
 * @see IsoTpSender::openSender()
 * @see IsoTpSender::closeSender()
 */
int IsoTpSender::sendData(const void* buffer, size_t size) const noexcept
{
    if (size > MAX_UDS_MSG_SIZE)
    {
        cerr << __func__ << "() Message size exceeds the maximum of 4096 bytes!\n";
        return 0;
    }

    if (send_skt_ < 0)
    {
        cerr << __func__ << "() Invalid socket file descriptor!\n";
        return -1;
    }

    int bytes_sent = 0;
    int retries = NUM_SEND_RETRIES;
    while(retries > 0)
    {
        bytes_sent = write(send_skt_, buffer, size);
        if (bytes_sent < 0)
        {
            cerr << __func__ << "() write: " << strerror(errno) << '\n';
            retries--;
            usleep(1000*5); // wait 5ms before retry
        } else {
            retries = 0;
        }
    }

    return bytes_sent;
}
