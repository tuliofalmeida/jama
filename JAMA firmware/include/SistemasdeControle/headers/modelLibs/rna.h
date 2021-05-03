#ifndef RNA_H
#define RNA_H

#include "SistemasdeControle/headers/modelLibs/model.h"
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
#include "SistemasdeControle/headers/modelLibs/neuron.h"

namespace ModelHandler
{
    template <typename Type>
    class RNA : public Model<Type>
    {
        public:
            RNA();
            RNA(unsigned InputSize,
                unsigned HidderSize,
                unsigned OutputSize,
                const NeuralNetworkHandler::Neuron<Type> &Neuron);
//            RNA(unsigned InputSize,
//                unsigned HiderSize,
//                unsigned OutputSize,
//                NeuralNetworkHandler::Neuron<Type> Neuron);
//            RNA(LinAlg::Matrix<Type> RNASize,
//                NeuralNetworkHandler::Neuron<Type> Neuron);
//            RNA(LinAlg::Matrix<Type> RNASize,
//                LinAlg::Matrix< NeuralNetworkHandler::Neuron<Type> > Neuron);

            Type         sim(Type x){return 0;}
            Type         sim(Type x, Type y){return 0;}
            LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x);
            LinAlg::Matrix<Type> sim(Type lmin, Type lmax, Type step){return LinAlg::Zeros<Type>(1,1);}
            LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x, LinAlg::Matrix<Type> y){return LinAlg::Zeros<Type>(1,1);}

            unsigned getNumberOfVariables(){return 0;}
            unsigned getNumberOfInputs() const {return 0;}
            unsigned getNumberOfOutputs() const {return 0;}

            void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output){}
            void setLinearModel(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output){}

            std::string print(){return 0;}

        private:
            NeuralNetworkHandler::Neuron<Type> neuron;

            LinAlg::Matrix<Type> inLayer, hiddLayer, outLayer;
            LinAlg::Matrix<Type> inWeight, hidWeight, outWeight;

    };
}

#include"SistemasdeControle/headers/modelLibs/rna.hpp"
#endif // RNA_H
