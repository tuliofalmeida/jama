#ifdef testModel
    #include "../../../headers/optimizationLibs/pso.h"
#else
    #include "SistemasdeControle/headers/optimizationLibs/pso.h"
#endif

#include <ctime>

template <class UsedType>
OptimizationHandler::PSO<UsedType>::PSO(ModelHandler::Model<UsedType> *model, const uint32_t &varNum, const uint32_t &PopSize,
                                        const uint32_t &GenSize, const UsedType &phi1, const UsedType &phi2, const UsedType &omega,
                                        const UsedType &minX, const UsedType &maxX, const bool &MinMax)
{
    this->model   = model;
    this->varNum  = varNum;
    this->PopSize = PopSize;
    this->GenSize = GenSize;
    this->phi1    = phi1;
    this->phi2    = phi2;
    this->omega   = omega;
    this->minX = minX;
    this->maxX = maxX;
    this->MinMax  = MinMax;
    srand((time(NULL)));
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::initAlgorithm()
{
    //LinAlg::Matrix<UsedType> init = "0.203979,0.097670,0.445005,0.369224,0.121721,0.200847,0.974407,0.999997,2.999732";
    this->X = this->maxX/50*LinAlg::Random<UsedType>(this->PopSize, this->varNum);
//    for(uint32_ti = 0; i < this->X.getNumberOfRows(); ++i)
//        for(uint32_tj = 0; j < this->X.getNumberOfColumns(); ++j)
//            this->X(i,j) += init(0,j);

    //std::cout << X;
    this->V = 0.01*LinAlg::Random<UsedType>(this->PopSize, this->varNum);
    this->P = this->maxX/50*LinAlg::Random<UsedType>(this->PopSize, this->varNum);
//    for(uint32_ti = 0; i < this->P.getNumberOfRows(); ++i)
//        for(uint32_tj = 0; j < this->X.getNumberOfColumns(); ++j)
//            this->P(i,j) += init(0,j);

    this->Pfitness = Evaluation(this->P);
    this->G = this->maxX/10 *LinAlg::Random<UsedType>(1, this->varNum);
    this->Xfitness = Evaluation(this->X);
//    Xfitness.print();
    this->Gfitness = Evaluation(this->G);
//    Gfitness.print();
    this->Pfitness = this->Xfitness;
  
}

template <class UsedType>
LinAlg::Matrix<UsedType> OptimizationHandler::PSO<UsedType>::Evaluation(LinAlg::Matrix<UsedType> Matrix2Evaluate)
{
    LinAlg::Matrix<UsedType> ret(Matrix2Evaluate.getNumberOfRows(), 1);
    LinAlg::Matrix<UsedType> Error;
    //TODO -> Tornar a função mais fléxivel.

    for(uint32_t i = 0; i < Matrix2Evaluate.getNumberOfRows(); i++)
    {
      model->setModelCoef(Matrix2Evaluate.getRow(i));
      Error =  10000*(Out - model->sim(In));
      ret(i,0) = ((~Error)*Error)(0,0);
    }

    return ret;
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::ParticleUpdate()
{
    this->X = this->X + this->V ;
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::VelocityUpdate()
{
//    srand((time(NULL)));
    double Rand1, Rand2;


    for(uint32_t i = 0; i < this->PopSize; i++)
        for(uint32_t j = 0; j < this->varNum; j++)
        {
            Rand1 = rand()*this->phi1/RAND_MAX;
            Rand2 = rand()*this->phi2/RAND_MAX;
            this->V(i, j) = (this->omega*this->V(i,j) + Rand1*(this->P(i,j) - this->X(i,j)) + Rand2*(this->G(0,j) - this->X(i,j)));// + (this->maxX/1e4)*rand()/RAND_MAX;
        }
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::ParticleEvaluation()
{
    this->Xfitness = Evaluation(this->X);
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::FitnessUpdate()
{
    if(this->MinMax == true)
        FitnessUpdateMax();
    else
        FitnessUpdateMin();
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::FitnessUpdateMin()
{
  for (uint32_t i = 0; i < this->PopSize; i++)
  {
      if (this->Xfitness(i,0) < this->Pfitness(i,0))
      {
          this->Pfitness(i,0) = this->Xfitness(i,0);
          for(uint32_t j = 0; j < this->varNum; j++)
            this->P(i, j) = this->X(i,j);
      }

      if (this->Pfitness(i,0) < this->Gfitness(0,0))
      {
          this->Gfitness(0,0) = this->Pfitness(i,0);
          for(uint32_t j = 0; j < this->varNum; j++)
            this->G(0, j) = this->P(i,j);
      }
  }
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::FitnessUpdateMax()
{
    for (uint32_t i = 0; i < this->PopSize; i++)
    {
        if (this->Xfitness(i,0) > this->Pfitness(i,0))
        {
            this->Pfitness(i,0) = this->Xfitness(i,0);
            for(uint32_t j = 0; j < this->varNum; j++)
              this->P(i, j) = this->X(i,j);
        }

        if (this->Pfitness(i,0) > this->Gfitness(0,0))
        {
            this->Gfitness(0,0) = this->Pfitness(i,0);
            for(uint32_t j = 0; j < this->varNum; j++)
                this->G(0, j) = this->P(i,j);
        }
    }
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::Optimize()
{
//    clock_t start, stop;

    std::cout << "Iteration  Gfitness  BestSolution \n";

    initAlgorithm();

    for(uint32_t i = 0; i < this->GenSize; i++)
    {
        VelocityUpdate();
        ParticleUpdate();

//        start = clock();
        this->limits();
        this->Xfitness = Evaluation(this->X);
//        stop = clock();
//        this->Stime = (double) (stop-start)/CLOCKS_PER_SEC;
//        cout << this->Stime << endl;

        FitnessUpdate();
        std::cout << i+1 << ": " << (Gfitness|G);
//        Gfitness.print();
//        this->GGen = this->GGen||this->G; // função lenta
//        this->GfitnessGen = this->GfitnessnTime||this->Gfitness; // função lenta
    }
    this->OptimizatedVariable = this->G;
//    return this->G;

}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::Run(uint32_t nTimes)
{
    this->GnTimes = LinAlg::Zeros<UsedType>(nTimes, this->G.getNumberOfColumns());
    this->GfitnessnTime = LinAlg::Zeros<UsedType>(nTimes, 1);
    for (uint32_t i = 0; i < nTimes; i++)
    {
        this->Optimize();
//        this->GnTimes = this->GnTimes||this->G;
        this->GfitnessnTime(i, 0) = this->Gfitness(0,0);
        this->RunTime(i, 0) = this->Stime;
//        this->Gfitness.print();
//        this->G.print();
    }

//    this->GfitnessnTime.print();
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::setData(LinAlg::Matrix<UsedType> dataIn, LinAlg::Matrix<UsedType> dataOut)
{
    this->In = dataIn; Out = dataOut;
}

template <class UsedType>
double OptimizationHandler::PSO<UsedType>::getTime()
{
    return this->Stime;
}

template <class UsedType>
void OptimizationHandler::PSO<UsedType>::limits()
{
    for(uint32_t i = 0; i < this->PopSize; i++)
        for(uint32_t j = 0; j < this->varNum; j++)
        {
            if(this->X(i,j) > maxX)
                this->X(i,j) = maxX;
            if(this->X(i,j) < minX)
                this->X(i,j) = minX;
        }
}
