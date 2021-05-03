#ifdef testControl
    #include "../../../headers/controlLibs/pid.h"
#else
    #include "SistemasdeControle/headers/controlLibs/pid.h"
#endif

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

    this->Step = 0.1;
    this->upperLimit = 200;
    this->lowerLimit = -200;

    //------------
//    e = LinAlg::Matrix<Type>(1,3);
}

template<typename Type>
ControlHandler::PID<Type>::PID(const LinAlg::Matrix<Type> &PIDsParameters)
{
    this->kp = PIDsParameters(0,0);
    this->ki = PIDsParameters(0,1);
    this->kd = PIDsParameters(0,2);

    this->Error = 0;
    this->derivativeError = 0;
    this->pastError = 0;
    this->integralError = 0;

    this->Step = 0.1;
    this->upperLimit = 200;
    this->lowerLimit = -200;
}

template<typename Type>
void ControlHandler::PID<Type>::errorLimitation()
{
    if(this->PIDout >= this->upperLimit)
    {
        this->checkUpLim = true;
        this->PIDout = this->upperLimit;
    }
    else
        this->checkUpLim = false;

    if(this->PIDout <= this->lowerLimit)
    {
        this->checkLowLim = true;
        this->PIDout = this->lowerLimit;
    }
    else
        this->checkLowLim = false;
}

template<typename Type>
void ControlHandler::PID<Type>::intError()
{
    this->errorLimitation();

    if(!this->checkUpLim && !this->checkLowLim)
        this->integralError += this->Error*this->Step;
}

template<typename Type>
void ControlHandler::PID<Type>::difError()
{
    this->derivativeError = ((this->Error - this->pastError)/this->Step);
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
    this->Step = Time;
}

template<typename Type>
void ControlHandler::PID<Type>::setParams(Type kp, Type ki, Type kd)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}

template<typename Type>
void ControlHandler::PID<Type>::setParams(const LinAlg::Matrix<Type> &PIDsParameters)
{
    this->kp = PIDsParameters(0,0);
    this->ki = PIDsParameters(0,1);
    this->kd = PIDsParameters(0,2);
}

template<typename Type>
Type ControlHandler::PID<Type>::OutputControl(Type Reference, Type SignalInput)
{
    this->Error = Reference - SignalInput;

    difError();
    intError();
    this->PIDout = (this->kp*this->Error + this->ki*this->integralError + this->kd*this->derivativeError);
    errorLimitation();

//    e.removeColumn(3);
//    e = LinAlg::Matrix<Type>(this->Error)|e;
//    K1 = kp + this->Step*ki + kd/this->Step;
//    K2 = -kp - 2*kd/this->Step;
//    K3 = kd/this->Step;
//    this->PIDout = this->PIDout + (K1*e(1,1) + K2*e(1,2) + K3*e(1,3));
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
    params(0,1) = this->ki;
    params(0,2) = this->kd;

    return params;
}

template<typename Type> // ok
std::ostream& ControlHandler::operator<< (std::ostream& output, ControlHandler::PID<Type> controller)
{
    std::string str; str << controller;
    output << str;
    return output;
}
#include <string>
template<typename Type> //ok
std::string&  ControlHandler::operator<< (std::string& output,  const ControlHandler::PID<Type> &controller)
{
    LinAlg::Matrix<Type> parameters = controller.getParams();

    output = "U(s) = ";
    if(parameters(0,0) != 0)
    {
        std::stringstream ss;
        if(parameters(0,0) != 1)
        {
            ss << parameters(0,0);
            output += ss.str();
        }
        output += " E(s)";
    }
    if(parameters(0,1) != 0)
    {
        output += " + ";
        std::stringstream ss;
        if(parameters(0,1) != 1)
        {
            ss << parameters(0,1);
            output += ss.str();
        }
        output += " (E(s)/s)";
    }
    if(parameters(0,2) != 0)
    {
        output += " + ";
        std::stringstream ss;
        if(parameters(0,2) != 1)
        {
            ss << parameters(0,2);
            output += ss.str();
        }
        output += " s E(s) ";
    }
    return output;
}

