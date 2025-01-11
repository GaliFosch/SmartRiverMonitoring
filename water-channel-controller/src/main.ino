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


ChannelControllerFSM* fsm;

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  while (!Serial){}
  #endif
  Potentiometer* pot = new Potentiometer(POT_PIN);
  ButtonImpl* button = new ButtonImpl(BUTTON_PIN);
  ServoMotor* servo = new ServoMotor(SERVO_PIN);
  LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27,20,4);
  SerialComm* serialComm = new SerialComm();
  fsm = new ChannelControllerFSM(button, servo, lcd, pot, serialComm);
  #ifdef DEBUG
  Serial.println("FINE SETUP");
  #endif
}

void loop() {
  fsm->checkEvents();
}