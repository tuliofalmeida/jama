#include "SistemasdeControle/headers/zeroFunctionLib/steffensen.h"
#include <cmath>

template <class UsedType>
void steffensen<UsedType>::setInterval(UsedType a, UsedType b)
{
    this->x     = a;
    this->fx    = this->f->sim (a);
}

template <class UsedType>
UsedType steffensen<UsedType>::zeroFind()
{
    unsigned n = 1;

    while(true)
    {
        if(std::abs(this->fx) < this->tolerance || n > this->nMaxIterarion)
            break;

        this->x     = this->x - (pow((this->fx),2)/(this->f->sim(this->x+this->fx) - this->fx));
        this->fx    = this->f->sim (this->x);

        n++;
    }

    return this->x;
}

template class steffensen<float>;
template class steffensen<double>;
