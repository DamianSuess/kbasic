
void SETPROPERTY_Flip(t_boolean n)
{ 
  if (GETPROPERTY_Flip() != n){

    _property::SETPROPERTY_Flip(n);

    SETPROPERTY_Flat(GETPROPERTY_Flat());


  }
}
