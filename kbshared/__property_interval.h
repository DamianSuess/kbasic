
void SETPROPERTY_Interval(t_integer n)
{ 

  {

    _property::SETPROPERTY_Interval(n);

#ifdef RUN
    t.setInterval(n);
    if (n == 0 && t.isActive()) t.stop();
    if (GETPROPERTY_Interval() >= 0 && GETPROPERTY_Enabled()) t.start();
#endif
  }
}