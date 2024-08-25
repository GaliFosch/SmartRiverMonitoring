#include "ServoMotor.h"
#include <Arduino.h>

ServoMotor::ServoMotor(int pin) {
    this->pin = pin;
    this->servo.attach(pin);
}

int ServoMotor::fromPercentToAngle(int percent) {
    return map(percent, 0, 100, 0, 180);
}

void ServoMotor::changePosition(int percent) {
    this->servo.write(this->fromPercentToAngle(percent));
}

int ServoMotor::getPosition() {
    return this->servo.read();
}