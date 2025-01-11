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
        SerialComm* serialComm
      ) {
      this->button = button;
      this->console = console;
      this->servo = servo;
      this->lcd = lcd;
      this->pot = pot;
      this->serialComm = serialComm;
      this->currState = AUTOMATIC;

      this->serialComm->registerObserver(this);
      this->button->registerObserver(this);
      this->pot->registerObserver(this);

      this->lcd->init();
      this->lcd->backlight();
      this->changeGatePosition(this->servo->getPosition());
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
          #ifdef DEBUG
          this->console->log("DEBUG: State change MAN->AUT");
          #endif
          }
          break;
        case POT_CHECK_EVENT:
          {
          int servoPos = this->pot->getValue();
          this->changeGatePosition(servoPos);
          break;
          }
        default:
          #ifdef DEBUG
          this->console->log("DEBUG: Default case reached in ChannelControllerFSM::handleManual");
          #endif
          break;
      }
    };

    void handleAutomatic(Event *ev) {
      #ifdef DEBUG
      this->console->log("DEBUG: Evento ricevuto in AUTOMATIC");
      #endif
      switch (ev->getType()) {
        case BUTTON_PRESSED_EVENT:
          {
          this->currState = MANUAL;
          #ifdef DEBUG
          this->console->log("DEBUG: State change AUT->MAN");
          #endif
          break;
          }
        case POS_RECEIVED_EVENT:
          {
          #ifdef DEBUG
          this->console->log("received position");
          #endif
          int pos = this->serialComm->getLastValue();
          this->changeGatePosition(pos);
          break;
          }
        default:
          #ifdef DEBUG
          this->console->log("DEBUG: Default case reached in ChannelControllerFSM::handleAutomatic");
          #endif
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
      this->serialComm->notifyUpdate(this->servo->getPosition());
    }
};

Potentiometer* pot = new Potentiometer(POT_PIN);
ChannelControllerFSM* fsm;
long timeLastCheck;
SerialComm* serialComm;

void setup() {
  Serial.begin(9600);
  while (!Serial){}
  
  ButtonImpl* button = new ButtonImpl(BUTTON_PIN);
  Console* console = new Console();
  ServoMotor* servo = new ServoMotor(SERVO_PIN);
  LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27,20,4);
  serialComm = new SerialComm();
  fsm = new ChannelControllerFSM(button, console, servo, lcd, pot, serialComm);
  timeLastCheck = millis();
  #ifdef DEBUG
  console->log("FINE SETUP");
  #endif
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