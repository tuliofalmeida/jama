#include "SistemasdeControle/headers/restrictedOptimization/generalisedrestrictednewton.h"

template <typename Type>
restrictedOptimizationHandler::GeneralisedRestrictedNewton<Type>::GeneralisedRestrictedNewton(ModelHandler::Model<restrictedOptimizationHandler::Type> *model)
{
    this->model = model;
    this->X = LinAlg::Zeros<Type>(this->model->getNumberOfVariables(),1);
    this->dFunc = LinAlg::Zeros<Type>(this->model->getOutputMatrix().getNumberOfRows(), this->model->getNumberOfVariables());
}

template <typename Type>
void restrictedOptimizationHandler::GeneralisedRestrictedNewton<Type>::Jacobian()
{
    this->model->setModelCoef(this->X);

    LinAlg::Matrix<Type> fx = this->model->sim(this->model->getInputMatrix());
    LinAlg::Matrix<Type> Dfx;
    LinAlg::Matrix<Type> deltX = LinAlg::Zeros<Type>(this->X.getNumberOfRows(),1);

    deltX(1,1) = 0.01;
    for(unsigned j = 1; j <= this->dFunc.getNumberOfColumns(); ++j){

        this->model->setModelCoef(this->X + deltX);
        deltX(j+1,1) = deltX(j,1);
        deltX(j,1) = 0;
        Dfx = this->model->sim(this->model->getInputMatrix());

        this->dFunc(i,j) = (Dfx - fx)/0.01;
    }
}

template <typename Type>
void restrictedOptimizationHandler::GeneralisedRestrictedNewton<Type>::funcBuild()
{
    this->model->setModelCoef(this->X);
    this->Func = this->model->sim(this->model->getInputMatrix()) - this->model->getOutputMatrix();
}

//template<typename Type>
//void restrictedOptimizationHandler::GeneralisedRestrictedNewton<Type>::setOptimizationConstraints(Type duMax, Type duMin, Type yMax,
//                                                                              Type yMin, Type uMax, Type uMin,
//                                                                              const LinAlg::Matrix<Type> &uk1,
//                                                                              const LinAlg::Matrix<Type> &A,
//                                                                              const LinAlg::Matrix<Type> &B,
//                                                                              const LinAlg::Matrix<Type> &C,
//                                                                              const LinAlg::Matrix<Type> &X0)
//{
//    if(this->QP)
//    {
//        LinAlg::Matrix<Type> Fdu = LinAlg::Eye<Type>(B.getNumberOfColumns());
//        LinAlg::Matrix<Type> Gdu = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(duMax - this->QP->getTolerance());
////        LinAlg::Matrix<Type> Gdu = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(duMax);
//        LinAlg::Matrix<Type> Fy  = LinAlg::Eye<Type>(C.getNumberOfRows());
//        LinAlg::Matrix<Type> Gy  = LinAlg::Ones<Type>(C.getNumberOfRows(),1)*(yMax - this->QP->getTolerance());
////        LinAlg::Matrix<Type> Gy  = LinAlg::Ones<Type>(C.getNumberOfRows(),1)*(yMax);
//        LinAlg::Matrix<Type> Fu  = LinAlg::Eye<Type>(B.getNumberOfColumns());
//        LinAlg::Matrix<Type> Gu  = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(uMax - this->QP->getTolerance());
////        LinAlg::Matrix<Type> Gu  = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(uMax);
//        LinAlg::Matrix<Type> Mtemp1;
//        for (unsigned i = 1; i <= B.getNumberOfColumns(); ++i)
//           Mtemp1 = Mtemp1 ||
//                    LinAlg::Ones<Type>(1,i) | LinAlg::Zeros<Type>(1,B.getNumberOfColumns()-i);

//        LinAlg::Matrix<Type> L   = LinAlg::Ones<Type>(B.getNumberOfColumns(),1);

//        LinAlg::Matrix<Type> Fp = Fdu || Fy*C*B || Fu*Mtemp1;
//        LinAlg::Matrix<Type> Gp = Gdu || Gy-Fy*C*A*X0 || Gu-Fu*L*uk1;

//        LinAlg::Matrix<Type> Fdun = LinAlg::Eye<Type>(B.getNumberOfColumns());
//        LinAlg::Matrix<Type> Gdun = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(duMin + this->QP->getTolerance());
////        LinAlg::Matrix<Type> Gdun = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(duMin);
//        LinAlg::Matrix<Type> Fyn  = LinAlg::Eye<Type>(C.getNumberOfRows());
//        LinAlg::Matrix<Type> Gyn  = LinAlg::Ones<Type>(C.getNumberOfRows(),1)*(yMin + this->QP->getTolerance());
////        LinAlg::Matrix<Type> Gyn  = LinAlg::Ones<Type>(C.getNumberOfRows(),1)*(yMin);
//        LinAlg::Matrix<Type> Fun  = LinAlg::Eye<Type>(B.getNumberOfColumns());
//        LinAlg::Matrix<Type> Gun  = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(uMin + this->QP->getTolerance());
////        LinAlg::Matrix<Type> Gun  = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(uMin);
//        LinAlg::Matrix<Type> Mtemp2;

//        for (unsigned i = 1; i <= B.getNumberOfColumns(); ++i)
//           Mtemp2 = Mtemp2 || LinAlg::Ones<Type>(1,i) | LinAlg::Zeros<Type>(1,B.getNumberOfColumns()-i);

//        L   = LinAlg::Ones<Type>(B.getNumberOfColumns(),1);

//        LinAlg::Matrix<Type> Fn = Fdun || Fyn*C*B || Fun*Mtemp2;
//        LinAlg::Matrix<Type> Gn = Gdun || Gyn-Fyn*C*A*X0 || Gun-Fun*L*uk1;
//        this->QP->setRestrictions(MatrixRestrictionHandler::MatrixEquality<Type>(), Fn >= Gn, Fp <= Gp);
//    }
//    else
//        std::cout << "O otimizador nao foi setado\n";
//}

template <typename Type>
void restrictedOptimizationHandler::GeneralisedRestrictedNewton<Type>::optimize()
{
//    unsigned n = 1;

//    while(true)
//    {
//        if(std::abs(this->Func) < this->tolerance || n > this->nMaxIterarion)
//            break;

    this->funcBuild();
    this->Jacobian();

    this->X = LinAlg::inv_numeric(~this->dFunc * this->dFunc) * ~this->dFunc * (this->Func + (this->dFunc * this->X));

//        n++;
//    }
}
