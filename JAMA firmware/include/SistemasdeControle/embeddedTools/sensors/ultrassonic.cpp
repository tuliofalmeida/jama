#include "ultrassonic.h"

Ultrassonic::Ultrassonic(gpio_num_t triger, gpio_num_t echo)
{
	gpio_config_t io_conf;
	//interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_HIGH_LEVEL;
    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = (1<<echo);
    //set as input mode    
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = (gpio_pullup_t)1;
    gpio_config(&io_conf);

    //change gpio intrrupt type for one pin
	gpio_set_intr_type(echo, GPIO_INTR_HIGH_LEVEL);

	// //create a queue to handle gpio event from isr
 //    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
 //    //start gpio task
    // xTaskCreate(ultrassonicHandler, "UltrassonicFunction", 2048, NULL, 10, NULL);

    //install gpio isr service
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
	gpio_isr_handler_add(echo, gpio_isr_ultrassinic_handler, (void*) echo);

	gpio_pad_select_gpio(triger);
    gpio_set_direction(triger, GPIO_MODE_OUTPUT);

    Ultrassonic_triger = triger;
    Ultrassonic_echo = echo;
    // Ultrassonic_flag = true;
}

static void IRAM_ATTR gpio_isr_ultrassinic_handler(void* arg)
{
	++Ultrassonic_time;
	// clock_t init_time = clock();
	// while(gpio_get_level(Ultrassonic_echo));	
	// Ultrassonic_time = (uint32_t)clock()-init_time;
	// if(Ultrassonic_flag){
	// 	Ultrassonic_time = 0;
	// 	Ultrassonic_flag = false;
	// 	while(!Ultrassonic_flag)
	// 	{
	// 		// ets_delay_us(1);
	// 		++Ultrassonic_time;
	// 	}
	// }
	// else{
	// 	// Ultrassonic_echo_time = ((clock() - Ultrassonic_time));
	// 	Ultrassonic_flag = true;
	// }
}

 double ultrassonicRead(void)
{
	// while(1)
	// {
		Ultrassonic_time = 0;
		gpio_intr_disable(Ultrassonic_triger);
		ets_delay_us(2);
		gpio_set_level(Ultrassonic_triger,0);
		ets_delay_us(2);
		gpio_set_level(Ultrassonic_triger,1);
		ets_delay_us(10);
		gpio_set_level(Ultrassonic_triger,0);
		ets_delay_us(2);
		gpio_intr_enable(Ultrassonic_triger);

		// while(!gpio_get_level(Ultrassonic_echo));
		// clock_t init_time = clock();
		// while(gpio_get_level(Ultrassonic_echo));
		// Ultrassonic_time = (uint32_t)clock()-init_time;
		// gpio_intr_disable(Ultrassonic_triger);

		vTaskDelay(100 / portTICK_PERIOD_MS);
		Ultrassonic_time_output += (0.1/1.5)*(Ultrassonic_time-Ultrassonic_time_output);
		// y = -0,0622x + 20,131
		// printf("%f\n", -0.062*Ultrassonic_time_output + 20.131);
	// }
		return -0.062*Ultrassonic_time_output + 20.131;
}