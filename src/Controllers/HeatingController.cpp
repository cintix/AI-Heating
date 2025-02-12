#include "HeatingController.h"
#include <Arduino.h>

HeatingController::HeatingController(int pin) : pin(pin) {
    pinMode(pin, OUTPUT);
}

void HeatingController::activate() {
    digitalWrite(pin, HIGH);
    activated = true;
}

void HeatingController::deactivate() {
    digitalWrite(pin, LOW);
    activated = false;
}

bool HeatingController::isActive() {
    return activated;
}