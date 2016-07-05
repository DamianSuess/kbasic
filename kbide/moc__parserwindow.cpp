/****************************************************************************
** Meta object code from reading C++ file '_parserwindow.h'
**
** Created: Sat May 2 07:54:16 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_parserwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_parserwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__parserwindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      50,   38,   14,   14, 0x08,
      90,   38,   14,   14, 0x08,
     131,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__parserwindow[] = {
    "_parserwindow\0\0itemSelectionChanged()\0"
    "item,column\0itemDoubleClicked(QTreeWidgetItem*,int)\0"
    "itemDoubleClicked2(QTreeWidgetItem*,int)\0"
    "actionSelected()\0"
};

const QMetaObject _parserwindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__parserwindow,
      qt_meta_data__parserwindow, 0 }
};

const QMetaObject *_parserwindow::metaObject() const
{
    return &staticMetaObject;
}

void *_parserwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__parserwindow))
        return static_cast<void*>(const_cast< _parserwindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int _parserwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemSelectionChanged(); break;
        case 1: itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: itemDoubleClicked2((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: actionSelected(); break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
