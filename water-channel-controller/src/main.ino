#include <Arduino.h>
#include <async_fsm.h>
#include <ServoMotor.h>
#include <console.h>
#include <ButtonImpl.h>
#include <LiquidCrystal_I2C.h>
#include <Potentiometer.h>
#include "SerialComm.h"

#include <ChannelControllerFSM.h>

#define BUTTON_PIN 3
#define POT_PIN A1
#define SERVO_PIN 10

#define POLL_PERIOD 500

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