#ifndef __PCA_H_INCLUDED
#define __PCA_H_INCLUDED

#ifdef testPolynom
    #include "../../../headers/primitiveLibs/LinAlg/matrix.h"
    #include "../../../headers/primitiveLibs/LinAlg/linalg.h"
    #include "../../../headers/primitiveLibs/polynom.h"
#else
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
    #include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
    #include "SistemasdeControle/headers/primitiveLibs/polynom.h"
#endif

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

template <typename Type>
struct PWAFunction
{
    LinAlg::Matrix<Type> correlatedClusterData, F, g, M, a;
};

template<typename Type>
inline std::ostream& operator<< (std::ostream& output, const PWAFunction<Type> pwa)
{
    output << "Lei afim: \nF: " << pwa.F << "\ng: " << pwa.g << "\n";
    output << "parametros PCA: \nM: " << pwa.M << "\na: " << pwa.a << "\n";
    return output;
}

namespace ClusteringHandler {
    template <typename Type>
    LinAlg::Matrix<Type> subspaceSimulation(LinAlg::Matrix<Type> dataIn, LinAlg::Matrix<Type> a, LinAlg::Matrix<Type> M);

    template <typename Type>
    LinAlg::Matrix<Type> grid(uint32_t dimension, Type lowerLimit, Type upperLimit, Type step);

    template <typename Type>
    LinAlg::Matrix<Type> optimalSignalControlGenerator(LinAlg::Matrix<Type> A, LinAlg::Matrix<Type> B, LinAlg::Matrix<Type> C,
                                                       LinAlg::Matrix<Type> D, LinAlg::Matrix<Type> G, LinAlg::Matrix<Type> rho,
                                                       LinAlg::Matrix<Type> w, LinAlg::Matrix<Type> eta, LinAlg::Matrix<Type> x);
    template <typename Type>
    LinAlg::Matrix<PWAFunction<Type> > clustering(LinAlg::Matrix<Type> data, Type dist1, Type dist2, uint32_t dim);
}



#ifdef testMatrix
    #include "../../../../src/advancedLinALg/PCA.hpp"
#else
    #ifdef testPolynom
        #include "../../../src/advancedLinALg/PCA.hpp"
    #else
        #include "SistemasdeControle/src/advancedLinALg/PCA.hpp"
    #endif
#endif
//#include "SistemasdeControle/src/advancedLinALg/PCA.hpp"
#endif // PCA_H
