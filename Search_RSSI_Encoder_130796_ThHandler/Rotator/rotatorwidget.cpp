#include "rotatorwidget.h"
#include "ui_rotatorwidget.h"

#include <iostream>
#include <stdlib.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtGui>
#include <QMap>
#include <QTextStream>
#include <QString>
#include <QTimer>
#include <math.h>
# include <qcustomplot.h>
#include <QDesktopWidget>
//
#include "transformmatrix.h"
#include "matrix_algebra.h"
#include "iterative_estimation.h"
#include <Eigen_Library/Eigen/Eigen>
#include <fstream>
#include <SGP4/sgp4ext.h>
#include <SGP4/sgp4io.h>
#include <SGP4/sgp4unit.h>
#include "tleconversion.h"
#include <QtWebKit/QtWebKit>
#include "monitorform.h"
#include <QObject>
//_monitorForm

using namespace std;
QTimer *rotatorDateTimeTimer;
QSerialPort *rotatorSerial;
QList<Axis> *Path;
RotatorWidget::RotatorWidget(DopplerEntity *dopplerEntity, QSerialPort *kenwoodSerial ,MonitorForm *monitorForm, QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::RotatorWidget)
{
    ui->setupUi(this);
    _monitorForm = monitorForm;
    _dopplerEntity = dopplerEntity;

    ui->chkconnectedboardcontroller->setVisible(false);
    ui->chkconnectedboardcontroller->setChecked(false);

    ui->chkconnectedrotator->setVisible(false);
    ui->chkconnectedrotator->setChecked(false);

    ui->chkconnectedboardcontroller->setDisabled(true);
    ui->chkconnectedrotator->setDisabled(true);
    //    ui->btndisconnect->setDisabled(true);
    //    //fill combo of ports

    socket = new QTcpSocket(this);
    socket2 = new QTcpSocket(this);
    discoversocket = new QUdpSocket(this);

    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        ui->cmbdevicelist->addItem(info.portName(),info.portName());
        //ui->cmbkenwooddevices->addItem(info.portName(),info.portName());
    }

    //Discovery: Who is out there?
    discoversocket->bind(30303, QUdpSocket::ShareAddress);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReadFromNetwork()));
    connect(socket2, SIGNAL(readyRead()), this, SLOT(readyReadFromControl()));
    connect(discoversocket, SIGNAL(readyRead()), this, SLOT( GetHelloAnswer()));



    //console
    console = new Console;
    console->setEnabled(false);
    console->setMinimumWidth(300);
    ui->formLayout->addWidget(console);
    connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));

    //rotatorSerial = new QSerialPort(this);
    rotatorSerial = kenwoodSerial;
    on_rbtNetwork_clicked();

}



RotatorWidget::~RotatorWidget()
{
    socket2->write("$$TurnOFF@@");
    delete ui;
}

void RotatorWidget::RefreshTime()
{
    QTime date =QDateTime::currentDateTime().time();
    QTime utcdate =QDateTime::currentDateTimeUtc().time();
    ui->cmblocaldatetime->setTime(date);
    ui->cmbutctime->setTime(utcdate);
    if(!run)
    {
        run = true;
        //
        //_monitorForm->stopAnimation();
        Path = new QList<Axis>();
        QDateTime current = QDateTime::currentDateTimeUtc();
        for (int sec=0;sec<=ui->txthours->value()*3600;sec++)
        {
            current = current.addSecs(1);
            qDebug() << "Current Time= " <<current.toString();
            Axis currentAxis;
            Tleconversion TLE;
            string TLE1_str=ui->txtTLE1->text().toStdString();
            string TLE2_str=ui->txtTLE2->text().toStdString();

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
            LLA_GS(0) = ui->txtLatitude->text().toDouble();
            LLA_GS(1) = ui->txtLongitude->text().toDouble();
            LLA_GS(2) = ui->txtaltitude->text().toDouble();

            double Lambda=(ui->Lambda_TLE_lineEdit->text().toDouble())/1e3;

            VectorXd RV_ECI=TLE.tle2rveci(longstr1,longstr2,Jd_now,false);
            VectorXd R_ECI=RV_ECI.block(0,0,3,1);
            MatrixXd MX_ECI2ECEF=E2.dcmeci2ecefExact(Jd_now);
            MatrixXd MX_ECI2ECEF2=MX_ECI2ECEF.block(0,0,3,3);
            VectorXd R_ECEF=MX_ECI2ECEF2*R_ECI;
            VectorXd LLA_TLE=E2.ecef2lla(R_ECEF*1e3);

            ui->txtLatitudetle->clear();
            ui->txtLatitudetle->setText(QString::number(LLA_TLE(0),'g',8));
            ui->txtLongitudetle->clear();
            ui->txtLongitudetle->setText(QString::number(LLA_TLE(1),'g',8));
            ui->txtaltitudetle->clear();
            ui->txtaltitudetle->setText(QString::number(LLA_TLE(2),'g',8));

            QString Lon =QString::number(LLA_TLE(1),'g',8);
            QString lat = QString::number(LLA_TLE(0),'g',8);
            float  temp=0;
            temp=Lon.toFloat();
            qDebug()<<"Temp Long"<<temp;
            //double alt  =  LLA_TLE(2);
            //currentAxis.x = (width/2)+(temp/180)*(width/2);
            currentAxis.x = 400+(temp/180)*400;
            temp=lat.toFloat();
            qDebug()<<"Temp Lat"<<temp;
            //currentAxis.y = (height/2)-(temp/90)*(height/2);
            currentAxis.y = 200-(temp/90)*200;
            qDebug()<<"CurrentX="<< currentAxis.x;
            qDebug()<<"CurrentY="<< currentAxis.y;
            currentAxis.t =  current.toLocalTime();

            Path->append(currentAxis);

        }
        for(int i=0; i< Path->count() ; i++)
        {
            qDebug() << "Ehsan X= " << Path->at(i).x << ",Ehsan Y= " << Path->at(i).y;
        }

        _monitorForm->setSatellitePosition(Path);
        _monitorForm->startAnimation();
    }
}



QTimer *rotatorTimerTLE ;//= new QTimer(this);

//QString fileName;

bool rotatorConnect = false;
bool rotatorNetworkConnected = false;
//int  rotatorAzvalue = -1000;
//int  rotatorElvalue = -1000;
int rotatorElevation = 0;
int rotatorAzimuth = 0;



void RotatorWidget::on_btnloadtlefromfile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.sharif)"));
    ui->txttlefileaddress->setText(fileName);
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    //if find tle read two line after that
    bool findtle;
    //if find lla read three ling after that
    bool findlla;

    while(!in.atEnd())
    {
        QString text = in.readLine();
        if(text.startsWith("$$$",Qt::CaseInsensitive))
        {
            text = in.readLine();
            ui->txtaltitude->setText(text);
            text = in.readLine();
            ui->txtLongitude->setText(text);
            text = in.readLine();
            ui->txtaltitude->setText(text);
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
    ui->cmbsats->addItems(rotatorListOfSatsName);
}

void RotatorWidget::on_cmbsats_currentIndexChanged(const QString &arg1)
{
    int index = ui->cmbsats->currentIndex();
    QString tle1 = rotatorListofSatsTle[index*2];
    QString tle2 = rotatorListofSatsTle[index*2+1];
    ui->txtTLE1->setText(tle1);
    ui->txtTLE2->setText(tle2);
}

void RotatorWidget::on_rbtNetwork_clicked()
{
    ui->SerialGroup->setDisabled(true);
    ui->NetworkGroup->setEnabled(true);
}

void RotatorWidget::on_rbtSerial_clicked()
{
    ui->NetworkGroup->setDisabled(true);
    ui->SerialGroup->setEnabled(true);
}

void RotatorWidget::on_btnDiscoverNetwork_clicked()
{
    QByteArray message ;//= "Discovery: Who is out there?";
    message.append("Discovery: Who is out there?");
    QByteArray datagram = message;
    discoversocket->writeDatagram(datagram.data(), datagram.size(),
                                  QHostAddress::Broadcast, 30303);
}

void RotatorWidget::GetHelloAnswer()
{
    QString line   = "";

    while (discoversocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(discoversocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        discoversocket->readDatagram(datagram.data(), datagram.size(),
                                     &sender, &senderPort);
        qDebug()<< line;
        qDebug()<< sender.toString();
        qDebug()<< datagram.data();
        line = datagram.data();
        if(line.contains("TT&C ANTENNA SH"))
        {
            ui->txtIPAddress->setText(sender.toString());
        }
    }
}

void RotatorWidget::on_btnconnectNetwork_clicked()
{
    socket->connectToHost(ui->txtIPAddress->text(), ui->txtportnumber->text().toInt());
    socket2->connectToHost(ui->txtIPAddress->text(),ui->txtcontrolport->text().toInt());
    if (socket->waitForConnected(1000))
    {
        rotatorConnect = true;
    }
    if (socket2->waitForConnected(1000))
    {
        rotatorConnect = true;
    }
}
void RotatorWidget::RefreshAxis()
{
    QString command = "C2\r\n";
    SendCommand(command.toLocal8Bit(),false);
}

void RotatorWidget::on_btndisconnectnetwork_clicked()
{
    socket->close();
    socket2->close();
    rotatorConnect= false;
}

void RotatorWidget::on_btnturnon_clicked()
{
    qDebug()<<"BeforeSendTurnON:"<<QDateTime::currentDateTime().toString();
    socket2->write("$$TurnON@@");
    qDebug()<<"AfterSendTurnON:"<<QDateTime::currentDateTime().toString();
    QTimer *timerenter = new QTimer(this);
    connect(timerenter, SIGNAL(timeout()), this, SLOT(SendEnter()));
    timerenter->start(500);
}

int rotatorTimer=0;
void RotatorWidget::SendEnter()
{
    if(rotatorTimer == 1)
    {
        SendCommand("\r\n",true);

        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(RefreshAxis()));
        timer->start(500);
    }
    rotatorTimer ++;
}

void RotatorWidget::msleep(unsigned long msecs)
{
    QMutex mutex;
    mutex.lock();

    QWaitCondition waitCondition;
    waitCondition.wait(&mutex, msecs);

    mutex.unlock();
}

void RotatorWidget::on_btnturnoff_clicked()
{
    rotatorTimer = 0;
    socket2->write("$$TurnOFF@@");
}

void RotatorWidget::on_btnvoltage_clicked()
{
    socket2->write("$$Battery@@");
}
void RotatorWidget::readyReadFromControl()
{
    QByteArray data  ;
    data = socket2->readAll();
    float v0;
    float V;
    if(data.count()>0)
    {
        v0 = float(data[0])+float(data[1])*256;
        //V = ((v0*3.3)/1023)*(116/16);
        V = v0*0.0233871;
    }
    ui->txtvoltage->setText(QString::number(V));
}

void RotatorWidget::readyReadFromNetwork()
{
//    // We'll loop over every (complete) line of text that the server has sent us:
//    while(socket->canReadLine())
//    {
//        // Here's the line the of text the server sent us (we use UTF-8 so
//        // that non-English speakers can chat in their native language)
//        QString line = QString::fromUtf8(socket->readLine()).trimmed();

//        QString text = line;
//        //qDebug()<<text;
//        if(text.contains("Connect OK"))
//        {
//            //ui->txtinputext->insertPlainText("Connect To Device Successfull");
//            rotatorConnect = true;
//        }
//        if(text.contains("AZ=") && text.contains("EL="))
//        {
//            QString AZ= text.replace("AZ=","");
//            AZ = AZ.left(3);
//            rotatorAzvalue = AZ.toInt();
//            text = text.remove(0,3);

//            ui->lblazimuth->setText(QString::number(rotatorAzvalue));

//            text= text.replace("EL=","").trimmed();
//            rotatorElvalue =  text.toInt();
//            ui->lblelevation->setText(QString::number(rotatorElvalue));

//        }
//        else
//        {
//            //ui->txtinputext->insertPlainText(text);
//        }
//    }
}

void RotatorWidget::on_btnConnectSerial_clicked()
{

    rotatorSerial->setPortName(ui->cmbdevicelist->currentText());
    int baudrate=ui->txtbaudrate->text().toInt();
    if (rotatorSerial->open(QIODevice::ReadWrite)) {
        if (rotatorSerial->setBaudRate(baudrate,QSerialPort::AllDirections)
                && rotatorSerial->setDataBits(QSerialPort::Data8)
                && rotatorSerial->setParity(QSerialPort::NoParity)
                && rotatorSerial->setStopBits( QSerialPort::OneStop)
                && rotatorSerial->setFlowControl(QSerialPort::NoFlowControl))
        {
            connect(rotatorSerial, SIGNAL(readyRead()), this, SLOT(readDataFromSerial()));
            ui->btnConnectSerial->setDisabled(true);
            ui->btnDisconnectSerial->setEnabled(true);
            QTimer *timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(RefreshAxis()));
            timer->start(200);

            //            ui->AutomaticGroup->setEnabled(true);
            //            ui->ManualGroup->setEnabled(true);

            //            //console
            //            console->setEnabled(true);
            //            console->setLocalEchoEnabled(true);
        }
    }
}
QString rotatorText;

void RotatorWidget::readDataFromSerial()
{
    //Connect OK
//    QByteArray data = rotatorSerial->readAll();

//    if(rotatorText.length()>0)
//        rotatorText =rotatorText +  QString::fromAscii(data);
//    else
//        rotatorText = QString::fromAscii(data);

//    if(rotatorText.contains("nnect OK"))
//    {
//        rotatorConnect = true;
//    }
//    else if(rotatorText.contains("FA") && rotatorText.length()>13)
//    {
//        rotatorText = rotatorText.replace("\r\n","");
//        rotatorText = rotatorText.replace("FA","");
//        rotatorText = rotatorText.replace(";","");
//        qDebug()<<"FAMessage"<<rotatorText;
//        long value  = rotatorText.toLong();
//        rotatorText = QString::number(value);
//    }
//    else if(rotatorText.contains("AZ=") && rotatorText.contains("EL="))
//    {
//        qDebug()<< "UnHandeled Data";
//    }
//    else if(rotatorText.contains("AZ="))
//    {
//        QString AZ= rotatorText.right(5);
//        rotatorAzvalue = AZ.toInt();
//        ui->lblazimuth->setText(QString::number(rotatorAzvalue));
//    }
//    else if(rotatorText.contains("OI") && rotatorText.count()>35)
//    {
//        qDebug()<<"Read Value:"<<rotatorText;
//        rotatorText = rotatorText.replace("\r\n","");
//        int indexofoi = rotatorText.indexOf("OI",0);
//        if(rotatorText.length() >= 35+indexofoi)
//        {
//            rotatorText = rotatorText.remove(0,indexofoi+13);
//            rotatorText = rotatorText.trimmed();
//            int indexofend  = rotatorText.indexOf(";",0);
//            rotatorText = rotatorText.remove(indexofend,rotatorText.count()-indexofend);
//            //FIXME: 5 changed to 6
//            if(rotatorText.contains("-"))
//                rotatorText = rotatorText.remove(6, rotatorText.count()-6);
//            else
//                rotatorText = rotatorText.remove(5, rotatorText.count()-5);
//            qDebug()<<"RIT Value:"<<rotatorText;
//            RITValue = rotatorText.toDouble();
//            //qDebug()<<"Original :"<<RITValue;
//            rotatorText="";
//        }
//    }
//    else if(rotatorText.contains("EL="))
//    {
//        QString EL= rotatorText.right(5);
//        rotatorElvalue =  EL.toInt();
//        ui->lblelevation->setText(QString::number(rotatorElvalue));
//    }
    //
    //    if(!rotatorText.contains("EL"))
    //        if(!rotatorText.contains("AZ"))
//            console->putData(data);
}

void RotatorWidget::on_btnDisconnectSerial_clicked()
{
    rotatorSerial->close();
    ui->btnConnectSerial->setEnabled(true);
    ui->btnDisconnectSerial->setDisabled(true);
    rotatorConnect= false;

    //    ui->AutomaticGroup->setDisabled(true);
    //    ui->ManualGroup->setDisabled(true);
}

void RotatorWidget::on_chkoffset_clicked()
{
    if(ui->chkoffset->isChecked())
    {
        ui->txtAzOffset->setEnabled(true);
        ui->txtELOffset->setEnabled(true);
    }
    else
    {
        ui->txtELOffset->setEnabled(false);
        ui->txtAzOffset->setEnabled(false);
    }
}

void RotatorWidget::on_btnstart_clicked()
{
    rotatorTimerTLE = new QTimer(this);
    connect(rotatorTimerTLE, SIGNAL(timeout()), this, SLOT(ConvertTLETOAZEL()));
    int interval = ui->txtrefreshrate->text().toInt();
    rotatorTimerTLE->start(interval);
}

double rotatorOlddoppler=0;

//int sbandOldElevation=0;
//int sbandOldAzimuth=-100000;
//int rotatorIndexgrid = 0;
void RotatorWidget::ConvertTLETOAZEL()
{
//    try
//    {
//    int typeofpath = 0;
//    int timeoffset = ui->txttimeoffset->value();
//    if(ui->GridViewSatRising->rowCount() == 0)
//    {
//        ui->lblnotification->setText("Predict Rising Time on TLE TAB");
//    }
//    else
//    {

//        ui->lblnotification->setText("");
//        for(int i = 0 ;i<=ui->GridViewSatRising->rowCount();i++)
//        {


//            QString TrackingState = ui->GridViewSatRising->item(i,7)->text();

//            if(TrackingState.trimmed() == "1")
//            {
//                QDateTime risingdatetime = QDateTime::fromString(ui->GridViewSatRising->item(i,0)->text(),"yyyy-MM-dd hh:mm:ss");

//                QDateTime now = QDateTime::currentDateTime();
//                now.addSecs(timeoffset);
//                typeofpath =  ui->GridViewSatRising->item(i,8)->text().toInt();

//                if(now.secsTo(risingdatetime) <= (6000) && now.secsTo(risingdatetime)>0 && risingdatetime > now && rotatorIndexgrid != i)
//                {
//                    rotatorIndexgrid = i;
//                    int azimuthgrid = (int)ui->GridViewSatRising->item(i,1)->text().toDouble();

//                    if(typeofpath==1)
//                    {
//                        if(azimuthgrid<90)
//                            azimuthgrid = azimuthgrid+360;
//                    }
//                    else if(typeofpath == 2)
//                    {
//                        if(azimuthgrid<90)
//                            azimuthgrid = azimuthgrid + 360;
//                    }

//                    qDebug()<<azimuthgrid;
//                    GoToSpecificLocation(0,azimuthgrid);

//                }
//                break;
//            }
//            else
//            {
//                QDateTime risingdatetime = QDateTime::fromString(ui->GridViewSatRising->item(i,0)->text(),"yyyy-MM-dd hh:mm:ss");
//                QDateTime now = QDateTime::currentDateTime();
//                if(risingdatetime>now)
//                    return;
//            }
//        }
//    }



//    //read time from system with UTC format
//    QDateTime current = QDateTime::currentDateTimeUtc();
//    current = current.addSecs(timeoffset);

//    VectorXd Angle_dplr=CalcVectorXd(current,ui->txtTLE1->text(),ui->txtTLE2->text());
//    int elevation = int((Angle_dplr(0)/pi)*180);
//    int azimuth =int((Angle_dplr(1)/pi)*180);

//    double doppler = 0;
//    if(ui->rbtTLE->isChecked())
//    {
//        doppler = Angle_dplr(2);
//        qDebug()<<"Doppler:"<<doppler;
//        qDebug()<<"ABS:"<<abs(doppler-RITValue);
//        if(abs(doppler-RITValue)>100.0)
//        {
//            qDebug()<<"Here 3....";
//            SETVALUE( int(doppler-RITValue));
//            //           rotatorOlddoppler = doppler;
//        }
//    }
//    else if(ui->rbtReceiver->isChecked())
//    {
//        doppler = this->_dopplerEntity->getDoppler();

//        if (doppler>-11000 && doppler<11000)
//        {
//            if(abs(doppler-RITValue)>100.0 )
//            {
//                SETVALUE(int(doppler-RITValue));
//            }
//        }
//        else
//        {
//            doppler = 100000;
//            ui->lblnotification->setText("Doppler is not set from receiver!!!");
//        }
//    }

//    ui->txtdoppler->setText(QString::number(doppler));
//    //ui->lblSuggestedAzimuth->setText(QString::number(rotatorOldAzimuth));
//    //ui->lblSuggestedElevation->setText(QString::number(elevation));
//    if(elevation >= 0 )
//    {
//        //move rotator to specified axis

//        int currentAZ = ui->lblazimuth->text().toInt();
//        int currentEL = ui->lblelevation->text().toInt();

//        int eloffset = ui->txtELOffset->text().toInt();
//        int azoffset = ui->txtAzOffset->text().toInt();
//        if(ui->chkoffset->isChecked())
//        {
//            elevation    = elevation+eloffset;
//            //azimuth  = azimuth+azoffset+rotatorAzimuthoffset;
//        }
//        int stepsize = ui->txtStepSize->text().toInt();

//        if(typeofpath==1)
//        {
//            qDebug()<<"type1";
//            if(azimuth<90)
//                azimuth = azimuth+360;
//            else if(azimuth<180 && azimuth>90)
//                return;
//        }
//        else if(typeofpath == 2)
//        {
//            if(azimuth<90)
//                azimuth = azimuth + 360;
//            qDebug()<<"type2";
//        }
//        else if(typeofpath == 3)
//        {
//            qDebug()<<"type3";
//            if(azimuth>180)
//                return;
//        }
//        qDebug()<<"3             ";
//        QString ElevationValue = QString::number(elevation);
//        QString AzimuthValue = QString::number(azimuth);
//labelnumber:
//        if(ElevationValue.length()<3)
//        {
//            ElevationValue = "0"+ElevationValue;
//            goto labelnumber;
//        }
//        if(AzimuthValue.length()<3)
//        {
//            AzimuthValue = "0"+AzimuthValue;
//            goto labelnumber;
//        }

//        if(sbandOldElevation!=elevation || sbandOldAzimuth!=azimuth)
//        {
//            //for step size
//            if(abs(currentAZ-azimuth) > stepsize || abs(currentEL-elevation) > stepsize)
//            {

//                QString command ="W"+AzimuthValue +" " +ElevationValue+"\r\n";
//                SendCommand(command.toLocal8Bit(),true);
//            }
//        }

//    }
//    sbandOldElevation = elevation;
//    sbandOldAzimuth=azimuth;

//    }
//    catch(...)
//    {
//      //
//        qDebug()<<"Exception ";
//    }
}
void RotatorWidget::GoToSpecificLocation(int elevation,int azimuth)
{
    QString ElevationValue = QString::number(elevation);
    QString AzimuthValue = QString::number(azimuth);
labelnumber:
    if(ElevationValue.length()<3)
    {
        ElevationValue = "0"+ElevationValue;
        goto labelnumber;
    }
    if(AzimuthValue.length()<3)
    {
        AzimuthValue = "0"+AzimuthValue;
        goto labelnumber;
    }
    QString command ="W"+AzimuthValue +" " +ElevationValue+"\r\n";
    SendCommand(command.toLocal8Bit(),true);
}

void RotatorWidget::on_btnStopRotator_clicked()
{
    QString command = "S\r\n";
    SendCommand(command.toLocal8Bit(),true);
}

void RotatorWidget::on_btnright_clicked()
{
    QString command = "R\r\n";
    SendCommand(command.toLocal8Bit(),true);
}

void RotatorWidget::on_btnleft_clicked()
{
    QString command = "L\r\n";
    SendCommand(command.toLocal8Bit(),true);
}

void RotatorWidget::on_btndown_clicked()
{
    QString command = "D\r\n";
    SendCommand(command.toLocal8Bit(),true);
}

void RotatorWidget::on_btnup_clicked()
{
    QString command = "U\r\n";
    SendCommand(command.toLocal8Bit(),true);

}

void RotatorWidget::on_btnGoToAZEL_clicked()
{
    on_btnstop_clicked();
    int currentEL = ui->lblelevation->text().toInt();
    int currentAZ = ui->lblazimuth->text().toInt();


    QString el =QString::number( ui->txtEL->text().toInt());
    QString az =QString::number( ui->txtAZ->text().toInt());
    rotatorElevation = el.toInt();
    rotatorAzimuth  = az.toInt();
    if(ui->chkoffset->isChecked())
    {
        rotatorElevation = rotatorElevation + ui->txtELOffset->text().toInt();
        rotatorAzimuth = rotatorAzimuth + ui->txtAzOffset->text().toInt();
    }
    qDebug()<<abs(currentEL-rotatorElevation);
    qDebug()<<abs(currentAZ-rotatorAzimuth);
    qDebug()<<ui->txtStepSize->text().toInt();
    if(abs(currentEL-rotatorElevation) > ui->txtStepSize->text().toInt() || abs(currentAZ-rotatorAzimuth) > ui->txtStepSize->text().toInt())
    {
        QString ElevationValue = QString::number(rotatorElevation);
        QString AzimuthValue = QString::number(rotatorAzimuth);
lableformat:
        if(ElevationValue.length()<3)
        {
            ElevationValue = "0"+ElevationValue;
            goto lableformat;
        }
        if(AzimuthValue.length()<3)
        {
            AzimuthValue = "0"+AzimuthValue;
            goto lableformat;
        }
        QString command ="W"+AzimuthValue +" " +ElevationValue+"\r\n";
        SendCommand(command.toLocal8Bit(),true);
    }
}

void RotatorWidget::on_btnSendCommand_clicked()
{
    QString command = ui->txtcustomCommand->text()+"\r\n";
    SendCommand(command,true);
}

void RotatorWidget::on_BtnPark_clicked()
{
    on_btnstop_clicked();
   GoToSpecificLocation(0,0);
}

void RotatorWidget::on_btnstop_clicked()
{
    rotatorTimerTLE->stop();
    rotatorTimerTLE->~QTimer();
    rotatorOlddoppler = 0;    
    RITValue = 0;
}

void RotatorWidget::on_btnConvertTLETOLLA_clicked()
{
    Tleconversion TLE;
    string TLE1_str=ui->txtTLE1->text().toStdString();
    string TLE2_str=ui->txtTLE2->text().toStdString();

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
    LLA_GS(0) = ui->txtLatitude->text().toDouble();
    LLA_GS(1) = ui->txtLongitude->text().toDouble();
    LLA_GS(2) = ui->txtaltitude->text().toDouble();

    double Lambda=(ui->Lambda_TLE_lineEdit->text().toDouble())/1e3;

    VectorXd RV_ECI=TLE.tle2rveci(longstr1,longstr2,Jd_now,false);
    VectorXd R_ECI=RV_ECI.block(0,0,3,1);
    MatrixXd MX_ECI2ECEF=E2.dcmeci2ecefExact(Jd_now);
    MatrixXd MX_ECI2ECEF2=MX_ECI2ECEF.block(0,0,3,3);
    VectorXd R_ECEF=MX_ECI2ECEF2*R_ECI;
    VectorXd LLA_TLE=E2.ecef2lla(R_ECEF*1e3);

    ui->txtLatitudetle->clear();
    ui->txtLatitudetle->setText(QString::number(LLA_TLE(0),'g',8));
    ui->txtLongitudetle->clear();
    ui->txtLongitudetle->setText(QString::number(LLA_TLE(1),'g',8));
    ui->txtaltitudetle->clear();
    ui->txtaltitudetle->setText(QString::number(LLA_TLE(2),'g',8));

}

QDateTime rotatorSatupDateTime;
QDateTime rotatorSatDownDateTime;
//bool isDTR = true;
void RotatorWidget::SETVALUE(int ritvalue)
{
    if(ritvalue<0 && rotatorSerial->isOpen())
    {
        QString RIT="";
        RIT =QString::number(abs(ritvalue));
        for(int i = RIT.length() ;i<5;i++)
            RIT = "0"+RIT;
        QString command = "RD"+RIT+";";
        qDebug()<<"Write Command 3:"<<command;
        rotatorSerial->write(command.toLocal8Bit());
        command = "OI;";
        rotatorSerial->write(command.toLocal8Bit());

    }
    else if(rotatorSerial->isOpen())
    {
        QString RIT="";
        RIT =QString::number(abs(ritvalue));
        for(int i = RIT.length() ;i<5;i++)
            RIT = "0"+RIT;
        QString command = "RU"+RIT+";";
        qDebug()<<"Write Command 4:"<<command;
        rotatorSerial->write(command.toLocal8Bit());
        command = "OI;";
        rotatorSerial->write(command.toLocal8Bit());

    }
}

void RotatorWidget::on_btnpredict_clicked()
{
    run = false;
    rotatorDateTimeTimer = new QTimer(this);
    connect(rotatorDateTimeTimer, SIGNAL(timeout()), this, SLOT(RefreshTime()));
    rotatorDateTimeTimer->start(10000);
    //Path= new QList();
    //Axis Path[seconds];
    //rotatorIndexgrid = -1;
    //array for Plot
    QVector <double> Elevations(0);
    QVector <double> Dopplers(0);
    QVector <double> Azimuths(0);
    QVector <double> RisingAzimuths(0);
    QVector <QDateTime> Times(0);
    QVector <double> Times_Vec;

    int seconds = ui->txthours->value()*3600;

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
    double width = _monitorForm->getSceneWidth();
    double height = _monitorForm->getSceneHeight();
    for (int i = 0 ;i<=seconds;i++)
    {
        current = current.addSecs(1);
        VectorXd Angle_dplr=CalcVectorXd(current.toUTC(),ui->txtTLE1->text(),ui->txtTLE2->text());

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

            VectorXd Angle_dplr=CalcVectorXd(current,ui->txtTLE1->text(),ui->txtTLE2->text());

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

        ui->progressBar->setValue(int(double(double(i)/double(seconds))*100));

    }

    for(int i=0;i<Times.count();i++)
    {
        Times_Vec.append(i/60.0/60.0);
    }

    ui->plot_predict->clearGraphs();
    ui->plot_predict->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    ui->plot_predict->legend->setFont(legendFont);
    ui->plot_predict->legend->setBrush(QBrush(QColor(255,255,255,230)));
    ui->plot_predict->xAxis->setLabel("Time [hour]");

    ui->plot_predict->yAxis->setLabelFont(legendFont);
    ui->plot_predict->xAxis->setLabelFont(legendFont);

    if(ui->EL_radioButton->isChecked())
    {
        ui->plot_predict->addGraph();
        ui->plot_predict->graph(0)->setPen(QPen(Qt::red));
        ui->plot_predict->graph(0)->setName("EL");
        ui->plot_predict->graph(0)->setData(Times_Vec,Elevations);
        ui->plot_predict->yAxis->setLabel("El Angle [degree]");
    }
    else if (ui->Doppler_radioButton->isChecked())
    {
        ui->plot_predict->addGraph();
        ui->plot_predict->graph(0)->setPen(QPen(Qt::blue));
        ui->plot_predict->graph(0)->setName("Doppler");
        ui->plot_predict->graph(0)->setData(Times_Vec,Dopplers);
        ui->plot_predict->yAxis->setLabel("Doppler [kHz]");
    }
    else if(ui->EL_Doppler_radioButton->isChecked())
    {
        ui->plot_predict->addGraph();
        ui->plot_predict->graph(0)->setPen(QPen(Qt::red));
        ui->plot_predict->graph(0)->setName("EL");
        ui->plot_predict->graph(0)->setData(Times_Vec,Elevations);

        ui->plot_predict->addGraph();
        ui->plot_predict->graph(1)->setPen(QPen(Qt::blue));
        ui->plot_predict->graph(1)->setName("Doppler");
        ui->plot_predict->graph(1)->setData(Times_Vec,Dopplers);

        ui->plot_predict->yAxis->setLabel("El Angle [degree], Doppler [kHz]");
    }
    else if(ui->EL_AZ_radioButton->isChecked())
    {
        ui->plot_predict->addGraph();
        ui->plot_predict->graph(0)->setPen(QPen(Qt::red));
        ui->plot_predict->graph(0)->setName("EL");
        ui->plot_predict->graph(0)->setData(Times_Vec,Elevations);

        ui->plot_predict->addGraph();
        ui->plot_predict->graph(1)->setPen(QPen(Qt::blue));
        ui->plot_predict->graph(1)->setName("AZ");
        ui->plot_predict->graph(1)->setData(Times_Vec,Azimuths);

        ui->plot_predict->yAxis->setLabel("El Angle [degree], AZ Angle [degree]");
    }

    ui->plot_predict->rescaleAxes();
    ui->plot_predict->replot();
    ui->plot_predict->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    //MonitorForm.setSatellitePosition(Path,Path.length());
    //MonitorForm.startAnimation();
    //_monitorForm->setSatellitePosition(Path);
    //_monitorForm->startAnimation();


}
//the current must be in utc format
VectorXd RotatorWidget::CalcVectorXd(QDateTime current,QString Line1,QString line2)
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

    double PI=3.14159265;
    // Convert TLE to Local Angles
    VectorXd LLA_GS=VectorXd::Zero(3);
    LLA_GS(0) = ui->txtLatitude->text().toDouble();
    LLA_GS(1) = ui->txtLongitude->text().toDouble();
    LLA_GS(2) = ui->txtaltitude->text().toDouble();

    double Lambda=(ui->Lambda_TLE_lineEdit->text().toDouble())/1e3;

    VectorXd Angle_dplr=TLE.tle2angle(longstr1,longstr2,Jd_now,Lambda,LLA_GS,false);
    return Angle_dplr;
}
void RotatorWidget::writeData(const QByteArray &data)
{
    SendCommand(QString(data),false);
}
void RotatorWidget::SendCommand(QString command,bool show)
{
    qDebug()<<command;
    if(ui->rbtNetwork->isChecked())
    {
        socket->write(command.toLocal8Bit());
    }
    else
    {
        rotatorSerial->write(command.toLocal8Bit());
    }
}

void RotatorWidget::on_pushButton_clicked()
{


    //show LLA of TLE on Map
    QFile file(qApp->applicationDirPath() + "/map.html");
    if(!file.exists())
        qDebug()<<"The file is not exist";
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Cannot open the file";
        return;
    }
    qDebug()<<"openfile";
    QTextStream htmlstream(&file);
    QString htmlfile=htmlstream.readAll();

    QString line1= "var myLatlng = new google.maps.LatLng("+ui->txtLatitudetle->text()+","+ui->txtLongitudetle->text()+")";
    QString line2 = "center: new google.maps.LatLng("+ui->txtLatitudetle->text()+","+ui->txtLongitudetle->text()+"),";

    htmlfile.replace("###",line1);
    htmlfile.replace("$$$",line2);
    qDebug()<<htmlfile;
    file.close();
    QFile filetle(qApp->applicationDirPath() + "/TLELocation.html");
    if (!filetle.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream txtstream(&filetle);
    txtstream<<htmlfile;
    filetle.close();

    ui->LLAwebView->page()->mainFrame()->evaluateJavaScript( "map.panTo(myLatlng);" );

    ui->LLAwebView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    QString fileName = qApp->applicationDirPath() + "/TLELocation.html";
    QUrl url = QUrl::fromLocalFile( fileName );
    ui->LLAwebView->load( url );
}

void RotatorWidget::on_btnShowOnMap_clicked()
{
    //show LLA of TLE on Map
    QFile file(qApp->applicationDirPath() + "/map.html");
    if(!file.exists())
        qDebug()<<"The file is not exist";
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Cannot open the file";
        return;
    }
    qDebug()<<"openfile";
    QTextStream htmlstream(&file);
    QString htmlfile=htmlstream.readAll();

    QString line1= "var myLatlng = new google.maps.LatLng("+ui->txtLatitude->text()+","+ui->txtLongitude->text()+")";
    QString line2 = "center: new google.maps.LatLng("+ui->txtLatitude->text()+","+ui->txtLongitude->text()+"),";

    htmlfile.replace("###",line1);
    htmlfile.replace("$$$",line2);
    qDebug()<<htmlfile;
    file.close();
    QFile filetle(qApp->applicationDirPath() + "/TLELocation.html");
    if (!filetle.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream txtstream(&filetle);
    txtstream<<htmlfile ;
    filetle.close();

    ui->LLAwebView->page()->mainFrame()->evaluateJavaScript( "map.panTo(myLatlng);" );

    ui->LLAwebView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    QString fileName = qApp->applicationDirPath() + "/TLELocation.html";
    QUrl url = QUrl::fromLocalFile( fileName );
    ui->LLAwebView->load( url );
}

void RotatorWidget::on_btnupgrade_clicked()
{
    socket2->write("$$Upgrade@@");
}

void RotatorWidget::on_btnclearLCD_clicked()
{
    console->clear();
}



bool readyToSend = false; //Hojjat
void RotatorWidget::on_btnkenwoodconnect_clicked()
{
    if(rotatorSerial->isOpen())
    {
        if(!readyToSend)
        {
            connect(rotatorSerial, SIGNAL(readyRead()), this, SLOT(readDataFromSerial()));

            //ui->lblkenwoodconnection->setText("ConnectOK");
            QString command = "RT1;";
            rotatorSerial->write(command.toLocal8Bit());
            command = "RD40000;";
            rotatorSerial->write(command.toLocal8Bit());
            command = "RU20000;";
            rotatorSerial->write(command.toLocal8Bit());
            readyToSend = true;
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "Kenwood serial port is not open.");
    }
//    return;
//    rotatorSerial = new QSerialPort(this);
//    rotatorSerial->setPortName(ui->cmbkenwooddevices->currentText());
//    int baudrate=ui->txtkenwoodbaudrate->text().toInt();
//    if (rotatorSerial->open(QIODevice::ReadWrite)) {
//        if (rotatorSerial->setBaudRate(baudrate,QSerialPort::AllDirections)
//                && rotatorSerial->setDataBits(QSerialPort::Data8)
//                && rotatorSerial->setParity(QSerialPort::NoParity)
//                && rotatorSerial->setStopBits( QSerialPort::OneStop)
//                && rotatorSerial->setFlowControl(QSerialPort::NoFlowControl))
//        {


//        }
//    }
}

void RotatorWidget::on_btnDisconnectSerial_2_clicked()
{
    //rotatorSerial->close();
    disconnect(rotatorSerial, SIGNAL(readyRead()), this, SLOT(readDataFromSerial()));
    //ui->lblkenwoodconnection->setText("");
    readyToSend = false;
}

void RotatorWidget::on_btnsetfreq_clicked()
{
    if( rotatorSerial->isOpen())
    {
        int douppler =0;
        douppler= (int)((ui->txtdoppler->text().toDouble())/1000);
        qDebug()<<douppler;
        if(douppler<0)
        {
            QString RIT="";
            RIT =QString::number(abs(douppler));
            for(int i = RIT.length() ;i<5;i++)
                RIT = "0"+RIT;
            QString command = "RD"+RIT+";";
            qDebug()<<command;
            rotatorSerial->write(command.toLocal8Bit());
        }
        else
        {
            QString RIT="";
            RIT =QString::number(abs(douppler));
            for(int i = RIT.length() ;i<5;i++)
                RIT = "0"+RIT;
            QString command = "RU"+RIT+";";
            qDebug()<<command;
            rotatorSerial->write(command.toLocal8Bit());
        }
    }
}

void RotatorWidget::on_pushButton_4_clicked()
{
    if( rotatorSerial->isOpen())
    {
        QString command = "RU00100;";
        rotatorSerial->write(command.toLocal8Bit());
    }
}

void RotatorWidget::on_pushButton_5_clicked()
{
    if( rotatorSerial->isOpen())
    {
        QString command = "FC00436650000;";
        rotatorSerial->write(command.toLocal8Bit());
    }
}

void RotatorWidget::on_btnreadfreq_clicked()
{
    QString command = "FA;";
    qDebug()<<command;
    rotatorSerial->write(command.toLocal8Bit());
}
int countoftle=0;
void RotatorWidget::on_btnperedict_clicked()
{
    countoftle = 0;
     ui->gridperdicSats->setRowCount(0);
    QString Line1="";
    QString Line2="";
    QString SatName="";
    QString fileName =  ui->txttlefileaddress->text();
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    //if find tle read two line after that
    bool findtle;
    //if find lla read three ling after that
    bool findlla;

    countoftle = ui->cmbsats->count();

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
void RotatorWidget::PerdictSat(QString line1, QString line2, QString satname)
{
    //rotatorIndexgrid = -1;

    int seconds = ui->txthours->value()*3600;


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
//            int indx=1;
//            for(int ii=1;ii<RisingAzimuths.count()-1;ii++)
//            {
//                if(RisingAzimuths[ii]!=RisingAzimuths[0])
//                {
//                    indx=ii;
//                    break;
//                }
//            }
//            if( RisingAzimuths[0]>=180 )
//            {

//                if( RisingAzimuths[indx]>RisingAzimuths[0] )
//                {
//                    type=1;
//                }
//                //adad haye kamtar az 90 ra ba 360 jam+ kon va ghesmati ke bishtar az 90 ast va kamtar az 180
//                // ra track nakon, dar in sourat nimeye bishtar niz track shode

//            }
//            else if( RisingAzimuths[0]<180 && RisingAzimuths[0]>=90 )
//            {
//                if( RisingAzimuths[indx]<RisingAzimuths[0] )
//                    type=3;
//                // تنها لازم است تا نیمه اول ردگیری شود در این صورت نیمه بیشتر ردیابی شده است
//                // یعنی تا وقتی که یک برش بزرگ مشاهده شد ردگیری کن

//            }
//            else if( RisingAzimuths[0]<90 )
//            {
//                if( RisingAzimuths[indx]<RisingAzimuths[0] )
//                    type=2;
//                // عددهای کمتر از ۹۰ را با ۳۶۰ جمع کن و عددهای بیشتر از ۹۰ را دست نزن
//            }
//            else
//            {
//                type=0;
//            }
            // دو حالت بد و استثنایی ممکن است مشکل ایجاد کند
            // نخست اینکه آزیموس اولی مثلا ۳۵۹ باشد و دومی ییهو صفر شود
            // ویا آزیموس اولی ۰ باشد و دومی ییهو ۳۵۹ شود
            //که بهتر است اینها نیز شناسایی شوند


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

//            RisingAzimuths.clear();
            qDebug()<<"End OF Adding in Grid::"<<i;
        }
        //reset maxEL
        if(elevation<0 && !satup)
        {
            type=0;
            maxelval=elevation;
        }
//        if(elevation>=0)
//        {
//            RisingAzimuths.append(azimuth);
//        }
//        // ui->progresssat->setValue(int(double(double(i)/double(seconds))*100));
    }


}
bool flag = true;
void RotatorWidget::on_btnDTR_clicked()
{
    rotatorSerial->setDataTerminalReady(flag);
    flag= !flag;
}

void RotatorWidget::on_checkBox_clicked()
{

}

void RotatorWidget::on_dopplercheckbox_toggled(bool checked)
{
    if(ui->dopplercheckbox->isChecked())
    {
        ui->DopplerGroupBox->setEnabled(true);
        ui->rbtTLE->setEnabled(true);
        ui->rbtReceiver->setEnabled(true);
        ui->txtdoppler->setEnabled(true);
        if(rotatorSerial->isOpen())
        {
            if(!readyToSend)
            {
                connect(rotatorSerial, SIGNAL(readyRead()), this, SLOT(readDataFromSerial()));

                //ui->lblkenwoodconnection->setText("ConnectOK");
                QString command = "RT1;";
                rotatorSerial->write(command.toLocal8Bit());
                command = "RD40000;";
                rotatorSerial->write(command.toLocal8Bit());
                command = "RU20000;";
                rotatorSerial->write(command.toLocal8Bit());
                readyToSend = true;
            }
        }
        else
        {
            QMessageBox::warning(this, "Error", "Kenwood serial port is not open.");
        }
    }
    else
    {
        ui->DopplerGroupBox->setDisabled(true);
        ui->rbtTLE->setDisabled(true);
        ui->rbtReceiver->setDisabled(true);
        ui->txtdoppler->setDisabled(true);
        //
        //
        //
        disconnect(rotatorSerial, SIGNAL(readyRead()), this, SLOT(readDataFromSerial()));
        //ui->lblkenwoodconnection->setText("");
        readyToSend = false;
    }
}

void RotatorWidget::on_dopplercheckbox_clicked()
{

}

void RotatorWidget::on_cmbsats_currentIndexChanged(int index)
{

}

void RotatorWidget::on_rbtNetwork_toggled(bool checked)
{

}

void RotatorWidget::on_chkoffset_toggled(bool checked)
{

}

void RotatorWidget::on_chkoffset_stateChanged(int arg1)
{

}
