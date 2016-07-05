/****************************************************************************
** Meta object code from reading C++ file '_qbe_sql.h'
**
** Created: Sat May 2 07:54:54 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_qbe_sql.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_qbe_sql.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__qbe_sql[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__qbe_sql[] = {
    "_qbe_sql\0"
};

const QMetaObject _qbe_sql::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata__qbe_sql,
      qt_meta_data__qbe_sql, 0 }
};

const QMetaObject *_qbe_sql::metaObject() const
{
    return &staticMetaObject;
}

void *_qbe_sql::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__qbe_sql))
        return static_cast<void*>(const_cast< _qbe_sql*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int _qbe_sql::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
