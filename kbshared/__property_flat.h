
void SETPROPERTY_Flat(t_boolean n)
{ 
  
  {
    
#ifdef _LINE
    if (n){
      setFrameShadow(QFrame::Plain);
    } else {
      setFrameShadow(GETPROPERTY_Flip() ? QFrame::Raised : QFrame::Sunken);
    }
#endif

#ifdef _SPINBOX
    setFrame(!n);
#endif

#ifdef _COMMANDBUTTON
    setFlat(n);
#endif

#ifdef _COMMANDLINKBUTTON
    setFlat(n);
#endif

#ifdef _TEXTBOX
    setFrame(!n);
#endif

#ifdef _COMBOBOX
    setFrame(!n);
#endif

#ifdef _DATEBOX
    setFrame(!n);
#endif

#ifdef _TIMEBOX
    setFrame(!n);
#endif

#ifdef _DATETIMEBOX
    setFrame(!n);
#endif

#if defined(_LISTBOX) || defined(_EDITOR) || defined(_BROWSER) || defined(_TREEVIEW)
    setFrameStyle(n ? QFrame::NoFrame : QFrame::StyledPanel);
#endif
    _property::SETPROPERTY_Flat(n);
  }
}
