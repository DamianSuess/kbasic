
void SETPROPERTY_WhatsThis(const QString & n)
{ 
  if (GETPROPERTY_WhatsThis() != n){  

#ifdef RUN
#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
    if (my_qaction) my_qaction->setWhatsThis(n);
#else
    setWhatsThis(n);
#endif
#endif

    _property::SETPROPERTY_WhatsThis(n);
  }
}

