
void SETPROPERTY_Editable(t_boolean n)
{ 
  if (GETPROPERTY_Editable() != n){
    
#ifdef _COMBOBOX
    setEditable(n);
#endif

    _property::SETPROPERTY_Editable(n);
  }
}