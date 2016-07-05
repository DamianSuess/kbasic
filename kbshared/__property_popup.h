
void SETPROPERTY_PopUp(t_boolean n)
{ 
  if (GETPROPERTY_PopUp() != n){
    
#ifdef RUN
      setCalendarPopup(n);
#endif

    _property::SETPROPERTY_PopUp(n);
  }
}