#include <Arduino.h>
#include <async_fsm.h>
#include <ServoMotor.h>
#include <console.h>
#include <ButtonImpl.h>
#include <LiquidCrystal_I2C.h>
#include <Potentiometer.h>
#include "TimerOne.h"
#include "SerialComm.h"

#define BUTTON_PIN 3
#define POT_PIN A1
#define SERVO_PIN 10

#define POLL_PERIOD 500

enum State {
  AUTOMATIC,
  MANUAL,
  DASHBOARD
};

class ChannelControllerFSM : public AsyncFSM {
  public:
    ChannelControllerFSM (ButtonImpl* button, 
        Console* console, 
        ServoMotor* servo,
        LiquidCrystal_I2C* lcd, 
        Potentiometer* pot,
        SerialComm* serialcomm
      ) {
      this->button = button;
      this->console = console;
      this->servo = servo;
      this->lcd = lcd;
      this->pot = pot;
      this->serialComm = serialComm;
      this->currState = AUTOMATIC;

      this->button->registerObserver(this);
      this->pot->registerObserver(this);

      this->lcd->init();
      this->lcd->backlight();
      this->lcd->setCursor(2,1);
      this->lcd->print("Automatic:");
      this->lcd->print(this->servo->getPosition());
      this->lcd->print("%");
    }

    void handleEvent(Event* ev) {
      switch (currState) {
        case AUTOMATIC:
          this->handleAutomatic(ev);
          break;
        case MANUAL:
          this->handleManual(ev);
          break;
        case DASHBOARD:
          this->handleDashboard(ev);
          break;
        default:
          this->console->log("DEBUG: Default value reached in ChannelControllerFSM::handleEvent");
      }
    }
  
    Potentiometer* getPot() {
      return this->pot;
    }

    State getCurrentState() {
      return currState;
    }

  private:
    ServoMotor* servo;
    ButtonImpl* button;
    Console* console;
    SerialComm* serialComm;
    LiquidCrystal_I2C* lcd;
    Potentiometer* pot;
    State currState;

    void handleManual(Event* ev) {
      switch (ev->getType()) {
        case BUTTON_PRESSED_EVENT:
          {
          this->currState = AUTOMATIC;
          this->changeGatePosition(this->servo->getPosition());
          this->console->log("DEBUG: State change MAN->AUT");
          }
          break;
        case POT_CHECK_EVENT:
          {
          int servoPos = this->pot->getValue();
          this->changeGatePosition(servoPos);
          break;
          }
        default:
          this->console->log("DEBUG: Default case reached in ChannelControllerFSM::handleManual");
          break;
      }
    };

    void handleAutomatic(Event *ev) {
      switch (ev->getType()) {
        case BUTTON_PRESSED_EVENT:
          {
          this->currState = MANUAL;
          this->changeGatePosition(this->pot->getValue());
          this->console->log("DEBUG: State change AUT->MAN");
          break;
          }
        case POS_RECEIVED_EVENT:
          {
          int servoPos = this->pot->getValue();
          this->changeGatePosition(servoPos);
          }
        default:
          this->console->log("DEBUG: Default case reached in ChannelControllerFSM::handleAutomatic");
          break;
      }
    }

    void handleDashboard(Event *ev) {

    }

    void changeGatePosition(int value){
      this->servo->changePosition(value);
      this->lcd->clear();
      this->lcd->setCursor(2,1);
      if(this->currState == AUTOMATIC)
        this->lcd->print("Automatic: ");
      else
        this->lcd->print("Manual: ");
      this->lcd->print(this->servo->getPosition());
      this->lcd->print("%");
      delay(50);
      this->serialComm->notifyUpdate(this->currState, this->servo->getPosition());
    }
};

Potentiometer* pot = new Potentiometer(POT_PIN);
ChannelControllerFSM* fsm;
long timeLastCheck;
ServoMotor* servo;
SerialComm* serialComm;
void setup() {
  ButtonImpl* button = new ButtonImpl(BUTTON_PIN);
  Console* console = new Console();
  ServoMotor* servo = new ServoMotor(SERVO_PIN);
  LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27,20,4);
  fsm = new ChannelControllerFSM(button, console, servo, lcd, pot, serialComm);
  
  timeLastCheck = millis();
}

void loop() {
  if ((millis() - timeLastCheck > POLL_PERIOD)) {
    timeLastCheck = millis();
    if(fsm->getCurrentState()==MANUAL)
      pot->notifyEvent();
    else
      serialComm->serialCheck();
  }
  fsm->checkEvents();
}