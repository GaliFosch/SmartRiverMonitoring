#include "ServoMotor.h"

ServoMotor::ServoMotor(int pin) {
    this->pin = pin;
    this->servo.attach(pin);
    this->isActive = true;
}

void ServoMotor::changePosition(int angle) {
    this->servo.write(angle);
}

int ServoMotor::getPosition() {
    return this->servo.read();
}

void ServoMotor::activate() {
    Deactivable::activate();
    this->servo.attach(this->pin);
}

void ServoMotor::deactivate() {
    Deactivable::deactivate();
    this->servo.detach();
}