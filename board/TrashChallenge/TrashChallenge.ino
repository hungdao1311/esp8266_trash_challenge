#include <FirebaseArduino.h>

#include "BoardConfiguration.h"
#include "WiFiConnection.h"
#include "DeviceService.h"
#include "FireBaseConnection.h"

using namespace ArduinoJson;

void handleDevices(FirebaseObject devices);
void checkResetConfig();
String resetPath;
String connectedTime;

void setup() {
    ESP8266Configuration.setup();
    wifiConnection.setup();
    fireBaseConnection.setup();
    deviceService.setup();
    String macString = wifiConnection.getMacString();
    String devicePath = "/boards/" + macString;
    resetPath = devicePath + "/reset";
    connectedTime = devicePath + "/lastConnectedTime";
}
void loop() {
    if(wifiConnection.checkResetConfig(RESET_PRESS_TIME, RESET_CONFIG_PIN)) {
      fireBaseConnection.storeResetFlag(resetPath);
      wifiConnection.resetConfig();
      ESP.restart();
    }

    if(!wifiConnection.isConnected()) {
      delay(2000);
      deviceService.clearAllOutputPins();
      delay(1000);
      return;
    }
    
    if(!fireBaseConnection.isConnected(connectedTime, deviceService.getCurrentTime())) {
      delay(2000);
      deviceService.clearAllOutputPins();
      delay(1000);
      return;
    }

    fireBaseConnection.clearResetFlag(resetPath);
    deviceService.handleObstacle(wifiConnection.getMacString());
    delay(500);
}



