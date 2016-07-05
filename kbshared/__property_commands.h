
void SETPROPERTY_Commands(const QString & n)
{ 
  if (GETPROPERTY_Commands() != n){    
  
    _property::SETPROPERTY_Commands(n);

    if (highlighter == 0) highlighter = new_highlighter(this, document());
    rehighlight(highlighter);
  }
}