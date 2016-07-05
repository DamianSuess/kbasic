
void SETPROPERTY_FontBold(t_boolean n)
{ 
  if (GETPROPERTY_FontBold() != n){
    
    QFont f = font();
    f.setBold(n);
    setFont(f);      
  

    _property::SETPROPERTY_FontBold(n);
  }
}