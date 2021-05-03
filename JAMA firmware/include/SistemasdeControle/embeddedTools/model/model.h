#ifndef MODEL_H
#define MODEL_H

#include "LinAlg/matrix.h"


//A ideia eh implementar apenas algoritmos recursivos de modelagem e otimizacao

namespace ModelHandler {
    template <typename Type>
    class Model
    {
    public:
        Model(){}
        ~Model(){}
        void setSampleTime(const Type &sampleTime);
        void setModelCoef(LinAlg::Matrix<Type> coef);
        void setTimeSimulation(const Type &timeSimulation);
        void setIO(LinAlg::Matrix<Type> in, LinAlg::Matrix<Type> out);
        Type getSampleTime() const;
        Type getTimeSimulation() const;

        LinAlg::Matrix<Type> getModelCoef() const;
        LinAlg::Matrix<Type> getInputMatrix() const;
        LinAlg::Matrix<Type> getOutputMatrix() const;

        LinAlg::Matrix<Type> getLinearVectorA() const;
        LinAlg::Matrix<Type> getLinearEqualityVectorB() const;

        virtual std::string print() = 0;
        virtual unsigned getNumberOfInputs()  const = 0;
        virtual unsigned getNumberOfOutputs() const = 0;
        virtual unsigned getNumberOfVariables() const = 0;
        virtual LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x) = 0;
        virtual void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output) = 0;

    protected:
        Type                 sampleTime, timeSimulation;
        LinAlg::Matrix<Type> Input,    Output,       ModelCoef,
                             LinearVectorA,   LinearVectorB;
    };
    template<typename Type> // ok
    std::ostream& operator<< (std::ostream& output, ModelHandler::Model<Type> model);
    template<typename Type> //ok
    std::string&  operator<< (std::string& output,  ModelHandler::Model<Type> model);
}

#include "model.hpp"

#endif // MODEL_H
