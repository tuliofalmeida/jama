#ifndef RECURSIVEACTIVESET_H
#define RECURSIVEACTIVESET_H
#ifdef testModel
    #include "../../../headers/restrictedOptimization/quadprog.h"
#else
    #include "SistemasdeControle/headers/restrictedOptimization/quadprog.h"
#endif

namespace restrictedOptimizationHandler{

    template <typename Type>
    class RecursiveActiveSet : public QuadProg <Type>
    {
    public:
        RecursiveActiveSet(){this->tol = 1e-3;}
        void optimize();
    private:
        Type cost;

        LinAlg::Matrix<Type> activeRestrictions(const LinAlg::Matrix<Type> &A,
                                                const LinAlg::Matrix<Type> &b,
                                                Type tol = 1e-2);

        void RKKT(LinAlg::Matrix<Type> A,
                  LinAlg::Matrix<Type> b,
                  LinAlg::Matrix<Type> &P,
                  LinAlg::Matrix<Type> &x);
    };
}

#ifdef testModel
    #include "../../../src/restrictedOptimization/recursiveactiveset.hpp"
#else
    #include "SistemasdeControle/src/restrictedOptimization/recursiveactiveset.hpp"
#endif

#endif // RECURSIVEACTIVESET_H

