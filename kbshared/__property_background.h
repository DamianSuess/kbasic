
QColor cBackground;
void SETPROPERTY_Background(const QString & n)
{ 
  if (GETPROPERTY_Background() != n){  
  QString nn = n;

  static QPalette SAVE; static bool bSAVE = false;
  if (!bSAVE){
    bSAVE = true;
    SAVE = palette();
  }

#ifdef RUN

  if (!nn.isEmpty()){
    setAutoFillBackground(true);

    if (nn.contains("&H")){

      QPalette p = palette();
      QColor c = _property::getColor(nn);
      p.setColor(QPalette::Window, c);  
      p.setColor(QPalette::Base, c);  
      p.setColor(QPalette::Button, c);            
      setPalette(p);

      cBackground = c;
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
        p.setColor(QPalette::Window, cc);  
        p.setColor(QPalette::Base, cc);  
        p.setColor(QPalette::Button, cc);            
        setPalette(p);

        cBackground = cc;

      } else {
        QBrush b(loadPixmap(nn));

        QPalette p = palette();
        p.setBrush(QPalette::Window, b);  
        p.setBrush(QPalette::Base, b);  
        p.setBrush(QPalette::Button, b);  
        setPalette(p);
      }
    }

  } else {
    setAutoFillBackground(false);

    QPalette p = palette();
    p.setBrush(QPalette::Window, SAVE.brush(QPalette::Window));  
    p.setBrush(QPalette::Base, SAVE.brush(QPalette::Base));  
    p.setBrush(QPalette::Button, SAVE.brush(QPalette::Button));  
    setPalette(p);
    update();
  }

#endif

#ifdef IDE

  
      if (!nn.isEmpty()){
        setAutoFillBackground(true);
        if (nn.contains("&H")){

          QPalette p = palette();
          QColor c = _property::getColor(nn);


          p.setColor(QPalette::Window, c);  
          p.setColor(QPalette::Base, c);  
          p.setColor(QPalette::Button, c);            
          setPalette(p);

          cBackground = c;
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

            p.setColor(QPalette::Window, cc);  
            p.setColor(QPalette::Base, cc);  
            p.setColor(QPalette::Button, cc);            
            setPalette(p);

            cBackground = cc;

          } else {
            QPixmap pp = loadPixmap(nn);

            QBrush b(pp);

            QPalette p = palette();
            p.setBrush(QPalette::Window, b);  
            p.setBrush(QPalette::Base, b);  
            p.setBrush(QPalette::Button, b);  
            setPalette(p);
          }
        }
      } else {
        setAutoFillBackground(false);

        QPalette p = palette();
        p.setBrush(QPalette::Window, SAVE.brush(QPalette::Window));  
        p.setBrush(QPalette::Base, SAVE.brush(QPalette::Base));  
        p.setBrush(QPalette::Button, SAVE.brush(QPalette::Button));  
        setPalette(p);
        update();
      }
  

#endif

  

    _property::SETPROPERTY_Background(n);
  }
}

