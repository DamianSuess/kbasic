
void SETPROPERTY_Icon(const QString & n)
{ 
 
  {  

#if defined(_LABEL)
    if (n.isEmpty()){
      setPixmap(QPixmap());
    } else {

       bool bMovie = false;
#ifdef RUN
       QList<QByteArray> l = QMovie::supportedFormats();
       for (int i = 0; i < l.size(); ++i) {
          QString ss(l.at(i));
          if (n.endsWith("." + ss, Qt::CaseInsensitive)){
            bMovie = true;
            break;
          }
       }      
#endif
       if (bMovie){
         if (setMyMovie(this, &movie, &moviea, &movieb, n)){
           //connect(movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
           this->setMovie(movie);
           movie->start();
         } else {
           setPixmap(loadPixmap(n.contains(".") ? n : n + ".png"));
         }
         
       } else {
         if (n.length() > 200){ // QString contains binary data

            if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
              QString m = n;
              m = m.trimmed();
              QSvgWidget w(0);
              w.resize(100, 100);
              QSvgRenderer *r = w.renderer();
              if (r->load(m.toLatin1())){

                QPixmap p(100, 100);
                QPainter painter(&p);
                r->render(&painter);
                //= QPixmap::grabWidget(&w); 
                setPixmap(p);       
              }
            } else {
               QPixmap pi; pi.loadFromData(n.toLatin1());
               setPixmap(pi);
            }

         } else {
           setPixmap(loadPixmap(n.contains(".") ? n : n + ".png"));
         }
       }
      
    }
    
#elif defined(_IMAGEBUTTON)

   bool bMovie = false;
#ifdef RUN
   QList<QByteArray> l = QMovie::supportedFormats();
   for (int i = 0; i < l.size(); ++i) {
      QString ss(l.at(i));
      if (n.endsWith("." + ss, Qt::CaseInsensitive)){
        bMovie = true;
        break;
      }
   }      
#endif
   if (bMovie){
     if (setMyMovie(0, &movie, &moviea, &movieb, n)){
       connect(movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
       movie->start();
     } else {
       qpixmap = loadPixmap(n.contains(".") ? n : n + ".png");
     }
     
   } else {

     if (n.length() > 200){ // QString contains binary data

        if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
          QString m = n;
          m = m.trimmed();
          QSvgWidget w(0);
          w.resize(100, 100);
          QSvgRenderer *r = w.renderer();
          if (r->load(m.toLatin1())){

            QPixmap p(100, 100);
            QPainter painter(&p);
            r->render(&painter);
            qpixmap = p;       
          }
        } else {
           QPixmap pi; pi.loadFromData(n.toLatin1());
           qpixmap = pi;
        }

     } else {
       qpixmap = loadPixmap(n.contains(".") ? n : n + ".png");
     }
   
   }

#elif defined(_COMMANDBUTTON) || defined(_COMMANDLINKBUTTON) || defined(_TOOLBUTTON)

#if defined(_TOOLBUTTON)
    if (n.isEmpty()){
      setToolButtonStyle(Qt::ToolButtonTextOnly);
    } else {
      if (GETPROPERTY_Caption().isEmpty()){
        setToolButtonStyle(Qt::ToolButtonIconOnly);
      } else {
        setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
      }      
    }
#endif

   bool bMovie = false;
#ifdef RUN
   QList<QByteArray> l = QMovie::supportedFormats();
   for (int i = 0; i < l.size(); ++i) {
      QString ss(l.at(i));
      if (n.endsWith("." + ss, Qt::CaseInsensitive)){
        bMovie = true;
        break;
      }
   }      
#endif
   if (bMovie){
     if (setMyMovie(this, &movie, &moviea, &movieb, n)){
       connect(movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
       movie->start();
     } else {
       setIcon(QIcon(loadPixmap(n.contains(".") ? n : n + ".png")));
     }
     
   } else {

       if (n.length() > 200){ // QString contains binary data

          if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
            QString m = n;
            m = m.trimmed();
            QSvgWidget w(0);
            w.resize(100, 100);
            QSvgRenderer *r = w.renderer();
            if (r->load(m.toLatin1())){

              QPixmap p(100, 100);
              QPainter painter(&p);
              r->render(&painter);
              //= QPixmap::grabWidget(&w); 
              setIcon(p);       
            }
          } else {
             QPixmap pi; pi.loadFromData(n.toLatin1());
             setIcon(pi);
          }

       } else {
         setIcon(loadPixmap(n.contains(".") ? n : n + ".png"));
       }

     
   }
  
    
#elif defined(_CHECKBOX)

   bool bMovie = false;
#ifdef RUN
   QList<QByteArray> l = QMovie::supportedFormats();
   for (int i = 0; i < l.size(); ++i) {
      QString ss(l.at(i));
      if (n.endsWith("." + ss, Qt::CaseInsensitive)){
        bMovie = true;
        break;
      }
   }      
#endif
   if (bMovie){
     if (setMyMovie(0, &movie, &moviea, &movieb, n)){
       connect(movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
       movie->start();
     } else {
       setIcon(QIcon(loadPixmap(n.contains(".") ? n : n + ".png")));
     }
     
   } else {

     if (n.length() > 200){ // QString contains binary data

        if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
          QString m = n;
          m = m.trimmed();
          QSvgWidget w(0);
          w.resize(100, 100);
          QSvgRenderer *r = w.renderer();
          if (r->load(m.toLatin1())){

            QPixmap p(100, 100);
            QPainter painter(&p);
            r->render(&painter);
            //= QPixmap::grabWidget(&w); 
            setIcon(p);       
          }
        } else {
           QPixmap pi; pi.loadFromData(n.toLatin1());
           setIcon(pi);
        }

     } else {
       setIcon(loadPixmap(n.contains(".") ? n : n + ".png"));
     }
   
   }
#elif defined(_RADIOBUTTON)

   bool bMovie = false;
#ifdef RUN
   QList<QByteArray> l = QMovie::supportedFormats();
   for (int i = 0; i < l.size(); ++i) {
      QString ss(l.at(i));
      if (n.endsWith("." + ss, Qt::CaseInsensitive)){
        bMovie = true;
        break;
      }
   }      
#endif
   if (bMovie){
     if (setMyMovie(0, &movie, &moviea, &movieb, n)){
       connect(movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
       movie->start();
     } else {
       setIcon(QIcon(loadPixmap(n.contains(".") ? n : n + ".png")));
     }
     
   } else {

       if (n.length() > 200){ // QString contains binary data
         
          if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
            QString m = n;
            m = m.trimmed();
            QSvgWidget w(0);
            w.resize(100, 100);
            QSvgRenderer *r = w.renderer();
            if (r->load(m.toLatin1())){

              QPixmap p(100, 100);
              QPainter painter(&p);
              r->render(&painter);
              //= QPixmap::grabWidget(&w); 
              setIcon(p);       
            }
          } else {
             QPixmap pi; pi.loadFromData(n.toLatin1());
             setIcon(pi);
          }

       } else {
         setIcon(loadPixmap(n.contains(".") ? n : n + ".png"));
       }

   }
    
#elif defined(_FORM)
  #ifdef RUN

   bool bMovie = false;
#ifdef RUN
   QList<QByteArray> l = QMovie::supportedFormats();
   for (int i = 0; i < l.size(); ++i) {
      QString ss(l.at(i));
      if (n.endsWith("." + ss, Qt::CaseInsensitive)){
        bMovie = true;
        break;
      }
   }      
#endif
   if (bMovie){
     if (setMyMovie(0, &movie, &moviea, &movieb, n)){
       bool bbbb = connect(movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
       movie->start();
     } else {
       setWindowIcon(QIcon(loadPixmap(n.contains(".") ? n : n + ".png"))); 
     }
     
   } else {

     if (n.length() > 200){ // QString contains binary data
       
        if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
          QString m = n;
          m = m.trimmed();
          QSvgWidget w(0);
          w.resize(100, 100);
          QSvgRenderer *r = w.renderer();
          if (r->load(m.toLatin1())){

            QPixmap p(100, 100);
            QPainter painter(&p);
            r->render(&painter);
            //= QPixmap::grabWidget(&w); 
            setWindowIcon(p);       
          }
        } else {
           QPixmap pi; pi.loadFromData(n.toLatin1());
           setWindowIcon(pi);
        }

     } else {
       setWindowIcon(loadPixmap(n.contains(".") ? n : n + ".png"));
     }

   }
     
  #endif
#elif defined(_MENUBARITEM)
  #ifdef RUN

   bool bMovie = false;
#ifdef RUN
   QList<QByteArray> l = QMovie::supportedFormats();
   for (int i = 0; i < l.size(); ++i) {
      QString ss(l.at(i));
      if (n.endsWith("." + ss, Qt::CaseInsensitive)){
        bMovie = true;
        break;
      }
   }      
#endif
   if (bMovie){
     if (setMyMovie(0, &movie, &moviea, &movieb, n)){
       QObject::connect(movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
       movie->start();
     } else {
       if (my_qaction) my_qaction->setIcon(QIcon(interpreter_loadPixmap(n.contains(".") ? n : n + ".png")));
     }
     
   } else {

     if (n.length() > 200){ // QString contains binary data
       
        if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
          QString m = n;
          m = m.trimmed();
          QSvgWidget w(0);
          w.resize(100, 100);
          QSvgRenderer *r = w.renderer();
          if (r->load(m.toLatin1())){

            QPixmap p(100, 100);
            QPainter painter(&p);
            r->render(&painter);
            if (my_qaction) my_qaction->setIcon(p);
          }
        } else {
           QPixmap pi; pi.loadFromData(n.toLatin1());
           if (my_qaction) my_qaction->setIcon(pi);
        }

     } else {
       if (my_qaction) my_qaction->setIcon(interpreter_loadPixmap(n.contains(".") ? n : n + ".png"));
     }
   }

  #endif
#elif defined(_TOOLBARITEM)
  #ifdef RUN

   bool bMovie = false;
#ifdef RUN
   QList<QByteArray> l = QMovie::supportedFormats();
   for (int i = 0; i < l.size(); ++i) {
      QString ss(l.at(i));
      if (n.endsWith("." + ss, Qt::CaseInsensitive)){
        bMovie = true;
        break;
      }
   }      
#endif
   if (bMovie){
     if (setMyMovie(0, &movie, &moviea, &movieb, n)){
       QObject::connect(movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
       movie->start();
     } else {
       if (my_qaction) my_qaction->setIcon(QIcon(interpreter_loadPixmap(n.contains(".") ? n : n + ".png")));
     }
     
   } else {

     if (n.length() > 200){ // QString contains binary data       

        if (n.left(200).contains("<svg ", Qt::CaseInsensitive)){
          QString m = n;
          m = m.trimmed();
          QSvgWidget w(0);
          w.resize(100, 100);
          QSvgRenderer *r = w.renderer();
          if (r->load(m.toLatin1())){

            QPixmap p(100, 100);
            QPainter painter(&p);
            r->render(&painter);
            if (my_qaction) my_qaction->setIcon(p);
          }
        } else {
           QPixmap pi; pi.loadFromData(n.toLatin1());
           if (my_qaction) my_qaction->setIcon(pi);
        }

     } else {
       if (my_qaction) my_qaction->setIcon(interpreter_loadPixmap(n.contains(".") ? n : n + ".png"));
     }

   }

  #endif
#endif      

    _property::SETPROPERTY_Icon(n);

#if defined(_IMAGEBUTTON)
  repaint();
#endif

  }
}

