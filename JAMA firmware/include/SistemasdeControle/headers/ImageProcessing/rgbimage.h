#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include "ImageProcessing/imageprocessing.h"
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"

namespace ImageProcessing
{
    template <class Type>
    class RGBImage
    {
        public:
            RGBImage(){}
            RGBImage(const LinAlg::Matrix<Type> &r,
                     const LinAlg::Matrix<Type> &g,
                     const LinAlg::Matrix<Type> &b);
            RGBImage(const ImageProcessing::RGBImage<Type> &rgb);
            ~RGBImage();

            LinAlg::Matrix<Type> getRed()   const {return this->red;}
            LinAlg::Matrix<Type> getGreen() const {return this->green;}
            LinAlg::Matrix<Type> getBlue()  const {return this->blue;}

            unsigned getWidth() const {return this->width;}
            unsigned getHeight()const {return this->height;}

            ImageProcessing::RGBImage<Type>& operator =(const ImageProcessing::RGBImage<Type>& rgbImg);
//            template<typename RightType>
//            ImageProcessing::RGBImage<Type>& operator= (const ImageProcessing::RGBImage<RightType>& rgbImg);

            ImageProcessing::RGBImage<Type>& operator+= (const ImageProcessing::RGBImage<Type>& rgbImg);
            ImageProcessing::RGBImage<Type>& operator+= (const Type& value);
            template<typename RightType>
            ImageProcessing::RGBImage<Type>& operator+= (const RightType& value);

            ImageProcessing::RGBImage<Type>& operator-= (const ImageProcessing::RGBImage<Type>& rgbImg);
            ImageProcessing::RGBImage<Type>& operator-= (const Type& value);
            template<typename RightType>
            ImageProcessing::RGBImage<Type>& operator-= (const RightType& value);

            ImageProcessing::RGBImage<Type>& operator*= (const ImageProcessing::RGBImage<Type>& rgbImg);
            ImageProcessing::RGBImage<Type>& operator*= (const Type& value);
            template<typename RightType>
            ImageProcessing::RGBImage<Type>& operator*= (const RightType& value);

            ImageProcessing::RGBImage<Type>& operator/= (const Type& value);
            template<typename RightType>
            ImageProcessing::RGBImage<Type>& operator/= (const RightType& value);

            ImageProcessing::RGBImage<Type>& operator^= (const Type& value);
            template<typename RightType>
            ImageProcessing::RGBImage<Type>& operator^= (const RightType& value);

        private:
            LinAlg::Matrix<Type> red,green,blue;
            unsigned height, width, a;
    };

    template <typename Type>
    ImageProcessing::RGBImage<Type> operator +(ImageProcessing::RGBImage<Type> lhs,const Type& rhs){return lhs += rhs;}
    template <typename Type, typename OtherType>
    ImageProcessing::RGBImage<Type> operator +(ImageProcessing::RGBImage<Type> lhs,const OtherType& rhs){return lhs += rhs;}
    template <typename Type>
    ImageProcessing::RGBImage<Type> operator +(const Type& lhs,ImageProcessing::RGBImage<Type> rhs){return rhs += lhs;}
    template <typename Type, typename OtherType>
    ImageProcessing::RGBImage<Type> operator +(const OtherType& lhs,ImageProcessing::RGBImage<Type> rhs){return rhs += lhs;}
    template <typename Type>
    ImageProcessing::RGBImage<Type> operator +(ImageProcessing::RGBImage<Type> lhs,ImageProcessing::RGBImage<Type> rhs){return lhs += rhs;}

    template <typename Type>
    ImageProcessing::RGBImage<Type> operator -(ImageProcessing::RGBImage<Type> lhs,const Type& rhs){return lhs -= rhs;}
    template <typename Type, typename OtherType>
    ImageProcessing::RGBImage<Type> operator -(ImageProcessing::RGBImage<Type> lhs,const OtherType& rhs){return lhs -= rhs;}
    template <typename Type>
    ImageProcessing::RGBImage<Type> operator -(const Type& lhs,ImageProcessing::RGBImage<Type> rhs){return rhs -= lhs;}
    template <typename Type, typename OtherType>
    ImageProcessing::RGBImage<Type> operator -(const OtherType& lhs,ImageProcessing::RGBImage<Type> rhs){return rhs -= lhs;}
    template <typename Type>
    ImageProcessing::RGBImage<Type> operator -(ImageProcessing::RGBImage<Type> lhs,ImageProcessing::RGBImage<Type> rhs){return lhs -= rhs;}

    template <typename Type>
    ImageProcessing::RGBImage<Type> operator *(ImageProcessing::RGBImage<Type> lhs,const Type& rhs){return lhs *= rhs;}
    template <typename Type, typename OtherType>
    ImageProcessing::RGBImage<Type> operator *(ImageProcessing::RGBImage<Type> lhs,const OtherType& rhs){return lhs *= rhs;}
    template <typename Type>
    ImageProcessing::RGBImage<Type> operator *(const Type& lhs,ImageProcessing::RGBImage<Type> rhs){return rhs *= lhs;}
    template <typename Type, typename OtherType>
    ImageProcessing::RGBImage<Type> operator *(const OtherType& lhs,ImageProcessing::RGBImage<Type> rhs){return rhs *= lhs;}
    template <typename Type>
    ImageProcessing::RGBImage<Type> operator *(ImageProcessing::RGBImage<Type> lhs,ImageProcessing::RGBImage<Type> rhs){return lhs *= rhs;}

    template <typename Type>
    ImageProcessing::RGBImage<Type> operator /(ImageProcessing::RGBImage<Type> lhs,const Type& rhs){return lhs /= rhs;}
    template <typename Type, typename OtherType>
    ImageProcessing::RGBImage<Type> operator /(ImageProcessing::RGBImage<Type> lhs,const OtherType& rhs){return lhs /= rhs;}

    template <typename Type>
    ImageProcessing::RGBImage<Type> operator ^(ImageProcessing::RGBImage<Type> lhs,const Type& rhs){return lhs ^= rhs;}
    template <typename Type, typename OtherType>
    ImageProcessing::RGBImage<Type> operator ^(ImageProcessing::RGBImage<Type> lhs,const OtherType& rhs){return lhs ^= rhs;}
    template <typename Type>
    ImageProcessing::RGBImage<Type> operator ^(const Type& lhs,ImageProcessing::RGBImage<Type> rhs){return rhs ^= lhs;}
    template <typename Type, typename OtherType>
    ImageProcessing::RGBImage<Type> operator ^(const OtherType& lhs,ImageProcessing::RGBImage<Type> rhs){return rhs ^= lhs;}

    template <typename Type>
    ImageProcessing::RGBImage<Type> Rotation(const ImageProcessing::RGBImage<Type> &rgbimg, const double &angle);
    template <typename Type>
    ImageProcessing::RGBImage<Type> Scale(const ImageProcessing::RGBImage<Type> &rgbimg, const double &scale);
    template <typename Type>
    ImageProcessing::RGBImage<Type> Reflect(const ImageProcessing::RGBImage<Type> &rgbimg, bool flag = false);
    template <typename Type>
    ImageProcessing::RGBImage<Type> negative(const ImageProcessing::RGBImage<Type> &rgbimg);

    template <typename Type>
    ImageProcessing::RGBImage<Type> MediaFilter(const ImageProcessing::RGBImage<Type> &rgbimg, const int &sizeMask);
    template <typename Type>
    ImageProcessing::RGBImage<Type> MedianFilter(const ImageProcessing::RGBImage<Type> &rgbimg, const int &sizeMask);
    template <typename Type>
    ImageProcessing::RGBImage<Type> GaussianFilter(const ImageProcessing::RGBImage<Type> &rgbimg, const int &sizeMask, double step = 1);

    template <typename Type>
    LinAlg::Matrix<Type> Histogram(const ImageProcessing::RGBImage<Type> &rgbimg); //ok
}
#include "ImageProcessing/rgbimage.hpp"
#endif // RGBIMAGE_H
