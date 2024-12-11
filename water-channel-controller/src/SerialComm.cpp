#include "SerialComm.h"

SerialComm::SerialComm()
{
    if(!Serial){
        Serial.begin(9600);
        while(!Serial){}
    }
}

void SerialComm::notifyInterrupt(int pin)
{
}

void SerialComm::serialCheck()
{
    int value = readSerial();
    if(value<0 || value>100) return;
    lastValue = value;
    generateEvent(new SerialEvent());
}

int SerialComm::getLastValue()
{
    return this->lastValue;
}

void SerialComm::notifyUpdate(int state, int openingValue)
{
}

int SerialComm::readSerial()
{
    if(!Serial.available()) return -1;
    String line = Serial.readString();
    int value = line.toInt();
    return value;
}
