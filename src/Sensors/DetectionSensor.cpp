#include "DetectionSensor.h"
#include <Arduino.h>

DetectionSensor::DetectionSensor(int pin, int cooldown) : pin(pin), cooldown(cooldown), lastActivationTime(0) {
    pinMode(pin, INPUT_PULLUP);
}

bool DetectionSensor::activated() {
    unsigned long currentTime = millis();
    
    if (digitalRead(pin) == LOW && (currentTime - lastActivationTime) >= (cooldown * 1000)) {
        lastActivationTime = currentTime;
        waitingForCoolDown = true;
        return true;
    }
    
    return false;
}

bool DetectionSensor::isOnCooldown() {
    unsigned long currentTime = millis();
    if ((currentTime - lastActivationTime) >= (cooldown * 1000) && waitingForCoolDown) {
        waitingForCoolDown = false;
    }
    return waitingForCoolDown;
}

void DetectionSensor::setCooldown(int cooldown) {
    this->cooldown = cooldown;
}
