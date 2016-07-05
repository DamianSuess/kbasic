
bool loadToolbar(QString m)
{ 
  if (m.isEmpty()) return false;

  QString s = "";

#ifdef RUN
    QString m2;

    if (!sCurrentLanguage.isEmpty()){
      m2 = m + "." + sCurrentLanguage + ".kbasic_toolbar";
      s = loadProjectFile(m2);
      s = s.replace("\r", "");

      // try English version
      if (s.isEmpty()){
        m2 = m + ".kbasic_toolbar";
        s = loadProjectFile(m2);
        s = s.replace("\r", "");
      }
    } else {
      m2 = m + ".kbasic_toolbar";
      s = loadProjectFile(m2);
      s = s.replace("\r", "");
    }    

    sFilename = m2;
#endif
#ifdef IDE
    QFile f(m);
    if (!f.open(QIODevice::ReadOnly)){
      QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(m));
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
    
      if ((sTypeName).compare("ToolBar") == 0){
      } else {
       // error handling
      }

      loadToolbarProperty(&s, sName);

    } else {

      eatDummyLine(&s);
     
    }

  } while ((s).length()); 

#ifdef IDE
  unselectAllControls();
#endif

  //setUpdatesEnabled(false);


  build();

  //setUpdatesEnabled(true);
#ifdef IDE  
  my_qtoolbar->show();

  setToolbarSelf();
#endif

  return true;
}

#ifdef IDE
bool saveToolbar(QString m/*, bool bAll = true*/)
{

  QString s = "";

  s += "Begin ToolBar *\n";

  s += "\n";

  saveControls(&s);

  s += "\n";
  s += "End ToolBar";
  s += "\n";

  bool bSaveCode = true;

  QStringList trl = EXTERN_my_mainwindow->getProjectPreference("Translation").split(";");

  {
    QString sExt = EXTERN_my_mainwindow->getFilenameExtension(m);
    QString q = m.left(m.length() - sExt.length() - 1);

    if (q.count(".") > 1){

      QString sLanguage = EXTERN_my_mainwindow->getFilenameExtension(q);
      if (trl.contains(sLanguage)){        
         bSaveCode = false;
      }
    }
  }

  if (bSaveCode) s += _toolbar::getToolBarClassSourceCodeForSaving(sFilename);


  QFile f(m);
  if (!f.open(QIODevice::WriteOnly )){
    QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(m));
    //  errormessage
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << s;
    f.close();
    
    //setNonModified();
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

      ct = t_toolbaritem;

      loadControl(s, ct, sName);

    } else {
      eatDummyLine(s);
    }

  } while ( !((*s).length() <= 0 || (*s).startsWith("End")) );


  /*
  _toolbaritem *c;
  _toolbaritem *m;

  if (firstControl(&c)){
   
    do {

      m = (_toolbaritem *) c;

      QString k = m->GETPROPERTY_ParentControl();

      if (k.length()){
//        c->parent = getParent(k);
      //  if (c->parent){
//           c->my_qmenu = c->parent->my_qmenu;
      //  }        
      }

    } while (nextControl(&c)); 
  }
  */

  return true;
}

bool loadToolbarProperty(QString *s, QString sName)
{ 
/*
  SETPROPERTY_Name(sName);

  do {

    const char *sss = (*s).toAscii();

    *s = (*s).trimmed();

    QString sKey;

    bool bb;
    QString ss;
    int nn;

    loadProperty(s, &sKey, &bb, &ss, &nn);

    if (sKey.isEmpty() || sKey.isNull()){      
      break;
      
    } else if (sKey == "Tag"){      
      SETPROPERTY_Tag(ss);

    // TOOLBAR_CONTROL // CONTROL


    // TOOLBAR_EVENT // EVENT

    }

    // ***

  } while ( !((*s).length() <= 0 || (*s).startsWith("Begin")) );
*/

  // load controls
  loadControls(s);

  // eat 'End ToolBar'
  *s = (*s).mid(11); 

  // load source code of form
  loadToolBarClass(s);

  return true;
}

bool loadToolBarClass(QString *s)
{ 

  while ((*s).startsWith("\n")){
    // eat '\n'
    *s = (*s).mid(1); 
  }
  //setFormClassSourceCode(*s);

  *s = "";

  return true;
}

bool loadControl(QString *s, _controlType ct, QString sName);

QString sControlName;

#ifdef IDE
bool saveControls(QString *s)
{

  _toolbaritem *c;

  if (firstControl(&c)){

    do {

      _controlType ct = controlType(c);

      sControlName = "";
      #define SWITCH GETPROPERTY_Name();      
      #define SWITCH3 sControlName
      #include "_toolbar_property_switch.h"   
      #undef SWITCH3

      *s += "\n";

      *s += "  Begin ";
      
      *s += "ToolBarItem";

      *s += " ";
      *s += sControlName + "\n";

      #define SWITCH saveProperty(s);
      #include "_toolbar_property_switch.h"    

      *s += "  End";
      *s += "\n";

    } while (nextControl(&c));
    
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
    } else {
      // error handling
    }
  } else {
    QString k = (*s).left(n2);

    k = k.trimmed();
     
    if (k.length() == 0){
      *s = (*s).mid(n2 + 1); // eat EOL
    } else {
      // error handling
    }
  }
  return true;
}

