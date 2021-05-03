#ifndef plotTest
    #include "SistemasdeControle/headers/graphicLibs/plot.h"
#else
    #include "../../../headers/graphicLibs/plot.h"
#endif


template<typename Type>
PlotHandler::plot<Type>::plot(QWidget *PlotFrame)
{
    this->properties.setPlotFrame(PlotFrame);
    this->realTimePlotInit();
}

template<typename Type>
PlotHandler::plot<Type>::plot(unsigned ySubplot, unsigned xSubplot, QWidget *PlotFrame)
{
    this->properties.setPlotFrame(PlotFrame);
    this->properties.setPlotSize(this->properties.windowSizeX*(xSubplot-1),this->properties.windowSizeY*(ySubplot-1),this->properties.windowSizeX, this->properties.windowSizeY);
    this->realTimePlotInit();
}

template<typename Type>
PlotHandler::plot<Type>::plot(unsigned ySubplot, unsigned xSubplot, plotProperties properties)
{
    this->properties = properties;
    this->properties.setPlotSize(this->properties.windowSizeX*(xSubplot-1),this->properties.windowSizeY*(ySubplot-1),this->properties.windowSizeX, this->properties.windowSizeY);

    this->realTimePlotInit();
}

template<typename Type>
PlotHandler::plot<Type>::plot(LinAlg::Matrix<Type> Y, QWidget *PlotFrame)
{
    LinAlg::Matrix<Type> X = LinAlg::LineVector<Type>(0,Y.getNumberOfColumns()-1);
    this->properties.setPlotFrame(PlotFrame);
    this->properties.PlotFrame->hide();
    this->generalPlot(X,Y);
    this->properties.PlotFrame->show();
}

template<typename Type>
PlotHandler::plot<Type>::plot(LinAlg::Matrix<Type> Y, plotProperties properties)
{
    LinAlg::Matrix<Type> X = LinAlg::LineVector<Type>(0,Y.getNumberOfColumns());
    this->properties = properties;
    this->properties.PlotFrame->hide();
    this->generalPlot(X,Y);
    this->properties.PlotFrame->show();
}

template<typename Type>
PlotHandler::plot<Type>::plot(LinAlg::Matrix<Type> X, LinAlg::Matrix<Type> Y, plotProperties properties)
{
    this->properties = properties;
    this->properties.PlotFrame->hide();
    this->generalPlot(X,Y);
    this->properties.PlotFrame->show();
}

template<typename Type>
PlotHandler::plot<Type>::plot(LinAlg::Matrix<Type> X, LinAlg::Matrix<Type> Y, QWidget *PlotFrame)
{
    this->properties.setPlotFrame(PlotFrame);
    this->properties.PlotFrame->hide();
    this->generalPlot(X,Y);
    this->properties.PlotFrame->show();
}

template<typename Type>
PlotHandler::plot<Type>::plot(LinAlg::Matrix<Type> X, LinAlg::Matrix<Type> Y, unsigned ySubplot, unsigned xSubplot, QWidget *PlotFrame)
{
    this->properties.setPlotFrame(PlotFrame);
    this->properties.setPlotSize(this->properties.windowSizeX*(xSubplot-1),this->properties.windowSizeY*(ySubplot-1),this->properties.windowSizeX, this->properties.windowSizeY);
    this->properties.PlotFrame->hide();
    this->generalPlot(X,Y);
    this->properties.PlotFrame->show();
}

template<typename Type>
PlotHandler::plot<Type>::plot(LinAlg::Matrix<Type> X, LinAlg::Matrix<Type> Y, unsigned ySubplot, unsigned xSubplot, plotProperties properties)
{
    this->properties = properties;
    this->properties.setPlotSize(this->properties.windowSizeX*(xSubplot-1),this->properties.windowSizeY*(ySubplot-1),this->properties.windowSizeX, this->properties.windowSizeY);
    this->properties.PlotFrame->hide();
    this->generalPlot(X,Y);
    this->properties.PlotFrame->show();

}

template <typename Type>
void PlotHandler::plot<Type>::generalPlot(LinAlg::Matrix<Type> X, LinAlg::Matrix<Type> Y)
{
//    centralWidget = new QWidget(this->properties.MainWindow);
//    centralWidget->setGeometry(QRect(this->properties.windowPosX, this->properties.windowPosY, this->properties.windowSizeX, this->properties.windowSizeY));
    customPlot = new QCustomPlot(this->properties.PlotFrame);
    customPlot->setGeometry(QRect(0, 0,this->properties.PlotFrame->geometry().width(), this->properties.PlotFrame->geometry().height()));

    // add title layout element:
    if(this->properties.titleFlag)
    {
        customPlot->plotLayout()->insertRow(0);
        customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(this->customPlot, this->properties.title.c_str()));
    }

    if(X.getNumberOfColumns() == Y.getNumberOfColumns() && X.getNumberOfRows() == Y.getNumberOfRows())
    {
        this->properties.rows = X.getNumberOfRows();
        this->properties.columns = X.getNumberOfColumns();
//        this->setLegend();

        QPen pen;
        // add graphs with different scatter styles:
        for (unsigned i = 0; i < this->properties.rows; ++i)
        {
          customPlot->addGraph();
          pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
          // generate data:
          QVector<double> x(this->properties.columns), y(this->properties.columns);
          for (unsigned k = 0; k < this->properties.columns; ++k)
          {
            x[k] = X(i+1,k+1);
            y[k] = Y(i+1,k+1);
          }
          customPlot->graph()->setData(x, y);
          customPlot->graph()->rescaleAxes(true);
          customPlot->graph()->setPen(pen);

          if(this->properties.variablesNameFlag)
              customPlot->graph()->setName("Grafico" + QString::number(i+1));

          customPlot->graph()->setLineStyle(QCPGraph::lsLine);

          if(this->properties.xLabelFlag)
              customPlot->xAxis->setLabel(this->properties.xLabel.c_str());
          if(this->properties.yLabelFlag)
              customPlot->yAxis->setLabel(this->properties.yLabel.c_str());
          // set scatter style:
        }
     }
    customPlot->rescaleAxes();
}

template <typename Type>
void PlotHandler::plot<Type>::generalPlot(LinAlg::Matrix<Type> X)
{
//    centralWidget = new QWidget(this->properties.MainWindow);
//    centralWidget->setGeometry(QRect(this->properties.windowPosX, this->properties.windowPosY, this->properties.windowSizeX, this->properties.windowSizeY));
    customPlot = new QCustomPlot(this->properties.PlotFrame);
    customPlot->setGeometry(QRect(0, 0,this->properties.PlotFrame->geometry().width(), this->properties.PlotFrame->geometry().height()));

    // add title layout element:
    if(this->properties.titleFlag)
    {
        customPlot->plotLayout()->insertRow(0);
        customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(this->customPlot, this->properties.title.c_str()));
    }

    this->properties.rows = X.getNumberOfRows();
    this->properties.columns = X.getNumberOfColumns();
//        this->setLegend();

    QPen pen;
    // add graphs with different scatter styles:
    for (unsigned i = 0; i < this->properties.rows; ++i)
    {
      customPlot->addGraph();
      pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
      // generate data:
      QVector<double> x(this->properties.columns), y(this->properties.columns);
      for (unsigned k = 0; k < this->properties.columns; ++k)
      {
        x[k] = X(i+1,k+1);
        y[k] = k;
      }
      customPlot->graph()->setData(x, y);
      customPlot->graph()->rescaleAxes(true);
      customPlot->graph()->setPen(pen);

      if(this->properties.variablesNameFlag)
          customPlot->graph()->setName("Grafico" + QString::number(i+1));

      customPlot->graph()->setLineStyle(QCPGraph::lsLine);

      if(this->properties.xLabelFlag)
          customPlot->xAxis->setLabel(this->properties.xLabel.c_str());
      if(this->properties.yLabelFlag)
          customPlot->yAxis->setLabel(this->properties.yLabel.c_str());
      // set scatter style:

    }
    customPlot->rescaleAxes();
}

template <typename Type>
void PlotHandler::plot<Type>::realTimeDataUpdate(double i, double j)
{
//    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    customPlot->graph(0)->addData(i, j);
//    customPlot->graph(0)->removeDataBefore(i-8);
//    customPlot->graph(1)->clearData();
    customPlot->graph(1)->addData(i, j);
    customPlot->rescaleAxes();
    customPlot->replot();
}

template <typename Type>
void PlotHandler::plot<Type>::realTimePlotInit()
{
//    centralWidget = new QWidget(this->properties.MainWindow);
//    centralWidget->setGeometry(QRect(this->properties.windowPosX, this->properties.windowPosY, this->properties.windowSizeX, this->properties.windowSizeY));
    customPlot = new QCustomPlot(this->properties.PlotFrame);
    customPlot->setGeometry(QRect(0, 0,this->properties.PlotFrame->geometry().width(), this->properties.PlotFrame->geometry().height()));

    customPlot->addGraph(); // blue line
    customPlot->graph()->setPen(QPen(Qt::blue));
    customPlot->graph()->setBrush(QBrush(QColor(240, 255, 200)));
    customPlot->graph()->setAntialiasedFill(false);
    customPlot->addGraph(); // blue dot
    customPlot->graph()->setPen(QPen(Qt::blue));
    customPlot->graph()->setLineStyle(QCPGraph::lsNone);
    customPlot->graph()->setScatterStyle(QCPScatterStyle::ssDisc);

    customPlot->xAxis->setTicker(QSharedPointer<QCPAxisTickerPi>(new QCPAxisTickerPi));
//    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
//    customPlot->xAxis->setAutoTickStep(false);
//    customPlot->xAxis->setTickStep(2);
    customPlot->axisRect()->setupFullAxesBox();

    // add title layout element:
    if(this->properties.titleFlag)
    {
        customPlot->plotLayout()->insertRow(0);
        customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(this->customPlot, this->properties.title.c_str()));
    }
    if(this->properties.yLabelFlag)
        customPlot->yAxis->setLabel(this->properties.yLabel.c_str());

}

