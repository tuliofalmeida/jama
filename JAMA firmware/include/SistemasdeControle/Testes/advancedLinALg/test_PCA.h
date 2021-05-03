#ifndef __PCA_H_INCLUDED
#define __PCA_H_INCLUDED
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"

namespace LinAlg {

    template <typename Type>
    class PCA
    {
    public:
        PCA(LinAlg::Matrix<Type> data, const unsigned &reducedDimensionQuantities);

        LinAlg::Matrix<Type> getData()const {return data;}
        LinAlg::Matrix<Type> getDataMean()const {return dataMean;}
        LinAlg::Matrix<Type> getEigenvalueOrder()const {return eigenvalueOrder;}
        LinAlg::Matrix<Type> getProjectioMatrix()const {return projectioMatrix;}
        LinAlg::Matrix<Type> getOriginalData()const {return originalData;}

    private:
        LinAlg::Matrix<Type> data, dataMean, projectioMatrix,
                             eigenvalueOrder, originalData; //= PCAf(Dados, dim)
    };
}

#include "SistemasdeControle/src/advancedLinALg/PCA.hpp"
#endif // PCA_H
