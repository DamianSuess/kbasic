
void SETPROPERTY_TickPosition(const QString & n)
{
  int i = 0;

#ifdef _SLIDER
  if (n.contains("NoTicks", Qt::CaseInsensitive)) i |= QSlider::NoTicks;
  else if (n.contains("TicksBothSides", Qt::CaseInsensitive)) i |= QSlider::TicksBothSides;
  else if (n.contains("TicksAbove", Qt::CaseInsensitive)) i |= QSlider::TicksAbove;
  else if (n.contains("TicksBelow", Qt::CaseInsensitive)) i |= QSlider::TicksBelow;
  else if (n.contains("TicksLeft", Qt::CaseInsensitive)) i |= QSlider::TicksLeft;
  else if (n.contains("TicksRight", Qt::CaseInsensitive)) i |= QSlider::TicksRight;
  setTickPosition((QSlider::TickPosition) i);
#endif

  _property::SETPROPERTY_TickPosition(n);
}

QString GETPROPERTY_TickPosition()
{
  QString i = "";

#ifdef _SLIDER
  QSlider::TickPosition t = (QSlider::TickPosition) tickPosition();
  
  if (t == QSlider::NoTicks) i += "NoTicks"; 
  else if (t == QSlider::TicksBothSides) i += "TicksBothSides"; 
  else if (t == QSlider::TicksAbove) i += "TicksAbove"; 
  else if (t == QSlider::TicksBelow) i += "TicksBelow"; 
  else if (t == QSlider::TicksLeft) i += "TicksLeft"; 
  else if (t == QSlider::TicksRight) i += "TicksRight"; 
#endif

  return i;
}
