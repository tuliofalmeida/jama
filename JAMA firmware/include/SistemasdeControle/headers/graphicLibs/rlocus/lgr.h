#ifndef PLOT_H
#define PLOT_H

#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>
#include <QtGui/QResizeEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtWidgets/QGraphicsTextItem>
#include <QValueAxis>
#include "SistemasdeControle/headers/graphicLibs/callout.h"
#include <QtGui/QMouseEvent>
#include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
#include "SistemasdeControle/headers/modelLibs/transferfunction.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

class Callout;

QT_CHARTS_USE_NAMESPACE

class LGR: public QGraphicsView
{
    Q_OBJECT

public:
//    plot(QWidget *parent = 0){}
    LGR(const LinAlg::Matrix<double> &X, const LinAlg::Matrix<double> &Y,
         QWidget *parent = 0);
    LGR(const ModelHandler::TransferFunction<double> &TF, QWidget *parent = 0);
    LGR(const ModelHandler::TransferFunction<double> &G, const ModelHandler::TransferFunction<double> &H, QWidget *parent = 0);
    void setTitle(QString title);
    void setRange(const double &xMin, const double &xMax, const double &yMin, const double &yMax);
//    void rlocus/*(const ModelHandler::TransferFunction<double> &TF)*/;

protected:
    void resizeEvent(QResizeEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

private:
    QGraphicsSimpleTextItem *m_coordX;
    QGraphicsSimpleTextItem *m_coordY;
    QChart *m_chart;
    Callout *m_tooltip;
    QList<Callout *> m_callouts;
    QScatterSeries **series;
};

#endif // PLOT_H
