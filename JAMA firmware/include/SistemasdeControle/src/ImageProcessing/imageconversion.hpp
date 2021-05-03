#include "imageconversion.h"

template <typename Type>
QImage ImageProcessing::RGBImage2QImage(const ImageProcessing::RGBImage<Type> &rgbImg)
{
    return ImageProcessing::SetPixel<Type>(rgbImg.getRed(),rgbImg.getGreen(),rgbImg.getBlue());
}

template <typename Type>
QImage ImageProcessing::GrayImage2QImage(const ImageProcessing::GrayImage<Type> &grayImg)
{
    LinAlg::Matrix<Type> gray = grayImg.getGray();
    return ImageProcessing::SetPixel<Type>(gray,gray,gray);
}

template <typename Type>
QImage ImageProcessing::Bitmap2QImage(const LinAlg::Matrix<Type> bitmap)
{
    return ImageProcessing::SetPixel<Type>(bitmap, bitmap, bitmap);
}

template <typename Type>
QImage ImageProcessing::Bitmap2QImage(const LinAlg::Matrix<bool> &img)
{
    LinAlg::Matrix<Type> ret(img.getNumberOfRows(), img.getNumberOfColumns());

    for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j)
            ret(i,j) = Type(img(i,j))*255;

    return ImageProcessing::SetPixel<Type>(ret,ret,ret);
}

template <typename Type>
QImage ImageProcessing::RedImage(const ImageProcessing::RGBImage<Type> &rgbImg)
{
    LinAlg::Matrix<Type> g = LinAlg::Zeros<Type>(rgbImg.getWidth(), rgbImg.getHeight());
    LinAlg::Matrix<Type> b = LinAlg::Zeros<Type>(rgbImg.getWidth(), rgbImg.getHeight());

    return ImageProcessing::SetPixel<Type>(rgbImg.getRed(),g,b);
}

template <typename Type>
QImage ImageProcessing::GreenImage(const ImageProcessing::RGBImage<Type> &rgbImg)
{
    LinAlg::Matrix<Type> r = LinAlg::Zeros<Type>(rgbImg.getWidth(), rgbImg.getHeight());
    LinAlg::Matrix<Type> b = LinAlg::Zeros<Type>(rgbImg.getWidth(), rgbImg.getHeight());

    return ImageProcessing::SetPixel<Type>(r,rgbImg.getGreen(),b);
}

template <typename Type>
QImage ImageProcessing::BlueImage(const ImageProcessing::RGBImage<Type> &rgbImg)
{
    LinAlg::Matrix<Type> r = LinAlg::Zeros<Type>(rgbImg.getWidth(), rgbImg.getHeight());
    LinAlg::Matrix<Type> g = LinAlg::Zeros<Type>(rgbImg.getWidth(), rgbImg.getHeight());

    return ImageProcessing::SetPixel<Type>(r,g,rgbImg.getBlue());
}

template <typename Type>
QImage ImageProcessing::SetPixel(const LinAlg::Matrix<Type> &r, const LinAlg::Matrix<Type> &g, const LinAlg::Matrix<Type> &b)
{
    QImage ret(r.getNumberOfRows(),r.getNumberOfColumns(),QImage::Format_RGB32);

    for(unsigned i = 0; i < r.getNumberOfRows(); ++i)
        for(unsigned j = 0; j < r.getNumberOfColumns(); ++j)
            ret.setPixel(i,j,QColor(r(i+1,j+1),g(i+1,j+1),b(i+1,j+1)).rgb());

    return ret;
}

template <typename Type>
ImageProcessing::RGBImage<Type> ImageProcessing::QImage2RGBImage(const QImage &img)
{
    LinAlg::Matrix<Type> r(img.width(),img.height()), g(img.width(),img.height()), b(img.width(),img.height());

    for(unsigned i = 0; i < img.width(); ++i)
            for(unsigned j = 0; j < img.height(); ++j){
                QColor color(img.pixel(i,j));
                r(i+1,j+1) = color.red();
                g(i+1,j+1) = color.green();
                b(i+1,j+1) = color.blue();
            }

    ImageProcessing::RGBImage<Type> ret(r,g,b);

    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::QImage2GrayImage(const QImage &img)
{
    LinAlg::Matrix<Type> gray(img.width(),img.height());
    for(unsigned i = 0; i < img.width(); ++i)
            for(unsigned j = 0; j < img.height(); ++j){
                QColor color(img.pixel(i,j));
                gray(i+1,j+1) = qGray(color.red(),color.green(),color.blue());
            }

    ImageProcessing::GrayImage<Type> ret(gray);
    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::RGBImage2GrayImage(const ImageProcessing::RGBImage<Type> &rgbimg)
{
    LinAlg::Matrix<Type> gray(rgbimg.getWidth(), rgbimg.getHeight()),
                        r = rgbimg.getRed(),
                        g = rgbimg.getGreen(),
                        b = rgbimg.getBlue();

    for(unsigned i = 1; i <= gray.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= gray.getNumberOfColumns(); ++j)
            gray(i,j) = qGray(r(i,j),g(i,j),b(i,j));

    ImageProcessing::GrayImage<Type> ret(gray);
    return ret;
}

template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::Bitmap2GrayImage(const LinAlg::Matrix<bool> &img)
{
    LinAlg::Matrix<Type> gray(img.getNumberOfRows(), img.getNumberOfColumns());

    for(unsigned i = 1; i <= gray.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= gray.getNumberOfColumns(); ++j)
            gray(i,j) = Type(img(i,j))*255;

    ImageProcessing::GrayImage<Type> ret(gray);
    return ret;
}
template <typename Type>
ImageProcessing::GrayImage<Type> ImageProcessing::Bitmap2GrayImage(const LinAlg::Matrix<Type> &img)
{
    ImageProcessing::GrayImage<Type> ret(img);
    return ret;
}
