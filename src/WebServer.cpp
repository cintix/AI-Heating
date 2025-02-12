#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>
#include <FS.h>
#include "WebServer.h"

WebServer::WebServer() : server(80) {}

void WebServer::init() {
    if (!LittleFS.begin()) {
        Serial.println("LittleFS Mount Failed");
        return;
    }
    delay(1000);  // Allow filesystem to settle
    // Debug: List all files in LittleFS
    Serial.println("Listing files in LittleFS:");
    Dir dir = LittleFS.openDir("/");
    while (dir.next()) {
        Serial.print("File: ");
        Serial.println(dir.fileName());
    }

    localIP = IPAddress(192, 168, 4, 1);   // Local IP for the AP
    gateway = IPAddress(192, 168, 4, 1);   // Gateway is the same as local IP
    subnet = IPAddress(255, 255, 255, 0);  // Subnet mask

    // Start the Access Point
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(localIP, gateway, subnet);

    Serial.println("Access Point started!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    // Start DNS server for captive portal
    dnsServer.start(DNS_PORT, "*", localIP);

    // Register routes
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { 
        request->send(LittleFS, "/index.html", "text/html"); 
    });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) { 
        request->send(LittleFS, "/style.css", "text/css"); 
    });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) { 
        request->send(LittleFS, "/script.js", "application/javascript"); 
    });

    server.on("/api/schedule", HTTP_GET, [this](AsyncWebServerRequest *request) { 
        handleAPI(request); 
    });

    // Add endpoint for setting time
    server.on("/api/settime", HTTP_GET, [this](AsyncWebServerRequest *request) { 
        handleSetTime(request); 
    });

    server.begin();
}

void WebServer::update() { 
    dnsServer.processNextRequest(); 
}

void WebServer::handleAPI(AsyncWebServerRequest *request) {
    String json = "{\"schedule\": {\"day\": 1, \"hour\": 12, \"value\": 0.5}}";
    request->send(200, "application/json", json);
}

void WebServer::handleSetTime(AsyncWebServerRequest *request) {
    if (request->hasArg("timestamp")) {
        unsigned long timestamp = request->arg("timestamp").toInt();  // Get the Unix timestamp
        Serial.println("Time set to Unix timestamp: " + String(timestamp));
        request->send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        request->send(400, "application/json", "{\"status\":\"error\", \"message\":\"Missing timestamp parameter\"}");
    }
}
