
void SETPROPERTY_FontColor(const QString & n)
{ 
  if (GETPROPERTY_FontColor() != n){  

#ifndef _FORM

    QString nn = n;

    static QPalette SAVE; static bool bSAVE = false;
    if (!bSAVE){
      bSAVE = true;
      SAVE = palette();
    }

    if (!nn.isEmpty()){
      if (nn.contains("&H")){

        QPalette p = palette();          
        p.setColor(QPalette::ButtonText, _property::getColor(nn));  
        p.setColor(QPalette::WindowText, _property::getColor(nn));  
        p.setColor(QPalette::Text, _property::getColor(nn));    
#ifdef _LINE
        p.setColor(QPalette::Dark, _property::getColor(nn));         

#endif
        setPalette(p);

      } else {
    
        if (nn.startsWith("Color.", Qt::CaseInsensitive)){
          nn = nn.mid(nn.indexOf("Color.", Qt::CaseInsensitive));
        }

        QColor cc;

        if (nn.compare(nn, "White", Qt::CaseInsensitive) == 0) cc = Qt::white;
        else if (nn.compare(nn, "Black", Qt::CaseInsensitive) == 0) cc = Qt::black;
        else if (nn.compare(nn, "Red", Qt::CaseInsensitive) == 0) cc = Qt::red;
        else if (nn.compare(nn, "DarkRed", Qt::CaseInsensitive) == 0) cc = Qt::darkRed;
        else if (nn.compare(nn, "Green", Qt::CaseInsensitive) == 0) cc = Qt::green;
        else if (nn.compare(nn, "DarkGreen", Qt::CaseInsensitive) == 0) cc = Qt::darkGreen;
        else if (nn.compare(nn, "Blue", Qt::CaseInsensitive) == 0) cc = Qt::blue;
        else if (nn.compare(nn, "DarkBlue", Qt::CaseInsensitive) == 0) cc = Qt::darkBlue;
        else if (nn.compare(nn, "Cyan", Qt::CaseInsensitive) == 0) cc = Qt::cyan;
        else if (nn.compare(nn, "DarkCyan", Qt::CaseInsensitive) == 0) cc = Qt::darkCyan;
        else if (nn.compare(nn, "Magenta", Qt::CaseInsensitive) == 0) cc = Qt::magenta;
        else if (nn.compare(nn, "DarkMagenta", Qt::CaseInsensitive) == 0) cc = Qt::darkMagenta;
        else if (nn.compare(nn, "Yellow", Qt::CaseInsensitive) == 0) cc = Qt::yellow;
        else if (nn.compare(nn, "DarkYellow", Qt::CaseInsensitive) == 0) cc = Qt::darkYellow;
        else if (nn.compare(nn, "Gray", Qt::CaseInsensitive) == 0) cc = Qt::gray;
        else if (nn.compare(nn, "DarkGray", Qt::CaseInsensitive) == 0) cc = Qt::darkGray;
        else if (nn.compare(nn, "LightGray", Qt::CaseInsensitive) == 0) cc = Qt::lightGray;

        if (cc.isValid()){
          QPalette p = palette();
          p.setColor(QPalette::ButtonText, cc);  
          p.setColor(QPalette::WindowText, cc);  
          p.setColor(QPalette::Text, cc);          
#ifdef _LINE
          p.setColor(QPalette::BrightText, cc);          
#endif
          setPalette(p);
        }
      }
    } else {
      QPalette p = palette();
      p.setBrush(QPalette::ButtonText, SAVE.brush(QPalette::ButtonText));  
      p.setBrush(QPalette::WindowText, SAVE.brush(QPalette::WindowText));  
      p.setBrush(QPalette::Text, SAVE.brush(QPalette::Text));  
#ifdef _LINE
      p.setBrush(QPalette::BrightText, SAVE.brush(QPalette::BrightText));  
#endif
      setPalette(p);
      update();
    }

#endif

    _property::SETPROPERTY_FontColor(n);
  }
}

