
void SETPROPERTY_KeywordColor(const QString & n)
{ 
  if (GETPROPERTY_KeywordColor() != n){

    if (highlighter == 0) highlighter = new_highlighter(this, document());
    rehighlight(highlighter);
  
    _property::SETPROPERTY_KeywordColor(n);
  }
}