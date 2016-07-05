/****************************************************************************
** Meta object code from reading C++ file '_udpsocket.h'
**
** Created: Sat May 2 08:08:24 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_udpsocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_udpsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__udpsocket[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      27,   11,   11,   11, 0x0a,
      43,   11,   11,   11, 0x0a,
      61,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__udpsocket[] = {
    "_udpsocket\0\0SoundOnEvent()\0EVENT_OnEvent()\0"
    "frameChanged(int)\0cursoranimation_frameChanged(int)\0"
};

const QMetaObject _udpsocket::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata__udpsocket,
      qt_meta_data__udpsocket, 0 }
};

const QMetaObject *_udpsocket::metaObject() const
{
    return &staticMetaObject;
}

void *_udpsocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__udpsocket))
        return static_cast<void*>(const_cast< _udpsocket*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _udpsocket*>(this));
    return QLabel::qt_metacast(_clname);
}

int _udpsocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SoundOnEvent(); break;
        case 1: EVENT_OnEvent(); break;
        case 2: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
