/****************************************************************************
** Meta object code from reading C++ file '_commandbutton.h'
**
** Created: Fri May 1 19:09:15 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_commandbutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_commandbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__commandbutton[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      31,   15,   15,   15, 0x0a,
      49,   47,   15,   15, 0x0a,
      70,   15,   15,   15, 0x0a,
      88,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__commandbutton[] = {
    "_commandbutton\0\0SoundOnEvent()\0"
    "EVENT_OnEvent()\0b\0EVENT_OnEvent2(bool)\0"
    "frameChanged(int)\0cursoranimation_frameChanged(int)\0"
};

const QMetaObject _commandbutton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata__commandbutton,
      qt_meta_data__commandbutton, 0 }
};

const QMetaObject *_commandbutton::metaObject() const
{
    return &staticMetaObject;
}

void *_commandbutton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__commandbutton))
        return static_cast<void*>(const_cast< _commandbutton*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _commandbutton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int _commandbutton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
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
