#include <Arduino.h>
#include <Network/WebServer.h>
#include <Time/TimeManager.h>
#include <Controllers/LightingController.h>
#include <Controllers/HeatingController.h>
#include <Sensors/DetectionSensor.h>

int lightControllerPin = 15;
int heatingControllerPin = 13;
int detectionSensorPin = 16;
int detectionCoolDownInSeconds = 3;

WebServer webServer;
TimeManager timeManager;
HeatingController heatingController(heatingControllerPin);
LightingController lightController(lightControllerPin);
DetectionSensor detectionSensor(detectionSensorPin, detectionCoolDownInSeconds);

void setup()
{
  Serial.begin(9600);

  webServer.init();
  timeManager.init(); 

}

void loop()
{
  webServer.update();
}
