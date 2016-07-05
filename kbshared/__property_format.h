
void SETPROPERTY_Format(const QString & n)
{ 
  if (GETPROPERTY_Format() != n){    

#if defined(_PROGRESSBAR)
    setFormat(n);
    setTextVisible(!n.isEmpty());
#elif defined(_DATEBOX)
    setDisplayFormat(n);
#elif defined(_TIMEBOX)
    setDisplayFormat(n);
#elif defined(_DATETIMEBOX)
    setDisplayFormat(n);
#endif

    _property::SETPROPERTY_Format(n);
  }
}
