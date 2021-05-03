#include "serial.h"

void Communication::Serial::connect()
{
    
    this->uart_config.baud_rate = 115200;
    this->uart_config.data_bits = UART_DATA_8_BITS;
    this->uart_config.parity    = UART_PARITY_DISABLE;
    this->uart_config.stop_bits = UART_STOP_BITS_1;
    this->uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;

    uart_param_config(UART_NUM_0, &this->uart_config);
    uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_0, Communication::BUF_SIZE * 2, 0, 0, NULL, 0);

}

uint8_t Communication::Serial::read()
{
    this->len = uart_read_bytes(UART_NUM_0, data, BUF_SIZE, this->timeDelay / portTICK_RATE_MS);
    return len;
}