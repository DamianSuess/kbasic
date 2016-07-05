/****************************************************************************
** Meta object code from reading C++ file '_sourcecodeeditor.h'
**
** Created: Sat May 2 07:55:23 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_sourcecodeeditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_sourcecodeeditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__sourcecodeeditor[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      35,   18,   18,   18, 0x0a,
      65,   59,   18,   18, 0x0a,
      80,   18,   18,   18, 0x0a,
      96,   18,   18,   18, 0x0a,
     115,   18,   18,   18, 0x0a,
     134,   18,   18,   18, 0x0a,
     151,  147,   18,   18, 0x08,
     171,  147,   18,   18, 0x08,
     191,  147,   18,   18, 0x08,
     211,   18,   18,   18, 0x08,
     225,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__sourcecodeeditor[] = {
    "_sourcecodeeditor\0\0updateBrowser()\0"
    "cursorPositionChanged()\0index\0"
    "activated(int)\0setFullscreen()\0"
    "setNoFullscreen2()\0setWindow_extend()\0"
    "showEvents()\0yes\0copyAvailable(bool)\0"
    "redoAvailable(bool)\0undoAvailable(bool)\0"
    "textChanged()\0selectionChanged()\0"
};

const QMetaObject _sourcecodeeditor::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata__sourcecodeeditor,
      qt_meta_data__sourcecodeeditor, 0 }
};

const QMetaObject *_sourcecodeeditor::metaObject() const
{
    return &staticMetaObject;
}

void *_sourcecodeeditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__sourcecodeeditor))
        return static_cast<void*>(const_cast< _sourcecodeeditor*>(this));
    return QFrame::qt_metacast(_clname);
}

int _sourcecodeeditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateBrowser(); break;
        case 1: cursorPositionChanged(); break;
        case 2: activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setFullscreen(); break;
        case 4: setNoFullscreen2(); break;
        case 5: setWindow_extend(); break;
        case 6: showEvents(); break;
        case 7: copyAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: redoAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: undoAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: textChanged(); break;
        case 11: selectionChanged(); break;
        }
        _id -= 12;
    }
    return _id;
}
static const uint qt_meta_data__border[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__border[] = {
    "_border\0"
};

const QMetaObject _border::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__border,
      qt_meta_data__border, 0 }
};

const QMetaObject *_border::metaObject() const
{
    return &staticMetaObject;
}

void *_border::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__border))
        return static_cast<void*>(const_cast< _border*>(this));
    return QWidget::qt_metacast(_clname);
}

int _border::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data__finddefinition[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__finddefinition[] = {
    "_finddefinition\0\0item\0"
    "itemDoubleClicked(QListWidgetItem*)\0"
};

const QMetaObject _finddefinition::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata__finddefinition,
      qt_meta_data__finddefinition, 0 }
};

const QMetaObject *_finddefinition::metaObject() const
{
    return &staticMetaObject;
}

void *_finddefinition::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__finddefinition))
        return static_cast<void*>(const_cast< _finddefinition*>(this));
    return QListWidget::qt_metacast(_clname);
}

int _finddefinition::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
