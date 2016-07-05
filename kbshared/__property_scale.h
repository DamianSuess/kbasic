
void SETPROPERTY_Scale(t_boolean n)
{ 
  if (GETPROPERTY_Scale() != n){
        
#ifdef _LABEL
    setScaledContents(n);
#endif    

    _property::SETPROPERTY_Scale(n);
  }
}