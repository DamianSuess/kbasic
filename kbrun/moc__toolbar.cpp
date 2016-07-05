/****************************************************************************
** Meta object code from reading C++ file '_toolbar.h'
**
** Created: Fri May 1 19:15:20 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_toolbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_toolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__toolbar[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__toolbar[] = {
    "_toolbar\0\0triggered(QAction*)\0"
};

const QMetaObject _toolbar::staticMetaObject = {
    { &QToolBar::staticMetaObject, qt_meta_stringdata__toolbar,
      qt_meta_data__toolbar, 0 }
};

const QMetaObject *_toolbar::metaObject() const
{
    return &staticMetaObject;
}

void *_toolbar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__toolbar))
        return static_cast<void*>(const_cast< _toolbar*>(this));
    return QToolBar::qt_metacast(_clname);
}

int _toolbar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: triggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
