
void SETPROPERTY_Comment1Begin(const QString & n)
{ 
  if (GETPROPERTY_Comment1Begin() != n){

    _property::SETPROPERTY_Comment1Begin(n);

    if (highlighter == 0) highlighter = new_highlighter(this, document());
    rehighlight(highlighter);      
  }
}