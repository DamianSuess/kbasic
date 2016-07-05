
void SETPROPERTY_SingleStep(t_integer n)
{ 
 
#ifdef _SCROLLBAR
  setSingleStep(n);
#endif

#ifdef _SLIDER
  setSingleStep(n);
#endif

#ifdef _SPINBOX
  setSingleStep(n);
#endif

  _property::SETPROPERTY_SingleStep(n);
 
}
