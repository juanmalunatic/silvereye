/****************************************************************************
** Meta object code from reading C++ file 'systemstatuspanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Silverapp/systemstatuspanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemstatuspanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SystemStatusPanel_t {
    QByteArrayData data[5];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SystemStatusPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SystemStatusPanel_t qt_meta_stringdata_SystemStatusPanel = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SystemStatusPanel"
QT_MOC_LITERAL(1, 18, 24), // "refreshWithNewSensorData"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 21), // "std::array<ImuData,7>"
QT_MOC_LITERAL(4, 66, 7) // "newData"

    },
    "SystemStatusPanel\0refreshWithNewSensorData\0"
    "\0std::array<ImuData,7>\0newData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SystemStatusPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void SystemStatusPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SystemStatusPanel *_t = static_cast<SystemStatusPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refreshWithNewSensorData((*reinterpret_cast< const std::array<ImuData,7>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SystemStatusPanel::staticMetaObject = {
    { &QPanel::staticMetaObject, qt_meta_stringdata_SystemStatusPanel.data,
      qt_meta_data_SystemStatusPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SystemStatusPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemStatusPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SystemStatusPanel.stringdata0))
        return static_cast<void*>(const_cast< SystemStatusPanel*>(this));
    return QPanel::qt_metacast(_clname);
}

int SystemStatusPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPanel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
