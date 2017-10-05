#ifndef CUSTOMPLOTZOOM_H
#define CUSTOMPLOTZOOM_H

#include <QObject>
#include "qcustomplot.h"
#include <QPoint>

class QRubberBand;
class QMouseEvent;
class QWidget;
class CustomPlotZoom  : public QCustomPlot
{
    Q_OBJECT
public:
    //explicit CustomPlotZoom(QObject *parent = 0);
    CustomPlotZoom(QWidget * parent = 0);
    virtual ~CustomPlotZoom();
    void setZoomMode(bool mode);

signals:
    
private slots:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
private:
    bool mZoomMode;
    QRubberBand * mRubberBand;
    QPoint mOrigin;
};

#endif // CUSTOMPLOTZOOM_H
