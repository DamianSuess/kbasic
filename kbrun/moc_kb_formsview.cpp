/****************************************************************************
** Meta object code from reading C++ file 'kb_formsview.h'
**
** Created: Fri May 1 19:16:21 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbasic_binding/_formsview/kb_formsview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kb_formsview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_kb_formsview[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_kb_formsview[] = {
    "kb_formsview\0"
};

const QMetaObject kb_formsview::staticMetaObject = {
    { &_formsview::staticMetaObject, qt_meta_stringdata_kb_formsview,
      qt_meta_data_kb_formsview, 0 }
};

const QMetaObject *kb_formsview::metaObject() const
{
    return &staticMetaObject;
}

void *kb_formsview::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_kb_formsview))
        return static_cast<void*>(const_cast< kb_formsview*>(this));
    return _formsview::qt_metacast(_clname);
}

int kb_formsview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _formsview::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
