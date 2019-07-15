//
// Created by Lanh Nguyen on 7/22/17.
//

#ifndef WIFI_CONFIGURATION_H
#define WIFI_CONFIGURATION_H

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#include <EEPROM.h>

#define WIFI_MODE WIFI_AP_STA
#define WIFI_STATUS_LED 0
#define WIFI_AP_SSID "ESP_SmartWater"
#define WIFI_AP_PASSWORD "87654321"

class WiFiConnection {
    byte macArray[6];
    String macStr;
    String IP;
    bool isResetConfig = false;
    public:
        /**
         * setup all configuration for wifi on esp8266
         */
        void setup();

        /**
         * check Connection
         */
        bool isConnected();

        /**
         * detect a long press action in a specific PIN for a time.
         * @param time configurable time for a long press action
         * @param listenedPIN PIN to listen reset config action
         */
        bool checkResetConfig(int time, int listenedPIN);

        /**
         * reset WiFi to default
         */
        void resetConfig();

        /**
         * get Mac Address of ESP8266
         */
        String getMacString();

        /**
         * get current Local IP Address
         */
        String getCurrentIP();

        /**
         * convert an byte array to String
         */
        String byteToHexString(byte arr[]);
};

extern WiFiConnection wifiConnection;

#endif //WIFI_CONFIGURATION_H
