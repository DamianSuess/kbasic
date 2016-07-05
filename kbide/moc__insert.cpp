/****************************************************************************
** Meta object code from reading C++ file '_insert.h'
**
** Created: Sat May 2 07:54:03 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_insert.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_insert.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__insert[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      19,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert[] = {
    "_insert\0\0SLOT_ok()\0SLOT_close()\0"
};

const QMetaObject _insert::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__insert,
      qt_meta_data__insert, 0 }
};

const QMetaObject *_insert::metaObject() const
{
    return &staticMetaObject;
}

void *_insert::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert))
        return static_cast<void*>(const_cast< _insert*>(this));
    return QDialog::qt_metacast(_clname);
}

int _insert::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SLOT_ok(); break;
        case 1: SLOT_close(); break;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data__insert_option_kbasic[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      25,   23,   22,   22, 0x0a,
      41,   23,   22,   22, 0x0a,
      57,   23,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_option_kbasic[] = {
    "_insert_option_kbasic\0\0b\0clicked_0(bool)\0"
    "clicked_1(bool)\0clicked_2(bool)\0"
};

const QMetaObject _insert_option_kbasic::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_option_kbasic,
      qt_meta_data__insert_option_kbasic, 0 }
};

const QMetaObject *_insert_option_kbasic::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_option_kbasic::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_option_kbasic))
        return static_cast<void*>(const_cast< _insert_option_kbasic*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_option_kbasic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clicked_0((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: clicked_1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: clicked_2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data__insert_option_oldbasic[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__insert_option_oldbasic[] = {
    "_insert_option_oldbasic\0"
};

const QMetaObject _insert_option_oldbasic::staticMetaObject = {
    { &_insert_option_kbasic::staticMetaObject, qt_meta_stringdata__insert_option_oldbasic,
      qt_meta_data__insert_option_oldbasic, 0 }
};

const QMetaObject *_insert_option_oldbasic::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_option_oldbasic::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_option_oldbasic))
        return static_cast<void*>(const_cast< _insert_option_oldbasic*>(this));
    return _insert_option_kbasic::qt_metacast(_clname);
}

int _insert_option_oldbasic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert_option_kbasic::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data__insert_option_veryoldbasic[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__insert_option_veryoldbasic[] = {
    "_insert_option_veryoldbasic\0"
};

const QMetaObject _insert_option_veryoldbasic::staticMetaObject = {
    { &_insert_option_kbasic::staticMetaObject, qt_meta_stringdata__insert_option_veryoldbasic,
      qt_meta_data__insert_option_veryoldbasic, 0 }
};

const QMetaObject *_insert_option_veryoldbasic::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_option_veryoldbasic::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_option_veryoldbasic))
        return static_cast<void*>(const_cast< _insert_option_veryoldbasic*>(this));
    return _insert_option_kbasic::qt_metacast(_clname);
}

int _insert_option_veryoldbasic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert_option_kbasic::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data__insert_assignment[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_assignment[] = {
    "_insert_assignment\0\0textChanged()\0"
};

const QMetaObject _insert_assignment::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_assignment,
      qt_meta_data__insert_assignment, 0 }
};

const QMetaObject *_insert_assignment::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_assignment::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_assignment))
        return static_cast<void*>(const_cast< _insert_assignment*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_assignment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_statement[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_statement[] = {
    "_insert_statement\0\0textChanged()\0"
};

const QMetaObject _insert_statement::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_statement,
      qt_meta_data__insert_statement, 0 }
};

const QMetaObject *_insert_statement::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_statement::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_statement))
        return static_cast<void*>(const_cast< _insert_statement*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_statement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_expression[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_expression[] = {
    "_insert_expression\0\0textChanged()\0"
};

const QMetaObject _insert_expression::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_expression,
      qt_meta_data__insert_expression, 0 }
};

const QMetaObject *_insert_expression::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_expression::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_expression))
        return static_cast<void*>(const_cast< _insert_expression*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_expression::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_operator[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_operator[] = {
    "_insert_operator\0\0index\0activated(int)\0"
};

const QMetaObject _insert_operator::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_operator,
      qt_meta_data__insert_operator, 0 }
};

const QMetaObject *_insert_operator::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_operator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_operator))
        return static_cast<void*>(const_cast< _insert_operator*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_operator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_if[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_if[] = {
    "_insert_if\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_if::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_if,
      qt_meta_data__insert_if, 0 }
};

const QMetaObject *_insert_if::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_if::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_if))
        return static_cast<void*>(const_cast< _insert_if*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_if::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_select[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_select[] = {
    "_insert_select\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_select::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_select,
      qt_meta_data__insert_select, 0 }
};

const QMetaObject *_insert_select::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_select::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_select))
        return static_cast<void*>(const_cast< _insert_select*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_select::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_fornext[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      19,   17,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_fornext[] = {
    "_insert_fornext\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_fornext::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_fornext,
      qt_meta_data__insert_fornext, 0 }
};

const QMetaObject *_insert_fornext::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_fornext::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_fornext))
        return static_cast<void*>(const_cast< _insert_fornext*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_fornext::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_whileloop[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_whileloop[] = {
    "_insert_whileloop\0\0textChanged(QString)\0"
};

const QMetaObject _insert_whileloop::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_whileloop,
      qt_meta_data__insert_whileloop, 0 }
};

const QMetaObject *_insert_whileloop::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_whileloop::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_whileloop))
        return static_cast<void*>(const_cast< _insert_whileloop*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_whileloop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_loopwhile[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_loopwhile[] = {
    "_insert_loopwhile\0\0textChanged(QString)\0"
};

const QMetaObject _insert_loopwhile::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_loopwhile,
      qt_meta_data__insert_loopwhile, 0 }
};

const QMetaObject *_insert_loopwhile::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_loopwhile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_loopwhile))
        return static_cast<void*>(const_cast< _insert_loopwhile*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_loopwhile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_exception[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   19,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_exception[] = {
    "_insert_exception\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_exception::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_exception,
      qt_meta_data__insert_exception, 0 }
};

const QMetaObject *_insert_exception::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_exception::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_exception))
        return static_cast<void*>(const_cast< _insert_exception*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_exception::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_variable[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_variable[] = {
    "_insert_variable\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_variable::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_variable,
      qt_meta_data__insert_variable, 0 }
};

const QMetaObject *_insert_variable::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_variable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_variable))
        return static_cast<void*>(const_cast< _insert_variable*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_variable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_const[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_const[] = {
    "_insert_const\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_const::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_const,
      qt_meta_data__insert_const, 0 }
};

const QMetaObject *_insert_const::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_const::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_const))
        return static_cast<void*>(const_cast< _insert_const*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_const::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_sub[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_sub[] = {
    "_insert_sub\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_sub::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_sub,
      qt_meta_data__insert_sub, 0 }
};

const QMetaObject *_insert_sub::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_sub::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_sub))
        return static_cast<void*>(const_cast< _insert_sub*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_sub::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_function[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_function[] = {
    "_insert_function\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_function::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_function,
      qt_meta_data__insert_function, 0 }
};

const QMetaObject *_insert_function::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_function::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_function))
        return static_cast<void*>(const_cast< _insert_function*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_function::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_property[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_property[] = {
    "_insert_property\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_property::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_property,
      qt_meta_data__insert_property, 0 }
};

const QMetaObject *_insert_property::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_property::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_property))
        return static_cast<void*>(const_cast< _insert_property*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_property::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_type[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_type[] = {
    "_insert_type\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_type::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_type,
      qt_meta_data__insert_type, 0 }
};

const QMetaObject *_insert_type::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_type::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_type))
        return static_cast<void*>(const_cast< _insert_type*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_type::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_enum[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_enum[] = {
    "_insert_enum\0\0s\0textChanged(QString)\0"
};

const QMetaObject _insert_enum::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_enum,
      qt_meta_data__insert_enum, 0 }
};

const QMetaObject *_insert_enum::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_enum::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_enum))
        return static_cast<void*>(const_cast< _insert_enum*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_enum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__insert_remark[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__insert_remark[] = {
    "_insert_remark\0\0textChanged()\0"
};

const QMetaObject _insert_remark::staticMetaObject = {
    { &_insert::staticMetaObject, qt_meta_stringdata__insert_remark,
      qt_meta_data__insert_remark, 0 }
};

const QMetaObject *_insert_remark::metaObject() const
{
    return &staticMetaObject;
}

void *_insert_remark::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__insert_remark))
        return static_cast<void*>(const_cast< _insert_remark*>(this));
    return _insert::qt_metacast(_clname);
}

int _insert_remark::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = _insert::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
