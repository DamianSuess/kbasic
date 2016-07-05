/****************************************************************************
** Meta object code from reading C++ file '_relation.h'
**
** Created: Sat May 2 07:55:11 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_relation.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_relation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__relation[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      25,   11,   10,   10, 0x0a,
      50,   10,   10,   10, 0x0a,
      78,   63,   10,   10, 0x0a,
      94,   10,   10,   10, 0x2a,
     106,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__relation[] = {
    "_relation\0\0sTable,sField\0"
    "addItem(QString,QString)\0SLOT_close()\0"
    "bApplyGeometry\0loadRules(bool)\0"
    "loadRules()\0saveRules()\0"
};

const QMetaObject _relation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__relation,
      qt_meta_data__relation, 0 }
};

const QMetaObject *_relation::metaObject() const
{
    return &staticMetaObject;
}

void *_relation::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__relation))
        return static_cast<void*>(const_cast< _relation*>(this));
    return QDialog::qt_metacast(_clname);
}

int _relation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addItem((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: SLOT_close(); break;
        case 2: loadRules((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: loadRules(); break;
        case 4: saveRules(); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
