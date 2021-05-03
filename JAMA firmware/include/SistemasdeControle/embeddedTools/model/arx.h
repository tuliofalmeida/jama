#ifndef ARX_H
#define ARX_H

#include "model.h"


namespace ModelHandler {
    template <typename Type>
    class ARX : public Model<Type>
    {
    public:
        ARX(unsigned nInputDelay, unsigned nOutputDelay,
            unsigned delay = 0,
            unsigned qdtInputVar = 1, unsigned qdtOutputVar = 1,
            double sampleTime = 0.1);
        ARX(const ARX<Type>& OtherArxModel);
        template<typename OtherType>
        ARX(const ModelHandler::ARX<OtherType>& otherARXFunction);

        ARX<Type>& operator= (const ARX<Type>& otherARXFunction);
        template<typename OtherARXFunctionType>
        ARX<Type>& operator= (const ARX<OtherARXFunctionType>& otherARXFunction);

        unsigned getNumberOfInputDelays() const {return this->nInputDelay;}
        unsigned getNumberOfOutputDelays() const {return this->nOutputDelay;}
        unsigned getNumberOfVariables() const;
        unsigned getMaxnInOut () const { return this->maxnInOut;}
        unsigned getNSample () const { return this->nSample;}

        Type getTimeSimulation() const { return this->timeSimulation;}
        Type getTransportDelay() const { return this->delay;}

        std::string print();
        unsigned getNumberOfInputs() const {return this->qdtInputVar;}
        unsigned getNumberOfOutputs() const {return this->qdtOutputVar;}
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> Input);
        void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> PastOutput);

    private:
        unsigned nInputDelay  , nOutputDelay,
                 qdtInputVar, qdtOutputVar, nSample,
                 maxnInOut, delay;
        LinAlg::Matrix<Type> InputLinearVector, OutputLinearVector;
    };
    template<typename Type> // ok
    std::ostream& operator<< (std::ostream& output, ModelHandler::ARX<Type> model);
    template<typename Type> //ok
    std::string&  operator<< (std::string& output,  ModelHandler::ARX<Type> model);
}

#include "arx.hpp"
#endif // ARX_H
