#ifndef FZERO_H
#define FZERO_H

#include "SistemasdeControle/headers/modelLibs/model.h"

template <class UsedType>
class FZero
{
protected:
    unsigned nMaxIterarion;
    UsedType tolerance;
    Model<UsedType> *f;

public:
    FZero(Model<UsedType> *f);
    virtual UsedType zeroFind()=0;
    virtual void setInterval(double a, double b = 0)=0;
};

#endif // FZERO_H
