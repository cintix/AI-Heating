#include "DetectionSensor.h"
#include <Arduino.h>

DetectionSensor::DetectionSensor(int pin, int cooldown) : pin(pin), cooldown(cooldown), lastActivationTime(0) {
    pinMode(pin, INPUT_PULLUP);
}

bool DetectionSensor::activated() {
    unsigned long currentTime = millis();
    
    if (digitalRead(pin) == LOW && (currentTime - lastActivationTime) >= (cooldown * 1000)) {
        lastActivationTime = currentTime;
        return true;
    }
    
    return false;
}

void DetectionSensor::setCooldown(int cooldown) {
    this->cooldown = cooldown;
}
