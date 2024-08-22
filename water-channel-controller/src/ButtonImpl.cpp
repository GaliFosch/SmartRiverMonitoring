#include "ButtonImpl.h"
#include "Arduino.h"

#define DEBOUNCING_TIME 1000

ButtonImpl::ButtonImpl(int pin){
  this->pin = pin;
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
          ev = new ButtonPress(this);
          this->generateEvent(ev);
    }
  }
}
