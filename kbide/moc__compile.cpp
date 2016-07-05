/****************************************************************************
** Meta object code from reading C++ file '_compile.h'
**
** Created: Sat May 2 07:53:36 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_compile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_compile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__compile[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   10,    9,    9, 0x08,
      66,   46,    9,    9, 0x08,
     101,    9,    9,    9, 0x08,
     126,    9,    9,    9, 0x08,
     152,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__compile[] = {
    "_compile\0\0error\0error(QProcess::ProcessError)\0"
    "exitCode,exitStatus\0"
    "finished(int,QProcess::ExitStatus)\0"
    "readyReadStandardError()\0"
    "readyReadStandardOutput()\0started()\0"
};

const QMetaObject _compile::staticMetaObject = {
    { &QProcess::staticMetaObject, qt_meta_stringdata__compile,
      qt_meta_data__compile, 0 }
};

const QMetaObject *_compile::metaObject() const
{
    return &staticMetaObject;
}

void *_compile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__compile))
        return static_cast<void*>(const_cast< _compile*>(this));
    return QProcess::qt_metacast(_clname);
}

int _compile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QProcess::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: error((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 1: finished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 2: readyReadStandardError(); break;
        case 3: readyReadStandardOutput(); break;
        case 4: started(); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
