#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
    this->bindInterrupt(pin);
}

int Potentiometer::readValue() {
    return map(analogRead(this->pin), 0, 1023, 0, 100);
}

void Potentiometer::notifyEvent() {
    #ifdef DEBUG
    Serial.println("DEBUG: Inside Potentiometer::notifyEvent()");
    #endif
    int newValue = this->readValue();
    if (this->lastValue != newValue) {
        #ifdef DEBUG
        Serial.println("DEBUG: Inside if clause in Potentiometer::notifyEvent()");
        #endif
        this->lastValue = newValue;
        #ifdef DEBUG
        Serial.println(this->lastValue);
        #endif
        Event* ev;
        ev = new PotentiometerCheck(this);
        this->generateEvent(ev);
    }
}

int Potentiometer::getValue() {
    return this->lastValue;
}

void Potentiometer::notifyInterrupt(int pin) {
    // the potentiometer is a analog device so it doesn't usually
    // create interrupts
}