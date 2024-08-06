#ifndef __BUTTON__
#define __BUTTON__

#include "async_fsm.h"

#define MANUAL_MODE_EVENT 1
#define AUTO_MODE_EVENT 2

class Button : public EventSource {
public: 
  virtual bool isPressed() = 0;
};

class ManualMode: public Event {
public:
  ManualMode(Button* source) : Event(MANUAL_MODE_EVENT){
    this->source = source;  
  } 
 
  Button* getSource(){
    return source;
  } 
private:
  Button* source;  
};

class AutoMode: public Event {
public:
  AutoMode(Button* source) : Event(AUTO_MODE_EVENT){
    this->source = source;  
  } 
 
  Button* getSource(){
    return source;
  } 
private:
  Button* source;  
};

#endif
