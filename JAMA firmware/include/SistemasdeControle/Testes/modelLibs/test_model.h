#ifndef MODEL_H
#define MODEL_H
#include <cfloat>
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
#include "SistemasdeControle/headers/primitiveLibs/polynom.h"

namespace ModelHandler {
    template <typename Type>
    class Model
    {
    public:
//        Model(ModelHandler::Model<Type>* InheritedModel);
        Model(): input(0), output(0), step(1){}
        virtual ~Model();

        void setStep(Type step);
        void setModelCoef(LinAlg::Matrix<Type> coef);
        void setIO(LinAlg::Matrix<Type> in, LinAlg::Matrix<Type> out);

        Type getStep() const;
        Type getOutput() const;
        LinAlg::Matrix<Type> getModelCoef() const;
        LinAlg::Matrix<Type> getInputMatrix() const;
        LinAlg::Matrix<Type> getOutputMatrix() const;
        LinAlg::Matrix<Type> getLinearVectorA() const;
        LinAlg::Matrix<Type> getLinearMatrixA() const;
        LinAlg::Matrix<Type> getLinearEqualityB() const;
        LinAlg::Matrix<Type> getLinearEqualityVectorB() const;

//        void operator= (ModelHandler::Model<Type>* InheritedModel); // implementar

        virtual Type         sim(Type x) = 0;
        virtual Type         sim(Type x, Type y) = 0;
        virtual LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x) = 0;
        virtual LinAlg::Matrix<Type> sim(Type lmin, Type lmax, Type step) = 0;
        virtual LinAlg::Matrix<Type> sim(LinAlg::Matrix<Type> x, LinAlg::Matrix<Type> y) = 0;

        virtual std::string print()=0;
        virtual unsigned getNumberOfVariables()=0;
        virtual unsigned getNumberOfInputs() const = 0;
        virtual unsigned getNumberOfOutputs() const = 0;
        virtual void setLinearVector(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output) = 0;
        virtual void setLinearModel(LinAlg::Matrix<Type> Input, LinAlg::Matrix<Type> Output)=0;

    protected:
//        virtual bool isFunction() = 0;
        Type                 input,    output,      lmin,lmax,            step;
        LinAlg::Matrix<Type> Input,    Output,      EstOutput,       ModelCoef,
                         LinearVectorA,   LinearEqualityVectorB, LinearMatrixA,
                         LinearEqualityB, InputLinearVector, OutputLinearVector;

    };

    template<typename Type> // implementar
    std::ostream& operator<< (std::ostream& output, ModelHandler::Model<Type> *model);
    template<typename Type> // implementar
    std::string&  operator<< (std::string& output,  ModelHandler::Model<Type> *model);

    template<typename Type> // implementar
    Type sim(const ModelHandler::Model<Type> *model, Type x);
    template<typename Type> // implementar
    Type sim(const ModelHandler::Model<Type> *model, Type x, Type y);
    template<typename Type> // implementar
    LinAlg::Matrix<Type> sim(const ModelHandler::Model<Type> *model, LinAlg::Matrix<Type> X);
    template<typename Type> // implementar
    LinAlg::Matrix<Type> sim(const ModelHandler::Model<Type> *model, Type lsim, Type lmax, Type step);
    template<typename Type> // implementar
    LinAlg::Matrix<Type> sim(const ModelHandler::Model<Type> *model, LinAlg::Matrix<Type> X, LinAlg::Matrix<Type> Y);

    template <typename Type>
    Type diff(const ModelHandler::Model<Type> *model, Type x);
}

#include "SistemasdeControle/src/modelLibs/model.hpp"

#endif // MODEL_H
