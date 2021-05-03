#ifndef ACTIVESET_H
#define ACTIVESET_H
#include "SistemasdeControle/headers/restrictedOptimization/quadprog.h"

namespace restrictedOptimizationHandler{

    template <typename Type>
    class activeSet : public QuadProg <Type>
    {
    public:
        activeSet(){this->tol = 1e-2;}
        void optimize();
    private:
        Type cost;
        void initializeMethod(const LinAlg::Matrix<Type> &Ap,
                              const LinAlg::Matrix<Type> &bp,
                              const LinAlg::Matrix<Type> &An,
                              const LinAlg::Matrix<Type> &bn,
                              Type tol = 1e-2);
        void activeSetMethod(const LinAlg::Matrix<Type> &P,
                             const LinAlg::Matrix<Type> &q,
                             const LinAlg::Matrix<Type> &A0,
                             const LinAlg::Matrix<Type> &b0,
                             Type tol = 1e-2);
        LinAlg::Matrix<Type> activeRestrictions(const LinAlg::Matrix<Type> &A,
                                                const LinAlg::Matrix<Type> &b,
                                                Type tol = 1e-2);
        void KKT(LinAlg::Matrix<Type> A,
                 LinAlg::Matrix<Type> b,
                 LinAlg::Matrix<Type> &x,
                 LinAlg::Matrix<Type> &v);

        void RKKT(LinAlg::Matrix<Type> A,
                  LinAlg::Matrix<Type> b,
                  LinAlg::Matrix<Type> &P,
                  LinAlg::Matrix<Type> &x);
    };
}

#include "SistemasdeControle/src/restrictedOptimization/activeset.hpp"
#endif // ACTIVESET_H
