
void SETPROPERTY_Space(t_integer n)
{ 
  if (GETPROPERTY_Space() != n){
    
    layout()->setSpacing(n);

    _property::SETPROPERTY_Space(n);
  }
}
