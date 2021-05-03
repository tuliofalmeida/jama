#ifndef SIMPLEX_H
#define SIMPLEX_H

#ifdef testModel
    #include "../../../headers/restrictedOptimization/linprog.h"
    #include "../../../headers/primitiveLibs/LinAlg/linalg.h"
#else
    #include "SistemasdeControle/headers/restrictedOptimization/linprog.h"
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
#endif


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

#ifdef testModel
    #include "../../../src/restrictedOptimization/simplex.hpp"
#else
    #include "SistemasdeControle/src/restrictedOptimization/simplex.hpp"
#endif

#endif // SIMPLEX_H
