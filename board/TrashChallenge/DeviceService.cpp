//
// Created by Lanh Nguyen on 7/23/17.
//

#include "DeviceService.h"
#include "FireBaseConnection.h"

void DeviceService::setup() {
  pinMode(DEVICE_PIN_12, INPUT);
  pinMode(DEVICE_PIN_13, OUTPUT);
  
  digitalWrite(DEVICE_PIN_13, LOW);
  
}

int isObstacle = HIGH;

void DeviceService::handleObstacle(String macAddressStr) {
  isObstacle = digitalRead(DEVICE_PIN_12);
  if (isObstacle == LOW){ 
  
    Serial.println("Detecting Obstacle");
    String basePath = "/boards/" + macAddressStr;
    int count = Firebase.get(basePath + "/counter").getJsonVariant();
    Firebase.set(basePath + "/counter", count+1);
    digitalWrite(DEVICE_PIN_13, HIGH);
    delay(1000);
  };
  digitalWrite(DEVICE_PIN_13, LOW);
}

String DeviceService::getCurrentTime(){
    time_t now = time(nullptr);
    struct tm * curtime;
    time(&now);
    curtime = localtime (&now);
    return asctime(curtime);
}

void DeviceService::clearAllOutputPins() {
  digitalWrite(DEVICE_PIN_13, LOW);
}
DeviceService deviceService;
