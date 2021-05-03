#include <QString>
#include <QtTest>

#define testPolynom
#define testModel
#include "../../../headers/primitiveLibs/LinAlg/matrix.h"
#include "../../../headers/primitiveLibs/polynom.h"
#include "../../../headers/modelLibs/transferfunction.h"
#include "../../../headers/modelLibs/arx.h"
#include "../../../headers/modelLibs/conversions.h"

class ConversionsTest : public QObject
{
    Q_OBJECT

public:
    ConversionsTest(){}

private Q_SLOTS:
    void ss2tf();
    void ss2tfSISO();
    void arx2tf();
    void arx2SS();
    void tf2ss();
    void tf2ssSISO();
    void tf2arxSISO();
    void c2dCase1();
    void c2dCase2();
    void d2c();
    void d2cCase2();
    void integrativeModelDiscrete();
    void integrativeModelContinuous();
    void predictionModelDiscrete();
    void predictionModelContinuous();
};

void ConversionsTest::ss2tf()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0,1;1,0", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    ModelHandler::TransferFunction<double> tf;

    QBENCHMARK {
        tf = ModelHandler::ss2tf(SS);
    }

    LinAlg::Matrix<double> numTF1 = tf(0,0).getNum();
    LinAlg::Matrix<double> denTF1 = tf(0,0).getDen();
    LinAlg::Matrix<double> numTF2 = tf(0,1).getNum();
    LinAlg::Matrix<double> denTF2 = tf(0,1).getDen();

    QVERIFY2(fabs(numTF1(0,0)) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(numTF1(0,1) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,0) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,1) - 2) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,2) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

    QVERIFY2(fabs(numTF2(0,0) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(numTF2(0,1) - 2) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF2(0,0) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF2(0,1) - 2) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF2(0,2) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

//    std::string str; str << tf;
//    std::cout << str << std::endl;
}

void ConversionsTest::ss2tfSISO()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D);
    ModelHandler::TransferFunction<double> tf;

    QBENCHMARK {
        tf = ModelHandler::ss2tfSISO(SS);
    }

    LinAlg::Matrix<double> numTF1 = tf(0,0).getNum();
    LinAlg::Matrix<double> denTF1 = tf(0,0).getDen();

    QVERIFY2(fabs(numTF1(0,0)) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(numTF1(0,1) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,0) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,1) - 2) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,2) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
//    std::string str; str << tf;
//    std::cout << str << std::endl;
}

void ConversionsTest::arx2tf()
{
    ModelHandler::ARX<double> arx(2,2,0,2,1,0.1);
    arx.setModelCoef("-1.810;0.819;0.094;0.088;0.074;0.058");
    ModelHandler::TransferFunction<double> tf;
    QBENCHMARK {
        tf = ModelHandler::arx2tf(arx);
    }

    LinAlg::Matrix<double> numTF1 = tf(0,0).getNum();
    LinAlg::Matrix<double> denTF1 = tf(0,0).getDen();
    LinAlg::Matrix<double> numTF2 = tf(0,1).getNum();
    LinAlg::Matrix<double> denTF2 = tf(0,1).getDen();

    QVERIFY2(fabs(numTF1(0,0) - 0.094) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(numTF1(0,1) - 0.088) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,0) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,1) + 1.810) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,2) - 0.819 ) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

    QVERIFY2(fabs(numTF2(0,0) - 0.074) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(numTF2(0,1) - 0.058) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF2(0,0) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF2(0,1) + 1.810) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF2(0,2) - 0.819) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
//    std::string str; str << tf;
//    std::cout << str << std::endl;
}

void ConversionsTest::arx2SS()
{
    ModelHandler::ARX<double> arx(2,2,0,2,1,0.1);
    arx.setModelCoef("-1.810;0.819;0.094;0.088;0.074;0.058");
    ModelHandler::StateSpace<double> SS;
    QBENCHMARK {
        SS = ModelHandler::arx2SS(arx);
    }

    LinAlg::Matrix<double> A = SS.getA();
    LinAlg::Matrix<double> B = SS.getB();
    LinAlg::Matrix<double> C = SS.getC();
    LinAlg::Matrix<double> D = SS.getD();

    QVERIFY2(LinAlg::isEqual(A, LinAlg::Matrix<double>("1.810,1.000;-0.819,0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(B, LinAlg::Matrix<double>("0.094,0.074;0.088,0.058")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(C, LinAlg::Matrix<double>("1,0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(D, LinAlg::Matrix<double>("0,0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

//    std::string str; str << SS;
//    std::cout << str << std::endl;
}

void ConversionsTest::tf2ss()
{
    ModelHandler::StateSpace<double> SS;
    ModelHandler::TransferFunction<double> tf(1,2);
    tf(0,0) = PolynomHandler::Polynom<double>(1,"1,2,1");
    tf(0,1) = PolynomHandler::Polynom<double>("1,2","1,2,1");
    QBENCHMARK {
        SS = ModelHandler::tf2ss(tf);
    }
    QSKIP("Estudar outra forma de Realizar a conversão de função de transferência para espaço de estados.");
//    std::string str; str << SS;
//    std::cout << str << std::endl;
}

void ConversionsTest::tf2ssSISO()
{
    ModelHandler::StateSpace<double> SS;
    ModelHandler::TransferFunction<double> tf(1,1);
    tf(0,0) = PolynomHandler::Polynom<double>(1,"1,2,1");
    QBENCHMARK {
        SS = ModelHandler::tf2ss(tf);
    }

    LinAlg::Matrix<double> A = SS.getA();
    LinAlg::Matrix<double> B = SS.getB();
    LinAlg::Matrix<double> C = SS.getC();
    LinAlg::Matrix<double> D = SS.getD();

    QVERIFY2(LinAlg::isEqual(A, LinAlg::Matrix<double>("0,1;-1,-2")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(B, LinAlg::Matrix<double>("0;1")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(C, LinAlg::Matrix<double>("1,0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(D, LinAlg::Matrix<double>("0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

//    std::string str; str << SS;
//    std::cout << str << std::endl;
}

void ConversionsTest::tf2arxSISO()
{
    ModelHandler::TransferFunction<double> tf(1,1);
    tf(0,0) = PolynomHandler::Polynom<double>(1,"1,2,1");
    ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(tf,0.1);
    QBENCHMARK {
        ModelHandler::ARX<double> arx = ModelHandler::tf2arxSISO(tf,0.1);
    }

    std::string str; str << arx;
    //std::cout << str;
    QVERIFY2(str == " y1( k ) = 1.80967 y1( k - 1 )  - 0.818731 y1( k - 2 )  + 0.00467883 u1( k - 1 )  + 0.00437708 u1( k - 2 ) \n", "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
//    std::cout << str << std::endl;
}

void ConversionsTest::c2dCase1()
{
    ModelHandler::TransferFunction<double> tf(1,1),tfd(1,1);
    tf(0,0) = PolynomHandler::Polynom<double>(1,"1,2,1");
    QBENCHMARK {
        tfd = ModelHandler::c2d(tf,0.1);
    }

    LinAlg::Matrix<double> numTF1 = tfd(0,0).getNum();
    LinAlg::Matrix<double> denTF1 = tfd(0,0).getDen();

    QVERIFY2(fabs(numTF1(0,0)- 0.00467884) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(numTF1(0,1) - 0.00437708) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,0) - 1) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,1) + 1.80967) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(fabs(denTF1(0,2) - 0.818731) < 1e-5, "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

//    std::string str; str << tfd;
//    std::cout << str << std::endl;
}

void ConversionsTest::c2dCase2()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0,1;1,0", C = "1,0", D = "0,0";
    ModelHandler::StateSpace<double> SS(A,B,C,D),SSd;
    SS.setNDiscretizationValue(4);

    QBENCHMARK {
        SSd = ModelHandler::c2d(SS,0.1);
    }

    LinAlg::Matrix<double> Ad = SSd.getA();
    LinAlg::Matrix<double> Bd = SSd.getB();
    LinAlg::Matrix<double> Cd = SSd.getC();
    LinAlg::Matrix<double> Dd = SSd.getD();

    QVERIFY2(LinAlg::isEqual(Ad, LinAlg::Matrix<double>("0.995,0.090;-0.090,0.814"),1e-3), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Bd, LinAlg::Matrix<double>("0.005,0.100;0.090,-0.005"),1e-3), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Cd, LinAlg::Matrix<double>("1,0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Dd, LinAlg::Matrix<double>("0,0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

//    std::string str; str << SSd;
//    std::cout << str << std::endl;
}

void ConversionsTest::d2c()
{
    LinAlg::Matrix<double> Ad = "0.998,0.095;-0.095,0.807", Bd = "0.003,0.100;0.095,-0.002", Cd = "1,0", Dd = "0,0";
    ModelHandler::StateSpace<double> SS,SSd(Ad,Bd,Cd,Dd,0.1);

    QBENCHMARK {
        SS = ModelHandler::d2c(SSd);
    }

    LinAlg::Matrix<double> A = SS.getA();
    LinAlg::Matrix<double> B = SS.getB();
    LinAlg::Matrix<double> C = SS.getC();
    LinAlg::Matrix<double> D = SS.getD();

//    std::string str; str << SS;
//    std::cout << str << std::endl;
    QVERIFY2(LinAlg::isEqual(A, LinAlg::Matrix<double>("0,1;-1,-2"),5e-1), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(B, LinAlg::Matrix<double>("0,1;1,0"),5e-1), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(C, LinAlg::Matrix<double>("1,0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(D, LinAlg::Matrix<double>("0,0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

}

void ConversionsTest::d2cCase2()
{
    ModelHandler::TransferFunction<long double> Tf("0.51987","1,-0.949896",12.5);
    std::string num, den;
    ModelHandler::TransferFunction<long double> Tfc;
    QBENCHMARK {
        Tfc = ModelHandler::d2c(Tf);
    }
    num << Tfc(0,0).getNum(); den << Tfc(0,0).getDen();
   // std::cout << Tfc; std::cout << "\n";
    QVERIFY2(num == "  0.043 \n", "Falhou ao comparar As funcoes de Transferencia discreta.");
    QVERIFY2(den == "  1.000   0.004 \n", "Falhou ao comparar As funcoes de Transferencia discreta.");
}

void ConversionsTest::integrativeModelDiscrete()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D), SSI;
    SS = ModelHandler::c2d(SS,0.1);

    QBENCHMARK {
        SSI = ModelHandler::integrativeModel(SS);
    }

    LinAlg::Matrix<double> Ad = SSI.getA();
    LinAlg::Matrix<double> Bd = SSI.getB();
    LinAlg::Matrix<double> Cd = SSI.getC();
    LinAlg::Matrix<double> Dd = SSI.getD();

    QVERIFY2(LinAlg::isEqual(Ad, LinAlg::Matrix<double>("0.9953,0.0905,0;-0.0905,0.8144,0;0.9953,0.0905,1.0000"),1e-2), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Bd, LinAlg::Matrix<double>("0.0047;0.0905;0.0047"), 1e-2), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Cd, LinAlg::Matrix<double>("0,0,1")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Dd, LinAlg::Matrix<double>("0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

//    std::string str; str << SSI;
//    std::cout << str << std::endl;
}


void ConversionsTest::integrativeModelContinuous()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D), SSI;

    QBENCHMARK {
        SSI = ModelHandler::integrativeModel(SS);
    }

    LinAlg::Matrix<double> Ad = SSI.getA();
    LinAlg::Matrix<double> Bd = SSI.getB();
    LinAlg::Matrix<double> Cd = SSI.getC();
    LinAlg::Matrix<double> Dd = SSI.getD();

//    std::string str; str << SSI;
//    std::cout << str << std::endl;
    QVERIFY2(LinAlg::isEqual(Ad, LinAlg::Matrix<double>("0,1.000,0;0,0,1.000;0,-1.000,-2.000"),1e-2), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Bd, LinAlg::Matrix<double>("0;0;1"), 1e-2), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Cd, LinAlg::Matrix<double>("0,0,1")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Dd, LinAlg::Matrix<double>("0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

}

void ConversionsTest::predictionModelDiscrete()
{
    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
    ModelHandler::StateSpace<double> SS(A,B,C,D), SSI, SSP;
    SS = ModelHandler::c2d(SS,0.1);
    SSI = ModelHandler::integrativeModel(SS);

    QBENCHMARK {
        SSP = ModelHandler::predictionModel(SSI,1,2,2);
    }

    LinAlg::Matrix<double> Ad = SSP.getA();
    LinAlg::Matrix<double> Bd = SSP.getB();
    LinAlg::Matrix<double> Cd = SSP.getC();
    LinAlg::Matrix<double> Dd = SSP.getD();

    QVERIFY2(LinAlg::isEqual(Ad, LinAlg::Matrix<double>("0.9953,0.0905,0;-0.0905,0.8144,0;0.9953,0.0905,1.0000;0.9825,0.1637,0;-0.1637,0.6550,0;1.9778,0.2542,1.0000"),1e-2), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Bd, LinAlg::Matrix<double>("0.0047,0;0.0905,0;0.0047,0;0.0128,0.0128;0.0733,0.0733;0.0175,0.0175"), 1e-2), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Cd, LinAlg::Matrix<double>("0,0,1,0,0,0;0,0,0,0,0,1")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");
    QVERIFY2(LinAlg::isEqual(Dd, LinAlg::Matrix<double>("0")), "Falhou ao comparar As funcoes de Transferencia a partir da em espaco de estados.");

//    std::string str; str << SSP;
//    std::cout << str << std::endl;
}

void ConversionsTest::predictionModelContinuous()
{
    QSKIP("Implementar depois");
//    LinAlg::Matrix<double> A = "0,1;-1,-2", B = "0;1", C = "1,0", D = 0.0;
//    ModelHandler::StateSpace<double> SS(A,B,C,D), SSI, SSP;
//    SS = ModelHandler::c2d(SS,0.1);
//    SSI = ModelHandler::integrativeModel(SS);

//    QBENCHMARK {
//        SSP = ModelHandler::predictionModel(SSI,0,2,2);
//    }

//    std::string str; str << SSP;
////    std::cout << str << std::endl;
}

QTEST_APPLESS_MAIN(ConversionsTest)

#include "tst_conversionstest.moc"
