/****************************************************************************
** Meta object code from reading C++ file '_web.h'
**
** Created: Fri May 1 19:16:12 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_web.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_web.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_qwebpage[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_qwebpage[] = {
    "qwebpage\0"
};

const QMetaObject qwebpage::staticMetaObject = {
    { &QWebPage::staticMetaObject, qt_meta_stringdata_qwebpage,
      qt_meta_data_qwebpage, 0 }
};

const QMetaObject *qwebpage::metaObject() const
{
    return &staticMetaObject;
}

void *qwebpage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_qwebpage))
        return static_cast<void*>(const_cast< qwebpage*>(this));
    return QWebPage::qt_metacast(_clname);
}

int qwebpage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data__web[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       8,    6,    5,    5, 0x0a,
      25,    6,    5,    5, 0x0a,
      49,   43,    5,    5, 0x0a,
     126,   84,    5,    5, 0x0a,
     177,  169,    5,    5, 0x0a,
     222,  199,    5,    5, 0x0a,
     270,  267,    5,    5, 0x0a,
     298,  267,    5,    5, 0x0a,
     339,  330,    5,    5, 0x0a,
     366,  330,    5,    5, 0x0a,
     398,    5,    5,    5, 0x0a,
     420,    5,    5,    5, 0x0a,
     451,    5,    5,    5, 0x0a,
     469,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__web[] = {
    "_web\0\0u\0urlChanged(QUrl)\0linkClicked(QUrl)\0"
    "reply\0unsupportedContent(QNetworkReply*)\0"
    "BackwardAvailable,ForwardAvailable,NewURL\0"
    "EVENT_OnEvent(t_boolean,t_boolean,QString)\0"
    "NewPage\0EVENT_OnPage(QString)\0"
    "Link,Title,TextContent\0"
    "EVENT_OnLinkHovered(QString,QString,QString)\0"
    "Ok\0EVENT_OnLoadFinished2(bool)\0"
    "EVENT_OnLoadFinished(t_boolean)\0"
    "Progress\0EVENT_OnLoadProgress2(int)\0"
    "EVENT_OnLoadProgress(t_integer)\0"
    "EVENT_OnLoadStarted()\0"
    "EVENT_OnWindowCloseRequested()\0"
    "frameChanged(int)\0cursoranimation_frameChanged(int)\0"
};

const QMetaObject _web::staticMetaObject = {
    { &QWebView::staticMetaObject, qt_meta_stringdata__web,
      qt_meta_data__web, 0 }
};

const QMetaObject *_web::metaObject() const
{
    return &staticMetaObject;
}

void *_web::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__web))
        return static_cast<void*>(const_cast< _web*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _web*>(this));
    return QWebView::qt_metacast(_clname);
}

int _web::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: urlChanged((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 1: linkClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 2: unsupportedContent((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: EVENT_OnEvent((*reinterpret_cast< t_boolean(*)>(_a[1])),(*reinterpret_cast< t_boolean(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: EVENT_OnPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: EVENT_OnLinkHovered((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 6: EVENT_OnLoadFinished2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: EVENT_OnLoadFinished((*reinterpret_cast< t_boolean(*)>(_a[1]))); break;
        case 8: EVENT_OnLoadProgress2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: EVENT_OnLoadProgress((*reinterpret_cast< t_integer(*)>(_a[1]))); break;
        case 10: EVENT_OnLoadStarted(); break;
        case 11: EVENT_OnWindowCloseRequested(); break;
        case 12: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
