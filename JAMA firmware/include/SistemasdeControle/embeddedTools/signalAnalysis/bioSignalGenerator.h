#ifndef BIOSIGNALGENERATOR_H
#define BIOSIGNALGENERATOR_H

#include <iostream>
#include <time.h>
#include <driver/adc.h>
#include "esp_adc_cal.h"
#include "esp_system.h"
#include "rom/ets_sys.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "map"
#include "driver/i2s.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "soc/sens_reg.h"
#include <soc/sens_struct.h>
#include "soc/rtc.h"
#include "soc/syscon_struct.h"

namespace ElectroStimulation{
    class bioSignalController{
    public:
        bioSignalController(){}
        void boostInit(const gpio_num_t &pin, const uint32_t &freq, const ledc_channel_t channel);
        void setOutputHandlerDirectPin(const gpio_num_t &pin);
        void setPowerLevel(const double &powerLevel);
        void setOutputDirectPin(){gpio_set_level(directPin, true);}
        void resetOutputDirectPin(){gpio_set_level(directPin, false);}
        //void setModulationTimeOn(const double &dutyCicle);
        //void setOutputHandlerDirectPin(const gpio_num_t &pin/*, uint8_t freq, ledc_channel_t channel*/);
        //void setOutputHandlerReversePin(const gpio_num_t &outputHandlerReversePin);

    private:
        ledc_channel_config_t ledc_channel_boost,ledc_channel_modulation_Direct;
        ledc_timer_config_t ledc_timer_boost,ledc_timer_modulation_Direct;
        gpio_num_t directPin; 
    };
    
}

#include "bioSignalGenerator.hpp"
#endif // BIOSIGNALGENERATOR_H
