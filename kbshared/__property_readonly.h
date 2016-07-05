
void SETPROPERTY_ReadOnly(t_boolean n)
{ 
  if (GETPROPERTY_ReadOnly() != n){
    
#ifdef RUN
    setReadOnly(n);
#endif    

    _property::SETPROPERTY_ReadOnly(n);
  }
}