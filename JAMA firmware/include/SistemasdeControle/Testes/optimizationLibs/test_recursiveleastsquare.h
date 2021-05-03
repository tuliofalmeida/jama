#ifndef RECURSIVELEASTSQUARE_H
#define RECURSIVELEASTSQUARE_H
#include "SistemasdeControle/headers/optimizationLibs/optimization.h"

namespace OptimizationHandler {
    template <class Type>
    class RecursiveLeastSquare: public Optimization<Type>
    {
    public:
        RecursiveLeastSquare(ModelHandler::Model<Type> *model,
                             Type p0 = 1e5,
                             Type lambda = 1);

        void Iteration();
        void Optimize();
        void Optimize(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);

    private:
        bool firstTimeFlag;
        Type p0, lambda;
        LinAlg::Matrix<Type> P, K, E, Input, Output;
    };
}

#include "SistemasdeControle/src/optimizationLibs/recursiveleastsquare.hpp"
#endif // RECURSIVELEASTSQUARE_H
