/** 
 * @file electronic_control_unit.h
 * 
 */

#ifndef ELECTRONIC_CONTROL_UNIT_H
#define ELECTRONIC_CONTROL_UNIT_H

#include "selene.h"
#include "ecu_lua_script.h"
#include "config.h"
#include "session_controller.h"
#include "isotp_sender.h"
#include "broadcast_receiver.h"
#include "uds_receiver.h"
#include "j1939_simulator.h"
#include <string>
#include <thread>
#include <memory>

class ElectronicControlUnit
{
public:
    static bool hasSimulation(EcuLuaScript *pEcuScript);

public:
    ElectronicControlUnit() = delete;
    ElectronicControlUnit(const std::string& device, EcuLuaScript *pEcuScript);
    ElectronicControlUnit(const ElectronicControlUnit& orig) = default;
    ElectronicControlUnit& operator =(const ElectronicControlUnit& orig) = default;
    ElectronicControlUnit(ElectronicControlUnit&& orig) = default;
    ElectronicControlUnit& operator =(ElectronicControlUnit&& orig) = default;
    virtual ~ElectronicControlUnit();

    void stopSimulation();
    void waitForSimulationEnd();


private:
    std::uint32_t requId_;
    std::uint32_t respId_;
    SessionController sessionControl_;
    IsoTpSender sender_;
    BroadcastReceiver broadcastReceiver_;
    UdsReceiver udsReceiver_;
    std::thread udsReceiverThread_;
    std::thread broadcastReceiverThread_;
};

#endif /* ELECTRONIC_CONTROL_UNIT_H */
