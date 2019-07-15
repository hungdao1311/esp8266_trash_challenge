//
// Created by Lanh Nguyen on 7/22/17.
//

#ifndef BOARD_CONFIGURATION_H
#define BOARD_CONFIGURATION_H

#include <ESP8266WiFi.h>

#define RESET_CONFIG_PIN 15 //D8
#define SERIAL_CLOCK_RATE 9600
#define SERIAL_DEBUG true
#define RESET_PRESS_TIME 5000

class BoardConfiguration {
    public:
        /**
         * setup All configuration for ESP8266 board
         */
        void setup();
 
        /**
         * check if reset ping (defined as RESET_CONFIG_PIN) is pressed for a long time
         */
        bool isResetConfig();

        /**
         * erase all config and restart ESP8266 board
         */
        void resetConfig();

};
extern BoardConfiguration ESP8266Configuration;

#endif //BOARD_CONFIGURATION_H
