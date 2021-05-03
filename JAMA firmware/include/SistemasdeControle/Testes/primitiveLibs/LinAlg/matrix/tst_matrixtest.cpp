#include <QString>
#include <QtTest>
#define testMatrix
#include "../../../../headers/primitiveLibs/LinAlg/matrix.h"

class MatrixTest : public QObject
{
    Q_OBJECT

public:
    MatrixTest(){}

private Q_SLOTS:
    void constructorMatrixTypeInt();
    void constructorMatrixTypeChar();
    void constructorMatrixTypeShort();
    void constructorMatrixTypeFloat();
    void constructorMatrixTypeLongDouble ();

    //Testes utilizando o tipo Double
    void constructorMatrixTypeDouble ();
    void constructorMatrixTypeCStringAndDouble ();
    void constructorMatrixTypeStringAndDouble ();
    void constructorSizedVoidMatrixDouble ();
    void constructorNULLMatrixDouble ();
    void copyconstructorDouble ();
    void copyconstructorOtherTypeDoubleAndInt ();
    void destructorDouble ();
    void removeRowDoubleFirstTest ();
    void removeRowDoubleSecondTest ();
    void removeRowDoubleThirdTest ();
    void removeColumnDoubleFirstTest ();
    void removeColumnDoubleSecondTest ();
    void removeColumnDoubleThirdTest ();
    void getNumberOfRowsDouble ();
    void getNumberOfColumnsDouble ();
    void getRowDouble ();
    void getColumnDouble ();
    void swapRowsDouble ();
    void swapColumnsDouble ();
    void lengthDouble ();
    void sizeDouble ();
    void isNullDouble ();
    void isSquareDouble ();
    void operatorParenthesisInputTwoUnsignedDouble ();
    void operatorParenthesisInputTwoUnsignedOutputConstDouble ();
    void operatorParenthesisInputFromToAndUnsignedDouble ();
    void operatorParenthesisInputUnsignedAndFromToDouble ();
    void operatorParenthesisInputFromToAndFromToDouble ();
    void operatorParenthesisInputFromToAndMatrixDouble ();
    void operatorParenthesisInputMatrixAndFromToDouble ();
    void operatorParenthesisInputUnsignedAndMatrixDouble ();
    void operatorParenthesisInputMatrixAndUnsignedDouble ();
    void operatorParenthesisInputMatrixAndMatrixDouble ();
    void operatorParenthesisInputFromToAndUnsignedInvertedAccessDouble ();
    void operatorParenthesisInputUnsignedAndFromToInvertedAccessDouble ();
    void operatorParenthesisInputFromToAndFromToInvertedAccessDouble ();
    void operatorParenthesisInputFromToAndMatrixInvertedAccessDouble ();
    void operatorParenthesisInputMatrixAndFromToInvertedAccessDouble ();
    void operatorParenthesisInputUnsignedAndMatrixInvertedAccessDouble ();
    void operatorParenthesisInputMatrixAndUnsignedInvertedAccessDouble ();
    void operatorParenthesisInputMatrixAndMatrixInvertedAccessDouble ();
    void operatorAtributionMatrixPointerDouble ();
    void operatorAtributionMatrixMoreThanTwoParametersPointerDouble ();
    void operatorAtributionDoubleReturningVoid ();
    void operatorAtributionDoubleReturningDouble ();
    void operatorAtributionDoubleReturningInt ();
    void operatorAtributionDoubleReturningShort ();
    void operatorAtributionDoubleReturningLongInt ();
    void operatorAtributionDoubleReturningLongFloat ();
    void operatorSumAccumulatorScalarDouble ();
    void operatorSumAccumulatorMatrixDouble ();
    void operatorSubtractionAccumulatorScalarDouble ();
    void operatorSubtractionAccumulatorMatrixDouble ();
    void operatorMultiplicationAccumulatorScalarDouble ();
    void operatorMultiplicationAccumulatorMatrixDouble ();
    void operatorDivisionAccumulatorScalarDouble ();
    void operatorDivisionAccumulatorMatrixDouble ();
    void operatorPotentiationAccumulatorScalarDouble ();
    void operatorEqualDouble ();
    void operatorLessEqualThanDouble ();
    void operatorGreaterEqualThanDouble ();
    void operatorLessThanDouble ();
    void operatorGreaterThanDouble ();
    void horizontalConcatenationOperatorScalarDouble ();
    void horizontalConcatenationOperatorMatrixDouble ();
    void verticalConcatenationOperatorScalarDouble ();
    void verticalConcatenationOperatorMatrixDouble ();
    void bufferOperatorDoubleCase1 ();
    void bufferOperatorDoubleCase2 ();
    void bufferOperatorDoubleCase3 ();
    void bufferOperatorDoubleCase4 ();
    void bufferOperatorDoubleCase5 ();
    void bufferOperatorDoubleCase6 ();
    void bufferOperatorDoubleCase7 ();
    void bufferOperatorDoubleCase8 ();
    void bufferOperatorDoubleCase9 ();
    void bufferOperatorDoubleCase10 ();
    void swapTwoMatrixDouble();
    void swapTwoMatrixFriendDouble();
    void operatorSumMatrixScalarDouble ();
    void operatorSumScalarMatrixDouble ();
    void operatorSumMatrixMatrixDouble ();
    void operatorSubtractionMatrixScalarDouble ();
    void operatorSubtractionScalarMatrixDouble ();
    void operatorSubtractionMatrixMatrixDouble ();
    void operatorMultiplicationMatrixScalarDouble ();
    void operatorMultiplicationScalarMatrixDouble ();
    void operatorMultiplicationMatrixMatrixDouble ();
    void operatorDivisionMatrixScalarDouble ();
    void operatorDivisionMatrixMatrixDouble ();
    void operatorNegativeMatrixDouble ();
    void operatorTransposeMatrixDouble();
    void operatorPotentiationScalarDouble ();
    void zerosMatrixDouble ();
    void identityMatrixDouble ();
    void onesMatrixDouble ();
    void LineVector ();
    void Random ();
    void Determinant ();
//    void Cofactor ();
    void Inverse ();
    void operatorBufferStringShow ();
    void operatorBufferStringBack ();
    void sort ();
    void min ();
    void max ();
    void sum ();

    //    LinAlg::Matrix<Type> divPoint(const LinAlg::Matrix<Type> &A, const LinAlg::Matrix<Type> &B);
//    bool operator== (const LinAlg::Matrix<Type>& lhs, const LinAlg::Matrix<Type>& rhs);
//    bool operator!= (const LinAlg::Matrix<Type>& lhs, const LinAlg::Matrix<Type>& rhs);
};

void MatrixTest::constructorMatrixTypeChar()
{
    QBENCHMARK {
        LinAlg::Matrix<char> A('a');
    }
    LinAlg::Matrix<char> A('a');
    QVERIFY2(A.getNumberOfColumns() == 1 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 'a', "Falhou ao comparar o elemento da matriz com valor char");
    QVERIFY2(sizeof(A(0,0)) == sizeof(char), "Falhou ao comparar o tipo do elemento da matriz com valor char");
}

void MatrixTest::constructorMatrixTypeShort()
{
    QBENCHMARK {
        LinAlg::Matrix<short> A(1);
    }
    LinAlg::Matrix<short> A(1);
    QVERIFY2(A.getNumberOfColumns() == 1 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1, "Falhou ao comparar o elemento da matriz com valor short");
    QVERIFY2(sizeof(A(0,0)) == sizeof(short), "Falhou ao comparar o tipo do elemento da matriz com valor short");
}

void MatrixTest::constructorMatrixTypeInt()
{
    QBENCHMARK {
        LinAlg::Matrix<int> A(1);
    }
    LinAlg::Matrix<int> A(1);
    QVERIFY2(A.getNumberOfColumns() == 1 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1, "Falhou ao comparar o elemento da matriz com valor inteiro");
    QVERIFY2(sizeof(A(0,0)) == sizeof(int), "Falhou ao comparar o tipo do elemento da matriz com valor inteiro");
}

void MatrixTest::constructorMatrixTypeFloat()
{
    QBENCHMARK {
        LinAlg::Matrix<float> A(1.5);
    }
    LinAlg::Matrix<float> A(1.5);
    QVERIFY2(A.getNumberOfColumns() == 1 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1.5, "Falhou ao comparar o elemento da matriz com valor float");
    QVERIFY2(sizeof(A(0,0)) == sizeof(float), "Falhou ao comparar o tipo do elemento da matriz com valor float");
}

void MatrixTest::constructorMatrixTypeDouble()
{
    QBENCHMARK {
        LinAlg::Matrix<double> A(1.1);
    }
    LinAlg::Matrix<double> A(1.1);
    QVERIFY2(A.getNumberOfColumns() == 1 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1.1, "Falhou ao comparar o elemento da matriz com valor double");
    QVERIFY2(sizeof(A(0,0)) == sizeof(double), "Falhou ao comparar o tipo do elemento da matriz com valor double");
}

void MatrixTest::constructorMatrixTypeLongDouble()
{
    QBENCHMARK {
        LinAlg::Matrix<long double> A(1.1);
    }
    LinAlg::Matrix<long double> A(1.1);
    QVERIFY2(A.getNumberOfColumns() == 1 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1.1, "Falhou ao comparar o elemento da matriz com valor long double");
    QVERIFY2(sizeof(A(0,0)) == sizeof(long double), "Falhou ao comparar o tipo do elemento da matriz com valor long double");
}

void MatrixTest::constructorMatrixTypeCStringAndDouble()
{
    QBENCHMARK {
        LinAlg::Matrix<double> A("1,2,3,4;5,6,7,8");
    }
    LinAlg::Matrix<double> A("1,2,3,4;5,6,7,8");
    QVERIFY2(A.getNumberOfColumns() == 4 && A.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1.0 && A(0,1) == 2.0 && A(0,2) == 3.0 && A(0,3) == 4.0 &&
             A(1,0) == 5.0 && A(1,1) == 6.0 && A(1,2) == 7.0 && A(1,3) == 8.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::constructorMatrixTypeStringAndDouble()
{
    std::string str = "1,2,3,4;5,6,7,8";
    QBENCHMARK {
        LinAlg::Matrix<double> A(str);
    }
    LinAlg::Matrix<double> A(str);
    QVERIFY2(A.getNumberOfColumns() == 4 && A.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1.0 && A(0,1) == 2.0 && A(0,2) == 3.0 && A(0,3) == 4.0 &&
             A(1,0) == 5.0 && A(1,1) == 6.0 && A(1,2) == 7.0 && A(1,3) == 8.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::constructorSizedVoidMatrixDouble()
{
    QBENCHMARK {
        LinAlg::Matrix<double> A(3,3);
    }
    LinAlg::Matrix<double> A(3,3);
    QVERIFY2(A.getNumberOfColumns() == 3 && A.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 0.0 && A(0,1) == 0.0 && A(0,2) == 0.0 &&
             A(1,0) == 0.0 && A(1,1) == 0.0 && A(1,2) == 0.0 &&
             A(2,0) == 0.0 && A(2,1) == 0.0 && A(2,2) == 0.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::constructorNULLMatrixDouble()
{
    QBENCHMARK {
        LinAlg::Matrix<double> A;
    }
    LinAlg::Matrix<double> A;
    QVERIFY2(A.getNumberOfColumns() == 0 && A.getNumberOfRows() == 0, "Falhou ao testar o tamanho da matriz");
}

void MatrixTest::copyconstructorDouble()
{
    LinAlg::Matrix<double> A = "1,2;3,4";
    QBENCHMARK {
        LinAlg::Matrix<double> B(A);
    }
    LinAlg::Matrix<double> B(A);
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1.0 && B(0,1) == 2.0 &&
             B(1,0) == 3.0 && B(1,1) == 4.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::copyconstructorOtherTypeDoubleAndInt()
{
    LinAlg::Matrix<int> A = "1,2;3,4";
    QBENCHMARK {
        LinAlg::Matrix<double> B(A);
    }
    LinAlg::Matrix<double> B(A);
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1.0 && B(0,1) == 2.0 &&
             B(1,0) == 3.0 && B(1,1) == 4.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::destructorDouble()
{
    LinAlg::Matrix<int> A = "1,2;3,4";
    QBENCHMARK {
        A.~Matrix();
    }
    QVERIFY2(A.getNumberOfColumns() == 0 && A.getNumberOfRows() == 0, "Falhou ao testar o tamanho da matriz");
}

void MatrixTest::removeRowDoubleFirstTest()
{
    std::string str = "1,2,3,4";
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = str.c_str();
        A.removeRow(1);
    }
    QVERIFY2(A.getNumberOfColumns() == 0 && A.getNumberOfRows() == 0, "Falhou ao testar o tamanho da matriz");
}

void MatrixTest::removeRowDoubleSecondTest()
{
    std::string str = "1,2,3,4;5,6,7,8";
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = str.c_str();
        A.removeRow(0);
    }
    QVERIFY2(A.getNumberOfColumns() == 4 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 5.0 && A(0,1) == 6.0 && A(0,2) == 7.0 && A(0,3) == 8.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::removeRowDoubleThirdTest()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = str.c_str();
        A.removeRow(1);
    }
    QVERIFY2(A.getNumberOfColumns() == 4 && A.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1.0 && A(0,1) == 2.0 && A(0,2) == 3.0 && A(0,3) == 4.0 &&
             A(1,0) == 9.0 && A(1,1) == 10.0 && A(1,2) == 11.0 && A(1,3) == 12.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::removeColumnDoubleFirstTest()
{
    std::string str = "1;2;3;4";
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = str.c_str();
        A.removeColumn(0);
    }
    QVERIFY2(A.getNumberOfColumns() == 0 && A.getNumberOfRows() == 0, "Falhou ao testar o tamanho da matriz");
}

void MatrixTest::removeColumnDoubleSecondTest()
{
    std::string str = "1,5;2,6;3,7;4,8";
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = str.c_str();
        A.removeColumn(0);
    }
    QVERIFY2(A.getNumberOfColumns() == 1 && A.getNumberOfRows() == 4, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 5.0 && A(1,0) == 6.0 && A(2,0) == 7.0 && A(3,0) == 8.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::removeColumnDoubleThirdTest()
{
    std::string str = "1,5,9;2,6,10;3,7,11;4,8,12";
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = str.c_str();
        A.removeColumn(1);
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 4, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1.0 && A(1,0) == 2.0 && A(2,0) == 3.0 && A(3,0) == 4.0 &&
             A(0,1) == 9.0 && A(1,1) == 10.0 && A(2,1) == 11.0 && A(3,1) == 12.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::getNumberOfRowsDouble()
{
    std::string str = "1;2;3;4;5;6;7;8;9;0";
    LinAlg::Matrix<double> A;
    A = str.c_str();
    QBENCHMARK {
        A.getNumberOfRows();
    }
    QVERIFY2(A.getNumberOfColumns() == 1 && A.getNumberOfRows() == 10, "Falhou ao testar o tamanho da matriz");
}

void MatrixTest::getNumberOfColumnsDouble()
{
    std::string str = "1,2,3,4,5,6,7,8,9,0";
    LinAlg::Matrix<double> A;
    A = str.c_str();
    QBENCHMARK {
        A.getNumberOfColumns();
    }
    QVERIFY2(A.getNumberOfColumns() == 10 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
}

void MatrixTest::getRowDouble()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A,B;
    A = str.c_str();
    QBENCHMARK {
        B = A.getRow(0);
    }
    QVERIFY2(B.getNumberOfColumns() == 4 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1.0 && B(0,1) == 2.0 && B(0,2) == 3.0 && B(0,3) == 4.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::getColumnDouble()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A,B;
    A = str.c_str();
    QBENCHMARK {
        B = A.getColumn(0);
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1.0 && B(1,0) == 5.0 && B(2,0) == 9.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::swapRowsDouble()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = str.c_str();
        A.swapRows(0,1);
    }
    QVERIFY2(A.getNumberOfColumns() == 4 && A.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 5.0 && A(0,1) == 6.0 && A(0,2) == 7.0 && A(0,3) == 8.0 &&
             A(1,0) == 1.0 && A(1,1) == 2.0 && A(1,2) == 3.0 && A(1,3) == 4.0 &&
             A(2,0) == 9.0 && A(2,1) == 10.0 && A(2,2) == 11.0 && A(2,3) == 12.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::swapColumnsDouble()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = str.c_str();
        A.swapColumns(0,1);
    }
    QVERIFY2(A.getNumberOfColumns() == 4 && A.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 2.0 && A(0,1) == 1.0 && A(0,2) == 3.0 && A(0,3) == 4.0 &&
             A(1,0) == 6.0 && A(1,1) == 5.0 && A(1,2) == 7.0 && A(1,3) == 8.0 &&
             A(2,0) == 10.0 && A(2,1) == 9.0 && A(2,2) == 11.0 && A(2,3) == 12.0
             , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::lengthDouble()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str;
    QBENCHMARK {
        A.length();
    }
    QVERIFY2(A.getNumberOfColumns() == 4 && A.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A.length() == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::sizeDouble()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A.size();
    }
    QVERIFY2(A.getNumberOfColumns() == 4 && A.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 3 && B(0,1) == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::isNullDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        A.isNull();
        B.isNull();
    }
    QVERIFY2(B.isNull(), "Matriz deveria ser vazia");
    QVERIFY2(!A.isNull(), "Matriz não deveria ser vazia");
}

void MatrixTest::isSquareDouble ()
{
    LinAlg::Matrix<double> A = LinAlg::Zeros<double>(1,5), B = LinAlg::Zeros<double>(5,5);
    QBENCHMARK {
        A.isSquare();
        B.isSquare();
    }
    QVERIFY2(B.isSquare(), "Matriz deveria ser quadrada");
    QVERIFY2(!A.isSquare(), "Matriz não deveria ser quadrada");
}

void MatrixTest::operatorParenthesisInputTwoUnsignedDouble ()
{
    LinAlg::Matrix<double> A = LinAlg::Zeros<double>(1,5);
    QBENCHMARK {
        A(0,0) = 2.0;
    }
    A(0,0) = 2.0;
    QVERIFY2(A(0,0) == 2.0, "Atribuição não realizada com sucesso");
}

void MatrixTest::operatorParenthesisInputTwoUnsignedOutputConstDouble ()
{
    LinAlg::Matrix<double> A = LinAlg::Zeros<double>(1,5);
    bool flag;
    QBENCHMARK {
        flag = (A(0,0) == 0.0);
    }
    QVERIFY2(flag, "Acesso ao elemento da matriz não realizado com sucesso");
}

void MatrixTest::operatorParenthesisInputFromToAndUnsignedDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(from(1)-->2,1);
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 6 && B(1,0) == 10, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputUnsignedAndFromToDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(1,from(1)-->2);
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 6 && B(0,1) == 7, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputFromToAndFromToDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(from(1)-->2,from(1)-->2);
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 6 && B(1,0) == 10 && B(0,1) == 7 && B(1,1) == 11, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputFromToAndMatrixDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(from(1)-->2,"1,2");
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 6 && B(1,0) == 10 && B(0,1) == 7 && B(1,1) == 11, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputMatrixAndFromToDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A("1,2",from(1)-->2);
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 6 && B(1,0) == 10 && B(0,1) == 7 && B(1,1) == 11, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputUnsignedAndMatrixDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(1,"1,2");
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 6 && B(0,1) == 7, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputMatrixAndUnsignedDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A("1,2",1);
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 6 && B(1,0) == 10, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputMatrixAndMatrixDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A("1,2","1,2");
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 6 && B(1,0) == 10 && B(0,1) == 7 && B(1,1) == 11, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputFromToAndUnsignedInvertedAccessDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(from(2)-->1,1);
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 10 && B(1,0) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputUnsignedAndFromToInvertedAccessDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(1,from(2)-->1);
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 7 && B(0,1) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputFromToAndFromToInvertedAccessDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(from(2)-->1,from(2)-->1);
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 11 && B(1,0) == 7 && B(0,1) == 10 && B(1,1) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputFromToAndMatrixInvertedAccessDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(from(2)-->1,"2,1");
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 11 && B(1,0) == 7 && B(0,1) == 10 && B(1,1) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputMatrixAndFromToInvertedAccessDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A("2,1",from(2)-->1);
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 11 && B(1,0) == 7 && B(0,1) == 10 && B(1,1) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputUnsignedAndMatrixInvertedAccessDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A(1,"2,1");
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 7 && B(0,1) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputMatrixAndUnsignedInvertedAccessDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A("2,1",1);
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 10 && B(1,0) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorParenthesisInputMatrixAndMatrixInvertedAccessDouble ()
{
    std::string str = "1,2,3,4;5,6,7,8;9,10,11,12";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A("2,1","2,1");
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 11 && B(1,0) == 7 && B(0,1) == 10 && B(1,1) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorAtributionMatrixPointerDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", B = "1,2,3,4", C, D;
    QBENCHMARK {
        *(C,D) = (A,B);
    }
    QVERIFY2(C.getNumberOfColumns() == 2 && C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == A(0,0) && C(0,1) == A(0,1) &&
             C(1,0) == A(1,0) && C(1,1) == A(1,1), "Falhou ao comparar todos os elementos da matriz com valor double");
    QVERIFY2(&C != &A, "Falhou ao comparar os endereços da matriz com valor double");

    QVERIFY2(D.getNumberOfColumns() == 4 && D.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(D(0,0) == B(0,0) && D(0,1) == B(0,1) &&
             D(0,2) == B(0,2) && D(0,3) == B(0,3), "Falhou ao comparar todos os elementos da matriz com valor double");
    QVERIFY2(&D != &B, "Falhou ao comparar os endereços da matriz com valor double");
}

void MatrixTest::operatorAtributionMatrixMoreThanTwoParametersPointerDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", B = "1,2,3,4", C = "1,2", D, E, F;
    QBENCHMARK {
        *(D,E,F) = (A,B,C);
    }
    QVERIFY2(D.getNumberOfColumns() == 2 && D.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(D(0,0) == A(0,0) && D(0,1) == A(0,1) &&
             D(1,0) == A(1,0) && D(1,1) == A(1,1), "Falhou ao comparar todos os elementos da matriz com valor double");
    QVERIFY2(&D != &A, "Falhou ao comparar os endereços da matriz com valor double");

    QVERIFY2(E.getNumberOfColumns() == 4 && E.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(E(0,0) == B(0,0) && E(0,1) == B(0,1) &&
             E(0,2) == B(0,2) && E(0,3) == B(0,3), "Falhou ao comparar todos os elementos da matriz com valor double");
    QVERIFY2(&E != &B, "Falhou ao comparar os endereços da matriz com valor double");

    QVERIFY2(F.getNumberOfColumns() == 2 && F.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(F(0,0) == C(0,0) && F(0,1) == C(0,1), "Falhou ao comparar todos os elementos da matriz com valor double");
    QVERIFY2(&F != &C, "Falhou ao comparar os endereços da matriz com valor double");
}

void MatrixTest::operatorAtributionDoubleReturningVoid ()
{
    LinAlg::Matrix<double> B;
    QBENCHMARK {
        B = "3,2";
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 3 && B(0,1) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorAtributionDoubleReturningDouble ()
{
    std::string str = "1,2;3,4";
    LinAlg::Matrix<double> A = str,B;
    QBENCHMARK {
        B = A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 3 && B(0,1) == 2 && B(1,1) == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorAtributionDoubleReturningInt ()
{
    std::string str = "1,2;3,4";
    LinAlg::Matrix<double> A = str;
    LinAlg::Matrix<int> B;
    QBENCHMARK {
        B = A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 3 && B(0,1) == 2 && B(1,1) == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorAtributionDoubleReturningShort ()
{
    std::string str = "1,2;3,4";
    LinAlg::Matrix<double> A = str;
    LinAlg::Matrix<short> B;
    QBENCHMARK {
        B = A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 3 && B(0,1) == 2 && B(1,1) == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorAtributionDoubleReturningLongInt ()
{
    std::string str = "1,2;3,4";
    LinAlg::Matrix<double> A = str;
    LinAlg::Matrix<long int> B;
    QBENCHMARK {
        B = A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 3 && B(0,1) == 2 && B(1,1) == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorAtributionDoubleReturningLongFloat ()
{
    std::string str = "1,2;3,4";
    LinAlg::Matrix<double> A = str;
    LinAlg::Matrix<float> B;
    QBENCHMARK {
        B = A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 3 && B(0,1) == 2 && B(1,1) == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}




void MatrixTest::operatorSumAccumulatorScalarDouble ()
{
    LinAlg::Matrix<double> B = LinAlg::Zeros<double>(2,2);
    QBENCHMARK {
        B = LinAlg::Zeros<double>(2,2);
        B += 1;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 1 && B(0,1) == 1 && B(1,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorSumAccumulatorMatrixDouble ()
{
    LinAlg::Matrix<double> B = LinAlg::Zeros<double>(2,2), A = LinAlg::Ones<double>(2,2);
    QBENCHMARK {
        B = LinAlg::Zeros<double>(2,2);
        B += A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 1 && B(0,1) == 1 && B(1,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorSubtractionAccumulatorScalarDouble ()
{
    LinAlg::Matrix<double> B = LinAlg::Zeros<double>(2,2);
    QBENCHMARK {
        B = LinAlg::Zeros<double>(2,2);
        B -= 1;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == -1 && B(1,0) == -1 && B(0,1) == -1 && B(1,1) == -1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorSubtractionAccumulatorMatrixDouble ()
{
    LinAlg::Matrix<double> B = LinAlg::Zeros<double>(2,2), A = LinAlg::Ones<double>(2,2);
    QBENCHMARK {
        B = LinAlg::Zeros<double>(2,2);
        B -= A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == -1 && B(1,0) == -1 && B(0,1) == -1 && B(1,1) == -1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorMultiplicationAccumulatorScalarDouble ()
{
    LinAlg::Matrix<double> B = 2*LinAlg::Ones<double>(2,2);
    QBENCHMARK {
        B = 2*LinAlg::Ones<double>(2,2);
        B *= 2;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 4 && B(1,0) == 4 && B(0,1) == 4 && B(1,1) == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorMultiplicationAccumulatorMatrixDouble ()
{
    LinAlg::Matrix<double> B = LinAlg::Ones<double>(2,2), A = LinAlg::Ones<double>(2,2);
    QBENCHMARK {
        B = LinAlg::Ones<double>(2,2);
        B *= A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 2 && B(1,0) == 2 && B(0,1) == 2 && B(1,1) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorDivisionAccumulatorScalarDouble ()
{
    LinAlg::Matrix<double> B = 2*LinAlg::Ones<double>(2,2);
    QBENCHMARK {
        B = 2*LinAlg::Ones<double>(2,2);
        B /= 2;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 1 && B(0,1) == 1 && B(1,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorDivisionAccumulatorMatrixDouble ()
{
    LinAlg::Matrix<double> B = LinAlg::Ones<double>(2,2), A = LinAlg::Eye<double>(2);
    QBENCHMARK {
        B = LinAlg::Ones<double>(2,2);
        B /= A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 1 && B(0,1) == 1 && B(1,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorPotentiationAccumulatorScalarDouble ()
{
    LinAlg::Matrix<double> B = LinAlg::Ones<double>(2,2), A = LinAlg::Ones<double>(2,2);
    QBENCHMARK {
        B = LinAlg::Ones<double>(2,2);
        B ^= 2;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 2 && B(1,0) == 2 && B(0,1) == 2 && B(1,1) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorEqualDouble ()
{
    LinAlg::Matrix<double> A = "1,2;1,2";
    LinAlg::Matrix<bool> B;
    QBENCHMARK {
        B = A == 1;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 1 && B(0,1) == 0 && B(1,1) == 0, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorLessEqualThanDouble ()
{
    LinAlg::Matrix<double> A = "1,2;1,2";
    LinAlg::Matrix<bool> B;
    QBENCHMARK {
        B = A <= 1;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 1 && B(0,1) == 0 && B(1,1) == 0, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorGreaterEqualThanDouble ()
{
    LinAlg::Matrix<double> A = "1,2;1,2";
    LinAlg::Matrix<bool> B;
    QBENCHMARK {
        B = A >= 2;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 0 && B(1,0) == 0 && B(0,1) == 1 && B(1,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorLessThanDouble ()
{
    LinAlg::Matrix<double> A = "1,2;1,2";
    LinAlg::Matrix<bool> B;
    QBENCHMARK {
        B = A < 2;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 1 && B(0,1) == 0 && B(1,1) == 0, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorGreaterThanDouble ()
{
    LinAlg::Matrix<double> A = "1,2;1,2";
    LinAlg::Matrix<bool> B;
    QBENCHMARK {
        B = A > 1;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 0 && B(1,0) == 0 && B(0,1) == 1 && B(1,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::horizontalConcatenationOperatorScalarDouble ()
{
    LinAlg::Matrix<double> A = "1,2", B;

    QBENCHMARK {
        B = A|3;
    }
    QVERIFY2(B.getNumberOfColumns() == 3 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(0,1) == 2 && B(0,2) == 3, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::horizontalConcatenationOperatorMatrixDouble ()
{
    LinAlg::Matrix<double> A = "1,2", B;

    QBENCHMARK {
        B = A|LinAlg::Matrix<double>(3);
    }
    QVERIFY2(B.getNumberOfColumns() == 3 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(0,1) == 2 && B(0,2) == 3, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::verticalConcatenationOperatorScalarDouble()
{
    LinAlg::Matrix<double> A = "1;2", B;

    QBENCHMARK {
        B = A||3;
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 2 && B(2,0) == 3, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::verticalConcatenationOperatorMatrixDouble()
{
    LinAlg::Matrix<double> A = "1;2", B;

    QBENCHMARK {
        B = A||LinAlg::Matrix<double>(3);
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 2 && B(2,0) == 3, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase1 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "1"; B = "2,3";
        B << A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 3 && B(0,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase2 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "2"; B = "1";
        B << A;
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase3 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "2;2"; B = "1;1";
        B << A;
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 2 && B(1,0) == 2 , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase4 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "2;2"; B = "1,1;1,1";
        B << A;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 1 && B(0,1) == 2 && B(1,1) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase5 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "2,2;2,2;2,2"; B = "1,1,1;1,1,1;1,1,1";
        B << A;
    }
    QVERIFY2(B.getNumberOfColumns() == 3 && B.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(1,0) == 1 && B(2,0) == 1 &&
             B(0,1) == 2 && B(1,1) == 2 && B(2,1) == 2 &&
             B(0,2) == 2 && B(1,2) == 2 && B(2,2) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase6 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "1"; B = "2,3";
        A >> B;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(0,1) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase7 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "2"; B = "1";
        A >> B;
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase8 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "2;2"; B = "1;1";
        A >> B;
    }
    QVERIFY2(B.getNumberOfColumns() == 1 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 2 && B(1,0) == 2 , "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase9 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "2;2"; B = "1,1;1,1";
        A >> B;
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 2 && B(1,0) == 2 && B(0,1) == 1 && B(1,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::bufferOperatorDoubleCase10 ()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "2,2;2,2;2,2"; B = "1,1,1;1,1,1;1,1,1";
        A >> B;
    }
    QVERIFY2(B.getNumberOfColumns() == 3 && B.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 2 && B(1,0) == 2 && B(2,0) == 2 &&
             B(0,1) == 2 && B(1,1) == 2 && B(2,1) == 2 &&
             B(0,2) == 1 && B(1,2) == 1 && B(2,2) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::swapTwoMatrixDouble()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "1,2;3,4"; B = "4,3;2,1";
        B.swap(A);
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(0,1) == 2 &&
             B(1,0) == 3 && B(1,1) == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::swapTwoMatrixFriendDouble()
{
    LinAlg::Matrix<double> A, B;

    QBENCHMARK {
        A = "1,2;3,4"; B = "4,3;2,1";
        swap(B,A);
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == 1 && B(0,1) == 2 &&
             B(1,0) == 3 && B(1,1) == 4, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorSumMatrixScalarDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;

    QBENCHMARK {
        C = A+2;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 3 && C(0,1) == 4 &&
             C(1,0) == 5 && C(1,1) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorSumScalarMatrixDouble()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;

    QBENCHMARK {
        C = 2+A;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 3 && C(0,1) == 4 &&
             C(1,0) == 5 && C(1,1) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorSumMatrixMatrixDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;
    LinAlg::Matrix<int> B = "4,3;2,1";
    QBENCHMARK {
        C = A+B;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 5 && C(0,1) == 5 &&
             C(1,0) == 5 && C(1,1) == 5, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorSubtractionMatrixScalarDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;

    QBENCHMARK {
        C = A-2;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == -1 && C(0,1) == 0 &&
             C(1,0) == 1 && C(1,1) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorSubtractionScalarMatrixDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;

    QBENCHMARK {
        C = 2-A;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 1 && C(0,1) == 0 &&
             C(1,0) == -1 && C(1,1) == -2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorSubtractionMatrixMatrixDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;
    LinAlg::Matrix<int> B = "4,3;2,1";
    QBENCHMARK {
        C = A-B;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == -3 && C(0,1) == -1 &&
             C(1,0) == 1 && C(1,1) == 3, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorMultiplicationMatrixScalarDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;

    QBENCHMARK {
        C = A*2;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 2 && C(0,1) == 4 &&
             C(1,0) == 6 && C(1,1) == 8, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorMultiplicationScalarMatrixDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;

    QBENCHMARK {
        C = 2*A;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 2 && C(0,1) == 4 &&
             C(1,0) == 6 && C(1,1) == 8, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorMultiplicationMatrixMatrixDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4;5,6", C;
    LinAlg::Matrix<int> B = "1,2;3,4";
    QBENCHMARK {
        C = A*B;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 7  && C(0,1) == 10 &&
             C(1,0) == 15 && C(1,1) == 22 &&
             C(2,0) == 23 && C(2,1) == 34, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorDivisionMatrixScalarDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;

    QBENCHMARK {
        C = A/2;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 0.5 && C(0,1) == 1 &&
             C(1,0) == 1.5 && C(1,1) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorDivisionMatrixMatrixDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4;5,6", C;
    LinAlg::Matrix<double> B = "1,2;3,4";
    QBENCHMARK {
        C = A/B;

    }
    QVERIFY2(C.getNumberOfColumns() == 2 &&C.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 1  && C(0,1) == 0 &&
             C(1,0) == 0  && C(1,1) == 1 &&
             C(2,0) == -1 && C(2,1) == 2, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorNegativeMatrixDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4;5,6", C;
    QBENCHMARK {
        C = -A;
    }
    QVERIFY2(C.getNumberOfColumns() == 2 && C.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == -1  && C(0,1) == -2 &&
             C(1,0) == -3  && C(1,1) == -4 &&
             C(2,0) == -5  && C(2,1) == -6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorTransposeMatrixDouble()
{
    LinAlg::Matrix<double> A = "1,2;3,4;5,6", C;
    QBENCHMARK {
        C = ~A;
    }
    QVERIFY2(C.getNumberOfColumns() == 3 && C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 1  && C(0,1) == 3 && C(0,2) == 5 &&
             C(1,0) == 2  && C(1,1) == 4 && C(1,2) == 6, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::operatorPotentiationScalarDouble ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", C;
    QBENCHMARK {
        C = A^2;
    }
    QVERIFY2(C.getNumberOfColumns() == 2 && C.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(C(0,0) == 7  && C(0,1) == 10 &&
             C(1,0) == 15 && C(1,1) == 22, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::zerosMatrixDouble ()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = LinAlg::Zeros<double>(2,2);
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 0 && A(0,1) == 0 &&
             A(1,0) == 0 && A(1,1) == 0, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::identityMatrixDouble ()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = LinAlg::Eye<double>(2);
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1 && A(0,1) == 0 &&
             A(1,0) == 0 && A(1,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}
void MatrixTest::onesMatrixDouble ()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = LinAlg::Ones<double>(2,2);
    }
    QVERIFY2(A.getNumberOfColumns() == 2 && A.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1 && A(0,1) == 1 &&
             A(1,0) == 1 && A(1,1) == 1, "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::LineVector ()
{
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = LinAlg::LineVector<double>(1,5);
    }
    QVERIFY2(A.getNumberOfColumns() == 5 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) == 1 && A(0,1) == 2 && A(0,2) == 3 && A(0,3) == 4 && A(0,4) == 5,
             "Falhou ao comparar todos os elementos da matriz com valor double");

    QBENCHMARK {
        A = LinAlg::LineVector<double>(5,1,-1);
    }
    QVERIFY2(A.getNumberOfColumns() == 5 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
//    std::cout << A;
    QVERIFY2(A(0,0) == 5 && A(0,1) == 4 && A(0,2) == 3 && A(0,3) == 2 && A(0,4) == 1,
             "Falhou ao comparar todos os elementos da matriz com valor double");
}

void MatrixTest::Random ()
{
    srand(time(NULL));
    LinAlg::Matrix<double> A;
    QBENCHMARK {
        A = LinAlg::Random<double>(2,5);
    }
    QVERIFY2(A.getNumberOfColumns() == 5 && A.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(A(0,0) < 1 && A(0,1) < 1 && A(0,2) < 1 && A(0,3) < 1 && A(0,4) < 1,
             "Falhou ao comparar todos os elementos da matriz com valor double");

}

void MatrixTest::Determinant ()
{
    LinAlg::Matrix<double> A = "1,2;3,4";
    double b;
    QBENCHMARK {
        b = LinAlg::Determinant(A);
    }
//    QVERIFY2(A.getNumberOfColumns() == 5 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(b == -2, "Falhou ao comparar o determinante com valor double");
}

//void MatrixTest::Cofactor ()
//{
//    LinAlg::Matrix<double> A = "1,2;3,4";
//    QBENCHMARK {
//        double b = LinAlg::Determinant(A);
//    }
////    QVERIFY2(A.getNumberOfColumns() == 5 && A.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
//    QVERIFY2(LinAlg::Determinant(A) == -2,
//             "Falhou ao comparar o determinante com valor double");
//}

void MatrixTest::Inverse ()
{
    LinAlg::Matrix<double> A = "1,2;3,4", B;
    QBENCHMARK {
        B = LinAlg::Inverse(A);
    }
    QVERIFY2(B.getNumberOfColumns() == 2 && B.getNumberOfRows() == 2, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(B(0,0) == -2 && B(0,1) == 1 && B(1,0) == 1.5 && B(1,1) == -0.5,
             "Falhou ao comparar a inversa com valor double");
}

void MatrixTest::operatorBufferStringShow ()
{
    LinAlg::Matrix<double> A = "1,2;3,4";
    std::string B;
    QBENCHMARK {
        B << A;
    }
//    std::cout << B;
    QVERIFY2(B.find("1.000 ") != -1 && B.find("2.000 ") != -1 && B.find("3.000 ") != -1 && B.find("4.000 ") != -1,
             "Falhou ao comparar a string com valor double");
}

void MatrixTest::operatorBufferStringBack ()
{
    LinAlg::Matrix<double> A = "1,2;3,4";
    std::string B;
    QBENCHMARK {
        B <<= A;
    }
//    std::cout << B;
    QVERIFY2(B.find("1.000,") != -1 && B.find("2.000;") != -1 && B.find("3.000,") != -1 && B.find("4.000") != -1,
             "Falhou ao comparar a string com valor double");
}

void MatrixTest::sort ()
{
    LinAlg::Matrix<double> A = "1,5,6,3,2,7", matrixSorted, matrixIndices;
    QBENCHMARK {
        *(matrixSorted, matrixIndices) = LinAlg::sort(A);
    }

    QVERIFY2(matrixSorted.getNumberOfColumns() == 6 && matrixSorted.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(matrixSorted(0,0) == 1 && matrixSorted(0,1) == 2 && matrixSorted(0,2) == 3 &&
             matrixSorted(0,3) == 5 && matrixSorted(0,4) == 6 && matrixSorted(0,5) == 7,
             "Falhou ao comparar elementos da matriz com valor double");
    QVERIFY2(matrixIndices.getNumberOfColumns() == 6 && matrixIndices.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(matrixIndices(0,0) == 0 && matrixIndices(0,1) == 4 && matrixIndices(0,2) == 3 &&
             matrixIndices(0,3) == 1 && matrixIndices(0,4) == 2 && matrixIndices(0,5) == 5,
             "Falhou ao comparar elementos da matriz com valor double");

    A = ~A;
    QBENCHMARK {
        *(matrixSorted, matrixIndices) = LinAlg::sort(A);
    }

    QVERIFY2(matrixSorted.getNumberOfColumns() == 1 && matrixSorted.getNumberOfRows() == 6, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(matrixSorted(0,0) == 1 && matrixSorted(1,0) == 2 && matrixSorted(2,0) == 3 &&
             matrixSorted(3,0) == 5 && matrixSorted(4,0) == 6 && matrixSorted(5,0) == 7,
             "Falhou ao comparar elementos da matriz com valor double");
    QVERIFY2(matrixIndices.getNumberOfColumns() == 1 && matrixIndices.getNumberOfRows() == 6, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(matrixIndices(0,0) == 0 && matrixIndices(1,0) == 4 && matrixIndices(2,0) == 3 &&
             matrixIndices(3,0) == 1 && matrixIndices(4,0) == 2 && matrixIndices(5,0) == 5,
             "Falhou ao comparar elementos da matriz com valor double");
}

void MatrixTest::min ()
{
    LinAlg::Matrix<double> A = "1,5;2,1;5,3", minMatrix, minIndices;
    QBENCHMARK {
        *(minMatrix, minIndices) = LinAlg::min(A);
    }

    QVERIFY2(minMatrix.getNumberOfColumns() == 2 && minMatrix.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(minMatrix(0,0) == 1 && minMatrix(0,1) == 1,
             "Falhou ao comparar elementos da matriz com valor double");
    QVERIFY2(minIndices.getNumberOfColumns() == 2 && minIndices.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(minIndices(0,0) == 0 && minIndices(0,1) == 1,
             "Falhou ao comparar elementos da matriz com valor double");

    A = "1,2,4,1";
    QBENCHMARK {
        *(minMatrix, minIndices) = LinAlg::min(A);
    }

    QVERIFY2(minMatrix.getNumberOfColumns() == 1 && minMatrix.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(minMatrix(0,0) == 1.0,
             "Falhou ao comparar elementos da matriz com valor double");
    QVERIFY2(minIndices.getNumberOfColumns() == 1 && minIndices.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(minIndices(0,0) == 0,
             "Falhou ao comparar elementos da matriz com valor double");
}

void MatrixTest::max ()
{
    LinAlg::Matrix<double> A = "1,5;2,1;5,3", maxMatrix, maxIndices;
    QBENCHMARK {
        *(maxMatrix, maxIndices) = LinAlg::max(A);
    }

    QVERIFY2(maxMatrix.getNumberOfColumns() == 2 && maxMatrix.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(maxMatrix(0,0) == 5 && maxMatrix(0,1) == 5,
             "Falhou ao comparar elementos da matriz com valor double");
    QVERIFY2(maxIndices.getNumberOfColumns() == 2 && maxIndices.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(maxIndices(0,0) == 2 && maxIndices(0,1) == 0,
             "Falhou ao comparar elementos da matriz com valor double");

    A = "1,2,4,1";
    QBENCHMARK {
        *(maxMatrix, maxIndices) = LinAlg::max(A);
    }

    QVERIFY2(maxMatrix.getNumberOfColumns() == 1 && maxMatrix.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(maxMatrix(0,0) == 4,
             "Falhou ao comparar elementos da matriz com valor double");
    QVERIFY2(maxIndices.getNumberOfColumns() == 1 && maxIndices.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(maxIndices(0,0) == 2,
             "Falhou ao comparar elementos da matriz com valor double");
}

void MatrixTest::sum ()
{
    LinAlg::Matrix<double> A = "1,5;2,1;5,3", sumMatrix;
    QBENCHMARK {
        sumMatrix = LinAlg::sum(A);
    }
    QVERIFY2(sumMatrix.getNumberOfColumns() == 2 && sumMatrix.getNumberOfRows() == 1, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(sumMatrix(0,0) == 8 && sumMatrix(0,1) == 9,
             "Falhou ao comparar elementos da matriz com valor double");

    QBENCHMARK {
        sumMatrix = LinAlg::sum(A,1);
    }
    QVERIFY2(sumMatrix.getNumberOfColumns() == 1 && sumMatrix.getNumberOfRows() == 3, "Falhou ao testar o tamanho da matriz");
    QVERIFY2(sumMatrix(0,0) == 6 && sumMatrix(1,0) == 3 && sumMatrix(2,0) == 8,
             "Falhou ao comparar elementos da matriz com valor double");
}


QTEST_APPLESS_MAIN(MatrixTest)

#include "tst_matrixtest.moc"
