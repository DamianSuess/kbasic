/****************************************************************************
** Meta object code from reading C++ file '_propertywidget.h'
**
** Created: Sat May 2 07:54:28 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_propertywidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_propertywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__property_header[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__property_header[] = {
    "_property_header\0"
};

const QMetaObject _property_header::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata__property_header,
      qt_meta_data__property_header, 0 }
};

const QMetaObject *_property_header::metaObject() const
{
    return &staticMetaObject;
}

void *_property_header::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_header))
        return static_cast<void*>(const_cast< _property_header*>(this));
    return QLabel::qt_metacast(_clname);
}

int _property_header::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data__property_label[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__property_label[] = {
    "_property_label\0"
};

const QMetaObject _property_label::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata__property_label,
      qt_meta_data__property_label, 0 }
};

const QMetaObject *_property_label::metaObject() const
{
    return &staticMetaObject;
}

void *_property_label::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_label))
        return static_cast<void*>(const_cast< _property_label*>(this));
    return QLabel::qt_metacast(_clname);
}

int _property_label::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data__property_linelabel[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

       0        // eod
};

static const char qt_meta_stringdata__property_linelabel[] = {
    "_property_linelabel\0\0textChanged()\0"
};

const QMetaObject _property_linelabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata__property_linelabel,
      qt_meta_data__property_linelabel, 0 }
};

const QMetaObject *_property_linelabel::metaObject() const
{
    return &staticMetaObject;
}

void *_property_linelabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_linelabel))
        return static_cast<void*>(const_cast< _property_linelabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int _property_linelabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void _property_linelabel::textChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data__property_lineedit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      31,   19,   19,   19, 0x0a,
      47,   19,   19,   19, 0x0a,
      64,   19,   19,   19, 0x0a,
      87,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__property_lineedit[] = {
    "_property_lineedit\0\0showHelp()\0"
    "checkOldValue()\0checkOldValue2()\0"
    "emit_editingFinished()\0textChanged()\0"
};

const QMetaObject _property_lineedit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata__property_lineedit,
      qt_meta_data__property_lineedit, 0 }
};

const QMetaObject *_property_lineedit::metaObject() const
{
    return &staticMetaObject;
}

void *_property_lineedit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_lineedit))
        return static_cast<void*>(const_cast< _property_lineedit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int _property_lineedit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showHelp(); break;
        case 1: checkOldValue(); break;
        case 2: checkOldValue2(); break;
        case 3: emit_editingFinished(); break;
        case 4: textChanged(); break;
        }
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data__property_booleancombobox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__property_booleancombobox[] = {
    "_property_booleancombobox\0\0highlighted()\0"
};

const QMetaObject _property_booleancombobox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata__property_booleancombobox,
      qt_meta_data__property_booleancombobox, 0 }
};

const QMetaObject *_property_booleancombobox::metaObject() const
{
    return &staticMetaObject;
}

void *_property_booleancombobox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_booleancombobox))
        return static_cast<void*>(const_cast< _property_booleancombobox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int _property_booleancombobox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: highlighted(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__property_listcombobox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__property_listcombobox[] = {
    "_property_listcombobox\0"
};

const QMetaObject _property_listcombobox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata__property_listcombobox,
      qt_meta_data__property_listcombobox, 0 }
};

const QMetaObject *_property_listcombobox::metaObject() const
{
    return &staticMetaObject;
}

void *_property_listcombobox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_listcombobox))
        return static_cast<void*>(const_cast< _property_listcombobox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int _property_listcombobox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data__property_coloredit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      34,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__property_coloredit[] = {
    "_property_coloredit\0\0checkColor()\0"
    "getColor()\0"
};

const QMetaObject _property_coloredit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__property_coloredit,
      qt_meta_data__property_coloredit, 0 }
};

const QMetaObject *_property_coloredit::metaObject() const
{
    return &staticMetaObject;
}

void *_property_coloredit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_coloredit))
        return static_cast<void*>(const_cast< _property_coloredit*>(this));
    return QWidget::qt_metacast(_clname);
}

int _property_coloredit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkColor(); break;
        case 1: getColor(); break;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data__property_imageedit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      31,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__property_imageedit[] = {
    "_property_imageedit\0\0getFile()\0"
    "getFile2()\0"
};

const QMetaObject _property_imageedit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__property_imageedit,
      qt_meta_data__property_imageedit, 0 }
};

const QMetaObject *_property_imageedit::metaObject() const
{
    return &staticMetaObject;
}

void *_property_imageedit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_imageedit))
        return static_cast<void*>(const_cast< _property_imageedit*>(this));
    return QWidget::qt_metacast(_clname);
}

int _property_imageedit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getFile(); break;
        case 1: getFile2(); break;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data__property_fileedit[] = {

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

static const char qt_meta_stringdata__property_fileedit[] = {
    "_property_fileedit\0\0getFile()\0"
};

const QMetaObject _property_fileedit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__property_fileedit,
      qt_meta_data__property_fileedit, 0 }
};

const QMetaObject *_property_fileedit::metaObject() const
{
    return &staticMetaObject;
}

void *_property_fileedit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_fileedit))
        return static_cast<void*>(const_cast< _property_fileedit*>(this));
    return QWidget::qt_metacast(_clname);
}

int _property_fileedit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getFile(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__property_soundedit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__property_soundedit[] = {
    "_property_soundedit\0\0getFile()\0"
};

const QMetaObject _property_soundedit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__property_soundedit,
      qt_meta_data__property_soundedit, 0 }
};

const QMetaObject *_property_soundedit::metaObject() const
{
    return &staticMetaObject;
}

void *_property_soundedit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_soundedit))
        return static_cast<void*>(const_cast< _property_soundedit*>(this));
    return QWidget::qt_metacast(_clname);
}

int _property_soundedit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getFile(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__property_pixeledit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__property_pixeledit[] = {
    "_property_pixeledit\0\0getFile()\0"
};

const QMetaObject _property_pixeledit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__property_pixeledit,
      qt_meta_data__property_pixeledit, 0 }
};

const QMetaObject *_property_pixeledit::metaObject() const
{
    return &staticMetaObject;
}

void *_property_pixeledit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_pixeledit))
        return static_cast<void*>(const_cast< _property_pixeledit*>(this));
    return QWidget::qt_metacast(_clname);
}

int _property_pixeledit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getFile(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__property_colorimageedit[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,
      36,   25,   25,   25, 0x0a,
      47,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__property_colorimageedit[] = {
    "_property_colorimageedit\0\0getFile()\0"
    "getFile2()\0getColor()\0"
};

const QMetaObject _property_colorimageedit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__property_colorimageedit,
      qt_meta_data__property_colorimageedit, 0 }
};

const QMetaObject *_property_colorimageedit::metaObject() const
{
    return &staticMetaObject;
}

void *_property_colorimageedit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_colorimageedit))
        return static_cast<void*>(const_cast< _property_colorimageedit*>(this));
    return QWidget::qt_metacast(_clname);
}

int _property_colorimageedit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getFile(); break;
        case 1: getFile2(); break;
        case 2: getColor(); break;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data__property_choicebox[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__property_choicebox[] = {
    "_property_choicebox\0\0get()\0"
};

const QMetaObject _property_choicebox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__property_choicebox,
      qt_meta_data__property_choicebox, 0 }
};

const QMetaObject *_property_choicebox::metaObject() const
{
    return &staticMetaObject;
}

void *_property_choicebox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_choicebox))
        return static_cast<void*>(const_cast< _property_choicebox*>(this));
    return QWidget::qt_metacast(_clname);
}

int _property_choicebox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: get(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__property_fontedit[] = {

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

static const char qt_meta_stringdata__property_fontedit[] = {
    "_property_fontedit\0\0getFont()\0"
};

const QMetaObject _property_fontedit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__property_fontedit,
      qt_meta_data__property_fontedit, 0 }
};

const QMetaObject *_property_fontedit::metaObject() const
{
    return &staticMetaObject;
}

void *_property_fontedit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_fontedit))
        return static_cast<void*>(const_cast< _property_fontedit*>(this));
    return QWidget::qt_metacast(_clname);
}

int _property_fontedit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getFont(); break;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data__property_event[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   17,   16,   16, 0x0a,
      57,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__property_event[] = {
    "_property_event\0\0_pw\0"
    "setPropertyWindow(_propertywindow*)\0"
    "goEvent()\0"
};

const QMetaObject _property_event::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__property_event,
      qt_meta_data__property_event, 0 }
};

const QMetaObject *_property_event::metaObject() const
{
    return &staticMetaObject;
}

void *_property_event::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__property_event))
        return static_cast<void*>(const_cast< _property_event*>(this));
    return QWidget::qt_metacast(_clname);
}

int _property_event::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setPropertyWindow((*reinterpret_cast< _propertywindow*(*)>(_a[1]))); break;
        case 1: goEvent(); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
