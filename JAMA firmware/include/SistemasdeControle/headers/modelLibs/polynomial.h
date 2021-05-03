#ifndef Polynomial_H
#define Polynomial_H
#ifdef testModel
    #include "../../../headers/modelLibs/model.h"
#else
    #include "SistemasdeControle/headers/modelLibs/model.h"
#endif

namespace ModelHandler {
    template <typename Type>
    class Polynomial : public Model<Type>
    {
    public:
        Polynomial(uint8_t degree, uint8_t nInput = 1,  uint8_t nOutput = 1);
        Polynomial(const Polynomial<Type>& OtherPolynomialModel);
        template<typename OtherType>
        Polynomial(const ModelHandler::Polynomial<OtherType>& otherPolynomialFunction);

        Polynomial<Type>& operator= (const Polynomial<Type>& otherPolynomialFunction);
        template<typename OtherPolynomialFunctionType>
        Polynomial<Type>& operator= (const Polynomial<OtherPolynomialFunctionType>& otherPolynomialFunction);

        operator std::string(){return this->print();}

        unsigned getNumberOfInputDelays() const{ return 0;}
        unsigned getNumberOfInputs() const{ return this->nInput;}
        unsigned getNumberOfOutputDelays() const{ return 0;}
        unsigned getNumberOfOutputs() const{ return this->nOutput;}
        unsigned getNumberOfVariables() const{ return this->nInput*(this->degree+1);}
        unsigned getMaxnInOut () const { return 0;}
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
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output){}
        LinAlg::Matrix<Type> sim(Type lmin, Type lmax, Type step);

    private:
        unsigned nSample;
        uint8_t degree, nInput, nOutput;
    };

    template<typename Type> // ok
    std::ostream& operator<< (std::ostream& output, ModelHandler::Polynomial<Type> arx);
    template<typename Type> //ok
    std::string&  operator<< (std::string& output,  ModelHandler::Polynomial<Type> arx);
}

#ifdef testModel
    #include "../../../src/modelLibs/polynomial.hpp"
#else
    #include "SistemasdeControle/src/modelLibs/polynomial.hpp"
#endif

#endif // Polynomial_H
