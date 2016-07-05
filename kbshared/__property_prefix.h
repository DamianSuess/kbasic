
void SETPROPERTY_Prefix(const QString & n)
{ 
  if (GETPROPERTY_Prefix() != n){
    
    setPrefix(n);

    _property::SETPROPERTY_Prefix(n);
  }
}