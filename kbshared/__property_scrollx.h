
void SETPROPERTY_ScrollX(t_integer n)
{ 
  if (GETPROPERTY_ScrollX() != n){

#ifdef RUN
#if defined(_FORM)
    this->horizontalScrollBar()->setValue(n);

#endif
#endif

    _property::SETPROPERTY_ScrollX(n);
  }
}
