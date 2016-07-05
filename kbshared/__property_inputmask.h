
void SETPROPERTY_InputMask(const QString & n)
{ 
  if (GETPROPERTY_InputMask() != n){
    
#ifdef RUN
    setInputMask(n);
#endif

    _property::SETPROPERTY_InputMask(n);
  }
}