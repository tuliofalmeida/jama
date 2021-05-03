#ifndef NEURON_H
#define NEURON_H

#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"

namespace NeuralNetworkHandler
{
    template <typename Type>
    class Neuron
    {

        public:
            Neuron();
            Neuron(std::string ActiveFunctionType, Type coef, Type min, Type max);
            ~Neuron();

            LinAlg::Matrix<Type> GetInput();
            LinAlg::Matrix<Type> GetWeight();
            LinAlg::Matrix<Type> GetActivationFunctionVariables();
            Type GetOutput();

            void SetInput(const LinAlg::Matrix<Type> &Input);
            void SetWeight(const LinAlg::Matrix<Type> &Weight);
            void SetActivationFunctionVariables(const LinAlg::Matrix<Type> &ActivationFunctionVariables);
            void SetOutput(const Type &Output);
            void SetBias(const Type &Bias);

            Type sim(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Weight, Type Bias);

        protected:
            LinAlg::Matrix<Type> Input, Weight, ActivationFunctionVariables;
            Type Output, Bias, min, max, coef;
            std::string ActiveFunctionType;

            Type Signal(const Type &value);
            Type HardLimit(const Type &value);
            Type Linear(const Type &value);
            Type PositiveLinear(const Type &value);
            Type SymmetricLinear(const Type &value);
            Type SaturatingLinear(const Type &value);
            Type Gaussian(const Type &value);
            Type Multiquadrics(const Type &value);
            Type InverseMultiquadrics(const Type &value);
            Type Sigmoid(const Type &value);
            Type HyperbolicTangentSigmoid(const Type &value);
    };
}

#include "SistemasdeControle/headers/modelLibs/neuron.hpp"

#endif // NEURON_H
