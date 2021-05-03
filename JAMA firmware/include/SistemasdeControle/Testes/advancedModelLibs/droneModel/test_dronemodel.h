#ifndef DRONEMODEL_H
#define DRONEMODEL_H

#include "SistemasdeControle/headers/modelLibs/model.h"

namespace ModelHandler {
    template <class Type>
    class droneModel : public Model<Type>
    {
    public:
        droneModel();

        Type         sim(Type x){}
        Type         sim(Type x, Type y){}
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x);
        LinAlg::Matrix<Type> sim(Type lmin, Type lmax, Type step){}
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x, LinAlg::Matrix<Type> y){}

        std::string print(){}
        unsigned getNumberOfVariables(){}
        unsigned getNumberOfInputs() const{};
        unsigned getNumberOfOutputs() const{};
        void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output){}
        void setLinearModel(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output){}

    private:
        Type X_pp, Y_pp, Z_pp, X_p, Y_p, Z_p, X, Y, Z; // Accel, Speed, Position
        Type phi_pp, theta_pp, psi_pp, phi_p, theta_p, psi_p; // Angular Accel, Speed
        Type phi, theta, psi; // angular position
        Type mass, gravity, Inertia_xx, Inertia_yy, Inertia_zz; //Constants

    };
}

#include "SistemasdeControle/src/advancedModelLibs/droneModel/dronemodel.hpp"
#endif // DRONEMODEL_H
