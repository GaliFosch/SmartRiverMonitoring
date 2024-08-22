#include "ServoMotor.h"

ServoMotor::ServoMotor(int pin) {
    this->pin = pin;
    this->servo.attach(pin);
}

void ServoMotor::changePosition(int angle) {
    this->servo.write(angle);
}

int ServoMotor::getPosition() {
    return this->servo.read();
}