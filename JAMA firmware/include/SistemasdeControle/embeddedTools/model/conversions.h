#include "LinAlg/matrix.h"
#include "arx.h"

inline unsigned factorial(unsigned n)
{
    unsigned retval = 1;
    for (int i = n; i > 1; --i)  retval *= i;
    return retval;
}

LinAlg::Matrix<long double> d2cConversion(const ModelHandler::ARX<long double> &arx)// retorna numerador e denominador da Ft e atraso de transporte
{
    LinAlg::Matrix<double> params = arx.getModelCoef(); double step = arx.getSampleTime();
    //std::cout << "Parametros do Modelo Discreto: " << params << std::endl;
    double Ad = -params(0,0), A = 0, Bd = 1, B = 0, C = params(1,0);
    //std::cout << "Entrou 4" << std::endl;
    unsigned factor =  (unsigned)ceil(fabs(Ad));
    //std::cout << "factor" << factor << std::endl;
    //std::cout << "Entrou 5" << std::endl;
    //taylor
    //std::cout << "Ad = " << Ad << "Bd = " << Bd << std::endl;
    for(long double i = 1; i < 7; ++i){ 
        A += -(pow(-1,i))*(pow(Ad/(factor) - 1.0,i))/i;
        //A += (1/factorial(i))*pow((Ad*step/factor),i);
        //std::cout << "A = " << A << std::endl;
    }

    //std::cout << "Entrou 6" << std::endl;
    A = (A + log(factor))/step;
    //std::cout << "A = " << A << std::endl;
    //std::cout << "Entrou 7" << std::endl;
    B = 1/((1/A)*(Ad - (1)))*Bd;
    //std::cout << "B = " << B << std::endl;
    //std::cout << "C = " << C << std::endl;
    //std::cout << "Entrou 8" << std::endl;
    LinAlg::Matrix<double> ret(1,3);
    ret(0,0) = B*C; ret(0,1) = -A; ret(0,2) = step;
    std::cout << "Parametros do Modelo Continuo: " << ret << std::endl;
    //std::cout << "Entrou 9" << std::endl;
    return ret;
}