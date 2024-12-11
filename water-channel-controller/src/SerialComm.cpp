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
    if(value<0) return;

    generateEvent(new SerialEvent(value));
}

int SerialComm::readSerial()
{
    if(!Serial.available()) return -1;
    String line = Serial.readString();
    int value = line.toInt();
    return value;
}

SerialEvent::SerialEvent(int value): Event(POS_RECEIVED_EVENT), value(value)
{
}

int SerialEvent::getValue()
{
    return this->value;
}
