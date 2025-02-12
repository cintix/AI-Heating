#include "LocalTime.h"

unsigned long LocalTime::epochTime = 0; // Initialize static variable

LocalTime::LocalTime() : lastMillis(0) {}

void LocalTime::setTime(unsigned long unixTimestamp)
{
    // CET is UTC+1, so add 1 hour (3600 seconds)
    epochTime = unixTimestamp + 3600; // Add 1 hour for CET
    lastMillis = millis();
}

int LocalTime::getHour()
{
    unsigned long elapsedSeconds = (millis() - lastMillis) / 1000;
    unsigned long currentTime = epochTime + elapsedSeconds;
    return (currentTime % 86400L) / 3600; // Extract hour (0-23) from Unix timestamp
}

int LocalTime::getDayOfWeek()
{
    unsigned long elapsedSeconds = (millis() - lastMillis) / 1000;
    unsigned long currentTime = epochTime + elapsedSeconds;
    return ((currentTime / 86400L) + 3) % 7; // Adjust to make Monday = 0, Sunday = 6
}

String LocalTime::getFormattedTime()
{
    unsigned long elapsedSeconds = (millis() - lastMillis) / 1000;
    unsigned long currentTime = epochTime + elapsedSeconds;

    int hours = (currentTime % 86400L) / 3600;
    int minutes = (currentTime % 3600) / 60;
    int seconds = currentTime % 60;

    char buffer[9]; // "hh:mm:ss" + null terminator
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, seconds);

    return String(buffer);
}