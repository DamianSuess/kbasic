
void SETPROPERTY_MenuItemIndex(const QString & n)
{ 
  if (GETPROPERTY_MenuItemIndex() != n){

    if (n.isEmpty()){
    } else {
      int i = n.toInt();
      nIndex = i;
    }
    
    _property::SETPROPERTY_MenuItemIndex(n);
  }
}
