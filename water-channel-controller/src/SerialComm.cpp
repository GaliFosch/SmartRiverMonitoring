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
    char type;
    int value;
    if(readSerial(&type, &value)!=0) return;

    int eventType = 0;
    switch(type){
        case 'v':
        eventType = POS_RECEIVED_EVENT;
        break;
        case 'd':
        eventType = DASHBOARD_START_EVENT;
        break;
        case 'e':
        eventType = DASHBOARD_END_EVENT;
        break;
        default:
        return;
    }

    generateEvent(new SerialEvent(eventType, value));
}

int SerialComm::readSerial(char* out_type, int* out_value)
{
    if(!Serial.available()) return -1;
    String line = Serial.readString();
    String valueS = line.substring(1);
    *out_type = line.charAt(0);
    *out_value = valueS.toInt();
    return 0;
}

SerialEvent::SerialEvent(int type, int value): Event(type), value(value)
{
}

int SerialEvent::getValue()
{
    return this->value;
}
