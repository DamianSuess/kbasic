/****************************************************************************
** Meta object code from reading C++ file '_sound.h'
**
** Created: Fri May 1 19:14:15 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kbshared/_sound.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file '_sound.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data__sound[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      26,    8,    7,    7, 0x0a,
      68,    7,    7,    7, 0x0a,
      84,    7,    7,    7, 0x0a,
      95,    7,    7,    7, 0x0a,
     110,    7,    7,    7, 0x0a,
     128,  126,    7,    7, 0x0a,
     167,  149,    7,    7, 0x0a,
     205,    7,    7,    7, 0x0a,
     229,    7,    7,    7, 0x0a,
     248,  126,    7,    7, 0x0a,
     280,  126,    7,    7, 0x0a,
     313,  126,    7,    7, 0x0a,
     350,  126,    7,    7, 0x0a,
     382,  126,    7,    7, 0x0a,
     415,    7,    7,    7, 0x0a,
     433,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata__sound[] = {
    "_sound\0\0newstate,oldstate\0"
    "stateChanged(Phonon::State,Phonon::State)\0"
    "aboutToFinish()\0finished()\0SoundOnEvent()\0"
    "EVENT_OnEvent()\0n\0EVENT_OnTick(t_long)\0"
    "NewState,OldState\0"
    "EVENT_OnStateChanged(QString,QString)\0"
    "EVENT_OnAboutToFinish()\0EVENT_OnFinished()\0"
    "EVENT_OnMutedChanged(t_boolean)\0"
    "EVENT_OnVolumeChanged(t_integer)\0"
    "EVENT_OnPlayingTitleChanged(QString)\0"
    "EVENT_OnBufferStatus(t_integer)\0"
    "EVENT_OnTotalTimeChanged(t_long)\0"
    "frameChanged(int)\0cursoranimation_frameChanged(int)\0"
};

const QMetaObject _sound::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata__sound,
      qt_meta_data__sound, 0 }
};

const QMetaObject *_sound::metaObject() const
{
    return &staticMetaObject;
}

void *_sound::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata__sound))
        return static_cast<void*>(const_cast< _sound*>(this));
    if (!strcmp(_clname, "_property"))
        return static_cast< _property*>(const_cast< _sound*>(this));
    return QLabel::qt_metacast(_clname);
}

int _sound::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 1: aboutToFinish(); break;
        case 2: finished(); break;
        case 3: SoundOnEvent(); break;
        case 4: EVENT_OnEvent(); break;
        case 5: EVENT_OnTick((*reinterpret_cast< t_long(*)>(_a[1]))); break;
        case 6: EVENT_OnStateChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: EVENT_OnAboutToFinish(); break;
        case 8: EVENT_OnFinished(); break;
        case 9: EVENT_OnMutedChanged((*reinterpret_cast< t_boolean(*)>(_a[1]))); break;
        case 10: EVENT_OnVolumeChanged((*reinterpret_cast< t_integer(*)>(_a[1]))); break;
        case 11: EVENT_OnPlayingTitleChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: EVENT_OnBufferStatus((*reinterpret_cast< t_integer(*)>(_a[1]))); break;
        case 13: EVENT_OnTotalTimeChanged((*reinterpret_cast< t_long(*)>(_a[1]))); break;
        case 14: frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: cursoranimation_frameChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
