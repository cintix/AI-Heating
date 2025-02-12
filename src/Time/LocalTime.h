#ifndef LOCAL_TIME_H
#define LOCAL_TIME_H

#include <Arduino.h>

class LocalTime {
private:
    unsigned long epochTime;  // Stores the last set Unix timestamp
    unsigned long lastMillis; // Stores the millis() value at the time of setting
public:
    LocalTime();
    void setTime(unsigned long unixTimestamp);
    int getHour();
    int getDayOfWeek();
};

#endif