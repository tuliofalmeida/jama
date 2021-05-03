#include "SistemasdeControle/headers/zeroFunctionLib/newton.h"
#include <cmath>

template <class UsedType>
void Newton<UsedType>::setInterval(UsedType a, UsedType b)
{
    this->f->setInstance(this->f);
    this->f->setStep    (this->tolerance);

    this->x     = a;
    this->fx    = this->f->sim (a);
    this->dfx   = this->f->diff(a);
}

template <class UsedType>
UsedType Newton<UsedType>::zeroFind()
{
    unsigned n = 1;

    while(true)
    {
        if(std::abs(this->fx) < this->tolerance || n > this->nMaxIterarion)
            break;

        this->x = this->x - (this->fx/this->dfx);
        this->fx    = this->f->sim (this->x);
        this->dfx   = this->f->diff(this->x);

        n++;
    }

    return this->x;
}

template class Newton<float>;
template class Newton<double>;
