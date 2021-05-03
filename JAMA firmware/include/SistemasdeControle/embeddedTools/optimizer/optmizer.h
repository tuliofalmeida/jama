#ifndef OPTMIZER_H
#define OPTMIZER_H

#include "model.h"

namespace OptimizationHandler {
    template <typename Type>
    class Optmizer
    {
    public:
        Optmizer(){}

        void   setmodel(ModelHandler::Model<Type> *model){this->model = model;}
        void   setConstraints(LinAlg::Matrix<Type> constraints) {this->constraints = constraints;}

        ModelHandler::Model<Type> *getmodel()    {return this->model;}
        LinAlg::Matrix<Type> getConstraints()    {return this->constraints;}
        LinAlg::Matrix<Type> getOptimizedValue() {return this->optimizedValue;}

        virtual std::string print() = 0;
        virtual void   optimize(LinAlg::Matrix<Type> input, LinAlg::Matrix<Type> output) = 0;
    protected:
        LinAlg::Matrix<Type> optimizedValue, constraints;
        ModelHandler::Model<Type> *model;
    };
}

#endif // OPTMIZER_H
