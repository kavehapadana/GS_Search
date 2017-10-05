#ifndef ROTATORWIDGET_H
#define ROTATORWIDGET_H

#include <QScrollArea>
#include <QtGui>
#include <QtCore>
#include <qframe.h>
#include <qpalette.h>
//#include <speedo_meter.h>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QtWebKit/QtWebKit>

#include "transformmatrix.h"
#include "matrix_algebra.h"
#include "iterative_estimation.h"
#include <Eigen_Library/Eigen/Eigen>
#include <fstream>
#include <SGP4/sgp4ext.h>
#include <SGP4/sgp4io.h>
#include <SGP4/sgp4unit.h>
#include "tleconversion.h"
#include "console.h"
#include "dopplerentity.h"
#include <QtSerialPort/QSerialPort>
#include "functions.h"
#include "monitorform.h"
#include "Kenwood/kenwoodwidget.h"
extern double RITValue;
namespace Ui {
class RotatorWidget;
}

class RotatorWidget : public QScrollArea
{
    Q_OBJECT
    
public:
    explicit RotatorWidget(DopplerEntity *dopplerEntity, QSerialPort *kenwoodSerial,MonitorForm *monitorForm,QWidget *parent = 0);
    ~RotatorWidget();    
private slots:

    void readDataFromSerial();

    void RefreshAxis();

    void readyReadFromNetwork();

    void GetHelloAnswer();

    void ConvertTLETOAZEL();

    void on_btnloadtlefromfile_clicked();

    void on_cmbsats_currentIndexChanged(const QString &arg1);

    void on_rbtNetwork_clicked();

    void on_rbtSerial_clicked();

    void on_btnDiscoverNetwork_clicked();

    void on_btnconnectNetwork_clicked();

    void on_btndisconnectnetwork_clicked();

    void on_btnturnon_clicked();

    void on_btnturnoff_clicked();

    void on_btnvoltage_clicked();

    void on_btnConnectSerial_clicked();

    void on_btnDisconnectSerial_clicked();

    void on_chkoffset_clicked();

    void on_btnstart_clicked();

    void on_btnStopRotator_clicked();

    void on_btnright_clicked();

    void on_btnleft_clicked();

    void on_btndown_clicked();

    void on_btnup_clicked();

    void on_btnGoToAZEL_clicked();

    void on_btnSendCommand_clicked();

    void on_BtnPark_clicked();

    void on_btnstop_clicked();

    void on_btnConvertTLETOLLA_clicked();

    void on_btnpredict_clicked();

    void RefreshTime();

    VectorXd CalcVectorXd(QDateTime current,QString Line1,QString line2);

    void readyReadFromControl();

    void SendCommand(QString command,bool show);

    void on_pushButton_clicked();

    void on_btnShowOnMap_clicked();

    void on_btnupgrade_clicked();

    void on_btnclearLCD_clicked();

    void writeData(const QByteArray &data);

    void GoToSpecificLocation(int elevation,int azimuth);

    void msleep(unsigned long msecs);

    void SendEnter();

    void on_btnkenwoodconnect_clicked();

    void on_btnDisconnectSerial_2_clicked();

    void on_btnsetfreq_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_btnreadfreq_clicked();

    void SETVALUE(int ritvalue);

    void on_btnperedict_clicked();

    void PerdictSat(QString line1,QString line2,QString satname);

    void on_btnDTR_clicked();

    void on_checkBox_clicked();

    void on_dopplercheckbox_toggled(bool checked);

    void on_dopplercheckbox_clicked();

    void on_rbtNetwork_toggled(bool checked);

    void on_cmbsats_currentIndexChanged(int index);

    void on_chkoffset_toggled(bool checked);

    void on_chkoffset_stateChanged(int arg1);

private:
    Ui::RotatorWidget *ui;
    QTcpSocket *socket;
    QTcpSocket *socket2;
    QUdpSocket *discoversocket;
    //Console
    Console *console;
    DopplerEntity *_dopplerEntity;
    MonitorForm *_monitorForm;
    QStringList rotatorListOfSatsName ;
    QStringList rotatorListofSatsTle ;
    bool run;
};

#endif // ROTATORWIDGET_H
