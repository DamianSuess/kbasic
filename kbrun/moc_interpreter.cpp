/****************************************************************************
** Meta object code from reading C++ file 'interpreter.h'
**
** Created: Fri May 1 19:07:34 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "interpreter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interpreter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__ontimer[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__ontimer[] = {
    "_ontimer\0\0onTimer()\0"
};

const QMetaObject _ontimer::staticMetaObject = {
    { &QTimer::staticMetaObject, qt_meta_stringdata__ontimer,
      qt_meta_data__ontimer, 0 }
};

const QMetaObject *_ontimer::metaObject() const
{
    return &staticMetaObject;
}

void *_ontimer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__ontimer))
        return static_cast<void*>(const_cast< _ontimer*>(this));
    return QTimer::qt_metacast(_clname);
}

int _ontimer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTimer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onTimer(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_interpreter[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_interpreter[] = {
    "interpreter\0"
};

const QMetaObject interpreter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_interpreter,
      qt_meta_data_interpreter, 0 }
};

const QMetaObject *interpreter::metaObject() const
{
    return &staticMetaObject;
}

void *interpreter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_interpreter))
        return static_cast<void*>(const_cast< interpreter*>(this));
    return QObject::qt_metacast(_clname);
}

int interpreter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
