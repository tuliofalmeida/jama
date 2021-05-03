#ifndef SERVO_H
#define SERVO_H
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

class servomotor{
  public:
    servomotor(gpio_num_t servo_pin);
    void setPosition(unsigned int pos);
    void controlMotor(void*arg);
    // void initControl(uint32_t pos);
  private:
    gpio_num_t servo_pin;
    uint32_t pos;
};

#endif
