#include "SonarTask.h"
#include "Globals.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient client(espClient);

SonarTask::SonarTask(int trigPin, int echoPin) {
    this->sonar = new Sonar(trigPin, echoPin);
}

void callback(char* topic, byte* payload, unsigned int length) {

}

void SonarTask::init(int period) {
    Task::init(period);
    client.setServer(mqtt_server, 1883);
    client.setCallback([this](char* topic, byte* payload, unsigned int length) {
        String payloadStr = "";
        for (unsigned int i = 0; i < length; i++) {
            payloadStr += (char) payload[i];
        }

        //Parse JSON
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payloadStr);
        
        if (error) {
            Serial.print("Failed to parse JSON: ");
            Serial.println(error.f_str());
            return;
        }

        if (doc["type"] == "FREQ") {
            double newFrequency = doc["value"];
            int newPeriod = (int) (1000/newFrequency);
            this->changePeriod(newPeriod);
        }
    });
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
    JsonDocument doc;
    doc["type"] = "VALUE";
    doc["value"] = value;
    String payload; 
    serializeJson(doc, payload);
    #ifdef DEBUG
    Serial.println(payload);
    #endif
    client.publish(sendTopic, payload.c_str());
}

void SonarTask::reconnect() {
    #ifdef DEBUG
    Serial.println("DEBUG: attempting to connect");
    #endif
    String clientId = String("esiot-2122-water-service-")+String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
        #ifdef DEBUG
        Serial.println("DEBUG: mqtt connection started");
        #endif
        client.subscribe(listenTopic);
    }
    #ifdef DEBUG 
    else {
        Serial.print(WiFi.localIP());
        Serial.print("MQTT connection failed, rc=");
        Serial.println(client.state());
    }
    #endif
}

