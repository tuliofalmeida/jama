#ifndef IntegrativeModel_H
#define IntegrativeModel_H
#ifdef testModel
    #include "../../../headers/primitiveLibs/LinAlg/matrix.h"
    #include "../../../headers/primitiveLibs/LinAlg/linalg.h"
#else
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
#endif
#include "model.h"
#include "statespace.h"

namespace ModelHandler {
    template <class Type>
    class IntegrativeModel: public ModelHandler::Model<Type>
    {
    public:
        IntegrativeModel(){}
        IntegrativeModel(LinAlg::Matrix<Type> A , LinAlg::Matrix<Type> B,
                          LinAlg::Matrix<Type> C , LinAlg::Matrix<Type> D);
        IntegrativeModel(LinAlg::Matrix<Type> Ad, LinAlg::Matrix<Type> Bd,
                          LinAlg::Matrix<Type> C , LinAlg::Matrix<Type> D,
                          Type SampleTime);
        IntegrativeModel(ModelHandler::StateSpace<Type> &SS);

//        ModelHandler::IntegrativeModel<Type>& operator= (const ModelHandler::IntegrativeModel<Type>& otherIntegrativeModel) const;

        LinAlg::Matrix<Type> getA() const;
        LinAlg::Matrix<Type> getB() const;
        LinAlg::Matrix<Type> getC() const;
        LinAlg::Matrix<Type> getD() const;

        unsigned getNumberOfVariables(){}
        unsigned getNumberOfInputs() const {}
        unsigned getNumberOfOutputs() const {}

        void setContinuous(bool Continuous);
        void setSampleTime(double SampleTime);
        void setInitialState(LinAlg::Matrix<Type> X0);
        void setLinearModel(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output){}
        void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output){}
        void SetObserverParameter(LinAlg::Matrix<Type> L);

        bool isContinuous()  const;
        bool isObservable()  const;
        bool isControlable() const;

        Type sim(Type u);
        Type sim(Type u, Type y){}
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> u);
        LinAlg::Matrix<Type> sim(Type lmin, Type lmax, Type step);
        LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> u, LinAlg::Matrix<Type> y){}

        std::string print();

    private:
        bool Continuous;
        unsigned nDiscretization;
        Type SampleTime, TimeSimulation;
        LinAlg::Matrix<Type> A, B, C, D, Ad, Bd, X, initialState, L;
    };

    template<typename Type>
    std::ostream& operator<< (std::ostream& output, ModelHandler::IntegrativeModel<Type> SS);
    template<typename Type>
    std::string&  operator<< (std::string& output,  ModelHandler::IntegrativeModel<Type> SS);
}

#ifdef testModel
    #include "../../../src/modelLibs/integrativemodel.hpp"
#else
    #include "SistemasdeControle/src/modelLibs/integrativemodel.hpp"
#endif
#endif // IntegrativeModel_H
