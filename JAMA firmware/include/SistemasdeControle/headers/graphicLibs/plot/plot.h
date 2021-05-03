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
#include <QtGui/QMouseEvent>

//#define testPolynom
#ifdef testMatrix
    #include "../../../headers/primitiveLibs/LinAlg/matrix.h"
    #include "../../../headers/graphicLibs/callout.h"
#else
    #ifdef testPolynom
        #include "../../../headers/primitiveLibs/LinAlg/matrix.h"
        #include "../../../headers/graphicLibs/callout.h"
    #else
        #include "SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h"
        #include "SistemasdeControle/headers/graphicLibs/callout.h"
    #endif
#endif

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

class Plot: public QGraphicsView
{
    Q_OBJECT

public:
    Plot(QWidget *parent = 0);
    Plot(const LinAlg::Matrix<double> &X, const LinAlg::Matrix<double> &Y,
         QWidget *parent = 0, double windowSizeHeigh = 800, double windowSizeWidth = 600);
    void realTimeDataUpdate(const double &x, const double &y);
    void setTitle(QString title);
    void setxLabel(QString xLabel);
    void setyLabel(QString yLabel);
    void setRange(const double &xMin, const double &xMax, const double &yMin, const double &yMax);

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
    QSplineSeries **series;
};

#endif // PLOT_H
