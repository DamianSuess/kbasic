

void SETPROPERTY_TimerInterval(t_integer n)
{ 
  
  {

    _property::SETPROPERTY_TimerInterval(n);

#ifdef RUN
#ifdef _FORM
    if (bLoading == false){
      if (nTimerId != 0) killTimer(nTimerId);
      nTimerId = startTimer(n == -1 ? n : n); // setting -1 in IDE means setting 0 for qt->void heavy cpu usage in form.timerinterval
    }
#else
#endif
#endif
  }
}

