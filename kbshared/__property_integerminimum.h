
void SETPROPERTY_IntegerMinimum(t_integer n)
{ 
  
  {

#if defined(_PROGRESSBAR)
    setMinimum(n);
    update();    
#elif defined(_SCROLLBAR)
    setMinimum(n);
#elif defined(_SLIDER)
    setMinimum(n);
#elif defined(_SPINBOX)
    setMinimum(n);
#endif
    

    _property::SETPROPERTY_IntegerMinimum(n);
  }
}