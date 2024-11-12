#include "SonarTask.h"
#include "Globals.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

SonarTask::SonarTask(int trigPin, int echoPin) {
    this->sonar = new Sonar(trigPin, echoPin);
}

// TODO: remove
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(String("Message arrived on [") + topic + "] len: " + length );
}

void SonarTask::init(int period) {
    Task::init(period);
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void SonarTask::tick() {
    if (currState == CONNECTED) {
        if (!client.connected()) {
            reconnect();
        } else {
            client.loop();
            sendMessage();
        }
    }
}

void SonarTask::sendMessage() {
    client.publish(topic, "DEBUG: Ciaissimo");
}

void SonarTask::reconnect() {
    Serial.println("DEBUG: attempting to connect");
    String clientId = String("esiot-2122-water-service-")+String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
        Serial.println("DEBUG: mqtt connection started");
        client.subscribe(topic);
    }
}

