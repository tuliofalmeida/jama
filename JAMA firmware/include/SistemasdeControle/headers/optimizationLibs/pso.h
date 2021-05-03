#ifndef _PSO_H_INCLUDED
#define _PSO_H_INCLUDED

#ifdef testModel
    #include "../../../headers/modelLibs/model.h"
    #include "../../../headers/optimizationLibs/optimization.h"
#else
    #include "SistemasdeControle/headers/optimizationLibs/optimization.h"
    #include "SistemasdeControle/headers/modelLibs/model.h"
#endif

namespace OptimizationHandler {
    template <class UsedType>
    class PSO : public  Optimization<UsedType>
    {
    private:
        bool MinMax;
        uint32_t varNum, PopSize, GenSize;
        UsedType phi1, phi2, omega, Stime, minX, maxX;
        LinAlg::Matrix<UsedType> V, X, P, G, GGen, GnTimes,
                         Xfitness, Pfitness, Gfitness,
                         GfitnessGen, GfitnessnTime, RunTime, In,Out;
        ModelHandler::Model<UsedType> *model;


        LinAlg::Matrix<UsedType> Evaluation(LinAlg::Matrix<UsedType> Matrix2Evaluate);
        void ParticleUpdate();
        void ParticleEvaluation();
        void VelocityUpdate();
        void initAlgorithm();
        void FitnessUpdate();
        void FitnessUpdateMin();
        void FitnessUpdateMax();
        void limits();

    public:
        PSO(ModelHandler::Model<UsedType> *model, const uint32_t &varNum = 1, const uint32_t &PopSize = 80,
            const uint32_t &GenSize = 2000, const UsedType &phi1 = 1, const UsedType &phi2 = 1, const UsedType &omega = 1,
            const UsedType &minX = 0, const UsedType &maxX = 10, const bool &MinMax = false);
        ~PSO(){}

        void Optimize();
        void Optimize(LinAlg::Matrix<UsedType> dataIn, LinAlg::Matrix<UsedType> dataOut){}
        void Run(uint32_t nTimes);
        void setData(LinAlg::Matrix<UsedType> dataIn, LinAlg::Matrix<UsedType> dataOut);

        double getTime();
    };
}

#ifdef testModel
    #include "../../../src/optimizationLibs/pso.hpp"
#else
    #include "SistemasdeControle/src/optimizationLibs/pso.hpp"
#endif

#endif // PSO_H
