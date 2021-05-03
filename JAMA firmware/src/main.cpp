#include <Arduino.h>
#include <AsyncTCP.h>
#include "WiFi.h"
#include <sstream>
#include "sendIMUData.h"

void setup() {
  Serial.begin(115200);
  serverIP = IPAddress(192,168,137,102);
  wifiSTATCPInit();
  addFunctions("imuSendInit",imuSendInit);
}

void loop() {
  delay(1);
}