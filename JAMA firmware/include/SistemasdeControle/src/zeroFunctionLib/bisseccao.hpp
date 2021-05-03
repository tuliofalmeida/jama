#include "SistemasdeControle/headers/zeroFunctionLib/bisseccao.h"
#include <cmath>

template <class UsedType>
void bisseccao<UsedType>::setInterval(UsedType a, UsedType b)
{
    this->a = a;
    this->b = b;
    this->fa = this->f->sim(a);
    this->fb = this->f->sim(b);

    if(this->fa * this->fb > 0)
        std::cout << "\nNao foi possível encontrar raíz no intervalo dado." << std::endl;
}

template <class UsedType>
UsedType bisseccao<UsedType>::zeroFind()
{
    unsigned n = 1;

    while(this->fa * this->fb < 0)
    {
        this->c = (this->a + this->b) / 2;
        this->fc = this->f->sim(c);

        if(std::abs(this->fc) < this->tolerance || n > this->nMaxIterarion)
            break;

        if(this->fa * this->fc < 0)
        {
            this->b = this->c;
            this->fb = this->fc;
        }
        else if(this->fb * this->fc < 0)
        {
            this->a = this->c;
            this->fa = this->fc;
        }
    }

    return this->c;
}

template class bisseccao<float>;
template class bisseccao<double>;
