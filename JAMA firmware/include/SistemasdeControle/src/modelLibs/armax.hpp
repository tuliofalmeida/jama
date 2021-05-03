#include "SistemasdeControle/headers/modelLibs/armax.h"

template <class UsedType>
ARMAX<UsedType>::ARMAX()
{

}

template <class UsedType>
void ARMAX<UsedType>::setLinearVector(LinAlg::Matrix<UsedType> Input, LinAlg::Matrix<UsedType> Output)
{

}

template <class UsedType>
void ARMAX<UsedType>::setLinearModel(LinAlg::Matrix<UsedType> Input, LinAlg::Matrix<UsedType> Output)
{

}

template <class UsedType>
void ARMAX<UsedType>::print()
{

}

template <class UsedType>
UsedType ARMAX<UsedType>::sim(UsedType input)
{

}

template <class UsedType>
UsedType ARMAX<UsedType>::sim(UsedType x, UsedType y)
{

}

template <class UsedType>
LinAlg::Matrix<UsedType> ARMAX<UsedType>::sim(LinAlg::Matrix<UsedType> x)
{

}

template <class UsedType>
LinAlg::Matrix<UsedType> ARMAX<UsedType>::sim(LinAlg::Matrix<UsedType> x, LinAlg::Matrix<UsedType> y)
{

}

template <class UsedType>
LinAlg::Matrix<UsedType> ARMAX<UsedType>::sim(UsedType lsim, UsedType lmax, UsedType step)
{

}

//template <class UsedType>
//void Sim<UsedType>::SetArmaxOneStep()
//{
//    this->LinSysOneStep.zeros(1, this->nInPut*this->InPut.getCols() + this->nOutPut*this->OutPut.getCols() + this->nError);

//    int cont = 1;
//    for(int i = 1; i <= this->OutPut.getCols(); i++)
//    {
//        for(int j = 1; j <= this->nOutPut; j++)
//        {
//            this->LinSysOneStep.add(1, cont, -this->EstOutPut(this->nSample - j, i));
//            cont++;
//        }
//    }
//    for(int i = 1; i <= this->InPut.getCols(); i++)
//    {
//        for(int j = 1; j <= this->nInPut; j++)
//        {
//            this->LinSysOneStep.add(1, cont, this->InPut(this->nSample - j, i));
//            cont++;
//        }
//    }

//    for(int j = 1; j <= this->nError; j++)
//    {
//        this->LinSysOneStep.add(1, cont, this->Error(this->nSample - j, 1));
//        cont++;
//    }
//}

//template class TransferFunction<int>;
template class ARMAX<float>;
template class ARMAX<double>;
