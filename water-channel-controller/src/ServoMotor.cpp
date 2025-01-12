#include "ServoMotor.h"
#include <Arduino.h>

ServoMotor::ServoMotor(int pin) {
    this->pin = pin;
    this->on();
    this->servo.write(90);
    delay(500);
    this->off(); 
    this->position = this->fromAngleToPercent(90);
}

int ServoMotor::fromPercentToAngle(int percent) {
    return map(percent, 0, 100, 0, 180);
}

int ServoMotor::fromAngleToPercent(int angle) {
    return map(angle, 0, 180, 0, 100);
}

void ServoMotor::changePosition(int percent) {
    float angle = this->fromPercentToAngle(percent);
    this->on();
    servo.write(angle);
    delay(500);
    this->off();

    this->position = percent;
}

int ServoMotor::getPosition() {
    return this->position;
}

void ServoMotor::on()
{
  servo.attach(this->pin);
}

void ServoMotor::off()
{
  servo.detach();
}