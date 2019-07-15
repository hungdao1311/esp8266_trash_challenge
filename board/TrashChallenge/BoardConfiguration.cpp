//
// Created by Lanh Nguyen on 7/22/17.
//

#include "BoardConfiguration.h"

void setupPIN();
void setupSerial();

void BoardConfiguration::setup(){
    setupPIN();
    setupSerial();
}

bool BoardConfiguration::isResetConfig(){
    if (digitalRead(RESET_CONFIG_PIN) == HIGH) {
      Serial.println("Reset pressed.");
      long buttonTimer = millis();
      while (digitalRead(RESET_CONFIG_PIN) == HIGH){
          if (millis() - buttonTimer > RESET_PRESS_TIME) {
              Serial.println("Reset long pressed.");
              return true;
          }
      }
    }
    return false;
}

void BoardConfiguration::resetConfig(){
    WiFi.disconnect(true);
    ESP.eraseConfig();
    ESP.restart();
}

void setupPIN() {
    pinMode(RESET_CONFIG_PIN, INPUT);
}

void setupSerial() {
    Serial.begin(SERIAL_CLOCK_RATE);
    Serial.setDebugOutput(SERIAL_DEBUG);
}

BoardConfiguration ESP8266Configuration;


