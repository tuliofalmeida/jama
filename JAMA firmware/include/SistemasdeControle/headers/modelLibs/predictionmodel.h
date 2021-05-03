#ifndef MODELOPREDICAO_H
#define MODELOPREDICAO_H

#ifdef testModel
    #include "../../../headers/modelLibs/model.h"
    #include "../../../headers/modelLibs/statespace.h"
    #include "../../../headers/primitiveLibs/LinAlg/matrix.h"
    #include "../../../headers/primitiveLibs/LinAlg/linalg.h"
    #include "../../../headers/modelLibs/model.h"
    #include "../../../headers/modelLibs/integrativemodel.h"
#else
    #include "SistemasdeControle/headers/modelLibs/model.h"
    #include "SistemasdeControle/headers/modelLibs/statespace.h"
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
    #include "SistemasdeControle/headers/modelLibs/integrativemodel.h"
#endif

namespace ModelHandler {
    template <class Type>
    class PredictionModel: public ModelHandler::Model<Type>
    {
    public:
        PredictionModel(){}
        PredictionModel(ModelHandler::IntegrativeModel<Type> MI,
                       unsigned HorizontePredicaoMin, unsigned HorizontePredicaoMax, unsigned HorizonteControle);
        PredictionModel(LinAlg::Matrix<Type> A , LinAlg::Matrix<Type> B,
                          LinAlg::Matrix<Type> C , LinAlg::Matrix<Type> D);
        PredictionModel(LinAlg::Matrix<Type> Ad, LinAlg::Matrix<Type> Bd,
                          LinAlg::Matrix<Type> C , LinAlg::Matrix<Type> D,
                          Type SampleTime);

//        ModelHandler::PredictionModel<Type>& operator= (const ModelHandler::PredictionModel<Type>& otherPredictionModel) const;

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
        unsigned nDiscretization, HorizontePredicaoMin, HorizontePredicaoMax, HorizonteControle;
        Type SampleTime, TimeSimulation;
        LinAlg::Matrix<Type> A, B, C, D, Ad, Bd, X, initialState;
    };

    template<typename Type>
    std::ostream& operator<< (std::ostream& output, ModelHandler::PredictionModel<Type> IM);
    template<typename Type>
    std::string&  operator<< (std::string& output,  ModelHandler::PredictionModel<Type> IM);

}

#ifdef testModel
    #include "../../../src/modelLibs/predictionmodel.hpp"
#else
    #include "SistemasdeControle/src/modelLibs/predictionmodel.hpp"
#endif

#endif // MODELOPREDICAO_H
