/****************************************************************************
** Meta object code from reading C++ file '_form.h'
**
** Created: Fri May 1 19:10:19 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_form.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__form[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,    7,    6,    6, 0x0a,
      61,   52,    6,    6, 0x0a,
      91,   83,    6,    6, 0x0a,
     115,    6,    6,    6, 0x0a,
     133,    6,    6,    6, 0x0a,
     173,  167,    6,    6, 0x0a,
     202,  167,    6,    6, 0x0a,
     231,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__form[] = {
    "_form\0\0area\0dockLocationChanged(Qt::DockWidgetArea)\0"
    "topLevel\0topLevelChanged(bool)\0visible\0"
    "visibilityChanged(bool)\0frameChanged(int)\0"
    "cursoranimation_frameChanged(int)\0"
    "value\0XScrollBar_valueChanged(int)\0"
    "YScrollBar_valueChanged(int)\0"
    "form_topLevelChanged(bool)\0"
};

const QMetaObject _form::staticMetaObject = {
    { &QScrollArea::staticMetaObject, qt_meta_stringdata__form,
      qt_meta_data__form, 0 }
};

const QMetaObject *_form::metaObject() const
{
    return &staticMetaObject;
}

void *_form::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__form))
        return static_cast<void*>(const_cast< _form*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _form*>(this));
    return QScrollArea::qt_metacast(_clname);
}

int _form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dockLocationChanged((*reinterpret_cast< Qt::DockWidgetArea(*)>(_a[1]))); break;
        case 1: topLevelChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: visibilityChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: XScrollBar_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: YScrollBar_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: form_topLevelChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 8;
    }
    return _id;
}
static const uint qt_meta_data_TableViewDelegate[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TableViewDelegate[] = {
    "TableViewDelegate\0\0commitAndCloseEditor()\0"
};

const QMetaObject TableViewDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_TableViewDelegate,
      qt_meta_data_TableViewDelegate, 0 }
};

const QMetaObject *TableViewDelegate::metaObject() const
{
    return &staticMetaObject;
}

void *TableViewDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableViewDelegate))
        return static_cast<void*>(const_cast< TableViewDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int TableViewDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: commitAndCloseEditor(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_TableView[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_TableView[] = {
    "TableView\0"
};

const QMetaObject TableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_TableView,
      qt_meta_data_TableView, 0 }
};

const QMetaObject *TableView::metaObject() const
{
    return &staticMetaObject;
}

void *TableView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableView))
        return static_cast<void*>(const_cast< TableView*>(this));
    return QTableView::qt_metacast(_clname);
}

int TableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
