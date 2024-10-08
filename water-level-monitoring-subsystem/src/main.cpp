#include <Arduino.h>
#include "StateTask.h"
#include "SonarTask.h"
#include "Globals.h"

#define TRIG 5
#define ECHO 4
#define RED_LED 12
#define GREEN_LED 13

void setup() {
  extern State currState;
  currState = DISCONNECTED;

  StateTask *stateTask = new StateTask(RED_LED, GREEN_LED);
  stateTask->init(200);

  SonarTask *sonarTask = new SonarTask(TRIG, ECHO);
  stateTask->init(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
}