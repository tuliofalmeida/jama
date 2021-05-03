#ifndef STEPPER_H
#define STEPPER_H
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

class stepperA4988{
  public:
    stepperA4988(gpio_num_t step_pin, gpio_num_t direction_pin);
    void newStep(bool direction = false);
  private:
    gpio_num_t step_pin, direction_pin;
    bool direction;
};

#endif
