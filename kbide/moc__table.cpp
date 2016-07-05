/****************************************************************************
** Meta object code from reading C++ file '_table.h'
**
** Created: Sat May 2 08:07:06 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_table.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_table.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
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
static const uint qt_meta_data__tableviewer[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      24,   13,   13,   13, 0x0a,
      35,   13,   13,   13, 0x0a,
      49,   13,   13,   13, 0x0a,
      62,   13,   13,   13, 0x0a,
      72,   13,   13,   13, 0x0a,
      84,   13,   13,   13, 0x0a,
      99,   13,   13,   13, 0x0a,
     111,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__tableviewer[] = {
    "_tableviewer\0\0SQLGoto()\0SQLFirst()\0"
    "SQLBackward()\0SQLForward()\0SQLLast()\0"
    "SQLAddNew()\0SQLAddNew100()\0SQLDelete()\0"
    "SQLDeleteAll()\0"
};

const QMetaObject _tableviewer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__tableviewer,
      qt_meta_data__tableviewer, 0 }
};

const QMetaObject *_tableviewer::metaObject() const
{
    return &staticMetaObject;
}

void *_tableviewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__tableviewer))
        return static_cast<void*>(const_cast< _tableviewer*>(this));
    return QWidget::qt_metacast(_clname);
}

int _tableviewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SQLGoto(); break;
        case 1: SQLFirst(); break;
        case 2: SQLBackward(); break;
        case 3: SQLForward(); break;
        case 4: SQLLast(); break;
        case 5: SQLAddNew(); break;
        case 6: SQLAddNew100(); break;
        case 7: SQLDelete(); break;
        case 8: SQLDeleteAll(); break;
        }
        _id -= 9;
    }
    return _id;
}
static const uint qt_meta_data_TableDelegate[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TableDelegate[] = {
    "TableDelegate\0\0commitAndCloseEditor()\0"
};

const QMetaObject TableDelegate::staticMetaObject = {
    { &QSqlRelationalDelegate::staticMetaObject, qt_meta_stringdata_TableDelegate,
      qt_meta_data_TableDelegate, 0 }
};

const QMetaObject *TableDelegate::metaObject() const
{
    return &staticMetaObject;
}

void *TableDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TableDelegate))
        return static_cast<void*>(const_cast< TableDelegate*>(this));
    return QSqlRelationalDelegate::qt_metacast(_clname);
}

int TableDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlRelationalDelegate::qt_metacall(_c, _id, _a);
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
static const uint qt_meta_data__table[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      60,    8,    7,    7, 0x0a,
     107,   96,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__table[] = {
    "_table\0\0currentRow,currentColumn,previousRow,previousColumn\0"
    "currentCellChanged(int,int,int,int)\0"
    "row,column\0cellChanged(int,int)\0"
};

const QMetaObject _table::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata__table,
      qt_meta_data__table, 0 }
};

const QMetaObject *_table::metaObject() const
{
    return &staticMetaObject;
}

void *_table::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__table))
        return static_cast<void*>(const_cast< _table*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int _table::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: currentCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
