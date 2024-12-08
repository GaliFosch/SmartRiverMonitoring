#ifndef __SERVO_H__
#define __SERVO_H__

#include <Servo.h>

class ServoMotor {
    public:
        ServoMotor(int pin);
        void changePosition(int percent);
        int getPosition();
    private:
        int fromPercentToAngle(int percent);
        void on();
        void off();
        int pin;
        int position;
        Servo servo;
};

#endif