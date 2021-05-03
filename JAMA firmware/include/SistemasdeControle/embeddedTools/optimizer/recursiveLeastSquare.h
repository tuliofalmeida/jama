#ifndef RECURSIVELEASTSQUARE_H
#define RECURSIVELEASTSQUARE_H

#include "optmizer.h"


namespace OptimizationHandler {
    template <class Type>
    class RecursiveLeastSquare: public Optmizer<Type>
    {
    public:
        RecursiveLeastSquare(){}
        RecursiveLeastSquare(ModelHandler::Model<Type> *model,
                             Type p0 = 1e5,
                             Type lambda = 1);
        void initialization(ModelHandler::Model<Type> *model,
                             Type p0 = 1e5,
                             Type lambda = 1);
        void optimize(LinAlg::Matrix<Type> input, LinAlg::Matrix<Type> output);
        std::string print(){std::string str = "O modelo otimizado eh: \n"; str += this->model->print(); return str;}

    private:
        bool firstTimeFlag;
        Type p0, lambda;
        LinAlg::Matrix<Type> P, K, E, Input, Output;
    };
}

#include "recursiveleastsquare.hpp"


#endif // RECURSIVELEASTSQUARE_H
