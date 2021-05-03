#include "mp_pid.h"

template<typename Type>
void ControlHandler::MP_PID<Type>::intError()
{
    this->integralError += this->error*this->step;
}

template<typename Type>
void ControlHandler::MP_PID<Type>::difError()
{
    this->derivativeError = ((this->error - this->pastError)/this->step);
    this->pastError = this->error;
}

template<typename Type>
Type ControlHandler::MP_PID<Type>::OutputControl(Type Reference, Type SignalInput)
{
    this->error = Reference - SignalInput;

    this->difError();
    this->intError();

    LinAlg::Matrix<Type> state(3,1); state(0,0) = this->integralError;
    state(1,0) = this->error; state(2,0) = this->derivativeError;

    if(this->isInside(state))
    {
    	this->ki   = this->controllerParameters[this->inWitchRegion](0,0);
    	this->kp   = this->controllerParameters[this->inWitchRegion](0,1);
    	this->kd   = this->controllerParameters[this->inWitchRegion](0,2);
    	this->bias = this->controllerParameters[this->inWitchRegion](0,3);

    	this->PIDout = (this->kp*this->error + this->ki*this->integralError + this->kd*this->derivativeError + this->bias);
    }
    else
    	std::cout << "Valor enviado nao pertence ao conjunto de restricoes!" << std::endl;

    return this->PIDout;
}

