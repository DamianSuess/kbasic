
void SETPROPERTY_FontSize(t_integer n)
{ 
  if (GETPROPERTY_FontSize() != n){  

    static int nOriginalFontSize = font().pointSize();

    QFont f = font();
    if (n > 0){
      f.setPointSize(n);
      setFont(f);      
    } else {
      f.setPointSize(nOriginalFontSize);
      setFont(f);      
    }
    
    _property::SETPROPERTY_FontSize(n);
  }
}