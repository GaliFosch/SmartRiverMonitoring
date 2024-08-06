#ifndef __SERVO_H__
#define __SERVO_H__

#include "Deactivable.h";
#include <Servo.h>;

class ServoMotor : public Deactivable {
    public:
        ServoMotor(int pin);
        void changePosition(int angle);
        int getPosition();
        void activate();
        void deactivate();
    private:
        int pin;
        Servo servo;
};

#endif