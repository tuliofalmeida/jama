#ifndef __OPTIMIZATION_H_INCLUDED
#define __OPTIMIZATION_H_INCLUDED

#include "SistemasdeControle/headers/modelLibs/model.h"
#include "SistemasdeControle/headers/modelLibs/arx.h"

//Biblioteca incompleta, ainda nao funcional.
namespace OptimizationHandler {
    template <class Type>
    class Optimization
    {
    public:
        Optimization();

        virtual void Optimize()=0;
        virtual void Optimize(LinAlg::Matrix<Type> Input,
                              LinAlg::Matrix<Type> Output)=0;

    protected:
        ModelHandler::Model<Type> *model;
    };
}

#include "SistemasdeControle/src/optimizationLibs/optimization.hpp"
#endif // OPTIMIZATION_H
