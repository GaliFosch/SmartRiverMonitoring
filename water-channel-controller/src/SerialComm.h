#ifndef __SERIAL_COMM__
#define __SERIAL_COMM__

#include "async_fsm.h"
#include "Events.h"
#include "Arduino.h"

class SerialComm : public EventSource {
    public:
        SerialComm();
        void notifyInterrupt(int pin);
        void serialCheck();
    private:
        int readSerial(char* out_type, int* out_value);
};

class SerialEvent : public Event {
    public:
        SerialEvent(int type, int value);
        int getValue();
};

#endif