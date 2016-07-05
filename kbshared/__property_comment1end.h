
void SETPROPERTY_Comment1End(const QString & n)
{ 
  if (GETPROPERTY_Comment1End() != n){    
  
    _property::SETPROPERTY_Comment1End(n);

    if (highlighter == 0) highlighter = new_highlighter(this, document());
    rehighlight(highlighter);
  }
}