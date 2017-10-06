/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri Oct 6 21:17:52 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      66,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      29,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   11,   11,   11, 0x08,
      76,   11,   11,   11, 0x08,
     101,   11,   11,   11, 0x08,
     127,   11,   11,   11, 0x08,
     152,   11,   11,   11, 0x08,
     185,   11,   11,   11, 0x08,
     220,   11,   11,   11, 0x08,
     244,   11,   11,   11, 0x08,
     267,   11,   11,   11, 0x08,
     292,   11,   11,   11, 0x08,
     328,  316,   11,   11, 0x08,
     382,  372,  363,   11, 0x08,
     430,  420,   11,   11, 0x08,
     446,   11,   11,   11, 0x08,
     475,   11,   11,   11, 0x08,
     487,   11,   11,   11, 0x08,
     523,   11,   11,   11, 0x08,
     546,   11,   11,   11, 0x08,
     562,   11,   11,   11, 0x08,
     579,   11,   11,   11, 0x08,
     598,   11,   11,   11, 0x08,
     623,  616,   11,   11, 0x08,
     668,  658,   11,   11, 0x08,
     722,   11,   11,   11, 0x08,
     762,  752,   11,   11, 0x08,
     790,   11,   11,   11, 0x08,
     815,   11,   11,   11, 0x08,
     839,   11,   11,   11, 0x08,
     859,   11,   11,   11, 0x08,
     873,   11,   11,   11, 0x08,
     891,   11,   11,   11, 0x08,
     931,  923,   11,   11, 0x08,
     956,   11,   11,   11, 0x08,
     971,   11,   11,   11, 0x08,
     983,   11,   11,   11, 0x08,
     998,   11,   11,   11, 0x08,
    1019,   11,   11,   11, 0x08,
    1051, 1049,   11,   11, 0x08,
    1073,   11,   11,   11, 0x08,
    1099,   11,   11,   11, 0x08,
    1126,   11,   11,   11, 0x08,
    1154,   11,   11,   11, 0x08,
    1187, 1183,   11,   11, 0x08,
    1206,   11,   11,   11, 0x08,
    1237,  923,   11,   11, 0x08,
    1273,   11,   11,   11, 0x08,
    1296,  923,   11,   11, 0x08,
    1327,   11,   11,   11, 0x08,
    1343,   11,   11,   11, 0x08,
    1357,   11,   11,   11, 0x08,
    1381,   11,   11,   11, 0x08,
    1404,   11,   11,   11, 0x08,
    1430,   11,   11,   11, 0x08,
    1455,   11,   11,   11, 0x08,
    1489,   11,   11,   11, 0x08,
    1523,   11,   11,   11, 0x08,
    1578, 1558, 1549,   11, 0x08,
    1638, 1618,   11,   11, 0x08,
    1674,   11,   11,   11, 0x08,
    1698,   11,   11,   11, 0x08,
    1729, 1723,   11,   11, 0x08,
    1769,  923,   11,   11, 0x08,
    1800,   11,   11,   11, 0x08,
    1835,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0operate(QString)\0"
    "txDataSignal()\0on_btnSerialOpenClose_clicked()\0"
    "on_btnForwardM_clicked()\0"
    "on_btnStopMotor_clicked()\0"
    "on_btnReverseM_clicked()\0"
    "on_btnParkSerachAntena_clicked()\0"
    "on_btnEmergencyStopMotor_clicked()\0"
    "on_btnSetFreq_clicked()\0on_btnSetAcc_clicked()\0"
    "on_btnSetDeAcc_clicked()\0"
    "readyDataSerialSerach()\0_msg,msg_ID\0"
    "TransmitMessage(QByteArray,quint8)\0"
    "uint16_t\0data,size\0"
    "gen_crc16_tx(const uint8_t*,uint16_t)\0"
    "buff,size\0CRC(uchar*,int)\0"
    "on_btnClearMaxData_clicked()\0timerTick()\0"
    "autoMoveManyCommandTimerTimerTick()\0"
    "autoUncheckTimerTick()\0TimerTestTick()\0"
    "TimerTest2Tick()\0ClosingTimerTick()\0"
    "SecondTimerTick()\0msg,dt\0"
    "parseMessage(QByteArray,QDateTime)\0"
    "_grph,X,Y\0"
    "setMainGraphData(int,QVector<double>,QVector<double>)\0"
    "on_btnResetMaxTable_clicked()\0_row,_col\0"
    "table_CellSelected(int,int)\0"
    "on_btnOpenFile_clicked()\0"
    "on_btnAnalyze_clicked()\0writeMaxArratTo3D()\0"
    "UpdateLists()\0mainUpdateLists()\0"
    "on_btnResetMaxTable_a_clicked()\0checked\0"
    "on_chkAuto_toggled(bool)\0forwardStyle()\0"
    "stopStyle()\0reverseStyle()\0"
    "on_btnTest_clicked()\0on_btnClearDiagrams_clicked()\0"
    "s\0errorString(QString&)\0"
    "on_btnForceExit_clicked()\0"
    "on_btnSimplePLot_clicked()\0"
    "on_btnSetAutoSpan_clicked()\0"
    "on_btnMaxPlotAnaGO_clicked()\0cnt\0"
    "maxPlotGoBack(int)\0on_btnMaxPlotAnaBack_clicked()\0"
    "on_rb_adc_EncoderPlot_toggled(bool)\0"
    "on_btn_test2_clicked()\0"
    "on_rb_LinearPlot_toggled(bool)\0"
    "ResetAllPlots()\0rcvDataSlot()\0"
    "on_btnHighSum_clicked()\0on_btnLowSum_clicked()\0"
    "on_btnHighDelta_clicked()\0"
    "on_btnLowDelta_clicked()\0"
    "on_btnloadtlefromfile_2_clicked()\0"
    "on_btnConvertTLETOLLA_2_clicked()\0"
    "on_btnpredict_3_clicked()\0VectorXd\0"
    "current,Line1,line2\0"
    "CalcVectorXd(QDateTime,QString,QString)\0"
    "line1,line2,satname\0"
    "PerdictSat(QString,QString,QString)\0"
    "on_pushButton_clicked()\0"
    "on_btnperedict_clicked()\0index\0"
    "on_comboBoxGPS_currentIndexChanged(int)\0"
    "on_rbSelectDelta_toggled(bool)\0"
    "on_btnsetFrequencyRotMCU_clicked()\0"
    "handleResults(QString)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->operate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->txDataSignal(); break;
        case 2: _t->on_btnSerialOpenClose_clicked(); break;
        case 3: _t->on_btnForwardM_clicked(); break;
        case 4: _t->on_btnStopMotor_clicked(); break;
        case 5: _t->on_btnReverseM_clicked(); break;
        case 6: _t->on_btnParkSerachAntena_clicked(); break;
        case 7: _t->on_btnEmergencyStopMotor_clicked(); break;
        case 8: _t->on_btnSetFreq_clicked(); break;
        case 9: _t->on_btnSetAcc_clicked(); break;
        case 10: _t->on_btnSetDeAcc_clicked(); break;
        case 11: _t->readyDataSerialSerach(); break;
        case 12: _t->TransmitMessage((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 13: { uint16_t _r = _t->gen_crc16_tx((*reinterpret_cast< const uint8_t*(*)>(_a[1])),(*reinterpret_cast< uint16_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< uint16_t*>(_a[0]) = _r; }  break;
        case 14: _t->CRC((*reinterpret_cast< uchar*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->on_btnClearMaxData_clicked(); break;
        case 16: _t->timerTick(); break;
        case 17: _t->autoMoveManyCommandTimerTimerTick(); break;
        case 18: _t->autoUncheckTimerTick(); break;
        case 19: _t->TimerTestTick(); break;
        case 20: _t->TimerTest2Tick(); break;
        case 21: _t->ClosingTimerTick(); break;
        case 22: _t->SecondTimerTick(); break;
        case 23: _t->parseMessage((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QDateTime(*)>(_a[2]))); break;
        case 24: _t->setMainGraphData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVector<double>(*)>(_a[2])),(*reinterpret_cast< QVector<double>(*)>(_a[3]))); break;
        case 25: _t->on_btnResetMaxTable_clicked(); break;
        case 26: _t->table_CellSelected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 27: _t->on_btnOpenFile_clicked(); break;
        case 28: _t->on_btnAnalyze_clicked(); break;
        case 29: _t->writeMaxArratTo3D(); break;
        case 30: _t->UpdateLists(); break;
        case 31: _t->mainUpdateLists(); break;
        case 32: _t->on_btnResetMaxTable_a_clicked(); break;
        case 33: _t->on_chkAuto_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->forwardStyle(); break;
        case 35: _t->stopStyle(); break;
        case 36: _t->reverseStyle(); break;
        case 37: _t->on_btnTest_clicked(); break;
        case 38: _t->on_btnClearDiagrams_clicked(); break;
        case 39: _t->errorString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 40: _t->on_btnForceExit_clicked(); break;
        case 41: _t->on_btnSimplePLot_clicked(); break;
        case 42: _t->on_btnSetAutoSpan_clicked(); break;
        case 43: _t->on_btnMaxPlotAnaGO_clicked(); break;
        case 44: _t->maxPlotGoBack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 45: _t->on_btnMaxPlotAnaBack_clicked(); break;
        case 46: _t->on_rb_adc_EncoderPlot_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 47: _t->on_btn_test2_clicked(); break;
        case 48: _t->on_rb_LinearPlot_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 49: _t->ResetAllPlots(); break;
        case 50: _t->rcvDataSlot(); break;
        case 51: _t->on_btnHighSum_clicked(); break;
        case 52: _t->on_btnLowSum_clicked(); break;
        case 53: _t->on_btnHighDelta_clicked(); break;
        case 54: _t->on_btnLowDelta_clicked(); break;
        case 55: _t->on_btnloadtlefromfile_2_clicked(); break;
        case 56: _t->on_btnConvertTLETOLLA_2_clicked(); break;
        case 57: _t->on_btnpredict_3_clicked(); break;
        case 58: { VectorXd _r = _t->CalcVectorXd((*reinterpret_cast< QDateTime(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< VectorXd*>(_a[0]) = _r; }  break;
        case 59: _t->PerdictSat((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 60: _t->on_pushButton_clicked(); break;
        case 61: _t->on_btnperedict_clicked(); break;
        case 62: _t->on_comboBoxGPS_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->on_rbSelectDelta_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 64: _t->on_btnsetFrequencyRotMCU_clicked(); break;
        case 65: _t->handleResults((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 66)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 66;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::operate(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::txDataSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
