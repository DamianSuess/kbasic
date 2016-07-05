/****************************************************************************
** Meta object code from reading C++ file '_helpwindow_shortcut.h'
**
** Created: Sat May 2 07:53:55 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_helpwindow_shortcut.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_helpwindow_shortcut.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__helpwindow_shortcut[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      35,   21,   21,   21, 0x08,
      52,   21,   21,   21, 0x08,
      65,   21,   21,   21, 0x08,
      80,   21,   21,   21, 0x08,
      94,   21,   21,   21, 0x08,
     108,   21,   21,   21, 0x08,
     124,   21,   21,   21, 0x08,
     138,   21,   21,   21, 0x08,
     157,   21,   21,   21, 0x08,
     172,   21,   21,   21, 0x08,
     187,   21,   21,   21, 0x08,
     201,   21,   21,   21, 0x08,
     217,   21,   21,   21, 0x08,
     239,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__helpwindow_shortcut[] = {
    "_helpwindow_shortcut\0\0_token__IF()\0"
    "_token__SELECT()\0_token__DO()\0"
    "_token__LOOP()\0_token__FOR()\0_token__DIM()\0"
    "_token__CONST()\0_token__SUB()\0"
    "_token__FUNCTION()\0_token__TYPE()\0"
    "_token__ENUM()\0_token__TRY()\0"
    "_token__CLASS()\0_token__CONSTRUCTOR()\0"
    "_token__PROPERTY()\0"
};

const QMetaObject _helpwindow_shortcut::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata__helpwindow_shortcut,
      qt_meta_data__helpwindow_shortcut, 0 }
};

const QMetaObject *_helpwindow_shortcut::metaObject() const
{
    return &staticMetaObject;
}

void *_helpwindow_shortcut::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__helpwindow_shortcut))
        return static_cast<void*>(const_cast< _helpwindow_shortcut*>(this));
    return QListWidget::qt_metacast(_clname);
}

int _helpwindow_shortcut::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _token__IF(); break;
        case 1: _token__SELECT(); break;
        case 2: _token__DO(); break;
        case 3: _token__LOOP(); break;
        case 4: _token__FOR(); break;
        case 5: _token__DIM(); break;
        case 6: _token__CONST(); break;
        case 7: _token__SUB(); break;
        case 8: _token__FUNCTION(); break;
        case 9: _token__TYPE(); break;
        case 10: _token__ENUM(); break;
        case 11: _token__TRY(); break;
        case 12: _token__CLASS(); break;
        case 13: _token__CONSTRUCTOR(); break;
        case 14: _token__PROPERTY(); break;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
