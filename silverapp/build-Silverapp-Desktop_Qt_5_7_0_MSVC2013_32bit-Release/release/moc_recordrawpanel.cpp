/****************************************************************************
** Meta object code from reading C++ file 'recordrawpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Silverapp/recordrawpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recordrawpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RecordRawPanel_t {
    QByteArrayData data[10];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordRawPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordRawPanel_t qt_meta_stringdata_RecordRawPanel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RecordRawPanel"
QT_MOC_LITERAL(1, 15, 23), // "on_FolderButton_clicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 21), // "on_FileButton_clicked"
QT_MOC_LITERAL(4, 62, 27), // "on_FileLineEdit_textChanged"
QT_MOC_LITERAL(5, 90, 4), // "arg1"
QT_MOC_LITERAL(6, 95, 23), // "on_RecordButton_clicked"
QT_MOC_LITERAL(7, 119, 20), // "streamDataToOpenFile"
QT_MOC_LITERAL(8, 140, 21), // "std::array<ImuData,7>"
QT_MOC_LITERAL(9, 162, 7) // "newData"

    },
    "RecordRawPanel\0on_FolderButton_clicked\0"
    "\0on_FileButton_clicked\0"
    "on_FileLineEdit_textChanged\0arg1\0"
    "on_RecordButton_clicked\0streamDataToOpenFile\0"
    "std::array<ImuData,7>\0newData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordRawPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    1,   41,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    1,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void RecordRawPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RecordRawPanel *_t = static_cast<RecordRawPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_FolderButton_clicked(); break;
        case 1: _t->on_FileButton_clicked(); break;
        case 2: _t->on_FileLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_RecordButton_clicked(); break;
        case 4: _t->streamDataToOpenFile((*reinterpret_cast< const std::array<ImuData,7>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject RecordRawPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RecordRawPanel.data,
      qt_meta_data_RecordRawPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RecordRawPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordRawPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RecordRawPanel.stringdata0))
        return static_cast<void*>(const_cast< RecordRawPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int RecordRawPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
