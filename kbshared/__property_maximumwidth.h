
void SETPROPERTY_MaximumWidth(t_integer n)
{ 
  if (GETPROPERTY_MaximumWidth() != n){

    if (n == 0){        
      setMaximumWidth(QWIDGETSIZE_MAX);
    } else {
      setMaximumWidth(n);
    }    

    _property::SETPROPERTY_MaximumWidth(n);
  }
}
