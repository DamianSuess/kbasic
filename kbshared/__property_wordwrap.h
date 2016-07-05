
void SETPROPERTY_WordWrap(t_boolean n)
{ 
  if (GETPROPERTY_WordWrap() != n){
       
#ifdef _EDITOR
    setLineWrapMode(n ? QTextEdit::WidgetWidth : QTextEdit::NoWrap);
#else
    setWordWrap(n);
#endif
    
    _property::SETPROPERTY_WordWrap(n);
  }
}