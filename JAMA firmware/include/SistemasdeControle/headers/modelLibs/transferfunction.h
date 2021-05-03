#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include "model.h"
#include "arx.h"
#include "statespace.h"

namespace ModelHandler {
    template <typename Type>
    class TransferFunction : public Model<Type>
    {
    public:
        TransferFunction(int rows, int cols);
        TransferFunction(const PolynomHandler::Polynom<Type> &TFSISO);
        TransferFunction(LinAlg::Matrix< PolynomHandler::Polynom<Type> > TF);
        TransferFunction(const LinAlg::Matrix<Type> &numPol, const LinAlg::Matrix<Type> &denPol);
        TransferFunction(): var('s'), Continuous(1), TF(1,1) { this->step = 0.1; this->timeSimulation = 10;}

        TransferFunction(int rows, int cols, double sampleTime);
        TransferFunction(const PolynomHandler::Polynom<Type> &TFSISO, double sampleTime);
        TransferFunction(LinAlg::Matrix< PolynomHandler::Polynom<Type> > TF, double sampleTime);
        TransferFunction(const LinAlg::Matrix<Type> &numPol, const LinAlg::Matrix<Type> &denPol, double sampleTime);
        template<typename OtherType>
        TransferFunction (const ModelHandler::TransferFunction<OtherType>& otherPolynom);

        LinAlg::Matrix<Type> getTransportDelay () const {return transportDelay;}
        bool isContinuous() const;
        char getVar() const {return this->var;}
        double getSampleTime() const;
        double getTimeSimulation() const{return this->timeSimulation;}
        int getNumberOfRows() const; // OK
        int getNumberOfColumns() const; // OK
        unsigned getNumberOfVariables() const{return TF.getNumberOfRows() + TF.getNumberOfColumns();}
        unsigned getNumberOfInputs() const { return TF.getNumberOfRows();}
        unsigned getNumberOfOutputs() const { return TF.getNumberOfColumns();}

        void setTransportDelay(const LinAlg::Matrix<Type> &TD){this->transportDelay = TD;}
        void setContinuous(const bool &continuous); //ok
        void setSampleTime(const double &sampleTime);//ok
        void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);
        void setLinearModel (LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output); // não feito

        PolynomHandler::Polynom<Type>& operator()(int row, int column); // ok
        PolynomHandler::Polynom<Type>  operator()(int row, int column) const; // ok

        void operator= (const PolynomHandler::Polynom<Type> &rhs);
        TransferFunction<Type>& operator= (const TransferFunction<Type>& otherTransferFunction); //ok
        template<typename OtherTransferFunctionType> // não funciona
        TransferFunction<Type>& operator= (const TransferFunction<OtherTransferFunctionType>& otherTransferFunction);

        TransferFunction<Type> operator+= (const Type& rhs /*scalar*/){ return TransferFunction<Type>(this->TF += rhs);} //testada
        template<typename RightType> //testada
        TransferFunction<Type> operator+= (const TransferFunction<RightType>& rhs){return TransferFunction<Type>(this->TF += rhs.TF);}

        TransferFunction<Type> operator-= (const Type& rhs /*scalar*/){return TransferFunction<Type>(this->TF -= rhs);} // testada
        template<typename RightType>
        TransferFunction<Type> operator-= (const TransferFunction<RightType>& rhs){return TransferFunction<Type>(this->TF -= rhs.TF);}

        TransferFunction<Type> operator*= (const Type& rhs /*scalar*/){return TransferFunction<Type>(this->TF *= rhs);} // testada
        template<typename RightType>
        TransferFunction<Type> operator*= (const TransferFunction<RightType>& rhs){return TransferFunction<Type>(this->TF *= rhs.TF);}

        TransferFunction<Type> operator/= (const Type& rhs /*scalar*/){ return TransferFunction<Type>(this->TF *= 1/rhs);}
        template<typename RightType>
        TransferFunction<Type> operator/= (const TransferFunction<RightType>& rhs){return TransferFunction<Type>(this->TF *= LinAlg::Inverse(rhs.TF));}
        operator std::string() const{ std::string str; str << *this; return str;}

        Type sim(Type input);
        Type sim(Type x, Type y);
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x);
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x, LinAlg::Matrix<Type> y);
        LinAlg::Matrix<Type> sim(Type lsim, Type lmax, Type step);

        std::string ContinuosFirstOrderCaracteristics();
        std::string ContinuosSecondOrderCaracteristics();

        std::string print();

    private:
        char var;
        bool Continuous, simulationFlag;
        LinAlg::Matrix< PolynomHandler::Polynom<Type> > TF;
        LinAlg::Matrix<Type> inputState, outputState;
        LinAlg::Matrix<Type> transportDelay;
    };

    template<typename PolynomType, typename ScalarType>
    TransferFunction<PolynomType> operator+ (TransferFunction<PolynomType> lhs, const ScalarType& rhs) {return lhs += rhs;}
    template<typename PolynomType, typename ScalarType>
    TransferFunction<PolynomType> operator+ (const ScalarType& lhs, TransferFunction<PolynomType> rhs) {return rhs += lhs;}
    template<typename LeftType, typename RightType>
    TransferFunction<LeftType> operator+ (TransferFunction<LeftType> lhs, const TransferFunction<RightType>& rhs) {return lhs += rhs;}

    template<typename PolynomType>
    TransferFunction<PolynomType> operator- (TransferFunction<PolynomType> rhs){return -1*rhs;}
    template<typename PolynomType, typename ScalarType>
    TransferFunction<PolynomType> operator- (TransferFunction<PolynomType> lhs, const ScalarType& rhs) {return lhs -= rhs;}
    template<typename PolynomType, typename ScalarType>
    TransferFunction<PolynomType> operator- (const ScalarType& lhs, TransferFunction<PolynomType> rhs) {return -1*(rhs -= lhs);}
    template<typename LeftType, typename RightType>
    TransferFunction<LeftType> operator- (TransferFunction<LeftType> lhs, const TransferFunction<RightType>& rhs) {return lhs -= rhs;}

    template<typename PolynomType, typename ScalarType>
    TransferFunction<PolynomType>  operator* (TransferFunction<PolynomType>  lhs, const ScalarType& rhs) {return lhs *= rhs;}
    template<typename PolynomType, typename ScalarType>
    TransferFunction<PolynomType>  operator* (const ScalarType& lhs, TransferFunction<PolynomType>  rhs) {return rhs *= lhs;}
    template<typename LeftType, typename RightType>
    TransferFunction<LeftType> operator* (TransferFunction<LeftType> lhs, const TransferFunction<RightType>& rhs) {return lhs *= rhs;}

    template<typename PolynomType, typename ScalarType>
    TransferFunction<PolynomType> operator/ (TransferFunction<PolynomType> lhs, const ScalarType& rhs) {return lhs /= rhs;}
    template<typename PolynomType, typename ScalarType>
    TransferFunction<PolynomType> operator/ (ScalarType lhs, const TransferFunction<PolynomType> &rhs) {TransferFunction<PolynomType> ret(lhs); return ret /= rhs;}
    template<typename LeftType, typename RightType>
    TransferFunction<LeftType> operator/ (TransferFunction<LeftType> lhs, const TransferFunction<RightType> &rhs) {return lhs /= rhs;}

    template<typename Type> // ok
    std::ostream& operator<< (std::ostream& output, ModelHandler::TransferFunction<Type> TF);
    template<typename Type> //ok
    std::string&  operator<< (std::string& output,  ModelHandler::TransferFunction<Type> TF);

    template<typename Type> // ok
    TransferFunction<Type> pade(const Type &time, const int &order);

    template<typename Type> // ok
    TransferFunction<Type> FOPDTCurvaDeReacao(LinAlg::Matrix<Type> Y, LinAlg::Matrix<Type> U, Type sampleTime = 0.1);

    template<typename Type> // ok
    TransferFunction<Type> FOPDTZieglerNichols(LinAlg::Matrix<Type> Y, LinAlg::Matrix<Type> U, Type sampleTime = 0.1);

    template<typename Type> // ok
    TransferFunction<Type> FOPDTSmith(LinAlg::Matrix<Type> Y, LinAlg::Matrix<Type> U, Type sampleTime = 0.1);

    template<typename Type> // ok
    TransferFunction<Type> FOPDTSundaresanKrishnaswamy(LinAlg::Matrix<Type> Y, LinAlg::Matrix<Type> U, Type sampleTime = 0.1);

//    int factorial(int n);
}

#ifdef testModel
    #include "../../../src/modelLibs/transferfunction.hpp"
#else
    #include "SistemasdeControle/src/modelLibs/transferfunction.hpp"
#endif

#endif // TRANSFERFUNCTION_H
