
void SETPROPERTY_ValidatorDouble(t_boolean n)
{ 
  if (GETPROPERTY_ValidatorDouble() != n){
    
#ifdef RUN
    setValidator(n ? new QDoubleValidator(this) : 0);
#endif    

    _property::SETPROPERTY_ValidatorDouble(n);
  }
}