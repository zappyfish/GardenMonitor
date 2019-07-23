//
// Created by Liam Kelly on 7/22/19.
//

#ifndef JONNYLIB_DATA_UPLOADER_H
#define JONNYLIB_DATA_UPLOADER_H

#include <Arduino.h>
#include <WiFi101.h>
#include <WiFiSSLClient.h>


class DataUploader {

public:

    DataUploader(char *firebasehost, char *ssid, char *pass, bool debug);
    ~DataUploader();

    bool uploadDataPoint(float temp, float light, float moist);
    void init();


private:

    WiFiSSLClient client;

    char *firebaseHost;
    char *ssID;
    char *passw;

    bool debugOn;

};


#endif //JONNYLIB_DATA_UPLOADER_H
