
void SETPROPERTY_Y(t_integer n)
{ 
   if (GETPROPERTY_Y() != n){

#ifdef RUN
// CONTROL
#ifdef _SERIALPORT
#elif defined(_UDPSOCKET)
#elif defined(_TIMER)
#elif defined(_SOUND)
#else
    _SETPROPERTY_Y(my_form, this, n);
    SETPROPERTY_GlobalY(this->mapToGlobal(QPoint(0, n)).y());
#endif
#endif    

    _property::SETPROPERTY_Y(n);
   }
  
}