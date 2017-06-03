/****************************************************************************
** Meta object code from reading C++ file 'modelcalibrationpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Silverapp/modelcalibrationpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modelcalibrationpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModelCalibrationPanel_t {
    QByteArrayData data[20];
    char stringdata0[458];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModelCalibrationPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModelCalibrationPanel_t qt_meta_stringdata_ModelCalibrationPanel = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ModelCalibrationPanel"
QT_MOC_LITERAL(1, 22, 25), // "virtualOrientationChanged"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 18), // "Eigen::Quaterniond"
QT_MOC_LITERAL(4, 68, 13), // "Q_virtual_new"
QT_MOC_LITERAL(5, 82, 32), // "initialSensorOrientationsChanged"
QT_MOC_LITERAL(6, 115, 32), // "std::array<Eigen::Quaterniond,7>"
QT_MOC_LITERAL(7, 148, 17), // "Q_sensors_ref_new"
QT_MOC_LITERAL(8, 166, 19), // "compensationChanged"
QT_MOC_LITERAL(9, 186, 12), // "Q_compensate"
QT_MOC_LITERAL(10, 199, 20), // "viewportResetClicked"
QT_MOC_LITERAL(11, 220, 23), // "viewportSagittalClicked"
QT_MOC_LITERAL(12, 244, 16), // "updateReferences"
QT_MOC_LITERAL(13, 261, 13), // "Q_sensors_raw"
QT_MOC_LITERAL(14, 275, 28), // "on_saveFrontalButton_clicked"
QT_MOC_LITERAL(15, 304, 29), // "on_saveMountingButton_clicked"
QT_MOC_LITERAL(16, 334, 24), // "on_saveAllButton_clicked"
QT_MOC_LITERAL(17, 359, 33), // "on_saveCompensationButton_cli..."
QT_MOC_LITERAL(18, 393, 30), // "on_resetViewportButton_clicked"
QT_MOC_LITERAL(19, 424, 33) // "on_sagittalViewportButton_cli..."

    },
    "ModelCalibrationPanel\0virtualOrientationChanged\0"
    "\0Eigen::Quaterniond\0Q_virtual_new\0"
    "initialSensorOrientationsChanged\0"
    "std::array<Eigen::Quaterniond,7>\0"
    "Q_sensors_ref_new\0compensationChanged\0"
    "Q_compensate\0viewportResetClicked\0"
    "viewportSagittalClicked\0updateReferences\0"
    "Q_sensors_raw\0on_saveFrontalButton_clicked\0"
    "on_saveMountingButton_clicked\0"
    "on_saveAllButton_clicked\0"
    "on_saveCompensationButton_clicked\0"
    "on_resetViewportButton_clicked\0"
    "on_sagittalViewportButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelCalibrationPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,
       8,    1,   80,    2, 0x06 /* Public */,
      10,    0,   83,    2, 0x06 /* Public */,
      11,    0,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   85,    2, 0x0a /* Public */,
      14,    0,   88,    2, 0x0a /* Public */,
      15,    0,   89,    2, 0x0a /* Public */,
      16,    0,   90,    2, 0x0a /* Public */,
      17,    0,   91,    2, 0x0a /* Public */,
      18,    0,   92,    2, 0x0a /* Public */,
      19,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    9,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ModelCalibrationPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModelCalibrationPanel *_t = static_cast<ModelCalibrationPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->virtualOrientationChanged((*reinterpret_cast< const Eigen::Quaterniond(*)>(_a[1]))); break;
        case 1: _t->initialSensorOrientationsChanged((*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[1]))); break;
        case 2: _t->compensationChanged((*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[1]))); break;
        case 3: _t->viewportResetClicked(); break;
        case 4: _t->viewportSagittalClicked(); break;
        case 5: _t->updateReferences((*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[1]))); break;
        case 6: _t->on_saveFrontalButton_clicked(); break;
        case 7: _t->on_saveMountingButton_clicked(); break;
        case 8: _t->on_saveAllButton_clicked(); break;
        case 9: _t->on_saveCompensationButton_clicked(); break;
        case 10: _t->on_resetViewportButton_clicked(); break;
        case 11: _t->on_sagittalViewportButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ModelCalibrationPanel::*_t)(const Eigen::Quaterniond & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelCalibrationPanel::virtualOrientationChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ModelCalibrationPanel::*_t)(const std::array<Eigen::Quaterniond,7> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelCalibrationPanel::initialSensorOrientationsChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ModelCalibrationPanel::*_t)(const std::array<Eigen::Quaterniond,7> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelCalibrationPanel::compensationChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ModelCalibrationPanel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelCalibrationPanel::viewportResetClicked)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ModelCalibrationPanel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelCalibrationPanel::viewportSagittalClicked)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject ModelCalibrationPanel::staticMetaObject = {
    { &QPanel::staticMetaObject, qt_meta_stringdata_ModelCalibrationPanel.data,
      qt_meta_data_ModelCalibrationPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModelCalibrationPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelCalibrationPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModelCalibrationPanel.stringdata0))
        return static_cast<void*>(const_cast< ModelCalibrationPanel*>(this));
    return QPanel::qt_metacast(_clname);
}

int ModelCalibrationPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPanel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ModelCalibrationPanel::virtualOrientationChanged(const Eigen::Quaterniond & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModelCalibrationPanel::initialSensorOrientationsChanged(const std::array<Eigen::Quaterniond,7> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ModelCalibrationPanel::compensationChanged(const std::array<Eigen::Quaterniond,7> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ModelCalibrationPanel::viewportResetClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void ModelCalibrationPanel::viewportSagittalClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
