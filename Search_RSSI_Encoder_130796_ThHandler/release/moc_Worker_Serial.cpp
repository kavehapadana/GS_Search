/****************************************************************************
** Meta object code from reading C++ file 'Worker_Serial.h'
**
** Created: Fri Oct 6 21:17:55 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/Worker_Serial.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Worker_Serial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Worker_Serial[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      26,   14,   14,   14, 0x05,
      46,   42,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   14,   14,   14, 0x0a,
      71,   14,   14,   14, 0x0a,
      83,   14,   14,   14, 0x0a,
     106,  101,   96,   14, 0x08,
     150,  140,  131,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Worker_Serial[] = {
    "Worker_Serial\0\0finished()\0rcvDataSignal()\0"
    "err\0error(QString)\0process()\0readyData()\0"
    "txDataSlot()\0char\0Data\0parseByte(unsigned char)\0"
    "uint16_t\0data,size\0"
    "gen_crc16(const uint8_t*,uint16_t)\0"
};

void Worker_Serial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Worker_Serial *_t = static_cast<Worker_Serial *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->rcvDataSignal(); break;
        case 2: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->process(); break;
        case 4: _t->readyData(); break;
        case 5: _t->txDataSlot(); break;
        case 6: { char _r = _t->parseByte((*reinterpret_cast< unsigned char(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< char*>(_a[0]) = _r; }  break;
        case 7: { uint16_t _r = _t->gen_crc16((*reinterpret_cast< const uint8_t*(*)>(_a[1])),(*reinterpret_cast< uint16_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< uint16_t*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Worker_Serial::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Worker_Serial::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Worker_Serial,
      qt_meta_data_Worker_Serial, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Worker_Serial::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Worker_Serial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Worker_Serial::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Worker_Serial))
        return static_cast<void*>(const_cast< Worker_Serial*>(this));
    return QObject::qt_metacast(_clname);
}

int Worker_Serial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Worker_Serial::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Worker_Serial::rcvDataSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Worker_Serial::error(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
