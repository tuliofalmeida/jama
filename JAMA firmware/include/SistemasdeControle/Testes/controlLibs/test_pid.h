#ifndef __PID_H_INCLUDED
#define __PID_H_INCLUDED

#include <cmath>

namespace ControlHandler{
    template <typename Type>
    class PID
    {
    private:
        bool checkUpLim, checkLowLim;
        Type Error, pastError, integralError, derivativeError, Step, kp, ki, kd, upperLimit, lowerLimit, PIDout;

        void antReset();

        void intError();
        void difError();

    public:
        PID();

        void setSampleTime(Type Time);
        void setLimits(Type upperLimit, Type lowerLimit);
        void setParams(Type kp, Type ki, Type kd);
        void setParams(const LinAlg::Matrix<Type> &PIDsParameters);

        Type OutputControl(Type Reference, Type SignalInput);
    };
}

#include "SistemasdeControle/src/controlLibs/pid.hpp"
#endif // PID_H
