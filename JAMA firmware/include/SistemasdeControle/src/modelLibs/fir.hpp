#include "SistemasdeControle/headers/modelLibs/fir.h"

template <class Type>
ModelHandler::FIR<Type>::FIR(unsigned nInputpar,
                             unsigned delay,
                             unsigned qdtInputVar, unsigned qdtOutputVar,
                             double sampleTime)
{
    this->delay        = delay;
    this->nInputpar    = nInputpar;
    this->sampleTime   = sampleTime;
    this->qdtInputVar  = qdtInputVar;
    this->qdtOutputVar = qdtOutputVar;

    this->ModelCoef = LinAlg::Zeros<Type>(nInputpar*qdtInputVar, qdtOutputVar);
    this->Input = LinAlg::Matrix<Type>();
    this->Output = LinAlg::Matrix<Type>();
    this->EstOutput = this->Output;
    this->nSample = delay + nInputpar + 1;
    this->InputLinearVector  = LinAlg::Zeros<Type>(this->qdtInputVar, this->nInputpar);
    this->LinearVectorA = LinAlg::Zeros<Type>(this->qdtOutputVar, this->nInputpar+this->delay);
}

template <class Type>
ModelHandler::FIR<Type>::FIR(const ModelHandler::FIR<Type>& OtherFIRModel){
    this->delay                 = OtherFIRModel.delay;
    this->nInputpar             = OtherFIRModel.nInputpar;
    this->qdtInputVar           = OtherFIRModel.qdtInputVar;
    this->qdtOutputVar          = OtherFIRModel.qdtOutputVar;
    this->sampleTime            = OtherFIRModel.sampleTime;
    this->EstOutput             = OtherFIRModel.EstOutput;
    this->Input                 = OtherFIRModel.Input;
    this->input                 = OtherFIRModel.input;
    this->InputLinearVector     = OtherFIRModel.InputLinearVector;
    this->LinearEqualityB       = OtherFIRModel.LinearEqualityB;
    this->LinearEqualityVectorB = OtherFIRModel.LinearEqualityVectorB;
    this->LinearMatrixA         = OtherFIRModel.LinearMatrixA;
    this->LinearVectorA         = OtherFIRModel.LinearVectorA;
    this->lmax                  = OtherFIRModel.lmax;
    this->lmin                  = OtherFIRModel.lmin;
}

// Neste caso Input e Output se forem escalares corresponderão ao próximo valor
// a ser colocado no vetor de saídas ou entradas e sor uma matriz corresponderá
// a um conjunto de variáveis no instante de tempo pedido
//Saida = nº de linhas
template <class Type>
void ModelHandler::FIR<Type>::setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> PastOutput)
{
    this->InputLinearVector.removeColumn(this->InputLinearVector.getNumberOfColumns());
    this->InputLinearVector  =  Input|this->InputLinearVector;
    LinAlg::Matrix<Type> TempLinearVector;

    for(unsigned i = 1; i <= this->InputLinearVector.getNumberOfRows(); ++i)
        TempLinearVector = TempLinearVector | this->InputLinearVector.GetRow(i);

    this->LinearVectorA = TempLinearVector;
}

template <class Type>
void ModelHandler::FIR<Type>::setLinearModel(LinAlg::Matrix<Type> Input,
                                   LinAlg::Matrix<Type> Output)
{
    this->Input = Input;
    this->Output = Output;

    for(nSample = 1; nSample <= this->Output.getNumberOfColumns(); ++nSample)
    {
        this->setLinearVector(Input.GetColumn(nSample),0.0);
        this->LinearMatrixA = this->LinearMatrixA || this->LinearVectorA;
        this->LinearEqualityB = this->LinearEqualityB || ~Output.GetColumn(nSample);
    }
//    std::cout << this->LinearMatrixA;
}

template <class Type>
Type ModelHandler::FIR<Type>::sim(Type input)
{
    this->setLinearVector(input,0.0);
    this->output = (this->LinearVectorA*this->ModelCoef)(1,1);
    return this->output;
}

template <class Type>
Type ModelHandler::FIR<Type>::sim(Type input, Type output)
{
    this->setLinearVector(input, output);
    this->output = (this->LinearVectorA*this->ModelCoef)(1,1);
    return this->output;
}

template <class Type>
std::string ModelHandler::FIR<Type>::print()
{
    return "função não implementada";
}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::FIR<Type>::sim(LinAlg::Matrix<Type> Input)
{
    this->Input  = Input;
    LinAlg::Matrix<Type> TempOutput;

    for(unsigned i = 1; i <= Input.getNumberOfColumns(); ++i){
        this->setLinearVector(Input.GetColumn(i),TempOutput);
        TempOutput = TempOutput|~(this->LinearVectorA*this->ModelCoef);
    }
    this->Output = TempOutput;
    return this->Output;
}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::FIR<Type>::sim(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output)
{
    this->Input  = Input;
    LinAlg::Matrix<Type> TempOutput;

    for(unsigned i = 1; i <= Input.getNumberOfColumns(); ++i){
        this->setLinearVector(Input.GetColumn(i),Output);
        TempOutput = TempOutput|~(this->LinearVectorA*this->ModelCoef);
    }
    this->Output = TempOutput;
    return this->Output;
}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::FIR<Type>::sim(Type lsim, Type lmax, Type step)
{
    return 0.0;
}

template <class Type>
unsigned ModelHandler::FIR<Type>::getNumberOfInputDelays() const{
    return this->nInputpar;
}

template <class Type>
unsigned ModelHandler::FIR<Type>::getNumberOfInputs()const {
    return this->qdtInputVar;
}

template <class Type>
unsigned ModelHandler::FIR<Type>::getNumberOfOutputDelays() const {
    return 0;
}

template <class Type>
unsigned ModelHandler::FIR<Type>::getNumberOfOutputs() const {
    return this->qdtOutputVar;
}

template <class Type>
double ModelHandler::FIR<Type>::getSampleTime() const {
    return this->sampleTime;
}

template <class Type>
unsigned ModelHandler::FIR<Type>::getNumberOfVariables(){
    return this->qdtInputVar*this->nInputpar;
}
