#ifndef LINALG_H
#define LINALG_H

#define SWAP

#include "matrix.h"
#include <complex>//numeros complexos
#include <cfloat>
#include <cmath>

namespace LinAlg {
    template <typename  Type>
    inline void balance (LinAlg::Matrix<Type>& matrix_to_balance);

    template<typename Type>
    inline Type trace (const LinAlg::Matrix<Type>& mat);

    template<typename Type>
    inline LinAlg::Matrix<Type> characteristicPolynom (const LinAlg::Matrix<Type>& mat);

    template<typename Type>
    inline LinAlg::Matrix<Type> inv_numeric(LinAlg::Matrix<Type> mat);

    template<typename Type>
    inline LinAlg::Matrix< LinAlg::Matrix<Type>* >* QR_Factorization_ModifiedGramSchmidt (LinAlg::Matrix<Type> input_matrix);

    template<typename Type>
    inline LinAlg::Matrix< LinAlg::Matrix<Type>* >* QR_Factorization (const LinAlg::Matrix<Type>& input_matrix);

    template<typename Type>
    inline LinAlg::Matrix< LinAlg::Matrix<Type>* >* QR (const LinAlg::Matrix<Type>& input_matrix);

    template <typename Type>
    inline LinAlg::Matrix< LinAlg::Matrix<Type>* >* LU_Factorization(LinAlg::Matrix<Type> input_matrix);

    template<typename Type>
    inline LinAlg::Matrix<Type> Hessemberg_Form (const LinAlg::Matrix<Type>& matrix_to_reduce);

    template<typename Type>
    inline LinAlg::Matrix<Type> Hess (const LinAlg::Matrix<Type>& matrix_to_reduce);

    template <typename Type>
    inline LinAlg::Matrix<Type> eigenValues(const LinAlg::Matrix<Type>& matrix_to_get_eigens, uint32_t iterations = 100, Type tolerance = 1e-5);

    template <typename Type>
    inline LinAlg::Matrix<Type> eigenVectors(const LinAlg::Matrix<Type>& matrix_to_get_eigens, uint32_t iterations = 100);

    template <typename Type>
    inline LinAlg::Matrix<Type> eigenValues_LU(const LinAlg::Matrix<Type>& matrix_to_get_eigenvalues, uint32_t iterations = 40);

    template <typename Type>
    inline Type *MultPoly(const Type *lhs, const Type  *rhs, const uint32_t &lhsSize, const uint32_t &rhsSize);

    template <typename Type>
    inline LinAlg::Matrix<Type> abs(const LinAlg::Matrix<Type> &mat);

    template <typename Type>
    inline LinAlg::Matrix<Type> sqrtMatrix(const LinAlg::Matrix<Type> &mat);

    template <typename Type>
    inline LinAlg::Matrix<Type> powMatrix(const LinAlg::Matrix<Type> &mat, Type potence);

    template <typename Type>
    inline LinAlg::Matrix<Type> expM(const LinAlg::Matrix<Type> &mat, const Type &sampleTime = 1, const uint32_t &precision = 10);

    template <typename Type>
    inline LinAlg::Matrix<Type> logM(const LinAlg::Matrix<Type> &mat, const Type &sampleTime = 1, const uint32_t &precision = 40);

    template <typename Type>
    inline LinAlg::Matrix<Type> mean(const LinAlg::Matrix<Type> &mat, const uint32_t &rowColumn = 1);
}

#ifdef testMatrix
    #include "../../../../src/primitiveLibs/LinAlg/linalg.hpp"
#else
    #ifdef testPolynom
        #include "../../../src/primitiveLibs/LinAlg/linalg.hpp"
    #else
        #include "SistemasdeControle/src/primitiveLibs/LinAlg/linalg.hpp"
    #endif
#endif

#endif // LINALG_H




