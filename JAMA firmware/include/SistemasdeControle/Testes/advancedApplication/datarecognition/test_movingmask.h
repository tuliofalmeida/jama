#ifndef MOVINGMASK_H
#define MOVINGMASK_H
#include "SistemasdeControle/headers/modelLibs/arx.h"
#include "SistemasdeControle/headers/modelLibs/fir.h"
#include "SistemasdeControle/headers/modelLibs/nfir.h"
#include "SistemasdeControle/headers/optimizationLibs/leastsquare.h"
#include "SistemasdeControle/headers/optimizationLibs/recursiveleastsquare.h"

namespace AdvancedApplication {
    template <class Type>
    class movingMask
    {

    public:

        movingMask(){}
        movingMask(const unsigned &quantidadeVariaveis , const unsigned &tamanho, ModelHandler::Model<Type> *model = 0);

        void dataRecognitionStart(const unsigned &quantidadeVariaveis, const unsigned &tamanho);
        void dataRecognitionRestart();
        void operator << (const LinAlg::Matrix<Type> &inputData);

        LinAlg::Matrix<Type> dataRecognition();
        Type dataRecognition(const LinAlg::Matrix<Type> &defaultData, Type tolerance = 1000);
        void filterOptimization(LinAlg::Matrix<Type> data2beFiltered);

        LinAlg::Matrix<Type> getFilterParameters() const;
        LinAlg::Matrix<Type> getRecognitionModel() const;
        LinAlg::Matrix<Type> getFilteredData(LinAlg::Matrix<Type> data2beFiltered) const;
        LinAlg::Matrix<Type> getData() const;

        void setRecognitionModel(ModelHandler::Model<Type> *recognitionModel);
        void optimizeRecognitionModel(LinAlg::Matrix<Type> dataOutput);

    private:
        ModelHandler::Model<Type> *filterModel, *recognitionModel;
        OptimizationHandler::Optimization<Type> *RLSFilter, *RLSRecognition;
        LinAlg::Matrix<Type> data2Register, filterMatrix;
        Type quantidadeVariaveis, tamanho;
        unsigned counter, filterCounter;
        bool wasDataOptimized;
    };
}


#include "SistemasdeControle/src/advancedApplication/datarecognition/movingmask.hpp"
#endif // MOVINGMASK_H
