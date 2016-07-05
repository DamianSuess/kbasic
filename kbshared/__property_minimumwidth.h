
void SETPROPERTY_MinimumWidth(t_integer n)
{ 
  if (GETPROPERTY_MinimumWidth() != n){

    setMinimumWidth(n);
    
    _property::SETPROPERTY_MinimumWidth(n);
  }
}