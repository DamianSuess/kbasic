
void SETPROPERTY_FontUnderline(t_boolean n)
{ 
  if (GETPROPERTY_FontUnderline() != n){
    
    QFont f = font();
    f.setUnderline(n);
    setFont(f);         

    _property::SETPROPERTY_FontUnderline(n);
  }
}