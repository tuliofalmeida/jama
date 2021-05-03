#ifndef SECANT_H
#define SECANT_H

#include "fzero.h"

template <class UsedType>
class secant : public FZero<UsedType>
{
   UsedType a,b,m,fa,fb,fm;


public:
   secant(Model<UsedType> *f): FZero<UsedType>(f){}

   void setInterval(UsedType a, UsedType b);
   UsedType zeroFind();
};

#endif // SECANT_H
