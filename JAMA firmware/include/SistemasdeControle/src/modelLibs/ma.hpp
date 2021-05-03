#include "SistemasdeControle/headers/modelLibs/ma.h"

template <class UsedType>
MA<UsedType>::MA()
{
}

template <class UsedType>
void MA<UsedType>::setLinearVector(LinAlg::Matrix<UsedType> Input, LinAlg::Matrix<UsedType> Output)
{

}

template <class UsedType>
void MA<UsedType>::setLinearModel(LinAlg::Matrix<UsedType> Input, LinAlg::Matrix<UsedType> Output)
{

}

template <class UsedType>
void MA<UsedType>::print()
{

}

template <class UsedType>
UsedType MA<UsedType>::sim(UsedType input)
{

}

template <class UsedType>
UsedType MA<UsedType>::sim(UsedType x, UsedType y)
{

}

template <class UsedType>
LinAlg::Matrix<UsedType> MA<UsedType>::sim(LinAlg::Matrix<UsedType> x)
{

}

template <class UsedType>
LinAlg::Matrix<UsedType> MA<UsedType>::sim(LinAlg::Matrix<UsedType> x, LinAlg::Matrix<UsedType> y)
{

}

template <class UsedType>
LinAlg::Matrix<UsedType> MA<UsedType>::sim(UsedType lsim, UsedType lmax, UsedType step)
{

}

//template <class UsedType>
//void Sim<UsedType>::SetArmaxOneStep()
//{
//    this->LinSysOneStep.zeros(1, this->nInPut*this->InPut.getCols() + this->nOutPut*this->OutPut.getCols() + this->nError);

//    for(int j = 1; j <= this->nError; j++)
//    {
//        this->LinSysOneStep.add(1, cont, this->Error(this->nSample - j, 1));
//        cont++;
//    }
//}

//template class TransferFunction<int>;
template class MA<float>;
template class MA<double>;
