#ifndef __STATETASK_H__
#define __STATETASK_H__

#include "Task.h"
#include "Led.h"

class StateTask : public Task {
    public:
        StateTask(int redPin, int greenPin);
        void init(int period);
        void tick();
    private:
        Led* red;
        Led* green;
};

#endif