
void SETPROPERTY_FontItalic(t_boolean n)
{ 
  if (GETPROPERTY_FontItalic() != n){
  
    QFont f = font();
    f.setItalic(n);
    setFont(f);          

    _property::SETPROPERTY_FontItalic(n);
  }
}