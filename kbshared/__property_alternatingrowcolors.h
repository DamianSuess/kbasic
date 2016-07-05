

void SETPROPERTY_AlternatingRowColors(t_boolean n)
{ 
  if (GETPROPERTY_AlternatingRowColors() != n){
    
    setAlternatingRowColors(n);

    _property::SETPROPERTY_AlternatingRowColors(n);
  }
}
