#ifdef testMatrix
    #include "../../../../headers/primitiveLibs/LinAlg/linalg.h"
#else
    #ifdef testPolynom
        #include "../../../headers/primitiveLibs/LinAlg/linalg.h"
    #else
        #include "SistemasdeControle/headers/primitiveLibs/LinAlg/linalg.h"
    #endif
#endif

template <typename Type>
void LinAlg::balance (LinAlg::Matrix<Type> &matrix_to_balance)
{
    uint32_t aux = 0;
    Type radix = FLT_RADIX, sqrdx = radix*radix, s, r, g, f, c;

    while(aux == 0)
    {
        aux = 1;
        for(uint32_t i = 0; i < matrix_to_balance.getNumberOfRows(); i++)
        {
            r = c = 0.0;
            for(uint32_t j = 0; j < matrix_to_balance.getNumberOfColumns(); j++)
                if( j != i)
                {
                    c += std::fabs(matrix_to_balance(j, i));
                    r += std::fabs(matrix_to_balance(i, j));
                }
            if(c && r)
            {
                g = r/radix;
                f = 1.0;
                s = c + r;
                while(c < g)
                {
                    f *= radix;
                    c *= sqrdx;
                }

                g = r*radix;
                while(c > g)
                {
                    f /= radix;
                    c /= sqrdx;
                }
                if((c + r)/f < 0.95*s)
                {
                    aux = 0;
                    g = 1.0/f;
                    for(uint32_t j = 0; j < matrix_to_balance.getNumberOfColumns(); j++)
                    {
                        matrix_to_balance(i, j) *= g;
                        matrix_to_balance(j, i) *= f;
                    }
                }
            }
        }
    }

}

template<typename Type>
Type LinAlg::trace (const LinAlg::Matrix<Type>& mat)
{
    Type ret = 0;

    if(mat.getNumberOfRows() != mat.getNumberOfColumns())
        std::cout << "O traco so e calculado para matrizes quadradas.";
    else
    {
        for(uint32_t i = 0; i < mat.getNumberOfRows(); i++)
            for(uint32_t j = 0; j < mat.getNumberOfColumns(); j++)
                if(i == j)
                    ret += mat(i, j);
    }

    return ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::characteristicPolynom (const LinAlg::Matrix<Type>& mat)
{
    uint32_t n = mat.getNumberOfColumns();
    Matrix<Type> z; z = eigenValues(mat);
    Matrix<Type> ret(1,n+1);
    std::complex<Type> *tempPoly = new std::complex<Type> [2];
    tempPoly[0] = 1;
    tempPoly[1] = std::complex<Type>(-z(0,0),-z(0,1));
    std::complex<Type> * tempPolyEigenvalue = new std::complex<Type>[2];

    uint32_t sizeTempPoly = 2;
    tempPolyEigenvalue[0] = 1;
    for(uint32_t i = 1; i < n ; ++i)
    {
        tempPolyEigenvalue[1] = std::complex<Type>(-z(i,0),-z(i,1));//apos o templade entre (real,imaginario) atribuição
        tempPoly = LinAlg::MultPoly(tempPoly,tempPolyEigenvalue,sizeTempPoly,2);
        sizeTempPoly++;
    }

    for(uint32_t i = 0; i < sizeTempPoly ; ++i)
        ret(0,i) = tempPoly[i].real();

    return ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::inv_numeric(LinAlg::Matrix<Type> mat)
{
    LinAlg::Matrix<Type> Id;

//    try
//    {
        if (mat.getNumberOfColumns() != mat.getNumberOfRows())
            std::cout << "A matriz nao e quadrada\n";
//            throw "A matriz nao e quadrada";
        else
        {
            Id = LinAlg::Eye<Type>(mat.getNumberOfRows());

            for(uint32_t i = 0; i < mat.getNumberOfRows(); ++i)
                for(uint32_t j = i+1; j < mat.getNumberOfRows(); ++j)
                {
                    Type m = mat(j,i)/mat(i,i);
                    for(uint32_t k = 0; k < mat.getNumberOfRows(); ++k)
                    {
                        mat(j,k) = mat(j,k)-m*mat(i,k);
                        Id(j,k) = Id(j,k)-m*Id(i,k);
                    }
                }

            for(int32_t i = mat.getNumberOfRows()-1; i >= 0; --i)
                for(int32_t j = i - 1; j >= 0; --j)
                {
                    Type m = mat(j,i)/mat(i,i);
                    for(uint32_t k = 0; k < mat.getNumberOfRows(); ++k)
                    {
                        mat(j,k) = mat(j,k)-m*mat(i,k);
                        Id(j,k) = Id(j,k)-m*Id(i,k);
                    }
                }

            for(uint32_t i = 0; i < mat.getNumberOfRows(); ++i)
            {
                Type m = 1/mat(i,i);
                for(uint32_t j = 0; j < mat.getNumberOfRows(); ++j)
                {
                     mat(i,j) = m*mat(i,j);
                     Id(i,j) = m*Id(i,j);
                }

            }
        }
//    }

//    catch (const char* msg)
//    {
//        cerr<<msg<<endl;
//    }

    return Id;
}

template<typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* > *LinAlg::QR_Factorization_ModifiedGramSchmidt (LinAlg::Matrix<Type> input_matrix)
{
    Type s;
//    LinAlg::balance(input_matrix);
    uint32_t n = input_matrix.getNumberOfColumns(), m = input_matrix.getNumberOfRows();
    LinAlg::Matrix<Type> output_Q_matrix = LinAlg::Zeros<Type>(m,n);
    LinAlg::Matrix<Type> output_R_matrix = LinAlg::Zeros<Type>(m,n);
    for(uint32_t k = 0; k < n; ++k){
        s = 0;

        for(uint32_t j = 0; j < m; ++j){
            s = s + (input_matrix(j,k) * input_matrix(j,k));
        }
        output_R_matrix(k,k) = sqrt(s);

        for(uint32_t j = 0; j < m; ++j){
            output_Q_matrix(j,k) = input_matrix(j,k)/output_R_matrix(k,k);
        }

        for(uint32_t i = k ; i < n; ++i){
            s = 0;
            for(uint32_t j = 0; j < m; ++j){
                s += input_matrix(j,i)*output_Q_matrix(j,k);
            }
            output_R_matrix(k,i) = s;
            for(uint32_t j = 0; j < m; ++j){
                input_matrix(j,i) -= (output_R_matrix(k,i)*output_Q_matrix(j,k));
            }
        }
    }

    LinAlg::Matrix< LinAlg::Matrix<Type>* > *A = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*A)(0,0) = new LinAlg::Matrix<Type>(output_Q_matrix.getNumberOfRows(),output_Q_matrix.getNumberOfColumns());
    (*A)(0,1) = new LinAlg::Matrix<Type>(output_R_matrix.getNumberOfRows(),output_R_matrix.getNumberOfColumns());
    (*((*A)(0,0))) = output_Q_matrix;
    (*((*A)(0,1))) = output_R_matrix;
    return A;
}

template<typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* > *LinAlg::QR_Factorization (const LinAlg::Matrix<Type>& input_matrix)
{

    //Constants calculated and needed for the QR algorithm.
    uint32_t R_rows = input_matrix.getNumberOfRows(), R_columns = input_matrix.getNumberOfColumns();
    Type tal, gama, sigma;

    LinAlg::Matrix<Type> output_Q_matrix = LinAlg::Eye<Type>(R_rows);
    LinAlg::Matrix<Type> output_R_matrix = input_matrix;

    for(uint32_t j = 0; j < R_columns; j++)
        for(uint32_t i = R_rows - 1; i > j; i--)
        {
            if(output_R_matrix(i, j) != 0)
            {
                LinAlg::Matrix<Type> temp;

                temp = LinAlg::Eye<Type>(R_rows);

                if(std::abs(output_R_matrix(i - 1, j)) > std::abs(output_R_matrix(i, j)))
                {
                    tal = output_R_matrix(i, j)/output_R_matrix(i - 1, j);
                    gama = 1/(std::sqrt(1 + std::pow(tal, 2)));
                    sigma = tal*gama;
                }
                else
                {
                    tal = output_R_matrix(i - 1, j)/output_R_matrix(i, j);
                    sigma = 1/(std::sqrt(1 + std::pow(tal, 2)));
                    gama = sigma*tal;
                }

                temp(i, i) = gama;
                temp(i, i - 1) = sigma;
                temp(i - 1, i) = -sigma;
                temp(i - 1, i - 1) = gama;

                output_R_matrix = (~temp)*output_R_matrix;
                output_Q_matrix *= temp;
            }

        }
    for(uint32_t i = 0; i < output_R_matrix.getNumberOfRows(); ++i)
    {
        if(output_R_matrix(i,i) < 0)
        {
            for(uint32_t j = 0; j < output_R_matrix.getNumberOfColumns(); ++j)
            {
                output_Q_matrix(j,i) = -output_Q_matrix(j,i);
                output_R_matrix(i,j) = -output_R_matrix(i,j);
            }
        }
    }

    LinAlg::Matrix< LinAlg::Matrix<Type>* > *A = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*A)(0,0) = new LinAlg::Matrix<Type>(output_Q_matrix.getNumberOfRows(),output_Q_matrix.getNumberOfColumns());
    (*A)(0,1) = new LinAlg::Matrix<Type>(output_Q_matrix.getNumberOfRows(),output_Q_matrix.getNumberOfColumns());
    (*((*A)(0,0))) = output_Q_matrix;
    (*((*A)(0,1))) = output_R_matrix;
    return A;
}

template<typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* > *LinAlg::QR (const LinAlg::Matrix<Type>& input_matrix)
{
    LinAlg::Matrix<Type> Q, R;
//    LinAlg::QR_Factorization(input_matrix, output_Q_matrix, output_R_matrix);
    *(Q,R) = LinAlg::QR_Factorization_ModifiedGramSchmidt(input_matrix);

    LinAlg::Matrix< LinAlg::Matrix<Type>* > *A = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*A)(0,0) = new LinAlg::Matrix<Type>(Q.getNumberOfRows(),Q.getNumberOfColumns());
    (*A)(0,1) = new LinAlg::Matrix<Type>(R.getNumberOfRows(),R.getNumberOfColumns());
    (*((*A)(0,0))) = Q;
    (*((*A)(0,1))) = R;
    return A;
}

template<typename Type>
LinAlg::Matrix< LinAlg::Matrix<Type>* > *LinAlg::LU_Factorization (LinAlg::Matrix<Type> input_matrix){

    LinAlg::Matrix<Type> U = input_matrix;

    LinAlg::Matrix<Type> L = LinAlg::Eye<Type>(U.getNumberOfRows());

    for(uint32_t j= 0; j < U.getNumberOfColumns()-1; ++j)
        for(uint32_t i = j+1; i < U.getNumberOfRows(); ++i) {
            Type m = U(i,j)/U(j,j);
            for(uint32_t k = j; k < U.getNumberOfColumns(); ++k){
              U(i,k) = U(i,k) - m*U(j,k);
            }
            L(i,j) = m;
        }
    LinAlg::Matrix< LinAlg::Matrix<Type>* > *A = new LinAlg::Matrix< LinAlg::Matrix<Type>* >(1,2);
    (*A)(0,0) = new LinAlg::Matrix<Type>(L.getNumberOfRows(),L.getNumberOfColumns());
    (*A)(0,1) = new LinAlg::Matrix<Type>(U.getNumberOfRows(),U.getNumberOfColumns());
    (*((*A)(0,0))) = L;
    (*((*A)(0,1))) = U;
    return A;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::Hessemberg_Form (const LinAlg::Matrix<Type> &matrix_to_reduce)
{
    uint32_t aux = 0;
    LinAlg::Matrix<Type> ret(matrix_to_reduce);

    if(ret.isSquare())
    {
        for(uint32_t i = 2; i < ret.getNumberOfRows(); i++)
        {
            Type alfa = 0, gama;
            LinAlg::Matrix<Type> omega(ret.getNumberOfRows(), 1), H;

            for(uint32_t k = i - 1; k < ret.getNumberOfRows(); k++)
                alfa += std::pow(ret(k, aux), 2);

            if(ret(i - 1, aux) < 0)
                alfa = std::sqrt(alfa);
            else
                alfa = -std::sqrt(alfa);

            gama = std::sqrt((std::pow(alfa, 2)/2) - 0.5*ret(i - 1, aux)*alfa);

            for(uint32_t k = 1; k <= i - 2; k++)
                omega(k, 0) = 0;

            omega(i - 1, 0) = ((ret(i - 1, aux) - alfa))/(2*gama);

            for(uint32_t k = i; k < omega.getNumberOfRows(); k++)
                omega(k, 0) = ret(k, aux)/(2*gama);


            H = LinAlg::Eye<Type>(ret.getNumberOfRows()) - 2*omega*(~omega);
            ret = H*ret*H;

            aux++;
        }
    }

    return ret;
}

template<typename Type>
LinAlg::Matrix<Type> LinAlg::Hess (const LinAlg::Matrix<Type>& matrix_to_reduce)
{
    return LinAlg::Hessemberg_Form(matrix_to_reduce);
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::eigenVectors(const LinAlg::Matrix<Type> &matrix_to_get_eigens, uint32_t iterations)//sincronizado
{
    LinAlg::Matrix<Type> EigenValues = matrix_to_get_eigens;
    LinAlg::Matrix<Type> EigenVector = LinAlg::Eye<Type>(matrix_to_get_eigens.getNumberOfRows());
    LinAlg::Matrix<Type> Q, R;
    for(uint32_t j = 0; j < iterations; ++j ){
        *(Q,R) = LinAlg::QR(EigenValues);
        EigenValues = R*Q;
        EigenVector *= Q;
    }
    return EigenVector;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::eigenValues(const LinAlg::Matrix<Type> &matrix_to_get_eigens, uint32_t iterations, Type tolerance)//sincronizado
{
    LinAlg::Matrix<Type> EigenValues = LinAlg::Hess(matrix_to_get_eigens), temp = LinAlg::Eye<Type>(EigenValues.getNumberOfRows());
    LinAlg::Matrix<Type> Q, R;
    Type Re,IM; uint32_t size = EigenValues.getNumberOfColumns()-1;
    Matrix<Type> Raizes(size+1,2);

    uint32_t j=0;

    do{
        for(uint32_t i = size; i > 0; --i){
            LinAlg::balance(EigenValues);
            Type shift1 = EigenValues(i,i);
            *(Q,R) = LinAlg::QR(EigenValues - shift1*temp);
            EigenValues = R*Q + shift1*temp;
    //        LinAlg::balance(EigenValues);
    //        Type shift2 = EigenValues(size-1,size-1);
    //        *(Q,R) = LinAlg::QR(EigenValues - shift2*temp);
    //        EigenValues = R*Q + shift2*temp;
        }
        if(size <= 0)
            break;
        ++j;
    }while(j < iterations && fabs(EigenValues(size,size-1)) > tolerance);

    for(uint32_t i = 0; i <= size; ++i)
    {
        if(i+1 <= size){
            if(fabs(EigenValues(i+1,i)) >= tolerance && fabs(EigenValues(i,i+1)) >= tolerance)
            {
                Re = (EigenValues(i,i) + EigenValues(i+1,i+1))/2;
                IM = EigenValues(i+1,i)*EigenValues(i,i+1);
                if( IM > 0)
                    IM = (sqrt(IM));
                else
                    IM = (sqrt(-IM));
                Raizes(i,0)   = Re; Raizes(i,1)   = -IM;
                Raizes(i+1,0) = Re; Raizes(i+1,1) = IM;
                i++;
            }else{
                Raizes(i,0) = EigenValues(i,i); Raizes(i,1) = 0;
            }
         }else{
            Raizes(i,0) = EigenValues(i,i); Raizes(i,1) = 0;
         }
    }
    return Raizes;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::eigenValues_LU(const LinAlg::Matrix<Type> &matrix_to_get_eigenvalues, uint32_t iterations )//sincronizado
{
    LinAlg::Matrix<Type> L,U;
    *(L,U) = LinAlg::LU_Factorization(matrix_to_get_eigenvalues);

    for(uint32_t i = 0; i <= iterations; ++i)
    {
        *(L,U) = LinAlg::LU_Factorization(U * L);
    }
    return U * L;
}

template <class Type>
Type *LinAlg::MultPoly(const Type *lhs, const Type *rhs, const uint32_t &lhsSize, const  uint32_t  &rhsSize)
{
    Type *ret;

    ret = (Type*)calloc((lhsSize+rhsSize+1),(lhsSize+rhsSize+1)*sizeof(Type*));
    for(uint32_t i = 0; i < lhsSize; ++i)
        for(uint32_t j = 0; j < rhsSize; ++j)
        {
            ret[i+j] = ret[i+j] +  lhs[i]*rhs[j];
        }

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::abs(const LinAlg::Matrix<Type> &mat)
{
    LinAlg::Matrix<Type> ret = LinAlg::Zeros<Type>(mat.getNumberOfRows(), mat.getNumberOfColumns());
    for(uint32_t i = 0; i < mat.getNumberOfRows(); ++i)
        for(uint32_t j = 0; j < mat.getNumberOfColumns(); ++j)
            if(mat(i,j) > 0)
                ret(i,j) = mat(i,j);
            else
                ret(i,j) = -mat(i,j);

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::sqrtMatrix(const LinAlg::Matrix<Type> &mat)
{
    LinAlg::Matrix<Type> ret = LinAlg::Zeros<Type>(mat.getNumberOfRows(), mat.getNumberOfColumns());
    for(uint32_t i = 0; i < mat.getNumberOfRows(); ++i)
        for(uint32_t j = 0; j < mat.getNumberOfColumns(); ++j)
                ret(i,j) = sqrt(mat(i,j));

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::powMatrix(const LinAlg::Matrix<Type> &mat, Type potence)
{
    LinAlg::Matrix<Type> ret = mat;
    for(uint32_t i = 0; i < mat.getNumberOfRows(); ++i)
        for(uint32_t j = 0; j < mat.getNumberOfColumns(); ++j)
                ret(i,j) = pow(mat(i,j),potence);

    return ret;
}

template <typename Type>
LinAlg::Matrix<Type> LinAlg::mean(const LinAlg::Matrix<Type> &mat, const uint32_t &rowColumn)
{
    uint32_t row = 2, column = 1;
    LinAlg::Matrix<Type> ret;

    if(rowColumn == row)
    {
        uint32_t length = mat.getNumberOfColumns();
        ret = Zeros<Type>(mat.getNumberOfRows(),1);

        for(uint32_t i = 0; i < mat.getNumberOfRows(); ++i)
            for(uint32_t j = 0; j < mat.getNumberOfColumns(); ++j)
                ret(i,0) += mat(i,j)/length;
    }
    else if(rowColumn == column)
    {
        uint32_t length = mat.getNumberOfRows();
        ret = Zeros<Type>(1,mat.getNumberOfColumns());

        for(uint32_t i = 0; i < mat.getNumberOfColumns(); ++i)
            for(uint32_t j = 0; j < mat.getNumberOfRows(); ++j)
                ret(0,i) += mat(j,i)/length;
    }

    return ret;
}

template <typename Type>
inline LinAlg::Matrix<Type> LinAlg::expM(const LinAlg::Matrix<Type> &mat, const Type &sampleTime, const uint32_t &precision)
{
    LinAlg::Matrix<Type> ret(mat.getNumberOfRows(), mat.getNumberOfColumns());

    LinAlg::Matrix<Type> max, maxInd;
    *(max, maxInd) = LinAlg::max(LinAlg::abs(mat));
    *(max, maxInd) = LinAlg::max(LinAlg::abs(max));
    uint32_t factor =  (uint32_t)ceil(max(0,0)*sampleTime);

    //taylor
    for(uint32_t i = 0; i < precision; ++i)
        ret += (1/(Type)factorial(i))*((mat*sampleTime/factor)^i);

    ret ^= factor;
    return ret;
}

template <typename Type>
inline LinAlg::Matrix<Type> LinAlg::logM(const LinAlg::Matrix<Type> &mat, const Type &sampleTime, const uint32_t &precision)
{
    LinAlg::Matrix<Type> I = LinAlg::Eye<Type> (mat.getNumberOfRows());
    LinAlg::Matrix<Type> ret(mat.getNumberOfRows(),mat.getNumberOfRows());
    LinAlg::Matrix<Type> max, maxInd, AdTemp;
    *(max, maxInd) = LinAlg::max(LinAlg::abs(mat));
    *(max, maxInd) = LinAlg::max(LinAlg::abs(max));
    Type factor =  (ceil(max(0,0))/sampleTime);

    for(uint32_t i = 1; i < precision + 1; ++i)
        ret += -(pow(-1,i))*((mat/factor - I)^i)/i;
    ret = (ret + log(factor)*I)/sampleTime;

    return ret;
}
