#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

#include "QImage"
#include "QLabel"
#include "QWidget"
#include "qcustomplot.h"

#include "ImageProcessing/grayimage.h"
#include "ImageProcessing/rgbimage.h"
#include "ImageProcessing/imageconversion.h"
#include "ImageProcessing/imageprocessing.h"

#include "SistemasdeControle/headers/graphicLibs/plot.h"
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"

namespace ImageProcessing
{
    template <typename Type>
    void imShow(QImage img,QLabel *label);
    template <typename Type>
    void imShow(LinAlg::Matrix<Type> img,QLabel *label);
    template <typename Type>
    void imShow(ImageProcessing::RGBImage<Type> img,QLabel *label);
    template <typename Type>
    void imShow(ImageProcessing::GrayImage<Type> img,QLabel *label);

    template <typename Type>
    void plot(LinAlg::Matrix<Type> histograma, QWidget *widget);
    template <typename Type>
    void plot(ImageProcessing::GrayImage<Type> img, QWidget *widget);
    template <typename Type>
    void plot(ImageProcessing::RGBImage<Type> img, QWidget *widget){}

    template <typename Type>
    void bar(LinAlg::Matrix<Type> histograma, QWidget *widget);
    template <typename Type>
    void bar(ImageProcessing::GrayImage<Type> img, QWidget *widget);
    template <typename Type>
    void bar(ImageProcessing::RGBImage<Type> img, QWidget *widget){}
}

#include "ImageProcessing/imagepreview.hpp"
#endif // IMAGEPREVIEW_H
