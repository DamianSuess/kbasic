
void SETPROPERTY_ValidatorRegEx(const QString & n)
{ 
  if (GETPROPERTY_ValidatorRegEx() != n){
    
#ifdef RUN
    setValidator(n.isEmpty() ? 0 : new QRegExpValidator(QRegExp(n, Qt::CaseSensitive, QRegExp::RegExp), this));
#endif    

    _property::SETPROPERTY_ValidatorRegEx(n);
  }
}