#ifndef _OPTIMIZATION_H_INCLUDED
#define _OPTIMIZATION_H_INCLUDED

#ifdef testModel
    #include "../../../headers/primitiveLibs/LinAlg/matrix.h"
    #include "../../../headers/modelLibs/model.h"
    #include "../../../headers/modelLibs/arx.h"
    #include "../../../headers/advancedModelLibs/droneModel/limbModel.h"

#else
    #include "SistemasdeControle/headers/modelLibs/model.h"
    #include "SistemasdeControle/headers/modelLibs/arx.h"
#endif

//Biblioteca incompleta, ainda nao funcional.
namespace OptimizationHandler {
    template <class Type>
    class Optimization
    {
    public:
        Optimization(){}

        virtual void Optimize()=0;
        virtual void Optimize(LinAlg::Matrix<Type> Input,
                              LinAlg::Matrix<Type> Output)=0;
        LinAlg::Matrix<Type> getOptimizedVariable(){return OptimizatedVariable;}
    protected:
        ModelHandler::Model<Type> *model;
        LinAlg::Matrix<Type> OptimizatedVariable;
    };
}

#endif // OPTIMIZATION_H
