/****************************************************************************
** Meta object code from reading C++ file '_listbox.h'
**
** Created: Fri May 1 19:12:08 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_listbox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_listbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__listbox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x0a,
      48,   34,    9,    9, 0x0a,
      75,    9,    9,    9, 0x0a,
      94,    9,    9,    9, 0x0a,
     112,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__listbox[] = {
    "_listbox\0\0Index\0EVENT_2Event(int)\0"
    "Index,Caption\0EVENT_OnEvent(int,QString)\0"
    "EVENT_OnSQLEvent()\0frameChanged(int)\0"
    "cursoranimation_frameChanged(int)\0"
};

const QMetaObject _listbox::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata__listbox,
      qt_meta_data__listbox, 0 }
};

const QMetaObject *_listbox::metaObject() const
{
    return &staticMetaObject;
}

void *_listbox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__listbox))
        return static_cast<void*>(const_cast< _listbox*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _listbox*>(this));
    return QListWidget::qt_metacast(_clname);
}

int _listbox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: EVENT_2Event((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: EVENT_OnEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: EVENT_OnSQLEvent(); break;
        case 3: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
