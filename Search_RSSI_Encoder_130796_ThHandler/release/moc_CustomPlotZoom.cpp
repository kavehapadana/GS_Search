/****************************************************************************
** Meta object code from reading C++ file 'CustomPlotZoom.h'
**
** Created: Fri Oct 6 21:17:54 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/CustomPlotZoom.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomPlotZoom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomPlotZoom[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x08,
      52,   16,   15,   15, 0x08,
      81,   16,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CustomPlotZoom[] = {
    "CustomPlotZoom\0\0event\0"
    "mousePressEvent(QMouseEvent*)\0"
    "mouseMoveEvent(QMouseEvent*)\0"
    "mouseReleaseEvent(QMouseEvent*)\0"
};

void CustomPlotZoom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CustomPlotZoom *_t = static_cast<CustomPlotZoom *>(_o);
        switch (_id) {
        case 0: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CustomPlotZoom::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CustomPlotZoom::staticMetaObject = {
    { &QCustomPlot::staticMetaObject, qt_meta_stringdata_CustomPlotZoom,
      qt_meta_data_CustomPlotZoom, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CustomPlotZoom::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CustomPlotZoom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CustomPlotZoom::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomPlotZoom))
        return static_cast<void*>(const_cast< CustomPlotZoom*>(this));
    return QCustomPlot::qt_metacast(_clname);
}

int CustomPlotZoom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCustomPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
