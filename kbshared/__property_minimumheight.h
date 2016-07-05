
void SETPROPERTY_MinimumHeight(t_integer n)
{ 
  if (GETPROPERTY_MinimumHeight() != n){

    setMinimumHeight(n);
    
    _property::SETPROPERTY_MinimumHeight(n);
  }
}