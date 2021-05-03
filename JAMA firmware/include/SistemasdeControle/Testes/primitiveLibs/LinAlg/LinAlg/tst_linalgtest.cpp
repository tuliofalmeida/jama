#include <QString>
#include <QtTest>
#include <complex>

#define testMatrix
#include "../../../../headers/primitiveLibs/LinAlg/linalg.h"
#include <complex>

class LinAlgTest : public QObject
{
    Q_OBJECT

public:
    LinAlgTest(){}

private Q_SLOTS:

    void traceDouble ();
    void HessDoubleCase1 ();
    void HessDoubleCase2 ();
    void HessFormDoubleCase1 ();
    void HessFormDoubleCase2 ();
    void QR_Factorization_ModifiedGramSchmidtDouble ();
    void QR_FactorizationDouble ();
    void QRDouble ();
    void LU_FactorizationDouble ();
    void balanceDouble ();
    void eigenValuesDouble();
    void eigenValuesDoubleCase2();
    void eigenVectorsDouble(); //Continuar daqui;
    void eigenValues_LUDouble ();
    void inv_numericDouble ();
    void caracteristicPolynomDouble ();
    void multPolyDouble ();
    void absDouble ();
    void sqrtMatrixDouble ();
    void powMatrixDouble ();
    void meanDoubleCase1 ();
    void meanDoubleCase2 ();
    void meanDoubleCase3 ();
    void expMDouble ();
    void logMDouble ();
};

void LinAlgTest::traceDouble (){
    LinAlg::Matrix<double> B = LinAlg::Ones<double>(10,10);
    double A;
    QBENCHMARK {
        A = LinAlg::trace(B);
    }
    QVERIFY2(A == 10, "Falhou ao calcular o traco da matriz com valor double");
}

void LinAlgTest::HessDoubleCase1 ()
{
    LinAlg::Matrix<double> A, B = "1, 8, -10; -4, 2, 4; -5, 2, 8";
    QBENCHMARK {
        A = LinAlg::Hess(B);
    }
    QVERIFY2(A.getNumberOfColumns() == 3 && A.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(A(0,0) - 1) <= 0.001      && fabs(A(0,1) - 2.8111) <= 0.001   && abs(A(0,2) - (-12.4939)) <= 0.001  &&
             fabs(A(1,0) - 6.4031) <= 0.001 && fabs(A(1,1) - 8.5854) <= 0.001   && abs(A(1,2) - (-3.2683)) <= 0.001   &&
             fabs(A(2,0)) <= 0.001          && fabs(A(2,1) - (-1.2683)) <= 0.001 && abs(A(2,2) - 1.4146) <= 0.001,
    "Falhou ao verificar a forma de hessemberg");
}

void LinAlgTest::HessDoubleCase2 ()
{
    LinAlg::Matrix<double> A, B = "1,7,7,2,9;3,1,9,0,6;3,7,9,7,6;7,5,3,5,9;1,8,7,5,8";
    QBENCHMARK {
        A = LinAlg::Hess(B);
    }
    QVERIFY2(A.getNumberOfColumns() == 5 && A.getNumberOfRows() == 5, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(A(0,0) - 1)         <= 0.001      && fabs(A(0,1) - (-7.8824)) <= 0.001   && abs(A(0,2) - (-9.5752)) <= 0.001 && fabs(A(0,3) - (5.4014))  <= 0.001   && abs(A(0,4) - (0.0890))  <= 0.001 &&
             fabs(A(1,0) - (-8.2462)) <= 0.001      && fabs(A(1,1) - (14.4265)) <= 0.001   && abs(A(1,2) - (12.3793)) <= 0.001 && fabs(A(1,3) - (-4.7446)) <= 0.001   && abs(A(1,4) - (-2.0256)) <= 0.001 &&
             fabs(A(2,0) - 0)         <= 0.001      && fabs(A(2,1) - (12.1997)) <= 0.001   && abs(A(2,2) - ( 7.0241)) <= 0.001 && fabs(A(2,3) - (-4.2974)) <= 0.001   && abs(A(2,4) - (2.1237))  <= 0.001 &&
             fabs(A(3,0) - 0)         <= 0.001      && fabs(A(3,1) - (0))       <= 0.001   && abs(A(3,2) - (-6.3114)) <= 0.001 && fabs(A(3,3) - (-1.3976)) <= 0.001   && abs(A(3,4) - (-2.7984)) <= 0.001 &&
             fabs(A(4,0) - 0)         <= 0.001      && fabs(A(4,1) - (0))       <= 0.001   && abs(A(4,2) - (0))       <= 0.001 && fabs(A(4,3) - ( 2.7502)) <= 0.001   && abs(A(4,4) - (2.9470))  <= 0.001,
    "Falhou ao verificar a forma de hessemberg");
}

void LinAlgTest::HessFormDoubleCase1 ()
{
    LinAlg::Matrix<double> A, B = "1, 8, -10; -4, 2, 4; -5, 2, 8";
    QBENCHMARK {
        A = LinAlg::Hessemberg_Form(B);
    }
    QVERIFY2(A.getNumberOfColumns() == 3 && A.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(A(0,0) - 1) <= 0.001      && fabs(A(0,1) - 2.8111) <= 0.001   && abs(A(0,2) - (-12.4939)) <= 0.001  &&
             fabs(A(1,0) - 6.4031) <= 0.001 && fabs(A(1,1) - 8.5854) <= 0.001   && abs(A(1,2) - (-3.2683)) <= 0.001   &&
             fabs(A(2,0)) <= 0.001          && fabs(A(2,1) - (-1.2683)) <= 0.001 && abs(A(2,2) - 1.4146) <= 0.001,
    "Falhou ao verificar a forma de hessemberg");
}

void LinAlgTest::HessFormDoubleCase2 ()
{
    LinAlg::Matrix<double> A, B = "1,7,7,2,9;3,1,9,0,6;3,7,9,7,6;7,5,3,5,9;1,8,7,5,8";
    QBENCHMARK {
        A = LinAlg::Hessemberg_Form(B);
    }
    QVERIFY2(A.getNumberOfColumns() == 5 && A.getNumberOfRows() == 5, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(A(0,0) - 1)         <= 0.001      && fabs(A(0,1) - (-7.8824)) <= 0.001   && abs(A(0,2) - (-9.5752)) <= 0.001 && fabs(A(0,3) - (5.4014))  <= 0.001   && abs(A(0,4) - (0.0890))  <= 0.001 &&
             fabs(A(1,0) - (-8.2462)) <= 0.001      && fabs(A(1,1) - (14.4265)) <= 0.001   && abs(A(1,2) - (12.3793)) <= 0.001 && fabs(A(1,3) - (-4.7446)) <= 0.001   && abs(A(1,4) - (-2.0256)) <= 0.001 &&
             fabs(A(2,0) - 0)         <= 0.001      && fabs(A(2,1) - (12.1997)) <= 0.001   && abs(A(2,2) - ( 7.0241)) <= 0.001 && fabs(A(2,3) - (-4.2974)) <= 0.001   && abs(A(2,4) - (2.1237))  <= 0.001 &&
             fabs(A(3,0) - 0)         <= 0.001      && fabs(A(3,1) - (0))       <= 0.001   && abs(A(3,2) - (-6.3114)) <= 0.001 && fabs(A(3,3) - (-1.3976)) <= 0.001   && abs(A(3,4) - (-2.7984)) <= 0.001 &&
             fabs(A(4,0) - 0)         <= 0.001      && fabs(A(4,1) - (0))       <= 0.001   && abs(A(4,2) - (0))       <= 0.001 && fabs(A(4,3) - ( 2.7502)) <= 0.001   && abs(A(4,4) - (2.9470))  <= 0.001,
    "Falhou ao verificar a forma de hessemberg");
}

void LinAlgTest::QR_Factorization_ModifiedGramSchmidtDouble (){
    LinAlg::Matrix<double> Q, R, B = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        *(Q,R) = LinAlg::QR_Factorization_ModifiedGramSchmidt(B);
    }

    QVERIFY2(Q.getNumberOfColumns() == 3 && Q.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Q(0,0) - 0.7001) <= 0.01 && fabs(Q(0,1) - (0.6999))  <= 0.01 && fabs(Q(0,2) - (-0.1412)) <= 0.01 &&
             fabs(Q(1,0) - 0.7001) <= 0.01 && fabs(Q(1,1) - (-0.7118)) <= 0.01 && fabs(Q(1,2) - (-0.0565)) <= 0.01 &&
             fabs(Q(2,0) - 0.1400) <= 0.01 && fabs(Q(2,1) - (0.0593))  <= 0.01 && fabs(Q(2,2) - (0.9884))  <= 0.01,
    "Falhou ao verificar o Q da Fatoração QR");

    QVERIFY2(R.getNumberOfColumns() == 3 && R.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(R(0,0) - 7.141) <= 0.01 && fabs(R(0,1) - 5.041) <= 0.01 && fabs(R(0,2) - 5.321) <= 0.01 &&
             fabs(R(1,0) - 0)     <= 0.01 && fabs(R(1,1) - 4.959) <= 0.01 && fabs(R(1,2) - 3.262) <= 0.01 &&
             fabs(R(2,0) - 0)     <= 0.01 && fabs(R(2,1) - 0)     <= 0.01 && fabs(R(2,2) - 7.144) <= 0.01,
    "Falhou ao verificar o R da Fatoração QR");
}
void LinAlgTest::QR_FactorizationDouble ()
{
    LinAlg::Matrix<double> Q, R, B = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        *(Q,R) = LinAlg::QR_Factorization(B);
    }
    QVERIFY2(Q.getNumberOfColumns() == 3 && Q.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Q(0,0) - 0.7001) <= 0.01 && fabs(Q(0,1) - (0.6999))  <= 0.01 && fabs(Q(0,2) - (-0.1412)) <= 0.01 &&
             fabs(Q(1,0) - 0.7001) <= 0.01 && fabs(Q(1,1) - (-0.7118)) <= 0.01 && fabs(Q(1,2) - (-0.0565)) <= 0.01 &&
             fabs(Q(2,0) - 0.1400) <= 0.01 && fabs(Q(2,1) - (0.0593))  <= 0.01 && fabs(Q(2,2) - (0.9884))  <= 0.01,
    "Falhou ao verificar o Q da Fatoração QR");

    QVERIFY2(R.getNumberOfColumns() == 3 && R.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(R(0,0) - 7.141) <= 0.01 && fabs(R(0,1) - 5.041) <= 0.01 && fabs(R(0,2) - 5.321) <= 0.01 &&
             fabs(R(1,0) - 0)     <= 0.01 && fabs(R(1,1) - 4.959) <= 0.01 && fabs(R(1,2) - 3.262) <= 0.01 &&
             fabs(R(2,0) - 0)     <= 0.01 && fabs(R(2,1) - 0)     <= 0.01 && fabs(R(2,2) - 7.144) <= 0.01,
    "Falhou ao verificar o R da Fatoração QR");
}
void LinAlgTest::QRDouble ()
{
    LinAlg::Matrix<double> Q, R, B = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        *(Q,R) = LinAlg::QR(B);
    }
    QVERIFY2(Q.getNumberOfColumns() == 3 && Q.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Q(0,0) - 0.7001) <= 0.01 && fabs(Q(0,1) - (0.6999))  <= 0.01 && fabs(Q(0,2) - (-0.1412)) <= 0.01 &&
             fabs(Q(1,0) - 0.7001) <= 0.01 && fabs(Q(1,1) - (-0.7118)) <= 0.01 && fabs(Q(1,2) - (-0.0565)) <= 0.01 &&
             fabs(Q(2,0) - 0.1400) <= 0.01 && fabs(Q(2,1) - (0.0593))  <= 0.01 && fabs(Q(2,2) - (0.9884))  <= 0.01,
    "Falhou ao verificar o Q da Fatoração QR");

    QVERIFY2(R.getNumberOfColumns() == 3 && R.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(R(0,0) - 7.141) <= 0.01 && fabs(R(0,1) - 5.041) <= 0.01 && fabs(R(0,2) - 5.321) <= 0.01 &&
             fabs(R(1,0) - 0)     <= 0.01 && fabs(R(1,1) - 4.959) <= 0.01 && fabs(R(1,2) - 3.262) <= 0.01 &&
             fabs(R(2,0) - 0)     <= 0.01 && fabs(R(2,1) - 0)     <= 0.01 && fabs(R(2,2) - 7.144) <= 0.01,
    "Falhou ao verificar o R da Fatoração QR");
}

void LinAlgTest::LU_FactorizationDouble ()
{
    LinAlg::Matrix<double> L, U, B = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        *(L,U) = LinAlg::LU_Factorization(B);
    }
    QVERIFY2(U.getNumberOfColumns() == 3 && U.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(U(0,0) - 5.0000) <= 0.001 && fabs(U(0,1) - (7.0000))  <= 0.001 && fabs(U(0,2) - (5.0000)) <= 0.001 &&
             fabs(U(1,0) - 0.0000) <= 0.001 && fabs(U(1,1) - (-7.0000)) <= 0.001 && fabs(U(1,2) - (-4.0000)) <= 0.001 &&
             fabs(U(2,0) - 0.0000) <= 0.001 && fabs(U(2,1) - (0.0000))  <= 0.001 && fabs(U(2,2) - (7.2286))  <= 0.001,
    "Falhou ao verificar o U da Fatoração LU");

    QVERIFY2(L.getNumberOfColumns() == 3 && L.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(L(0,0) - 1.0000) <= 0.01 && fabs(L(0,1) - 0.000) <= 0.01 && fabs(L(0,2) - 0.000) <= 0.01 &&
             fabs(L(1,0) - 1.0000) <= 0.01 && fabs(L(1,1) - 1.000) <= 0.01 && fabs(L(1,2) - 0.000) <= 0.01 &&
             fabs(L(2,0) - 0.2000) <= 0.01 && fabs(L(2,1) - 0.057) <= 0.01 && fabs(L(2,2) - 1.000) <= 0.01,
    "Falhou ao verificar o L da Fatoração LU");
}

void LinAlgTest::balanceDouble ()
{
    LinAlg::Matrix<double> A = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
       LinAlg::balance(A);
    }
    QVERIFY2(A.getNumberOfColumns() == 3 && A.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(A(0,0) - 5.0000) <= 0.001 && fabs(A(0,1) - (7.0000))  <= 0.001 && fabs(A(0,2) - (2.5000)) <= 0.001 &&
             fabs(A(1,0) - 5.0000) <= 0.001 && fabs(A(1,1) - (0.0000))  <= 0.001 && fabs(A(1,2) - (0.5000)) <= 0.001 &&
             fabs(A(2,0) - 2.0000) <= 0.001 && fabs(A(2,1) - (2.0000))  <= 0.001 && fabs(A(2,2) - (8.000))  <= 0.001,
    "Falhou ao verificar a função balance");
}

void LinAlgTest::eigenValuesDouble()
{
    LinAlg::Matrix<double> Ava, A = "5,7,5;5,0,1;1,1,8";
    A = (~A)*A;
    QBENCHMARK {
        Ava = LinAlg::eigenValues(A);
    }

    QVERIFY2(Ava.getNumberOfColumns() == 2 && Ava.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Ava(0,0) - 145.589) <= 0.01 && fabs(Ava(0,1)) <= 0.01 &&
             fabs(Ava(1,0) - 13.994)  <= 0.01 && fabs(Ava(1,1)) <= 0.01 &&
             fabs(Ava(2,0) - 31.417)  <= 0.01 && fabs(Ava(2,1)) <= 0.01,
    "Falhou ao verificar os autovalores");
}

void LinAlgTest::eigenValuesDoubleCase2()
{
    LinAlg::Matrix<double> Ava, A = "1, 8, -10; -4, 2, 4; -5, 2, 8";
    QBENCHMARK {
        Ava = LinAlg::eigenValues(A);
    }

    QVERIFY2(Ava.getNumberOfColumns() == 2 && Ava.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Ava(0,0) - 11.622) <= 0.01 && fabs(Ava(0,1)) <= 0.01 &&
             fabs(Ava(1,0) + 0.311)  <= 0.01 && fabs(Ava(1,1)+2.670) <= 0.01 &&
             fabs(Ava(2,0) + 0.311)  <= 0.01 && fabs(Ava(2,1)-2.670) <= 0.01,
    "Falhou ao verificar os autovalores");
}

void LinAlgTest::eigenVectorsDouble()
{
    LinAlg::Matrix<double> Ave, A = "5,7,5;5,0,1;1,1,8";
    A = (~A)*A;
    QBENCHMARK {
        Ave = LinAlg::eigenVectors(A);
    }
    QVERIFY2(Ave.getNumberOfColumns() == 3 && Ave.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Ave(0,0) - 0.480) <= 0.001 && fabs(Ave(0,1) - (-0.618)) && fabs(Ave(0,2) - ( 0.622)) &&
             fabs(Ave(1,0) - 0.504) <= 0.001 && fabs(Ave(1,1) - (-0.386)) && fabs(Ave(1,2) - (-0.773)) &&
             fabs(Ave(2,0) - 0.718) <= 0.001 && fabs(Ave(2,1) - ( 0.685)) && fabs(Ave(2,2) - ( 0.126)),
    "Falhou ao verificar os autovalores");
}

void LinAlgTest::eigenValues_LUDouble ()
{
    LinAlg::Matrix<double> Ava, A = "5,7,5;5,0,1;1,1,8";
    A = (~A)*A;
    QBENCHMARK {
        Ava = LinAlg::eigenValues_LU(A);
    }
    QVERIFY2(Ava.getNumberOfColumns() == 3 && Ava.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Ava(0,0) - 145.589) <= 0.001 &&
             fabs(Ava(1,1) - 31.417)  <= 0.001 &&
             fabs(Ava(2,2) - 13.994)  <= 0.001,
    "Falhou ao verificar os autovalores");
}

void LinAlgTest::caracteristicPolynomDouble ()
{
    LinAlg::Matrix<double> A, B = "1, 8, -10; -4, 2, 4; -5, 2, 8";
    QBENCHMARK {
        A = LinAlg::characteristicPolynom(B);
    }
    QVERIFY2(A.getNumberOfColumns() == 4 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(A(0,0) - 1) <= 0.001 && fabs(A(0,1) - (-11)) <= 0.001 && fabs(A(0,2)) <= 0.001 && fabs(A(0,3) - (-84)) <= 0.001,
             "Falhou ao verificar os coeficientes do polinomio caracteristico");
}

void LinAlgTest::inv_numericDouble ()
{
    LinAlg::Matrix<double> Ave, A = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        Ave = LinAlg::inv_numeric(A);
    }
    QVERIFY2(Ave.getNumberOfColumns() == 3 && Ave.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Ave(0,0) - 0.0040)    <= 0.001 && fabs(Ave(0,1) - ( 0.2016)) && fabs(Ave(0,2) - (-0.0277)) &&
             fabs(Ave(1,0) - 0.1542)    <= 0.001 && fabs(Ave(1,1) - (-0.1383)) && fabs(Ave(1,2) - (-0.0791)) &&
             fabs(Ave(2,0) - (-0.0198)) <= 0.001 && fabs(Ave(2,1) - (-0.0079)) && fabs(Ave(2,2) - ( 0.1383)),
    "Falhou ao verificar os elementos da inversa matricial");
}

void LinAlgTest::multPolyDouble ()
{
    double *A;
    double *den1 = new double[3], *den2 = new double[3];
    den1[0] = 1;den1[1] = 2;den1[2] = 1;
    den2[0] = 1;den2[1] = 2;den2[2] = 1;
    unsigned sizeDen1 = 3, sizeDen2 = 3;
    QBENCHMARK {
        A = LinAlg::MultPoly(den1,den2,sizeDen1,sizeDen2);
    }
    QVERIFY2(A[0] == 1 && A[1] == 4 && A[2] == 6 && A[3] == 4 && A[4] == 1, "Falhou ao testar o resultado da multiplicação dos Polinomios");
}

void LinAlgTest::absDouble ()
{
    LinAlg::Matrix<double> Ave, A = "-5,7,-5;5,0,-1;1,-1,8";
    QBENCHMARK {
        Ave = LinAlg::abs(A);
    }
    QVERIFY2(Ave.getNumberOfColumns() == 3 && Ave.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(Ave(0,0) == 5 && Ave(0,1) == 7 && Ave(0,2) == 5&&
             Ave(1,0) == 5 && Ave(1,1) == 0 && Ave(1,2) == 1&&
             Ave(2,0) == 1 && Ave(2,1) == 1 && Ave(2,2) == 8,
    "Falhou ao verificar os elementos do módulo da matriz");
}

void LinAlgTest::sqrtMatrixDouble ()
{
    LinAlg::Matrix<double> Ave, A = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        Ave = LinAlg::sqrtMatrix(A);
    }
    QVERIFY2(Ave.getNumberOfColumns() == 3 && Ave.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(Ave(0,0) == sqrt(5) && Ave(0,1) == sqrt(7) && Ave(0,2) == sqrt(5) &&
             Ave(1,0) == sqrt(5) && Ave(1,1) == sqrt(0) && Ave(1,2) == sqrt(1) &&
             Ave(2,0) == sqrt(1) && Ave(2,1) == sqrt(1) && Ave(2,2) == sqrt(8),
    "Falhou ao verificar os elementos do módulo da matriz");
}

void LinAlgTest::powMatrixDouble ()
{
    LinAlg::Matrix<double> Ave, A = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        Ave = LinAlg::powMatrix(A,2.0);
    }
    QVERIFY2(Ave.getNumberOfColumns() == 3 && Ave.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(Ave(0,0) == pow(5,2) && Ave(0,1) == pow(7,2) && Ave(0,2) == pow(5,2) &&
             Ave(1,0) == pow(5,2) && Ave(1,1) == pow(0,2) && Ave(1,2) == pow(1,2) &&
             Ave(2,0) == pow(1,2) && Ave(2,1) == pow(1,2) && Ave(2,2) == pow(8,2),
    "Falhou ao verificar os elementos da potência da matriz");
}

void LinAlgTest::meanDoubleCase1 ()
{
    LinAlg::Matrix<double> Ave, A = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        Ave = LinAlg::mean(A);
    }
    QVERIFY2(Ave.getNumberOfColumns() == 3 && Ave.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Ave(0,0) - 11.0/3.0) <= 0.001 && fabs(Ave(0,1) - 8.0/3.0) <= 0.001 && fabs(Ave(0,2) - 14.0/3.0) <= 0.001,
    "Falhou ao verificar os elementos da media da matriz");
}

void LinAlgTest::meanDoubleCase2 ()
{
    LinAlg::Matrix<double> Ave, A = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        Ave = LinAlg::mean(A,1);
    }
    QVERIFY2(Ave.getNumberOfColumns() == 3 && Ave.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Ave(0,0) - 11.0/3.0) <= 0.001 && fabs(Ave(0,1) - 8.0/3.0) <= 0.001 && fabs(Ave(0,2) - 14.0/3.0) <= 0.001,
    "Falhou ao verificar os elementos da media da matriz");
}

void LinAlgTest::meanDoubleCase3 ()
{
    LinAlg::Matrix<double> Ave, A = "5,7,5;5,0,1;1,1,8";
    QBENCHMARK {
        Ave = LinAlg::mean(A,2);
    }
    QVERIFY2(Ave.getNumberOfColumns() == 1 && Ave.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(Ave(0,0) - 17.0/3.0) <= 0.001 && fabs(Ave(1,0) - 2) <= 0.001 && fabs(Ave(2,0) - 10.0/3.0) <= 0.001,
    "Falhou ao verificar os elementos da media da matriz");
}

void LinAlgTest::expMDouble ()
{
    LinAlg::Matrix<double> expm, A = "0.2699,0.7104,0.8504;0.5246,0.3119,0.9116;0.9727,0.2915,0.6393";
    QBENCHMARK {
        expm = LinAlg::expM(A);
    }

    QVERIFY2(expm.getNumberOfColumns() == 3 && expm.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(expm(0,0) - 2.4973) <= 0.001 && fabs(expm(0,1) - (1.4665)) <= 0.001 && fabs(expm(0,2) - (2.2973)) <= 0.001 &&
             fabs(expm(1,0) - 1.6889) <= 0.001 && fabs(expm(1,1) - (2.0880)) <= 0.001 && fabs(expm(1,2) - (2.2821)) <= 0.001 &&
             fabs(expm(2,0) - 2.1215) <= 0.001 && fabs(expm(2,1) - (1.2017)) <= 0.001 && fabs(expm(2,2) - (3.1609)) <= 0.001,
    "Falhou ao verificar os elementos da exponencial matricial");
}

void LinAlgTest::logMDouble ()
{
    LinAlg::Matrix<long double> logm, A = "2.4973,1.4665,2.2973;1.6889,2.0880,2.2821;2.1215,1.2017,3.1609";
    QBENCHMARK {
        logm = LinAlg::logM(A);
    }

    QVERIFY2(logm.getNumberOfColumns() == 3 && logm.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(logm(0,0) - 0.2699) <= 0.001 && fabs(logm(0,1) - (0.7104)) <= 0.001 && fabs(logm(0,2) - (0.8504)) <= 0.001 &&
             fabs(logm(1,0) - 0.5246) <= 0.001 && fabs(logm(1,1) - (0.3119)) <= 0.001 && fabs(logm(1,2) - (0.9116)) <= 0.001 &&
             fabs(logm(2,0) - 0.9727) <= 0.001 && fabs(logm(2,1) - (0.2915)) <= 0.001 && fabs(logm(2,2) - (0.6393)) <= 0.001,
    "Falhou ao verificar os elementos da exponencial matricial");

    LinAlg::Matrix<long double> logmc, Ac = "0.9350,0.3963,0.7566;0.4795,0.7051,0.9955;0.2318,0.5586,0.9624";
    QBENCHMARK {
        logmc = LinAlg::logM(Ac);
    }
    QVERIFY2(logmc.getNumberOfColumns() == 3 && logmc.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(fabs(logmc(0,0) - (-0.2077)) <= 0.01 && fabs(logmc(0,1) - (0.2322 )) <= 0.01 && fabs(logmc(0,2) -  (0.7889 )) <= 0.01 &&
             fabs(logmc(1,0) - ( 0.7265)) <= 0.01 && fabs(logmc(1,1) - (-1.3362)) <= 0.01 && fabs(logmc(1,2) -  (1.6495 )) <= 0.01 &&
             fabs(logmc(2,0) - ( 0.0083)) <= 0.01 && fabs(logmc(2,1) - (1.1029 )) <= 0.01 && fabs(logmc(2,2) -  (-0.7376)) <= 0.01,
    "Falhou ao verificar os elementos da exponencial matricial");
}

QTEST_APPLESS_MAIN(LinAlgTest)

#include "tst_linalgtest.moc"
