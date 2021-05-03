#ifndef WiFistaTCP_h
#define WiFistaTCP_h

#include <Arduino.h>
#include <AsyncTCP.h>
#include "WiFi.h"
#include <map>

const char *ssid = "ESP";
const char *password = "12345678";

AsyncClient *client;
AsyncServer server(4000);

IPAddress serverIP(192,168,137,100);
IPAddress gateway(192,168,137,1);
IPAddress subnet(255,255,255,0);

typedef String (*SDLEventFunction)(void*,size_t);
std::map<String,SDLEventFunction> functions;

void addFunctions(String functioname, SDLEventFunction function) {
    functions[functioname] = function;
}

void removeFunctions(String functioname) {
    functions.erase(functioname);
}

void onData(void* arg, AsyncClient* c, void* data, size_t len) {
  for (std::map<String,SDLEventFunction>::iterator it = functions.begin() ; it != functions.end(); ++it)
    c->write(((it->second)(data,len)).c_str());
}

void onConnect(void* arg, AsyncClient* c) {
  Serial.print("We're connected!\n");
}

void onDisconnect(void* arg, AsyncClient* c) {
  Serial.print("We're disconnected!\n");
}

void onConnectServer(void* arg, AsyncClient* c){
  Serial.print("We're connected!\n");
  client = c;
  //c->write("hello from server");
  client->onConnect(onConnect);
  client->onDisconnect(onDisconnect);
  client->onData(onData);
}


void wifiSTATCPInit(){
    WiFi.mode(WIFI_STA);
    WiFi.config(serverIP,gateway,subnet);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) 
            delay(1000);
    }
    server.onClient(onConnectServer, NULL);
    server.begin();
}

#endif