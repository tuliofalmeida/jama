#include "SistemasdeControle/embeddedTools/sensors/kalman.h"

#define mF (F)
#define mB (B)
#define mQ (Q)
#define mH (H)
#define mR (R)
#define mX X
#define mP P

kalman::kalman()
{ }


void kalman::init(LinAlg::Matrix<double> F, LinAlg::Matrix<double> B, LinAlg::Matrix<double> Q, LinAlg::Matrix<double> H, LinAlg::Matrix<double> R)
{
    this->F = F;
    this->B = B;
    this->Q = Q;
    this->H = H;
    this->R = R;

    this->X = LinAlg::Matrix<double>(B.getNumberOfRows(), B.getNumberOfColumns());

    this->P = "1.0 , 0.0; 0.0 , 1.0";
}


double kalman::update(const double &angle, const double &rate)
{
    LinAlg::Matrix<double> K;

    mX = (mF * mX) + (mB * angle);
    mP = (mF * mP * (~mF)) + mQ;
    K  = mP*(~mH)*((mH * mP * (~mH) + mR)^-1);
    mX = mX + K*(rate - (mH*mX)(0,0));
    mP = mP - K*mH*mP;
    return (mH * mX)(0,0);
}
