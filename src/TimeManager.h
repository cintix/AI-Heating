#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

class TimeManager {
public:
    void init();
    void updatePattern(int day, int hour);
    float getActivationPattern(int day, int hour);
    void setTime(int year, int month, int day, int hour, int minute);
    String getTimeAsString();
    void saveToFile();
    void loadFromFile();

private:
    float schedule[7][24];  // 7 days x 24 hours
    const float ALPHA = 0.1;
    int currentYear, currentMonth, currentDay, currentHour, currentMinute;
};

#endif
