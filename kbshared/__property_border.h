
void SETPROPERTY_Border(t_integer n)
{ 
  if (GETPROPERTY_Border() != n){

    layout()->setMargin(n);      

    _property::SETPROPERTY_Border(n);

  }
}
