/****************************************************************************
** Meta object code from reading C++ file '_findfilelist.h'
**
** Created: Sat May 2 07:53:46 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_findfilelist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_findfilelist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__findfilelist[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__findfilelist[] = {
    "_findfilelist\0\0item\0itemActivated(QListWidgetItem*)\0"
};

const QMetaObject _findfilelist::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata__findfilelist,
      qt_meta_data__findfilelist, 0 }
};

const QMetaObject *_findfilelist::metaObject() const
{
    return &staticMetaObject;
}

void *_findfilelist::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__findfilelist))
        return static_cast<void*>(const_cast< _findfilelist*>(this));
    return QListWidget::qt_metacast(_clname);
}

int _findfilelist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemActivated((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
