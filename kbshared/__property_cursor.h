
void SETPROPERTY_Cursor(const QString & n)
{ 
  if (GETPROPERTY_Cursor() != n){  

#ifdef RUN
    if (n.simplified().isEmpty()){
      unsetCursor();
    } else {

      int i = 0;

      if (n.compare("ArrowCursor", Qt::CaseInsensitive) == 0) i |= Qt::ArrowCursor;
      else if (n.compare("UpArrowCursor", Qt::CaseInsensitive) == 0) i |= Qt::UpArrowCursor;
      else if (n.compare("CrossCursor", Qt::CaseInsensitive) == 0) i |= Qt::CrossCursor;
      else if (n.compare("WaitCursor", Qt::CaseInsensitive) == 0) i |= Qt::WaitCursor;
      else if (n.compare("IBeamCursor", Qt::CaseInsensitive) == 0) i |= Qt::IBeamCursor;
      else if (n.compare("SizeVerCursor", Qt::CaseInsensitive) == 0) i |= Qt::SizeVerCursor;
      else if (n.compare("SizeHorCursor", Qt::CaseInsensitive) == 0) i |= Qt::SizeHorCursor;
      else if (n.compare("SizeFDiagCursor", Qt::CaseInsensitive) == 0) i |= Qt::SizeFDiagCursor;
      else if (n.compare("SizeBDiagCursor", Qt::CaseInsensitive) == 0) i |= Qt::SizeBDiagCursor;
      else if (n.compare("SizeAllCursor", Qt::CaseInsensitive) == 0) i |= Qt::SizeAllCursor;
      else if (n.compare("BlankCursor", Qt::CaseInsensitive) == 0) i |= Qt::BlankCursor;
      else if (n.compare("SplitVCursor", Qt::CaseInsensitive) == 0) i |= Qt::SplitVCursor;
      else if (n.compare("SplitHCursor", Qt::CaseInsensitive) == 0) i |= Qt::SplitHCursor;
      else if (n.compare("PointingHandCursor", Qt::CaseInsensitive) == 0) i |= Qt::PointingHandCursor;
      else if (n.compare("ForbiddenCursor", Qt::CaseInsensitive) == 0) i |= Qt::ForbiddenCursor;
      else if (n.compare("OpenHandCursor", Qt::CaseInsensitive) == 0) i |= Qt::OpenHandCursor;
      else if (n.compare("ClosedHandCursor", Qt::CaseInsensitive) == 0) i |= Qt::ClosedHandCursor;
      else if (n.compare("WhatsThisCursor", Qt::CaseInsensitive) == 0) i |= Qt::WhatsThisCursor;
      else if (n.compare("BusyCursor", Qt::CaseInsensitive) == 0) i |= Qt::BusyCursor;
      else goto _else;

      if (i >= 0){
        setCursor(QCursor((Qt::CursorShape) i));
      } else {
_else:
#ifdef _FORM        

  if (n.length() > 200){ // QString contains binary data
    QPixmap p; p.loadFromData(n.toLatin1());
    setCursor(QCursor(p));
  } else {
    setCursor(QCursor(loadPixmap(n.contains(".") ? n : n + ".png")));
  }
        
#else
       
  if (n.length() > 200){ // QString contains binary data
    QPixmap p; p.loadFromData(n.toLatin1());
    setCursor(QCursor(p));
  } else {
    if (!n.isEmpty()) setCursor(QCursor(loadPixmap(n.contains(".") ? n : n + ".png")));
  }

#endif
      }
    }
      
#endif

    _property::SETPROPERTY_Cursor(n);
  }
}