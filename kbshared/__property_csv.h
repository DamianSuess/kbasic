


void SETPROPERTY_CSV(const QString & n)
{ 
  if (GETPROPERTY_CSV() != n){
  
  #if defined(_LISTBOX)
      
    clear();
    QString s = n;
    if (s.trimmed().length()){
      QStringList l = n.split(s.contains(",") ? "," : ";");
      for (int i = 0; i < l.size(); i++){
        QString k = l.at(i);
        if (k.startsWith("[[") && k.contains("]]")){
          int i = k.indexOf("]]");
          QString a = k.left(i);
          a = a.mid(2);
          if (!a.contains(".")) a += ".png";
          QString b = k.mid(i + 2);
          addItem(new QListWidgetItem(QIcon(loadPixmap(a)), b));
        } else {
          addItem(l.at(i));
        }
      }
    }
  #elif defined(_TREEVIEW)      
    clear();
    QString s = n;
    if (s.trimmed().length()){
      QStringList l = n.split(s.contains(",") ? "," : ";");
      for (int i = 0; i < l.size(); i++){
        QString k = l.at(i);
        if (k.startsWith("[[") && k.contains("]]")){
          int i = k.indexOf("]]");
          QString a = k.left(i);
          a = a.mid(2);
          if (!a.contains(".")) a += ".png";
          QString b = k.mid(i + 2);
          QTreeWidgetItem *it = new QTreeWidgetItem(this, QStringList(b)); 
          it->setIcon(0, QIcon(loadPixmap(a)));
        } else {
          new QTreeWidgetItem(this, QStringList(l.at(i))); 
        }
      }
    }
  #elif defined(_COMBOBOX)
		clear();
		QString s = n;
		if (s.trimmed().length()){
      QStringList l = n.split(s.contains(",") ? "," : ";");
      for (int i = 0; i < l.size(); i++){
        QString k = l.at(i);
        if (k.startsWith("[[") && k.contains("]]")){
          int i = k.indexOf("]]");
          QString a = k.left(i);
          a = a.mid(2);
          if (!a.contains(".")) a += ".png";
          QString b = k.mid(i + 2);
          addItem(QIcon(loadPixmap(a)), b);
        } else {
          addItem(l.at(i));
        }
		  }   
		}
  #endif
  


    _property::SETPROPERTY_CSV(n);
  }
}