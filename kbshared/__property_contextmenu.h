
void SETPROPERTY_ContextMenu(const QString & n)
{ 
  if (GETPROPERTY_ContextMenu() != n){  

#ifdef RUN
#ifdef _TOOLBARITEM
   my_toolbar_setMenuForButton(my_toolbar, n, this->GETPROPERTY_Name());
#else
   my_form_setMenuForButton(my_form, n, this);
#endif
#endif

    _property::SETPROPERTY_ContextMenu(n);
  }
}