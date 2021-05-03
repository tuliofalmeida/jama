#include "rna.h"

template <typename Type>
ModelHandler::RNA<Type>::RNA()
{
}

template <typename Type>
ModelHandler::RNA<Type>::RNA(unsigned InputSize,
                             unsigned HidderSize,
                             unsigned OutputSize,
                             const NeuralNetworkHandler::Neuron<ModelHandler::Type> &Neuron)
{
    this->neuron = Neuron;

    this->inLayer = LinAlg::Zeros<Type>(InputSize,1);
    this->hiddLayer = LinAlg::Zeros<Type>(HidderSize,1);
    this->outLayer = LinAlg::Zeros<Type>(OutputSize,1);
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::RNA<Type>::sim(LinAlg::Matrix<Type> x)
{

    this->inWeight = LinAlg::Random<Type>(x.getNumberOfRows(),1);
    this->hidWeight = LinAlg::Random<Type>(this->inLayer.getNumberOfRows(),this->hiddLayer.getNumberOfRows());
    this->outWeight = LinAlg::Random<Type>(this->hiddLayer.getNumberOfRows(),this->outLayer.getNumberOfRows());

    for(unsigned i = 1; i <= this->inLayer.getNumberOfRows(); ++i)
      this->inLayer(i,1) = this->neuron.sim(x,this->inWeight.GetColumn(i),1);

    for(unsigned i = 1; i <= this->hiddLayer.getNumberOfRows(); ++i)
      this->hiddLayer(i,1) = this->neuron.sim(this->inLayer,this->hidWeight.GetColumn(i),1);

    for(unsigned i = 1; i <= this->outLayer.getNumberOfRows(); ++i)
      this->outLayer(i,1) = this->neuron.sim(this->hiddLayer,this->outWeight.GetColumn(i),1);

}
