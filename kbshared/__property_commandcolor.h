
void SETPROPERTY_CommandColor(const QString & n)
{ 
  if (GETPROPERTY_CommandColor() != n){

    if (highlighter == 0) highlighter = new_highlighter(this, document());
    rehighlight(highlighter);
  
    _property::SETPROPERTY_CommandColor(n);
  }
}