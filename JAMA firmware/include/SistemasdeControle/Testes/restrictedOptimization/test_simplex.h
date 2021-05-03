#ifndef SIMPLEX_H
#define SIMPLEX_H
#include "SistemasdeControle/headers/restrictedOptimization/linprog.h"
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"

namespace restrictedOptimizationHandler{

    template <typename Type>
    class simplex : public linProg<Type>
    {
    public:
        simplex(){}
        void optimize();
    private:
        Type cost;
        void simplexOptimization(const LinAlg::Matrix<Type> &c,
                                 const LinAlg::Matrix<Type> &A,
                                 const LinAlg::Matrix<Type> &b,
                                 LinAlg::Matrix<Type> &B,
                                 LinAlg::Matrix<Type> &N);
        LinAlg::Matrix<Type> EscalSimplex(LinAlg::Matrix<Type> A, unsigned index);
    };
}

#include "SistemasdeControle/src/restrictedOptimization/simplex.hpp"
#endif // SIMPLEX_H
