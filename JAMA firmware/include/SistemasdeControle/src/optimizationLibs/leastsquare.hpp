#ifdef testModel
    #include "../../../headers/optimizationLibs/leastsquare.h"
#else
    #include "SistemasdeControle/headers/optimizationLibs/leastsquare.h"
#endif


template <class Type>
OptimizationHandler::LeastSquare<Type>::LeastSquare(ModelHandler::Model<Type> *model)
{
    this->model = model;
}

template <class Type>
void OptimizationHandler::LeastSquare<Type>::Optimize()
{
    LinAlg::Matrix<Type> A = this->model->getLinearMatrixA(),
                         B = this->model->getLinearEqualityB();
    this->model->setModelCoef((((~A)*A)^-1)*(~A)*B);
}

template <class Type>
void OptimizationHandler::LeastSquare<Type>::Optimize(LinAlg::Matrix<Type> Input,
                                     LinAlg::Matrix<Type> Output)
{
    this->model->setLinearModel(Input,Output);
    LinAlg::Matrix<Type> A = this->model->getLinearMatrixA(),
                         B = this->model->getLinearEqualityB();
//    std::cout << A;
//    std::cout << B;
//    std::cout << ((~A)*B);
    this->model->setModelCoef(LinAlg::inv_numeric(((~A)*A))*(~A)*B);
}
