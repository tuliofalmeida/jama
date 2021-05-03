#ifndef PREDITIVO_H
#define PREDITIVO_H

#include "SistemasdeControle/headers/restrictedOptimization/activeset.h"
#include "SistemasdeControle/headers/modelLibs/model.h"
#include "SistemasdeControle/headers/modelLibs/statespace.h"
#include "SistemasdeControle/headers/modelLibs/conversions.h"
#include "SistemasdeControle/headers/modelLibs/integrativemodel.h"
#include "SistemasdeControle/headers/modelLibs/predictionmodel.h"
#include "SistemasdeControle/headers/restrictedOptimization/recursiveactiveset.h"

namespace ControlHandler{
    template <class Type>
    class ModelPredictiveControl
    {
        ModelHandler::StateSpace<Type> SSd, SSdStateStimated;
        ModelHandler::PredictionModel<Type> SSP;
        ModelHandler::IntegrativeModel<Type> SSI;
        LinAlg::Matrix<Type> K, W, Q, R, U;
        Type N1,N2,NU, uMax, uMin, duMax, duMin, yMax, yMin;
        restrictedOptimizationHandler::QuadProg<Type> *QP;

        void setOptimizationConstraints(Type duMax, Type duMin, Type yMax,
                                        Type yMin, Type uMax, Type uMin,
                                        const LinAlg::Matrix<Type> &uk1,
                                        const LinAlg::Matrix<Type> &A,
                                        const LinAlg::Matrix<Type> &B,
                                        const LinAlg::Matrix<Type> &C,
                                        const LinAlg::Matrix<Type> &X0);

    public:
        ModelPredictiveControl(){this->QP = NULL;}
        ModelPredictiveControl(const ModelHandler::StateSpace<Type> &SS,
                               unsigned N1, unsigned N2, unsigned NU,
                               Type Q, Type R, Type W);
        ModelPredictiveControl(const ModelHandler::ARX<Type> &gz,
                               unsigned N1, unsigned N2, unsigned NU,
                               Type Q, Type R, Type W);

        void setLimits(Type Umax, Type Umin);
        void setLimits(Type duMax, Type duMin, Type yMax, Type yMin, Type uMax, Type uMin);
        void setReference(LinAlg::Matrix<Type> W);
        void setErrorWeight(LinAlg::Matrix<Type> Q);
        void setControlWeight(LinAlg::Matrix<Type> R);
        void setInitialState(LinAlg::Matrix<Type> X0);
        void setOptimizationAlgorithm2QuadProg(restrictedOptimizationHandler::QuadProg<Type> *QP){this->QP = QP;}

        void LimitControlOutput();

        void setNewModel(const ModelHandler::ARX<Type> &gz);
        void setNewModel(ModelHandler::StateSpace<Type> SS);

        LinAlg::Matrix<Type> getReference() const;
        LinAlg::Matrix<Type> getErrorWeight() const;
        LinAlg::Matrix<Type> getInitialState() const;
        LinAlg::Matrix<Type> getControlWeight() const;
        LinAlg::Matrix<Type> getControlerGain() const;

        LinAlg::Matrix<Type> OutputControlCalc(const LinAlg::Matrix<Type> &X_input);
        LinAlg::Matrix<Type> OutputControlCalc(const ModelHandler::ARX<Type> &gz);
        LinAlg::Matrix<Type> OutputControlCalc(LinAlg::Matrix<Type> X_input, LinAlg::Matrix<Type> W);
        LinAlg::Matrix<Type> OutputControlCalc(LinAlg::Matrix<Type> X_input, LinAlg::Matrix<Type> Q, LinAlg::Matrix<Type> R, LinAlg::Matrix<Type> W);

    };
}

#include "SistemasdeControle/src/controlLibs/modelpredictivecontrol.hpp"
#endif // PREDITIVO_H
