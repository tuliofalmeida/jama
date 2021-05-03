#ifndef STATESPACE_H
#define STATESPACE_H
#ifdef testModel
    #include "../../../headers/modelLibs/model.h"
    #include "../../../headers/primitiveLibs/primitives.h"
#else
    #include "SistemasdeControle/headers/modelLibs/model.h"
    #include "SistemasdeControle/headers/primitiveLibs/primitives.h"
#endif

namespace ModelHandler {
    template <typename Type>
    class StateSpace : public Model<Type>
    {
    public:
        StateSpace();
        StateSpace(LinAlg::Matrix<Type> A , LinAlg::Matrix<Type> B,
                   LinAlg::Matrix<Type> C , LinAlg::Matrix<Type> D);
        StateSpace(LinAlg::Matrix<Type> Ad, LinAlg::Matrix<Type> Bd,
                   LinAlg::Matrix<Type> C , LinAlg::Matrix<Type> D,
                   Type SampleTime);
        template<typename OtherType>
        StateSpace(const ModelHandler::StateSpace<OtherType>& otherStateSpaceFunction);

        StateSpace<Type>& operator= (const StateSpace<Type>& otherStateSpaceFunction);
        template<typename OtherStateSpaceFunctionType>
        StateSpace<Type>& operator= (const StateSpace<OtherStateSpaceFunctionType>& otherStateSpaceFunction);

        operator std::string() const{ std::string str; str << *this; return str;}

        Type getSampleTime() const; // ok
        Type getTimeSimulation() const{return this->timeSimulation;} // ok

        unsigned getnDiscretizationParameter() const {return this->nDiscretization;}
        unsigned getNDiscretizationValue() const {return this->nDiscretization;}
        unsigned getMinPredictionHorizon() const {return this->minPredictionHorizon;}
        unsigned getMaxPredictionHorizon() const {return this->maxPredictionHorizon;}
        unsigned getControlHorizon() const {return this->controlHorizon;}

        LinAlg::Matrix<Type> getA() const; //ok
        LinAlg::Matrix<Type> getB() const; //ok
        LinAlg::Matrix<Type> getC() const; //ok
        LinAlg::Matrix<Type> getD() const; //ok
        LinAlg::Matrix< LinAlg::Matrix<Type>* >* getContinuousParameters() const;
        LinAlg::Matrix< LinAlg::Matrix<Type>* >* getDiscreteParameters() const;
        LinAlg::Matrix<Type> getActualState() const; //ok
        LinAlg::Matrix<Type> getObserverParameters() const{return L;} //ok
        LinAlg::Matrix<Type> getContinuousObserverParametersByAckerman(LinAlg::Matrix<Type> polesToBePlaced);
        LinAlg::Matrix<Type> getKalmanFilterParameters() const{return P;}

        unsigned getNumberOfVariables() const {return 0;}
        unsigned getNumberOfInputs() const {return 0;}
        unsigned getNumberOfOutputs() const {return 0;}

        void setA(LinAlg::Matrix<Type> A); //ok
        void setB(LinAlg::Matrix<Type> B); //ok
        void setC(LinAlg::Matrix<Type> C); //ok
        void setD(LinAlg::Matrix<Type> D); //ok
        void setContinuous(bool Continuous); //ok
        void setSampleTime(Type SampleTime); //ok
        void setInitialState(LinAlg::Matrix<Type> X0); //ok
        void setLinearModel(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);
        void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output);
        void setObserverParameters(LinAlg::Matrix<Type> L);//ok
        void setNDiscretizationValue(const unsigned &nDiscretization){this->nDiscretization = nDiscretization;}
        void setMinPredictionHorizon(const unsigned &minPredictionHorizon){this->minPredictionHorizon = minPredictionHorizon;}
        void setMaxPredictionHorizon(const unsigned &maxPredictionHorizon){this->maxPredictionHorizon = maxPredictionHorizon;}
        void setControlHorizon(const unsigned &controlHorizon){this->controlHorizon = controlHorizon;}

        bool isContinuous()  const;
        bool isObservable()  const;
        bool isControlable() const;
        LinAlg::Matrix<Type> ObserverLoop(LinAlg::Matrix<Type> U, LinAlg::Matrix<Type> Y);
        LinAlg::Matrix<Type> KalmanFilterObserverLoop(LinAlg::Matrix<Type> U, LinAlg::Matrix<Type> Y);

        Type sim(Type u); //ok
        Type sim(Type u, Type y); // não é usado
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> u); //ok
        LinAlg::Matrix<Type> sim(Type lmin, Type lmax, Type step); //ok
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> u, LinAlg::Matrix<Type> y); // não é usado

        void c2dConversion(); //ok
        void d2cConversion();
        std::string print(); //ok

    private:
        bool continuous,firstTimeKalmanObserver;
        unsigned nDiscretization, minPredictionHorizon, maxPredictionHorizon, controlHorizon;
        LinAlg::Matrix<Type> A, B, C, D, Ad, Bd, X, L, initialState,P;
    };

    template<typename Type> // ok
    std::ostream& operator<< (std::ostream& output, ModelHandler::StateSpace<Type> SS);
    template<typename Type> //ok
    std::string&  operator<< (std::string& output,  ModelHandler::StateSpace<Type> SS);

    template<typename Type> // ok
    Type sim(ModelHandler::StateSpace<Type> &SS, Type u);
    template<typename Type> // ok
    LinAlg::Matrix<Type> sim(ModelHandler::StateSpace<Type> &SS, LinAlg::Matrix<Type> u);
    template<typename Type> //ok
    LinAlg::Matrix<Type> sim(ModelHandler::StateSpace<Type> &SS, Type lmin, Type lmax, Type step);

}

#ifdef testModel
    #include "../../../src/modelLibs/statespace.hpp"
#else
    #include "SistemasdeControle/src/modelLibs/statespace.hpp"
#endif

#endif // STATESPACE_H
