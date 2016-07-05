
void SETPROPERTY_Focus(t_boolean n)
{ 
  if (GETPROPERTY_Focus() != n){    

#if defined(_MENUBARITEM)
#elif defined(_TOOLBARITEM)
#else
#ifdef RUN

#ifdef _FORM
  activateWindow();
#else
  setFocus();
#endif
    
#endif
#endif

    _property::SETPROPERTY_Focus(n);
  }
}

#ifdef RUN
  #if defined(_MENUBARITEM)
  #elif defined(_TOOLBARITEM)
  #else

    t_boolean GETPROPERTY_Focus()
    {   
      return this == QApplication::focusWidget();
    }
  #endif
#endif


