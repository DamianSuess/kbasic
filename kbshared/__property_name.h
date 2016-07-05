
void SETPROPERTY_Name(const QString & n)
{ 


  if (GETPROPERTY_Name() != n){

#ifdef RUN
  #if defined(_MENUBARITEM)
  #elif defined(_TOOLBARITEM)
  #elif defined(_FORM)
  #else
      my_form_readdToCollection(my_form, this, GETPROPERTY_Name(), sName, TEST3);
  #endif
#endif

#ifdef IDE
// CONTROL
#ifdef _TIMER
    QString r = "Control 'Timer' ";
    r += n;
    setText(r);
#endif
#ifdef _UDPSOCKET
    QString r = "Control 'UdpSocket' ";
    r += n;
    setText(r);
#endif
#ifdef _SERIALPORT
    QString r = "Control 'SerialPort' ";
    r += n;
    setText(r);
#endif
#ifdef _MOVIE
    QString r = "Control 'MovieBox' ";
    r += n;
    setText(r);
#endif
#ifdef _SOUND
    QString r = "Control 'Sound' ";
    r += n;
    setText(r);
#endif
#ifdef _HIDDEN
    QString r = "Control 'Hidden' ";
    r += n;
    setText(r);
#endif
#endif


#if defined(_MENUBARITEM)

  #ifdef RUN
    sName = n;
    a = sName.toAscii();
    acName = a.data();
  #endif

#elif defined(_TOOLBARITEM)

  #ifdef RUN
    sName = n;
    a = sName.toAscii();
    acName = a.data();
  #endif

#elif defined(_TABLEITEM)
#else
  setObjectName(n);

#ifdef IDE
  setToolTip(objectName() + " As " + property("__kb1979.ControlType.kb__").toString());
#endif

  #ifdef RUN
    sName = n;
    a = sName.toAscii();
#ifdef _FORM
    // events are always named with Form: Form_EVENTNAME(...)
#else
    acName = a.data();
#endif

  #endif

#endif
    _property::SETPROPERTY_Name(n);
  }

}

