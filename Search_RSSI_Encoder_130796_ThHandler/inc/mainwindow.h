#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QMainWindow>
#include <inc/serial_message.h>
#include <QDir>
#include <QTimer>
#include <QThread>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QStandardItemModel>
#include <Worker.h>
#include <Worker_Serial.h>
#include <Rotator/tleconversion.h>
#include <Rotator/transformmatrix.h>
#include <Rotator/matrix_algebra.h>
#define pi 3.14159265358979323846

namespace Ui {
    class MainWindow;
}

#include <queue>
#include <iostream>
#include <functional>

using namespace std;
#define getMask(data, index)    ((data >> index) & 1)

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;

    struct task
    {
        int id;
        std::function<void()> f;
        void operator()(){f();}
    };

    queue<struct task> functions_queue;
    QThread* thread;
    QThread* serialRcvThread;
    Worker*  worker;
    Worker_Serial* worker_serial;



private slots:
    void on_btnSerialOpenClose_clicked();

    void on_btnForwardM_clicked();

    void on_btnStopMotor_clicked();

    void on_btnReverseM_clicked();

    void on_btnParkSerachAntena_clicked();

    void on_btnEmergencyStopMotor_clicked();

    void on_btnSetFreq_clicked();

    void on_btnSetAcc_clicked();

    void on_btnSetDeAcc_clicked();

    void readyDataSerialSerach();

    void TransmitMessage(QByteArray _msg, quint8 msg_ID);

    uint16_t gen_crc16_tx(const uint8_t *data, uint16_t size);

    //char parseByte(unsigned char Data);

    void CRC(uchar* buff, int size);

    //void on_chkShowSerialData_stateChanged(int arg1);

    void on_btnClearMaxData_clicked();

    void timerTick();

    void autoMoveManyCommandTimerTimerTick();

    void autoUncheckTimerTick();

    void TimerTestTick();

    void TimerTest2Tick();

    void ClosingTimerTick();

    void SecondTimerTick();

    void parseMessage(QByteArray msg, QDateTime dt);

    void setMainGraphData(int _grph, QVector<double> X,QVector<double> Y);

    double RSSI_SUM_Analyzor(double _rssi_sum);

    double RSSI_Delta_Analyzor(double _rssi_delta);

    double RSSI_SLC_Analyzor(double _rssi_slc);

    void on_btnResetMaxTable_clicked();

    void table_CellSelected(int _row,int _col);

    void on_btnOpenFile_clicked();

    void on_btnAnalyze_clicked();

    void writeMaxArratTo3D();

    void UpdateLists();

    void mainUpdateLists();

    void on_btnResetMaxTable_a_clicked();

    void on_chkAuto_toggled(bool checked);

    void forwardStyle();

    void stopStyle();

    void reverseStyle();
    void on_btnTest_clicked();

    void on_btnClearDiagrams_clicked();

    void errorString(QString &s);

    void on_btnForceExit_clicked();

    void on_btnSimplePLot_clicked();

    void on_btnSetAutoSpan_clicked();

    void on_btnMaxPlotAnaGO_clicked();

    void maxPlotGoBack(int cnt);

    void on_btnMaxPlotAnaBack_clicked();

    void on_rb_adc_EncoderPlot_toggled(bool checked);

    void on_btn_test2_clicked();

    void on_rb_LinearPlot_toggled(bool checked);

    void ResetAllPlots();

    void rcvDataSlot();

    void on_btnHighSum_clicked();

    void on_btnLowSum_clicked();

    void on_btnHighDelta_clicked();

    void on_btnLowDelta_clicked();

    void on_btnloadtlefromfile_2_clicked();

    void on_btnConvertTLETOLLA_2_clicked();

    void on_btnpredict_3_clicked();

    VectorXd  CalcVectorXd(QDateTime current,QString Line1,QString line2);

    void PerdictSat(QString line1, QString line2, QString satname);

    void on_pushButton_clicked();

    void on_btnperedict_clicked();

    void on_comboBoxGPS_currentIndexChanged(int index);

    void on_rbSelectDelta_toggled(bool checked);

    void on_btnsetFrequencyRotMCU_clicked();

private:
    QSerialPort *SerialSearch;
    QTimer *aliveCheckTimer;
    QTimer *autoUncheckTimer;
    QTimer *autoMoveManyCommandTimer;
    QTimer *TimerTest;
    QTimer *TimerTest2;


    QTimer *ClosingTimer;
    QTimer *SecondTimer;

    QStandardItemModel *model;
    QStandardItem *tableItem;

    // TLE Tab
    QStringList rotatorListOfSatsName ;
    QStringList rotatorListofSatsTle ;
    bool run;

    QTimer *rotatorDateTimeTimer;
    int rotatorIndexgrid ;
    QDateTime rotatorSatupDateTime;
    QDateTime rotatorSatDownDateTime;
    int countoftle;


public slots:
    void handleResults(const QString &);

signals:
    void operate(const QString &);
    void txDataSignal();
protected:
    void closeEvent(QCloseEvent *e);

};

#endif // MAINWINDOW_H
