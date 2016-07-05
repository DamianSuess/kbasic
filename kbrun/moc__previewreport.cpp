/****************************************************************************
** Meta object code from reading C++ file '_previewreport.h'
**
** Created: Wed Dec 3 14:14:43 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_previewreport.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_previewreport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__previewreport[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      24,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__previewreport[] = {
    "_previewreport\0\0print()\0pageSetup()\0"
};

const QMetaObject _previewreport::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata__previewreport,
      qt_meta_data__previewreport, 0 }
};

const QMetaObject *_previewreport::metaObject() const
{
    return &staticMetaObject;
}

void *_previewreport::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__previewreport))
	return static_cast<void*>(const_cast< _previewreport*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int _previewreport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: print(); break;
        case 1: pageSetup(); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
