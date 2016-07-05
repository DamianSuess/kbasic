
void SETPROPERTY_Checkable(t_boolean n)
{ 
  if (GETPROPERTY_Checkable() != n){
    
#ifdef _MENUBARITEM
    if (my_qaction) my_qaction->setCheckable(n);
#else

#ifdef _TOOLBARITEM
    if (my_qaction) my_qaction->setCheckable(n);
#else
    setCheckable(n);
#endif

#endif

    _property::SETPROPERTY_Checkable(n);
  }
}
