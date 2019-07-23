//
// Created by Liam Kelly on 7/22/19.
//

#include "DataUploader.h"

DataUploader::DataUploader(char *firebasehost, char *ssid, char *pass, bool debug) {
    ssID = ssid;
    passw = pass;
    firebaseHost = firebasehost;
    debugOn = debug;
}

DataUploader::~DataUploader() {}

void DataUploader::init() {
  if (debugOn) {
    Serial.begin(9600);
  }
  int status = WL_IDLE_STATUS;
    WiFi.begin(ssID, passw);
    while (status != WL_CONNECTED) {
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssID, passw);
        // wait 1 second for connection:
        Serial.println("attempting to connect");
        delay(1000);
    }
    if (debugOn) {
      Serial.println("connected to wifi");
    }
}

bool DataUploader::uploadDataPoint(float temp, float light, float moist) {
    // close any connection before send a new request.
    client.stop();
    client.flush();
    // send SSL request
    if (client.connectSSL(firebaseHost, 443)) {
        // PUT request
        String toSend = "POST /data";
        toSend += ".json HTTP/1.1\r\n";
        toSend += "Host:";
        toSend += firebaseHost;
        toSend += "\r\n" ;
        toSend += "Content-Type: application/json\r\n";
        String payload = "{\"timestamp\":{\".sv\":\"timestamp\"},\"temp\":";
        payload += temp;
        payload += ",\"light\":";
        payload += light;
        payload += ",\"moist\":";
        payload += moist;
        payload += "}";
        payload += "\r\n";
        toSend += "Content-Length: " + String(payload.length()) + "\r\n";
        toSend += "\r\n";
        toSend += payload;
        client.println(toSend);
        client.println();
        client.flush();
        client.stop();
        if (debugOn) {
          Serial.println("success");
        }
        return true;
    } else {
        // if you couldn't make a connection:
        client.flush();
        client.stop();
        Serial.println("failure");
        return false;
    }
}
