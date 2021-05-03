#ifdef testModel
    #include "../../../headers/restrictedOptimization/simplex.h"
#else
    #include "SistemasdeControle/headers/restrictedOptimization/simplex.h"
#endif

template <typename Type>
void restrictedOptimizationHandler::simplex<Type>::optimize()
{
if(this->N.A.getNumberOfColumns() != 0 && this->N.A.getNumberOfRows() != 0)
    {
        this->P.A = (this->P.A | LinAlg::Eye<Type>(this->P.A.getNumberOfRows())                               | LinAlg::Zeros<Type>(this->N.A.getNumberOfRows(),this->N.A.getNumberOfRows())) ||
                  (this->N.A | LinAlg::Zeros<Type>(this->P.A.getNumberOfRows(),this->P.A.getNumberOfRows()) | -LinAlg::Eye<Type>(this->N.A.getNumberOfRows()));
//        std::cout << this->A << "\n";
        this->P.b = this->P.b || this->N.b;
        this->A = this->P.A   | LinAlg::Eye<Type>(this->P.A.getNumberOfRows())||
                  this->E.A | LinAlg::Zeros<Type>(this->E.A.getNumberOfRows(),this->P.A.getNumberOfRows());
        this->b = this->P.b || this->E.b;
//        LinAlg::Matrix<Type> c = this->function2Optimize || LinAlg::Zeros<Type>(1,this->P.b.getNumberOfRows() - this->E.b.getNumberOfRows() + this->N.b.getNumberOfRows());
        LinAlg::Matrix<Type> w = LinAlg::Zeros<Type>(this->A.getNumberOfColumns() - this->P.A.getNumberOfRows(),1)||
                                 LinAlg::Ones<Type>(this->P.A.getNumberOfRows(),1);
        LinAlg::Matrix<Type> B = LinAlg::LineVector<Type>(this->A.getNumberOfColumns() - this->P.A.getNumberOfRows() +1, this->A.getNumberOfColumns())-1;
        LinAlg::Matrix<Type> n = LinAlg::LineVector<Type>(1,this->A.getNumberOfColumns() - this->P.A.getNumberOfRows())-1;
        simplexOptimization(w,this->A,this->b,B,n);
        this->x = this->x(uint32_t(0),from(0)-->this->x.getNumberOfRows()-this->P.A.getNumberOfRows()-1);
        this->A = this->A(from(0)-->this->A.getNumberOfRows()-1,from(0)-->this->A.getNumberOfColumns()-this->P.A.getNumberOfRows()-1);
        LinAlg::Matrix<Type> c = this->function2Optimize ||
                                 LinAlg::Zeros<Type>(this->b.getNumberOfRows(),1);
        n = n(1,from(0)-->n.getNumberOfColumns()-this->P.A.getNumberOfRows()-1);
        simplexOptimization(c,this->A,this->b,B,n);
        this->set = B;
    }
    else
    {
        this->A = (this->P.A | LinAlg::Eye<Type>(this->P.A.getNumberOfRows()))||
                  (this->E.A | LinAlg::Zeros<Type>(this->E.A.getNumberOfRows(),this->P.A.getNumberOfRows()));
        this->b = this->P.b || this->E.b;

        LinAlg::Matrix<Type> c = this->function2Optimize ||
                                 LinAlg::Zeros<Type>(this->b.getNumberOfRows()-1, 1);
        LinAlg::Matrix<Type> B = LinAlg::LineVector<Type>(this->A.getNumberOfColumns() - this->P.A.getNumberOfRows() +1, this->A.getNumberOfColumns(),1)-1;
        LinAlg::Matrix<Type> n = LinAlg::LineVector<Type>(1,this->A.getNumberOfColumns() - this->P.A.getNumberOfRows())-1;
        std::cout << B << "\n\n";
        std::cout << n << "\n\n";
        simplexOptimization(c,this->A,this->b,B,n);
        this->set = B;
    }
//    std::cout << this->x << "\n\n";
}

template <typename Type>
void restrictedOptimizationHandler::simplex<Type>::simplexOptimization(const LinAlg::Matrix<Type> &c,
                                                                       const LinAlg::Matrix<Type> &A,
                                                                       const LinAlg::Matrix<Type> &b,
                                                                       LinAlg::Matrix<Type> &B,
                                                                       LinAlg::Matrix<Type> &N)
{
    uint32_t zero = 0;
    LinAlg::Matrix<Type> An = A(from(0)-->A.getNumberOfRows()-1,N);
        LinAlg::Matrix<Type> Ab = A(from(0)-->A.getNumberOfRows()-1,B);
    //    std::cout << N << "\n";
        LinAlg::Matrix<Type> Abinv = LinAlg::inv_numeric(Ab);
    //    LinAlg::Matrix<Type> Abinv = (Ab^-1);
        LinAlg::Matrix<Type> xb;
    //    %% Verifique o vetor dos custos reduzidos
        for(unsigned terminate = 1; terminate <= 1000; ++terminate)
        {
            LinAlg::Matrix<Type> cn = c(N,zero);
            LinAlg::Matrix<Type> cb = c(B,zero);
            LinAlg::Matrix<Type>An = A(from(0)-->A.getNumberOfRows()-1,N);
            Ab = A(from(0)-->A.getNumberOfRows()-1,B);
            LinAlg::Matrix<Type> r = (~cn) - (~cb)*Abinv*An;
            this->cost = ((~cb)*Abinv*b)(0,0);
            xb = Abinv*b;
            unsigned contFlag = 0;
    //        std::cout << r << std::endl;
            for (unsigned i=0; i < r.getNumberOfColumns(); ++i)
               if(r(zero,i) <= 0) //Modificar o sinal para maximizar: <= ou menimizar: >=
               {
                   contFlag = contFlag + 1;
    //%               break;
               }
            if(contFlag == r.getNumberOfColumns())
                break;
            //%determine o vetor de chegada
            LinAlg::Matrix<Type> maxValue, maxIndice;
            *(maxValue, maxIndice) = LinAlg::max(~r);
            unsigned indMinD = maxIndice(0,0);
    //        unsigned indMinD = LinAlg::lineOfMinValue(~r);

            this->x = Abinv*An(from(0)-->An.getNumberOfRows()-1,indMinD);
            LinAlg::Matrix<Type> d = LinAlg::divPoint(xb,this->x);
            Type dMin = INFINITY;
            unsigned indMinB = 0;
            for (unsigned i = 0; i < d.getNumberOfRows(); ++i)
               if(this->x(i,0) > 0 && d(i,0) < dMin)
               {
                   dMin = d(i,0);
                   indMinB = i;
               }

            Abinv = EscalSimplex((Abinv | xb | this->x),indMinB);
            Type Bout = B(0,indMinB);
            Type Nout = N(0,indMinD);
            N = N(zero,from(0)-->(indMinD-2)) | Bout | N(zero, from(indMinD)-->(N.getNumberOfColumns()-1));
            B = B(zero,from(0)-->(indMinB-2)) | Nout | B(zero,from(indMinB)-->(B.getNumberOfColumns()-1));
        }

        this->x = xb || LinAlg::Zeros<Type>(An.getNumberOfColumns(),1);
    //    LinAlg::Matrix<Type> ind = LinAlg::sortColumnVectorIndices<Type>(B|N);
        LinAlg::Matrix<Type> reorderedMatrix,ind;

        *(reorderedMatrix,ind) = LinAlg::sort<Type>(B|N);
        this->x = this->x(ind,zero);
    //    std::cout << "\n\n" << ind << "\n\n";
        *(reorderedMatrix,N) = LinAlg::sort<Type>(N);
        *(reorderedMatrix,B) = LinAlg::sort<Type>(B);
    //    N = LinAlg::sortColumnVector<Type>(N);
    //    B = LinAlg::sortColumnVector<Type>(B);
}

template <typename Type>
LinAlg::Matrix<Type> restrictedOptimizationHandler::simplex<Type>::EscalSimplex(LinAlg::Matrix<Type> A,
                                                                                unsigned index)
{
    for(unsigned i = 0; i < A.getNumberOfColumns(); ++i)
            A(index,i) = A(index,i)/A(index,A.getNumberOfColumns()-1);

        for (unsigned i = 0; i < A.getNumberOfRows(); ++i)
            if(i != index)
            {
                Type m = A(i,A.getNumberOfColumns()-1)/A(index,A.getNumberOfColumns()-1);
                for(unsigned j = 0; j < A.getNumberOfColumns(); ++j)
                    A(i,j)=A(i,j)-m*A(index,j);
            }

    //    Xb   = A(from(1)-->A.getNumberOfRows(),A.getNumberOfColumns()-1);
        LinAlg::Matrix<Type> Binv = A(from(0)-->A.getNumberOfRows()-1,from(0)-->A.getNumberOfColumns()-3);
    //    X    = A(from(1)--> A.getNumberOfRows(),A.getNumberOfColumns());
        return Binv;
}
