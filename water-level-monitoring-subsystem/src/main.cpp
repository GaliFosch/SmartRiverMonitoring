#include <Arduino.h>
#include "StateTask.h"
#include "SonarTask.h"
#include "Globals.h"
#include "Scheduler.h"

#define TRIG 5
#define ECHO 4
#define RED_LED 12
#define GREEN_LED 13

Scheduler sched;

void setup() {
  Serial.begin(9600);
  sched.init(200);

  StateTask *stateTask = new StateTask(RED_LED, GREEN_LED);
  stateTask->init(200);

  SonarTask *sonarTask = new SonarTask(TRIG, ECHO);
  sonarTask->init(1000);

  sched.addTask(stateTask);
  sched.addTask(sonarTask);
}

void loop() {
  sched.schedule();
}