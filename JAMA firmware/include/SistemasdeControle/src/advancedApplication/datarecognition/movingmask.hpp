#include "SistemasdeControle/headers/advancedApplication/datarecognition/movingmask.h"

template <typename Type>
AdvancedApplication::movingMask<Type>::movingMask(const unsigned &quantidadeVariaveis, const unsigned &tamanho, ModelHandler::Model<Type> *model)
{
    this->quantidadeVariaveis =  quantidadeVariaveis;
    this->tamanho = tamanho;
    this->data2Register = LinAlg::Matrix<unsigned>(quantidadeVariaveis*tamanho,1);

    this->recognitionModel = NULL;
    this->filterModel = model;
    if(this->filterModel){
        this->filterModel = model;
        this->RLSFilter = new OptimizationHandler::RecursiveLeastSquare<Type>(this->filterModel);
    }
}

template <typename Type>
void AdvancedApplication::movingMask<Type>::dataRecognitionRestart()
{
    this->data2Register = -100*LinAlg::Random<unsigned>(quantidadeVariaveis*tamanho,1);
}

template <typename Type>
void AdvancedApplication::movingMask<Type>::dataRecognitionStart(const unsigned &quantidadeVariaveis, const unsigned &tamanho)
{
    this->quantidadeVariaveis =  quantidadeVariaveis;
    this->tamanho = tamanho;
    this->data2Register = LinAlg::Matrix<unsigned>(quantidadeVariaveis*tamanho,1);
}

template <typename Type>
void AdvancedApplication::movingMask<Type>::operator <<(const LinAlg::Matrix<Type> &inputData)
{
//    if(counter >= unsigned(tamanho))
//    {
//        counter = 0;
//        this->data2Register = LinAlg::Matrix<unsigned>(quantidadeVariaveis*tamanho,1);
//    }
//    counter++;

    for(unsigned i = inputData.getNumberOfRows()+1; i <= this->data2Register.getNumberOfRows(); ++i )
        this->data2Register(i-inputData.getNumberOfRows(),1) = this->data2Register(i,1);
    unsigned j = 1;
    for(unsigned i = data2Register.getNumberOfRows()-inputData.getNumberOfRows()+1; i <= this->data2Register.getNumberOfRows(); ++i)
    {
        this->data2Register(i,1) = inputData(j,1);
        ++j;
    }
}

template <typename Type>
LinAlg::Matrix<Type> AdvancedApplication::movingMask<Type>::dataRecognition()
{
    return this->recognitionModel->sim(this->data2Register);
}

template <typename Type>
LinAlg::Matrix<Type> AdvancedApplication::movingMask<Type>::getRecognitionModel() const
{
    return this->recognitionModel->getModelCoef();
}

template <typename Type>
void AdvancedApplication::movingMask<Type>::setRecognitionModel(ModelHandler::Model<Type> *recognitionModel)
{
    this->recognitionModel = recognitionModel;
    this->RLSRecognition = new OptimizationHandler::RecursiveLeastSquare<Type>(recognitionModel,1e12);
}

template <typename Type>
void AdvancedApplication::movingMask<Type>::optimizeRecognitionModel(LinAlg::Matrix<Type> dataOutput)
{
    this->RLSRecognition->Optimize(this->data2Register, dataOutput);
    this->data2Register = LinAlg::Zeros<Type>(this->data2Register.getNumberOfRows(),this->data2Register.getNumberOfColumns());
    counter = 0;
}

template <typename Type>
Type AdvancedApplication::movingMask<Type>::dataRecognition(const LinAlg::Matrix<Type> &defaultData, Type tolerance)
{
    LinAlg::Matrix<Type> TempRegister = defaultData;
    unsigned j = 1;
    for(unsigned i = data2Register.getNumberOfRows()-defaultData.getNumberOfRows()+1; i <= this->data2Register.getNumberOfRows(); ++i)
    {
        TempRegister(j,1) = this->data2Register(i,1);
        ++j;
    }

//    std::cout << (TempRegister|defaultData|(TempRegister-defaultData)) << "\n\n";
//    std::cout << (((~(TempRegister-defaultData))*(TempRegister-defaultData))(1,1)) << "\n\n";
    unsigned match = 0;
    TempRegister = LinAlg::powMatrix(TempRegister-defaultData,2.0);
    for(unsigned i = 1; i <= TempRegister.getNumberOfRows(); ++i)
        if(TempRegister(i,1) <= tolerance)
            match++;

    return(Type(match))/Type(j);
}
template <typename Type>
void AdvancedApplication::movingMask<Type>::filterOptimization(LinAlg::Matrix<Type> data2beFiltered)
{
    if(this->filterMatrix.isNull()){
        this->filterMatrix = LinAlg::Zeros<Type>(data2beFiltered.getNumberOfRows(),1);
        this->filterCounter = 0;
    }

    this->filterCounter++;
    this->filterMatrix = this->filterMatrix + data2beFiltered;
    this->RLSFilter->Optimize(data2beFiltered, this->filterMatrix/filterCounter);

}

template <typename Type>
LinAlg::Matrix<Type> AdvancedApplication::movingMask<Type>::getFilterParameters() const
{
    return filterModel->getModelCoef();
}

template <typename Type>
LinAlg::Matrix<Type> AdvancedApplication::movingMask<Type>::getFilteredData(LinAlg::Matrix<Type> data2beFiltered) const
{
    if(!this->wasDataOptimized)
        return this->filterModel->sim(data2beFiltered);

    return this->filterModel->getLinearVectorA()*filterModel->getModelCoef();
}

template <typename Type>
LinAlg::Matrix<Type> AdvancedApplication::movingMask<Type>::getData() const
{
    return this->data2Register;
}
