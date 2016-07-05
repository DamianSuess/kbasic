/****************************************************************************
** Meta object code from reading C++ file '_toolboxwindow_toolbar.h'
**
** Created: Sat May 2 07:55:44 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_toolboxwindow_toolbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_toolboxwindow_toolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__toolboxwindow_toolbar[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x08,
      34,   23,   23,   23, 0x08,
      48,   23,   23,   23, 0x08,
      55,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__toolboxwindow_toolbar[] = {
    "_toolboxwindow_toolbar\0\0pointer()\0"
    "toolbaritem()\0move()\0_delete()\0"
};

const QMetaObject _toolboxwindow_toolbar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__toolboxwindow_toolbar,
      qt_meta_data__toolboxwindow_toolbar, 0 }
};

const QMetaObject *_toolboxwindow_toolbar::metaObject() const
{
    return &staticMetaObject;
}

void *_toolboxwindow_toolbar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__toolboxwindow_toolbar))
        return static_cast<void*>(const_cast< _toolboxwindow_toolbar*>(this));
    return QWidget::qt_metacast(_clname);
}

int _toolboxwindow_toolbar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pointer(); break;
        case 1: toolbaritem(); break;
        case 2: move(); break;
        case 3: _delete(); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
