#include "SistemasdeControle/headers/advancedControlLibs/droneControl/dronecontrol.h"

template <typename Type>
ControlHandler::DroneControl<Type>::DroneControl(unsigned predictionHorizon,
                                                 unsigned errorWeigth,
                                                 unsigned controlHorizon,
                                                 unsigned controlWeigth,
                                                 const ModelHandler::ARX<Type> *gz,
                                                 bool isAdaptive)
{
    this->N1 = 1;
    this->gz = gz;
    this->Q = errorWeigth;
    this->R =controlWeigth;
    this->NU = controlHorizon;
    this->N2 = predictionHorizon;
    this->isAdaptive = isAdaptive;
    this->Output = LinAlg::Zeros<Type>(6,1);
    this->Input  = LinAlg::Zeros<Type>(4,1);
    this->localReference = LinAlg::Zeros<Type>(4,1);

    Input(1,1) += (9.8*2.2);
    mpcInput  = LinAlg::Zeros<Type>(4,1);
    this->drone = new ModelHandler::droneModel<Type>();
    ModelPredictiveControl<Type> MPC = new ModelPredictiveControl<Type>(*(this->gz),
                                                                        this->N1,
                                                                        this->N2,
                                                                        this->NU,
                                                                        this->Q,
                                                                        this->R,0);
    MPC.setReference("0;0;0;0");

    OptimizationHandler::RecursiveLeastSquare<Type> RLS = new OptimizationHandler::RecursiveLeastSquare<Type>(gz,1e3,0.999);
}

template <typename Type>
ControlHandler::DroneControl<Type>::DroneControl(const LinAlg::Matrix<Type> &PIDsParameters)
{
    this->gz = 0;

    for(unsigned i = 0; i < 2; ++i)
        advancedPID[i].setParams(PIDsParameters.GetRow(i+1));

    for(unsigned i = 2; i < 6; ++i)
        PID[i-2].setParams(PIDsParameters.GetRow(i+1));

    Output = LinAlg::Zeros<Type>(6,1);
    Input  = LinAlg::Zeros<Type>(4,1);
    this->localReference = LinAlg::Zeros<Type>(4,1);

    Input(1,1) += (9.8*2.2);

    this->drone = new ModelHandler::droneModel<Type>();
}

template <typename Type>
void ControlHandler::DroneControl<Type>::OutputControlCalc(const LinAlg::Matrix<Type> &Reference)
{
    if(this->gz == 0)
    {
        this->Input(1,1) = this->PID[0].OutputControl(Reference(1,1),this->Output(3,1)) + (9.8 * 2.2);
        this->Input(2,1) = this->PID[1].OutputControl(Reference(2,1),this->Output(4,1));
        this->Input(3,1) = this->PID[2].OutputControl(Reference(3,1),this->Output(5,1));
        this->Input(4,1) = this->PID[3].OutputControl(Reference(4,1),this->Output(6,1));
    }else{
        this->MPC->setReference(Reference);

        if(this->isAdaptive)
            this->RLS->Optimize(mpcInput, Output("3,4,5,6",1));
        else
            this->gz->setLinearVector(mpcInput, Output("3,4,5,6",1));

        this->mpcInput = this->MPC->OutputControlCalc(*(this->gz));
        this->Input(1,1) = this->mpcInput(1,1) + (9.8*2.2);
        this->Input(2,1) = this->mpcInput(2,1);
        this->Input(3,1) = this->mpcInput(3,1);
        this->Input(4,1) = this->mpcInput(4,1);
    }
}

template <typename Type>
void ControlHandler::DroneControl<Type>::DroneControlSimulated(const LinAlg::Matrix<Type> &Reference)
{
    localReference = LinAlg::Zeros<Type>(4,1);
    if(Reference(3,1) != 0){
        localReference(1,1) = Reference(3,1);
        localReference(2,1) = this->advancedPID[1].OutputControl(-Reference(2,1),-this->Output(2,1));
        localReference(3,1) = this->advancedPID[0].OutputControl(Reference(1,1),this->Output(1,1));
//        localReference(4,1) = 0;
    }

    this->OutputControlCalc(localReference);
    this->Output = drone->sim(Input);
}

template <typename Type>
LinAlg::Matrix<Type> ControlHandler::DroneControl<Type>::OutputControlCalc(const LinAlg::Matrix<Type> &Output,
                                                                           const LinAlg::Matrix<Type> &Reference)
{
    localReference = LinAlg::Zeros<Type>(4,1);
    if(Reference(3,1) != 0){
        localReference(1,1) = Reference(3,1);
        localReference(2,1) = this->advancedPID[1].OutputControl(-Reference(2,1),-Output(2,1));
        localReference(3,1) = this->advancedPID[0].OutputControl(Reference(1,1),Output(1,1));
//        localReference(4,1) = 0;
    }


    return localReference;
}
