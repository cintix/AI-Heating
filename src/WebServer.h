#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

class WebServer
{
public:
    WebServer();  // Constructor
    void init();
    void update();
    void handleClient();

private:
    const char *ssid = "AI Heating";      // Access Point SSID
    const char *password = "ec2remember"; // Access Point Password
    const byte DNS_PORT = 53;             // DNS port for captive portal

    // Web server and DNS server
    ESP8266WebServer server;   // Web server on port 80
    DNSServer dnsServer;       // DNS server for captive portal

    IPAddress localIP;          // Local IP of the AP
    IPAddress gateway;          // Gateway IP (typically the same as localIP)
    IPAddress subnet;           // Subnet mask

    void serveFile(const String &path);
    void handleAPI();
    void handleSetTime();
};

#endif