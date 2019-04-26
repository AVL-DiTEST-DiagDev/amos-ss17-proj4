/**
 * @file electronic_control_unit.cpp
 *
 * This file contains a class which constitutes a Electronic Control Unit (ECU).
 */

#include "electronic_control_unit.h"
#include <array>
#include <unistd.h>
#include <iostream>

using namespace std;

/**
 * Constructor for a ECU which only simulate DoIP
 * @param pEcuScript    pointer to ecu config object
 */
ElectronicControlUnit::ElectronicControlUnit(std::unique_ptr<EcuLuaScript> pEcuScript)
: requId_(pEcuScript->getRequestId())
, respId_(pEcuScript->getResponseId())
, logicalAddress_(pEcuScript->getLogicalAddress())
, udsReceiver_(move(pEcuScript))
{
}

ElectronicControlUnit::ElectronicControlUnit(const string& device, unique_ptr<EcuLuaScript> pEcuScript)
: requId_(pEcuScript->getRequestId())
, respId_(pEcuScript->getResponseId())
, logicalAddress_(pEcuScript->getLogicalAddress())
, sender_(respId_, requId_, device)
, broadcastReceiver_(pEcuScript->getBroadcastId(), device, &udsReceiver_)
, udsReceiver_(respId_, requId_, device, move(pEcuScript), &sender_, &sessionControl_)
, udsReceiverThread_(&IsoTpReceiver::readData, &udsReceiver_)
, broadcastReceiverThread_(&IsoTpReceiver::readData, &broadcastReceiver_)
{
}

ElectronicControlUnit::~ElectronicControlUnit()
{
    broadcastReceiverThread_.join();
    udsReceiverThread_.join();
}

UdsReceiver* ElectronicControlUnit::getUdsReceiver() 
{
    return &udsReceiver_;
}

uint16_t ElectronicControlUnit::getLogicalAddress() const
{
    return logicalAddress_;
}