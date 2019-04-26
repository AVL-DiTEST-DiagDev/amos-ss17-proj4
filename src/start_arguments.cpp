#include "start_arguments.h"
#include <string>
#include <iostream>

//Initialize extern variables
bool startargs::doip_flag = false;
bool startargs::can_flag = false;
std::string startargs::can_device;

/**
 * Parses the arguments when starting the car simulator.
 * Usage:   ./car-simulator doip vcan0  for doip and can simulation
 *          ./car-simulator             for doip and can simulation
 *          ./car-simulator doip        for doip simulation
 *          ./car-simulator vcan0       for can simulation
 */
void startargs::parse_arguments(int argc, char** argv) {
    
    //when no arguments passed, doip and can simulation will be used
    if(argc <= 1) {
        startargs::doip_flag = true;
        startargs::can_flag = true;
        startargs::can_device = startargs::DEFAULT_CAN_DEVICE;
        return;
    }
    
    for(int arg_index = 1; arg_index < argc; arg_index++) {
        if(std::string(argv[arg_index]).find("doip") != std::string::npos) {
            startargs::doip_flag = true;
        } else {
            //if the argument value is not doip then we assume it is a can device
            //the latest argument which is not doip will be saved as can device 
            startargs::can_flag = true;
            startargs::can_device = std::string(argv[arg_index]);
        }
    }
}
