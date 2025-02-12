#include "LocalTime.h"

LocalTime::LocalTime() : epochTime(0), lastMillis(0) {}

void LocalTime::setTime(unsigned long unixTimestamp) {
    epochTime = unixTimestamp;
    lastMillis = millis();
}

int LocalTime::getHour() {
    unsigned long elapsedSeconds = (millis() - lastMillis) / 1000;
    unsigned long currentTime = epochTime + elapsedSeconds;
    return (currentTime % 86400L) / 3600; // Extract hour (0-23) from Unix timestamp
}

int LocalTime::getDayOfWeek() {
    unsigned long elapsedSeconds = (millis() - lastMillis) / 1000;
    unsigned long currentTime = epochTime + elapsedSeconds;
    return ((currentTime / 86400L) + 4) % 7; // Adjust to make Monday = 0, Sunday = 6
}
