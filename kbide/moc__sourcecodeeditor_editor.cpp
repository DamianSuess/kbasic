/****************************************************************************
** Meta object code from reading C++ file '_sourcecodeeditor_editor.h'
**
** Created: Sat May 2 07:55:26 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_sourcecodeeditor_editor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_sourcecodeeditor_editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__sourcecodeeditor_editor[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,
      33,   25,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__sourcecodeeditor_editor[] = {
    "_sourcecodeeditor_editor\0\0undo()\0"
    "textChanged()\0"
};

const QMetaObject _sourcecodeeditor_editor::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata__sourcecodeeditor_editor,
      qt_meta_data__sourcecodeeditor_editor, 0 }
};

const QMetaObject *_sourcecodeeditor_editor::metaObject() const
{
    return &staticMetaObject;
}

void *_sourcecodeeditor_editor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__sourcecodeeditor_editor))
        return static_cast<void*>(const_cast< _sourcecodeeditor_editor*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int _sourcecodeeditor_editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: undo(); break;
        case 1: textChanged(); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
