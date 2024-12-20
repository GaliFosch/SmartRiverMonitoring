#include "SerialComm.h"

bool isInteger(String s) {
  if (s.length() == 0) return false;  // Controlla che la stringa non sia vuota

  // Controlla se è presente un segno negativo iniziale
  int startIndex = 0;
  if (s[0] == '-') {
    if (s.length() == 1) return false;  // Una stringa solo con '-' non è un intero
    startIndex = 1;
  }

  for (unsigned int i = startIndex; i < s.length(); i++) {
    if (!isdigit(s[i])) {
      return false;  // Se un carattere non è una cifra, ritorna false
    }
  }
  return true;
}

SerialComm::SerialComm()
{
    if(!Serial){
        Serial.begin(9600);
        while(!Serial){}
    }
}

void SerialComm::notifyInterrupt(int pin)
{
}

void SerialComm::serialCheck()
{
    int value = readSerial();
    if(value<0 || value>100) return;
    lastValue = value;
    generateEvent(new SerialEvent());
}

int SerialComm::getLastValue()
{
    return this->lastValue;
}

void SerialComm::notifyUpdate(int openingValue)
{
}

int SerialComm::readSerial()
{
    if(!Serial.available()) return -1;
    String line = Serial.readString();
    delay(100);
    if (line.endsWith("\n")) {
        line.remove(line.length() - 1);
    }
    if(isInteger(line)){
        int value = line.toInt();
        return value;
    }
        return -1;
}

