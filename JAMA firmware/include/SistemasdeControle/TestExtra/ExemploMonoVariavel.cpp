#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PlotHandler::plotProperties PlotProperty;
    PlotProperty.setPlotFrame(ui->widget);
    PlotProperty.setTitle("Sinal de Controle");
    PlotProperty.setxLabel("Tempo em segundos");
    PlotProperty.setyLabel("Amplitude em unidades de engenharia");
//    PlotProperty.setPlotSize(0,0,400,150);
    PlotProperty.font        = "Helvetica";
    PlotVar    = new PlotHandler::plot<double>*[2];
    PlotVar[0] = new PlotHandler::plot<double>(1,2,PlotProperty);
    PlotProperty.setTitle("Saída do Sistema");
    PlotVar[1] = new PlotHandler::plot<double>(2,2,PlotProperty);

    //variáveis do preditivo
    unsigned N1 = 1, N2 = 20, NU = 5;
    //Equação de estados
    LinAlg::Matrix<double> A(2,2),B(2,1),C(1,2),D(1,1);
    double R = 2.7, L = 0.004, K = 0.105, b = 9.3e-6, J = 1e-5;
    A(1,1) = -R/L; A(1,2) = -K/L; A(2,1) = K/L; A(2,2) = -b/J;
    B(1,1) = 1/L; B(2,1) = 0;
    C = "0,1"; D = "0";

    ModelHandler::StateSpace<double> SS(A,B,C,D);
    ModelHandler::StateSpace<double> SSd = ModelHandler::c2d(SS,0.1);
    ModelHandler::StateSpace<double> SSd2 = ModelHandler::c2d(SS,0.1);

    ModelHandler::IntegrativeModel<double> SSI(SSd);

    //        //Inicio do controle preditivo
    ModelHandler::PredictionModel<double> SSP(SSd,N1,N2,NU);
    std::cout << SSP;

    LinAlg::Matrix<double> X  = LinAlg::Zeros<double>(SSd.getA().getNumberOfRows(),2);
    LinAlg::Matrix<double> Y  = LinAlg::Zeros<double>((SSd.getC()*X).getNumberOfRows(),(SSd.getC()*X).getNumberOfColumns());
    LinAlg::Matrix<double> Q  = LinAlg::Eye<double>((SSP.getC()*SSP.getB()).getNumberOfRows());
    LinAlg::Matrix<double> W  = 50*LinAlg::Ones<double>((SSP.getC()*SSP.getA()*(X||Y)).getNumberOfRows(),(SSd.getB()).getNumberOfColumns());
    LinAlg::Matrix<double> Ru = 10*LinAlg::Eye<double>(NU);

    ControlHandler::ModelPredictiveControl<double> MPC(SSd,SSI,SSP,Q,Ru,W);
    ModelHandler::ARX<double> gz(2,2), gz2(2,2);
    OptimizationHandler::Optimization<double> *RLS = new OptimizationHandler::RecursiveLeastSquare<double>(&gz);
    OptimizationHandler::Optimization<double> *LS = new OptimizationHandler::LeastSquare<double>(&gz2);
    LinAlg::Matrix<double> Uf, Yf;
    std::string str;

    for(unsigned i = 0; i < 60; ++i)
    {
        LinAlg::Matrix<double> Umpc = MPC.OutputControlCalc(SSd.getActualState());
        if(i > 30) Umpc += 2.0;
        LinAlg::Matrix<double> Ympc = SSd.sim(Umpc(1,1));
        if(i > 1)
            RLS->Optimize(Uf(1,i-1),Yf(1,from(i-1)-->(i)));
        if(i > 2)
        {
            ModelHandler::TransferFunction<double> TF = ModelHandler::arx2tf(gz,0.1);
            SSd2 = ModelHandler::tf2ssSISO(TF);
            SSI = ModelHandler::IntegrativeModel<double>(SSd2);
            SSP = ModelHandler::PredictionModel<double>(SSd2,N1,N2,NU);
            MPC.setNewModel(SSd2,SSI,SSP,Q,Ru,W);
        }
        PlotVar[0]->realTimeDataUpdate(i*0.1, (Umpc(1,1)));
        PlotVar[1]->realTimeDataUpdate(i*0.1, (Ympc(1,1)));
        Uf = Uf|Umpc;
        Yf = Yf|Ympc;
    }

    LS->Optimize(Uf,Yf);
    ModelHandler::TransferFunction<double> TF = ModelHandler::arx2tf(gz,0.1);
    ModelHandler::TransferFunction<double> TF2 = ModelHandler::arx2tf(gz2,0.1);
    ModelHandler::TransferFunction<double> TF3 = ModelHandler::ss2tfSISO(SSd);
    str += "Recursive Least Square estimated Transfer Function \n\n";
    str <<  TF;
    str += "\n\nLeast Square estimated Transfer Function \n\n";
    str << TF2;
    str += "\n\nOriginal Transfer Function\n\n";
    str << TF3;
    ui->textEdit->setText(str.c_str());
//      i = 0; j = 0;
//      startTimer(100);
//      this->resize(2*400,2*300);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *)
{
//    i = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
////    j = 100*qCos(2*i);
//    A[0]->realTimeDataUpdate(i,100*qCos(2*i));
//    A[1]->realTimeDataUpdate(i,100*qSin(2*i));
//    A[2]->realTimeDataUpdate(i,150*qCos(1.5*i));
//    A[3]->realTimeDataUpdate(i,100*qSin(1.5*i));
}

void MainWindow::on_pushButton_clicked()
{
//Teste básico matrix
//----------------------------------------------------------
//    QByteArray array = ui->lineEdit->text().toLocal8Bit();
//    std::string buffer = array.data();
//    LinAlg::Matrix<double> B = buffer;

//    std::string str;
//    str << B;
//    ui->textEdit->setText(str.c_str());

//Teste básico polinômios
//----------------------------------------------------------

//    QByteArray array = ui->lineEdit->text().toLocal8Bit();
//    std::string buffer = array.data();
//    PolynomHandler::Polynom<double> B("1","1,1"), C("1,1","1,2,1");
//    double num[2] = {1,1}, den[3] = {1,2,1};
//    B += C;
////    C = PolynomHandler::simplify<double>(num,den,2,3);
//    std::string str;
//    str <<  C;
//    ui->textEdit->setText(str.c_str());
}
