#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

class TimeManager {
public:
    static void init();
    static void updateSchedule(int day, int hour);
    static float getActivationSchedule(int day, int hour);
    static void saveToFile();
    static void loadFromFile();

private:
    static float schedule[7][24];  // 7 days x 24 hours
    static constexpr float ALPHA = 0.3;
};

#endif
