/****************************************************************************
** Meta object code from reading C++ file '_qbe.h'
**
** Created: Sat May 2 07:54:45 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_qbe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_qbe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__qbe[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      58,    6,    5,    5, 0x0a,
      94,    5,    5,    5, 0x0a,
     108,    5,    5,    5, 0x0a,
     118,    5,    5,    5, 0x0a,
     129,    5,    5,    5, 0x0a,
     140,    5,    5,    5, 0x0a,
     153,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__qbe[] = {
    "_qbe\0\0currentRow,currentColumn,previousRow,previousColumn\0"
    "currentCellChanged(int,int,int,int)\0"
    "textChanged()\0SLOT_ok()\0SLOT_ok2()\0"
    "SLOT_ok3()\0SLOT_close()\0refreshSQL()\0"
};

const QMetaObject _qbe::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__qbe,
      qt_meta_data__qbe, 0 }
};

const QMetaObject *_qbe::metaObject() const
{
    return &staticMetaObject;
}

void *_qbe::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__qbe))
        return static_cast<void*>(const_cast< _qbe*>(this));
    return QWidget::qt_metacast(_clname);
}

int _qbe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: currentCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: textChanged(); break;
        case 2: SLOT_ok(); break;
        case 3: SLOT_ok2(); break;
        case 4: SLOT_ok3(); break;
        case 5: SLOT_close(); break;
        case 6: refreshSQL(); break;
        }
        _id -= 7;
    }
    return _id;
}
static const uint qt_meta_data_QBETableDelegate[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QBETableDelegate[] = {
    "QBETableDelegate\0\0commitAndCloseEditor()\0"
};

const QMetaObject QBETableDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_QBETableDelegate,
      qt_meta_data_QBETableDelegate, 0 }
};

const QMetaObject *QBETableDelegate::metaObject() const
{
    return &staticMetaObject;
}

void *QBETableDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBETableDelegate))
        return static_cast<void*>(const_cast< QBETableDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int QBETableDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
