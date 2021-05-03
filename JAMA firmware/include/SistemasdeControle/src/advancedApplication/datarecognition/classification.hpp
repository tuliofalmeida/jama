#include "SistemasdeControle/headers/advancedApplication/datarecognition/classification.h"

template <typename Type>
AdvancedApplication::Classification<Type>::Classification(ModelHandler::Model<Type> *model, Type tolerance)
{
    this->model = model;
    this->error = LinAlg::Zeros<Type>(this->model->getNumberOfOutputs(),1);
    this->tolerance = tolerance;
    this->classificationMask = 0;
}

template <typename Type>
void AdvancedApplication::Classification<Type>::dataRegistration(const LinAlg::Matrix<Type> &data2Register)
{
    this->RLS = new OptimizationHandler::RecursiveLeastSquare<double>(this->model);
    for(unsigned i = 1; i <= data2Register.getNumberOfColumns()-2; ++i)
        this->RLS->Optimize(data2Register.GetColumn(i), data2Register.GetColumn(i+1));
    this->classificationMask = 0;
    this->dataSizeRegistered = data2Register.getNumberOfColumns()-2;
}

template <typename Type>
void AdvancedApplication::Classification<Type>::dataRecognitionStart(LinAlg::Matrix<Type> data2beRecognized)
{
    this->data2Register = data2beRecognized|LinAlg::Zeros<Type>(this->model->getNumberOfOutputs(),1);
}

template <typename Type>
double AdvancedApplication::Classification<Type>::dataRecognition(LinAlg::Matrix<Type> data2beRecognized)
{
    this->data2Register.removeColumn(2);
    this->data2Register = data2beRecognized|this->data2Register;
    this->Output = this->model->sim(this->data2Register.GetColumn(2));
    this->error  = this->data2Register.GetColumn(1) - Output /*+ 0.95*this->error*/;

    if(((~this->error)*this->error)(1,1) < this->tolerance){
        ++this->classificationMask;
        if(this->classificationMask >= this->dataSizeRegistered-this->dataSizeRegistered*0.1)
          this->classificationMask = 0;
    }else{
        --this->classificationMask;
        if(this->classificationMask < 0)
            this->classificationMask = 0;
    }
    return double(this->classificationMask)/double(this->dataSizeRegistered);
}


