#include <Arduino.h>
#include <AsyncTCP.h>
#include "WiFi.h"
#include <sstream>
#include "sendIMUData.h"

/*
DONE BY: Tulio F. Almeida and André Dantas


MIT License
Copyright (c) 2021 Tulio F. Almeida
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
___________________________________________________
These files must be changed:

serverIP = Determine ESP IP Aaddress
freq = Determine the frequency of the acquisition 

In "WiFistaTCP_h":
You must change the name and password of the hotspot 
or set these variables to create the hotspot

const char *ssid = "ESP";
const char *password = "12345678";
____________________________________________________
*/

void setup() {
  Serial.begin(115200);
  serverIP = IPAddress(192,168,137,100);
  freq = 75
  wifiSTATCPInit();
  addFunctions("imuSendInit",imuSendInit);
}

void loop() {
  delay(1);
}