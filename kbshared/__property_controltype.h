
void SETPROPERTY_ControlType(const QString & n)
{ 

  if (GETPROPERTY_ControlType() != n){

#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
#elif defined(_TABLEITEM)
#else      


    setProperty("__kb1979.ControlType.kb__", QVariant(n));
#endif
    _property::SETPROPERTY_ControlType(n);
  }

}
