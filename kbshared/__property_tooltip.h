
void SETPROPERTY_ToolTip(const QString & n)
{ 
  if (GETPROPERTY_ToolTip() != n){  

#ifdef RUN
#if defined(_MENUBARITEM)
    if (my_qaction) my_qaction->setToolTip(n);
#elif defined(_TOOLBARITEM)
    if (my_qaction){
      my_qaction->setToolTip(n);
      my_qaction->setVisible(true);
    }
    
#else
    setToolTip(n);
#endif
#endif  

    _property::SETPROPERTY_ToolTip(n);
  }
}

