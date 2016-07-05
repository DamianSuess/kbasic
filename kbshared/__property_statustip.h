
void SETPROPERTY_StatusTip(const QString & n)
{ 
  if (GETPROPERTY_StatusTip() != n){  

#ifdef RUN
#if defined(_MENUBARITEM)
    if (my_qaction) my_qaction->setStatusTip(n);
#elif defined(_TOOLBARITEM)
    if (my_qaction) my_qaction->setStatusTip(n);
#else
    setStatusTip(n);
#endif
#endif
    

    _property::SETPROPERTY_StatusTip(n);
  }
}

