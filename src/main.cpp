/**
 * @file main.cpp
 *
 * This file contains the `main()`-function with a simple Lua script test. See
 * https://github.com/jeremyong/Selene for usage instructions.
 */

#include "ecu_lua_script.h"
#include "electronic_control_unit.h"
#include "j1939_simulator.h"
#include "ecu_timer.h"
#include "utilities.h"
#include <string>
#include <thread>
#include <csignal>
#include <cstdio>
#include <filesystem>

using namespace std;

vector<ElectronicControlUnit *> udsSimulators;
vector<J1939Simulator *> j1939Simulators;


void start_server(const string &config_file, const string &device)
{
    cout << "start_server for config file: " << config_file
         << " on device: " << device << endl;

    EcuLuaScript *script = new EcuLuaScript("Main", config_file);

    ElectronicControlUnit *udsSimulator = NULL;
    J1939Simulator *j1939Simulator = NULL;

    if(ElectronicControlUnit::hasSimulation(script)) {
        udsSimulator = new ElectronicControlUnit(device, script);
        udsSimulators.push_back(udsSimulator);
    }
    if(J1939Simulator::hasSimulation(script)) {
        j1939Simulator = new J1939Simulator(device, script);
        j1939Simulators.push_back(j1939Simulator);
    }

    if(udsSimulator) {
        udsSimulator->waitForSimulationEnd();
        cout << "UDS terminated" << endl;
        delete udsSimulator;
    }
    if(j1939Simulator) {
        j1939Simulator->waitForSimulationEnd();
        cout << "J1939 terminated" << endl;
        delete j1939Simulator;
    }
}

void signalHandler(int signum) {
    printf("Received signal %d\n",signum);
    if(signum == SIGINT) {
        for (ElectronicControlUnit *simulator : udsSimulators) {
            simulator->stopSimulation();
        }
        for (J1939Simulator *simulator : j1939Simulators) {
            simulator->stopSimulation();
        }
        exit(1);
    }
}
/**
 * The main application only for testing purposes.
 *
 * @param argc: the number of arguments
 * @param argv: the argument list
 * @return 0 on success, otherwise a negative value
 */
int main(int argc, char** argv)
{
    string device = "vcan0";
    if (argc > 1)
    {
        device = argv[1];
    }
    
    // listen to this communication with `isotpsniffer -s 100 -d 200 -c -td vcan0`

    filesystem::current_path(filesystem::path(LUA_CONFIG_PATH));

    vector<string> config_files = utils::getConfigFilenames(".");
    vector<thread> threads;

    signal(SIGINT, signalHandler);

    for (const string &config_file : config_files)
    {
        thread t(start_server, config_file, device);
        threads.push_back(move(t));
        usleep(50000);
    }

    for (unsigned int i = 0; i < threads.size(); ++i)
    {
        threads[i].join();
    }

    return 0;
}

