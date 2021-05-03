#ifndef BISSECCAO_H
#define BISSECCAO_H

#include "fzero.h"

template <class UsedType>
class bisseccao : public FZero<UsedType>
{    
   UsedType a,b,c,fa,fb,fc;


public:
   bisseccao(Model<UsedType> *f): FZero<UsedType>(f){}

   void setInterval(UsedType a, UsedType b);
   UsedType zeroFind();
};

#endif // BISSECCAO_H
