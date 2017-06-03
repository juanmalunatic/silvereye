/****************************************************************************
** Meta object code from reading C++ file 'recordkinematicspanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Silverapp/recordkinematicspanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recordkinematicspanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RecordKinematicsPanel_t {
    QByteArrayData data[16];
    char stringdata0[299];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordKinematicsPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordKinematicsPanel_t qt_meta_stringdata_RecordKinematicsPanel = {
    {
QT_MOC_LITERAL(0, 0, 21), // "RecordKinematicsPanel"
QT_MOC_LITERAL(1, 22, 22), // "writeSignalsToOpenFile"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 15), // "QVector<double>"
QT_MOC_LITERAL(4, 62, 15), // "sagittal_angles"
QT_MOC_LITERAL(5, 78, 32), // "std::array<Eigen::Quaterniond,7>"
QT_MOC_LITERAL(6, 111, 9), // "quats_raw"
QT_MOC_LITERAL(7, 121, 14), // "quats_segments"
QT_MOC_LITERAL(8, 136, 32), // "std::array<Eigen::Quaterniond,6>"
QT_MOC_LITERAL(9, 169, 12), // "quats_joints"
QT_MOC_LITERAL(10, 182, 23), // "on_FolderButton_clicked"
QT_MOC_LITERAL(11, 206, 21), // "on_FileButton_clicked"
QT_MOC_LITERAL(12, 228, 27), // "on_FileLineEdit_textChanged"
QT_MOC_LITERAL(13, 256, 4), // "arg1"
QT_MOC_LITERAL(14, 261, 23), // "on_RecordButton_clicked"
QT_MOC_LITERAL(15, 285, 13) // "updateElapsed"

    },
    "RecordKinematicsPanel\0writeSignalsToOpenFile\0"
    "\0QVector<double>\0sagittal_angles\0"
    "std::array<Eigen::Quaterniond,7>\0"
    "quats_raw\0quats_segments\0"
    "std::array<Eigen::Quaterniond,6>\0"
    "quats_joints\0on_FolderButton_clicked\0"
    "on_FileButton_clicked\0on_FileLineEdit_textChanged\0"
    "arg1\0on_RecordButton_clicked\0updateElapsed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordKinematicsPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    4,   44,    2, 0x0a /* Public */,
      10,    0,   53,    2, 0x08 /* Private */,
      11,    0,   54,    2, 0x08 /* Private */,
      12,    1,   55,    2, 0x08 /* Private */,
      14,    0,   58,    2, 0x08 /* Private */,
      15,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 8,    4,    6,    7,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RecordKinematicsPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RecordKinematicsPanel *_t = static_cast<RecordKinematicsPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->writeSignalsToOpenFile((*reinterpret_cast< const QVector<double>(*)>(_a[1])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[2])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[3])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,6>(*)>(_a[4]))); break;
        case 1: _t->on_FolderButton_clicked(); break;
        case 2: _t->on_FileButton_clicked(); break;
        case 3: _t->on_FileLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_RecordButton_clicked(); break;
        case 5: _t->updateElapsed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    }
}

const QMetaObject RecordKinematicsPanel::staticMetaObject = {
    { &QPanel::staticMetaObject, qt_meta_stringdata_RecordKinematicsPanel.data,
      qt_meta_data_RecordKinematicsPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RecordKinematicsPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordKinematicsPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RecordKinematicsPanel.stringdata0))
        return static_cast<void*>(const_cast< RecordKinematicsPanel*>(this));
    return QPanel::qt_metacast(_clname);
}

int RecordKinematicsPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPanel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
