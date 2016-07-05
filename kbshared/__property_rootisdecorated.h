

void SETPROPERTY_RootIsDecorated(t_boolean n)
{ 
  if (GETPROPERTY_RootIsDecorated() != n){
    
    setRootIsDecorated(n);

    _property::SETPROPERTY_RootIsDecorated(n);
  }
}

t_boolean GETPROPERTY_IsAlternatingRowColors()
{
  return rootIsDecorated();
}
