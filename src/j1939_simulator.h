/**
 * @file j1939_simulator.h
 *
 */

#ifndef J1939_SIMULATOR_H
#define J1939_SIMULATOR_H

#include <cstdint>
#include <string>
#include <memory>
#include <thread>

#include "ecu_lua_script.h"


class J1939Simulator
{
public:
    static bool hasSimulation(EcuLuaScript *pEcuScript);

public:
    J1939Simulator() = delete;
    J1939Simulator(const std::string& device,
                   EcuLuaScript* pEcuScript);
    virtual ~J1939Simulator();
    int openReceiver() noexcept;
    void closeReceiver() noexcept;
    int readData() noexcept;
    void startPeriodicSenderThreads();
    void proceedReceivedData(const uint8_t* buffer, const size_t num_bytes, const uint8_t sourceAddress) noexcept;
    void sendVIN(const uint8_t targetAddress) noexcept;
    void sendCyclicMessage(const std::string pgn) noexcept;

    void stopSimulation();
    void waitForSimulationEnd();


private:
    uint8_t source_address_;
    std::string device_;
    EcuLuaScript* pEcuScript_;
    int receive_skt_ = -1;
    bool isOnExit_ = false;
    //std::thread j1939ReceiverThread_;
    std::vector<std::thread*> cyclicMessageThreads;

    sel::State lua_state_;
    uint16_t *pgns_;

    int openBroadcastSocket() const noexcept;
    uint32_t parsePGN(std::string pgn) const noexcept;
    bool isBusActive();

};

#endif // J1939_SIMULATOR_H