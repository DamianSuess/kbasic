/****************************************************************************
** Meta object code from reading C++ file '_help.h'
**
** Created: Sat May 2 07:53:52 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_help.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_help.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__helpwindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__helpwindow[] = {
    "_helpwindow\0"
};

const QMetaObject _helpwindow::staticMetaObject = {
    { &QTextBrowser::staticMetaObject, qt_meta_stringdata__helpwindow,
      qt_meta_data__helpwindow, 0 }
};

const QMetaObject *_helpwindow::metaObject() const
{
    return &staticMetaObject;
}

void *_helpwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__helpwindow))
        return static_cast<void*>(const_cast< _helpwindow*>(this));
    return QTextBrowser::qt_metacast(_clname);
}

int _helpwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data__help[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata__help[] = {
    "_help\0"
};

const QMetaObject _help::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata__help,
      qt_meta_data__help, 0 }
};

const QMetaObject *_help::metaObject() const
{
    return &staticMetaObject;
}

void *_help::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__help))
        return static_cast<void*>(const_cast< _help*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int _help::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data__examplebrowser[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__examplebrowser[] = {
    "_examplebrowser\0\0perform()\0"
};

const QMetaObject _examplebrowser::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata__examplebrowser,
      qt_meta_data__examplebrowser, 0 }
};

const QMetaObject *_examplebrowser::metaObject() const
{
    return &staticMetaObject;
}

void *_examplebrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__examplebrowser))
        return static_cast<void*>(const_cast< _examplebrowser*>(this));
    return QDialog::qt_metacast(_clname);
}

int _examplebrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: perform(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
