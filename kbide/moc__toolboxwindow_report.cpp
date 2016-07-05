/****************************************************************************
** Meta object code from reading C++ file '_toolboxwindow_report.h'
**
** Created: Sat May 2 07:55:42 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_toolboxwindow_report.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_toolboxwindow_report.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__toolboxwindow_report[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      33,   22,   22,   22, 0x08,
      41,   22,   22,   22, 0x08,
      51,   22,   22,   22, 0x08,
      62,   22,   22,   22, 0x08,
      70,   22,   22,   22, 0x08,
      84,   22,   22,   22, 0x08,
      92,   22,   22,   22, 0x08,
      98,   22,   22,   22, 0x08,
     107,   22,   22,   22, 0x08,
     117,   22,   22,   22, 0x08,
     127,   22,   22,   22, 0x08,
     137,   22,   22,   22, 0x08,
     151,   22,   22,   22, 0x08,
     160,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__toolboxwindow_report[] = {
    "_toolboxwindow_report\0\0pointer()\0"
    "label()\0textbox()\0checkbox()\0frame()\0"
    "progressbar()\0image()\0box()\0editor()\0"
    "browser()\0datebox()\0timebox()\0"
    "datetimebox()\0header()\0footer()\0"
};

const QMetaObject _toolboxwindow_report::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__toolboxwindow_report,
      qt_meta_data__toolboxwindow_report, 0 }
};

const QMetaObject *_toolboxwindow_report::metaObject() const
{
    return &staticMetaObject;
}

void *_toolboxwindow_report::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__toolboxwindow_report))
        return static_cast<void*>(const_cast< _toolboxwindow_report*>(this));
    return QWidget::qt_metacast(_clname);
}

int _toolboxwindow_report::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pointer(); break;
        case 1: label(); break;
        case 2: textbox(); break;
        case 3: checkbox(); break;
        case 4: frame(); break;
        case 5: progressbar(); break;
        case 6: image(); break;
        case 7: box(); break;
        case 8: editor(); break;
        case 9: browser(); break;
        case 10: datebox(); break;
        case 11: timebox(); break;
        case 12: datetimebox(); break;
        case 13: header(); break;
        case 14: footer(); break;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
