/****************************************************************************
** Meta object code from reading C++ file '_preferences.h'
**
** Created: Sat May 2 07:54:19 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_preferences.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_preferences.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__preferences[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      24,   13,   13,   13, 0x08,
      35,   13,   13,   13, 0x08,
      46,   13,   13,   13, 0x08,
      64,   62,   13,   13, 0x08,
      78,   13,   13,   13, 0x08,
      92,   13,   13,   13, 0x08,
     109,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__preferences[] = {
    "_preferences\0\0clicked()\0clicked2()\0"
    "clicked3()\0updateExample()\0n\0selected(int)\0"
    "performSave()\0performDefault()\0"
    "performClose()\0"
};

const QMetaObject _preferences::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__preferences,
      qt_meta_data__preferences, 0 }
};

const QMetaObject *_preferences::metaObject() const
{
    return &staticMetaObject;
}

void *_preferences::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__preferences))
        return static_cast<void*>(const_cast< _preferences*>(this));
    return QDialog::qt_metacast(_clname);
}

int _preferences::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked(); break;
        case 1: clicked2(); break;
        case 2: clicked3(); break;
        case 3: updateExample(); break;
        case 4: selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: performSave(); break;
        case 6: performDefault(); break;
        case 7: performClose(); break;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
