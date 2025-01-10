#ifndef __TASK__
#define __TASK__

#include <Arduino.h>

class Task {
  int myPeriod;
  int timeElapsed;
  
protected:
  void changePeriod(int period) {
    this->myPeriod = period;
  }

public:
  unsigned int totalTimeElapsed;

  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }
  
};

#endif