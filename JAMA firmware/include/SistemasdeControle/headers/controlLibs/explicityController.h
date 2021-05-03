#ifndef MPGENERALCONTROLLER_H_INCLUDED
#define MPGENERALCONTROLLER_H_INCLUDED

#ifdef testControl
    #include "../../../headers/modelLibs/transferfunction.h"
#else
    #include "SistemasdeControle/headers/modelLibs/transferfunction.h"
#endif

namespace ControlHandler{
	template <typename Type>
    class ExplicityController
    {
    public:
        ExplicityController(){}

        std::string setConstraints(std::string Constraints); // Recebe uma string com R no final de cada conjunto de restrições. Converte cada trecho do início até encontrar o R em uma matriz e deleta o trecho da string.
        void setConstraints(const LinAlg::Matrix<Type> *Constraints, const unsigned &size); // Recebe uma string com R no final de cada conjunto de restrições. Converte cada trecho do início até encontrar o R em uma matriz e deleta o trecho da string.
        std::string setControllerParameters(std::string controllers);// Recebe uma string com C no final de cada conjunto parâmetros do controlador afim por partes. Converte cada trecho do início até encontrar o C em uma matriz e deleta o trecho da string.
        void setControllerParameters(const LinAlg::Matrix<Type> *controllers, const unsigned &size);
        virtual LinAlg::Matrix<Type> outputControlActionsCalc(LinAlg::Matrix<Type> Reference, LinAlg::Matrix<Type> SignalInput) = 0; // Obriga as classes filhas a implementar essa função.
        virtual LinAlg::Matrix<Type> outputControlActionsCalc(LinAlg::Matrix<Type> Reference, LinAlg::Matrix<Type> SignalInput, LinAlg::Matrix<Type> States) = 0;
        LinAlg::Matrix<Type> getState()const{ return this->states;}

    protected://significa que todas as classes filhas podem acessar os atributos abaixo.
        LinAlg::Matrix<Type> *Constraints, states; // Vetor de Matrizes contendo todas as restrições para cada conjunto.
    	LinAlg::Matrix<Type> *controllerParameters; // Vetor de Matrizes contendo todos os parâmetros de controlador para cada conjunto.
        uint16_t quantityOfRegions, stateSize; // Quantidade de regiões em que o conjunto foi subdividido.
        int inWitchRegion; // Sinalisa em qual região pertence o estado calculado.

    	bool isInside(const LinAlg::Matrix<Type> &_point);// Verifica se um estado pertence ao conjunto invariante.
        bool any(const LinAlg::Matrix<Type> &H);// função para auxiliar isInside.
	};
}

#ifdef testControl
    #include "../../../src/controlLibs/ExplicityController.hpp"
#else
    #include "SistemasdeControle/src/controlLibs/ExplicityController.hpp"
#endif
#endif
