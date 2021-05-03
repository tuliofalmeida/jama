#ifndef WIFISTA_H
#define WIFISTA_H

#include "driver/gpio.h"
#include <iostream>
#include <string.h>
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include <lwip/ip.h>
#include <lwip/opt.h>
#include <lwip/arch.h>
#include <lwip/api.h>

#include <sstream>

namespace Communication{
  class WifiSTA
  {
    public:
      WifiSTA(){ this->FunctionToCall = nullptr;}
      ~WifiSTA(){::vTaskDelete(m_pTask);}
      bool connect(void (*FunctionToCall)() = 0);
      bool write(std::string word){ err = netconn_write(this->newconn,  word.c_str(),strlen(word.c_str()),NETCONN_COPY); word.clear(); return 1;}
      void read(std::string readString){this->readString = readString;}

      std::string getData(){ return readString;}
      void clearBuffer(){readString.clear();}

      void setReadString(const std::string &str){this->readString = str;}

      typedef void(*funcCall)(void);
      funcCall getFunctionPointer(){return this->FunctionToCall;}

      bool disconnect(){return 0;}
      void communicationInit();

      /**
       * Singletons should not be cloneable.
       */
      WifiSTA(WifiSTA &other) = delete;
      /**
       * Singletons should not be assignable.
       */
      void operator=(const WifiSTA &) = delete;

      static Communication::WifiSTA* GetInstance();
      static void initializeComunication();

      struct netconn *conn, *newconn;   
      err_t err;
      std::string readString;

      static Communication::WifiSTA* WifiSTA_;

    private:

      void (*FunctionToCall)(void);
      tcpip_adapter_ip_info_t info;
      TaskHandle_t  m_pTask;

      void callFunction();
  };
  static esp_err_t event_handler(void *ctx, system_event_t *event);
  static EventGroupHandle_t wifi_event_group;
  wifi_init_config_t initConfig;
  wifi_config_t config;
  bool initialise_wifi(void);
  #define EXAMPLE_WIFI_SSID "ESP"
  #define EXAMPLE_WIFI_PASS "12345678"
  static const char *TAG = "Wifi Station Mode";
  static const int CONNECTED_BIT = BIT0;
  
  void operator<< (Communication::WifiSTA *wifi, std::string str){ wifi->write(str);}
  // void operator>> (Communication::Wifi wifi, std::string &str);
  // void operator>> (Communication::WifiSTA *wifi, void (*FunctionToCall)());
  // std::ostream& operator<< (std::ostream& output, Communication::Wifi wifi){ output << wifi.readString; return output;}
  // void operator << (Communication::Wifi wifi, std::string str){ wifi.write(str);}
}

Communication::WifiSTA* Communication::WifiSTA::WifiSTA_= nullptr;;

#include "wifista.hpp"
#endif
