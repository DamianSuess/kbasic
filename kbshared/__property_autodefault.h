
void SETPROPERTY_AutoDefault(t_boolean n)
{ 
  if (GETPROPERTY_AutoDefault() != n){
    
    setAutoDefault(n);

    _property::SETPROPERTY_AutoDefault(n);
  }
}
