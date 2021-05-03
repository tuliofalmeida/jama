#ifndef __PID_H_INCLUDED
#define __PID_H_INCLUDED

#include "SistemasdeControle/embeddedTools/primitiveLibs/LinAlg/matrix.h"

namespace ControlHandler{
    template <typename Type>
    class PID
    {
    private:
        bool checkUpLim, checkLowLim;
        Type Error, pastError, integralError, derivativeError, Step, kp, ki, kd, upperLimit, lowerLimit, PIDout, inputOperationalPoint;

        inline void errorLimitation();
        inline void intError();
        inline void difError();

    public:
        PID();
        PID(const LinAlg::Matrix<Type> &PIDsParameters, const Type &Step = 1);
        PID(Type kp, Type ki, Type kd, const Type &Step = 1);

        Type getInputOperationalPoint(){return this->inputOperationalPoint;}
        Type getSampleTime() const {return this->Step;}
        Type getErrorValue() const {return this->Error;}
        Type getDerivativeErrorValue() const {return this->derivativeError;}
        Type getIntegralErrorValue() const {return this->integralError;}
        LinAlg::Matrix<Type> getLimits() const;
        LinAlg::Matrix<Type> getParams() const;

        void setInputOperationalPoint(Type inputOperationalPoint){this->inputOperationalPoint = inputOperationalPoint;}
        void setSampleTime(Type Time);
        void setLimits(Type lowerLimit, Type upperLimit);
        void setParams(Type kp, Type ki, Type kd);
        void setParams(const LinAlg::Matrix<Type> &PIDsParameters);
        void resetIntegralValue(){ integralError = 0.0;}

        Type OutputControl(Type Reference, Type SignalInput);
    };

    template<typename Type>
    std::ostream& operator<< (std::ostream& output, ControlHandler::PID<Type> controller);
}

#include "pid.hpp"

#endif // PID_H
