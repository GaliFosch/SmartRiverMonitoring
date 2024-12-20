#include "Sonar.h"
#include <Arduino.h>

Sonar::Sonar(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float Sonar::readValue() {
    digitalWrite(this->trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(this->trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin,LOW);

    float rawValue = pulseIn(echoPin, HIGH);
    float t = rawValue / 1000.0 / 1000.0 / 2.0;
    float distance = t * vs;
    return distance;
}