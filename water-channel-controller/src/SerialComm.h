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
        int readSerial();
};

class SerialEvent : public Event {
    public:
        SerialEvent(int value);
        int getValue();
    private:
        int value;
};

#endif