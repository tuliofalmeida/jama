#ifndef __MPPID_H_INCLUDED
#define __MPPID_H_INCLUDED

#include "matrix.h"
#include "mp_general_controller.h"

namespace ControlHandler{
	template <typename Type>
    class MP_PID : public MP_General_Controller<Type>
    {
	public:
		MP_PID(){}

    	Type OutputControl(Type Reference, Type SignalInput);

    protected:
    	Type step, error, pastError, integralError, derivativeError, PIDout, kp, ki, kd, bias;
    	
    	void intError(void);
        void difError(void);
	};
}

#include "mp_pid.hpp"
#endif