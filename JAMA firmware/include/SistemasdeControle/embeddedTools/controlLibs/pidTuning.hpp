#include "pidTuning.h"


template <typename Type>
ControlHandler::PID<Type> ControlHandler::controllerTuning(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType,
                                                           const std::string &tuningMethod, const Type &sensibility)
{
    ControlHandler::PID<Type> pid;

    if (tuningMethod == "ZieglerNichols")
        pid = ControlHandler::tunningZieglerNichols<Type>(FOPDT,controllerType);
    else if (tuningMethod == "CHRServo0OV")
        pid = ControlHandler::tunningCHRServo0OV<Type>(FOPDT,controllerType);
    else if (tuningMethod == "CHRServo20OV")
        pid = ControlHandler::tunningCHRServo20OV<Type>(FOPDT,controllerType);
    else if (tuningMethod == "CHRRegulatorio")
        pid = ControlHandler::tunningCHRRegulatorio<Type>(FOPDT,controllerType);
    else if (tuningMethod == "CohenCoon")
        pid = ControlHandler::tunningCohenCoon<Type>(FOPDT,controllerType);
    else if (tuningMethod == "IAELopes")
        pid = ControlHandler::tunningIAELopes<Type>(FOPDT,controllerType);
    else if (tuningMethod == "ITAELopes")
        pid = ControlHandler::tunningITAELopes<Type>(FOPDT,controllerType);
    else if (tuningMethod == "IAERovira")
        pid = ControlHandler::tunningIAERovira<Type>(FOPDT,controllerType);
    else if (tuningMethod == "ITAERovira")
        pid = ControlHandler::tunningITAERovira<Type>(FOPDT,controllerType);
    else if (tuningMethod == "IMC")
        pid = ControlHandler::tunningIMC<Type>(FOPDT,controllerType,sensibility);
    else
        std::cout << "Metodo de sintonia nao encontrado!!\n\n";

    return pid;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningZieglerNichols(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    //std::cout << "tau = " << tau << " K = " << K << " theta = " << theta << std::endl;

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);
    if(controllerType == "P")
    {
        Type Kp = tau/(K*theta);
        controller.setParams(Kp,0.0,0.0);
    }
    else if(controllerType == "PI")
    {
        Type Kp = 0.9*tau/(K*theta);
        controller.setParams(Kp,Kp/(3.33*theta),0.0);
    }
    else if(controllerType == "PID")
    {
        Type Kp = 1.2*tau/(K*theta);
        controller.setParams(Kp,Kp/(2*theta),Kp*0.5*theta);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningCHRServo0OV(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);
    if(controllerType == "P")
    {
        Type Kp = 0.3*tau/(K*theta);
        controller.setParams(Kp,0.0,0.0);
    }
    else if(controllerType == "PI")
    {
        Type Kp = 0.35*tau/(K*theta);
        controller.setParams(Kp,Kp/(1.16*tau),0.0);
    }
    else if(controllerType == "PID")
    {
        Type Kp = 1.2*tau/(K*theta);
        controller.setParams(Kp,Kp/tau,Kp*0.5*theta);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningCHRServo20OV(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);
    if(controllerType == "P")
    {
        Type Kp = 0.7*tau/(K*theta);
        controller.setParams(Kp,0.0,0.0);
    }
    else if(controllerType == "PI")
    {
        Type Kp = 0.6*tau/(K*theta);
        controller.setParams(Kp,Kp/(tau),0.0);
    }
    else if(controllerType == "PID")
    {
        Type Kp = 0.95*tau/(K*theta);
        controller.setParams(Kp,Kp/(1.357*tau),Kp*0.473*theta);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningCHRRegulatorio(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);
    if(controllerType == "P")
    {
        Type Kp = 0.3*tau/(K*theta);
        controller.setParams(Kp,0.0,0.0);
    }
    else if(controllerType == "PI")
    {
        Type Kp = 0.6*tau/(K*theta);
        controller.setParams(Kp,Kp/(4*theta),0.0);
    }
    else if(controllerType == "PID")
    {
        Type Kp = 1.2*tau/(K*theta);
        controller.setParams(Kp,Kp/(2.375*theta),Kp*0.421*theta);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningCohenCoon(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);
    if(controllerType == "P")
    {
        Type Kp = (1.03+0.35*tau/theta)*(tau/(K*theta));
        controller.setParams(Kp,0.0,0.0);
    }
    else if(controllerType == "PI")
    {
        Type Kp = (0.9+0.083*tau/theta)*(tau/(K*theta));
        Type Ti = ((0.9+0.083*tau/theta)/(1.27+0.6*(tau/theta)))*theta;
        controller.setParams(Kp,Kp/Ti,0.0);
    }
    else if(controllerType == "PID")
    {
        Type Kp = (1.35+0.25*tau/theta)*(tau/(K*theta));
        Type Ti = ((1.35+0.25*tau/theta)/(0.54+0.6*(tau/theta)))*theta;
        Type Td = ((0.5*theta)/(1.35+0.25*(theta/tau)));
        controller.setParams(Kp,Kp/Ti,Kp*Td);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningIAELopes(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);
    if(controllerType == "PI")
    {
        Type Kp = ((0.984/K)*pow(tau/theta,0.986));
        Type Ti = tau/(0.608*pow(tau/theta,0.707));
        controller.setParams(Kp,Kp/Ti,0.0);
    }
    else if(controllerType == "PID")
    {
        Type Kp = ((1.435/K)*pow(tau/theta,0.921));
        Type Ti = tau/(0.878*pow(tau/theta,0.749));
        Type Td = tau*(0.482*pow(theta/tau,1.137));
        controller.setParams(Kp,Kp/Ti,Kp*Td);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningITAELopes(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);
    if(controllerType == "PI")
    {
        Type Kp = ((0.959/K)*pow(tau/theta,0.977));
        Type Ti = tau/(0.674*pow(tau/theta,0.68));
        controller.setParams(Kp,Kp/Ti,0.0);
    }
    else if(controllerType == "PID")
    {
        Type Kp = ((1.357/K)*pow(tau/theta,0.947));
        Type Ti = tau/(0.842*pow(tau/theta,0.738));
        Type Td = tau*(0.381*pow(theta/tau,0.995));
        controller.setParams(Kp,Kp/Ti,Kp*Td);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningIAERovira(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);
    if(controllerType == "PI")
    {
        Type Kp = ((0.758/K)*pow(tau/theta,0.861));
        Type Ti = tau/(1.02-0.323*(theta/tau));
        controller.setParams(Kp,Kp/Ti,0.0);
    }
    else if(controllerType == "PID")
    {
        Type Kp = ((1.086/K)*pow(tau/theta,0.869));
        Type Ti = tau/(0.74-0.130*(theta/tau));
        Type Td = tau*(0.348*pow(theta/tau,0.914));
        controller.setParams(Kp,Kp/Ti,Kp*Td);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningITAERovira(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);
    if(controllerType == "PI")
    {
        Type Kp = ((0.586/K)*pow(tau/theta,0.916));
        Type Ti = tau/(1.03-0.165*(theta/tau));
        controller.setParams(Kp,Kp/Ti,0.0);
    }
    else if(controllerType == "PID")
    {
        Type Kp = ((0.965/K)*pow(tau/theta,0.850));
        Type Ti = tau/(0.796-0.147*(theta/tau));
        Type Td = tau*(0.308*pow(theta/tau,0.929));
        controller.setParams(Kp,Kp/Ti,Kp*Td);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}

template <typename Type>
ControlHandler::PID<Type> ControlHandler::tunningIMC(const LinAlg::Matrix<Type> &FOPDT, const std::string &controllerType, const Type &lambda)
{
    Type num = FOPDT(0,0);
    Type den = FOPDT(0,1);

    //std::cout << FOPDT << std::endl;
    Type tau = 1/den, K = num/den, theta = FOPDT(0,2);

    //std::cout << "tau = " << tau << " num = " << num << " den = " << den << std::endl;

    ControlHandler::PID<Type> controller;
    controller.setSampleTime(theta);

    if(controllerType == "PI")
    {
        if(lambda < 0.8*theta)
            std::cout << "Valor de lambda menor que o esperado" << std::endl;
        Type Kp = (2*tau+theta)/(2*K*lambda);
        Type Ti = tau+(theta/2);
        controller.setParams(Kp,Kp/Ti,0.0);
    }
    else if(controllerType == "PID")
    {
        if(lambda < 1.7*theta)
            std::cout << "Valor de lambda menor que o esperado" << std::endl;

        Type Kp = (2*tau+theta)/(K*(2*lambda+theta));
        Type Ti = tau+(theta/2);
        Type Td = tau*theta/(2*tau+theta);
        controller.setParams(Kp,Kp/Ti,Kp*Td);
    }
    else
        std::cout << "Controlador nao encontrado" << std::endl;
    return controller;
}
