
void SETPROPERTY_CheckDisabledImage(const QString & n)
{ 

  if (GETPROPERTY_Checked() && GETPROPERTY_Enabled() == false){
  
    setAutoFillBackground(!n.isEmpty());

     if (n.length() > 200){ // QString contains binary data     

        QPixmap pi;
        if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
          QString fn = n;
          fn = fn.trimmed();
          QSvgWidget w(0);
          w.resize(width(), height());
          QSvgRenderer *r = w.renderer();
          if (r->load(fn.toLatin1())){
            QPixmap p(width(), height());
            QPainter painter(&p);
            r->render(&painter);
            pi = p;
          }
        } else {
          pi.loadFromData(n.toLatin1());
        }

        if (GETPROPERTY_Scale() && !pi.isNull()){
          pi = pi.scaled(width(), height());
        }

       QBrush b(pi);
       QPalette p = palette();
       p.setBrush(QPalette::Window, b);  
       setPalette(p);

     } else {

        QPixmap pi = loadPixmap(n.contains(".") ? n : n + ".png");
        if (GETPROPERTY_Scale() && !pi.isNull()){
          pi = pi.scaled(width(), height());
        }

       QBrush b(pi);
       QPalette p = palette();
       p.setBrush(QPalette::Window, b);  
       setPalette(p);
     }
   
  }
  _property::SETPROPERTY_CheckDisabledImage(n);
  
}
