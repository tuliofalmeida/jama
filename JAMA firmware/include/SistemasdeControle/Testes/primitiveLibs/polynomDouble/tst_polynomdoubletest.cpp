#include <QString>
#include <QtTest>
#define testPolynom
#include "../../../headers/primitiveLibs/polynom.h"


class PolynomDoubleTest : public QObject
{
    Q_OBJECT

public:
    PolynomDoubleTest(){}

private Q_SLOTS:
    void constructorPolynomEscalarDouble ();
    void constructorPolynomMatrixNumeratorDoubleCase1 ();
    void constructorPolynomMatrixNumeratorDoubleCase2 ();
    void constructorPolynomMatrixNumeratorDoubleCase3 ();
    void PolynomCopyConstructorDoubleCase1 ();
    void PolynomCopyConstructorDoubleCase2 ();
    void constructorPolynomMatrixNumeratorDenominatorDoubleCase1 ();
    void constructorPolynomMatrixNumeratorDenominatorDoubleCase2 ();
    void constructorPolynomVoidDouble ();
    void destructorPolynomDoubleCase1 ();
    void destructorPolynomDoubleCase2 ();

    void getVarDoubleCase1 ();
    void getVarDoubleCase2 ();
    void getVarDoubleCase3 ();
    void getVarDoubleCase4 ();
    void changeVarDouble ();
    void getNumSizeDouble ();
    void getDenSizeDouble ();
    void getNumDouble ();
    void getDenDouble ();
    void setNumDoubleCase1 ();
    void setNumDoubleCase2 ();
    void setDenDoubleCase1 ();
    void setDenDoubleCase2 ();
    void assignOperatorDouble ();
    void copyAssignOperatorDouble ();
    void assignOperatorOtherTypeDouble ();
    void operatorSumAccumulatorScalarDoubleCase1 ();
    void operatorSumAccumulatorScalarDoubleCase2 ();
    void operatorSumAccumulatorScalarDoubleCase3 ();
    void operatorSumAccumulatorScalarDoubleCase4 ();
    void operatorSumAccumulatorScalarDoubleCase5 ();
    void operatorSumAccumulatorPolynomDoubleCase1 ();
    void operatorSumAccumulatorPolynomDoubleCase2 ();
    void operatorSubtractionAccumulatorScalarDoubleCase1 ();
    void operatorSubtractionAccumulatorScalarDoubleCase2 ();
    void operatorSubtractionAccumulatorScalarDoubleCase3 ();
    void operatorSubtractionAccumulatorScalarDoubleCase4 ();
    void operatorSubtractionAccumulatorScalarDoubleCase5 ();
    void operatorSubtractionAccumulatorPolynomDoubleCase1 ();
    void operatorSubtractionAccumulatorPolynomDoubleCase2 ();
    void operatorMultiplicationAccumulatorScalarDoubleCase1 ();
    void operatorMultiplicationAccumulatorScalarDoubleCase2 ();
    void operatorMultiplicationAccumulatorPolynomDoubleCase1 ();
    void operatorMultiplicationAccumulatorPolynomDoubleCase2 ();
    void operatorDivisionAccumulatorScalarDoubleCase1 ();
    void operatorDivisionAccumulatorScalarDoubleCase2 ();
    void operatorDivisionAccumulatorPolynomDoubleCase1 ();
    void operatorDivisionAccumulatorPolynomDoubleCase2 ();
    void operatorDivisionAccumulatorPolynomDoubleCase3 ();
    void operatorPotentiationAccumulatorScalarDoubleCase1 ();
    void operatorPotentiationAccumulatorScalarDoubleCase2 ();
    void operatorPotentiationAccumulatorScalarDoubleCase3 ();
    void operatorPotentiationAccumulatorScalarDoubleCase4 ();
    void operatorSumScalarDoubleCase1 ();
    void operatorSumScalarDoubleCase2 ();
    void operatorSumScalarDoubleCase3 ();
    void operatorSumScalarDoubleCase4 ();
    void operatorSumScalarDoubleCase5 ();
    void operatorSumScalarDoubleCase6 ();
    void operatorSumScalarDoubleCase7 ();
    void operatorSumScalarDoubleCase8 ();
    void operatorSumScalarDoubleCase9 ();
    void operatorSumScalarDoubleCase10 ();
    void operatorSumPolynomDoubleCase1 ();
    void operatorSumPolynomDoubleCase2 ();
    void operatorSubtractionScalarDoubleCase1 ();
    void operatorSubtractionScalarDoubleCase2 ();
    void operatorSubtractionScalarDoubleCase3 ();
    void operatorSubtractionScalarDoubleCase4 ();
    void operatorSubtractionScalarDoubleCase5 ();
    void operatorSubtractionScalarDoubleCase6 ();
    void operatorSubtractionScalarDoubleCase7 ();
    void operatorSubtractionScalarDoubleCase8 ();
    void operatorSubtractionScalarDoubleCase9 ();
    void operatorSubtractionScalarDoubleCase10 ();
    void operatorSubtractionPolynomDoubleCase1 ();
    void operatorSubtractionPolynomDoubleCase2 ();
    void operatorMultiplicationScalarDoubleCase1 ();
    void operatorMultiplicationScalarDoubleCase2 ();
    void operatorMultiplicationScalarDoubleCase3 ();
    void operatorMultiplicationScalarDoubleCase4 ();
    void operatorMultiplicationPolynomDoubleCase1 ();
    void operatorMultiplicationPolynomDoubleCase2 ();
    void operatorDivisionScalarDoubleCase1 ();
    void operatorDivisionScalarDoubleCase2 ();
    void operatorDivisionScalarDoubleCase3 ();
    void operatorDivisionScalarDoubleCase4 ();
    void operatorDivisionPolynomDoubleCase1 ();
    void operatorDivisionPolynomDoubleCase2 ();
    void operatorPotentiationScalarDoubleCase1 ();
    void operatorPotentiationScalarDoubleCase2 ();
    void operatorPotentiationScalarDoubleCase3 ();
    void operatorPotentiationScalarDoubleCase4 ();
    void equalityOperator();
    void operatorDivisionMatrixPolynom ();
    void minusOperatorDouble ();
    void derivateCase1();
    void derivateCase2();
    void derivateCase3();
    void derivateCase4();
    void derivateCase5();
    void printSmallPolynomCase1 ();
    void printSmallPolynomCase2 ();
    void printSmallPolynomCase3 ();
    void printSmallPolynomCase4 ();
    void printSmallPolynomCase5 ();
    void printSmallPolynomCase6 ();
    void printSmallPolynomCase7 ();
    void printSmallPolynomCase8 ();
    void printSmallPolynomCase9 ();
    void printSmallPolynomCase10 ();
    void printSmallPolynomCase11 ();
    void printSmallPolynomCase12 ();
    void printSmallPolynomCase13 ();
    void printSmallPolynomCase14 ();
    void printSmallPolynomCase15 ();
    void printSmallPolynomCase16 ();
    void printSmallPolynomCase17 ();
    void printSmallPolynomCase18 ();
    void printSmallPolynomCase19 ();
    void printSmallPolynomCase20 ();
    void printSmallPolynomCase21 ();
    void printSmallPolynomCase22 ();
    void printSmallPolynomCase23 ();
    void printSmallPolynomCase24 ();
    void printSmallPolynomCase25 ();

    void printPolynomCase1 ();
    void printPolynomCase2 ();
    void printPolynomCase3 ();

//    std::string& operator<< (std::string& output, PolynomHandler::Polynom<Type> rhs);
    void vefDen ();
    void sumPoly ();
    void multPolyPointer ();
    void multPolyMatrix ();
    void simplify ();
    void rootscase1 ();
    void rootscase2 ();
    void rootscase3 ();
    void rootscase4 ();
    void rootscase5 ();
    void rootscase6 ();
    void rootscase7 ();
    void rootscase8 ();
    void rootscase9 ();
    void root2Poly ();
    void rootsContainRoot ();
};

void PolynomDoubleTest::constructorPolynomEscalarDouble ()
{
    PolynomHandler::Polynom<double> A(1.5);
    QBENCHMARK {
        PolynomHandler::Polynom<double> A(1.5);
    }
    QVERIFY2(A.getNumSize() == 1 && A.getDenSize() == 1, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1.5 && A.getDen()(0,0) == 1, "Falhou ao comparar elementos do polinomio com valor Double");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::constructorPolynomMatrixNumeratorDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A("1,2,1");
    QBENCHMARK {
        PolynomHandler::Polynom<double> A("1,2,1");
    }
    QVERIFY2(A.getNumSize() == 3 && A.getDenSize() == 1, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2 && A.getNum()(0,2) == 1 && A.getDen()(0,0) == 1, "Falhou ao comparar elementos do polinomio com valor Double");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::constructorPolynomMatrixNumeratorDoubleCase2 ()
{
    LinAlg::Matrix<double> num = "1,2,1";
    PolynomHandler::Polynom<double> A(num);
    QBENCHMARK {
        PolynomHandler::Polynom<double> A(num);
    }
    QVERIFY2(A.getNumSize() == 3 && A.getDenSize() == 1, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2 && A.getNum()(0,2) == 1 && A.getDen()(0,0) == 1, "Falhou ao comparar elementos do polinomio com valor Double");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::constructorPolynomMatrixNumeratorDoubleCase3 ()
{
    LinAlg::Matrix<int> num = "1,2,1";
    PolynomHandler::Polynom<double> A(num);
    QBENCHMARK {
        PolynomHandler::Polynom<double> A(num);
    }
    QVERIFY2(A.getNumSize() == 3 && A.getDenSize() == 1, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2 && A.getNum()(0,2) == 1 && A.getDen()(0,0) == 1, "Falhou ao comparar elementos do polinomio com valor Double");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::PolynomCopyConstructorDoubleCase1 ()
{
    PolynomHandler::Polynom<double> B("1,2,1");
    PolynomHandler::Polynom<double> A(B);
    QBENCHMARK {
        PolynomHandler::Polynom<double> A(B);
    }
    QVERIFY2(A.getNumSize() == 3 && A.getDenSize() == 1, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2 && A.getNum()(0,2) == 1 && A.getDen()(0,0) == 1, "Falhou ao comparar elementos do polinomio com valor Double");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::PolynomCopyConstructorDoubleCase2 ()
{
    PolynomHandler::Polynom<int> B("1,2,1");
    PolynomHandler::Polynom<double> A(B);
    QBENCHMARK {
        PolynomHandler::Polynom<double> A(B);
    }
    QVERIFY2(A.getNumSize() == 3 && A.getDenSize() == 1, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2 && A.getNum()(0,2) == 1 && A.getDen()(0,0) == 1, "Falhou ao comparar elementos do polinomio com valor Double");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::constructorPolynomMatrixNumeratorDenominatorDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A("1,1","1,2,1");
    QBENCHMARK {
        PolynomHandler::Polynom<double> A("1,1","1,2,1");
    }
    QVERIFY2(A.getNumSize() == 2 && A.getDenSize() == 3, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 1 &&
             A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao comparar elementos do polinomio com valor Double");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::constructorPolynomMatrixNumeratorDenominatorDoubleCase2 ()
{
    LinAlg::Matrix<double> num = "1,1", den = "1,2,1";

    PolynomHandler::Polynom<double> A(num,den);
    QBENCHMARK {
        PolynomHandler::Polynom<double> A(num,den);
    }
    QVERIFY2(A.getNumSize() == 2 && A.getDenSize() == 3, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 1 &&
             A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao comparar elementos do polinomio com valor Double");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::constructorPolynomVoidDouble ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
        PolynomHandler::Polynom<double> A;
    }
    QVERIFY2(A.getNumSize() == 0 && A.getDenSize() == 0, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::destructorPolynomDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A;
    A.~Polynom();
    QBENCHMARK {
        PolynomHandler::Polynom<double> A;
        A.~Polynom();
    }
    QVERIFY2(A.getNumSize() == 0 && A.getDenSize() == 0, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::destructorPolynomDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A("1,1","1,2,1");
    A.~Polynom();
    QBENCHMARK {
        PolynomHandler::Polynom<double> A("1,1","1,2,1");
        A.~Polynom();
    }
    QVERIFY2(A.getNumSize() == 0 && A.getDenSize() == 0, "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(sizeof(A) == sizeof(PolynomHandler::Polynom<double>), "Falhou ao comparar o tipo do elemento do polinômio com valor double");
}

void PolynomDoubleTest::getVarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A(1);
    char x;
    QBENCHMARK {
        x = A.getVar();
    }
    QVERIFY2(x == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::getVarDoubleCase2 ()
{
    LinAlg::Matrix<double> num = "1,1";
    PolynomHandler::Polynom<double> A(num);
    char x;
    QBENCHMARK {
        x = A.getVar();
    }
    QVERIFY2(x == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::getVarDoubleCase3 ()
{
    LinAlg::Matrix<double> num = "1,1", den = "1,2,1";
    PolynomHandler::Polynom<double> A(num,den);
    char x;
    QBENCHMARK {
        x = A.getVar();
    }
    QVERIFY2(x == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::getVarDoubleCase4 ()
{
    PolynomHandler::Polynom<double> A;
    char x;
    QBENCHMARK {
        x = A.getVar();
    }
    QVERIFY2(x == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::changeVarDouble ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
       A.changeVar('s');
    }
    QVERIFY2(A.getVar() == 's', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::getNumSizeDouble ()
{
    LinAlg::Matrix<double> num = "1,1", den = "1,2,1";
    unsigned numSize;
    PolynomHandler::Polynom<double> A(num,den);
    QBENCHMARK {
        numSize = A.getNumSize();
    }
    QVERIFY2(numSize == 2, "Falhou ao testar o tamanho do Polinomio");
}

void PolynomDoubleTest::getDenSizeDouble ()
{
    LinAlg::Matrix<double> num = "1,1", den = "1,2,1";
    unsigned denSize;
    PolynomHandler::Polynom<double> A(num,den);
    QBENCHMARK {
        denSize = A.getDenSize();
    }
    QVERIFY2(denSize == 3, "Falhou ao testar o tamanho do Polinomio");
}

void PolynomDoubleTest::getNumDouble ()
{
    LinAlg::Matrix<double> num = "1,1", den = "1,2,1";
    PolynomHandler::Polynom<double> A(num,den);
    QBENCHMARK {
        num = A.getNum();
    }
    QVERIFY2(num.getNumberOfColumns() == 2, "Falhou ao testar o tamanho do numerador do Polinomio");
    QVERIFY2(num(0,0) == 1 && num(0,1) == 1, "Falhou ao testar os valores do numerador do Polinomio");
}

void PolynomDoubleTest::getDenDouble ()
{
    LinAlg::Matrix<double> num = "1,1", den = "1,2,1";
    PolynomHandler::Polynom<double> A(num,den);
    QBENCHMARK {
        den = A.getDen();
    }
    QVERIFY2(den.getNumberOfColumns() == 3, "Falhou ao testar o tamanho do denominador do Polinomio");
    QVERIFY2(den(0,0) == 1 && den(0,1) == 2 && den(0,2) == 1, "Falhou ao testar os valores do denominador do Polinomio");
}

void PolynomDoubleTest::setNumDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
        A.setNum("1,1");
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2, "Falhou ao testar o tamanho do numerador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 1, "Falhou ao testar os valores do numerador do Polinomio");
}

void PolynomDoubleTest::setNumDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A;
    double *num = new double[2]; num[0] = 1; num[1] = 1;
    QBENCHMARK {
        A.setNum(num,2);
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2, "Falhou ao testar o tamanho do numerador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 1, "Falhou ao testar os valores do numerador do Polinomio");
}

void PolynomDoubleTest::setDenDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
        A.setDen("1,2,1");
    }
    QVERIFY2(A.getDen().getNumberOfColumns() == 3, "Falhou ao testar o tamanho do denominador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
}

void PolynomDoubleTest::setDenDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A;
    double *den = new double[2]; den[0] = 1; den[1] = 2; den[2] = 1;
    QBENCHMARK {
        A.setDen(den,3);
    }
    QVERIFY2(A.getDen().getNumberOfColumns() == 3, "Falhou ao testar o tamanho do denominador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
}

void PolynomDoubleTest::assignOperatorDouble ()
{
    PolynomHandler::Polynom<double> A,B("1,1","1,2,1");
    B.changeVar('s');
    QBENCHMARK {
        A = B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == B.getVar(), "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::copyAssignOperatorDouble ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
        A = PolynomHandler::Polynom<double>("1,1","1,2,1");
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::assignOperatorOtherTypeDouble ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
        A = PolynomHandler::Polynom<int>("1,1","1,2,1");
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumAccumulatorScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A("1","1,1");
    QBENCHMARK {
        A += 0;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumAccumulatorScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A("1","1,1");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A += 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumAccumulatorScalarDoubleCase3 ()
{
    PolynomHandler::Polynom<double> A("1,1","1,1");
    QBENCHMARK {
        A.setNum("1,1");
        A.setDen("1,1");
        A += 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumAccumulatorScalarDoubleCase4 ()
{
    PolynomHandler::Polynom<double> A("1,1","1,2,1");
    QBENCHMARK {
        A.setNum("1,1");
        A.setDen("1,2,1");
        A += 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 3 && A.getNum()(0,2) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumAccumulatorScalarDoubleCase5 ()
{
    PolynomHandler::Polynom<double> A("1","1,1");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A += 1;
        A += 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2 && A.getNum()(0,1) == 3,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumAccumulatorPolynomDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A("1","1,1"), B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A += B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2 && A.getNum()(0,1) == 3,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 3 && A.getDen()(0,2) == 2,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumAccumulatorPolynomDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A("1","1,1"), B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A += B;
        A += B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 3 && A.getNum()(0,1) == 10 && A.getNum()(0,2) == 8,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 5 && A.getDen()(0,2) == 8 && A.getDen()(0,3) == 4,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}




void PolynomDoubleTest::operatorSubtractionAccumulatorScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A("1","1,1");
    QBENCHMARK {
        A -= 0;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionAccumulatorScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A("1","1,1");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A -= 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -1 && A.getNum()(0,1) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionAccumulatorScalarDoubleCase3 ()
{
    PolynomHandler::Polynom<double> A("1,1","1,1");
    QBENCHMARK {
        A.setNum("1,1");
        A.setDen("1,1");
        A -= 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 0 ,
             "Falhou ao testar os valores do numerador do Polinomio");
//    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
//             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionAccumulatorScalarDoubleCase4 ()
{
    PolynomHandler::Polynom<double> A("1,1","1,2,1");
    QBENCHMARK {
        A.setNum("1,1");
        A.setDen("1,2,1");
        A -= 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -1 && A.getNum()(0,1) == -1 && A.getNum()(0,2) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionAccumulatorScalarDoubleCase5 ()
{
    PolynomHandler::Polynom<double> A("1","1,1");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A -= 1;
        A -= 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -2 && A.getNum()(0,1) == -1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionAccumulatorPolynomDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A("1","1,1"), B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A -= B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 3 && A.getDen()(0,2) == 2,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionAccumulatorPolynomDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A("1","1,1"), B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A -= B;
        A -= B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -1 && A.getNum()(0,1) == -2 && A.getNum()(0,2) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 5 && A.getDen()(0,2) == 8 && A.getDen()(0,3) == 4,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorMultiplicationAccumulatorScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A *= 2;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorMultiplicationAccumulatorScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A *= 2;
        A *= 2;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 4,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorMultiplicationAccumulatorPolynomDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A *= B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 3 && A.getDen()(0,2) == 2,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorMultiplicationAccumulatorPolynomDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A, B("1,3","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A *= B;
        A *= B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 6 && A.getNum()(0,2) == 9,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 5 && A.getDen()(0,2) == 8 && A.getDen()(0,3) == 4,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionAccumulatorScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A /= 2;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 0.5,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionAccumulatorScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A;
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A /= 2;
        A /= 2;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 0.25,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionAccumulatorPolynomDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A /= B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionAccumulatorPolynomDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A, B("1,3","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A /= B;
        A /= B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 4 && A.getNum()(0,2) == 4,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 7 && A.getDen()(0,2) == 15 && A.getDen()(0,3) == 9,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionAccumulatorPolynomDoubleCase3 ()
{
    PolynomHandler::Polynom<double> A, B(0.5);
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A /= B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 0.5 && A.getDen()(0,1) == 0.5,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorPotentiationAccumulatorScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A("1,3","1,2");
    QBENCHMARK {
        A.setNum("1,3");
        A.setDen("1,2");
        A ^= 4;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 5 && A.getDen().getNumberOfColumns() == 5,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 12 && A.getNum()(0,2) == 54 && A.getNum()(0,3) == 108 && A.getNum()(0,4) == 81,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 8 && A.getDen()(0,2) == 24 && A.getDen()(0,3) == 32 && A.getDen()(0,4) == 16,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorPotentiationAccumulatorScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A("1,3","1,2");
    QBENCHMARK {
        A.setNum("1,3");
        A.setDen("1,2");
        A ^= -4;
    }
//    std::cout << A << std::endl;
    QVERIFY2(A.getNum().getNumberOfColumns() == 5 && A.getDen().getNumberOfColumns() == 5,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 8 && A.getNum()(0,2) == 24 && A.getNum()(0,3) == 32 && A.getNum()(0,4) == 16,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 12 && A.getDen()(0,2) == 54 && A.getDen()(0,3) == 108 && A.getDen()(0,4) == 81,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorPotentiationAccumulatorScalarDoubleCase3 ()
{
    PolynomHandler::Polynom<double> A("1,3","1,2");
    QBENCHMARK {
        A.setNum("1,3");
        A.setDen("1,2");
        A ^= 0;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 1,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorPotentiationAccumulatorScalarDoubleCase4 ()
{
    PolynomHandler::Polynom<double> A("1,3","1,2");
    QBENCHMARK {
        A.setNum("1,3");
        A.setDen("1,2");
        A ^= 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 3,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::equalityOperator()
{
    PolynomHandler::Polynom<double> A("1,3","1,2");
    bool equal;

    QBENCHMARK {
        equal = A==A;
    }
    QVERIFY2(equal, "Falhou ao testar se os Polinomios sao iguais");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = B + 0;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = B + 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase3 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,1");
    QBENCHMARK {
        A = B + 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase4 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,2,1");
    QBENCHMARK {
        A = B + 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 3 && A.getNum()(0,2) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase5 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,2,1");
    QBENCHMARK {
        A = B + 1;
        A = B + 1;
        A = B + 1;
        A = B + 1;
        A = B + 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 3 && A.getNum()(0,2) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase6 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = 0 + B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase7 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = 1 + B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase8 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,1");
    QBENCHMARK {
        A = 1 + B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase9 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,2,1");
    QBENCHMARK {
        A = 1 + B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 3 && A.getNum()(0,2) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumScalarDoubleCase10 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,2,1");
    QBENCHMARK {
        A = 1 + B;
        A = 1 + B;
        A = 1 + B;
        A = 1 + B;
        A = 1 + B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 3 && A.getNum()(0,2) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}


void PolynomDoubleTest::operatorSumPolynomDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A("1","1,1"), B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A = A + B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2 && A.getNum()(0,1) == 3,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 3 && A.getDen()(0,2) == 2,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSumPolynomDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A("1","1,1"), B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A = A + B;
        A = A + B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 3 && A.getNum()(0,1) == 10 && A.getNum()(0,2) == 8,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 5 && A.getDen()(0,2) == 8 && A.getDen()(0,3) == 4,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

//void PolynomDoubleTest::operatorSumPolynomDoubleCase3 ()
//{
//    PolynomHandler::Polynom<double> A("1","1,1");
//    PolynomHandler::Polynom<int> B("1","1,2");
//    QBENCHMARK {
//        A.setNum("1");
//        A.setDen("1,1");
//        A = A + B;
//        A = A + B;
//    }
//    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
//             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
//    QVERIFY2(A.getNum()(0,0) == 3 && A.getNum()(0,1) == 10 && A.getNum()(0,2) == 8,
//             "Falhou ao testar os valores do numerador do Polinomio");
//    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 5 && A.getDen()(0,2) == 8 && A.getDen()(0,3) == 4,
//             "Falhou ao testar os valores do denominador do Polinomio");
//    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
//}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = B - 0;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = B - 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -1 && A.getNum()(0,1) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase3 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,1");
    QBENCHMARK {
        A = B - 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
//    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
//             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase4 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,2,1");
    QBENCHMARK {
        A = B - 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -1 && A.getNum()(0,1) == -1 && A.getNum()(0,2) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase5 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,2,1");
    QBENCHMARK {
        A = B - 1;
        A = B - 1;
        A = B - 1;
        A = B - 1;
        A = B - 1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -1 && A.getNum()(0,1) == -1 && A.getNum()(0,2) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase6 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = 0 - B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase7 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = 1 - B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase8 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,1");
    QBENCHMARK {
        A = 1 - B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
//    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
//             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase9 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,2,1");
    QBENCHMARK {
        A = 1 - B;
    }
//    std::cout << A << std::endl;
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 1 && A.getNum()(0,2) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionScalarDoubleCase10 ()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,2,1");
    QBENCHMARK {
        A = 1 - B;
        A = 1 - B;
        A = 1 - B;
        A = 1 - B;
        A = 1 - B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 1 && A.getNum()(0,2) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionPolynomDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A("1","1,1"), B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A = A - B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 3 && A.getDen()(0,2) == 2,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorSubtractionPolynomDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A("1","1,1"), B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A = A - B;
        A = A - B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -1 && A.getNum()(0,1) == -2 && A.getNum()(0,2) == 0,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 5 && A.getDen()(0,2) == 8 && A.getDen()(0,3) == 4,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

//void PolynomDoubleTest::operatorSubtractionPolynomDoubleCase3 ()
//{
//    PolynomHandler::Polynom<double> A("1","1,1");
//    PolynomHandler::Polynom<int> B("1","1,2");
//    QBENCHMARK {
//        A.setNum("1");
//        A.setDen("1,1");
//        A = A - B;
//        A = A - B;
//    }
//    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
//             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
//    QVERIFY2(A.getNum()(0,0) == -1 && A.getNum()(0,1) == -2 && A.getNum()(0,2) == 0,
//             "Falhou ao testar os valores do numerador do Polinomio");
//    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 5 && A.getDen()(0,2) == 8 && A.getDen()(0,3) == 4,
//             "Falhou ao testar os valores do denominador do Polinomio");
//    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
//}

void PolynomDoubleTest::operatorMultiplicationScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = B*2;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorMultiplicationScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = B*2;
        A = B*2;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorMultiplicationScalarDoubleCase3 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = 2*B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorMultiplicationScalarDoubleCase4 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = 2*B;
        A = 2*B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorMultiplicationPolynomDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A = A*B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 3 && A.getDen()(0,2) == 2,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorMultiplicationPolynomDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A, B("1,3","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A = A*B;
        A = A*B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 6 && A.getNum()(0,2) == 9,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 5 && A.getDen()(0,2) == 8 && A.getDen()(0,3) == 4,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

//void PolynomDoubleTest::operatorMultiplicationPolynomDoubleCase3 ()
//{
//    PolynomHandler::Polynom<double> A;
//    PolynomHandler::Polynom<int> B("1,3","1,2");
//    QBENCHMARK {
//        A.setNum("1");
//        A.setDen("1,1");
//        A = A*B;
//        A = A*B;
//    }
//    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
//             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
//    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 6 && A.getNum()(0,2) == 9,
//             "Falhou ao testar os valores do numerador do Polinomio");
//    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 5 && A.getDen()(0,2) == 8 && A.getDen()(0,3) == 4,
//             "Falhou ao testar os valores do denominador do Polinomio");
//    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
//}

void PolynomDoubleTest::operatorDivisionScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = B/2;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 0.5,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = B/2;
        A = B/2;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 0.5,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionScalarDoubleCase3 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = 2/B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 1,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionScalarDoubleCase4 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,1");
    QBENCHMARK {
        A = 2/B;
        A = 2/B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 1,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 2 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionPolynomDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A, B("1","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A = A/B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionPolynomDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A, B("1,3","1,2");
    QBENCHMARK {
        A.setNum("1");
        A.setDen("1,1");
        A = A/B;
        A = A/B;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 4 && A.getNum()(0,2) == 4,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 7 && A.getDen()(0,2) == 15 && A.getDen()(0,3) == 9,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

//void PolynomDoubleTest::operatorDivisionPolynomDoubleCase3 ()
//{
//    PolynomHandler::Polynom<double> A;
//    PolynomHandler::Polynom<int> B("1,3","1,2");
//    QBENCHMARK {
//        A.setNum("1");
//        A.setDen("1,1");
//        A = A/B;
//        A = A/B;
//    }
//    QVERIFY2(A.getNum().getNumberOfColumns() == 3 && A.getDen().getNumberOfColumns() == 4,
//             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
//    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 4 && A.getNum()(0,2) == 4,
//             "Falhou ao testar os valores do numerador do Polinomio");
//    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 7 && A.getDen()(0,2) == 15 && A.getDen()(0,3) == 9,
//             "Falhou ao testar os valores do denominador do Polinomio");
//    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
//}

void PolynomDoubleTest::operatorPotentiationScalarDoubleCase1 ()
{
    PolynomHandler::Polynom<double> A, B("1,3","1,2");
    QBENCHMARK {
        A = B^4;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 5 && A.getDen().getNumberOfColumns() == 5,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 12 && A.getNum()(0,2) == 54 && A.getNum()(0,3) == 108 && A.getNum()(0,4) == 81,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 8 && A.getDen()(0,2) == 24 && A.getDen()(0,3) == 32 && A.getDen()(0,4) == 16,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorPotentiationScalarDoubleCase2 ()
{
    PolynomHandler::Polynom<double> A, B("1,3","1,2");
    QBENCHMARK {
        A = B^-4;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 5 && A.getDen().getNumberOfColumns() == 5,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 8 && A.getNum()(0,2) == 24 && A.getNum()(0,3) == 32 && A.getNum()(0,4) == 16,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 12 && A.getDen()(0,2) == 54 && A.getDen()(0,3) == 108 && A.getDen()(0,4) == 81,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorPotentiationScalarDoubleCase3 ()
{
    PolynomHandler::Polynom<double> A, B("1,3","1,2");
    QBENCHMARK {
        A = B^0;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 1,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorPotentiationScalarDoubleCase4 ()
{
    PolynomHandler::Polynom<double> A, B("1,3","1,2");
    QBENCHMARK {
        A = B^1;
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 && A.getNum()(0,1) == 3,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::operatorDivisionMatrixPolynom ()
{
    LinAlg::Matrix< PolynomHandler::Polynom<double> > A(1,1);
    PolynomHandler::Polynom<double> B("1,3","1,2");
    QBENCHMARK {
        A(0,0).setNum("1"); A(0,0).setDen("1,2");
        A = A/B;
    }
    QVERIFY2(A(0,0).getNum().getNumberOfColumns() == 2 && A(0,0).getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A(0,0).getNum()(0,0) == 1 && A(0,0).getNum()(0,1) == 2,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A(0,0).getDen()(0,0) == 1 && A(0,0).getDen()(0,1) == 5 && A(0,0).getDen()(0,2) == 6,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A(0,0).getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::minusOperatorDouble()
{
    PolynomHandler::Polynom<double> A, B("1,1","1,2,1");
    QBENCHMARK {
        A = -B;
    }
//    std::cout << A << std::endl;
    QVERIFY2(A.getNum().getNumberOfColumns() == 2 && A.getDen().getNumberOfColumns() == 3,
             "Falhou ao testar o tamanho dos numerador e denominador do Polinomio");
    QVERIFY2(A.getNum()(0,0) == -1 && A.getNum()(0,1) == -1,
             "Falhou ao testar os valores do numerador do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && A.getDen()(0,1) == 2 && A.getDen()(0,2) == 1,
             "Falhou ao testar os valores do denominador do Polinomio");
    QVERIFY2(A.getVar() == 'x', "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::derivateCase1()
{
    LinAlg::Matrix<double> smallPoly("1,2,1");
    QBENCHMARK {
        PolynomHandler::derivate(smallPoly);
    }
    QVERIFY2(LinAlg::isEqual(PolynomHandler::derivate(smallPoly),LinAlg::Matrix<double>("2,2")), "Falhou ao testar a derivada do Polinomio");
}

void PolynomDoubleTest::derivateCase2()
{
    LinAlg::Matrix<double> smallPoly("5,2,1,6,5,30,1,2,1");
    QBENCHMARK {
        PolynomHandler::derivate(smallPoly);
    }
    QVERIFY2(LinAlg::isEqual(PolynomHandler::derivate(smallPoly),LinAlg::Matrix<double>("40,14,6,30,20,90,2,2")), "Falhou ao testar a derivada do Polinomio");
}

void PolynomDoubleTest::derivateCase3()
{
    LinAlg::Matrix<double> smallPoly("10");
    QBENCHMARK {
        PolynomHandler::derivate(smallPoly);
    }
    QVERIFY2(LinAlg::isEqual(PolynomHandler::derivate(smallPoly),LinAlg::Matrix<double>("0")), "Falhou ao testar a derivada do Polinomio");
}

void PolynomDoubleTest::derivateCase4()
{
    LinAlg::Matrix<double> smallPoly,dif;
    QBENCHMARK {
        dif = PolynomHandler::derivate(smallPoly);
    }
    QVERIFY2(dif.getNumberOfRows() == 0 && dif.getNumberOfColumns() == 0, "Falhou ao testar a derivada do Polinomio");
}

void PolynomDoubleTest::derivateCase5()
{
    PolynomHandler::Polynom<double> p("6,-10,9,8,-5","2,-4,5");
    PolynomHandler::Polynom<double> dp;
    QBENCHMARK {
        dp = PolynomHandler::derivate(p);
    }

    QVERIFY2(LinAlg::isEqual(dp.getNum(),LinAlg::Matrix<double>("24,-92,200,-202,110,20")), "Falhou ao testar a derivada do Polinomio");
    QVERIFY2(LinAlg::isEqual(dp.getDen(),LinAlg::Matrix<double>("4,-16,36,-40,25")), "Falhou ao testar a derivada do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase1()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("0",'x');
    }
    QVERIFY2(A == " ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase2()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1",'x');
    }
    QVERIFY2(A == "  1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase3()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("0,1",'x');
    }
    QVERIFY2(A == "  1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase4()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,0",'x');
    }
    QVERIFY2(A == "x  ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase5()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("2",'x');
    }
    QVERIFY2(A == "  2.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase6()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("2,0",'x');
    }
    QVERIFY2(A == "  2.000x  ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase7()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("2,1",'x');
    }
    QVERIFY2(A == "  2.000x +   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase8()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("-1",'x');
    }
    QVERIFY2(A == "-   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase9()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("-1,0",'x');
    }
    QVERIFY2(A == "- x  ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase10()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("-1,-1",'x');
    }
    QVERIFY2(A == "- x -   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase11()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("-1,1",'x');
    }
    QVERIFY2(A == "- x +   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase12()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,-1",'x');
    }
    QVERIFY2(A == "x -   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase13()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,2,0",'x');
    }
    QVERIFY2(A == "x^2 +   2.000x  ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase14()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,2,-1",'x');
    }
    QVERIFY2(A == "x^2 +   2.000x -   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase15()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,-2,0",'x');
    }
    QVERIFY2(A == "x^2 -   2.000x  ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase16()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("-1,2,0",'x');
    }
    QVERIFY2(A == "- x^2 +   2.000x  ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase17()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,-2,1",'x');
    }
    QVERIFY2(A == "x^2 -   2.000x +   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase18()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("-1,-2,-1",'x');
    }
    QVERIFY2(A == "- x^2 -   2.000x -   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase19()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("-1,2,-1",'x');
    }
    QVERIFY2(A == "- x^2 +   2.000x -   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase20()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,0,0",'x');
    }
    QVERIFY2(A == "x^2   ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase21()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,0,-1",'x');
    }
    QVERIFY2(A == "x^2  -   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase22()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("3,1,0,-1",'x');
    }
    QVERIFY2(A == "  3.000x^3 + x^2  -   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase23()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,0,0,-1",'x');
    }
    QVERIFY2(A == "x^3   -   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase24()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("1,0,-0,-1",'x');
    }
    QVERIFY2(A == "x^3   -   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printSmallPolynomCase25()
{
    std::string A;
    QBENCHMARK {
        A = PolynomHandler::printSmallPolynom<double>("-1,0,0,1",'x');
    }
    QVERIFY2(A == "- x^3   +   1.000 ", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printPolynomCase1()
{
    PolynomHandler::Polynom<double> pol("1,2,1",1.0);
    std::string str; str << pol;

    QBENCHMARK {
        std::string str; str << pol;
    }
    QVERIFY2(str == "   x^2 +   2.000x +   1.000    \n", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printPolynomCase2()
{
    PolynomHandler::Polynom<double> pol("1,2,1",2.0);
    std::string str; str << pol;

    QBENCHMARK {
        std::string str; str << pol;
    }
    QVERIFY2(str == "   x^2 +   2.000x +   1.000    \n-------------------------------\n             2.000            \n", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::printPolynomCase3()
{
    PolynomHandler::Polynom<double> pol("1,2,1",0.0);
    std::string str; str << pol;

    QBENCHMARK {
        std::string str; str << pol;
    }
    QVERIFY2(str == "Polinomio tem denominador zero!!", "Falhou ao testar variável do Polinomio");
}

void PolynomDoubleTest::vefDen ()
{
    bool A;
    double *den1 = new double[3], *den2 = new double[3];
    den1[0] = 1;den1[1] = 2;den1[2] = 1;
    den2[0] = 1;den2[1] = 2;den2[2] = 1;
    unsigned sizeDen1 = 3, sizeDen2 = 3;
    QBENCHMARK {
        A = PolynomHandler::VefDen(den1,den2,sizeDen1,sizeDen2);
    }
    QVERIFY2(A == 1, "Falhou ao testar o denominador do Polinomio");
}

void PolynomDoubleTest::sumPoly ()
{
    double *A;
    double *den1 = new double[3], *den2 = new double[3];
    den1[0] = 1;den1[1] = 2;den1[2] = 1;
    den2[0] = 1;den2[1] = 2;den2[2] = 1;
    unsigned sizeDen1 = 3, sizeDen2 = 3;
    QBENCHMARK {
        A = PolynomHandler::SumPoly(den1,den2,sizeDen1,sizeDen2);
    }
    QVERIFY2(A[0] == 2 && A[1] == 4 && A[2] == 2, "Falhou ao testar a soma dos Polinomios");
}

void PolynomDoubleTest::multPolyMatrix ()
{
    LinAlg::Matrix<double> A, B("1,2,1");
    QBENCHMARK {
        A = PolynomHandler::MultPoly(B,B);
    }
    QVERIFY2(A(0,0) == 1 && A(0,1) == 4 && A(0,2) == 6 && A(0,3) == 4 && A(0,4) == 1, "Falhou ao testar a multiplicação dos Polinomios");
}

void PolynomDoubleTest::multPolyPointer ()
{
    double *A;
    double *den1 = new double[3], *den2 = new double[3];
    den1[0] = 1;den1[1] = 2;den1[2] = 1;
    den2[0] = 1;den2[1] = 2;den2[2] = 1;
    unsigned sizeDen1 = 3, sizeDen2 = 3;
    QBENCHMARK {
        A = PolynomHandler::MultPoly(den1,den2,sizeDen1,sizeDen2);
    }
    QVERIFY2(A[0] == 1 && A[1] == 4 && A[2] == 6 && A[3] == 4 && A[4] == 1, "Falhou ao testar o denominador do Polinomio");
}

void PolynomDoubleTest::simplify ()
{
    PolynomHandler::Polynom<double> A,B("1,15,85,225,274,120","1,16,100,310,499,394,120");
    QBENCHMARK {
        A = PolynomHandler::simplify<double>(B);
    }
    QVERIFY2(A.getNum().getNumberOfColumns() == 1 && A.getDen().getNumberOfColumns() == 2,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A.getNum()(0,0) == 1 ,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(A.getDen()(0,0) == 1 && fabs(A.getDen()(0,1)-1) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
}

void PolynomDoubleTest::rootscase1()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = PolynomHandler::rootsNewtonBairstow<double>("1,-2,4,-4,4");
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 4,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A(0,0) == 1 && A(1,0) == 1 && A(2,0) == 0 && A(3,0) == 0,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(A(0,1) == 1 && A(1,1) == -1 && A(2,1) == sqrt(2) && A(3,1) == -sqrt(2),
             "Falhou ao testar os valores do Polinomio");
}
void PolynomDoubleTest::rootscase2()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = PolynomHandler::rootsNewtonBairstow<double>("1,11,41,61,30");
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 4,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2 (fabs(A(0,0) - (-1)) <= 0.0001 && fabs(A(1,0) - (-5)) <=0.0001 && fabs(A(2,0) - (-2)) <= 0.0001 && fabs(A(3,0) - (-3))<=0.0001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(A(0,1) == 0 && A(1,1) == 0 && A(2,1) == 0 && A(3,1) == 0,
             "Falhou ao testar os valores do Polinomio");
}
void PolynomDoubleTest::rootscase3()
{
    LinAlg::Matrix<long double> A;
    QBENCHMARK {
        A = PolynomHandler::rootsNewtonBairstow<long double>("1,15,92,296,528,496,192",1e-35);
    }
//        std::cout<<A<<std::endl;
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 6,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(fabs(A(0,0) + (2)) <= 0.001 && fabs(A(0,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(1,0) + (4)) <= 0.001 && fabs(A(1,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(2,0) + (2)) <= 0.001 && fabs(A(2,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(3,0) + (3)) <= 0.001 && fabs(A(3,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(4,0) + (2)) <= 0.001 && fabs(A(4,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(5,0) + (2)) <= 0.001 && fabs(A(5,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
}
void PolynomDoubleTest::rootscase4()
{
    LinAlg::Matrix<long double> A;
    QBENCHMARK {
        A = PolynomHandler::rootsNewtonBairstow<long double>("1,15,85,237,346,252,72",1e-35);
    }
//    std::cout << A << std::endl;
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 6,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(fabs(A(0,0) + (1)) <= 0.001 && fabs(A(0,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(1,0) + (6)) <= 0.001 && fabs(A(1,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(2,0) + (1)) <= 0.001 && fabs(A(2,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(3,0) + (3)) <= 0.001 && fabs(A(3,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(4,0) + (2)) <= 0.001 && fabs(A(4,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(5,0) + (2)) <= 0.001 && fabs(A(5,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
}
void PolynomDoubleTest::rootscase5()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = PolynomHandler::rootsNewtonBairstow<double>(" 1,18,130,480,949,942,360");
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 6,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(fabs(A(0,0) - (-1)) <= 0.0001 && fabs(A(1,0) - (-5)) <= 0.0001 && fabs(A(2,0) - (-2)) <= 0.0001 && fabs(A(3,0) - (-4)) <= 0.0001 && fabs(A(4,0) - (-3)) <= 0.0001 && fabs(A(5,0) - (-3)) <= 0.0001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(A(0,1) == 0 && A(1,1) == 0 && A(2,1) == 0 && A(3,1) == 0,
             "Falhou ao testar os valores do Polinomio");
}
void PolynomDoubleTest::rootscase6()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = PolynomHandler::rootsNewtonBairstow<double>("1,7,19,27,20,6");
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 5,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(fabs(A(0,0) + 1) <= 0.001 && fabs(A(1,0) + 1) <= 0.001 && fabs(A(2,0) + 1) <= 0.001 && fabs(A(3,0) + 1) <= 0.001 && fabs(A(4,0) + 3) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(0,1)) <= 0.001 && fabs(A(1,1)) <= 0.001 && fabs(A(2,1)-1) <= 0.001 && fabs(A(3,1) + 1) <= 0.001 && fabs(A(4,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
}
void PolynomDoubleTest::rootscase7()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = PolynomHandler::rootsNewtonBairstow<double>("1,14,66,104,80");
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 4,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(fabs(A(0,0) +1) <= 0.001 && fabs(A(1,0) +1) <= 0.001 && fabs(A(2,0) + 6) <= 0.001 && fabs(A(3,0) + 6) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(0,1) - 1) <= 0.001 && fabs(A(1,1) + 1) <= 0.001 && fabs(A(2,1) - 2) <= 0.001 && fabs(A(3,1) + 2) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
}
void PolynomDoubleTest::rootscase8()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = PolynomHandler::rootsNewtonBairstow<double>("1,2,2");
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 2,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A(0,0) == -1 && A(1,0) == -1,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(0,1) - (1)) <= 0.001 && fabs(A(1,1) + 1) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
}

void PolynomDoubleTest::rootscase9()
{
    LinAlg::Matrix<long double> A;
    QBENCHMARK {
        A = PolynomHandler::rootsNewtonBairstow<long double>("1,6,15,20,15,6,1", 1e-35);
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 6,
             "Falhou ao testar o tamanho do Polinomio");
//    std::cout << A;
    QVERIFY2(fabs(A(0,0) + (1)) <= 0.001 && fabs(A(0,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(1,0) + (1)) <= 0.001 && fabs(A(1,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(2,0) + (1)) <= 0.001 && fabs(A(2,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(3,0) + (1)) <= 0.001 && fabs(A(3,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(4,0) + (1)) <= 0.001 && fabs(A(4,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
    QVERIFY2(fabs(A(5,0) + (1)) <= 0.001 && fabs(A(5,1)) <= 0.001,
             "Falhou ao testar os valores do Polinomio");
}

void PolynomDoubleTest::root2Poly ()
{
    LinAlg::Matrix<double> B,A;
    B = PolynomHandler::rootsNewtonBairstow<double>("1,-2,4,-4,4");
    QBENCHMARK {
        A = PolynomHandler::Root2Poly(B);
    }
    QVERIFY2(A.getNumberOfColumns() == 5 && A.getNumberOfRows() == 1,
             "Falhou ao testar o tamanho do Polinomio");
    QVERIFY2(A(0,0) - 1 <= 0.001 && A(0,1)- (-2) <= 0.001 && A(0,2) - 4 <= 0.001 && A(0,3) - (-4) <= 0.001 && A(0,4) - 4 <= 0.001,
             "Falhou ao testar os valores do Polinomio");
}

void PolynomDoubleTest::rootsContainRoot ()
{
    LinAlg::Matrix<double> B;
    double C = 1.0; bool A;
    B = PolynomHandler::rootsNewtonBairstow<double>("1,-2,4,-4,4");
    QBENCHMARK {
        A = PolynomHandler::rootsContainRoot(C,B);
    }
    QVERIFY2(A, "Falhou ao testar o tamanho do Polinomio");
}

QTEST_APPLESS_MAIN(PolynomDoubleTest)
#include "tst_polynomdoubletest.moc"
