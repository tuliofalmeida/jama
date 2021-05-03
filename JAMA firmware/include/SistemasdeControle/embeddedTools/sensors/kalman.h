#ifndef ADRONE_KALMANFILTER_H
#define ADRONE_KALMANFILTER_H

#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"


class kalman
{
public:
    /**
     * Constructor sets the initial settings. Copy and move have been disabled
     * 
     * @param other kalman object
     */
    kalman();
    kalman(const kalman &kalman)  = delete;
    kalman(const kalman &&kalman) = delete;

    /**
     * Disable copy and move assignment operator
     * 
     * @param other kalman object
     */
    kalman& operator=(const kalman &other)  = delete;
    kalman& operator=(const kalman &&other) = delete;

    /**
     * [description]
     * 
     * @param F [description]
     * @param B [description]
     * @param Q [description]
     * @param H [description]
     * @param R [description]
     */
    void init(LinAlg::Matrix<double> F, LinAlg::Matrix<double> B, LinAlg::Matrix<double> Q, LinAlg::Matrix<double> H, LinAlg::Matrix<double> R);

    /**
     * Update filter
     * 
     * @param angle [description]
     * @param rate [description]
     * 
     * @return [description]
     */
    double update(const double &angle, const double &rate);

private:
    LinAlg::Matrix<double> F; LinAlg::Matrix<double>  B; LinAlg::Matrix<double>  Q; LinAlg::Matrix<double>  H;
    LinAlg::Matrix<double> R;
    LinAlg::Matrix<double> X; LinAlg::Matrix<double>  P;
};

#include "SistemasdeControle/embeddedTools/sensors/kalman.cpp"
#endif
