#include "bioSignalGeneratorMCPWM.h"

void ElectroStimulation::bioSignalControllerMCPWM::powerControllerInit(const gpio_num_t &pin1, const gpio_num_t &pin2, const uint32_t &freq, const mcpwm_unit_t &mcpwm_num, const mcpwm_timer_t &timer_num)
{
  this->mcpwm_num = mcpwm_num;
  this->timer_num = timer_num;
  mcpwm_config_t  pwm_config;

  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, pin1);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, pin2);

  pwm_config.frequency = freq;    //frequency = 500Hz,
  pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
  pwm_config.cmpr_b = 0;    //duty cycle of PWMxb = 0
  pwm_config.counter_mode = MCPWM_UP_COUNTER;
  pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(mcpwm_num, timer_num, &pwm_config);
  mcpwm_deadtime_enable(mcpwm_num, timer_num, MCPWM_BYPASS_FED, 100,100);

  
  //Enable deadtime on PWM0A and PWM2B with red = (10)*100ns on PWMA
}

void ElectroStimulation::bioSignalControllerMCPWM::setPowerLevel(const double &powerLevel)
{
    //float duty_cycle       = (uint16_t)((powerLevel)*1024/100); 
    //mcpwm_set_signal_low(mcpwm_num, timer_num, MCPWM_OPR_A);
    //mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_A, powerLevel);
    //mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
    //mcpwm_set_duty(mcpwm_num, timer_num, MCPWM_OPR_B, powerLevel);
    //mcpwm_set_duty_type(mcpwm_num, timer_num, MCPWM_OPR_B, MCPWM_DUTY_MODE_1);
    //mcpwm_deadtime_enable(mcpwm_num, timer_num, MCPWM_ACTIVE_HIGH_MODE, 1000,1000);
    mcpwm_config_t  pwm_config;
    pwm_config.frequency = 5000;    //frequency = 500Hz,
    pwm_config.cmpr_a = powerLevel;    //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = powerLevel+10;    //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(mcpwm_num, timer_num, &pwm_config);
    mcpwm_deadtime_enable(mcpwm_num, timer_num, MCPWM_BYPASS_FED, 200,200);
}

void ElectroStimulation::bioSignalControllerMCPWM::setOutputHandlerPin(const gpio_num_t &outputHandlerPin)
{
    this->outputHandlerPin = outputHandlerPin;
    gpio_pad_select_gpio(this->outputHandlerPin);
    gpio_set_direction(this->outputHandlerPin, GPIO_MODE_OUTPUT); 
}

void ElectroStimulation::bioSignalControllerMCPWM::addSignalBehavior(const std::string &signalBehaviorName, const double &signalBehavior)
{
    this->signalBehaviorHandler.emplace(signalBehaviorName, signalBehavior);
}

void ElectroStimulation::bioSignalControllerMCPWM::removeSignalBehavior(const std::string &signalBehaviorName)
{
    this->signalBehaviorHandler.erase (signalBehaviorName);
}

double ElectroStimulation::bioSignalControllerMCPWM::getSignalBehavior(const std::string &signalBehavior) const
{
    return this->signalBehaviorHandler.find(signalBehavior)->second;                        
}

void ElectroStimulation::burstController(void* pvParameter)
{
    bioSignalControllerMCPWM signalHandler = *((bioSignalControllerMCPWM*) pvParameter);  

    while(1){
        signalHandler.setPowerLevel(signalHandler.getSignalBehavior("ccLevel"));
        for(int i = 0; i<10; i++){ 
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(signalHandler.getSignalBehavior("period"));
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(10000-signalHandler.getSignalBehavior("period"));
        }
        ets_delay_us((1000000/signalHandler.getSignalBehavior("freq"))-100000);
    }
}

void ElectroStimulation::normalController(void* pvParameter)
{
    bioSignalControllerMCPWM signalHandler = *((bioSignalControllerMCPWM*) pvParameter);

    while(1){
        signalHandler.setPowerLevel(signalHandler.getSignalBehavior("ccLevel"));
        gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
        ets_delay_us(signalHandler.getSignalBehavior("period"));
        gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
        ets_delay_us((1000000/signalHandler.getSignalBehavior("freq"))-signalHandler.getSignalBehavior("period"));
    }
}

void ElectroStimulation::modulationController(void* pvParameter)
{
    bioSignalControllerMCPWM signalHandler = *((bioSignalControllerMCPWM*) pvParameter);
    
    uint16_t time;
    
    while(1){
        signalHandler.setPowerLevel(signalHandler.getSignalBehavior("ccLevel"));
        time = (1000000/signalHandler.getSignalBehavior("freq"));
        for(int i = 0; i < (500000/time); i++ ){
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(time/2); 
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(time/2);
        }
        time = (1000000/(signalHandler.getSignalBehavior("freq")/2));
        for(int i = 0; i < (500000/time); i++ ){
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(time/2); 
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(time/2); 
        }
    }
}

void ElectroStimulation::sd1Controller(void* pvParameter)
{
    bioSignalControllerMCPWM signalHandler = *((bioSignalControllerMCPWM*) pvParameter);

    uint16_t time, value, valDecay;
    double K = 4/50;
    
    while(1){
        time = (1000000/signalHandler.getSignalBehavior("freq"));
        // duty = signalHandler.getSignalBehavior("period");
        value = signalHandler.getSignalBehavior("ccLevel");
        valDecay = K*(signalHandler.getSignalBehavior("ccLevel")/signalHandler.getSignalBehavior("freq"));
        // dutyDecay = K*(signalHandler.getSignalBehavior("period")/signalHandler.getSignalBehavior("freq"));
        gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
        signalHandler.setPowerLevel(value);
        for(uint32_t i = 0; i < (uint32_t)(5000000/time); ++i){
            //gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            //ets_delay_us(duty += dutyDecay);
            //gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            //ets_delay_us(time-duty);
            signalHandler.setPowerLevel(value -= valDecay);
            ets_delay_us(time);
        }
        for(uint32_t i = 0; i < (uint32_t)(5000000/time); ++i){
            //gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            //ets_delay_us(duty -= dutyDecay);
            //gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            //ets_delay_us(time-duty);
            signalHandler.setPowerLevel(value += valDecay);
            ets_delay_us(time);
        }
    }
}

void ElectroStimulation::sd2Controller(void* pvParameter)
{
    bioSignalControllerMCPWM signalHandler = *((bioSignalControllerMCPWM*) pvParameter);

    uint16_t time, duty, value, valDecay, dutyDecay;
    
    while(1){
        time = (1000000/signalHandler.getSignalBehavior("freq"));
        duty = signalHandler.getSignalBehavior("period");
        value = signalHandler.getSignalBehavior("ccLevel");
        valDecay = (7*signalHandler.getSignalBehavior("ccLevel"))/(50*signalHandler.getSignalBehavior("freq"));
        dutyDecay = (7*signalHandler.getSignalBehavior("period"))/(50*signalHandler.getSignalBehavior("freq"));

        signalHandler.setPowerLevel(value);
        for(int i = 0; i < (5000000/time); i++){
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(duty);
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(time-duty);
            duty += dutyDecay;
            value -= valDecay;
            signalHandler.setPowerLevel(value);
        }
        for(int i = 0; i < (5000000/time); i++){
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(duty);
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(time-duty);
            duty -= dutyDecay;
            value += valDecay;
            signalHandler.setPowerLevel(value);
        }
    }
}