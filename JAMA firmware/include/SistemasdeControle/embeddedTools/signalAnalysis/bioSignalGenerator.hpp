#include "bioSignalGenerator.h"

void ElectroStimulation::bioSignalController::boostInit(const gpio_num_t &pin, const uint32_t &freq, const ledc_channel_t channel)
{
    gpio_pad_select_gpio((gpio_num_t)pin);
    gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT); 

    ledc_timer_boost.duty_resolution = LEDC_TIMER_12_BIT;
    ledc_timer_boost.freq_hz = freq;
    ledc_timer_boost.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_timer_boost.timer_num = LEDC_TIMER_2;
    // Set configuration of timer0 for high speed channels
    ledc_timer_config(&ledc_timer_boost);

    ledc_channel_boost.hpoint     = 0;
	ledc_channel_boost.duty       = 0; 
	ledc_channel_boost.channel    = channel;
	ledc_channel_boost.gpio_num   = pin;
	ledc_channel_boost.timer_sel  = LEDC_TIMER_2;
	ledc_channel_boost.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_config(&ledc_channel_boost);
}

void ElectroStimulation::bioSignalController::setOutputHandlerDirectPin(const gpio_num_t &pin
                                                                        /*, uint8_t freq, ledc_channel_t channel*/)
{
    gpio_pad_select_gpio((gpio_num_t)pin);
    gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT); 
    directPin = pin;
    // ledc_timer_modulation_Direct.duty_resolution = LEDC_TIMER_13_BIT;
    // ledc_timer_modulation_Direct.freq_hz = freq;
    // ledc_timer_modulation_Direct.speed_mode = LEDC_LOW_SPEED_MODE;
    // ledc_timer_modulation_Direct.timer_num = LEDC_TIMER_0;
    // // Set configuration of timer0 for high speed channels
    // ledc_timer_config(&ledc_timer_modulation_Direct);

    // ledc_channel_modulation_Direct.hpoint     = 0;
	// ledc_channel_modulation_Direct.duty       = 0; 
	// ledc_channel_modulation_Direct.channel    = channel;
	// ledc_channel_modulation_Direct.gpio_num   = pin;
	// ledc_channel_modulation_Direct.timer_sel  = LEDC_TIMER_0;
	// ledc_channel_modulation_Direct.speed_mode = LEDC_LOW_SPEED_MODE;
    // ledc_channel_config(&ledc_channel_modulation_Direct);
}

void ElectroStimulation::bioSignalController::setPowerLevel(const double &powerLevel)
{
    ledc_channel_boost.duty       = (uint16_t)((powerLevel)*8192/200); 
    ledc_set_duty(ledc_channel_boost.speed_mode, ledc_channel_boost.channel, ledc_channel_boost.duty);
    ledc_update_duty(ledc_channel_boost.speed_mode, ledc_channel_boost.channel);
}

// void ElectroStimulation::bioSignalController::setModulationTimeOn(const double &dutyCicle)
// {
//    ledc_channel_modulation_Direct.duty       = (uint16_t)((dutyCicle)*8192/100); 
//    ledc_set_duty(ledc_channel_modulation_Direct.speed_mode, ledc_channel_modulation_Direct.channel, ledc_channel_modulation_Direct.duty);
//    ledc_update_duty(ledc_channel_modulation_Direct.speed_mode, ledc_channel_modulation_Direct.channel);
// }


//void ElectroStimulation::bioSignalController::setOutputHandlerReversePin(const gpio_num_t &outputHandlerReversePin)
//{
 ///   this->outputHandlerReversePin = outputHandlerReversePin;
//    gpio_pad_select_gpio(this->outputHandlerReversePin);
/////    gpio_set_direction(this->outputHandlerReversePin, GPIO_MODE_OUTPUT); 
//}
