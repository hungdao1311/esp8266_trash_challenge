//
// Created by Lanh Nguyen on 7/23/17.
//

#include "DeviceService.h"
#include "FireBaseConnection.h"

void DeviceService::setup() {
  pinMode(SENSOR_READ_PIN_12, INPUT);
  pinMode(SENSOR_WRITE_PIN_13, OUTPUT);

  digitalWrite(SENSOR_WRITE_PIN_13, LOW);
}

void DeviceService::handleObstacle(String macAddressStr) {
  bool obstacle = (digitalRead(SENSOR_READ_PIN_12) == LOW);

  if (isNewObstacle(obstacle)) {
    updateFirebase(macAddressStr);
    delay(10);
  };
}

bool DeviceService::isNewObstacle(bool obstacle) {
  if (!obstacle) {
    digitalWrite(SENSOR_WRITE_PIN_13, LOW);
    if (pulseFlag == false) {
      pulseFlag = true;
    }
    return false;
  } else {
    digitalWrite(SENSOR_WRITE_PIN_13, HIGH);
    if (pulseFlag == true) {
      pulseFlag = false;
      return true;
    }
    return false;
  }
}

void DeviceService::updateFirebase(String macAddressStr) {
  Serial.println("Obstacle Detected");
  String basePath = "/boards/" + macAddressStr;
  int count = Firebase.get(basePath + "/counter").getJsonVariant();
  Firebase.set(basePath + "/counter", count + 1);
  if (Firebase.failed()){
    Serial.print("Cannot connect to Firebase...");
    Serial.println(Firebase.error());
  }
}

String DeviceService::getCurrentTime() {
  time_t now = time(nullptr);
  struct tm *curtime;
  time(&now);
  curtime = localtime(&now);
  return asctime(curtime);
}

void DeviceService::clearAllOutputPins() {
  digitalWrite(SENSOR_WRITE_PIN_13, LOW);
}
DeviceService deviceService;
