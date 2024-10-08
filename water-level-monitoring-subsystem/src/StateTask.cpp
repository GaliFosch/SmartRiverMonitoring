#include "StateTask.h"
#include "Globals.h"

// TODO: Remove this import
#include <Arduino.h> 

StateTask::StateTask(int redPin, int greenPin) {
    this->red = new Led(redPin);
    this->green = new Led(greenPin);
}

void StateTask::init(int period) {
    Task::init(period);
    this->red->switchOn();
    this->green->switchOff();
}

void StateTask::tick() {
    switch (currState) {
        case DISCONNECTED:
            Serial.println("DEBUG State: DISCONNECTED");
            if (1) {
                currState = CONNECTED;
                this->red->switchOff();
                this->green->switchOn();
            }
            break;
        case CONNECTED:
            Serial.println("DEBUG State: CONNECTED");
            break;
        default:
            break;
    }
}