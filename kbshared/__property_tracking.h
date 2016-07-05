
void SETPROPERTY_Tracking(t_boolean n)
{ 
  if (GETPROPERTY_Tracking() != n){
    
#ifdef _SCROLLBAR
    setTracking(n);
#endif

#ifdef _SLIDER
    setTracking(n);
#endif

#ifdef _SPINBOX
    setKeyboardTracking(n);
#endif

    _property::SETPROPERTY_Tracking(n);
  }
}
