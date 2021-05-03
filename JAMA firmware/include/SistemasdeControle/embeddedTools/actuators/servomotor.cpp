#include "servomotor.h"

servomotor::servomotor(gpio_num_t servo_pin)
{
    this->servo_pin = servo_pin;
    gpio_pad_select_gpio(servo_pin);
    gpio_set_direction(servo_pin, GPIO_MODE_OUTPUT);
    return;
}

void servomotor::controlMotor(void*arg)
{
	while(1) {
        this->setPosition(this->pos);
    }
}

void servomotor::setPosition(unsigned int pos)
{
  // programação feita com lógica inversa, pois usei um transistor bc337 para aumentar a tensão de 3,3 para 5v
      gpio_set_level(servo_pin,1);
      ets_delay_us((uint32_t)pos);
      gpio_set_level(servo_pin,0);
      ets_delay_us((uint32_t)10000-pos);
}
