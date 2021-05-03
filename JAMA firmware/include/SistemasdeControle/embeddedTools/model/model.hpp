
#include "model.h"


template <typename Type>
void ModelHandler::Model<Type>::setTimeSimulation(const Type &timeSimulation)
{
    this->timeSimulation = timeSimulation;
}

template <typename Type>
Type ModelHandler::Model<Type>::getTimeSimulation() const
{
    return this->timeSimulation;
}

template <typename Type>
void ModelHandler::Model<Type>::setSampleTime(const Type &sampleTime)
{
    this->sampleTime = sampleTime;
}

template <typename Type>
void ModelHandler::Model<Type>::setModelCoef(LinAlg::Matrix<Type> coef)
{
    this->ModelCoef = coef;
}

template <typename Type>
void ModelHandler::Model<Type>::setIO(LinAlg::Matrix<Type> in, LinAlg::Matrix<Type> out)
{
    this->Input = in;
    this->Output = out;
}

template <typename Type>
Type ModelHandler::Model<Type>::getSampleTime() const
{
    return this->sampleTime;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getModelCoef() const
{
    return this->ModelCoef;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getInputMatrix() const
{
    return this->Input;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getOutputMatrix() const
{
    return this->Output;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getLinearVectorA() const
{
    return this->LinearVectorA;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getLinearEqualityVectorB() const
{
    return this->LinearVectorB;
}

template<typename Type> // ok
std::ostream& ModelHandler::operator<< (std::ostream& output, ModelHandler::Model<Type> model)
{
    output << model.print();
    return output;
}

template<typename Type> //ok
std::string&  ModelHandler::operator<< (std::string& output,  ModelHandler::Model<Type> model)
{
    output += model.print();
    return output;
}
