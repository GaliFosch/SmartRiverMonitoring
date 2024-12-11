#ifndef __SERIAL_COMM__
#define __SERIAL_COMM__

#include "async_fsm.h"
#include "Events.h"
#include "Arduino.h"

#define SERIAL_POLL_PERIOD 1000

class SerialComm : public EventSource {
    public:
        SerialComm();
        void notifyInterrupt(int pin);
        void serialCheck();
        void notifyUpdate(int state, int openingValue);
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