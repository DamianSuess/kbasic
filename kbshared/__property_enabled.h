
void SETPROPERTY_Enabled(t_boolean n)
{ 

  {
    
    {
#if defined(_TIMER)
  #ifdef RUN
    if (my_form_isOpened(my_form)){
      if (n){
        METHOD_Start();
      } else {
        METHOD_Stop();
      }
    }
  #endif
#elif defined(_MENUBARITEM)
  #ifdef RUN
     if (my_qaction) my_qaction->setEnabled(n);
  #endif
#elif defined(_TOOLBARITEM)
  #ifdef RUN
     if (my_qaction) my_qaction->setEnabled(n);
  #endif
#else 

      setEnabled(n);

#if defined(_LABEL)
  if (n == false){
    sEnabledText = text();
    QString s = "<font color='gray'>";
    s += sEnabledText;
    s += "</font>";
    setText(s);

  } else {
    setText(sEnabledText);
  }
#endif


#endif
    }

    _property::SETPROPERTY_Enabled(n);

#ifdef _IMAGEBUTTON
    if (GETPROPERTY_Checked()){
      if (GETPROPERTY_Enabled()){
        SETPROPERTY_CheckEnabledImage(GETPROPERTY_CheckEnabledImage());
      } else {
        SETPROPERTY_CheckDisabledImage(GETPROPERTY_CheckDisabledImage());
      }
    } else {
      if (GETPROPERTY_Enabled()){
        SETPROPERTY_EnabledImage(GETPROPERTY_EnabledImage());
      } else {
        SETPROPERTY_DisabledImage(GETPROPERTY_DisabledImage());
      }
    }
#endif

  }
}