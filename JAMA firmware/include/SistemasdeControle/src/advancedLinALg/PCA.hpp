//#include "SistemasdeControle/headers/advancedLinALg/PCA.h"
#ifdef testPolynom
    #include "../../../headers/advancedLinALg/PCA.h"
#else
    #include "SistemasdeControle/headers/advancedLinALg/PCA.h"
#endif

template <typename Type>
LinAlg::PCA<Type>::PCA(LinAlg::Matrix<Type> data, const unsigned &reducedDimensionQuantities)
{
    this->data = data;
    this->dataMean = LinAlg::mean(data,2);
    LinAlg::Matrix<Type> adjustedData;

    for(unsigned i = 0; i< data.getNumberOfRows(); ++i)
        adjustedData = adjustedData || data.getRow(i) - this->dataMean(i,0);

    LinAlg::Matrix<Type> matrixcov = ((adjustedData*(~adjustedData))/(adjustedData.getNumberOfColumns()-1));
    LinAlg::Matrix<Type> eigenvalues  = LinAlg::eigenValues(matrixcov);
    LinAlg::Matrix<Type> eigenvectors = -LinAlg::eigenVectors(matrixcov);

    this->projectioMatrix = eigenvectors(from(0)-->eigenvectors.getNumberOfRows()-1, LinAlg::LineVector<Type>(0,reducedDimensionQuantities-1));
    LinAlg::Matrix<Type> Y = (~this->projectioMatrix) * adjustedData;
    this->eigenvalueOrder = LinAlg::LineVector<Type>(0,eigenvectors.getNumberOfRows()-1);

    LinAlg::Matrix<Type> originalData;
    for (unsigned i = 0; i < data.getNumberOfRows(); ++i)
        originalData = originalData || this->projectioMatrix.getRow(i) * Y + this->dataMean(i,0);
    this->originalData = originalData;
}

template <typename Type>
LinAlg::Matrix<Type> ClusteringHandler::subspaceSimulation(LinAlg::Matrix<Type> dataIn, LinAlg::Matrix<Type> a, LinAlg::Matrix<Type> M)
{
    LinAlg::Matrix<Type> R, ret;
    for (unsigned i = 0; i < dataIn.getNumberOfRows(); ++i)
        R = (R || (dataIn.getRow(i) - a(i,0)));

    //Projeção
    LinAlg::Matrix<Type> Y1 = (~M)*R;
    //LinAlg::Matrix<Type> DadoFinal = M * Y1;

    //PCA na reconstrução
    //for (unsigned i = 0; i < DadoFinal.getNumberOfRows(); ++i)
    //    ret = DadoFinal.getRow(i) + a(i,0);

    for (unsigned i = 0; i < dataIn.getNumberOfRows(); ++i)
        ret = ret || M.getRow(i) * Y1 + a(i,0);
    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ClusteringHandler::grid(uint32_t dimension, Type lowerLimit, Type upperLimit, Type step)
{
    LinAlg::Matrix<Type> referenceState = LinAlg::LineVector<Type>(lowerLimit, upperLimit, step);
    uint32_t sizeState = referenceState.getNumberOfColumns(), totalDimension = pow(sizeState,dimension);
    LinAlg::Matrix<Type> ret(dimension,totalDimension);

    for(uint32_t i = 0; i < dimension; ++i)
    {
        double size = pow(sizeState,i);
        for(uint32_t k = 0; k < totalDimension; ++k)
            ret(i,k) = referenceState(0,(uint32_t(k/size))%sizeState);
    }

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> ClusteringHandler::optimalSignalControlGenerator(LinAlg::Matrix<Type> A, LinAlg::Matrix<Type> B, LinAlg::Matrix<Type> C,
                                                                 LinAlg::Matrix<Type> D, LinAlg::Matrix<Type> G, LinAlg::Matrix<Type> rho,
                                                                 LinAlg::Matrix<Type> w, LinAlg::Matrix<Type> eta, LinAlg::Matrix<Type> x)
{
    // given A,C,G,rho,y, find psi(i) for i=1:g such that
    //      psi(i) = max G(i,:)*A*e
    //                x
    //	under  G*x <= rho
    //	       |C*x - y| <= eta
    LinAlg::Matrix<Type> GC = (G||C||-C), rhoEta = (rho||eta+x||eta-x), obj, psi;
    uint32_t g = G.getNumberOfRows();

//    for(uint8_t i = 0; i < g; ++i)
//    {
//        obj = (-G(i,from(0)-->G.getNumberOfColumns()-1)*A);
//        psi = (psi||-linprog(obj, G, rhoEta));
//    }

//    LinAlg::Matrix<Type> delta;
//    for(uint8_t i = 0; i < g; ++i)
//        delta = (delta||G(i,from(0)-->G.getNumberOfColumns()-1)*B*linSolve(-G(i,from(0)-->G.getNumberOfColumns()-1)*B,D,w));

//    uint32_t n = A.getNumberOfRows();
//    LinAlg::Matrix<Type> v = linSolve(LinAlg::Zeros<Type>(n,0)||1.0,G|-rho ,-psi_eta-delta);
//    epsi = v(n);
//    vt = v(from(0)-->n-1,0);
}

template <typename Type>
LinAlg::Matrix<PWAFunction<Type> > ClusteringHandler::clustering(LinAlg::Matrix<Type> data, Type dist1, Type dist2, uint32_t dim)
{
    srand(time(NULL));

    uint32_t i = 0;
    LinAlg::Matrix<uint32_t> indF;
    LinAlg::Matrix<PWAFunction<Type> > Cluster_Parte;
    LinAlg::Matrix<Type> ones = LinAlg::Ones<Type>(1,data.getNumberOfRows());

    while(true)
    {
        LinAlg::Matrix<Type> Gt_P;
        Type col = (data.getNumberOfColumns()-1)*LinAlg::Random<Type>(1,1)(0,0);
        col = round(col);
        LinAlg::Matrix<Type> dis = LinAlg::Zeros<Type>(1,data.getNumberOfColumns());
        LinAlg::Matrix<Type> dist = LinAlg::Zeros<Type>(1,data.getNumberOfColumns());
        for (uint32_t j = 0; j < data.getNumberOfColumns(); ++j)
        {
            LinAlg::Matrix<Type> norm = data(from(0)-->data.getNumberOfRows()-1,col) - data(from(0)-->data.getNumberOfRows()-1,j);
            dis(0,j) = sqrt((((~norm)*norm))(0,0));
//            std::cout << data(from(0)-->data.getNumberOfRows()-1,col) << std::endl;
//            std::cout << dis(0,j)<<std::endl;
            if (dis(0,j) < dist1)
              Gt_P = Gt_P | data(from(0)--> data.getNumberOfRows()-1,j);
        }

        //std::cout << dis << std::endl << (~Gt_P) << std::endl;

        LinAlg::PCA<Type> pca(Gt_P,dim);
        PWAFunction<Type> P; P.M = pca.getProjectioMatrix(); P.a = pca.getDataMean();
        //std::cout << P.M << std::endl << P.a << std::endl;
        //uint32_t cont = 1;
        LinAlg::Matrix<Type> dadosTemp;
        LinAlg::Matrix<Type> indtTemp;
        for (uint32_t j = 0; j < data.getNumberOfColumns(); ++j)
        {
            LinAlg::Matrix<Type> subspace =  data(from(0)-->data.getNumberOfRows()-1,j);
            subspace = subspace - ClusteringHandler::subspaceSimulation(data(from(0)-->data.getNumberOfRows()-1,j),P.a,P.M);
            dist(0,j) = sqrt((((~subspace)*subspace))(0,0));
        }

        for (uint32_t j = 0; j < data.getNumberOfColumns(); ++j)
            if (dist(0,j) < dist2)
            {
                P.correlatedClusterData = P.correlatedClusterData|data(from(0)--> data.getNumberOfRows()-1,j);
                indF = indF|i;
            }

            else
                dadosTemp =  dadosTemp|data(from(0)--> data.getNumberOfRows()-1,j);

        Cluster_Parte = Cluster_Parte|P;
        if((dadosTemp.getNumberOfRows() == 0) && (dadosTemp.getNumberOfColumns() == 0) )
            break;

        if(Cluster_Parte(0,i).correlatedClusterData.getNumberOfColumns() != 0)
             i = i + 1;
        data = dadosTemp;
    }
    return Cluster_Parte;
}
