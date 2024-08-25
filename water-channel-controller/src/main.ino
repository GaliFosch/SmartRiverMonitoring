#include <Arduino.h>
#include <async_fsm.h>
#include <ServoMotor.h>
#include <console.h>
#include <ButtonImpl.h>
#include <LiquidCrystal_I2C.h>
#include <Potentiometer.h>

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
    // TODO: ADD POTENTIOMETER
    ChannelControllerFSM (ButtonImpl* button, Console* console, ServoMotor* servo,
                          LiquidCrystal_I2C* lcd, Potentiometer* pot) {
      this->button = button;
      this->console = console;
      this->servo = servo;
      this->lcd = lcd;
      this->pot = pot;
      this->currState = AUTOMATIC;

      this->button->registerObserver(this);

      this->lcd->init();
      this->lcd->backlight();
      this->lcd->setCursor(2,1);
      this->lcd->print("Automatic");
    }

    void handleEvent(Event* ev) {
      switch (currState) {
        case AUTOMATIC:
          if (ev->getType() == BUTTON_PRESSED_EVENT) {
            this->lcd->clear();
            this->lcd->setCursor(2,1);
            this->lcd->print("Manual");
            this->currState = MANUAL;
          }
          break;
        case MANUAL:
          if (ev->getType() == BUTTON_PRESSED_EVENT) {
            this->lcd->clear();
            this->lcd->setCursor(2,1);
            this->lcd->print("Automatic");
            this->currState = AUTOMATIC;
          }
          else if (ev->getType() == POT_MOVED_EVENT) {
            // idkkkkkk
          }
          else if (ev->getType() == POS_RECEIVED_EVENT) {
            this->lcd->clear();
            this->lcd->setCursor(2,1);
            this->lcd->print("Manual");
            this->currState = DASHBOARD;
          }
          break;
        case DASHBOARD:
          break;
      }
    }
  
  private:
    ServoMotor* servo;
    ButtonImpl* button;
    Console* console;
    LiquidCrystal_I2C* lcd;
    Potentiometer* pot;
    State currState;
};

ChannelControllerFSM* fsm;

void setup() {
  ButtonImpl* button = new ButtonImpl(BUTTON_PIN);
  Console* console = new Console();
  ServoMotor* servo = new ServoMotor(SERVO_PIN);
  LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27,20,4);
  Potentiometer* pot = new Potentiometer(POT_PIN);
  fsm = new ChannelControllerFSM(button, console, servo, lcd, pot);
}

void loop() {
  fsm->checkEvents();
}