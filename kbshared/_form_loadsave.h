//#ifndef _FORM_LOADSAVE_H
//#define _FORM_LOADSAVE_H
bool loadForm(QString m)
{ 
  

  if (m.isEmpty()) return false;

  //QString m =  "c:\\kbasic\\examples/test\\formtest.txt";
  QString s = "";

#ifdef RUN
    QString m2;

    if (!sCurrentLanguage.isEmpty()){
      m2 = m + "." + sCurrentLanguage + ".kbasic_form";
      s = loadProjectFile(m2);
      s = s.replace("\r", "");

      // try English version
      if (s.isEmpty()){
        m2 = m + ".kbasic_form";
        s = loadProjectFile(m2);
        s = s.replace("\r", "");
      }
    } else {
      m2 = m + ".kbasic_form";
      s = loadProjectFile(m2);
      s = s.replace("\r", "");
    }    

    sFilename = m2;
#endif
#ifdef IDE
    QFile f(m);
    if (!f.open(QIODevice::ReadOnly)){
      QMessageBox::information(this, "MYAPP", QString("Could not read from %1").arg(m));
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

    //QMessageBox::information(0,"loadForm0", "sName");   

    if (eatBegin(&s, &sName, &sTypeName)){

       
      //QMessageBox::information(0,"loadForm1", "sName");   
       //QMessageBox::information(0,"loadForm2", "sTypeName");   
    
      if (isForm() && (sTypeName).compare("Form") == 0){
        sName = getFilenameWithoutPathAndExtension();
      } else if ((sTypeName).compare("Report") == 0){
        sName = getFilenameWithoutPathAndExtension();
      } else {
       // error handling
      }



      loadFormProperty(&s, sName);

    } else {

      eatDummyLine(&s);
     
    }

  } while ((s).length());  

  QWidget *c; 

  if (firstControl(&c)){
    do {

      if (controlType(c) == t_tab){
        tabPageSelected((_tab *) c, 0);
      }        
    } while (nextControl(&c));
  }

#ifdef IDE
  if (GETPROPERTY_ScrollWidth() || GETPROPERTY_ScrollHeight()){ // show the scrollbars, if needed
    showScrollBars();
  }
#endif

  return true;
}

#ifdef IDE
bool saveForm(QString m/*, bool bAll = true*/)
{
//  if (normalMode()) return false;

  QString s = "";

  if (bObjectEditor){
    
    s += "Begin ";
    s += sObjectName;
    s += " ";
    s += GETPROPERTY_Name() + "\n";
  } else {
    if (isForm()) s += "Begin Form *\n";
    else s += "Begin Report *\n";
//    s += "Begin Form " + GETPROPERTY_Name() + "\n";
  }
  saveProperty(&s);
  s += "\n";

  if (bObjectEditor == false){
    saveControls(&s);
  }

  s += "\n";
  if (isForm()) s += "End Form";
  else s += "End Report";
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

  /*
  if (bAll){
    s += getFormClassSourceCode(false);
  } else {
*/
    //_form *f = 0;//new _form(0, 0, "", 0, true, sObjectName);
    //f->load(s, true);

  if (bSaveCode){
    QString k = _form::getFormClassSourceCodeForSaving(sFilename);
    //f->close();

    s += k;
  }

 // }

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

bool saveFormControlsOnly(QString m)
{
  return saveForm(m/*, false*/);
}

static int getFormClassSourceCodeFilePos(QString m, QString *ss)
{
  QString s = "";
  int n = 0;

  QFile f2(m);
  if (!f2.open(QIODevice::ReadOnly )){
    return 0;
  } else {
	  QTextStream t(&f2);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    *ss = t.readAll();
    n = f2.size();
	  f2.close();
  }

  QString g = m.endsWith(".kbasic_form", Qt::CaseInsensitive) ? "End Form" : "End Report";
  //g += getFilenameWithoutPathAndExtension(m);

  int n2 = (*ss).lastIndexOf(g, -1, Qt::CaseInsensitive);

  return n2 != -1 ? n2 + g.length() + 1 : n;
}

/*
static bool saveFormClassSourceCodeOnly(QString m)
{
  QString s = "";
  QString ss = "";

  int n = getFormClassSourceCodeFilePos(m, &ss);
  s = ss;
  ss = ss.left(n - 1);

  s = ss.mid(n);

  QFile f(m);
  if (!f.open(QIODevice::WriteOnly )){
    QMessageBox::information(EXTERN_my_mainwindow, MYAPP, QString("Could not read from %1").arg(m));
  } else {
    //f.at(n);
    QTextStream t(&f);
         t.setCodec("UTF-8");
         t.setAutoDetectUnicode(true);
         t.setGenerateByteOrderMark(true);

         t << ss;
    t << s;
    f.close();
  }

  return true;
}
*/

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

      ct = getControlType(sTypeName);

      loadControl(s, ct, sName);

    } else {
      eatDummyLine(s);
    }

  } while ( !((*s).length() <= 0 || (*s).startsWith("End")) );


  QWidget *c;
  bool b = false;

  if (firstControl(&c, 1)){ // , 1 because of SETPROPERTY_InputControl using firstControl() internally
   
    do {    

#ifdef RUN
      if (controlType(c) == t_label){
        ((kb_label *) c)->SETPROPERTY_InputControl(((kb_label *) c)->GETPROPERTY_InputControl());
      }
#endif

      #define SWITCH GETPROPERTY_Visible();      
      #define SWITCH3 b
      #include "_form_property_switch.h"   
      #undef SWITCH3
      
      if (b) c->show();

    } while (nextControl(&c, 1)); 
  }

  return true;
}


#ifdef IDE

bool loadFormClass(QString *s)
{ 

  while ((*s).startsWith("\n")){
    // eat '\n'
    *s = (*s).mid(1); 
  }
  //setFormClassSourceCode(*s);

  *s = "";

  return true;
}

#endif

bool loadFormProperty(QString *s, QString sName);

void applyProperty(QWidget *c, QString sKey, bool bb, QString &ss, int nn, double d);


bool loadControl(QString *s, _controlType ct, QString sName, QWidget *c = 0);

QString sControlName;

#ifdef IDE
bool saveControls(QString *s);

#endif

bool eatBegin(QString *s, QString *sName, QString *sTypeName)
{
  //QMessageBox::information(0,"eatBegin", "1");   

  //QMessageBox::information(0,"eatBegin2a", *s);   

  if ( (*s).startsWith("Begin	") || (*s).startsWith("Begin ") ){

    //QMessageBox::information(0,"eatBegin2", *s);   

    *s = (*s).mid(6); // eat 'Begin'

    int n = (*s).indexOf(" ");
    if (n < 0) n = (*s).indexOf(" "); // tab zeichen

    (*sTypeName) = (*s).left(n);

    *s = (*s).mid(n + 1); // eat type-name

    //QMessageBox::information(0,"eatBegin3", *s);   

    n = (*s).indexOf("'");
    int n2 = (*s).indexOf("\n");

    if (n >= n2 || n2 == 0 || n == -1) n = n2;

    (*sName) = (*s).left(n);
    (*sName) = (*sName).trimmed();

    //QMessageBox::information(0,"eatBegin4", *s);   

    *s = (*s).mid(n2 + 1); // eat name

    //QMessageBox::information(0,"eatBegin5", *s);   

    //QMessageBox::information(0,*sName, *sTypeName);   

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


//#endif