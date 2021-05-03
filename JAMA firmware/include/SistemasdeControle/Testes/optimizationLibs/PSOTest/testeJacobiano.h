#ifndef TESTEJACOBIANO_H
#define TESTEJACOBIANO_H

template <typename Type>
LinAlg::Matrix<Type> limbSim(LinAlg::Matrix<Type> parameters, LinAlg::Matrix<Type> input, LinAlg::Matrix<Type> states){
    LinAlg::Matrix<Type> Y = 1000*LinAlg::Ones<Type>(x.getNumberOfRows(),1), x = input, Jacobiano;
    Type K1 = parameters(0,0); Type K2 = parameters(0,1); Type K3 = parameters(0,2);
    Type B1 = parameters(0,4); Type B2 = parameters(0,5); Type B3 = parameters(0,6);
    Type Td = parameters(0,3); Type J  = parameters(0,7); Type m  = parameters(0,8);

    Type theta_pp = 0, theta_p = 0, theta = 0;

    for(int i = 0; i < x.getNumberOfRows(); ++i)
    {
        theta_pp = (1.0/J)*(x(i,0)*cos(theta) - (K1*exp(K2*theta))*(theta-K3) - m*g*l*sin(theta) - B1*tanh(-B2*theta_p) - B3*theta_p + Td);

        theta_p += this->step*theta_pp;
        theta   += this->step*theta_p;
        if(theta == NAN)
            break;
        Y(i,0) = theta;
    }

    return Y;
}

#endif // TESTEJACOBIANO_H
