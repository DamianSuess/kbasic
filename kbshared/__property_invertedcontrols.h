
void SETPROPERTY_InvertedControls(t_boolean n)
{ 
  if (GETPROPERTY_InvertedControls() != n){
    
    setInvertedControls(n);

    _property::SETPROPERTY_InvertedControls(n);
  }
}
