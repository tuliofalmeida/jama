#ifndef ARX_H
#define ARX_H
#ifdef testModel
    #include "../../../headers/modelLibs/model.h"
#else
    #include "SistemasdeControle/headers/modelLibs/model.h"
#endif

namespace ModelHandler {
    template <typename Type>
    class ARX : public Model<Type>
    {
    public:
        ARX(unsigned nInputpar, unsigned nOutputpar,
            unsigned delay = 0,
            unsigned qdtInputVar = 1, unsigned qdtOutputVar = 1,
            double sampleTime = 0.1);
        ARX(const ARX<Type>& OtherArxModel);
        template<typename OtherType>
        ARX(const ModelHandler::ARX<OtherType>& otherARXFunction);

        ARX<Type>& operator= (const ARX<Type>& otherARXFunction);
        template<typename OtherARXFunctionType>
        ARX<Type>& operator= (const ARX<OtherARXFunctionType>& otherARXFunction);

        operator std::string(){return this->print();}

        unsigned getNumberOfInputDelays() const;
        unsigned getNumberOfInputs() const;
        unsigned getNumberOfOutputDelays() const;
        unsigned getNumberOfOutputs() const;
        unsigned getNumberOfVariables() const;
        unsigned getMaxnInOut () const { return this->maxnInOut;}
        unsigned getNSample () const { return this->nSample;}

        Type getTimeSimulation() const { return this->timeSimulation;}
        Type getTransportDelay() const { return this->delay;}

        LinAlg::Matrix<Type> getInputLinearVector() const { return this->InputLinearVector;}
        LinAlg::Matrix<Type> getOutputLinearVector() const { return this->OutputLinearVector;}

        void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> PastOutput);
        void setLinearModel (LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);
        void setInitialOutputValue(const LinAlg::Matrix<Type> &Output);

        std::string print();
        Type sim(Type input);
        Type sim(Type input, Type output);
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> Input);
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);
        LinAlg::Matrix<Type> sim(Type lmin, Type lmax, Type step);

    private:
        unsigned nInputpar  , nOutputpar,
                 qdtInputVar, qdtOutputVar, nSample,
                 maxnInOut;
    };

    template<typename Type> // ok
    std::ostream& operator<< (std::ostream& output, ModelHandler::ARX<Type> arx);
    template<typename Type> //ok
    std::string&  operator<< (std::string& output,  ModelHandler::ARX<Type> arx);
}

#ifdef testModel
    #include "../../../src/modelLibs/arx.hpp"
#else
    #include "SistemasdeControle/src/modelLibs/arx.hpp"
#endif

#endif // ARX_H
