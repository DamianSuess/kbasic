
void SETPROPERTY_Caption(const QString & n)
{ 
  if (GETPROPERTY_Caption() != n){    

#if defined(_MENUBARITEM)
  #ifdef RUN
    if (my_qaction) my_qaction->setText(n);
  #endif
#elif defined(_TOOLBARITEM)
  #ifdef RUN
    if (my_qaction) my_qaction->setIconText(n);
  #endif
#else

#if defined(_LABEL)
  if (isEnabled()){
    setText(n);  
    sEnabledText = n;
  } else {
    sEnabledText = n;
    QString s = "<font color='gray'>";
    s += sEnabledText;
    s += "</font>";
    setText(s);
  }
  _property::SETPROPERTY_StringValue(n);
  
#elif defined(_TOOLBUTTON)
    setText(n);
    if (n.isEmpty()){
      setToolButtonStyle(Qt::ToolButtonIconOnly);
    } else {
      setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }
#elif defined(_COMMANDBUTTON)
    setText(n);
#elif defined(_COMMANDLINKBUTTON)
    setText(n);
    
#elif defined(_HEADER)
    setText(n);
#elif defined(_FOOTER)
    setText(n);
#elif defined(_CHECKBOX)
    setText(n);
#elif defined(_RADIOBUTTON)
    setText(n);
#elif defined(_PROGRESSBAR)
    setText(n);
#elif defined(_FORM)

  #ifdef RUN
     if (bLoading == false) setWindowTitle(n);
  #endif

#else
  #ifdef _FRAME


    static int nOriginalFontSize = font().pointSize();

    if (n.isEmpty()){
      setTitle("."); // WORKAROUND, otherwise Qt crashes

      QFont f = font();
      f.setPointSize(1);
      setFont(f);    

    } else {

      QFont f = font();
      if (font().pointSize() == 1) f.setPointSize(nOriginalFontSize);
      setFont(f);    

      setTitle(n);
    }
  #endif
  #endif
#endif

    _property::SETPROPERTY_Caption(n);

#if defined(_IMAGEBUTTON)
  repaint();
#endif
  }
}
