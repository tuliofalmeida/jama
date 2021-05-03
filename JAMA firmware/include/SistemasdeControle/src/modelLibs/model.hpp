#ifdef testModel
    #include "../../../headers/modelLibs/model.h"
#else
    #include "SistemasdeControle/headers/modelLibs/model.h"
#endif


//template <typename Type>
//ModelHandler::Model<Type>::Model(ModelHandler::Model<Type>* InheritedModel)
//{
//    this->step     = 1;
//    this->input    = 0;
//    this->output   = 0;

//    this->InheritedModel = InheritedModel;
//}

template<typename Type>
ModelHandler::Model<Type>::~Model()
{
}

template <typename Type>
void ModelHandler::Model<Type>::setStep(Type step)
{
    this->step = step;
}

template <typename Type>
void ModelHandler::Model<Type>::setModelCoef(LinAlg::Matrix<Type> coef)
{
    this->ModelCoef = coef;
}

template <typename Type>
void ModelHandler::Model<Type>::setIO(LinAlg::Matrix<Type> in, LinAlg::Matrix<Type> out)
{
    this->Input  = in;
    this->EstOutput = out;
    this->Output = out;
}

template <typename Type>
void ModelHandler::Model<Type>::setIO(Type in, Type out)
{
    this->input  = in;
    this->output = out;
    this->estOutput = out;
}

//template <typename Type>
//Type ModelHandler::Model<Type>::getOutput() const
//{
//    return this->output;
//}

template <typename Type>
Type ModelHandler::Model<Type>::getStep() const
{
    return this->step;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getModelCoef() const
{
    return this->ModelCoef;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getInputMatrix() const
{
    return this->Input;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getOutputMatrix() const
{
    return this->Output;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getLinearVectorA() const
{
    return this->LinearVectorA;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getLinearMatrixA() const
{
    return this->LinearMatrixA;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getLinearEqualityB() const
{
    return this->LinearEqualityB;
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::Model<Type>::getLinearEqualityVectorB() const
{
    return this->LinearEqualityVectorB;
}

template <typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* >* ModelHandler::Model<Type>::getLinearSystem() const
{
    LinAlg::Matrix< LinAlg::Matrix<Type>* > *A = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*A)(0,0) = new LinAlg::Matrix<Type>(this->LinearMatrixA.getNumberOfRows(), this->LinearMatrixA.getNumberOfColumns());
    (*A)(0,1) = new LinAlg::Matrix<Type>(this->LinearEqualityB.getNumberOfRows(), this->LinearEqualityB.getNumberOfColumns());
    (*((*A)(0,0))) = this->LinearMatrixA;
    (*((*A)(0,1))) = this->LinearEqualityB;
    return A;
}

template<typename Type>
std::ostream& ModelHandler::operator<< (std::ostream& output, ModelHandler::Model<Type> *model)
{
    output << model->print();
    return output;
}

template<typename Type>
std::string& ModelHandler::operator<< (std::string& output, ModelHandler::Model<Type> *model)
{
    return model->print();
}

template <typename Type>
Type ModelHandler::diff(const ModelHandler::Model<Type> *model, Type x)
{
    return (model->sim(x + model->getStep()) - model->sim(x))/model->getStep();
}
