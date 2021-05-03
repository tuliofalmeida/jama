#include "arx.h"


template <typename Type>
ModelHandler::ARX<Type>::ARX(unsigned nInputDelay,unsigned nOutputDelay,
                             unsigned delay,
                             unsigned qdtInputVar, unsigned qdtOutputVar,
                             double sampleTime)
{
    this->maxnInOut    = nInputDelay;
    if( nOutputDelay > nInputDelay)
        this->maxnInOut    = nOutputDelay;

    this->delay        = delay;
    this->sampleTime   = sampleTime;
    this->nInputDelay  = nInputDelay;
    this->qdtInputVar  = qdtInputVar;
    this->nOutputDelay = nOutputDelay;
    this->qdtOutputVar = qdtOutputVar;

    this->nSample   = this->delay + this->maxnInOut + 1;
    this->Input     = LinAlg::Zeros<Type>(qdtInputVar, nInputDelay);
    this->Output    = LinAlg::Zeros<Type>(qdtOutputVar, nOutputDelay);
    this->ModelCoef = LinAlg::Zeros<Type>(nInputDelay*qdtInputVar + nOutputDelay*qdtOutputVar, qdtOutputVar);

    this->InputLinearVector  = LinAlg::Zeros<Type>(this->qdtInputVar, this->nInputDelay);
    this->OutputLinearVector = LinAlg::Zeros<Type>(this->qdtOutputVar, this->delay + this->nOutputDelay);
    this->LinearVectorA      = LinAlg::Zeros<Type>(this->qdtOutputVar, this->nInputDelay+this->delay + this->nOutputDelay);
}

template <typename Type>
ModelHandler::ARX<Type>::ARX(const ModelHandler::ARX<Type>& OtherArxModel){

    this->delay                 = OtherArxModel.delay;
    this->nInputDelay           = OtherArxModel.nInputDelay;
    this->qdtInputVar           = OtherArxModel.qdtInputVar;
    this->nOutputDelay          = OtherArxModel.nOutputDelay;
    this->qdtOutputVar          = OtherArxModel.qdtOutputVar;
    this->maxnInOut             = OtherArxModel.maxnInOut;
    this->nSample               = OtherArxModel.nSample;

    this->sampleTime            = OtherArxModel.getSampleTime();
    this->timeSimulation        = OtherArxModel.timeSimulation;
    this->Input                 = OtherArxModel.Input;
    this->Output                = OtherArxModel.Output;
    this->ModelCoef             = OtherArxModel.ModelCoef;
    this->LinearVectorA         = OtherArxModel.LinearVectorA;
    this->LinearVectorB         = OtherArxModel.LinearVectorB;
    this->InputLinearVector     = OtherArxModel.InputLinearVector;
    this->OutputLinearVector    = OtherArxModel.OutputLinearVector;
}

template<typename Type> template<typename OtherType>
ModelHandler::ARX<Type>::ARX(const ModelHandler::ARX<OtherType>& otherARXFunction)
{
    this->nInputDelay  = otherARXFunction.getNumberOfInputDelays();
    this->qdtInputVar  = otherARXFunction.getNumberOfInputs();
    this->nOutputDelay = otherARXFunction.getNumberOfOutputDelays();
    this->qdtOutputVar = otherARXFunction.getNumberOfOutputs();
    this->maxnInOut    = otherARXFunction.getMaxnInOut ();
    this->nSample      = otherARXFunction.getNSample ();

    this->sampleTime            = otherARXFunction.getSampleTime();
    this->timeSimulation        = otherARXFunction.getTimeSimulation();
    this->delay                 = otherARXFunction.getTransportDelay();
    this->Input                 = otherARXFunction.getInputMatrix();
    this->Output                = otherARXFunction.getOutputMatrix();
    this->ModelCoef             = otherARXFunction.getModelCoef();
    this->LinearVectorA         = otherARXFunction.getLinearVectorA();
    this->LinearVectorB         = otherARXFunction.getLinearEqualityVectorB();
}

template <typename Type>
ModelHandler::ARX<Type>& ModelHandler::ARX<Type>::operator= (const ModelHandler::ARX<Type>& otherARXFunction)
{
    this->delay                 = otherARXFunction.delay;
    this->nInputDelay           = otherARXFunction.nInputDelay;
    this->qdtInputVar           = otherARXFunction.qdtInputVar;
    this->nOutputDelay          = otherARXFunction.nOutputDelay;
    this->qdtOutputVar          = otherARXFunction.qdtOutputVar;
    this->maxnInOut             = otherARXFunction.maxnInOut;
    this->nSample               = otherARXFunction.nSample;

    this->sampleTime            = otherARXFunction.getSampleTime();
    this->timeSimulation        = otherARXFunction.timeSimulation;
    this->Input                 = otherARXFunction.Input;
    this->Output                = otherARXFunction.Output;
    this->ModelCoef             = otherARXFunction.ModelCoef;
    this->LinearVectorA         = otherARXFunction.LinearVectorA;
    this->LinearEqualityVectorB = otherARXFunction.LinearEqualityVectorB;
    this->InputLinearVector     = otherARXFunction.InputLinearVector;
    this->OutputLinearVector    = otherARXFunction.OutputLinearVector;

    return *this;
}

template<typename Type> template<typename OtherARXFunctionType> // não funciona
ModelHandler::ARX<Type>& ModelHandler::ARX<Type>::operator= (const ModelHandler::ARX<OtherARXFunctionType>& otherARXFunction)
{
    this->nInputDelay    = otherARXFunction.getNumberOfInputDelays();
    this->qdtInputVar  = otherARXFunction.getNumberOfInputs();
    this->nOutputDelay   = otherARXFunction.getNumberOfOutputDelays();
    this->qdtOutputVar = otherARXFunction.getNumberOfOutputs();
    this->maxnInOut    = otherARXFunction.getMaxnInOut ();
    this->nSample      = otherARXFunction.getNSample ();

    this->sampleTime            = otherARXFunction.getSampleTime();
    this->timeSimulation        = otherARXFunction.getTimeSimulation();
    this->delay                 = otherARXFunction.getTransportDelay();
    this->Input                 = otherARXFunction.getInputMatrix();
    this->Output                = otherARXFunction.getOutputMatrix();
    this->ModelCoef             = otherARXFunction.getModelCoef();
    this->LinearVectorA         = otherARXFunction.getLinearVectorA();
    this->LinearVectorB = otherARXFunction.getLinearEqualityVectorB();

    return *this;
}

// Nesta função será avaliada a quantidade de saídas pelo número de linhas das matrizes
// Neste caso Input e Output se forem escalares corresponderão ao próximo valor
// a ser colocado no vetor de saídas ou entradas e sor uma matriz corresponderá
// a um conjunto de variáveis no instante de tempo pedido
template <typename Type>
void ModelHandler::ARX<Type>::setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> PastOutput)
{
//    this->InputLinearVector  =  (Input      << this->InputLinearVector);
    Input >> this->InputLinearVector;
//    this->OutputLinearVector =  (PastOutput << this->OutputLinearVector);
    PastOutput >> this->OutputLinearVector;
    LinAlg::Matrix<Type> TempLinearVector;


    for(unsigned i = 0; i < this->OutputLinearVector.getNumberOfRows(); ++i)
        TempLinearVector = TempLinearVector | -this->OutputLinearVector.getRow(i);

    for(unsigned i = 0; i < this->InputLinearVector.getNumberOfRows(); ++i)
        TempLinearVector = TempLinearVector | this->InputLinearVector.getRow(i);

    this->LinearVectorA = TempLinearVector;
    this->LinearVectorB = PastOutput;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::ARX<Type>::sim(LinAlg::Matrix<Type> Input)
{
    this->Input  = Input;
    LinAlg::Matrix<Type> EstOutput = LinAlg::Zeros<Type>(this->qdtOutputVar,Input.getNumberOfColumns());

    for(unsigned i = 0; i < Input.getNumberOfColumns()-1; ++i){
        this->setLinearVector(Input.getColumn(i),EstOutput.getColumn(Input.getNumberOfColumns()-1));
        EstOutput << ~(this->LinearVectorA*this->ModelCoef);
    }
    return this->Output = EstOutput;
}

template <typename Type>
unsigned ModelHandler::ARX<Type>::getNumberOfVariables() const
{
    return this->qdtInputVar*this->nInputDelay + this->qdtOutputVar*this->nOutputDelay;
}

template <typename Type>
std::string ModelHandler::ARX<Type>::print()
{
    std::string str;
    for(unsigned nOutputVar = 0; nOutputVar < this->qdtOutputVar; ++nOutputVar)
    {
        str += " y";
        std::stringstream ss2; ss2 << nOutputVar + 1; str += ss2.str();
        str += "( k ) = ";

        unsigned nCoef = 0;
        bool isTheFirst = true;
        for(unsigned yPar = 0; yPar < this->qdtOutputVar; ++yPar)
        {
            for(unsigned ny = 0; ny < this->nOutputDelay; ++ny)
            {
                if(fabs(this->ModelCoef(nCoef,nOutputVar)) < 1e-30)
                {
                    ++nCoef;
                    continue;
                }
                else if(this->ModelCoef(nCoef,nOutputVar) > 0)
                {
                    std::stringstream ss1;
                    ss1 << this->ModelCoef(nCoef,nOutputVar);
                    str += " - ";
                    str += ss1.str();
                }
                else
                {
                    std::stringstream ss1;
                    ss1 << -this->ModelCoef(nCoef,nOutputVar);
                    if(!isTheFirst)
                        str += " + ";
                    str += ss1.str();
                }
                str += " y";
                std::stringstream ss2; ss2 << yPar + 1; str += ss2.str();
                str += "( k - ";
                std::stringstream ss3; ss3 << ny+1; str += ss3.str();
                str += " ) ";
                ++nCoef;
                isTheFirst = false;
            }
        }
        for(unsigned uPar = 0; uPar < this->qdtInputVar; ++uPar)
        {
            for(unsigned nu = 0; nu < this->nInputDelay; ++nu)
            {
                if(fabs(this->ModelCoef(nCoef,nOutputVar)) < 1e-30)
                {
                    ++nCoef;
                    continue;
                }
                else if(this->ModelCoef(nCoef,nOutputVar) > 0)
                {
                    std::stringstream ss1;
                    ss1 << this->ModelCoef(nCoef,nOutputVar);
                    if(!isTheFirst)
                        str += " + ";
                    str += ss1.str();
                }
                else
                {
                    std::stringstream ss1;
                    ss1 << -this->ModelCoef(nCoef,nOutputVar);
                    str += " - ";
                    str += ss1.str();
                }
                str += " u";
                std::stringstream ss2; ss2 << uPar + 1; str += ss2.str();
                str += "( k - ";
                std::stringstream ss3; ss3 << nu + 1; str += ss3.str();
                str += " ) ";
                ++nCoef;
                isTheFirst = false;
            }
        }
        if(nCoef == 0)
            str += "0 ";
        str += "\n";
    }
    return str;
}

template<typename Type> // ok
std::ostream& ModelHandler::operator<< (std::ostream& output, ModelHandler::ARX<Type> model)
{
    output << model.print();
    return output;
}

template<typename Type> //ok
std::string&  ModelHandler::operator<< (std::string& output,  ModelHandler::ARX<Type> model)
{
    output += model.print();
    return output;
}
