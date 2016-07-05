/****************************************************************************
** Meta object code from reading C++ file '_tab.h'
**
** Created: Sat May 2 08:06:57 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_tab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_tab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__tab[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,    6,    5,    5, 0x0a,
      32,    6,    5,    5, 0x0a,
      52,    6,    5,    5, 0x0a,
      71,    5,    5,    5, 0x0a,
      89,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__tab[] = {
    "_tab\0\0Index\0EVENT_OnEvent2(int)\0"
    "EVENT_OnEvent3(int)\0EVENT_OnEvent(int)\0"
    "frameChanged(int)\0cursoranimation_frameChanged(int)\0"
};

const QMetaObject _tab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__tab,
      qt_meta_data__tab, 0 }
};

const QMetaObject *_tab::metaObject() const
{
    return &staticMetaObject;
}

void *_tab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__tab))
        return static_cast<void*>(const_cast< _tab*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _tab*>(this));
    return QWidget::qt_metacast(_clname);
}

int _tab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: EVENT_OnEvent2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: EVENT_OnEvent3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: EVENT_OnEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
