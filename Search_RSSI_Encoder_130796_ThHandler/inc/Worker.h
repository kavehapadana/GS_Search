#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QVector>
#include <QFile>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    ~Worker();
    void beforProcess();
    void afterProcess();
    int CntThread;
    QString serialFileName;
    QFile serialFileStream;
    QVector<double> tmDoubleList;
    QVector<double> RSSI_SUM_List;
    QVector<double> RSSI_Delta_List;
    QVector<double> timeList;
    QVector<double> DopplerList;
    QVector<double> FinalDegList;
    QVector<int> FinalRevList;
    QVector<double> EncDegList;
    QVector<int> EncRevList;
    QVector<double> RefDegList;
    QVector<int> RefRevList;
    QVector<uint> InterruptList;
    QVector<QString> tmStringList;
signals:
    void finished();
    void error(QString err);

public slots:
    void process();

};

#endif // WORKER_H
