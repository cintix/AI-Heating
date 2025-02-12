#include "TimeManager.h"

void TimeManager::init() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            schedule[i][j] = 0;
        }
    }
    
    loadFromFile(); // Load time and patterns from LittleFS if available
}

void TimeManager::updatePattern(int day, int hour) {
    schedule[day][hour] = (ALPHA * 1) + ((1 - ALPHA) * schedule[day][hour]);
}

float TimeManager::getActivationPattern(int day, int hour) {
    return schedule[day][hour];
}

void TimeManager::setTime(int year, int month, int day, int hour, int minute) {
    currentYear = year;
    currentMonth = month;
    currentDay = day;
    currentHour = hour;
    currentMinute = minute;
    saveToFile();  // Save the new time to LittleFS
}

String TimeManager::getTimeAsString() {
    String timeString = String(currentYear) + "-" + String(currentMonth) + "-" + String(currentDay) + " " +
                        String(currentHour) + ":" + String(currentMinute);
    return timeString;
}

void TimeManager::saveToFile() {
    File file = LittleFS.open("/time.json", "w");
    if (file) {
        file.print("{\"year\":");
        file.print(currentYear);
        file.print(", \"month\":");
        file.print(currentMonth);
        file.print(", \"day\":");
        file.print(currentDay);
        file.print(", \"hour\":");
        file.print(currentHour);
        file.print(", \"minute\":");
        file.print(currentMinute);
        file.print("}");
        file.close();
    }
}

void TimeManager::loadFromFile() {
    File file = LittleFS.open("/time.json", "r");
    if (file) {
        String content = file.readString();
        JsonDocument doc;
        deserializeJson(doc, content);
        
        currentYear = doc["year"];
        currentMonth = doc["month"];
        currentDay = doc["day"];
        currentHour = doc["hour"];
        currentMinute = doc["minute"];
        
        file.close();
    }
}
