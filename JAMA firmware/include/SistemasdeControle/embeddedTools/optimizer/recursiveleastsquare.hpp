
#include "recursiveLeastSquare.h"


template <class Type>
OptimizationHandler::RecursiveLeastSquare<Type>::RecursiveLeastSquare(ModelHandler::Model<Type> *model,
                                                     Type p0,
                                                     Type lambda)
{
    this->initialization(model,p0,lambda);
}

template <class Type>
void OptimizationHandler::RecursiveLeastSquare<Type>::initialization(ModelHandler::Model<Type> *model,
                                                     Type p0,
                                                     Type lambda)
{
    srand(time(NULL));
    this->p0     = p0;
    this->model  = model;
    this->lambda = lambda;    
    this->firstTimeFlag = false;
    this->model->setModelCoef(LinAlg::Ones<Type>(this->model->getNumberOfVariables(), this->model->getNumberOfOutputs())/this->p0);
    this->P = LinAlg::Eye<Type>(this->model->getNumberOfVariables())*(this->p0);

    this->Input  = LinAlg::Zeros<Type>(this->model->getNumberOfInputs(), 2);
    this->Output = LinAlg::Zeros<Type>(this->model->getNumberOfOutputs(), 2);
}

template <class Type>
void OptimizationHandler::RecursiveLeastSquare<Type>::optimize(LinAlg::Matrix<Type> input, LinAlg::Matrix<Type> output)
{
    input  >> this->Input;
    output >> this->Output;

    this->model->setLinearVector(this->Input.getColumn(0),
                                 this->Output.getColumn(1));


    LinAlg::Matrix<Type> phi = this->model->getLinearVectorA();
    this->E = this->Output.getColumn(0) - ~(phi*this->model->getModelCoef());
    this->K = (this->P*~phi)/(((phi*this->P)*~phi)(0,0) + this->lambda); // para o caso matricial teria que ser do tipo matriz?
    LinAlg::Matrix<Type> KxE;
    for(unsigned i = 0; i < this->model->getNumberOfOutputs(); ++i)
        KxE = KxE | this->K*this->E(i,0);
    this->model->setModelCoef(this->model->getModelCoef() + KxE);
    this->P = (this->P - (this->K*(phi*this->P)))/this->lambda;
}
