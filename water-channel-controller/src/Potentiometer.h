#ifndef __POTENTIOMETER_H__
#define __POTENTIOMETER_H__

#include "async_fsm.h"
#include "Events.h"

#define POLL_PERIOD 6000

class Potentiometer : public EventSource{
    public:
        Potentiometer(int pin);
        void notifyInterrupt(int pin);
        void notifyEvent();
        int getValue();
    private:
        int readValue();
        int pin;
        int lastValue = -1;
};

class PotentiometerCheck : public Event {
    public:
        PotentiometerCheck(Potentiometer* source) : Event(POT_CHECK_EVENT) {
            this->source = source;
        }

        Potentiometer* getSource() {
            return this->source;
        }
    private:
        Potentiometer* source;
};

#endif