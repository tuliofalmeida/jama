#ifndef NEWTON_H
#define NEWTON_H

#include "fzero.h"

template <class UsedType>
class Newton : public FZero<UsedType>
{
   UsedType x,fx,dfx;


public:
   Newton(Model<UsedType> *f): FZero<UsedType>(f){}

   void setInterval(UsedType a, UsedType b);
   UsedType zeroFind();
};

#endif // NEWTON_H
