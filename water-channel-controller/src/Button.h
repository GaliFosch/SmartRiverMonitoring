#ifndef __BUTTON__
#define __BUTTON__

#include "async_fsm.h"
#include "Events.h"

class Button : public EventSource {
public: 
  virtual bool isPressed() = 0;
};

class ButtonPress: public Event {
public:
  ButtonPress(Button* source) : Event(BUTTON_PRESSED_EVENT){
    this->source = source;  
  } 
 
  Button* getSource(){
    return source;
  } 
private:
  Button* source;  
};

#endif
