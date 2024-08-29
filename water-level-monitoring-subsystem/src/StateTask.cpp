#include "StateTask.h"
#include "Globals.h"

StateTask::StateTask(int redPin, int greenPin) {
    this->red = new Led(redPin);
    this->green = new Led(greenPin);
}

void StateTask::init(int period) {
    Task::init(period);
    this->red->switchOn();
    this->green->switchOff();
    currState = DISCONNECTED;
}

void StateTask::tick() {
    switch (currState) {
        case DISCONNECTED:
            // if it connects
            if (1) {
                currState = CONNECTED;
                this->red->switchOff();
                this->green->switchOn();
            }
            break;
        case CONNECTED:
            break;
        default:
            break;
    }
}