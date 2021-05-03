#ifndef RECURSIVELEASTSQUARE_H
#define RECURSIVELEASTSQUARE_H
#include "optimization.h"

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

#ifdef testModel
    #include "../../../src/optimizationLibs/recursiveleastsquare.hpp"
#else
    #include "SistemasdeControle/src/optimizationLibs/recursiveleastsquare.hpp"
#endif

#endif // RECURSIVELEASTSQUARE_H
