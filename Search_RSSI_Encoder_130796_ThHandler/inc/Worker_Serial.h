#ifndef WORKER_SERIAL_H
#define WORKER_SERIAL_H

#include <QObject>
#include <QVector>
#include <QFile>
#include "Worker_Serial.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDateTime>

class Worker_Serial : public QObject
{
    Q_OBJECT
public:
    explicit Worker_Serial(QObject *parent = 0);
    ~Worker_Serial();
    QVector<uint8_t> dataRcvPersed;
    QVector<uint8_t> dataRcvPersedInternal;
    QByteArray dataTx;
    QString serialName;
    int serialBaudrate;
    bool serialConnected;
    bool ringBufferFull;
    int ringMsgNo;
    QVector < QVector< uint8_t > > vecTemp2d;
    QVector<QDateTime> vecTempDate;

    void beforProcess();
    void afterProcess();
signals:
    void finished();
    void rcvDataSignal();
    void error(QString err);

public slots:
    void process();
    void readyData();
    void txDataSlot();
private slots:
    char parseByte(unsigned char Data);
    uint16_t gen_crc16(const uint8_t *data,uint16_t size);

private:
    QSerialPort *SerialSearchThread;
    QDateTime *myDate;
    QByteArray dataTxInternal;
    QVector < QVector< uint8_t > > vecTemp2dInternal;
    QVector<QDateTime> vecTempDateInternal;

};

#endif // WORKER_SERIAL_H
