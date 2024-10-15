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
    attemptConnection();
}

void StateTask::tick() {
    switch (currState) {
        case DISCONNECTED:
            Serial.println("DEBUG State: DISCONNECTED");
            if (WiFi.status() == WL_CONNECTED) {
                currState = CONNECTED;
                this->red->switchOff();
                this->green->switchOn();
            }
            break;
        case CONNECTED:
            Serial.println("DEBUG State: CONNECTED");
            if (WiFi.status() != WL_CONNECTED) {
                currState = DISCONNECTED;
                this->red->switchOn();
                this->green->switchOff();
            }
            break;
        default:
            break;
    }
}

void StateTask::attemptConnection() { 
    Serial.println(String("DEBUG: Connecting to ") + ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
}