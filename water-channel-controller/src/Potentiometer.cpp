#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
}

int Potentiometer::readValue() {
    return map(analogRead(this->pin), 0, 1023, 0, 100);
}

void Potentiometer::notifyEvent() {
    Serial.println("DEBUG: Inside Potentiometer::notifyEvent()");
    int newValue = this->readValue();
    if (this->lastValue != newValue) {
        Serial.println("DEBUG: Inside if clause in Potentiometer::notifyEvent()");
        this->lastValue = newValue;
        Event* ev;
        ev = new PotentiometerCheck(this);
        this->generateEvent(ev);
    }
}

int Potentiometer::getValue() {
    return this->lastValue;
}

void Potentiometer::notifyInterrupt(int pin) {
    // DEBUG: this stays empty until I can figure out how it works
    int p = 0;
    p + 1;
}