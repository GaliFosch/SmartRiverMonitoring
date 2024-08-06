#ifndef __CONSOLE__
#define __CONSOLE__

#include "Arduino.h"

// GIU: all these could become private and I could make a new public function called logServoPosition

class Console {
  public:
    Console();
   void log(const char* msg);
   void log(const String& msg);
   void log(int value);
   void log(float value);
};


#endif
