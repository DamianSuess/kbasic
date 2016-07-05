
void SETPROPERTY_IntegerValue(t_integer n)
{ 
  
  {

#if defined(_PROGRESSBAR)
    setValue(n);
#endif

#if defined(_SLIDER)
    setValue(n);
#endif

#if defined(_SCROLLBAR)
    setValue(n);
#endif

#if defined(_SPINBOX)
    setValue(n);
#endif

    _property::SETPROPERTY_IntegerValue(n);
  }
}
