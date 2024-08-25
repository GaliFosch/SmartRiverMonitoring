#ifndef __POTENTIOMETER_H__
#define __POTENTIOMETER_H__

#include "async_fsm.h"
#include "Events.h"

class Potentiometer{
    public:
        Potentiometer(int pin);
    private:
        int readValue();
        int pin;
};

#endif