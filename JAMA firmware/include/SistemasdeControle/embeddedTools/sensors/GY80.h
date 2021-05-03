#ifndef GY80_H
#define GY80_H 

template<class Type>
class GY80{
 public:
    GY80(gpio_num_t pin)
    {
       this->pin = &pin;
    }
    virtual LinAlg::Matrix<Type> get();

 private:
    LinAlg::Matrix<Type> input;
    gpio_num_t *pin;
    
};
#endif