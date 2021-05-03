#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <deque>

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
            Matrix (unsigned row, unsigned column);
            Matrix (){}
            Matrix (const LinAlg::Matrix<Type>& otherMatrix);
            template<typename OtherMatrixType>
            Matrix (const LinAlg::Matrix<OtherMatrixType>& otherMatrix);
            virtual ~Matrix ();

            void removeRow (unsigned row);
            void removeColumn (unsigned column);

            unsigned getNumberOfRows () const;
            unsigned getNumberOfColumns () const;

            LinAlg::Matrix<Type> getRow (const unsigned &number_of_the_row) const;
            LinAlg::Matrix<Type> getColumn (const unsigned &number_of_the_column) const;

            unsigned length () const;
            LinAlg::Matrix<Type> size () const;

            bool isNull ();
            bool isSquare ();

            Type& operator() (unsigned row, unsigned column);
            Type  operator() (unsigned  row, unsigned column) const;

            void operator= (const char* rhs);
            LinAlg::Matrix<Type>& operator= (const LinAlg::Matrix<Type>& rhs) const;
            template<typename OtherMatrixType>
            LinAlg::Matrix<Type>& operator= (const LinAlg::Matrix<OtherMatrixType>& otherMatrix);

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
            LinAlg::Matrix<Type> operator| (LinAlg::Matrix<RightType> rhs);
            template<typename RightType>
            LinAlg::Matrix<Type> operator| (RightType rhs);
            template<typename RightType>
            LinAlg::Matrix<Type> operator|| (LinAlg::Matrix<RightType> rhs);
            template<typename RightType>
            LinAlg::Matrix<Type> operator|| (RightType rhs);

            void operator<< (const LinAlg::Matrix<Type>& mat);
            void operator>> (LinAlg::Matrix<Type>& mat);

        private:
            void Init (std::string Mat);
            void Init (unsigned row, unsigned column);

            template<typename OtherMatrixType>
            bool CheckDimensions(const LinAlg::Matrix<OtherMatrixType>& rhs, unsigned operation);

//            unsigned rows, columns;
            std::deque<std::deque<Type>> mat;
    };

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
    inline LinAlg::Matrix<Type> operator^ (LinAlg::Matrix<Type> lhs, int exp) {return lhs ^= exp;}

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

    template<typename Type>
    inline LinAlg::Matrix<Type> Zeros (unsigned rows, unsigned columns);

    template<typename Type>
    LinAlg::Matrix<Type> Eye (unsigned dimension);

    template<typename Type>
    inline LinAlg::Matrix<Type> LineVector (Type from, Type to, Type step);

    template<typename Type>
    LinAlg::Matrix<Type> Ones(unsigned rows, unsigned columns);

    template<typename Type,typename otherType>
    bool isEqual(const LinAlg::Matrix<Type> &mat1, const LinAlg::Matrix<otherType> &mat2, const Type &tolerance = 0.0);

    template<typename Type>
    LinAlg::Matrix<Type> linSolve(LinAlg::Matrix<Type> A);
}

#include "matrix.hpp"
#endif // MATRIX_H