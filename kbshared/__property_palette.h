
void SETPROPERTY_Palette(const QString & n)
{ 
  if (GETPROPERTY_Palette() != n){  

    QStringList l = n.count(";") ? n.split(";") : n.split(",");

    if (l.count()){

      static QPalette SAVE; static bool bSAVE = false;
      if (!bSAVE){
        bSAVE = true;
        SAVE = palette();
      }


      QMap<QString, QString> v;

      foreach(QString s, l){
        int m = s.indexOf("=");
        if (m >= 0){
          QString sKey = s.left(m).simplified();
          QString sValue = s.mid(m + 1).simplified();
          v[sKey] = sValue;
        }
      }
      
      QPalette p = SAVE;//palette();

      QMapIterator<QString, QString> ii(v);
      while (ii.hasNext()){
          ii.next();

          QString a = ii.key();
          QString b = ii.value();

          QColor c;

          if (b.contains("&H")){
            c = _property::getColor(b);
          } else {

            if (b.startsWith("Color.", Qt::CaseInsensitive)){
              b = b.mid(b.indexOf("Color.", Qt::CaseInsensitive));
            }

            if (b.compare(b, "White", Qt::CaseInsensitive) == 0) c = Qt::white;
            else if (b.compare(b, "Black", Qt::CaseInsensitive) == 0) c = Qt::black;
            else if (b.compare(b, "Red", Qt::CaseInsensitive) == 0) c = Qt::red;
            else if (b.compare(b, "DarkRed", Qt::CaseInsensitive) == 0) c = Qt::darkRed;
            else if (b.compare(b, "Green", Qt::CaseInsensitive) == 0) c = Qt::green;
            else if (b.compare(b, "DarkGreen", Qt::CaseInsensitive) == 0) c = Qt::darkGreen;
            else if (b.compare(b, "Blue", Qt::CaseInsensitive) == 0) c = Qt::blue;
            else if (b.compare(b, "DarkBlue", Qt::CaseInsensitive) == 0) c = Qt::darkBlue;
            else if (b.compare(b, "Cyan", Qt::CaseInsensitive) == 0) c = Qt::cyan;
            else if (b.compare(b, "DarkCyan", Qt::CaseInsensitive) == 0) c = Qt::darkCyan;
            else if (b.compare(b, "Magenta", Qt::CaseInsensitive) == 0) c = Qt::magenta;
            else if (b.compare(b, "DarkMagenta", Qt::CaseInsensitive) == 0) c = Qt::darkMagenta;
            else if (b.compare(b, "Yellow", Qt::CaseInsensitive) == 0) c = Qt::yellow;
            else if (b.compare(b, "DarkYellow", Qt::CaseInsensitive) == 0) c = Qt::darkYellow;
            else if (b.compare(b, "Gray", Qt::CaseInsensitive) == 0) c = Qt::gray;
            else if (b.compare(b, "DarkGray", Qt::CaseInsensitive) == 0) c = Qt::darkGray;
            else if (b.compare(b, "LightGray", Qt::CaseInsensitive) == 0) c = Qt::lightGray;
          }

          int i = 0;

          if (a.contains("WindowText", Qt::CaseInsensitive)) i |= QPalette::WindowText;
          else if (a.contains("AlternateBase", Qt::CaseInsensitive)) i |= QPalette::AlternateBase;
          else if (a.contains("ToolTipBase", Qt::CaseInsensitive)) i |= QPalette::ToolTipBase;
          else if (a.contains("ToolTipText", Qt::CaseInsensitive)) i |= QPalette::ToolTipText;
          else if (a.contains("ButtonText", Qt::CaseInsensitive)) i |= QPalette::ButtonText;
          else if (a.contains("Button", Qt::CaseInsensitive)) i |= QPalette::Button;
          else if (a.contains("BrightText", Qt::CaseInsensitive)) i |= QPalette::BrightText;
          else if (a.contains("Light", Qt::CaseInsensitive)) i |= QPalette::Light;
          else if (a.contains("Midlight", Qt::CaseInsensitive)) i |= QPalette::Midlight;
          else if (a.contains("Dark", Qt::CaseInsensitive)) i |= QPalette::Dark;
          else if (a.contains("Shadow", Qt::CaseInsensitive)) i |= QPalette::Shadow;
          else if (a.contains("HighlightedText", Qt::CaseInsensitive)) i |= QPalette::HighlightedText;
          else if (a.contains("LinkVisited", Qt::CaseInsensitive)) i |= QPalette::LinkVisited;

          else if (a.contains("Window", Qt::CaseInsensitive)) i |= QPalette::Window;
          else if (a.contains("Mid", Qt::CaseInsensitive)) i |= QPalette::Mid;
          else if (a.contains("Highlight", Qt::CaseInsensitive)) i |= QPalette::Highlight;
          else if (a.contains("Link", Qt::CaseInsensitive)) i |= QPalette::Link;
          else if (a.contains("Text", Qt::CaseInsensitive)) i |= QPalette::Text;
          else if (a.contains("Base", Qt::CaseInsensitive)) i |= QPalette::Base;

          if (c.isValid()){
            if (a.contains("Active", Qt::CaseInsensitive)) p.setColor(QPalette::Active, (QPalette::ColorRole) i , c); 
            else if (a.contains("Normal", Qt::CaseInsensitive)) p.setColor(QPalette::Normal, (QPalette::ColorRole) i , c); 
            else if (a.contains("Disabled", Qt::CaseInsensitive)) p.setColor(QPalette::Disabled, (QPalette::ColorRole) i , c); 
            else if (a.contains("Inactive", Qt::CaseInsensitive)) p.setColor(QPalette::Inactive, (QPalette::ColorRole) i , c); 
            else p.setColor((QPalette::ColorRole) i , c); 
          }

          
          
      }

      setPalette(p);
      setAutoFillBackground(true);

    }    

    _property::SETPROPERTY_Palette(n);
  }
  if (n.isEmpty()) setAutoFillBackground(false);
}

