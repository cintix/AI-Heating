#ifndef DETECTION_SENSOR_H
#define DETECTION_SENSOR_H

#include <Arduino.h>

class DetectionSensor {
private:
    int pin;
    int cooldown;
    unsigned long lastActivationTime;
public:
    DetectionSensor(int pin, int cooldown);
    bool activated();
    void setCooldown(int cooldown);
};

#endif
