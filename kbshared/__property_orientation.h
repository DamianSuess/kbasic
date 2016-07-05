
void SETPROPERTY_Orientation(const QString & n)
{
  int i = 0;

#ifdef _LINE
  if (n.contains("Horizontal", Qt::CaseInsensitive)) i |= QFrame::HLine;
  else if (n.contains("Vertical", Qt::CaseInsensitive)) i |= QFrame::VLine;
  setFrameShape((QFrame::Shape) i);
#endif

#ifdef _SCROLLBAR
  if (n.contains("Horizontal", Qt::CaseInsensitive)) i |= Qt::Horizontal;
  else if (n.contains("Vertical", Qt::CaseInsensitive)) i |= Qt::Vertical;
  setOrientation ((Qt::Orientation) i);
#endif

#ifdef _SLIDER
  if (n.contains("Horizontal", Qt::CaseInsensitive)) i |= Qt::Horizontal;
  else if (n.contains("Vertical", Qt::CaseInsensitive)) i |= Qt::Vertical;
  setOrientation ((Qt::Orientation) i);
#endif

  _property::SETPROPERTY_Orientation(n);
}

QString GETPROPERTY_Orientation()
{
  
  QString i = "";

#ifdef _LINE
  QFrame::Shape t = (QFrame::Shape) frameShape();

  if (t == QFrame::HLine) i += "Horizontal"; 
  else if (t == QFrame::VLine) i += "Vertical"; 
#endif

#ifdef _SLIDER
  Qt::Orientation t = (Qt::Orientation) orientation();

  if (t == Qt::Horizontal) i += "Horizontal"; 
  else if (t == Qt::Vertical) i += "Vertical"; 
#endif

  return i;
}
