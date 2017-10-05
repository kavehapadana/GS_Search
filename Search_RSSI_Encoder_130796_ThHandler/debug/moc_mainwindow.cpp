/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Aug 28 11:23:46 2017
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
      51,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   11,   11,   11, 0x08,
      61,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,
     112,   11,   11,   11, 0x08,
     137,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     205,   11,   11,   11, 0x08,
     229,   11,   11,   11, 0x08,
     252,   11,   11,   11, 0x08,
     277,   11,   11,   11, 0x08,
     313,  301,   11,   11, 0x08,
     358,  353,  348,   11, 0x08,
     383,   11,   11,   11, 0x08,
     408,  398,   11,   11, 0x08,
     424,   11,   11,   11, 0x08,
     452,   11,   11,   11, 0x08,
     481,   11,   11,   11, 0x08,
     493,   11,   11,   11, 0x08,
     529,   11,   11,   11, 0x08,
     552,   11,   11,   11, 0x08,
     568,   11,   11,   11, 0x08,
     585,   11,   11,   11, 0x08,
     604,   11,   11,   11, 0x08,
     622,   11,   11,   11, 0x08,
     647,   11,   11,   11, 0x08,
     687,  677,   11,   11, 0x08,
     715,   11,   11,   11, 0x08,
     740,   11,   11,   11, 0x08,
     764,   11,   11,   11, 0x08,
     784,   11,   11,   11, 0x08,
     798,   11,   11,   11, 0x08,
     816,   11,   11,   11, 0x08,
     856,  848,   11,   11, 0x08,
     881,   11,   11,   11, 0x08,
     896,   11,   11,   11, 0x08,
     908,   11,   11,   11, 0x08,
     923,   11,   11,   11, 0x08,
     944,   11,   11,   11, 0x08,
     976,  974,   11,   11, 0x08,
     998,   11,   11,   11, 0x08,
    1024,   11,   11,   11, 0x08,
    1051,   11,   11,   11, 0x08,
    1079,   11,   11,   11, 0x08,
    1112, 1108,   11,   11, 0x08,
    1131,   11,   11,   11, 0x08,
    1162,  848,   11,   11, 0x08,
    1198,   11,   11,   11, 0x08,
    1221,  848,   11,   11, 0x08,
    1252,   11,   11,   11, 0x08,
    1268,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0operate(QString)\0"
    "on_btnSerialOpenClose_clicked()\0"
    "on_btnForwardM_clicked()\0"
    "on_btnStopMotor_clicked()\0"
    "on_btnReverseM_clicked()\0"
    "on_btnParkSerachAntena_clicked()\0"
    "on_btnEmergencyStopMotor_clicked()\0"
    "on_btnSetFreq_clicked()\0on_btnSetAcc_clicked()\0"
    "on_btnSetDeAcc_clicked()\0"
    "readyDataSerialSerach()\0_msg,msg_ID\0"
    "TransmitMessage(QByteArray,quint8)\0"
    "char\0Data\0parseByte(unsigned char)\0"
    "parseMessage()\0buff,size\0CRC(uchar*,int)\0"
    "on_btn_MCU_Detect_clicked()\0"
    "on_btnClearMaxData_clicked()\0timerTick()\0"
    "autoMoveManyCommandTimerTimerTick()\0"
    "autoUncheckTimerTick()\0TimerTestTick()\0"
    "TimerTest2Tick()\0ClosingTimerTick()\0"
    "SecondTimerTick()\0on_btnResetDup_clicked()\0"
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
    "ResetAllPlots()\0handleResults(QString)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->operate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_btnSerialOpenClose_clicked(); break;
        case 2: _t->on_btnForwardM_clicked(); break;
        case 3: _t->on_btnStopMotor_clicked(); break;
        case 4: _t->on_btnReverseM_clicked(); break;
        case 5: _t->on_btnParkSerachAntena_clicked(); break;
        case 6: _t->on_btnEmergencyStopMotor_clicked(); break;
        case 7: _t->on_btnSetFreq_clicked(); break;
        case 8: _t->on_btnSetAcc_clicked(); break;
        case 9: _t->on_btnSetDeAcc_clicked(); break;
        case 10: _t->readyDataSerialSerach(); break;
        case 11: _t->TransmitMessage((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 12: { char _r = _t->parseByte((*reinterpret_cast< unsigned char(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< char*>(_a[0]) = _r; }  break;
        case 13: _t->parseMessage(); break;
        case 14: _t->CRC((*reinterpret_cast< uchar*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->on_btn_MCU_Detect_clicked(); break;
        case 16: _t->on_btnClearMaxData_clicked(); break;
        case 17: _t->timerTick(); break;
        case 18: _t->autoMoveManyCommandTimerTimerTick(); break;
        case 19: _t->autoUncheckTimerTick(); break;
        case 20: _t->TimerTestTick(); break;
        case 21: _t->TimerTest2Tick(); break;
        case 22: _t->ClosingTimerTick(); break;
        case 23: _t->SecondTimerTick(); break;
        case 24: _t->on_btnResetDup_clicked(); break;
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
        case 50: _t->handleResults((*reinterpret_cast< const QString(*)>(_a[1]))); break;
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
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::operate(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
