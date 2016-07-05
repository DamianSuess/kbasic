
void SETPROPERTY_Comment2End(const QString & n)
{ 
  if (GETPROPERTY_Comment2End() != n){    
  
    _property::SETPROPERTY_Comment2End(n);

    if (highlighter == 0) highlighter = new_highlighter(this, document());
    rehighlight(highlighter);
  }
}