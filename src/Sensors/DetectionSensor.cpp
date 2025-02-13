#include "DetectionSensor.h"  // Include the header for the DetectionSensor class
#include <Arduino.h>          // Include the Arduino library for basic functionality

// Constructor to initialize the sensor with pin and cooldown time
DetectionSensor::DetectionSensor(int pin, int cooldown) : pin(pin), cooldown(cooldown), lastActivationTime(0) {
    pinMode(pin, INPUT_PULLUP);  // Set the pin mode to input with an internal pull-up resistor
}

// Method to check if the sensor has been activated
bool DetectionSensor::activated() {
    unsigned long currentTime = millis();  // Get the current time in milliseconds
    
    // Check if the sensor is triggered (LOW) and if the cooldown period has passed
    if (digitalRead(pin) == LOW && (currentTime - lastActivationTime) >= (cooldown * 1000)) {
        lastActivationTime = currentTime;  // Update the last activation time
        waitingForCoolDown = true;         // Set the sensor to cooldown state
        return true;                       // Return true, indicating the sensor has been activated
    }
    
    return false;  // Return false if the sensor has not been activated
}

// Method to check if the sensor is still on cooldown
bool DetectionSensor::isOnCooldown() {
    unsigned long currentTime = millis();  // Get the current time in milliseconds
    
    // If the cooldown period has passed and we were previously waiting for cooldown, reset the flag
    if ((currentTime - lastActivationTime) >= (cooldown * 1000) && waitingForCoolDown) {
        waitingForCoolDown = false;  // No longer on cooldown
    }
    
    return waitingForCoolDown;  // Return whether the sensor is still in cooldown
}

// Method to set a new cooldown time (in seconds)
void DetectionSensor::setCooldown(int cooldown) {
    this->cooldown = cooldown;  // Set the cooldown time
}
