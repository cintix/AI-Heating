#include <Arduino.h>
#include <WebServer.h>
#include <TimeManager.h>

int lightControllerPin = 15;
int heatingControllerPin = 13;
int detectionSensorPin = 16;

WebServer webServer;
TimeManager timeManager;

void setup()
{
  Serial.begin(115200);

  webServer.init();
  timeManager.init(); 

  pinMode(lightControllerPin, OUTPUT);
  pinMode(heatingControllerPin, OUTPUT);
  pinMode(detectionSensorPin, INPUT_PULLDOWN_16);
}

void loop()
{
  webServer.update();

  

}
