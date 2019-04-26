#ifndef DOIP_CONFIGURATION_FILE_H
#define DOIP_CONFIGURATION_FILE_H

#include "selene.h"
#include "utilities.h"
#include <string>
#include <stdio.h>

constexpr char VIN[] = "VIN";
constexpr char LA[] = "LOGICAL_ADDRESS";
constexpr char EID[] = "EID";
constexpr char GID[] = "GID";
constexpr char FA[] = "FURTHER_ACTION";
constexpr char GI[] = "T_TCP_General_Inactivity";

constexpr char ANNOUNCE_NUM[] = "ANNOUNCE_NUM";
constexpr char ANNOUNCE_INTERVAL[] = "ANNOUNCE_INTERVAL";

class DoipConfigurationFile 
{
public:
    DoipConfigurationFile (const std::string& luaScript);
    DoipConfigurationFile (); 
    
    std::string getVin() const;
    std::uint64_t getGid() const;
    std::uint64_t getEid() const;
    std::uint16_t getLogicalAddress() const;
    std::uint8_t getFurtherAction() const;
    std::uint16_t getGeneralInactivity() const;
    int getAnnounceNumber() const;
    int getAnnounceInterval() const;
    bool getEIDflag() const;
    
private:
    sel::State lua_state;
    

    std::string vin;
    std::uint64_t eid;
    std::uint64_t gid;
    std::uint16_t logicalAddress;
    std::uint8_t furtherAction;
    std::uint16_t generalInactivity;

    

    bool EIDflag = false;

    int A_DoIP_Announce_Num;
    int A_DoIP_Announce_Interval;

};

#endif /* DOIP_LUA_SCRIPT_H */



