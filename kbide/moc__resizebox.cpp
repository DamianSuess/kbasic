/****************************************************************************
** Meta object code from reading C++ file '_resizebox.h'
**
** Created: Sat May 2 08:05:55 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_resizebox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_resizebox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__resizebox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      30,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__resizebox[] = {
    "_resizebox\0\0frameChanged(int)\0"
    "cursoranimation_frameChanged(int)\0"
};

const QMetaObject _resizebox::staticMetaObject = {
    { &QSizeGrip::staticMetaObject, qt_meta_stringdata__resizebox,
      qt_meta_data__resizebox, 0 }
};

const QMetaObject *_resizebox::metaObject() const
{
    return &staticMetaObject;
}

void *_resizebox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__resizebox))
        return static_cast<void*>(const_cast< _resizebox*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _resizebox*>(this));
    return QSizeGrip::qt_metacast(_clname);
}

int _resizebox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSizeGrip::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
