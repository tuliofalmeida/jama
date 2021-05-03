#ifndef PIDTUNNING_H
#define PIDTUNNING_H

#include <cmath>
#ifdef testControl
    #include "../../../headers/controlLibs/pid.h"
#else
    #include "SistemasdeControle/headers/controlLibs/pid.h"
#endif

namespace ControlHandler{
    const static std::string tune[10] = {"ZieglerNichols", "CHRServo0OV", "CHRServo20OV","CHRRegulatorio","CohenCoon","IAELopes","IT                                                                                                                   AELopes","IAERovira","ITAERovira","IMC"};
    template <typename Type>
    PID<Type> controllerTuning(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType, const std::string &tuningMethod, const Type &sensibility = 15);
    template <typename Type>
    PID<Type> tunningZieglerNichols(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningCHRServo0OV(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningCHRServo20OV(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningCHRRegulatorio(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningCohenCoon(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningIAELopes(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningITAELopes(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningIAERovira(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningITAERovira(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningIMC(const ModelHandler::TransferFunction<Type> &FOPDT, const std::string &controllerType, const Type &lambda);

}

#ifdef testControl
    #include "../../../src/controlLibs/pidTuning.hpp"
#else
    #include "SistemasdeControle/src/controlLibs/pidTuning.hpp"
#endif

#endif // PIDTUNNING_H
