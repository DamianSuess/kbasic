/****************************************************************************
** Meta object code from reading C++ file '_header.h'
**
** Created: Sat May 2 08:01:05 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_header.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_header.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__header[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      25,    8,    8,    8, 0x0a,
      43,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__header[] = {
    "_header\0\0EVENT_OnEvent()\0frameChanged(int)\0"
    "cursoranimation_frameChanged(int)\0"
};

const QMetaObject _header::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata__header,
      qt_meta_data__header, 0 }
};

const QMetaObject *_header::metaObject() const
{
    return &staticMetaObject;
}

void *_header::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__header))
        return static_cast<void*>(const_cast< _header*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _header*>(this));
    return QPushButton::qt_metacast(_clname);
}

int _header::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: EVENT_OnEvent(); break;
        case 1: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
