#include "LightingController.h"
#include <Arduino.h>

LightingController::LightingController(int pin) : pin(pin) {
    pinMode(pin, OUTPUT);
}

void LightingController::activate() {
    digitalWrite(pin, HIGH);
}

void LightingController::deactivate() {
    digitalWrite(pin, LOW);
}