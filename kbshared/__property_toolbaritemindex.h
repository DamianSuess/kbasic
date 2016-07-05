
void SETPROPERTY_ToolBarItemIndex(const QString & n)
{ 
  if (GETPROPERTY_ToolBarItemIndex() != n){

    if (n.isEmpty()){
    } else {
      int i = n.toInt();
      nIndex = i;
    }
  
    _property::SETPROPERTY_ToolBarItemIndex(n);
  }
}
