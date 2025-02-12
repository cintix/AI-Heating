#include "LightingController.h"
#include <Arduino.h>

LightingController::LightingController(int pin) : pin(pin) {
    pinMode(pin, OUTPUT);
}

void LightingController::activate() {
    digitalWrite(pin, HIGH);
    activated = true;
}

void LightingController::deactivate() {
    digitalWrite(pin, LOW);
    activated = false;
}

bool LightingController::isActive() {
    return activated;
}