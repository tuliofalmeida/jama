#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "SistemasdeControle/headers/modelLibs/model.h"
#include "SistemasdeControle/headers/modelLibs/arx.h"
#include "SistemasdeControle/headers/modelLibs/statespace.h"
#include "SistemasdeControle/headers/modelLibs/transferfunction.h"

namespace ModelHandler{

    template <typename Type>
    TransferFunction<Type> ss2tf(const StateSpace<Type> &SS);
    template <typename Type>
    TransferFunction<Type> ss2tfSISO(const StateSpace<Type> &SS);

    template <typename Type>
    TransferFunction<Type> arx2tf(const ARX<Type> &Arx, double sampleTime = 0);
    template <typename Type>
    StateSpace<Type> arx2SS(const ARX<Type> &Arx);


    template <typename Type>
    StateSpace<Type> tf2ss(const TransferFunction<Type> &TF);
    template <typename Type>
    StateSpace<Type> tf2ssSISO(const TransferFunction<Type> &TF);

    template<typename Type> //ok
    ModelHandler::StateSpace<Type> c2d(const ModelHandler::StateSpace<Type> &SS, Type SampleTime);
    template<typename Type>
    TransferFunction<Type> c2d(const TransferFunction<Type>& TF, Type sampleTime);

    template<typename Type> //ok
    ModelHandler::StateSpace<Type> d2c(const ModelHandler::StateSpace<Type> &discreteSS);
}

#include "SistemasdeControle/src/modelLibs/conversions.hpp"
#endif // CONVERSIONS_H

