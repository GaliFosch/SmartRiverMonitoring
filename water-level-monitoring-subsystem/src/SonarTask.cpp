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
    // Serial.println(String("Message arrived on [") + topic + "]" +  );
    String payloadStr = "";
    for (unsigned int i = 0; i < length; i++) {
        payloadStr += (char) payload[i];
    }
    Serial.println(payloadStr);
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
    float value = this->sonar->readValue();
    String payload = "[ \"VALUE\", {\"value\": " + String(value, 2) + "}]";
    client.publish(topic, payload.c_str());
}

void SonarTask::reconnect() {
    Serial.println("DEBUG: attempting to connect");
    String clientId = String("esiot-2122-water-service-")+String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
        Serial.println("DEBUG: mqtt connection started");
        client.subscribe(topic);
    } else {
        Serial.print("MQTT connection failed, rc=");
        Serial.println(client.state());
}
}

