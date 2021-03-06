#ifdef testControl
    #include "../../../headers/controlLibs/modelpredictivecontrol.h"
#else
    #include "SistemasdeControle/headers/controlLibs/modelpredictivecontrol.h"
#endif

//#include "../../../headers/modelLibs/conversions.h"
template<typename Type>
ControlHandler::ModelPredictiveControl<Type>::
       ModelPredictiveControl(const ModelHandler::StateSpace<Type> &SS,
                              unsigned N1, unsigned N2, unsigned NU,
                              Type Q, Type R, Type W)
{
    this->N1 = N1;
    this->N2 = N2;
    this->NU = NU;

    if(SS.isContinuous())
        this->SSd = ModelHandler::c2d(SS,0.1);
    else
        this->SSd = SS;
    this->SSdStateStimated = this->SSd;

    LinAlg::Matrix<Type> X  = LinAlg::Zeros<Type>(SSd.getA().getNumberOfRows(),2);
    LinAlg::Matrix<Type> Y  = LinAlg::Zeros<Type>((SSd.getC()*X).getNumberOfRows(),(SSd.getC()*X).getNumberOfColumns());
//    this->SSI = new ModelHandler::IntegrativeModel<Type>(SSd);
//    this->SSP = new ModelHandler::PredictionModel<Type>(SSd,N1,N2,NU);
    this->SSI = ModelHandler::integrativeModel(SSd);
    this->SSP = ModelHandler::predictionModel(this->SSI,this->N1,this->N2,this->NU);
    this->Q = Q*LinAlg::Eye<Type>((SSP.getC()*SSP.getB()).getNumberOfRows());
    this->R = R*LinAlg::Eye<Type>(NU*SSd.getB().getNumberOfColumns());
    this->W = W*LinAlg::Ones<Type>((SSP.getC()*SSP.getA()*(X||Y)).getNumberOfRows(),1);
    this->U  = LinAlg::Zeros<Type>(SSI.getB().getNumberOfColumns(),1);
    this->K = (LinAlg::inv_numeric((~SSP.getB())*(~SSP.getC())*this->Q*SSP.getC()*SSP.getB()+this->R ))*(~SSP.getB())*(~SSP.getC())*(~this->Q);
//    this->lMax = 5000;
//    this->lMin = -this->lMax;
    this->QP = NULL;
}

template<typename Type>
ControlHandler::ModelPredictiveControl<Type>::
       ModelPredictiveControl(const ModelHandler::ARX<Type> &gz,
                              unsigned N1, unsigned N2, unsigned NU,
                              Type Q, Type R, Type W)
{
    this->N1 = N1;
    this->N2 = N2;
    this->NU = NU;

    this->SSd = ModelHandler::arx2SS<Type>(gz);
    LinAlg::Matrix<Type> X  = LinAlg::Zeros<Type>(SSd.getA().getNumberOfRows(),2);
    LinAlg::Matrix<Type> Y  = LinAlg::Zeros<Type>((SSd.getC()*X).getNumberOfRows(),(SSd.getC()*X).getNumberOfColumns());
    this->SSdStateStimated = this->SSd;

    //    this->SSI = new ModelHandler::IntegrativeModel<Type>(SSd);
    //    this->SSP = new ModelHandler::PredictionModel<Type>(SSd,N1,N2,NU);
    this->SSI = ModelHandler::integrativeModel(SSd);
    this->SSP = ModelHandler::predictionModel(this->SSI,this->N1,this->N2,this->NU);
    this->Q = Q*LinAlg::Eye<Type>((SSP.getC()*SSP.getB()).getNumberOfRows());
    this->R = R*LinAlg::Eye<Type>(NU*SSd.getB().getNumberOfColumns());
    this->W = W*LinAlg::Ones<Type>((SSP.getC()*SSP.getA()*(X||Y)).getNumberOfRows(),1);
    this->U  = LinAlg::Zeros<Type>(SSI.getB().getNumberOfColumns(),1);
    this->K = (LinAlg::inv_numeric((~SSP.getB())*(~SSP.getC())*this->Q*SSP.getC()*SSP.getB()+this->R ))*(~SSP.getB())*(~SSP.getC())*(~this->Q);
    this->uMax = 50000;
    this->uMin = -this->uMax;
    this->QP = NULL;
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setControlLimits(Type Umax, Type Umin)
{
    this->uMax = Umax; this->uMin = Umin;
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setControlVariationLimits(Type duMax, Type duMin)
{
    this->duMax = duMax; this->duMin = duMin;
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setOutputLimits(Type yMax, Type yMin)
{
    this->yMax = yMax; this->yMin = yMin;
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setLimits(Type duMax, Type duMin,
                                                             Type yMax, Type yMin,
                                                             Type uMax, Type uMin)
{
    this->duMax = duMax; this->duMin = duMin;
    this->uMax = uMax;   this->uMin = uMin;
    this->yMax = yMax;   this->yMin = yMin;
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setOptimizationConstraints(Type duMax, Type duMin, Type yMax,
                                                                              Type yMin, Type uMax, Type uMin,
                                                                              const LinAlg::Matrix<Type> &uk1,
                                                                              const LinAlg::Matrix<Type> &A,
                                                                              const LinAlg::Matrix<Type> &B,
                                                                              const LinAlg::Matrix<Type> &C,
                                                                              const LinAlg::Matrix<Type> &X0)
{
    if(this->QP)
    {
        LinAlg::Matrix<Type> Fdu = LinAlg::Eye<Type>(B.getNumberOfColumns());
        LinAlg::Matrix<Type> Gdu = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(duMax - this->QP->getTolerance());
//        LinAlg::Matrix<Type> Gdu = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(duMax);
        LinAlg::Matrix<Type> Fy  = LinAlg::Eye<Type>(C.getNumberOfRows());
        LinAlg::Matrix<Type> Gy  = LinAlg::Ones<Type>(C.getNumberOfRows(),1)*(yMax - this->QP->getTolerance());
//        LinAlg::Matrix<Type> Gy  = LinAlg::Ones<Type>(C.getNumberOfRows(),1)*(yMax);
        LinAlg::Matrix<Type> Fu  = LinAlg::Eye<Type>(B.getNumberOfColumns());
        LinAlg::Matrix<Type> Gu  = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(uMax - this->QP->getTolerance());
//        LinAlg::Matrix<Type> Gu  = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(uMax);
        LinAlg::Matrix<Type> Mtemp1;
        for (unsigned i = 1; i <= B.getNumberOfColumns(); ++i)
           Mtemp1 = Mtemp1 ||
                    LinAlg::Ones<Type>(1,i) | LinAlg::Zeros<Type>(1,B.getNumberOfColumns()-i);

        LinAlg::Matrix<Type> L   = LinAlg::Ones<Type>(B.getNumberOfColumns(),1);

        LinAlg::Matrix<Type> Fp = Fdu || Fy*C*B || Fu*Mtemp1;
        LinAlg::Matrix<Type> Gp = Gdu || Gy-Fy*C*A*X0 || Gu-Fu*L*uk1;

        LinAlg::Matrix<Type> Fdun = LinAlg::Eye<Type>(B.getNumberOfColumns());
        LinAlg::Matrix<Type> Gdun = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(duMin + this->QP->getTolerance());
//        LinAlg::Matrix<Type> Gdun = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(duMin);
        LinAlg::Matrix<Type> Fyn  = LinAlg::Eye<Type>(C.getNumberOfRows());
        LinAlg::Matrix<Type> Gyn  = LinAlg::Ones<Type>(C.getNumberOfRows(),1)*(yMin + this->QP->getTolerance());
//        LinAlg::Matrix<Type> Gyn  = LinAlg::Ones<Type>(C.getNumberOfRows(),1)*(yMin);
        LinAlg::Matrix<Type> Fun  = LinAlg::Eye<Type>(B.getNumberOfColumns());
        LinAlg::Matrix<Type> Gun  = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(uMin + this->QP->getTolerance());
//        LinAlg::Matrix<Type> Gun  = LinAlg::Ones<Type>(B.getNumberOfColumns(),1)*(uMin);
        LinAlg::Matrix<Type> Mtemp2;

        for (unsigned i = 1; i <= B.getNumberOfColumns(); ++i)
           Mtemp2 = Mtemp2 || LinAlg::Ones<Type>(1,i) | LinAlg::Zeros<Type>(1,B.getNumberOfColumns()-i);

        L   = LinAlg::Ones<Type>(B.getNumberOfColumns(),1);

        LinAlg::Matrix<Type> Fn = Fdun || Fyn*C*B || Fun*Mtemp2;
        LinAlg::Matrix<Type> Gn = Gdun || Gyn-Fyn*C*A*X0 || Gun-Fun*L*uk1;
        this->QP->setRestrictions(MatrixRestrictionHandler::MatrixEquality<Type>(), Fn >= Gn, Fp <= Gp);
    }
    else
        std::cout << "O otimizador nao foi setado\n";
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setReference(LinAlg::Matrix<Type> W)
{
//    this->W = LinAlg::Zeros<Type>(this->W.getNumberOfRows(),this->SSd.getB().getNumberOfColumns());
    for(unsigned k = 0; k < this->W.getNumberOfColumns(); ++k)
        for(unsigned i = 0; i < this->W.getNumberOfRows(); i += this->SSd.getC().getNumberOfRows())
                for(unsigned j = 0; j < this->SSd.getC().getNumberOfRows(); ++j)
                    this->W(i+j,  k)  = W(j,k);
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setErrorWeight(LinAlg::Matrix<Type> Q)
{
    this->Q = Q;
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setInitialState(LinAlg::Matrix<Type> X0)
{
    this->SSd.setInitialState(X0);
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setControlWeight(LinAlg::Matrix<Type> R)
{
    this->R = R;
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setNewModel(const ModelHandler::ARX<Type> &gz)
{
    LinAlg::Matrix<Type> X = this->SSd.getActualState()/*, Xss = SSdStateStimated.getActualState()*/;
    this->SSdStateStimated = ModelHandler::arx2SS(gz);
    LinAlg::Matrix<Type> gzState = gz.getLinearVectorA();

    for(unsigned i = 1; i <= X.getNumberOfRows(); i += gz.getNumberOfOutputDelays())
        X(i, 1) = -gzState(1,i);

    SSdStateStimated.setInitialState(X);
    SSdStateStimated.sim(this->U);
    //    this->SSI = new ModelHandler::IntegrativeModel<Type>(SSd);
    //    this->SSP = new ModelHandler::PredictionModel<Type>(SSd,N1,N2,NU);
    this->SSI = ModelHandler::integrativeModel(SSd);
    this->SSP = ModelHandler::predictionModel(this->SSI,this->N1,this->N2,this->NU);

    this->K = (LinAlg::inv_numeric((~SSP.getB())*(~SSP.getC())*this->Q*SSP.getC()*SSP.getB()+this->R ))*(~SSP.getB())*(~SSP.getC())*(~this->Q);
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::setNewModel(ModelHandler::StateSpace<Type> SS)
{
////    SS.setInitialState(this->SSd.getActualState());
//    if(SS.isContinuous())
//        this->SSdStateStimated = ModelHandler::c2d(SS,0.1);
//    else
//        this->SSdStateStimated = SS;
////    this->SSd.setInitialState(SS.getActualState());
//    this->SSI = new ModelHandler::IntegrativeModel<double>(SSd);
//    this->SSP = new ModelHandler::PredictionModel<double>(SSd,N1,N2,NU);

//    this->K = (LinAlg::inv_numeric((~SSP.getB())*(~SSP.getC())*Q*SSP.getC()*SSP.getB()+R ))*(~SSP.getB())*(~SSP.getC())*(~Q);
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::ModelPredictiveControl<Type>::getReference() const
{
    return W;
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::ModelPredictiveControl<Type>::getErrorWeight() const
{
    return Q;
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::ModelPredictiveControl<Type>::getInitialState() const
{
    return SSd.getActualState();
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::ModelPredictiveControl<Type>::getControlWeight() const
{
    return R;
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::ModelPredictiveControl<Type>::getControlerGain() const
{
    return K;
}

template<typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* >* ControlHandler::ModelPredictiveControl<Type>::getControlLimits()
{
    LinAlg::Matrix< LinAlg::Matrix<Type>* > *controlLimits = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*controlLimits)(0,0) = new LinAlg::Matrix<Type>(1,1);
    (*controlLimits)(0,1) = new LinAlg::Matrix<Type>(1,1);
    (*((*controlLimits)(0,0))) = LinAlg::Matrix<Type>(this->uMax);
    (*((*controlLimits)(0,1))) = LinAlg::Matrix<Type>(this->uMin);
    return controlLimits;
}

template<typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* >* ControlHandler::ModelPredictiveControl<Type>::getControlVariationLimits()
{
    LinAlg::Matrix< LinAlg::Matrix<Type>* > *controlVariationLimits = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*controlVariationLimits)(0,0) = new LinAlg::Matrix<Type>(1,1);
    (*controlVariationLimits)(0,1) = new LinAlg::Matrix<Type>(1,1);
    (*((*controlVariationLimits)(0,0))) = LinAlg::Matrix<Type>(this->duMax);
    (*((*controlVariationLimits)(0,1))) = LinAlg::Matrix<Type>(this->duMin);
    return controlVariationLimits;
}

template<typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* >* ControlHandler::ModelPredictiveControl<Type>::getOutputLimits()
{
    LinAlg::Matrix< LinAlg::Matrix<Type>* > *outputLimits = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*outputLimits)(0,0) = new LinAlg::Matrix<Type>(1,1);
    (*outputLimits)(0,1) = new LinAlg::Matrix<Type>(1,1);
    (*((*outputLimits)(0,0))) = LinAlg::Matrix<Type>(this->yMax);
    (*((*outputLimits)(0,1))) = LinAlg::Matrix<Type>(this->yMin);
    return outputLimits;
}

template<typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* >* ControlHandler::ModelPredictiveControl<Type>::getLimits()
{
    LinAlg::Matrix< LinAlg::Matrix<Type>* > *Limits = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,6);
    (*Limits)(0,0) = new LinAlg::Matrix<Type>(1,1);
    (*Limits)(0,1) = new LinAlg::Matrix<Type>(1,1);
    (*Limits)(0,2) = new LinAlg::Matrix<Type>(1,1);
    (*Limits)(0,3) = new LinAlg::Matrix<Type>(1,1);
    (*Limits)(0,4) = new LinAlg::Matrix<Type>(1,1);
    (*Limits)(0,5) = new LinAlg::Matrix<Type>(1,1);
    (*((*Limits)(0,0))) = LinAlg::Matrix<Type>(this->duMax);
    (*((*Limits)(0,1))) = LinAlg::Matrix<Type>(this->duMin);
    (*((*Limits)(0,2))) = LinAlg::Matrix<Type>(this->yMax);
    (*((*Limits)(0,3))) = LinAlg::Matrix<Type>(this->yMin);
    (*((*Limits)(0,4))) = LinAlg::Matrix<Type>(this->uMax);
    (*((*Limits)(0,5))) = LinAlg::Matrix<Type>(this->uMin);
    return Limits;
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::ModelPredictiveControl<Type>::OutputControlCalc(const ModelHandler::ARX<Type>& gz)
{
    this->setNewModel(gz);
    LinAlg::Matrix<Type> X_state = SSd.getActualState();
//    std::cout << (X_state);
    LinAlg::Matrix<Type> X_input = SSdStateStimated.getActualState();
    LinAlg::Matrix<Type> X = ((X_input - X_state)|| this->SSd.getC()*X_input);

    SSd.setInitialState(X_input);
    LinAlg::Matrix<Type> du;
    if(!this->QP){
        du = this->K*(this->W - SSP.getC()*SSP.getA()*X);
    }
    else
    {
        this->setOptimizationConstraints(duMax,duMin,yMax,yMin,uMax,uMin,U,SSP.getA(),SSP.getB(),SSP.getC(),X);
//        std::cout << 2*((~SSP.getB())*(~SSP.getC())*Q*SSP.getC()*SSP.getB()+R) << "\n";
//        std::cout << 2*(~SSP.getB())*(~SSP.getC())*(~Q)*(SSP.getC()*SSP.getA()*X-W) << "\n";
        this->QP->setfunction2Optimize(2*((~SSP.getB())*(~SSP.getC())*Q*SSP.getC()*SSP.getB()+R),2*(~SSP.getB())*(~SSP.getC())*(~Q)*(SSP.getC()*SSP.getA()*X-W));
        QP->optimize();
        du = QP->getOptimizatedValue();
    }
    this->U = this->U + du(LinAlg::LineVector<Type>(1,this->U.getNumberOfRows()),1);
//    std::cout << du << std::endl;
    LimitControlOutput();

    return this->U;
}


template<typename Type>
LinAlg::Matrix<Type> ControlHandler::ModelPredictiveControl<Type>::OutputControlCalc(const LinAlg::Matrix<Type> &X_input)
{
    LinAlg::Matrix<Type> X_state = SSd.getActualState();
    LinAlg::Matrix<Type> X = ((X_input - X_state)|| this->SSd.getC()*X_input);

    SSd.setInitialState(X_input);

    LinAlg::Matrix<Type> du = this->K*(this->W - SSP.getC()*SSP.getA()*X);
    this->U = this->U + du(LinAlg::LineVector<Type>(1,du.getNumberOfRows(),2),1);
    LimitControlOutput();

    return this->U;
}

template<typename Type>
void ControlHandler::ModelPredictiveControl<Type>::LimitControlOutput()
{
    for(unsigned i = 1; i <= this->U.getNumberOfRows(); ++i)
        if(this->U(i,1) > uMax)
            this->U(i,1) = uMax;
        else if(this->U(i,1) < uMin)
            this->U(i,1) = uMin;
}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::ModelPredictiveControl<Type>::OutputControlCalc(LinAlg::Matrix<Type> X_input, LinAlg::Matrix<Type> W)
{

}

template<typename Type>
LinAlg::Matrix<Type> ControlHandler::ModelPredictiveControl<Type>::OutputControlCalc(LinAlg::Matrix<Type> X_input, LinAlg::Matrix<Type> Q, LinAlg::Matrix<Type> R, LinAlg::Matrix<Type> W)
{

}

template<typename Type>
std::string ControlHandler::ModelPredictiveControl<Type>::print()
{
    std::string str;
    str += "The Model Predictive Control has the following structure:\n\n";
    str += "The prediction horizon is:\n from: "; str << LinAlg::Matrix<Type>(N1);
    str += " to: "; str << LinAlg::Matrix<Type>(N2);
    str += "The control horizon is:\n"; str << LinAlg::Matrix<Type>(NU);
    str += "The Error weigth is:\n"; str << getErrorWeight();
    str += "The Control weigth is:\n"; str << getControlWeight();
    str += "The Controller Gain is:\n"; str << getControlerGain();
    str << SSP;
    str += "The initial state is:\n"; str << getInitialState();
    str += "The reference is:\n"; str << getReference();
    str += '\n';

    return str;
}

template<typename Type>
std::ostream& operator<< (std::ostream& output, ControlHandler::ModelPredictiveControl<Type> rhs)
{
    output << rhs.print();
    return output;
}
