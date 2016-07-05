
void SETPROPERTY_ValidatorRegEx2(const QString & n)
{ 
  if (GETPROPERTY_ValidatorRegEx2() != n){
    
#ifdef RUN
    setValidator(n.isEmpty() ? 0 : new QRegExpValidator(QRegExp(n, Qt::CaseSensitive, QRegExp::RegExp2), this));
#endif    

    _property::SETPROPERTY_ValidatorRegEx2(n);
  }
}