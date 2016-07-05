/****************************************************************************
** Meta object code from reading C++ file '_radiobutton.h'
**
** Created: Sat May 2 08:02:33 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_radiobutton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_radiobutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__radiobutton[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      29,   13,   13,   13, 0x0a,
      45,   13,   13,   13, 0x0a,
      62,   13,   13,   13, 0x0a,
      80,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__radiobutton[] = {
    "_radiobutton\0\0SoundOnEvent()\0"
    "EVENT_OnEvent()\0EVENT_OnEvent2()\0"
    "frameChanged(int)\0cursoranimation_frameChanged(int)\0"
};

const QMetaObject _radiobutton::staticMetaObject = {
    { &QRadioButton::staticMetaObject, qt_meta_stringdata__radiobutton,
      qt_meta_data__radiobutton, 0 }
};

const QMetaObject *_radiobutton::metaObject() const
{
    return &staticMetaObject;
}

void *_radiobutton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__radiobutton))
        return static_cast<void*>(const_cast< _radiobutton*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _radiobutton*>(this));
    return QRadioButton::qt_metacast(_clname);
}

int _radiobutton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QRadioButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SoundOnEvent(); break;
        case 1: EVENT_OnEvent(); break;
        case 2: EVENT_OnEvent2(); break;
        case 3: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
