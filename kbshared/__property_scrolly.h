
void SETPROPERTY_ScrollY(t_integer n)
{ 
  if (GETPROPERTY_ScrollY() != n){

#ifdef RUN
#if defined(_FORM)
    this->verticalScrollBar()->setValue(n);
#endif
#endif

    _property::SETPROPERTY_ScrollY(n);
  }
}
