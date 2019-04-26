#ifndef START_ARGUMENTS_H
#define START_ARGUMENTS_H

#include <string>
#include <unistd.h>

namespace startargs {
    const std::string DEFAULT_CAN_DEVICE = "vcan0";
    
    void parse_arguments(int argc, char** argv);
    extern bool doip_flag;
    extern bool can_flag;
    extern std::string can_device;
}

#endif /* START_ARGUMENTS_H */

