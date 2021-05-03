#ifdef testModel
    #include "../../../headers/restrictedOptimization/recursiveactiveset.h"
#else
    #include "SistemasdeControle/headers/restrictedOptimization/recursiveactiveset.h"
#endif

template <typename Type>
void restrictedOptimizationHandler::RecursiveActiveSet<Type>::optimize()
{
    LinAlg::Matrix<Type> A0 = this->P.A || -this->N.A; // As inequações de restrição são montadas P.A < P.b e N.A > N.B
    LinAlg::Matrix<Type> b0 = this->P.b || -this->N.b; // As inequações de restrição são montadas P.A < P.b e N.A > N.B

    this->x = (((~this->QuadMat)*this->QuadMat)^-1)*(~this->QuadMat)*-this->LinMat; // Solução de mínimos quadrados do problema
    LinAlg::Matrix<Type> Cov = LinAlg::Eye<Type>(A0.getNumberOfColumns())*1e8; // Matriz de covariância do mínimos quadrados recursivo

//    std::cout << this->x << "\n";
    while(1)// Esse while roda enquanto existirem restrições que não são obedecidas.
    {
        LinAlg::Matrix<Type> S = this->activeRestrictions(A0,b0,this->tol); // verifica quais restrições não estão sendo obedecidas caso não exista retorna uma matriz 0X0
        if(S.getNumberOfColumns() == 0)// verifica se todas as restrições foram obedecidas
            break;// se sim, sai do loop
//        std::cout << S << "\n";
        LinAlg::Matrix<Type> A = A0(S,from(1)-->A0.getNumberOfColumns());// seleciona a restrição que não foi obedecida
        LinAlg::Matrix<Type> b = b0(S,1);// seleciona a restrição que não foi obedecida
        this->RKKT(A,b,Cov,this->x);// faz a solução x ser "puxada" para dentro do conjunto de restrições
//        std::cout << this->x << "\n";
    }
    /*
     * Suposta explicação (Ainda não tenho comprovações matemáticas)
     * Ao encontrar uma restrição o algoritmo de mínimos quadrados recursivo
     * recebe mais uma coluna de dados que representa a restrição
     * Como, estatisticamente, essa restrição começa a se repetir
     * a solução começa a tender para os limites, dentro de uma determinada
     * tolerância.
    */
}

template <typename Type>
LinAlg::Matrix<Type> restrictedOptimizationHandler::RecursiveActiveSet<Type>::activeRestrictions(const LinAlg::Matrix<Type> &A,
                                                                                                 const LinAlg::Matrix<Type> &b,
                                                                                                 Type tol)
{
    LinAlg::Matrix<Type> restrictionsTest = (A*this->x - b), ind;
    for(unsigned i = 1; i <= restrictionsTest.getNumberOfRows(); ++i)
        if(restrictionsTest(i,1) >= tol)
            ind = ind | Type(i);
    return ind;
}

template <typename Type>
void restrictedOptimizationHandler::RecursiveActiveSet<Type>::RKKT(LinAlg::Matrix<Type> A,
                                                                   LinAlg::Matrix<Type> b,
                                                                   LinAlg::Matrix<Type> &P,
                                                                   LinAlg::Matrix<Type> &x)
{
    LinAlg::Matrix<Type> PHI = A;
    LinAlg::Matrix<Type> Y = b;
    LinAlg::Matrix<Type> E,K;
    Type lambda = 1;

    for(unsigned i = 1; i <= PHI.getNumberOfRows(); ++i)
    {
        LinAlg::Matrix<Type> phi = PHI.GetRow(i);
        E = ~Y.GetRow(i) - ~(phi*x);
        K = (P*~phi)/(((phi*P)*~phi) + lambda);
        LinAlg::Matrix<Type> KxE;
        for(unsigned i = 1; i <= Y.getNumberOfColumns(); ++i)
            KxE = KxE | K*E(i,1);
        x = x + KxE;
        P = (P - (K*(phi*P)))/lambda;
    }
}
