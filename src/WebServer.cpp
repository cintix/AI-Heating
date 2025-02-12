#include "WebServer.h"
#include <LittleFS.h>

WebServer::WebServer() : server(80) {}

void WebServer::init()
{

    if (!LittleFS.begin())
    {
        Serial.println("LittleFS Mount Failed");
        return;
    }
    delay(1000);  // Allow filesystem to settle
    // Debug: List all files in LittleFS
    Serial.println("Listing files in LittleFS:");
    Dir dir = LittleFS.openDir("/");
    while (dir.next())
    {
        Serial.print("File: ");
        Serial.println(dir.fileName());
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

    server.on("/", HTTP_GET, [this]()
              { serveFile("/index.html"); });
    server.on("/style.css", HTTP_GET, [this]()
              { serveFile("/style.css"); });
    server.on("/script.js", HTTP_GET, [this]()
              { serveFile("/script.js"); });
    server.on("/api/schedule", HTTP_GET, [this]()
              { handleAPI(); });
    server.begin();
}

void WebServer::handleClient()
{
    server.handleClient();
}

void WebServer::update()
{
    dnsServer.processNextRequest();
    server.handleClient();
}

void WebServer::serveFile(const String &path)
{
    Serial.print("Serving file: ");
    Serial.println(path);

    File file = LittleFS.open(path, "r");
    if (!file)
    {
        server.send(404, "text/plain", "File not found");
        return;
    }
    String mimeType = "text/plain"; // Default MIME type

    if (path.endsWith(".html"))
    {
        mimeType = "text/html";
    }
    else if (path.endsWith(".css"))
    {
        mimeType = "text/css";
    }
    else if (path.endsWith(".js"))
    {
        mimeType = "application/javascript";
    }

    server.streamFile(file, mimeType);
    file.close();
}

void WebServer::handleAPI()
{
    String json = "{\"schedule\": {\"day\": 1, \"hour\": 12, \"value\": 0.5}}";
    server.send(200, "application/json", json);
}

void WebServer::handleSetTime()
{
    if (server.hasArg("timestamp"))
    {
        unsigned long timestamp = server.arg("timestamp").toInt(); // Get the Unix timestamp

        // Calculate the number of milliseconds from the timestamp
        unsigned long currentMillis = millis();

        // Set the system time offset based on the Unix timestamp and current millis
        //  systemTimeOffset = currentMillis - timestamp;

        // Optionally save the timestamp to LittleFS for future reference
        // saveToFile();

        Serial.println("Time set to Unix timestamp: " + String(timestamp));

        server.send(200, "application/json", "{\"status\":\"success\"}");
    }
    else
    {
        server.send(400, "application/json", "{\"status\":\"error\", \"message\":\"Missing timestamp parameter\"}");
    }
}
