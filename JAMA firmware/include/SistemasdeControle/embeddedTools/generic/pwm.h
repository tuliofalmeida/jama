// #ifndef PWM_H_INCLUDED
// #define PWM_H_INCLUDED

// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/ledc.h"
// #include "esp_err.h"

// class PWM
// {
// public:
//     PWM(gpio_num_t pin, uint16_t freq, uint8_t channel);
//     void update(uint16_t duty);
//     uint16_t getDuty() { return ledc_channel.duty; }

// private:
//     ledc_channel_config_t ledc_channel;
//     ledc_timer_config_t ledc_timer;
// };

// #endif