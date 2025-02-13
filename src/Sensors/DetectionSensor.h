#ifndef DETECTION_SENSOR_H
#define DETECTION_SENSOR_H

#include <Arduino.h>

class DetectionSensor {
private:
    int pin;
    int cooldown;
    unsigned long lastActivationTime;
    bool waitingForCoolDown;
public:
    DetectionSensor(int pin, int cooldown);
    bool activated();
    bool isOnCooldown();
    void setCooldown(int cooldown);
};

#endif
