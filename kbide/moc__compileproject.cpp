/****************************************************************************
** Meta object code from reading C++ file '_compileproject.h'
**
** Created: Sat May 2 07:53:37 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_compileproject.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_compileproject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__compileproject[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      28,   16,   16,   16, 0x08,
      33,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__compileproject[] = {
    "_compileproject\0\0clicked2()\0ok()\0"
    "cancel()\0"
};

const QMetaObject _compileproject::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__compileproject,
      qt_meta_data__compileproject, 0 }
};

const QMetaObject *_compileproject::metaObject() const
{
    return &staticMetaObject;
}

void *_compileproject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__compileproject))
        return static_cast<void*>(const_cast< _compileproject*>(this));
    return QDialog::qt_metacast(_clname);
}

int _compileproject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked2(); break;
        case 1: ok(); break;
        case 2: cancel(); break;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
