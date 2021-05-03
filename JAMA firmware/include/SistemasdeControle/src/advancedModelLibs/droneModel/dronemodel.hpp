#include "SistemasdeControle/headers/advancedModelLibs/droneModel/dronemodel.h"

template <class Type>
ModelHandler::droneModel<Type>::droneModel()
{
    X_pp = 0; Y_pp = 0; Z_pp = 0; X_p = 0; Y_p = 0; Z_p = 0; X = 0; Y = 0; Z = 0;
    phi_pp = 0; theta_pp = 0; psi_pp = 0; phi_p = 0; theta_p = 0; psi_p = 0;
    phi = 0, theta = 0, psi = 0;
    mass = 2.2; gravity = 9.8; Inertia_xx = 16.76337;  // valores padrão baseados no artigo
    Inertia_yy = 16.76337; Inertia_zz = 23.1447; // valores padrão baseados no artigo
    srand(time(NULL));
    this->setStep(0.1);
}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::droneModel<Type>::sim(LinAlg::Matrix<Type> x){
    Type u1 = x(1,1), u2 = x(2,1), u3 = x(3,1), u4 = x(4,1);

    X_pp     = ((sin(psi)*sin(phi) + cos(psi)*cos(phi)*sin(theta))/mass)*u1;
    Y_pp     = ((-cos(psi)*sin(phi) + sin(theta)*sin(psi)*cos(phi))/mass)*u1;
    Z_pp     = (cos(theta)*cos(phi)/mass)*u1 - gravity;

    phi_pp   = (u2 - (Inertia_zz - Inertia_yy)*theta_p*psi_p)/Inertia_xx;
    theta_pp = (u3 - (Inertia_xx - Inertia_zz)*phi_p*psi_p)/Inertia_yy;
    psi_pp   = u4/Inertia_zz;

    X_p += this->step*X_pp;
    Y_p += this->step*Y_pp;
    Z_p += this->step*Z_pp;

    X   += this->step*X_p;
    Y   += this->step*Y_p;
    Z   += this->step*Z_p;

    phi_p   += this->step*phi_pp;
    psi_p   += this->step*psi_pp;
    theta_p += this->step*theta_pp;

    phi     += this->step*phi_p;
    psi     += this->step*psi_p;
    theta   += this->step*theta_p;

    LinAlg::Matrix<Type> ret(6,1);
    ret(1,1) = X + Type(rand()%100-50)/40000;   ret(2,1) = Y + Type(rand()%100-50)/40000; ret(3,1) = Z + Type(rand()%100-50)/40000;
    ret(4,1) = phi + Type(rand()%100-50)/40000; ret(6,1) = psi + Type(rand()%100-50)/40000; ret(5,1) = theta + Type(rand()%100-50)/40000;

    return ret;
}

