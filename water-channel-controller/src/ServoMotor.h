#ifndef __SERVO_H__
#define __SERVO_H__

#include <Servo.h>

class ServoMotor {
    public:
        ServoMotor(int pin);
        void changePosition(int angle);
        int getPosition();
    private:
        int pin;
        Servo servo;
};

#endif