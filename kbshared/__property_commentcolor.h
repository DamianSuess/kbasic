
void SETPROPERTY_CommentColor(const QString & n)
{ 
  if (GETPROPERTY_CommentColor() != n){

    if (highlighter == 0) highlighter = new_highlighter(this, document());
    rehighlight(highlighter);  
    
    _property::SETPROPERTY_CommentColor(n);
  }
}