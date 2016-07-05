
#if defined(_TEXTBOX) || defined(_COMBOBOX) || defined(_LISTBOX) || defined(_TREEVIEW)

void SETPROPERTY_SQL(const QString & n)
{ 
  
  {  
#ifdef RUN
    if (!n.isEmpty()){


#ifdef _TREEVIEW
    clear();

    QString ss = "";  
    QString s = n;

    if (s.contains(" GROUP BY ", Qt::CaseInsensitive)){
      s = s.replace(" , ", ", ");
      
      QString sTable = "";

      int n = s.indexOf(" FROM ", Qt::CaseInsensitive);
      n += 6;
      sTable = s.mid(n);
      n = sTable.indexOf(" ", Qt::CaseInsensitive);
      sTable = sTable.left(n);

      QString sGroup = "";

      n = s.indexOf(" GROUP BY ", Qt::CaseInsensitive);
      n += 10;
      sGroup = s.mid(n);
      n = sGroup.indexOf(" ORDER BY ", Qt::CaseInsensitive);
      if (n >= 0) sGroup = sGroup.left(n);
      sGroup = sGroup.simplified();

      QString sDetail = "";
      n = s.indexOf(" GROUP BY ", Qt::CaseInsensitive);
      sDetail = s.left(n);
      n = s.indexOf(" ORDER BY ", Qt::CaseInsensitive);
      if (n >= 0) sDetail += s.mid(n);
      sDetail = sDetail.simplified();

      QStringList groups = sGroup.split(",");
      QStringList values = groups;

      foreach(QString ss, groups){
        sDetail = sDetail.replace(ss + ",", "");
        sDetail = sDetail.replace(ss, "");
      }
      sDetail = sDetail.replace(",  FROM", " FROM");
      sDetail = sDetail.replace(", FROM", " FROM");

      fillWithSQLForTreeView(this, 0, sTable, sDetail, groups, values, 0);


    } else {
      QSqlQuery rr;

      if (rr.exec(s)){

        if (rr.first()){

          QSqlRecord r = rr.record();

          for (int i = 0; i < r.count() - 1; i++){
            this->headerItem()->setText(i, r.fieldName(i + 1));
          }

          do {          
            ss = "";
        
            QStringList l;
            
            for (int i = 0; i < r.count() - 1; i++){
              QString sss = rr.value(i + 1).toString();
              ss += sss;
              //ss += " | ";   
              l.append(sss);     
            }
            qulonglong recordid = rr.value(0).toULongLong();

            QTreeWidgetItem *it = new QTreeWidgetItem(this, l);
            it->setData(0, Qt::UserRole, QVariant(recordid)); 
            it->setHidden(false);

          } while (rr.next());
        }
      }

    }

#else

#ifdef _TEXTBOX
#else
    clear();
#endif

    QString ss = "";
    QSqlQuery rr;
    if (rr.exec(n)){

      if (rr.first()){

#ifdef _COMBOBOX
        addItem("", QVariant(0));
#endif
#ifdef _LISTBOX
        QListWidgetItem *it = new QListWidgetItem();
        it->setText(""); it->setData(Qt::UserRole, QVariant(0));
        addItem(it);        
#endif
        QSqlRecord r = rr.record();

        do {
          
      #ifdef _TEXTBOX
      #else
          ss = "";
      #endif
          
          for (int i = 0; i < r.count() - 1; i++){
            QString sss = rr.value(i + 1).toString();
            ss += sss;
      #ifndef _TEXTBOX
      #else
            ss += " | ";
      #endif
          }

          qulonglong recordid = rr.value(0).toULongLong();

#ifdef _COMBOBOX
          addItem(ss, QVariant(recordid));
          //addItem("ss");//, QVariant(recordid));
       //   setItemData(count(), QVariant(recordid));
        //  int n = count();
        //  n = n;
#endif
#ifdef _LISTBOX
          QListWidgetItem *it = new QListWidgetItem();
          it->setText(ss); it->setData(Qt::UserRole, QVariant(recordid));
          addItem(it);        
#endif


        } while (rr.next());
      }
    } else QMessageBox::information(this, "KBasic", rr.lastError().text());

#ifdef _TEXTBOX
        QStringList l = ss.split(" | ");
        QCompleter *c = new QCompleter(l, this);
        c->setCaseSensitivity(Qt::CaseInsensitive);
        setCompleter(c);
#endif
#endif


     }

#endif
    _property::SETPROPERTY_SQL(n);


  }
}

#endif
