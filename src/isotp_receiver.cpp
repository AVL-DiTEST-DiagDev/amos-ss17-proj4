/**
 * @file isotp_receiver.cpp
 * 
 * This file holds a basic receiver class to transmit data over CAN using the 
 * ISO-TP protocol. The received data is handled by the 
 * `proceedReceivedData()`-function. To do something useful with the received
 * information, derive a new class from this one and override 
 * `proceedReceivedData()` with the new data handling (e.g. a routine to send
 * a proper response).
 */

#include "isotp_receiver.h"
#include "can/isotp.h"
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <iomanip>

using namespace std;

constexpr size_t MAX_BUFSIZE = 4096; ///< max. 4096 bytes per UDS message

/**
 * Constructor. Opens the receiver socket.
 * 
 * @param source: the source CAN address
 * @param dest: the destination CAN address
 * @param device: the device used for the transmission (e.g. "vcan0")
 */
IsoTpReceiver::IsoTpReceiver(canid_t source,
                             canid_t dest,
                             const string& device)
: source_(source)
, dest_(dest)
, device_(device)
{
    int err = openReceiver();
    if (err != 0)
    {
        throw exception();
    }
}

/**
 * Destructor. Closes the receiver socket.
 */
IsoTpReceiver::~IsoTpReceiver()
{
}

/**
 * Opens the socket for receiving the via ISO_TP transmitted data.
 *
 * @return 0 on success, otherwise a negative value
 * @see IsoTpReceiver::closeReceiver()
 */
int IsoTpReceiver::openReceiver() noexcept
{
    isOnExit_ = false;
    struct sockaddr_can addr;

    cout << "receiver tx_id: " << dec << (uint32_t)source_ << " - ";
    addr.can_addr.tp.tx_id = source_;
    if(source_ > 0x7FFu) {
        cout << "29bit";
        addr.can_addr.tp.tx_id |= CAN_EFF_FLAG;
    }
    cout << endl;

    cout << "receiver rx_id: " << dec << (uint32_t)dest_ << " - ";
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

    receive_skt_ = skt;
    return 0;
}

/**
 * Closes the socket for receiving data.
 * 
 * @see IsoTpReceiver::openReceiver()
 */
void IsoTpReceiver::closeReceiver() noexcept
{
    isOnExit_ = true;

    if (receive_skt_ < 0)
    {
        cerr << __func__ << "() Receiver socket is already closed!\n";
        return;
    }
    close(receive_skt_);
    receive_skt_ = -1;
}

/**
 * Reads the data from the opened receiver socket. The handling of the received
 * data is controlled by the inside nested `proceedReceivedData()` function. To 
 * change its behavior, deduce a new class form `IsoTpSocket` and override the
 * `proceedReceivedData()`-function to your likings.
 * 
 * @return 0 on success, otherwise a negative value
 * @see IsoTpReceiver::proceedReceivedData()
 * @see IsoTpReceiver::closeReceiver()
 */
int IsoTpReceiver::readData() noexcept
{
    if (receive_skt_ < 0)
    {
        cerr << __func__ << "() Can not read data. Receiver socket invalid!\n";
        return -1;
    }

    uint8_t msg[MAX_BUFSIZE];
    size_t num_bytes;
    do
    {
        num_bytes = read(receive_skt_, msg, MAX_BUFSIZE);
        cout << "READ returned" << endl;
        if (num_bytes > 0 && num_bytes < MAX_BUFSIZE)
        {
            proceedReceivedData(msg, num_bytes);
        }
    }
    while (!isOnExit_);

    return 0;
}

/**
 * Proceeds the received data. This is the default implementation, which simply
 * prints out the received data in hexadecimal notation to `std::out`. This 
 * function is supposed be overridden to do something useful with the received 
 * data. To do this, derive a new class from `IsoTpSocket` and override the 
 * function to your likings.
 * 
 * @see IsoTpReceiver::readData()
 */
void IsoTpReceiver::proceedReceivedData(const uint8_t* buffer, const size_t num_bytes) noexcept
{
    cout << __func__ << "() Received " << dec << num_bytes << " bytes.\n";
    for (size_t i = 0; i < num_bytes; i++)
    {
        cout << " 0x"
                << hex
                << setw(2)
                << setfill('0')
                << static_cast<int> (buffer[i]);
    }
    cout << endl;
}