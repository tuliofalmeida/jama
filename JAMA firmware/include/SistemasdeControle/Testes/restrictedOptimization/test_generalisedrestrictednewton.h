#ifndef GENERALISEDRESTRICTEDNEWTON_H
#define GENERALISEDRESTRICTEDNEWTON_H

#include "SistemasdeControle/headers/modelLibs/model.h"
#include "SistemasdeControle/headers/restrictedOptimization/quadprog.h"

namespace restrictedOptimizationHandler{

    template <typename Type>
    class GeneralisedRestrictedNewton
    {
        ModelHandler::Model<Type> *model;
        LinAlg::Matrix<Type> Func, dFunc, X, P;

//        restrictedOptimizationHandler::QuadProg<Type> QP;

        void Jacobian();
        void funcBuild();

//        void setOptimizationConstraints(Type duMax, Type duMin, Type yMax,
//                                  Type yMin, Type uMax, Type uMin,
//                                  const LinAlg::Matrix<Type> &uk1,
//                                  const LinAlg::Matrix<Type> &A,
//                                  const LinAlg::Matrix<Type> &B,
//                                  const LinAlg::Matrix<Type> &C,
//                                  const LinAlg::Matrix<Type> &X0);

    public:
        GeneralisedRestrictedNewton(ModelHandler::Model<Type> *model);

        void optimize();
    };
}
#include "SistemasdeControle/src/restrictedOptimization/generalisedrestrictednewton.hpp"
#endif // GENERALISEDRESTRICTEDNEWTON_H
