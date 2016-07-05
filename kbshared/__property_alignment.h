

void SETPROPERTY_Alignment(const QString & n)
{ 
  if (GETPROPERTY_Alignment() != n){      

    int i = 0;

    if (n.contains("AlignLeft", Qt::CaseInsensitive)) i |= Qt::AlignLeft;
    if (n.contains("AlignRight", Qt::CaseInsensitive)) i |= Qt::AlignRight;
    if (n.contains("AlignHCenter", Qt::CaseInsensitive)) i |= Qt::AlignHCenter;
    if (n.contains("AlignJustify", Qt::CaseInsensitive)) i |= Qt::AlignJustify;
    if (n.contains("AlignTop", Qt::CaseInsensitive)) i |= Qt::AlignTop;
    if (n.contains("AlignBottom", Qt::CaseInsensitive)) i |= Qt::AlignBottom;
    if (n.contains("AlignVCenter", Qt::CaseInsensitive)) i |= Qt::AlignVCenter;
    if (n.contains("AlignCenter", Qt::CaseInsensitive)) i |= Qt::AlignCenter;
    if (n.contains("AlignAbsolute", Qt::CaseInsensitive)) i |= Qt::AlignAbsolute;
    if (n.contains("AlignLeading", Qt::CaseInsensitive)) i |= Qt::AlignLeading;
    if (n.contains("AlignTrailing", Qt::CaseInsensitive)) i |= Qt::AlignTrailing;
    if (n.contains("AlignHorizontal_Mask", Qt::CaseInsensitive)) i |= Qt::AlignHorizontal_Mask;
    if (n.contains("AlignVertical_Mask", Qt::CaseInsensitive)) i |= Qt::AlignVertical_Mask;

    setAlignment((Qt::Alignment) i);
    
  

    _property::SETPROPERTY_Alignment(n);
  }
}