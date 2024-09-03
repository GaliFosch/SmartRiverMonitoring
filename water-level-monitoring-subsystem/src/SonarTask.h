#ifndef __SONARTASK_H__
#define __SONARTASK_H__

#include "Task.h"
#include "Sonar.h"

#define F1 1000;
#define F2 500;

class SonarTask : public Task {
    public:
        SonarTask(int trigPin, int echoPin);
        void init(int period);
        void tick();
    private:
        Sonar* sonar;
};

#endif