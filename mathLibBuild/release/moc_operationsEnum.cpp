/****************************************************************************
** Meta object code from reading C++ file 'operationsEnum.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mLib/operationsEnum.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'operationsEnum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Operation_t {
    QByteArrayData data[8];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operation_t qt_meta_stringdata_Operation = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Operation"
QT_MOC_LITERAL(1, 10, 9), // "operation"
QT_MOC_LITERAL(2, 20, 3), // "SUM"
QT_MOC_LITERAL(3, 24, 3), // "SUB"
QT_MOC_LITERAL(4, 28, 3), // "DIV"
QT_MOC_LITERAL(5, 32, 3), // "MUL"
QT_MOC_LITERAL(6, 36, 3), // "RST"
QT_MOC_LITERAL(7, 40, 4) // "NOOP"

    },
    "Operation\0operation\0SUM\0SUB\0DIV\0MUL\0"
    "RST\0NOOP"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x2,    6,   19,

 // enum data: key, value
       2, uint(Operation::operation::SUM),
       3, uint(Operation::operation::SUB),
       4, uint(Operation::operation::DIV),
       5, uint(Operation::operation::MUL),
       6, uint(Operation::operation::RST),
       7, uint(Operation::operation::NOOP),

       0        // eod
};

void Operation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Operation::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Operation.data,
    qt_meta_data_Operation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Operation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Operation.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Operation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
