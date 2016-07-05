
void SETPROPERTY_Completer(const QString & n)
{ 
  if (GETPROPERTY_Completer() != n){  

#ifdef RUN

#if defined(_TEXTBOX)
      QString s = n;
      if (s.trimmed().length()){
        QStringList l = n.split(s.contains(",") ? "," : ";");
        QCompleter *c = new QCompleter(l, this);
        setCompleter(c);
      } else {
        setCompleter(0);
      }
    
#endif
#endif

    _property::SETPROPERTY_Completer(n);
  }
}

