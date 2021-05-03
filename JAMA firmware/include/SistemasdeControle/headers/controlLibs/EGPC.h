#ifndef __EGPC_H_INCLUDED
#define __EGPC_H_INCLUDED

#include "explicityController.h"

namespace ControlHandler{
	template <typename Type>
    class EGPC : public ExplicityController<Type>
    {
    public:
        EGPC(const uint8_t &nInputDelay, const uint8_t &nOutputDelay, const uint8_t &nInput, const uint8_t &nOutput);
        LinAlg::Matrix<Type> outputControlActionsCalc(LinAlg::Matrix<Type> Reference, LinAlg::Matrix<Type> SignalInput); // implementa uma função obrigatória para herdar MP_General_Controller. É a única função que deve ser chamada no loop.
        LinAlg::Matrix<Type> outputControlActionsCalc(LinAlg::Matrix<Type> Reference, LinAlg::Matrix<Type> SignalInput, LinAlg::Matrix<Type> States){}

    protected:
        Type inputSize;
        LinAlg::Matrix<Type> freeDU, freeY, Input, Reference;
        void setStates(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);
    };
}

#ifdef testControl
    #include "../../../src/controlLibs/EGPC.hpp"
#else
    #include "SistemasdeControle/src/controlLibs/EGPC.hpp"
#endif
#endif
