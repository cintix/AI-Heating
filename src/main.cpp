#include <Arduino.h>
#include <Network/WebServer.h>
#include <Time/TimeManager.h>
#include <Time/LocalTime.h>
#include <Controllers/LightingController.h>
#include <Controllers/HeatingController.h>
#include <Sensors/DetectionSensor.h>

int lightControllerPin = 15;
int heatingControllerPin = 13;
int detectionSensorPin = 5;
int detectionCoolDownInSeconds = 10;

WebServer webServer;
TimeManager timeManager;
HeatingController heatingController(heatingControllerPin);
LightingController lightController(lightControllerPin);
LocalTime localTime;
DetectionSensor detectionSensor(detectionSensorPin, detectionCoolDownInSeconds);

const char* weekdayNames[] = {
  "Monday",    // 0
  "Tuesday",   // 1
  "Wednesday", // 2
  "Thursday",  // 3
  "Friday",    // 4
  "Saturday",  // 5
  "Sunday"     // 6
};

void setup()
{
  Serial.begin(9600);

  webServer.init();
  timeManager.init(); 

  localTime.setTime(1739370813L);
  
  Serial.print("Today is ");
  Serial.println(weekdayNames[localTime.getDayOfWeek()]);

  Serial.print("Current hour is ");
  Serial.println(localTime.getHour());

}

void loop()
{
  webServer.update();

  if (detectionSensor.activated()) {

    Serial.print("Detection at [");
    Serial.print(localTime.getFormattedTime());
    Serial.println("]");

    if (!lightController.isActive()) lightController.activate();
    if (!heatingController.isActive()) heatingController.activate();

    timeManager.updateSchedule(localTime.getDayOfWeek(), localTime.getHour());
  }


  if (!detectionSensor.isOnCooldown()) {
    if (lightController.isActive()) lightController.deactivate();
    if (heatingController.isActive()) heatingController.deactivate();
  }
  

}
