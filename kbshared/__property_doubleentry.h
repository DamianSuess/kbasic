
void SETPROPERTY_DoubleEntry(t_boolean n)
{ 
  if (GETPROPERTY_DoubleEntry() != n){
    
#ifdef _COMBOBOX
    setDuplicatesEnabled(n);
#endif

    _property::SETPROPERTY_DoubleEntry(n);
  }
}