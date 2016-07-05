
void SETPROPERTY_ScrollBar(const QString & n)
{ 
  if (GETPROPERTY_ScrollBar() != n){  

#ifdef IDE
#ifdef _FORM

    if (XScrollBar == 0) XScrollBar = new QScrollBar(Qt::Horizontal);
    if (YScrollBar == 0) YScrollBar = new QScrollBar(Qt::Vertical);

    if (n.contains("XScrollBarAlwaysOff", Qt::CaseInsensitive)) XScrollBar->setHidden(true);
    if (n.contains("YScrollBarAlwaysOff", Qt::CaseInsensitive)) YScrollBar->setHidden(true);
#else
    int i = 0;

    if (n.contains("XScrollBarAsNeeded", Qt::CaseInsensitive)) i |= Qt::ScrollBarAsNeeded;
    if (n.contains("XScrollBarAlwaysOff", Qt::CaseInsensitive)) i |= Qt::ScrollBarAlwaysOff;
    if (n.contains("XScrollBarAlwaysOn", Qt::CaseInsensitive)) i |= Qt::ScrollBarAlwaysOn;

    setHorizontalScrollBarPolicy((Qt::ScrollBarPolicy) i);

    if (n.contains("YScrollBarAsNeeded", Qt::CaseInsensitive)) i |= Qt::ScrollBarAsNeeded;
    if (n.contains("YScrollBarAlwaysOff", Qt::CaseInsensitive)) i |= Qt::ScrollBarAlwaysOff;
    if (n.contains("YScrollBarAlwaysOn", Qt::CaseInsensitive)) i |= Qt::ScrollBarAlwaysOn;

    setVerticalScrollBarPolicy((Qt::ScrollBarPolicy) i);
#endif
#else
    int i = 0;

    if (n.contains("XScrollBarAsNeeded", Qt::CaseInsensitive)) i |= Qt::ScrollBarAsNeeded;
    if (n.contains("XScrollBarAlwaysOff", Qt::CaseInsensitive)) i |= Qt::ScrollBarAlwaysOff;
    if (n.contains("XScrollBarAlwaysOn", Qt::CaseInsensitive)) i |= Qt::ScrollBarAlwaysOn;

    setHorizontalScrollBarPolicy((Qt::ScrollBarPolicy) i);

    if (n.contains("YScrollBarAsNeeded", Qt::CaseInsensitive)) i |= Qt::ScrollBarAsNeeded;
    if (n.contains("YScrollBarAlwaysOff", Qt::CaseInsensitive)) i |= Qt::ScrollBarAlwaysOff;
    if (n.contains("YScrollBarAlwaysOn", Qt::CaseInsensitive)) i |= Qt::ScrollBarAlwaysOn;

    setVerticalScrollBarPolicy((Qt::ScrollBarPolicy) i);
    
#endif
    _property::SETPROPERTY_ScrollBar(n);

  }
}
