#ifndef __MPPID_H_INCLUDED
#define __MPPID_H_INCLUDED

#include "explicityController.h"

namespace ControlHandler{
	template <typename Type>
    class MP_PID : public ExplicityController<Type>
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

#ifdef testControl
    #include "../../../src/controlLibs/mp_pid.hpp"
#else
    #include "SistemasdeControle/src/controlLibs/mp_pid.hpp"
#endif
#endif
