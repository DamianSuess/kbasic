
void SETPROPERTY_Default(t_boolean n)
{ 
  if (GETPROPERTY_Default() != n){
    
    setDefault(n);

    _property::SETPROPERTY_Default(n);
  }
}
