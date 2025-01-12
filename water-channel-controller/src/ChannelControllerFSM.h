#ifndef __CHANNEL_CONTROLLER_FSM__
#define __CHANNEL_CONTROLLER_FSM__

#include <Arduino.h>
#include <async_fsm.h>
#include <ServoMotor.h>
#include <console.h>
#include <ButtonImpl.h>
#include <LiquidCrystal_I2C.h>
#include <Potentiometer.h>
#include "SerialComm.h"

#define POLL_PERIOD 500

enum State {
  AUTOMATIC,
  MANUAL
};

class ChannelControllerFSM : public AsyncFSM {
  public:
    ChannelControllerFSM (ButtonImpl* button,
        ServoMotor* servo,
        LiquidCrystal_I2C* lcd, 
        Potentiometer* pot,
        SerialComm* serialComm
      );

    void handleEvent(Event* ev);
  
    Potentiometer* getPot();

    State getCurrentState();

  private:
    ServoMotor* servo;
    ButtonImpl* button;
    SerialComm* serialComm;
    LiquidCrystal_I2C* lcd;
    Potentiometer* pot;
    State currState;

    void handleManual(Event* ev);

    void handleAutomatic(Event *ev);

    void changeGatePosition(int value);
    
};

#endif