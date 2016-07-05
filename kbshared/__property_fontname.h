
void SETPROPERTY_FontName(const QString & n)
{ 
  if (GETPROPERTY_FontName() != n){  

    QFont f = font();
    f.setFamily(n.isEmpty() ? f.defaultFamily() : n);
    setFont(f);      
    
    _property::SETPROPERTY_FontName(n);
  }
}