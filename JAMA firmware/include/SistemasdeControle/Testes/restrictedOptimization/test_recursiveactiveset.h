#ifndef RECURSIVEACTIVESET_H
#define RECURSIVEACTIVESET_H
#include "SistemasdeControle/headers/restrictedOptimization/quadprog.h"

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

#include "SistemasdeControle/src/restrictedOptimization/recursiveactiveset.hpp"
#endif // RECURSIVEACTIVESET_H

