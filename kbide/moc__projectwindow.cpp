/****************************************************************************
** Meta object code from reading C++ file '_projectwindow.h'
**
** Created: Sat May 2 07:54:24 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_projectwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_projectwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__projectwindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      28,   15,   15,   15, 0x08,
      57,   45,   15,   15, 0x08,
      91,   45,   15,   15, 0x08,
     131,   15,   15,   15, 0x08,
     171,  154,   15,   15, 0x08,
     229,  225,   15,   15, 0x08,
     264,   15,   15,   15, 0x08,
     281,   15,   15,   15, 0x08,
     299,   15,   15,   15, 0x08,
     318,   15,   15,   15, 0x08,
     338,   15,   15,   15, 0x08,
     354,   15,   15,   15, 0x08,
     369,   15,   15,   15, 0x08,
     382,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__projectwindow[] = {
    "_projectwindow\0\0settingdb()\0"
    "actionSelected()\0item,column\0"
    "itemChanged(QTreeWidgetItem*,int)\0"
    "itemDoubleClicked(QTreeWidgetItem*,int)\0"
    "itemSelectionChanged()\0current,previous\0"
    "currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "pos\0customContextMenuRequested(QPoint)\0"
    "event_EDIT_CUT()\0event_EDIT_COPY()\0"
    "event_EDIT_PASTE()\0event_EDIT_DELETE()\0"
    "event_REFRESH()\0event_RENAME()\0"
    "event_OPEN()\0event_OPEN2()\0"
};

const QMetaObject _projectwindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__projectwindow,
      qt_meta_data__projectwindow, 0 }
};

const QMetaObject *_projectwindow::metaObject() const
{
    return &staticMetaObject;
}

void *_projectwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__projectwindow))
        return static_cast<void*>(const_cast< _projectwindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int _projectwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: settingdb(); break;
        case 1: actionSelected(); break;
        case 2: itemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: itemSelectionChanged(); break;
        case 5: currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 6: customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 7: event_EDIT_CUT(); break;
        case 8: event_EDIT_COPY(); break;
        case 9: event_EDIT_PASTE(); break;
        case 10: event_EDIT_DELETE(); break;
        case 11: event_REFRESH(); break;
        case 12: event_RENAME(); break;
        case 13: event_OPEN(); break;
        case 14: event_OPEN2(); break;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
