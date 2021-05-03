#ifdef testModel
    #include "../../../headers/restrictedOptimization/linprog.h"
#else
    #include "SistemasdeControle/headers/restrictedOptimization/linprog.h"
#endif

template<typename Type>
restrictedOptimizationHandler::linProg<Type>::linProg()
{

}

template<typename Type>
void restrictedOptimizationHandler::linProg<Type>::operator=
                                (const MatrixRestrictionHandler::MatrixEquality<Type> &E)
{
    this->E.A = E.A;
    this->E.b = E.b;
}

template<typename Type>
void restrictedOptimizationHandler::linProg<Type>::operator=
                                (const MatrixRestrictionHandler::MatrixNegativeInequality<Type> &N)
{
    this->N.A = N.A;
    this->N.b = N.b;
}

template<typename Type>
void restrictedOptimizationHandler::linProg<Type>::operator=
                                (const MatrixRestrictionHandler::MatrixPositiveInequality<Type> &P)
{
    this->P.A = P.A;
    this->P.b = P.b;
}

template<typename Type>
void restrictedOptimizationHandler::linProg<Type>::setRestrictions(
                       const MatrixRestrictionHandler::MatrixEquality<Type> &E,
                       const MatrixRestrictionHandler::MatrixNegativeInequality<Type> &N,
                       const MatrixRestrictionHandler::MatrixPositiveInequality<Type> &P)
{
    this->E.A = E.A;
    this->E.b = E.b;
    this->N.A = N.A;
    this->N.b = N.b;
    this->P.A = P.A;
    this->P.b = P.b;
}


template<typename Type>
std::ostream& restrictedOptimizationHandler::operator<< (std::ostream& output,
                                                         const restrictedOptimizationHandler::linProg<Type> LP)
{
    output << "Matrix Equality (A = b): \n";
    output << "A = \n";
    output << LP.getMatrixEquality().A;
    output << "b = \n";
    output << LP.getMatrixEquality().b;

    output << "\nMatrix Positive Inequality (A < b): \n";
    output << "A = \n";
    output << LP.getMatrixPositiveInequality().A;
    output << "b = \n";
    output << LP.getMatrixPositiveInequality().b;

    output << "\nMatrix Negative Inequality (A > b): \n";
    output << "A = \n";
    output << LP.getMatrixNegativeInequality().A;
    output << "b = \n";
    output << LP.getMatrixNegativeInequality().b;

    return output;
}


