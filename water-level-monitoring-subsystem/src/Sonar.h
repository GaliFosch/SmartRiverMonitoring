#ifndef __SONAR_H__
#define __SONAR_H__

class Sonar {
    public:
        Sonar(int trigPin, int echoPin);
        float readValue();
    private:
        const float temperature = 20;
        const float vs = 331.45 + 0.62 * temperature;
        int trigPin;
        int echoPin;
};

#endif