#include "ServoMotor.h"
#include <Arduino.h>

ServoMotor::ServoMotor(int pin) {
    this->pin = pin;
}

int ServoMotor::fromPercentToAngle(int percent) {
    return map(percent, 0, 100, 0, 180);
}

void ServoMotor::changePosition(int percent) {
    //float coeff = (2250.0 - 750.0) / 180;
    float angle = this->fromPercentToAngle(percent);
    float curr = this->getPosition();
    Serial.print("Angle:");
    Serial.println(angle);
    Serial.print("Curr:");
    Serial.println(curr);
    //servo.write(750 + angle * coeff);
    //this->servo.write(this->fromPercentToAngle(percent));
    this->on();
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
}

int ServoMotor::getPosition() {
    return this->servo.read();
}

void ServoMotor::on()
{
  servo.attach(this->pin);
}

void ServoMotor::off()
{
  servo.detach();
}