#ifndef SERIAL_H
#define SERIAL_H

#include <string.h>
#include <string>
#include "driver/uart.h"

namespace Communication{
    static uint16_t BUF_SIZE = 1024;
    class Serial
    {
    public:
        Serial(uint16_t timeDelay = 1000){data =  (uint8_t *) malloc(Communication::BUF_SIZE); len = 0; this->timeDelay = timeDelay;}
        ~Serial(){}
        void connect();
        void write(std::string str){uart_write_bytes(UART_NUM_0, str.c_str(), str.size());}
        uint8_t read();
        std::string getData(){ std::string str; if(len < 1024) for(uint16_t i = 0; i < len; ++i) str += data[i]; return str; }

    private:
        uart_config_t uart_config;
        uint8_t *data;
        uint16_t len;
        uint16_t timeDelay;
    };
    void operator<< (Communication::Serial uart, std::string str){ uart.write(str);}
    void operator>> (Communication::Serial uart, std::string &str){ uart.read(); str = uart.getData(); }
}

#include "serial.hpp"
#endif