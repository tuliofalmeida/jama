#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
	
static uint32_t counter = 0;
class Encoder
{
public:
	Encoder(gpio_num_t pin);	
};

static xQueueHandle gpio_evt_queue = NULL;
static void IRAM_ATTR gpio_isr_handler(void* arg);
static void encodeHandler(void* arg);

#endif