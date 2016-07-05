/****************************************************************************
** Meta object code from reading C++ file '_replacefile.h'
**
** Created: Sat May 2 07:55:15 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_replacefile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_replacefile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__replacefile[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      25,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__replacefile[] = {
    "_replacefile\0\0findNext()\0close()\0"
};

const QMetaObject _replacefile::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__replacefile,
      qt_meta_data__replacefile, 0 }
};

const QMetaObject *_replacefile::metaObject() const
{
    return &staticMetaObject;
}

void *_replacefile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__replacefile))
        return static_cast<void*>(const_cast< _replacefile*>(this));
    return QDialog::qt_metacast(_clname);
}

int _replacefile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: findNext(); break;
        case 1: close(); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
