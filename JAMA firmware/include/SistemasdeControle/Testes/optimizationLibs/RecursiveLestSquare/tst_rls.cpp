#define testPolynom
#define testModel

#include <QString>
#include <QtTest>
#include "../../../headers/primitiveLibs/LinAlg/matrix.h"
#include "../../../headers/modelLibs/model.h"
#include "../../../headers/modelLibs/arx.h"
#include "../../../headers/modelLibs/polynomial.h"
#include "../../../headers/modelLibs/transferfunction.h"
#include "../../../headers/modelLibs/conversions.h"
#include "../../../headers/advancedModelLibs/droneModel/limbModel.h"
#include "../../../headers/optimizationLibs/leastsquare.h"
#include "../../../headers/optimizationLibs/recursiveleastsquare.h"
// add necessary includes here

class rls : public QObject
{
    Q_OBJECT

public:
    rls(){qputenv("QTEST_FUNCTION_TIMEOUT", "100000000");}
    ~rls(){}

private slots:
    //void identification_SISO_case1();
    //void identification_MIMO_case1();
    //void identification_Polynomial_SISO_case1();
    //void identification_Polynomial_MIMO_case1();
    void identification_Hammerstein_MIMO_case1();

};
/*
void rls::identification_SISO_case1()
{
    ModelHandler::TransferFunction<double> TF("10","1,2,1");
    ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
    LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
    LinAlg::Matrix<double> Y = TFd.sim(U);
    ModelHandler::ARX<double> arx(2,2);
    OptimizationHandler::RecursiveLeastSquare<double> RLS(&arx,1e6);

    QBENCHMARK {
        ModelHandler::TransferFunction<double> TF("10","1,2,1");
        ModelHandler::TransferFunction<double> TFd = ModelHandler::c2d(TF,0.1);
        LinAlg::Matrix<double> U = 0.43*LinAlg::Ones<double>(1,10);
        LinAlg::Matrix<double> Y = TFd.sim(U);
        ModelHandler::ARX<double> arx(2,2);
        OptimizationHandler::RecursiveLeastSquare<double> RLS(&arx,1e6);

        for(uint32_t i = 0; i < 9; ++i)
        {
            RLS.Optimize(U(0,i),Y(0,i+1));
            std::cout << (arx) << std::endl;
        }

        std::cout << ModelHandler::arx2tf(arx) << std::endl;
        std::cout << TFd << std::endl;
    }

    for(uint32_t i = 0; i < 9; ++i)
    {
        RLS.Optimize(U(0,i),Y(0,i+1));
    }
    //std::cout << arx << "\n";
}

void rls::identification_MIMO_case1()
{
    QBENCHMARK {
        ModelHandler::TransferFunction<double> TFd(2,4,0.1);
        PolynomHandler::Polynom<double> TFsiso1("0,0.0502643150445874,0.0486265591254919", "1,-1.80682836869774,0.905709516037680");
        PolynomHandler::Polynom<double> TFsiso2("0,0.0694528157694939,0.0671898433202834", "1,-1.80682836869774,0.905709516037680");
        PolynomHandler::Polynom<double> TFsiso3("0,0.0550157982343233,0.0532226351589859", "1,-1.79748080135868,0.905709516037680");
        PolynomHandler::Polynom<double> TFsiso4("0,0.0646020956501844,0.0624964806045582", "1,-1.79748080135868,0.905709516037680");
        PolynomHandler::Polynom<double> TFsiso0("0", "1");

        TFd(0,0) = TFsiso1; TFd(0,1) = TFsiso2; TFd(0,2) = TFsiso0; TFd(0,3) = TFsiso0;
        TFd(1,0) = TFsiso0; TFd(1,1) = TFsiso0; TFd(1,2) = TFsiso3; TFd(1,3) = TFsiso4;
        //std::cout << TFd << std::endl;

        LinAlg::Matrix<double> In = 10*LinAlg::Random<double>(4,10);
        LinAlg::Matrix<double> U;
        for(int i = 0; i < In.getNumberOfColumns(); ++i)
            U = U|((In(0,i)*LinAlg::Ones<double>(1,20)||In(1,i)*LinAlg::Ones<double>(1,20)||In(2,i)*LinAlg::Ones<double>(1,20)||In(3,1)*LinAlg::Ones<double>(1,20)));
        LinAlg::Matrix<double> Y = TFd.sim(U);
        ModelHandler::ARX<double> arx(2,2,0,4,2,0.1);
        OptimizationHandler::RecursiveLeastSquare<double> RLS(&arx,1e6);

        for(uint32_t i = 0; i < 200; ++i)
        {
            RLS.Optimize(U(from(0)-->(3),i),Y(from(0)-->(1),i+1));
            std::cout << (arx) << std::endl;
        }

        std::cout << ModelHandler::arx2tf(arx) << std::endl;
        std::cout << TFd << std::endl;
    }

void rls::identification_Polynomial_SISO_case1()
{
    ModelHandler::Polynomial<double> pol(6);
    pol.setModelCoef("0; 11.9677550168665; 0; 4.34814267315048;0;0;1.92078367330958");
    std::cout << (pol.print()) << std::endl;

    LinAlg::Matrix<double> U = 10*LinAlg::Random<double>(1,20);
    LinAlg::Matrix<double> Y = pol.sim(U);

    std::cout << Y << "\n";
    ModelHandler::Polynomial<double> pol2(6);
    OptimizationHandler::RecursiveLeastSquare<double> RLS(&pol2,1e9);

    for(unsigned i = 0; i < 9; ++i)
    {
        RLS.Optimize(U(0,i),Y(0,i));
        std::cout << (pol2.print()) << std::endl;
    }

    std::cout << (pol.print()) << std::endl;
}

void rls::identification_Polynomial_MIMO_case1()
{
    ModelHandler::Polynomial<double> pol(6,2,2);
    LinAlg::Matrix<double> temp = "0; 11.9677550168665; 0; 4.34814267315048;0;0;1.92078367330958;0; 11.9677550168665; 0; 4.34814267315048;0;0;1.92078367330958";
    pol.setModelCoef(temp|temp);
    std::cout << (pol.print()) << std::endl;

    LinAlg::Matrix<double> U = 10*LinAlg::Random<double>(2,50);
    LinAlg::Matrix<double> Y = pol.sim(U);

    std::cout << Y << "\n";
    ModelHandler::Polynomial<double> pol2(6,2,2);
    OptimizationHandler::RecursiveLeastSquare<double> RLS(&pol2,1e9);

    for(unsigned i = 0; i < 50; ++i)
    {
        RLS.Optimize(U.getColumn(i),Y.getColumn(i));
        std::cout << (pol2.print()) << std::endl;
    }

    std::cout << (pol.print()) << std::endl;
}
*/
void rls::identification_Hammerstein_MIMO_case1()
{
    LinAlg::Matrix<double> tempInput = "0;0.0523359562429438;0.104528463267653;0.156434465040231;0.207911690817759;0.258819045102521;0.309016994374947;0.358367949545300;0.406736643075800;0.453990499739547;0.500000000000000;0.544639035015027;0.587785252292473;0.629320391049837;0.669130606358858;0.707106781186548;0.743144825477394;0.777145961456971;0.809016994374948;0.838670567945424;0.866025403784439;0.891006524188368;0.913545457642601;0.933580426497202;0.951056516295154;0.965925826289068;0.978147600733806;0.987688340595138;0.994521895368273;0.998629534754574;1;0.998629534754574;0.994521895368273;0.987688340595138;0.978147600733806;0.965925826289068;0.951056516295154;0.933580426497202;0.913545457642601;0.891006524188368;0.866025403784439;0.838670567945424;0.809016994374948;0.777145961456971;0.743144825477394;0.707106781186548;0.669130606358858;0.629320391049837;0.587785252292473;0.544639035015027;0.500000000000000;0.453990499739547;0.406736643075800;0.358367949545300;0.309016994374948;0.258819045102521;0.207911690817759;0.156434465040231;0.104528463267654;0.0523359562429438";
    uint32_t size = 1500, counter = 0;
    LinAlg::Matrix<double> In(tempInput.getNumberOfRows()*size,1);
    for(uint16_t i = 0; i < tempInput.getNumberOfRows(); ++i){
        for(uint16_t j = 0; j < size; ++j)
        {
            In(counter,0) = tempInput(i,0)*50;
            counter++;
        }
        std::cout << tempInput(i,0)*50 << std::endl;
    }

    ModelHandler::LimbModel<double> limb("0,0.01,0,0,0,0.01,1,1,3");
    LinAlg::Matrix<double> Out = limb.sim(In);

    counter = 0;
    LinAlg::Matrix<double> in(1,60), out(1,60);
    ModelHandler::Polynomial<double> pol2(10,1,1);
    OptimizationHandler::RecursiveLeastSquare<double> RLS1(&pol2,1e12);

    for(uint32_t i = size-1; i < size*60; i+=size)
    {
        in(0,counter) = In(i,0); out(0,counter) = Out(i,0);
        RLS1.Optimize(Out(i,0),In(i,0));
        //std::cout << ( pol2.print()) << std::endl;
        counter++;
    }

    //std::cout <<Y << (pol2.print()) << std::endl;
    LinAlg::Matrix<double> U = pol2.sim(out);
    //std::cout << ~(in||U||(in-U)) << std::endl;

    size = 100; counter = 0;
    LinAlg::Matrix<double> InTemp(tempInput.getNumberOfRows()*size,1);
    LinAlg::Matrix<double> In2(tempInput.getNumberOfRows()*size,1);
    for(uint16_t i = 0; i < tempInput.getNumberOfRows(); ++i){
        for(uint16_t j = 0; j < size; ++j)
        {
            In2(counter,0) = tempInput(i,0)*50;
            counter++;
        }
    }

    for(uint32_t i = 0; i < size*60; ++i)
        InTemp(i,0) = pol2.sim((In2(i,(uint32_t)0)/50));
    LinAlg::Matrix<double> Y = limb.sim(InTemp);
    ModelHandler::ARX<double> arxLimb(2,2);
    arxLimb.setModelCoef("-1.99828; 0.998521; 0.00123245; -0.000981273");
    LinAlg::Matrix<double> Ylin = arxLimb.sim(~In2/50);
    std::cout << (In2/50|Y|~Ylin) << std::endl;

    ModelHandler::ARX<double> arx(2,2,0,1,1,0.1);
    OptimizationHandler::RecursiveLeastSquare<double> RLS2(&arx,1e12);
    //U = pol2.sim((~In(i,(uint32_t)0))/50
    double a; counter = 0;
    for(uint32_t i = 0; i < size*30; ++i)
    {
        if(i%size == 0){
            std::cout << (arx.print()) << std::endl;
            a = tempInput(counter,0);
            counter++;
        }
        RLS2.Optimize(a,Y(i+1,(uint32_t)0));

    }
    std::cout << (arx.print()) << std::endl;
   //std::cout << TFd << std::endl;*/
}
/*
void rls::identification_Hammerstein_SISO_case1()
{
    QBENCHMARK {
        ModelHandler::TransferFunction<double> TFd("0,0.0502643150445874,0.0486265591254919", "1,-1.80682836869774,0.905709516037680");
        LinAlg::Matrix<double> In = 10*LinAlg::Random<double>(1,10);
        LinAlg::Matrix<double> U;
        for(int i = 0; i < In.getNumberOfColumns(); ++i)
            U = U|((In(0,i)*LinAlg::Ones<double>(1,20)||In(1,i)*LinAlg::Ones<double>(1,20)||In(2,i)*LinAlg::Ones<double>(1,20)||In(3,1)*LinAlg::Ones<double>(1,20)));

        LinAlg::Matrix<double> Y = TFd.sim(U);
        ModelHandler::ARX<double> arx(2,2);
        OptimizationHandler::RecursiveLeastSquare<double> RLS(&arx,1e6);

        for(uint32_t i = 0; i < 9; ++i)
        {
            RLS.Optimize(U(0,i),Y(0,i+1));
            std::cout << (arx) << std::endl;
        }

        std::cout << ModelHandler::arx2tf(arx) << std::endl;
        std::cout << TFd << std::endl;
    }
}

}
*/

QTEST_APPLESS_MAIN(rls)

#include "tst_rls.moc"
