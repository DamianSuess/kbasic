/****************************************************************************
** Meta object code from reading C++ file '_udpsocket.h'
**
** Created: Fri May 1 19:16:04 2009
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
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      33,   11,   11,   11, 0x0a,
      51,   11,   11,   11, 0x0a,
      70,   11,   11,   11, 0x0a,
      85,   11,   11,   11, 0x0a,
     101,   11,   11,   11, 0x0a,
     116,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__udpsocket[] = {
    "_udpsocket\0\0EVENT_OnSingleShot()\0"
    "EVENT_OnEnabled()\0EVENT_OnDisabled()\0"
    "SoundOnEvent()\0EVENT_OnEvent()\0"
    "EVENT_OnOpen()\0EVENT_OnClose()\0"
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
        case 0: EVENT_OnSingleShot(); break;
        case 1: EVENT_OnEnabled(); break;
        case 2: EVENT_OnDisabled(); break;
        case 3: SoundOnEvent(); break;
        case 4: EVENT_OnEvent(); break;
        case 5: EVENT_OnOpen(); break;
        case 6: EVENT_OnClose(); break;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
