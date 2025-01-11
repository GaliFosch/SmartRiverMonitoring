#include "console.h"
#include "Arduino.h"

// GIU: probably should be modified to be an event listener, but wait until server communication works
// GIU: also it should read as well as write on serial, but maybe that can be a private function
// GIU: Or, it could both receive events (comms from dashboard) and dispatch them (state changes)

Console::Console(){
  Serial.begin(9600);
  while (!Serial) {}
}

void Console::log(const char* msg){
  Serial.println(msg);
}

void Console::log(int value){
  Serial.println(value);
}

void Console::log(float value){
  Serial.println(value);
}

void Console::log(const String& msg){
  Serial.println(msg.c_str());
}
