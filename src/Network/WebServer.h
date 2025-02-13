#ifndef HTTP_ANY
#define HTTP_ANY 0
#endif

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>
#include <FS.h>
#include <ArduinoJson.h>


class WebServer
{
public:
    WebServer();  // Constructor
    void init();
    void update();
private:
    const char *ssid = "AI Heating";      // Access Point SSID
    const char *password = "ec2remember"; // Access Point Password
    const byte DNS_PORT = 53;             // DNS port for captive portal

    // Web server and DNS server
    AsyncWebServer server;     // Web server on port 80
    DNSServer dnsServer;       // DNS server for captive portal

    IPAddress localIP;          // Local IP of the AP
    IPAddress gateway;          // Gateway IP (typically the same as localIP)
    IPAddress subnet;           // Subnet mask

    void handleAPI(AsyncWebServerRequest *request);
    void handleSetTime(AsyncWebServerRequest *request);
};

#endif