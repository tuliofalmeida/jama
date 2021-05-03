#ifndef LINPROG_H
#define LINPROG_H
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrixrestriction.h"

namespace restrictedOptimizationHandler{

    template <typename Type>
    class linProg
    {
    public:
        linProg();
        linProg(const MatrixRestrictionHandler::MatrixEquality<Type> &E);
        linProg(const MatrixRestrictionHandler::MatrixNegativeInequality<Type> &N);
        linProg(const MatrixRestrictionHandler::MatrixPositiveInequality<Type> &P);

        virtual void optimize() = 0;
        void operator= (const MatrixRestrictionHandler::MatrixEquality<Type> &E);
        void operator= (const MatrixRestrictionHandler::MatrixNegativeInequality<Type> &N);
        void operator= (const MatrixRestrictionHandler::MatrixPositiveInequality<Type> &P);

        void setRestrictions(const MatrixRestrictionHandler::MatrixEquality<Type> &E,
                             const MatrixRestrictionHandler::MatrixNegativeInequality<Type> &N,
                             const MatrixRestrictionHandler::MatrixPositiveInequality<Type> &P);
        void setfunction2Optimize(const LinAlg::Matrix<Type> &function2Optimize){this->function2Optimize = function2Optimize;}

        void getRestrictions(LinAlg::Matrix<Type> &A, LinAlg::Matrix<Type> &b){ A = this->A; b = this->b;}

        LinAlg::Matrix<Type> getSet() const {return this->set;}
        LinAlg::Matrix<Type> getOptimizatedValue() const {return this->x;}

        MatrixRestrictionHandler::MatrixEquality<Type> getMatrixEquality()const {return E;}
        MatrixRestrictionHandler::MatrixNegativeInequality<Type> getMatrixNegativeInequality()const {return N;}
        MatrixRestrictionHandler::MatrixPositiveInequality<Type> getMatrixPositiveInequality()const {return P;}

    protected:
        MatrixRestrictionHandler::MatrixEquality<Type> E;
        MatrixRestrictionHandler::MatrixNegativeInequality<Type> N;
        MatrixRestrictionHandler::MatrixPositiveInequality<Type> P;
        LinAlg::Matrix<Type> A, b, x, set, function2Optimize;
    };
    template<typename Type>
    std::ostream& operator<< (std::ostream& output, const restrictedOptimizationHandler::linProg<Type> LP);
}

#include "SistemasdeControle/src/restrictedOptimization/linprog.hpp"
#endif // LINPROG_H
