#ifndef MATRIXRESTRICTION_H
#define MATRIXRESTRICTION_H
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"

namespace MatrixRestrictionHandler {

    template <typename Type>
    struct MatrixPositiveInequality{ // A <= b
        LinAlg::Matrix<Type> A,b;
    };

    template <typename Type>
        struct MatrixNegativeInequality{ // A <= b
        LinAlg::Matrix<Type> A,b;
    };

    template <typename Type>
    struct MatrixEquality{ // A <= b
        LinAlg::Matrix<Type> A,b;
    };

    template <typename Type>
    struct ConicForm{ // A <= b
        LinAlg::Matrix<Type> A,b;
    };

}

template <typename Type>
MatrixRestrictionHandler::MatrixPositiveInequality<Type> operator< (LinAlg::Matrix<Type> A,
                                                                    LinAlg::Matrix<Type> b);
template <typename Type>
MatrixRestrictionHandler::MatrixPositiveInequality<Type> operator<= (LinAlg::Matrix<Type> A,                                                                     LinAlg::Matrix<Type> b);

template <typename Type>
MatrixRestrictionHandler::MatrixNegativeInequality<Type> operator> (LinAlg::Matrix<Type> A,
                                                                    LinAlg::Matrix<Type> b);
template <typename Type>
MatrixRestrictionHandler::MatrixNegativeInequality<Type> operator>= (LinAlg::Matrix<Type> A,
                                                                     LinAlg::Matrix<Type> b);
template <typename Type>
MatrixRestrictionHandler::MatrixEquality<Type> operator== (LinAlg::Matrix<Type> A,
                                                           LinAlg::Matrix<Type> b);
#include "SistemasdeControle/src/primitiveLibs/LinAlg/matrixrestriction.hpp"
#endif // MATRIXRESTRICTION_H
