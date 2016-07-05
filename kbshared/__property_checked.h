
void SETPROPERTY_Checked(t_boolean n)
{ 
  //if (GETPROPERTY_Checked() != n)
  {        

#if defined(_MENUBARITEM)
  #ifdef RUN
    if (my_qaction){
      my_qaction->setChecked(n);
    }
  #endif
#endif    

#if defined(_TOOLBARITEM)
  #ifdef RUN
    if (my_qaction){
      my_qaction->setChecked(n);
    }
  #endif
#endif    

#if defined(_COMMANDBUTTON)
    QString s = GETPROPERTY_Group();
    if (s.isEmpty()){
      setChecked(n);
    } else {
      my_form_setCommandButtonBooleanValue(my_form, s, this, n);
    }        
#endif  


#if defined(_COMMANDLINKBUTTON)
    QString s = GETPROPERTY_Group();
    if (s.isEmpty()){
      setChecked(n);
    } else {
      my_form_setCommandLinkButtonBooleanValue(my_form, s, this, n);
    }        
#endif  

#if defined(_IMAGEBUTTON)
    QString s = GETPROPERTY_Group();
    if (s.isEmpty()){
      _property::SETPROPERTY_Checked(n);
    } else {
      my_form_setImageButtonBooleanValue(my_form, s, this, n);
    }        
#endif  
    _property::SETPROPERTY_Checked(n);
  }

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

void SETPROPERTY_Checked2(t_boolean n)
{
   _property::SETPROPERTY_Checked(n);
}


t_boolean GETPROPERTY_Checked()
{
#if defined(_MENUBARITEM)
  #ifdef RUN
    if (my_qaction){
      bool b = my_qaction->isChecked();
      return b;
    }
  #endif
#endif    

#if defined(_TOOLBARITEM)
  #ifdef RUN
    if (my_qaction){
      bool b = my_qaction->isChecked();
      return b;
    }
  #endif
#endif    

#if defined(_COMMANDBUTTON) || defined(_COMMANDLINKBUTTON) || defined(_TOOLBUTTON)
   bool b = isChecked();
   return b; 
#endif  

#if defined(_IMAGEBUTTON)
   bool b = _property::GETPROPERTY_Checked();
   return b; 
#endif  
   return false;
}

t_boolean GETPROPERTY_Checked2()
{
  return _property::GETPROPERTY_Checked();
}