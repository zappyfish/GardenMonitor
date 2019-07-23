#include "DataUploader.h"

char host[] = "HOST";
char ssid[] = "SSID";
char pass[] = "SSIDPASS";

DataUploader uploader(host, ssid, pass, true);

float temp = 5;
float light = 6;
float moist = 8.2;

void setup() {
  uploader.init();
}

void loop() {
  temp += 1;
  light += 3.3;
  moist += 2;
  uploader.uploadDataPoint(temp, light, moist);
  delay(2000);
}
