#ifndef STEFFENSEN_H
#define STEFFENSEN_H

#include "fzero.h"


//! Classe steffensen, com o intuito de encontrar o zero de uma função modelo.
/*!
  x = valor final
  fx =
*/

template <class UsedType>
class steffensen : public FZero<UsedType>
{
   UsedType x,fx;


public:
   steffensen(Model<UsedType> *f): FZero<UsedType>(f){}

   void setInterval(UsedType a, UsedType b);
   UsedType zeroFind();
};

#endif // STEFFENSEN_H
