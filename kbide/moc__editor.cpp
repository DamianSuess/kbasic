/****************************************************************************
** Meta object code from reading C++ file '_editor.h'
**
** Created: Sat May 2 07:57:14 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_editor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__editor[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      13,    9,    8,    8, 0x0a,
      33,    9,    8,    8, 0x0a,
      53,    8,    8,    8, 0x0a,
      72,    8,    8,    8, 0x0a,
      87,    8,    8,    8, 0x0a,
     159,  103,    8,    8, 0x0a,
     215,    8,    8,    8, 0x0a,
     247,    8,    8,    8, 0x0a,
     266,    8,    8,    8, 0x0a,
     284,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__editor[] = {
    "_editor\0\0yes\0redoAvailable(bool)\0"
    "undoAvailable(bool)\0selectionChanged()\0"
    "SoundOnEvent()\0EVENT_OnEvent()\0"
    "TextSelected,PasteAvailable,UndoAvailable,RedoAvailable\0"
    "EVENT_OnEvent1(t_boolean,t_boolean,t_boolean,t_boolean)\0"
    "EVENT_OnCursorPositionChanged()\0"
    "EVENT_OnSQLEvent()\0frameChanged(int)\0"
    "cursoranimation_frameChanged(int)\0"
};

const QMetaObject _editor::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata__editor,
      qt_meta_data__editor, 0 }
};

const QMetaObject *_editor::metaObject() const
{
    return &staticMetaObject;
}

void *_editor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__editor))
        return static_cast<void*>(const_cast< _editor*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _editor*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int _editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: redoAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: undoAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: selectionChanged(); break;
        case 3: SoundOnEvent(); break;
        case 4: EVENT_OnEvent(); break;
        case 5: EVENT_OnEvent1((*reinterpret_cast< t_boolean(*)>(_a[1])),(*reinterpret_cast< t_boolean(*)>(_a[2])),(*reinterpret_cast< t_boolean(*)>(_a[3])),(*reinterpret_cast< t_boolean(*)>(_a[4]))); break;
        case 6: EVENT_OnCursorPositionChanged(); break;
        case 7: EVENT_OnSQLEvent(); break;
        case 8: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 10;
    }
    return _id;
}
static const uint qt_meta_data__syntaxhighlighter[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__syntaxhighlighter[] = {
    "_syntaxhighlighter\0"
};

const QMetaObject _syntaxhighlighter::staticMetaObject = {
    { &QSyntaxHighlighter::staticMetaObject, qt_meta_stringdata__syntaxhighlighter,
      qt_meta_data__syntaxhighlighter, 0 }
};

const QMetaObject *_syntaxhighlighter::metaObject() const
{
    return &staticMetaObject;
}

void *_syntaxhighlighter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__syntaxhighlighter))
        return static_cast<void*>(const_cast< _syntaxhighlighter*>(this));
    return QSyntaxHighlighter::qt_metacast(_clname);
}

int _syntaxhighlighter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSyntaxHighlighter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
