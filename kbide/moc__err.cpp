/****************************************************************************
** Meta object code from reading C++ file '_err.h'
**
** Created: Sat May 2 07:57:23 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_err.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_err.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__err[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__err[] = {
    "_err\0"
};

const QMetaObject _err::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata__err,
      qt_meta_data__err, 0 }
};

const QMetaObject *_err::metaObject() const
{
    return &staticMetaObject;
}

void *_err::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__err))
        return static_cast<void*>(const_cast< _err*>(this));
    return QObject::qt_metacast(_clname);
}

int _err::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
