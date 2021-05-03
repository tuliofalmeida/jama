#ifndef ULTRASSONIC_H_INCLUDED
#define ULTRASSONIC_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "rom/ets_sys.h"

class Ultrassonic
{
public:
  Ultrassonic(gpio_num_t triger, gpio_num_t echo); 

};

volatile static gpio_num_t Ultrassonic_triger, Ultrassonic_echo;
volatile static bool Ultrassonic_flag;
volatile static uint32_t Ultrassonic_time;
volatile static double Ultrassonic_time_output = 0;
// volatile static uint32_t Ultrassonic_echo_time;
static void IRAM_ATTR gpio_isr_ultrassinic_handler(void* arg);
 double ultrassonicRead(void);

#endif