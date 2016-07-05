/****************************************************************************
** Meta object code from reading C++ file '_toolboxwindow_vista.h'
**
** Created: Sat May 2 07:55:47 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "_toolboxwindow_vista.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_toolboxwindow_vista.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__toolboxwindow_vista[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      32,   21,   21,   21, 0x08,
      44,   21,   21,   21, 0x08,
      57,   21,   21,   21, 0x08,
      83,   21,   21,   21, 0x08,
     104,   21,   21,   21, 0x08,
     128,   21,   21,   21, 0x08,
     152,   21,   21,   21, 0x08,
     177,   21,   21,   21, 0x08,
     203,   21,   21,   21, 0x08,
     221,   21,   21,   21, 0x08,
     239,   21,   21,   21, 0x08,
     260,   21,   21,   21, 0x08,
     280,   21,   21,   21, 0x08,
     308,   21,   21,   21, 0x08,
     332,   21,   21,   21, 0x08,
     356,   21,   21,   21, 0x08,
     383,   21,   21,   21, 0x08,
     405,   21,   21,   21, 0x08,
     425,   21,   21,   21, 0x08,
     446,   21,   21,   21, 0x08,
     473,   21,   21,   21, 0x08,
     497,   21,   21,   21, 0x08,
     521,   21,   21,   21, 0x08,
     544,   21,   21,   21, 0x08,
     568,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata__toolboxwindow_vista[] = {
    "_toolboxwindow_vista\0\0pointer()\0"
    "vista_bar()\0vista_ball()\0"
    "vista_bar_commandbutton()\0"
    "vista_window_close()\0vista_window_minimize()\0"
    "vista_window_maximize()\0"
    "vista_button_arrowleft()\0"
    "vista_button_arrowright()\0vista_box_black()\0"
    "vista_box_white()\0vista_window_white()\0"
    "vista_icon_search()\0vista_imagebox_whiteblack()\0"
    "vista_separator_white()\0vista_separator_black()\0"
    "vista_textbox_whiteblack()\0"
    "vista_button_middle()\0vista_button_left()\0"
    "vista_button_right()\0vista_buttonblack_middle()\0"
    "vista_selection_black()\0vista_selection_white()\0"
    "vista_navigation_bar()\0vista_navigation_left()\0"
    "vista_navigation_right()\0"
};

const QMetaObject _toolboxwindow_vista::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata__toolboxwindow_vista,
      qt_meta_data__toolboxwindow_vista, 0 }
};

const QMetaObject *_toolboxwindow_vista::metaObject() const
{
    return &staticMetaObject;
}

void *_toolboxwindow_vista::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__toolboxwindow_vista))
        return static_cast<void*>(const_cast< _toolboxwindow_vista*>(this));
    return QWidget::qt_metacast(_clname);
}

int _toolboxwindow_vista::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pointer(); break;
        case 1: vista_bar(); break;
        case 2: vista_ball(); break;
        case 3: vista_bar_commandbutton(); break;
        case 4: vista_window_close(); break;
        case 5: vista_window_minimize(); break;
        case 6: vista_window_maximize(); break;
        case 7: vista_button_arrowleft(); break;
        case 8: vista_button_arrowright(); break;
        case 9: vista_box_black(); break;
        case 10: vista_box_white(); break;
        case 11: vista_window_white(); break;
        case 12: vista_icon_search(); break;
        case 13: vista_imagebox_whiteblack(); break;
        case 14: vista_separator_white(); break;
        case 15: vista_separator_black(); break;
        case 16: vista_textbox_whiteblack(); break;
        case 17: vista_button_middle(); break;
        case 18: vista_button_left(); break;
        case 19: vista_button_right(); break;
        case 20: vista_buttonblack_middle(); break;
        case 21: vista_selection_black(); break;
        case 22: vista_selection_white(); break;
        case 23: vista_navigation_bar(); break;
        case 24: vista_navigation_left(); break;
        case 25: vista_navigation_right(); break;
        }
        _id -= 26;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
