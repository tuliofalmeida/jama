#ifndef __SIM_H_INCLUDED
#define __SIM_H_INCLUDED
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
#include "fstream"

template <class UsedType>
class Sim
{
private:
    LinAlg::Matrix<UsedType> OutPut, InPut, Error, LinSysMultStep, LinSysOneStep, EstOutPut, LinSysParameters, LinSysOutPut;
    int Degree, nSample, nOutPut, nInPut, nError, NonLinDegree;
    bool DataChange;
    std::string TypeModel;

    void SetPolyOneStep();
    void SetMaOneStep();
    void SetFirOneStep();
    void SetArxOneStep();
    void SetArmaxOneStep();
//    void SetBillinearOneStep();
//    void SetNaxrOneStep  (int nInPut,  int OutPut, int NonLinDegree, int nSample);
//    void SetNarmaxOneStep(int nInPut,  int OutPut, int nError, int NonLinDegree, int nSample);

//    void SetArmaxOneStepReal();
    void SetArmaxOMultStep();
    void SetPolyMultStep();

    UsedType SimOneStep();
//    LinAlg::Matrix<UsedType> SimOneStep (int var1, int var2, int var3, string Model);
//    LinAlg::Matrix<UsedType> SimOneStep (int var1, int var2, int var3, int var4, string Model);
//    LinAlg::Matrix<UsedType> SimOneStep (int var1, int var2, int var3, int var4, int var5, string Model);

public:
    Sim(LinAlg::Matrix<UsedType> InPut, LinAlg::Matrix<UsedType> OutPut, std::string Model, int var1 = 0, int var2 = 0, int var3 = 0, int var4 = 0, int var5 = 0);

//    void SetParametersModel();
    LinAlg::Matrix<UsedType> RunSimulation(LinAlg::Matrix<UsedType> LinSysParameters, int nSteps = 0);
    LinAlg::Matrix<UsedType> GetInput();
    LinAlg::Matrix<UsedType> GetRealOutPut();
    LinAlg::Matrix<UsedType> GetEstimatedOutPut();
    LinAlg::Matrix<UsedType> GetError();
    LinAlg::Matrix<UsedType> GetLinSysOutPut();
    LinAlg::Matrix<UsedType> GetLinMatrix();

};

#endif // SIM_H
