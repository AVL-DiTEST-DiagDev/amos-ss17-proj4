#!/bin/bash
if [ $# -lt 1 ]
then
    echo "Usage: $0 <can interface>"
    exit 1
fi

CANINTERFACE=$1

while true
do
    #if [ "$(ip -details link show $CANINTERFACE | grep -e 'ERROR-WARNING\|ERROR-PASSIVE')" != "" ]
    if [ "$(ip -details link show $CANINTERFACE | grep -e 'ERROR-PASSIVE')" != "" ]
    then
        echo "Interface $CANINTERFACE is in ERROR-PASSIVE state - restarting interface"
        ifconfig $CANINTERFACE down
        ifconfig $CANINTERFACE up
    fi
    sleep 1
done
