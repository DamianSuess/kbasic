
void SETPROPERTY_ValidatorInteger(t_boolean n)
{ 
  if (GETPROPERTY_ValidatorInteger() != n){
    
#ifdef RUN
    setValidator(n ? new QIntValidator(this) : 0);
#endif    

    _property::SETPROPERTY_ValidatorInteger(n);
  }
}