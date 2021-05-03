#include "SistemasdeControle/headers/ImageProcessing/grayimage.h"

template <typename Type>
ImageProcessing::GrayImage<Type>::~GrayImage()
{

}

template <typename Type>
ImageProcessing::GrayImage<Type>::GrayImage(const LinAlg::Matrix<Type> &gray)
{
    this->gray = ImageProcessing::checkValue<Type>(gray);

    this->width = gray.getNumberOfRows();
    this->height = gray.getNumberOfColumns();
    this->a = 255;
}


template <typename Type>
ImageProcessing::GrayImage<Type>::GrayImage(const ImageProcessing::GrayImage<Type> &gray)
{
    this->gray = gray.getGray();

    this->width = gray.getWidth();
    this->height = gray.getHeight();
    this->a = 255;
}
template <typename Type>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator =(const ImageProcessing::GrayImage<Type>& grayImg)
{
    this->gray = grayImg.getGray();
    this->width = grayImg.getWidth();
    this->height = grayImg.getHeight();
    this->a = 255;

    return *this;
}

template <typename Type> template<typename OtherType>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator =(const ImageProcessing::GrayImage<OtherType>& grayImg)
{
    this->gray = grayImg.getGray();
    this->width = grayImg.getWidth();
    this->height = grayImg.getHeight();
    this->a = 255;

    return *this;
}

template <typename Type>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator +=(const Type& value)
{
    this->gray += value;
    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type> template<typename OtherType>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator +=(const OtherType& value)
{
    this->gray += value;
    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator +=(const ImageProcessing::GrayImage<Type>& grayImg)
{
    LinAlg::Matrix<Type> aux = LinAlg::sumPointToPoint<Type>(this->getGray(),grayImg.getGray());
    this->gray = ImageProcessing::checkValue<Type>(aux);
    return *this;
}

template <typename Type>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator -=(const Type& value)
{
    this->gray -= value;
    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type> template<typename OtherType>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator -=(const OtherType& value)
{
    this->gray -= value;
    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator -=(const ImageProcessing::GrayImage<Type>& grayImg)
{
    LinAlg::Matrix<Type> aux = LinAlg::subPointToPoint<Type>(this->getGray(),grayImg.getGray());
    this->gray = ImageProcessing::checkValue<Type>(aux);
    return *this;
}

template <typename Type>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator *=(const Type& value)
{
    this->gray *= value;
    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type> template<typename OtherType>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator *=(const OtherType& value)
{
    this->gray *= value;
    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator *=(const ImageProcessing::GrayImage<Type>& grayImg)
{
    LinAlg::Matrix<Type> aux = LinAlg::multPointToPoint<Type>(this->getGray(),grayImg.getGray());
    this->gray = ImageProcessing::checkValue<Type>(aux);
    return *this;
}

template <typename Type>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator /=(const Type& value)
{
    this->gray /= value;
    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type> template<typename OtherType>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator /=(const OtherType& value)
{
    this->gray /= value;
    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator ^=(const Type& value)
{
    for(unsigned i = 1; i <= this->width; ++i)
        for(unsigned j = 1; j <= this->height; ++j)
            this->gray(i,j) = this->gray(i,j)^value;

    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type> template<class OtherType>
ImageProcessing::GrayImage<Type>& ImageProcessing::GrayImage<Type>::operator ^=(const OtherType& value)
{
    for(unsigned i = 1; i <= this->width; ++i)
        for(unsigned j = 1; j <= this->height; ++j)
            this->gray(i,j) = this->gray(i,j)^value;

    this->gray = ImageProcessing::checkValue<Type>(this->gray);
    return *this;
}

template <typename Type>
LinAlg::Matrix<bool> ImageProcessing::operator <=(ImageProcessing::GrayImage<Type> lhs, const Type& value)
{
    LinAlg::Matrix<bool> aux = ImageProcessing::im2bw(lhs.getGray(),value);
    LinAlg::Matrix<bool> ret = LinAlg::complement<Type>(aux);

    return ret;
}

template <typename Type>
LinAlg::Matrix<bool> ImageProcessing::operator >=(ImageProcessing::GrayImage<Type> lhs, const Type& value)
{
    LinAlg::Matrix<bool> ret = ImageProcessing::im2bw(lhs.getGray(),value);
    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::Histogram(const ImageProcessing::GrayImage<Type> &grayimg)
{
    return ImageProcessing::Histogram<Type>(grayimg.getGray());
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::Rotation(const ImageProcessing::GrayImage<Type> &grayimg, const double &angle)
{
    ImageProcessing::GrayImage<Type> ret(ImageProcessing::Rotation<Type>(grayimg.getGray(),angle));
    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::Scale(const ImageProcessing::GrayImage<Type> &grayimg, const double &scale)
{
    ImageProcessing::GrayImage<Type> ret(ImageProcessing::Scale<Type>(grayimg.getGray(),scale));
    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::Reflect(const ImageProcessing::GrayImage<Type> &grayimg, bool flag)
{
    ImageProcessing::GrayImage<Type> ret(ImageProcessing::Reflect<Type>(grayimg.getGray(),flag));
    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::negative(const ImageProcessing::GrayImage<Type> &grayimg)
{
    ImageProcessing::GrayImage<Type> ret(ImageProcessing::negative<Type>(grayimg.getGray()));
    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::MediaFilter(const ImageProcessing::GrayImage<Type> &grayimg, const int &sizeMask)
{
    ImageProcessing::GrayImage<Type> ret(ImageProcessing::MediaFilter<Type>(grayimg.getGray(), sizeMask));
    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::MedianFilter(const ImageProcessing::GrayImage<Type> &grayimg, const int &sizeMask)
{
    ImageProcessing::GrayImage<Type> ret(ImageProcessing::MedianFilter<Type>(grayimg.getGray(), sizeMask));
    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::SelfReinforcementFilter(const ImageProcessing::GrayImage<Type> &grayimg, const int &sizeMask, double a)
{
    ImageProcessing::GrayImage<Type> ret(ImageProcessing::SelfReinforcementFilter<Type>(grayimg.getGray(), sizeMask, a));
    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::GaussianFilter(const ImageProcessing::GrayImage<Type> &grayimg, const int &sizeMask, double step)
{
    ImageProcessing::GrayImage<Type> ret(ImageProcessing::GaussianFilter<Type>(grayimg.getGray(), sizeMask, step));
    return ret;
}

template <typename Type>
LinAlg::Matrix<bool> ImageProcessing::im2bw(const ImageProcessing::GrayImage<Type> &grayimg, const double &limiar)
{
    LinAlg::Matrix<bool> ret = ImageProcessing::im2bw(grayimg.getGray(),limiar);
    return ret;
}
