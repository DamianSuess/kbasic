/****************************************************************************
** Meta object code from reading C++ file '_toolbaritem.h'
**
** Created: Sat May 2 08:07:49 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_toolbaritem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_toolbaritem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__toolbaritem[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__toolbaritem[] = {
    "_toolbaritem\0\0frameChanged(int)\0"
};

const QMetaObject _toolbaritem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata__toolbaritem,
      qt_meta_data__toolbaritem, 0 }
};

const QMetaObject *_toolbaritem::metaObject() const
{
    return &staticMetaObject;
}

void *_toolbaritem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__toolbaritem))
        return static_cast<void*>(const_cast< _toolbaritem*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _toolbaritem*>(this));
    return QObject::qt_metacast(_clname);
}

int _toolbaritem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
