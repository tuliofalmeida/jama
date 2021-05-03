#ifndef PIDTUNNING_H
#define PIDTUNNING_H

#include "pid.h"
#include "conversions.h"
#include "pidTuning.h"


namespace ControlHandler{
    const static std::string tune[10] = {"ZieglerNichols", "CHRServo0OV", "CHRServo20OV","CHRRegulatorio","CohenCoon","IAELopes","IT                                                                                                                   AELopes","IAERovira","ITAERovira","IMC"};
    template <typename Type>
    PID<Type> controllerTuning(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType, const std::string &tuningMethod, const Type &sensibility = 15);
    template <typename Type>
    PID<Type> tunningZieglerNichols(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningCHRServo0OV(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningCHRServo20OV(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningCHRRegulatorio(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningCohenCoon(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningIAELopes(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningITAELopes(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningIAERovira(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningITAERovira(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType);
    template <typename Type>
    PID<Type> tunningIMC(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType, const Type &lambda);

}

#include "pidTuning.hpp"


#endif // PIDTUNNING_H