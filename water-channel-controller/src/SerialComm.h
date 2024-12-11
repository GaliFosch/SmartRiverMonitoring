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
        int getLastValue();
        void notifyUpdate(int state, int openingValue);
    private:
        int readSerial();

        int lastValue = 0;
};

class SerialEvent : public Event {
    public:
        SerialEvent():Event(POS_RECEIVED_EVENT){};
};

#endif