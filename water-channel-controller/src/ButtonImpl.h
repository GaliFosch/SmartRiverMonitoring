 #ifndef __BUTTONIMPL__
#define __BUTTONIMPL__

#include "Button.h"
#include "Deactivable.h"

class ButtonImpl: public Button, public Deactivable {
 
public: 
  ButtonImpl(int pin);
  virtual bool isPressed();
  virtual void notifyInterrupt(int pin);
  void activate() { Deactivable::activate(); };
  void deactivate() { Deactivable::deactivate(); };
  
private:
  int pin;
  bool isInAuto;
  long lastEventTime;
};

#endif
