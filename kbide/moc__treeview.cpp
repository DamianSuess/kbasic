/****************************************************************************
** Meta object code from reading C++ file '_treeview.h'
**
** Created: Sat May 2 08:08:15 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_treeview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_treeview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__treeview[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      26,   10,   10,   10, 0x0a,
      59,   42,   10,   10, 0x0a,
     125,  113,   10,   10, 0x0a,
     161,  113,   10,   10, 0x0a,
     195,  113,   10,   10, 0x0a,
     234,  229,   10,   10, 0x0a,
     266,  113,   10,   10, 0x0a,
     306,  113,   10,   10, 0x0a,
     340,  229,   10,   10, 0x0a,
     371,  113,   10,   10, 0x0a,
     405,   10,   10,   10, 0x0a,
     428,   10,   10,   10, 0x0a,
     446,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__treeview[] = {
    "_treeview\0\0SoundOnEvent()\0EVENT_OnEvent()\0"
    "current,previous\0"
    "currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "item,Column\0itemActivated(QTreeWidgetItem*,int)\0"
    "itemChanged(QTreeWidgetItem*,int)\0"
    "itemClicked(QTreeWidgetItem*,int)\0"
    "item\0itemCollapsed(QTreeWidgetItem*)\0"
    "itemDoubleClicked(QTreeWidgetItem*,int)\0"
    "itemEntered(QTreeWidgetItem*,int)\0"
    "itemExpanded(QTreeWidgetItem*)\0"
    "itemPressed(QTreeWidgetItem*,int)\0"
    "itemSelectionChanged()\0frameChanged(int)\0"
    "cursoranimation_frameChanged(int)\0"
};

const QMetaObject _treeview::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata__treeview,
      qt_meta_data__treeview, 0 }
};

const QMetaObject *_treeview::metaObject() const
{
    return &staticMetaObject;
}

void *_treeview::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__treeview))
        return static_cast<void*>(const_cast< _treeview*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _treeview*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int _treeview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SoundOnEvent(); break;
        case 1: EVENT_OnEvent(); break;
        case 2: currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 3: itemActivated((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: itemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: itemCollapsed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 7: itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: itemEntered((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: itemExpanded((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 10: itemPressed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: itemSelectionChanged(); break;
        case 12: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
