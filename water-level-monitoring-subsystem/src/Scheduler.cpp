#include "Scheduler.h"
#include <Ticker.h>


void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  this->lastScheduled = millis();
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
  if (millis() - lastScheduled < basePeriod){
    return;
  }
  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->updateAndCheckTime(basePeriod)){
      taskList[i]->tick();
    }
  }
}
