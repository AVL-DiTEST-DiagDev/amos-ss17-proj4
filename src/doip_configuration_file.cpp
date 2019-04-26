#include "doip_configuration_file.h"

/**
 * Default Constructor if no lua file was found.
 */
DoipConfigurationFile ::DoipConfigurationFile(){ //if there is no config for the doip server or the ecus this default configuration will be used
    
    std::cout<<"Setting Default Configuration for the DoIPServer"<<std::endl;
    this->A_DoIP_Announce_Num = 3;
    this->A_DoIP_Announce_Interval = 500;
    this->vin = "00000000000000000";
    this->logicalAddress = int(0x0000);
    this->EIDflag = true; 
    this->gid = 0x000000000000;
    this->furtherAction = int(0x00);    
}


/**
 * Constructor. Reads lua file and save fields. 
 * @param luaScript     path to the lua script file
 */
DoipConfigurationFile ::DoipConfigurationFile (const std::string& luaScript) {

    const std::string id = "Main";
    
    if(utils::existsFile(luaScript)) {
        lua_state.Load(luaScript);
        
        if(lua_state[id.c_str()].exists()) {
            
            auto lua_announce_num = lua_state[id.c_str()][ANNOUNCE_NUM];
            if(lua_announce_num.exists()) {
                //set announce number from lua file
                this->A_DoIP_Announce_Num = lua_announce_num;
            } else {
                //set announce number to default
                this->A_DoIP_Announce_Num = 3;
            }
            
            auto lua_announce_interval = lua_state[id.c_str()][ANNOUNCE_INTERVAL];
            if(lua_announce_interval.exists()) {
                //set announce interval from lua file
                this->A_DoIP_Announce_Interval = lua_announce_interval;
            } else {
                //set announce interval to default
                this->A_DoIP_Announce_Interval = 500;
            }
            
            std::string lua_vin = lua_state[id.c_str()][VIN];
            if(!lua_vin.empty()) {
                //set vin from lua file
                this->vin = lua_vin;
            } else {
                //set vin to default
                this->vin = "00000000000000000";
            }
            
            auto lua_logicaladdress = lua_state[id.c_str()][LA];
            if(lua_logicaladdress.exists()) {
                //set la from lua
                this->logicalAddress = int(lua_logicaladdress);
            } else {
                //set la to default
                this->logicalAddress = int(0x0000);
            }
            
            std::string lua_eid = lua_state[id.c_str()][EID];
            if(!lua_eid.empty()) {
                //set eid from lua              
                this->eid = std::stoull(lua_eid);       
            } else {
                
                this->EIDflag = true;     
            }
            
            std::string lua_gid = lua_state[id.c_str()][GID];
            if(!lua_gid.empty()) {
                //set gid from lua
                this->gid = std::stoull(lua_gid);
            } else {
                //set gid to default
                this->gid = 0x000000000000;
            }
            
            auto lua_furtheraction = lua_state[id.c_str()][FA];
            if(lua_furtheraction.exists()) {
                //set furtheraction from lua
                this->furtherAction = int(lua_furtheraction);
            } else {
                //set furtheraction to default
                this->furtherAction = int(0x00);
            }
            
            auto generalInactivity = lua_state[id.c_str()][GI];
            if(generalInactivity.exists()) {
                //set general inactivity time from lua
                generalInactivity = int(generalInactivity);
            } else {
                //set general inactivity time to default
                generalInactivity = 300;
            }
            
        } else {
            throw std::invalid_argument("Invalid Lua configuration file for doip simulation");
        }
    } else {
        throw std::invalid_argument("No Lua configuration file for doip simulation found");
    }
}


/**
 * Gets the VIN from the lua configuration file
 * @return      vin as string
 */
std::string DoipConfigurationFile ::getVin() const 
{
    return this->vin;
}

/**
 * Gets the Logical Address from the lua configuration file
 * @return      logical address
 */
std::uint16_t DoipConfigurationFile ::getLogicalAddress() const
{
    return this->logicalAddress;
}


/**
 * Gets the EID from the lua configuration file
 * @return      eid as string
 */
unsigned long DoipConfigurationFile ::getEid() const
{
    return this->eid;
}

/**
 * Gets the GID from the lua configuration file
 * @return      gid as string
 */
unsigned long DoipConfigurationFile ::getGid() const 
{
    return this->gid;
}

/**
 * Gets the Further Action Code from the lua configuration file
 * @return      further action code
 */
std::uint8_t DoipConfigurationFile ::getFurtherAction() const
{
    return this->furtherAction;
}

/*
 * Gets the T_TCP_General_Inactivity time from the lua configuration file
 * @return      general inactivity time in seconds
 */
std::uint16_t DoipConfigurationFile::getGeneralInactivity() const {
    return this->generalInactivity;
}

/**
 * Gets the number of announcements messages which will be sended
 * @return      times the announcment message
 */
int DoipConfigurationFile ::getAnnounceNumber() const 
{
    return this->A_DoIP_Announce_Num;
}

/**
 * Gets the timing parameter which specifies the time between the
 * announcement messages
 * @return      delay in milliseconds
 */
int DoipConfigurationFile ::getAnnounceInterval() const
{
    return this->A_DoIP_Announce_Interval;
}

bool DoipConfigurationFile ::getEIDflag() const
{
    return this->EIDflag;
}
