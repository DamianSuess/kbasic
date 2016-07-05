
void SETPROPERTY_CursorAnimation(const QString & n)
{ 
  if (GETPROPERTY_CursorAnimation() != n){  

    if (n.simplified().isEmpty()){
      unsetCursor();
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
       if (setMyMovie(0, &cursoranimation_movie, &cursoranimation_moviea, &cursoranimation_movieb, n)){
         connect(cursoranimation_movie, SIGNAL(frameChanged(int)), this, SLOT(cursoranimation_frameChanged(int)));
         cursoranimation_movie->start();
       }
       
     } else {
       if (cursoranimation_movie) cursoranimation_movie->stop();
       unsetCursor();
     }

    }
  

    _property::SETPROPERTY_CursorAnimation(n);
  }
}

