# Electrostimulation

[![NPM Version][npm-image]][npm-url]
[![Build Status][travis-image]][travis-url]
[![Downloads Stats][npm-downloads]][npm-url]

Implemented Templates:

![](../2.jpeg)
![](../3.jpeg)


# Burst Controller

```C++
void ElectroStimulation::burstController(void* pvParameter)
{
    bioSignalController signalHandler = *((bioSignalController*) pvParameter);  

    while(1){
        signalHandler.setPowerLevel(signalHandler.getSignalBehavior("ccLevel"));
        for(int i = 0; i<10; i++){ 
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(signalHandler.getSignalBehavior("period"));
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(10000-signalHandler.getSignalBehavior("period"));
        }
        ets_delay_us((1000000/signalHandler.getSignalBehavior("freq"))-100000);
    }
}
```

# Normal Controller

```C++
void ElectroStimulation::normalController(void* pvParameter)
{
    bioSignalController signalHandler = *((bioSignalController*) pvParameter);

    while(1){
        signalHandler.setPowerLevel(signalHandler.getSignalBehavior("ccLevel"));
        gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
        ets_delay_us(signalHandler.getSignalBehavior("period"));
        gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
        ets_delay_us((1000000/signalHandler.getSignalBehavior("freq"))-signalHandler.getSignalBehavior("period"));
    }
}
```

# Modulation Controller

```C++
void ElectroStimulation::modulationController(void* pvParameter)
{
    bioSignalController signalHandler = *((bioSignalController*) pvParameter);
    
    uint16_t time;
    
    while(1){
        signalHandler.setPowerLevel(signalHandler.getSignalBehavior("ccLevel"));
        time = (1000000/signalHandler.getSignalBehavior("freq"));
        for(int i = 0; i < (500000/time); i++ ){
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(time/2); 
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(time/2);
        }
        time = (1000000/(signalHandler.getSignalBehavior("freq")/2));
        for(int i = 0; i < (500000/time); i++ ){
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(time/2); 
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(time/2); 
        }
    }
}
```

# SD1 Controller

```C++
void ElectroStimulation::sd1Controller(void* pvParameter)
{
    bioSignalController signalHandler = *((bioSignalController*) pvParameter);

    uint16_t time, value, valDecay;
    double K = 4/50;
    
    while(1){
        time = (1000000/signalHandler.getSignalBehavior("freq"));
        value = signalHandler.getSignalBehavior("ccLevel");
        valDecay = K*(signalHandler.getSignalBehavior("ccLevel")/signalHandler.getSignalBehavior("freq"));
        gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
        signalHandler.setPowerLevel(value);
        for(uint32_t i = 0; i < (uint32_t)(5000000/time); ++i){
            signalHandler.setPowerLevel(value -= valDecay);
            ets_delay_us(time);
        }
        for(uint32_t i = 0; i < (uint32_t)(5000000/time); ++i){
            signalHandler.setPowerLevel(value += valDecay);
            ets_delay_us(time);
        }
    }
}
```

# SD2 Controller

```C++
void ElectroStimulation::sd2Controller(void* pvParameter)
{
    bioSignalController signalHandler = *((bioSignalController*) pvParameter);

    uint16_t time, duty, value, valDecay, dutyDecay;
    
    while(1){
        time = (1000000/signalHandler.getSignalBehavior("freq"));
        duty = signalHandler.getSignalBehavior("period");
        value = signalHandler.getSignalBehavior("ccLevel");
        valDecay = (7*signalHandler.getSignalBehavior("ccLevel"))/(50*signalHandler.getSignalBehavior("freq"));
        dutyDecay = (7*signalHandler.getSignalBehavior("period"))/(50*signalHandler.getSignalBehavior("freq"));

        signalHandler.setPowerLevel(value);
        for(int i = 0; i < (5000000/time); i++){
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(duty);
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(time-duty);
            duty += dutyDecay;
            value -= valDecay;
            signalHandler.setPowerLevel(value);
        }
        for(int i = 0; i < (5000000/time); i++){
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 1);
            ets_delay_us(duty);
            gpio_set_level((gpio_num_t) signalHandler.getOutputHandlerPin(), 0);
            ets_delay_us(time-duty);
            duty -= dutyDecay;
            value += valDecay;
            signalHandler.setPowerLevel(value);
        }
    }
}

```
<!-- Markdown link & img dfn's -->
[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/yourname/yourproject/wiki