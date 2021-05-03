#ifndef __DRONECONTROL_H_INCLUDED
#define __DRONECONTROL_H_INCLUDED

#include "SistemasdeControle/headers/modelLibs/arx.h"
#include "SistemasdeControle/headers/controlLibs/pid.h"
#include "SistemasdeControle/headers/graphicLibs/plot.h"
#include "SistemasdeControle/headers/controlLibs/modelpredictivecontrol.h"
#include "SistemasdeControle/headers/optimizationLibs/recursiveleastsquare.h"
#include "SistemasdeControle/headers/advancedModelLibs/droneModel/dronemodel.h"

namespace ControlHandler{

    template<typename Type>
    class DroneControl{
    public:
        DroneControl(unsigned predictionHorizon = 20,
                     unsigned errorWeigth = 20,
                     unsigned controlHorizon = 2,
                     unsigned controlWeigth = 1,
                     const ModelHandler::ARX<Type> *gz = 0,
                     bool isAdaptive = 0);
        DroneControl(const LinAlg::Matrix<Type> &PIDsParameters);

        LinAlg::Matrix<Type> getInput()const { return this->Input;}
        LinAlg::Matrix<Type> getLocalReference()const { return this->localReference;}
        LinAlg::Matrix<Type> getOutput()const { return this->Output;}

        void DroneControlSimulated(const LinAlg::Matrix<Type> &Reference);
        LinAlg::Matrix<Type> OutputControlCalc(const LinAlg::Matrix<Type> &Output, const LinAlg::Matrix<Type> &Reference);

    private:
        bool isAdaptive;
        unsigned N1, N2, NU, Q, R;
        ModelHandler::ARX<Type> *gz;
        ModelHandler::droneModel<Type> *drone;
        ControlHandler::PID<Type> PID[4], advancedPID[2];
        ControlHandler::ModelPredictiveControl<Type> *MPC;
        OptimizationHandler::RecursiveLeastSquare<Type> *RLS;
        LinAlg::Matrix<Type> mpcInput, Input, Output, localReference;

        void OutputControlCalc(const LinAlg::Matrix<Type> &Reference);
    };
}

#include "SistemasdeControle/src/advancedControlLibs/droneControl/dronecontrol.hpp"
#endif // DRONECONTROL_H
