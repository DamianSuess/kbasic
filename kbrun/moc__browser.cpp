/****************************************************************************
** Meta object code from reading C++ file '_browser.h'
**
** Created: Fri May 1 19:08:40 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_browser.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_browser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__browser[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x0a,
      36,   10,    9,    9, 0x0a,
      61,   59,    9,    9, 0x0a,
     123,   81,    9,    9, 0x0a,
     166,    9,    9,    9, 0x0a,
     184,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__browser[] = {
    "_browser\0\0b\0backwardAvailable(bool)\0"
    "forwardAvailable(bool)\0u\0sourceChanged(QUrl)\0"
    "BackwardAvailable,ForwardAvailable,NewURL\0"
    "EVENT_OnEvent(t_boolean,t_boolean,QString)\0"
    "frameChanged(int)\0cursoranimation_frameChanged(int)\0"
};

const QMetaObject _browser::staticMetaObject = {
    { &QTextBrowser::staticMetaObject, qt_meta_stringdata__browser,
      qt_meta_data__browser, 0 }
};

const QMetaObject *_browser::metaObject() const
{
    return &staticMetaObject;
}

void *_browser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__browser))
        return static_cast<void*>(const_cast< _browser*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _browser*>(this));
    return QTextBrowser::qt_metacast(_clname);
}

int _browser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: backwardAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: forwardAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: sourceChanged((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 3: EVENT_OnEvent((*reinterpret_cast< t_boolean(*)>(_a[1])),(*reinterpret_cast< t_boolean(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
