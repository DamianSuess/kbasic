/****************************************************************************
** Meta object code from reading C++ file '_svg.h'
**
** Created: Fri May 1 19:14:35 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_svg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_svg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__svg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      24,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__svg[] = {
    "_svg\0\0frameChanged(int)\0"
    "cursoranimation_frameChanged(int)\0"
};

const QMetaObject _svg::staticMetaObject = {
    { &QSvgWidget::staticMetaObject, qt_meta_stringdata__svg,
      qt_meta_data__svg, 0 }
};

const QMetaObject *_svg::metaObject() const
{
    return &staticMetaObject;
}

void *_svg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__svg))
        return static_cast<void*>(const_cast< _svg*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _svg*>(this));
    return QSvgWidget::qt_metacast(_clname);
}

int _svg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSvgWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
