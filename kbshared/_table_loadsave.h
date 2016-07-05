
bool loadTable(QString m)
{ 
  if (m.isEmpty()) return false;

  QString s = "";

#ifdef RUN
    QString m2 = m + ".kbasic_table";
    s = loadProjectFile(m2);
    s = s.replace("\r", "");

    sFilename = m2;
#endif
#ifdef IDE
    QFile f(m);
    if (!f.open(QIODevice::ReadOnly)){
      // maybe it is asynchron, so it is ok
//      QMessageBox::information(this, "KBasic", QString("Could not read from %1").arg(m));
    } else {
      QTextStream t(&f);
      
      t.setCodec("UTF-8");
      t.setAutoDetectUnicode(true);
      t.setGenerateByteOrderMark(true);

      s = t.readAll();
      s = s.replace("\r", "");
      f.close();
    }
#endif

  QString sTypeName = "";
  QString sName = "";  

  do {

    s = (s).trimmed();

    const char *ss = (s).toAscii();
    ss = ss;

    if (eatBegin(&s, &sName, &sTypeName)){
    
      if ((sTypeName).compare("Table") == 0){
      } else {
      }

      loadTableProperty(&s, sName);
      break;

    } else {

      eatDummyLine(&s);
     
    }

  } while ((s).length()); 

#ifdef IDE
  unselectAllControls();
#endif


  return true;
}

#ifdef IDE
bool saveTable(QString m/*, bool bAll = true*/)
{

  QString s = "";

  s += "Begin Table *\n";

  s += "\n";

  saveControls(&s);

  s += "\n";
  s += "End Table";
  s += "\nFields=";
  s += sCREATETABLE;
  s += "\n";


  QFile f(m);
  if (!f.open(QIODevice::WriteOnly )){
    QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(m));
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << s;
    f.close();

    bIsModified = false;
    
  }
  return true;
}

#endif
bool loadControls(QString *s)
{ 
  _controlType ct = t_notype;
  QString sTypeName = "";
  QString sName = "";  

  do {

    *s = (*s).trimmed();

    const char *ss = (*s).toAscii();
    ss = ss;

    if (eatBegin(s, &sName, &sTypeName)){

      ct = t_tableitem;

      loadControl(s, ct, sName);

    } else {
      eatDummyLine(s);
    }

  } while ( !((*s).length() <= 0 || (*s).startsWith("End")) );



  return true;
}

bool loadTableProperty(QString *s, QString sName)
{ 


  // load controls
  loadControls(s);

  // eat 'End Table'
  *s = (*s).mid(9); 

  return true;
}


bool loadControl(QString *s, _controlType ct, QString sName)
{ 
  _tableitem *c = 0;

  #define SWITCH4 ();
  #define SWITCH3 c
  #include "_table_property_switch.h" 
  #undef SWITCH3
  #undef SWITCH4


  METHOD_insertControl(c, ct);


  #define SWITCH SETPROPERTY_Name(sName);
  #include "_table_property_switch.h"       


  do {

    const char *sss = (*s).toAscii();

    *s = (*s).trimmed();

    QString sKey;

    bool bb;
    QString ss;
    int nn;

    #define SWITCH loadProperty(s, &sKey, &bb, &ss, &nn);
    #include "_table_property_switch.h"       


    // TABLE_CONTROL // CONTROL 
/*
    if (sKey == "Null"){      
      #define SWITCH SETPROPERTY_Null(bb);
      #include "_table_property_switch.h"   
    } else */
      
    if (sKey == "Index"){      
      #define SWITCH SETPROPERTY_Index(bb);
      #include "_table_property_switch.h"   

    } else if (sKey == "Type"){   
      #define SWITCH SETPROPERTY_Type(ss);
      #include "_table_property_switch.h"   

    } else if (sKey == "Tag"){      
      #define SWITCH SETPROPERTY_Tag(ss);
      #include "_table_property_switch.h"   


    
    // TABLE_EVENT
/*
    } else if (sKey == "OnEvent"){      
      #define SWITCH SETPROPERTY_OnEvent(bb);
      #include "_table_property_switch.h"  
*/
    }

    // ***

  } while ( !((*s).length() <= 0 || (*s).startsWith("End")/* || (*s).startsWith("End ") || (*s).startsWith("End'") || (*s).startsWith("End\n") || (*s).startsWith("End ")*/) );

  *s = (*s).mid(3); // eat 'End'

  return true;
}

QString sControlName;

#ifdef IDE
bool saveControls(QString *s)
{

  QString sType = "";
  _tableitem *c;

  for (int i = 0; i < 64; i++){

    if (firstControl(&c)){

      do {

        if (c->nRow == i){

          _controlType ct = controlType(c);

          sControlName = "";
          #define SWITCH GETPROPERTY_Name();      
          #define SWITCH3 sControlName
          #include "_table_property_switch.h"   
          #undef SWITCH3

          sType = "";
          #define SWITCH GETPROPERTY_Type();      
          #define SWITCH3 sType
          #include "_table_property_switch.h"   
          #undef SWITCH3

          if (!sCREATETABLE.isEmpty()) sCREATETABLE += ", ";
          sCREATETABLE += sControlName + " As " + sType;

          if (sControlName == "kbrecordid") continue; // user may not change it, it is handled by kbasic
          if (sControlName.isEmpty()) continue;

          *s += "\n";

          *s += "  Begin ";
          
          *s += "TableItem";

          *s += " ";
          *s += sControlName + "\n";

          #define SWITCH saveProperty(s);
          #include "_table_property_switch.h"    

          *s += "  End";
          *s += "\n";
          break;
        }

      } while (nextControl(&c));
      
    }


  }
  return true;
}

#endif
bool eatBegin(QString *s, QString *sName, QString *sTypeName)
{
  if ( (*s).startsWith("Begin ") || (*s).startsWith("Begin ") ){

    *s = (*s).mid(6); // eat 'Begin'

    int n = (*s).indexOf(" ");
    if (n < 0) n = (*s).indexOf(" "); // tab zeichen

    (*sTypeName) = (*s).left(n);
    (*sTypeName) = (*sTypeName).trimmed();

    *s = (*s).mid(n + 1); // eat type-name

    n = (*s).indexOf("'");
    int n2 = (*s).indexOf("\n");

    if (n >= n2 || n2 == 0 || n == -1) n = n2;

    (*sName) = (*s).left(n);
    (*sName) = (*sName).trimmed();

    *s = (*s).mid(n2 + 1); // eat name

    return true;
  }
  return false;
}

bool eatDummyLine(QString *s)
{
  int n = (*s).indexOf("'");
  int n2 = (*s).indexOf("\n");

  if (n2 > n){
    QString k = (*s).left(n);

    k = k.trimmed();
     
    if (k.length() == 0){
      *s = (*s).mid(n2 + 1); // eat comment
    }
  } else {
    QString k = (*s).left(n2);

    k = k.trimmed();
     
    if (k.length() == 0){
      *s = (*s).mid(n2 + 1); // eat EOL
    }
  }
  return true;
}

