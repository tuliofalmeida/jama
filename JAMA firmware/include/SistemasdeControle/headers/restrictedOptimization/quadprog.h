#ifndef QUADPROG_H
#define QUADPROG_H

#ifdef testModel
    #include "../../../headers/primitiveLibs/LinAlg/matrixrestriction.h"
    #include "../../../headers/restrictedOptimization/simplex.h"
#else
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrixrestriction.h"
    #include "SistemasdeControle/headers/restrictedOptimization/simplex.h"
#endif

namespace restrictedOptimizationHandler{

    template <typename Type>
    class QuadProg
    {
    public:
        QuadProg();
        virtual void optimize() = 0;
        void operator= (const MatrixRestrictionHandler::MatrixEquality<Type> &E);
        void operator= (const MatrixRestrictionHandler::MatrixNegativeInequality<Type> &E);
        void operator= (const MatrixRestrictionHandler::MatrixPositiveInequality<Type> &E);

        void setRestrictions(const MatrixRestrictionHandler::MatrixEquality<Type> &E,
                             const MatrixRestrictionHandler::MatrixNegativeInequality<Type> &N,
                             const MatrixRestrictionHandler::MatrixPositiveInequality<Type> &P){this->E = E; this->N = N; this->P=P;}
        void setfunction2Optimize(const LinAlg::Matrix<Type> &QuadMat,
                                  const LinAlg::Matrix<Type> &LinMat){this->QuadMat = QuadMat; this->LinMat = LinMat;}

        void getRestrictions(LinAlg::Matrix<Type> &A, LinAlg::Matrix<Type> &b){ A = this->A; b = this->b;}

        LinAlg::Matrix<Type> getSet() const {return this->set;}
        LinAlg::Matrix<Type> getOptimizatedValue() const {return this->x;}

        Type getTolerance() const {return this->tol;}

        MatrixRestrictionHandler::MatrixEquality<Type> getMatrixEquality()const {return E;}
        MatrixRestrictionHandler::MatrixNegativeInequality<Type> getMatrixNegativeInequality()const {return N;}
        MatrixRestrictionHandler::MatrixPositiveInequality<Type> getMatrixPositiveInequality()const {return P;}

    protected:
        MatrixRestrictionHandler::MatrixEquality<Type> E;
        MatrixRestrictionHandler::MatrixNegativeInequality<Type> N;
        MatrixRestrictionHandler::MatrixPositiveInequality<Type> P;
        LinAlg::Matrix<Type> QuadMat, LinMat, x, set;
        Type tol;
    };
}

#ifdef testModel
    #include "../../../src/restrictedOptimization/quadprog.hpp"
#else
    #include "SistemasdeControle/src/restrictedOptimization/quadprog.hpp"
#endif

#endif // QUADPROG_H
