#ifndef __MPPI_H_INCLUDED
#define __MPPI_H_INCLUDED

#include "matrix.h"
#include "mp_general_controller.h"

namespace ControlHandler{
	template <typename Type>
    class MP_PI : public MP_General_Controller<Type>
    {
    public:
        MP_PI(){this->step = 0.1; error = 1.0; integralError = 1.0;} //seta os parâmetros iniciais do controlador PI. Período de amostragem (step), erro e integral do erro.

        Type OutputControl(Type Reference, Type SignalInput); // implementa uma função obrigatória para herdar MP_General_Controller. É a única função que deve ser chamada no loop.

    protected:
    	Type step, error, integralError, PIout, kp, ki, kd, bias; //Atributos de um controlador PI
    	
    	void intError(void); //Método para calcular a integral do erro. OBS: Para calcular o pertencimento dos estados no conjunto invariante é necessário ter o PI calculado dessa forma. Não deve mudar a maneira como o cálculo é realizado.
	};
}

#include "mp_pi.hpp"
#endif
