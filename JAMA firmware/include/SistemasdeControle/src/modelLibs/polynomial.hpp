#ifdef testModel
    #include "../../../headers/modelLibs/polynomial.h"
#else
    #include "SistemasdeControle/headers/modelLibs/polynomial.h"
#endif

template <typename Type>
ModelHandler::Polynomial<Type>::Polynomial(uint8_t degree, uint8_t nInput,  uint8_t nOutput)
{
    this->degree = degree;
    this->nInput = nInput;
    this->nOutput = nOutput;
    this->LinearVectorA = LinAlg::Zeros<Type>(1,nInput*(degree+1));
    this->ModelCoef = LinAlg::Zeros<Type>(nInput*(degree+1),nOutput);
}

template<typename Type>
ModelHandler::Polynomial<Type>::Polynomial(const Polynomial<Type>& OtherPolynomialModel)
{
    this->degree = (OtherPolynomialModel.getNumberOfVariables()/OtherPolynomialModel.getNumberOfInputs()) - 1;
    this->nInput = OtherPolynomialModel.getNumberOfInputs();
    this->nOutput = OtherPolynomialModel.getNumberOfOutputs();
    this->ModelCoef             = OtherPolynomialModel.getModelCoef();
    this->LinearVectorA         = OtherPolynomialModel.getLinearVectorA();
}

template<typename Type> template<typename OtherType>
ModelHandler::Polynomial<Type>::Polynomial(const ModelHandler::Polynomial<OtherType>& otherPolynomialFunction)
{
    this->degree = (otherPolynomialFunction.getNumberOfVariables()/otherPolynomialFunction.getNumberOfInputs()) - 1;
    this->nInput = otherPolynomialFunction.getNumberOfInputs();
    this->nOutput = otherPolynomialFunction.getNumberOfOutputs();
    this->LinearVectorA = otherPolynomialFunction.getLinearVectorA();

    this->setModelCoef(otherPolynomialFunction.getModelCoef());
}

template <typename Type>
ModelHandler::Polynomial<Type>& ModelHandler::Polynomial<Type>::operator= (const Polynomial<Type>& otherPolynomialFunction)
{
    this->degree = (otherPolynomialFunction.getNumberOfVariables()/otherPolynomialFunction.getNumberOfInputs()) - 1;
    this->nInput = otherPolynomialFunction.getNumberOfInputs();
    this->nOutput = otherPolynomialFunction.getNumberOfOutputs();
    this->ModelCoef             = otherPolynomialFunction.getModelCoef();
    this->LinearVectorA         = otherPolynomialFunction.getLinearVectorA();
}

template<typename Type> template <typename OtherPolynomialFunctionType>
ModelHandler::Polynomial<Type>& ModelHandler::Polynomial<Type>::operator= (const Polynomial<OtherPolynomialFunctionType>& otherPolynomialFunction)
{
    this->degree = (otherPolynomialFunction.getNumberOfVariables()/otherPolynomialFunction.getNumberOfInputs()) - 1;
    this->nInput = otherPolynomialFunction.getNumberOfInputs();
    this->nOutput = otherPolynomialFunction.getNumberOfOutputs();
    this->ModelCoef             = otherPolynomialFunction.getModelCoef();
    this->LinearVectorA         = otherPolynomialFunction.getLinearVectorA();
}

template <typename Type>
void ModelHandler::Polynomial<Type>::setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> PastOutput)
{

    uint8_t counter = 0;
    for(uint8_t k = 0; k < this->nInput; ++k)
        for(uint8_t j = 0; j <= this->degree; ++j)
        {
            this->LinearVectorA(0,counter) = pow(Input(k,0), j);
            counter++;
        }

    this->LinearEqualityVectorB = PastOutput;
}

template <typename Type>
void ModelHandler::Polynomial<Type>::setLinearModel (LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output)
{

}

template <typename Type>
void ModelHandler::Polynomial<Type>::setInitialOutputValue(const LinAlg::Matrix<Type> &Output)
{

}

template <typename Type>
std::string ModelHandler::Polynomial<Type>::print()
{
    std::string str;

    for(uint8_t i = 0; i < this->nInput; ++i)
    {
        uint8_t counter = 0;
        str += " y";std::stringstream ss2; ss2 << i+1; str += ss2.str(); ss2.clear();
        str += " = ";
        for(uint8_t k = 0; k < this->nInput; ++k)
        {
            for(uint8_t j = 0; j <= this-> degree; ++j)
            {
                if(this->ModelCoef(counter,i) > 0)
                {
                    std::stringstream ss1;
                    ss1 << this->ModelCoef(counter,i);
                    str += " + ";
                    str += ss1.str();
                }
                else
                {
                    std::stringstream ss1;
                    ss1 << -this->ModelCoef(counter,i);
                    str += ss1.str();
                }
                if(j > 0)
                {
                    str += " u";
                    std::stringstream ss1;
                    ss1 << int(k) << "^" << int(j) << " ";
                    str += ss1.str().c_str();
                }
                counter++;
            }

        }
        str += '\n';
    }
    return str;
}

template <typename Type>
Type ModelHandler::Polynomial<Type>::sim(Type input)
{
    this->setLinearVector(input,0.0);
    //std::cout << this->LinearVectorA << this->LinearVectorA*this->ModelCoef;
    return (this->LinearVectorA*this->ModelCoef)(0,0);
}

template <typename Type>
Type ModelHandler::Polynomial<Type>::sim(Type input, Type output)
{

}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Polynomial<Type>::sim(LinAlg::Matrix<Type> Input)
{
    LinAlg::Matrix<double> Y;// = LinAlg::Zeros<Type>(Input.getNumberOfRows(),Input.getNumberOfColumns());
    for(uint32_t i = 0; i < Input.getNumberOfColumns(); ++i)
    {
        this->setLinearVector(Input.getColumn(i),"0");
        Y = Y||this->LinearVectorA*this->ModelCoef;
    }
    //std::cout << this->ModelCoef << "\n";
    //std::cout << this->LinearMatrixA << "\n";
    return ~(Y);
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Polynomial<Type>::sim(Type lmin, Type lmax, Type step)
{

}
