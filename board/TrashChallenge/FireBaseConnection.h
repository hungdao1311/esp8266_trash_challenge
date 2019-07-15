//
// Created by Lanh Nguyen on 7/22/17.
//

#ifndef SMARTWATER_FIREBASE_CONFIGURATION_H
#define SMARTWATER_FIREBASE_CONFIGURATION_H
#include <FirebaseArduino.h>
#include "BoardConfiguration.h"

//Firebase configurations
#define FIREBASE_HOST "esp8266-obstacle.firebaseio.com"
#define FIREBASE_AUTH "eAMfo8AWKYy7XOasUXY67JWzXlqCGAN5JZkiQsBv"

#define FIREBASE_STATUS_LED 2 //D4

class FireBaseConnection {
    public:
        /**
         * Setup led status & init connection to Firebase
         */
        void setup();

        /**
         * check connection to FireBase
         * <li> If connected: FIREBASE_STATUS_LED is HIGH
         * <li> otherwise FIREBASE_STATUS_LED is LOW
         */
        bool isConnected(String lastTimePath, String curTime);

        /**
         * Get config of specific path
         * @param path Full Path from root
         */
        FirebaseObject getDevicesConfig(String path);
        
        /**
         * store reset flag to firebase server
         */
        void storeResetFlag(String path);

         /**
         * clear reset flag to firebase server
         */
        void clearResetFlag(String path);

};
extern FireBaseConnection fireBaseConnection;


#endif //SMARTWATER_FIREBASE_CONFIGURATION_H
