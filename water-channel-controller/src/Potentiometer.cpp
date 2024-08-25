#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
}

int Potentiometer::readValue() {
    return map(analogRead(this->pin), 0, 1023, 0, 100);
}