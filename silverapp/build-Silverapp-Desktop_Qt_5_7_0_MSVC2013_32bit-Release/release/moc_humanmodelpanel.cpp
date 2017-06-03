/****************************************************************************
** Meta object code from reading C++ file 'humanmodelpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Silverapp/humanmodelpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'humanmodelpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HumanModelPanel_t {
    QByteArrayData data[14];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HumanModelPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HumanModelPanel_t qt_meta_stringdata_HumanModelPanel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "HumanModelPanel"
QT_MOC_LITERAL(1, 16, 11), // "updateModel"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 32), // "std::array<Eigen::Quaterniond,7>"
QT_MOC_LITERAL(4, 62, 14), // "Q_segments_new"
QT_MOC_LITERAL(5, 77, 32), // "std::array<Eigen::Quaterniond,6>"
QT_MOC_LITERAL(6, 110, 12), // "Q_joints_new"
QT_MOC_LITERAL(7, 123, 16), // "debugCalibration"
QT_MOC_LITERAL(8, 140, 18), // "Eigen::Quaterniond"
QT_MOC_LITERAL(9, 159, 9), // "Q_virtual"
QT_MOC_LITERAL(10, 169, 13), // "Q_sensors_raw"
QT_MOC_LITERAL(11, 183, 13), // "Q_sensors_ref"
QT_MOC_LITERAL(12, 197, 13), // "resetViewport"
QT_MOC_LITERAL(13, 211, 16) // "sagittalViewport"

    },
    "HumanModelPanel\0updateModel\0\0"
    "std::array<Eigen::Quaterniond,7>\0"
    "Q_segments_new\0std::array<Eigen::Quaterniond,6>\0"
    "Q_joints_new\0debugCalibration\0"
    "Eigen::Quaterniond\0Q_virtual\0Q_sensors_raw\0"
    "Q_sensors_ref\0resetViewport\0"
    "sagittalViewport"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HumanModelPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x0a /* Public */,
       7,    3,   39,    2, 0x0a /* Public */,
      12,    0,   46,    2, 0x0a /* Public */,
      13,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 3, 0x80000000 | 3,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HumanModelPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HumanModelPanel *_t = static_cast<HumanModelPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateModel((*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[1])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,6>(*)>(_a[2]))); break;
        case 1: _t->debugCalibration((*reinterpret_cast< const Eigen::Quaterniond(*)>(_a[1])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[2])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[3]))); break;
        case 2: _t->resetViewport(); break;
        case 3: _t->sagittalViewport(); break;
        default: ;
        }
    }
}

const QMetaObject HumanModelPanel::staticMetaObject = {
    { &QTOgreWindow::staticMetaObject, qt_meta_stringdata_HumanModelPanel.data,
      qt_meta_data_HumanModelPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HumanModelPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HumanModelPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HumanModelPanel.stringdata0))
        return static_cast<void*>(const_cast< HumanModelPanel*>(this));
    return QTOgreWindow::qt_metacast(_clname);
}

int HumanModelPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTOgreWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
