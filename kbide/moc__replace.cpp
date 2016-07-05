/****************************************************************************
** Meta object code from reading C++ file '_replace.h'
**
** Created: Sat May 2 07:55:13 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_replace.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_replace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__replace[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      44,   15,   10,    9, 0x0a,
      76,   64,   10,    9, 0x2a,
      91,    9,   10,    9, 0x2a,
     102,    9,    9,    9, 0x0a,
     112,    9,    9,    9, 0x0a,
     125,    9,    9,    9, 0x0a,
     142,  133,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__replace[] = {
    "_replace\0\0bool\0bReplaceAll,nSelectionLength\0"
    "findNext(bool,int*)\0bReplaceAll\0"
    "findNext(bool)\0findNext()\0replace()\0"
    "replaceAll()\0close()\0bChecked\0"
    "toggled(bool)\0"
};

const QMetaObject _replace::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__replace,
      qt_meta_data__replace, 0 }
};

const QMetaObject *_replace::metaObject() const
{
    return &staticMetaObject;
}

void *_replace::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__replace))
        return static_cast<void*>(const_cast< _replace*>(this));
    return QDialog::qt_metacast(_clname);
}

int _replace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = findNext((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = findNext((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = findNext();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: replace(); break;
        case 4: replaceAll(); break;
        case 5: close(); break;
        case 6: toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
