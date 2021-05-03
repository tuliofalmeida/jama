#ifndef __PSO_H_INCLUDED
#define __PSO_H_INCLUDED
#include "SistemasdeControle/headers/optimizationLibs/optimization.h"
#include "SistemasdeControle/headers/modelLibs/model.h"

template <class UsedType>
class PSO : public  Optimization<UsedType>
{
private:
    bool MinMax;
    int varNum, PopSize, GenSize;
    double phi1, phi2, omega, Stime;
    LinAlg::Matrix<UsedType> V, X, P, G, GGen, GnTimes,
                     Xfitness, Pfitness, Gfitness,
                     GfitnessGen, GfitnessnTime, RunTime;
    Model<UsedType> *model;


    LinAlg::Matrix<UsedType> Evaluation(LinAlg::Matrix<UsedType> Matrix2Evaluate);
    void ParticleUpdate();
    void ParticleEvaluation();
    void VelocityUpdate();
    void initAlgorithm();
    void FitnessUpdate();
    void FitnessUpdateMin();
    void FitnessUpdateMax();

public:
    PSO(Model<UsedType> *model);
    PSO(Model<UsedType> *model, int    varNum, int PopSize, int GenSize);
    PSO(Model<UsedType> *model, int    varNum, int PopSize, int GenSize,
        double           phi1 , double phi2);
    PSO(Model<UsedType> *model, int    varNum, int    PopSize, int  GenSize,
        double           phi1 , double phi2  , double omega  , bool MinMax);
    ~PSO();

    void Optimize();
    void Run(int nTimes);
    void setData(LinAlg::Matrix<UsedType> dataIn, LinAlg::Matrix<UsedType> dataOut);

    double getTime();
};

#endif // PSO_H
