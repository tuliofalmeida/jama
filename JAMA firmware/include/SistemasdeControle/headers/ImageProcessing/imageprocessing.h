#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include "QColor"
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"

namespace LinAlg{

    template <typename Type, typename OtherType>
    LinAlg::Matrix<Type> sumPointToPoint(const LinAlg::Matrix<Type> &left, const LinAlg::Matrix<OtherType> &right)
    {
        LinAlg::Matrix<Type> ret = LinAlg::Zeros<Type>(left.getNumberOfRows(),left.getNumberOfColumns());

        for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i){
            for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j){
                ret(i,j) = left(i,j)+right(i,j);
            }
        }
        return ret;
    }
    template <typename Type, typename OtherType>
    LinAlg::Matrix<Type> subPointToPoint(const LinAlg::Matrix<Type> &left, const LinAlg::Matrix<OtherType> &right)
    {
        LinAlg::Matrix<Type> ret = LinAlg::Zeros<Type>(left.getNumberOfRows(),left.getNumberOfColumns());

        for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i){
            for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j){
                ret(i,j) = left(i,j)-right(i,j);
            }
        }
        return ret;
    }
    template <typename Type, typename OtherType>
    LinAlg::Matrix<Type> multPointToPoint(const LinAlg::Matrix<Type> &left, const LinAlg::Matrix<OtherType> &right)
    {
        LinAlg::Matrix<Type> ret = LinAlg::Zeros<Type>(left.getNumberOfRows(),left.getNumberOfColumns());

        for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i){
            for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j){
                ret(i,j) = left(i,j)*right(i,j);
            }
        }
        return ret;
    }

    template <typename Type>
    LinAlg::Matrix<bool> complement(const LinAlg::Matrix<bool> &rhs)
    {
        LinAlg::Matrix<bool> ret = rhs;
        for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i)
            for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j)
                ret(i,j) = !rhs(i,j);

        return ret;
    }

    template <typename Type>
    bool isEqual(const LinAlg::Matrix<bool> &rhs, const LinAlg::Matrix<bool> &lhs){
        bool isequal = true;

        for(unsigned i = 1; i <= rhs.getNumberOfRows(); ++i)
            for(unsigned j = 1; j <= rhs.getNumberOfColumns(); ++j)
                if(rhs(i,j) !=  lhs(i,j)){
                    isequal = false;
                    break;
                }

        return isequal;
    }
}

namespace ImageProcessing
{
    template <typename Type>
    LinAlg::Matrix<Type> checkValue(const LinAlg::Matrix<Type> &mat);
    template <typename Type>
    LinAlg::Matrix<Type> GetColorPixel(const LinAlg::Matrix<Type> &r,
                                    const LinAlg::Matrix<Type> &g,
                                    const LinAlg::Matrix<Type> &b); //not ok
    template <typename Type>
    LinAlg::Matrix<Type> Histogram(const LinAlg::Matrix<Type> &img); //ok
    template <typename Type>
    LinAlg::Matrix<Type> ApplyingMask(const LinAlg::Matrix<Type> &mat, const LinAlg::Matrix<Type> &mask);
    template <typename Type, typename OtherType>
    LinAlg::Matrix<Type> ApplyingMask(const LinAlg::Matrix<Type> &mat, const LinAlg::Matrix<OtherType> &mask);
    template<typename Type>
    LinAlg::Matrix<Type> negative(const LinAlg::Matrix<Type> &mat);
    template <typename Type>
    LinAlg::Matrix<Type> Rotation(const LinAlg::Matrix<Type> &mat, const double &angle);
    template <typename Type>
    LinAlg::Matrix<Type> Scale(const LinAlg::Matrix<Type> &mat, const double &scale);
    template <typename Type>
    LinAlg::Matrix<Type> Reflect(const LinAlg::Matrix<Type> &mat, bool flag = false);
    template <typename Type>
    LinAlg::Matrix<Type> MediaFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask);
    template <typename Type>
    LinAlg::Matrix<Type> MedianFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask);
    template <typename Type>
    LinAlg::Matrix<Type> GaussianFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask, double step = 1); // 0.5 <= step <= 1.2
    template <typename Type>
    LinAlg::Matrix<Type> SelfReinforcementFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask, double a = 1);
    template <typename Type>
    LinAlg::Matrix<Type> LineFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask, const double a = 1);

    template<typename Type>
    LinAlg::Matrix<bool> im2bw(const LinAlg::Matrix<Type> &mat, const unsigned &limiar);
    template <typename Type>
    LinAlg::Matrix<bool> Erosion(const LinAlg::Matrix<bool> &mat);
    template <typename Type>
    LinAlg::Matrix<Type> ErosionMask(const LinAlg::Matrix<Type> &mat, const unsigned &row, const unsigned &col);
    template <typename Type>
    LinAlg::Matrix<bool> Dilatation(const LinAlg::Matrix<bool> &mat);
    template <typename Type>
    LinAlg::Matrix< LinAlg::Matrix<Type> > bound(LinAlg::Matrix<bool> &mat);

    template <typename Type>
    int GetColorPixel(const Type &r,const Type &g, const Type &b); //ok

    template <typename Type>
    LinAlg::Matrix<Type> completing(const LinAlg::Matrix<Type> &mat, const unsigned &sizemask);
    template <typename Type>
    LinAlg::Matrix<Type> pullingOut(const LinAlg::Matrix<Type> &completingMat, const unsigned &sizemask);

    //teste
    template <typename Type>
    LinAlg::Matrix<Type> ft2d(const LinAlg::Matrix<Type> &mat, const unsigned &sizemask)
    {
        LinAlg::Matrix<Type> mask(sizemask,sizemask);
        LinAlg::Matrix<Type> ret, aux;
        aux = ImageProcessing::completing<Type>(mat,sizemask);



        ret = ImageProcessing::ApplyingMask<Type>(aux,mask);
        ret = ImageProcessing::pullingOut<Type>(ret,sizemask);
        return ret;
    }
}
#include "SistemasdeControle/src/ImageProcessing/imageprocessing.hpp"
#endif // IMAGEPROCESSING_H
