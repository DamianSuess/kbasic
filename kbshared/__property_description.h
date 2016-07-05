
void SETPROPERTY_Description(const QString & n)
{ 

  if (GETPROPERTY_Description() != n){
    setDescription(n);  
  }

  _property::SETPROPERTY_Description(n);
  
}
