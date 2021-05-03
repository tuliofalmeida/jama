#define testPolynom
#define testModel

#define coutPrecision 8
#include <QString>
#include <QtTest>
#include "../../../headers/primitiveLibs/LinAlg/matrix.h"
#include "../../../headers/modelLibs/model.h"
#include "../../../headers/modelLibs/arx.h"
#include "../../../headers/modelLibs/transferfunction.h"
#include "../../../headers/modelLibs/conversions.h"
#include "../../../headers/optimizationLibs/leastsquare.h"
#include "../../../headers/optimizationLibs/recursiveleastsquare.h"

class ArxDoubleTest : public QObject
{
    Q_OBJECT

public:
    ArxDoubleTest(){}

private Q_SLOTS:
    void SS();
    void voidConstructorCase1 ();
    void voidConstructorCase2 ();
    void voidConstructorCase3 ();
    void voidConstructorCase4 ();
    void voidConstructorCase5 ();
    void voidConstructorCase6 ();
    void copyConstructor ();
    void copyConstructorOtherType ();
    void copyAssignment ();
    void copyAssignmentOtherType ();
    void stringConversionCase1();
    void stringConversionCase2();
    void stringConversionCase3();
    void stringConversionCase4();
    void stringConversionCase5();
    void stringConversionCase6();
    void stringConversionCase7();
    void stringConversionCase8();
    void stringConversionCase9();
    void stringConversionCase10();
    void stringConversionCase11();
    void stringConversionCase12();
    void stringConversionCase13();
    void stringConversionCase14();
    void stringConversionCase15();
    void getNumberOfInputDelays();
    void getNumberOfInputs();
    void getNumberOfOutputDelays();
    void getNumberOfOutputs();
    void getNumberOfVariables();
    void getMaxnInOut ();
    void getNSample ();
    void getSingleInput();
    void getSingleOutput();
    void getSingleEstOutput();
    void getLmin();
    void getLmax();
    void getStep();
    void getTimeSimulation();
    void getTransportDelay();
    void getInputMatrix();
    void getOutputMatrix();
    void getEstOutputMatrix();
    void getModelCoef();

    void getLinearSystem();
    void getLinearMatrixA();
    void getLinearEqualityB();
    void getLinearVectorA();
    void getLinearEqualityVectorB();
    void getInputLinearVector();
    void getOutputLinearVector();
    void setLinearModel ();
    void setLinearVector();
    void setInitialOutputValue();

    void simInScalar();
    void simInOutScalar();
    void simInMatrix();
    void simInOutMatrix();
    void simRange(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
};



void ArxDoubleTest::SS()
{
    ModelHandler::ARX<double> arx(2,2,0,2,2,0.1);
    arx.setModelCoef("-1.87085281783314,-0.0257757033875835;0.872372441342299,0.0260503483855521;0.0134449857557203,-1.91759967979487;-0.0138029025062675,0.878507728995683;0.00803352607122690,9.86084948436049e-05;-0.00264657484585805,-0.000400820393917207;5.66450203206749e-06,0.00164742672119849;1.38049689720422e-06,-0.000609528899845942");
    std::cout << arx.print() << std::endl;

    std::cout << ModelHandler::arx2SS(arx) << std::endl;

    std::cout << ModelHandler::arx2tf(arx) << std::endl;
    arx.print();
}

void ArxDoubleTest::voidConstructorCase1()
{
    ModelHandler::ARX<double> arx(1,1);
    QBENCHMARK {
        ModelHandler::ARX<double> arx(1,1);
    }
    QVERIFY2(arx.getNumberOfInputDelays()  == 1, "Falha ao testar o numero de atrasos das entradas do modelo arx");
    QVERIFY2(arx.getNumberOfOutputDelays() == 1, "Falha ao testar o numero de atrasos das saidas do modelo arx");
    QVERIFY2(arx.getNumberOfInputs()    == 1, "Falha ao testar o numero de entradas do modelo arx");
    QVERIFY2(arx.getNumberOfOutputs()   == 1, "Falha ao testar o numero de saidas do modelo arx");
    QVERIFY2(arx.getNumberOfVariables() == 2, "Falha ao testar o numero de variaveis do modelo arx");
    QVERIFY2(arx.getNumberOfInputs()    == 1, "Falha ao testar o numero de entradas do modelo arx");
    QVERIFY2(arx.getNumberOfOutputs()   == 1, "Falha ao testar o numero de saidas do modelo arx");
    QVERIFY2(arx.getNumberOfVariables() == 2, "Falha ao testar o numero de variaveis do modelo arx");
    QVERIFY2(arx.getStep() == 0.1, "Falha ao testar o periodo de amostragem do modelo arx");
    QVERIFY2(arx.getModelCoef()(0,0) == 0 && arx.getModelCoef()(1,0) == 0, "Falha ao testar os parametros do modelo arx");
    QVERIFY2(arx.getInputMatrix()(0,0) == 0, "Falha ao testar as entradas do modelo arx");
    QVERIFY2(arx.getOutputMatrix()(0,0) == 0, "Falha ao testar as saidas do modelo arx");
    QVERIFY2(arx.getSingleOutput() == 0, "Falha ao testar as saidas do modelo arx");
}

void ArxDoubleTest::voidConstructorCase2()
{
    ModelHandler::Model<double> *M = new ModelHandler::ARX<double>(1,1);

    QBENCHMARK {
        ModelHandler::Model<double> *M = new ModelHandler::ARX<double>(1,1);
    }

    QVERIFY2(M->getNumberOfInputs()    == 1, "Falha ao testar o numero de entradas do modelo arx");
    QVERIFY2(M->getNumberOfOutputs()   == 1, "Falha ao testar o numero de saidas do modelo arx");
    QVERIFY2(M->getNumberOfVariables() == 2, "Falha ao testar o numero de variaveis do modelo arx");
    QVERIFY2(M->getStep() == 0.1, "Falha ao testar o periodo de amostragem do modelo arx");
    QVERIFY2(M->getModelCoef()(0,0) == 0 && M->getModelCoef()(1,0) == 0, "Falha ao testar os parametros do modelo arx");
    QVERIFY2(M->getInputMatrix()(0,0) == 0, "Falha ao testar as entradas do modelo arx");
    QVERIFY2(M->getOutputMatrix()(0,0) == 0, "Falha ao testar as saidas do modelo arx");
    QVERIFY2(M->getSingleOutput() == 0, "Falha ao testar as saidas do modelo arx");
}

void ArxDoubleTest::voidConstructorCase3()
{
    ModelHandler::ARX<double> arx(2,2);

    QBENCHMARK {
        ModelHandler::ARX<double> arx(2,2);
    }

    QVERIFY2(arx.getNumberOfInputs()    == 1, "Falha ao testar o numero de entradas do modelo arx");
    QVERIFY2(arx.getNumberOfOutputs()   == 1, "Falha ao testar o numero de saidas do modelo arx");
    QVERIFY2(arx.getNumberOfVariables() == 4, "Falha ao testar o numero de variaveis do modelo arx");
    QVERIFY2(arx.getStep() == 0.1, "Falha ao testar o periodo de amostragem do modelo arx");
    QVERIFY2(arx.getModelCoef()(0,0) == 0 && arx.getModelCoef()(1,0) == 0 &&
             arx.getModelCoef()(2,0) == 0 && arx.getModelCoef()(3,0) == 0, "Falha ao testar os parametros do modelo arx");
    QVERIFY2(arx.getInputMatrix()(0,0) == 0 && arx.getInputMatrix()(0,1) == 0, "Falha ao testar as entradas do modelo arx");
    QVERIFY2(arx.getOutputMatrix()(0,0) == 0 && arx.getOutputMatrix()(0,1) == 0, "Falha ao testar as saidas do modelo arx");
    QVERIFY2(arx.getSingleOutput() == 0, "Falha ao testar as saidas do modelo arx");
    QVERIFY2(arx.getNumberOfInputDelays()  == 2, "Falha ao testar o numero de atrasos das entradas do modelo arx");
    QVERIFY2(arx.getNumberOfOutputDelays() == 2, "Falha ao testar o numero de atrasos das saidas do modelo arx");
    QVERIFY2(arx.getNumberOfInputs()    == 1, "Falha ao testar o numero de entradas do modelo arx");
    QVERIFY2(arx.getNumberOfOutputs()   == 1, "Falha ao testar o numero de saidas do modelo arx");
    QVERIFY2(arx.getNumberOfVariables() == 4, "Falha ao testar o numero de variaveis do modelo arx");
}

void ArxDoubleTest::voidConstructorCase4()
{
    ModelHandler::Model<double> *M = new ModelHandler::ARX<double>(2,2);

    QBENCHMARK {
        ModelHandler::Model<double> *M = new ModelHandler::ARX<double>(2,2);
    }

    QVERIFY2(M->getNumberOfInputs()    == 1, "Falha ao testar o numero de entradas do modelo arx");
    QVERIFY2(M->getNumberOfOutputs()   == 1, "Falha ao testar o numero de saidas do modelo arx");
    QVERIFY2(M->getNumberOfVariables() == 4, "Falha ao testar o numero de variaveis do modelo arx");
    QVERIFY2(M->getStep() == 0.1, "Falha ao testar o periodo de amostragem do modelo arx");
    QVERIFY2(M->getModelCoef()(0,0) == 0 && M->getModelCoef()(1,0) == 0 &&
             M->getModelCoef()(2,0) == 0 && M->getModelCoef()(3,0) == 0, "Falha ao testar os parametros do modelo arx");
    QVERIFY2(M->getInputMatrix()(0,0) == 0 && M->getInputMatrix()(0,1) == 0, "Falha ao testar as entradas do modelo arx");
    QVERIFY2(M->getOutputMatrix()(0,0) == 0 && M->getOutputMatrix()(0,1) == 0, "Falha ao testar as saidas do modelo arx");
    QVERIFY2(M->getSingleOutput() == 0, "Falha ao testar as saidas do modelo arx");
}

void ArxDoubleTest::voidConstructorCase5()
{
    ModelHandler::ARX<double> arx(2,2,0,2,2,0.1);

    QBENCHMARK {
        ModelHandler::ARX<double> arx(2,2,0,2,2,0.1);
    }

    QVERIFY2(arx.getNumberOfInputDelays()  == 2, "Falha ao testar o numero de atrasos das entradas do modelo arx");
    QVERIFY2(arx.getNumberOfOutputDelays() == 2, "Falha ao testar o numero de atrasos das saidas do modelo arx");
    QVERIFY2(arx.getNumberOfInputs()    == 2, "Falha ao testar o numero de entradas do modelo arx");
    QVERIFY2(arx.getNumberOfOutputs()   == 2, "Falha ao testar o numero de saidas do modelo arx");
    QVERIFY2(arx.getNumberOfVariables() == 8, "Falha ao testar o numero de variaveis do modelo arx");
}

void ArxDoubleTest::voidConstructorCase6()
{
    ModelHandler::Model<double> *M = new ModelHandler::ARX<double>(2,2,0,2,2,0.1);

    QBENCHMARK {
        ModelHandler::Model<double> *M = new ModelHandler::ARX<double>(2,2,0,2,2,0.1);
    }

    QVERIFY2(M->getNumberOfInputs()    == 2, "Falha ao testar o numero de entradas do modelo arx");
    QVERIFY2(M->getNumberOfOutputs()   == 2, "Falha ao testar o numero de saidas do modelo arx");
    QVERIFY2(M->getNumberOfVariables() == 8, "Falha ao testar o numero de variaveis do modelo arx");
    QVERIFY2(M->getStep() == 0.1, "Falha ao testar o periodo de amostragem do modelo arx");
    QVERIFY2(M->getModelCoef()(0,0) == 0 && M->getModelCoef()(1,0) == 0 &&
             M->getModelCoef()(2,0) == 0 && M->getModelCoef()(3,0) == 0, "Falha ao testar os parametros do modelo arx");
    QVERIFY2(M->getModelCoef()(0,1) == 0 && M->getModelCoef()(1,1) == 0 &&
             M->getModelCoef()(2,1) == 0 && M->getModelCoef()(3,1) == 0, "Falha ao testar os parametros do modelo arx");
    QVERIFY2(M->getInputMatrix()(0,0) == 0 && M->getInputMatrix()(0,1) == 0, "Falha ao testar as entradas do modelo arx");
    QVERIFY2(M->getInputMatrix()(1,0) == 0 && M->getInputMatrix()(1,1) == 0, "Falha ao testar as entradas do modelo arx");
    QVERIFY2(M->getOutputMatrix()(0,0) == 0 && M->getOutputMatrix()(0,1) == 0, "Falha ao testar as saidas do modelo arx");
    QVERIFY2(M->getOutputMatrix()(1,0) == 0 && M->getOutputMatrix()(1,1) == 0, "Falha ao testar as saidas do modelo arx");
    QVERIFY2(M->getSingleOutput() == 0, "Falha ao testar as saidas do modelo arx");
}

void ArxDoubleTest::copyConstructor ()
{
    ModelHandler::ARX<double> arx2(2,2,0,2,2,0.1);
    ModelHandler::ARX<double> arx(arx2);

    QBENCHMARK {
        ModelHandler::ARX<double> arx2(2,2,0,2,2,0.1);
        ModelHandler::ARX<double> arx(arx2);
    }

    QVERIFY2(arx.getNumberOfInputDelays() == arx2.getNumberOfInputDelays(), "O numero de atrasos nas entradas e diferente na copia do construtor");
    QVERIFY2(arx.getNumberOfInputs() == arx2.getNumberOfInputs(), "O numero de variaveis de entrada e diferente na copia do construtor");
    QVERIFY2(arx.getNumberOfOutputDelays() == arx2.getNumberOfOutputDelays(), "O numero de atrasos nas saidas e diferente na copia do construtor");
    QVERIFY2(arx.getNumberOfOutputs() == arx2.getNumberOfOutputs(), "O numero de variaveis de saida e diferente na copia do construtor");
    QVERIFY2(arx.getMaxnInOut () == arx2.getMaxnInOut(), "O numero de maximo de atrasos e diferente na copia do construtor");
    QVERIFY2(arx.getNSample () == arx2.getNSample(), "O numero de amostras e diferente na copia do construtor");

    QVERIFY2(arx.getSingleInput() == arx2.getSingleInput(), "O valor das entradas e diferente na copia do construtor");
    QVERIFY2(arx.getSingleOutput() == arx2.getSingleOutput(), "O valor das saidas e diferente na copia do construtor");
    QVERIFY2(arx.getSingleEstOutput() == arx2.getSingleEstOutput(), "O valor das saidas estimadas e diferente na copia do construtor");
    QVERIFY2(arx.getLmin() == arx2.getLmin(), "O valor do limite minimo e diferente na copia do construtor");
    QVERIFY2(arx.getLmax() == arx2.getLmax(), "O valor do limite maximo e diferente na copia do construtor");
    QVERIFY2(arx.getStep() == arx2.getStep(), "O valor do passo de simulacao e diferente na copia do construtor");
    QVERIFY2(arx.getTimeSimulation() == arx2.getTimeSimulation(), "O tempo de simulacao e diferente na copia do construtor");
    QVERIFY2(arx.getTransportDelay() == arx2.getTransportDelay(), "O valor dos atrasos de transporte e diferente na copia do construtor");

    QVERIFY2(LinAlg::isEqual(arx.getInputMatrix(),arx2.getInputMatrix()), "O valor das entradas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getOutputMatrix(),arx2.getOutputMatrix()), "O valor das saidas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getEstOutputMatrix(),arx2.getEstOutputMatrix()), "O valor das saidas estimadas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getModelCoef(),arx2.getModelCoef()), "O valor dos coeficientes do modelo e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityVectorB(),arx2.getLinearEqualityVectorB()), "O valor dos elementos de B no vetor do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearMatrixA(),arx2.getLinearMatrixA()), "O valor dos elementos de A na Matrix do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearVectorA(),arx2.getLinearVectorA()), "O valor dos elementos de A no vetor do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityB(),arx2.getLinearEqualityB()), "O valor dos elementos de B na Matrix do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getInputLinearVector(),arx2.getInputLinearVector()), "O vetor de estados da entrada e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getOutputLinearVector(),arx2.getOutputLinearVector()), "O vetor de estados da saida e diferente na copia do construtor");
}

void ArxDoubleTest::copyConstructorOtherType ()
{
    ModelHandler::ARX<double> arx2(2,2,0,2,2,0.1);
    ModelHandler::ARX<long double> arx(arx2);

    QBENCHMARK {
        ModelHandler::ARX<double> arx2(2,2,0,2,2,0.1);
        ModelHandler::ARX<long double> arx(arx2);
    }

    QVERIFY2(fabs(arx.getNumberOfInputDelays() - arx2.getNumberOfInputDelays()) < 1e-30, "O numero de atrasos nas entradas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getNumberOfInputs() - arx2.getNumberOfInputs()) < 1e-30, "O numero de variaveis de entrada e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getNumberOfOutputDelays() - arx2.getNumberOfOutputDelays()) < 1e-30, "O numero de atrasos nas saidas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getNumberOfOutputs() - arx2.getNumberOfOutputs()) < 1e-30, "O numero de variaveis de saida e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getMaxnInOut() - arx2.getMaxnInOut()) < 1e-30, "O numero de maximo de atrasos e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getNSample() - arx2.getNSample()) < 1e-30, "O numero de amostras e diferente na copia do construtor");

    QVERIFY2(fabs(arx.getSingleInput() - arx2.getSingleInput()) < 1e-30, "O valor das entradas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getSingleOutput() - arx2.getSingleOutput()) < 1e-30, "O valor das saidas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getSingleEstOutput() - arx2.getSingleEstOutput()) < 1e-30, "O valor das saidas estimadas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getLmin() - arx2.getLmin()) < 1e-30, "O valor do limite minimo e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getLmax() - arx2.getLmax()) < 1e-30, "O valor do limite maximo e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getStep() - arx2.getStep()) < 1e-30, "O valor do passo de simulacao e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getTimeSimulation() - arx2.getTimeSimulation()) < 1e-30, "O tempo de simulacao e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getTransportDelay() - arx2.getTransportDelay()) < 1e-30, "O valor dos atrasos de transporte e diferente na copia do construtor");

    QVERIFY2(LinAlg::isEqual(arx.getInputMatrix(),arx2.getInputMatrix()), "O valor das entradas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getOutputMatrix(),arx2.getOutputMatrix()), "O valor das saidas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getEstOutputMatrix(),arx2.getEstOutputMatrix()), "O valor das saidas estimadas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getModelCoef(),arx2.getModelCoef()), "O valor dos coeficientes do modelo e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityVectorB(),arx2.getLinearEqualityVectorB()), "O valor dos elementos de B no vetor do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearMatrixA(),arx2.getLinearMatrixA()), "O valor dos elementos de A na Matrix do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearVectorA(),arx2.getLinearVectorA()), "O valor dos elementos de A no vetor do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityB(),arx2.getLinearEqualityB()), "O valor dos elementos de B na Matrix do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getInputLinearVector(),arx2.getInputLinearVector()), "O vetor de estados da entrada e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getOutputLinearVector(),arx2.getOutputLinearVector()), "O vetor de estados da saida e diferente na copia do construtor");
}

void ArxDoubleTest::copyAssignment ()
{
    ModelHandler::ARX<double> arx2(2,2,0,2,2,0.1);
    ModelHandler::ARX<double> arx = arx2;

    QBENCHMARK {
        ModelHandler::ARX<double> arx2(2,2,0,2,2,0.1);
        ModelHandler::ARX<double> arx = arx2;
    }

    QVERIFY2(arx.getNumberOfInputDelays() == arx2.getNumberOfInputDelays(), "O numero de atrasos nas entradas e diferente na copia do construtor");
    QVERIFY2(arx.getNumberOfInputs() == arx2.getNumberOfInputs(), "O numero de variaveis de entrada e diferente na copia do construtor");
    QVERIFY2(arx.getNumberOfOutputDelays() == arx2.getNumberOfOutputDelays(), "O numero de atrasos nas saidas e diferente na copia do construtor");
    QVERIFY2(arx.getNumberOfOutputs() == arx2.getNumberOfOutputs(), "O numero de variaveis de saida e diferente na copia do construtor");
    QVERIFY2(arx.getMaxnInOut () == arx2.getMaxnInOut(), "O numero de maximo de atrasos e diferente na copia do construtor");
    QVERIFY2(arx.getNSample () == arx2.getNSample(), "O numero de amostras e diferente na copia do construtor");

    QVERIFY2(arx.getSingleInput() == arx2.getSingleInput(), "O valor das entradas e diferente na copia do construtor");
    QVERIFY2(arx.getSingleOutput() == arx2.getSingleOutput(), "O valor das saidas e diferente na copia do construtor");
    QVERIFY2(arx.getSingleEstOutput() == arx2.getSingleEstOutput(), "O valor das saidas estimadas e diferente na copia do construtor");
    QVERIFY2(arx.getLmin() == arx2.getLmin(), "O valor do limite minimo e diferente na copia do construtor");
    QVERIFY2(arx.getLmax() == arx2.getLmax(), "O valor do limite maximo e diferente na copia do construtor");
    QVERIFY2(arx.getStep() == arx2.getStep(), "O valor do passo de simulacao e diferente na copia do construtor");
    QVERIFY2(arx.getTimeSimulation() == arx2.getTimeSimulation(), "O tempo de simulacao e diferente na copia do construtor");
    QVERIFY2(arx.getTransportDelay() == arx2.getTransportDelay(), "O valor dos atrasos de transporte e diferente na copia do construtor");

    QVERIFY2(LinAlg::isEqual(arx.getInputMatrix(),arx2.getInputMatrix()), "O valor das entradas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getOutputMatrix(),arx2.getOutputMatrix()), "O valor das saidas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getEstOutputMatrix(),arx2.getEstOutputMatrix()), "O valor das saidas estimadas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getModelCoef(),arx2.getModelCoef()), "O valor dos coeficientes do modelo e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityVectorB(),arx2.getLinearEqualityVectorB()), "O valor dos elementos de B no vetor do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearMatrixA(),arx2.getLinearMatrixA()), "O valor dos elementos de A na Matrix do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearVectorA(),arx2.getLinearVectorA()), "O valor dos elementos de A no vetor do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityB(),arx2.getLinearEqualityB()), "O valor dos elementos de B na Matrix do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getInputLinearVector(),arx2.getInputLinearVector()), "O vetor de estados da entrada e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getOutputLinearVector(),arx2.getOutputLinearVector()), "O vetor de estados da saida e diferente na copia do construtor");
}

void ArxDoubleTest::copyAssignmentOtherType ()
{
    ModelHandler::ARX<double> arx2(2,2,0,2,2,0.1);
    ModelHandler::ARX<long double> arx(1,1);
    QBENCHMARK {
        arx = arx2;
    }

    QVERIFY2(fabs(arx.getNumberOfInputDelays() - arx2.getNumberOfInputDelays()) < 1e-20, "O numero de atrasos nas entradas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getNumberOfInputs() - arx2.getNumberOfInputs()) < 1e-20, "O numero de variaveis de entrada e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getNumberOfOutputDelays() - arx2.getNumberOfOutputDelays()) < 1e-20, "O numero de atrasos nas saidas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getNumberOfOutputs() - arx2.getNumberOfOutputs()) < 1e-20, "O numero de variaveis de saida e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getMaxnInOut() - arx2.getMaxnInOut()) < 1e-20, "O numero de maximo de atrasos e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getNSample() - arx2.getNSample()) < 1e-20, "O numero de amostras e diferente na copia do construtor");

    QVERIFY2(fabs(arx.getSingleInput() - arx2.getSingleInput()) < 1e-20, "O valor das entradas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getSingleOutput() - arx2.getSingleOutput()) < 1e-20, "O valor das saidas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getSingleEstOutput() - arx2.getSingleEstOutput()) < 1e-20, "O valor das saidas estimadas e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getLmin() - arx2.getLmin()) < 1e-20, "O valor do limite minimo e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getLmax() - arx2.getLmax()) < 1e-20, "O valor do limite maximo e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getStep() - arx2.getStep()) < 1e-20, "O valor do passo de simulacao e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getTimeSimulation() - arx2.getTimeSimulation()) < 1e-20, "O tempo de simulacao e diferente na copia do construtor");
    QVERIFY2(fabs(arx.getTransportDelay() - arx2.getTransportDelay()) < 1e-20, "O valor dos atrasos de transporte e diferente na copia do construtor");

    QVERIFY2(LinAlg::isEqual(arx.getInputMatrix(),arx2.getInputMatrix()), "O valor das entradas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getOutputMatrix(),arx2.getOutputMatrix()), "O valor das saidas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getEstOutputMatrix(),arx2.getEstOutputMatrix()), "O valor das saidas estimadas e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getModelCoef(),arx2.getModelCoef()), "O valor dos coeficientes do modelo e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityVectorB(),arx2.getLinearEqualityVectorB()), "O valor dos elementos de B no vetor do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearMatrixA(),arx2.getLinearMatrixA()), "O valor dos elementos de A na Matrix do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearVectorA(),arx2.getLinearVectorA()), "O valor dos elementos de A no vetor do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityB(),arx2.getLinearEqualityB()), "O valor dos elementos de B na Matrix do sistema linear e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getInputLinearVector(),arx2.getInputLinearVector()), "O vetor de estados da entrada e diferente na copia do construtor");
    QVERIFY2(LinAlg::isEqual(arx.getOutputLinearVector(),arx2.getOutputLinearVector()), "O vetor de estados da saida e diferente na copia do construtor");
}

void ArxDoubleTest::stringConversionCase1()
{
    ModelHandler::TransferFunction<double> TF("20","1,2,1");
    ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TF,0.1);

    //std::cout << arx.print() << "\n";
    QBENCHMARK {
        arx.print();
    }

    QVERIFY2( arx.print() == " y1( k ) = 1.80967 y1( k - 1 )  - 0.818731 y1( k - 2 )  + 0.0935767 u1( k - 1 )  + 0.0875417 u1( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase2()
{
    ModelHandler::ARX<double> arx(2,2,0,2,1,0.1);
    arx.setModelCoef("-1.810;0.819;0.094;0.088;0.094;0.088");

    QBENCHMARK {
        arx.print();
    }

    QVERIFY2( arx.print() == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 )  + 0.094 u2( k - 1 )  + 0.088 u2( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase3()
{
    ModelHandler::ARX<double> arx(2,2,0,1,2,0.1);
    arx.setModelCoef("-1.810,0;0.819,0;0,-1.810;0,0.819;0.094,0.094;0.088,0.094");

    QBENCHMARK {
        arx.print();
    }

    QVERIFY2( arx.print() == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 ) \n y2( k ) = 1.81 y2( k - 1 )  - 0.819 y2( k - 2 )  + 0.094 u1( k - 1 )  + 0.094 u1( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase4()
{
    ModelHandler::ARX<double> arx(2,2,0,2,2,0.1);
    arx.setModelCoef("-1.810,0;0.819,0;0,-1.810;0,0.819;0.094,0;0.088,0;0,0.094;0,0.088");

    QBENCHMARK {
        arx.print();
    }

    QVERIFY2( arx.print() == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 ) \n y2( k ) = 1.81 y2( k - 1 )  - 0.819 y2( k - 2 )  + 0.094 u2( k - 1 )  + 0.088 u2( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase5()
{
    ModelHandler::ARX<double> arx(2,2,0,2,2,0.1);
    arx.setModelCoef("-1.810,-1.908;0.819,0.741;-1.952,-1.810;0.881,0.819;0.094,0.045;0.088,0.43;0.038,0.094;0.049,0.088");

    QBENCHMARK {
        arx.print();
    }

    QVERIFY2( arx.print() == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 1.952 y2( k - 1 )  - 0.881 y2( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 )  + 0.038 u2( k - 1 )  + 0.049 u2( k - 2 ) \n y2( k ) = 1.908 y1( k - 1 )  - 0.741 y1( k - 2 )  + 1.81 y2( k - 1 )  - 0.819 y2( k - 2 )  + 0.045 u1( k - 1 )  + 0.43 u1( k - 2 )  + 0.094 u2( k - 1 )  + 0.088 u2( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase6()
{
    ModelHandler::TransferFunction<double> TF("20","1,2,1");
    ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TF,0.1);
    std::string str = arx;
    QBENCHMARK {
        std::string str = arx;
    }

    QVERIFY2( str == " y1( k ) = 1.80967 y1( k - 1 )  - 0.818731 y1( k - 2 )  + 0.0935767 u1( k - 1 )  + 0.0875417 u1( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase7()
{
    ModelHandler::ARX<double> arx(2,2,0,2,1,0.1);
    arx.setModelCoef("-1.810;0.819;0.094;0.088;0.094;0.088");
    std::string str = arx;
    QBENCHMARK {
        std::string str = arx;
    }

    QVERIFY2( str == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 )  + 0.094 u2( k - 1 )  + 0.088 u2( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase8()
{
    ModelHandler::ARX<double> arx(2,2,0,1,2,0.1);
    arx.setModelCoef("-1.810,0;0.819,0;0,-1.810;0,0.819;0.094,0.094;0.088,0.094");
    std::string str = arx;
    QBENCHMARK {
        std::string str = arx;
    }

    QVERIFY2( str == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 ) \n y2( k ) = 1.81 y2( k - 1 )  - 0.819 y2( k - 2 )  + 0.094 u1( k - 1 )  + 0.094 u1( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase9()
{
    ModelHandler::ARX<double> arx(2,2,0,2,2,0.1);
    arx.setModelCoef("-1.810,0;0.819,0;0,-1.810;0,0.819;0.094,0;0.088,0;0,0.094;0,0.088");
    std::string str = arx;
    QBENCHMARK {
        std::string str = arx;
    }

    QVERIFY2( str == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 ) \n y2( k ) = 1.81 y2( k - 1 )  - 0.819 y2( k - 2 )  + 0.094 u2( k - 1 )  + 0.088 u2( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase10()
{
    ModelHandler::ARX<double> arx(2,2,0,2,2,0.1);
    arx.setModelCoef("-1.810,-1.908;0.819,0.741;-1.952,-1.810;0.881,0.819;0.094,0.045;0.088,0.43;0.038,0.094;0.049,0.088");
    std::string str = arx;
    QBENCHMARK {
        std::string str = arx;
    }

    QVERIFY2( str == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 1.952 y2( k - 1 )  - 0.881 y2( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 )  + 0.038 u2( k - 1 )  + 0.049 u2( k - 2 ) \n y2( k ) = 1.908 y1( k - 1 )  - 0.741 y1( k - 2 )  + 1.81 y2( k - 1 )  - 0.819 y2( k - 2 )  + 0.045 u1( k - 1 )  + 0.43 u1( k - 2 )  + 0.094 u2( k - 1 )  + 0.088 u2( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase11()
{
    ModelHandler::TransferFunction<double> TF("20","1,2,1");
    ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TF,0.1);
    std::string str;
    str << arx;
    QBENCHMARK {
        std::string str;
        str << arx;
    }

    QVERIFY2( str == " y1( k ) = 1.80967 y1( k - 1 )  - 0.818731 y1( k - 2 )  + 0.0935767 u1( k - 1 )  + 0.0875417 u1( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase12()
{
    ModelHandler::ARX<double> arx(2,2,0,2,1,0.1);
    arx.setModelCoef("-1.810;0.819;0.094;0.088;0.094;0.088");
    std::string str;
    str << arx;
    QBENCHMARK {
        std::string str;
        str << arx;
    }

    QVERIFY2( str == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 )  + 0.094 u2( k - 1 )  + 0.088 u2( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase13()
{
    ModelHandler::ARX<double> arx(2,2,0,1,2,0.1);
    arx.setModelCoef("-1.810,0;0.819,0;0,-1.810;0,0.819;0.094,0.094;0.088,0.094");
    std::string str;
    str << arx;
    QBENCHMARK {
        std::string str;
        str << arx;
    }

    QVERIFY2( str == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 ) \n y2( k ) = 1.81 y2( k - 1 )  - 0.819 y2( k - 2 )  + 0.094 u1( k - 1 )  + 0.094 u1( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase14()
{
    ModelHandler::ARX<double> arx(2,2,0,2,2,0.1);
    arx.setModelCoef("-1.810,0;0.819,0;0,-1.810;0,0.819;0.094,0;0.088,0;0,0.094;0,0.088");
    std::string str;
    str << arx;
    QBENCHMARK {
        std::string str;
        str << arx;
    }

    QVERIFY2( str == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 ) \n y2( k ) = 1.81 y2( k - 1 )  - 0.819 y2( k - 2 )  + 0.094 u2( k - 1 )  + 0.088 u2( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::stringConversionCase15()
{
    ModelHandler::ARX<double> arx(2,2,0,2,2,0.1);
    arx.setModelCoef("-1.810,-1.908;0.819,0.741;-1.952,-1.810;0.881,0.819;0.094,0.045;0.088,0.43;0.038,0.094;0.049,0.088");
    std::string str;
    str << arx;
    QBENCHMARK {
        std::string str;
        str << arx;
    }

    QVERIFY2( str == " y1( k ) = 1.81 y1( k - 1 )  - 0.819 y1( k - 2 )  + 1.952 y2( k - 1 )  - 0.881 y2( k - 2 )  + 0.094 u1( k - 1 )  + 0.088 u1( k - 2 )  + 0.038 u2( k - 1 )  + 0.049 u2( k - 2 ) \n y2( k ) = 1.908 y1( k - 1 )  - 0.741 y1( k - 2 )  + 1.81 y2( k - 1 )  - 0.819 y2( k - 2 )  + 0.045 u1( k - 1 )  + 0.43 u1( k - 2 )  + 0.094 u2( k - 1 )  + 0.088 u2( k - 2 ) \n", "Impressao do modelo ARX realizada de forma incorreta.");
}

void ArxDoubleTest::getNumberOfInputDelays()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    QBENCHMARK {
        arx.getNumberOfInputDelays();
    }

    QVERIFY2(arx.getNumberOfInputDelays() == 1, "O numero de atrasos nas entradas e diferente");
}

void ArxDoubleTest::getNumberOfInputs()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    QBENCHMARK {
        arx.getNumberOfInputs();
    }

    QVERIFY2(arx.getNumberOfInputs() == 3, "O numero de variaveis de entrada e diferente");
}

void ArxDoubleTest::getNumberOfOutputDelays()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    QBENCHMARK {
        arx.getNumberOfOutputDelays();
    }

    QVERIFY2(arx.getNumberOfOutputDelays() == 2, "O numero de atrasos nas saidas e diferente");
}

void ArxDoubleTest::getNumberOfOutputs()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    QBENCHMARK {
        arx.getNumberOfOutputs();
    }

    QVERIFY2(arx.getNumberOfOutputs() == 4, "O numero de variaveis de saida e diferente");
}

void ArxDoubleTest::getNumberOfVariables()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    QBENCHMARK {
        arx.getNumberOfVariables();
    }

    QVERIFY2(arx.getNumberOfVariables() == 11, "O numero de variaveis e diferente");
}

void ArxDoubleTest::getMaxnInOut ()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    QBENCHMARK {
        arx.getMaxnInOut();
    }

    QVERIFY2(arx.getMaxnInOut() == 2, "O numero de maximo de atrasos e diferente");
}

void ArxDoubleTest::getNSample ()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    QBENCHMARK {
        arx.getNSample();
    }

    QVERIFY2(arx.getNSample() == 3, "O numero de amostras e diferente");
}

void ArxDoubleTest::getSingleInput()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    arx.setIO(1,1);
    double value;
    QBENCHMARK {
        arx.getSingleInput();
    }

    QVERIFY2(arx.getSingleInput() == 1, "O valor das entradas e diferente");
}

void ArxDoubleTest::getSingleOutput()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    arx.setIO(1,1);
    double value;
    QBENCHMARK {
        value = arx.getSingleOutput();
    }

    QVERIFY2(arx.getSingleOutput() == 1, "O valor das saidas e diferente");
}

void ArxDoubleTest::getSingleEstOutput()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    arx.setIO(1,1);
    double value;
    QBENCHMARK {
        value = arx.getSingleEstOutput();
    }

    QVERIFY2(arx.getSingleEstOutput() == 1, "O valor das saidas estimadas e diferente");
}

void ArxDoubleTest::getLmin()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    arx.setLimits(1,1);
    double value;
    QBENCHMARK {
        value = arx.getLmin();
    }

    QVERIFY2(arx.getLmin() == 1, "O valor do limite minimo e diferente");
}

void ArxDoubleTest::getLmax()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    arx.setLimits(1,1);
    double value;
    QBENCHMARK {
        value = arx.getLmax();
    }

    QVERIFY2(arx.getLmax() == 1, "O valor do limite maximo e diferente");
}

void ArxDoubleTest::getStep()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    arx.setStep(0.5);
    double value;
    QBENCHMARK {
        value = arx.getStep();
    }

    QVERIFY2(arx.getStep() == 0.5, "O valor do passo de simulacao e diferente");
}

void ArxDoubleTest::getTimeSimulation()
{
    ModelHandler::ARX<double> arx(1,2,0,3,4,0.1);
    arx.setTimeSimulation(10);
    double value;
    QBENCHMARK {
        value = arx.getTimeSimulation();
    }

    QVERIFY2(arx.getTimeSimulation() == 10, "O tempo de simulacao e diferente");
}

void ArxDoubleTest::getTransportDelay()
{
    ModelHandler::ARX<double> arx(1,2,2,3,4,0.1);
    double value;
    QBENCHMARK {
        value = arx.getTransportDelay();
    }

    QVERIFY2(arx.getTransportDelay() == 2, "O valor dos atrasos de transporte e diferente");
}

void ArxDoubleTest::getInputMatrix()
{
    ModelHandler::ARX<double> arx(1,1,0,1,1,0.1);
    arx.setIO("1;1","1;1");
    QBENCHMARK {
        arx.getInputMatrix();
    }

    QVERIFY2(LinAlg::isEqual(arx.getInputMatrix(),LinAlg::Matrix<double>("1;1")), "O valor das entradas e diferente");
}

void ArxDoubleTest::getOutputMatrix()
{
    ModelHandler::ARX<double> arx(1,1,0,1,1,0.1);
    arx.setIO("1;1","1;2");
    QBENCHMARK {
        arx.getOutputMatrix();
    }

    QVERIFY2(LinAlg::isEqual(arx.getOutputMatrix(),LinAlg::Matrix<double>("1;2")), "O valor das saidas e diferente");
}

void ArxDoubleTest::getEstOutputMatrix()
{
    ModelHandler::ARX<double> arx(1,1,0,1,1,0.1);
    arx.setIO("1;1","1;2");
    QBENCHMARK {
        arx.getEstOutputMatrix();
    }

    QVERIFY2(LinAlg::isEqual(arx.getEstOutputMatrix(),LinAlg::Matrix<double>("1;2")), "O valor das saidas estimadas e diferente");
}

void ArxDoubleTest::getModelCoef()
{
    ModelHandler::ARX<double> arx(1,1,0,1,1,0.1);
    arx.setModelCoef("0.982;0.045");
    QBENCHMARK {
        arx.getModelCoef();
    }

    QVERIFY2(LinAlg::isEqual(arx.getModelCoef(),LinAlg::Matrix<double>("0.982;0.045")), "O valor dos coeficientes do modelo e diferente");
//    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityVectorB(),arx2.getLinearEqualityVectorB()), "O valor dos elementos de B no vetor do sistema linear e diferente");
//    QVERIFY2(LinAlg::isEqual(arx.getLinearMatrixA(),arx2.getLinearMatrixA()), "O valor dos elementos de A na Matrix do sistema linear e diferente");
//    QVERIFY2(LinAlg::isEqual(arx.getLinearVectorA(),arx2.getLinearVectorA()), "O valor dos elementos de A no vetor do sistema linear e diferente");
//    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityB(),arx2.getLinearEqualityB()), "O valor dos elementos de B na Matrix do sistema linear e diferente");
//    QVERIFY2(LinAlg::isEqual(arx.getInputLinearVector(),arx2.getInputLinearVector()), "O vetor de estados da entrada e diferente");
//    QVERIFY2(LinAlg::isEqual(arx.getOutputLinearVector(),arx2.getOutputLinearVector()), "O vetor de estados da saida e diferente");
}

void ArxDoubleTest::getLinearSystem()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    ModelHandler::ARX<double> arx(2,2);
    OptimizationHandler::LeastSquare<double> LS(&arx);
    LS.Optimize(U,Y);
    LinAlg::Matrix<double> A, b;
    LinAlg::Matrix<double> Acorreto = "-0,     -0,  0.430,      0; -0.020,     -0,  0.430,  0.430; -0.075, -0.020,  0.430,  0.430; -0.159, -0.075,  0.430,  0.430; -0.265, -0.159,  0.430,  0.430; -0.388, -0.265,  0.430,  0.430; -0.524, -0.388,  0.430,  0.430; -0.670, -0.524,  0.430,  0.430; -0.822, -0.670,  0.430,  0.430", bCorreto = "0.020;  0.075;  0.159;  0.265;  0.388;  0.524;  0.670;  0.822;  0.978";

    QBENCHMARK {
        *(A,b) = arx.getLinearSystem();
    }

    QVERIFY2(LinAlg::isEqual(A,Acorreto,0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
    QVERIFY2(LinAlg::isEqual(b,bCorreto,0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
}

void ArxDoubleTest::getLinearMatrixA()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    ModelHandler::ARX<double> arx(2,2);
    OptimizationHandler::LeastSquare<double> LS(&arx);
    LS.Optimize(U,Y);
    LinAlg::Matrix<double> A;
    LinAlg::Matrix<double> Acorreto = "-0,     -0,  0.430,      0; -0.020,     -0,  0.430,  0.430; -0.075, -0.020,  0.430,  0.430; -0.159, -0.075,  0.430,  0.430; -0.265, -0.159,  0.430,  0.430; -0.388, -0.265,  0.430,  0.430; -0.524, -0.388,  0.430,  0.430; -0.670, -0.524,  0.430,  0.430; -0.822, -0.670,  0.430,  0.430";

    QBENCHMARK {
        A = arx.getLinearMatrixA();
    }

    QVERIFY2(LinAlg::isEqual(A,Acorreto,0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
}

void ArxDoubleTest::getLinearEqualityB()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    ModelHandler::ARX<double> arx(2,2);
    OptimizationHandler::LeastSquare<double> LS(&arx);
    LS.Optimize(U,Y);
    LinAlg::Matrix<double> b;
    LinAlg::Matrix<double> bCorreto = "0.020;  0.075;  0.159;  0.265;  0.388;  0.524;  0.670;  0.822;  0.978";

    QBENCHMARK {
        b = arx.getLinearEqualityB();
    }

    QVERIFY2(LinAlg::isEqual(b,bCorreto,0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
}

void ArxDoubleTest::getLinearVectorA()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    ModelHandler::ARX<double> arx(2,2);
    OptimizationHandler::RecursiveLeastSquare<double> RLS(&arx,1e6);

    QBENCHMARK {
        arx.getLinearVectorA();
    }

    LinAlg::Matrix<double> Acorreto = "-0,     -0,  0.430,      0; -0.020,     -0,  0.430,  0.430; -0.075, -0.020,  0.430,  0.430; -0.159, -0.075,  0.430,  0.430; -0.265, -0.159,  0.430,  0.430; -0.388, -0.265,  0.430,  0.430; -0.524, -0.388,  0.430,  0.430; -0.670, -0.524,  0.430,  0.430; -0.822, -0.670,  0.430,  0.430";

    for(unsigned i = 0; i < 9; ++i)
    {
        RLS.Optimize(U(0,i),Y(0,i+1));
        QVERIFY2(LinAlg::isEqual(arx.getLinearVectorA(),Acorreto.getRow(i),0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
    }
}

void ArxDoubleTest::getLinearEqualityVectorB()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    ModelHandler::ARX<double> arx(2,2);
    OptimizationHandler::RecursiveLeastSquare<double> RLS(&arx,1e6);

    QBENCHMARK {
        arx.getLinearEqualityVectorB();
    }

    LinAlg::Matrix<double> bCorreto = "0; 0.020;  0.075;  0.159;  0.265;  0.388;  0.524;  0.670;  0.822;  0.978";

    for(unsigned i = 0; i < 9; ++i)
    {
        RLS.Optimize(U(0,i),Y(0,i+1));
        QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityVectorB(),bCorreto.getRow(i),0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
    }

}

void ArxDoubleTest::getInputLinearVector()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    ModelHandler::ARX<double> arx(2,2);
    OptimizationHandler::RecursiveLeastSquare<double> RLS(&arx,1e6);

    QBENCHMARK {
        arx.getInputLinearVector();
    }

    LinAlg::Matrix<double> Acorreto = "-0,     -0,  0.430,      0; -0.020,     -0,  0.430,  0.430; -0.075, -0.020,  0.430,  0.430; -0.159, -0.075,  0.430,  0.430; -0.265, -0.159,  0.430,  0.430; -0.388, -0.265,  0.430,  0.430; -0.524, -0.388,  0.430,  0.430; -0.670, -0.524,  0.430,  0.430; -0.822, -0.670,  0.430,  0.430";

    for(unsigned i = 0; i < 9; ++i)
    {
        RLS.Optimize(U(0,i),Y(0,i+1));
//        std::cout << (arx.getInputLinearVector()|-Acorreto(i,from(3)-->4)) << std::endl;
        QVERIFY2(LinAlg::isEqual(arx.getInputLinearVector(),Acorreto(i,from(2)-->3),0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
    }

}

void ArxDoubleTest::getOutputLinearVector()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    ModelHandler::ARX<double> arx(2,2);
    OptimizationHandler::RecursiveLeastSquare<double> RLS(&arx,1e6);

    QBENCHMARK {
        arx.getOutputLinearVector();
    }

    LinAlg::Matrix<double> Acorreto = "-0,     -0,  0.430,      0; -0.020,     -0,  0.430,  0.430; -0.075, -0.020,  0.430,  0.430; -0.159, -0.075,  0.430,  0.430; -0.265, -0.159,  0.430,  0.430; -0.388, -0.265,  0.430,  0.430; -0.524, -0.388,  0.430,  0.430; -0.670, -0.524,  0.430,  0.430; -0.822, -0.670,  0.430,  0.430";

    for(unsigned i = 0; i < 9; ++i)
    {
        RLS.Optimize(U(0,i),Y(0,i+1));
//        std::cout << (arx.getOutputLinearVector()|Acorreto(i,from(1)-->2)) << std::endl;
        QVERIFY2(LinAlg::isEqual(arx.getOutputLinearVector(),-Acorreto(i,from(0)-->1),0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
    }

}

void ArxDoubleTest::setLinearModel()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y    = TFd.sim(U);
    LinAlg::Matrix<double> Acorreto = "-0,     -0,  0.430,      0; -0.020,     -0,  0.430,  0.430; -0.075, -0.020,  0.430,  0.430; -0.159, -0.075,  0.430,  0.430; -0.265, -0.159,  0.430,  0.430; -0.388, -0.265,  0.430,  0.430; -0.524, -0.388,  0.430,  0.430; -0.670, -0.524,  0.430,  0.430; -0.822, -0.670,  0.430,  0.430", bCorreto = "0.020;  0.075;  0.159;  0.265;  0.388;  0.524;  0.670;  0.822;  0.978";

    QBENCHMARK {
        ModelHandler::ARX<double> arx(2,2);
        arx.setLinearModel(U,Y);
    }

    ModelHandler::ARX<double> arx(2,2);
    arx.setLinearModel(U,Y);

    QVERIFY2(LinAlg::isEqual(arx.getLinearMatrixA(),Acorreto,0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
    QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityB(),bCorreto,0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
}

void ArxDoubleTest::setLinearVector()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    QBENCHMARK {
        ModelHandler::ARX<double> arx(2,2);
        arx.setLinearVector(U.getRow(0),Y.getRow(0));
    }
    LinAlg::Matrix<double> Acorreto = "-0,     -0,  0.430,      0; -0.020,     -0,  0.430,  0.430; -0.075, -0.020,  0.430,  0.430; -0.159, -0.075,  0.430,  0.430; -0.265, -0.159,  0.430,  0.430; -0.388, -0.265,  0.430,  0.430; -0.524, -0.388,  0.430,  0.430; -0.670, -0.524,  0.430,  0.430; -0.822, -0.670,  0.430,  0.430", bCorreto = "0;0.020;  0.075;  0.159;  0.265;  0.388;  0.524;  0.670;  0.822;  0.978";

    ModelHandler::ARX<double> arx(2,2);
    for(unsigned i = 0; i < 9; ++i)
    {
        arx.setLinearVector(U.getColumn(i),Y.getColumn(i));
        QVERIFY2(LinAlg::isEqual(arx.getLinearVectorA(),Acorreto.getRow(i),0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
        QVERIFY2(LinAlg::isEqual(arx.getLinearEqualityVectorB(),bCorreto.getRow(i),0.01), "O valor dos elementos de A na matriz do sistema linear e diferente");
    }
}

void ArxDoubleTest::simInScalar()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    QBENCHMARK {
        ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TFd,0.1);
        double Y2;
        for(unsigned i = 0; i < U.getNumberOfColumns(); ++i)
            Y2 = arx.sim(U(0,i));
    }

    ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TFd,0.1);
    double Y2;
    for(unsigned i = 0; i < U.getNumberOfColumns(); ++i)
    {
        Y2 = arx.sim(U(0,i));
        QVERIFY2(fabs(Y(0,i+1)-Y2) < 0.01, "O resultado das simulacoes e diferente");
    }
}

void ArxDoubleTest::simInOutScalar()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    QBENCHMARK {
        ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TFd,0.1);
        double Y2;
        for(unsigned i = 0; i < U.getNumberOfColumns(); ++i)
            Y2 = arx.sim(U(0,i),Y(0,i));
    }

    ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TFd,0.1);
    double Y2;
    for(unsigned i = 0; i < U.getNumberOfColumns(); ++i)
    {
        Y2 = arx.sim(U(0,i),Y(0,i));
        QVERIFY2(fabs(Y(0,i+1)-Y2) < 0.01, "O resultado das simulacoes e diferente");
    }
}

void ArxDoubleTest::simInMatrix()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U),Y2;

    QBENCHMARK {
        LinAlg::Matrix<double> Y2;
        ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TFd,0.1);
        Y2 = arx.sim(U);
    }

    ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TFd,0.1);
    Y2 = arx.sim(U);
    //std::cout << (~Y|~Y2) << std::endl;
    QVERIFY2(LinAlg::isEqual(Y,Y2,0.01), "O resultado das simulacoes e diferente");
}

void ArxDoubleTest::simInOutMatrix()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U),Y2;

    QBENCHMARK {
        LinAlg::Matrix<double> Y2;
        ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TFd,0.1);
        Y2 = arx.sim(U,Y);
    }

    ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TFd,0.1);
    Y2 = arx.sim(U,Y);
    QVERIFY2(LinAlg::isEqual(Y,Y2, 0.01), "O resultado das simulacoes e diferente");
}

void ArxDoubleTest::setInitialOutputValue()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(TFd,0.1);

    QBENCHMARK {
        arx.setInitialOutputValue(1.0);
    }

    QVERIFY2(arx.getOutputLinearVector()(0,0)-1 < 0.01, "O resultado das simulacoes e diferente");
}

QTEST_APPLESS_MAIN(ArxDoubleTest)

#include "tst_arxdoubletest.moc"
