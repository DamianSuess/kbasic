
void SETPROPERTY_InvertedAppearance(t_boolean n)
{ 
  if (GETPROPERTY_InvertedAppearance() != n){
    
    setInvertedAppearance(n);

    _property::SETPROPERTY_InvertedAppearance(n);
  }
}
