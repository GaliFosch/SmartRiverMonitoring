#ifndef __STATETASK_H__
#define __STATETASK_H__

#include "Task.h"
#include "Led.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class StateTask : public Task {
    public:
        StateTask(int redPin, int greenPin);
        void init(int period);
        void tick();
    private:
        // Galileo.Cell
        const char* ssid = "Galileo.Cell";
        // WIFI1331
        //const char* password = "scva1852";
        const char* password = "WIFI1331";
        Led* red;
        Led* green;
        void attemptConnection();
};

#endif