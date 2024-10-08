#include "Scheduler.h"
#include <Ticker.h>

volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timerFlag = false;
  long period = 1000l*basePeriod;
  ticker.attach(period, timerHandler);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}
  
void Scheduler::schedule(){   
  while (!timerFlag){
    Serial.println("ue");
  }
  timerFlag = false;

  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->updateAndCheckTime(basePeriod)){
      taskList[i]->tick();
    }
  }
}
