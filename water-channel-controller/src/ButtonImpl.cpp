#include "ButtonImpl.h"
#include "Arduino.h"

#define DEBOUNCING_TIME 20

ButtonImpl::ButtonImpl(int pin){
  this->pin = pin;
  this->isInAuto = true;
  pinMode(pin, INPUT);  
  bindInterrupt(pin);
  lastEventTime = millis();
} 
  
bool ButtonImpl::isPressed(){
  return digitalRead(pin) == HIGH;
}

void ButtonImpl::notifyInterrupt(int pin){
  if(this->isActive) {
    long curr = millis();
    if (curr - lastEventTime > DEBOUNCING_TIME){
          lastEventTime = curr;
          Event* ev;
          if (isInAuto){
            ev = new ManualMode(this);
          } else {
            ev = new AutoMode(this);
          }
          isInAuto = !isInAuto;
          this->generateEvent(ev);
    }
  }
}
