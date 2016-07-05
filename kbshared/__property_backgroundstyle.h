
bool bBackgroundStyle;
void SETPROPERTY_BackgroundStyle(const QString & n)
{ 

  if (GETPROPERTY_BackgroundStyle() != n){  

#if defined(_LABEL) || defined(_CHECKBOX) || defined(_RADIOBUTTON) || defined(_COMMANDBUTTON)

    bBackgroundStyle = !n.isEmpty();

    repaint();

#endif
    _property::SETPROPERTY_BackgroundStyle(n);
  }

}

