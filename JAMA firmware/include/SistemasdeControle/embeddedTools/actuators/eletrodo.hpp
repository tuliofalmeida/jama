#ifndef ELETRODO_H
#define ELETRODO_H

#include "generic/pwm.h"

template <class Type>
class Eletrodo : public Output
{
public:
   Eletrodo(gpio_num_t pin, uint16_t freq, uint8_t channel) 
   { 
      PWM ch(pin, freq, channel);
      this->_ch = &ch;
   }
   virtual void set(const LinAlg::Matrix<Type> &output)
   {
      this->output = output;
      this->_ch.update(output);
   }
   LinAlg::Matrix<Type> &getOutput() const
   {
      return this->output;
   }

private:
   LinAlg::Matrix<Type> output;
   PWM *_ch;
};
#endif

// Input<double> *fio = new Eletrodo<double>();
// fio->getInput();
// Eletrodo<double> t;
// t.getInput();