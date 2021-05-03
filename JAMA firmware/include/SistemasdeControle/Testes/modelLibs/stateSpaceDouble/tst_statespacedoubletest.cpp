#include <QString>
#include <QtTest>
#define testPolynom
#define testModel
#include "../../../headers/primitiveLibs/LinAlg/matrix.h"
#include "../../../headers/primitiveLibs/polynom.h"
#include "../../../headers/modelLibs/transferfunction.h"
#include "../../../headers/modelLibs/arx.h"
#include "../../../headers/modelLibs/conversions.h"

class StateSpaceDoubleTest : public QObject
{
    Q_OBJECT

public:
    StateSpaceDoubleTest(){}

private Q_SLOTS:
    void SSVoidConstructorDouble ();
    void SSContinuousConstructorDouble ();
    void SSDiscreteConstructorDouble ();
    void copyConstructorDouble ();
    void copyAssignmentDouble ();
    void copyAssignmentOtherType ();
    void stringConversion();
    void getSampleTime();
    void getTimeSimulation();
    void getnDiscretizationParameter();
    void getA();
    void getB();
    void getC();
    void getD();
    void getContinuousParameters();
    void getDiscreteParameters();
    void getActualState();
    void getObserverParameters();//ok
    void getContinuousObserverParametersByAckerman();
    void setA();
    void setB();
    void setC();
    void setD();
    void setContinuous();
    void setSampleTime();
    void setInitialState();
    void setObserverParameters();
    void isContinuous();
    void isObservableCase1();
    void isObservableCase2();
    void isControlableCase1();
    void isControlableCase2();
    void ObserverLoop();
    void simScalar(); //ok
    void simMatrix(); //ok
    void c2dConversion(); //ok
    void d2cConversion();
    void print(); //ok
    void bufferString();

    void getNDiscretizationValue();
    void getMinPredictionHorizon();
    void getMaxPredictionHorizon();
    void getControlHorizon();
    void setNDiscretizationValue();
    void setMinPredictionHorizon();
    void setMaxPredictionHorizon();
    void setControlHorizon();



    void simScalarInOut() {QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
    void simMatrixInOut(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
    void simRange(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
    void getNumberOfVariables(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
    void getNumberOfInputs(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
    void getNumberOfOutputs(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
    void setLinearModel(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
    void setLinearVector(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
    void getKalmanFilterParameters(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
    void KalmanFilterObserver(){QSKIP("Função não implementada. Por enquanto não há necessidade", SkipAll);}
};

void StateSpaceDoubleTest::SSVoidConstructorDouble ()
{
    ModelHandler::StateSpace<double> A;
    QBENCHMARK {
        ModelHandler::StateSpace<double> A;
    }
    QVERIFY2(A.getTimeSimulation() == 10, "Falhou ao comparar o tempo de simulacao.");
    QVERIFY2(A.isContinuous() && A.getSampleTime() == 0.1, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
    QVERIFY2(sizeof(A) == sizeof(ModelHandler::StateSpace<double>), "Falhou ao comparar o tipo da equacao de estados");
}

void StateSpaceDoubleTest::SSContinuousConstructorDouble()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        ModelHandler::StateSpace<double> SS(A,B,C,D);
    }
    QVERIFY2(SS.getTimeSimulation() == 10, "Falhou ao comparar o tempo de simulacao.");
    QVERIFY2(SS.isContinuous() && SS.getSampleTime() == 0.1, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
    QVERIFY2(SS.getA()(0,0) == 0 && SS.getA()(0,1) == 1 && SS.getA()(1,0) == -1 && SS.getA()(1,1) == -2 , "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getB()(0,0) == 0) & (SS.getB()(1,0) == 1), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getC()(0,0) == 1) & (SS.getC()(0,1) == 0), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getD()(0,0) == 0, "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getActualState()(0,0) == 0 && SS.getActualState()(1,0) == 0, "Falhou ao verificar a matriz de estados");
    QVERIFY2(sizeof(SS) == sizeof(ModelHandler::StateSpace<double>), "Falhou ao comparar o tipo da equacao de estados");
}

void StateSpaceDoubleTest::SSDiscreteConstructorDouble()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D,0.2);
    QBENCHMARK {
        ModelHandler::StateSpace<double> SS(A,B,C,D,0.2);
    }
    QVERIFY2(SS.getTimeSimulation() == 10, "Falhou ao comparar o tempo de simulacao.");
    QVERIFY2(!SS.isContinuous() && SS.getSampleTime() == 0.2, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
    QVERIFY2(SS.getA()(0,0) == 0 && SS.getA()(0,1) == 1 && SS.getA()(1,0) == -1 && SS.getA()(1,1) == -2 , "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getB()(0,0) == 0) & (SS.getB()(1,0) == 1), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getC()(0,0) == 1) & (SS.getC()(0,1) == 0), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getD()(0,0) == 0, "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getActualState()(0,0) == 0 && SS.getActualState()(1,0) == 0, "Falhou ao verificar a matriz de estados");
    QVERIFY2(sizeof(SS) == sizeof(ModelHandler::StateSpace<double>), "Falhou ao comparar o tipo da equacao de estados");
}

void StateSpaceDoubleTest::copyConstructorDouble ()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<long double> SS2(A,B,C,D);
    ModelHandler::StateSpace<double> SS(SS2);
    QBENCHMARK {
        ModelHandler::StateSpace<double> SS(SS2);
    }
    QVERIFY2(SS.getTimeSimulation() == 10, "Falhou ao comparar o tempo de simulacao.");
    QVERIFY2(SS.isContinuous() && SS.getSampleTime() == 0.1, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
    QVERIFY2(SS.getA()(0,0) == 0 && SS.getA()(0,1) == 1 && SS.getA()(1,0) == -1 && SS.getA()(1,1) == -2 , "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getB()(0,0) == 0) & (SS.getB()(1,0) == 1), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getC()(0,0) == 1) & (SS.getC()(0,1) == 0), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getD()(0,0) == 0, "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getActualState()(0,0) == 0 && SS.getActualState()(1,0) == 0, "Falhou ao verificar a matriz de estados");
    QVERIFY2(sizeof(SS) == sizeof(ModelHandler::StateSpace<double>), "Falhou ao comparar o tipo da equacao de estados");
}

void StateSpaceDoubleTest::copyAssignmentDouble ()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS2(A,B,C,D);
    ModelHandler::StateSpace<double> SS = SS2;
    QBENCHMARK {
        ModelHandler::StateSpace<double> SS = SS2;
    }
    QVERIFY2(SS.getTimeSimulation() == 10, "Falhou ao comparar o tempo de simulacao.");
    QVERIFY2(SS.isContinuous() && SS.getSampleTime() == 0.1, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
    QVERIFY2(SS.getA()(0,0) == 0 && SS.getA()(0,1) == 1 && SS.getA()(1,0) == -1 && SS.getA()(1,1) == -2 , "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getB()(0,0) == 0) & (SS.getB()(1,0) == 1), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getC()(0,0) == 1) & (SS.getC()(0,1) == 0), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getD()(0,0) == 0, "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getActualState()(0,0) == 0 && SS.getActualState()(1,0) == 0, "Falhou ao verificar a matriz de estados");
    QVERIFY2(sizeof(SS) == sizeof(ModelHandler::StateSpace<double>), "Falhou ao comparar o tipo da equacao de estados");
}

void StateSpaceDoubleTest::copyAssignmentOtherType ()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<long double> SS2(A,B,C,D);
    ModelHandler::StateSpace<double> SS = SS2;
    QBENCHMARK {
        ModelHandler::StateSpace<double> SS = SS2;
    }
    QVERIFY2(SS.getTimeSimulation() == 10, "Falhou ao comparar o tempo de simulacao.");
    QVERIFY2(SS.isContinuous() && SS.getSampleTime() == 0.1, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
    QVERIFY2(SS.getA()(0,0) == 0 && SS.getA()(0,1) == 1 && SS.getA()(1,0) == -1 && SS.getA()(1,1) == -2 , "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getB()(0,0) == 0) & (SS.getB()(1,0) == 1), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((SS.getC()(0,0) == 1) & (SS.getC()(0,1) == 0), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getD()(0,0) == 0, "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(SS.getActualState()(0,0) == 0 && SS.getActualState()(1,0) == 0, "Falhou ao verificar a matriz de estados");
    QVERIFY2(sizeof(SS) == sizeof(ModelHandler::StateSpace<double>), "Falhou ao comparar o tipo da equacao de estados");
}

void StateSpaceDoubleTest::getSampleTime()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D,0.2);
    QBENCHMARK {
        SS.getSampleTime();
    }
    QVERIFY2(!SS.isContinuous() && SS.getSampleTime() == 0.2, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
}

void StateSpaceDoubleTest::getTimeSimulation()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D,0.2);
    QBENCHMARK {
        SS.getTimeSimulation();
    }
    QVERIFY2(SS.getTimeSimulation() == 10, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
}

void StateSpaceDoubleTest::getnDiscretizationParameter()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D,0.2);
    QBENCHMARK {
        SS.getnDiscretizationParameter();
    }
    QVERIFY2(SS.getnDiscretizationParameter() == 6, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
}

void StateSpaceDoubleTest::getA()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.getA();
    }
    QVERIFY2(SS.getA()(0,0) == 0 && SS.getA()(0,1) == 1 && SS.getA()(1,0) == -1 && SS.getA()(1,1) == -2 , "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::getB()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.getB();
    }
    QVERIFY2((SS.getB()(0,0) == 0) & (SS.getB()(1,0) == 1), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::getC()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.getC();
    }
    QVERIFY2((SS.getC()(0,0) == 1) & (SS.getC()(0,1) == 0), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::getD()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.getD();
    }
    QVERIFY2(SS.getD()(0,0) == 0, "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::getContinuousParameters()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    LinAlg::Matrix<double> As, Bs, Cs, Ds;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        *(As,Bs,Cs,Ds) = SS.getContinuousParameters();
    }
    QVERIFY2(As(0,0) == 0 && As(0,1) == 1 && As(1,0) == -1 && As(1,1) == -2 , "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((Bs(0,0) == 0) & (Bs(1,0) == 1), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((Cs(0,0) == 1) & (Cs(0,1) == 0), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(Ds(0,0) == 0, "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::getDiscreteParameters()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    LinAlg::Matrix<double> As, Bs, Cs, Ds;
    ModelHandler::StateSpace<double> SS(A,B,C,D,0.1);
    QBENCHMARK {
        *(As,Bs,Cs,Ds) = SS.getDiscreteParameters();
    }
    QVERIFY2(As(0,0) == 0 && As(0,1) == 1 && As(1,0) == -1 && As(1,1) == -2 , "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((Bs(0,0) == 0) & (Bs(1,0) == 1), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2((Cs(0,0) == 1) & (Cs(0,1) == 0), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
    QVERIFY2(Ds(0,0) == 0, "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::getActualState()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.getActualState();
    }
    QVERIFY2(SS.getActualState()(0,0) == 0 && SS.getActualState()(1,0) == 0, "Falhou ao verificar a matriz de estados");
}

void StateSpaceDoubleTest::getObserverParameters()
{
    LinAlg::Matrix<double> A = "-2,0;0,-1", B = "2;1", C = "3,0", D = 0.0, L;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setObserverParameters("1;2");
    QBENCHMARK {
        L = SS.getObserverParameters();
    }
    QVERIFY2(SS.getObserverParameters()(0,0) == 1 && SS.getObserverParameters()(1,0) == 2, "Falhou ao verificar a controlabilidade do sistema");
}

void StateSpaceDoubleTest::getContinuousObserverParametersByAckerman()
{
    LinAlg::Matrix<double> A = "-1,1;1,-2", B = "1;0", C = "1,0", D = 0.0, L;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        L = SS.getContinuousObserverParametersByAckerman("1,11,30");
    }
    L = SS.getContinuousObserverParametersByAckerman("1,11,30");
    QVERIFY2(L (0,0) == 8 && L(1,0) == 13, "Falhou ao verificar os parametros do observador");
}

void StateSpaceDoubleTest::setA()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.setA("1,2;-2,-3");
    }
    QVERIFY2(SS.getA()(0,0) == 1 && SS.getA()(0,1) == 2 && SS.getA()(1,0) == -2 && SS.getA()(1,1) == -3 , "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::setB()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.setB("1;0");
    }
    QVERIFY2((SS.getB()(0,0) == 1) & (SS.getB()(1,0) == 0), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::setC()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.setC("0,1");
    }
    QVERIFY2((SS.getC()(0,0) == 0) & (SS.getC()(0,1) == 1), "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::setD()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.setD(1.0);
    }
    QVERIFY2(SS.getD()(0,0) == 1, "Falhou ao verificar as matrizes dos sistema em espaco de estados");
}

void StateSpaceDoubleTest::setContinuous()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.setContinuous(false);
    }
    QVERIFY2(!SS.isContinuous() && SS.getSampleTime() == 0.1, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
}

void StateSpaceDoubleTest::setSampleTime()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.setSampleTime(0.2);
    }
    QVERIFY2(SS.isContinuous() && SS.getSampleTime() == 0.2, "Falhou ao verificar que a função e continua e ao verificar o periodo de amostragem");
}

void StateSpaceDoubleTest::setInitialState()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.setInitialState("1;2");
    }
    QVERIFY2(SS.getActualState()(0,0) == 1 && SS.getActualState()(1,0) == 2, "Falhou ao verificar a matriz de estados");
}

void StateSpaceDoubleTest::isContinuous()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.isContinuous();
    }
    QVERIFY2(SS.isContinuous() , "Falhou ao verificar se o sistema e continuo");
}

void StateSpaceDoubleTest::isObservableCase1()
{
    LinAlg::Matrix<double> A = "-2,0;0,-1", B = "2;1", C = "3,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.isObservable();
    }
    QVERIFY2(!SS.isObservable() , "Falhou ao verificar a observabilidade do sistema");
}

void StateSpaceDoubleTest::isObservableCase2()
{
    LinAlg::Matrix<double> A = "-2,0;0,-1", B = "2;0", C = "3,2", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.isObservable();
    }
    QVERIFY2(SS.isObservable() , "Falhou ao verificar a observabilidade do sistema");
}

void StateSpaceDoubleTest::isControlableCase1()
{
    LinAlg::Matrix<double> A = "-2,0;0,-1", B = "2;1", C = "3,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.isControlable();
    }
    QVERIFY2(SS.isControlable(), "Falhou ao verificar a controlabilidade do sistema");
}

void StateSpaceDoubleTest::isControlableCase2()
{
    LinAlg::Matrix<double> A = "-2,0;0,-1", B = "2;0", C = "3,2", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.isControlable();
    }
    QVERIFY2(!SS.isControlable(), "Falhou ao verificar a controlabilidade do sistema");
}

void StateSpaceDoubleTest::ObserverLoop()
{
    LinAlg::Matrix<double> A = "-1,1;1,-2", B = "1;0", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    ModelHandler::StateSpace<double> SS2 = SS;
    SS2.getContinuousObserverParametersByAckerman("1,11,30");
    double Y;
    QBENCHMARK {
        SS.setInitialState("1;0");
        SS2.setInitialState("0;0");

        for(unsigned i = 0; i < 50; ++i)
        {
            Y = SS.sim(1.0);
            SS2.ObserverLoop(1.0,Y);
        }
    }
    QVERIFY2( fabs(SS.getActualState()(0,0) - SS2.getActualState()(0,0)) < 0.001 && fabs(SS.getActualState()(1,0) - SS2.getActualState()(1,0)) < 0.001, "Falhou ao verificar os valores de simulação do sistema.");
}

void StateSpaceDoubleTest::simScalar()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    LinAlg::Matrix<double> Y;
    QBENCHMARK {
        SS.setInitialState("0;0");
        Y = LinAlg::Matrix<double>(SS.sim(1.0));
        for(unsigned i = 0; i < 10; ++i)
        {
            Y = Y|SS.sim(1.0);
        }
    }

    QVERIFY2( fabs(Y(0,0) - 0) < 0.001 && fabs(Y(0,1) - 0.0047) < 0.001 &&
              fabs(Y(0,2) - 0.0175) < 0.001 && fabs(Y(0,3) - 0.0369) < 0.001 &&
              fabs(Y(0,4) - 0.0616) < 0.001 && fabs(Y(0,5) - 0.0902) < 0.001 &&
              fabs(Y(0,6) - 0.1219) < 0.001 && fabs(Y(0,7) - 0.1558) < 0.001 &&
              fabs(Y(0,8) - 0.1912) < 0.001 && fabs(Y(0,9) - 0.2275) < 0.001 && fabs(Y(0,10) - 0.2642) < 0.001, "Falhou ao verificar os valores de simulação do sistema.");
}

void StateSpaceDoubleTest::simMatrix()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    LinAlg::Matrix<double> Y;
    QBENCHMARK {
        SS.setInitialState("0;0");
        Y = SS.sim("1,1,1,1,1,1,1,1,1,1,1");
    }

    QVERIFY2( fabs(Y(0,0) - 0) < 0.001 && fabs(Y(0,1) - 0.0047) < 0.001 &&
              fabs(Y(0,2) - 0.0175) < 0.001 && fabs(Y(0,3) - 0.0369) < 0.001 &&
              fabs(Y(0,4) - 0.0616) < 0.001 && fabs(Y(0,5) - 0.0902) < 0.001 &&
              fabs(Y(0,6) - 0.1219) < 0.001 && fabs(Y(0,7) - 0.1558) < 0.001 &&
              fabs(Y(0,8) - 0.1912) < 0.001 && fabs(Y(0,9) - 0.2275) < 0.001 && fabs(Y(0,10) - 0.2642) < 0.001, "Falhou ao verificar os valores de simulação do sistema.");
}

void StateSpaceDoubleTest::c2dConversion()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setContinuous(false);
    SS.c2dConversion();
    QBENCHMARK {
        ModelHandler::StateSpace<double> SS(A,B,C,D);
        SS.setContinuous(false);
        SS.c2dConversion();
    }

//    std::cout << SS << std::endl;
    QVERIFY2( fabs(SS.getA()(0,0) - 0.995) < 0.001 && fabs(SS.getA()(0,1) - 0.090) < 0.001 &&
              fabs(SS.getA()(1,0) - (-0.09)) < 0.001 && fabs(SS.getA()(1,1) - 0.814) < 0.001, "Falhou ao verificar a matriz discreta");
    QVERIFY2( fabs(SS.getB()(0,0) - 0.005) < 0.001 && fabs(SS.getB()(1,0) - 0.090) < 0.001, "Falhou ao verificar a matriz discreta");
}

void StateSpaceDoubleTest::d2cConversion()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.c2dConversion();
    SS.d2cConversion();
    QBENCHMARK {
        ModelHandler::StateSpace<double> SS(A,B,C,D);
        SS.c2dConversion();
        SS.d2cConversion();
    }

    QVERIFY2( fabs(SS.getA()(0,0) - 0) < 0.2 && fabs(SS.getA()(0,1) - 1) < 0.2 &&
              fabs(SS.getA()(1,0) - (-1)) < 0.2 && fabs(SS.getA()(1,1) - (-2)) < 0.2, "Falhou ao verificar a matriz discreta");
    QVERIFY2( fabs(SS.getB()(0,0) - 0) < 0.2 && fabs(SS.getB()(1,0) - 1) < 0.2, "Falhou ao verificar a matriz discreta");
}

void StateSpaceDoubleTest::print()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    std::string str;
    QBENCHMARK {
        str = SS.print();
    }

    QVERIFY2( str == "The Continuous State Space Model is: \n\nA = \n      0   1.000 \n -1.000  -2.000 \n\n\nB = \n      0 \n  1.000 \n\n\nC = \n  1.000       0 \n\n\nD = \n      0 \n\n", "Falhou ao verificar se o sistema e continuo");
}

void StateSpaceDoubleTest::bufferString()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    std::string str;
    str << SS;
    QBENCHMARK {
        std::string str;
        str << SS;
    }

    QVERIFY2( str == "The Continuous State Space Model is: \n\nA = \n      0   1.000 \n -1.000  -2.000 \n\n\nB = \n      0 \n  1.000 \n\n\nC = \n  1.000       0 \n\n\nD = \n      0 \n\n", "Falhou ao verificar se o sistema e continuo");
}

void StateSpaceDoubleTest::getNDiscretizationValue()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setNDiscretizationValue(6);

    QBENCHMARK {
        SS.getNDiscretizationValue();
    }

    QVERIFY2( SS.getNDiscretizationValue() == 6, "O valor de discretização esta errado.");
}

void StateSpaceDoubleTest::getMinPredictionHorizon()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setMinPredictionHorizon(0);

    QBENCHMARK {
        SS.getMinPredictionHorizon();
    }

    QVERIFY2( SS.getMinPredictionHorizon() == 0, "O minimo horizonte de predicao esta errado.");
}

void StateSpaceDoubleTest::getMaxPredictionHorizon()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setMaxPredictionHorizon(10);

    QBENCHMARK {
        SS.getMaxPredictionHorizon();
    }

    QVERIFY2( SS.getMaxPredictionHorizon() == 10, "O maximo horizonte de predicao esta errado.");
}

void StateSpaceDoubleTest::getControlHorizon()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setControlHorizon(4);

    QBENCHMARK {
        SS.getControlHorizon();
    }

    QVERIFY2( SS.getControlHorizon() == 4, "O horizonte de controle esta errado.");
}

void StateSpaceDoubleTest::setNDiscretizationValue()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setNDiscretizationValue(6);

    QBENCHMARK {
        SS.setNDiscretizationValue(6);
    }

    QVERIFY2( SS.getNDiscretizationValue() == 6, "O valor de discretização esta errado.");
}

void StateSpaceDoubleTest::setMinPredictionHorizon()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setMinPredictionHorizon(0);

    QBENCHMARK {
        SS.setMinPredictionHorizon(0);
    }

    QVERIFY2( SS.getMinPredictionHorizon() == 0, "O minimo horizonte de predicao esta errado.");
}

void StateSpaceDoubleTest::setMaxPredictionHorizon()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setMaxPredictionHorizon(10);

    QBENCHMARK {
        SS.setMaxPredictionHorizon(10);
    }

    QVERIFY2( SS.getMaxPredictionHorizon() == 10, "O maximo horizonte de predicao esta errado.");
}

void StateSpaceDoubleTest::setControlHorizon()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    SS.setControlHorizon(4);

    QBENCHMARK {
        SS.setControlHorizon(4);
    }

    QVERIFY2( SS.getControlHorizon() == 4, "O horizonte de controle esta errado.");
}

void StateSpaceDoubleTest::stringConversion()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    std::string str = SS;
    QBENCHMARK {
        std::string str = SS;
    }

    QVERIFY2( str == "The Continuous State Space Model is: \n\nA = \n      0   1.000 \n -1.000  -2.000 \n\n\nB = \n      0 \n  1.000 \n\n\nC = \n  1.000       0 \n\n\nD = \n      0 \n\n", "Falhou ao verificar se o sistema e continuo");
}

void StateSpaceDoubleTest::setObserverParameters()
{
    LinAlg::Matrix<double> A = "-2,0;0,-1", B = "2;1", C = "3,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    QBENCHMARK {
        SS.setObserverParameters("1;2");
    }
    QVERIFY2(SS.getObserverParameters()(0,0) == 1 && SS.getObserverParameters()(1,0) == 2, "Falhou ao verificar a controlabilidade do sistema");
}

QTEST_APPLESS_MAIN(StateSpaceDoubleTest)

#include "tst_statespacedoubletest.moc"







