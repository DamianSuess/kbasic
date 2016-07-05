
void SETPROPERTY_MaximumHeight(t_integer n)
{ 
  if (GETPROPERTY_MaximumHeight() != n){

    if (n == 0){        
      setMaximumHeight(QWIDGETSIZE_MAX);
    } else {
      setMaximumHeight(n);
    }    

    _property::SETPROPERTY_MaximumHeight(n);
  }
}