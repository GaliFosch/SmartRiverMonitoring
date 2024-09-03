#include "Sonar.h"
#include <Arduino.h>

Sonar::Sonar(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float Sonar::readValue() {
    float rawValue = pulseIn(echoPin, HIGH);
    float t = rawValue / 1000.0 / 1000.0 / 2;
    float distance = t * vs;
    return distance;
}