#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>
#include <FS.h>
#include "WebServer.h"
#include <Time/LocalTime.h>
#include <Time/TimeManager.h>

WebServer::WebServer() : server(80) {}

void WebServer::init()
{

    if (!LittleFS.begin())
    {
        Serial.println("LittleFS Mount Failed");
        return;
    }

    localIP = IPAddress(192, 168, 4, 1);  // Local IP for the AP
    gateway = IPAddress(192, 168, 4, 1);  // Gateway is the same as local IP
    subnet = IPAddress(255, 255, 255, 0); // Subnet mask

    // Start the Access Point
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(localIP, gateway, subnet);

    Serial.println("Access Point started!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    // Start DNS server for captive portal
    dnsServer.start(DNS_PORT, "*", localIP);

    // Register routes
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", "text/html"); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/style.css", "text/css"); });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/script.js", "application/javascript"); });

    server.on("/api/schedule", HTTP_GET, [this](AsyncWebServerRequest *request)
              { handleAPI(request); });

    // Add endpoint for setting time
    server.on("/api/settime", HTTP_GET, [this](AsyncWebServerRequest *request)
              { handleSetTime(request); });

    server.begin();
}

void WebServer::update()
{
    dnsServer.processNextRequest();
}

void WebServer::handleAPI(AsyncWebServerRequest *request)
{
    TimeManager timeManager;
    JsonDocument doc; // Adjust size as needed
    JsonObject scheduleObj = doc["schedule"].to<JsonObject>();

    for (int day = 0; day < 7; day++)
    {
        JsonObject dayObj = scheduleObj[String(day)].to<JsonObject>();
        for (int hour = 0; hour < 24; hour++)
        {
            dayObj[String(hour)] = timeManager.getActivationSchedule(day, hour);
        }
    }

    String json;
    serializeJson(doc, json);
    request->send(200, "application/json", json);
}

void WebServer::handleSetTime(AsyncWebServerRequest *request)
{
    if (request->hasArg("timestamp"))
    {
        LocalTime localTime;
        const char *weekdayNames[] = {
            "Monday",    // 0
            "Tuesday",   // 1
            "Wednesday", // 2
            "Thursday",  // 3
            "Friday",    // 4
            "Saturday",  // 5
            "Sunday"     // 6
        };

        unsigned long timestamp = request->arg("timestamp").toInt(); // Get the Unix timestamp
        localTime.setTime(timestamp);

        Serial.print("Today is ");
        Serial.println(weekdayNames[localTime.getDayOfWeek()]);

        Serial.print("Current hour is ");
        Serial.println(localTime.getHour());

        request->send(200, "application/json", "{\"status\":\"success\"}");
    }
    else
    {
        request->send(400, "application/json", "{\"status\":\"error\", \"message\":\"Missing timestamp parameter\"}");
    }
}
