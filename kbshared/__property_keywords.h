
void SETPROPERTY_Keywords(const QString & n)
{ 
  if (GETPROPERTY_Keywords() != n){    
  
    _property::SETPROPERTY_Keywords(n);

    if (highlighter == 0) highlighter = new_highlighter(this, document());
    rehighlight(highlighter);
  }
}