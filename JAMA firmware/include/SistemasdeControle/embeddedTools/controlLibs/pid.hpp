#include "pid.h"

template<typename Type>
ControlHandler::PID<Type>::PID()
{
    this->kd = 0;
    this->ki = 0;
    this->kp = 0;

    this->Error = 0;
    this->derivativeError = 0;
    this->pastError = 0;
    this->integralError = 0;

    this->Step = 1;
    //this->upperLimit = 200; 
    //this->lowerLimit = -200;
    this->upperLimit = 20 / this->Step;// ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.;
    this->lowerLimit = -20/ this->Step;// ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação;
    this->inputOperationalPoint = 0;
}

template<typename Type>
ControlHandler::PID<Type>::PID(Type kp, Type ki, Type kd, const Type &Step)
{
    this->Step = Step;
    this->kp = kp;
    this->ki = ki * this->Step; // ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.
    if(!this->Step)
        this->Step = 1;

    this->kd = kd / this->Step; // ajustei para que Kd seja dividido pelo step. Isso vai diminuir em 1 divisão.
    
    this->Error = 0;
    this->derivativeError = 0;
    this->pastError = 0;
    this->integralError = 0;
    this->upperLimit = 20 / this->Step;// ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.;
    this->lowerLimit = -20/ this->Step;// ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação;
    this->inputOperationalPoint = 0;
}

template<typename Type>
ControlHandler::PID<Type>::PID(const LinAlg::Matrix<Type> &PIDsParameters, const Type &Step)
{
    this->Step = Step;
    this->kp = PIDsParameters(0,0);
    this->ki = PIDsParameters(0,1) * this->Step; // ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.
    if(!this->Step)
        this->Step = 1;

    this->kd = PIDsParameters(0,2) / this->Step; // ajustei para que Kd seja dividido pelo step. Isso vai diminuir em 1 divisão.
    
    this->Error = 0;
    this->derivativeError = 0;
    this->pastError = 0;
    this->integralError = 0;
    this->upperLimit = 20 / this->Step;// ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.;
    this->lowerLimit = -20/ this->Step;// ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação;
    this->inputOperationalPoint = 0;
}

template<typename Type>
void ControlHandler::PID<Type>::errorLimitation()
{
    if(this->PIDout >= this->upperLimit)
    {
        //std::cout << "PIDU: " << this->PIDout << "\n";
        this->checkUpLim = true;
        this->PIDout = this->upperLimit;
    }
    else
        this->checkUpLim = false;

    if(this->PIDout <= this->lowerLimit)
    {
        //std::cout << "PIDL: " << this->PIDout << "\n";
        this->checkLowLim = true;
        this->PIDout = this->lowerLimit;
    }
    else
        this->checkLowLim = false;
    // std::cout << "UUL: " << this->upperLimit << " LLL:" << this->lowerLimit << "\n";
    // std::cout << "LL: " << this->checkLowLim << " UL:" << this->checkUpLim << "\n";
}

template<typename Type>
void ControlHandler::PID<Type>::intError()
{
    this->errorLimitation();

    if(!this->checkUpLim && !this->checkLowLim)
        //this->integralError += this->Error*this->Step;
        this->integralError += 0.01*this->Error; // ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.
}

template<typename Type>
void ControlHandler::PID<Type>::difError()
{
    //this->derivativeError = ((this->Error - this->pastError)/this->Step);
    this->derivativeError = ((this->Error - this->pastError)); // ajustei para que Kd seja dividido pelo step. Isso vai diminuir em 1 divisão.
    this->pastError = this->Error;
}

template<typename Type>
void ControlHandler::PID<Type>::setLimits(Type lowerLimit, Type upperLimit)
{
    this->upperLimit = upperLimit;
    this->lowerLimit = lowerLimit;
}

template<typename Type>
void ControlHandler::PID<Type>::setSampleTime(Type Time)
{
    this->ki = ki / this->Step; // ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.
    this->kd = kd * this->Step; // ajustei para que Kd seja dividido pelo step. Isso vai diminuir em 1 divisão.

    this->Step = Time;

    this->ki = ki * this->Step; // ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.
    this->kd = kd / this->Step; // ajustei para que Kd seja dividido pelo step. Isso vai diminuir em 1 divisão.
    
}

template<typename Type>
void ControlHandler::PID<Type>::setParams(Type kp, Type ki, Type kd)
{
    this->kp = kp;
    //this->ki = ki;
    //this->kd = kd;
    this->ki = ki * this->Step; // ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.
    this->kd = kd / this->Step; // ajustei para que Kd seja dividido pelo step. Isso vai diminuir em 1 divisão.
}

template<typename Type>
void ControlHandler::PID<Type>::setParams(const LinAlg::Matrix<Type> &PIDsParameters)
{
    this->kp = PIDsParameters(0,0);
    //this->ki = PIDsParameters(0,1);
    //this->kd = PIDsParameters(0,2);
    this->ki = PIDsParameters(0,1) * this->Step; // ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.
    this->kd = PIDsParameters(0,2) / this->Step; // ajustei para que Kd seja dividido pelo step. Isso vai diminuir em 1 divisão.
    
}

template<typename Type>
Type ControlHandler::PID<Type>::OutputControl(Type Reference, Type SignalInput)
{
    this->Error = Reference - SignalInput;
    std::cout << "E: " << this->Error << " IE:" << this->integralError << "\n";
    //difError();
    intError();
    //std::cout << "kp: " << this->kp << " ki:" << this->ki <<  "\n";
    this->PIDout = (this->kp*this->Error + this->ki*this->integralError) + this->kd*this->derivativeError;
    errorLimitation();
    
    return this->PIDout;
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::PID<Type>::getLimits() const
{
    LinAlg::Matrix<Type> limits(1,2);

    limits(0,0) = this->lowerLimit;
    limits(0,1) = this->upperLimit;

    return limits;
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::PID<Type>::getParams() const
{
    LinAlg::Matrix<Type> params(1,3);

    params(0,0) = this->kp;
    //params(0,1) = this->ki;
    //params(0,2) = this->kd;
    params(0,1) = this->ki / this->Step; // ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.
    params(0,2) = this->kd * this->Step; // ajustei para que Kd seja dividido pelo step. Isso vai diminuir em 1 divisão.
    return params;
}

template<typename Type>
std::ostream& ControlHandler::operator<< (std::ostream& output, ControlHandler::PID<Type> controller)
{
    LinAlg::Matrix<Type> parameters = controller.getParams();

    output << "U(s) = ";
    if(parameters(0,0) != 0)
    {
        if(parameters(0,0) != 1)
            output << parameters(0,0);
        output << " E(s)";
    }
    if(parameters(0,1) != 0)
    {
        output << " + ";
        if(parameters(0,1) != 1)
            //output << parameters(0,1);
            output << parameters(0,1) / controller.getSampleTime(); // ajustei para que Ki seja multiplicado pelo step. Isso vai diminuir em 1 multiplicação.
        output << " (E(s)/s)";
    }
    if(parameters(0,2) != 0)
    {
        output << " + ";
        if(parameters(0,2) != 1)
            //output << parameters(0,2);
            output << parameters(0,2) * controller.getSampleTime(); // ajustei para que Kd seja dividido pelo step. Isso vai diminuir em 1 divisão.
        output << " s E(s) ";
    }
    return output;
}


