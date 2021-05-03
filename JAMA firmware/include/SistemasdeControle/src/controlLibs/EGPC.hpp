#ifdef testControl
    #include "../../../headers/controlLibs/EGPC.h"
#else
    #include "SistemasdeControle/headers/controlLibs/EGPC.h"
#endif

template<typename Type>
ControlHandler::EGPC<Type>::EGPC(const uint8_t &nInputDelay, const uint8_t &nOutputDelay,
                                 const uint8_t &nInput,      const uint8_t &nOutput)
{
    this->inputSize = nInput;
    this->freeY  = LinAlg::Zeros<Type>(nOutput, nOutputDelay+1);
    this->freeDU = LinAlg::Zeros<Type>(nInput , nInputDelay-1);
    this->states = LinAlg::Matrix<Type>(nInput +
                                        nInput*nInputDelay+
                                        nOutput*(nOutputDelay),1);
    this->stateSize = nInput +
            nInput*nInputDelay+
            nOutput*(nOutputDelay);
    this->Input = LinAlg::Zeros<Type>(nInput , 1);
}

template <typename Type>
void ControlHandler::EGPC<Type>::setStates(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output)
{
    this->freeDU =  Input |this->freeDU;
    this->freeY  =  Output|this->freeY;
    this->freeDU.removeColumn(this->freeDU.getNumberOfColumns()-1);
    this->freeY.removeColumn(this->freeY.getNumberOfColumns()-1);
    uint16_t pos = 0;

    for(uint16_t j = 0; j < this->Input.getNumberOfRows(); ++j){
        this->states(pos,0) = this->Input(j,0);
        pos++;
    }

    for(uint16_t i = 0; i < this->freeDU.getNumberOfRows(); ++i)
        for(uint16_t j = 0; j < this->freeDU.getNumberOfColumns(); ++j){
            this->states(pos,0) = this->freeDU(i,j);
            pos++;
        }

    for(uint16_t i = 0; i < this->freeY.getNumberOfColumns(); ++i)
        for(uint16_t j = 0; j < this->freeY.getNumberOfRows(); ++j){
            this->states(pos,0) = this->freeY(j,i);
            pos++;
        }
    for(uint16_t j = 0; j < this->Reference.getNumberOfColumns(); ++j){
        this->states(pos,0) = this->Reference(0,j);
        pos++;
    }
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::EGPC<Type>::outputControlActionsCalc(LinAlg::Matrix<Type> Reference, LinAlg::Matrix<Type> SignalInput)
{
    this->Reference  = Reference;
    this->setStates(Input, SignalInput);
    if(this->isInside(this->states)){ // Verifica em qual poliedro os estados estão (inWhitchRegion).
        for(uint16_t j = 0; j < this->inputSize; ++j){
            this->Input(j,0) = 0;
            for(uint16_t i = 0; i < this->stateSize; ++i)
                this->Input(j,0) += this->controllerParameters[this->inWitchRegion](j,i)*this->states(i,0);
            this->Input(j,0) += this->controllerParameters[this->inWitchRegion](j,this->stateSize);
        }
    }
    else //Esse caso não deve acontecer exceto que o sistema seja iniciado de maneira errada.
    	std::cout << "Valor enviado nao pertence ao conjunto de restricoes!" << std::endl;

    return this->Input;
}

