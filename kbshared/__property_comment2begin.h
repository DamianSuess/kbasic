
void SETPROPERTY_Comment2Begin(const QString & n)
{ 
  if (GETPROPERTY_Comment2Begin() != n){    
  
    _property::SETPROPERTY_Comment2Begin(n);

    if (highlighter == 0) highlighter = new_highlighter(this, document());
    rehighlight(highlighter);
  }
}