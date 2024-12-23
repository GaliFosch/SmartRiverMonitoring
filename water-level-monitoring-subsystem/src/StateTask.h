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
        // Vodafone-A38371406
        // LaSaphiGamer
        const char* ssid = "Galileo.Cell";
        // G: WIFI1331
        // V: e97CtHJpPXgF4C4P
        // L: scva1852
        const char* password = "WIFI1331";
        Led* red;
        Led* green;
        void attemptConnection();
};

#endif