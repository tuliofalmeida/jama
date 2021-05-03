#ifndef LEASTSQUARE_H
#define LEASTSQUARE_H
#include "SistemasdeControle/headers/optimizationLibs/optimization.h"

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

#include "SistemasdeControle/src/optimizationLibs/leastsquare.hpp"
#endif // LEASTSQUARE_H
