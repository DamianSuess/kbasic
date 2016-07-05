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

#include <QtGui>
#include <QtSql>

#include "_mainwindow.h"
#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"
#include "../kbshared/_table.h"

#include "_projectwindow.h"
#include "_inputtip_parser.h"
#include "_parserwindow.h"


QMap<QString, _inputtip_parser>ci;

extern bool checkObjectName(QString s);

extern QString kbasicPath(QString sPath);
extern _projectwindow *EXTERN_my_projectwindow;

extern const QIcon &kbasicIcon(QString s);
extern _mainwindow *EXTERN_my_mainwindow;

extern _parserwindow *EXTERN_my_parserwindow;

extern QSqlDatabase CurrentDatabase;

QString sKBasicPath;
QSystemTrayIcon *trayIcon;


extern QString EXTERN_sError;

void _mainwindow::buildExampleMenu(QString sPath, QMenu *m)
{
  //return;

   QMenu *m_orig = m;
  m = 0;
  QDir thisDir( sPath );	
  QFileInfoList files = thisDir.entryInfoList();

  QAction *a = 0;
  if ( files.size() ) {

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i) {
     fi = files.at(i);

		    if (fi.fileName() == "." || fi.fileName() == "..")
		        ; // nothing
		    else if ( fi.isSymLink()) {
		    }
        else if ( fi.isDir() ){
          //int n = ++nExampleFileCounter;

          if (isProjectDir(fi.fileName())){
           

            if (m == 0){
              m = m_orig;
            }

            a = m->addAction(/*kbasicIcon(kbasicPath("ide/kbasic_icon.jpg")), */fi.fileName());
            connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
            exampleMapper->setMapping(a, fi.absoluteFilePath() + "/" + fi.fileName());

          } else {
            QMenu *m2 = new QMenu( fi.fileName() );
            buildExampleMenu(sPath + "/" + fi.fileName(), m2);

            if (m == 0){
              m = m_orig;
            }

            m->addMenu(/*_mainwindow::getPixmap(kbasicPath("ide/folder.png")), */m2);

          }

        } else {
          //int n = ++nExampleFileCounter;

//          i1++;

          QString s = fi.fileName();

          // following project related is not executed anymore
          if (isProjectDir(sPath)){

            if (m == 0){
              m = m_orig;
            }


            if (isProjectFile(s)){
              m->addSeparator();
              a = m->addAction(kbasicIcon(kbasicPath("ide/kbasic_icon.jpg")), s);
              connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
              exampleMapper->setMapping(a, fi.absoluteFilePath());



              m->addSeparator();

            } else if (isClassFile(s)){
              a = m->addAction(/*_mainwindow::getPixmap(kbasicPath("ide/folder_red.png")),*/ s);
              connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
              exampleMapper->setMapping(a, fi.absoluteFilePath());

            } else if (isModuleFile(s)){
              a = m->addAction(/*_mainwindow::getPixmap(kbasicPath("ide/folder_violet.png")),*/ s);
              connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
              exampleMapper->setMapping(a, fi.absoluteFilePath());

            } else if (isFormFile(s)){
              a = m->addAction(/*_mainwindow::getPixmap(kbasicPath("ide/folder_yellow.png")), */s);
              connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
              exampleMapper->setMapping(a, fi.absoluteFilePath());
            
            } else if (isMenuBarFile(s)){
              a = m->addAction(/*_mainwindow::getPixmap(kbasicPath("ide/folder_grey.png")), */s);
              connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
              exampleMapper->setMapping(a, fi.absoluteFilePath());

            } else if (isToolBarFile(s)){
              a = m->addAction(/*_mainwindow::getPixmap(kbasicPath("ide/folder_grey.png")), */s);
              connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
              exampleMapper->setMapping(a, fi.absoluteFilePath());

            } else {
              a = m->addAction(/*_mainwindow::getPixmap(kbasicPath("ide/folder_grey.png")), */s);
              connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
              exampleMapper->setMapping(a, fi.absoluteFilePath());

            }
            
          } else {           
            QString e = fi.absoluteFilePath ();
           
            if (m == 0){
              m = m_orig;
            }
            
            a = m->addAction(s);
            connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
            exampleMapper->setMapping(a, fi.absoluteFilePath());

            if (isClassFile(s) || isModuleFile(s)){

              QString k = s.left(1).toUpper();

              if (!e.contains("TODO")){
                int gg = k.at(0).toLatin1();
                if (gg < 65 || gg > 65 + 26) gg = 26; else gg -= 65;
                
                a = abc[gg]->addAction(s);
                connect(a, SIGNAL(triggered()), exampleMapper, SLOT(map()));
                exampleMapper->setMapping(a, fi.absoluteFilePath());
                
              }
            }


          }

        }		    
	    }
  
  }    
}

void _mainwindow::openProjectListFile(QString s)
{
  if (isFormFile(s)){
    openForm(s);
  } else if (isTableFile(s)){
    openTable(s);
  } else if (isQueryFile(s)){
    openQuery(s);
  } else if (isClassFile(s)){
    openClass(s);
  } else if (isModuleFile(s)){
    openModule(s);
  } else if (isMenuBarFile(s)){
    openMenuBar(s);
  } else if (isToolBarFile(s)){
    openToolBar(s);
  } else if (isReportFile(s)){
    openReport(s);
  } else {

    if (s.endsWith(".jpg", Qt::CaseInsensitive) 
      || s.endsWith(".jpeg", Qt::CaseInsensitive) 
      || s.endsWith(".mng", Qt::CaseInsensitive) 
      || s.endsWith(".png", Qt::CaseInsensitive) 
      || s.endsWith(".bmp", Qt::CaseInsensitive) 
      || s.endsWith(".gif", Qt::CaseInsensitive)

      || s.endsWith(".pbm", Qt::CaseInsensitive)
      || s.endsWith(".pgm", Qt::CaseInsensitive)
      || s.endsWith(".ppm", Qt::CaseInsensitive)
      || s.endsWith(".xbm", Qt::CaseInsensitive)
      || s.endsWith(".xpm", Qt::CaseInsensitive)

      || s.endsWith(".svg", Qt::CaseInsensitive)
      || s.endsWith(".mid", Qt::CaseInsensitive)
      || s.endsWith(".midi", Qt::CaseInsensitive)

      || s.endsWith(".aiff", Qt::CaseInsensitive)
      || s.endsWith(".ogg", Qt::CaseInsensitive)
      || s.endsWith(".wav", Qt::CaseInsensitive)
      || s.endsWith(".mp4", Qt::CaseInsensitive)
      || s.endsWith(".mp3", Qt::CaseInsensitive)
      || s.endsWith(".mpg", Qt::CaseInsensitive)
      || s.endsWith(".mpeg", Qt::CaseInsensitive)
      || s.endsWith(".mov", Qt::CaseInsensitive)
      || s.endsWith(".avi", Qt::CaseInsensitive)
      || s.endsWith(".wmv", Qt::CaseInsensitive)
    ){
      QDesktopServices::openUrl(QUrl("file:///" + s));

    } else if (s.endsWith(".html", Qt::CaseInsensitive) 
      || s.endsWith(".htm", Qt::CaseInsensitive) 
    ){

      QDesktopServices::openUrl(QUrl("file:///" + s));
    } else {
      openOther(s);
    }
  }

}

void _mainwindow::openExampleFile(QString s)
{
  if (isProjectFile(s)){
    loadProject(s);
  } else {
    if (isOtherFile(s)){
      loadOther(s);
    } else if (isFormFile(s)){
      loadForm(s);
    } else {
      loadFile(s);
    }   
  }
}

QString _mainwindow::locale()
{
  QString s = EXTERN_my_mainwindow->getPreference("Language");

  if (s.length()){
    if (s == "English") return "";
    if (s == "German") return "de";
  }

  QLocale l;
  if (l.language() == QLocale::German) return "de";

  return "en";

}

void _mainwindow::performInsertTextInSourceCode(QString s)
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->performInsertText(s);
  }
}

bool _mainwindow::isPreferenceSet(QString s)
{
  QString k = preferences[QString(s).toUpper()];

  return k == "Yes";
}

QString _mainwindow::getPreference(QString sKey)
{
  return preferences[QString(sKey).toUpper()];
}

void _mainwindow::setPreference(QString sKey, QString sValue)
{
  preferences[QString(sKey).toUpper()] = sValue;
}

QString _mainwindow::getProjectPreference(QString sKey)
{
  return projectPreferences[QString(sKey).toUpper()];
}

void _mainwindow::setProjectPreference(QString sKey, QString sValue)
{
  projectPreferences[QString(sKey).toUpper()] = sValue;
}

void _mainwindow::setDefaultPreferences()
{

  // general
  preferences[QString("License").toUpper()] = "";
  preferences[QString("SplashScreen").toUpper()] = "Yes";
  //preferences[QString("BackgroundImages").toUpper()] = "Yes";
  preferences[QString("ThanksScreen").toUpper()] = "Yes";
  preferences[QString("QuickCommands").toUpper()] = "Yes";
  //preferences[QString("ExampleOnQuickCommands").toUpper()] = "Yes";
  //preferences[QString("MascotKonqui").toUpper()] = "Yes";
  //preferences[QString("MascotRunner").toUpper()] = "Yes";
  preferences[QString("GridInFormDesign").toUpper()] = "Yes";
  preferences[QString("KBasicScreenshot").toUpper()] = "Yes";
  preferences[QString("IntroductionHelp").toUpper()] = "Yes";
  preferences[QString("WelcomeScreen").toUpper()] = "Yes";
  preferences[QString("SearchBrowserAndHelpTips").toUpper()] = "Yes";
  preferences[QString("ImportantHelpIndex").toUpper()] = "Yes";
  preferences[QString("MascotTux").toUpper()] = "Yes";
  preferences[QString("MascotDevil").toUpper()] = "Yes";
  preferences[QString("HelpPropertyWindow").toUpper()] = "Yes";
  preferences[QString("BackImageInFormDesign").toUpper()] = "Yes";
  preferences[QString("StatusBar").toUpper()] = "Yes";
  preferences[QString("MenuIcon").toUpper()] = "Yes";  
  preferences[QString("CompileScreen").toUpper()] = "Yes";
  preferences[QString("ExamplesInMenu").toUpper()] = "Yes";  
  preferences[QString("EnableUnfinished").toUpper()] = "Yes";  
  preferences[QString("ShowColorizedIcon").toUpper()] = "Yes";  
  preferences[QString("ConsoleInfo").toUpper()] = "Yes";  
  preferences[QString("ShowTabBar").toUpper()] = "No";  
    
  preferences[QString("CachedCompilation").toUpper()] = "Yes";
  preferences[QString("LogFile").toUpper()] = "No";
  preferences[QString("PlaySound").toUpper()] = "Yes";
  preferences[QString("DefaultProject").toUpper()] = "";
  preferences[QString("DefaultFile").toUpper()] = "";  
  preferences[QString("Language").toUpper()] = "";
  
  // page1a
  preferences[QString("ShowQt").toUpper()] = "Yes";
  preferences[QString("ShowMySQL").toUpper()] = "Yes";

  // page2
  preferences[QString("ShowIconType").toUpper()] = "No";
  preferences[QString("UnderLineSubsFunctions").toUpper()] = "Yes";
  preferences[QString("HighlightCurrentCursorLine").toUpper()] = "Yes";
  preferences[QString("SyntaxHighlighting").toUpper()] = "Yes";
  preferences[QString("BookmarkPicture").toUpper()] = "Yes";
  preferences[QString("SubFunctionLines").toUpper()] = "Yes";
  preferences[QString("VariableRedOnDblClick").toUpper()] = "Yes";
  preferences[QString("FlashDebuggingMessage").toUpper()] = "Yes";
  preferences[QString("RedLineAter$END").toUpper()] = "Yes";
  preferences[QString("BreakpointPicture").toUpper()] = "Yes";
  preferences[QString("BackImageOnNewFile").toUpper()] = "Yes";
  preferences[QString("ConsoleDebugInfo").toUpper()] = "Yes";
  preferences[QString("SourcecodeBrowserImage").toUpper()] = "Yes";  
  preferences[QString("SourcecodeBrowserImage2").toUpper()] = "No";  
  

  preferences[QString("AutoInsert").toUpper()] = "Yes";
  preferences[QString("AutoCompletion").toUpper()] = "Yes";
  preferences[QString("AutoCorrection").toUpper()] = "Yes";

  // page3
  preferences[QString("Standard").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Keyword").toUpper()] = "Automatic|Automatic|bold";
  preferences[QString("Builtin Function").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Type").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Operator").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Symbol").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("String").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Comment").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Bookmark").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Breakpoint").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Debug Line").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Current Line").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Marked Line").toUpper()] = "Automatic|Automatic|normal";
  preferences[QString("Marked Comment").toUpper()] = "Automatic|Automatic|normal";
  
  // extern tools
  preferences[QString("ExternTool1").toUpper()] = "";
  preferences[QString("ExternTool2").toUpper()] = "";
  preferences[QString("ExternTool3").toUpper()] = "";
  preferences[QString("ExternTool4").toUpper()] = "";
  preferences[QString("ExternTool5").toUpper()] = "";

  // misc
  preferences[QString("FontName").toUpper()] = "Courier";
#ifdef MAC
  preferences[QString("FontSize").toUpper()] = "14"; // HIDE
#else
  preferences[QString("FontSize").toUpper()] = "12";
#endif

  // hidden

  preferences[QString("EDIT_TOOLBARS_FILE").toUpper()] = "Yes";
  preferences[QString("EDIT_TOOLBARS_RUN").toUpper()] = "Yes";
  preferences[QString("EDIT_TOOLBARS_EDIT").toUpper()] = "Yes";
  preferences[QString("EDIT_TOOLBARS_FORMAT").toUpper()] = "Yes";
  preferences[QString("EDIT_TOOLBARS_INSERT").toUpper()] = "Yes";
  preferences[QString("EDIT_TOOLBARS_HELP").toUpper()] = "Yes";  
}

bool _mainwindow::selfTest(QString sPath)
{  
  static bool bFirstTime = true;
  static QString sLastSelfTest = "";

  if (!bFirstTime && sLastSelfTest == ""){
    _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      sLastSelfTest = o->getFilename();
    }
  }
  bFirstTime = false;

  QDir thisDir( sPath );	
  QFileInfoList files = thisDir.entryInfoList();

  if ( files.size() ) {

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i) {
     fi = files.at(i);

		    if (fi.fileName() == "." || fi.fileName() == "..")
		        ; // nothing
		    else if ( fi.isSymLink()) {
		    }
        else if ( fi.isDir() ){
          //int n = ++nExampleFileCounter;

          if (!selfTest(sPath + "/" + fi.fileName())) return false;

        } else {

          QString s = fi.fileName();
          QString s2 = fi.absolutePath();
          QString s3 = s2 + "/" + s;

          if (isProjectDir(s2)){ 
             // ignore projects
          } else {    

            if (!s2.contains("todo", Qt::CaseInsensitive) && !s2.contains("shortcut", Qt::CaseInsensitive)){ // einstiegspunkt festlegen

              if (sLastSelfTest.length() == 0 || sLastSelfTest == s3){
                if (sLastSelfTest == s3) sLastSelfTest = "";

                if (isClassFile(s)){
                    openClass(s3);
                    if (!event_RUN_BUILD()){
                      sLastSelfTest = s3;
                      return false;
                    }
                    workspace->closeActiveSubWindow();
                }

                if (isModuleFile(s)){
                    openModule(s3);
                    if (!event_RUN_BUILD()){
                      sLastSelfTest = s3;
                      return false;
                    }
                    workspace->closeActiveSubWindow();
                }
              }
            }

          }

        }		    
	    }

  }      

 
  return true;
  

  return false;

}

bool _mainwindow::copyDir (const QString& from, const QString& to)
{
  QDir d;
  d.mkpath(to);

  QDir thisDir( from );	
  QFileInfoList files = thisDir.entryInfoList();

  if ( files.size() ) {

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i) {
      fi = files.at(i);

      QString ss = fi.absoluteFilePath();

		  if (fi.fileName() == "." || fi.fileName() == ".."){
		      ; // nothing
		  } else if ( fi.isSymLink()){
          ; // nothing
		  } else if ( fi.isDir() ){

        if (!copyDir(fi.absoluteFilePath(), to + "/" + fi.fileName())) return false;

      } else {

        if (!copyFile(fi.absoluteFilePath(), to + "/" + fi.fileName())) return false;

      }		    
	}
  
  }    
  return true;
}

bool _mainwindow::copyFile (const QString& from, const QString& to)
{
  

  QFile file(from);
  //if (!file.open( IO_ReadOnly | IO_Raw  )) return false;
  //QDataStream stream( &file );

  QFile file2(to);
  bool b = file2.remove();

  return file.copy(to);

} 

bool _mainwindow::deleteFile (const QString& from)
{
  QFile file(from);
  return file.remove();
} 


bool _mainwindow::createDir (const QString& from)
{
  QDir f;  

  return f.mkdir(from);
} 

bool _mainwindow::createFile (const QString& from, QString sText)
{
  QFile f(from);

  if (!f.open(QFile::WriteOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(from));
    return false;
  }

  if (!sText.isEmpty()){
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << sText;
  }

  f.close();

  return true;
} 

bool _mainwindow::renameFile (const QString& from, const QString& to)
{
  if (copyFile(from, to)){
    if (deleteFile(from)){
      return true;
    }
  }
  return false;
} 


bool _mainwindow::processGUI()
{
  qApp->processEvents();
  return true;
}

bool _mainwindow::processGUI(int msec)
{
  qApp->processEvents(QEventLoop::AllEvents, msec);
  return true;
}

void _mainwindow::interruptDebugAtBreakpoint(QString file, int line)
{
 
}

void _mainwindow::clearLocal()
{
  
}

void _mainwindow::addLocal(QString sName, QString sType, QString sValue)
{

}

void _mainwindow::clearGlobal()
{
 
}

void _mainwindow::addGlobal(QString sName, QString sType, QString sValue)
{
}

void _mainwindow::clearStack()
{
  
}

void _mainwindow::addStack(QString sName)
{
 
}

bool _mainwindow::pasteFile()
{
  bool bCut = sCopy.length() == 0 && sCut.length();

  QTreeWidgetItem *l = 0;
  QString s = "";
  QString k = "";
  QString z = bCut ? sCut : sCopy;

  if (z.contains(".kbasic_class")){
    l = _class2;
    s = "class";      
    k = "ide/PROJECT_NEW_CLASS.png";
  } else if (z.contains(".kbasic_module")){
    l = _module2;
    s = "module";      
    k = "";
  } else if (z.contains(".kbasic_form")){
    l = _form2;
    s = "form";      
    k = "ide/PROJECT_NEW_FORM.png";
  } else if (z.contains(".kbasic_report")){
    l = _report2;
    s = "report";      
    k = "";
  } else if (z.contains(".kbasic_menubar")){
    l = _menubar2;
    s = "menubar";      
    k = "";
  } else if (z.contains(".kbasic_toolbar")){
    l = _toolbar2;
    s = "toolbar";      
    k = "";
/*
    // OBJECT
  } else if (sCopy.contains(".kbasic_file")){
    l = _file;
    s = "file";      
    k = "ide/empty.png";
*/
  } else if (z.contains(".kbasic")){
    l = _module2;
    s = "module";      
    k = "";
  } else {
    l = _other2;
    s = "file";      
    k = "";
  }
  int i = 1;
re:
  i++;
  QString ss = "";
  if (i) ss.sprintf("%d", i);  bool b;
  QString c = getFilenamePath(z) + "/" + getFilenameWithoutPathAndExtension(z) + ss + "." + getFilenameExtension(z);

  bool bTable = false;

  if (z.endsWith(".kbasic_class", Qt::CaseInsensitive)){
    if (existsClassFile(c)) goto re;

  } else if (z.endsWith(".kbasic_module", Qt::CaseInsensitive)){
    if (existsModuleFile(c)) goto re;
  } else if (z.endsWith(".kbasic", Qt::CaseInsensitive)){
    if (existsModuleFile(c)) goto re;

  } else if (z.endsWith(".kbasic_form", Qt::CaseInsensitive)){
    if (existsFormFile(c)) goto re;

  } else if (z.endsWith(".kbasic_report", Qt::CaseInsensitive)){
    if (existsReportFile(c)) goto re;

  } else if (z.endsWith(".kbasic_table", Qt::CaseInsensitive)){
    if (existsTableFile(c)) goto re;
    bTable = true;

  } else if (z.endsWith(".kbasic_query", Qt::CaseInsensitive)){
    if (existsQueryFile(c)) goto re;

  } else if (z.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){
    if (existsMenuBarFile(c)) goto re;

  } else if (z.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){
    if (existsToolBarFile(c)) goto re;
  } else {
    if (existsOtherFile(c)) goto re;
  }      
goo:
  QString text = QInputDialog::getText(this, tr("Copy ") + s + ": '" + getFilenameWithoutPath(sCopy) + "'", tr("Enter the ") + s + tr(" name of the copy:"), QLineEdit::Normal, getFilenameWithoutPathAndExtension(c), &b);
  if (!text.contains("/") && !text.contains("\\")){
    c = getFilenamePath(z) + "/" + text + "." + getFilenameExtension(z);
  } else {
    c = text;
  }
  if (b && !text.isEmpty()){

    if (!checkObjectName(text)) goto goo;

    if (QFile::exists(c)){
      QMessageBox::information(this, MYAPP, QString("Could not create %1, because it already exists.").arg(getFilenameWithoutPath(c)));
      return false;
    }
    copyFile(z, c);

    if (bTable){
      QString sSource = getFilenameWithoutPathAndExtension(z);
      QString sDestination = getFilenameWithoutPathAndExtension(c);

      _table o; 
      QStringList l = o.load(z, true);

      bool bSQLite = false;
      bool bMySQL = false;
      if (CurrentDatabase.driverName().contains("sqlite", Qt::CaseInsensitive)){
        bSQLite = true;
      } else if (CurrentDatabase.driverName().contains("mysql", Qt::CaseInsensitive)){
        bMySQL = true;
      }
       QSqlQuery rr;

       s = "DROP TABLE " + sDestination + ";";
       if (!rr.exec(s)){ 
       }

       QSqlQuery r;
       QString s = "SELECT * FROM " + sSource;
       if (r.exec(s)){

          if (r.first()){

            QString sFields = "";            
            QString sDesc = "";

            QSqlRecord a = r.record();

            int n = a.count();

            for (int i = 0; i < n; i++){
              if (i > 0) sFields += ", ";
              sFields += a.fieldName(i);
               
              QSqlField f = a.field(i);

              QString value = "";

              switch(f.type()){
                case QVariant::Bool:
                  value = "boolean";
                  break;
                case QVariant::Date: 
                  value = "date";
                  break;
                case QVariant::Time: 
                  value = "time";
                  break;
                case QVariant::Double:
                  value = "float";
                  break;
                case QVariant::Int:
                  value = "integer";
                  break;
                case QVariant::String: 
                  value = "text";
                  break;
                default:
                  value = "text";
                  break;
              }

              QString sNotNull = "";

              for (int y = 0; y < l.size(); y++){
                if (l.at(y) == a.fieldName(i)){
                  sNotNull = l.at(y + 3);
                  if (sNotNull.isEmpty()) sNotNull = "NOT NULL";
                }
              }             

              if (a.fieldName(i) != "kbrecordid") sDesc += a.fieldName(i) + " " + value + ",\n";
            }

            s = "CREATE TABLE " + sDestination + " (\n" + sDesc;
            s += "\nkbrecordid int NOT NULL,\nCONSTRAINT " + sDestination + "_kbrecordid PRIMARY KEY (kbrecordid)\n);";
            if (!rr.exec(s)){ QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + rr.lastError().text()); goto re2; }
            
            if (bSQLite){
              s = "CREATE INDEX " + sDestination + "_idx_kbrecordid ON " + sDestination + " (kbrecordid);";
            } else if (bMySQL){
              s = "CREATE INDEX " + sDestination + "_idx_kbrecordid USING btree ON " + sDestination + " (kbrecordid);";
            } else {
              s = "CREATE INDEX " + sDestination + "_idx_kbrecordid ON " + sDestination + " USING btree (kbrecordid);";
            }
            if (!rr.exec(s)){ QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + rr.lastError().text()); goto re2; }

            for (int y = 0; y < l.size(); y += 4){ 
              QString sIndex = l.at(y + 2);

              if (!sIndex.isEmpty()){

                if (bSQLite){
                  s = "CREATE INDEX " + sDestination + "_idx_" + l.at(y + 0) + " ON " + sDestination + " (" + l.at(y + 0) + ");";
                } else if (bMySQL){
                  s = "CREATE INDEX " + sDestination + "_idx_kbrecordid USING btree ON " + sDestination + " (kbrecordid);";
                } else {
                  s = "CREATE INDEX " + sDestination + "_idx_" + l.at(y + 0) + " ON " + sDestination + " USING btree (" + l.at(y + 0) + ");";
                }
                if (!rr.exec(s)){ QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + rr.lastError().text()); goto re2; }

              }
            }


            do {
              a = r.record();

              QString sValues = "";

              for (int i = 0; i < n; i++){
                QVariant f = a.value(i);
                QString value = f.toString();

                switch(f.type()){
                  case QVariant::Bool:
                    if (value.isEmpty()) value = "NULL";
                    break;
                  case QVariant::Date: 
                    if (value.isEmpty()) value = "NULL"; else value = "'" + value + "'";
                    break;
                  case QVariant::Time: 
                    if (value.isEmpty()) value = "NULL"; else value = "'" + value + "'";
                    break;
                  case QVariant::Double:
                    if (value.isEmpty()) value = "0"; else value = value;
                    break;
                  case QVariant::Int:
                    if (value.isEmpty()) value = "0"; else value = value;
                    break;
                  case QVariant::String: 
                    if (value.isEmpty()) value = "NULL"; else value = "'" + value + "'";
                    break;
                  default:
                    if (value.isEmpty()) value = "NULL"; else value = value;
                    break;
                }

                if (i > 0) sValues += ", ";
                sValues += value;
              }

              s = "INSERT INTO " + sDestination + "(" + sFields + ") VALUES (" + sValues + ");";
              if (!rr.exec(s)){ QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + rr.lastError().text()); goto re2; }

            } while (r.next());
          }
        }

       }

re2:
    EXTERN_my_projectwindow->refresh();


  }

  return true;
}

bool _mainwindow::deleteFile()
{
  QTreeWidgetItem *l = 0;

  if (tree->hasFocus()){
    l = tree->currentItem();
  } else return false;

  QString s = l->text(0);

  if (QMessageBox::question(
      this, tr("Delete file"),   
      tr("Delete file ") + s + "?",
      QMessageBox::Ok,
      QMessageBox::Cancel 
      
      ) == QMessageBox::Ok )
  {
  
    deleteFile (l->text(1));
    if (l->text(1).endsWith(".kbasic_table", Qt::CaseInsensitive)){
      QSqlQuery r;
       s = "DROP TABLE " + getFilenameWithoutPathAndExtension(l->text(1)) + ";";
       if (!r.exec(s)){ 
       //  QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s); 
       }
    }
    EXTERN_my_projectwindow->refresh();
    
  }
  
  return true;
}

void _mainwindow::ci_parse(QString sFilename, QString sText)
{
  
  {
    ci[sFilename].parse(sFilename, sText);
    ci_bUpdatedAs = true;
    ci_bUpdatedDot = true;
    ci_bUpdatedDotMethod = true;
    
    EXTERN_my_parserwindow->refresh(sFilename);
  }
}

QList<_inputtip_info> ci_listAs;
QList<_inputtip_info> _mainwindow::ci_getAsForFile(QString sForFile, QString sScope)
{

  if (ci_bUpdatedAs){ 
    ci_listAs.clear();

    foreach (_inputtip_parser v, ci)
    { 
      ci_listAs += v.getAsForFile(sForFile, sScope);
    }
  }

  ci_bUpdatedAs = false;

  return ci_listAs;
}

QList<_inputtip_info> ci_listEvents;
QList<_inputtip_info> _mainwindow::ci_getEventsForClass(QString sControlType)
{  
  ci_listEvents.clear();

  foreach (_inputtip_parser v, ci)
  { 
    ci_listEvents += v.framework_getEventsForClass(sControlType);
    break;
  }

  return ci_listEvents;
}

QList<_inputtip_info> ci_listDot;
QList<_inputtip_info> _mainwindow::ci_getDotForFile(QString sForFile, QString sScope, QString sScope2, QString sDot)
{  

  if (ci_bUpdatedDot){ 
    ci_listDot.clear();

    bool b = true;
    foreach (_inputtip_parser v, ci)
    { 
      qApp->processEvents(QEventLoop::AllEvents, 100);

      ci_listDot += v.getDotForFile(sForFile, sScope, sScope2, sDot);
      if (b){
        b = false;
        if (sDot != "999") ci_listDot += v.framework_getDotForFile("777", "", sDot);
      }
    }
    
  }

  ci_bUpdatedDot = false;  

  return ci_listDot;
}

QList<_inputtip_info> ci_listDotMethod;
QList<_inputtip_info> _mainwindow::ci_getDotMethodForFile(QString sForFile, QString sScope, QString sScope2, QString sDot)
{

  if (ci_bUpdatedDotMethod){ 
    ci_listDotMethod.clear();

    foreach (_inputtip_parser v, ci)
    { 
      ci_listDotMethod += v.getDotMethodForFile(sForFile, sScope, sScope2, sDot);
    }
  }

  ci_bUpdatedDotMethod = false;

  return ci_listDotMethod;
}

QList<_inputtip_info> ci_listFindDefinition;
QList<_inputtip_info> _mainwindow::ci_getFindDefinition(QString sForFile, QString sScope, QString sScope2, QString sDot, QString sBeforeDot)
{
  
  ci_listFindDefinition.clear();

  foreach (_inputtip_parser v, ci)
  { 
    ci_listFindDefinition += v.getFindDefinition(sForFile, sScope, sScope2, sDot, sBeforeDot);
  }

  return ci_listFindDefinition;
}

QList<_inputtip_info> _mainwindow::ci_getAllForFile(QString sForFile)
{
  if (ci.contains(sForFile)){
    return ci[sForFile].getAllForFile(sForFile);
  }
  static QList<_inputtip_info> l;
  return l;
}

QString _mainwindow::getForF1(QString sDot, QString sDot2)
{
  foreach (_inputtip_parser v, ci)
  { 
    QString s = v.getForF1(sDot, sDot2);
    if (!s.isEmpty()) return s;
  }
  return "";
}
bool _mainwindow::showError(QString _sFile, int _nLine, QString _sError)
{  
  if (_sError.contains("is still in use, all queries", Qt::CaseInsensitive)) return false; // WORKAROUND
  if (_sError.contains("could not parse application", Qt::CaseInsensitive)) return false; // WORKAROUND
  if (_sError.contains("saveState", Qt::CaseInsensitive)) return false; // WORKAROUND
  if (_sError.contains("restoreState", Qt::CaseInsensitive)) return false; // WORKAROUND
  if (_sError.contains("QWidget::setMinimumSize", Qt::CaseInsensitive)) return false; // WORKAROUND
 
  _sourcecodeeditor *o = 0;
 
  
  // close opened screen
  foreach (QWidget *w, QApplication::allWidgets()){
    if (w->objectName() == "Console"){
      w->hide();
      w->close();
      qApp->processEvents();
      break;
    }
  }

  bool b = EXTERN_my_mainwindow->isActiveWindow();

  QWidget *w = qobject_cast<QWidget*>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (w){
    w->activateWindow();
    w->setFocus();
  }

  if (_sFile.endsWith(".kbasic_class", Qt::CaseInsensitive)){
    openClass(_sFile);

  } else if (_sFile.endsWith(".kbasic_form", Qt::CaseInsensitive)){        
    openFormClassSourceCode(_sFile);

  } else if (_sFile.endsWith(".kbasic_report", Qt::CaseInsensitive)){        
    openFormClassSourceCode(_sFile);

  } else if (_sFile.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){        
    openMenuBarClassSourceCode(_sFile);

  } else if (_sFile.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){        
    openToolBarClassSourceCode(_sFile);

  } else if (_sFile.endsWith(".kbasic", Qt::CaseInsensitive) || _sFile.endsWith(".kbasic_module", Qt::CaseInsensitive)){
    openModule(_sFile);
  } else {
    goto o;
  }

  o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QString k = o->my_sourcecodeeditor_editor->toPlainText();
    int n = k.count("\n");
    if (n < _nLine){
    } else {
      o->setCurrentLineAndSelectLine(_nLine);
    }
  }
o:

  if (!_sError.isEmpty()){
    if (_sFile.isEmpty()){
     
      if (!b){
        if (trayIcon == 0){
          trayIcon = new QSystemTrayIcon(this);
          connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIcon_activated));
        }
        trayIcon->setIcon(kbasicIcon(kbasicPath("ide/kbasic_icon.jpg")));
        trayIcon->show();
        trayIcon->showMessage(tr("Error"), _sError);   
      } else if (trayIcon){
        trayIcon->hide();
      }

      statusBar()->setHidden(false);
      statusBar()->showMessage(_sError + " in " + EXTERN_my_mainwindow->getFilenameWithoutPath(_sFile));
      QMessageBox::warning(this, tr("Error"), _sError);

    } else {

      if (!b){
        if (trayIcon == 0){
          trayIcon = new QSystemTrayIcon(this);
          connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIcon_activated(void)));
          connect(trayIcon, SIGNAL(messageClicked(void)), this, SLOT(trayIcon_activated(void)));
        }
        trayIcon->setIcon(kbasicIcon(kbasicPath("ide/kbasic_icon.jpg")));
        trayIcon->show();
        trayIcon->showMessage(_sError, QString() + tr("Error in ") + _sFile);
      } else if (trayIcon){
        trayIcon->hide();
      }

      EXTERN_sError = _sError + " in " + EXTERN_my_mainwindow->getFilenameWithoutPath(_sFile);
      QMessageBox::warning(this, QString() + tr("Error in ") + _sFile, _sError);
    }  
  }

  return true;
}

bool _mainwindow::showDebug(QString _sFile, int _nLine)
{  

  // close opened screen
  foreach (QWidget *w, QApplication::allWidgets()){
    if (w->objectName() == "Console"){
      w->hide();
      w->close();
      qApp->processEvents();
      break;
    }
  }

  QWidget *w = qobject_cast<QWidget*>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (w){
    w->activateWindow();
    w->setFocus();
  }

  if (_sFile.endsWith(".kbasic_class", Qt::CaseInsensitive)){
    openClass(_sFile);

  } else if (_sFile.endsWith(".kbasic_form", Qt::CaseInsensitive)){        
    openFormClassSourceCode(_sFile);

  } else if (_sFile.endsWith(".kbasic_report", Qt::CaseInsensitive)){        
    openFormClassSourceCode(_sFile);

  } else if (_sFile.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){        
    openMenuBarClassSourceCode(_sFile);

  } else if (_sFile.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){        
    openToolBarClassSourceCode(_sFile);

  } else if (_sFile.endsWith(".kbasic", Qt::CaseInsensitive) || _sFile.endsWith(".kbasic_module", Qt::CaseInsensitive)){
    openModule(_sFile);
  }

  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    int n = 0;
    QString s = o->getFilename();

    if (
      s.endsWith(".kbasic_form", Qt::CaseInsensitive) 
      || s.endsWith(".kbasic_report", Qt::CaseInsensitive) 
      || s.endsWith(".kbasic_menubar", Qt::CaseInsensitive) 
      || s.endsWith(".kbasic_toolbar", Qt::CaseInsensitive) 
      ) n = 1; // set the correct line numbers for sources extended by the compiler

    o->setCurrentLineAndSelectLine(_nLine - n);
  }

  return true;
}

void _mainwindow::gotoFileLine(QString sFile, int nLine)
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QString s = sFile;
    if (s != o->getFilename()){
      if (s.endsWith(".kbasic_class", Qt::CaseInsensitive)) openClass(s);
      else if (s.endsWith(".kbasic_module", Qt::CaseInsensitive)) openModule(s);
      else if (s.endsWith(".kbasic_form", Qt::CaseInsensitive)) openFormClassSourceCode(s);        
      else if (s.endsWith(".kbasic_report", Qt::CaseInsensitive)) openFormClassSourceCode(s);        
      else if (s.endsWith(".kbasic_menubar", Qt::CaseInsensitive)) openMenuBarClassSourceCode(s);        
      else if (s.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)) openToolBarClassSourceCode(s);        
      else if (s.endsWith(".kbasic", Qt::CaseInsensitive)) openModule(s);
      
      _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
      if (o){
        o->setCurrentLineAndSelectLine(nLine);
      }
    } else {
      o->setCurrentLineAndSelectLine(nLine);
    }
    
  }
  
}

void _mainwindow::trayIcon_activated()
{
  EXTERN_my_mainwindow->activateWindow();
  EXTERN_my_mainwindow->show();
  trayIcon->hide();
}

bool _mainwindow::saveStringInFile(QString sFile, QString s)
{
  QFile f(sFile);
  if (!f.open(QIODevice::WriteOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(sFile));
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << s;
    f.close(); 
    return true;
  }
  return false;
}

bool _mainwindow::loadStringFromFile(QString sFile, QString &s)
{
  QFile f(sFile);
  if (!f.open(QIODevice::ReadOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(sFile));
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s = s.replace("\r", "");
    f.close();
    return true;
  }
  return false;
}

QString _mainwindow::trFilename(QString s)
{
  if (sCurrentLanguage.isEmpty()) return s;

  int i = s.lastIndexOf('.');

  s = s.insert(i, "." + sCurrentLanguage);

  return s;
}