/****************************************************************************
** Meta object code from reading C++ file '_toolbutton.h'
**
** Created: Sat May 2 08:08:06 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_toolbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_toolbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__toolbutton[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      28,   12,   12,   12, 0x0a,
      46,   44,   12,   12, 0x0a,
      67,   12,   12,   12, 0x0a,
      85,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__toolbutton[] = {
    "_toolbutton\0\0SoundOnEvent()\0EVENT_OnEvent()\0"
    "b\0EVENT_OnEvent2(bool)\0frameChanged(int)\0"
    "cursoranimation_frameChanged(int)\0"
};

const QMetaObject _toolbutton::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata__toolbutton,
      qt_meta_data__toolbutton, 0 }
};

const QMetaObject *_toolbutton::metaObject() const
{
    return &staticMetaObject;
}

void *_toolbutton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__toolbutton))
        return static_cast<void*>(const_cast< _toolbutton*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _toolbutton*>(this));
    return QToolButton::qt_metacast(_clname);
}

int _toolbutton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SoundOnEvent(); break;
        case 1: EVENT_OnEvent(); break;
        case 2: EVENT_OnEvent2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
