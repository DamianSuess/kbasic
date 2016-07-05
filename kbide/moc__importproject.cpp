/****************************************************************************
** Meta object code from reading C++ file '_importproject.h'
**
** Created: Sat May 2 07:53:58 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_importproject.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_importproject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__importproject[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      26,   15,   15,   15, 0x08,
      37,   15,   15,   15, 0x08,
      42,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__importproject[] = {
    "_importproject\0\0clicked()\0clicked2()\0"
    "ok()\0cancel()\0"
};

const QMetaObject _importproject::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__importproject,
      qt_meta_data__importproject, 0 }
};

const QMetaObject *_importproject::metaObject() const
{
    return &staticMetaObject;
}

void *_importproject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__importproject))
        return static_cast<void*>(const_cast< _importproject*>(this));
    return QDialog::qt_metacast(_clname);
}

int _importproject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked(); break;
        case 1: clicked2(); break;
        case 2: ok(); break;
        case 3: cancel(); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
