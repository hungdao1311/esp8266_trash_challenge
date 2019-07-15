//
// Created by Lanh Nguyen on 7/23/17.
//

#ifndef SMARTWATER_DEVICESERVICE_H
#define SMARTWATER_DEVICESERVICE_H
#include <FirebaseArduino.h>
#include "BoardConfiguration.h"
#include <time.h>

#define ROOT_PATH "/boards"
#define DEVICE_PIN_14 14 //D5
#define DEVICE_PIN_12 12 //D6
#define DEVICE_PIN_13 13 //D7
#define MAXIMUM_NUMBER_SETTING 10
class DeviceService {
  public:
      /*
       * setup the initial state of device's PIN
       */
      void setup();
      
      /**
       * set board's state with a setting from FireBase
       */
      void handleObstacle(String macAddressStr);

      String getCurrentTime();
      /**
       * clear all output Pins (4, 12, 13, 14)
       */
       void clearAllOutputPins();
};

extern DeviceService deviceService;


#endif //SMARTWATER_DEVICESERVICE_H
