
void SETPROPERTY_StyleSheet(const QString & n)
{ 
  if (GETPROPERTY_StyleSheet() != n){  


    setStyleSheet(n);
 

    _property::SETPROPERTY_StyleSheet(n);
  }
}

