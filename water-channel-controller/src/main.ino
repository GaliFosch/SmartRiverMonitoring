#include <Arduino.h>
#include <async_fsm.h>
#include <ServoMotor.h>
#include <console.h>
#include <ButtonImpl.h>
#include <LiquidCrystal_I2C.h>
#include <Potentiometer.h>
#include "TimerOne.h"

#define BUTTON_PIN 3
#define POT_PIN A1
#define SERVO_PIN 10

enum State {
  AUTOMATIC,
  MANUAL,
  DASHBOARD
};

class ChannelControllerFSM : public AsyncFSM {
  public:
    ChannelControllerFSM (ButtonImpl* button, Console* console, ServoMotor* servo,
                          LiquidCrystal_I2C* lcd, Potentiometer* pot) {
      this->button = button;
      this->console = console;
      this->servo = servo;
      this->lcd = lcd;
      this->pot = pot;
      this->currState = AUTOMATIC;

      this->button->registerObserver(this);
      this->pot->registerObserver(this);

      this->lcd->init();
      this->lcd->backlight();
      this->lcd->setCursor(2,1);
      this->lcd->print("Automatic");
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

  private:
    ServoMotor* servo;
    ButtonImpl* button;
    Console* console;
    LiquidCrystal_I2C* lcd;
    Potentiometer* pot;
    State currState;

    void handleManual(Event* ev) {
      switch (ev->getType()) {
        case BUTTON_PRESSED_EVENT:
          {
          this->lcd->clear();
          this->lcd->setCursor(2,1);
          this->lcd->print("Automatic");
          this->console->log("DEBUG: State change MAN->AUT");
          this->currState = AUTOMATIC;
          }
          break;
        case POT_CHECK_EVENT:
          {
          int servoPos = this->pot->getValue();
          this->servo->changePosition(servoPos);
          break;
          }
        case POS_RECEIVED_EVENT:
          {
          this->lcd->clear();
          this->lcd->setCursor(2,1);
          this->lcd->print("Manual");
          this->currState = DASHBOARD;
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
          this->lcd->clear();
          this->lcd->setCursor(2,1);
          this->lcd->print("Manual");
          this->console->log("DEBUG: State change AUT->MAN");
          this->currState = MANUAL;
          break;
          }
        default:
          this->console->log("DEBUG: Default case reached in ChannelControllerFSM::handleAutomatic");
          break;
      }
    }

    void handleDashboard(Event *ev) {

    }
};

Potentiometer* pot = new Potentiometer(POT_PIN);
ChannelControllerFSM* fsm;
long timeLastPotCheck;

void setup() {
  ButtonImpl* button = new ButtonImpl(BUTTON_PIN);
  Console* console = new Console();
  ServoMotor* servo = new ServoMotor(SERVO_PIN);
  LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27,20,4);
  fsm = new ChannelControllerFSM(button, console, servo, lcd, pot);
  timeLastPotCheck = millis();
}

void loop() {
  if (millis() - timeLastPotCheck > POLL_PERIOD) {
    timeLastPotCheck = millis();
    pot->notifyEvent();
  }
  fsm->checkEvents();
}