#ifdef testModel
    #include "../../../headers/advancedModelLibs/DroneModel/limbModel.h"
#else
    #include "SistemasdeControle/headers/advancedModelLibs/DroneModel/limbModel.h"
#endif

template <typename Type>
ModelHandler::LimbModel<Type>::LimbModel(LinAlg::Matrix<Type> parameters)
{
    //this->K1 = 0.02;
    //this->K2 = 0.01;
   // this->K3 = 0.03;
    //this->Td = 0.04;
    //this->B1 = 0.05;
    //this->B2 = 0.01;
    //this->B3 = 1;
    //this->J = 1;
    //this->m = 3;
    this->setModelCoef(parameters);
    this->K1 = parameters(0,0);
    this->K2 = parameters(0,1);
    this->K3 = parameters(0,2);
    this->Td = parameters(0,3);
    this->B1 = parameters(0,4);
    this->B2 = parameters(0,5);
    this->B3 = parameters(0,6);
    this->J  = parameters(0,7);
    this->m  = parameters(0,8);
    this->g = 9.789;
    this->l = 0.4;
    this->setStep(0.01);
}

template <typename Type>
LinAlg::Matrix<Type> ModelHandler::LimbModel<Type>::sim(LinAlg::Matrix<Type> x){
    LinAlg::Matrix<Type> Y = 1000*LinAlg::Ones<Type>(x.getNumberOfRows(),1), parameters = this->getModelCoef();
    this->K1 = parameters(0,0); this->K2 = parameters(0,1); this->K3 = parameters(0,2);
    this->B1 = parameters(0,4); this->B2 = parameters(0,5); this->B3 = parameters(0,6);
    this->Td = parameters(0,3); this->J  = parameters(0,7); this->m  = parameters(0,8);

    this->theta_pp = 0; this->theta_p = 0; this->theta = 0;

    for(uint32_t i = 0; i < x.getNumberOfRows(); ++i)
    {

        theta_pp = (1.0/J)*(x(i,0)*cos(theta) - (K1*exp(K2*theta))*(theta-K3) - m*g*l*sin(theta) - B1*tanh(-B2*theta_p) - B3*theta_p + Td);
        theta   += this->step*theta_p;
        theta_p += this->step*theta_pp;
        if(theta == NAN)
            break;
        Y(i,0) = theta;
        //std::cout << Y(i,0);
    }

    return Y;
}

