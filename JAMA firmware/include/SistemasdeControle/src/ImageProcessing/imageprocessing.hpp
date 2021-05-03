#include "SistemasdeControle/headers/ImageProcessing/imageprocessing.h"

template <typename Type>
int ImageProcessing::GetColorPixel(const Type &r,const Type &g, const Type &b)
{
    return QColor(r,g,b).value();
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::checkValue(const LinAlg::Matrix<Type> &mat)
{
    LinAlg::Matrix<Type> ret(mat.getNumberOfRows(),mat.getNumberOfColumns());

    for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j)
        {
            if(mat(i,j) > 255)
                ret(i,j) = 255;
            else if(mat(i,j) < 0)
                ret(i,j) = 0;
            else
                ret(i,j) = mat(i,j);
        }

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::GetColorPixel(const LinAlg::Matrix<Type> &r, const LinAlg::Matrix<Type> &g, const LinAlg::Matrix<Type> &b)
{
    LinAlg::Matrix<Type> ret(r.getNumberOfRows(),r.getNumberOfColumns());

    for(unsigned i = 1; i <= r.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= r.getNumberOfColumns(); ++j)
            ret(i,j) = QColor(r(i,j),g(i,j),b(i,j)).value();

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::Histogram(const LinAlg::Matrix<Type> &img)
{
    LinAlg::Matrix<Type> ret = LinAlg::Zeros<Type>(1,256);

    for(unsigned i = 1; i <= img.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= img.getNumberOfColumns(); ++j)
        {
            int k = img(i,j);
            ret(1,k) += 1;
        }

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::ApplyingMask(const LinAlg::Matrix<Type> &mat, const LinAlg::Matrix<Type> &mask)
{
    LinAlg::Matrix<Type> ret = ImageProcessing::completing<Type>(mat,mask.getNumberOfRows());
    LinAlg::Matrix<Type> aux;
    unsigned n = (int)mask.getNumberOfRows()/2;

    for(unsigned i = n; i <= ret.getNumberOfRows()-n-1; ++i){
        for(unsigned j = n; j <= ret.getNumberOfColumns()-n-1; ++j){
            aux = ret(from(i-n+mask.getNumberOfRows())-->(i-n+1),from(j-n+mask.getNumberOfColumns())-->(j-n+1));
            ret(i+1,j+1) = LinAlg::sum(LinAlg::multPointToPoint(aux,mask));
        }
    }
    ret = ImageProcessing::pullingOut<Type>(ret,mask.getNumberOfRows());
    return ret;
}

template <typename Type, typename OtherType>
LinAlg::Matrix<Type> ImageProcessing::ApplyingMask(const LinAlg::Matrix<Type> &mat, const LinAlg::Matrix<OtherType> &mask)
{
    LinAlg::Matrix<Type> ret = ImageProcessing::completing<Type>(mat,mask.getNumberOfRows());
    LinAlg::Matrix<Type> aux;
    unsigned n = (int)mask.getNumberOfRows()/2;

    for(unsigned i = n; i <= ret.getNumberOfRows()-n-1; ++i){
        for(unsigned j = n; j <= ret.getNumberOfColumns()-n-1; ++j){
            aux = ret(from(i-n+mask.getNumberOfRows())-->(i-n+1),from(j-n+mask.getNumberOfColumns())-->(j-n+1));
            ret(i+1,j+1) = LinAlg::sum(LinAlg::multPointToPoint(aux,mask));
        }
    }
    ret = ImageProcessing::pullingOut<Type>(ret,mask.getNumberOfRows());
    return ret;
}

template<typename Type>
LinAlg::Matrix<bool> ImageProcessing::im2bw(const LinAlg::Matrix<Type> &mat, const unsigned &limiar)
{
    LinAlg::Matrix<bool> ret(mat.getNumberOfRows(), mat.getNumberOfColumns());

    for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j)
        {
            if(mat(i,j) >= limiar)
                ret(i,j) = true;
            else
                ret(i,j) = false;
        }
    return ret;
}


template<typename Type>
LinAlg::Matrix<Type> ImageProcessing::negative(const LinAlg::Matrix<Type> &mat)
{
    LinAlg::Matrix<Type> ret(mat.getNumberOfRows(), mat.getNumberOfColumns());
    for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j)
            ret(i,j) = 255 - mat(i,j);

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::Rotation(const LinAlg::Matrix<Type> &mat, const double &angle)
{
    LinAlg::Matrix<Type> ret(mat.getNumberOfRows(),mat.getNumberOfColumns());
    LinAlg::Matrix<double> p1(2,1), p2(2,1), pos;
    LinAlg::Matrix<double> rot(2,2);

    double ang  = angle * M_PI/180;

    rot(1,1) = cos(ang); rot(1,2) = sin(ang);
    rot(2,1) = -sin(ang); rot(2,2) = cos(ang);

    p2(1,1) = mat.getNumberOfColumns()/2;
    p2(2,1) = mat.getNumberOfRows()/2;

    for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j){
            p1(1,1) = i - p2(2,1);
            p1(2,1) = j - p2(1,1);
            pos = (rot *p1) + p2;
            if(pos(2,1)>0 && pos(2,1) <= mat.getNumberOfColumns() && pos(1,1)>0 && pos(1,1) <= mat.getNumberOfRows())
                ret(i,j) = mat(Type(pos(1,1)),Type(pos(2,1)));
        }

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::Scale(const LinAlg::Matrix<Type> &mat, const double &scale)
{
    LinAlg::Matrix<Type> ret;

    if(scale > 1)
        ret = LinAlg::Zeros<Type>((Type)ceil(mat.getNumberOfRows()*scale),(Type)ceil(mat.getNumberOfColumns()*scale));
    else
        ret = LinAlg::Zeros<Type>((Type)floor(mat.getNumberOfRows()*scale),(Type)floor(mat.getNumberOfColumns()*scale));

    for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i)
        for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j)
        {
            if(scale > 1)
                ret(i,j) = mat(ceil(i/scale),ceil(j/scale));
            else
                ret(i,j) = mat(floor(i/scale),floor(j/scale));
        }

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::Reflect(const LinAlg::Matrix<Type> &mat, bool flag)
{
    LinAlg::Matrix<Type> ret(mat.getNumberOfRows(), mat.getNumberOfColumns());

    if(flag){
        for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i)
            for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j)
                ret(i,j) = mat(i,ret.getNumberOfColumns()-j+1);
    } else {
        for(unsigned i = 1; i <= ret.getNumberOfRows(); ++i)
            for(unsigned j = 1; j <= ret.getNumberOfColumns(); ++j)
                ret(i,j) = mat(ret.getNumberOfRows()-i+1,j);
    }

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::MediaFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask)
{
    if(sizeMask % 2 == 0){
        std::cout << "sizeMask deve ser impar" << std::endl;
        return mat;
    } else{
        LinAlg::Matrix<Type> aux2 = ImageProcessing::completing<Type>(mat,sizeMask);
        LinAlg::Matrix<Type> aux, ret = aux2;
        int n = sizeMask / 2;
        Type temp = 0;

        for(unsigned i = n; i <= ret.getNumberOfRows()-n-1; ++i)
            for(unsigned j = n; j <= ret.getNumberOfColumns()-n-1; ++j){
                aux = aux2(from(i-n+1)-->(i-n+sizeMask),from(j-n+1)-->(j-n+sizeMask));
                temp = LinAlg::sum(aux)/(sizeMask*sizeMask);
                ret(i+1,j+1) = temp;
            }
        ret = ImageProcessing::pullingOut<Type>(aux2,sizeMask);
        return ret;
    }
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::MedianFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask)
{
    LinAlg::Matrix<Type> aux2 = ImageProcessing::completing<Type>(mat,sizeMask);
    LinAlg::Matrix<Type> aux, ret = aux2;
    int n = sizeMask / 2, g = (sizeMask*sizeMask)/2;

    Type temp = 0;

    for(unsigned i = n; i <= ret.getNumberOfRows()-n-1; ++i)
        for(unsigned j = n; j <= ret.getNumberOfColumns()-n-1; ++j){
            aux = aux2(from(i-n+1)-->(i-n+sizeMask),from(j-n+1)-->(j-n+sizeMask));
            std::cout << "Comentei essa linha" << std::endl;
//            aux = LinAlg::selectionSort<Type>(aux);
            if(sizeMask % 2 == 0)
                temp = (aux(1,g) + aux(1,g+1))/2;
            else
                temp = aux(1,g);

            ret(i+1,j+1) = temp;
        }
    ret = ImageProcessing::pullingOut<Type>(ret,sizeMask);
    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::GaussianFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask, double step)
{
    if(sizeMask % 2 == 0){
        std::cout << "sizeMask deve ser impar" << std::endl;
        return mat;
    } else{
        LinAlg::Matrix<Type> ret = mat;
        LinAlg::Matrix<double> mask(sizeMask,sizeMask);
        int cont = (sizeMask/2) + 1;
        double temp = 1 / (2*M_PI*(step*step)), x = 0, y = 0, aux;

        for(unsigned i = 1; i <= mask.getNumberOfRows(); ++i)
            for(unsigned j = 1; j <= mask.getNumberOfColumns(); ++j)
            {
                x = pow((cont-i),2);
                y = pow((cont-j),2);
                mask(i,j) = (temp * exp(-(x+y)/(2*step*step)));
            }
        aux = LinAlg::sum(mask);
        ret = ImageProcessing::ApplyingMask<Type>(mat,mask);

        return ImageProcessing::checkValue<Type>(ret);
    }
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::SelfReinforcementFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask, double a)
{
    if(sizeMask % 2 == 0){
        std::cout << "sizeMask deve ser impar" << std::endl;
        return mat;
    } else{

        LinAlg::Matrix<Type> aux, filtro;
        LinAlg::Matrix<Type> aux2 = ImageProcessing::completing<Type>(mat,sizeMask);
        LinAlg::Matrix<Type> ret = aux2;
        filtro = LinAlg::Ones<Type>(sizeMask,sizeMask);
        int n = sizeMask / 2;
        Type temp = 0;

        for(unsigned i = n; i <= ret.getNumberOfRows()-n-1; ++i)
            for(unsigned j = n; j <= ret.getNumberOfColumns()-n-1; ++j){
                aux = aux2(from(i-n+1)-->(i-n+sizeMask),from(j-n+1)-->(j-n+sizeMask));
                temp = LinAlg::sum<Type>(LinAlg::multPointToPoint<Type>(aux,filtro));
                ret(i,j) = temp;
            }
        ret = ImageProcessing::pullingOut<Type>(ret,sizeMask);
        ret = LinAlg::abs<Type>(a*mat-ret);
        return ImageProcessing::checkValue<Type>(ret);
    }
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::LineFilter(const LinAlg::Matrix<Type> &mat, const int &sizeMask, const double a)
{
    if(sizeMask % 2 == 0){
        std::cout << "sizeMask deve ser impar" << std::endl;
        return mat;
    } else{
        LinAlg::Matrix<Type> aux, filtro;
        LinAlg::Matrix<Type> aux2 = ImageProcessing::completing<Type>(mat,sizeMask);
        LinAlg::Matrix<Type> ret = aux2;
        filtro = LinAlg::Ones<Type>(sizeMask,sizeMask);
        int n = (sizeMask) / 2;
        Type temp = 0;

        for(unsigned i = 1; i <= sizeMask; ++i)
            filtro(i,(sizeMask+1)/2) = sizeMask-1;

        for(unsigned i = 1+n; i <= ret.getNumberOfRows()-n-1; ++i)
            for(unsigned j = 1+n; j <= ret.getNumberOfColumns()-n-1; ++j)
            {
                aux = aux2(from(i-n)-->(i+n),from(j-n)-->(j+n));
                aux = LinAlg::multPointToPoint<Type>(aux,filtro);
                temp = LinAlg::sum<Type>(aux)/(sizeMask*sizeMask);
                aux2(i,j) = temp;
            }

        ret = ImageProcessing::pullingOut<Type>(ret,sizeMask);
        ret = LinAlg::abs<Type>((mat*a)-ret);
        return ImageProcessing::checkValue<Type>(ret);
    }

}

template <typename Type>
LinAlg::Matrix<bool> ImageProcessing::Erosion(const LinAlg::Matrix<bool> &mat)
{
    LinAlg::Matrix<bool> ret = LinAlg::Zeros<Type>(mat.getNumberOfRows(), mat.getNumberOfColumns());
    LinAlg::Matrix<bool>one = LinAlg::Ones<bool>(3,3);

    for(unsigned i = 1; i < ret.getNumberOfRows(); ++i)
        for(unsigned j = 1; j < ret.getNumberOfColumns(); ++j)
        {
            if(mat(i,j) == 1){
                LinAlg::Matrix<bool>submat = ImageProcessing::ErosionMask<bool>(mat,i,j);
                if(LinAlg::isEqual<bool>(submat,one))
                    ret(i,j) = 1;
            }
        }

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::ErosionMask(const LinAlg::Matrix<Type> &mat, const unsigned &row, const unsigned &col)
{
    LinAlg::Matrix<Type> submat = LinAlg::Zeros<Type>(3,3), ret;
    submat(2,2) = 1;

    if(row-1 > 0)
        if(mat(row-1,col) == 1)
            submat(1,2) = 1;

    if(row-1 > 0 && col+1 <= mat.getNumberOfColumns())
        if(mat(row-1,col+1) == 1)
            submat(1,3) = 1;

    if(col+1 <= mat.getNumberOfColumns())
        if(mat(row,col+1) == 1)
            submat(2,3) = 1;

    if(row+1 <= mat.getNumberOfRows() && col+1 <= mat.getNumberOfColumns())
        if(mat(row+1,col+1) == 1)
            submat(3,3) = 1;

    if(row+1 <= mat.getNumberOfRows())
        if(mat(row+1,col) == 1)
            submat(3,2) = 1;

    if(row+1 <= mat.getNumberOfRows() && col-1 > 0)
        if(mat(row+1,col-1) == 1)
            submat(3,1) = 1;

    if(col-1 > 0 )
        if(mat(row,col-1) == 1)
            submat(2,1) = 1;

    if(row-1 > 0 && col-1 > 0)
        if(mat(row-1, col-1) == 1)
            submat(1,1) = 1;

    ret = submat;
    return ret;
}

template <typename Type>
LinAlg::Matrix<bool> ImageProcessing::Dilatation(const LinAlg::Matrix<bool> &mat)
{
    LinAlg::Matrix<bool> ret = LinAlg::complement<bool>(mat);
    LinAlg::Matrix<bool> aux = LinAlg::Zeros<bool>(ret.getNumberOfRows(),ret.getNumberOfColumns());
    ret = ImageProcessing::Erosion<bool>(ret);
    ret = LinAlg::complement<bool>(ret);

    for(unsigned i = 3; i <= aux.getNumberOfRows()-4;++i)
        for(unsigned j = 3; j <= aux.getNumberOfColumns()-4;++j)
            aux(i,j) = ret(i,j);

    ret = aux;
    return ret;
}

template <typename Type>
LinAlg::Matrix<LinAlg::Matrix<Type> > ImageProcessing::bound(LinAlg::Matrix<bool> &mat)
{
    LinAlg::Matrix<LinAlg::Matrix<unsigned> > t(1,2);
    LinAlg::Matrix<Type> aux,       x = LinAlg::Zeros<unsigned>(1,4*mat.getNumberOfColumns()*mat.getNumberOfRows()),
                                    y = LinAlg::Zeros<unsigned>(1,4*mat.getNumberOfColumns()*mat.getNumberOfRows());
    aux = mat;
    unsigned ret;
    unsigned cont = 0, cont2 = 1;
    bool ok = false;

    if(sizeof(mat(1,1)) == sizeof(bool))
    {
        for(unsigned i = 1; i <= aux.getNumberOfRows(); ++i){
            for(unsigned j= 1; j <= aux.getNumberOfColumns(); ++j){
                if(aux(i,j) == 1){
                    x(1,1) = i;
                    y(1,1) = j;
                    aux(i,j) = cont + 1;
                    ok = true;
                    break;
                }else{
                    x(1,1) = 0;
                    y(1,1) = 0;
                }
            }
            if(ok)
                break;
        }

        cont2 = 2;

        while(x(1,1) != 0 && x(1,1) != 0){
            for(unsigned j = 1; j <= aux.getNumberOfColumns()*aux.getNumberOfRows(); ++j){
                if(cont2-1 < j)
                    continue;
                if(x(1,j)-1 > 0){
                    if(aux(x(1,j)-1,y(1,j)) == 1){
                        aux(x(1,j)-1,y(1,j)) = cont + 1;
                        x(1,cont2) = x(1,j)-1;
                        y(1,cont2) = y(1,j);
                        cont2 = cont2+1;
                    }
                }
                if(x(1,j)+1 <= aux.getNumberOfRows()){
                    if(aux(x(1,j)+1,y(1,j)) == 1){
                        aux(x(1,j)+1,y(1,j)) = cont+1;
                        x(1,cont2) = x(1,j)+1;
                        y(1,cont2) = y(1,j);
                        cont2=cont2+1;
                    }
                }
                if(y(1,j)-1 > 0){
                   if(aux(x(1,j),y(1,j)-1) == 1){
                        aux(x(1,j),y(1,j)-1) = cont+1;
                        x(1,cont2) = x(1,j);
                        y(1,cont2) = y(1,j)-1;
                        cont2=cont2+1;
                   }
                }
                if(y(1,j)+1 <= aux.getNumberOfColumns()){
                    if(aux(x(1,j),y(1,j)+1) == 1){
                        aux(x(1,j),y(1,j)+1) = cont+1;
                        x(1,cont2) = x(1,j);
                        y(1,cont2) = y(1,j)+1;
                        cont2 = cont2+1;
                    }
                }
            }
            cont  = cont+1;
            cont2 = 2;
            ok = false;
            for(unsigned i = 1; i <= aux.getNumberOfRows(); ++i){
                for(unsigned j = 1; j <= aux.getNumberOfColumns(); ++j){
                    if(aux(i,j) == 1){
                        x(1,1) = i;
                        y(1,1) = j;
                        aux(i,j) = cont + 1;
                        ok = true;
                        break;
                    }else{
                        x(1,1) = 0;
                        y(1,1) = 0;
                    }
                }
                if(ok)
                    break;
            }
        }
        ret = cont - 1;
    }
    else
    {
        std::cout << "Apenas com Imagens Booleanas, ou seja binarias" << std::endl;
    }
    t(1,1) = LinAlg::Matrix<Type>((Type)ret);
    t(1,2) = aux;
    return t;
}

template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::completing(const LinAlg::Matrix<Type> &mat, const unsigned &sizemask)
{
    unsigned n = (int)sizemask/2;
    LinAlg::Matrix<Type> ret = LinAlg::Zeros<Type>(mat.getNumberOfRows()+n*2,mat.getNumberOfColumns()+n*2);

    for(unsigned i = n; i <= ret.getNumberOfRows()-n-1; ++i)
        for(unsigned j = n; j <= ret.getNumberOfColumns()-n-1; ++j)
            ret(i+1,j+1) = mat((i-n+1),(j-n+1));

    return ret;
}
template <typename Type>
LinAlg::Matrix<Type> ImageProcessing::pullingOut(const LinAlg::Matrix<Type> &completingMat, const unsigned &sizemask)
{
    unsigned n = (unsigned)sizemask/2;
    LinAlg::Matrix<Type> ret;
    ret = completingMat(from(n+1)-->completingMat.getNumberOfRows()-n,from(n+1)-->completingMat.getNumberOfColumns()-n);
    return ret;
}

