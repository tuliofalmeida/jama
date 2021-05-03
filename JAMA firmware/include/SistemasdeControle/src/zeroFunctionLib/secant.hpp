#include "SistemasdeControle/headers/zeroFunctionLib/secant.h"
#include <cmath>

template <class UsedType>
void secant<UsedType>::setInterval(UsedType a, UsedType b)
{
    this->a = a;
    this->b = b;
    this->fa = this->f->sim(a);
    this->fb = this->f->sim(b);

    if(this->fa * this->fb > 0)
        std::cout << "\nNao foi possível encontrar raíz no intervalo dado." << std::endl;
}

template <class UsedType>
UsedType secant<UsedType>::zeroFind()
{
    unsigned n = 1;

    while(true)
    {
        this->m = (this->a*this->fb - this->b*this->fa) / (this->fb - this->fa);
        this->fm = this->f->sim(m);

        if(std::abs(this->fm) < this->tolerance || n > this->nMaxIterarion)
            break;

        if(this->fa * this->fm < 0)
        {
            this->b = this->m;
            this->fb = this->fm;
        }
        else if(this->fb * this->fm < 0)
        {
            this->a = this->m;
            this->fa = this->fm;
        }

        n++;
    }

    return this->m;
}

template class secant<float>;
template class secant<double>;
