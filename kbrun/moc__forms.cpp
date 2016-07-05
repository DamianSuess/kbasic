/****************************************************************************
** Meta object code from reading C++ file '_forms.h'
**
** Created: Fri May 1 19:10:58 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_forms.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_forms.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__forms[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      53,    7,    7,    7, 0x0a,
      70,    7,    7,    7, 0x0a,
      97,    7,    7,    7, 0x0a,
     122,  115,    7,    7, 0x0a,
     151,    7,    7,    7, 0x0a,
     162,    7,    7,    7, 0x0a,
     170,    7,    7,    7, 0x0a,
     187,    7,    7,    7, 0x0a,
     207,    7,    7,    7, 0x0a,
     224,    7,    7,    7, 0x0a,
     244,    7,    7,    7, 0x0a,
     263,    7,    7,    7, 0x0a,
     284,    7,    7,    7, 0x0a,
     306,    7,    7,    7, 0x0a,
     318,    7,    7,    7, 0x0a,
     333,    7,    7,    7, 0x0a,
     347,    7,    7,    7, 0x0a,
     361,    7,    7,    7, 0x0a,
     375,    7,    7,    7, 0x0a,
     386,    7,    7,    7, 0x0a,
     398,    7,    7,    7, 0x0a,
     411,    7,    7,    7, 0x0a,
     432,  430,    7,    7, 0x0a,
     467,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__forms[] = {
    "_forms\0\0activated(QSystemTrayIcon::ActivationReason)\0"
    "messageClicked()\0trayIcon_frameChanged(int)\0"
    "frameChanged(int)\0window\0"
    "setActiveSubWindow(QWidget*)\0CONTENTS()\0"
    "ABOUT()\0SLOT_AddFilter()\0SLOT_AddNotFilter()\0"
    "SLOT_SetFilter()\0SLOT_SetNotFilter()\0"
    "SLOT_ClearFilter()\0SLOT_SortAscending()\0"
    "SLOT_SortDescending()\0SLOT_Seek()\0"
    "SLOT_Requery()\0SLOT_AddNew()\0SLOT_Update()\0"
    "SLOT_Delete()\0SLOT_Cut()\0SLOT_Copy()\0"
    "SLOT_Paste()\0updateWindowMenu()\0w\0"
    "subWindowActivated(QMdiSubWindow*)\0"
    "lastWindowClosed()\0"
};

const QMetaObject _forms::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata__forms,
      qt_meta_data__forms, 0 }
};

const QMetaObject *_forms::metaObject() const
{
    return &staticMetaObject;
}

void *_forms::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__forms))
        return static_cast<void*>(const_cast< _forms*>(this));
    return QObject::qt_metacast(_clname);
}

int _forms::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 1: messageClicked(); break;
        case 2: trayIcon_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setActiveSubWindow((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 5: CONTENTS(); break;
        case 6: ABOUT(); break;
        case 7: SLOT_AddFilter(); break;
        case 8: SLOT_AddNotFilter(); break;
        case 9: SLOT_SetFilter(); break;
        case 10: SLOT_SetNotFilter(); break;
        case 11: SLOT_ClearFilter(); break;
        case 12: SLOT_SortAscending(); break;
        case 13: SLOT_SortDescending(); break;
        case 14: SLOT_Seek(); break;
        case 15: SLOT_Requery(); break;
        case 16: SLOT_AddNew(); break;
        case 17: SLOT_Update(); break;
        case 18: SLOT_Delete(); break;
        case 19: SLOT_Cut(); break;
        case 20: SLOT_Copy(); break;
        case 21: SLOT_Paste(); break;
        case 22: updateWindowMenu(); break;
        case 23: subWindowActivated((*reinterpret_cast< QMdiSubWindow*(*)>(_a[1]))); break;
        case 24: lastWindowClosed(); break;
        }
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
