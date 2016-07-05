
void SETPROPERTY_Suffix(const QString & n)
{ 
  if (GETPROPERTY_Suffix() != n){
    
    setSuffix(n);

    _property::SETPROPERTY_Suffix(n);
  }
}