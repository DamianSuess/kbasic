/****************************************************************************
** Meta object code from reading C++ file '_dbcondialog.h'
**
** Created: Sat May 2 07:53:40 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_dbcondialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_dbcondialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__dbcondialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      31,   13,   13,   13, 0x08,
      42,   13,   13,   13, 0x08,
      55,   13,   13,   13, 0x08,
      60,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__dbcondialog[] = {
    "_dbcondialog\0\0createdatabase()\0"
    "embedded()\0nodatabase()\0ok()\0cancel()\0"
};

const QMetaObject _dbcondialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__dbcondialog,
      qt_meta_data__dbcondialog, 0 }
};

const QMetaObject *_dbcondialog::metaObject() const
{
    return &staticMetaObject;
}

void *_dbcondialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__dbcondialog))
        return static_cast<void*>(const_cast< _dbcondialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int _dbcondialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createdatabase(); break;
        case 1: embedded(); break;
        case 2: nodatabase(); break;
        case 3: ok(); break;
        case 4: cancel(); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
