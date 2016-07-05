
void SETPROPERTY_IntegerMaximum(t_integer n)
{ 
  
  {

#if defined(_TEXTBOX)    
    if (n) setMaxLength(n);
#elif defined(_SLIDER)
    setMaximum(n);
#elif defined(_SCROLLBAR)
    setMaximum(n);
#elif defined(_SPINBOX)
    setMaximum(n);
#elif defined(_COMBOBOX)
    if (n > 0) setMaxCount(n);
#elif defined(_PROGRESSBAR)
    setMaximum(n);
    update();
    //setValue(value()); // need for updated on screen
#endif
    

    _property::SETPROPERTY_IntegerMaximum(n);
  }
}