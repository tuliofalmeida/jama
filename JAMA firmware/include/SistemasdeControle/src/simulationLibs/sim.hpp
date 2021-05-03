#include "SistemasdeControle/headers/simulationLibs/sim.h"

template <class UsedType>
Sim<UsedType>::Sim(LinAlg::Matrix<UsedType> InPut, LinAlg::Matrix<UsedType> OutPut, std::string Model, int var1, int var2, int var3, int var4, int var5)
{
    this->InPut = InPut;
    this->OutPut = OutPut;
    DataChange = 1;

    if(Model == "POLINOMIAL")
    {
        this->TypeModel = Model;
        this->Degree    = var1;
        this->nSample   = var2;

        this->nError = 0;
        this->nInPut = 0;
        this->NonLinDegree = 0;
        this->nOutPut = 0;
    }
    else if(Model == "MA")
    {
        this->TypeModel = Model;
        this->nOutPut   = var1;
        this->nSample   = var2;

        this->nError = 0;
        this->nInPut = 0;
        this->NonLinDegree = 0;
        this->Degree = 0;
    }
    else if(Model == "FIR")
    {
        this->TypeModel = Model;
        this->nInPut    = var1;
        this->nSample   = var2;

        this->nError = 0;
        this->nOutPut = 0;
        this->NonLinDegree = 0;
        this->Degree = 0;
    }
    else if(Model == "ARX")
    {
        this->TypeModel = Model;
        this->nInPut    = var1;
        this->nOutPut   = var2;
        this->nSample   = var3;

        this->nError = 0;
        this->NonLinDegree = 0;
        this->Degree = 0;
    }
    else if(Model == "ARMAX")
    {
        this->TypeModel = Model;
        this->nInPut    = var1;
        this->nOutPut   = var2;
        this->nError    = var3;
        this->nSample   = var4;

        this->NonLinDegree = 0;
        this->Degree = 0;
    }
//    else if(Model == "NARX")
//    {
//        this->TypeModel = Model;
//        this->nInPut    = var1;
//        this->nSample   = var2;
        this->NonLinDegree = var5;
//    }
//    else if(Model == "NARMAX")
//    {
//        this->TypeModel = Model;
//        this->nInPut    = var1;
//        this->nSample   = var2;
//    }
}

//-----------------------------------------------------------------------//
//--------------------One Step Model Construction------------------------//
//-----------------------------------------------------------------------//

template <class UsedType>
void Sim<UsedType>::SetPolyOneStep()
{
    this->LinSysOneStep = LinAlg::Ones<UsedType>(1, (this->Degree + 1)*this->InPut.getNumberOfColumns());

    for(int i = 0; i < this->InPut.getNumberOfColumns(); i++)
        for(int j = 2; j <= this->Degree + 1; j++)
            this->LinSysOneStep(1, j + ((this->Degree + 1)*i)) = pow((double) this->InPut(this->nSample, i + 1), j - 1);
}

template <class UsedType>
void Sim<UsedType>::SetArmaxOneStep()
{
    this->LinSysOneStep = LinAlg::Zeros<UsedType>(1, this->nInPut*this->InPut.getNumberOfColumns() + this->nOutPut*this->OutPut.getNumberOfColumns() + this->nError);

    int cont = 1;
    for(int i = 1; i <= this->OutPut.getNumberOfColumns(); i++)
    {
        for(int j = 1; j <= this->nOutPut; j++)
        {
            this->LinSysOneStep(1, cont) = -this->EstOutPut(this->nSample - j, i);
            cont++;
        }
    }
    for(int i = 1; i <= this->InPut.getNumberOfColumns(); i++)
    {
        for(int j = 1; j <= this->nInPut; j++)
        {
            this->LinSysOneStep(1, cont) = this->InPut(this->nSample - j, i);
            cont++;
        }
    }

    for(int j = 1; j <= this->nError; j++)
    {
        this->LinSysOneStep(1, cont) = this->Error(this->nSample - j, 1);
        cont++;
    }
}

//-----------------------------------------------------------------------//
//---------------------Mult Step Model Construction----------------------//
//-----------------------------------------------------------------------//

template <class UsedType>
void Sim<UsedType>::SetPolyMultStep()
{
    this->LinSysOutPut = this->OutPut;
    this->LinSysMultStep = LinAlg::Ones<UsedType>(this->LinSysOutPut.getNumberOfRows(), (this->Degree + 1)*this->InPut.getNumberOfColumns());

    for(int k = 1; k <= this->LinSysOutPut.getNumberOfRows(); k++)
        for(int i = 0; i < this->InPut.getNumberOfColumns(); i++)
            for(int j = 2; j <= this->Degree + 1; j++)
                this->LinSysOneStep(k, j + ((this->Degree + 1)*i)) = pow((double) this->InPut(this->nSample, i + 1), j - 1);
}

template  <class UsedType>
void Sim<UsedType>::SetArmaxOMultStep()
{
    int maxNuNy,minRowInOut;

    if(this->nOutPut > this->nInPut)
        maxNuNy = this->nOutPut;
    else
        maxNuNy = this->nInPut;

    if(this->OutPut.getNumberOfRows() > this->InPut.getNumberOfRows())
        minRowInOut = this->InPut.getNumberOfRows();
    else
        minRowInOut = this->OutPut.getNumberOfRows();

    this->LinSysMultStep = LinAlg::Zeros<UsedType>(minRowInOut - maxNuNy, this->nInPut*this->InPut.getNumberOfColumns() + this->nOutPut*this->OutPut.getNumberOfColumns() + this->nError);

    for(int k = maxNuNy + 1; k <= minRowInOut; k++)
    {
        int cont = 1;
        for(int i = 1; i <= this->OutPut.getNumberOfColumns(); i++)
        {
            for(int j = 1; j <= this->nOutPut; j++)
            {
                this->LinSysMultStep(k - maxNuNy , cont) = -this->OutPut(k - j, i);
                cont++;
            }
            this->LinSysOutPut(k - maxNuNy, i) = this->OutPut(k,i);
        }

        for(int i = 1; i <= this->InPut.getNumberOfColumns(); i++)
        {
            for(int j = 1; j <= this->nInPut; j++)
            {
                this->LinSysMultStep(k - maxNuNy, cont) = this->InPut(k - j, i);
                cont++;
            }
        }

        for(int j = 1; j <= this->nError; j++)
        {
            this->LinSysMultStep(k - maxNuNy, cont) = this->Error(k - j, 1);
            cont++;
        }

    }

}



//-----------------------------------------------------------------------//
//------------------------One Step Model Simulation----------------------//
//-----------------------------------------------------------------------//

template <class UsedType>
UsedType Sim<UsedType>::SimOneStep()
{
    this->LinSysParameters = LinSysParameters;
    if(this->TypeModel == "POLINOMIAL")
    {
        if(this->DataChange == 1)
            this->SetPolyMultStep();
        if(nSample != 0)
            this->SetPolyOneStep();
    }

    else if(this->TypeModel == "MA" || this->TypeModel == "FIR" || this->TypeModel == "ARX" || this->TypeModel == "ARMAX")
    {
        if(this->DataChange == 1)
            this->SetArmaxOMultStep();
        if(nSample != 0)
            this->SetArmaxOneStep();
    }

    this->DataChange = 0;
    if(nSample != 0)
        return ((this->LinSysOneStep*this->LinSysParameters)(1,1));
    else
        return ((this->LinSysMultStep*this->LinSysParameters)(1,1));
}

//-----------------------------------------------------------------------//
//---------------------Gathering all the Simulation----------------------//
//-----------------------------------------------------------------------//
template <class UsedType>
LinAlg::Matrix<UsedType> Sim<UsedType>::RunSimulation(LinAlg::Matrix<UsedType> LinSysParameters, int nSteps)
{
    this->nSample = nSteps;
    this->LinSysParameters = LinSysParameters;
    this->EstOutPut = LinAlg::Zeros<UsedType>(nSteps, 1);
    this->SimOneStep();
    return this->EstOutPut;
}

//-----------------------------------------------------------------------//
//------------------------Getting OutPut Data----------------------------//
//-----------------------------------------------------------------------//

template  <class UsedType>
LinAlg::Matrix<UsedType> Sim<UsedType>::GetInput()
{
    return this->InPut;
}

template  <class UsedType>
LinAlg::Matrix<UsedType> Sim<UsedType>::GetRealOutPut()
{
    return this->OutPut;
}

template  <class UsedType>
LinAlg::Matrix<UsedType> Sim<UsedType>::GetEstimatedOutPut()
{
    return this->EstOutPut;
}

template  <class UsedType>
LinAlg::Matrix<UsedType> Sim<UsedType>::GetLinSysOutPut()
{
    return this->LinSysOutPut;
}

template  <class UsedType>
LinAlg::Matrix<UsedType> Sim<UsedType>::GetLinMatrix()
{
    return this->LinSysMultStep;
}

template  <class UsedType>
LinAlg::Matrix<UsedType> Sim<UsedType>::GetError()
{
    return this->Error;
}

template class Sim<float>;
template class Sim<double>;
