#include "SistemasdeControle/headers/modelLibs/nfir.h"

template <class Type>
ModelHandler::NFIR<Type>::NFIR(unsigned nInputpar, unsigned degree,
                             unsigned delay,
                             unsigned qdtInputVar, unsigned qdtOutputVar,
                             double sampleTime)
{
    this->delay        = delay;
    this->degree       = degree;
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
ModelHandler::NFIR<Type>::NFIR(const ModelHandler::NFIR<Type>& OtherNFIRModel){
    this->delay                 = OtherNFIRModel.delay;
    this->degree                = OtherNFIRModel.degree;
    this->nInputpar             = OtherNFIRModel.nInputpar;
    this->qdtInputVar           = OtherNFIRModel.qdtInputVar;
    this->qdtOutputVar          = OtherNFIRModel.qdtOutputVar;
    this->sampleTime            = OtherNFIRModel.sampleTime;
    this->EstOutput             = OtherNFIRModel.EstOutput;
    this->Input                 = OtherNFIRModel.Input;
    this->input                 = OtherNFIRModel.input;
    this->InputLinearVector     = OtherNFIRModel.InputLinearVector;
    this->LinearEqualityB       = OtherNFIRModel.LinearEqualityB;
    this->LinearEqualityVectorB = OtherNFIRModel.LinearEqualityVectorB;
    this->LinearMatrixA         = OtherNFIRModel.LinearMatrixA;
    this->LinearVectorA         = OtherNFIRModel.LinearVectorA;
    this->lmax                  = OtherNFIRModel.lmax;
    this->lmin                  = OtherNFIRModel.lmin;
}

// Neste caso Input e Output se forem escalares corresponderão ao próximo valor
// a ser colocado no vetor de saídas ou entradas e sor uma matriz corresponderá
// a um conjunto de variáveis no instante de tempo pedido
//Saida = nº de linhas
template <class Type>
void ModelHandler::NFIR<Type>::setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> PastOutput)
{
    this->InputLinearVector.removeColumn(this->InputLinearVector.getNumberOfColumns());
    this->InputLinearVector  =  Input|this->InputLinearVector;
    LinAlg::Matrix<Type> TempLinearVector1, TempLinearVector;

    for(unsigned i = 1; i <= this->InputLinearVector.getNumberOfRows(); ++i)
        TempLinearVector1 = TempLinearVector1 | this->InputLinearVector.GetRow(i);

    for(unsigned j = 1; j <= this->degree; ++j)
        TempLinearVector = TempLinearVector| LinAlg::powMatrix(TempLinearVector1, Type(this->degree));
    this->LinearVectorA = TempLinearVector;
}

template <class Type>
void ModelHandler::NFIR<Type>::setLinearModel(LinAlg::Matrix<Type> Input,
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
Type ModelHandler::NFIR<Type>::sim(Type input)
{
    this->setLinearVector(input,0.0);
    this->output = (this->LinearVectorA*this->ModelCoef)(1,1);
    return this->output;
}

template <class Type>
Type ModelHandler::NFIR<Type>::sim(Type input, Type output)
{
    this->setLinearVector(input, output);
    this->output = (this->LinearVectorA*this->ModelCoef)(1,1);
    return this->output;
}

template <class Type>
std::string ModelHandler::NFIR<Type>::print()
{
    return "função não implementada";
}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::NFIR<Type>::sim(LinAlg::Matrix<Type> Input)
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
LinAlg::Matrix<Type> ModelHandler::NFIR<Type>::sim(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output)
{
//    this->Input  = Input;
//    this->Output = LinAlg::Zeros<Type>(1, this->qdtOutputVar);

//    for(unsigned i = 1; i < Input.getNumberOfColumns(); ++i){
//        this->setLinearVector(Input(from(1) --> Input.getNumberOfRows(), i), Output(from(1) --> Output.getNumberOfRows(), i));
//        this->Output = this->Output | this->LinearVectorA*this->ModelCoef;
//    }
    return this->Output;
}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::NFIR<Type>::sim(Type lsim, Type lmax, Type step)
{
    return 0.0;
}

template <class Type>
unsigned ModelHandler::NFIR<Type>::getNumberOfInputDelays() const{
    return this->nInputpar;
}

template <class Type>
unsigned ModelHandler::NFIR<Type>::getNumberOfInputs()const {
    return this->qdtInputVar;
}

template <class Type>
unsigned ModelHandler::NFIR<Type>::getNumberOfOutputDelays() const {
    return 0;
}

template <class Type>
unsigned ModelHandler::NFIR<Type>::getNumberOfOutputs() const {
    return this->qdtOutputVar;
}

template <class Type>
double ModelHandler::NFIR<Type>::getSampleTime() const {
    return this->sampleTime;
}

template <class Type>
unsigned ModelHandler::NFIR<Type>::getNumberOfVariables(){
    return this->qdtInputVar*this->nInputpar*this->degree;
}
