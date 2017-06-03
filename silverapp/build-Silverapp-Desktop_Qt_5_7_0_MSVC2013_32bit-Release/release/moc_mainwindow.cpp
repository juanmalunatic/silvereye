/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Silverapp/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[43];
    char stringdata0[819];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "sensorDataChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 21), // "std::array<ImuData,7>"
QT_MOC_LITERAL(4, 52, 14), // "currSensorData"
QT_MOC_LITERAL(5, 67, 21), // "quaternionDataChanged"
QT_MOC_LITERAL(6, 89, 32), // "std::array<Eigen::Quaterniond,7>"
QT_MOC_LITERAL(7, 122, 13), // "Q_sensors_raw"
QT_MOC_LITERAL(8, 136, 24), // "segmentsAndJointsChanged"
QT_MOC_LITERAL(9, 161, 14), // "Q_segments_new"
QT_MOC_LITERAL(10, 176, 32), // "std::array<Eigen::Quaterniond,6>"
QT_MOC_LITERAL(11, 209, 12), // "Q_joints_new"
QT_MOC_LITERAL(12, 222, 13), // "anglesChanged"
QT_MOC_LITERAL(13, 236, 15), // "QVector<double>"
QT_MOC_LITERAL(14, 252, 10), // "angles_new"
QT_MOC_LITERAL(15, 263, 16), // "debugCalibration"
QT_MOC_LITERAL(16, 280, 18), // "Eigen::Quaterniond"
QT_MOC_LITERAL(17, 299, 9), // "Q_virtual"
QT_MOC_LITERAL(18, 309, 13), // "Q_sensors_ref"
QT_MOC_LITERAL(19, 323, 17), // "kinematicsChanged"
QT_MOC_LITERAL(20, 341, 15), // "sagittal_angles"
QT_MOC_LITERAL(21, 357, 9), // "quats_raw"
QT_MOC_LITERAL(22, 367, 14), // "quats_segments"
QT_MOC_LITERAL(23, 382, 12), // "quats_joints"
QT_MOC_LITERAL(24, 395, 15), // "disconnectPanel"
QT_MOC_LITERAL(25, 411, 7), // "QPanel*"
QT_MOC_LITERAL(26, 419, 5), // "Panel"
QT_MOC_LITERAL(27, 425, 17), // "processSerialData"
QT_MOC_LITERAL(28, 443, 13), // "newSensorData"
QT_MOC_LITERAL(29, 457, 29), // "on_systemStatusButton_clicked"
QT_MOC_LITERAL(30, 487, 26), // "on_recordRawButton_clicked"
QT_MOC_LITERAL(31, 514, 31), // "on_serialSettingsButton_clicked"
QT_MOC_LITERAL(32, 546, 33), // "on_modelCalibrationButton_cli..."
QT_MOC_LITERAL(33, 580, 27), // "on_humanModelButton_clicked"
QT_MOC_LITERAL(34, 608, 31), // "on_sagittalAnglesButton_clicked"
QT_MOC_LITERAL(35, 640, 33), // "on_recordKinematicsButton_cli..."
QT_MOC_LITERAL(36, 674, 23), // "updateSegmentsAndJoints"
QT_MOC_LITERAL(37, 698, 24), // "updateVirtualOrientation"
QT_MOC_LITERAL(38, 723, 13), // "Q_virtual_new"
QT_MOC_LITERAL(39, 737, 31), // "updateInitialSensorOrientations"
QT_MOC_LITERAL(40, 769, 17), // "Q_sensors_ref_new"
QT_MOC_LITERAL(41, 787, 18), // "updateCompensation"
QT_MOC_LITERAL(42, 806, 12) // "Q_compensate"

    },
    "MainWindow\0sensorDataChanged\0\0"
    "std::array<ImuData,7>\0currSensorData\0"
    "quaternionDataChanged\0"
    "std::array<Eigen::Quaterniond,7>\0"
    "Q_sensors_raw\0segmentsAndJointsChanged\0"
    "Q_segments_new\0std::array<Eigen::Quaterniond,6>\0"
    "Q_joints_new\0anglesChanged\0QVector<double>\0"
    "angles_new\0debugCalibration\0"
    "Eigen::Quaterniond\0Q_virtual\0Q_sensors_ref\0"
    "kinematicsChanged\0sagittal_angles\0"
    "quats_raw\0quats_segments\0quats_joints\0"
    "disconnectPanel\0QPanel*\0Panel\0"
    "processSerialData\0newSensorData\0"
    "on_systemStatusButton_clicked\0"
    "on_recordRawButton_clicked\0"
    "on_serialSettingsButton_clicked\0"
    "on_modelCalibrationButton_clicked\0"
    "on_humanModelButton_clicked\0"
    "on_sagittalAnglesButton_clicked\0"
    "on_recordKinematicsButton_clicked\0"
    "updateSegmentsAndJoints\0"
    "updateVirtualOrientation\0Q_virtual_new\0"
    "updateInitialSensorOrientations\0"
    "Q_sensors_ref_new\0updateCompensation\0"
    "Q_compensate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       5,    1,  112,    2, 0x06 /* Public */,
       8,    2,  115,    2, 0x06 /* Public */,
      12,    1,  120,    2, 0x06 /* Public */,
      15,    3,  123,    2, 0x06 /* Public */,
      19,    4,  130,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    1,  139,    2, 0x08 /* Private */,
      27,    1,  142,    2, 0x08 /* Private */,
      29,    0,  145,    2, 0x08 /* Private */,
      30,    0,  146,    2, 0x08 /* Private */,
      31,    0,  147,    2, 0x08 /* Private */,
      32,    0,  148,    2, 0x08 /* Private */,
      33,    0,  149,    2, 0x08 /* Private */,
      34,    0,  150,    2, 0x08 /* Private */,
      35,    0,  151,    2, 0x08 /* Private */,
      36,    0,  152,    2, 0x08 /* Private */,
      37,    1,  153,    2, 0x0a /* Public */,
      39,    1,  156,    2, 0x0a /* Public */,
      41,    1,  159,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 10,    9,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 6, 0x80000000 | 6,   17,    7,   18,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 6, 0x80000000 | 6, 0x80000000 | 10,   20,   21,   22,   23,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, QMetaType::QByteArray,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   38,
    QMetaType::Void, 0x80000000 | 6,   40,
    QMetaType::Void, 0x80000000 | 6,   42,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sensorDataChanged((*reinterpret_cast< const std::array<ImuData,7>(*)>(_a[1]))); break;
        case 1: _t->quaternionDataChanged((*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[1]))); break;
        case 2: _t->segmentsAndJointsChanged((*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[1])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,6>(*)>(_a[2]))); break;
        case 3: _t->anglesChanged((*reinterpret_cast< const QVector<double>(*)>(_a[1]))); break;
        case 4: _t->debugCalibration((*reinterpret_cast< const Eigen::Quaterniond(*)>(_a[1])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[2])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[3]))); break;
        case 5: _t->kinematicsChanged((*reinterpret_cast< const QVector<double>(*)>(_a[1])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[2])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[3])),(*reinterpret_cast< const std::array<Eigen::Quaterniond,6>(*)>(_a[4]))); break;
        case 6: _t->disconnectPanel((*reinterpret_cast< QPanel*(*)>(_a[1]))); break;
        case 7: _t->processSerialData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 8: _t->on_systemStatusButton_clicked(); break;
        case 9: _t->on_recordRawButton_clicked(); break;
        case 10: _t->on_serialSettingsButton_clicked(); break;
        case 11: _t->on_modelCalibrationButton_clicked(); break;
        case 12: _t->on_humanModelButton_clicked(); break;
        case 13: _t->on_sagittalAnglesButton_clicked(); break;
        case 14: _t->on_recordKinematicsButton_clicked(); break;
        case 15: _t->updateSegmentsAndJoints(); break;
        case 16: _t->updateVirtualOrientation((*reinterpret_cast< const Eigen::Quaterniond(*)>(_a[1]))); break;
        case 17: _t->updateInitialSensorOrientations((*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[1]))); break;
        case 18: _t->updateCompensation((*reinterpret_cast< const std::array<Eigen::Quaterniond,7>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QPanel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(const std::array<ImuData,7> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sensorDataChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const std::array<Eigen::Quaterniond,7> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::quaternionDataChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const std::array<Eigen::Quaterniond,7> & , const std::array<Eigen::Quaterniond,6> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::segmentsAndJointsChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const QVector<double> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::anglesChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const Eigen::Quaterniond & , const std::array<Eigen::Quaterniond,7> & , const std::array<Eigen::Quaterniond,7> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::debugCalibration)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const QVector<double> & , const std::array<Eigen::Quaterniond,7> & , const std::array<Eigen::Quaterniond,7> & , const std::array<Eigen::Quaterniond,6> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::kinematicsChanged)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sensorDataChanged(const std::array<ImuData,7> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::quaternionDataChanged(const std::array<Eigen::Quaterniond,7> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::segmentsAndJointsChanged(const std::array<Eigen::Quaterniond,7> & _t1, const std::array<Eigen::Quaterniond,6> & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::anglesChanged(const QVector<double> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::debugCalibration(const Eigen::Quaterniond & _t1, const std::array<Eigen::Quaterniond,7> & _t2, const std::array<Eigen::Quaterniond,7> & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::kinematicsChanged(const QVector<double> & _t1, const std::array<Eigen::Quaterniond,7> & _t2, const std::array<Eigen::Quaterniond,7> & _t3, const std::array<Eigen::Quaterniond,6> & _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
