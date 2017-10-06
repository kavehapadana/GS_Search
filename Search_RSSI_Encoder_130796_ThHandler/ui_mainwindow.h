/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Oct 6 21:30:53 2017
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QTimeEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "hled.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *Tab;
    QWidget *tab_COM;
    QPushButton *btnTest;
    QPushButton *btnForceExit;
    QLabel *lbl_AnimationSerial;
    QGroupBox *gbMotor;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vlMotor;
    QPushButton *btnForwardM;
    QPushButton *btnStopMotor;
    QPushButton *btnReverseM;
    QPushButton *btnEmergencyStopMotor;
    QPushButton *btnParkSerachAntena;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_12;
    QLineEdit *txtFreq;
    QLineEdit *txtDeAcc;
    QPushButton *btnSetDeAcc;
    QLineEdit *txtAcc;
    QLabel *label_79;
    QLabel *label_77;
    QLabel *label_78;
    QPushButton *btnSetAcc;
    QPushButton *btnSetFreq;
    QGroupBox *gbAutoMove;
    QCheckBox *chkAuto;
    QLabel *errorNo_3;
    QLabel *errorNo_2;
    QLabel *errorNo_4;
    QLabel *errorNo_5;
    QLineEdit *txtCenterOfSpan;
    QLineEdit *txtSpan;
    QTextEdit *txtSpan__1;
    QPushButton *btnSetAutoSpan;
    QScrollBar *csCenterofSpan;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_11;
    QLabel *lbl_SerialCom;
    QComboBox *cmbSerialComSearch;
    QPushButton *btnSerialOpenClose;
    QLabel *lbl_SerialBaud;
    QComboBox *cmbSerialBaud;
    QLabel *lbl_serialStatus;
    QLabel *lbl_PC_Password;
    QLineEdit *lePassWord;
    QWidget *horizontalLayoutWidget_RSSI_SUM_Delta;
    QHBoxLayout *_2;
    QCustomPlot *plot_RSSI_SUM_Delta;
    QTableWidget *tableWidget;
    QPushButton *btnResetMaxTable;
    QLabel *lbl_MovingFlage;
    QLabel *lbl_finalDegreefinal;
    QGroupBox *gb_SerialPlotRadios;
    QRadioButton *rdbRealTime;
    QRadioButton *rdbEncoderPlot;
    QGroupBox *gb_SerialPlotRadios_plarLinear;
    QRadioButton *rdbPolarPlot;
    QRadioButton *rdbLinearPlot;
    QGroupBox *groupBox_2;
    QCheckBox *chkPlotSUM;
    QCheckBox *chkPlotDelta;
    QCheckBox *chkPlotSUM_Anlz;
    QCheckBox *chkPlotDeltaSLC_Anlz;
    QGroupBox *gbxAnlzType;
    QRadioButton *rdbAnlzAve;
    QRadioButton *rdbAveFIR;
    QWidget *tab_Plot;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QCustomPlot *plot_Dopp;
    QLabel *lblfinalDegree;
    QPushButton *btnClearDiagrams;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_17;
    QLabel *lbl_MoveStatus;
    QWidget *tab_Watch_Config;
    QWidget *horizontalLayoutWidget_SAT;
    QHBoxLayout *horizontalLayout_Plot_SAT;
    QCustomPlot *plot_RSSI_Delta;
    HLed *ledRotaryMCU_State;
    QLabel *slbl_2;
    QLabel *slbl_3;
    HLed *ledFixMCU_State;
    QPushButton *btnHighSum;
    QPushButton *btnLowSum;
    QPushButton *btnHighDelta;
    QPushButton *btnLowDelta;
    QLabel *slbl_4;
    QLabel *slbl_5;
    HLed *ledRcvDataSum;
    HLed *ledRcvDataDelta;
    QGroupBox *gbDelta_SLC;
    HLed *ledSelectDeltafb;
    QWidget *layoutWidget_1;
    QVBoxLayout *verticalLayout;
    QRadioButton *rdbSelectDelta;
    QRadioButton *rdbSelectSLC;
    HLed *ledSelectSLCfb;
    QLabel *lblAxb;
    QLineEdit *leOffsetAnalyzerSum;
    QLabel *lblAxb_3;
    QPushButton *pushButton;
    QLabel *lblBAnalyzor;
    QLineEdit *leOffsetAnalyzerDelta;
    QLabel *lblAxb_2;
    QLineEdit *leCoefAnlyzorSum;
    QLabel *lblleOffsetAnalyzer;
    QLineEdit *leCoefAnlyzorDelta;
    QLabel *lblAxb_4;
    QLabel *slbl;
    HLed *ledDetect1;
    HLed *ledSUM_SerialPin;
    HLed *ledDeltaSLC_SerialPin;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblAxb_5;
    QSpacerItem *horizontalSpacer_19;
    QLineEdit *leFreqRotMCU;
    QSpacerItem *horizontalSpacer_20;
    QPushButton *btnsetFrequencyRotMCU;
    QWidget *tab_Analyzer;
    QWidget *horizontalLayoutWidget_a_2;
    QHBoxLayout *horizontalLayout_Plot_a;
    QCustomPlot *plot_Analyzer_RSSI_SUM;
    QGroupBox *gb_AnalyzerPlotRadios;
    QRadioButton *rb_RealTime_a;
    QRadioButton *rb_adc_EncoderPlot_a;
    QWidget *horizontalLayoutWidget_a;
    QHBoxLayout *horizontalLayout_a;
    QCustomPlot *plot_Analyzer_Dopp;
    QTableWidget *tableWidget_a;
    QPushButton *btnResetMaxTable_a;
    QPushButton *btnOpenFile;
    QLabel *lbl_load;
    QPushButton *btnAnalyze;
    QLabel *label;
    QLineEdit *txtDataC_Size;
    QPushButton *btnSimplePLot;
    QPushButton *btnMaxPlotAnaGO;
    QPushButton *btnMaxPlotAnaBack;
    QLabel *lbl_load_2;
    QProgressBar *pbPlotPicks;
    QLabel *lblCntMax;
    QLabel *lblPicksSize;
    QPushButton *btn_test2;
    QWidget *tab_TLE;
    QHBoxLayout *horizontalLayout_13;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_4;
    QHBoxLayout *horizontalLayout_16;
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_23;
    QHBoxLayout *horizontalLayout_19;
    QVBoxLayout *verticalLayout_29;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_32;
    QGridLayout *gridLayout_4;
    QLabel *label_44;
    QLineEdit *txttlefileaddress_2;
    QPushButton *btnloadtlefromfile_2;
    QHBoxLayout *horizontalLayout_23;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_46;
    QComboBox *cmbsats_2;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_24;
    QGridLayout *gridLayout_5;
    QLabel *label_50;
    QLineEdit *txtTLE1_2;
    QLabel *label_51;
    QLineEdit *txtTLE2_2;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_37;
    QFrame *line_5;
    QVBoxLayout *verticalLayout_33;
    QGridLayout *gridLayout_18;
    QLabel *label_52;
    QLabel *label_54;
    QLineEdit *txtaltitude_2;
    QLineEdit *txtLatitude_2;
    QLabel *label_53;
    QLineEdit *txtLongitude_2;
    QComboBox *comboBoxGPS;
    QHBoxLayout *horizontalLayout_38;
    QPushButton *btnShowOnMap_2;
    QSpacerItem *horizontalSpacer_16;
    QVBoxLayout *verticalLayout_34;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_35;
    QLineEdit *Lambda_TLE_lineEdit_2;
    QSpacerItem *verticalSpacer_12;
    QVBoxLayout *verticalLayout_36;
    QGridLayout *gridLayout_19;
    QLineEdit *txtLongitudetle_2;
    QLabel *label_58;
    QLabel *label_56;
    QLineEdit *txtLatitudetle_2;
    QLabel *label_57;
    QLineEdit *txtaltitudetle_2;
    QPushButton *btnConvertTLETOLLA_2;
    QHBoxLayout *horizontalLayout_39;
    QSpacerItem *horizontalSpacer_18;
    QPushButton *pushButton_6;
    QFrame *line_6;
    QHBoxLayout *horizontalLayout_40;
    QCustomPlot *plot_predict_2;
    QVBoxLayout *verticalLayout_37;
    QRadioButton *EL_radioButton_2;
    QRadioButton *Doppler_radioButton_2;
    QRadioButton *EL_AZ_radioButton_2;
    QRadioButton *EL_Doppler_radioButton_2;
    QSpacerItem *verticalSpacer_14;
    QHBoxLayout *horizontalLayout_45;
    QGroupBox *groupBox_10;
    QHBoxLayout *horizontalLayout_48;
    QVBoxLayout *verticalLayout_42;
    QGridLayout *gridLayout_26;
    QLabel *label_67;
    QTimeEdit *cmblocaldatetime_3;
    QGridLayout *gridLayout_27;
    QTimeEdit *cmbutctime_3;
    QLabel *label_68;
    QGridLayout *gridLayout_28;
    QVBoxLayout *verticalLayout_43;
    QPushButton *btnpredict_3;
    QCheckBox *chkSavePredict2File;
    QSpacerItem *verticalSpacer_16;
    QHBoxLayout *horizontalLayout_49;
    QSpinBox *txthours_3;
    QLabel *label_69;
    QProgressBar *progressBar_3;
    QSpacerItem *verticalSpacer_15;
    QTableWidget *GridViewSatRising;
    QWidget *tab_5;
    QHBoxLayout *horizontalLayout_18;
    QHBoxLayout *horizontalLayout_17;
    QVBoxLayout *verticalLayout_16;
    QPushButton *btnperedict;
    QProgressBar *progresssat;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_21;
    QTableWidget *gridperdicSats;
    QWidget *tab_Settings;
    QLineEdit *lePassWord_Settings;
    QLabel *lbl_PC_Password_2;
    QPushButton *pushButton_2;
    QWidget *layoutWidget_5;
    QVBoxLayout *verticalLayout_2;
    QWidget *layoutWidget_6;
    QVBoxLayout *verticalLayout_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1086, 745);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Tab = new QTabWidget(centralWidget);
        Tab->setObjectName(QString::fromUtf8("Tab"));
        Tab->setGeometry(QRect(0, 0, 1071, 671));
        tab_COM = new QWidget();
        tab_COM->setObjectName(QString::fromUtf8("tab_COM"));
        btnTest = new QPushButton(tab_COM);
        btnTest->setObjectName(QString::fromUtf8("btnTest"));
        btnTest->setGeometry(QRect(240, 180, 98, 27));
        btnForceExit = new QPushButton(tab_COM);
        btnForceExit->setObjectName(QString::fromUtf8("btnForceExit"));
        btnForceExit->setGeometry(QRect(240, 210, 98, 27));
        lbl_AnimationSerial = new QLabel(tab_COM);
        lbl_AnimationSerial->setObjectName(QString::fromUtf8("lbl_AnimationSerial"));
        lbl_AnimationSerial->setGeometry(QRect(230, 140, 66, 17));
        gbMotor = new QGroupBox(tab_COM);
        gbMotor->setObjectName(QString::fromUtf8("gbMotor"));
        gbMotor->setGeometry(QRect(10, 230, 401, 401));
        verticalLayoutWidget = new QWidget(gbMotor);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 30, 87, 95));
        vlMotor = new QVBoxLayout(verticalLayoutWidget);
        vlMotor->setSpacing(6);
        vlMotor->setContentsMargins(11, 11, 11, 11);
        vlMotor->setObjectName(QString::fromUtf8("vlMotor"));
        vlMotor->setContentsMargins(0, 0, 0, 0);
        btnForwardM = new QPushButton(verticalLayoutWidget);
        btnForwardM->setObjectName(QString::fromUtf8("btnForwardM"));

        vlMotor->addWidget(btnForwardM);

        btnStopMotor = new QPushButton(verticalLayoutWidget);
        btnStopMotor->setObjectName(QString::fromUtf8("btnStopMotor"));

        vlMotor->addWidget(btnStopMotor);

        btnReverseM = new QPushButton(verticalLayoutWidget);
        btnReverseM->setObjectName(QString::fromUtf8("btnReverseM"));

        vlMotor->addWidget(btnReverseM);

        btnEmergencyStopMotor = new QPushButton(gbMotor);
        btnEmergencyStopMotor->setObjectName(QString::fromUtf8("btnEmergencyStopMotor"));
        btnEmergencyStopMotor->setGeometry(QRect(130, 80, 121, 60));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(200);
        sizePolicy.setVerticalStretch(200);
        sizePolicy.setHeightForWidth(btnEmergencyStopMotor->sizePolicy().hasHeightForWidth());
        btnEmergencyStopMotor->setSizePolicy(sizePolicy);
        btnEmergencyStopMotor->setMinimumSize(QSize(0, 60));
        btnEmergencyStopMotor->setIconSize(QSize(50, 50));
        btnEmergencyStopMotor->setAutoDefault(false);
        btnParkSerachAntena = new QPushButton(gbMotor);
        btnParkSerachAntena->setObjectName(QString::fromUtf8("btnParkSerachAntena"));
        btnParkSerachAntena->setGeometry(QRect(130, 20, 121, 51));
        gridLayoutWidget_3 = new QWidget(gbMotor);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 270, 301, 131));
        gridLayout_12 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        txtFreq = new QLineEdit(gridLayoutWidget_3);
        txtFreq->setObjectName(QString::fromUtf8("txtFreq"));

        gridLayout_12->addWidget(txtFreq, 0, 2, 1, 1);

        txtDeAcc = new QLineEdit(gridLayoutWidget_3);
        txtDeAcc->setObjectName(QString::fromUtf8("txtDeAcc"));

        gridLayout_12->addWidget(txtDeAcc, 2, 2, 1, 1);

        btnSetDeAcc = new QPushButton(gridLayoutWidget_3);
        btnSetDeAcc->setObjectName(QString::fromUtf8("btnSetDeAcc"));

        gridLayout_12->addWidget(btnSetDeAcc, 2, 3, 1, 1);

        txtAcc = new QLineEdit(gridLayoutWidget_3);
        txtAcc->setObjectName(QString::fromUtf8("txtAcc"));

        gridLayout_12->addWidget(txtAcc, 1, 2, 1, 1);

        label_79 = new QLabel(gridLayoutWidget_3);
        label_79->setObjectName(QString::fromUtf8("label_79"));

        gridLayout_12->addWidget(label_79, 2, 0, 1, 1);

        label_77 = new QLabel(gridLayoutWidget_3);
        label_77->setObjectName(QString::fromUtf8("label_77"));

        gridLayout_12->addWidget(label_77, 1, 0, 1, 1);

        label_78 = new QLabel(gridLayoutWidget_3);
        label_78->setObjectName(QString::fromUtf8("label_78"));

        gridLayout_12->addWidget(label_78, 0, 0, 1, 1);

        btnSetAcc = new QPushButton(gridLayoutWidget_3);
        btnSetAcc->setObjectName(QString::fromUtf8("btnSetAcc"));

        gridLayout_12->addWidget(btnSetAcc, 1, 3, 1, 1);

        btnSetFreq = new QPushButton(gridLayoutWidget_3);
        btnSetFreq->setObjectName(QString::fromUtf8("btnSetFreq"));

        gridLayout_12->addWidget(btnSetFreq, 0, 3, 1, 1);

        gbAutoMove = new QGroupBox(gbMotor);
        gbAutoMove->setObjectName(QString::fromUtf8("gbAutoMove"));
        gbAutoMove->setGeometry(QRect(10, 150, 421, 111));
        chkAuto = new QCheckBox(gbAutoMove);
        chkAuto->setObjectName(QString::fromUtf8("chkAuto"));
        chkAuto->setGeometry(QRect(0, 50, 101, 22));
        errorNo_3 = new QLabel(gbAutoMove);
        errorNo_3->setObjectName(QString::fromUtf8("errorNo_3"));
        errorNo_3->setGeometry(QRect(120, 80, 81, 20));
        errorNo_2 = new QLabel(gbAutoMove);
        errorNo_2->setObjectName(QString::fromUtf8("errorNo_2"));
        errorNo_2->setGeometry(QRect(110, 40, 91, 20));
        errorNo_4 = new QLabel(gbAutoMove);
        errorNo_4->setObjectName(QString::fromUtf8("errorNo_4"));
        errorNo_4->setGeometry(QRect(280, 80, 81, 20));
        errorNo_5 = new QLabel(gbAutoMove);
        errorNo_5->setObjectName(QString::fromUtf8("errorNo_5"));
        errorNo_5->setGeometry(QRect(280, 40, 91, 20));
        txtCenterOfSpan = new QLineEdit(gbAutoMove);
        txtCenterOfSpan->setObjectName(QString::fromUtf8("txtCenterOfSpan"));
        txtCenterOfSpan->setGeometry(QRect(210, 40, 51, 27));
        txtSpan = new QLineEdit(gbAutoMove);
        txtSpan->setObjectName(QString::fromUtf8("txtSpan"));
        txtSpan->setGeometry(QRect(210, 80, 51, 27));
        txtSpan__1 = new QTextEdit(gbAutoMove);
        txtSpan__1->setObjectName(QString::fromUtf8("txtSpan__1"));
        txtSpan__1->setGeometry(QRect(240, 160, 51, 21));
        txtSpan__1->setFocusPolicy(Qt::WheelFocus);
        txtSpan__1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        txtSpan__1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        btnSetAutoSpan = new QPushButton(gbAutoMove);
        btnSetAutoSpan->setObjectName(QString::fromUtf8("btnSetAutoSpan"));
        btnSetAutoSpan->setGeometry(QRect(30, 80, 51, 27));
        csCenterofSpan = new QScrollBar(gbAutoMove);
        csCenterofSpan->setObjectName(QString::fromUtf8("csCenterofSpan"));
        csCenterofSpan->setGeometry(QRect(40, 20, 321, 16));
        csCenterofSpan->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(tab_COM);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 221, 191));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 191, 161));
        gridLayout_11 = new QGridLayout(gridLayoutWidget);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        lbl_SerialCom = new QLabel(gridLayoutWidget);
        lbl_SerialCom->setObjectName(QString::fromUtf8("lbl_SerialCom"));

        gridLayout_11->addWidget(lbl_SerialCom, 0, 0, 1, 1);

        cmbSerialComSearch = new QComboBox(gridLayoutWidget);
        cmbSerialComSearch->setObjectName(QString::fromUtf8("cmbSerialComSearch"));

        gridLayout_11->addWidget(cmbSerialComSearch, 0, 1, 1, 1);

        btnSerialOpenClose = new QPushButton(gridLayoutWidget);
        btnSerialOpenClose->setObjectName(QString::fromUtf8("btnSerialOpenClose"));

        gridLayout_11->addWidget(btnSerialOpenClose, 3, 0, 1, 1);

        lbl_SerialBaud = new QLabel(gridLayoutWidget);
        lbl_SerialBaud->setObjectName(QString::fromUtf8("lbl_SerialBaud"));

        gridLayout_11->addWidget(lbl_SerialBaud, 1, 0, 1, 1);

        cmbSerialBaud = new QComboBox(gridLayoutWidget);
        cmbSerialBaud->setObjectName(QString::fromUtf8("cmbSerialBaud"));

        gridLayout_11->addWidget(cmbSerialBaud, 1, 1, 1, 1);

        lbl_serialStatus = new QLabel(gridLayoutWidget);
        lbl_serialStatus->setObjectName(QString::fromUtf8("lbl_serialStatus"));

        gridLayout_11->addWidget(lbl_serialStatus, 3, 1, 1, 1);

        lbl_PC_Password = new QLabel(gridLayoutWidget);
        lbl_PC_Password->setObjectName(QString::fromUtf8("lbl_PC_Password"));

        gridLayout_11->addWidget(lbl_PC_Password, 2, 0, 1, 1);

        lePassWord = new QLineEdit(gridLayoutWidget);
        lePassWord->setObjectName(QString::fromUtf8("lePassWord"));

        gridLayout_11->addWidget(lePassWord, 2, 1, 1, 1);

        horizontalLayoutWidget_RSSI_SUM_Delta = new QWidget(tab_COM);
        horizontalLayoutWidget_RSSI_SUM_Delta->setObjectName(QString::fromUtf8("horizontalLayoutWidget_RSSI_SUM_Delta"));
        horizontalLayoutWidget_RSSI_SUM_Delta->setGeometry(QRect(540, 240, 501, 331));
        _2 = new QHBoxLayout(horizontalLayoutWidget_RSSI_SUM_Delta);
        _2->setSpacing(6);
        _2->setContentsMargins(11, 11, 11, 11);
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(0, 0, 0, 0);
        plot_RSSI_SUM_Delta = new QCustomPlot(horizontalLayoutWidget_RSSI_SUM_Delta);
        plot_RSSI_SUM_Delta->setObjectName(QString::fromUtf8("plot_RSSI_SUM_Delta"));
        plot_RSSI_SUM_Delta->setMinimumSize(QSize(400, 200));

        _2->addWidget(plot_RSSI_SUM_Delta);

        tableWidget = new QTableWidget(tab_COM);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(500, 21, 541, 211));
        btnResetMaxTable = new QPushButton(tab_COM);
        btnResetMaxTable->setObjectName(QString::fromUtf8("btnResetMaxTable"));
        btnResetMaxTable->setGeometry(QRect(390, 30, 98, 27));
        lbl_MovingFlage = new QLabel(tab_COM);
        lbl_MovingFlage->setObjectName(QString::fromUtf8("lbl_MovingFlage"));
        lbl_MovingFlage->setGeometry(QRect(250, 60, 51, 17));
        lbl_finalDegreefinal = new QLabel(tab_COM);
        lbl_finalDegreefinal->setObjectName(QString::fromUtf8("lbl_finalDegreefinal"));
        lbl_finalDegreefinal->setGeometry(QRect(250, 100, 101, 17));
        QFont font;
        font.setPointSize(14);
        lbl_finalDegreefinal->setFont(font);
        gb_SerialPlotRadios = new QGroupBox(tab_COM);
        gb_SerialPlotRadios->setObjectName(QString::fromUtf8("gb_SerialPlotRadios"));
        gb_SerialPlotRadios->setGeometry(QRect(420, 420, 111, 91));
        rdbRealTime = new QRadioButton(gb_SerialPlotRadios);
        rdbRealTime->setObjectName(QString::fromUtf8("rdbRealTime"));
        rdbRealTime->setGeometry(QRect(10, 30, 131, 22));
        rdbRealTime->setChecked(false);
        rdbEncoderPlot = new QRadioButton(gb_SerialPlotRadios);
        rdbEncoderPlot->setObjectName(QString::fromUtf8("rdbEncoderPlot"));
        rdbEncoderPlot->setGeometry(QRect(10, 60, 121, 22));
        rdbEncoderPlot->setChecked(true);
        gb_SerialPlotRadios_plarLinear = new QGroupBox(tab_COM);
        gb_SerialPlotRadios_plarLinear->setObjectName(QString::fromUtf8("gb_SerialPlotRadios_plarLinear"));
        gb_SerialPlotRadios_plarLinear->setGeometry(QRect(420, 530, 91, 91));
        rdbPolarPlot = new QRadioButton(gb_SerialPlotRadios_plarLinear);
        rdbPolarPlot->setObjectName(QString::fromUtf8("rdbPolarPlot"));
        rdbPolarPlot->setGeometry(QRect(10, 60, 131, 22));
        rdbPolarPlot->setChecked(false);
        rdbLinearPlot = new QRadioButton(gb_SerialPlotRadios_plarLinear);
        rdbLinearPlot->setObjectName(QString::fromUtf8("rdbLinearPlot"));
        rdbLinearPlot->setGeometry(QRect(10, 20, 121, 22));
        rdbLinearPlot->setChecked(true);
        groupBox_2 = new QGroupBox(tab_COM);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(409, 240, 121, 161));
        chkPlotSUM = new QCheckBox(groupBox_2);
        chkPlotSUM->setObjectName(QString::fromUtf8("chkPlotSUM"));
        chkPlotSUM->setGeometry(QRect(0, 30, 97, 22));
        chkPlotDelta = new QCheckBox(groupBox_2);
        chkPlotDelta->setObjectName(QString::fromUtf8("chkPlotDelta"));
        chkPlotDelta->setGeometry(QRect(0, 60, 97, 22));
        chkPlotSUM_Anlz = new QCheckBox(groupBox_2);
        chkPlotSUM_Anlz->setObjectName(QString::fromUtf8("chkPlotSUM_Anlz"));
        chkPlotSUM_Anlz->setGeometry(QRect(0, 90, 97, 22));
        chkPlotDeltaSLC_Anlz = new QCheckBox(groupBox_2);
        chkPlotDeltaSLC_Anlz->setObjectName(QString::fromUtf8("chkPlotDeltaSLC_Anlz"));
        chkPlotDeltaSLC_Anlz->setGeometry(QRect(0, 120, 121, 22));
        gbxAnlzType = new QGroupBox(tab_COM);
        gbxAnlzType->setObjectName(QString::fromUtf8("gbxAnlzType"));
        gbxAnlzType->setGeometry(QRect(370, 90, 120, 111));
        rdbAnlzAve = new QRadioButton(gbxAnlzType);
        rdbAnlzAve->setObjectName(QString::fromUtf8("rdbAnlzAve"));
        rdbAnlzAve->setGeometry(QRect(0, 30, 116, 22));
        rdbAnlzAve->setChecked(true);
        rdbAveFIR = new QRadioButton(gbxAnlzType);
        rdbAveFIR->setObjectName(QString::fromUtf8("rdbAveFIR"));
        rdbAveFIR->setGeometry(QRect(0, 60, 116, 22));
        Tab->addTab(tab_COM, QString());
        btnForceExit->raise();
        lbl_AnimationSerial->raise();
        btnTest->raise();
        gbMotor->raise();
        groupBox->raise();
        horizontalLayoutWidget_RSSI_SUM_Delta->raise();
        tableWidget->raise();
        btnResetMaxTable->raise();
        lbl_MovingFlage->raise();
        lbl_finalDegreefinal->raise();
        gb_SerialPlotRadios->raise();
        gb_SerialPlotRadios_plarLinear->raise();
        groupBox_2->raise();
        gbxAnlzType->raise();
        tab_Plot = new QWidget();
        tab_Plot->setObjectName(QString::fromUtf8("tab_Plot"));
        horizontalLayoutWidget_2 = new QWidget(tab_Plot);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(40, 220, 421, 331));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        plot_Dopp = new QCustomPlot(horizontalLayoutWidget_2);
        plot_Dopp->setObjectName(QString::fromUtf8("plot_Dopp"));
        plot_Dopp->setMinimumSize(QSize(400, 200));

        horizontalLayout->addWidget(plot_Dopp);

        lblfinalDegree = new QLabel(tab_Plot);
        lblfinalDegree->setObjectName(QString::fromUtf8("lblfinalDegree"));
        lblfinalDegree->setGeometry(QRect(180, 80, 66, 17));
        lblfinalDegree->setFont(font);
        btnClearDiagrams = new QPushButton(tab_Plot);
        btnClearDiagrams->setObjectName(QString::fromUtf8("btnClearDiagrams"));
        btnClearDiagrams->setGeometry(QRect(40, 170, 121, 27));
        layoutWidget1 = new QWidget(tab_Plot);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(175, 50, 206, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_17);

        lbl_MoveStatus = new QLabel(layoutWidget1);
        lbl_MoveStatus->setObjectName(QString::fromUtf8("lbl_MoveStatus"));

        horizontalLayout_2->addWidget(lbl_MoveStatus);

        Tab->addTab(tab_Plot, QString());
        tab_Watch_Config = new QWidget();
        tab_Watch_Config->setObjectName(QString::fromUtf8("tab_Watch_Config"));
        horizontalLayoutWidget_SAT = new QWidget(tab_Watch_Config);
        horizontalLayoutWidget_SAT->setObjectName(QString::fromUtf8("horizontalLayoutWidget_SAT"));
        horizontalLayoutWidget_SAT->setGeometry(QRect(530, 220, 501, 331));
        horizontalLayout_Plot_SAT = new QHBoxLayout(horizontalLayoutWidget_SAT);
        horizontalLayout_Plot_SAT->setSpacing(6);
        horizontalLayout_Plot_SAT->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_Plot_SAT->setObjectName(QString::fromUtf8("horizontalLayout_Plot_SAT"));
        horizontalLayout_Plot_SAT->setContentsMargins(0, 0, 0, 0);
        plot_RSSI_Delta = new QCustomPlot(horizontalLayoutWidget_SAT);
        plot_RSSI_Delta->setObjectName(QString::fromUtf8("plot_RSSI_Delta"));
        plot_RSSI_Delta->setMinimumSize(QSize(400, 200));

        horizontalLayout_Plot_SAT->addWidget(plot_RSSI_Delta);

        ledRotaryMCU_State = new HLed(tab_Watch_Config);
        ledRotaryMCU_State->setObjectName(QString::fromUtf8("ledRotaryMCU_State"));
        ledRotaryMCU_State->setGeometry(QRect(190, 60, 20, 20));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ledRotaryMCU_State->sizePolicy().hasHeightForWidth());
        ledRotaryMCU_State->setSizePolicy(sizePolicy1);
        ledRotaryMCU_State->setMinimumSize(QSize(15, 15));
        ledRotaryMCU_State->setMaximumSize(QSize(20, 20));
        slbl_2 = new QLabel(tab_Watch_Config);
        slbl_2->setObjectName(QString::fromUtf8("slbl_2"));
        slbl_2->setGeometry(QRect(40, 60, 141, 20));
        slbl_3 = new QLabel(tab_Watch_Config);
        slbl_3->setObjectName(QString::fromUtf8("slbl_3"));
        slbl_3->setGeometry(QRect(40, 100, 141, 20));
        ledFixMCU_State = new HLed(tab_Watch_Config);
        ledFixMCU_State->setObjectName(QString::fromUtf8("ledFixMCU_State"));
        ledFixMCU_State->setGeometry(QRect(190, 100, 20, 20));
        sizePolicy1.setHeightForWidth(ledFixMCU_State->sizePolicy().hasHeightForWidth());
        ledFixMCU_State->setSizePolicy(sizePolicy1);
        ledFixMCU_State->setMinimumSize(QSize(15, 15));
        ledFixMCU_State->setMaximumSize(QSize(20, 20));
        btnHighSum = new QPushButton(tab_Watch_Config);
        btnHighSum->setObjectName(QString::fromUtf8("btnHighSum"));
        btnHighSum->setGeometry(QRect(380, 30, 98, 27));
        btnLowSum = new QPushButton(tab_Watch_Config);
        btnLowSum->setObjectName(QString::fromUtf8("btnLowSum"));
        btnLowSum->setGeometry(QRect(380, 70, 98, 27));
        btnHighDelta = new QPushButton(tab_Watch_Config);
        btnHighDelta->setObjectName(QString::fromUtf8("btnHighDelta"));
        btnHighDelta->setGeometry(QRect(380, 110, 98, 27));
        btnLowDelta = new QPushButton(tab_Watch_Config);
        btnLowDelta->setObjectName(QString::fromUtf8("btnLowDelta"));
        btnLowDelta->setGeometry(QRect(380, 150, 98, 27));
        slbl_4 = new QLabel(tab_Watch_Config);
        slbl_4->setObjectName(QString::fromUtf8("slbl_4"));
        slbl_4->setGeometry(QRect(40, 140, 141, 20));
        slbl_5 = new QLabel(tab_Watch_Config);
        slbl_5->setObjectName(QString::fromUtf8("slbl_5"));
        slbl_5->setGeometry(QRect(40, 180, 141, 20));
        ledRcvDataSum = new HLed(tab_Watch_Config);
        ledRcvDataSum->setObjectName(QString::fromUtf8("ledRcvDataSum"));
        ledRcvDataSum->setGeometry(QRect(190, 140, 20, 20));
        sizePolicy1.setHeightForWidth(ledRcvDataSum->sizePolicy().hasHeightForWidth());
        ledRcvDataSum->setSizePolicy(sizePolicy1);
        ledRcvDataSum->setMinimumSize(QSize(15, 15));
        ledRcvDataSum->setMaximumSize(QSize(20, 20));
        ledRcvDataDelta = new HLed(tab_Watch_Config);
        ledRcvDataDelta->setObjectName(QString::fromUtf8("ledRcvDataDelta"));
        ledRcvDataDelta->setGeometry(QRect(190, 180, 20, 20));
        sizePolicy1.setHeightForWidth(ledRcvDataDelta->sizePolicy().hasHeightForWidth());
        ledRcvDataDelta->setSizePolicy(sizePolicy1);
        ledRcvDataDelta->setMinimumSize(QSize(15, 15));
        ledRcvDataDelta->setMaximumSize(QSize(20, 20));
        gbDelta_SLC = new QGroupBox(tab_Watch_Config);
        gbDelta_SLC->setObjectName(QString::fromUtf8("gbDelta_SLC"));
        gbDelta_SLC->setGeometry(QRect(590, 40, 201, 91));
        QFont font1;
        font1.setItalic(false);
        font1.setUnderline(false);
        gbDelta_SLC->setFont(font1);
        ledSelectDeltafb = new HLed(gbDelta_SLC);
        ledSelectDeltafb->setObjectName(QString::fromUtf8("ledSelectDeltafb"));
        ledSelectDeltafb->setGeometry(QRect(130, 30, 20, 20));
        sizePolicy1.setHeightForWidth(ledSelectDeltafb->sizePolicy().hasHeightForWidth());
        ledSelectDeltafb->setSizePolicy(sizePolicy1);
        ledSelectDeltafb->setMinimumSize(QSize(15, 15));
        ledSelectDeltafb->setMaximumSize(QSize(20, 20));
        layoutWidget_1 = new QWidget(gbDelta_SLC);
        layoutWidget_1->setObjectName(QString::fromUtf8("layoutWidget_1"));
        layoutWidget_1->setGeometry(QRect(30, 30, 131, 56));
        verticalLayout = new QVBoxLayout(layoutWidget_1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        rdbSelectDelta = new QRadioButton(layoutWidget_1);
        rdbSelectDelta->setObjectName(QString::fromUtf8("rdbSelectDelta"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        rdbSelectDelta->setFont(font2);
        rdbSelectDelta->setChecked(true);

        verticalLayout->addWidget(rdbSelectDelta);

        rdbSelectSLC = new QRadioButton(layoutWidget_1);
        rdbSelectSLC->setObjectName(QString::fromUtf8("rdbSelectSLC"));
        rdbSelectSLC->setFont(font2);

        verticalLayout->addWidget(rdbSelectSLC);

        layoutWidget_1->raise();
        ledSelectDeltafb->raise();
        ledSelectSLCfb = new HLed(tab_Watch_Config);
        ledSelectSLCfb->setObjectName(QString::fromUtf8("ledSelectSLCfb"));
        ledSelectSLCfb->setGeometry(QRect(720, 100, 20, 20));
        sizePolicy1.setHeightForWidth(ledSelectSLCfb->sizePolicy().hasHeightForWidth());
        ledSelectSLCfb->setSizePolicy(sizePolicy1);
        ledSelectSLCfb->setMinimumSize(QSize(15, 15));
        ledSelectSLCfb->setMaximumSize(QSize(20, 20));
        lblAxb = new QLabel(tab_Watch_Config);
        lblAxb->setObjectName(QString::fromUtf8("lblAxb"));
        lblAxb->setGeometry(QRect(120, 250, 101, 17));
        leOffsetAnalyzerSum = new QLineEdit(tab_Watch_Config);
        leOffsetAnalyzerSum->setObjectName(QString::fromUtf8("leOffsetAnalyzerSum"));
        leOffsetAnalyzerSum->setGeometry(QRect(170, 270, 51, 27));
        lblAxb_3 = new QLabel(tab_Watch_Config);
        lblAxb_3->setObjectName(QString::fromUtf8("lblAxb_3"));
        lblAxb_3->setGeometry(QRect(120, 310, 101, 17));
        pushButton = new QPushButton(tab_Watch_Config);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 300, 51, 27));
        lblBAnalyzor = new QLabel(tab_Watch_Config);
        lblBAnalyzor->setObjectName(QString::fromUtf8("lblBAnalyzor"));
        lblBAnalyzor->setGeometry(QRect(150, 340, 21, 17));
        leOffsetAnalyzerDelta = new QLineEdit(tab_Watch_Config);
        leOffsetAnalyzerDelta->setObjectName(QString::fromUtf8("leOffsetAnalyzerDelta"));
        leOffsetAnalyzerDelta->setGeometry(QRect(170, 330, 51, 27));
        lblAxb_2 = new QLabel(tab_Watch_Config);
        lblAxb_2->setObjectName(QString::fromUtf8("lblAxb_2"));
        lblAxb_2->setGeometry(QRect(50, 280, 16, 17));
        leCoefAnlyzorSum = new QLineEdit(tab_Watch_Config);
        leCoefAnlyzorSum->setObjectName(QString::fromUtf8("leCoefAnlyzorSum"));
        leCoefAnlyzorSum->setGeometry(QRect(70, 270, 51, 27));
        lblleOffsetAnalyzer = new QLabel(tab_Watch_Config);
        lblleOffsetAnalyzer->setObjectName(QString::fromUtf8("lblleOffsetAnalyzer"));
        lblleOffsetAnalyzer->setGeometry(QRect(150, 280, 21, 17));
        leCoefAnlyzorDelta = new QLineEdit(tab_Watch_Config);
        leCoefAnlyzorDelta->setObjectName(QString::fromUtf8("leCoefAnlyzorDelta"));
        leCoefAnlyzorDelta->setGeometry(QRect(70, 330, 51, 27));
        lblAxb_4 = new QLabel(tab_Watch_Config);
        lblAxb_4->setObjectName(QString::fromUtf8("lblAxb_4"));
        lblAxb_4->setGeometry(QRect(50, 340, 16, 17));
        slbl = new QLabel(tab_Watch_Config);
        slbl->setObjectName(QString::fromUtf8("slbl"));
        slbl->setGeometry(QRect(40, 20, 51, 17));
        ledDetect1 = new HLed(tab_Watch_Config);
        ledDetect1->setObjectName(QString::fromUtf8("ledDetect1"));
        ledDetect1->setGeometry(QRect(190, 20, 20, 20));
        sizePolicy1.setHeightForWidth(ledDetect1->sizePolicy().hasHeightForWidth());
        ledDetect1->setSizePolicy(sizePolicy1);
        ledDetect1->setMinimumSize(QSize(15, 15));
        ledDetect1->setMaximumSize(QSize(20, 20));
        ledSUM_SerialPin = new HLed(tab_Watch_Config);
        ledSUM_SerialPin->setObjectName(QString::fromUtf8("ledSUM_SerialPin"));
        ledSUM_SerialPin->setGeometry(QRect(500, 50, 20, 20));
        sizePolicy1.setHeightForWidth(ledSUM_SerialPin->sizePolicy().hasHeightForWidth());
        ledSUM_SerialPin->setSizePolicy(sizePolicy1);
        ledSUM_SerialPin->setMinimumSize(QSize(15, 15));
        ledSUM_SerialPin->setMaximumSize(QSize(20, 20));
        ledDeltaSLC_SerialPin = new HLed(tab_Watch_Config);
        ledDeltaSLC_SerialPin->setObjectName(QString::fromUtf8("ledDeltaSLC_SerialPin"));
        ledDeltaSLC_SerialPin->setGeometry(QRect(500, 130, 20, 20));
        sizePolicy1.setHeightForWidth(ledDeltaSLC_SerialPin->sizePolicy().hasHeightForWidth());
        ledDeltaSLC_SerialPin->setSizePolicy(sizePolicy1);
        ledDeltaSLC_SerialPin->setMinimumSize(QSize(15, 15));
        ledDeltaSLC_SerialPin->setMaximumSize(QSize(20, 20));
        layoutWidget = new QWidget(tab_Watch_Config);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 420, 361, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        lblAxb_5 = new QLabel(layoutWidget);
        lblAxb_5->setObjectName(QString::fromUtf8("lblAxb_5"));

        horizontalLayout_3->addWidget(lblAxb_5);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_19);

        leFreqRotMCU = new QLineEdit(layoutWidget);
        leFreqRotMCU->setObjectName(QString::fromUtf8("leFreqRotMCU"));

        horizontalLayout_3->addWidget(leFreqRotMCU);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_20);

        btnsetFrequencyRotMCU = new QPushButton(layoutWidget);
        btnsetFrequencyRotMCU->setObjectName(QString::fromUtf8("btnsetFrequencyRotMCU"));

        horizontalLayout_3->addWidget(btnsetFrequencyRotMCU);

        Tab->addTab(tab_Watch_Config, QString());
        tab_Analyzer = new QWidget();
        tab_Analyzer->setObjectName(QString::fromUtf8("tab_Analyzer"));
        horizontalLayoutWidget_a_2 = new QWidget(tab_Analyzer);
        horizontalLayoutWidget_a_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_a_2"));
        horizontalLayoutWidget_a_2->setGeometry(QRect(510, 220, 521, 331));
        horizontalLayout_Plot_a = new QHBoxLayout(horizontalLayoutWidget_a_2);
        horizontalLayout_Plot_a->setSpacing(6);
        horizontalLayout_Plot_a->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_Plot_a->setObjectName(QString::fromUtf8("horizontalLayout_Plot_a"));
        horizontalLayout_Plot_a->setContentsMargins(0, 0, 0, 0);
        plot_Analyzer_RSSI_SUM = new QCustomPlot(horizontalLayoutWidget_a_2);
        plot_Analyzer_RSSI_SUM->setObjectName(QString::fromUtf8("plot_Analyzer_RSSI_SUM"));
        plot_Analyzer_RSSI_SUM->setMinimumSize(QSize(400, 200));

        horizontalLayout_Plot_a->addWidget(plot_Analyzer_RSSI_SUM);

        gb_AnalyzerPlotRadios = new QGroupBox(tab_Analyzer);
        gb_AnalyzerPlotRadios->setObjectName(QString::fromUtf8("gb_AnalyzerPlotRadios"));
        gb_AnalyzerPlotRadios->setGeometry(QRect(270, 580, 511, 41));
        rb_RealTime_a = new QRadioButton(gb_AnalyzerPlotRadios);
        rb_RealTime_a->setObjectName(QString::fromUtf8("rb_RealTime_a"));
        rb_RealTime_a->setGeometry(QRect(90, 10, 131, 22));
        rb_RealTime_a->setChecked(false);
        rb_adc_EncoderPlot_a = new QRadioButton(gb_AnalyzerPlotRadios);
        rb_adc_EncoderPlot_a->setObjectName(QString::fromUtf8("rb_adc_EncoderPlot_a"));
        rb_adc_EncoderPlot_a->setGeometry(QRect(270, 10, 121, 22));
        rb_adc_EncoderPlot_a->setChecked(true);
        horizontalLayoutWidget_a = new QWidget(tab_Analyzer);
        horizontalLayoutWidget_a->setObjectName(QString::fromUtf8("horizontalLayoutWidget_a"));
        horizontalLayoutWidget_a->setGeometry(QRect(40, 220, 421, 331));
        horizontalLayout_a = new QHBoxLayout(horizontalLayoutWidget_a);
        horizontalLayout_a->setSpacing(6);
        horizontalLayout_a->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_a->setObjectName(QString::fromUtf8("horizontalLayout_a"));
        horizontalLayout_a->setContentsMargins(0, 0, 0, 0);
        plot_Analyzer_Dopp = new QCustomPlot(horizontalLayoutWidget_a);
        plot_Analyzer_Dopp->setObjectName(QString::fromUtf8("plot_Analyzer_Dopp"));
        plot_Analyzer_Dopp->setMinimumSize(QSize(400, 200));

        horizontalLayout_a->addWidget(plot_Analyzer_Dopp);

        tableWidget_a = new QTableWidget(tab_Analyzer);
        tableWidget_a->setObjectName(QString::fromUtf8("tableWidget_a"));
        tableWidget_a->setGeometry(QRect(490, 1, 541, 211));
        btnResetMaxTable_a = new QPushButton(tab_Analyzer);
        btnResetMaxTable_a->setObjectName(QString::fromUtf8("btnResetMaxTable_a"));
        btnResetMaxTable_a->setGeometry(QRect(370, 100, 98, 27));
        btnOpenFile = new QPushButton(tab_Analyzer);
        btnOpenFile->setObjectName(QString::fromUtf8("btnOpenFile"));
        btnOpenFile->setGeometry(QRect(40, 40, 98, 27));
        lbl_load = new QLabel(tab_Analyzer);
        lbl_load->setObjectName(QString::fromUtf8("lbl_load"));
        lbl_load->setGeometry(QRect(150, 50, 66, 17));
        btnAnalyze = new QPushButton(tab_Analyzer);
        btnAnalyze->setObjectName(QString::fromUtf8("btnAnalyze"));
        btnAnalyze->setGeometry(QRect(40, 80, 98, 27));
        label = new QLabel(tab_Analyzer);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 60, 81, 17));
        txtDataC_Size = new QLineEdit(tab_Analyzer);
        txtDataC_Size->setObjectName(QString::fromUtf8("txtDataC_Size"));
        txtDataC_Size->setGeometry(QRect(360, 60, 113, 27));
        btnSimplePLot = new QPushButton(tab_Analyzer);
        btnSimplePLot->setObjectName(QString::fromUtf8("btnSimplePLot"));
        btnSimplePLot->setGeometry(QRect(40, 120, 98, 27));
        btnMaxPlotAnaGO = new QPushButton(tab_Analyzer);
        btnMaxPlotAnaGO->setObjectName(QString::fromUtf8("btnMaxPlotAnaGO"));
        btnMaxPlotAnaGO->setGeometry(QRect(344, 160, 41, 27));
        btnMaxPlotAnaBack = new QPushButton(tab_Analyzer);
        btnMaxPlotAnaBack->setObjectName(QString::fromUtf8("btnMaxPlotAnaBack"));
        btnMaxPlotAnaBack->setGeometry(QRect(290, 160, 41, 27));
        lbl_load_2 = new QLabel(tab_Analyzer);
        lbl_load_2->setObjectName(QString::fromUtf8("lbl_load_2"));
        lbl_load_2->setGeometry(QRect(200, 160, 82, 29));
        pbPlotPicks = new QProgressBar(tab_Analyzer);
        pbPlotPicks->setObjectName(QString::fromUtf8("pbPlotPicks"));
        pbPlotPicks->setGeometry(QRect(200, 190, 181, 23));
        pbPlotPicks->setValue(24);
        lblCntMax = new QLabel(tab_Analyzer);
        lblCntMax->setObjectName(QString::fromUtf8("lblCntMax"));
        lblCntMax->setGeometry(QRect(60, 170, 66, 17));
        lblPicksSize = new QLabel(tab_Analyzer);
        lblPicksSize->setObjectName(QString::fromUtf8("lblPicksSize"));
        lblPicksSize->setGeometry(QRect(60, 190, 66, 17));
        btn_test2 = new QPushButton(tab_Analyzer);
        btn_test2->setObjectName(QString::fromUtf8("btn_test2"));
        btn_test2->setGeometry(QRect(370, 20, 98, 27));
        Tab->addTab(tab_Analyzer, QString());
        tab_TLE = new QWidget();
        tab_TLE->setObjectName(QString::fromUtf8("tab_TLE"));
        horizontalLayout_13 = new QHBoxLayout(tab_TLE);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        scrollArea_3 = new QScrollArea(tab_TLE);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 1031, 893));
        horizontalLayout_16 = new QHBoxLayout(scrollAreaWidgetContents_4);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        tabWidget = new QTabWidget(scrollAreaWidgetContents_4);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMaximumSize(QSize(1677, 16777215));
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_23 = new QVBoxLayout(tab_4);
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        verticalLayout_29 = new QVBoxLayout();
        verticalLayout_29->setSpacing(6);
        verticalLayout_29->setObjectName(QString::fromUtf8("verticalLayout_29"));
        groupBox_7 = new QGroupBox(tab_4);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setStyleSheet(QString::fromUtf8("\n"
"border-color: rgb(76, 109, 255);"));
        verticalLayout_32 = new QVBoxLayout(groupBox_7);
        verticalLayout_32->setSpacing(6);
        verticalLayout_32->setContentsMargins(11, 11, 11, 11);
        verticalLayout_32->setObjectName(QString::fromUtf8("verticalLayout_32"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_44 = new QLabel(groupBox_7);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout_4->addWidget(label_44, 0, 0, 1, 1);

        txttlefileaddress_2 = new QLineEdit(groupBox_7);
        txttlefileaddress_2->setObjectName(QString::fromUtf8("txttlefileaddress_2"));

        gridLayout_4->addWidget(txttlefileaddress_2, 0, 1, 1, 1);

        btnloadtlefromfile_2 = new QPushButton(groupBox_7);
        btnloadtlefromfile_2->setObjectName(QString::fromUtf8("btnloadtlefromfile_2"));

        gridLayout_4->addWidget(btnloadtlefromfile_2, 0, 2, 1, 1);


        verticalLayout_32->addLayout(gridLayout_4);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_46 = new QLabel(groupBox_7);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        horizontalLayout_14->addWidget(label_46);

        cmbsats_2 = new QComboBox(groupBox_7);
        cmbsats_2->setObjectName(QString::fromUtf8("cmbsats_2"));

        horizontalLayout_14->addWidget(cmbsats_2);


        horizontalLayout_23->addLayout(horizontalLayout_14);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_15);


        verticalLayout_32->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_50 = new QLabel(groupBox_7);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        gridLayout_5->addWidget(label_50, 0, 0, 1, 1);

        txtTLE1_2 = new QLineEdit(groupBox_7);
        txtTLE1_2->setObjectName(QString::fromUtf8("txtTLE1_2"));
        txtTLE1_2->setEnabled(true);
        txtTLE1_2->setMinimumSize(QSize(400, 0));

        gridLayout_5->addWidget(txtTLE1_2, 0, 1, 1, 1);

        label_51 = new QLabel(groupBox_7);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_5->addWidget(label_51, 1, 0, 1, 1);

        txtTLE2_2 = new QLineEdit(groupBox_7);
        txtTLE2_2->setObjectName(QString::fromUtf8("txtTLE2_2"));
        txtTLE2_2->setEnabled(true);
        txtTLE2_2->setMinimumSize(QSize(400, 0));

        gridLayout_5->addWidget(txtTLE2_2, 1, 1, 1, 1);


        horizontalLayout_24->addLayout(gridLayout_5);


        verticalLayout_32->addLayout(horizontalLayout_24);


        verticalLayout_29->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(tab_4);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        horizontalLayout_37 = new QHBoxLayout(groupBox_8);
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        line_5 = new QFrame(groupBox_8);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_37->addWidget(line_5);

        verticalLayout_33 = new QVBoxLayout();
        verticalLayout_33->setSpacing(6);
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        gridLayout_18 = new QGridLayout();
        gridLayout_18->setSpacing(6);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        label_52 = new QLabel(groupBox_8);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        gridLayout_18->addWidget(label_52, 3, 0, 1, 1);

        label_54 = new QLabel(groupBox_8);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        gridLayout_18->addWidget(label_54, 5, 0, 1, 1);

        txtaltitude_2 = new QLineEdit(groupBox_8);
        txtaltitude_2->setObjectName(QString::fromUtf8("txtaltitude_2"));

        gridLayout_18->addWidget(txtaltitude_2, 5, 1, 1, 1);

        txtLatitude_2 = new QLineEdit(groupBox_8);
        txtLatitude_2->setObjectName(QString::fromUtf8("txtLatitude_2"));

        gridLayout_18->addWidget(txtLatitude_2, 3, 1, 1, 1);

        label_53 = new QLabel(groupBox_8);
        label_53->setObjectName(QString::fromUtf8("label_53"));

        gridLayout_18->addWidget(label_53, 4, 0, 1, 1);

        txtLongitude_2 = new QLineEdit(groupBox_8);
        txtLongitude_2->setObjectName(QString::fromUtf8("txtLongitude_2"));

        gridLayout_18->addWidget(txtLongitude_2, 4, 1, 1, 1);

        comboBoxGPS = new QComboBox(groupBox_8);
        comboBoxGPS->setObjectName(QString::fromUtf8("comboBoxGPS"));

        gridLayout_18->addWidget(comboBoxGPS, 2, 0, 1, 2);


        verticalLayout_33->addLayout(gridLayout_18);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        btnShowOnMap_2 = new QPushButton(groupBox_8);
        btnShowOnMap_2->setObjectName(QString::fromUtf8("btnShowOnMap_2"));

        horizontalLayout_38->addWidget(btnShowOnMap_2);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer_16);


        verticalLayout_33->addLayout(horizontalLayout_38);


        horizontalLayout_37->addLayout(verticalLayout_33);

        verticalLayout_34 = new QVBoxLayout();
        verticalLayout_34->setSpacing(6);
        verticalLayout_34->setObjectName(QString::fromUtf8("verticalLayout_34"));
        groupBox_9 = new QGroupBox(groupBox_8);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        verticalLayout_35 = new QVBoxLayout(groupBox_9);
        verticalLayout_35->setSpacing(6);
        verticalLayout_35->setContentsMargins(11, 11, 11, 11);
        verticalLayout_35->setObjectName(QString::fromUtf8("verticalLayout_35"));
        Lambda_TLE_lineEdit_2 = new QLineEdit(groupBox_9);
        Lambda_TLE_lineEdit_2->setObjectName(QString::fromUtf8("Lambda_TLE_lineEdit_2"));

        verticalLayout_35->addWidget(Lambda_TLE_lineEdit_2);


        verticalLayout_34->addWidget(groupBox_9);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_34->addItem(verticalSpacer_12);


        horizontalLayout_37->addLayout(verticalLayout_34);

        verticalLayout_36 = new QVBoxLayout();
        verticalLayout_36->setSpacing(6);
        verticalLayout_36->setObjectName(QString::fromUtf8("verticalLayout_36"));
        gridLayout_19 = new QGridLayout();
        gridLayout_19->setSpacing(6);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        txtLongitudetle_2 = new QLineEdit(groupBox_8);
        txtLongitudetle_2->setObjectName(QString::fromUtf8("txtLongitudetle_2"));

        gridLayout_19->addWidget(txtLongitudetle_2, 2, 1, 1, 1);

        label_58 = new QLabel(groupBox_8);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        gridLayout_19->addWidget(label_58, 3, 0, 1, 1);

        label_56 = new QLabel(groupBox_8);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        gridLayout_19->addWidget(label_56, 1, 0, 1, 1);

        txtLatitudetle_2 = new QLineEdit(groupBox_8);
        txtLatitudetle_2->setObjectName(QString::fromUtf8("txtLatitudetle_2"));

        gridLayout_19->addWidget(txtLatitudetle_2, 1, 1, 1, 1);

        label_57 = new QLabel(groupBox_8);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        gridLayout_19->addWidget(label_57, 2, 0, 1, 1);

        txtaltitudetle_2 = new QLineEdit(groupBox_8);
        txtaltitudetle_2->setObjectName(QString::fromUtf8("txtaltitudetle_2"));

        gridLayout_19->addWidget(txtaltitudetle_2, 3, 1, 1, 1);

        btnConvertTLETOLLA_2 = new QPushButton(groupBox_8);
        btnConvertTLETOLLA_2->setObjectName(QString::fromUtf8("btnConvertTLETOLLA_2"));

        gridLayout_19->addWidget(btnConvertTLETOLLA_2, 0, 0, 1, 2);


        verticalLayout_36->addLayout(gridLayout_19);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_18);

        pushButton_6 = new QPushButton(groupBox_8);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        horizontalLayout_39->addWidget(pushButton_6);


        verticalLayout_36->addLayout(horizontalLayout_39);


        horizontalLayout_37->addLayout(verticalLayout_36);

        line_6 = new QFrame(groupBox_8);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setMaximumSize(QSize(16777215, 16777210));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_37->addWidget(line_6);


        verticalLayout_29->addWidget(groupBox_8);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        plot_predict_2 = new QCustomPlot(tab_4);
        plot_predict_2->setObjectName(QString::fromUtf8("plot_predict_2"));
        plot_predict_2->setMinimumSize(QSize(400, 200));

        horizontalLayout_40->addWidget(plot_predict_2);

        verticalLayout_37 = new QVBoxLayout();
        verticalLayout_37->setSpacing(6);
        verticalLayout_37->setObjectName(QString::fromUtf8("verticalLayout_37"));
        EL_radioButton_2 = new QRadioButton(tab_4);
        EL_radioButton_2->setObjectName(QString::fromUtf8("EL_radioButton_2"));
        EL_radioButton_2->setChecked(true);

        verticalLayout_37->addWidget(EL_radioButton_2);

        Doppler_radioButton_2 = new QRadioButton(tab_4);
        Doppler_radioButton_2->setObjectName(QString::fromUtf8("Doppler_radioButton_2"));

        verticalLayout_37->addWidget(Doppler_radioButton_2);

        EL_AZ_radioButton_2 = new QRadioButton(tab_4);
        EL_AZ_radioButton_2->setObjectName(QString::fromUtf8("EL_AZ_radioButton_2"));

        verticalLayout_37->addWidget(EL_AZ_radioButton_2);

        EL_Doppler_radioButton_2 = new QRadioButton(tab_4);
        EL_Doppler_radioButton_2->setObjectName(QString::fromUtf8("EL_Doppler_radioButton_2"));

        verticalLayout_37->addWidget(EL_Doppler_radioButton_2);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_37->addItem(verticalSpacer_14);


        horizontalLayout_40->addLayout(verticalLayout_37);


        verticalLayout_29->addLayout(horizontalLayout_40);


        horizontalLayout_19->addLayout(verticalLayout_29);


        verticalLayout_23->addLayout(horizontalLayout_19);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        groupBox_10 = new QGroupBox(tab_4);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        horizontalLayout_48 = new QHBoxLayout(groupBox_10);
        horizontalLayout_48->setSpacing(6);
        horizontalLayout_48->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_48->setObjectName(QString::fromUtf8("horizontalLayout_48"));
        verticalLayout_42 = new QVBoxLayout();
        verticalLayout_42->setSpacing(6);
        verticalLayout_42->setObjectName(QString::fromUtf8("verticalLayout_42"));
        gridLayout_26 = new QGridLayout();
        gridLayout_26->setSpacing(6);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        label_67 = new QLabel(groupBox_10);
        label_67->setObjectName(QString::fromUtf8("label_67"));

        gridLayout_26->addWidget(label_67, 0, 0, 1, 1);

        cmblocaldatetime_3 = new QTimeEdit(groupBox_10);
        cmblocaldatetime_3->setObjectName(QString::fromUtf8("cmblocaldatetime_3"));
        cmblocaldatetime_3->setEnabled(false);
        cmblocaldatetime_3->setTime(QTime(4, 0, 0));
        cmblocaldatetime_3->setTimeSpec(Qt::LocalTime);

        gridLayout_26->addWidget(cmblocaldatetime_3, 0, 1, 1, 1);


        verticalLayout_42->addLayout(gridLayout_26);

        gridLayout_27 = new QGridLayout();
        gridLayout_27->setSpacing(6);
        gridLayout_27->setObjectName(QString::fromUtf8("gridLayout_27"));
        cmbutctime_3 = new QTimeEdit(groupBox_10);
        cmbutctime_3->setObjectName(QString::fromUtf8("cmbutctime_3"));
        cmbutctime_3->setEnabled(false);

        gridLayout_27->addWidget(cmbutctime_3, 0, 1, 1, 1);

        label_68 = new QLabel(groupBox_10);
        label_68->setObjectName(QString::fromUtf8("label_68"));

        gridLayout_27->addWidget(label_68, 0, 0, 1, 1);


        verticalLayout_42->addLayout(gridLayout_27);

        gridLayout_28 = new QGridLayout();
        gridLayout_28->setSpacing(6);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));

        verticalLayout_42->addLayout(gridLayout_28);


        horizontalLayout_48->addLayout(verticalLayout_42);

        verticalLayout_43 = new QVBoxLayout();
        verticalLayout_43->setSpacing(6);
        verticalLayout_43->setObjectName(QString::fromUtf8("verticalLayout_43"));
        btnpredict_3 = new QPushButton(groupBox_10);
        btnpredict_3->setObjectName(QString::fromUtf8("btnpredict_3"));
        btnpredict_3->setMaximumSize(QSize(100, 30));

        verticalLayout_43->addWidget(btnpredict_3);

        chkSavePredict2File = new QCheckBox(groupBox_10);
        chkSavePredict2File->setObjectName(QString::fromUtf8("chkSavePredict2File"));

        verticalLayout_43->addWidget(chkSavePredict2File);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_43->addItem(verticalSpacer_16);

        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QString::fromUtf8("horizontalLayout_49"));
        txthours_3 = new QSpinBox(groupBox_10);
        txthours_3->setObjectName(QString::fromUtf8("txthours_3"));
        txthours_3->setMinimum(1);
        txthours_3->setMaximum(10000);
        txthours_3->setValue(9);

        horizontalLayout_49->addWidget(txthours_3);

        label_69 = new QLabel(groupBox_10);
        label_69->setObjectName(QString::fromUtf8("label_69"));

        horizontalLayout_49->addWidget(label_69);

        progressBar_3 = new QProgressBar(groupBox_10);
        progressBar_3->setObjectName(QString::fromUtf8("progressBar_3"));
        progressBar_3->setValue(0);

        horizontalLayout_49->addWidget(progressBar_3);


        verticalLayout_43->addLayout(horizontalLayout_49);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_43->addItem(verticalSpacer_15);


        horizontalLayout_48->addLayout(verticalLayout_43);


        horizontalLayout_45->addWidget(groupBox_10);


        verticalLayout_23->addLayout(horizontalLayout_45);

        GridViewSatRising = new QTableWidget(tab_4);
        if (GridViewSatRising->columnCount() < 9)
            GridViewSatRising->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        GridViewSatRising->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        GridViewSatRising->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        GridViewSatRising->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        GridViewSatRising->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        GridViewSatRising->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        GridViewSatRising->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        GridViewSatRising->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        GridViewSatRising->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        GridViewSatRising->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        GridViewSatRising->setObjectName(QString::fromUtf8("GridViewSatRising"));
        GridViewSatRising->setMinimumSize(QSize(500, 0));

        verticalLayout_23->addWidget(GridViewSatRising);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        horizontalLayout_18 = new QHBoxLayout(tab_5);
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setSizeConstraint(QLayout::SetDefaultConstraint);
        btnperedict = new QPushButton(tab_5);
        btnperedict->setObjectName(QString::fromUtf8("btnperedict"));
        btnperedict->setMaximumSize(QSize(100, 27));

        verticalLayout_16->addWidget(btnperedict);

        progresssat = new QProgressBar(tab_5);
        progresssat->setObjectName(QString::fromUtf8("progresssat"));
        progresssat->setMaximumSize(QSize(100, 25));
        progresssat->setValue(0);

        verticalLayout_16->addWidget(progresssat);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_3);


        horizontalLayout_17->addLayout(verticalLayout_16);

        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setSizeConstraint(QLayout::SetMaximumSize);
        gridperdicSats = new QTableWidget(tab_5);
        if (gridperdicSats->columnCount() < 9)
            gridperdicSats->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        gridperdicSats->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        gridperdicSats->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        gridperdicSats->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        gridperdicSats->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        gridperdicSats->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        gridperdicSats->setHorizontalHeaderItem(5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        gridperdicSats->setHorizontalHeaderItem(6, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        gridperdicSats->setHorizontalHeaderItem(7, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        gridperdicSats->setHorizontalHeaderItem(8, __qtablewidgetitem17);
        gridperdicSats->setObjectName(QString::fromUtf8("gridperdicSats"));

        verticalLayout_21->addWidget(gridperdicSats);


        horizontalLayout_17->addLayout(verticalLayout_21);

        horizontalLayout_17->setStretch(0, 10);
        horizontalLayout_17->setStretch(1, 90);

        horizontalLayout_18->addLayout(horizontalLayout_17);

        tabWidget->addTab(tab_5, QString());

        horizontalLayout_16->addWidget(tabWidget);

        scrollArea_3->setWidget(scrollAreaWidgetContents_4);

        horizontalLayout_13->addWidget(scrollArea_3);

        Tab->addTab(tab_TLE, QString());
        tab_Settings = new QWidget();
        tab_Settings->setObjectName(QString::fromUtf8("tab_Settings"));
        lePassWord_Settings = new QLineEdit(tab_Settings);
        lePassWord_Settings->setObjectName(QString::fromUtf8("lePassWord_Settings"));
        lePassWord_Settings->setGeometry(QRect(112, 20, 97, 27));
        lbl_PC_Password_2 = new QLabel(tab_Settings);
        lbl_PC_Password_2->setObjectName(QString::fromUtf8("lbl_PC_Password_2"));
        lbl_PC_Password_2->setGeometry(QRect(20, 20, 86, 27));
        pushButton_2 = new QPushButton(tab_Settings);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 20, 98, 27));
        Tab->addTab(tab_Settings, QString());
        layoutWidget_5 = new QWidget(centralWidget);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_5);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        layoutWidget_6 = new QWidget(centralWidget);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_6);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1086, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        Tab->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        btnTest->setText(QApplication::translate("MainWindow", "Test", 0, QApplication::UnicodeUTF8));
        btnForceExit->setText(QApplication::translate("MainWindow", "Force Exit", 0, QApplication::UnicodeUTF8));
        lbl_AnimationSerial->setText(QApplication::translate("MainWindow", ".", 0, QApplication::UnicodeUTF8));
        gbMotor->setTitle(QApplication::translate("MainWindow", "Motor Configue", 0, QApplication::UnicodeUTF8));
        btnForwardM->setText(QApplication::translate("MainWindow", "Forward", 0, QApplication::UnicodeUTF8));
        btnStopMotor->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        btnReverseM->setText(QApplication::translate("MainWindow", "Reverse", 0, QApplication::UnicodeUTF8));
        btnEmergencyStopMotor->setText(QApplication::translate("MainWindow", "Emergency Stop", 0, QApplication::UnicodeUTF8));
        btnParkSerachAntena->setText(QApplication::translate("MainWindow", "Park Antenna", 0, QApplication::UnicodeUTF8));
        btnSetDeAcc->setText(QApplication::translate("MainWindow", "Set DeAcc", 0, QApplication::UnicodeUTF8));
        label_79->setText(QApplication::translate("MainWindow", "DeAcc -10", 0, QApplication::UnicodeUTF8));
        label_77->setText(QApplication::translate("MainWindow", "Acc +10", 0, QApplication::UnicodeUTF8));
        label_78->setText(QApplication::translate("MainWindow", "Frequency", 0, QApplication::UnicodeUTF8));
        btnSetAcc->setText(QApplication::translate("MainWindow", "Set Accel", 0, QApplication::UnicodeUTF8));
        btnSetFreq->setText(QApplication::translate("MainWindow", "Set Freq", 0, QApplication::UnicodeUTF8));
        gbAutoMove->setTitle(QApplication::translate("MainWindow", "Auto Span", 0, QApplication::UnicodeUTF8));
        chkAuto->setText(QApplication::translate("MainWindow", "Auto move", 0, QApplication::UnicodeUTF8));
        errorNo_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Scan Domain</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        errorNo_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Center of Scan</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        errorNo_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">8 to 60</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        errorNo_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">0 to 359</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnSetAutoSpan->setText(QApplication::translate("MainWindow", "Set", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "COM Interface", 0, QApplication::UnicodeUTF8));
        lbl_SerialCom->setText(QApplication::translate("MainWindow", "COM", 0, QApplication::UnicodeUTF8));
        btnSerialOpenClose->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        lbl_SerialBaud->setText(QApplication::translate("MainWindow", "Buadrate", 0, QApplication::UnicodeUTF8));
        lbl_serialStatus->setText(QApplication::translate("MainWindow", "Closed", 0, QApplication::UnicodeUTF8));
        lbl_PC_Password->setText(QApplication::translate("MainWindow", "PC Password", 0, QApplication::UnicodeUTF8));
        btnResetMaxTable->setText(QApplication::translate("MainWindow", "Reset Table", 0, QApplication::UnicodeUTF8));
        lbl_MovingFlage->setText(QApplication::translate("MainWindow", "--", 0, QApplication::UnicodeUTF8));
        lbl_finalDegreefinal->setText(QApplication::translate("MainWindow", "--", 0, QApplication::UnicodeUTF8));
        gb_SerialPlotRadios->setTitle(QApplication::translate("MainWindow", "X Axis Plot", 0, QApplication::UnicodeUTF8));
        rdbRealTime->setText(QApplication::translate("MainWindow", "Real Time", 0, QApplication::UnicodeUTF8));
        rdbEncoderPlot->setText(QApplication::translate("MainWindow", "Encoder", 0, QApplication::UnicodeUTF8));
        gb_SerialPlotRadios_plarLinear->setTitle(QApplication::translate("MainWindow", "Plot Sketch", 0, QApplication::UnicodeUTF8));
        rdbPolarPlot->setText(QApplication::translate("MainWindow", "Polar", 0, QApplication::UnicodeUTF8));
        rdbLinearPlot->setText(QApplication::translate("MainWindow", "Linear", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Y Axis Plot", 0, QApplication::UnicodeUTF8));
        chkPlotSUM->setText(QApplication::translate("MainWindow", "SUM", 0, QApplication::UnicodeUTF8));
        chkPlotDelta->setText(QApplication::translate("MainWindow", "Delta", 0, QApplication::UnicodeUTF8));
        chkPlotSUM_Anlz->setText(QApplication::translate("MainWindow", "SUM_Anlz", 0, QApplication::UnicodeUTF8));
        chkPlotDeltaSLC_Anlz->setText(QApplication::translate("MainWindow", "Del_SLC_Anlz", 0, QApplication::UnicodeUTF8));
        gbxAnlzType->setTitle(QApplication::translate("MainWindow", "Analyzor Tpe", 0, QApplication::UnicodeUTF8));
        rdbAnlzAve->setText(QApplication::translate("MainWindow", "Average Anlz", 0, QApplication::UnicodeUTF8));
        rdbAveFIR->setText(QApplication::translate("MainWindow", "FIR Anlz", 0, QApplication::UnicodeUTF8));
        Tab->setTabText(Tab->indexOf(tab_COM), QApplication::translate("MainWindow", "Main", 0, QApplication::UnicodeUTF8));
        lblfinalDegree->setText(QApplication::translate("MainWindow", "--", 0, QApplication::UnicodeUTF8));
        btnClearDiagrams->setText(QApplication::translate("MainWindow", "Clear Diagrams", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Moving Status", 0, QApplication::UnicodeUTF8));
        lbl_MoveStatus->setText(QApplication::translate("MainWindow", "Stopped", 0, QApplication::UnicodeUTF8));
        Tab->setTabText(Tab->indexOf(tab_Plot), QApplication::translate("MainWindow", "Plot", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ledRotaryMCU_State->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        slbl_2->setText(QApplication::translate("MainWindow", "Rotary MCU State", 0, QApplication::UnicodeUTF8));
        slbl_3->setText(QApplication::translate("MainWindow", "Fix MCU State", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ledFixMCU_State->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        btnHighSum->setText(QApplication::translate("MainWindow", "HighSum", 0, QApplication::UnicodeUTF8));
        btnLowSum->setText(QApplication::translate("MainWindow", "LowSum", 0, QApplication::UnicodeUTF8));
        btnHighDelta->setText(QApplication::translate("MainWindow", "HighDeltaSLC", 0, QApplication::UnicodeUTF8));
        btnLowDelta->setText(QApplication::translate("MainWindow", "LowDeltaSLC", 0, QApplication::UnicodeUTF8));
        slbl_4->setText(QApplication::translate("MainWindow", "rcvData_Sum", 0, QApplication::UnicodeUTF8));
        slbl_5->setText(QApplication::translate("MainWindow", "rcvData_Delta", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ledRcvDataSum->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ledRcvDataDelta->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        gbDelta_SLC->setTitle(QApplication::translate("MainWindow", "Delta_SLC Selection", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ledSelectDeltafb->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        rdbSelectDelta->setText(QApplication::translate("MainWindow", "Delta", 0, QApplication::UnicodeUTF8));
        rdbSelectSLC->setText(QApplication::translate("MainWindow", "SLC", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ledSelectSLCfb->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        lblAxb->setText(QApplication::translate("MainWindow", "Sum :  a*x + b", 0, QApplication::UnicodeUTF8));
        lblAxb_3->setText(QApplication::translate("MainWindow", "Delta :  a*x + b", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Set", 0, QApplication::UnicodeUTF8));
        lblBAnalyzor->setText(QApplication::translate("MainWindow", "b=", 0, QApplication::UnicodeUTF8));
        lblAxb_2->setText(QApplication::translate("MainWindow", "a=", 0, QApplication::UnicodeUTF8));
        lblleOffsetAnalyzer->setText(QApplication::translate("MainWindow", "b=", 0, QApplication::UnicodeUTF8));
        lblAxb_4->setText(QApplication::translate("MainWindow", "a=", 0, QApplication::UnicodeUTF8));
        slbl->setText(QApplication::translate("MainWindow", "Detect", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ledDetect1->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ledSUM_SerialPin->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ledDeltaSLC_SerialPin->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        lblAxb_5->setText(QApplication::translate("MainWindow", "Frequency", 0, QApplication::UnicodeUTF8));
        leFreqRotMCU->setText(QApplication::translate("MainWindow", "12345.12345", 0, QApplication::UnicodeUTF8));
        btnsetFrequencyRotMCU->setText(QApplication::translate("MainWindow", "Set Frequncy", 0, QApplication::UnicodeUTF8));
        Tab->setTabText(Tab->indexOf(tab_Watch_Config), QApplication::translate("MainWindow", "Watch Config", 0, QApplication::UnicodeUTF8));
        gb_AnalyzerPlotRadios->setTitle(QApplication::translate("MainWindow", "Plotting", 0, QApplication::UnicodeUTF8));
        rb_RealTime_a->setText(QApplication::translate("MainWindow", "ADC Real Time", 0, QApplication::UnicodeUTF8));
        rb_adc_EncoderPlot_a->setText(QApplication::translate("MainWindow", "ADC_Encoder", 0, QApplication::UnicodeUTF8));
        btnResetMaxTable_a->setText(QApplication::translate("MainWindow", "Reset Table", 0, QApplication::UnicodeUTF8));
        btnOpenFile->setText(QApplication::translate("MainWindow", "Open File", 0, QApplication::UnicodeUTF8));
        lbl_load->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        btnAnalyze->setText(QApplication::translate("MainWindow", "Analyze", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "DataC_size", 0, QApplication::UnicodeUTF8));
        btnSimplePLot->setText(QApplication::translate("MainWindow", "Simple Plot", 0, QApplication::UnicodeUTF8));
        btnMaxPlotAnaGO->setText(QApplication::translate("MainWindow", ">>", 0, QApplication::UnicodeUTF8));
        btnMaxPlotAnaBack->setText(QApplication::translate("MainWindow", "<<", 0, QApplication::UnicodeUTF8));
        lbl_load_2->setText(QApplication::translate("MainWindow", "Plot Picks", 0, QApplication::UnicodeUTF8));
        lblCntMax->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        lblPicksSize->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        btn_test2->setText(QApplication::translate("MainWindow", "Test", 0, QApplication::UnicodeUTF8));
        Tab->setTabText(Tab->indexOf(tab_Analyzer), QApplication::translate("MainWindow", "Analyzer", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "TLE", 0, QApplication::UnicodeUTF8));
        label_44->setText(QApplication::translate("MainWindow", "FileAddress", 0, QApplication::UnicodeUTF8));
        btnloadtlefromfile_2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("MainWindow", "List OF Sats", 0, QApplication::UnicodeUTF8));
        label_50->setText(QApplication::translate("MainWindow", "Line1", 0, QApplication::UnicodeUTF8));
        txtTLE1_2->setText(QApplication::translate("MainWindow", "1 33499U 09002H   13290.29939973  .00001196  00000-0  19614-3 0  1819", 0, QApplication::UnicodeUTF8));
        label_51->setText(QApplication::translate("MainWindow", "Line2", 0, QApplication::UnicodeUTF8));
        txtTLE2_2->setText(QApplication::translate("MainWindow", "2 33499 098.1629 051.4594 0008874 325.4394 064.4555 14.72557634254093", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Ground Station LLA                                                                           Satellite LLA", 0, QApplication::UnicodeUTF8));
        label_52->setText(QApplication::translate("MainWindow", "Latitude", 0, QApplication::UnicodeUTF8));
        label_54->setText(QApplication::translate("MainWindow", "Altitude", 0, QApplication::UnicodeUTF8));
        txtaltitude_2->setText(QApplication::translate("MainWindow", "1053.0", 0, QApplication::UnicodeUTF8));
        txtLatitude_2->setText(QApplication::translate("MainWindow", "35.69439", 0, QApplication::UnicodeUTF8));
        label_53->setText(QApplication::translate("MainWindow", "Longitude", 0, QApplication::UnicodeUTF8));
        txtLongitude_2->setText(QApplication::translate("MainWindow", "51.42151", 0, QApplication::UnicodeUTF8));
        btnShowOnMap_2->setText(QApplication::translate("MainWindow", "Show Me On Map", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "Wave Length [m]", 0, QApplication::UnicodeUTF8));
        Lambda_TLE_lineEdit_2->setText(QApplication::translate("MainWindow", "0.68", 0, QApplication::UnicodeUTF8));
        txtLongitudetle_2->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_58->setText(QApplication::translate("MainWindow", "Altitude", 0, QApplication::UnicodeUTF8));
        label_56->setText(QApplication::translate("MainWindow", "Latitude", 0, QApplication::UnicodeUTF8));
        txtLatitudetle_2->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_57->setText(QApplication::translate("MainWindow", "Longitude", 0, QApplication::UnicodeUTF8));
        txtaltitudetle_2->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        btnConvertTLETOLLA_2->setText(QApplication::translate("MainWindow", "TLE2LLA", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MainWindow", "Show LLA Map Online", 0, QApplication::UnicodeUTF8));
        EL_radioButton_2->setText(QApplication::translate("MainWindow", "EL", 0, QApplication::UnicodeUTF8));
        Doppler_radioButton_2->setText(QApplication::translate("MainWindow", "Doppler", 0, QApplication::UnicodeUTF8));
        EL_AZ_radioButton_2->setText(QApplication::translate("MainWindow", "EL+AZ", 0, QApplication::UnicodeUTF8));
        EL_Doppler_radioButton_2->setText(QApplication::translate("MainWindow", "EL+Doppler", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("MainWindow", "Rising Prediction", 0, QApplication::UnicodeUTF8));
        label_67->setText(QApplication::translate("MainWindow", "Local Time", 0, QApplication::UnicodeUTF8));
        cmblocaldatetime_3->setDisplayFormat(QApplication::translate("MainWindow", "h:mm", 0, QApplication::UnicodeUTF8));
        label_68->setText(QApplication::translate("MainWindow", "UTC Time", 0, QApplication::UnicodeUTF8));
        btnpredict_3->setText(QApplication::translate("MainWindow", "Predict", 0, QApplication::UnicodeUTF8));
        chkSavePredict2File->setText(QApplication::translate("MainWindow", "Save Prediction to File", 0, QApplication::UnicodeUTF8));
        label_69->setText(QApplication::translate("MainWindow", "Up to(hours)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = GridViewSatRising->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "StartTime", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = GridViewSatRising->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "StartAz", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = GridViewSatRising->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "MaxElTime", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = GridViewSatRising->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "MaxEL", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = GridViewSatRising->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Az", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = GridViewSatRising->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "EndTime", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = GridViewSatRising->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "EndAz", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = GridViewSatRising->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Tracking", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = GridViewSatRising->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Type", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Parameters", 0, QApplication::UnicodeUTF8));
        btnperedict->setText(QApplication::translate("MainWindow", "Perdict", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = gridperdicSats->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "SatName", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = gridperdicSats->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "StartTime", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = gridperdicSats->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "StartAZ", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = gridperdicSats->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "MaxElTime", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = gridperdicSats->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "MaxEL", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = gridperdicSats->horizontalHeaderItem(5);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "MaxAZ", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = gridperdicSats->horizontalHeaderItem(6);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "EndTime", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = gridperdicSats->horizontalHeaderItem(7);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "EndAZ", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = gridperdicSats->horizontalHeaderItem(8);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "Type", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Peridict Sats", 0, QApplication::UnicodeUTF8));
        Tab->setTabText(Tab->indexOf(tab_TLE), QApplication::translate("MainWindow", "TLE", 0, QApplication::UnicodeUTF8));
        lbl_PC_Password_2->setText(QApplication::translate("MainWindow", "PC Password", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Unlock", 0, QApplication::UnicodeUTF8));
        Tab->setTabText(Tab->indexOf(tab_Settings), QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
