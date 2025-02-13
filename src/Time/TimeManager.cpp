#include "TimeManager.h"
#include <ArduinoJson.h>
#include <LittleFS.h>

#define FILE_PATH "/time.json"
#define MAX_VALUE 10.0f
#define DECAY_FACTOR 0.98f

// Static variable definition
float TimeManager::schedule[7][24];

void TimeManager::init() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            schedule[i][j] = 0.0f;
        }
    }
    
    loadFromFile();
}

void TimeManager::updateSchedule(int day, int hour) {
    schedule[day][hour] += ALPHA;

    if (schedule[day][hour] > MAX_VALUE) {
        schedule[day][hour] = MAX_VALUE;
        
        for (int j = 0; j < 24; j++) {
            if (j != hour) {
                schedule[day][j] *= DECAY_FACTOR;
            }
        }
    }

    saveToFile();
}

float TimeManager::getActivationSchedule(int day, int hour) {
    return schedule[day][hour];
}

void TimeManager::saveToFile() {
    File file = LittleFS.open(FILE_PATH, "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    JsonDocument doc;
    
    for (int i = 0; i < 7; i++) {
        JsonArray dayArray = doc.createNestedArray(String(i));
        for (int j = 0; j < 24; j++) {
            dayArray.add(schedule[i][j]);
        }
    }

    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write to file");
    }
    
    file.close();
}

void TimeManager::loadFromFile() {
    File file = LittleFS.open(FILE_PATH, "r");
    if (!file) {
        Serial.println("No existing schedule file found.");
        return;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.println("Failed to read JSON from file");
        return;
    }

    for (int i = 0; i < 7; i++) {
        JsonArray dayArray = doc[String(i)];
        if (!dayArray.isNull()) {
            for (int j = 0; j < 24; j++) {
                schedule[i][j] = dayArray[j].as<float>();
            }
        }
    }

    file.close();
}
