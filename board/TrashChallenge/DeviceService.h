//
// Created by Lanh Nguyen on 7/23/17.
//

#ifndef SMARTWATER_DEVICESERVICE_H
#define SMARTWATER_DEVICESERVICE_H
#include <FirebaseArduino.h>
#include "BoardConfiguration.h"
#include <time.h>

#define ROOT_PATH "/boards"
#define SENSOR_READ_PIN_12 12 //D6
#define SENSOR_WRITE_PIN_13 13 //D7
#define MAXIMUM_NUMBER_SETTING 10
class DeviceService {
  private:
      bool pulseFlag = true;
  public:
      /*
       * setup the initial state of device's PIN
       */
      void setup();
      /**
       * detect obstacle and write data to FireBase
       */
      void handleObstacle(String macAddressStr);
      
      bool isNewObstacle(bool obstacle);
      
      void updateFirebase(String macAddressStr);

      String getCurrentTime();
      /**
       * clear all output Pins (4, 12, 13, 14)
       */
      void clearAllOutputPins();

};

extern DeviceService deviceService;


#endif //SMARTWATER_DEVICESERVICE_H
