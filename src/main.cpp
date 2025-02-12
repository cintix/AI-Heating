#include <Arduino.h>
#include <WebServer.h>
#include <TimeManager.h>
#include <LightingController.h>
#include <HeatingController.h>

int lightControllerPin = 15;
int heatingControllerPin = 13;
int detectionSensorPin = 16;

WebServer webServer;
TimeManager timeManager;
HeatingController heatingController(heatingControllerPin);
LightingController lightController(lightControllerPin);


void setup()
{
  Serial.begin(9600);

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
