#ifndef NFIR_H
#define NFIR_H
#include "SistemasdeControle/headers/modelLibs/model.h"

#include "SistemasdeControle/headers/modelLibs/model.h"

namespace ModelHandler {
    template <class Type>
    class NFIR : public Model<Type>
    {
    public:
        NFIR(unsigned nInputpar = 1, unsigned degree = 1,
            unsigned delay = 0,
            unsigned qdtInputVar = 1, unsigned qdtOutputVar = 1,
            double sampleTime = 0.1);
        NFIR(const NFIR<Type>& OtherNFIRModel);

        unsigned getNumberOfInputs() const;
        unsigned getNumberOfOutputs() const;
        unsigned getNumberOfInputDelays() const;
        unsigned getNumberOfOutputDelays() const;

        double getSampleTime() const;
        unsigned getNumberOfVariables();

        void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> PastOutput = 0);
        void setLinearModel (LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);


        std::string print();
        Type sim(Type input);
        Type sim(Type input, Type output = 0);
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> Input);
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);
        LinAlg::Matrix<Type> sim(Type lsim, Type lmax, Type step);

    private:
        unsigned nInputpar, delay, degree,
                 qdtInputVar, qdtOutputVar, nSample,
                 sampleTime;
    };
}

#include "SistemasdeControle/src/modelLibs/nfir.hpp"
#endif // NFIR_H
