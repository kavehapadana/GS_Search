#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPixmap>
#include <QGraphicsScene>
#include <qtconcurrentrun.h>
#include <QCloseEvent>
#include <QFileDialog>
#include <QQueue>
#include "CustomPlotZoom.h"
#include <QMovie>
#include <QLineEdit>
#include <serial_message_tx.h>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

#define GlobalVariables
#ifdef GlobalVariables
QDateTime *myDate;
bool oneStopCommandSend = true;
bool ParkAntena_b = false;
bool movingMotor = false;
bool MotorParked = false;
int MotorDirection = 0; // 0 : Stop, 1: Forward, -1: Reverse

bool fixedMCU_Alive = false; uint8_t cntMCU_Alive = 0;
bool checkAutoEnable = false;

float CenterofSpan = 0;
int Span = 0;
int atCnt = 0;

#define Plot_No  30
#define Plot_Offset  10
bool openedSerial = false;

QString serialFileName;

uint32_t Message_Index;
char Message_ID;
uint32_t Message_Length;
unsigned char Transmit_Check_Sum;

Message_Status_t  	Message_Status;
Message_t			Message;

AC_ID_t AC_ID;
uchar Global_temp[4];

typedef union
{
    uint16_t u16;
    uint8_t u8[2];
}u16_8_t2;
u16_8_t2 u16_8_tx;

MCU_Data_Array_t MCU_Data_u;
int ADC_Data_count = 0;
bool moveToForward = true;
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->gbAutoMove->setEnabled(false);
    ui->chkAuto->setEnabled(true);
    ui->ledDetect1->setColor(Qt::red);
    ui->ledRotaryMCU_State->setColor(Qt::red);
    ui->ledFixMCU_State->setColor(Qt::red);
    ui->ledRcvDataSum->setColor(Qt::red);
    ui->ledRcvDataDelta->setColor(Qt::red);
    ui->lePassWord->setEchoMode(QLineEdit::Password);

    myDate = new QDateTime();
    ui->btnAnalyze->setEnabled(false);
    ui->btnSimplePLot->setEnabled(false);
    //ui->hlPlotPicks->setEnabled(false);
    ui->btnMaxPlotAnaGO->setEnabled(false);
    ui->btnMaxPlotAnaBack->setEnabled(false);
    ui->pbPlotPicks->setValue(0);
    ui->pbPlotPicks->setEnabled(false);

    //======================TIMER=======================//

    aliveCheckTimer = new QTimer(this);
    aliveCheckTimer->setInterval(100);
    connect(aliveCheckTimer,SIGNAL(timeout()),this,SLOT(timerTick()));

    autoUncheckTimer = new QTimer(this);
    autoUncheckTimer->setInterval(300);
    connect(autoUncheckTimer,SIGNAL(timeout()),this,SLOT(autoUncheckTimerTick()));

    autoMoveManyCommandTimer = new QTimer(this);
    autoMoveManyCommandTimer->setInterval(300);
    connect(autoMoveManyCommandTimer,SIGNAL(timeout()),this,SLOT(autoMoveManyCommandTimerTimerTick()));

    TimerTest = new QTimer(this);
    TimerTest->setInterval(100);
    connect(TimerTest,SIGNAL(timeout()),this,SLOT(TimerTestTick()));

    ClosingTimer = new QTimer(this);
    ClosingTimer->setInterval(1000);
    connect(ClosingTimer,SIGNAL(timeout()),this,SLOT(ClosingTimerTick()));

    SecondTimer = new QTimer(this);
    SecondTimer->setInterval(1000);
    connect(SecondTimer,SIGNAL(timeout()),this,SLOT(SecondTimerTick()));
    SecondTimer->start();
    //======================TIMER=======================//

    //======================Threads=====================//
    worker_serial = new Worker_Serial();

    /*********************Table************************/
    /*QtableWidget*/
    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setColumnCount(5);
    QStringList m_tableHeader;
    m_tableHeader << "Deg" << "RSSI_SUM_Data" << "Dopp_Data" << "Time" << "AutoMove";
    ui->tableWidget->setHorizontalHeaderLabels(m_tableHeader);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: green;}");
    connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(table_CellSelected(int,int)));

    ui->tableWidget_a->setRowCount(6);
    ui->tableWidget_a->setColumnCount(5);
    QStringList m_tableHeader_a;
    m_tableHeader_a << "Deg" << "RSSI_SUM_Data" << "Dopp_Data" << "Time" << "AutoMove";
    ui->tableWidget_a->setHorizontalHeaderLabels(m_tableHeader_a);
    ui->tableWidget_a->verticalHeader()->setVisible(false);
    ui->tableWidget_a->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_a->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidget_a->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_a->setStyleSheet("QTableView {selection-background-color: green;}");
    /*QtableWidget*/
    /*********************Table************************/

    //=================================PLOT_Dopp===========
    ui->plot_Dopp->clearGraphs();
    ui->plot_Dopp->addGraph();
    ui->plot_Dopp->graph(0)->setPen(QPen(QColor(40, 110, 255))); // blue line

    ui->plot_Dopp->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot_Dopp->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plot_Dopp->graph(0)->setName("Doppler Data");
    ui->plot_Dopp->yAxis->setLabel("Doppler Data");
    ui->plot_Dopp->xAxis->setLabel("Time _ (sec.)");
    ui->plot_Dopp->xAxis->setRange(0, 10);

    //=================================PLOT_Delta===========
    ui->plot_RSSI_Delta->clearGraphs();
    ui->plot_RSSI_Delta->addGraph();
    ui->plot_RSSI_Delta->graph(0)->setPen(QPen(QColor(40, 110, 255))); // blue line

    ui->plot_RSSI_Delta->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot_RSSI_Delta->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plot_RSSI_Delta->graph(0)->setName("RSSI_Delta Data");
    ui->plot_RSSI_Delta->yAxis->setLabel("RSSI_Delta Data");
    ui->plot_RSSI_Delta->xAxis->setLabel("Time _ (sec.)");
    ui->plot_RSSI_Delta->xAxis->setRange(0, 10);

    //==============================RSSI_SUM_Delta==============
    ui->plot_RSSI_SUM_Delta->clearGraphs();
    ui->plot_RSSI_SUM_Delta->addGraph(); // blue line
    ui->plot_RSSI_SUM_Delta->graph(0)->setPen(QPen(Qt::blue));
    ui->plot_RSSI_SUM_Delta->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot_RSSI_SUM_Delta->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plot_RSSI_SUM_Delta->graph(0)->setName("RSSI_SUM_Delta Data");

    ui->plot_RSSI_SUM_Delta->addGraph(); // blue line
    ui->plot_RSSI_SUM_Delta->graph(1)->setPen(QPen(Qt::red));
    ui->plot_RSSI_SUM_Delta->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->plot_RSSI_SUM_Delta->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plot_RSSI_SUM_Delta->graph(1)->setName("RSSI_SUM_Delta Data");

    ui->plot_RSSI_SUM_Delta->addGraph(); // green line
    ui->plot_RSSI_SUM_Delta->graph(2)->setPen(QPen(Qt::yellow));
    ui->plot_RSSI_SUM_Delta->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->plot_RSSI_SUM_Delta->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plot_RSSI_SUM_Delta->graph(2)->setName("RSSI_SUM_Delta Data");

    ui->plot_RSSI_SUM_Delta->addGraph(); // blue line
    ui->plot_RSSI_SUM_Delta->graph(3)->setPen(QPen(Qt::green));
    ui->plot_RSSI_SUM_Delta->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->plot_RSSI_SUM_Delta->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plot_RSSI_SUM_Delta->graph(3)->setName("RSSI_SUM_Delta Data");

    ui->plot_RSSI_SUM_Delta->yAxis->setRange(0, 10);
    ui->plot_RSSI_SUM_Delta->yAxis->setLabel("RSSI_SUM_Delta Data");
    ui->plot_RSSI_SUM_Delta->xAxis->setLabel("Time _ (sec.)");
    ui->plot_RSSI_SUM_Delta->xAxis->setRange(0, 10);

    ///====================PLOT for Analyzer RSSI_SUM
    ui->plot_Analyzer_RSSI_SUM->clearGraphs();
    ui->plot_Analyzer_RSSI_SUM->addGraph(); // blue line
    ui->plot_Analyzer_RSSI_SUM->graph(0)->setPen(QPen(QColor(40, 110, 255)));

    ui->plot_Analyzer_RSSI_SUM->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot_Analyzer_RSSI_SUM->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plot_Analyzer_RSSI_SUM->yAxis->setRange(0, 10);
    ui->plot_Analyzer_RSSI_SUM->graph(0)->setName("RSSI_SUM Data");
    ui->plot_Analyzer_RSSI_SUM->yAxis->setLabel("RSSI_SUM Data");
    ui->plot_Analyzer_RSSI_SUM->xAxis->setLabel("Time _ (sec.)");
    ui->plot_Analyzer_RSSI_SUM->xAxis->setRange(0, 180);

    CustomPlotZoom CSZ;
    connect(ui->plot_Analyzer_RSSI_SUM, SIGNAL(mousePress(QMouseEvent*)), &CSZ, SLOT(mousePressEvent(QMouseEvent*)));
    connect(ui->plot_Analyzer_RSSI_SUM, SIGNAL(mouseRelease(QMouseEvent*)), &CSZ, SLOT(mouseReleaseEvent(QMouseEvent*)));
    connect(ui->plot_Analyzer_RSSI_SUM, SIGNAL(mouseMove(QMouseEvent*)), &CSZ, SLOT(mouseMoveEvent(QMouseEvent*)));


    //=========================PLOT_Dopp=================
    ui->plot_Analyzer_Dopp->clearGraphs();
    ui->plot_Analyzer_Dopp->addGraph(); // blue line
    ui->plot_Analyzer_Dopp->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->plot_Analyzer_Dopp->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot_Analyzer_Dopp->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->plot_Analyzer_Dopp->yAxis->setRange(0, 255);
    ui->plot_Analyzer_Dopp->graph(0)->setName("Doppler Data");
    ui->plot_Analyzer_Dopp->yAxis->setLabel("Doppler Data");
    ui->plot_Analyzer_Dopp->xAxis->setLabel("Time _ (sec.)");
    ui->plot_Analyzer_Dopp->xAxis->setRange(0, 180);

    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot_Dopp->graph(0)->rescaleAxes(true);
    ui->plot_RSSI_Delta->graph(0)->rescaleAxes(true);
    ui->plot_RSSI_SUM_Delta->graph(0)->rescaleAxes(true);
    ui->plot_RSSI_SUM_Delta->graph(1)->rescaleAxes(true);
    ui->plot_RSSI_SUM_Delta->graph(2)->rescaleAxes(true);
    ui->plot_RSSI_SUM_Delta->graph(3)->rescaleAxes(true);

    ui->plot_Analyzer_RSSI_SUM->graph(0)->rescaleAxes(true);
    ui->plot_Analyzer_Dopp->graph(0)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->plot_Dopp->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_RSSI_Delta->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_RSSI_SUM_Delta->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(ui->plot_Dopp->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_Dopp->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot_Dopp->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_Dopp->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->plot_RSSI_Delta->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_RSSI_Delta->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot_RSSI_Delta->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_RSSI_Delta->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->plot_RSSI_SUM_Delta->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_RSSI_SUM_Delta->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot_RSSI_SUM_Delta->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_RSSI_SUM_Delta->yAxis2, SLOT(setRange(QCPRange)));

    ui->plot_Analyzer_RSSI_SUM->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot_Analyzer_Dopp->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    connect(ui->plot_Analyzer_RSSI_SUM->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_Analyzer_RSSI_SUM->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot_Analyzer_RSSI_SUM->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_Analyzer_RSSI_SUM->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->plot_Analyzer_Dopp->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_Analyzer_Dopp->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plot_Analyzer_Dopp->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_Analyzer_Dopp->yAxis2, SLOT(setRange(QCPRange)));


    //connect(ui->chkPlotSUM,toggled())
    //==============================Thread============

    //================================SerialSearch======================
    SerialSearch = new QSerialPort(this);
    QString sBaudrates("1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200");
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        ui->cmbSerialComSearch->addItem(info.portName(),info.portName());
    }
    ui->cmbSerialBaud->addItems(sBaudrates.split(","));
    ui->cmbSerialBaud->setCurrentIndex(3);

    QImage imageObject;
    imageObject.load("mm.jpg");

    ui->btnStopMotor->setEnabled(false);
    ui->btnForwardM->setEnabled(false);
    ui->btnReverseM->setEnabled(false);
    ui->btnEmergencyStopMotor->setEnabled(false);
    ui->btnEmergencyStopMotor->setStyleSheet("background-color:Orange; color: white;");
    ui->btnParkSerachAntena->setStyleSheet("background-color:green; color: white;");

    ui->btnSetFreq->setEnabled(false);
    ui->btnSetAcc->setEnabled(false);
    ui->btnSetDeAcc->setEnabled(false);

    ui->txtFreq->setText("5000");
    ui->txtFreq->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->txtAcc->setText("50");
    ui->txtDeAcc->setText("50");
    ui->txtSpan->setText("15");
    ui->txtCenterOfSpan->setText("100");
    ui->leCoefAnlyzorSum->setText("1");
    ui->leOffsetAnalyzerSum->setText("0");
    ui->leCoefAnlyzorDelta->setText("1");
    ui->leOffsetAnalyzerDelta->setText("0");
    CenterofSpan = ui->txtCenterOfSpan->text().toFloat();
    Span = ui->txtSpan->text().toInt();

//    ui->letPass->setEchoMode(QLineEdit::Password);
//    ui->letPass->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->lbl_MoveStatus->setStyleSheet("QLabel { background-color : rgb(170, 255, 127); color : black; }"); // Green
    ui->lbl_MoveStatus->setText("Stopped");
    ui->lbl_MoveStatus->setStyleSheet("QLabel { background-color : rgb(255, 170, 0); color : black; }"); // Orange

    ui->btnForwardM->setStyleSheet("QPushButton { background-color : rgb(255, 170, 0); color : black; }");
    ui->btnReverseM->setStyleSheet("QPushButton { background-color : rgb(255, 170, 0); color : black; }");
    ui->btnStopMotor->setStyleSheet("QPushButton { background-color : rgb(255, 170, 0); color : black; }");
    //==============
    ui->btnAnalyze->setEnabled(false);
    ui->lbl_load->setText("Not Load");
    ui->lbl_load->setStyleSheet("QLabel { background-color : red; color : black; }");

    ui->txtDataC_Size->setText("50");    //==============

    //==================TLE==================//
    ui->comboBoxGPS->addItem("Sharif UT");
    ui->comboBoxGPS->addItem("Mahdasht");
    ui->comboBoxGPS->addItem("Qeshm");
    ui->comboBoxGPS->addItem("Bushehr");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete SerialSearch;
    delete myDate;
    workerThread.quit();
    workerThread.wait();

}

void MainWindow::on_btnSerialOpenClose_clicked()
{
    QString strSys = "echo " + ui->lePassWord->text() + " | sudo -S chmod 777  /dev/" + ui->cmbSerialComSearch->currentText();
    //QString strSys = "echo 1 | sudo -S chmod 777 /dev/ttyUSB0";
    int passOK = system(strSys.toLatin1().data());

    QMovie *movie = new QMovie("../Res/ajax-loader.gif");
    ui->lbl_AnimationSerial->setMovie(movie);
    ui->lbl_AnimationSerial->show();
    movie->start();

    if(!passOK)
    {
     if(!openedSerial)
        {
         serialRcvThread = new QThread;
         aliveCheckTimer->start();
         QString serName = ui->cmbSerialComSearch->currentText();
         worker_serial->serialName = serName;
         //SerialSearch->setPortName();
         QString baudrate_str = ui->cmbSerialBaud->currentText();
         int baudrate = baudrate_str.toInt();

         worker_serial->serialBaudrate = baudrate;
         worker_serial->moveToThread(serialRcvThread);
         connect(serialRcvThread, SIGNAL(started()), worker_serial, SLOT(process()));
         connect(worker_serial, SIGNAL(finished()), serialRcvThread, SLOT(quit()));
         connect(worker_serial, SIGNAL(rcvDataSignal()), this, SLOT(rcvDataSlot()));
         connect(this, SIGNAL(txDataSignal()), worker_serial, SLOT(txDataSlot()));
         connect(worker_serial, SIGNAL(finished()), worker_serial, SLOT(deleteLater()));
         connect(serialRcvThread, SIGNAL(finished()), serialRcvThread, SLOT(deleteLater()));
         serialRcvThread->start();
         sleep(1);
         if (worker_serial->serialConnected)
         {
             openedSerial = true;
             ui->lbl_serialStatus->setText("Connected");
             ui->btnSerialOpenClose->setText("Disconnect");

             QString logFileName = qApp->applicationDirPath() + "/log";
             if(!QDir(logFileName).exists())
                 QDir().mkdir(logFileName);

             //ui->gbAutoMove->setEnabled(true);

            serialFileName = qApp->applicationDirPath() + "/log/" + "RSSI_Data_" + myDate->currentDateTime().toString("dd_MM_yyyy_hh:mm") + ".csv" ;
            QFile serialFileStream(serialFileName);
            if(serialFileStream.open(QIODevice::ReadWrite))
            {
                 QTextStream mystream(&serialFileStream);
                 mystream <<"date"<<" "<<"Time"<< "," << "SecTime" << "," << "Final_Deg" << "," << "Final_Rev" << "," << "Enc_Deg" << "," << "Enc_Rev" << "," << "Ref_Deg" << "," << "Ref_Rev" << "," << "Doppler_data" << "," << "RSSI_SUM_Data" << "," << "RSSI_Delta_Data" << "," << "Detection" << "," << endl;
            }
            serialFileStream.close();
            atCnt = 24;
            ui->txtFreq->setText("5000");
            autoUncheckTimer->start();

            thread = new QThread;
            worker = new Worker();

            worker->serialFileName = serialFileName;
            worker->beforProcess();
            worker->moveToThread(thread);
            connect(thread, SIGNAL(started()), worker, SLOT(process()));
            connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
            connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->start();
         }
         else
         {
             openedSerial = false;
             ui->lbl_serialStatus->setText("Disconnected");
             ui->btnSerialOpenClose->setText("Conncet");
             QMessageBox::warning(this, "Error", "Couldn't Connect serial port");
         }
     }
     else
     {
         openedSerial = false;
         aliveCheckTimer->stop();
         ui->lbl_serialStatus->setText("DisConnected");
         ui->btnSerialOpenClose->setText("Connect");
         disconnect(worker_serial, SIGNAL(rcvDataSignal()), this, SLOT(rcvDataSlot()));
         usleep(500);
         disconnect(this, SIGNAL(txDataSignal()), worker_serial, SLOT(txDataSlot()));
         worker_serial->afterProcess();
         //worker_serial = NULL;
         //serialRcvThread = NULL;
     }
    }
    else
    {
        QMessageBox::warning(this, "Error", "Your PC Password was not Correct\n please Enter Corrrect Password");
    }
    if(openedSerial)
    {

        ui->vlMotor->setEnabled(true);
        ui->btnStopMotor->setEnabled(true);
        ui->btnForwardM->setEnabled(true);
        ui->btnReverseM->setEnabled(true);
        ui->btnEmergencyStopMotor->setEnabled(true);
        ui->lbl_serialStatus->setStyleSheet("QLabel { background-color : green; color : white; }");
        ui->btnSetFreq->setEnabled(true);
        ui->btnSetAcc->setEnabled(true);
        ui->btnSetDeAcc->setEnabled(true);
    }
    else
    {
        ui->vlMotor->setEnabled(false);
        ui->btnStopMotor->setEnabled(false);
        ui->btnForwardM->setEnabled(false);
        ui->btnReverseM->setEnabled(false);
        ui->btnEmergencyStopMotor->setEnabled(false);
        ui->lbl_serialStatus->setStyleSheet("QLabel { background-color : red; color : black; }");
        ui->btnSetFreq->setEnabled(false);
        ui->btnSetAcc->setEnabled(false);
        ui->btnSetDeAcc->setEnabled(false);
    }
    movie->stop();
}

int AliveCnt = 0;
void MainWindow::timerTick()
{
    if(AliveCnt++ > 200)
    {
        AliveCnt = 0;
        QByteArray Message;
        Message[0] = 0;
        TransmitMessage(Message,msgAlive_ID);
    }

    if(!fixedMCU_Alive)
    {
        if(++cntMCU_Alive >= 10)
        {
            ui->ledFixMCU_State->setColor(Qt::red);
            cntMCU_Alive == 0;
        }
    }
    else
    {
        cntMCU_Alive = 0;
        ui->ledFixMCU_State->setColor(Qt::green);
    }
}

void MainWindow::forwardStyle()
{
    ui->lbl_MoveStatus->setText("Forwarding");
    ui->lbl_MoveStatus->setStyleSheet("QLabel { background-color : rgb(255, 170, 0); color : black; }"); // Orange

    ui->btnForwardM->setStyleSheet("QPushButton { background-color : rgb(170, 255, 127); color : black; }");
    ui->btnReverseM->setStyleSheet("QPushButton { background-color : rgb(255, 170, 0); color : black; }");
    ui->btnStopMotor->setStyleSheet("QPushButton { background-color : rgb(255, 170, 0); color : black; }");
}

void MainWindow::stopStyle()
{
    ui->lbl_MoveStatus->setText("Stopped");
    ui->lbl_MoveStatus->setStyleSheet("QLabel { background-color : rgb(255, 170, 0); color : black; }"); // Orange

    ui->btnForwardM->setStyleSheet("QPushButton { background-color : rgb(255, 170, 0); color : black; }");
    ui->btnReverseM->setStyleSheet("QPushButton { background-color : rgb(255, 170, 0); color : black; }");
    ui->btnStopMotor->setStyleSheet("QPushButton { background-color : rgb(170, 255, 127); color : black; }");
}

void MainWindow::reverseStyle()
{
    ui->lbl_MoveStatus->setText("Reversed");
    ui->lbl_MoveStatus->setStyleSheet("QLabel { background-color : rgb(255, 170, 0); color : black; }"); // Orange

    ui->btnForwardM->setStyleSheet("QPushButton { background-color : rgb(255, 170, 0); color : black; }");
    ui->btnReverseM->setStyleSheet("QPushButton { background-color : rgb(170, 255, 127); color : black; }");
    ui->btnStopMotor->setStyleSheet("QPushButton { background-color : rgb(255, 170, 0); color : black; }");
}

void MainWindow::ClosingTimerTick()
{
    ParkAntena_b = true;
    if(MotorParked && !movingMotor)
    {
        qApp->quit();
    }
}

void MainWindow::SecondTimerTick()
{
    fixedMCU_Alive = false;
}

void MainWindow::handleResults(const QString &)
{

}

QByteArray dataRCV;
int cntDataRcvPacket = 0;
void MainWindow::rcvDataSlot()
{
    QVector < QVector< uint8_t > > vecTemp2d;
    vecTemp2d = worker_serial->vecTemp2d;
    QVector <QDateTime> vecTempDate = worker_serial->vecTempDate;
    for(int i = 0;i< vecTemp2d.size();i++)
    {
        QVector <uint8_t> dataRcvVector = vecTemp2d[i];
        QDateTime dt = vecTempDate[i];
        QByteArray qba;
        QDataStream str(&qba,QIODevice::WriteOnly);
        for(auto x : dataRcvVector)
            str << x;
        parseMessage(qba,dt);
    }
    worker_serial->ringBufferFull = false;
}

void MainWindow::on_btnForwardM_clicked()
{
    //ui->chkAuto->setEnabled(true);

    QByteArray Message;
    moveToForward = true;
    Message[0] = 0;
    TransmitMessage(Message,AC_FORWARD);
    oneStopCommandSend = false;
    ParkAntena_b = false;
}

void MainWindow::on_btnStopMotor_clicked()
{
    QByteArray Message;
    moveToForward = false;
    Message[0] = 0;
    TransmitMessage(Message,AC_STOP);
    oneStopCommandSend = true;
    //ui->chkAuto->setEnabled(false);
    //    atCnt = 10;
    //    autoUncheckTimer->start();

}

void MainWindow::on_btnReverseM_clicked()
{
    QByteArray Message;
    moveToForward = false;
    Message[0] = 0;
    TransmitMessage(Message,AC_REVERSE);
    oneStopCommandSend = false;
    ParkAntena_b = false;
}

void MainWindow::on_btnEmergencyStopMotor_clicked()
{
    QByteArray Message;
    Message[0] = 0;
    TransmitMessage(Message,AC_EGC_STOP);
}

void MainWindow::CRC(uchar buff[], int size)
{
    uint crc = 0xFFFF;
    uchar myTemp2[6];
    memcpy(myTemp2,buff,6);
    for(int pos = 0; pos < size; pos++)
    {
        crc ^= (uint) buff[pos];
        for(int i = 8; i!= 0; i--)
        {
            if((crc & 0x0001) !=0 )
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
                crc >>= 1;
        }
    }

    Global_temp[0] = crc & 0x0FF;
    Global_temp[1] = (crc >> 8) & 0x0FF;
    Global_temp[2] = (crc >> 16) & 0x0FF;
    Global_temp[3] = (crc >> 24) & 0x0FF;
}

void MainWindow::on_btnSetFreq_clicked()
{
    QString Freq_str = ui->txtFreq->text();
    int _freq = Freq_str.toInt();
    if(_freq > 6000)
        _freq = 6000;
    if(_freq < 1000)
        _freq = 1000;
    uchar byte0 = _freq & 0x0FF;
    uchar byte1 = (_freq >> 8) & 0x0FF;
    QByteArray Message;
    Message[0] = byte0;
    Message[1] = byte1;
    TransmitMessage(Message,AC_FREQ);
}

void MainWindow::on_btnSetAcc_clicked()
{
    QString Acc_str = ui->txtAcc->text();
    int _acc = Acc_str.toInt();

    uchar byte0 = _acc & 0x0FF;
    uchar byte1 = (_acc >> 8) & 0x0FF;
    QByteArray Message;
    Message[0] = byte0;
    Message[1] = byte1;
    TransmitMessage(Message,AC_ACC);
}

void MainWindow::on_btnSetDeAcc_clicked()
{
    QString DeAcc_str = ui->txtDeAcc->text();
    int De_acc = DeAcc_str.toInt();

    uchar byte0 = De_acc & 0x0FF;
    uchar byte1 = (De_acc >> 8) & 0x0FF;
    QByteArray Message;
    Message[0] = byte0;
    Message[1] = byte1;
    TransmitMessage(Message,AC_DEC);
}

void MainWindow::on_btnParkSerachAntena_clicked()
{
    ParkAntena_b = true;
    QByteArray Message;
    Message[0] = 0;
    TransmitMessage(Message,AC_PARK);
}

void MainWindow::readyDataSerialSerach()
{
    QByteArray data = SerialSearch->readAll();
    for(int i = 0; i < data.size(); i++)
        i = 0;
        //parseByte((unsigned char)data[i]);
        //char msg_ID = parseByte((unsigned char)data[i]);
}

void MainWindow::TransmitMessage(QByteArray _msg, quint8 msg_ID)
{
    QByteArray  tranMSG;
    tranMSG.append(msgTrans_Sync1);
    tranMSG.append(msgTrans_Sync2);
    quint8 chkSum = 0;
    tranMSG.append(msg_ID);
    chkSum += msg_ID;

    tranMSG.append(_msg.size());
    chkSum += _msg.size();
    uint8_t msgg[_msg.size()];

    for(int i=0; i<_msg.size(); i++)
    {
        tranMSG.append(_msg[i]);
        chkSum += _msg[i];
        msgg[i] = _msg[i];
    }

    u16_8_tx.u16 = gen_crc16_tx(msgg,_msg.size());
    tranMSG.append(u16_8_tx.u8[0]);
    tranMSG.append(u16_8_tx.u8[1]);
    if(worker_serial->serialConnected)
    {
        worker_serial->dataTx = tranMSG;
        emit txDataSignal();
    }

}

#define CRC16_TX 0x8005
uint16_t MainWindow::gen_crc16_tx(const uint8_t *data, uint16_t size)
{
    uint16_t out =0;
    int bits_read = 0, bit_flag;

    if(data == NULL)
        return 0;

    while(size > 0)
    {
        bit_flag = out >> 15;

        /* Get next bit */
        out <<= 1;
        out |= (*data >> bits_read) & 1;

        bits_read++;
        if(bits_read > 7)
        {
            bits_read = 0;
            data++;
            size--;
        }
        /* Cycle Check */
        if(bit_flag)
            out ^= CRC16_TX;
    }
    int i;
    for(i = 0; i < 16 ; i++)
    {
        bit_flag = out >> 15;
        out <<= 1;
        if(bit_flag)
            out ^= CRC16_TX;
    }

    uint16_t crc = 0;
    i = 0x8000;
    int j = 0x0001;
    for(; i != 0; i >>= 1, j <<= 1){
        if(i & out) crc |= j;
    }

    return crc;
}

typedef enum
{
    msgUNINIT_RSSI_SUM,
    msgGOT_SYNC1_RSSI_SUM,
    msgGOT_SYNC2_RSSI_SUM,
    msgGOT_PAYLOAD_RSSI_SUM
} Message_Status_RSSI_SUM_t;

float lastEnc = 0;
float lastTime = 0;
int dataCounter = 0;
int nn = 0;
int dataCnt = 0;

QVector<double>     RSSI_SUM_List,RSSI_SUM_List0,RSSI_SUM_List1;
QVector<double>     DopplerList,DopplerList0,DopplerList1;
QVector<double>     FinalDegList,FinalDegList0,FinalDegList1;
QVector<double>     RSSI_Delta_List;

QVector<double>     RSSI_SUM_Analyzor_Mean_List;
QVector<double>     RSSI_Delta_Analyzor_Mean_List;
QVector<QString>    tmStringTableList,tmStringTableList0,tmStringTableList1;
QVector<double>     timeList;
QVector<double>     finalDegPlotList;
QVector<int>        FinalRevList;
QVector<double>     EncDegList;
QVector<int>        EncRevList;
QVector<double>     RefDegList;
QVector<int>        RefRevList;
QVector<uint>       InterruptList;
QVector<QString>    tmStringList;
QVector<double>     tmDoubleList;
QVector<double>     RSSI_SUM_List_Polar_X;
QVector<double>     RSSI_SUM_List_Polar_Y;
QVector<double>     Doppler_List_Polar_X;
QVector<double>     Doppler_List_Polar_Y;
QVector<double>     RSSI_Delta_List_Polar_X;
QVector<double>     RSSI_Delta_List_Polar_Y;

QVector<double>     RSSI_SUM_List_Ploting;
QVector<double>     RSSI_Delta_List_Ploting;
QVector<double>     RSSI_SUM_Analyzer_List_Ploting;
QVector<double>     RSSI_Delta_Analyzer_List_Ploting;
QVector<double>     DopplerList_Ploting;
QVector<double>     FinalDegList_Ploting;
QVector<double>     timeList_Ploting;

QVector<double>     RSSI_SUM_List_Sanp(4096,0);
QVector<double>     RSSI_Delta_List_Sanp(4096,0);
QVector<double>     DopplerList_Sanp(4096,0);
QVector<double>     FinalDegList_Sanp(4096,0);
QVector<bool>       validDataList_Sanp(4096,false);
QVector<double>     timeList_Sanp(4096,0);

QVector<double>     RSSI_SUM_List_SanpPlot;
QVector<double>     RSSI_Delta_List_SanpPlot;
QVector<double>     DopplerList_SanpPlot;
QVector<double>     FinalDegList_SanpPlot;
QVector<double>     timeList_SnapPlot;

QVector<double>     RSSI_SUM_List_Ploting_Polar_X;
QVector<double>     RSSI_SUM_List_Ploting_Polar_Y;
QVector<double>     Doppler_List_Ploting_Polar_X;
QVector<double>     Doppler_List_Ploting_Polar_Y;
QVector<double>     RSSI_Delta_List_Ploting_Polar_X;
QVector<double>     RSSI_Delta_List_Ploting_Polar_Y;

QVector<double>     RSSI_SUM_List_Snap_Polar_X(4096,0);
QVector<double>     RSSI_SUM_List_Snap_Polar_Y(4096,0);
QVector<double>     Doppler_List_Snap_Polar_X(4096,0);
QVector<double>     Doppler_List_Snap_Polar_Y(4096,0);
QVector<double>     RSSI_Delta_List_Snap_Polar_X(4096,0);
QVector<double>     RSSI_Delta_List_Snap_Polar_Y(4096,0);

QVector<double>     RSSI_SUM_List_SnapPloting_Polar_X;
QVector<double>     RSSI_SUM_List_SnapPloting_Polar_Y;
QVector<double>     Doppler_List_SnapPloting_Polar_X;
QVector<double>     Doppler_List_SnapPloting_Polar_Y;
QVector<double>     RSSI_Delta_List_SnapPloting_Polar_X;
QVector<double>     RSSI_Delta_List_SnapPloting_Polar_Y;

int Doppler = 0;
int degNo = 0;
bool toggleOddEvenRotation = false;
bool OnlyOneIf = true;
int CntForCheckMovingMotor = 0;
float movingEncoderData[2];

/* AutoTrcker  */
bool SnapOnEnable = false;
/* AutoTrcker  */

/*find picks*/
int peaksCnt = 0;
QVector<double> maxRSSI_SUM_List;
QMap<double,QString> DegTimeMaxMap;
QMap<double,double> DegDataMaxMap;
QMap<double,double> DegDoppMaxMap;
double maxFinder[3] = {0,0,0};
/*find picks*/

int minOfMoveDeg;
int maxOfMoveDeg;
int packageCnt = 0;
uint8_t packageNO = 10;
int packetSize = 100;
bool S_1 = true,S_2 = true;
int atMMCT = 0;
int buffDegreeTest[2];

void MainWindow::on_btnClearMaxData_clicked()
{
    ui->plot_Dopp->graph(0)->clearData();
    ui->plot_RSSI_Delta->graph(0)->clearData();
    ui->plot_RSSI_SUM_Delta->graph(0)->clearData();
    ui->plot_RSSI_SUM_Delta->graph(1)->clearData();
    ui->plot_RSSI_SUM_Delta->graph(2)->clearData();
    ui->plot_RSSI_SUM_Delta->graph(3)->clearData();

}
void MainWindow::on_btnSetAutoSpan_clicked()
{
    float CS = ui->txtCenterOfSpan->text().toFloat();
    if(((CS < 0) | (CS > 359)))
    {
        QMessageBox::warning(this, "Error", "Center of Span must be in 0 to 359 region\n Value set to defual: 100");
        ui->chkAuto->setCheckState(Qt::Unchecked);
        ui->txtCenterOfSpan->setText("100");
    }
    else
    {
        ui->txtCenterOfSpan->setText(QString::number(CS,'f',1));
    }
    CenterofSpan = ui->txtCenterOfSpan->text().toFloat();

    float sp = ui->txtSpan->text().toInt();
    if((sp < 15) | (sp > 60))
    {
        QMessageBox::warning(this, "Error", "Span must be in 8 to 60 region\n Value set to defual: 8");
        ui->chkAuto->setCheckState(Qt::Unchecked);
        ui->txtSpan->setText("15");
    }
    else
    {
        ui->txtSpan->setText(QString::number(sp));
    }
    Span = ui->txtSpan->text().toInt();

}
void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "GS_Search",
                                                                tr("Are you sure to close the program?\n The AC Motor will be Stoped"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes)
    {

        event->ignore();
    }
    else {
        if(movingMotor)
            event->ignore();
        ClosingTimer->start();
        //event->accept();
    }
}
void MainWindow::on_btnResetMaxTable_clicked()
{
    maxRSSI_SUM_List.clear();
    DegDataMaxMap.clear();
    DegTimeMaxMap.clear();
    DegDoppMaxMap.clear();
    peaksCnt = 0;
    for(int i = 0; i < 6;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString("")));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString("")));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString("")));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString("")));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString("")));
    }
}
void MainWindow::table_CellSelected(int _row,int _col)
{
    if(_col != 4)
        return;

    //on_btnReverseM_clicked();

    atCnt = 5;
    ui->txtFreq->setText("1000");
    autoUncheckTimer->start();
    QString _Deg_str = ui->tableWidget->item(_row,0)->text();
    ui->txtCenterOfSpan->setText(QString::number(_Deg_str.toFloat(),'f',1));
    if(MotorDirection == -1)
        checkAutoEnable = false;
    else
        checkAutoEnable = true;

    //ui->chkAuto->setChecked(true);
    float _Deg_float = _Deg_str.toFloat();
    uint _max = ui->tableWidget->item(_row,1)->text().toUInt();
    maxRSSI_SUM_List.append(_max);
    DegDataMaxMap.insert(_Deg_float,_max);
    DegTimeMaxMap.insert(_Deg_float,ui->tableWidget->item(_row,3)->text());
    DegDoppMaxMap.insert(_Deg_float,ui->tableWidget->item(_row,2)->text().toInt());

    if(!SnapOnEnable)
        on_btnResetMaxTable_clicked();
    SnapOnEnable = true;
}
void MainWindow::on_btnClearDiagrams_clicked()
{
    ResetAllPlots();
}
void MainWindow::on_chkAuto_toggled(bool checked)
{
    ResetAllPlots();
    if(checked)
    {
        //ui->txtFreq->setText("1000");
        //on_btnSetFreq_clicked();
    }
    else
    {
        //ui->txtFreq->setText("5000");
        //autoUncheckTimer->start();
        SnapOnEnable = false;
    }
}
void MainWindow::autoMoveManyCommandTimerTimerTick()
{
    atMMCT++;
    switch(atMMCT)
    {
        case 1:
            on_btnReverseM_clicked();
                break;

        case 2:
            on_btnReverseM_clicked();
            break;

        case 3:
            atMMCT=0;
            on_btnReverseM_clicked();
            autoMoveManyCommandTimer->stop();
            break;

        case 11:
            on_btnForwardM_clicked();
            break;

        case 12:
            on_btnForwardM_clicked();
            break;

        case 13:
            atMMCT = 0;
            on_btnForwardM_clicked();
            autoMoveManyCommandTimer->stop();
            break;
    }
}
void MainWindow::autoUncheckTimerTick()
{
    atCnt++;
    switch(atCnt)
    {
        case 1:
                on_btnForwardM_clicked();
            break;

        case 2:
                on_btnSetFreq_clicked();
            break;

        case 3:
                atCnt = 0;
                autoUncheckTimer->stop();
            break;

        case 6:
                on_btnSetAutoSpan_clicked();
        break;
        case 7:
                on_btnReverseM_clicked();
            break;

        case 8:
                on_btnSetFreq_clicked();
            break;

        case 9:
                atCnt = 0;
                autoUncheckTimer->stop();
            break;
        case 15:
                on_btnStopMotor_clicked();
            break;

        case 16:
                atCnt = 0;
                autoUncheckTimer->stop();
            break;

        case 25:
                on_btnSetFreq_clicked();
            break;

        case 26:
                atCnt = 0;
                autoUncheckTimer->stop();
            break;
    }
}
int CntTimerTest = 0;
void MainWindow::TimerTestTick()
{
    CntTimerTest++;
    qDebug() << CntTimerTest;
    on_btnForwardM_clicked();
    if(CntTimerTest  > 300)
        TimerTest->stop();
}
void MainWindow::on_btnTest_clicked()
{

}
void MainWindow::errorString(QString &s)
{

    qDebug() << "An Error Occured" << s;
}
void MainWindow::on_btnForceExit_clicked()
{
    QApplication::exit();
}

QVector<double> RSSI_SUM_List_a0,RSSI_SUM_List_a1,RSSI_SUM_List_a2;
QVector<double> DopplerList_a0,DopplerList_a1,DopplerList_a2;
QVector<double> FinalDegList_a0,FinalDegList_a1,FinalDegList_a2;
QVector<QString> tmStringTableList_a0,tmStringTableList_a1,tmStringTableList_a2;
QVector<double> maxRSSI_SUM_List_a;

int lineCnt = 0;
void MainWindow::on_btnOpenFile_clicked()
{
    DopplerList.clear();
    RSSI_SUM_List.clear();
    RSSI_Delta_List.clear();
    FinalDegList.clear();
    tmStringTableList.clear();
    maxRSSI_SUM_List_a.clear();

    RSSI_SUM_List_Polar_X.clear();
    RSSI_SUM_List_Polar_Y.clear();
    Doppler_List_Polar_X.clear();
    Doppler_List_Polar_Y.clear();
    RSSI_Delta_List_Polar_X.clear();
    RSSI_Delta_List_Polar_Y.clear();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"../",tr("Files (*.csv)"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    lineCnt = 0;
    while(!in.atEnd())
    {
        QString lineTxt = in.readLine();
        QStringList txtSplitted = lineTxt.split(',');

        if(lineCnt >= 1 & txtSplitted.size() > 2)
        {
            ui->lbl_load->setText("Loaded");
            ui->lbl_load->setStyleSheet("QLabel { background-color : green; color : black; }");
            RSSI_SUM_List.append((txtSplitted.at(7)).toDouble());
            tmStringTableList.append(((txtSplitted.at(0)).split(' ')).at(1));
            FinalDegList.append((txtSplitted.at(2)).toDouble());
            FinalRevList.append((txtSplitted.at(5)).toDouble());
            DopplerList.append((txtSplitted.at(6)).toDouble());
        }
        lineCnt++;
    }
    lineCnt--; /* the linecnt is one more after while */

    if(lineCnt > 2)
    {
        ui->btnAnalyze->setEnabled(true);
        ui->btnSimplePLot->setEnabled(true);
    }
    else
    {
        ui->btnAnalyze->setEnabled(false);
        ui->btnSimplePLot->setEnabled(false);
        ui->lbl_load->setText("Not Load");
        ui->lbl_load->setStyleSheet("QLabel { background-color : red; color : black; }");
    }
}

int peaksCnt_a = 0;
QMap<double,QString> DegTimeMaxMap_a;
QMap<double,double> DegDataMaxMap_a;
QMap<double,double> DegDoppMaxMap_a;
double maxFinder_a[3] = {0,0,0};

void MainWindow::UpdateLists()
{
    RSSI_SUM_List_a0 = RSSI_SUM_List_a1;
    RSSI_SUM_List_a1 = RSSI_SUM_List_a2;

    DopplerList_a0 = DopplerList_a1;
    DopplerList_a1 = DopplerList_a2;

    FinalDegList_a0 = FinalDegList_a1;
    FinalDegList_a1 = FinalDegList_a2;

    tmStringTableList_a0 = tmStringTableList_a1;
    tmStringTableList_a1 = tmStringTableList_a2;
}
void MainWindow::mainUpdateLists()
{
    RSSI_SUM_List0 = RSSI_SUM_List1;
    RSSI_SUM_List1 = RSSI_SUM_List;

    DopplerList0 = DopplerList1;
    DopplerList1 = DopplerList;

    FinalDegList0 = FinalDegList1;
    FinalDegList1 = FinalDegList;

    tmStringTableList0 = tmStringTableList1;
    tmStringTableList1 = tmStringTableList;
}

QVector < QVector < QVector < QVector< double > > > > vec4d_Max_Package;

void MainWindow::writeMaxArratTo3D()
{

    QVector < QVector < QVector < double > > > vecTemp3d;
    QVector < QVector< double > > vecTemp2d;

    //degree added
    vecTemp2d.push_back(FinalDegList_a0);
    vecTemp2d.push_back(FinalDegList_a1);
    vecTemp2d.push_back(FinalDegList_a2);
    vecTemp3d.push_back(vecTemp2d);
    vecTemp2d.clear();
    //RSSI_SUM Added
    vecTemp2d.push_back(RSSI_SUM_List_a0);
    vecTemp2d.push_back(RSSI_SUM_List_a1);
    vecTemp2d.push_back(RSSI_SUM_List_a2);
    vecTemp3d.push_back(vecTemp2d);
    vecTemp2d.clear();
    //dopp Added
    vecTemp2d.push_back(DopplerList_a2);
    vecTemp2d.push_back(DopplerList_a2);
    vecTemp2d.push_back(DopplerList_a2);
    vecTemp3d.push_back(vecTemp2d);
    vecTemp2d.clear();

    vec4d_Max_Package.push_back(vecTemp3d);
    vecTemp3d.clear();
}

int CntMaxFindGoBack = 0;
void MainWindow::on_btnAnalyze_clicked()
{
    uint dataLSize = ui->txtDataC_Size->text().toUInt();
    int packetNo = ((int)(RSSI_SUM_List.size()/dataLSize));
    vec4d_Max_Package.clear();
    for(int i = 0; i < packetNo; i++)
    {
        UpdateLists();



        double max_a = *std::max_element(RSSI_SUM_List_a2.begin(),RSSI_SUM_List_a2.end());

        /*find Peaks*/
        maxFinder_a[0] = maxFinder_a[1];
        maxFinder_a[1] = maxFinder_a[2];
        maxFinder_a[2] = max_a;
        if(maxFinder_a[1] >= maxFinder_a[0] && maxFinder_a[1] >= maxFinder_a[2])
        {
            maxRSSI_SUM_List_a.append(maxFinder_a[1]);
            int maxPos = RSSI_SUM_List_a1.indexOf(maxFinder_a[1]);
            DegDataMaxMap_a.insert(FinalDegList_a1.at(maxPos),maxFinder_a[1]);
            DegTimeMaxMap_a.insert(FinalDegList_a1.at(maxPos),tmStringTableList_a1.at(maxPos));
            DegDoppMaxMap_a.insert(FinalDegList_a1.at(maxPos),DopplerList_a1.at(maxPos));
            peaksCnt_a++;
            if(peaksCnt_a == 1)
            {
                peaksCnt_a = 0;
                qSort(maxRSSI_SUM_List_a.begin(), maxRSSI_SUM_List_a.end());
                for(int i = 0; i < std::min(maxRSSI_SUM_List_a.size(),6)  ;i++)
                {
                    double mxRSSI_SUM = maxRSSI_SUM_List_a.at(maxRSSI_SUM_List_a.size()-(i+1));
                    double _mxDeg = DegDataMaxMap_a.key(mxRSSI_SUM);
                    QString _mxStr = DegTimeMaxMap_a.value(_mxDeg);
                    double _mxDopp = DegDoppMaxMap_a.value(_mxDeg);

                    ui->tableWidget_a->setItem(i,0,new QTableWidgetItem(QString::number(_mxDeg)));
                    ui->tableWidget_a->setItem(i,1,new QTableWidgetItem(QString::number(mxRSSI_SUM)));
                    ui->tableWidget_a->setItem(i,2,new QTableWidgetItem(QString::number(_mxDopp)));
                    ui->tableWidget_a->setItem(i,3,new QTableWidgetItem(_mxStr));
                    ui->tableWidget_a->setItem(i,4,new QTableWidgetItem(QString("Snap On")));
                }
            }

            writeMaxArratTo3D();
        }
    }
    if(vec4d_Max_Package.size() > 0)
    {
        //ui->hlPlotPicks->setEnabled(true);
        ui->btnMaxPlotAnaGO->setEnabled(true);
        ui->pbPlotPicks->setEnabled(true);
        ui->pbPlotPicks->setMinimum(0);
        ui->pbPlotPicks->setMaximum(vec4d_Max_Package.size());
        ui->lblPicksSize->setText(QString::number(vec4d_Max_Package.size()));
    }
    else
    {
        ui->pbPlotPicks->setEnabled(false);
        //ui->hlPlotPicks->setEnabled(false);
    }
    CntMaxFindGoBack = 0;
    ui->btnMaxPlotAnaBack->setEnabled(false);
    maxRSSI_SUM_List_a.clear();
    /*find Peaks*/
}

int cntTest2 = 0;
void MainWindow::on_btn_test2_clicked()
{
    TimerTest2 = new QTimer(this);
    TimerTest2->setInterval(500);
    connect(TimerTest2,SIGNAL(timeout()),this,SLOT(TimerTest2Tick()));
    TimerTest2->start();
    cntTest2=0;

    /*plot with delay*/
}
void MainWindow::TimerTest2Tick()
{
    cntTest2++;
    uint dataLSize = ui->txtDataC_Size->text().toUInt();
    int packetNo = ((int)(RSSI_SUM_List.size()/dataLSize));

    if(cntTest2 < packetNo)
    {
        RSSI_SUM_List_a2 = RSSI_SUM_List.mid(cntTest2*dataLSize,dataLSize);
        FinalDegList_a2 = FinalDegList.mid(cntTest2*dataLSize,dataLSize);
        tmStringTableList_a2 = tmStringTableList.mid(cntTest2*dataLSize,dataLSize);
        DopplerList_a2 = DopplerList.mid(cntTest2*dataLSize,dataLSize);

        /*plot with delay*/
        //sleep(1);
        RSSI_SUM_List_Ploting   +=  (RSSI_SUM_List_a2);
        FinalDegList_Ploting    +=  (FinalDegList_a2);
        DopplerList_Ploting     +=  (DopplerList_a2);

        if(cntTest2>20)
        {
            RSSI_SUM_List_Ploting.remove(0,dataLSize);
            FinalDegList_Ploting.remove(0,dataLSize);
            DopplerList_Ploting.remove(0,dataLSize);
        }

        ui->plot_Analyzer_RSSI_SUM->graph(0)->clearData();
        ui->plot_Analyzer_RSSI_SUM->graph(0)->setData(FinalDegList_Ploting,RSSI_SUM_List_Ploting);
        ui->plot_Analyzer_RSSI_SUM->graph(0)->rescaleAxes(true);
        ui->plot_Analyzer_RSSI_SUM->replot();
        ui->plot_Analyzer_Dopp->graph(0)->clearData();
        ui->plot_Analyzer_Dopp->graph(0)->setData(FinalDegList_Ploting,DopplerList_Ploting);
        ui->plot_Analyzer_Dopp->graph(0)->rescaleAxes(true);
        ui->plot_Analyzer_Dopp->replot();
    }
}
//
// degree, RSSI_SUM, dopp
// pack 0 ,   1,   2
void MainWindow::on_btnMaxPlotAnaGO_clicked()
{
    ui->btnMaxPlotAnaBack->setEnabled(true);
    if(CntMaxFindGoBack == vec4d_Max_Package.size())
    {
        ui->btnMaxPlotAnaGO->setEnabled(false);
    }
    else
        CntMaxFindGoBack++;

    ui->lblCntMax->setText(QString::number(CntMaxFindGoBack));
    ui->pbPlotPicks->setValue(CntMaxFindGoBack);
    maxPlotGoBack(CntMaxFindGoBack - 1);

    ui->lblCntMax->setText(QString::number(CntMaxFindGoBack));
    ui->pbPlotPicks->setValue(CntMaxFindGoBack);
}

void MainWindow::on_btnMaxPlotAnaBack_clicked()
{

    ui->btnMaxPlotAnaGO->setEnabled(true);
    if(CntMaxFindGoBack == 1)
    {
        ui->pbPlotPicks->setValue(CntMaxFindGoBack);
        ui->btnMaxPlotAnaBack->setEnabled(false);
    }
    else
    {
        CntMaxFindGoBack--;
    }
    ui->lblCntMax->setText(QString::number(CntMaxFindGoBack));
    ui->pbPlotPicks->setValue(CntMaxFindGoBack);
    maxPlotGoBack(CntMaxFindGoBack - 1);
}

void MainWindow::maxPlotGoBack(int cnt)
{
    ui->plot_Analyzer_RSSI_SUM->graph(0)->clearData();
    ui->plot_Analyzer_Dopp->graph(0)->clearData();
    for(int i = 0; i < 3;i++)
    {
        QVector<double> degree = vec4d_Max_Package[cnt][0][i];
        QVector<double> RSSI_SUM_data = vec4d_Max_Package[cnt][1][i];
        QVector<double> dopp_data = vec4d_Max_Package[cnt][2][i];
        ui->plot_Analyzer_RSSI_SUM->graph(0)->addData(degree,RSSI_SUM_data);
        ui->plot_Analyzer_Dopp->graph(0)->addData(degree,dopp_data);
        ui->plot_Analyzer_RSSI_SUM->rescaleAxes(true);
        ui->plot_Analyzer_Dopp->rescaleAxes(true);
        ui->plot_Analyzer_RSSI_SUM->replot();
        ui->plot_Analyzer_Dopp->replot();
    }
}

void MainWindow::on_btnResetMaxTable_a_clicked()
{
    maxRSSI_SUM_List_a.clear();
    peaksCnt_a = 0;

    for(int i = 0; i < 6;i++)
    {
        ui->tableWidget_a->setItem(i,0,new QTableWidgetItem(QString("")));
        ui->tableWidget_a->setItem(i,1,new QTableWidgetItem(QString("")));
        ui->tableWidget_a->setItem(i,2,new QTableWidgetItem(QString("")));
        ui->tableWidget_a->setItem(i,3,new QTableWidgetItem(QString("")));
        ui->tableWidget_a->setItem(i,4,new QTableWidgetItem(QString("")));
    }
}

QVector<double> DegAnalyzerPlot;
void MainWindow::on_btnSimplePLot_clicked()
{
    for(int i = 0; i < FinalDegList.size();i++)
    {
        DegAnalyzerPlot.append(FinalDegList.at(i)*(FinalRevList.at(i)-FinalRevList.at(0)+1)*365);
    }
    ui->plot_Analyzer_RSSI_SUM->graph(0)->setData(DegAnalyzerPlot,RSSI_SUM_List);
    ui->plot_Analyzer_Dopp->graph(0)->setData(DegAnalyzerPlot,DopplerList);
    ui->plot_Analyzer_RSSI_SUM->graph(0)->rescaleAxes(true);
    ui->plot_Analyzer_Dopp->graph(0)->rescaleAxes(true);
    ui->plot_Analyzer_RSSI_SUM->replot();
}

void MainWindow::on_rb_adc_EncoderPlot_toggled(bool checked)
{
    ResetAllPlots();

    if(checked)
    {
        ui->rb_PolarPlot->setEnabled(true);
    }
    else
    {
        ui->rb_PolarPlot->setEnabled(false);
        ui->rb_LinearPlot->setChecked(Qt::Checked);
    }
}

void MainWindow::on_rb_LinearPlot_toggled(bool checked)
{
    ResetAllPlots();
}

void MainWindow::ResetAllPlots()
{

    if(ui->chkAuto->isChecked())
    {
        ui->plot_Dopp->xAxis->setRange(minOfMoveDeg, maxOfMoveDeg);
        ui->plot_Dopp->yAxis->setRange(0, 1);
        ui->plot_RSSI_Delta->xAxis->setRange(minOfMoveDeg, maxOfMoveDeg);
        ui->plot_RSSI_Delta->yAxis->setRange(0, 1);
        ui->plot_RSSI_SUM_Delta->xAxis->setRange(minOfMoveDeg, maxOfMoveDeg);
        ui->plot_RSSI_SUM_Delta->yAxis->setRange(0, 1);
    }
    else{
        ui->plot_Dopp->xAxis->setRange(0, 1);
        ui->plot_Dopp->yAxis->setRange(0, 1);
        ui->plot_RSSI_Delta->xAxis->setRange(0, 1);
        ui->plot_RSSI_Delta->yAxis->setRange(0, 1);
        ui->plot_RSSI_SUM_Delta->xAxis->setRange(0, 1);
        ui->plot_RSSI_SUM_Delta->yAxis->setRange(0, 1);
}


    packageCnt = 0;
    RSSI_SUM_List_Ploting.clear();
    RSSI_Delta_List_Ploting.clear();
    RSSI_SUM_Analyzer_List_Ploting.clear();
    RSSI_Delta_Analyzer_List_Ploting.clear();
    FinalDegList_Ploting.clear();
    DopplerList_Ploting.clear();

    for(int i = 0;i<4096;i++)
    {
        validDataList_Sanp[i] = false;
    }

    RSSI_SUM_List_SanpPlot.clear();
    RSSI_Delta_List_SanpPlot.clear();
    DopplerList_SanpPlot.clear();
    FinalDegList_SanpPlot.clear();
    timeList_SnapPlot.clear();

    RSSI_SUM_List_SnapPloting_Polar_X.clear();
    RSSI_SUM_List_SnapPloting_Polar_Y.clear();
    Doppler_List_SnapPloting_Polar_X.clear();
    Doppler_List_SnapPloting_Polar_Y.clear();
    RSSI_Delta_List_SnapPloting_Polar_X.clear();
    RSSI_Delta_List_SnapPloting_Polar_Y.clear();

    ui->plot_Dopp->graph(0)->clearData();
    ui->plot_RSSI_Delta->graph(0)->clearData();
    ui->plot_RSSI_SUM_Delta->graph(0)->clearData();
    ui->plot_RSSI_SUM_Delta->graph(1)->clearData();
    ui->plot_RSSI_SUM_Delta->graph(2)->clearData();
    ui->plot_RSSI_SUM_Delta->graph(3)->clearData();

    ui->plot_Dopp->replot();
    ui->plot_RSSI_Delta->replot();
    ui->plot_RSSI_SUM_Delta->replot();
    ui->plot_RSSI_SUM_Delta->replot();
}
double CoefAnlyzorSum = 1;
double OffsetAnalyzerSum = 0;
double CoefAnlyzorDelta = 1;
double OffsetAnalyzerDelta = 0;

typedef enum
{
    plot_RSSI_SUM = 0,
    plot_RSSI_DeltaSLC,
    plot_RSSI_SUM_Anlz,
    plot_RSSI_DeltaSLC_Anlz
} plotGraph_t;
 plotGraph_t plotGraph;

void MainWindow::parseMessage(QByteArray msg, QDateTime dt)
{
    fixedMCU_Alive = true;
    memcpy(MCU_Data_u.MCU_Data_Array,msg,msg.size());

    if(MCU_Data_u.MCU_Data_S.Interrupt_Bits == 0xF8)
    {
        ui->ledRotaryMCU_State->setColor(Qt::red);
    }
    else
        ui->ledRotaryMCU_State->setColor(Qt::green);

    if(MCU_Data_u.MCU_Data_S.Interrupt_Bits == 1)
    {
        ui->ledDetect1->setColor(Qt::red);
        ui->plot_Dopp->graph(0)->setPen(QPen(QColor(Qt::red)));
        ui->plot_RSSI_Delta->graph(0)->setPen(QPen(QColor(Qt::red)));
    }
    else
    {
        ui->ledDetect1->setColor(Qt::blue);
        ui->plot_Dopp->graph(0)->setPen(QPen(QColor(Qt::blue)));
        ui->plot_RSSI_Delta->graph(0)->setPen(QPen(QColor(Qt::blue)));
    }

    if(true) // LED Checks for all Events
    {
        if(getMask(MCU_Data_u.MCU_Data_S.bitWatch,we_Rot_COM_SUM))
            ui->ledRcvDataSum->setColor(Qt::red);
        else
            ui->ledRcvDataSum->setColor(Qt::green);

        if(getMask(MCU_Data_u.MCU_Data_S.bitWatch,we_Rot_COM_Delta))
            ui->ledRcvDataDelta->setColor(Qt::red);
        else
            ui->ledRcvDataDelta->setColor(Qt::green);

        if(getMask(MCU_Data_u.MCU_Data_S.bitWatch,w_Rot_SUM_Serial_Pin))
            ui->ledSUM_SerialPin->setColor(Qt::green);
        else
            ui->ledSUM_SerialPin->setColor(Qt::black);

        if(getMask(MCU_Data_u.MCU_Data_S.bitWatch,w_Rot_DeltaSLC_Serial_Pin))
            ui->ledDeltaSLC_SerialPin->setColor(Qt::green);
        else
            ui->ledDeltaSLC_SerialPin->setColor(Qt::black);

        if(getMask(MCU_Data_u.MCU_Data_S.bitWatch,w_Rot_SelectDeltaSLC))
        {
            ui->ledSelectDeltafb->setColor(Qt::green);
            ui->ledSelectSLCfb->setColor(Qt::black);
        }
        else
        {
            ui->ledSelectSLCfb->setColor(Qt::green);
            ui->ledSelectDeltafb->setColor(Qt::black);
        }

    }

    uint _RSSI_SUM_Data        = MCU_Data_u.MCU_Data_S.RSSI_SUM_UARTs_Data[0] + MCU_Data_u.MCU_Data_S.RSSI_SUM_UARTs_Data[1]*256 + MCU_Data_u.MCU_Data_S.RSSI_SUM_UARTs_Data[2]*65536;
    uint8_t _Dopp         = MCU_Data_u.MCU_Data_S.Dopp_UARTs_data;
    uint _RSSI_Delta_Data = MCU_Data_u.MCU_Data_S.RSSI_Delta_UARTs_Data[0] + MCU_Data_u.MCU_Data_S.RSSI_Delta_UARTs_Data[1]*256 + MCU_Data_u.MCU_Data_S.RSSI_Delta_UARTs_Data[2]*65536;

    //_RSSI_SUM_Data *= 1.5;

    double Enc_Deg_ = MCU_Data_u.MCU_Data_S.Encoder_AC_Motor[0] + 256 * MCU_Data_u.MCU_Data_S.Encoder_AC_Motor[1];

    buffDegreeTest[0] = buffDegreeTest[1];
    buffDegreeTest[1] = Enc_Deg_;
    int ab = (buffDegreeTest[1] - buffDegreeTest[0]);
    if((abs(ab) > 5))
    {
        //qDebug()<<"bufdeg 0 : "<< buffDegreeTest[0] << "bufdeg 1: " << buffDegreeTest[1];
        qDebug()<< ab;
    }

    double Enc_Deg = 360 - Enc_Deg_*360/4096.0;

    uint16_t Enc_Rev_ = MCU_Data_u.MCU_Data_S.Encoder_AC_Motor[2] + 256 * MCU_Data_u.MCU_Data_S.Encoder_AC_Motor[3];
    uint16_t Enc_Rev = 65535 - Enc_Rev_;

    double Enc_Ref_Deg_ = MCU_Data_u.MCU_Data_S.Encoder_Ref_AC_Motor[0] + 256 * MCU_Data_u.MCU_Data_S.Encoder_Ref_AC_Motor[1];
    double Enc_Ref_Deg = 360 - Enc_Ref_Deg_*360/4096.0;

    uint16_t Enc_Ref_Rev_ = MCU_Data_u.MCU_Data_S.Encoder_Ref_AC_Motor[2] + 256 * MCU_Data_u.MCU_Data_S.Encoder_Ref_AC_Motor[3];
    uint16_t Enc_Ref_Rev = 65535 - Enc_Ref_Rev_;

    float degOffset =  21; //ui->txtOffset->toPlainText().toFloat();

    float finalDeg = Enc_Deg - Enc_Ref_Deg;

    int finalRev = Enc_Rev - Enc_Ref_Rev;
    ((Enc_Deg - Enc_Ref_Deg) >= 0) ? finalDeg = finalDeg : finalDeg += 360;
    ((Enc_Rev - Enc_Ref_Rev) >= 0) ? finalRev = finalRev : finalRev += 65535;

    if(((abs(finalDeg - degOffset)) < 2) & OnlyOneIf)
    {
        OnlyOneIf = false;
        if(toggleOddEvenRotation)
            toggleOddEvenRotation = false;
        else
            toggleOddEvenRotation = true;
    }
    if((((abs(finalDeg - degOffset)) > 2)))
    {
        OnlyOneIf = true;
    }

    movingEncoderData[1] = movingEncoderData[0];
    CntForCheckMovingMotor++;
    if(CntForCheckMovingMotor > 100)
    {
        CntForCheckMovingMotor = 0;
        float deltaDegree = finalDeg - movingEncoderData[0];
        if(deltaDegree > 3)
        {
           MotorDirection = 1;
           forwardStyle();
        }
        else if(deltaDegree < -3)
        {
            MotorDirection = -1;
            reverseStyle();
        }
        else if(abs(deltaDegree) <= 3)
        {
            MotorDirection = 0;
            stopStyle();
        }

        ui->lbl_MovingFlage->setText(QString::number(MotorDirection));

        if(abs(finalDeg - movingEncoderData[0]) > 1)
            movingMotor = true;
        else
            movingMotor = false;

        movingEncoderData[0] = finalDeg;
    }

    finalDeg -= degOffset;
    if(finalDeg < 0)
       finalDeg += 360;
    if(finalDeg > 360)
       finalDeg -= 360;

    int diff__ = ((int)(finalDeg - ui->txtCenterOfSpan->text().toFloat()))%360;
    if(checkAutoEnable && (diff__ < 20))
    {
        checkAutoEnable = false;
        ui->chkAuto->setChecked(Qt::Checked);
    }
    if(ui->chkAuto->isChecked())
    {


        minOfMoveDeg = CenterofSpan - Span/2.0;
        maxOfMoveDeg = CenterofSpan + Span/2.0;

        minOfMoveDeg  = (minOfMoveDeg + 360)%360;
        maxOfMoveDeg %= 360;

        float x = finalDeg;

        int s1 = 0;
        if(minOfMoveDeg > maxOfMoveDeg)
        {
            float minOfMoveDeg_wrap =  minOfMoveDeg;
            float maxOfMoveDeg_wrap = maxOfMoveDeg + 360;
            float x_wrap = x;
            if(x < (maxOfMoveDeg+minOfMoveDeg_wrap)/2)
            {
                x_wrap = x + 360;
            }
            s1 = ((x_wrap > maxOfMoveDeg_wrap) && MotorDirection == 1) * 1 +
               ((x_wrap < minOfMoveDeg_wrap ) && MotorDirection == -1) * 2;
        }
        else
            {
             s1 = ((x > maxOfMoveDeg) && MotorDirection == 1) * 1 +
                ((x < minOfMoveDeg ) && MotorDirection == -1) * 2;
            }
        switch (s1)
        {
            case 1:
                {
                    if(S_1)
                    {
                        S_1 = false;
                        S_2 = true;
                        on_btnReverseM_clicked();
                        atMMCT = 0;
                        autoMoveManyCommandTimer->start();
                    }
                }
                break;

            case 2:
                {
                    if(S_2)
                    {
                        S_1 = true;
                        S_2 = false;
                        on_btnForwardM_clicked();
                        atMMCT = 10;
                        autoMoveManyCommandTimer->start();
                    }
                }
                break;
            default:
                //qDebug() << s1;
                break;
        }
    }

    float finalDeg_forPlot = finalDeg;

    if(((finalDeg < 85 & finalDeg > 84)) & ParkAntena_b)
    {
        on_btnStopMotor_clicked();
        MotorParked = true;
        ParkAntena_b = false;
    }

    ui->lbl_finalDegreefinal->setText(QString::number(finalDeg,'f',1));
    ui->lblfinalDegree->setText(QString::number(finalDeg,'f',1));
    if(_Dopp <= 127)
        Doppler = ((int)(_Dopp*765.625));
    else
        Doppler =((int)(( 127.0 - _Dopp)*765.625)); // 765.625 ~ 766Hz-FFT resolution

    //QDateTime dt = myDate->currentDateTime();
    double timeSec = (dt.time().second())%30 + dt.time().msec()/1000.0;

    tmDoubleList.append(dt.time().second() + dt.time().msec()/1000.0);
    InterruptList.append(MCU_Data_u.MCU_Data_S.Interrupt_Bits);

    _RSSI_SUM_Data &= 0x00FFFFFF;
    _RSSI_Delta_Data &= 0xFFFFFF;
    RSSI_SUM_List.append(_RSSI_SUM_Data);
    RSSI_Delta_List.append(_RSSI_Delta_Data);

    double deltasumMeanDiff = 0;
    if(true)   // Analyzor
    {
//        RSSI_SUM_Analyzor_List.append(_RSSI_SUM_Data);
//        RSSI_Delta_Analyzor_List.append(_RSSI_Delta_Data);
//        if(RSSI_SUM_Analyzor_List.size() > 50)
//        {
//            RSSI_SUM_Analyzor_List.remove(0);
//            RSSI_Delta_Analyzor_List.remove(0);
//        }

//        double SUM_Analyzor_Mean = std::accumulate(RSSI_SUM_Analyzor_List.begin(),RSSI_SUM_Analyzor_List.end(),.0)/RSSI_SUM_Analyzor_List.size();
//        double Delta_Analyzor_Mean =  std::accumulate(RSSI_Delta_Analyzor_List.begin(),RSSI_Delta_Analyzor_List.end(),.0)/RSSI_Delta_Analyzor_List.size();
//        SUM_Analyzor_Mean = SUM_Analyzor_Mean*CoefAnlyzorSum + OffsetAnalyzerSum;
//        Delta_Analyzor_Mean = Delta_Analyzor_Mean*CoefAnlyzorDelta + OffsetAnalyzerDelta;
        double SUM_Analyzor_Mean = RSSI_SUM_Analyzor(_RSSI_SUM_Data);
        double Delta_Analyzor_Mean = RSSI_Delta_Analyzor(_RSSI_Delta_Data);
        RSSI_SUM_Analyzor_Mean_List.append(SUM_Analyzor_Mean);
        RSSI_Delta_Analyzor_Mean_List.append(Delta_Analyzor_Mean);
        deltasumMeanDiff = SUM_Analyzor_Mean - Delta_Analyzor_Mean;

        if(RSSI_SUM_Analyzor_Mean_List.size() > packetSize)
        {
            RSSI_SUM_Analyzor_Mean_List.remove(0);
            RSSI_Delta_Analyzor_Mean_List.remove(0);
        }
    }
    timeList.append(timeSec);
    DopplerList.append(Doppler);
    //DopplerList.append(deltasumMeanDiff);
    FinalDegList.append(finalDeg);
    finalDegPlotList.append(finalDeg_forPlot);
    FinalRevList.append(finalRev);
    EncDegList.append(Enc_Deg);
    EncRevList.append(Enc_Rev);
    RefRevList.append(Enc_Ref_Rev);
    RefDegList.append(Enc_Ref_Deg);
    tmStringList.append(dt.toString("dd-MM-yy hh:mm:ss.zzz"));
    tmStringTableList.append(dt.toString("hh:mm:ss.z"));

    if(ui->chkAuto->isChecked())
    {
        int finalDeg_int = (int)(finalDeg*4096.0/360.0);

        validDataList_Sanp[finalDeg_int] = true;
        RSSI_SUM_List_Sanp[finalDeg_int] = _RSSI_SUM_Data;
        RSSI_Delta_List_Sanp[finalDeg_int] = _RSSI_Delta_Data;
        DopplerList_Sanp[finalDeg_int] = Doppler;
        FinalDegList_Sanp[finalDeg_int] = finalDeg;
        timeList_Sanp[finalDeg_int] = timeSec;

        RSSI_SUM_List_Snap_Polar_X[finalDeg_int] = (_RSSI_SUM_Data*cos((finalDeg*3.1415/180)));
        RSSI_SUM_List_Snap_Polar_Y[finalDeg_int] = (_RSSI_SUM_Data*sin((finalDeg*3.1415/180)));
        Doppler_List_Snap_Polar_X[finalDeg_int] = (Doppler*cos((finalDeg*3.1415/180)));
        Doppler_List_Snap_Polar_Y[finalDeg_int] = (Doppler*sin((finalDeg*3.1415/180)));
        RSSI_Delta_List_Snap_Polar_X[finalDeg_int] = (_RSSI_Delta_Data*cos((finalDeg*3.1415/180)));
        RSSI_Delta_List_Snap_Polar_Y[finalDeg_int] = (_RSSI_Delta_Data*sin((finalDeg*3.1415/180)));
    }
    else // Because it is not need for the Snapping
    {
        RSSI_SUM_List_Polar_X.append(_RSSI_SUM_Data*cos((finalDeg*3.1415/180)));
        RSSI_SUM_List_Polar_Y.append(_RSSI_SUM_Data*sin((finalDeg*3.1415/180)));
        Doppler_List_Polar_X.append(Doppler*cos((finalDeg*3.1415/180)));
        Doppler_List_Polar_Y.append(Doppler*sin((finalDeg*3.1415/180)));
        RSSI_Delta_List_Polar_X.append(_RSSI_Delta_Data*cos((finalDeg*3.1415/180)));
        RSSI_Delta_List_Polar_Y.append(_RSSI_Delta_Data*sin((finalDeg*3.1415/180)));
    }

    /*********************PLOTING_Saving_maxFinding*******************/
    dataCnt++;
    if(dataCnt == packetSize)
    {
        packageCnt++;

        /**************Saving***************/
        if(true)
        {
            worker->tmStringList = tmStringList;
            worker->tmDoubleList = tmDoubleList;
            worker->FinalDegList = FinalDegList;
            worker->FinalRevList = FinalRevList;
            worker->RefDegList = RefDegList;
            worker->RefRevList = RefRevList;
            worker->EncDegList = EncDegList;
            worker->EncRevList = EncRevList;
            worker->DopplerList = DopplerList;
            worker->InterruptList = InterruptList;
            worker->RSSI_SUM_List = RSSI_SUM_List;
            worker->RSSI_Delta_List = RSSI_Delta_List;
            //worker->moveToThread(thread);
            worker->process();
        }
        /**************Saving***************/
        /**************Ploting***************/
        if(true)
        {
            //ui->plot_Analyzer_Dopp->moveToThread(thread);
            ui->plot_Dopp->graph(0)->clearData();
            ui->plot_RSSI_Delta->graph(0)->clearData();
            ui->plot_RSSI_SUM_Delta->graph(0)->clearData();
            ui->plot_RSSI_SUM_Delta->graph(1)->clearData();
            ui->plot_RSSI_SUM_Delta->graph(2)->clearData();
            ui->plot_RSSI_SUM_Delta->graph(3)->clearData();

            int plotState = (ui->rb_LinearPlot->isChecked() && ui->rb_adc_EncoderPlot->isChecked())*1 + // plotting based Degree in linear
                       (ui->rb_LinearPlot->isChecked() && ui->rb_RealTime->isChecked())*3 + // plotting besed time in linear
                       (ui->rb_PolarPlot->isChecked() && ui->rb_adc_EncoderPlot->isChecked())*7; // plotting based encoder in Polar
            plotState*=((int)(ui->chkAuto->isChecked())+1); // Change the plot for Snap
            switch(plotState)
            {
            case 1:
            {
                ui->plot_Dopp->xAxis->setLabel("Azimuth (Deg.)");
                ui->plot_RSSI_Delta->xAxis->setLabel("Azimuth (Deg.)");
                ui->plot_RSSI_SUM_Delta->xAxis->setLabel("Azimuth (Deg.)");

                RSSI_SUM_List_Ploting   +=  RSSI_SUM_List;
                RSSI_Delta_List_Ploting +=  RSSI_Delta_List;
                DopplerList_Ploting     +=  DopplerList;
                FinalDegList_Ploting    +=  FinalDegList;

                if(packageCnt > packageNO)
                {
                    RSSI_SUM_List_Ploting.remove(0,packetSize);
                    RSSI_Delta_List_Ploting.remove(0,packetSize);
                    FinalDegList_Ploting.remove(0,packetSize);
                    DopplerList_Ploting.remove(0,packetSize);
                }

                ui->plot_Dopp->graph(0)->setData(FinalDegList_Ploting,DopplerList_Ploting);
                ui->plot_RSSI_SUM_Delta->graph(0)->setData(FinalDegList_Ploting,RSSI_SUM_List_Ploting);
                ui->plot_RSSI_SUM_Delta->graph(1)->setData(FinalDegList_Ploting,RSSI_Delta_List_Ploting);
            }
            break;
            case 3:
            {
                ui->plot_Dopp->xAxis->setLabel("Time (sec.)");
                ui->plot_RSSI_Delta->xAxis->setLabel("Time (sec.)");
                ui->plot_RSSI_SUM_Delta->xAxis->setLabel("Time (sec.)");

                RSSI_SUM_List_Ploting   +=  RSSI_SUM_List;
                RSSI_Delta_List_Ploting +=  RSSI_Delta_List;
                DopplerList_Ploting     +=  DopplerList;
                timeList_Ploting        +=  timeList;
                RSSI_SUM_Analyzer_List_Ploting += RSSI_SUM_Analyzor_Mean_List ;
                RSSI_Delta_Analyzer_List_Ploting += RSSI_Delta_Analyzor_Mean_List;

                if(packageCnt>packageNO)
                {
                    RSSI_SUM_List_Ploting.remove(0,packetSize);
                    RSSI_Delta_List_Ploting.remove(0,packetSize);
                    DopplerList_Ploting.remove(0,packetSize);
                    timeList_Ploting.remove(0,packetSize);
                    RSSI_SUM_Analyzer_List_Ploting.remove(0,packetSize);
                    RSSI_Delta_Analyzer_List_Ploting.remove(0,packetSize);
                }

                ui->plot_Dopp->graph(0)->setData(timeList_Ploting,DopplerList_Ploting);
                ui->plot_RSSI_Delta->graph(0)->setData(timeList_Ploting,RSSI_Delta_List_Ploting);
//                ui->plot_RSSI_SUM_Delta->graph(0)->setData(timeList_Ploting,RSSI_SUM_List_Ploting);
//                ui->plot_RSSI_SUM_Delta->graph(1)->setData(timeList_Ploting,RSSI_Delta_List_Ploting);
//                ui->plot_RSSI_SUM_Delta->graph(2)->setData(timeList_Ploting,RSSI_SUM_Analyzer_List_Ploting);
//                ui->plot_RSSI_SUM_Delta->graph(3)->setData(timeList_Ploting,RSSI_Delta_Analyzer_List_Ploting);


                setMainGraphData(0,timeList_Ploting,RSSI_SUM_List_Ploting);
                setMainGraphData(1,timeList_Ploting,RSSI_Delta_List_Ploting);
                setMainGraphData(2,timeList_Ploting,RSSI_SUM_Analyzer_List_Ploting);
                setMainGraphData(3,timeList_Ploting,RSSI_Delta_Analyzer_List_Ploting);

            }
            break;
            case 7:
            {
                ui->plot_Dopp->xAxis->setLabel("Polar Plot (Deg.)");
                ui->plot_RSSI_Delta->xAxis->setLabel("Polar Plot (Deg.)");
                ui->plot_RSSI_SUM_Delta->xAxis->setLabel("Polar Plot (Deg.)");

                RSSI_SUM_List_Ploting_Polar_X += RSSI_SUM_List_Polar_X;
                RSSI_SUM_List_Ploting_Polar_Y += RSSI_SUM_List_Polar_Y;
                Doppler_List_Ploting_Polar_X += Doppler_List_Polar_X;
                Doppler_List_Ploting_Polar_Y += Doppler_List_Polar_Y;
                RSSI_Delta_List_Ploting_Polar_X += RSSI_Delta_List_Polar_X;
                RSSI_Delta_List_Ploting_Polar_Y += RSSI_Delta_List_Polar_Y;

                if(packageCnt>packageNO)
                {
                    RSSI_SUM_List_Ploting_Polar_X.remove(0,packetSize);
                    RSSI_SUM_List_Ploting_Polar_Y.remove(0,packetSize);
                    Doppler_List_Ploting_Polar_X.remove(0,packetSize);
                    Doppler_List_Ploting_Polar_Y.remove(0,packetSize);
                    RSSI_Delta_List_Ploting_Polar_X.remove(0,packetSize);
                    RSSI_Delta_List_Ploting_Polar_Y.remove(0,packetSize);
                }

                ui->plot_Dopp->graph(0)->setData        (Doppler_List_Ploting_Polar_X,      Doppler_List_Ploting_Polar_Y);
                ui->plot_RSSI_Delta->graph(0)->setData  (RSSI_Delta_List_Ploting_Polar_X,   RSSI_Delta_List_Ploting_Polar_Y);
                ui->plot_RSSI_SUM_Delta->graph(0)->setData(RSSI_SUM_List_Ploting_Polar_X,RSSI_SUM_List_Ploting_Polar_Y);
                ui->plot_RSSI_SUM_Delta->graph(1)->setData(RSSI_Delta_List_Ploting_Polar_X,RSSI_Delta_List_Ploting_Polar_Y);
            }
            break;
            }

            switch(plotState)
            {
            case 2:
            {
                ui->plot_Dopp->xAxis->setLabel("Azimuth (Deg.) [Snapping]");
                ui->plot_RSSI_Delta->xAxis->setLabel("Azimuth (Deg.) [Snapping]");
                ui->plot_RSSI_SUM_Delta->xAxis->setLabel("Azimuth (Deg.) [Snapping]");

                for(int i =0; i < 4096;i++)
                {
                    if(validDataList_Sanp[i])
                    {
                        RSSI_SUM_List_SanpPlot.append(RSSI_SUM_List_Sanp[i]);
                        RSSI_Delta_List_SanpPlot.append(RSSI_Delta_List_Sanp[i]);
                        DopplerList_SanpPlot.append(DopplerList_Sanp[i]);
                        FinalDegList_SanpPlot.append(FinalDegList_Sanp[i]);
                    }
                }
                ui->plot_Dopp->graph(0)->setData(FinalDegList_SanpPlot,DopplerList_SanpPlot);
                ui->plot_RSSI_Delta->graph(0)->setData(FinalDegList_SanpPlot,RSSI_Delta_List_SanpPlot);
                ui->plot_RSSI_SUM_Delta->graph(0)->setData(FinalDegList_SanpPlot,RSSI_SUM_List_SanpPlot);
                ui->plot_RSSI_SUM_Delta->graph(1)->setData(FinalDegList_SanpPlot,RSSI_Delta_List_SanpPlot);
            }
            break;
            case 6:
            {
                ui->plot_Dopp->xAxis->setLabel("Time (sec.) [Snapping]");
                ui->plot_RSSI_Delta->xAxis->setLabel("Time (sec.) [Snapping]");
                ui->plot_RSSI_SUM_Delta->xAxis->setLabel("Time (sec.) [Snapping]");

                for(int i =0; i < 4096;i++)
                {
                    if(validDataList_Sanp[i])
                    {
                        RSSI_SUM_List_SanpPlot.append(RSSI_SUM_List_Sanp[i]);
                        RSSI_Delta_List_SanpPlot.append(RSSI_Delta_List_Sanp[i]);
                        DopplerList_SanpPlot.append(DopplerList_Sanp[i]);
                        timeList_SnapPlot.append(timeList_Sanp[i]);
                    }
                }
                ui->plot_Dopp->graph(0)->setData(timeList_SnapPlot,DopplerList_SanpPlot);
                ui->plot_RSSI_Delta->graph(0)->setData(timeList_SnapPlot,RSSI_Delta_List_SanpPlot);
                ui->plot_RSSI_SUM_Delta->graph(0)->setData(timeList_SnapPlot,RSSI_SUM_List_SanpPlot);
                ui->plot_RSSI_SUM_Delta->graph(1)->setData(timeList_SnapPlot,RSSI_Delta_List_SanpPlot);
            }
            break;
            case 14:
            {
                ui->plot_Dopp->xAxis->setLabel("Polar Plot (Deg.) [Snapping]");
                ui->plot_RSSI_Delta->xAxis->setLabel("Polar Plot (Deg.) [Snapping]");
                ui->plot_RSSI_SUM_Delta->xAxis->setLabel("Polar Plot (Deg.) [Snapping]");

                for(int i =0; i < 4096;i++)
                {
                    if(validDataList_Sanp[i])
                    {
                        RSSI_SUM_List_SnapPloting_Polar_X.append(RSSI_SUM_List_Snap_Polar_X[i]);
                        RSSI_SUM_List_SnapPloting_Polar_Y.append(RSSI_SUM_List_Snap_Polar_Y[i]);
                        Doppler_List_SnapPloting_Polar_X.append(Doppler_List_Snap_Polar_X[i]);
                        Doppler_List_SnapPloting_Polar_Y.append(Doppler_List_Snap_Polar_Y[i]);
                        RSSI_Delta_List_SnapPloting_Polar_X.append(RSSI_Delta_List_Snap_Polar_X[i]);
                        RSSI_Delta_List_SnapPloting_Polar_Y.append(RSSI_Delta_List_Snap_Polar_Y[i]);
                    }
                }
                ui->plot_Dopp->graph(0)->setData(Doppler_List_SnapPloting_Polar_X,Doppler_List_SnapPloting_Polar_Y);
                ui->plot_RSSI_Delta->graph(0)->setData(RSSI_Delta_List_SnapPloting_Polar_X,RSSI_Delta_List_SnapPloting_Polar_Y);
                ui->plot_RSSI_SUM_Delta->graph(0)->setData(RSSI_SUM_List_SnapPloting_Polar_X,RSSI_SUM_List_SnapPloting_Polar_Y);
                ui->plot_RSSI_SUM_Delta->graph(1)->setData(RSSI_Delta_List_SnapPloting_Polar_X,RSSI_Delta_List_SnapPloting_Polar_Y);
            }
            break;
            }
            ui->plot_Dopp->graph(0)->rescaleAxes(true);
            ui->plot_RSSI_Delta->graph(0)->rescaleAxes(true);
            ui->plot_RSSI_SUM_Delta->graph(0)->rescaleAxes(true);
            ui->plot_RSSI_SUM_Delta->graph(1)->rescaleAxes(true);
            ui->plot_RSSI_SUM_Delta->graph(2)->rescaleAxes(true);
            ui->plot_RSSI_SUM_Delta->graph(3)->rescaleAxes(true);
            // Note: we could have also just called customPlot->rescaleAxes(); instead
            // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
            ui->plot_Dopp->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
            ui->plot_RSSI_Delta->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
            ui->plot_RSSI_SUM_Delta->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

            ui->plot_Dopp->replot();
            //ui->plot_RSSI_Delta->replot();
            //ui->plot_RSSI_SUM_Delta->replot();
        }
        /**************Ploting***************/
        /**************maxFinding***************/
        if(true){
        /*find Peaks*/
        double max = *std::max_element(RSSI_SUM_List.begin(),RSSI_SUM_List.end());
        maxFinder[0] = maxFinder[1];
        maxFinder[1] = maxFinder[2];
        maxFinder[2] = max;
        if(maxFinder[1] > maxFinder[0] && maxFinder[1] > maxFinder[2])
        {
            maxRSSI_SUM_List.append(maxFinder[1]);
            int maxPos = RSSI_SUM_List1.indexOf(maxFinder[1]);
            DegDataMaxMap.insert(FinalDegList1.at(maxPos),RSSI_SUM_List1.at(maxPos));
            DegTimeMaxMap.insert(FinalDegList1.at(maxPos),tmStringTableList1.at(maxPos));
            DegDoppMaxMap.insert(FinalDegList1.at(maxPos),DopplerList1.at(maxPos));
            peaksCnt++;

            if(peaksCnt == 1)
            {
                peaksCnt = 0;
                qSort(maxRSSI_SUM_List.begin(), maxRSSI_SUM_List.end());

                for(int i = 0; i < std::min(maxRSSI_SUM_List.size(),6)  ;i++)
                {
                    double mxRSSI_SUM   = maxRSSI_SUM_List.at(maxRSSI_SUM_List.size()-(i+1));
                    double _mxDeg       = DegDataMaxMap.key(mxRSSI_SUM);
                    QString _mxStr      = DegTimeMaxMap.value(_mxDeg);
                    double _mxDopp      = DegDoppMaxMap.value(_mxDeg);

                    ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(_mxDeg,'f',1)));
                    ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(mxRSSI_SUM)));
                    ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(_mxDopp)));
                    ui->tableWidget->setItem(i,3,new QTableWidgetItem(_mxStr));
                    ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString("Snap On")));
                }
            }
        }
        mainUpdateLists();
        /*find Peaks*/
        RSSI_SUM_List.clear();
        RSSI_Delta_List.clear();
        timeList.clear();
        DopplerList.clear();
        FinalDegList.clear();
        FinalRevList.clear();
        finalDegPlotList.clear();
        RefDegList.clear();
        RefRevList.clear();
        EncDegList.clear();
        EncRevList.clear();
        InterruptList.clear();
        tmStringList.clear();
        tmStringTableList.clear();
        tmDoubleList.clear();

        RSSI_SUM_List_Polar_X.clear();
        RSSI_SUM_List_Polar_Y.clear();
        Doppler_List_Polar_X.clear();
        Doppler_List_Polar_Y.clear();
        RSSI_Delta_List_Polar_X.clear();
        RSSI_Delta_List_Polar_Y.clear();
        /***************clear snap lists***************/
        if(true)
        {
            RSSI_SUM_List_SanpPlot.clear();
            RSSI_Delta_List_SanpPlot.clear();
            DopplerList_SanpPlot.clear();
            FinalDegList_SanpPlot.clear();
            timeList_SnapPlot.clear();

            RSSI_SUM_List_SnapPloting_Polar_X.clear();
            RSSI_SUM_List_SnapPloting_Polar_Y.clear();
            Doppler_List_SnapPloting_Polar_X.clear();
            Doppler_List_SnapPloting_Polar_Y.clear();
            RSSI_Delta_List_SnapPloting_Polar_X.clear();
            RSSI_Delta_List_SnapPloting_Polar_Y.clear();
        }
            /***************clear snap lists***************/
        }
        /**************maxFinding***************/
        dataCnt = 0;
    }
    /*********************PLOTING_Saving_maxFinding*******************/

}

void MainWindow::setMainGraphData(int _grph, QVector<double> X,QVector<double> Y)
{
    if(ui->chkPlotSUM->isChecked() & _grph == plot_RSSI_SUM)
    {
        ui->plot_RSSI_SUM_Delta->graph(plot_RSSI_SUM)->setData(X,Y);
    }
    if(ui->chkPlotDelta->isChecked() & _grph == plot_RSSI_DeltaSLC)
    {
        ui->plot_RSSI_SUM_Delta->graph(plot_RSSI_DeltaSLC)->setData(X,Y);
    }
    if(ui->chkPlotSUM_Anlz->isChecked()  & _grph == plot_RSSI_SUM_Anlz)
    {
        ui->plot_RSSI_SUM_Delta->graph(plot_RSSI_SUM_Anlz)->setData(X,Y);
    }
    if(ui->chkPlotDeltaSLC_Anlz->isChecked()  & _grph == plot_RSSI_DeltaSLC_Anlz)
    {
        ui->plot_RSSI_SUM_Delta->graph(plot_RSSI_DeltaSLC_Anlz)->setData(X,Y);
    }
    ui->plot_RSSI_SUM_Delta->graph(_grph)->rescaleAxes(true);
    ui->plot_RSSI_SUM_Delta->replot();

}

QVector<double>     RSSI_SUM_Analyzor_List;
double MainWindow::RSSI_SUM_Analyzor(double _rssi_sum)
{
    RSSI_SUM_Analyzor_List.append(_rssi_sum);
    if(RSSI_SUM_Analyzor_List.size() > 50)
    {
        RSSI_SUM_Analyzor_List.remove(0);
    }

    double SUM_Analyzor_Mean = std::accumulate(RSSI_SUM_Analyzor_List.begin(),RSSI_SUM_Analyzor_List.end(),.0)/RSSI_SUM_Analyzor_List.size();
    SUM_Analyzor_Mean = SUM_Analyzor_Mean*CoefAnlyzorSum + OffsetAnalyzerSum;

    return SUM_Analyzor_Mean;
}

QVector<double>     RSSI_Delta_Analyzor_List;
double MainWindow::RSSI_Delta_Analyzor(double _rssi_delta)
{
    RSSI_Delta_Analyzor_List.append(_rssi_delta);
    if(RSSI_Delta_Analyzor_List.size() > 50)
    {
        RSSI_Delta_Analyzor_List.remove(0);
    }

    double Delta_Analyzor_Mean =  std::accumulate(RSSI_Delta_Analyzor_List.begin(),RSSI_Delta_Analyzor_List.end(),.0)/RSSI_Delta_Analyzor_List.size();
    Delta_Analyzor_Mean = Delta_Analyzor_Mean*CoefAnlyzorDelta + OffsetAnalyzerDelta;

    return Delta_Analyzor_Mean;
}

double MainWindow::RSSI_SLC_Analyzor(double _rssi_slc)
{

    return 0;
}

void MainWindow::on_btnHighSum_clicked()
{
    QByteArray Message;
    Message[0] = RotMCU_HighSUM;
    TransmitMessage(Message,RotMCU_ID);
}

void MainWindow::on_btnLowSum_clicked()
{
    QByteArray Message;
    Message[0] = RotMCU_LowSUM;
    TransmitMessage(Message,RotMCU_ID);
}

void MainWindow::on_btnHighDelta_clicked()
{
    QByteArray Message;
    Message[0] = RotMCU_HighDelta;
    TransmitMessage(Message,RotMCU_ID);
}

void MainWindow::on_btnLowDelta_clicked()
{
    QByteArray Message;
    Message[0] = RotMCU_LowDelta;
    TransmitMessage(Message,RotMCU_ID);
}

/*==========================TLE TAB============================*/

void MainWindow::on_btnloadtlefromfile_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.sharif)"));
    ui->txttlefileaddress_2->setText(fileName);
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    //if find tle read two line after that
    bool findtle;
    //if find lla read three ling after that
    bool findlla;

    ui->cmbsats_2->clear();
    rotatorListOfSatsName.clear();
    rotatorListofSatsTle.clear();

    while(!in.atEnd())
    {
        QString text = in.readLine();
        if(text.startsWith("$$$",Qt::CaseInsensitive))
        {
            text = in.readLine();
            ui->txtaltitude_2->setText(text);
            text = in.readLine();
            ui->txtLongitude_2->setText(text);
            text = in.readLine();
            ui->txtaltitude_2->setText(text);
        }
        else if(text.startsWith("",Qt::CaseInsensitive))
        {
            rotatorListOfSatsName.append(text.replace("",""));
            text = in.readLine();
            rotatorListofSatsTle.append(text);
            text = in.readLine();
            rotatorListofSatsTle.append(text);
        }
    }
    ui->cmbsats_2->addItems(rotatorListOfSatsName);
}

/*==========================TLE TAB============================*/

void MainWindow::on_btnConvertTLETOLLA_2_clicked()
{
    Tleconversion TLE;
    string TLE1_str=ui->txtTLE1_2->text().toStdString();
    string TLE2_str=ui->txtTLE2_2->text().toStdString();

    //convert string to char
    char longstr1[130];
    char longstr2[130];
    int L_str1=TLE1_str.length();
    int L_str2=TLE2_str.length();

    for (int j=0;j<=L_str1-1;j++)
    {
        longstr1[j]=(TLE1_str[j]);
    }
    for (int j=0;j<=L_str2-1;j++)
    {
        longstr2[j]=(TLE2_str[j]);
    }
    //

    //read time from system with UTC format
    QDateTime current = QDateTime::currentDateTimeUtc();
    VectorXd Date_Now_Vector=VectorXd::Zero(6);
    Date_Now_Vector(0)=current.date().year();
    Date_Now_Vector(1)=current.date().month();
    Date_Now_Vector(2)=current.date().day();
    Date_Now_Vector(3)=current.time().hour();
    Date_Now_Vector(4)=current.time().minute();
    Date_Now_Vector(5)=current.time().second();
    //

    //    //Convert Date To Julian DateTime
    TransformMatrix E2;
    Matrix_Algebra E3;
    double Jd_now=E2.juliandate(Date_Now_Vector);

    double PI=3.14159265;
    // Convert TLE to Local Angles
    VectorXd LLA_GS=VectorXd::Zero(3);
    LLA_GS(0) = ui->txtLatitude_2->text().toDouble();
    LLA_GS(1) = ui->txtLongitude_2->text().toDouble();
    LLA_GS(2) = ui->txtaltitude_2->text().toDouble();

    double Lambda=(ui->Lambda_TLE_lineEdit_2->text().toDouble())/1e3;

    VectorXd RV_ECI=TLE.tle2rveci(longstr1,longstr2,Jd_now,false);
    VectorXd R_ECI=RV_ECI.block(0,0,3,1);
    MatrixXd MX_ECI2ECEF=E2.dcmeci2ecefExact(Jd_now);
    MatrixXd MX_ECI2ECEF2=MX_ECI2ECEF.block(0,0,3,3);
    VectorXd R_ECEF=MX_ECI2ECEF2*R_ECI;
    VectorXd LLA_TLE=E2.ecef2lla(R_ECEF*1e3);

    ui->txtLatitudetle_2->clear();
    ui->txtLatitudetle_2->setText(QString::number(LLA_TLE(0),'g',8));
    ui->txtLongitudetle_2->clear();
    ui->txtLongitudetle_2->setText(QString::number(LLA_TLE(1),'g',8));
    ui->txtaltitudetle_2->clear();
    ui->txtaltitudetle_2->setText(QString::number(LLA_TLE(2),'g',8));
}

int FrisingAzimuth=0,FrisingElevation=-10,FrisingType=0;
QDateTime FrisingTime;
void MainWindow::on_btnpredict_3_clicked()
{
    run = false;
    //rotatorDateTimeTimer = new QTimer(this);
    //connect(rotatorDateTimeTimer, SIGNAL(timeout()), this, SLOT(SatINMap()));
    //rotatorDateTimeTimer->start(10000);
    //Path= new QList();
    //Axis Path[seconds];
    rotatorIndexgrid = -1;
    //array for Plot
    QVector <double> Elevations(0);
    QVector <double> Dopplers(0);
    QVector <double> Azimuths(0);
    QVector <double> RisingAzimuths(0);
    QVector <QDateTime> Times(0);
    QVector <double> Times_Vec;

    int seconds = ui->txthours_3->value()*3600;

    ui->GridViewSatRising->setRowCount(0);
    QDateTime current = QDateTime::currentDateTime();

    bool satup=false;


    //type == 0  normal state
    //type == 1 set the azimuthoffset to 360
    //type == 2 when the azimuth[0]<90 and azimuth motion is decreasing then set the azimuthoffset to 360 for azimuths<90 ...
    //and set azimuth offset =0 when azimuth>90
    //type == 3 when the azimuth[0]>90 and azimuth motion is decreasing then just track until azimuth arrive to 0 or 1 degree
    int type = 0;
    //init all of column
    QTableWidgetItem *StartTime;
    QTableWidgetItem *StartAZ;
    QTableWidgetItem *MAXELTime;
    QTableWidgetItem *MAXEL;
    QTableWidgetItem *MAXAZ;
    QTableWidgetItem *EndTime;
    QTableWidgetItem *EndAZ;
    QTableWidgetItem *Tracking;
    QTableWidgetItem *TypeColumn;
    int maxelval;
    int maxazval;
    int count;
    QDateTime maxtime;
    double width = 100;//_monitorForm->getSceneWidth();
    double height = 300;//_monitorForm->getSceneHeight();
    for (int i = 0 ;i<=seconds;i++)
    {
        current = current.addSecs(1);
        VectorXd Angle_dplr=CalcVectorXd(current.toUTC(),ui->txtTLE1_2->text(),ui->txtTLE2_2->text());

        double elevation = (Angle_dplr(0)/pi)*180;
        double azimuth = (Angle_dplr(1)/pi)*180;
        double doppler = Angle_dplr(2)/1e3;

        //currentAxis.x = (width /2)*(ui->txtLongitudetle->text().toDouble())/(pi/2)+(width/2);
        //currentAxis.y = (height / 2) * (ui->txtLatitudetle->text().toDouble()) / (pi/2) + (double)height/ 2;
        //currentAxis.x = ((LLA_TLE(1)+180)/360)*width;
        //currentAxis.y = ((90-LLA_TLE(0))/180)*height;

        Elevations.append(elevation);
        Dopplers.append(doppler);
        Azimuths.append(azimuth);
        Times.append(current);



        if(maxelval<elevation)
        {
            maxelval=elevation;
            maxtime = current;
            maxazval=azimuth;
        }
        if(elevation>=0)
        {
            RisingAzimuths.append(azimuth);
        }

        //Path[seconds] = currentAxis;
        if(elevation>=0 && i == 0)
        {
            satup = true;
            count = ui->GridViewSatRising->rowCount();
            ui->GridViewSatRising->setRowCount(count+1);

            maxelval = elevation;
            maxazval=azimuth;
            maxtime=current;

            rotatorSatupDateTime = current;
            QDateTime timeofrising = current;
            timeofrising=  timeofrising.addSecs(1);

            QString _NewDateTimeString=current.toString("yyyy-MM-dd hh:mm:ss");

            StartTime = new QTableWidgetItem(tr("%1").arg(_NewDateTimeString));
            ui->GridViewSatRising->setItem(count, 0, StartTime);

            StartAZ = new QTableWidgetItem(tr("%1").arg(azimuth));
            ui->GridViewSatRising->setItem(count, 1, StartAZ);

            if(count==0)
            {
                FrisingAzimuth=azimuth;
                FrisingTime=current;
                FrisingType=type;
                FrisingElevation=elevation;
                qDebug()<<"In view1:"<<FrisingAzimuth<<" " << FrisingElevation << " "<< FrisingTime;
            }

            VectorXd Angle_dplr=CalcVectorXd(current,ui->txtTLE1_2->text(),ui->txtTLE2_2->text());

            elevation = (Angle_dplr(0)/pi)*180;
            azimuth = (Angle_dplr(1)/pi)*180;


        }
        if(elevation>=0 && !satup )
        {
            count = ui->GridViewSatRising->rowCount();
            ui->GridViewSatRising->setRowCount(count+1);

            maxelval = elevation;
            maxazval=azimuth;
            maxtime=current;

            satup = true;
            rotatorSatupDateTime = current;

            QString _NewDateTimeString=current.toString("yyyy-MM-dd hh:mm:ss");

            StartTime = new QTableWidgetItem(tr("%1").arg(_NewDateTimeString));
            ui->GridViewSatRising->setItem(count, 0, StartTime);

            StartAZ = new QTableWidgetItem(tr("%1").arg(azimuth));
            ui->GridViewSatRising->setItem(count, 1, StartAZ);

            if(count==0)
            {
                FrisingAzimuth=azimuth;
                FrisingTime=current;
                FrisingType=type;
                FrisingElevation=elevation;
                qDebug()<<"In view1:"<<FrisingAzimuth<<" " << FrisingElevation << " "<< FrisingTime;
            }

        }
        if(elevation<0 && satup && RisingAzimuths.count()>1)
        {
            int indx=1;
            for(int ii=1;ii<RisingAzimuths.count()-1;ii++)
            {
                if(RisingAzimuths[ii]!=RisingAzimuths[0])
                {
                    indx=ii;
                    break;
                }
            }
            if( RisingAzimuths[0]>=180 )
            {

                if( RisingAzimuths[indx]>RisingAzimuths[0] )
                {
                    type=1;
                }
                //adad haye kamtar az 90 ra ba 360 jam+ kon va ghesmati ke bishtar az 90 ast va kamtar az 180
                // ra track nakon, dar in sourat nimeye bishtar niz track shode

            }
            else if(RisingAzimuths[0]<180 && RisingAzimuths[0]>=90)
            {
                if(RisingAzimuths[indx]<RisingAzimuths[0])
                    type=3;
                // تنها لازم است تا نیمه اول ردگیری شود در این صورت نیمه بیشتر ردیابی شده است
                // یعنی تا وقتی که یک برش بزرگ مشاهده شد ردگیری کن

            }
            else if( RisingAzimuths[0]<90 )
            {
                if( RisingAzimuths[indx]<RisingAzimuths[0] )
                    type=2;
                // عددهای کمتر از ۹۰ را با ۳۶۰ جمع کن و عددهای بیشتر از ۹۰ را دست نزن
            }
            else
            {
                type=0;
            }
            // دو حالت بد و استثنایی ممکن است مشکل ایجاد کند
            // نخست اینکه آزیموس اولی مثلا ۳۵۹ باشد و دومی ییهو صفر شود
            // ویا آزیموس اولی ۰ باشد و دومی ییهو ۳۵۹ شود
            //که بهتر است اینها نیز شناسایی شوند


            //find max elevation
            satup=false;
            rotatorSatDownDateTime = current;

            QString _NewDateTimeString=maxtime.toString("yyyy-MM-dd hh:mm:ss");
            MAXELTime = new QTableWidgetItem(tr("%1").arg(_NewDateTimeString));
            ui->GridViewSatRising->setItem(count, 2, MAXELTime);

            MAXEL= new QTableWidgetItem(tr("%1").arg(maxelval));
            ui->GridViewSatRising->setItem(count,3, MAXEL);

            MAXAZ= new QTableWidgetItem(tr("%1").arg(maxazval));
            ui->GridViewSatRising->setItem(count,4, MAXAZ );


            _NewDateTimeString=current.toString("yyyy-MM-dd hh:mm:ss");
            EndTime = new QTableWidgetItem(tr("%1").arg(_NewDateTimeString));
            ui->GridViewSatRising->setItem(count, 5, EndTime);

            EndAZ = new QTableWidgetItem(tr("%1").arg(azimuth));
            ui->GridViewSatRising->setItem(count, 6, EndAZ);

            Tracking = new  QTableWidgetItem(tr("%1").arg("1"));
            ui->GridViewSatRising->setItem(count,7,Tracking);

            TypeColumn = new  QTableWidgetItem(tr("%1").arg(type));
            ui->GridViewSatRising->setItem(count,8,TypeColumn);

            RisingAzimuths.clear();
        }
        //reset maxEL
        if(elevation<0 && !satup)
        {
            type=0;
            maxelval=elevation;
        }

        ui->progressBar_3->setValue(int(double(double(i)/double(seconds))*100));
        if(i==seconds && elevation>0 )
        {
            Tracking = new  QTableWidgetItem(tr("%1").arg("1"));
            ui->GridViewSatRising->setItem(count,7,Tracking);

            TypeColumn = new  QTableWidgetItem(tr("%1").arg("0"));
            ui->GridViewSatRising->setItem(count,8,TypeColumn);
        }

    }

    for(int i=0;i<Times.count();i++)
    {
        Times_Vec.append(i/60.0/60.0);
    }

    ui->plot_predict_2->clearGraphs();
    ui->plot_predict_2->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    ui->plot_predict_2->legend->setFont(legendFont);
    ui->plot_predict_2->legend->setBrush(QBrush(QColor(255,255,255,230)));
    ui->plot_predict_2->xAxis->setLabel("Time [hour]");

    ui->plot_predict_2->yAxis->setLabelFont(legendFont);
    ui->plot_predict_2->xAxis->setLabelFont(legendFont);

    if(ui->EL_radioButton_2->isChecked())
    {
        ui->plot_predict_2->addGraph();
        ui->plot_predict_2->graph(0)->setPen(QPen(Qt::red));
        ui->plot_predict_2->graph(0)->setName("EL");
        ui->plot_predict_2->graph(0)->setData(Times_Vec,Elevations);
        ui->plot_predict_2->yAxis->setLabel("El Angle [degree]");
    }
    else if (ui->Doppler_radioButton_2->isChecked())
    {
        ui->plot_predict_2->addGraph();
        ui->plot_predict_2->graph(0)->setPen(QPen(Qt::blue));
        ui->plot_predict_2->graph(0)->setName("Doppler");
        ui->plot_predict_2->graph(0)->setData(Times_Vec,Dopplers);
        ui->plot_predict_2->yAxis->setLabel("Doppler [kHz]");
    }
    else if(ui->EL_Doppler_radioButton_2->isChecked())
    {
        ui->plot_predict_2->addGraph();
        ui->plot_predict_2->graph(0)->setPen(QPen(Qt::red));
        ui->plot_predict_2->graph(0)->setName("EL");
        ui->plot_predict_2->graph(0)->setData(Times_Vec,Elevations);

        ui->plot_predict_2->addGraph();
        ui->plot_predict_2->graph(1)->setPen(QPen(Qt::blue));
        ui->plot_predict_2->graph(1)->setName("Doppler");
        ui->plot_predict_2->graph(1)->setData(Times_Vec,Dopplers);

        ui->plot_predict_2->yAxis->setLabel("El Angle [degree], Doppler [kHz]");
    }
    else if(ui->EL_AZ_radioButton_2->isChecked())
    {
        ui->plot_predict_2->addGraph();
        ui->plot_predict_2->graph(0)->setPen(QPen(Qt::red));
        ui->plot_predict_2->graph(0)->setName("EL");
        ui->plot_predict_2->graph(0)->setData(Times_Vec,Elevations);

        ui->plot_predict_2->addGraph();
        ui->plot_predict_2->graph(1)->setPen(QPen(Qt::blue));
        ui->plot_predict_2->graph(1)->setName("AZ");
        ui->plot_predict_2->graph(1)->setData(Times_Vec,Azimuths);

        ui->plot_predict_2->yAxis->setLabel("El Angle [degree], AZ Angle [degree]");
    }

    ui->plot_predict_2->rescaleAxes();
    ui->plot_predict_2->replot();
    ui->plot_predict_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    if(ui->chkSavePredict2File->isChecked())
    {
        QString predictionFile = qApp->applicationDirPath() + "/predictionFiles/" + ui->cmbsats_2->currentText() + "_Prediction_File"  + ".csv" ;
        QFile predictionFileStream(predictionFile);
        if(predictionFileStream.open(QIODevice::ReadWrite))
        {
            QTextStream mystream(&predictionFileStream);
            mystream <<"date"<< " " << "Time"  << "," << "Elevations" << "," << "Azimuths" << "," << "Dopplers" << "," << endl;
            for (int i = 0 ;i < seconds;i++)
            {
                mystream << Times[i].toString("dd-MM-yy hh:mm:ss.zzz")  << "," << Elevations[i] << "," << Azimuths[i] << "," << Dopplers[i] << "," << endl;
            }
        }
        predictionFileStream.close();
    }

    //MonitorForm.setSatellitePosition(Path,Path.length());
    //MonitorForm.startAnimation();
    //_monitorForm->setSatellitePosition(Path);
    //_monitorForm->startAnimation();
}

VectorXd MainWindow::CalcVectorXd(QDateTime current,QString Line1,QString line2)
{
    Tleconversion TLE;
    string TLE1_str=Line1.toStdString();
    string TLE2_str=line2.toStdString();

    //convert string to char
    char longstr1[130];
    char longstr2[130];
    int L_str1=TLE1_str.length();
    int L_str2=TLE2_str.length();

    for (int j=0;j<=L_str1-1;j++)
    {
        longstr1[j]=(TLE1_str[j]);
    }
    for (int j=0;j<=L_str2-1;j++)
    {
        longstr2[j]=(TLE2_str[j]);
    }



    //
    VectorXd Date_Now_Vector=VectorXd::Zero(6);
    Date_Now_Vector(0)=current.date().year();
    Date_Now_Vector(1)=current.date().month();
    Date_Now_Vector(2)=current.date().day();
    Date_Now_Vector(3)=current.time().hour();
    Date_Now_Vector(4)=current.time().minute();
    Date_Now_Vector(5)=current.time().second();
    //

    //    //Convert Date To Julian DateTime
    TransformMatrix E2;
    double Jd_now=E2.juliandate(Date_Now_Vector);

    // Convert TLE to Local Angles
    VectorXd LLA_GS=VectorXd::Zero(3);
    LLA_GS(0) = ui->txtLatitude_2->text().toDouble();
    LLA_GS(1) = ui->txtLongitude_2->text().toDouble();
    LLA_GS(2) = ui->txtaltitude_2->text().toDouble();

    double Lambda=(ui->Lambda_TLE_lineEdit_2->text().toDouble())/1e3;

    VectorXd Angle_dplr=TLE.tle2angle(longstr1,longstr2,Jd_now,Lambda,LLA_GS,false);
    return Angle_dplr;
}

void MainWindow::on_pushButton_clicked()
{
    CoefAnlyzorSum = ui->leCoefAnlyzorSum->text().toDouble();
    OffsetAnalyzerSum = ui->leOffsetAnalyzerSum->text().toDouble();
    CoefAnlyzorDelta = ui->leCoefAnlyzorDelta->text().toDouble();
    OffsetAnalyzerDelta = ui->leOffsetAnalyzerDelta->text().toDouble();
}

void MainWindow::on_btnperedict_clicked()
{
    countoftle = 0;
     ui->gridperdicSats->setRowCount(0);
    QString Line1="";
    QString Line2="";
    QString SatName="";
    QString fileName =  ui->txttlefileaddress_2->text();
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    //if find tle read two line after that
    bool findtle;
    //if find lla read three ling after that
    bool findlla;

    countoftle = ui->cmbsats_2->count();

    int currentnumber = 0;
    while(!in.atEnd())
    {
        QString text = in.readLine();
        if(text.startsWith("",Qt::CaseInsensitive))
        {
            currentnumber++;
            SatName = text.replace("","");
            rotatorListOfSatsName.append(SatName);
            text = in.readLine();
            Line1 = text;
            rotatorListofSatsTle.append(text);
            text = in.readLine();
            Line2 = text;
            rotatorListofSatsTle.append(text);
            qDebug()<<"Sending Tle To Method";
            PerdictSat(Line1,Line2, SatName);

            ui->progresssat->setValue(int(double(double(currentnumber)/double(countoftle))*100));
        }
    }
}
void MainWindow::PerdictSat(QString line1, QString line2, QString satname)
{
    rotatorIndexgrid = -1;

    int seconds = ui->txthours_3->value()*3600;


    QDateTime current = QDateTime::currentDateTime();

    bool satup=false;


    //type == 0  normal state
    //type == 1 set the azimuthoffset to 360
    //type == 2 when the azimuth[0]<90 and azimuth motion is decreasing then set the azimuthoffset to 360 for azimuths<90 ...
    //and set azimuth offset =0 when azimuth>90
    //type == 3 when the azimuth[0]>90 and azimuth motion is decreasing then just track until azimuth arrive to 0 or 1 degree
    int type = 0;
    //init all of column
    QTableWidgetItem *SatName;
    QTableWidgetItem *StartTime;
    QTableWidgetItem *StartAZ;
    QTableWidgetItem *MAXELTime;
    QTableWidgetItem *MAXEL;
    QTableWidgetItem *MAXAZ;
    QTableWidgetItem *EndTime;
    QTableWidgetItem *EndAZ;
    QTableWidgetItem *TypeColumn;
    int maxelval;
    int maxazval;
    int count;
    QDateTime maxtime;
    for (int i = 0 ;i<=seconds;i++)
    {

        qDebug()<<"Second::"<<i;
        current = current.addSecs(1);
        VectorXd Angle_dplr=CalcVectorXd(current.toUTC(),line1,line2);

        double elevation = (Angle_dplr(0)/pi)*180;
        double azimuth = (Angle_dplr(1)/pi)*180;

        if(maxelval<elevation)
        {
            maxelval=elevation;
            maxtime = current;
            maxazval=azimuth;
        }

        if(elevation>=0 && i == 0)
        {
            qDebug()<<"FindRising ON::"<<i;
            satup = true;
            count = ui->gridperdicSats->rowCount();
            ui->gridperdicSats->setRowCount(count+1);

            maxelval = elevation;
            maxazval=azimuth;
            maxtime=current;

            rotatorSatupDateTime = current;
            QDateTime timeofrising = current;
            timeofrising=  timeofrising.addSecs(1);

            QString _NewDateTimeString=current.toString("yyyy-MM-dd hh:mm:ss");

            SatName = new QTableWidgetItem(tr("%1").arg(satname));
            ui->gridperdicSats->setItem(count, 0, SatName);

            StartTime = new QTableWidgetItem(tr("%1").arg(_NewDateTimeString));
            ui->gridperdicSats->setItem(count, 1, StartTime);

            StartAZ = new QTableWidgetItem(tr("%1").arg(azimuth));
            ui->gridperdicSats->setItem(count, 2, StartAZ);

            VectorXd Angle_dplr=CalcVectorXd(current,line1,line2);

            elevation =  (Angle_dplr(0)/pi)*180;
            azimuth =(Angle_dplr(1)/pi)*180;
        }
        if(elevation>=0 && !satup)
        {
            qDebug()<<"FindRising ON::"<<i;
            count = ui->gridperdicSats->rowCount();
            ui->gridperdicSats->setRowCount(count+1);

            maxelval = elevation;
            maxazval=azimuth;
            maxtime=current;

            satup = true;
            rotatorSatupDateTime = current;

            SatName = new QTableWidgetItem(tr("%1").arg(satname));
            ui->gridperdicSats->setItem(count, 0, SatName);

            QString _NewDateTimeString=current.toString("yyyy-MM-dd hh:mm:ss");

            StartTime = new QTableWidgetItem(tr("%1").arg(_NewDateTimeString));
            ui->gridperdicSats->setItem(count, 1, StartTime);

            StartAZ = new QTableWidgetItem(tr("%1").arg(azimuth));
            ui->gridperdicSats->setItem(count,2, StartAZ);
        }

        if(elevation<0 && satup)
        {
            qDebug()<<"Falling ON::"<<i;

            qDebug()<<"Adding ON Grid::"<<i;
            satup=false;
            rotatorSatDownDateTime = current;

            QString _NewDateTimeString=maxtime.toString("yyyy-MM-dd hh:mm:ss");
            MAXELTime = new QTableWidgetItem(tr("%1").arg(_NewDateTimeString));
            ui->gridperdicSats->setItem(count, 3, MAXELTime);

            MAXEL= new QTableWidgetItem(tr("%1").arg(maxelval));
            ui->gridperdicSats->setItem(count,4, MAXEL);

            MAXAZ= new QTableWidgetItem(tr("%1").arg(maxazval));
            ui->gridperdicSats->setItem(count,5, MAXAZ );


            _NewDateTimeString=current.toString("yyyy-MM-dd hh:mm:ss");
            EndTime = new QTableWidgetItem(tr("%1").arg(_NewDateTimeString));
            ui->gridperdicSats->setItem(count, 6, EndTime);

            EndAZ = new QTableWidgetItem(tr("%1").arg(azimuth));
            ui->gridperdicSats->setItem(count, 7, EndAZ);
            type=-1;
            TypeColumn = new  QTableWidgetItem(tr("%1").arg(type));
            ui->gridperdicSats->setItem(count,8,TypeColumn);

            qDebug()<<"End OF Adding in Grid::"<<i;
        }
        if(elevation<0 && !satup)
        {
            type=0;
            maxelval=elevation;
        }
    }


}

void MainWindow::on_comboBoxGPS_currentIndexChanged(int index)
{
    QString arg1=ui->comboBoxGPS->currentText();
    if(arg1.toUpper().contains("SHARIF"))
    {
        ui->txtLatitude_2->setText("35.702242");
        ui->txtLongitude_2->setText("51.352149");
        ui->txtaltitude_2->setText("1053");
    }
    else
    if(arg1.toUpper().contains("QESHM"))
    {
        ui->txtLatitude_2->setText("26.859455");
        ui->txtLongitude_2->setText("56.146428");
        ui->txtaltitude_2->setText("20");
    }
    else
    if(arg1.toUpper().contains("BUSHEHR"))
    {
        ui->txtLatitude_2->setText("28.9900440");
        ui->txtLongitude_2->setText("51.0236890");
        ui->txtaltitude_2->setText("20");
    }
    else
    if(arg1.toUpper().contains("MAHDASHT"))
    {
        ui->txtLatitude_2->setText("35.7632562");
        ui->txtLongitude_2->setText("50.7890844");
        ui->txtaltitude_2->setText("1000");
    }

}

void MainWindow::on_rbSelectDelta_toggled(bool checked)
{
    if(ui->rbSelectDelta->isChecked())
    {
        QByteArray Message;
        Message[0] = RotMCU_SelectDelta;
        TransmitMessage(Message,RotMCU_ID);
    }
    else if(ui->rbSelectSLC->isChecked())
    {
        QByteArray Message;
        Message[0] = RotMCU_SelectSLC;
        TransmitMessage(Message,RotMCU_ID);
    }
}

void pack24(uint32_t val, uint8_t *dost)
{
    dost[0] = (val & 0x0000ff) >> 0;
    dost[1] = (val & 0x00ff00) >> 8;
    dost[2] = (val & 0xff0000) >> 16;
}
void MainWindow::on_btnsetFrequencyRotMCU_clicked()
{
    QStringList txtSplittedIntFract = ui->leFreqRotMCU->text().split('.');
    if(txtSplittedIntFract.size() == 2)
    {
        int freqInt = txtSplittedIntFract.at(0).toInt();
        int freqFract = txtSplittedIntFract.at(1).toInt();

        QByteArray Message;
        Message[0] = (freqInt & 0x0000ff) >> 0;
        Message[1] = (freqInt & 0x00ff00) >> 8;
        Message[2] = (freqInt & 0xff0000) >> 16;
//==============================================//
        Message[3] = (freqFract & 0x0000ff) >> 0;
        Message[4] = (freqFract & 0x00ff00) >> 8;
        Message[5] = (freqFract & 0xff0000) >> 16;


        QByteArray  tranMSG;
        tranMSG.append(msgTrans_Sync1);
        tranMSG.append(msgTrans_Sync2);
        tranMSG.append(RotMCU_ID);

        tranMSG.append(Message.size());
        uint8_t msgg[Message.size()];

        for(int i=0; i < Message.size(); i++)
        {
            tranMSG.append(Message[i]);
            msgg[i] = Message[i];
        }

        u16_8_tx.u16 = gen_crc16_tx(msgg , tranMSG.size());
        tranMSG.append(u16_8_tx.u8[0]);
        tranMSG.append(u16_8_tx.u8[1]);
        TransmitMessage(tranMSG,RotMCU_ID);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Your number dose not match Double Value\n please Enter Corrrect number xxx.yyy");
    }
}
