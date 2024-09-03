#include "SonarTask.h"
#include "Globals.h";

SonarTask::SonarTask(int trigPin, int echoPin) {
    this->sonar = new Sonar(trigPin, echoPin);
}

void SonarTask::init(int period) {
    Task::init(period);
}

void SonarTask::tick() {
    if (currState == CONNECTED) {
        // ricevi messaggi da server
        // al ricevimento del messaggio, cambia periodo
    }
}

