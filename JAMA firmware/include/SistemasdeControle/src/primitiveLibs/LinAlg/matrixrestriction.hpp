#ifdef testModel
    #include "../../../headers/primitiveLibs/LinAlg/matrixrestriction.h"
#else
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrixrestriction.h"
#endif


template <typename Type>
MatrixRestrictionHandler::MatrixPositiveInequality<Type> operator<
                                                        (LinAlg::Matrix<Type> A,
                                                         LinAlg::Matrix<Type> b)
{
    MatrixRestrictionHandler::MatrixPositiveInequality<Type> ret;
    ret.A = A;
    ret.b = b;
    return ret;
}

template <typename Type>
MatrixRestrictionHandler::MatrixPositiveInequality<Type> operator<=
                                                        (LinAlg::Matrix<Type> A,
                                                         LinAlg::Matrix<Type> b)
{
    MatrixRestrictionHandler::MatrixPositiveInequality<Type> ret;
    ret.A = A;
    ret.b = b;
    return ret;
}

template <typename Type>
MatrixRestrictionHandler::MatrixNegativeInequality<Type> operator>
                                                        (LinAlg::Matrix<Type> A,
                                                         LinAlg::Matrix<Type> b)
{
    MatrixRestrictionHandler::MatrixNegativeInequality<Type> ret;
    ret.A = A;
    ret.b = b;
    return ret;
}

template <typename Type>
MatrixRestrictionHandler::MatrixNegativeInequality<Type> operator>=
                                                        (LinAlg::Matrix<Type> A,
                                                         LinAlg::Matrix<Type> b)
{
    MatrixRestrictionHandler::MatrixNegativeInequality<Type> ret;
    ret.A = A;
    ret.b = b;
    return ret;
}

template <typename Type>
MatrixRestrictionHandler::MatrixEquality<Type> operator==
                                                        (LinAlg::Matrix<Type> A,
                                                         LinAlg::Matrix<Type> b)
{
    MatrixRestrictionHandler::MatrixEquality<Type> ret;
    ret.A = A;
    ret.b = b;
    return ret;
}
