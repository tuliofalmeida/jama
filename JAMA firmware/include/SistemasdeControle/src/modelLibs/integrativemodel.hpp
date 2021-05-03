#ifdef testModel
    #include "../../../headers/modelLibs/integrativemodel.h"
#else
    #include "SistemasdeControle/headers/modelLibs/integrativemodel.h"
#endif


template <class Type>
ModelHandler::IntegrativeModel<Type>::IntegrativeModel(
                  LinAlg::Matrix<Type> A , LinAlg::Matrix<Type> B,
                  LinAlg::Matrix<Type> C , LinAlg::Matrix<Type> D)
{
    this->A                  =    A;
    this->B                  =    B;
    this->C                  =    C;
    this->D                  =    D;
    this->Continuous         = true;
    this->SampleTime         =  0.1;
    this->TimeSimulation     =   10;
    this->nDiscretization    =    6;

    this->initialState = LinAlg::Zeros<Type> (A.getNumberOfRows(),B.getNumberOfColumns());
    this->X = this->initialState;
}

template <class Type>
ModelHandler::IntegrativeModel<Type>::IntegrativeModel(LinAlg::Matrix<Type> Ad, LinAlg::Matrix<Type> Bd,
                  LinAlg::Matrix<Type> C , LinAlg::Matrix<Type> D,
                  Type SampleTime)
{
    this->Ad                 =    Ad;
    this->Bd                 =    Bd;
    this->C                  =    C;
    this->D                  =    D;
    this->Continuous         = false;
    this->SampleTime         = SampleTime;
    this->TimeSimulation     =   10;
    this->nDiscretization    =    6;

    this->initialState = LinAlg::Zeros<Type>(Ad.getNumberOfRows(),Bd.getNumberOfColumns());
    this->X = this->initialState;
}

template <class Type>
ModelHandler::IntegrativeModel<Type>::IntegrativeModel(ModelHandler::StateSpace<Type> &SS)
{
    this->Continuous = SS.isContinuous();
    if(Continuous)
    {
        this->A = LinAlg::Zeros<Type>(SS.getC().getNumberOfRows()+SS.getA().getNumberOfRows(),1)|(SS.getC()||SS.getA());

        this->B = (LinAlg::Zeros<Type>(SS.getC().getNumberOfRows()+SS.getB().getNumberOfColumns(),1)||SS.getB());
        //Retirado da apostila de meneghet
    }else{
        this->Ad = ( SS.getA()            | LinAlg::Zeros<Type>(SS.getA().getNumberOfRows(),SS.getC().getNumberOfRows()))
                || ((SS.getC()*SS.getA()) | LinAlg::Eye<Type>  (SS.getC().getNumberOfRows()));
//        Ba = [B; C*B];
        this->Bd = (SS.getB() || SS.getC()*SS.getB());
    }
    this->C = (LinAlg::Zeros<Type>(SS.getC().getNumberOfRows(),SS.getA().getNumberOfColumns()) | LinAlg::Eye<Type>(SS.getC().getNumberOfRows()));

    this->D = SS.getD();

    this->Continuous = SS.isContinuous();
    this->SampleTime = SS.getSampleTime();
}

//template <class Type>
//ModelHandler::IntegrativeModel<Type>& ModelHandler::IntegrativeModel<Type>::operator= (const ModelHandler::IntegrativeModel<Type>& otherIntegrativeModel) const
//{
//    this->A = otherIntegrativeModel.A;
//    this->Ad = otherIntegrativeModel.Ad;
//    this->B = otherIntegrativeModel.B;
//    this->Bd = otherIntegrativeModel.Bd;
//    this->C = otherIntegrativeModel.C;
//    this->D = otherIntegrativeModel.D;
//    this->Continuous = otherIntegrativeModel.Continuous;
//    this->EstOutput = otherIntegrativeModel.EstOutput;
//    this->initialState = otherIntegrativeModel.initialState;
//    this->Input = otherIntegrativeModel.Input;
//    this->input = otherIntegrativeModel.input;
//    this->InputLinearVector = otherIntegrativeModel.InputLinearVector;
//    this->LinearEqualityB = otherIntegrativeModel.LinearEqualityB;
//    this->LinearEqualityVectorB = otherIntegrativeModel.LinearEqualityVectorB;
//    this->LinearMatrixA = otherIntegrativeModel.LinearMatrixA;
//    this->LinearVectorA = otherIntegrativeModel.LinearVectorA;
//    this->lmax = otherIntegrativeModel.lmax;
//    this->lmin = otherIntegrativeModel.lmin;
//    this->ModelCoef = otherIntegrativeModel.ModelCoef;
//    this->nDiscretization = otherIntegrativeModel.nDiscretization;
//    this->Output = otherIntegrativeModel.Output;
//    this->output = otherIntegrativeModel.output;
//    this->OutputLinearVector = otherIntegrativeModel.OutputLinearVector;
//    this->SampleTime = otherIntegrativeModel.SampleTime;
//    this->step = otherIntegrativeModel.step;
//    this->TimeSimulation = otherIntegrativeModel.TimeSimulation;
//    this->X = otherIntegrativeModel.X;
//}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::IntegrativeModel<Type>::getA() const
{
    if(this->Continuous)
        return this->A;
    else
        return this->Ad;
}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::IntegrativeModel<Type>::getB() const
{
    if(this->Continuous)
        return this->B;
    else
        return this->Bd;
}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::IntegrativeModel<Type>::getC() const
{
    return this->C;
}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::IntegrativeModel<Type>::getD() const
{
    return this->D;
}

template <class Type>
void ModelHandler::IntegrativeModel<Type>::setContinuous(bool Continuous)
{
    this->Continuous = Continuous;
}

template <class Type>
void ModelHandler::IntegrativeModel<Type>::setSampleTime(double SampleTime)
{
    this->SampleTime = SampleTime;
}

template <class Type>
void ModelHandler::IntegrativeModel<Type>::setInitialState(LinAlg::Matrix<Type> X0)
{
    this->initialState = X0;
}

template <class Type>
void ModelHandler::IntegrativeModel<Type>::SetObserverParameter(LinAlg::Matrix<Type> L)
{
    this->L = L;
}

template <class Type>
bool ModelHandler::IntegrativeModel<Type>::isContinuous()  const
{
    return Continuous;
}

template <class Type>
bool ModelHandler::IntegrativeModel<Type>::isObservable()  const
{

}

template <class Type>
bool ModelHandler::IntegrativeModel<Type>::isControlable() const
{

}

template <class Type>
Type ModelHandler::IntegrativeModel<Type>::sim(Type u)
{

}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::IntegrativeModel<Type>::sim(LinAlg::Matrix<Type> u)
{

}

template <class Type>
LinAlg::Matrix<Type> ModelHandler::IntegrativeModel<Type>::sim(Type lmin, Type lmax, Type step)
{

}

template <class Type>
std::string ModelHandler::IntegrativeModel<Type>::print()
{
    std::string output;

    if(this->Continuous == true){
        output += "The Continuous Integrative Model is: \n\nA = \n";
        output << this->A; output += "\n\nB = \n";
        output << this->B; output += "\n\nC = \n";

    }else{
        output += "The Discrete Integrative Model is: \n\nA = \n";
        output << this->Ad; output += "\n\nB = \n";
        output << this->Bd; output += "\n\nC = \n";
    }

    output << this->C; output += "\n\nD = \n";
    output << this->D; output += '\n';

    return output;
}

template<typename Type>
std::ostream& ModelHandler::operator<< (std::ostream& output, ModelHandler::IntegrativeModel<Type> SS)
{
    output << SS.print();
    return output;
}

template<typename Type>
std::string& ModelHandler::operator<< (std::string& output, ModelHandler::IntegrativeModel<Type> SS)
{
    output += SS.print();
    return output;
}

