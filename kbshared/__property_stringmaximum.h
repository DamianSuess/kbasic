
void SETPROPERTY_StringMaximum(const QString & n)
{ 
  if (GETPROPERTY_StringMaximum() != n){  

#ifdef RUN

#if defined(_DATEBOX)
      QString y = n.left(4);
      QString m = n.mid(5, 2);
      QString d = n.mid(8, 2);
      setMaximumDate(QDate(y.toInt(), m.toInt(), d.toInt()));
#elif defined(_TIMEBOX)
      QString h = n.left(2);
      QString m = n.mid(3, 2);
      QString s = n.mid(6, 2);
      setTime(QTime(h.toInt(), m.toInt(), s.toInt()));
#elif defined(_DATETIMEBOX)
      QString y = n.left(4);
      QString m = n.mid(5, 2);
      QString d = n.mid(8, 2);
      QString h = n.left(13);
      QString mi = n.mid(15, 2);
      QString s = n.mid(17, 2);
      setMaximumDate(QDate(y.toInt(), m.toInt(), d.toInt()));
      setMaximumTime(QTime(h.toInt(), mi.toInt(), s.toInt()));
#endif
    
#endif

    _property::SETPROPERTY_StringMaximum(n);
  }
}

