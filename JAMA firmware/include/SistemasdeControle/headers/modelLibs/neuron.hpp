#include "neuron.h"

template <typename Type>
NeuralNetworkHandler::Neuron<Type>::Neuron()
{
    this->min = 0;
    this->max = 0;
    this->coef = 0;

    this->ActivationFunctionVariables = 0;
    this->Bias = 1;
    this->Output = 0;
    this->Input = LinAlg::Zeros<Type>(1,1);
    this->Weight = LinAlg::Zeros<Type>(1,1);
}

template <typename Type>
NeuralNetworkHandler::Neuron<Type>::Neuron(std::string ActiveFunctionType, Type coef, Type min, Type max)
{
    this->ActiveFunctionType = ActiveFunctionType;

    this->min = min;
    this->max = max;
    this->coef = coef;

    this->Bias = 1;
    this->Output = 0;
    this->Input = LinAlg::Zeros<Type>(1,1);
    this->Weight = LinAlg::Zeros<Type>(1,1);
    this->ActivationFunctionVariables = LinAlg::Zeros<Type>(1,1);
}

template <typename Type>
NeuralNetworkHandler::Neuron<Type>::~Neuron()
{

}

template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::sim(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Weight, Type Bias){

    Type tempOutput = 0;

    if(Input.getNumberOfRows() < Input.getNumberOfColumns() || Weight.getNumberOfRows() < Weight.getNumberOfColumns())
        std::cout<<"As dimensoes nao batem. Impossivel realizar operacao."<<std::endl;
    else{
        this->Input = Input;
        this->Weight = Weight;
        this->Bias = Bias;

        tempOutput = ((~this->Input * this->Weight) - this->Bias)(1,1);
        //std::cout<<tempOutput<<std::endl;

        if(this->ActiveFunctionType == "Signal")
            this->Output = this->Signal(tempOutput);
        else if(this->ActiveFunctionType == "HardLimit")
            this->Output = this->HardLimit(tempOutput);
        else if(this->ActiveFunctionType == "Linear")
            this->Output = this->Linear(tempOutput);
        else if(this->ActiveFunctionType == "PositiveLinear")
            this->Output = this->PositiveLinear(tempOutput);
        else if(this->ActiveFunctionType == "SymmetricLinear")
            this->Output = this->SymmetricLinear(tempOutput);
        else if(this->ActiveFunctionType == "SaturatingLinear")
            this->Output = this->SaturatingLinear(tempOutput);
        else if(this->ActiveFunctionType == "Gaussian")
            this->Output = this->Gaussian(tempOutput);
        else if(this->ActiveFunctionType == "Multiquadrics")
            this->Output = this->Multiquadrics(tempOutput);
        else if(this->ActiveFunctionType == "InverseMultiquadrics")
            this->Output = this->InverseMultiquadrics(tempOutput);
        else if(this->ActiveFunctionType == "Sigmoid")
            this->Output = this->Sigmoid(tempOutput);
        else if(this->ActiveFunctionType == "HyperbolicTangentSigmoid")
            this->Output = this->HyperbolicTangentSigmoid(tempOutput);
        else{
            std::cout<<"Metodo nao encontrado"<<std::endl;
            this->Output = tempOutput;
        }
        return Output;
    }
    return 0;
}

template <typename Type>
LinAlg::Matrix<Type> NeuralNetworkHandler::Neuron<Type>::GetActivationFunctionVariables(){
    return this->ActivationFunctionVariables;
}

template <typename Type>
LinAlg::Matrix<Type> NeuralNetworkHandler::Neuron<Type>::GetInput(){
    return this->Input;
}

template <typename Type>
LinAlg::Matrix<Type> NeuralNetworkHandler::Neuron<Type>::GetWeight(){
    return this->Weight;
}

template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::GetOutput(){
    return this->Output;
}

template <typename Type>
void NeuralNetworkHandler::Neuron<Type>::SetActivationFunctionVariables(const LinAlg::Matrix<Type> &ActivationFunctionVariables){
    this->ActivationFunctionVariables = ActivationFunctionVariables;
}

template <typename Type>
void NeuralNetworkHandler::Neuron<Type>::SetBias(const Type &Bias){
    this->Bias = Bias;
}

template <typename Type>
void NeuralNetworkHandler::Neuron<Type>::SetInput(const LinAlg::Matrix<Type> &Input){
    this->Input = Input;
}

template <typename Type>
void NeuralNetworkHandler::Neuron<Type>::SetOutput(const Type &Output){
    this->Output = Output;
}

template <typename Type>
void NeuralNetworkHandler::Neuron<Type>::SetWeight(const LinAlg::Matrix<Type> &Weight){
    this->Weight = Weight;
}


template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::Signal(const Type &value){
    if(value < this->min)
        return -1;
    else
        return 1;
}

template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::HardLimit(const Type &value){
    if(value < this->min)
        return 0;
    else
        return 1;
}

template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::Linear(const Type &value){
    return value;
}

template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::PositiveLinear(const Type &value){
    if(value < 0)
        return 0;
    else
        return value;
}

template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::SymmetricLinear(const Type &value){
    if(value < this->min)
        return this->min;
    else if(value > this->max)
        return this->max;
    else
        return value;
}

template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::SaturatingLinear(const Type &value){
    if(value < this->min)
        return this->min;
    else if(value > this->max)
        return this->max;
    else
        return value;
}

template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::Gaussian(const Type &value){
    return exp(-((pow(value,2))/(2*pow(this->coef,2))));
}

template<typename Type>
Type NeuralNetworkHandler::Neuron<Type>::Multiquadrics(const Type &value){
    return pow(pow(value,2)+pow(this->coef,2),1/2);
}

template<typename Type>
Type NeuralNetworkHandler::Neuron<Type>::InverseMultiquadrics(const Type &value){
    return 1/Multiquadrics(value);
}

template<typename Type>
Type NeuralNetworkHandler::Neuron<Type>::Sigmoid(const Type &value){
    return 2/((1 + exp(-this->coef*value))-1);
}

template <typename Type>
Type NeuralNetworkHandler::Neuron<Type>::HyperbolicTangentSigmoid(const Type &value){
    return (exp(this->coef*value) - exp(-this->coef*value))/(exp(this->coef*value) + exp(-this->coef*value));
}
