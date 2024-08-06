#ifndef __SERVO_H__
#define __SERVO_H__

#include "Deactivable.h";

class ServoMotor : public Deactivable {
    public:
        void changePosition(int pos);
        int getPosition();
    private:
        int pin;
};

#endif