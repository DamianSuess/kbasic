
void SETPROPERTY_X(t_integer n)
{ 
    if (GETPROPERTY_X() != n){   
#ifdef RUN
// CONTROL
#ifdef _SERIALPORT
#elif defined(_UDPSOCKET)
#elif defined(_TIMER)
#elif defined(_SOUND)
#else
    _SETPROPERTY_X(my_form, this, n);
    SETPROPERTY_GlobalX(this->mapToGlobal(QPoint(n, 0)).x());
#endif    
#endif    

    _property::SETPROPERTY_X(n);
   }
  
}
