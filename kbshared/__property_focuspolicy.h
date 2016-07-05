
void SETPROPERTY_FocusPolicy(const QString & n)
{ 
  if (GETPROPERTY_FocusPolicy() != n){  

#ifdef RUN

      int i = 0;

      if (n.contains("TabFocus"), Qt::CaseInsensitive) i |= Qt::TabFocus;
      if (n.contains("ClickFocus"), Qt::CaseInsensitive) i |= Qt::ClickFocus;
      if (n.contains("StrongFocus"), Qt::CaseInsensitive) i |= Qt::StrongFocus;
      if (n.contains("WheelFocus"), Qt::CaseInsensitive) i |= Qt::WheelFocus;
      if (n.contains("NoFocus"), Qt::CaseInsensitive) i |= Qt::NoFocus;

      setFocusPolicy((Qt::FocusPolicy) i);
      
#endif

    _property::SETPROPERTY_FocusPolicy(n);
  }
}