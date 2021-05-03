#ifndef LEASTSQUARE_H
#define LEASTSQUARE_H

#include "optimization.h"


namespace OptimizationHandler{

    template <class Type>
    class LeastSquare: public Optimization<Type>
    {
    public:
        LeastSquare(ModelHandler::Model<Type> *model);

        void Optimize();
        void Optimize(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);
    };
}

#ifdef testModel
    #include "../../../src/optimizationLibs/leastsquare.hpp"
#else
    #include "SistemasdeControle/src/optimizationLibs/leastsquare.hpp"
#endif

#endif // LEASTSQUARE_H
