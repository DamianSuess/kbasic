/****************************************************************************
** Meta object code from reading C++ file '_translation.h'
**
** Created: Sat May 2 07:55:49 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_translation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_translation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__translation[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      20,   13,   13,   13, 0x08,
      29,   13,   13,   13, 0x08,
      36,   13,   13,   13, 0x08,
      43,   13,   13,   13, 0x08,
      57,   52,   13,   13, 0x08,
      86,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__translation[] = {
    "_translation\0\0add()\0remove()\0next()\0"
    "mark()\0cancel()\0text\0currentIndexChanged(QString)\0"
    "textChanged()\0"
};

const QMetaObject _translation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__translation,
      qt_meta_data__translation, 0 }
};

const QMetaObject *_translation::metaObject() const
{
    return &staticMetaObject;
}

void *_translation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__translation))
        return static_cast<void*>(const_cast< _translation*>(this));
    return QDialog::qt_metacast(_clname);
}

int _translation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: add(); break;
        case 1: remove(); break;
        case 2: next(); break;
        case 3: mark(); break;
        case 4: cancel(); break;
        case 5: currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: textChanged(); break;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
