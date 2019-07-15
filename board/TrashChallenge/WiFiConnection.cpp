//
// Created by Lanh Nguyen on 7/22/17.
//

#include "WiFiConnection.h"
#include "BoardConfiguration.h"

WiFiManager wifiManager;
void writeToEEROM(int index, bool var);
bool readFromEEROM(int index);

void WiFiConnection::setup() {
    Serial.println("Reading EEROM: ");
    Serial.println(isResetConfig);
    isResetConfig = readFromEEROM(0);
    Serial.println(isResetConfig);
    WiFi.macAddress(macArray);
    macStr = WiFiConnection::byteToHexString(macArray);
    // connect to wifi.
    if(isResetConfig) wifiManager.resetSettings();
    
    wifiManager.autoConnect(WIFI_AP_SSID, WIFI_AP_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(WIFI_STATUS_LED, HIGH);
        Serial.print(".");
        delay(500);
    }
    digitalWrite(WIFI_STATUS_LED, LOW);
    Serial.println();
    Serial.print("connected: ");
    IP = WiFi.localIP().toString();
    Serial.println(IP);
    if (isResetConfig) {
        isResetConfig = false;
        writeToEEROM(0, isResetConfig);
    }
}

bool WiFiConnection::isConnected(){
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("Wifi disconnected...");
        digitalWrite(WIFI_STATUS_LED, HIGH);
        delay(500);
        return false;
    }
    digitalWrite(WIFI_STATUS_LED, LOW);
    return true;
}

bool WiFiConnection::checkResetConfig(int duration, int listenedPIN) {
    if (digitalRead(listenedPIN) == HIGH) {
        Serial.println("Reset pressed.");
        long buttonTimer = millis();
        while (digitalRead(listenedPIN) == HIGH) {
            Serial.print(".");
            if (millis() - buttonTimer > duration) {
                Serial.println("Reset long pressed.");
                isResetConfig = true;
                writeToEEROM(0, isResetConfig);
                return true;
            }
            delay(500);
        }
    }
    Serial.println(isResetConfig);
    return false;
}

void WiFiConnection::resetConfig() {
    ESP.restart();
}

String WiFiConnection::getMacString() {
    return macStr;
}

String WiFiConnection::getCurrentIP() {
    return IP;
}

String WiFiConnection::byteToHexString(byte arr[]) {
    String s;
    for (byte i = 0; i < 6; ++i)
    {
        char buf[3];
        sprintf(buf, "%2X", arr[i]);
        s += buf;
        if (i < 5) s += ':';
    }
    Serial.println("Mac Address: ");
    Serial.println(s);
    return s;
};

void writeToEEROM(int index, bool var){
    Serial.println("WRITE VALUE TO EEROM: ");
    Serial.println(var);
    EEPROM.begin(512);
    EEPROM.put(index, var);
    EEPROM.commit();
    EEPROM.end();
}

bool readFromEEROM(int index){
    bool var = false;
    EEPROM.begin(512);
    EEPROM.get(0, var);
    EEPROM.end();
    Serial.println("VALUE FROM EEROM: ");
    Serial.println(var);
    return var;
}

WiFiConnection wifiConnection;
