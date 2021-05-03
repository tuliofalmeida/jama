#ifndef __MPPI_H_INCLUDED
#define __MPPI_H_INCLUDED

#include "explicityController.h"

namespace ControlHandler{
	template <typename Type>
    class MP_PI : public ExplicityController<Type>
    {
    public:
        MP_PI(){this->step = 0.1; error = 1.0; integralError = 1.0;} //seta os parâmetros iniciais do controlador PI. Período de amostragem (step), erro e integral do erro.

        LinAlg::Matrix<Type> outputControlActionsCalc(LinAlg::Matrix<Type> Reference, LinAlg::Matrix<Type> SignalInput); // implementa uma função obrigatória para herdar MP_General_Controller. É a única função que deve ser chamada no loop.
        LinAlg::Matrix<Type> outputControlActionsCalc(LinAlg::Matrix<Type> Reference, LinAlg::Matrix<Type> SignalInput, LinAlg::Matrix<Type> States){}
    protected:
    	Type step, error, integralError, PIout, kp, ki, kd, bias; //Atributos de um controlador PI
    	
    	void intError(void); //Método para calcular a integral do erro. OBS: Para calcular o pertencimento dos estados no conjunto invariante é necessário ter o PI calculado dessa forma. Não deve mudar a maneira como o cálculo é realizado.
	};
}

#ifdef testControl
    #include "../../../src/controlLibs/mp_pi.hpp"
#else
    #include "SistemasdeControle/src/controlLibs/mp_pi.hpp"
#endif
#endif
