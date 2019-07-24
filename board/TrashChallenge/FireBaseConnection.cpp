//
// Created by Lanh Nguyen on 7/22/17.
//

#include "FireBaseConnection.h"

void FireBaseConnection::setup() {
    pinMode(FIREBASE_STATUS_LED, OUTPUT);
    digitalWrite(FIREBASE_STATUS_LED , LOW);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

bool FireBaseConnection::isConnected(String lastTimePath, String curTime) {
    Serial.println("Checking Connection to Firebase..");
    Firebase.setString(lastTimePath, curTime);
    Serial.println("Save Connection Time to Firebase..");
    if (Firebase.failed()) { // Check for errors
        Serial.print("Cannot connect to Firebase...");
        digitalWrite(FIREBASE_STATUS_LED, LOW);
        Serial.println(Firebase.error());
        delay(1000);
        return false;
    }

    digitalWrite(FIREBASE_STATUS_LED, HIGH);
    delay(100);
    Serial.println("Firebase Connected.");
    return true;
}

void FireBaseConnection::storeResetFlag(String path){
  Firebase.setBool(path, true);
}

void FireBaseConnection::clearResetFlag(String path){
  Firebase.setBool(path, false);
}

FireBaseConnection fireBaseConnection;
