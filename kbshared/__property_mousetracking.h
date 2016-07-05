
void SETPROPERTY_MouseTracking(t_boolean n)
{ 
  if (GETPROPERTY_MouseTracking() != n){
    
#ifdef RUN
    setMouseTracking(n);
#ifdef _FORM
    main->setMouseTracking(n);
#endif
#endif
    _property::SETPROPERTY_MouseTracking(n);
  }
}