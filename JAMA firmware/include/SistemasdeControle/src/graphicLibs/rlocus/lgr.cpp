#include "SistemasdeControle/headers/graphicLibs/rlocus/lgr.h"

//void plot::rlocus(const ModelHandler::TransferFunction<double> &TF)
LGR::LGR(const ModelHandler::TransferFunction<double> &TF, QWidget *parent):
    QGraphicsView(new QGraphicsScene, parent),
    m_coordX(0),
    m_coordY(0),
    m_chart(0),
    m_tooltip(0)
{
    LinAlg::Matrix<double> num = TF(1,1).getNum();
    LinAlg::Matrix<double> den = TF(1,1).getDen();
    LinAlg::Matrix<double> rootsNum = PolynomHandler::rootsNewtonBairstow(num);
    LinAlg::Matrix<double> rootsDen = PolynomHandler::rootsNewtonBairstow(den);

    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // chart
    m_chart = new QChart;
    m_chart->setMinimumSize(640, 480);
    m_chart->legend()->hide();

    series = new QScatterSeries*[2];
    series[0] = new QScatterSeries;
    series[1] = new QScatterSeries;
    series[0]->setMarkerSize(8.0);
    series[1]->setMarkerSize(8.0);

    if(num.getNumberOfColumns() > 1)
        for(unsigned i = 1; i <= rootsNum.getNumberOfRows(); ++i)
            series[0]->append(rootsNum(i,1),rootsNum(i,2));
    for(unsigned i = 1; i <= rootsDen.getNumberOfRows(); ++i)
        series[1]->append(rootsDen(i,1),rootsDen(i,2));

    for(double j = 0; j <= 50; j += 0.5)
    {
        double k = pow(j,2);
        PolynomHandler::Polynom<double> P1(k*num,"1"), P2(den,"1");
        rootsDen = PolynomHandler::rootsNewtonBairstow((P1+P2).getNum());
        for(unsigned i = 1; i <= rootsDen.getNumberOfRows(); ++i)
            series[1]->append(rootsDen(i,1),rootsDen(i,2));
    }

    m_chart->addSeries(series[0]);
    m_chart->addSeries(series[1]);

    m_chart->createDefaultAxes();
    m_chart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);
    scene()->addItem(m_chart);

    m_coordX = new QGraphicsSimpleTextItem(m_chart);
    m_coordY = new QGraphicsSimpleTextItem(m_chart);

    connect(series[0], SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
    connect(series[0], SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));
    connect(series[1], SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
    connect(series[1], SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));

    this->setMouseTracking(true);
}

LGR::LGR(const ModelHandler::TransferFunction<double> &G,
           const ModelHandler::TransferFunction<double> &H,
           QWidget *parent):
    QGraphicsView(new QGraphicsScene, parent),
    m_coordX(0),
    m_coordY(0),
    m_chart(0),
    m_tooltip(0)
{
    PolynomHandler::Polynom<double> N(G(1,1).getNum(),"1"),
                                    D(G(1,1).getDen(),"1"),
                                    Nh(H(1,1).getNum(),"1"),
                                    Dh(H(1,1).getDen(),"1");

    LinAlg::Matrix<double> num = (N*Dh).getNum();
    LinAlg::Matrix<double> den = (D*Dh+N*Nh).getNum();
    std::cout << PolynomHandler::Polynom<double>(num,den) << std::endl;
    LinAlg::Matrix<double> rootsNum = PolynomHandler::rootsNewtonBairstow(num);
    LinAlg::Matrix<double> rootsDen = PolynomHandler::rootsNewtonBairstow(den);

    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // chart
    m_chart = new QChart;
    m_chart->setMinimumSize(640, 480);
    m_chart->legend()->hide();

    series = new QScatterSeries*[2];
    series[0] = new QScatterSeries;
    series[1] = new QScatterSeries;

    if(num.getNumberOfColumns() > 1)
        for(unsigned i = 1; i <= rootsNum.getNumberOfRows(); ++i)
            series[0]->append(rootsNum(i,1),rootsNum(i,2));
    for(unsigned i = 1; i <= rootsDen.getNumberOfRows(); ++i)
        series[1]->append(rootsDen(i,1),rootsDen(i,2));


    series[0]->setMarkerSize(5.0);
    series[1]->setMarkerSize(5.0);
    for(double j = 0; j <= 50; j += 0.1)
    {
        double k = pow(j,2);
        rootsDen = PolynomHandler::rootsNewtonBairstow((D*Dh+k*N*Nh).getNum());
        for(unsigned i = 1; i <= rootsDen.getNumberOfRows(); ++i)
            series[1]->append(rootsDen(i,1),rootsDen(i,2));
    }

    m_chart->addSeries(series[0]);
    m_chart->addSeries(series[1]);

    m_chart->createDefaultAxes();
    m_chart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);
    scene()->addItem(m_chart);

    m_coordX = new QGraphicsSimpleTextItem(m_chart);
    m_coordY = new QGraphicsSimpleTextItem(m_chart);

    connect(series[0], SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
    connect(series[0], SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));
    connect(series[1], SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
    connect(series[1], SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));

    this->setMouseTracking(true);
}

LGR::LGR(const LinAlg::Matrix<double> &X, const LinAlg::Matrix<double> &Y,
           QWidget *parent)
    : QGraphicsView(new QGraphicsScene, parent),
      m_coordX(0),
      m_coordY(0),
      m_chart(0),
      m_tooltip(0)
{
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // chart
    m_chart = new QChart;
    m_chart->setMinimumSize(640, 480);
    m_chart->legend()->hide();

    series = new QScatterSeries*[X.getNumberOfRows()];
    for(unsigned i = 1; i <= X.getNumberOfRows(); ++i)
    {
        series[i] = new QScatterSeries;
        for(unsigned j = 1; j <= X.getNumberOfColumns(); ++j)
            series[i]->append(X(i,j), Y(i,j));

        m_chart->addSeries(series[i]);
    }

    m_chart->createDefaultAxes();
    m_chart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);
    scene()->addItem(m_chart);

    m_coordX = new QGraphicsSimpleTextItem(m_chart);
//    m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height());
//    m_coordX->setText("X: ");
    m_coordY = new QGraphicsSimpleTextItem(m_chart);
//    m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height());
//    m_coordY->setText("Y: ");

    for(unsigned i = 1; i <= X.getNumberOfRows(); ++i)
    {
        connect(series[i], SIGNAL(clicked(QPointF)), this, SLOT(keepCallout()));
        connect(series[i], SIGNAL(hovered(QPointF, bool)), this, SLOT(tooltip(QPointF,bool)));
    }

    this->setMouseTracking(true);
}

void LGR::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
         m_chart->resize(event->size());
         m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height() - 20);
         m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height() - 20);
         foreach (Callout *callout, m_callouts)
             callout->updateGeometry();
    }
    QGraphicsView::resizeEvent(event);
}

//void plot::mouseMoveEvent(QMouseEvent *event)
//{
//    m_coordX->setText(QString("X: %1").arg(m_chart->mapToValue(event->pos()).x()));
//    m_coordY->setText(QString("Y: %1").arg(m_chart->mapToValue(event->pos()).y()));
//    QGraphicsView::mouseMoveEvent(event);
//}

void LGR::keepCallout()
{
    m_callouts.append(m_tooltip);
    m_tooltip = new Callout(m_chart);
}

void LGR::tooltip(QPointF point, bool state)
{
    if (m_tooltip == 0)
        m_tooltip = new Callout(m_chart);

    if (state) {
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    } else {
        m_tooltip->hide();
    }
}

void LGR::setTitle(QString title)
{
    m_chart->setTitle(title);
}

void LGR::setRange(const double &xMin,
                    const double &xMax,
                    const double &yMin,
                    const double &yMax)
{
//    QScatterSeries *series = new QScatterSeries;
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(xMin, xMax);
//    axisX->setTickCount(10);
    axisX->setLabelFormat("%.2f");

    m_chart->setAxisX(axisX,series[0]);
    m_chart->setAxisX(axisX,series[1]);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(yMin, yMax);
//    axisY->setTickCount(10);
    axisY->setLabelFormat("%.2f");

    m_chart->setAxisY(axisY,series[0]);
    m_chart->setAxisY(axisY,series[1]);
}
