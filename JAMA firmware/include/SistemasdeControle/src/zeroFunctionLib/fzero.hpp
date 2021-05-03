#include "SistemasdeControle/headers/zeroFunctionLib/fzero.h"

template <class UsedType>
FZero<UsedType>::FZero(Model<UsedType> *f)
{
    this->f             = f;
    this->nMaxIterarion = 500;
    this->tolerance     = DBL_EPSILON * 10;

}

template class FZero<float>;
template class FZero<double>;
