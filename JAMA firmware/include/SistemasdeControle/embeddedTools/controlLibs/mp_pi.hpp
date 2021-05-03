#include "mp_pi.h"

template<typename Type>
void ControlHandler::MP_PI<Type>::intError()
{
    this->integralError += this->error*this->step; // Calcula a integral do erro. Esse "estado" é necessário (obrigatório) para o uso da invariância positiva.
}

template<typename Type>
Type ControlHandler::MP_PI<Type>::OutputControl(Type Reference, Type SignalInput)
{
    this->error = Reference - SignalInput; // Calcula o erro. OBS: Esse estado é obrigatório para encontrar o PI que será utilizado em uma iteração.

    this->intError(); // Calcula o erro integral. OBS: Esse estado é obrigatório para encontrar o PI que será utilizado em uma iteração.

    LinAlg::Matrix<Type> state(2,1); state(0,0) = this->integralError; // Cria o vetor de estados que será utilizado para calcular qual PI será usado.
    state(1,0) = this->error;
//    std::cout << "Estado interno: \n" << state(0,0) << ';' << state(1,0) << std::endl;
    if(this->isInside(state)) // Verifica em qual poliedro os estados estão (inWhitchRegion).
    {
        //Usa o PI apropriado para a região específica do conjunto.
    	this->ki   = this->controllerParameters[this->inWitchRegion](0,0);
    	this->kp   = this->controllerParameters[this->inWitchRegion](0,1);
        this->bias = this->controllerParameters[this->inWitchRegion](0,2);

        //Calcula o sinal de controle.
    	this->PIout = (this->kp*this->error + this->ki*this->integralError + this->bias);
    }
    else //Esse caso não deve acontecer exceto que o sistema seja iniciado de maneira errada.
    	std::cout << "Valor enviado nao pertence ao conjunto de restricoes!" << std::endl;

    return this->PIout;
}

