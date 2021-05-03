#include "wifi.h"

bool Communication::Wifi::connect(void (*FunctionToCall)(std::string))
{
  this->FunctionToCall = FunctionToCall;
  esp_event_loop_init(event_handler, NULL);
  wifi_event_group = xEventGroupCreate();
  this->setDHCPConfig();
  // this->start_dhcp_server();
  this->setWifiConfig();  
  this->initialise_wifi_in_ap();

  //  communicationInit();
  // ::xTaskCreatePinnedToCore(&taskRead, "Wifi Read Data", 1024, this, 5, NULL, 1);
  // ::xTaskCreate(&taskRead, "Wifi Read Data", 5*1024, this, 5, NULL);
  return 1;
}

void Communication::Wifi::setDHCPConfig(void)
{
  tcpip_adapter_init();
  tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);
  this->info = tcpip_adapter_ip_info_t();
  memset  (&this->info, 0, sizeof(this->info));
  IP4_ADDR(&this->info.ip, 192, 168, 4, 1);
  IP4_ADDR(&this->info.gw, 192, 168, 4, 1);
  IP4_ADDR(&this->info.netmask, 255, 255, 255, 0);  
  tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &this->info);
  tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP);
}

void Communication::Wifi::setWifiConfig(void)
{
  strcpy((char *)this->config.ap.ssid, "Eletroestimulador");
  this->config.ap.ssid_hidden = 0;
  this->config.ap.channel = 3;
  this->config.ap.ssid_len = strlen("AndreFelipe");
  this->config.ap.authmode = WIFI_AUTH_WPA2_PSK;
  strcpy((char *)this->config.ap.password, "12345678");
  this->config.ap.max_connection = 3;
  this->config.ap.beacon_interval = 752;
}

bool Communication::Wifi::start_dhcp_server(void){
  // tcpip_adapter_init();
  // tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);
  // std::cout << this->info.ip;
  // tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &this->info);
  // tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP);
  return 1;
}

bool Communication::Wifi::initialise_wifi_in_ap(void)
{
  this->initConfig = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&this->initConfig);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_mode(WIFI_MODE_AP);
    
  esp_wifi_set_config(WIFI_IF_AP, &this->config);
  esp_wifi_start();
  return 1;
}

void Communication::Wifi::communicationInit()
{
  this->conn = netconn_new(NETCONN_TCP);  //cria um novo identificador de conexão
  netconn_bind(this->conn,NULL,4000); //associa a conexão à porta 4000
  netconn_listen(this->conn); //começa a escutar a conexão
}

void Communication::Wifi::callFunction(const std::string &data)
{
  ((*this->FunctionToCall)(data));
}

void Communication::Wifi::taskRead(void* param)
{
  Wifi wifi = *((Wifi*)param);
  wifi.communicationInit();
  while(1){
    wifi.err = netconn_accept(wifi.conn, &wifi.newconn);
    if(wifi.err == ERR_OK) {// processando a nova conexão
      struct netbuf *buf; // criando um buffer para armazenar os dados recebidos via wifi
      void *data;      std::string data_char;      u16_t len;
      while((wifi.err = netconn_recv(wifi.newconn, &buf)) == ERR_OK){//entrando na rotina se algum dado for recebido
        // do{
          netbuf_data(buf,&data,&len);//lê os dados recebidos e coloca no buffer
          data_char = (char*)data; //convertendo os dados recebidos para caracter
          //wifi.setReadString(data_char);
          // wifi.write(wifi.getData());
          //std::cout << wifi.getData();
          if(wifi.getFunctionPointer())
            wifi.callFunction(data_char);
	        netbuf_free(buf);
        // }while(netbuf_next(buf) >= 0);//enquanto tiver dados recebidos, continua a executar
      }
      netconn_close(wifi.newconn);      
      netconn_delete(wifi.newconn);
    }
  }
}

void Communication::operator>> (Communication::Wifi &wifi, void (*FunctionToCall)(Communication::Wifi &wifi))
{ 
  wifi.communicationInit();
  wifi.err = netconn_accept(wifi.conn, &wifi.newconn);
  if(wifi.err == ERR_OK) {// processando a nova conexão
    struct netbuf *buf; // criando um buffer para armazenar os dados recebidos via wifi
    void *data;      std::string data_char;      u16_t len;
    while((wifi.err = netconn_recv(wifi.newconn, &buf)) == ERR_OK){//entrando na rotina se algum dado for recebido
        netbuf_data(buf, &data, &len);//lê os dados recebidos e coloca no buffer
        data_char = (char*)data; //convertendo os dados recebidos para caracter
        wifi.setReadString(data_char);
        (*FunctionToCall)(wifi);
        netbuf_free(buf);
    }
  }
  netconn_close(wifi.newconn);      
  netconn_delete(wifi.newconn);
}

static esp_err_t Communication::event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_AP_START:
    printf("Event: ESP32 is started in AP mode\n");
    break;
    
  case SYSTEM_EVENT_AP_STACONNECTED:
    xEventGroupSetBits(wifi_event_group, BIT0);
    break;

  case SYSTEM_EVENT_AP_STADISCONNECTED:
    xEventGroupSetBits(wifi_event_group, BIT1);
    break;    
    default:
        break;
    }
    return ESP_OK;
}


