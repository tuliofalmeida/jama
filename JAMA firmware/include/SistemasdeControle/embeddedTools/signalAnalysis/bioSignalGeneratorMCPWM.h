#ifndef BIOSIGNALGENERATOR_H
#define BIOSIGNALGENERATOR_H

#include <iostream>
#include <map>
#include "esp_attr.h"

#include "driver/mcpwm.h"

namespace ElectroStimulation{
    class bioSignalControllerMCPWM
    {
    public:
        bioSignalControllerMCPWM(){}
        void powerControllerInit(const gpio_num_t &pin1, const gpio_num_t &pin2, const uint32_t &freq, const mcpwm_unit_t &mcpwm_num, const mcpwm_timer_t &timer_num);
        void setPowerLevel(const double &powerLevel);
        void setOutputHandlerPin(const gpio_num_t &outputHandlerPin);
        gpio_num_t getOutputHandlerPin () const {return outputHandlerPin;}

        void addSignalBehavior(const std::string &signalBehaviorName, const double &signalBehavior);
        void removeSignalBehavior(const std::string &signalBehaviorName);
        double getSignalBehavior(const std::string &signalBehavior) const;

    private:

        mcpwm_unit_t mcpwm_num;
        mcpwm_timer_t timer_num;
        gpio_num_t outputHandlerPin;
        std::map<std::string, double> signalBehaviorHandler;
        
    };

    static void burstController(void*);
    static void normalController(void*);
    static void modulationController(void*);
    static void sd1Controller(void*);
    static void sd2Controller(void*);
}

#include "bioSignalGeneratorMCPWM.hpp"

#endif