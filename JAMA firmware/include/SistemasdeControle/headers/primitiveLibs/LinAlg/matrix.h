#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <time.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <iostream> 
#include <typeinfo>
#include <algorithm>
#include "../primitives.h"

#include "identifiers.h"

using namespace Identifiers;

namespace LinAlg {
    #ifndef coutPrecision
        #define coutPrecision 3
    #endif
    template<typename Type>
    class Matrix
    {
        public:
            Matrix (Type Number);
            Matrix (const char* Mat);
            Matrix (std::string Mat);
            Matrix (uint32_t row, uint32_t column);
            Matrix (): rows(0), columns(0), mat(NULL){}
            Matrix (const LinAlg::Matrix<Type>& otherMatrix);
            template<typename OtherMatrixType>
            Matrix (const LinAlg::Matrix<OtherMatrixType>& otherMatrix);
            virtual ~Matrix ();

            void removeRow (uint32_t row);
            void removeColumn (uint32_t column);

            uint32_t getNumberOfRows () const;
            uint32_t getNumberOfColumns () const;

            LinAlg::Matrix<Type> getRow (const uint32_t &number_of_the_row) const;
            LinAlg::Matrix<Type> getColumn (const uint32_t &number_of_the_column) const;

            void swapRows (uint32_t row_to_be_swapped, uint32_t  row_to_take_place);
            void swapColumns (uint32_t column_to_be_swapped, uint32_t column_to_take_place);

            uint32_t length () const;
            LinAlg::Matrix<Type> size () const;

            bool isNull ();
            bool isSquare ();

            Type& operator() (uint32_t row, uint32_t column);
            Type  operator() (uint32_t  row, uint32_t column) const;

            LinAlg::Matrix<Type> operator() (uint32_t* row_uint32_terval, uint32_t column) const;
            LinAlg::Matrix<Type> operator() (uint32_t  row, uint32_t* column_uint32_terval) const;
            LinAlg::Matrix<Type> operator() (uint32_t* row_uint32_terval, uint32_t* column_uint32_terval) const;
            LinAlg::Matrix<Type> operator() (uint32_t* row_uint32_terval, LinAlg::Matrix<Type> columns) const;
            LinAlg::Matrix<Type> operator() (LinAlg::Matrix<Type> rows, uint32_t* column_uint32_terval) const;
            LinAlg::Matrix<Type> operator() (uint32_t  row, LinAlg::Matrix<Type> columns) const;
            LinAlg::Matrix<Type> operator() (LinAlg::Matrix<Type> rows, uint32_t  column) const;
            LinAlg::Matrix<Type> operator() (LinAlg::Matrix<Type> rows, LinAlg::Matrix<Type> column) const;


            void operator= (const char* rhs);
            LinAlg::Matrix<Type>& operator= (const LinAlg::Matrix<Type>& rhs) const;
            template<typename OtherMatrixType>
            LinAlg::Matrix<Type>& operator= (const LinAlg::Matrix<OtherMatrixType>& otherMatrix);
            template<typename MatrixLeftType>
            void operator= (LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* > *rhs);


            LinAlg::Matrix<Type>& operator+= (const Type& rhs /*scalar*/);
            template<typename RightType>
            LinAlg::Matrix<Type>& operator+= (const LinAlg::Matrix<RightType>& rhs);

            LinAlg::Matrix<Type>& operator-= (const Type& rhs /*scalar*/);
            template<typename RightType>
            LinAlg::Matrix<Type>& operator-= (const LinAlg::Matrix<RightType>& rhs);

            LinAlg::Matrix<Type>& operator*= (const Type& rhs /*scalar*/);
            template<typename RightType>
            LinAlg::Matrix<Type>& operator*= (const LinAlg::Matrix<RightType>& rhs);


            LinAlg::Matrix<Type>& operator/= (const Type& rhs /*scalar*/);
            template<typename RightType>
            LinAlg::Matrix<Type>& operator/= (const LinAlg::Matrix<RightType>& rhs);

            LinAlg::Matrix<Type>& operator^= (uint32_t exp);

            LinAlg::Matrix<bool> operator== (const Type& rhs /*scalar*/);
            LinAlg::Matrix<bool> operator<= (const Type& rhs /*scalar*/);
            LinAlg::Matrix<bool> operator>= (const Type& rhs /*scalar*/);
            LinAlg::Matrix<bool> operator<  (const Type& rhs /*scalar*/);
            LinAlg::Matrix<bool> operator>  (const Type& rhs /*scalar*/);

            template<typename RightType>
            LinAlg::Matrix<Type> operator| (LinAlg::Matrix<RightType> rhs);
            template<typename RightType>
            LinAlg::Matrix<Type> operator| (RightType rhs);
            template<typename RightType>
            LinAlg::Matrix<Type> operator|| (LinAlg::Matrix<RightType> rhs);
            template<typename RightType>
            LinAlg::Matrix<Type> operator|| (RightType rhs);

            void operator<< (const LinAlg::Matrix<Type>& mat);
            void operator>> (LinAlg::Matrix<Type>& mat);

            template<typename OtherMatrixType>
            void swap (const LinAlg::Matrix<OtherMatrixType>& otherMatrix);

            //Should be declared as friend.
            template<typename OtherMatrixType>
            friend void swap (LinAlg::Matrix<Type>& lhs, LinAlg::Matrix<OtherMatrixType>& rhs) {lhs.swap(rhs);}

        private:
            void Init (std::string Mat);
            void Init (uint32_t row, uint32_t column);

            void ReInit (uint32_t row, uint32_t column);

            void Add (uint32_t row, uint32_t column, Type number);

            template<typename OtherMatrixType>
            bool CheckDimensions(const LinAlg::Matrix<OtherMatrixType>& rhs, uint32_t operation);

            uint32_t rows, columns;
            Type** mat;
    };

    template<typename MatrixLeftType, typename MatrixRigthType>
    inline LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* >* operator, (LinAlg::Matrix<MatrixLeftType> &lhs, LinAlg::Matrix<MatrixRigthType> &rhs);
    template<typename MatrixLeftType, typename MatrixRigthType>
    inline LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* >* operator, (LinAlg::Matrix< LinAlg::Matrix<MatrixLeftType>* >* lhs, LinAlg::Matrix<MatrixRigthType> &rhs);

    template<typename MatrixType, typename ScalarType>
    inline LinAlg::Matrix<MatrixType> operator+ (LinAlg::Matrix<MatrixType> lhs, const ScalarType& rhs) {return lhs += rhs;}
    template<typename MatrixType, typename ScalarType>
    inline LinAlg::Matrix<MatrixType> operator+ (const ScalarType& lhs, LinAlg::Matrix<MatrixType> rhs) {return rhs += lhs;}
    template<typename LeftType, typename RightType>
    inline LinAlg::Matrix<LeftType> operator+ (LinAlg::Matrix<LeftType> lhs, const LinAlg::Matrix<RightType>& rhs) {return lhs += rhs;}

    template<typename MatrixType, typename ScalarType>
    inline LinAlg::Matrix<MatrixType> operator- (LinAlg::Matrix<MatrixType> lhs, const ScalarType& rhs) {return lhs -= rhs;}
    template<typename MatrixType, typename ScalarType>
    inline LinAlg::Matrix<MatrixType> operator- (const ScalarType& lhs, LinAlg::Matrix<MatrixType> rhs) {return -rhs -= -lhs;}
    template<typename LeftType, typename RightType>
    inline LinAlg::Matrix<LeftType> operator- (LinAlg::Matrix<LeftType> lhs, const LinAlg::Matrix<RightType>& rhs) {return lhs -= rhs;}

    template<typename MatrixType, typename ScalarType>
    inline LinAlg::Matrix<MatrixType> operator* (LinAlg::Matrix<MatrixType> lhs, const ScalarType& rhs) {return lhs *= rhs;}
    template<typename MatrixType, typename ScalarType>
    inline LinAlg::Matrix<MatrixType> operator* (const ScalarType& lhs, LinAlg::Matrix<MatrixType> rhs) {return rhs *= lhs;}
    template<typename LeftType, typename RightType>
    inline LinAlg::Matrix<LeftType> operator* (LinAlg::Matrix<LeftType> lhs, const LinAlg::Matrix<RightType>& rhs) {return lhs *= rhs;}

    template<typename MatrixType, typename ScalarType>
    inline LinAlg::Matrix<MatrixType> operator/ (LinAlg::Matrix<MatrixType> lhs, const ScalarType& rhs) {return lhs /= rhs;}
    template<typename LeftType, typename RightType>
    inline LinAlg::Matrix<LeftType> operator/ (LinAlg::Matrix<LeftType> lhs, const LinAlg::Matrix<RightType>& rhs) {return lhs /= rhs;}

    template<typename Type>
    inline LinAlg::Matrix<Type> operator- (const LinAlg::Matrix<Type>& mat);

    template<typename Type>
    inline LinAlg::Matrix<Type> operator~ (LinAlg::Matrix<Type> mat);

    template<typename Type>
    inline LinAlg::Matrix<Type> operator^ (LinAlg::Matrix<Type> lhs, uint32_t exp) {return lhs ^= exp;}

    template<typename Type>
    inline std::ostream& operator<< (std::ostream& output, const LinAlg::Matrix<Type> mat);
    template<typename Type>
    inline std::ostream& operator<<= (std::ostream& output, const LinAlg::Matrix<Type> mat);
    template<typename Type>
    inline std::istream& operator>> (std::istream& input, LinAlg::Matrix<Type>& mat);

    template<typename Type>
    inline std::string& operator<< (std::string& output, const LinAlg::Matrix<Type> mat);

    template<typename Type>
    inline std::string& operator<<= (std::string& output, const LinAlg::Matrix<Type> mat);

//    template<typename Type>
//    bool operator== (const LinAlg::Matrix<Type>& lhs, const LinAlg::Matrix<Type>& rhs);
    template<typename Type>
    inline bool operator!= (const LinAlg::Matrix<Type>& lhs, const LinAlg::Matrix<Type>& rhs) {return !(lhs == rhs);}

    template <typename Type>
    inline LinAlg::Matrix<Type> divPoint(const LinAlg::Matrix<Type> &A, const LinAlg::Matrix<Type> &B);

    template <typename Type>
    inline LinAlg::Matrix< LinAlg::Matrix<Type>* >* sort(const LinAlg::Matrix<Type> &vector);

    template <typename Type>
    inline LinAlg::Matrix< LinAlg::Matrix<Type>* >* min(const LinAlg::Matrix<Type> &vector);

    template <typename Type>
    inline LinAlg::Matrix< LinAlg::Matrix<Type>* >* max(const LinAlg::Matrix<Type> &vector);

    template <typename Type>
    inline LinAlg::Matrix<Type> sum(const LinAlg::Matrix<Type> &vector, const bool &rowCol = 0);

//    template <typename Type>
//    uint32_t lineOfMinValue(const LinAlg::Matrix<Type> &mat);

//    template <typename Type>
//    uint32_t columnOfMinValue(const LinAlg::Matrix<Type> &mat);

//    template <typename Type>
//    Type MinValue(const LinAlg::Matrix<Type> &mat);

//    template <typename Type>
//    uint32_t lineOfMaxValue(const LinAlg::Matrix<Type> &mat);

//    template <typename Type>
//    uint32_t columnOfMaxValue(const LinAlg::Matrix<Type> &mat);

//    template <typename Type>
//    Type MaxValue(const LinAlg::Matrix<Type> &mat);

//    template <typename Type>
//    LinAlg::Matrix<Type> sumOfRowsElements(const LinAlg::Matrix<Type> &mat);

//    template <typename Type>
//    LinAlg::Matrix<Type> sumOfColumnsElements(const LinAlg::Matrix<Type> &mat);

//    template<typename Type>
//    void Zeros (LinAlg::Matrix<Type>& Mat);

    template<typename Type>
    inline LinAlg::Matrix<Type> Zeros (uint32_t rows, uint32_t columns);

    template<typename Type>
    inline LinAlg::Matrix<Type> Eye (uint32_t dimension);

    template<typename Type>
    inline LinAlg::Matrix<Type> LineVector (Type from, Type to, Type step = 1);

    template<typename Type>
    inline LinAlg::Matrix<Type> Ones (uint32_t rows, uint32_t columns);

    template<typename Type>
    inline LinAlg::Matrix<Type> Random (uint32_t rows, uint32_t columns);

    template<typename Type>
    inline LinAlg::Matrix<Type> diff (const LinAlg::Matrix<Type> &mat);

    template<typename Type>
    inline Type Determinant (const LinAlg::Matrix<Type>& mat);

    template<typename Type>
    inline LinAlg::Matrix<Type> Cofactor(const LinAlg::Matrix<Type>& mat);

    template<typename Type>
    inline LinAlg::Matrix<Type> Inverse(const LinAlg::Matrix<Type>& mat);

    template<typename Type>
    inline void Print (const LinAlg::Matrix<Type>& mat);

    template<typename Type>
    inline bool isEqual(const LinAlg::Matrix<Type>& lMat, const LinAlg::Matrix<Type>& rMat);
    template<typename Type, typename otherType>
    inline bool isEqual(const LinAlg::Matrix<Type>& lMat, const LinAlg::Matrix<otherType>& rMat, Type tol = 1e-30);
}

    #ifdef testMatrix
        #include "../../../../src/primitiveLibs/LinAlg/matrix.hpp"
    #else
        #ifdef testPolynom
            #include "../../../src/primitiveLibs/LinAlg/matrix.hpp"
        #else
            #include "SistemasdeControle/src/primitiveLibs/LinAlg/matrix.hpp"
        #endif
    #endif

#endif // MATRIX_H
