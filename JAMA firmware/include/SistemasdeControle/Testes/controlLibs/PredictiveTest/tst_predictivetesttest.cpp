#include <QString>
#include <QtTest>

#define testPolynom
#define testModel
#define testControl
#include "../../../headers/primitiveLibs/LinAlg/matrix.h"
#include "../../../headers/primitiveLibs/polynom.h"
#include "../../../headers/modelLibs/transferfunction.h"
#include "../../../headers/modelLibs/arx.h"
#include "../../../headers/modelLibs/conversions.h"
#include "../../../headers/controlLibs/modelpredictivecontrol.h"


class PredictiveTestTest : public QObject
{
    Q_OBJECT

public:
    PredictiveTestTest(){}

private Q_SLOTS:
    void ModelPredictiveControlConstructorCase1();
    void ModelPredictiveControlConstructorCase2();
    void ModelPredictiveControlConstructorCase3();

    void setLimitsCase1();
    void setLimitsCase2();
    void setLimitsCase3();
    void setLimitsCase4();
    void setReference();
    void setErrorWeight();
    void setControlWeight();
    void setInitialState();
    void setOptimizationAlgorithm2QuadProg();

    void setNewModelCase1();
    void setNewModelCase2();

    void getReference();
    void getErrorWeight();
    void getInitialState();
    void getControlWeight();
    void getControlerGain();

    void OutputControlCalcCase1();
    void OutputControlCalcCase2();
    void OutputControlCalcCase3();
    void OutputControlCalcCase4();
};

void PredictiveTestTest::ModelPredictiveControlConstructorCase1()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    QBENCHMARK {
        ControlHandler::ModelPredictiveControl<double> MPC;
    }
}

void PredictiveTestTest::ModelPredictiveControlConstructorCase2()
{
    LinAlg::Matrix<double> A(2,2), B(2,1), C(1,2), D(1,1);
    unsigned N1= 1, N2 = 2, NU = 2;
    double Q = 1, R, W = 1, L, b, J, K;
    R = 2.7; L = 0.004;
    K = 0.105; b = 9.3e-6; J = 1e-5;
    A(0,0) = -R/L; A(0,1) = -K/L;
    A(1,0) = K/L; A(1,1) = -b/J;
    B(0,0) = 1/L;
    B(1,0) = 0;
    C(0,0) = 0; C(0,1) = 1;
    D(0,0) = 0;

    ModelHandler::StateSpace<double> SS(A,B,C,D);
    ControlHandler::ModelPredictiveControl<double> MPC(SS,N1,N2,NU,Q,10,W);
    QBENCHMARK {
        ControlHandler::ModelPredictiveControl<double> MPC(SS,N1,N2,NU,Q,10,W);
    }

    QVERIFY2(LinAlg::isEqual(MPC.getControlerGain(), LinAlg::Matrix<double>("0.068,0.100;-0.014,0.107"),0.01), "Ganho do controlador errado!");
    QVERIFY2(LinAlg::isEqual(MPC.getControlWeight(), LinAlg::Matrix<double>("10.00,0;0,10.00"),0.01), "Ponderacao no sinal de controle errada!");
    QVERIFY2(LinAlg::isEqual(MPC.getErrorWeight(), LinAlg::Matrix<double>("1.000,0;0,1.000"),0.01), "Ponderacao do erro errada!");
    QVERIFY2(LinAlg::isEqual(MPC.getInitialState(), LinAlg::Matrix<double>("0;0")), "Valores dos estados errados!");
    QVERIFY2(LinAlg::isEqual(MPC.getReference(), LinAlg::Matrix<double>("1;1")), "Referencia errada!");
}

void PredictiveTestTest::ModelPredictiveControlConstructorCase3()
{
    ModelHandler::ARX<double> gz(2,2);
    gz.setModelCoef("-0.823; -0.000; 0.873; 0.012");
    ControlHandler::ModelPredictiveControl<double> MPC(gz,1,2,2,1,10,1);
    QBENCHMARK {
        ControlHandler::ModelPredictiveControl<double> MPC(gz,1,2,2,1,10,1);
    }

    QVERIFY2(LinAlg::isEqual(MPC.getControlerGain(), LinAlg::Matrix<double>("0.068,0.100;-0.014,0.107"),0.01), "Ganho do controlador errado!");
    QVERIFY2(LinAlg::isEqual(MPC.getControlWeight(), LinAlg::Matrix<double>("10.00,0;0,10.00"),0.01), "Ponderacao no sinal de controle errada!");
    QVERIFY2(LinAlg::isEqual(MPC.getErrorWeight(), LinAlg::Matrix<double>("1.000,0;0,1.000"),0.01), "Ponderacao do erro errada!");
    QVERIFY2(LinAlg::isEqual(MPC.getInitialState(), LinAlg::Matrix<double>("0;0")), "Valores dos estados errados!");
    QVERIFY2(LinAlg::isEqual(MPC.getReference(), LinAlg::Matrix<double>("1;1")), "Referencia errada!");
}

void PredictiveTestTest::setLimitsCase1()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> uMax, uMin;
    QBENCHMARK {
        MPC.setControlLimits(10,-10);
    }
    *(uMax,uMin) = MPC.getControlLimits();
    QVERIFY2(uMax(0,0) == 10, "Limites do controlador errado!");
    QVERIFY2(uMin(0,0) == -10, "Limites do controlador errado!");
}

void PredictiveTestTest::setLimitsCase2()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> duMax, duMin;
    QBENCHMARK {
        MPC.setControlVariationLimits(0.1,-0.1);
    }
    *(duMax,duMin) = MPC.getControlVariationLimits();
    QVERIFY2(duMax(0,0) == 0.10, "Limites do controlador errado!");
    QVERIFY2(duMin(0,0) == -0.10, "Limites do controlador errado!");
}

void PredictiveTestTest::setLimitsCase3()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> yMax, yMin;
    QBENCHMARK {
        MPC.setOutputLimits(10,-10);
    }
    *(yMax,yMin) = MPC.getOutputLimits();
    QVERIFY2(yMax(0,0) == 10, "Limites da saida errado!");
    QVERIFY2(yMin(0,0) == -10, "Limites da saida errado!");
}

void PredictiveTestTest::setLimitsCase4()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> uMax, uMin, duMax, duMin, yMax, yMin;
    QBENCHMARK {
        MPC.setLimits(0.1,-0.1,2,-2,10,-10);
    }
    *(duMax, duMin, yMax, yMin, uMax, uMin) = MPC.getLimits();
    QVERIFY2(uMax(0,0) == 10, "Limites do controlador errado!");
    QVERIFY2(uMin(0,0) == -10, "Limites do controlador errado!");
    QVERIFY2(duMax(0,0) == 0.10, "Limites do controlador errado!");
    QVERIFY2(duMin(0,0) == -0.10, "Limites do controlador errado!");
    QVERIFY2(yMax(0,0) == 2, "Limites da saida errado!");
    QVERIFY2(yMin(0,0) == -2, "Limites da saida errado!");
}

void PredictiveTestTest::setReference()
{
    double reference = 1;
    LinAlg::Matrix<double> A(2,2), B(2,1), C(1,2), D(1,1);
    unsigned N1= 1, N2 = 2, NU = 2;
    double Q = 1, R, W = 0, L, b, J, K;
    R = 2.7; L = 0.004;
    K = 0.105; b = 9.3e-6; J = 1e-5;
    A(0,0) = -R/L; A(0,1) = -K/L;
    A(1,0) = K/L; A(1,1) = -b/J;
    B(0,0) = 1/L;
    B(1,0) = 0;
    C(0,0) = 0; C(0,1) = 1;
    D(0,0) = 0;

    ModelHandler::StateSpace<double> SS(A,B,C,D);
    ControlHandler::ModelPredictiveControl<double> MPC(SS,N1,N2,NU,Q,10,W);
    QBENCHMARK {
        MPC.setReference(reference);
    }
//    std::cout << MPC.getReference() << std::endl;
    QVERIFY2(LinAlg::isEqual(MPC.getReference(), LinAlg::Matrix<double>("1;1")), "Referencia esta errada!");
}

void PredictiveTestTest::setErrorWeight()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> Q("1.000,0;0,1.000");
    QBENCHMARK {
        MPC.setErrorWeight(Q);
    }
    QVERIFY2(LinAlg::isEqual(MPC.getErrorWeight(), Q), "Ponderacao do erro errada!");
}

void PredictiveTestTest::setControlWeight()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> R("1.000,0;0,1.000");
    QBENCHMARK {
        MPC.setControlWeight(R);
    }
    QVERIFY2(LinAlg::isEqual(MPC.getControlWeight(), R), "Ponderacao do erro errada!");
}

void PredictiveTestTest::setInitialState()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> X("1.000;1.000");
    QBENCHMARK {
        MPC.setInitialState(X);
    }
    QVERIFY2(LinAlg::isEqual(MPC.getInitialState(), X), "Ponderacao do erro errada!");
}

void PredictiveTestTest::setOptimizationAlgorithm2QuadProg()
{
//    restrictedOptimizationHandler::QuadProg<Type> *QP = new restrictedOptimizationHandler::RecursiveActiveSet<double>;

}

void PredictiveTestTest::setNewModelCase1()
{

}

void PredictiveTestTest::setNewModelCase2()
{

}

void PredictiveTestTest::getReference()
{
    double reference = 1;
    LinAlg::Matrix<double> A(2,2), B(2,1), C(1,2), D(1,1);
    unsigned N1= 1, N2 = 2, NU = 2;
    double Q = 1, R, W = 0, L, b, J, K;
    R = 2.7; L = 0.004;
    K = 0.105; b = 9.3e-6; J = 1e-5;
    A(0,0) = -R/L; A(0,1) = -K/L;
    A(1,0) = K/L; A(1,1) = -b/J;
    B(0,0) = 1/L;
    B(1,0) = 0;
    C(0,0) = 0; C(0,1) = 1;
    D(0,0) = 0;

    ModelHandler::StateSpace<double> SS(A,B,C,D);
    ControlHandler::ModelPredictiveControl<double> MPC(SS,N1,N2,NU,Q,10,W);
    MPC.setReference(reference);
    QBENCHMARK {
        MPC.getReference();
    }
//    std::cout << MPC.getReference() << std::endl;
    QVERIFY2(LinAlg::isEqual(MPC.getReference(), LinAlg::Matrix<double>("1;1")), "Referencia esta errada!");
}

void PredictiveTestTest::getErrorWeight()
{

    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> Q("1.000,0;0,1.000");
    MPC.setErrorWeight(Q);
    QBENCHMARK {
        MPC.getErrorWeight();
    }
    QVERIFY2(LinAlg::isEqual(MPC.getErrorWeight(), Q), "Ponderacao do erro errada!");
}

void PredictiveTestTest::getInitialState()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> X("1.000;1.000");
    MPC.setInitialState(X);
    QBENCHMARK {
        MPC.getInitialState();
    }
    QVERIFY2(LinAlg::isEqual(MPC.getInitialState(), X), "Ponderacao do erro errada!");
}

void PredictiveTestTest::getControlWeight()
{
    ControlHandler::ModelPredictiveControl<double> MPC;
    LinAlg::Matrix<double> R("1.000,0;0,1.000");
    MPC.setControlWeight(R);
    QBENCHMARK {
        MPC.getControlWeight();
    }
    QVERIFY2(LinAlg::isEqual(MPC.getControlWeight(), R), "Ponderacao do erro errada!");
}

void PredictiveTestTest::getControlerGain()
{
    ModelHandler::ARX<double> gz(2,2);
    gz.setModelCoef("-0.823; -0.000; 0.873; 0.012");
    ControlHandler::ModelPredictiveControl<double> MPC(gz,1,2,2,1,10,1);
    QBENCHMARK {
        MPC.getControlerGain();
    }

    QVERIFY2(LinAlg::isEqual(MPC.getControlerGain(), LinAlg::Matrix<double>("0.068,0.100;-0.014,0.107"),0.01), "Ganho do controlador errado!");
}

void PredictiveTestTest::OutputControlCalcCase1()
{

}

void PredictiveTestTest::OutputControlCalcCase2()
{

}

void PredictiveTestTest::OutputControlCalcCase3()
{

}

void PredictiveTestTest::OutputControlCalcCase4()
{

}

QTEST_APPLESS_MAIN(PredictiveTestTest)

#include "tst_predictivetesttest.moc"
