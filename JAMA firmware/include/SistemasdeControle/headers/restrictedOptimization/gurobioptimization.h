#ifndef GUROBIOPTIMIZATION_H
#define GUROBIOPTIMIZATION_H
#ifdef testPolynom
    #include "../../../headers/primitiveLibs/LinAlg/matrix.h"
    #include "../../../headers/primitiveLibs/LinAlg/linalg.h"
    #include "../../../headers/primitiveLibs/polynom.h"
#else
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
    #include "SistemasdeControle/headers/primitiveLibs/polynom.h"
#endif

#include "gurobi_c++.h"

namespace OptimizationHandler
{
    template <typename Type>
    LinAlg::Matrix<Type> linprog(LinAlg::Matrix<Type> obj, LinAlg::Matrix<Type> A, LinAlg::Matrix<Type> b, LinAlg::Matrix<Type> Aeq, LinAlg::Matrix<Type> beq, bool maximization = 0);

    template <typename Type>
    LinAlg::Matrix<Type> linprog(LinAlg::Matrix<Type> obj, LinAlg::Matrix<Type> A, LinAlg::Matrix<Type> b, bool maximization = 0);

    template <typename Type>
    LinAlg::Matrix<Type> linprog(LinAlg::Matrix<Type> obj, LinAlg::Matrix<Type> A, LinAlg::Matrix<Type> b, LinAlg::Matrix<Type> Aeq, LinAlg::Matrix<Type> beq, LinAlg::Matrix<Type> Anineq, LinAlg::Matrix<Type> bnineq, bool maximization = 0);
}

#ifdef testMatrix
    #include "../../../../src/restrictedOptimization/gurobioptimization.hpp"
#else
    #ifdef testPolynom
        #include "../../../src/restrictedOptimization/gurobioptimization.hpp"
    #else
        #include "SistemasdeControle/src/restrictedOptimization/gurobioptimization.hpp"
    #endif
#endif
#endif // GUROBIOPTIMIZATION_H
