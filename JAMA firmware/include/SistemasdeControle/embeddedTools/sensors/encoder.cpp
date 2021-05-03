#include "encoder.h"

Encoder::Encoder(gpio_num_t pin)
{
	gpio_config_t io_conf;
	//interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = (1<<pin);
    //set as input mode    
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = (gpio_pullup_t)1;
    gpio_config(&io_conf);

    //change gpio intrrupt type for one pin
	gpio_set_intr_type(pin, GPIO_INTR_POSEDGE);

	//create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    //start gpio task
    xTaskCreate(encodeHandler, "gpio_task_example", 2048, NULL, 10, NULL);

    //install gpio isr service
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
	gpio_isr_handler_add(pin, gpio_isr_handler, (void*) pin);
}

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    // gpio_num_t gpio_num = (gpio_num_t)((uint32_t) arg);
    counter++;
    // xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void encodeHandler(void* arg)
{
    // gpio_num_t io_num;
    for(;;) {
    	vTaskDelay(1000 / portTICK_PERIOD_MS);
    	printf("%d\n", counter);
    	counter = 0;

        // if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            // printf("GPIO[%d] intr, val: %d\n", (uint32_t)io_num, gpio_get_level(io_num));
        // }
    }
}