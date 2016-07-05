
/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.

KBasic Software offers the source code for non-open source projects of the GUI and VM 
running on Windows, Mac and Linux. Namely IDE, form designer, toolbox, property window, 
menubar designer, toolbar designer, source code editor with syntax highlighting, code completion, 
bookmarks, breakpoints, source code browser, builtin help and project window for a low price. 

Please do not hesitate to contact KBasic Software: info@kbasic.com
***************************************************************************
*/

#include <QtGui>
#include <QtSql>

#include "_mainwindow.h"
#include "_projectwindow.h"

#include "../kbshared/_browser.h"


#include "../kbshared/_strings.h"
#include "../kbshared/_editor.h"
#include "../kbshared/_property.h"

#include "_helpwindow_shortcut.h"


extern QString sKBasicPath;


int MAIN_argc;
char **MAIN_argv;


bool bDebug; 


extern _mainwindow *EXTERN_my_mainwindow;
extern _projectwindow *EXTERN_my_projectwindow;

bool checkObjectName(QString s)
{
  QString ss = s;
  QString m = "";
  QChar c;
  
  if (s.isEmpty()){ m = QObject::tr("It contains no text."); goto re; }
  if (s.contains(" ")){ m = QObject::tr("It contains a space character."); goto re; }
  c = s.at(0);

  if (c.isMark() || c.isNumber() || c.isDigit() || c.isNumber() || c.isPunct() || c.isSymbol()){ m = QObject::tr("It starts with a forbidden character."); goto re; }

  s = s.mid(1);
  
  if (
    s.contains(",") || 
    s.contains(";") || 
    s.contains(":") || 
    s.contains("´") || 
    s.contains("`") || 
    s.contains("'") || 
    s.contains("#'") || 
    s.contains("|") || 
    s.contains("<") || 
    s.contains(">") || 
    s.contains("+") || 
    s.contains("-") || 
    s.contains("/") || 
    s.contains("*") || 
    s.contains("\\") || 
    s.contains("!") || 
    s.contains("\"") || 
    s.contains("§") || 
    s.contains("$") || 
    s.contains("%") || 
    s.contains("&") || 
    s.contains("~") || 
    s.contains("^") || 
    s.contains("°") || 
    s.contains("(") || 
    s.contains(")") || 
    s.contains("{") || 
    s.contains("}") || 
    s.contains("[") || 
    s.contains("]") || 
    s.contains("=") 
    ){ m = QObject::tr("It contains a forbidden non-text character."); goto re; }

    //toUtf8 
    //check auf ascii codes keine umlaute
  return true;
re:
  QString z = "'";
  z += ss;
  z += QObject::tr("' is named in a wrong way. ");
  z += m;
  QMessageBox::information(qApp->activeWindow(), QObject::tr("Error in naming objects"),  z);
  return false;
}

QString kbcPath(QString s)
{
  QString k = sKBasicPath + "/" + s; 
#ifdef WINDOWS
  k.replace("kbide", bDebug ? "kbc/Debug" : "kbc"); // HIDE
  k.replace("/", "\\"); // HIDE
#endif
  return k;
}

QString runPath(QString s)
{
  QString k = sKBasicPath + "/" + s; 
#ifdef WINDOWS
  k.replace("kbide", bDebug ? "kbrun/Debug" : "kbrun"); // HIDE
  k.replace("/", "\\"); // HIDE
#endif
  return k;
}


QString idePath(QString s)
{
  QString k = sKBasicPath + "/ide/" + s; 
#ifdef WINDOWS
  k.replace("/", "\\"); // HIDE
#endif
  return k;
}

QString kbasicControlPath(QString s)
{
#ifdef MAC
  QString k = sKBasicPath + "/ide/controls/mac/" + s;  // HIDE
#else
#ifdef WINDOWS
  QString k = sKBasicPath + "/ide/controls/windows/" + s;  // HIDE
  k.replace("/", "\\"); // HIDE
#else
  QString k = sKBasicPath + "/ide/controls/linux/" + s; 
#endif
#endif
  return k;
}

QString kbasicControlVistaPath(QString s)
{
#ifdef MAC
  QString k = sKBasicPath + "/ide/controls/vista/" + s;  // HIDE
#else
#ifdef WINDOWS
  QString k = sKBasicPath + "/ide/controls/vista/" + s;  // HIDE
  k.replace("/", "\\"); // HIDE
#else
  QString k = sKBasicPath + "/ide/controls/vista/" + s; 
#endif
#endif
  return k;
}

QString kbasicControlLeopardPath(QString s)
{
#ifdef MAC
  QString k = sKBasicPath + "/ide/controls/leopard/" + s;  // HIDE
#else
#ifdef WINDOWS
  QString k = sKBasicPath + "/ide/controls/leopard/" + s;  // HIDE
  k.replace("/", "\\"); // HIDE
#else
  QString k = sKBasicPath + "/ide/controls/leopard/" + s; 
#endif
#endif
  return k;
}

QString cachePath(QString s)
{
  QString k = sKBasicPath + "/ide/cache/" + s; 
#ifdef WINDOWS
  k.replace("/", "\\"); // HIDE
#endif
  return k;
}

QString kbasicPath(QString s)
{
  
  //if (sKBasicPath.isNull()) sKBasicPath = "c:\\kbasic16";
  QString k = sKBasicPath + "/"+ s; 
 
  //k = k.replace("\\", "/");
  
  //QMessageBox::information(0, "", k);
#ifdef WINDOWS
  k.replace("/", "\\"); // HIDE
#endif

  return k;
}

#ifdef MAC
QString contentsPath(QString s) // HIDE
{ // HIDE
  QString k = sKBasicPath; // HIDE
  int n = k.lastIndexOf("/"); // HIDE
  if (n >= 0){ // HIDE
    k = k.left(n); // HIDE
  } // HIDE
  return k + "/" + s; // HIDE
} // HIDE
#endif

const QIcon &kbasicIcon(QString s)
{
  static QMap<QString, QIcon>px;

  if (px.contains(s)) return px[s];

  px[s] = QIcon(s);
  return px[s];  
}


void copy_controlimage(QString s)
{
  QString sPath = EXTERN_my_mainwindow->getProjectPath();
  sPath += "/";
  sPath += EXTERN_my_mainwindow->getFilenameWithoutPath(s);

  EXTERN_my_mainwindow->copyFile(kbasicControlVistaPath(s), sPath);
  EXTERN_my_projectwindow->refresh();
}


/*
void doKBasic_docu()
{
	_docu_kbasic *kd = new _docu_kbasic();

  kd->generateAll();
  
	delete kd;
}*/

/*
void doKBasicBook_docu()
{
	_docu_kbasicbook *kd = new _docu_kbasicbook();

  kd->generateAll();
  
	delete kd;
}

void doSyntax_docu()
{
	_docu_syntax *kd = new _docu_syntax();

  kd->generateAll();
  
	delete kd;
}*/






 //#include "main.moc"

int kbasic_ui()
{

  QApplication a(MAIN_argc, MAIN_argv);

  qApp->addLibraryPath(qApp->applicationDirPath() + "/plugins");

    //  QMessageBox::information(0, MYAPP, "You need to run KBasic in adminstrator mode on Windows Vista.\nRight click on kbide.exe and select 'Run as adminstrator'. Start KBasic again.");

#ifdef WINDOWS
  if (QFile::exists(kbasicPath("ide/kbasic.config"))){ // HIDE
    QFile f("ide/kbasic.config"); // HIDE
    if (!f.open(QIODevice::WriteOnly)){ // HIDE
      QMessageBox::information(0, MYAPP, "Write access for kbasic directory failed.\n\nYou need to run KBasic in adminstrator mode on Windows Vista.\nRight click on kbide.exe (your application folder/kbasic/kbide.exe)\n and select 'Run as adminstrator'. Start KBasic again."); // HIDE
    } else {
    }
  }
#endif

  sKBasicPath = a.applicationDirPath();


  bDebug = false;
#ifdef WINDOWS
  bDebug = sKBasicPath.contains("Debug"); // HIDE
  sKBasicPath = sKBasicPath.replace("/Debug", "", Qt::CaseInsensitive); // WINDOWS // HIDE
  sKBasicPath = sKBasicPath.replace("/Release", "", Qt::CaseInsensitive); // WINDOWS // HIDE

#endif

  sKBasicPath = sKBasicPath.replace("\\", "/");


  

#ifdef WINDOWS
  if (bDebug){
  } else {
    sKBasicPath = sKBasicPath.replace("kbide/", ""); // HIDE
  }
#endif

  QString s = sKBasicPath + "/plugins";

  qApp->addLibraryPath(s);

  
  //QMessageBox::information(0, "QLibraryInfo::buildKey", QLibraryInfo::buildKey());
  /*
#ifdef WINDOWS
  //s = s.replace("/", "\\");

  QPluginLoader loader(s + "/imageformats/qgif4.dll");
  bool bbb = loader.load();
  QObject *plugin = loader.instance();

  //QPluginLoader::QPluginLoader ("qgif4.dll");
  if (plugin == 0){
    QMessageBox::information(0, s + "/imageformats/qgifd4.dll", loader.errorString ());
  }

#endif
 */

//QMessageBox::information(0, "KBasic Software", sKBasicPath);

  QSplashScreen *splash = 0;

  splash = new QSplashScreen(QPixmap( kbasicPath("ide/splash_professional.png")) );
  if (splash) splash->show();

  _mainwindow w(&a, splash);

  if (splash) splash->finish(&w);

  if (splash) delete splash;

  w.showMaximized();
  w.loadDefaultFiles();
  



  int nn = a.exec();


  return nn;

}

int main(int argc, char *argv[])
{


	MAIN_argc = argc;
	MAIN_argv = argv;


  return kbasic_ui();

}

