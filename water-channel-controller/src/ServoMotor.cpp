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
    //float coeff = (2250.0 - 750.0) / 180;
    float angle = this->fromPercentToAngle(percent);
    //servo.write(750 + angle * coeff);
    //this->servo.write(this->fromPercentToAngle(percent));
    this->on();

    // TODO: decidere cosa fare... Così funziona meglio
    servo.write(angle);
    delay(500);
    // if(angle > curr){
    //     for(int i = curr; i<=angle; i++){
    //         //servo.write(750 + i * coeff);
    //         servo.write(i);
    //         delay(10);
    //     }
    // }else if(angle < curr){
    //     Serial.println("angle< curr");
    //     for(int i = angle; i <= curr; i++){
    //         //servo.write(750 + i * coeff);
    //         servo.write(i);
    //         delay(10);
    //     }
    // }
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