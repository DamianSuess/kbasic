
void SETPROPERTY_MaximumVisible(t_integer n)
{ 
  if (GETPROPERTY_MaximumVisible() != n){

#ifdef RUN
#ifdef _COMBOBOX
    if (n) setMaxVisibleItems(n);
#endif
#endif

    _property::SETPROPERTY_MaximumVisible(n);
  }
}