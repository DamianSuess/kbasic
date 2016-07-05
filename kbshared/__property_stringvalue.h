
void SETPROPERTY_StringValue(const QString & n)
{ 
  bool b = GETPROPERTY_StringValue() != n;


#if defined(_LABEL) || defined(_SOUND) || defined(_IMAGE) || defined(_SVG) || defined(_MOVIE) || defined(_BROWSER) || defined(_WEB) || defined(_TEXTBOX) || defined(_COMBOBOX) || defined(_LISTBOX) || defined(_CHECKBOX) || defined(_DATEBOX) || defined(_TIMEBOX)/* || defined(_DATETIMEBOX)*/ || defined(_EDITOR)
  if (!GETPROPERTY_SQLName().isEmpty()) b = true;
#endif

  if (b){

#if defined(_LABEL)
  if (!isEnabled()){
    sEnabledText = text();
    QString s = "<font color='gray'>";
    s += sEnabledText;
    s += "</font>";
    setText(s);

  } else {
    sEnabledText = n;
    setText(sEnabledText);
  }
  _property::SETPROPERTY_Caption(n);
   
#elif defined(_TOOLBARITEM)
	#ifdef RUN
		if (my_qaction) my_qaction->setIconText(n);
	#endif
#elif defined(_TOOLBUTTON)
    setText(n);

    if (n.isEmpty()){
      setToolButtonStyle(Qt::ToolButtonIconOnly);
    } else {
      setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    }
#elif defined(_COMMANDBUTTON)

    setText(n);
#elif defined(_COMMANDLINKBUTTON)

    setText(n);
//#elif defined(_IMAGEBUTTON)
    //setText(n);
#endif

  #ifdef _FRAME


    static int nOriginalFontSize = font().pointSize();

    if (n.isEmpty()){
      setTitle("."); // WORKAROUND, otherwise Qt crashes

      QFont f = font();
      f.setPointSize(1);
      setFont(f);    

    } else {

      QFont f = font();
      if (font().pointSize() == 1) f.setPointSize(nOriginalFontSize);
      setFont(f);    

      setTitle(n);
    }

#elif defined(_FORM)
  #ifdef RUN
     setWindowTitle(n);
  #endif
#endif


#if defined(_COMBOBOX)
  int i = findText(n);
  if (i >= 0) setCurrentIndex(i);
  else setEditText(n);
#elif defined(_LISTBOX)
  QList<QListWidgetItem *> l = findItems(n, Qt::MatchExactly);
  for (int i = 0; i < l.size(); i++){
    setCurrentItem(l.at(i));
    break;
  }

#elif defined(_DATEBOX)
      QString y = n.left(4);
      QString m = n.mid(5, 2);
      QString d = n.mid(8, 2);
      if (m == 0 || d == 0){
        setDate(QDate());
      } else {
        setDate(QDate(y.toInt(), m.toInt(), d.toInt()));
      }
#elif defined(_TIMEBOX)
      QString h = n.left(2);
      QString m = n.mid(3, 2);
      QString s = n.mid(6, 2);
      setTime(QTime(h.toInt(), m.toInt(), s.toInt()));
#elif defined(_DATETIMEBOX)
      QString y = n.left(4);
      QString m = n.mid(5, 2);
      QString d = n.mid(8, 2);
      QString h = n.mid(11, 2);
      QString mi = n.mid(14, 2);
      QString s = n.mid(17, 2);
      setDate(QDate(y.toInt(), m.toInt(), d.toInt()));
      setTime(QTime(h.toInt(), mi.toInt(), s.toInt()));

#elif defined(_IMAGE)

  if (n.length() > 200){ // QString contains binary data

    QPixmap pi; 
    if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
      QString m = n;
      m = m.trimmed();
      QSvgWidget w(0);
      w.resize(width(), height());
      QSvgRenderer *r = w.renderer();
      if (r->load(m.toLatin1())){
        QPixmap p(width(), height());
        QPainter painter(&p);
        r->render(&painter);
        pi = p;
      }
    } else {
       pi.loadFromData(n.toLatin1());
    }
    
    setAutoFillBackground(true);    
    QBrush b(pi);
    QPalette p = palette();
    p.setBrush(QPalette::Window, b);  
    setPalette(p);
  } else {
    setAutoFillBackground(true);
    QBrush b(loadPixmap(n.contains(".") ? n : n + ".png"));
    QPalette p = palette();
    p.setBrush(QPalette::Window, b);  
    setPalette(p);
  }
#elif defined(_SVG)

  if (n.length() > 200){ // QString contains binary data
    load(n.toLatin1());
  } else {
    load(n.contains(".") ? n : n + ".svg");
  }
#elif defined(_TEXTBOX)
	  setText(n);
#elif defined(_EDITOR)

     
    if ((n.startsWith("<!DOCTYPE", Qt::CaseInsensitive) || n.startsWith("<HTML", Qt::CaseInsensitive)) && GETPROPERTY_AcceptRichText() && GETPROPERTY_Keywords().isEmpty()){
  	  setHtml(n);
    } else {
      setPlainText(n);
    }
    
#elif defined(_WEB)
    if (!GETPROPERTY_HomeURL().isEmpty() && !GETPROPERTY_HomeURL().startsWith("file:///WEBVIEW/", Qt::CaseInsensitive)) return;
    
    setHtml(n);  

#elif defined(_BROWSER)
    if (!GETPROPERTY_HomeURL().isEmpty()) return;
    
    setHtml(n);  
#elif defined(_PROGRESSBAR)
	  setText(n);
#elif defined(_SCROLLBOX)
#endif

r:
    _property::SETPROPERTY_StringValue(n);

#if defined(_IMAGEBUTTON)
  repaint();
#endif


#ifdef RUN

#if defined(_SOUND) || defined(_IMAGE) || defined(_MOVIE) || defined(_BROWSER) || defined(_WEB)
  EVENT_OnSQLEvent();
#endif

#endif
  }
}

#ifdef _COMBOBOX
QString GETPROPERTY_StringValue()
{
  int n = currentIndex();
  if (n >= 0) return itemText(n);
  QLineEdit *l = lineEdit();
  if (l) return l->text();
  return "";
}
#endif

#ifdef _LISTBOX
QString GETPROPERTY_StringValue()
{
  QListWidgetItem *l = currentItem();
  if (l) return l->text();
  return "";
}
#endif


#ifdef _DATEBOX
QString GETPROPERTY_StringValue()
{
  return date().toString("yyyy-MM-dd");
}
#endif

#ifdef _TIMEBOX
QString GETPROPERTY_StringValue()
{
  return time().toString("hh:mm:ss");
}
#endif


#ifdef _DATETIMEBOX
QString GETPROPERTY_StringValue()
{
  return dateTime().toString("yyyy-MM-dd hh:mm:ss");
}
#endif