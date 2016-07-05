/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#include <QTextEdit>
#include <QApplication>
#include <QFile>
#include <QTextStream>



#include "_inputtip_parser.h"

#include "../kbshared/_form.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"

#include "_mainwindow.h"

extern _mainwindow *EXTERN_my_mainwindow;

extern QList<_inputtip_info> ci_listAs;

extern bool bSelfTest;


QString sLastTERM;
QString sLastLastTERM;
QString sLastTERM2;


QList<_class>framework_classes;
QList<_variable>framework_variables;
QList<_method>framework_methods;



_inputtip_parser::_inputtip_parser()
{
  bShouldClose = false;
  bCanClose = true;
}

_inputtip_parser::~_inputtip_parser()
{
  while(bCanClose == false){
    qApp->processEvents(QEventLoop::AllEvents, 100);
  }
}


bool _inputtip_parser::insideString(int n)
{
  int nRet = sText.lastIndexOf("\n", n);
  if (nRet == -1) nRet = 0;
/*
  int nRet2 = sText.indexOf("\n", n);
  if (nRet2 == -1) nRet2 = 0;
*/
  QString s = sText.mid(n, 1);

 // if (s == "'")
  //{
    QString l = sText.mid(nRet, n - nRet);
   // QString r = sText.mid(nRet2, n - nRet2);
    int ll = l.count("\"");
   // int rr = r.count("\"");
    if (ll && ll % 2 != 0){
      return true;
    }
 
/*
  } else {
  }*/

  return false;
}

QString _inputtip_parser::prepareSourceCodeDefinition(QString sFile)
{
  QString sText = "";

  QFile f(sFile);
  if (!f.open(QIODevice::ReadOnly)){
    QMessageBox::information(0, MYAPP, QString("Could not read from %1").arg(sFile));
    return "";
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    sText = t.readAll();
    sText = sText.replace("\r", "");
    f.close();
  }
  
  int n = sText.indexOf("Begin");
  n++;

  static QString sDefinition;
  sDefinition = "";
  QString sConstructor = "";

  sDefinition += "\n";

  do {
    n = sText.indexOf("Begin ", n);
    if (n == -1) break;
    int n2 = sText.indexOf("\n", n);
    n += 6;
    QString sLine = sText.mid(n, n2 - n);
    int n3 = sLine.indexOf(" ");
    QString sType = sLine.mid(0, n3);
    QString sName = sLine.mid(n3 + 1);

    sDefinition += "Private ";
    sDefinition += sName;
    sDefinition += " As ";
    sDefinition += sType;
    sDefinition += "\n";

    sConstructor += sName;
    sConstructor += " = Control(\"";
    sConstructor += sName;
    sConstructor += "\")\n";

  } while (true);

  return sDefinition;
}

void _inputtip_parser::parse(QString _sFilename, QString t)
{
  if (bSelfTest) return; // if self test is running do not parse

  framework_parse();

  sFilename = _sFilename;
  sText = t;
  sText.simplified();

/*
  QString sAllText = "";

  if (sFilename.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){  
    int n = _menubar::getMenuBarClassSourceCodeFilePos(sFilename, &sAllText);
    sAllText = sAllText.left(n);
  } else if (sFilename.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){  
    int n = _toolbar::getToolBarClassSourceCodeFilePos(sFilename, &sAllText);
    sAllText = sAllText.left(n);
  } else if (sFilename.endsWith(".kbasic_form", Qt::CaseInsensitive)){  
    int n = _form::getFormClassSourceCodeFilePos(sFilename, &sAllText);
    sAllText = sAllText.left(n);
  }

  int mm = sAllText.count("\n");
  if (mm){
    sAllText.fill(QChar('\n'), mm);
    sText = sAllText + sText;
  }*/

  // eat comments ' / * * / / * *
  {
    int u = 0;
    while(true){
      qApp->processEvents(QEventLoop::AllEvents, 100);
      if (qApp->closingDown()){
        bCanClose = true;
        return;
      }
re:
      if (bShouldClose) return;

      if (sText.isEmpty()) break;
      if (sText.isNull()) break;

      int x = 0;
      int y = 0;
      int k;
      int k2;
      k = sText.indexOf("<?", u);
      if (k >= 0){

        while (k < sText.length()){
          int x = sText.indexOf("?>", k + 1);
          int y = sText.indexOf("<?", k + 1);
          if (y >= 0 && x < y){
            QString s = sText;
            sText = s.left(k);
            QString w = s.mid(k, x - k);
            int ww = w.count("\n");
            w.fill(QChar('\n'), ww);
            sText += w;
            sText += s.mid(x + 2);
            u = k;

            goto re;
          } else {

            QString s = sText;
            sText = s.left(k);
            QString w = s.mid(k, x - k);
            int ww = w.count("\n");
            w.fill(QChar('\n'), ww);
            sText += w;
            sText += s.mid(x + 2);
            u = k;

            goto re;
          }
        }
        goto re;
      }

      k = sText.indexOf("/*", u);
      if (k >= 0){
        if (insideString(k)){
          u++;
          continue;
        }
        int k2 = sText.indexOf("*/", k);
        if (k2 >= 0){
          QString s = sText;
          sText = s.left(k);
          QString w = s.mid(k, k2 - k);
          int ww = w.count("\n");
          w.fill(QChar('\n'), ww);
          sText += w;
          sText += s.mid(k2 + 2);
          u = k;
          continue;
        }
      }

      k = sText.indexOf("'", u);
      if (k >= 0){
        if (insideString(k)){
          u++;
          continue;
        }
        int k2 = sText.indexOf("\n", k);
        if (k2 >= 0){
          QString s = sText;
          sText = s.left(k);
          //sText += "\n";
          sText += s.mid(k2);
          u = k;
          continue;
        }
      }

      break;
    }
  }
/*
  QTextEdit *ttt = new QTextEdit(sText);
  ttt->show();
  return;*/

  nPos = 0;
  nLineCorrector = 0;

  QString tt = EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(sFilename);
  if (sFilename.endsWith(".kbasic_form", Qt::CaseInsensitive) && !sText.contains("Inherits Form", Qt::CaseInsensitive)){
    QString k = prepareSourceCodeDefinition(sFilename);
    nLineCorrector = k.count("\n");
    sText.prepend(k);
    sText.prepend(" Inherits Form : ");
    sText.prepend(tt);
    sText.prepend("Class ");
    sText.append("\nEnd Class\n");
  } else if (sFilename.endsWith(".kbasic_report", Qt::CaseInsensitive) && !sText.contains("Inherits Report", Qt::CaseInsensitive)){
    QString k = prepareSourceCodeDefinition(sFilename);
    nLineCorrector = k.count("\n");
    sText.prepend(k);
    sText.prepend(" Inherits Report : ");
    sText.prepend(tt);
    sText.prepend("Class ");
    sText.append("\nEnd Class\n");
  } else if (sFilename.endsWith(".kbasic_menubar", Qt::CaseInsensitive) && !sText.contains("Inherits MenuBar", Qt::CaseInsensitive)){
    QString k = prepareSourceCodeDefinition(sFilename);
    nLineCorrector = k.count("\n");
    sText.prepend(k);
    sText.prepend(" Inherits MenuBar : ");
    sText.prepend(tt);
    sText.prepend("Class ");
    sText.append("\nEnd Class\n");
  } else if (sFilename.endsWith(".kbasic_toolbar", Qt::CaseInsensitive) && !sText.contains("Inherits ToolBar", Qt::CaseInsensitive)){
    QString k = prepareSourceCodeDefinition(sFilename);
    nLineCorrector = k.count("\n");
    sText.prepend(k);
    sText.prepend(" Inherits ToolBar : ");
    sText.prepend(tt);
    sText.prepend("Class ");
    sText.append("\nEnd Class\n");
  }

  nLen = sText.length();

  classes.clear();
  modules.clear();
  constants.clear(); 
  variables.clear();
  properties.clear();
  methods.clear();
  enums.clear();
  types.clear();

  do {
    //if (sText == 0) break;

    qApp->processEvents(QEventLoop::AllEvents, 100);
    if (qApp->closingDown()){
      bCanClose = true;
      return;
    }

    while(bShouldClose == false && TERM2(" "));
    while(bShouldClose == false && TERM2("\n"));

    if (bShouldClose) break;

    QString r = sText.mid(nPos);
    r = r;

       //  if (fWHITESPACE());
         if (fMETHOD());
    else if (fCONST()); // after fMETHOD!
    else if (fENUM());
    else if (fTYPE());
    else if (fVAR()); // after fTYPE and others!
    else if (fPROPERTY()); // after fTYPE and others!
    else if (fCLASS());
    else if (fMODULE());
    else if (TO("\n")); // ignore unknown syntax

  } while (nPos < nLen);

  /*
  QString s = debug();
  QTextEdit *ttt = new QTextEdit(s);
  ttt->showMaximized();*/
  
}



QList<_inputtip_info> _inputtip_parser::framework_getAsForFile(QString sScope)
{
  framework_parse();

  static QList<_inputtip_info> l;
  if (sScope != "999") return l;

  static QList<_inputtip_info> l999;
  if (l999.count()) return l999;
  
  foreach (_class v, framework_classes)
  { 
    append(l999, v.name, __class, "", "", 0, v.type, "");
  }

  return l999;
}

QList<_inputtip_info> _inputtip_parser::getAllForFile(QString sForFile)
{
  static QList<_inputtip_info> l;
  l.clear();

  bool b = sForFile == sFilename; // equal file?
  if (!b) return l;

  bool b2 = true;
  bool b3 = false;

  foreach (_constant v, constants)
  { 
    if (v.file.compare(sForFile, Qt::CaseInsensitive) == 0) append(l, v.name, __constant, "", v.file, v.line, v.scope, v.scope2);
  }

  foreach (_variable v, variables)
  { 
    if (v.file.compare(sForFile, Qt::CaseInsensitive) == 0) append(l, v.name, __variable, v.type_name, v.file, v.line, v.scope, v.scope2);
  }

  foreach (_property2 v, properties)
  { 
    if (v.file.compare(sForFile, Qt::CaseInsensitive) == 0) append(l, v.name, __property2, v.type_name, v.file, v.line, v.scope, v.scope2);
  }

  foreach (_method v, methods)
  { 
    if (v.file.compare(sForFile, Qt::CaseInsensitive) == 0) append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", v.file, v.line, v.scope, "");
  }

  foreach (_enum v, enums)
  { 
    if (v.file.compare(sForFile, Qt::CaseInsensitive) == 0) append(l, v.name, __enum, "", v.file, v.line, v.scope, "");
  }
  foreach (_type v, types)
  { 
    if (v.file.compare(sForFile, Qt::CaseInsensitive) == 0) append(l, v.name, __type, "", v.file, v.line, v.scope, "");
  }
    
  return l;
}

QList<_inputtip_info> _inputtip_parser::getAsForFile(QString sForFile, QString sScope)
{
  bool b = sForFile == sFilename; // equal file?
  bool b2 = sScope.isEmpty();
  bool b3 = sScope == "999" || sScope == "888";

  static QList<_inputtip_info> l;
  l.clear();

  if (sScope != "888") l += framework_getAsForFile(sScope);

  foreach (_class v, classes)
  { 
    if (b || b3 || v.modifier == _public) append(l, v.name, __class, "", v.file, v.line, v.type, "");
  }

  foreach (_enum v, enums)
  { 
    if (b || b3 || v.modifier == _public && (b2 || b3 || v.scope.compare(sScope, Qt::CaseInsensitive) == 0)) append(l, v.name, __enum, "", v.file, v.line, v.scope, "");
  }
  foreach (_type v, types)
  { 
    if (b || b3 || v.modifier == _public && (b2 || b3 || v.scope.compare(sScope, Qt::CaseInsensitive) == 0)) append(l, v.name, __type, "", v.file, v.line, v.scope, "");
  }
  return l;
}

QList<_inputtip_info> _inputtip_parser::framework_getDotForFile(QString sScope, QString sScope2, QString sDot)
{
  framework_parse();

  static QList<_inputtip_info> l;
  l.clear();

  bool b = false;
  bool b3 = sDot == "999";
  bool b4 = sScope == "777";

  if (sDot.isEmpty()) return l;
   
  foreach (_class v, framework_classes)
  { 
    if (b3 || ((b || v.modifier == _public) && v.name.compare(sDot, Qt::CaseInsensitive) == 0)/* || v.type.compare("Control", Qt::CaseInsensitive) == 0)*/){
      bool bControl = v.type == "Control";

      if (bControl){
        foreach (_variable v, framework_variables)
        { 
          if (v.scope.compare("Control", Qt::CaseInsensitive) == 0) append(l, v.name, __variable, v.type_name, "", 0, v.scope, "Framework");
        }

        foreach (_method v, framework_methods)
        { 
          if (v.scope.compare("Control", Qt::CaseInsensitive) == 0) append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", "", 0, v.scope, "Framework");
        }
      }

      foreach (_variable v, framework_variables)
      { 
        if (b3 || ((v.modifier == _public || (v.scope.compare(sScope, Qt::CaseInsensitive) == 0 || (bControl && v.scope.compare("Control", Qt::CaseInsensitive) == 0))) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()))) append(l, v.name, __variable, v.type_name, "", 0, v.scope, "Framework");
      }

      foreach (_method v, framework_methods)
      { 
        if (b3 || ((v.modifier == _public || v.modifier == _protected || (v.scope.compare(sScope, Qt::CaseInsensitive) == 0) || (bControl && v.scope.compare("Control", Qt::CaseInsensitive) == 0)) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0)) append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", "", 0, v.scope, "Framework");
      }

    }
  }
  
  if (!b4){
    foreach (_variable v, variables)
    { 
      if (b3 || ((b || v.modifier == _public) && v.name.compare(sDot, Qt::CaseInsensitive) == 0 &&  v.scope.compare(sScope, Qt::CaseInsensitive) == 0)){
        QString save = sDot;
        sDot = v.type;

        foreach (_class v, framework_classes)
        { 
          if (b3 || (v.name.compare(sDot, Qt::CaseInsensitive) == 0)){            

            foreach (_variable v, framework_variables)
            { 
              append(l, v.name, __variable, v.type_name, "", 0, v.scope, "Framework");
            }

            foreach (_method v, framework_methods)
            { 
              append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", "", 0, v.scope, "Framework");
            }
            
          }
          
        }
        sDot = save;

      }        
    }
    
  }

  return l;
}

QList<_inputtip_info> _inputtip_parser::framework_getEventsForClass(QString sDot)
{
  framework_parse();

  static QList<_inputtip_info> l;
  l.clear();

  if (sDot.isEmpty()) return l;
   
  foreach (_class v, framework_classes)
  { 
    if (((v.modifier == _public) && v.name.compare(sDot, Qt::CaseInsensitive) == 0)){

      foreach (_method v, framework_methods)
      { 
        if (v.methodtype == _event && v.scope == sDot){
          append(l, v.name, __event2, "", v.type, 0, v.scope, v.def);
        }
      }
      
    }
  }
  
  foreach (_method v, framework_methods)
  { 
    if (v.methodtype == _event && v.scope == "Control"){
      append(l, v.name, __event2, "", v.type, 0, v.scope, v.def);
    }
  }

  return l;
}

QList<_inputtip_info> _inputtip_parser::getDotForFile(QString sForFile, QString sScope, QString sScope2, QString sDot)
{
  bCanClose = false;

  bool b = sForFile == sFilename; // equal file?
  bool b3 = sDot == "999";

  static QList<_inputtip_info> l;
  l.clear();

  int n = l.count();
  n = n;

  if (sDot.isEmpty()){
    bCanClose = true;
    return l;
  }

  if (sDot.compare("ME", Qt::CaseInsensitive) == 0){
    sDot = sScope;
    foreach (_class v, classes)
    { 
      qApp->processEvents(QEventLoop::AllEvents, 100);
      if (qApp->closingDown()){
        bCanClose = true;
        return l;
      }

      if (v.name.compare(sScope, Qt::CaseInsensitive) == 0){
        sDot = v.type;
        addFrameworkClasses(l, sDot);
        break;
      }
    }
  }
  if (sDot.compare("PARENT", Qt::CaseInsensitive) == 0){
    foreach (_class v, classes)
    { 
      qApp->processEvents(QEventLoop::AllEvents, 100);
      if (qApp->closingDown()){
        bCanClose = true;
        return l;
      }

      if (v.name.compare(sScope, Qt::CaseInsensitive) == 0){
        sDot = v.type;
        addFrameworkClasses(l, sDot);
        break;
      }
    }
  }
    
  foreach (_class v, classes)
  { 
    qApp->processEvents(QEventLoop::AllEvents, 100);
    if (qApp->closingDown()){
      bCanClose = true;
      return l;
    }

    if (b3 || ((b || v.modifier == _public) && v.name.compare(sDot, Qt::CaseInsensitive) == 0)){

      foreach (_constant v, constants)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()))) append(l, v.name, __constant, "", v.file, v.line, v.scope, v.scope2);
      }

      foreach (_variable v, variables)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()))) append(l, v.name, __variable, v.type_name, v.file, v.line, v.scope, v.scope2);
      }

      foreach (_property2 v, properties)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()))) append(l, v.name, __property2, v.type_name, v.file, v.line, v.scope, v.scope2);
      }

      foreach (_method v, methods)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.modifier == _protected || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0)) append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", v.file, v.line, v.scope, "");
      }

      foreach (_enum v, enums)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0)) append(l, v.name, __enum, "", v.file, v.line, v.scope, "");
      }
      foreach (_type v, types)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0)) append(l, v.name, __type, "", v.file, v.line, v.scope, "");
      }

      //return l;
    }
  }

  foreach (_module v, modules)
  { 
    qApp->processEvents(QEventLoop::AllEvents, 100);
    if (qApp->closingDown()){
      bCanClose = true;
      return l;
    }
    if (b3 || ((b || v.modifier == _public) && v.name.compare(sDot, Qt::CaseInsensitive) == 0)){

      foreach (_constant v, constants)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()))) append(l, v.name, __constant, "", v.file, v.line, v.scope, v.scope2);
      }

      foreach (_variable v, variables)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()))) append(l, v.name, __variable, v.type_name, v.file, v.line, v.scope, v.scope2);
      }

      foreach (_method v, methods)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.modifier == _protected || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0)) append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", v.file, v.line, v.scope, "");
      }

      foreach (_enum v, enums)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0)) append(l, v.name, __enum, "", v.file, v.line, v.scope, "");
      }
      foreach (_type v, types)
      { 
        qApp->processEvents(QEventLoop::AllEvents, 100);
        if (qApp->closingDown()){
          bCanClose = true;
          return l;
        }
        if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0)) append(l, v.name, __type, "", v.file, v.line, v.scope, "");
      }

      return l;
    }
  }
  
  {
    foreach (_variable v, variables)
    { 
      qApp->processEvents(QEventLoop::AllEvents, 100);
      if (qApp->closingDown()){
        bCanClose = true;
        return l;
      }
      if (b3 || ((b || v.modifier == _public) && v.name.compare(sDot, Qt::CaseInsensitive) == 0 &&  v.scope.compare(sScope, Qt::CaseInsensitive) == 0)){
        QString save = sDot;
        sDot = v.type;        

        do {
          l += framework_getDotForFile("", "", sDot);

          //if (b3 == false) l += getDotForFile(sForFile, "", "", save);

          foreach (_class v, classes)
          { 
            qApp->processEvents(QEventLoop::AllEvents, 100);
            if (qApp->closingDown()){
              bCanClose = true;
              return l;
            }
            if (b3 || (v.name.compare(sDot, Qt::CaseInsensitive) == 0)){

              foreach (_constant v, constants)
              { 
                qApp->processEvents(QEventLoop::AllEvents, 100);
                if (qApp->closingDown()){
                  bCanClose = true;
                  return l;
                }
                if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()))) append(l, v.name, __constant, "", v.file, v.line, v.scope, v.scope2);
              }

              foreach (_variable v, variables)
              { 
                qApp->processEvents(QEventLoop::AllEvents, 100);
                if (qApp->closingDown()){
                  bCanClose = true;
                  return l;
                }
                if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()))) append(l, v.name, __variable, v.type_name, v.file, v.line, v.scope, v.scope2);
              }

              foreach (_property2 v, properties)
              { 
                qApp->processEvents(QEventLoop::AllEvents, 100);
                if (qApp->closingDown()){
                  bCanClose = true;
                  return l;
                }
                if (b3 || ((v.modifier == _public || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()))) append(l, v.name, __property2, v.type_name, v.file, v.line, v.scope, v.scope2);
              }

              foreach (_method v, methods)
              { 
                qApp->processEvents(QEventLoop::AllEvents, 100);
                if (qApp->closingDown()){
                  bCanClose = true;
                  return l;
                }
                if (b3 || ((v.modifier == _public || v.modifier == _protected || v.scope.compare(sScope, Qt::CaseInsensitive) == 0) && v.scope.compare(sDot, Qt::CaseInsensitive) == 0)) append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", v.file, v.line, v.scope, "");
              }
              
            }
            
          }

          foreach (_enum v, enums)
          { 
            qApp->processEvents(QEventLoop::AllEvents, 100);
            if (qApp->closingDown()){
              bCanClose = true;
              return l;
            }
            if (b3 || (v.name.compare(sDot, Qt::CaseInsensitive) == 0)){
              int i = 0;
              while (!v.def[i].name.isEmpty()){
                qApp->processEvents(QEventLoop::AllEvents, 100);
                if (qApp->closingDown()){
                  bCanClose = true;
                  return l;
                }
                append(l, v.def[i].name, __dummy, "", v.file, v.line, v.scope, "");   
                i++;
              }
            }        
          }
          
          foreach (_type v, types)
          { 
            qApp->processEvents(QEventLoop::AllEvents, 100);
            if (qApp->closingDown()){
              bCanClose = true;
              return l;
            }
            if (b3 || (v.name.compare(sDot, Qt::CaseInsensitive) == 0)){
              int i = 0;
              while (!v.def[i].name.isEmpty()){
                qApp->processEvents(QEventLoop::AllEvents, 100);
                if (qApp->closingDown()){
                  bCanClose = true;
                  return l;
                }
                append(l, v.def[i].name, __dummy, "", v.file, v.line, v.scope, "");   
                i++;
              }
            }   
          }     
          bool bb = false;

          // finding parent class
          if (!b3){            


            foreach (_inputtip_info vv, ci_listAs)
            { 
              qApp->processEvents(QEventLoop::AllEvents, 100);
              if (qApp->closingDown()){
                bCanClose = true;
                return l;
              }
              if (vv.name.compare(sDot, Qt::CaseInsensitive) == 0){
                sDot = vv.scope;
                if (sDot == "Control") break;
                bb = true;
                break;
              }
            }  
            /*
            if (!bb){
              foreach (_class vv, framework_classes)
              { 
                if ((vv.modifier == _public) && vv.name.compare(sDot, Qt::CaseInsensitive) == 0){
                  sDot = vv.type;
                  bb = true;
                  break;
                }
              }     
            }*/
          } else break;
          if (!bb) break;

        } while(!sDot.isEmpty());

        sDot = save;

      }        
    }
    
  }

  {
    foreach (_method v, methods)
    { 
      qApp->processEvents(QEventLoop::AllEvents, 100);
      if (qApp->closingDown()){
        bCanClose = true;
        return l;
      }
      if (b3 || ((b || v.modifier == _public) && v.name.compare(sDot, Qt::CaseInsensitive) == 0 &&  v.scope.compare(sScope, Qt::CaseInsensitive) == 0)){
        append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", v.file, v.line, v.scope, "");        
      }        
    }
    
  }

  {
    foreach (_enum v, enums)
    { 
      qApp->processEvents(QEventLoop::AllEvents, 100);
      if (qApp->closingDown()){
        bCanClose = true;
        return l;
      }
      if (b3 || ((b || v.modifier == _public) && v.name.compare(sDot, Qt::CaseInsensitive) == 0 &&  v.scope.compare(sScope, Qt::CaseInsensitive) == 0)){
        int i = 0;
        while (!v.def[i].name.isEmpty()){
          qApp->processEvents(QEventLoop::AllEvents, 100);
          if (qApp->closingDown()){
            bCanClose = true;
            return l;
          }
          append(l, v.def[i].name, __dummy, "", v.file, v.line, v.scope, "");   
          i++;
        }
      }        
    }
    
  }

  {
    foreach (_type v, types)
    { 
      qApp->processEvents(QEventLoop::AllEvents, 100);
      if (qApp->closingDown()){
        bCanClose = true;
        return l;
      }
      if (b3 || ((b || v.modifier == _public) && v.name.compare(sDot, Qt::CaseInsensitive) == 0 &&  v.scope.compare(sScope, Qt::CaseInsensitive) == 0)){
        int i = 0;
        while (!v.def[i].name.isEmpty()){
          qApp->processEvents(QEventLoop::AllEvents, 100);
          if (qApp->closingDown()){
            bCanClose = true;
            return l;
          }
          append(l, v.def[i].name, __dummy, "", v.file, v.line, v.scope, "");   
          i++;
        }
      }        
    }
    
  }

  bCanClose = true;

  return l;
}

QList<_inputtip_info> _inputtip_parser::framework_getDotMethodForFile(QString sScope, QString sScope2, QString sDot)
{
  framework_parse();

  static QList<_inputtip_info> l;
  l.clear();

  if (sDot.isEmpty()) return l;

  if (sDot.compare("ME", Qt::CaseInsensitive) == 0) sDot = sScope;
  if (sDot.compare("PARENT", Qt::CaseInsensitive) == 0){
    foreach (_class v, framework_classes)
    { 
      if (v.name.compare(sScope, Qt::CaseInsensitive) == 0){
        sDot = v.type;
        break;
      }
    }
  }
    
  {
    foreach (_method v, framework_methods)
    { 
      if (/*(b || v.modifier == _public) && */v.name.compare(sDot, Qt::CaseInsensitive) == 0/* &&  v.scope.compare(sScope, Qt::CaseInsensitive) == 0*/){
        QString s = v.def;
        s = s.prepend("(");
        s = s.append(")");
        s = s.prepend(v.name);
        if (!v.type.isEmpty()){
          s = s.append(" As ");
          s = s.append(v.type);
        }
        s = s.prepend(v.methodtype == _constructor ? "Constructor " : v.methodtype == _function ? "Function " : "Sub ");
        append(l, s, __dummy, "", "", 0, v.scope, "");        
      }        
    }
    return l;
  }

  return l;
}


QList<_inputtip_info> _inputtip_parser::getDotMethodForFile(QString sForFile, QString sScope, QString sScope2, QString sDot)
{
  bool b = sForFile == sFilename; // equal file?

  static QList<_inputtip_info> l;
  l.clear();
  
  l += framework_getDotMethodForFile(sScope, sScope2, sDot);

  if (sDot.isEmpty()) return l;

  if (sDot.compare("ME", Qt::CaseInsensitive) == 0) sDot = sScope;
  if (sDot.compare("PARENT", Qt::CaseInsensitive) == 0){
    foreach (_class v, classes)
    { 
      if (v.name.compare(sScope, Qt::CaseInsensitive) == 0){
        sDot = v.type;
        break;
      }
    }
  }
    
  {
    foreach (_method v, methods)
    { 
      if (/*(b || v.modifier == _public) && */v.name.compare(sDot, Qt::CaseInsensitive) == 0/* &&  v.scope.compare(sScope, Qt::CaseInsensitive) == 0*/){
        QString s = v.def;
        s = s.prepend("(");
        s = s.append(")");
        s = s.prepend(v.name);
        if (!v.type.isEmpty()){
          s = s.append(" As ");
          s = s.append(v.type);
        }
        s = s.prepend(v.methodtype == _constructor ? "Constructor " : v.methodtype == _function ? "Function " : "Sub ");
        append(l, s, __dummy, "", v.file, v.line, v.scope, "");        
      }        
    }
    return l;
  }

  return l;
}


QList<_inputtip_info> _inputtip_parser::getFindDefinition(QString sForFile, QString sScope, QString sScope2, QString sDot, QString sBeforeDot)
{
  bool b = sForFile == sFilename; // equal file?

  static QList<_inputtip_info> l;
  l.clear();
  
  //l += framework_getDotMethodForFile(sScope, sScope2, sDot);

  if (sDot.isEmpty()) return l;

  if (sDot.compare("ME", Qt::CaseInsensitive) == 0) sDot = sScope;
  if (sDot.compare("PARENT", Qt::CaseInsensitive) == 0){
    foreach (_class v, classes)
    { 
      if (v.name.compare(sScope, Qt::CaseInsensitive) == 0){
        sDot = v.type;
        break;
      }
    }
  }    

  foreach (_class v, classes)
  { 
    if (sBeforeDot.isEmpty() && v.name.compare(sDot, Qt::CaseInsensitive) == 0){
      append(l, v.name, __class, "", v.file, v.line, "", "");
    }
    bool b = v.name.compare(sBeforeDot, Qt::CaseInsensitive) == 0;
    if (v.name.compare(sScope, Qt::CaseInsensitive) == 0 || b){

      foreach (_constant v, constants)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b ||(v.scope.compare(sScope, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty())))) append(l, v.name, __constant, "", v.file, v.line, v.scope, v.scope2);
      }

      foreach (_variable v, variables)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b ||(v.scope.compare(sScope, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty())))) append(l, v.name, __variable, v.type_name, v.file, v.line, v.scope, v.scope2);
      }

      foreach (_property2 v, properties)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b ||(v.scope.compare(sScope, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty())))) append(l, v.name, __property2, v.type_name, v.file, v.line, v.scope, v.scope2);
      }

      foreach (_method v, methods)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b ||(v.scope.compare(sScope, Qt::CaseInsensitive) == 0))) append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", v.file, v.line, v.scope, "");
      }

      foreach (_enum v, enums)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b ||(v.scope.compare(sScope, Qt::CaseInsensitive) == 0))) append(l, v.name, __enum, "", v.file, v.line, v.scope, "");
      }
      foreach (_type v, types)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b ||(v.scope.compare(sScope, Qt::CaseInsensitive) == 0))) append(l, v.name, __type, "", v.file, v.line, v.scope, "");
      }
    }
  }

  foreach (_module v, modules)
  { 
    if (sBeforeDot.isEmpty() && v.name.compare(sDot, Qt::CaseInsensitive) == 0){
      append(l, v.name, __module, "", v.file, v.line, "", "");
    }
    bool b = v.name.compare(sBeforeDot, Qt::CaseInsensitive) == 0;
    if (v.name.compare(sScope, Qt::CaseInsensitive) == 0 || b){
     
      foreach (_constant v, constants)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b || (v.scope.compare(sScope, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty())))) append(l, v.name, __constant, "", v.file, v.line, v.scope, v.scope2);
      }

      foreach (_variable v, variables)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b || (v.scope.compare(sScope, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty())))) append(l, v.name, __variable, v.type_name, v.file, v.line, v.scope, v.scope2);
      }

      foreach (_method v, methods)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b || (v.scope.compare(sScope, Qt::CaseInsensitive) == 0))) append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", v.file, v.line, v.scope, "");
      }

      foreach (_enum v, enums)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b || (v.scope.compare(sScope, Qt::CaseInsensitive) == 0))) append(l, v.name, __enum, "", v.file, v.line, v.scope, "");
      }
      foreach (_type v, types)
      { 
        if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (b || (v.scope.compare(sScope, Qt::CaseInsensitive) == 0))) append(l, v.name, __type, "", v.file, v.line, v.scope, "");
      }
    }
  }

  {
    foreach (_method v, methods)
    { 
      if ((v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope.compare(sScope, Qt::CaseInsensitive) == 0 || v.scope.compare(sBeforeDot, Qt::CaseInsensitive) == 0 || sBeforeDot.isEmpty()))){
        append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", v.file, v.line, v.scope, "");        
      }        
    }
    
  }

  {
    foreach (_constant v, constants)
    { 
      if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope.compare(sScope, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()) || sBeforeDot.isEmpty())) append(l, v.name, __constant, "", v.file, v.line, v.scope, v.scope2);
    }

    foreach (_variable v, variables)
    { 
      if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope.compare(sScope, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()) || sBeforeDot.isEmpty())) append(l, v.name, __variable, v.type_name, v.file, v.line, v.scope, v.scope2);
    }

    foreach (_property2 v, properties)
    { 
      if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && (v.scope.compare(sScope, Qt::CaseInsensitive) == 0 && (v.scope2.compare(sScope2, Qt::CaseInsensitive) == 0 || v.scope2.isEmpty()) || sBeforeDot.isEmpty())) append(l, v.name, __property2, v.type_name, v.file, v.line, v.scope, v.scope2);
    }
  }

  {
    foreach (_enum v, enums)
    { 
      if (v.name.compare(sDot, Qt::CaseInsensitive) == 0/*&& v.scope.compare(sScope, Qt::CaseInsensitive) == 0*/) append(l, v.name, __enum, "", v.file, v.line, v.scope, "");
    }
    
  }

  {
    foreach (_type v, types)
    { 
      if (v.name.compare(sDot, Qt::CaseInsensitive) == 0/* && v.scope.compare(sScope, Qt::CaseInsensitive) == 0*/) append(l, v.name, __type, "", v.file, v.line, v.scope, "");
    }
    
  }

  {
    foreach (_variable v, variables)
    { 
      if ((v.name.compare(sBeforeDot, Qt::CaseInsensitive) == 0/* &&  v.scope.compare(sScope, Qt::CaseInsensitive) == 0*/)){
        QString ss = v.type;

       foreach (_class v, classes)
        { 
          if ((v.name.compare(ss, Qt::CaseInsensitive) == 0)){

            foreach (_constant v, constants)
            { 
              if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && v.scope.compare(ss, Qt::CaseInsensitive) == 0) append(l, v.name, __constant, "", v.file, v.line, v.scope, v.scope2);
            }

            foreach (_variable v, variables)
            { 
              if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && v.scope.compare(ss, Qt::CaseInsensitive) == 0) append(l, v.name, __variable, v.type_name, v.file, v.line, v.scope, v.scope2);
            }

            foreach (_property2 v, properties)
            { 
              if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && v.scope.compare(ss, Qt::CaseInsensitive) == 0) append(l, v.name, __property2, v.type_name, v.file, v.line, v.scope, v.scope2);
            }

            foreach (_method v, methods)
            { 
              if ((v.name.compare(sDot, Qt::CaseInsensitive) == 0 &&  v.scope.compare(ss, Qt::CaseInsensitive) == 0)){
                append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", v.file, v.line, v.scope, "");        
              }        
            }
            
          }
          
        }
   /*    
        foreach (_module v, modules)
        { 
          if ((v.name.compare(ss, Qt::CaseInsensitive) == 0)){

            foreach (_constant v, constants)
            { 
              if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && v.scope.compare(ss, Qt::CaseInsensitive) == 0) append(l, v.name, __constant, v.file, v.line, v.scope, v.scope2);
            }

            foreach (_variable v, variables)
            { 
              if (v.name.compare(sDot, Qt::CaseInsensitive) == 0 && v.scope.compare(ss, Qt::CaseInsensitive) == 0) append(l, v.name, __variable, v.file, v.line, v.scope, v.scope2);
            }

            foreach (_method v, methods)
            { 
              if ((v.name.compare(sDot, Qt::CaseInsensitive) == 0 &&  v.scope.compare(ss, Qt::CaseInsensitive) == 0)){
                append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, v.file, v.line, v.scope, "");        
              }        
            }
            
          }
          
        }
      */
        foreach (_enum v, enums)
        { 
          if (v.name.compare(sDot, Qt::CaseInsensitive) == 0/* && v.scope.compare(sScope, Qt::CaseInsensitive) == 0*/) append(l, v.name, __enum, "", v.file, v.line, v.scope, "");
        }
               
        foreach (_type v, types)
        { 
          if (v.name.compare(sDot, Qt::CaseInsensitive) == 0/* && v.scope.compare(sScope, Qt::CaseInsensitive) == 0*/) append(l, v.name, __type, "", v.file, v.line, v.scope, "");
        }

      }        
    }
    
  }


  return l;
}

QString _inputtip_parser::getForF1(QString sDot, QString sDot2)
{
  framework_parse();

  if (sDot.compare("PARENT", Qt::CaseInsensitive) == 0){
    foreach (_class v, framework_classes)
    { 
      if (v.name.compare(sScope, Qt::CaseInsensitive) == 0){
        sDot = v.type;
        break;
      }
    }
  }    

  {
    foreach (_variable v, variables)
    { 
      if (v.name.compare(sDot, Qt::CaseInsensitive) == 0){
        sDot = v.type;
        break;
      }
    }
  }

  {
    foreach (_variable v, framework_variables)
    { 
      if (v.name.compare(sDot2, Qt::CaseInsensitive) == 0 &&  v.scope.compare(sDot, Qt::CaseInsensitive) == 0){
        return "http://www.kbasic.com/doku.php?id=" + sDot.toLower() + "#" + sDot2.toLower();
      }        
    }
  }

  {
    foreach (_method v, framework_methods)
    { 
      if (v.name.compare(sDot2, Qt::CaseInsensitive) == 0 &&  v.scope.compare(sDot, Qt::CaseInsensitive) == 0){
        return "http://www.kbasic.com/doku.php?id=" + sDot.toLower() + "#" + sDot2.toLower();
      }        
    }
  }

  return "";
}

void _inputtip_parser::framework_parse()
{

  if (framework_classes.count()) return;

  _class c;
  _method m;
  _variable v;

  // *** Control
  c.name = "Control"; c.type = "Object"; c.modifier = _public; framework_classes.append(c);
    
    // Properties
    v.name = "Name"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Layout"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Group"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Background"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "BackgroundStyle"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Palette"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "X"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Y"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Width"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Height"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Left"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Top"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "GlobalX"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "GlobalY"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LocalX"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LocalY"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldX"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldY"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldWidth"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldHeight"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LoadedX"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LoadedY"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LoadedWidth"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LoadedHeight"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MinimumWidth"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MinimumHeight"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MaximumWidth"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MaximumHeight"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Tag"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CSV"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SQL"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ParentForm"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ParentControl"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ControlType"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Focus"; v.type = "Boolean"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FocusPolicy"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FocusProxy"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FocusOrder"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Cursor"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CursorAnimation"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FontName"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FontSize"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FontItalic"; v.type = "Boolean"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FontBold"; v.type = "Boolean"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FontUnderline"; v.type = "Boolean"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FontColor"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Enabled"; v.type = "Boolean"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Visible"; v.type = "Boolean"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "StatusTip"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ToolTip"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SytleSheet"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "WhatsThis"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "TimerInterval"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Opacity"; v.type = "Integer"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ContextMenu"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DrawOnPaint"; v.type = "Boolean"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Mask"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SoundOnEvent"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ShowMode"; v.type = "String"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MouseTracking"; v.type = "Boolean"; v.scope = "Control"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    
    v.name = "SQLName"; v.type = "String"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SQLRelation"; v.type = "String"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "TableViewCaption"; v.type = "String"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "TableViewWidth"; v.type = "Integer"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "TableViewVisible"; v.type = "Boolean"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    
    // Methods
    m.name = "Close"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hide"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Lower"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Raise"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Repaint"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Show"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowFullScreen"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowMaximized"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowMinimized"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowNormal"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowCentered"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsShownFullScreen"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsShownMaximized"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsShownMinimized"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsShownNormal"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFocus"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = ""; m.def = "X As Integer, Y As Integer"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenHidden"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenFullScreen"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenCentered"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenMaximized"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenMinimized"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsOpen"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Move"; m.type = ""; m.def = "X As Integer, Y As Integer"; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "Resize"; m.type = ""; m.def = "Width As Integer, Height As Integer"; m.methodtype = _sub; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "ToggleVisible"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "ClearFocus"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataIds"; m.type = "Strings"; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataSetBoolean"; m.type = ""; m.def = "Id As String, Boolean"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataSetInteger"; m.type = ""; m.def = "Id As String, Integer"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataSetLong"; m.type = ""; m.def = "Id As String, Long"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataSetString"; m.type = ""; m.def = "Id As String, String"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataSetDouble"; m.type = ""; m.def = "Id As String, Double"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataSetDecimal"; m.type = ""; m.def = "Id As String, Decimal"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataSetDateTime"; m.type = ""; m.def = "Id As String, DateTime"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataBoolean"; m.type = "Boolean"; m.def = "Id As String"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataInteger"; m.type = "Integer"; m.def = "Id As String"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataLong"; m.type = "Long"; m.def = "Id As String"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataString"; m.type = "String"; m.def = "Id As String"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataDouble"; m.type = "Double"; m.def = "Id As String"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataDecimal"; m.type = "Decimal"; m.def = "Id As String"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "DataDateTime"; m.type = "DateTime"; m.def = "Id As String"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "SingleShot"; m.type = ""; m.def = "Milliseconds As Integer"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "StartTimer"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "StopTimer"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "GlobalX"; m.type = "Integer"; m.def = "Integer"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "GlobalY"; m.type = "Integer"; m.def = "Integer"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "LocalX"; m.type = "Integer"; m.def = "Integer"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "LocalY"; m.type = "Integer"; m.def = "Integer"; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "UnderMouse"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);

    m.name = "SQLName"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "SQLRelation"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "TableViewCaption"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "TableViewWidth"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "TableViewVisible"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnOpen"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnClose"; m.type = "Control"; m.def = "ByRef Cancel As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnEnter"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnGotFocus"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnLostFocus"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnHide"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnKeyDown"; m.type = "Control"; m.def = "KeyCode As Integer, Shift As Boolean, Control As Boolean, Alt As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnKeyUp"; m.type = "Control"; m.def = "KeyCode As Integer, Shift As Boolean, Control As Boolean, Alt As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnKeyPress"; m.type = "Control"; m.def = "KeyCode As Integer, Shift As Boolean, Control As Boolean, Alt As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnExit"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDblClick"; m.type = "Control"; m.def = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnClick"; m.type = "Control"; m.def = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnMouseMove"; m.type = "Control"; m.def = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnMouseDown"; m.type = "Control"; m.def = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnMouseUp"; m.type = "Control"; m.def = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnMove"; m.type = "Control"; m.def = "X As Integer, Y As Integer, OldX As Integer, OldY As Integer"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnPaint"; m.type = "Control"; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnResize"; m.type = "Control"; m.def = "Width As Integer, Height As Integer, OldWidth As Integer, OldHeight As Integer"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnShow"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnTimer"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnMouseWheel"; m.type = "Control"; m.def = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnMultiPageShow"; m.type = "Control"; m.def = "Page As Integer"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnContextMenu"; m.type = "Control"; m.def = "X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnSingleShot"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnEnabled"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDisabled"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDragEnter"; m.type = "Control"; m.def = "ByRef Cancel As Boolean, X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, Width As Integer, Height As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean, Shift As Boolean, Control As Boolean, Alt As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDragMove"; m.type = "Control"; m.def = "ByRef Cancel As Boolean, X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, Width As Integer, Height As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean, Shift As Boolean, Control As Boolean, Alt As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDragExit"; m.type = "Control"; m.def = ""; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDrop"; m.type = "Control"; m.def = "ByRef Cancel As Boolean, X As Integer, Y As Integer, GlobalX As Integer, GlobalY As Integer, Width As Integer, Height As Integer, LeftButton As Boolean, RightButton As Boolean, MidButton As Boolean, Shift As Boolean, Control As Boolean, Alt As Boolean"; m.methodtype = _event; m.scope = "Control"; m.modifier = _public; framework_methods.append(m);

  // *** Key   
  c.name = "Key"; c.type = ""; c.modifier = _public; framework_classes.append(c);
    
  // Properties
    m.name = "Escape"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Tab"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Backtab"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Backspace"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Return"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Enter"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Insert"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Delete"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Pause"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Print"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "SysReq"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Clear"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Home"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "End"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Left"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Up"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Right"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Down"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "PageUp"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "PageDown"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Shift"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Control"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Meta"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Alt"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "AltGr"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "CapsLock"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "NumLock"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "ScrollLock"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F1"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F2"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F3"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F4"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F5"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F6"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F7"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F8"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F9"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F10"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F11"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F12"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F13"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F14"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F15"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F16"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F17"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F18"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F19"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F20"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F21"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F22"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F23"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F24"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F25"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F26"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F27"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F28"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F29"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F30"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F31"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F32"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F33"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F34"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F35"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Super_L"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Super_R"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Menu"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hyper_L"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hyper_R"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Help"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Direction_L"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Direction_RSpace"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Any"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Exclam"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "QuoteDbl"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "NumberSign"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dollar"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Percent"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Ampersand"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Apostrophe"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "ParenLeft"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "ParenRight"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Asterisk"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "KeyPlus"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Comma"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Minus"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Period"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Slash"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "0"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "1"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "2"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "3"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "4"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "5"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "6"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "7"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "8"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "9"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Colon"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Semicolon"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Less"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Equal"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Greater"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Question"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "At"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "A"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "B"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "C"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "D"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "E"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "F"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "G"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "H"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "I"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "J"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "K"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "L"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "M"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "N"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "O"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "P"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Q"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "R"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "S"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "T"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "U"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "V"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "W"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "X"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Y"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Z"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "BracketLeft"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Backslash"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "BracketRight"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "AsciiCircum"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Underscore"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "QuoteLeft"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "BraceLeft"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Bar"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "BraceRight"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "AsciiTilde"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "nobreakspace"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "exclamdown"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "cent"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "sterling"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "currency"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "yen"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "brokenbar"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "section"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "diaeresis"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "copyright"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "ordfeminine"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "guillemotleft"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "notsign"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "hyphen"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "registered"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "macron"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "degree"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "plusminus"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "twosuperior"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "threesuperior"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "acute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "mu"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "paragraph"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "periodcentered"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "cedilla"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "onesuperior"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "masculine"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "guillemotright"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "onequarter"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "onehalf"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "threequarters"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "questiondown"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Agrave"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Aacute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Acircumflex"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Atilde"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Adiaeresis"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Aring"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "AE"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Ccedilla"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Egrave"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Eacute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Ecircumflex"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Ediaeresis"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Igrave"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Iacute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Icircumflex"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Idiaeresis"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "ETH"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Ntilde"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Ograve"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Oacute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Ocircumflex"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Otilde"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Odiaeresis"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "multiply"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Oobique"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Ugrave"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Uacute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Ucircumflex"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Udiaeresis"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Yacute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "THORN"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "ssharp"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "division"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "ydiaeresis"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Multi_key"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Codeinput"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "SingleCandidate"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "MultipleCandidate"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "PreviousCandidate"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Mode_switch"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Kanji"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Muhenkan"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Henkan"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Romaji"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hiragana"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Katakana"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hiragana_Katakana"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Zenkaku"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hankaku"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Zenkaku_Hankaku"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Touroku"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Massyo"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Kana_Lock"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Kana_Shift"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Eisu_Shift"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Eisu_toggle"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_Start"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_End"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_Hanja"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_Jamo"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_Romaja"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_Jeonja"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_Banja"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_PreHanja"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_PostHanja"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangul_Special"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Grave"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Acute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Circumflex"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Tilde"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Macron"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Breve"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Abovedot"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Diaeresis"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Abovering"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Doubleacute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Caron"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Cedilla"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Ogonek"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Iota"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Voiced_Sound"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Semivoiced_Sound"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Belowdot"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Hook"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Dead_Horn"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Back"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Forward"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Stop"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Refresh"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "VolumeDown"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "VolumeMute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "VolumeUp"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "BassBoost"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "BassUp"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "BassDown"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "TrebleUp"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "TrebleDown"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "MediaPlay"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "MediaStopMediaPrevious"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "MediaNext"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "MediaRecord"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "HomePage"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Favorites"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Search"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Standby"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "OpenUrl"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "LaunchMail"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "LaunchMedia"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch0"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch1"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch2"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch3"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch4"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch5"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch6"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch7"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch8"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Launch9"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "LaunchA"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "LaunchB"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "LaunchC"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "LaunchD"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "LaunchE"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "LaunchF"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "MediaLast"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "unknown"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Call"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Context1"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Context2"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Context3"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Context4"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Flip"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Hangup"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "No"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Select"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Yes"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Execute"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Printer"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Play"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Sleep"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Zoom"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    m.name = "Cancel"; v.type = "Integer"; v.scope = "Key"; v.scope2 = ""; v.modifier = _public;
    
  // *** Form    
  c.name = "Form"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);
    
    // Properties
    v.name = "FormFileName"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FormModified"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "InnerX"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "InnerY"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OuterWidth"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OuterHeight"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Resizable"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ResizableBigger"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ResizableSmaller"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "TableView"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Dock"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DockCaptionVisible"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DockTabify"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DockSplit"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DockWidth"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DockHeight"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "BorderTop"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "BorderBottom"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "BorderLeft"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "BorderRight"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MultiPageHeight"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MultiPageBorderTop"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MultiPageBorderBottom"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MultiPageBorderLeft"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MultiPageBorderRight"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ScrollX"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ScrollY"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ScrollWidth"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ScrollHeight"; v.type = "Integer"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ScrollBar"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MoveOnMouseDrag"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flag"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Caption"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Value"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Modal"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "StopOnClose"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OpenOnRun"; v.type = "Boolean"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "EventSource"; v.type = "Control"; v.scope = "Form"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    v.name = "SQLName"; v.type = "String"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SQLRelation"; v.type = "String"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SQLControls"; v.type = "String"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SQLAddNew"; v.type = "Boolean"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SQLUpdate"; v.type = "Boolean"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SQLDelete"; v.type = "Boolean"; v.scope = "SQL"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    
    // Methods
    m.name = "Hwnd"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);

    m.name = "ControlAppend"; m.type = "Boolean"; m.def = "ControlName As String, ControlType As String, ControlGroup As String, X As Integer, Y As Integer, Width As Integer, Height As Integer, Visible As Boolean"; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "ControlInsert"; m.type = "Boolean"; m.def = "ControlName As String, ControlType As String, ControlGroup As String, X As Integer, Y As Integer, Width As Integer, Height As Integer, Visible As Boolean"; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "ControlRemove"; m.type = "Boolean"; m.def = "ControlName As String"; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "Control"; m.type = "Control"; m.def = "ControlName As String"; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "ControlFocus"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "ControlFocusNext"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "ControlFirst"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "ControlNext"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    //m.name = "Load"; m.type = "Boolean"; m.def = "FormName As String"; m.methodtype = _function; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenPrint"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenPrintDialog"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenPrintPreview"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "MultiPageShow"; m.type = ""; m.def = "Page As Integer"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "MultiPageShowNext"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "MultiPageShowPrevious"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, Boolean"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, String"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, Integer"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, Double"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Tag As String, PropertyName As String, Boolean"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Tag As String, PropertyName As String, String"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Tag As String, PropertyName As String, Integer"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Tag As String, PropertyName As String, Double"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "DockSetFloating"; m.type = ""; m.def = "Boolean"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "DockIsFloating"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "DockTabify"; m.type = ""; m.def = "OnFormName As String"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "DockSplit"; m.type = ""; m.def = "OnFormName As String, Direction As String"; m.methodtype = _sub; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);

    m.name = "First"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Next"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Previous"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Last"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "GoTo"; m.type = "Boolean"; m.def = "Position As Long"; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Update"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Delete"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddNew"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Length"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Position"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDirty"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Run"; m.type = "Boolean"; m.def = "SQLStatement As String"; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Get"; m.type = "AnyType"; m.def = "SearchFor As String, InTableDotField As String, ReturnFieldName As String"; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Get"; m.type = "AnyType"; m.def = "SQLStatement As String"; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "PrimaryKey"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "PrimaryKeyName"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "kbrecordid"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "kbrecordid"; m.type = "Integer"; m.def = "FormView As String"; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Seek"; m.type = "Boolean"; m.def = "Filter As String = \"\", [Filter As String = \"\"]"; m.methodtype = _function; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "Requery"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "ClearFilter"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsFilterActive"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddFilter"; m.type = ""; m.def = "String = \"\""; m.methodtype = _sub; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFilter"; m.type = ""; m.def = "String = \"\""; m.methodtype = _sub; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "SortAscending"; m.type = ""; m.def = "String = \"\""; m.methodtype = _sub; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);
    m.name = "SortDescending"; m.type = ""; m.def = "String = \"\""; m.methodtype = _sub; m.scope = "SQL"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnScroll"; m.type = ""; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);  
    m.name = "OnGoTo"; m.type = "SQL"; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnQuery"; m.type = "SQL"; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnAddNew"; m.type = "SQL"; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDirty"; m.type = "SQL"; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnBeforeInsert"; m.type = "SQL"; m.def = "ByRef Cancel As Boolean"; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnBeforeUpdate"; m.type = "SQL"; m.def = "ByRef Cancel As Boolean"; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnBeforeDelete"; m.type = "SQL"; m.def = "ByRef Cancel As Boolean"; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDockMove"; m.type = ""; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDockShow"; m.type = ""; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDockHide"; m.type = ""; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDockFloating"; m.type = ""; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnDockNotFloating"; m.type = ""; m.def = ""; m.methodtype = _event; m.scope = "Form"; m.modifier = _public; framework_methods.append(m);

  // ***  

  // *** CommandButton    
  c.name = "CommandButton"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "AutoDefault"; v.type = "Boolean"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Default"; v.type = "Boolean"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checkable"; v.type = "Boolean"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checked"; v.type = "Boolean"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "String"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Key"; v.type = "String"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Caption"; v.type = "String"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Value"; v.type = "String"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "CommandButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "CommandButton"; m.modifier = _public; framework_methods.append(m);
  // ***  

  // *** CommandLinkButton    
  c.name = "CommandLinkButton"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "AutoDefault"; v.type = "Boolean"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Default"; v.type = "Boolean"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checkable"; v.type = "Boolean"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checked"; v.type = "Boolean"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "String"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Key"; v.type = "String"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Caption"; v.type = "String"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Value"; v.type = "String"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Description"; v.type = "String"; v.scope = "CommandLinkButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "CommandLinkButton"; m.modifier = _public; framework_methods.append(m);
  // ***  

  // *** ToolButton    
  c.name = "ToolButton"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Checkable"; v.type = "Boolean"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checked"; v.type = "Boolean"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "String"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Key"; v.type = "String"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Caption"; v.type = "String"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Value"; v.type = "String"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "ToolButton"; m.modifier = _public; framework_methods.append(m);
  // ***  

  // *** ImageButton     
  c.name = "ImageButton"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

  // Properties
    v.name = "Checkable"; v.type = "Boolean"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checked"; v.type = "Boolean"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Key"; v.type = "String"; v.scope = "ToolButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "EnabledImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DisabledImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "EnterImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ExitImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MouseDownImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MouseUpImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "EnterSound"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ExitSound"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MouseDownSound"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MouseUpSound"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CheckedEnabledImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CheckedDisabledImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CheckedEnterImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CheckedExitImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CheckedMouseDownImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CheckedMouseUpImage"; v.type = "String"; v.scope = "ImageButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "ImageButton"; m.modifier = _public; framework_methods.append(m);


  // *** Label    
  c.name = "Label"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Shape"; v.type = "Boolean"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OpenLinks"; v.type = "Boolean"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "WordWrap"; v.type = "Boolean"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Scale"; v.type = "Boolean"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Alignment"; v.type = "String"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Feature"; v.type = "String"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "InputControl"; v.type = "String"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "String"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Caption"; v.type = "String"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);    
    v.name = "Value"; v.type = "Boolean"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "Boolean"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "Label"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

  // *** CheckBox    
  c.name = "CheckBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "Boolean"; v.scope = "CheckBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "Boolean"; v.scope = "CheckBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Key"; v.type = "String"; v.scope = "CheckBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "String"; v.scope = "CheckBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Caption"; v.type = "String"; v.scope = "CheckBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "CheckBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    
    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "CheckBox"; m.modifier = _public; framework_methods.append(m);

  // *** RadioButton    
  c.name = "RadioButton"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "Boolean"; v.scope = "RadioButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "Boolean"; v.scope = "RadioButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Key"; v.type = "String"; v.scope = "RadioButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "String"; v.scope = "RadioButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Caption"; v.type = "String"; v.scope = "RadioButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "RadioButton"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    
    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "RadioButton"; m.modifier = _public; framework_methods.append(m);

  // *** TextBox     
  c.name = "TextBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Alignment"; v.type = "String"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "EchoMode"; v.type = "String"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Value"; v.type = "String"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "InputMask"; v.type = "String"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ReadOnly"; v.type = "Boolean"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ValidatorDouble"; v.type = "Boolean"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ValidatorInteger"; v.type = "Boolean"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "Integer"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Completer"; v.type = "String"; v.scope = "TextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "IsValid"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "TextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SelectAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "TextBox"; m.modifier = _public; framework_methods.append(m);
    
    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "TextBox"; m.modifier = _public; framework_methods.append(m);

  // *** Frame     
  c.name = "Frame"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Caption"; v.type = "String"; v.scope = "Frame"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Value"; v.type = "String"; v.scope = "Frame"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "Frame"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "Frame"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

  // *** ComboBox     
  c.name = "ComboBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "ComboBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "ComboBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "ComboBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DoubleEntry"; v.type = "Boolean"; v.scope = "ComboBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "InsertPolicy"; v.type = "String"; v.scope = "ComboBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Editable"; v.type = "Boolean"; v.scope = "ComboBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "Integer"; v.scope = "ComboBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MaximumVisible"; v.type = "Integer"; v.scope = "ComboBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "ComboBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "Length"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Find"; m.type = "Integer"; m.def = "Caption As String"; m.methodtype = _function; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "HidePopUp"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowPopUp"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "Index As Integer, Caption As String"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "Index As Integer, Icon As String, Caption As String"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "Caption As String"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "Icon As String, Caption As String"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Select"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Select"; m.type = ""; m.def = "Caption As String"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Selected"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Caption"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Index"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Data"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Caption"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCaption"; m.type = ""; m.def = "Index As Integer, Caption As String"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetIcon"; m.type = ""; m.def = "Index As Integer, Icon As String"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Tag"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetTag"; m.type = ""; m.def = "Index As Integer, Tag As String"; m.methodtype = _sub; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);
    
    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = "Index As Integer, Caption As String"; m.methodtype = _event; m.scope = "ComboBox"; m.modifier = _public; framework_methods.append(m);

  // *** ListBox     
  c.name = "ListBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "ListBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "ListBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "ListBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Sorted"; v.type = "Boolean"; v.scope = "ListBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SelectionMode"; v.type = "String"; v.scope = "ListBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "AlternatingRowColors"; v.type = "Boolean"; v.scope = "ListBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "ListBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "Length"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Sort"; m.type = ""; m.def = "Descending As Boolean"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "Index As Integer, Caption As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "Index As Integer, Icon As String, Caption As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "Caption As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "Icon As String, Caption As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Select"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Select"; m.type = ""; m.def = "Caption As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);   
    m.name = "Selected"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Caption"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Index"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Data"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Caption"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCaption"; m.type = ""; m.def = "Index As Integer, Caption As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetIcon"; m.type = ""; m.def = "Index As Integer, Icon As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Tag"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetTag"; m.type = ""; m.def = "Index As Integer, Tag As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "CheckState"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCheckState"; m.type = ""; m.def = "Index As Integer, CheckState As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Flag"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFlag"; m.type = ""; m.def = "Index As Integer, Flag As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBackground"; m.type = ""; m.def = "Index As Integer, ColorId As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBackground"; m.type = ""; m.def = "Index As Integer, ColorId As String, BrushStyle As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsHidden"; m.type = "Boolean"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetHidden"; m.type = ""; m.def = "Index As Integer, IsHidden As Boolean"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsSelected"; m.type = "Boolean"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetSelected"; m.type = ""; m.def = "Index As Integer, IsSelected As Boolean"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "StatusTip"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetStatusTip"; m.type = ""; m.def = "Index As Integer, StatusTip As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "ToolTip"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetToolTip"; m.type = ""; m.def = "Index As Integer, ToolTip As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "TextAlignment"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetTextAlignment"; m.type = ""; m.def = "Index As Integer, TextAlignment As String"; m.methodtype = _sub; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = "Index As Integer, Caption As String"; m.methodtype = _event; m.scope = "ListBox"; m.modifier = _public; framework_methods.append(m);

  // *** DateBox     
  c.name = "DateBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "DateBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "DateBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "DateBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "String"; v.scope = "DateBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minimum"; v.type = "String"; v.scope = "DateBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Format"; v.type = "String"; v.scope = "DateBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "PopUp"; v.type = "Boolean"; v.scope = "DateBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "DateBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "SetDateTime"; m.type = ""; m.def = "DateTime"; m.methodtype = _sub; m.scope = "DateBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTime"; m.type = "DateTime"; m.def = ""; m.methodtype = _function; m.scope = "DateBox"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "DateBox"; m.modifier = _public; framework_methods.append(m);

  // *** TimeBox     
  c.name = "TimeBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "TimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "TimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "TimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "String"; v.scope = "TimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minimum"; v.type = "String"; v.scope = "TimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Format"; v.type = "String"; v.scope = "TimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "PopUp"; v.type = "Boolean"; v.scope = "TimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "TimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "SetDateTime"; m.type = ""; m.def = "DateTime"; m.methodtype = _sub; m.scope = "TimeBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTime"; m.type = "DateTime"; m.def = ""; m.methodtype = _function; m.scope = "TimeBox"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "TimeBox"; m.modifier = _public; framework_methods.append(m);

  // *** DateTimeBox      
  c.name = "DateTimeBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "DateTimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "DateTimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "DateTimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "String"; v.scope = "DateTimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minimum"; v.type = "String"; v.scope = "DateTimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Format"; v.type = "String"; v.scope = "DateTimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "PopUp"; v.type = "Boolean"; v.scope = "DateTimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "DateTimeBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "SetDateTime"; m.type = ""; m.def = "dt As DateTime"; m.methodtype = _sub; m.scope = "DateTimeBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTime"; m.type = "DateTime"; m.def = ""; m.methodtype = _function; m.scope = "DateTimeBox"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "DateTimeBox"; m.modifier = _public; framework_methods.append(m);
 
  // *** ScrollBar      
  c.name = "ScrollBar"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "Integer"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "Integer"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minimum"; v.type = "Integer"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "Integer"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Orientation"; v.type = "String"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "InvertedAppearance"; v.type = "Boolean"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "InvertedControls"; v.type = "Boolean"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Tracking"; v.type = "Boolean"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "PageStep"; v.type = "Integer"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SingleStep"; v.type = "Integer"; v.scope = "ScrollBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "ScrollBar"; m.modifier = _public; framework_methods.append(m);
 
  // *** Slider      
  c.name = "Slider"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "Integer"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "Integer"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minimum"; v.type = "Integer"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "Integer"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Orientation"; v.type = "String"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "TickPosition"; v.type = "String"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "InvertedAppearance"; v.type = "Boolean"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "InvertedControls"; v.type = "Boolean"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Tracking"; v.type = "Boolean"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "TickInterval"; v.type = "Integer"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "PageStep"; v.type = "Integer"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SingleStep"; v.type = "Integer"; v.scope = "Slider"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "Slider"; m.modifier = _public; framework_methods.append(m);
 
  // *** SpinBox      
  c.name = "SpinBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "CleanText"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "SpinBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Text"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "SpinBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Clear"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "SpinBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SelectAll"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "SpinBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "StepDown"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "SpinBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "StepUp"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "SpinBox"; m.modifier = _public; framework_methods.append(m);
    
    // Properties
    v.name = "Value"; v.type = "Integer"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "Integer"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minimum"; v.type = "Integer"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "Integer"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Tracking"; v.type = "Boolean"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SingleStep"; v.type = "Integer"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Alignment"; v.type = "String"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ReadOnly"; v.type = "Boolean"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Prefix"; v.type = "String"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Suffix"; v.type = "String"; v.scope = "SpinBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "SpinBox"; m.modifier = _public; framework_methods.append(m);
 
  // CONTROL

  // *** FormsView      
  c.name = "FormsView"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);
    
    // Properties
    v.name = "SelectionMode"; v.type = "String"; v.scope = "FormsView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    
    // Methods
    m.name = "SelectAll"; m.type = ""; m.def = "YesNo As Boolean = True"; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Select"; m.type = ""; m.def = "Index As Integer, YesNo As Boolean = True"; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsSelected"; m.type = "Boolean"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Length"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveAll"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "Index As Integer, Form"; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "Form"; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetForm"; m.type = ""; m.def = "Index As Integer, Form"; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Form"; m.type = "Form"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ScrollTo"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "FormsView"; m.modifier = _public; framework_methods.append(m);

  // *** ToolBarView      
  c.name = "ToolBarView"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);
    
    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "ToolBarView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    
    // Methods
    m.name = "InsertControl"; m.type = ""; m.def = "Index As Integer, Control"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ToolBarItem"; m.type = "ToolBarItem"; m.def = "ToolBarItemName As String"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetEnabled"; m.type = ""; m.def = "ToolBarItemName As String, Boolean"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetVisible"; m.type = ""; m.def = "ToolBarItemName As String, Boolean"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, Boolean"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, Integer"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, String"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Group As String, PropertyName As String, Boolean"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Group As String, PropertyName As String, Integer"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Group As String, PropertyName As String, String"; m.methodtype = _function; m.scope = "ToolBarView"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = "ToolBarItemName As String"; m.methodtype = _event; m.scope = "DateTimeBox"; m.modifier = _public; framework_methods.append(m);
 

  // *** Timer      
  c.name = "Timer"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Interval"; v.type = "Integer"; v.scope = "Timer"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Enabled"; v.type = "Boolean"; v.scope = "Timer"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "EventOnOpen"; v.type = "Boolean"; v.scope = "Timer"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "IsRunning"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Timer"; m.modifier = _public; framework_methods.append(m);
    m.name = "Start"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Timer"; m.modifier = _public; framework_methods.append(m);
    m.name = "Stop"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Timer"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "Timer"; m.modifier = _public; framework_methods.append(m);

  // *** Sound      
  c.name = "Sound"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);
    
    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "Sound"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "Sound"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Muted"; v.type = "Boolean"; v.scope = "Sound"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Enabled"; v.type = "Boolean"; v.scope = "Sound"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "State"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "ErrorType"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "ErrorString"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentTime"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "TotalTime"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsPlaying"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsPaused"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsMuted"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsSeekable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "Play"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "Play"; m.type = ""; m.def = "String"; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "Load"; m.type = ""; m.def = "String"; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "Pause"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "Stop"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "Seek"; m.type = ""; m.def = "Long"; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnStateChanged"; m.type = "Event"; m.def = "NewState As String, OldState As String"; m.methodtype = _event; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnAboutToFinish"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnFinished"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnFinished"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);

  // *** Movie      
  c.name = "MovieBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);
    
    // Properties
    v.name = "ScaleMode"; v.type = "String"; v.scope = "MovieBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "AspectRatio"; v.type = "String"; v.scope = "MovieBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    v.name = "Value"; v.type = "String"; v.scope = "MovieBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "MovieBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Muted"; v.type = "Boolean"; v.scope = "MovieBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Enabled"; v.type = "Boolean"; v.scope = "MovieBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "State"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "ErrorType"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "ErrorString"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentTime"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "TotalTime"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsPlaying"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsPaused"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsMuted"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsSeekable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Play"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Play"; m.type = ""; m.def = "String"; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Load"; m.type = ""; m.def = "String"; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Pause"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Stop"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Seek"; m.type = ""; m.def = "Long"; m.methodtype = _function; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnStateChanged"; m.type = "Event"; m.def = "NewState As String, OldState As String"; m.methodtype = _event; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnAboutToFinish"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnFinished"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnFinished"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "MovieBox"; m.modifier = _public; framework_methods.append(m);

  // *** TabView      
  c.name = "TabView"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Select"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _sub; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Selected"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetTabEnabled"; m.type = ""; m.def = "Index As Integer, Enable As Boolean"; m.methodtype = _sub; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsTabEnabled"; m.type = "Boolean"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetToolTip"; m.type = ""; m.def = "Index As Integer, ToolTip As String"; m.methodtype = _sub; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "WhatsThis"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWhatsThis"; m.type = ""; m.def = "Index As Integer, ToolTip As String"; m.methodtype = _sub; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ToolTip"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCaption"; m.type = ""; m.def = "Index As Integer, Caption As String"; m.methodtype = _sub; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Caption"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetIcon"; m.type = ""; m.def = "Index As Integer, Icon As String"; m.methodtype = _sub; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);

    m.name = "Append"; m.type = "Integer"; m.def = "Icon As String, Caption As String"; m.methodtype = _function; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = "Integer"; m.def = "Index As Integer, Icon As String, Caption As String"; m.methodtype = _function; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _sub; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Length"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = "Index As Integer"; m.methodtype = _event; m.scope = "TabView"; m.modifier = _public; framework_methods.append(m);

  // *** ImageBox     
  c.name = "ImageBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "ImageBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "ImageBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "ImageBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

  // *** TreeView      
  c.name = "TreeView"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "SelectionMode"; v.type = "String"; v.scope = "TreeView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "AlternatingRowColors"; v.type = "Boolean"; v.scope = "TreeView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "RootIsDecorated"; v.type = "Boolean"; v.scope = "TreeView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "TreeView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "AppendChild"; m.type = "Integer"; m.def = "Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "AppendChild"; m.type = "Integer"; m.def = "Icon As String, Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "AppendChild"; m.type = "Integer"; m.def = "Id As Integer, Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "AppendChild"; m.type = "Integer"; m.def = "Id As Integer, Icon As String, Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ChildCount"; m.type = "Integer"; m.def = "Id As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Child"; m.type = "Integer"; m.def = "Id As Integer, Index As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Tag"; m.type = "String"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetTag"; m.type = ""; m.def = "Id As Integer, Column As Integer, Tag As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "CheckState"; m.type = "String"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCheckState"; m.type = ""; m.def = "Id As Integer, Column As Integer, CheckState As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Data"; m.type = "String"; m.def = "Id As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Flag"; m.type = "String"; m.def = "Id As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFlag"; m.type = ""; m.def = "Id As Integer, Flag As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBackground"; m.type = ""; m.def = "Id As Integer, Column As Integer, Color As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBackground"; m.type = ""; m.def = "Id As Integer, Column As Integer, Color As String, BrushStyle As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFontColor"; m.type = ""; m.def = "Id As Integer, Column As Integer, Color As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFontColor"; m.type = ""; m.def = "Id As Integer, Column As Integer, Color As String, BrushStyle As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFont"; m.type = ""; m.def = "Id As Integer, Column As Integer, Font As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Caption"; m.type = "String"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCaption"; m.type = ""; m.def = "Id As Integer, Column As Integer, Caption As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetIcon"; m.type = ""; m.def = "Id As Integer, Column As Integer, Icon As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);    
    m.name = "IndexOfChild"; m.type = "Integer"; m.def = "Id As Integer, ChildId As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "InsertChild"; m.type = "Integer"; m.def = "Id As Integer, Index As Integer, Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "InsertChild"; m.type = "Integer"; m.def = "Id As Integer, Index As Integer, Icon As String, Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsExpanded"; m.type = "Boolean"; m.def = "Id As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetExpanded"; m.type = ""; m.def = "Id As Integer, IsExpanded As Boolean"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsHidden"; m.type = "Boolean"; m.def = "Id As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetHidden"; m.type = ""; m.def = "Id As Integer, IsHidden As Boolean"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsSelected"; m.type = "Boolean"; m.def = "Id As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetSelected"; m.type = ""; m.def = "Id As Integer, IsSelected As Boolean"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "StatusTip"; m.type = "String"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetStatusTip"; m.type = ""; m.def = "Id As Integer, Column As Integer, StatusTip As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ToolTip"; m.type = "String"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetToolTip"; m.type = ""; m.def = "Id As Integer, Column As Integer, ToolTip As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveChild"; m.type = ""; m.def = "Id As Integer, Index As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "TextAlignment"; m.type = "String"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetTextAlignment"; m.type = ""; m.def = "Id As Integer, Column As Integer, TextAlignment As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ClosePersistentEditor"; m.type = ""; m.def = "Id As Integer, Column As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ColumnCount"; m.type = "Integer"; m.def = "Id As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentColumn"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentItem"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "FindItem"; m.type = "Integer"; m.def = "Caption As String, Flag As String, Column As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "HeaderItem"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IndexOfTopLevelItem"; m.type = "Integer"; m.def = "Id As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = "Integer"; m.def = "Index As Integer, Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = "Integer"; m.def = "Index As Integer, Icon As String, Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "InvisibleRootItem"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ItemAt"; m.type = "Integer"; m.def = "X As Integer, Y As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenPersistentEditor"; m.type = ""; m.def = "Id As Integer, Column As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "FirstSelectedItem"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "NextSelectedItem"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetColumnCount"; m.type = ""; m.def = "Count As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCurrentItem"; m.type = ""; m.def = "Id As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCurrentItem"; m.type = ""; m.def = "Id As Integer, Column As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetHeaderLabel"; m.type = ""; m.def = "Caption As String"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetHeaderLabel"; m.type = ""; m.def = "Caption As String, Column As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SortColumn"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SortItems"; m.type = ""; m.def = "Column As Integer, Descending As Boolean"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveTopLevelItem"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "TopLevelItem"; m.type = "Integer"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "TopLevelItemCount"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsColumnHidden"; m.type = "Boolean"; m.def = "Column As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetColumnHidden"; m.type = ""; m.def = "Column As Integer, IsColumnHidden As Boolean"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsSortingEnabled"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetSortingEnabled"; m.type = ""; m.def = "IsSortingEnabled As Boolean"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsItemsExpandable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetItemsExpandable"; m.type = ""; m.def = "IsItemsExpandable As Boolean"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsAllColumnsShowFocus"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetAllColumnsShowFocus"; m.type = ""; m.def = "IsAllColumnsShowFocus As Boolean"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ColumnWidth"; m.type = "Integer"; m.def = "Column As Integer"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetColumnWidth"; m.type = ""; m.def = "Column As Integer, Width As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "CollapseAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ExpandAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "SelectAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowColumn"; m.type = ""; m.def = "Column As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "CollapseItem"; m.type = ""; m.def = "Id As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ExpandItem"; m.type = ""; m.def = "Id As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ScrollToItem"; m.type = ""; m.def = "Id As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ScrollToBottom"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ScrollToTop"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = "Integer"; m.def = "Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = "Integer"; m.def = "Icon As String, Caption As String"; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);  
    m.name = "ColumnCount"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "EditItem"; m.type = ""; m.def = "Id As Integer, Column As Integer"; m.methodtype = _sub; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnCurrentItemChanged"; m.type = "Event"; m.def = "IdCurrent As Integer, IdPrevious As Integer"; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnItemActivated"; m.type = "Event"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnItemChanged"; m.type = "Event"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnItemClicked"; m.type = "Event"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnItemCollapsed"; m.type = "Event"; m.def = "Id As Integer"; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnItemDoubleClicked"; m.type = "Event"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnItemEntered"; m.type = "Event"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnItemExpanded"; m.type = "Event"; m.def = "Id As Integer"; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnItemPressed"; m.type = "Event"; m.def = "Id As Integer, Column As Integer"; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnItemSelectionChanged"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "TreeView"; m.modifier = _public; framework_methods.append(m);

  // *** ResizeBox      
  c.name = "ResizeBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

  // *** SvgBox      
  c.name = "SvgBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "SvgBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "SvgBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "SvgBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

  // *** Box      
  c.name = "Box"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

  // *** ProgressBar      
  c.name = "ProgressBar"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "Integer"; v.scope = "ProgressBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "Integer"; v.scope = "ProgressBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minimum"; v.type = "Integer"; v.scope = "ProgressBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "Integer"; v.scope = "ProgressBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Format"; v.type = "String"; v.scope = "ProgressBar"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

  // *** RichTextBox      
  c.name = "RichTextBox"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ReadOnly"; v.type = "Boolean"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "WordWrap"; v.type = "Boolean"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Alignment"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "AcceptRichText"; v.type = "Boolean"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Comment1Begin"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Comment1End"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Comment2Begin"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Keywords"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Commands"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CommentColor"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "KeywordColor"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CommandColor"; v.type = "String"; v.scope = "RichTextBox"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "Html"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsModified"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetModified"; m.type = ""; m.def = "Boolean"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFontColor"; m.type = ""; m.def = "ColorId As String"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetFontColor"; m.type = ""; m.def = "ColorObject As Color"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);

    m.name = "SetFontPointSize"; m.type = ""; m.def = "FontPointSize As Double"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFontFamily"; m.type = ""; m.def = "FontFamily As String"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFontBold"; m.type = ""; m.def = "IsFontBold As Boolean"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFontItalic"; m.type = ""; m.def = "IsFontItalic As Boolean"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFontUnderline"; m.type = ""; m.def = "IsFontUnderline As Boolean"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Line"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Column"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Selected"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Undo"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Redo"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetTabChangesFocus"; m.type = ""; m.def = "IsTabChangesFocus As Boolean"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Copy"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Paste"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Cut"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SelectAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "InsertHtml"; m.type = ""; m.def = "Text As String"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "InsertPlainText"; m.type = ""; m.def = "Text As String"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "Text As String"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetHtml"; m.type = ""; m.def = "Text As String"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetPlainText"; m.type = ""; m.def = "Text As String"; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "PlainText"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnCursorPositionChanged"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnAction"; m.type = "Event"; m.def = "CopyAvailable As Boolean, PasteAvailable As Boolean, UndoAvailable As Boolean, RedoAvailable As Boolean"; m.methodtype = _event; m.scope = "RichTextBox"; m.modifier = _public; framework_methods.append(m);

  // *** WebView      
  c.name = "WebView"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "WebView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "WebView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "WebView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "HomeURL"; v.type = "String"; v.scope = "WebView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Keys"; v.type = "Strings"; v.scope = "WebView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Values"; v.type = "Strings"; v.scope = "WebView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "BackwardAvailable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ForwardAvailable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Backward"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Forward"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Reload"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = "BackwardAvailable As Boolean, ForwardAvailable As Boolean, NewURL As String"; m.methodtype = _event; m.scope = "Web"; m.modifier = _public; framework_methods.append(m);

    m.name = "OnPage"; m.type = "Event"; m.def = "NewPage As String"; m.methodtype = _event; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnLinkHovered"; m.type = "Event"; m.def = "Link As String, Title As String, TextContent As String"; m.methodtype = _event; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnLoadFinished"; m.type = "Event"; m.def = "Ok As Boolean"; m.methodtype = _event; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnLoadProgress"; m.type = "Event"; m.def = "Progress As Integer"; m.methodtype = _event; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnLoadStarted"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnWindowCloseRequested"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "WebView"; m.modifier = _public; framework_methods.append(m);

  // *** HtmlView      
  c.name = "HtmlView"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "HtmlView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "HtmlView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "HtmlView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "HomeURL"; v.type = "String"; v.scope = "HtmlView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OpenLinks"; v.type = "Boolean"; v.scope = "HtmlView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flat"; v.type = "Boolean"; v.scope = "HtmlView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "BackwardAvailable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "HtmlView"; m.modifier = _public; framework_methods.append(m);
    m.name = "ForwardAvailable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "HtmlView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Backward"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "HtmlView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Forward"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "HtmlView"; m.modifier = _public; framework_methods.append(m);
    m.name = "Reload"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "HtmlView"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = "BackwardAvailable As Boolean, ForwardAvailable As Boolean, NewURL As String"; m.methodtype = _event; m.scope = "HtmlView"; m.modifier = _public; framework_methods.append(m);

  // *** MenuBarItem      
  c.name = "MenuBarItem"; c.type = "Object"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Name"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ControlType"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Caption"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Tag"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Separator"; v.type = "Boolean"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Enabled"; v.type = "Boolean"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checked"; v.type = "Boolean"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Key"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "StatusTip"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Group"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Visible"; v.type = "Boolean"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checkable"; v.type = "Boolean"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Data"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MenuBarRole"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ActionId"; v.type = "String"; v.scope = "MenuBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "MenuBarItem"; m.modifier = _public; framework_methods.append(m);

  // *** ToolBarItem      
  c.name = "ToolBarItem"; c.type = "Object"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Name"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ControlType"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Tag"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Separator"; v.type = "Boolean"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Enabled"; v.type = "Boolean"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ToolTip"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "StatusTip"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "WhatsThis"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);    
    v.name = "Caption"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Text"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Group"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checkable"; v.type = "Boolean"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Checked"; v.type = "Boolean"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ToolBarRole"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ContextMenu"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ArrowType"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "PopupMode"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ActionId"; v.type = "String"; v.scope = "ToolBarItem"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "ToolBarItem"; m.modifier = _public; framework_methods.append(m);

  // *** Report      
  c.name = "Report"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    m.name = "OpenPrintDialog"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Report"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenPrintPreview"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Report"; m.modifier = _public; framework_methods.append(m);
    
    /*
  // *** Header      
  c.name = "Header"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "Header"; m.modifier = _public; framework_methods.append(m);

  // *** Footer      
  c.name = "Footer"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "Footer"; m.modifier = _public; framework_methods.append(m);
*/

  // *** UdpSocket      
  c.name = "UdpSocket"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Open"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "UdpSocket"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "UdpSocket"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadData"; m.type = ""; m.def = "ByRef AnyType"; m.methodtype = _function; m.scope = "UdpSocket"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteData"; m.type = ""; m.def = "AnyType"; m.methodtype = _function; m.scope = "UdpSocket"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastError"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "UdpSocket"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastErrorText"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "UdpSocket"; m.modifier = _public; framework_methods.append(m);

    // Properties
    v.name = "Name"; v.type = "String"; v.scope = "UdpSocket"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ControlType"; v.type = "String"; v.scope = "UdpSocket"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Host"; v.type = "String"; v.scope = "UdpSocket"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Port"; v.type = "String"; v.scope = "UdpSocket"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "UdpSocket"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnOpen"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "UdpSocket"; m.modifier = _public; framework_methods.append(m);
    m.name = "OnClose"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "UdpSocket"; m.modifier = _public; framework_methods.append(m);
  
  // *** SerialPort      
  c.name = "SerialPort"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Open"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsOpen"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsReadable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsWritable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "Flush"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "BytesAvailable"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadData"; m.type = ""; m.def = "ByRef AnyType"; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteData"; m.type = ""; m.def = "AnyType"; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadLine"; m.type = ""; m.def = "ByRef String"; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteLine"; m.type = ""; m.def = "String"; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "BytesRead"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "BytesWritten"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetDtr"; m.type = ""; m.def = "Boolean"; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetRts"; m.type = ""; m.def = "Boolean"; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "AtEnd"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsCTS"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDSR"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDCD"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsRI"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "LineStatus"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastError"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastErrorText"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);

    // Properties
    v.name = "Name"; v.type = "String"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ControlType"; v.type = "String"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "PortName"; v.type = "String"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "BaudRate"; v.type = "String"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DataBits"; v.type = "String"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FlowControl"; v.type = "String"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Parity"; v.type = "String"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "StopBits"; v.type = "String"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "TimeOutMillisec"; v.type = "Integer"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "PollingInterval"; v.type = "Integer"; v.scope = "SerialPort"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "SerialPort"; m.modifier = _public; framework_methods.append(m);
  
  // *** FormView      
  c.name = "FormView"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Value"; v.type = "String"; v.scope = "FormView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "OldValue"; v.type = "String"; v.scope = "FormView"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "Form"; m.type = "Form"; m.def = ""; m.methodtype = _function; m.scope = "FormView"; m.modifier = _public; framework_methods.append(m);

  // *** Line      
  c.name = "Line"; c.type = "Control"; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Flat"; v.type = "Boolean"; v.scope = "Line"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Flip"; v.type = "Boolean"; v.scope = "Line"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Orientation"; v.type = "String"; v.scope = "Line"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Constants
    v.name = "Vertical"; v.type = "String"; v.scope = "Line"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Horizontal"; v.type = "String"; v.scope = "Line"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

  // *** String      
  c.name = "String"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Len"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "InStr"; m.type = "Integer"; m.def = "[Start As Integer ,] Sub As String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "InStRev"; m.type = "Integer"; m.def = "[Start As Integer ,] Sub As String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Val"; m.type = "Double"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Asc"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Left"; m.type = "String"; m.def = "howMany As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Right"; m.type = "String"; m.def = "howMany As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "LCase"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "UCase"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Trim"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "RTrim"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "LTrim"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Mid"; m.type = "String"; m.def = "Start As Integer [, Length As Integer]"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "StrComp"; m.type = "Integer"; m.def = "With As String [, CompareMode As Integer]"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Replace"; m.type = "String"; m.def = "Pattern As String, Replace As String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "StrReverse"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Split"; m.type = "Strings"; m.def = "Separator As String, KeepEmptyParts As Boolean, CaseSensitive As Boolean"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Peek"; m.type = ""; m.def = "UDF, Length As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Poke"; m.type = ""; m.def = "UDF, Length As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);

    m.name = "Length"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "IndexOf"; m.type = "Integer"; m.def = "Sub As String, Start As Integer = 1, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastIndexOf"; m.type = "Integer"; m.def = "Sub As String, Start As Integer = -1, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Value"; m.type = "Double"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Lower"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Upper"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Compare"; m.type = "Integer"; m.def = "String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Contains"; m.type = "Boolean"; m.def = "String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Count"; m.type = "Integer"; m.def = "String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "EndsWith"; m.type = "Boolean"; m.def = "String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "StartsWith"; m.type = "Boolean"; m.def = "String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Fill"; m.type = ""; m.def = "String, Length As Integer = -1"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "String, Position As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "LeftJustified"; m.type = "String"; m.def = "Width As Integer, Fill As String = " ", Truncate As Boolean = False"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Prepend"; m.type = ""; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "Position As Integer, Length As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "RightJustified"; m.type = "String"; m.def = "Width As Integer, Fill As String = " ", Truncate As Boolean = False"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Section"; m.type = "String"; m.def = "Separator As String, Start As Integer, End As Integer = -1, SectionFlags = \"SectionDefault\""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Simplified"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Trimmed"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Truncate"; m.type = ""; m.def = "Position As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Unicode"; m.type = "Integer"; m.def = "Position As Integer = 1"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Reversed"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadBinary"; m.type = "AnyType"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, AnyType"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "SeekBinary"; m.type = "Integer"; m.def = "Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Encode"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Decode"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
  
  // *** Strings      
  c.name = "Strings"; c.type = "Object"; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Length"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "Join"; m.type = "String"; m.def = "Separator As String"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetString"; m.type = ""; m.def = "Index As Integer, String"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "String"; m.type = "String"; m.def = "Index As Integer"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "Sort"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "Index As Integer"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "Prepend"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "Index As Integer, String"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "Replace"; m.type = ""; m.def = "Index As Integer, String"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "Contains"; m.type = "Boolean"; m.def = "String, CaseSensitive As Boolean = True"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "IndexOf"; m.type = "Integer"; m.def = "String, Position As Integer = 1"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastIndexOf"; m.type = "Integer"; m.def = "String, Position As Integer = -1"; m.methodtype = _sub; m.scope = "Strings"; m.modifier = _public; framework_methods.append(m);

  // *** Dictionary      
  c.name = "Dictionary"; c.type = "Object"; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Length"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "Key As String, Value As String"; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetString"; m.type = ""; m.def = "Key As String, Value As String"; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "String"; m.type = ""; m.def = "Key As String"; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveAll"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "Key As String"; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "Key As String, Value As String"; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "Replace"; m.type = ""; m.def = "Key As String, Value As String"; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "Contains"; m.type = ""; m.def = "Key As String"; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "Keys"; m.type = "Strings"; m.def = ""; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "Values"; m.type = "Strings"; m.def = ""; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "Key"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);
    m.name = "Value"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Dictionary"; m.modifier = _public; framework_methods.append(m);

  // *** Array      
  c.name = "Array"; c.type = "Object"; c.modifier = _public; framework_classes.append(c);

  // *** Bits      
  c.name = "Bits"; c.type = "Object"; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "SetBit"; m.type = ""; m.def = "Integer, Boolean"; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);
    m.name = "Bit"; m.type = "Boolean"; m.def = "Integer"; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);
    m.name = "TestBit"; m.type = "Boolean"; m.def = "Integer"; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);
    m.name = "ToggleBit"; m.type = ""; m.def = "Integer"; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetByte"; m.type = ""; m.def = "Byte"; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetShort"; m.type = ""; m.def = "Short"; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetInteger"; m.type = ""; m.def = "Integer"; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);
    m.name = "Byte"; m.type = "Byte"; m.def = ""; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);
    m.name = "Short"; m.type = "Short"; m.def = ""; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);
    m.name = "Integer"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Bits"; m.modifier = _public; framework_methods.append(m);

  // *** DateTime      
  c.name = "DateTime"; c.type = "Object"; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "AddDays"; m.type = ""; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddHours"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddMinutes"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddMonths"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddSeconds"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddYears"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Day"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayOfWeek"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayOfYear"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DaysInMonth"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DaysInYear"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DiffDays"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DiffSeconds"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hour"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsLeapYear"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Minute"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Month"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Second"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubDays"; m.type = "DateTime"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubHours"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubMinutes"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubMonths"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubSeconds"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubYears"; m.type = "DateTime"; m.def = "Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "WeekNumber"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Year"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);

  // *** My      
  c.name = "My"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Abs"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddDays"; m.type = "DateTime"; m.def = "DateTime, Days As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddHours"; m.type = "DateTime"; m.def = "DateTime, Hours As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddMinutes"; m.type = "DateTime"; m.def = "DateTime, Minutes As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddMonths"; m.type = "DateTime"; m.def = "DateTime, Months As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddSeconds"; m.type = "DateTime"; m.def = "DateTime, Seconds As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddYears"; m.type = "DateTime"; m.def = "DateTime, Years As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Append"; m.type = ""; m.def = "String, String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Asc"; m.type = "Integer"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Boolean"; m.type = "Boolean"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Byte"; m.type = "Byte"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Bin"; m.type = "String"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "CBool"; m.type = "Boolean"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "CByte"; m.type = "Byte"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "CDbl"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Chr"; m.type = "String"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "CInt"; m.type = "Integer"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Compare"; m.type = "Integer"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Contains"; m.type = "Boolean"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Count"; m.type = "Integer"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Cos"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Class"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "CSng"; m.type = "Single"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Currency"; m.type = "Currency"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Date"; m.type = "Date"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Date"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Day"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayName"; m.type = "String"; m.def = "DateTime, Format As String = \"\""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayOfWeek"; m.type = "String"; m.def = "DateTime, Format As String = \"\""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayOfYear"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "DaysInMonth"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTime"; m.type = "DateTime"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Decimal"; m.type = "Decimal"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Decode"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "DiffDays"; m.type = "Integer"; m.def = "DateTime, DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "DiffSeconds"; m.type = "Integer"; m.def = "DateTime, DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "DoEvents"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Double"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Encode"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "EndsWith"; m.type = "Boolean"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Exp"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "File"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "FileCopy"; m.type = "Boolean"; m.def = "Source As String, Destination As String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "FileLen"; m.type = "Long"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Fill"; m.type = ""; m.def = "String, String, Length As Integer = -1"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Fix"; m.type = "Long"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Format"; m.type = "String"; m.def = "Expression, [Format As String, [FillChar As String[, RightAligned As Boolean]]]"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Function"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hex"; m.type = "String"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hour"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "IndexOf"; m.type = "Integer"; m.def = "String, Sub As String, Start As Integer = 1, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "InputBox"; m.type = "String"; m.def = "Prompt As String [, Title As String] [, Default As String]"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "String, Insert As String, Position As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "InStr"; m.type = "Integer"; m.def = "[Start As Integer,] Source As String, Find As String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "InStRev"; m.type = "Integer"; m.def = "[Start As Integer,] Source As String, Find As String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Int"; m.type = "Long"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDateValid"; m.type = "Boolean"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDateTimeValid"; m.type = "Boolean"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsLeapYear"; m.type = "Boolean"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsTimeValid"; m.type = "Boolean"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsLinux"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsMac"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsNull"; m.type = "Boolean"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsWindows"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastIndexOf"; m.type = "Integer"; m.def = "String, Sub As String, Start As Integer = -1, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "LCase"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Left"; m.type = "String"; m.def = "String, Length As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "LeftJustified"; m.type = "String"; m.def = "String, Width As Integer, Fill As String = \" \", Truncate As Boolean = False"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Len"; m.type = "Integer"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Length"; m.type = "Integer"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Line"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Log"; m.type = ""; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Log"; m.type = "Long"; m.def = "Double"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Long"; m.type = "Long"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Lower"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "LTrim"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Max"; m.type = "Double"; m.def = "Expression, Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Mid"; m.type = "String"; m.def = "Variable As String, Start As Integer[, Len As Integer]"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Min"; m.type = "Double"; m.def = "Expression, Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Minute"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Module"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Month"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "MonthName"; m.type = "String"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "MsgBox"; m.type = ""; m.def = "Prompt As String [, Buttons As Integer] [, Title As String]"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Now"; m.type = "DateTime"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Peek"; m.type = ""; m.def = "ByRef String, UDF, Length As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Poke"; m.type = ""; m.def = "String, UDF, Length As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Prepend"; m.type = ""; m.def = "String, Prepend As String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Print"; m.type = ""; m.def = "{[ [#]FileNo ,] (Expression Spc(Expression) Tab(Expression) [; | ,]) }"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Random"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Randomize"; m.type = ""; m.def = "[StartValue As Integer]"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadBinary"; m.type = "AnyType"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "String, Position As Integer, Length As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Replace"; m.type = "String"; m.def = "Str As String, SearchFor As String, ReplaceWith As String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Reversed"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Right"; m.type = "String"; m.def = "String, Length As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "RightJustified"; m.type = "String"; m.def = "String, Width As Integer, Fill As String = \" \", Truncate As Boolean = False"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Rnd"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Round"; m.type = "Currency/Double/Long"; m.def = "Expression, Precision As Integer = 0"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "RTrim"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Second"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Section"; m.type = "String"; m.def = "String, Separator As String, Start As Integer, End As Integer = -1, SectionFlags = \"SectionDefault\""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SeekBinary"; m.type = "Integer"; m.def = "String, Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Sgn"; m.type = "Integer"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Short"; m.type = "Short"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Simplified"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Sin"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Single"; m.type = "Single"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Size"; m.type = "Integer"; m.def = "Variable"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Space"; m.type = "String"; m.def = "Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Split"; m.type = "Strings"; m.def = "String, Separator As String, KeepEmptyParts As Boolean, CaseSensitive As Boolean"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "StartsWith"; m.type = "Boolean"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Str"; m.type = "String"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "StrComp"; m.type = "Integer"; m.def = "String, String [, ComparisionMode As Integer]"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "String"; m.type = "String"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "StrReverse"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Sub"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubDays"; m.type = "DateTime"; m.def = "DateTime, Days As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubHours"; m.type = "DateTime"; m.def = "DateTime, Hours As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubMinutes"; m.type = "DateTime"; m.def = "DateTime, Minutes As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubMonths"; m.type = "DateTime"; m.def = "DateTime, Months As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubSeconds"; m.type = "DateTime"; m.def = "DateTime, Seconds As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubYears"; m.type = "DateTime"; m.def = "DateTime, Years As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Sqr"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Tan"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Time"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Trim"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Trimmed"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Truncate"; m.type = ""; m.def = "String, Position As Integer"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Type"; m.type = "String"; m.def = "Variable"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "UCase"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Unicode"; m.type = "String"; m.def = "Expression"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Unicode"; m.type = "Integer"; m.def = "String, Position As Integer = 1"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Upper"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Utf8"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Utf16"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Val"; m.type = "Double"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Value"; m.type = "Double"; m.def = "String"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "WeekNumber"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    
    m.name = "WriteBinary"; m.type = ""; m.def = "String, AnyType"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);
    m.name = "Year"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "My"; m.modifier = _public; framework_methods.append(m);    

  // *** String      
  c.name = "String"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Append"; m.type = ""; m.def = "String, String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Asc"; m.type = "Integer"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Compare"; m.type = "Integer"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Contains"; m.type = "Boolean"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Count"; m.type = "Integer"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Decode"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Encode"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "EndsWith"; m.type = "Boolean"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Fill"; m.type = ""; m.def = "String, String, Length As Integer = -1"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Fix"; m.type = "Long"; m.def = "Expression"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Format"; m.type = "String"; m.def = "Expression, [Format As String, [FillChar As String[, RightAligned As Boolean]]]"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "IndexOf"; m.type = "Integer"; m.def = "String, Sub As String, Start As Integer = 1, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = ""; m.def = "String, Insert As String, Position As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "InStr"; m.type = "Integer"; m.def = "[Start As Integer,] Source As String, Find As String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "InStRev"; m.type = "Integer"; m.def = "[Start As Integer,] Source As String, Find As String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastIndexOf"; m.type = "Integer"; m.def = "String, Sub As String, Start As Integer = -1, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "LCase"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Left"; m.type = "String"; m.def = "String, Length As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "LeftJustified"; m.type = "String"; m.def = "String, Width As Integer, Fill As String = \" \", Truncate As Boolean = False"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Len"; m.type = "Integer"; m.def = "Expression"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Length"; m.type = "Integer"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Lower"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "LTrim"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Mid"; m.type = "String"; m.def = "Variable As String, Start As Integer[, Len As Integer]"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Peek"; m.type = ""; m.def = "ByRef String, UDF, Length As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Poke"; m.type = ""; m.def = "String, UDF, Length As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Prepend"; m.type = ""; m.def = "String, Prepend As String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadBinary"; m.type = "AnyType"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "String, Position As Integer, Length As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Replace"; m.type = "String"; m.def = "Str As String, SearchFor As String, ReplaceWith As String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Reversed"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Right"; m.type = "String"; m.def = "String, Length As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "RightJustified"; m.type = "String"; m.def = "String, Width As Integer, Fill As String = \" \", Truncate As Boolean = False"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "RTrim"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Section"; m.type = "String"; m.def = "String, Separator As String, Start As Integer, End As Integer = -1, SectionFlags = \"SectionDefault\""; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SeekBinary"; m.type = "Integer"; m.def = "String, Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Simplified"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Split"; m.type = "Strings"; m.def = "String, Separator As String, KeepEmptyParts As Boolean, CaseSensitive As Boolean"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "StartsWith"; m.type = "Boolean"; m.def = "String, String, CaseSensitive As Boolean = True"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "StrComp"; m.type = "Integer"; m.def = "String, String [, ComparisionMode As Integer]"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "StrReverse"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Trim"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Trimmed"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Truncate"; m.type = ""; m.def = "String, Position As Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "UCase"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Unicode"; m.type = "Integer"; m.def = "String, Position As Integer = 1"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Upper"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Utf8"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Utf16"; m.type = "String"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Val"; m.type = "Double"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Value"; m.type = "Double"; m.def = "String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Boolean"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, String"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Byte"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Short"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Integer"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Long"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Single"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Double"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Decimal"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, DateTime"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Currency"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = ""; m.def = "String, Date"; m.methodtype = _function; m.scope = "String"; m.modifier = _public; framework_methods.append(m);    

  // *** DateTime      
  c.name = "DateTime"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "AddDays"; m.type = "DateTime"; m.def = "DateTime, Days As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddHours"; m.type = "DateTime"; m.def = "DateTime, Hours As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddMinutes"; m.type = "DateTime"; m.def = "DateTime, Minutes As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddMonths"; m.type = "DateTime"; m.def = "DateTime, Months As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddSeconds"; m.type = "DateTime"; m.def = "DateTime, Seconds As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddYears"; m.type = "DateTime"; m.def = "DateTime, Years As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Date"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Day"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayName"; m.type = "String"; m.def = "DateTime, Format As String = \"\""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayOfWeek"; m.type = "String"; m.def = "DateTime, Format As String = \"\""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayOfYear"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DaysInMonth"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DiffDays"; m.type = "Integer"; m.def = "DateTime, DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DiffSeconds"; m.type = "Integer"; m.def = "DateTime, DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hour"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDateValid"; m.type = "Boolean"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDateTimeValid"; m.type = "Boolean"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsLeapYear"; m.type = "Boolean"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsTimeValid"; m.type = "Boolean"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Minute"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Month"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "MonthName"; m.type = "String"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Now"; m.type = "DateTime"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Second"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubDays"; m.type = "DateTime"; m.def = "DateTime, Days As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubHours"; m.type = "DateTime"; m.def = "DateTime, Hours As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubMinutes"; m.type = "DateTime"; m.def = "DateTime, Minutes As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubMonths"; m.type = "DateTime"; m.def = "DateTime, Months As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubSeconds"; m.type = "DateTime"; m.def = "DateTime, Seconds As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
    m.name = "SubYears"; m.type = "DateTime"; m.def = "DateTime, Years As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Time"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
    m.name = "WeekNumber"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
    m.name = "Year"; m.type = "Integer"; m.def = "DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);    
        
  // *** Utility      
  c.name = "Utility"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Bin"; m.type = "String"; m.def = "Expression"; m.methodtype = _function; m.scope = "Utility"; m.modifier = _public; framework_methods.append(m);
    m.name = "Format"; m.type = "String"; m.def = "Expression, [Format As String, [FillChar As String[, RightAligned As Boolean]]]"; m.methodtype = _function; m.scope = "Utility"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hex"; m.type = "String"; m.def = "Expression"; m.methodtype = _function; m.scope = "Utility"; m.modifier = _public; framework_methods.append(m);
    m.name = "Random"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "Utility"; m.modifier = _public; framework_methods.append(m);
    m.name = "Randomize"; m.type = ""; m.def = "[StartValue As Integer]"; m.methodtype = _function; m.scope = "Utility"; m.modifier = _public; framework_methods.append(m);
    m.name = "Round"; m.type = "Currency/Double/Long"; m.def = "Expression, Precision As Integer = 0"; m.methodtype = _function; m.scope = "Utility"; m.modifier = _public; framework_methods.append(m);    

  // *** Cast      
  c.name = "Cast"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Boolean"; m.type = "Boolean"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "String"; m.type = "String"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "Byte"; m.type = "Byte"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "Short"; m.type = "Short"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "Integer"; m.type = "Integer"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "Long"; m.type = "Long"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "Single"; m.type = "Single"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "Double"; m.type = "Double"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "Decimal"; m.type = "Decimal"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTime"; m.type = "DateTime"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "Currency"; m.type = "Currency"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);
    m.name = "Date"; m.type = "Date"; m.def = "Expression"; m.methodtype = _function; m.scope = "Cast"; m.modifier = _public; framework_methods.append(m);

  // *** Debug      
  c.name = "Debug"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Type"; m.type = "String"; m.def = "Variable"; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "Size"; m.type = "Integer"; m.def = "Variable"; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "File"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "Line"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsLinux"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsMac"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsWindows"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "Sub"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "Function"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "Module"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);
    m.name = "Class"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Debug"; m.modifier = _public; framework_methods.append(m);

  // *** MenuBar    
  c.name = "MenuBar"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "MenuBarItem"; m.type = "MenuBarItem"; m.def = "Name As String"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetVisible"; m.type = ""; m.def = "Boolean"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsVisible"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowContextMenu"; m.type = ""; m.def = "MenuBarItemName As String, X As Integer, Y As Integer"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowContextMenu"; m.type = ""; m.def = "X As Integer, Y As Integer"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "AppendContextMenu"; m.type = ""; m.def = "MenuBarItem"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveAllChildren"; m.type = ""; m.def = "ParentMenuBarItemName As String"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "Show"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hide"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "ToggleVisible"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveAll"; m.type = ""; m.def = ""; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "AppendMenuBarItem"; m.type = ""; m.def = "ParentMenuBarItemName As String, MenuBarItem"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "AppendMenuBarItem"; m.type = ""; m.def = "MenuBarItem"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "AppendMenu"; m.type = ""; m.def = "MenuBarItem"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "AppendChildMenu"; m.type = ""; m.def = "ParentMenuBarItemName As String, MenuBarItem"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "AppendChildMenu"; m.type = ""; m.def = "MenuBarItem"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, Boolean"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, Integer"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, String"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Group As String, PropertyName As String, Boolean"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Group As String, PropertyName As String, Integer"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Group As String, PropertyName As String, String"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "InsertMenu"; m.type = ""; m.def = "ParentMenuBarItemName As String, MenuBarItem"; m.methodtype = _function; m.scope = "MenuBar"; m.modifier = _public; framework_methods.append(m);

  // *** ToolBar    
  c.name = "ToolBar"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "ToolBarItem"; m.type = "ToolBarItem"; m.def = "Name As String"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "InsertControl"; m.type = ""; m.def = "Index As Integer, Control"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetVisible"; m.type = ""; m.def = "Boolean"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsVisible"; m.type = "Boolean"; m.def = "SetVisible"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, Boolean"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, Integer"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithTag"; m.type = ""; m.def = "Tag As String, PropertyName As String, String"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Group As String, PropertyName As String, Boolean"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Group As String, PropertyName As String, Integer"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWithGroup"; m.type = ""; m.def = "Group As String, PropertyName As String, String"; m.methodtype = _function; m.scope = "ToolBar"; m.modifier = _public; framework_methods.append(m);
  
  // *** StatusBar    
  c.name = "StatusBar"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Clear"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "StatusBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveControl"; m.type = ""; m.def = "Control"; m.methodtype = _sub; m.scope = "StatusBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "InsertControl"; m.type = ""; m.def = "Index As Integer, Control"; m.methodtype = _sub; m.scope = "StatusBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "InsertControl"; m.type = ""; m.def = "Index As Integer, Control, Stretch As Integer"; m.methodtype = _sub; m.scope = "StatusBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "Print"; m.type = ""; m.def = "Text As String"; m.methodtype = _sub; m.scope = "StatusBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "Print"; m.type = ""; m.def = "Text As String, TimeOutInMilliSeconds As Integer"; m.methodtype = _sub; m.scope = "StatusBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hide"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "StatusBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "Show"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "StatusBar"; m.modifier = _public; framework_methods.append(m);
    m.name = "ToggleVisible"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "StatusBar"; m.modifier = _public; framework_methods.append(m);

  // *** Math    
  c.name = "Math"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Abs"; m.type = "Double"; m.def = "numerical expression"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Atn"; m.type = "Double"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Cos"; m.type = "Double"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Sin"; m.type = "Double"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Exp"; m.type = "Double"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Ln"; m.type = "Long"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Log"; m.type = "Long"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Sgn"; m.type = "Integer"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Fix"; m.type = "Long"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Int"; m.type = "Long"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Sqr"; m.type = "Long"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Tan"; m.type = "Long"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Rnd"; m.type = "Double"; m.def = "number"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Min"; m.type = "Double"; m.def = "numeric expression1, numeric expression2"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Max"; m.type = "Double"; m.def = "numeric expression1, numeric expression2"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);
    m.name = "Fact"; m.type = "Double"; m.def = "numeric expression1, numeric expression2"; m.methodtype = _function; m.scope = "Math"; m.modifier = _public; framework_methods.append(m);

  // *** CMath    
  c.name = "CMath"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "sin"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "cos"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "tan"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "asin"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "acos"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "atan"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "atan2"; m.type = "Double"; m.def = "Y As Double, X As Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "sinh"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "cosh"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "tanh"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "exp"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "log"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "log10"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "pow"; m.type = "Double"; m.def = "Double, Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "sqrt"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "ceil"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "floor"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "fabs"; m.type = "Double"; m.def = "Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);
    m.name = "fmod"; m.type = "Double"; m.def = "Double, Double"; m.methodtype = _function; m.scope = "CMath"; m.modifier = _public; framework_methods.append(m);

  // *** Application    
  c.name = "Application"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "PrintHtml"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "PrintHtmlAsPdf"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "MsgBox"; m.type = ""; m.def = "Title As String, Caption As String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "Run"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "Stop"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "ScreenWidth"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "ScreenHeight"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "DirectoryName"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "FileName"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetStyleSheet"; m.type = ""; m.def = "Text As String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetLayoutDirection"; m.type = ""; m.def = "RightToLeft As Boolean"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "DoEvents"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "LoadExternalBrowserWithHTML"; m.type = ""; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "CursorSetWait"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "CursorUnsetWait"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "Arguments"; m.type = "Strings"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "ArgumentsAsString"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "LoadProjectFileAsString"; m.type = "String"; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetClipboardText"; m.type = ""; m.def = "Text As String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "ClipboardText"; m.type = "String"; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "QtVersion"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "OperatingSystemName"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetDefaultIcon"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "ExternalOpenFile"; m.type = ""; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "CloseAllWindows"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsLayoutDirection"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentForm"; m.type = "Form"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "FocusControl"; m.type = "Control"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetStyle"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "LoadURLAsString"; m.type = "String"; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "AvailableMimeTypes"; m.type = "Strings"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsMimeTypeAvailable"; m.type = "Boolean"; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "AvailableLanguages"; m.type = "Strings"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetLanguage"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "PlaySound"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "PlayMovie"; m.type = ""; m.def = "String, KeyAndMouseCanCancel As Boolean = True"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "LoadProjectFileAsBinary"; m.type = "String"; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "LoadURLAsBinary"; m.type = "String"; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCountry"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);

    //m.name = "IsSoundAvailable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    //m.name = "Query"; m.type = "Query"; m.def = "String"; m.methodtype = _function; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCaption"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetIcon"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "CursorSetWait"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "CursorUnsetWait"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "ArgumentsAsString"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "QtException"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);
    m.name = "ClearQtException"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Application"; m.modifier = _public; framework_methods.append(m);

  // *** MainWindow    
  c.name = "MainWindow"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "X"; v.type = "Integer"; v.scope = "MainWindow"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Y"; v.type = "Integer"; v.scope = "MainWindow"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Width"; v.type = "Integer"; v.scope = "MainWindow"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Height"; v.type = "Integer"; v.scope = "MainWindow"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "ShowFullScreen"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowMaximized"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowMinimized"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowNormal"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFocusNext"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFocusPrevious"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "Cascade"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "CloseActive"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "CloseAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "Tile"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetScrollBarsEnabled"; m.type = ""; m.def = "Boolean"; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsScrollBarsEnabled"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetViewMode"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "ViewMode"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCaption"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetIcon"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "Move"; m.type = ""; m.def = "X As Integer, Y As Integer"; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "Resize"; m.type = ""; m.def = "Width As Integer, Height As Integer"; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetVisible"; m.type = ""; m.def = "Boolean"; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsVisible"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "MainWindow"; m.modifier = _public; framework_methods.append(m);
  
  // *** Forms    
  c.name = "Forms"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Close"; m.type = "Boolean"; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "Focus"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "First"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "Next"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "Form"; m.type = "Form"; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowFullScreen"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowMaximized"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowMinimized"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowNormal"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "Show"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hide"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFocus"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsOpen"; m.type = "Boolean"; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = "Boolean"; m.def = "String"; m.methodtype = _sub; m.scope = "Forms"; m.modifier = _public; framework_methods.append(m);

  // *** Sounds    
  c.name = "Sounds"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "SetSound"; m.type = "Boolean"; m.def = "SoundId As String, FileName As String"; m.methodtype = _sub; m.scope = "Sounds"; m.modifier = _public; framework_methods.append(m);
    m.name = "Load"; m.type = "Boolean"; m.def = "SoundId As String, FileName As String"; m.methodtype = _sub; m.scope = "Sounds"; m.modifier = _public; framework_methods.append(m);
    m.name = "Play"; m.type = ""; m.def = "SoundId As String"; m.methodtype = _sub; m.scope = "Sounds"; m.modifier = _public; framework_methods.append(m);

  // *** Pixmaps    
  c.name = "Pixmaps"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "SetPixmap"; m.type = "Boolean"; m.def = "PixmapId As String, FileName As String"; m.methodtype = _sub; m.scope = "Pixmaps"; m.modifier = _public; framework_methods.append(m);
    m.name = "Load"; m.type = "Boolean"; m.def = "PixmapId As String, FileName As String"; m.methodtype = _sub; m.scope = "Pixmaps"; m.modifier = _public; framework_methods.append(m);
  

  // *** Color   
  c.name = "Color"; c.type = ""; c.modifier = _public; framework_classes.append(c);
    
    // Properties
    v.name = "White"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Black"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Red"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DarkRed"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Green"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DarkGreen"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Blue"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DarkBlue"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Cyan"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DarkCyan"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Magenta"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DarkMagenta"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Yellow"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DarkYellow"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Gray"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DarkGray"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LightGray"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Color0"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Color1"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Transparent"; v.type = "Color"; v.scope = "Color"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

  // *** Colors   
  c.name = "Colors"; c.type = ""; c.modifier = _public; framework_classes.append(c);
   
    // Methods
    m.name = "SetColor"; m.type = ""; m.def = "ColorId As String, Red As Integer, Green As Integer, Blue As Integer, Alpha As Integer"; m.methodtype = _sub; m.scope = "Colors"; m.modifier = _public; framework_methods.append(m);

  // *** Fonts   
  c.name = "Fonts"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "SetFont"; m.type = ""; m.def = "FontId As String, Name As String, Size As Integer, Italic As Boolean, Bold As Boolean, Underline As Boolean"; m.methodtype = _sub; m.scope = "Fonts"; m.modifier = _public; framework_methods.append(m);

  // *** Painter   
  c.name = "Painter"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "DrawArc"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, StartAngle As Integer, SpanAngle As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawChord"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, StartAngle As Integer, SpanAngle As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawEllipse"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawLine"; m.type = ""; m.def = "X1 As Integer, Y1 As Integer, X2 As Integer, Y2 As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawPie"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, StartAngle As Integer, SpanAngle As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawPixmap"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, PixmapId As String, SX As Integer, SY As Integer, SWidth As Integer, SHeight As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawTiledPixmap"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, PixmapId As String, SX As Integer, SY As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "DrawPixmap"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, pixmapobject As Object, SX As Integer, SY As Integer, SWidth As Integer, SHeight As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "DrawTiledPixmap"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, pixmapobject As Object, SX As Integer, SY As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawPixmap"; m.type = ""; m.def = "X As Integer, Y As Integer, PixmapId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawTiledPixmap"; m.type = ""; m.def = "X As Integer, Y As Integer, PixmapId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "DrawPixmap"; m.type = ""; m.def = "X As Integer, Y As Integer, pixmapobject As Object"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "DrawTiledPixmap"; m.type = ""; m.def = "X As Integer, Y As Integer, pixmapobject As Object"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawPoint"; m.type = ""; m.def = "X As Integer, Y As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawRect"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawRoundRect"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, XRnd As Integer, YRnd As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawText"; m.type = ""; m.def = "X As Integer, Y As Integer, Text As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawFramedText"; m.type = ""; m.def = "X As Integer, Y As Integer, BlackFrame As Boolean, Text As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetFont"; m.type = ""; m.def = "FontId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetFont"; m.type = ""; m.def = "fontobject As Object"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetPen"; m.type = ""; m.def = "ColorId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetPen"; m.type = ""; m.def = "ColorId as String, PenStyle As Long, PenCapStyle As Long, PenJoinStyle As Long"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetPen"; m.type = ""; m.def = "colorobject As Object"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetPen"; m.type = ""; m.def = "colorobject As Object, PenStyle As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetPenPixmap"; m.type = ""; m.def = "pixmapobject As Object"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetPenPixmap"; m.type = ""; m.def = "PixmapId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBrush"; m.type = ""; m.def = "ColorId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBrush"; m.type = ""; m.def = "ColorId As String, BrushStyle As Long"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetBrush"; m.type = ""; m.def = "colorobject As Object"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetBrush"; m.type = ""; m.def = "colorobject As Object, BrushStyle As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetBrushPixmap"; m.type = ""; m.def = "pixmapobject As Object"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBrushPixmap"; m.type = ""; m.def = "PixmapId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetOpacity"; m.type = ""; m.def = "Double"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBackgroundFilled"; m.type = ""; m.def = "Boolean"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBackground"; m.type = ""; m.def = "ColorId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetBackgroundPixmap"; m.type = ""; m.def = "pixmapobject As Object"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBackgroundPixmap"; m.type = ""; m.def = "PixmapId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "FillRect"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, ColorId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "FillRectPixmap"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, PixmapId As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetLayoutDirection"; m.type = ""; m.def = "RightToLeft As Boolean"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);

    m.name = "DrawShadowedText"; m.type = ""; m.def = "X As Integer, Y As Integer, BlackShadow As Boolean, Text As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawTextRect"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, Text As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawFramedTextRect"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, BlackFrame As Boolean, Text As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawShadowedTextRect"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, BlackShadow As Boolean, Text As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawBinary"; m.type = ""; m.def = "DestinationX As Integer, DestinationY As Integer, DestinationWidth As Integer, DestinationHeight As Integer, Binary As String, SourceX As Integer, SourceY As Integer, SourceWidth As Integer, SourceHeight As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawBinary"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, Binary As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawBinary"; m.type = ""; m.def = "Binary As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "PutBinary"; m.type = ""; m.def = "DestinationX As Integer, DestinationY As Integer, DestinationWidth As Integer, DestinationHeight As Integer, Binary As String, SourceX As Integer, SourceY As Integer, SourceWidth As Integer, SourceHeight As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "PutBinary"; m.type = ""; m.def = "X As Integer, Y As Integer, Width As Integer, Height As Integer, Binary As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "PutBinary"; m.type = ""; m.def = "Binary As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetBinary"; m.type = "String"; m.def = "Control, X As Integer, Y As Integer, Width As Integer, Height As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetBinary"; m.type = "String"; m.def = "Control"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "LoadBinary"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "LoadBinary"; m.type = "Boolean"; m.def = "DestinationX As Integer, DestinationY As Integer, DestinationWidth As Integer, DestinationHeight As Integer, FileName As String, SourceX As Integer, SourceY As Integer, SourceWidth As Integer, SourceHeight As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SaveBinary"; m.type = "Boolean"; m.def = "Control, FileName As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "SaveBinary"; m.type = "Boolean"; m.def = "Control, X As Integer, Y As Integer, Width As Integer, Height As Integer, FileName As String"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "Begin"; m.type = ""; m.def = "Width As Integer, Height As Integer"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "End"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    
    /*
    m.name = "DrawConvexPolygon"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawPolygon"; m.type = ""; m.def = "OddEvenFill As Boolean"; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
    m.name = "DrawPolyline"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Painter"; m.modifier = _public; framework_methods.append(m);
*/

    // Properties
    v.name = "NoBrush"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SolidPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Dense1Pattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Dense2Pattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Dense3Pattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Dense4Pattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Dense5Pattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Dense6Pattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Dense7Pattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "HorPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "VerPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CrossPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "BDiagPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "FDiagPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DiagCrossPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LinearGradientPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ConicalGradientPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "RadialGradientPattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "TexturePattern"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    v.name = "NoPen"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SolidLine"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DashLine"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DotLine"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DashDotLine"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "DashDotDotLine"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CustomDashLine"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    v.name = "FlatCap"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SquareCap"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "RoundCap"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    v.name = "MiterJoin"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "BevelJoin"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "RoundJoin"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "SvgMiterJoin"; v.type = "Long"; v.scope = "Painter"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

  // *** OpenDialog    
  c.name = "OpenDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "GetFile"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "OpenDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetFile"; m.type = "String"; m.def = "Caption As String, Directory As String, Filter As String"; m.methodtype = _sub; m.scope = "OpenDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetFiles"; m.type = "Strings"; m.def = ""; m.methodtype = _sub; m.scope = "OpenDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetFiles"; m.type = "Strings"; m.def = "Caption As String, Directory As String, Filter As String"; m.methodtype = _sub; m.scope = "OpenDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetDirectory"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "OpenDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetDirectory"; m.type = "String"; m.def = "Caption As String, Directory As String"; m.methodtype = _sub; m.scope = "OpenDialog"; m.modifier = _public; framework_methods.append(m);
  
  // *** SaveDialog    
  c.name = "SaveDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "GetFile"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "SaveDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetFile"; m.type = "String"; m.def = "Caption As String, Directory As String, Filter As String"; m.methodtype = _sub; m.scope = "SaveDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetDirectory"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "SaveDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetDirectory"; m.type = "String"; m.def = "Caption As String, Directory As String"; m.methodtype = _sub; m.scope = "SaveDialog"; m.modifier = _public; framework_methods.append(m);

  // *** ColorDialog    
  c.name = "ColorDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "GetColor"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "ColorDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetColor"; m.type = "Boolean"; m.def = "Red As Integer, Green As Integer, Blue As Integer, Alpha As Integer"; m.methodtype = _sub; m.scope = "ColorDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Red"; m.type = "Integer"; m.def = ""; m.methodtype = _sub; m.scope = "ColorDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Green"; m.type = "Integer"; m.def = ""; m.methodtype = _sub; m.scope = "ColorDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Blue"; m.type = "Integer"; m.def = ""; m.methodtype = _sub; m.scope = "ColorDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Alpha"; m.type = "Integer"; m.def = ""; m.methodtype = _sub; m.scope = "ColorDialog"; m.modifier = _public; framework_methods.append(m);

  // *** FontDialog    
  c.name = "FontDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "GetFont"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetFont"; m.type = "Boolean"; m.def = "Name As String, Size As Integer, Italic As Boolean, Bold As Boolean, Underline As Boolean"; m.methodtype = _sub; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Name"; m.type = "Integer"; m.def = ""; m.methodtype = _sub; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Size"; m.type = "Integer"; m.def = ""; m.methodtype = _sub; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Italic"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Bold"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Underline"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);

  // *** ProgressDialog    
  c.name = "ProgressDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Show"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "ProgressDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Show"; m.type = ""; m.def = "Caption As String, CancelCaption As String"; m.methodtype = _sub; m.scope = "ProgressDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hide"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "ProgressDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Canceled"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "ProgressDialog"; m.modifier = _public; framework_methods.append(m);
    
    // Properties
    v.name = "Caption"; v.type = "String"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "CancelCaption"; v.type = "String"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Value"; v.type = "Integer"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minimum"; v.type = "Integer"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "Integer"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Wait"; v.type = "Integer"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

  // *** InputDialog    
  c.name = "InputDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "GetDouble"; m.type = ""; m.def = "Caption As String, Text As String = \"\", Value As Double = 0, Minimum As Double = -2147483647, Maximum As Double = 2147483647, Decimals = 1"; m.methodtype = _sub; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetInteger"; m.type = ""; m.def = "Caption As String, Text As String = \"\", Value As Integer = 0, Minimum As Integer = -2147483647, Maximum As Integer = 2147483647, Step = 1"; m.methodtype = _sub; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetString"; m.type = ""; m.def = "Caption As String, Text As String =  \" \", Value As String =  \" \", EchoMode = \"Normal \""; m.methodtype = _sub; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);

  // *** MessageBox    
  c.name = "MessageBox"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Show"; m.type = ""; m.def = "Caption As String, Text As String = \"\", Buttons As String = \"Ok\", DefaultButton As String = \"\", DetailedText As String = \"\", Icon As String = \"\""; m.methodtype = _sub; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Critical"; m.type = ""; m.def = "Caption As String, Text As String = \"\", Buttons As String = \"Ok\", DefaultButton As String = \"\""; m.methodtype = _sub; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Information"; m.type = ""; m.def = "Caption As String, Text As String = \"\", Buttons As String = \"Ok\", DefaultButton As String = \"\""; m.methodtype = _sub; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Question"; m.type = ""; m.def = "Caption As String, Text As String = \"\", Buttons As String = \"Ok\", DefaultButton As String = \"\""; m.methodtype = _sub; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Warning"; m.type = ""; m.def = "Caption As String, Text As String = \"\", Buttons As String = \"Ok\", DefaultButton As String = \"\""; m.methodtype = _sub; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);

  // *** SystemTray    
  c.name = "SystemTray"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "IsSystemTrayAvailable"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsPrintSupported"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "Print"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "Print"; m.type = ""; m.def = "Text As String, Title As String"; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "Print"; m.type = ""; m.def = "Text As String, Title As String, PrintIcon As String"; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "Print"; m.type = ""; m.def = "Text As String, Title As String, PrintIcon As String, TimeOut As Integer"; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "Show"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hide"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "ToggleVisible"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);

    // Properties
    v.name = "ContextMenu"; v.type = "SystemTray"; v.scope = "SystemTray"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Icon"; v.type = "SystemTray"; v.scope = "SystemTray"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ToolTip"; v.type = "SystemTray"; v.scope = "SystemTray"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Visible"; v.type = "Boolean"; v.scope = "SystemTray"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
  
  // *** Log    
  c.name = "Log"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Print"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Log"; m.modifier = _public; framework_methods.append(m);
    m.name = "PrintHtml"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Log"; m.modifier = _public; framework_methods.append(m);
    m.name = "PrintSql"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "Log"; m.modifier = _public; framework_methods.append(m);
    m.name = "Show"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Log"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowMaximized"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Log"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShowMinimized"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Log"; m.modifier = _public; framework_methods.append(m);
    m.name = "Hide"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Log"; m.modifier = _public; framework_methods.append(m);

  // *** Actions    
  c.name = "Actions"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "SetEnabled"; m.type = ""; m.def = "ActionId As String, Boolean"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsEnabled"; m.type = "Boolean"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetVisible"; m.type = ""; m.def = "ActionId As String, Boolean"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsVisible"; m.type = "Boolean"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetChecked"; m.type = ""; m.def = "ActionId As String, Boolean"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsChecked"; m.type = "Boolean"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetStatusTip"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsStatusTip"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetToolTip"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsToolTip"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetWhatsThis"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsWhatsThis"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetIcon"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsIcon"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetTag"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsTag"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCaption"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsCaption"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetText"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsText"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetSoundOnEvent"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsSoundOnEvent"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetGroup"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsGroup"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetKey"; m.type = ""; m.def = "ActionId As String, String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsKey"; m.type = "String"; m.def = "ActionId As String"; m.methodtype = _sub; m.scope = "Actions"; m.modifier = _public; framework_methods.append(m);

  // *** Preferences    
  c.name = "Preferences"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Language"; v.type = "String"; v.scope = "Preferences"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
   
    // Methods
    m.name = "Has"; m.type = "Boolean"; m.def = "PreferenceId As String"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = ""; m.def = "PreferenceId As String"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "Ids"; m.type = "Strings"; m.def = ""; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetBoolean"; m.type = ""; m.def = "PreferenceId As String, Boolean"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetInteger"; m.type = ""; m.def = "PreferenceId As String, Integer"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetString"; m.type = ""; m.def = "PreferenceId As String, String"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetDouble"; m.type = ""; m.def = "PreferenceId As String, Double"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "Boolean"; m.type = "Boolean"; m.def = "PreferenceId As String"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "Integer"; m.type = "Integer"; m.def = "PreferenceId As String"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "String"; m.type = "String"; m.def = "PreferenceId As String"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);
    m.name = "Double"; m.type = "Double"; m.def = "PreferenceId As String"; m.methodtype = _sub; m.scope = "Preferences"; m.modifier = _public; framework_methods.append(m);

  // *** Dir    
  c.name = "Dir"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Create"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "RecursiveCreate"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "RecursiveRemove"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "FindFile"; m.type = "Strings"; m.def = "Path As String, NameFilter As String, Filter As String = \"NoFilter\", Sorting As String = \"NoSort\""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "RecursiveFindFile"; m.type = "Strings"; m.def = "Path As String, NameFilter As String, Filter As String = \"NoFilter\", Sorting As String = \"NoSort\""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "FindFile"; m.type = "Strings"; m.def = "Path As String, NameFilter As Strings, Filter As String = \"NoFilter\", Sorting As String = \"NoSort\""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "RecursiveFindFile"; m.type = "Strings"; m.def = "Path As String, NameFilter As Strings, Filter As String = \"NoFilter\", Sorting As String = \"NoSort\""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "FileList"; m.type = "Strings"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "RecursiveFileList"; m.type = "Strings"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Copy"; m.type = "Boolean"; m.def = "SourcePath As String, DestinationPath As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Move"; m.type = "Boolean"; m.def = "SourcePath As String, DestinationPath As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Exists"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTimeCreatedAsString"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTimeUpdatedAsString"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTimeReadAsString"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Owner"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Group"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsReadable"; m.type = "Boolean"; m.def = "Path As String, Who As String = \"User\""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsWritable"; m.type = "Boolean"; m.def = "Path As String, Who As String = \"User\""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsExecutable"; m.type = "Boolean"; m.def = "Path As String, Who As String = \"User\""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsHidden"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDir"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Drives"; m.type = "Strings"; m.def = ""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "TempPath"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "HomePath"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "RootPath"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "WithNativeSeparators"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "WithoutNativeSeparators"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "BundleName"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "SymLinkTarget"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Name"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Path"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Suffix"; m.type = "String"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsRoot"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsRelative"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsSymLink"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsBundle"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _sub; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);

  // *** File    
  c.name = "File"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Size"; m.type = "Long"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Resize"; m.type = "Boolean"; m.def = "FileName As String, NewSize As Long"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Truncate"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadText"; m.type = "String"; m.def = "FileName As String, Codec As String = \"UTF-8\", AutoDetectUnicode As Boolean = True, GenerateByteOrderMark As Boolean = True"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteText"; m.type = "Boolean"; m.def = "FileName As String, Text As String, Append As Boolean = False, Codec As String = \"UTF-8\", AutoDetectUnicode As Boolean = True, GenerateByteOrderMark As Boolean = True"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadBinary"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBinary"; m.type = "Boolean"; m.def = "FileName As String, Binary As String, Append As Boolean = False"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Link"; m.type = "Boolean"; m.def = "SourceFileName As String, DestinationFileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Create"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Copy"; m.type = "Boolean"; m.def = "SourceFileName As String, DestinationFileName As String, Overwrite As Boolean = True"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Move"; m.type = "Boolean"; m.def = "SourceFileName As String, DestinationFileName As String, Overwrite As Boolean = True"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Rename"; m.type = "Boolean"; m.def = "SourceFileName As String, DestinationFileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Exists"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTimeCreatedAsString"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTimeUpdatedAsString"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "DateTimeReadAsString"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Owner"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Group"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsReadable"; m.type = "Boolean"; m.def = "FileName As String, Who As String = \"User\""; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsWritable"; m.type = "Boolean"; m.def = "FileName As String, Who As String = \"User\""; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsExecutable"; m.type = "Boolean"; m.def = "FileName As String, Who As String = \"User\""; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsHidden"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "WithNativeSeparators"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "WithoutNativeSeparators"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "SymLinkTarget"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Name"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Path"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Suffix"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsRelative"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsSymLink"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _sub; m.scope = "File"; m.modifier = _public; framework_methods.append(m);

  // *** Process    
  c.name = "Process"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Run"; m.type = "Boolean"; m.def = "String"; m.methodtype = _sub; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "Run"; m.type = "Boolean"; m.def = "String, Arguments As Strings"; m.methodtype = _sub; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);

  // *** DatabaseDialog    
  c.name = "DatabaseDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "GetDatabase"; m.type = "Boolean"; m.def = ""; m.methodtype = _sub; m.scope = "DatabaseDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetDatabase"; m.type = "Boolean"; m.def = "Driver As String, Name As String, User As String, Password As String, Host As String, Options As String, Port As String"; m.methodtype = _sub; m.scope = "DatabaseDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Driver"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "DatabaseDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Host"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "DatabaseDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Port"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "DatabaseDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Name"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "DatabaseDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "User"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "DatabaseDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Password"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "DatabaseDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Options"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "DatabaseDialog"; m.modifier = _public; framework_methods.append(m);

  // *** Database    
  c.name = "Database"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "MySQL"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "PostgreSQL"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "SQLite"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "ODBC"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "LocalHost"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "DefaultPort"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "DefaultOptions"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetCurrentDatabase"; m.type = "Boolean"; m.def = "Name As String"; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentDatabase"; m.type = "String"; m.def = ""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Exists"; m.type = "Boolean"; m.def = "Driver As String, Name As String, User As String, Password As String, Host As String = LocalHost, Options As String = DefaultOptions, Port As String = DefaultPort"; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Create"; m.type = "Boolean"; m.def = "Driver As String, Name As String, User As String, Password As String, Host As String = LocalHost, Options As String = DefaultOptions, Port As String = DefaultPort"; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "TestConnection"; m.type = "Boolean"; m.def = "Driver As String, User As String, Password As String, Host As String = LocalHost, Options As String = DefaultOptions, Port As String = DefaultPort"; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Empty"; m.type = "Boolean"; m.def = "Driver As String, Name As String, User As String, Password As String, Host As String = LocalHost, Options As String = DefaultOptions, Port As String = DefaultPort"; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Drop"; m.type = "Boolean"; m.def = "Driver As String, Name As String, User As String, Password As String, Host As String = LocalHost, Options As String = DefaultOptions, Port As String = DefaultPort"; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenSQLite"; m.type = "Boolean"; m.def = "Name As String"; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = "Boolean"; m.def = "Driver As String, Name As String, User As String, Password As String"; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = "Boolean"; m.def = "Driver As String, Name As String, User As String, Password As String, Host As String = LocalHost, Options As String = DefaultOptions, Port As String = DefaultPort"; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = "Boolean"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsOpen"; m.type = "Boolean"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastSQLError"; m.type = "String"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastSQLCommands"; m.type = "String"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastSQLCommandFailed"; m.type = "String"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsTransactionSupported"; m.type = "Boolean"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Transaction"; m.type = "Boolean"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Commit"; m.type = "Boolean"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Rollback"; m.type = "Boolean"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Tables"; m.type = "Strings"; m.def = "Name As String = \"\""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);
    m.name = "Drivers"; m.type = "Strings"; m.def = ""; m.methodtype = _sub; m.scope = "Database"; m.modifier = _public; framework_methods.append(m);

  // *** Table    
  c.name = "Table"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Exists"; m.type = "Boolean"; m.def = "Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Exists"; m.type = "Boolean"; m.def = "Database As String, Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Create"; m.type = "Boolean"; m.def = "Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Create"; m.type = "Boolean"; m.def = "Database As String, Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Create"; m.type = "Boolean"; m.def = "Table As String, Fields As Array"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Create"; m.type = "Boolean"; m.def = "Database As String, Table As String, Fields As Array"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Empty"; m.type = "Boolean"; m.def = "Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Empty"; m.type = "Boolean"; m.def = "Database As String, Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Drop"; m.type = "Boolean"; m.def = "Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Drop"; m.type = "Boolean"; m.def = "Database As String, Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Delete"; m.type = "Boolean"; m.def = "Table As String, Where As Array"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Delete"; m.type = "Boolean"; m.def = "Database As String, Table As String, Where As Array"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Update"; m.type = "Boolean"; m.def = "Table As String, Update As Array, Where As Array"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Update"; m.type = "Boolean"; m.def = "Database As String, Table As String, Update As Array, Where As Array"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = "Boolean"; m.def = "Table As String, Insert As Array"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "Insert"; m.type = "Boolean"; m.def = "Database As String, Table As String, Insert As Array"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "FieldNames"; m.type = "Strings"; m.def = "Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "FieldNames"; m.type = "Strings"; m.def = "Database As String, Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "PrimaryKeyName"; m.type = "String"; m.def = "Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);
    m.name = "PrimaryKeyName"; m.type = "String"; m.def = "Database As String, Table As String"; m.methodtype = _sub; m.scope = "Table"; m.modifier = _public; framework_methods.append(m);

  // *** Records    
  c.name = "Records"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Open"; m.type = "String"; m.def = "TableOrSql As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = "String"; m.def = "Database As String, TableOrSql As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = "String"; m.def = "Table As String, Where As Array"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = "String"; m.def = "Database As String, Table As String, Where As Array"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = "String"; m.def = "Table As String, Where As Array, OrderBy As Array"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = "String"; m.def = "Database As String, Table As String, Where As Array, OrderBy As Array"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = "Boolean"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Requery"; m.type = "Boolean"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "First"; m.type = "Boolean"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Next"; m.type = "Boolean"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Previous"; m.type = "Boolean"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Last"; m.type = "Boolean"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "GoTo"; m.type = "Boolean"; m.def = "RecordsId As String, Position As Integer"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Length"; m.type = "Integer"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Position"; m.type = "Integer"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "FieldNames"; m.type = "Strings"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "PrimaryKey"; m.type = "Integer"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "PrimaryKeyName"; m.type = "String"; m.def = "RecordsId As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
    m.name = "Value"; m.type = "Variant"; m.def = "RecordsId As String, Field As String"; m.methodtype = _sub; m.scope = "Records"; m.modifier = _public; framework_methods.append(m);
  
  // *** Err   
  c.name = "Err"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Number"; v.type = "Integer"; v.scope = "Err"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Source"; v.type = "String"; v.scope = "Err"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Description"; v.type = "String"; v.scope = "Err"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "Clear"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Err"; m.modifier = _public; framework_methods.append(m);
    m.name = "Raise"; m.type = ""; m.def = "Number As Integer, Source As String, Description As String"; m.methodtype = _sub; m.scope = "Err"; m.modifier = _public; framework_methods.append(m);


  // *** Color   
  //c.name = "Color"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    //m.name = "Set"; m.type = ""; m.def = "Color As String"; m.methodtype = _sub; m.scope = "Color"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetColor"; m.type = ""; m.def = "R As Integer, G As Integer, B As Integer, A As Integer"; m.methodtype = _sub; m.scope = "Color"; m.modifier = _public; framework_methods.append(m);
    /*
    m.name = "Rgba"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "Color"; m.modifier = _public; framework_methods.append(m);
    m.name = "Value"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Color"; m.modifier = _public; framework_methods.append(m);
    m.name = "r"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Color"; m.modifier = _public; framework_methods.append(m);
    m.name = "g"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Color"; m.modifier = _public; framework_methods.append(m);
    m.name = "b"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Color"; m.modifier = _public; framework_methods.append(m);
    m.name = "a"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Color"; m.modifier = _public; framework_methods.append(m);
*/



    /*
  // *** Dir    
  c.name = "Dir"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Name"; v.type = "String"; v.scope = "Dir"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    
    // Methods
    m.name = "Create"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "RecursiveRemove"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "FindFile"; m.type = "Strings"; m.def = "NameFilter As String, Filter As String, Sorting As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "RecursiveFindFile"; m.type = "Strings"; m.def = "NameFilter As String, Filter As String, Sorting As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "FileList"; m.type = "Strings"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "RecursiveFileList"; m.type = "Strings"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Copy"; m.type = "Boolean"; m.def = "DestinationPath As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Move"; m.type = "Boolean"; m.def = "NewPath As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Exists"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "CreateTime"; m.type = "DateTime"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "UpdateTime"; m.type = "DateTime"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "User"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Group"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetPermission"; m.type = "Boolean"; m.def = "Readable As Boolean, Writeable As Boolean, Executable As Boolean"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsReadable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsWriteable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsExecutable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsHidden"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);

    m.name = "TempPath"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Create"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Copy"; m.type = "Boolean"; m.def = "SourcePath As String, DestinationPath As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Move"; m.type = "Boolean"; m.def = "OldPath As String, NewPath As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDir"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsDir"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
    m.name = "Exists"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _function; m.scope = "Dir"; m.modifier = _public; framework_methods.append(m);
*/
    /*
  // *** File    
  c.name = "File"; c.type = ""; c.modifier = _public; framework_classes.append(c);
    
    // Methods
    m.name = "OpenForReading"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenForWriting"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenForUpdating"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenForAppending"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "OpenForTemporary"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "FileName"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Extension"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "BaseName"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Path"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadLine"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteLine"; m.type = "String"; m.def = "Data As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Read"; m.type = "UDFType"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Write"; m.type = "Boolean"; m.def = "UserDefinedType As UDFType"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadBytes"; m.type = "ByteArray"; m.def = "Len As Long"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBytes"; m.type = "Boolean"; m.def = "Bytes As ByteArray"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Position"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "ChangePosition"; m.type = "Boolean"; m.def = "NewPosition As Long"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsEOF"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Copy"; m.type = "Boolean"; m.def = "DestinationPath As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Move"; m.type = "Boolean"; m.def = "DestinationPath As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Len"; m.type = "Long"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "CreateTime"; m.type = "DataTime"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "UpdateTime"; m.type = "DataTime"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "User"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Group"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetPermission"; m.type = "Boolean"; m.def = "Readable As Boolean, Writeable As Boolean, Executable As Boolean"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsOpen"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsFile"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsExecutable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsReadable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsWriteable"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsHidden"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);

    m.name = "Create"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Remove"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Copy"; m.type = "Boolean"; m.def = "SourcePath As String, DestinationPath As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Move"; m.type = "Boolean"; m.def = "OldPath As String, NewPath As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsFile"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Exists"; m.type = "Boolean"; m.def = "Path As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Truncate"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Load"; m.type = "String"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "Save"; m.type = "Boolean"; m.def = "FileName As String, Data As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "ReadBytes"; m.type = "ByteArray"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
    m.name = "WriteBytes"; m.type = "Boolean"; m.def = "FileName As String, Bytes As ByteArray"; m.methodtype = _function; m.scope = "File"; m.modifier = _public; framework_methods.append(m);
*/


/*
  // *** DateTime    
  c.name = "DateTime"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Day"; v.type = "Integer"; v.scope = "DateTime"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Month"; v.type = "Integer"; v.scope = "DateTime"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Year"; v.type = "Integer"; v.scope = "DateTime"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Hour"; v.type = "Integer"; v.scope = "DateTime"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minute"; v.type = "Integer"; v.scope = "DateTime"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Second"; v.type = "Integer"; v.scope = "DateTime"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MSecond"; v.type = "Integer"; v.scope = "DateTime"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);    

    // Methods
    m.name = "AsString"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AsString"; m.type = "String"; m.def = "DateTimeFormat As Integer"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AsString"; m.type = "String"; m.def = "DateTimeFormat As String"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayOfWeek"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DayOfYear"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DaysInMonth"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DaysInYear"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "WeekNumber"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsLeapYear"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Equal"; m.type = "Boolean"; m.def = "OtherDateTime As DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "OlderAs"; m.type = "Boolean"; m.def = "OtherDateTime As DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "YoungerAs"; m.type = "Boolean"; m.def = "OtherDateTime As DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DiffDay"; m.type = "Integer"; m.def = "OtherDateTime As DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DiffSeconds"; m.type = "Integer"; m.def = "OtherDateTime As DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "DiffMSeconds"; m.type = "Integer"; m.def = "OtherDateTime As DateTime"; m.methodtype = _function; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddDate"; m.type = ""; m.def = "OtherDateTime As DateTime"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddDays"; m.type = ""; m.def = "Days As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddMonths"; m.type = ""; m.def = "Months As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddYears"; m.type = ""; m.def = "Years As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubDate"; m.type = ""; m.def = "OtherDateTime As DateTime"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubDays"; m.type = ""; m.def = "Days As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubMonths"; m.type = ""; m.def = "Months As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubYears"; m.type = ""; m.def = "Years As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddTime"; m.type = ""; m.def = "OtherDateTime As DateTime"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddHours"; m.type = ""; m.def = "Hours As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddMinutes"; m.type = ""; m.def = "Minutes As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddSeconds"; m.type = ""; m.def = "Seconds As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "AddMSeconds"; m.type = ""; m.def = "Seconds As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubHours"; m.type = ""; m.def = "Hours As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubMinutes"; m.type = ""; m.def = "Minutes As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubSeconds"; m.type = ""; m.def = "Seconds As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "SubMSeconds"; m.type = ""; m.def = "Seconds As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);

    m.name = "Now"; m.type = "DateTime"; m.def = ""; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentDate"; m.type = "DateTime"; m.def = ""; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentTime"; m.type = "DateTime"; m.def = ""; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "FromString"; m.type = "DateTime"; m.def = "DateTime As String"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentDayOfWeek"; m.type = "Integer"; m.def = ""; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "CurrentMonthOfYear"; m.type = "Integer"; m.def = ""; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "Weekday"; m.type = "Integer"; m.def = "Date As DateTime"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "YearMonth"; m.type = "Integer"; m.def = "Date As DateTime"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsValid"; m.type = "Boolean"; m.def = "Year As Integer, Month As Integer, Day As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShortMonthName"; m.type = "String"; m.def = "Month As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "ShortDayName"; m.type = "String"; m.def = "WeekDay As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "LongMonthName"; m.type = "String"; m.def = "Month As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
    m.name = "LongDayName"; m.type = "String"; m.def = "WeekDay As Integer"; m.methodtype = _sub; m.scope = "DateTime"; m.modifier = _public; framework_methods.append(m);
*/
    /*
  // *** Process    
  c.name = "Process"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Name"; v.type = "String"; v.scope = "Process"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "Run"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "Run"; m.type = "Boolean"; m.def = "FileName As String, Arguments As Strings, Environment As Strings"; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "Kill"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "Terminate"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "LastError"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsCrashed"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsRunning"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "IsStopped"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "ExitCode"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "WaitForStarted"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "WaitForReadyRead"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "WaitForBytesWritten"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "WaitForFinished"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "Read"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "Write"; m.type = "Boolean"; m.def = "Data As String"; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "StandardOutput"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "StandardError"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);

    m.name = "Run"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "Run"; m.type = "Boolean"; m.def = "FileName As String, Arguments As Strings, Environment As Strings"; m.methodtype = _function; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "OnEvent"; m.type = "Event"; m.def = "LastError As String, StandardOutput As String, StandardError As String, Done As Boolean"; m.methodtype = _event; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
    m.name = "Process_OnEvent"; m.type = "Event"; m.def = "LastError As String, StandardOutput As String, StandardError As String, Done As Boolean"; m.methodtype = _event; m.scope = "Process"; m.modifier = _public; framework_methods.append(m);
*/

/*
  // *** FontDialog    
  c.name = "FontDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "GetFont"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetFont"; m.type = "String"; m.def = "InitFontId As String"; m.methodtype = _function; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "ok"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "FontDialog"; m.modifier = _public; framework_methods.append(m);
*/
    /*
  // *** InputDialog    
  c.name = "InputDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "ok"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetDouble"; m.type = "Double"; m.def = "Title As String, Caption As String"; m.methodtype = _function; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetDouble"; m.type = "Double"; m.def = "Title As String, Caption As String, Value As Double, MinValue As Double, MaxValue As Double, Decimals As Integer"; m.methodtype = _function; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetInteger"; m.type = "Integer"; m.def = "Title As String, Caption As String"; m.methodtype = _function; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetInteger"; m.type = "Integer"; m.def = "Title As String, Caption As String, Value As Integer, MinValue As Integer, MaxValue As Integer"; m.methodtype = _function; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetString"; m.type = "String"; m.def = "Title As String, Caption As String"; m.methodtype = _function; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "GetString"; m.type = "String"; m.def = "Title As String, Caption As String, Value As String"; m.methodtype = _function; m.scope = "InputDialog"; m.modifier = _public; framework_methods.append(m);
*/
    /*
  // *** MessageBox    
  c.name = "MessageBox"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "About"; m.type = ""; m.def = "Title As String, Caption As String"; m.methodtype = _sub; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Critical"; m.type = "String"; m.def = "Title As String, Caption As String"; m.methodtype = _function; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Critical"; m.type = "String"; m.def = "Title As String, Caption As String, Buttons As String, DefaultButton As String"; m.methodtype = _function; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Information"; m.type = "String"; m.def = "Title As String, Caption As String"; m.methodtype = _function; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Information"; m.type = "String"; m.def = "Title As String, Caption As String, Buttons As String, DefaultButton As String"; m.methodtype = _function; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Question"; m.type = "String"; m.def = "Title As String, Caption As String"; m.methodtype = _function; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Question"; m.type = "String"; m.def = "Title As String, Caption As String, Buttons As String, DefaultButton As String"; m.methodtype = _function; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Warning"; m.type = "String"; m.def = "Title As String, Caption As String"; m.methodtype = _function; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
    m.name = "Warning"; m.type = "String"; m.def = "Title As String, Caption As String, Buttons As String, DefaultButton As String"; m.methodtype = _function; m.scope = "MessageBox"; m.modifier = _public; framework_methods.append(m);
*/
    /*
  // *** ProgressDialog    
  c.name = "ProgressDialog"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Caption"; v.type = "String"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Value"; v.type = "Integer"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Minimum"; v.type = "Integer"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Maximum"; v.type = "Integer"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Wait"; v.type = "Integer"; v.scope = "ProgressDialog"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "Open"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "ProgressDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "ProgressDialog"; m.modifier = _public; framework_methods.append(m);
    m.name = "Canceled"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "ProgressDialog"; m.modifier = _public; framework_methods.append(m);
*/
    /*

    /*
  // *** SplashScreen    
  c.name = "SplashScreen"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Image"; v.type = "String"; v.scope = "SplashScreen"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "Print"; m.type = ""; m.def = "Text As String"; m.methodtype = _sub; m.scope = "SplashScreen"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "SplashScreen"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "SplashScreen"; m.modifier = _public; framework_methods.append(m);
*/

    /*
  // *** SystemTray    
  c.name = "SystemTray"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Icon"; v.type = "String"; v.scope = "SystemTray"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ToolTip"; v.type = "String"; v.scope = "SystemTray"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Visible"; v.type = "Boolean"; v.scope = "SystemTray"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    // Methods
    m.name = "Print"; m.type = ""; m.def = "String"; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);

    // Events
    m.name = "SystemTray_OnEvent"; m.type = "Event"; m.def = ""; m.methodtype = _event; m.scope = "SystemTray"; m.modifier = _public; framework_methods.append(m);
*/
/*
  // *** Pixmap    
  c.name = "Pixmap"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Load"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "Pixmap"; m.modifier = _public; framework_methods.append(m);
    m.name = "Width"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Pixmap"; m.modifier = _public; framework_methods.append(m);
    m.name = "Height"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Pixmap"; m.modifier = _public; framework_methods.append(m);

  // *** Sounds   
  c.name = "Sounds"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Sound"; m.type = "Sound"; m.def = "String"; m.methodtype = _function; m.scope = "Sounds"; m.modifier = _public; framework_methods.append(m);

  // *** Sound   
  c.name = "Sound"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Load"; m.type = "Boolean"; m.def = "FileName As String"; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "Played"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "Play"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
    m.name = "Stop"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Sound"; m.modifier = _public; framework_methods.append(m);
*/


  // *** Font   
  //c.name = "Font"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    //m.name = "Set"; m.type = ""; m.def = "Font As String"; m.methodtype = _sub; m.scope = "Font"; m.modifier = _public; framework_methods.append(m);
    //m.name = "SetFont"; m.type = ""; m.def = "Name As String, Size As Integer, Italic As Boolean, Bold As Boolean, Underline As Boolean"; m.methodtype = _sub; m.scope = "Font"; m.modifier = _public; framework_methods.append(m);
    /*
    m.name = "Nsibu"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Font"; m.modifier = _public; framework_methods.append(m);
    m.name = "Value"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Font"; m.modifier = _public; framework_methods.append(m);
    m.name = "Name"; m.type = "String"; m.def = ""; m.methodtype = _function; m.scope = "Font"; m.modifier = _public; framework_methods.append(m);
    m.name = "Size"; m.type = "Integer"; m.def = ""; m.methodtype = _function; m.scope = "Font"; m.modifier = _public; framework_methods.append(m);
    m.name = "Italic"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Font"; m.modifier = _public; framework_methods.append(m);
    m.name = "Bold"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Font"; m.modifier = _public; framework_methods.append(m);
    m.name = "Underline"; m.type = "Boolean"; m.def = ""; m.methodtype = _function; m.scope = "Font"; m.modifier = _public; framework_methods.append(m);
    */
/*
  // *** Polygons   
  c.name = "Polygons"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "Polygon"; m.type = "Polygon"; m.def = "String"; m.methodtype = _function; m.scope = "Polygons"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveAll"; m.type = ""; m.def = ""; m.methodtype = _sub; m.scope = "Polygons"; m.modifier = _public; framework_methods.append(m);

  // *** Polygon   
  c.name = "Polygon"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "X"; m.type = "Integer"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "Polygon"; m.modifier = _public; framework_methods.append(m);
    m.name = "Y"; m.type = "Integer"; m.def = "Index As Integer"; m.methodtype = _function; m.scope = "Polygon"; m.modifier = _public; framework_methods.append(m);
    m.name = "Set"; m.type = ""; m.def = "Index As Integer, X As Integer, Y As Integer"; m.methodtype = _sub; m.scope = "Polygon"; m.modifier = _public; framework_methods.append(m);
    m.name = "Add"; m.type = ""; m.def = "X As Integer, Y As Integer"; m.methodtype = _sub; m.scope = "Polygon"; m.modifier = _public; framework_methods.append(m);
*/
    /*
  // *** Docks   
  c.name = "Docks"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Methods
    m.name = "AddDock"; m.type = ""; m.def = "Caption As String, FormName As String, LeftDock As Boolean, RightDock As Boolean, TopDock As Boolean, BottomDock As Boolean, DockId as As String"; m.methodtype = _sub; m.scope = "Docks"; m.modifier = _public; framework_methods.append(m);
    m.name = "RemoveDock"; m.type = ""; m.def = "DockId As String"; m.methodtype = _sub; m.scope = "Docks"; m.modifier = _public; framework_methods.append(m);
    m.name = "SplitDock"; m.type = ""; m.def = "FirstDockId As String, SecondDockId As String, HorizontalAndNotVertical As Boolean"; m.methodtype = _sub; m.scope = "Docks"; m.modifier = _public; framework_methods.append(m);
    m.name = "TabifyDock"; m.type = ""; m.def = "FirstDockId As String, SecondDockId As String"; m.methodtype = _sub; m.scope = "Docks"; m.modifier = _public; framework_methods.append(m);
    m.name = "SetDockNestingEnabled"; m.type = ""; m.def = "Boolean"; m.methodtype = _sub; m.scope = "Docks"; m.modifier = _public; framework_methods.append(m);
    m.name = "Open"; m.type = ""; m.def = "DockId As String"; m.methodtype = _sub; m.scope = "Docks"; m.modifier = _public; framework_methods.append(m);
    m.name = "Close"; m.type = ""; m.def = "DockId As String"; m.methodtype = _sub; m.scope = "Docks"; m.modifier = _public; framework_methods.append(m);
*/

  // ***  

    
    /*
  // *** kb   
  c.name = "kb"; c.type = ""; c.modifier = _public; framework_classes.append(c);

    // Properties
    v.name = "Monday"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Tuesday"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Wednesday"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Thursday"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Friday"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Saturday"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Sunday"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    v.name = "January"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "February"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "March"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "April"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "May"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "June"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "July"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "August"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "September"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "Octobre"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "November"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "December"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    v.name = "StandardDate"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LongDate"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MediumDate"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ShortDate"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);

    v.name = "StandardTime"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "LongTime"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "MediumTime"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
    v.name = "ShortTime"; v.type = "Integer"; v.scope = "kb"; v.scope2 = ""; v.modifier = _public; framework_variables.append(v);
*/

}

void _inputtip_parser::addFrameworkClasses(QList<_inputtip_info> &l, QString sName)
{
  foreach (_class v, framework_classes)
  { 
    if (v.name.compare(sName, Qt::CaseInsensitive) == 0){            

      foreach (_variable v, framework_variables)
      { 
        if (v.scope.compare(sName, Qt::CaseInsensitive) == 0) append(l, v.name, __variable, v.type_name, "", 0, v.scope, "Framework");
      }

      foreach (_method v, framework_methods)
      { 
        if (v.scope.compare(sName, Qt::CaseInsensitive) == 0) append(l, v.name, v.methodtype == _sub  ? __sub : v.methodtype == _function ? __function : v.methodtype == _constructor ? __constructor : __event2, "", "", 0, v.scope, "Framework");
      }

      addFrameworkClasses(l, v.type);
      
    }
    
  }
  
}