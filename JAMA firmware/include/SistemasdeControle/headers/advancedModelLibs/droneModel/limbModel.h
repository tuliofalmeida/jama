#ifndef LIMBMODEL_H
#define LIMBMODEL_H

#ifdef testModel
    #include "../../../headers/modelLibs/model.h"
#else
    #include "SistemasdeControle/headers/modelLibs/model.h"
#endif

namespace ModelHandler {
    template <typename Type>
    class LimbModel : public Model<Type>
    {
    public:
        LimbModel(LinAlg::Matrix<Type> parameters);

        Type         sim(Type x){}
        Type         sim(Type x, Type y){}
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x);
        LinAlg::Matrix<Type> sim(Type lmin, Type lmax, Type step){}
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x, LinAlg::Matrix<Type> y){}

        std::string print(){}
        unsigned getNumberOfVariables() const{}
        unsigned getNumberOfInputs() const{}
        unsigned getNumberOfOutputs() const{}
        void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output){}
        void setLinearModel(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output){}


    private:
        Type theta_pp, theta_p, theta; // Accel, Speed, Position
        Type K1, K2, K3, Td, B1, B2, B3, J, m, g, l;

    };
}

#ifdef testModel
    #include "../../../src/advancedModelLibs/DroneModel/limbModel.hpp"
#else
    #include "SistemasdeControle/src/advancedModelLibs/DroneModel/limbModel.hpp"
#endif

#endif // LIMBMODEL_H
