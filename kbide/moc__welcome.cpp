/****************************************************************************
** Meta object code from reading C++ file '_welcome.h'
**
** Created: Sat May 2 07:55:51 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_welcome.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_welcome.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__welcome[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      20,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__welcome[] = {
    "_welcome\0\0SLOT_ok()\0SLOT_close()\0"
};

const QMetaObject _welcome::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__welcome,
      qt_meta_data__welcome, 0 }
};

const QMetaObject *_welcome::metaObject() const
{
    return &staticMetaObject;
}

void *_welcome::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__welcome))
        return static_cast<void*>(const_cast< _welcome*>(this));
    return QDialog::qt_metacast(_clname);
}

int _welcome::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SLOT_ok(); break;
        case 1: SLOT_close(); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
