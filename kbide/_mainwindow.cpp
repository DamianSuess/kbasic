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

#include "_mainwindow.h"

#include "_importproject.h"



#include "_toolboxwindow_form.h"
#include "_toolboxwindow_vista.h"
#include "_toolboxwindow_leopard.h"
#include "_toolboxwindow_menubar.h"
#include "_toolboxwindow_toolbar.h"
//#include "_toolboxwindow_sql.h"
#include "_toolboxwindow_report.h"

#include "_helpwindow_shortcut.h"

#include "_projectwindow.h"
#include "_propertywindow.h"
#include "_parserwindow.h"
#include "_qbe_tables.h"






#include "_findfilelist.h"
#include "_replacefilelist.h"
#include "_quickcode.h"

#include "_globallist.h"
#include "_locallist.h"
#include "_stacklist.h"

#include "_sourcecodeeditor.h"

#include "../kbshared/_table.h"
//#include "_query.h"
#include "../kbshared/_form.h"
#include "../kbshared/_report.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"

//#include "_screen.h"
#include "../kbshared/_log.h"
#include "_infoconsole.h"
#include "_welcome.h"
#include "_qbe.h"
#include "_preferences.h"
#include "_resources.h"
#include "_help.h"

#ifdef WINDOWS
#include "QtDotNetStyle.h"
#endif

extern _sourcecodeeditor *EXTERN_my_sourcecodeeditor;


extern QSqlDatabase CurrentDatabase;

extern bool bRersourcesAreSelected;

_helpwindow_shortcut *EXTERN_my_helpwindow_shortcut;
_mainwindow *EXTERN_my_mainwindow;
_propertywindow *EXTERN_my_propertywindow;
_projectwindow *EXTERN_my_projectwindow;
_parserwindow *EXTERN_my_parserwindow;
//_helpwindow *EXTERN_my_helpwindow;

_toolboxwindow_form *EXTERN_toolboxwindow_form;
_toolboxwindow_vista *EXTERN_toolboxwindow_vista;
_toolboxwindow_leopard *EXTERN_toolboxwindow_leopard;
_toolboxwindow_menubar *EXTERN_toolboxwindow_menubar;
_toolboxwindow_toolbar *EXTERN_toolboxwindow_toolbar;
//_toolboxwindow_sql *EXTERN_toolboxwindow_sql;
_toolboxwindow_report *EXTERN_toolboxwindow_report;
_qbe_tables *EXTERN_qbe_tables;

_findfilelist *EXTERN_findfilelist;
_replacefilelist *EXTERN_replacefilelist;

QDockWidget *EXTERN_HelpWindow;
QDockWidget *EXTERN_ParserWindow;
QDockWidget *EXTERN_PropertyWindow;
QDockWidget *EXTERN_ProjectWindow;

QDockWidget *EXTERN_ToolboxForm;
QDockWidget *EXTERN_ToolboxMenuBar;
QDockWidget *EXTERN_ToolboxToolBar;
QDockWidget *EXTERN_ToolboxSql;
QDockWidget *EXTERN_ToolboxReport;
QDockWidget *EXTERN_DatabaseTables;

_quickcode *EXTERN_quickcode;

_globallist *EXTERN_globallist;
QDockWidget *EXTERN_Global;

_stacklist *EXTERN_stacklist;
QDockWidget *EXTERN_Stack;

_locallist *EXTERN_locallist;
QDockWidget *EXTERN_Local;

_melist *EXTERN_melist;
QDockWidget *EXTERN_Me;

QDockWidget *EXTERN_FileFind;
QDockWidget *EXTERN_FileReplace;

QDockWidget *EXTERN_Quickcode;
QDockWidget *EXTERN_Helpwindow_shortcut;




extern const QIcon &kbasicIcon(QString s);

extern QString idePath(QString s);
extern QString kbasicControlPath(QString s);


extern QSystemTrayIcon *trayIcon;

extern _resources *my_resources;

QTranslator *translator;



_mainwindow::_mainwindow(QApplication *app, QSplashScreen *splash, bool _bRuntime)
{
  bProjectLoading = false;

  macmenuBar = 0;
  my_resources = 0;

  translator = 0;
  EXTERN_my_parserwindow = 0; 

  setWindowTitle(tr(MYAPP));
  setWindowIcon(kbasicIcon(kbasicPath("ide/kbasic_icon.png")));

  QFile::remove(idePath("screen.png"));
  QFile::remove(idePath("log.html"));

  myInterpreter = 0;

  trayIcon = 0;

  fsWatcher = 0;
  
#ifdef MAC
  qApp->setAttribute(Qt::AA_DontShowIconsInMenus); // HIDE
#endif

  my_qapplication = app;
  bRuntime = _bRuntime; 
  EXTERN_my_mainwindow = this;
  EXTERN_my_propertywindow = 0;
  EXTERN_my_parserwindow = 0;
//  EXTERN_my_helpwindow = 0;



  workspace = new QMdiArea;
#ifdef MAC
  QFont f = workspace->font(); f.setPixelSize(12); workspace->setFont(f); 
  workspace->setDocumentMode(true);
#endif

  setCentralWidget(workspace);
  connect(workspace, SIGNAL(subWindowActivated(QMdiSubWindow *)), this, SLOT(subWindowActivated(QMdiSubWindow *)));
  
  workspace->setOption(QMdiArea::DontMaximizeSubWindowOnActivation);

  workspace->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  workspace->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
/*
#ifdef WINDOWS
  workspace->setTabShape(QTabWidget::Triangular);
#endif
*/
  my_compile = 0;
  my_infoconsole = new _infoconsole(this);
  my_log = 0;

  if (splash) splash->showMessage(tr("Starting"), Qt::AlignBottom | Qt::AlignRight);

  if (splash) splash->showMessage(tr("Reading Settings"), Qt::AlignBottom | Qt::AlignRight);
  setDefaultPreferences();
  if (!bRuntime){
    _preferences::load(this);

    QString en = _mainwindow::locale();
    if (en != "en"){
      translator = new QTranslator( 0 ); 
      bool bg = translator->load( QString(kbasicPath("ide/tr_")) + en);
      qApp->installTranslator( translator );
    }
  }

  ci_bUpdatedDot = false;
  ci_bUpdatedDotMethod = false;
  ci_bUpdatedAs = false;

  EXTERN_my_projectwindow = new _projectwindow(this); 

  bRunning = false;
  bCompiling = false;
  bDebugging = false;
  bProject = false;


  windowMapper = new QSignalMapper(this);
  exampleMapper = new QSignalMapper(this);
  projectlistMapper = new QSignalMapper(this);

  connect(windowMapper, SIGNAL(mapped(QWidget *)), this, SLOT(setActiveSubWindow(QWidget *)));

  connect(exampleMapper, SIGNAL(mapped(const QString &)), this, SLOT(openExampleFile(QString)));
  connect(projectlistMapper, SIGNAL(mapped(const QString &)), this, SLOT(openProjectListFile(QString)));

  if (!bRuntime){
    createActions();

    if (splash) splash->showMessage(tr("Reading Examples"), Qt::AlignBottom | Qt::AlignRight);
    createMenus();

    if (splash) splash->showMessage(tr("Creating GUI"), Qt::AlignBottom | Qt::AlignRight);
    createToolBars();
    createStatusBar();
    createDockWindows();

    _sourcecodeeditor::createMap(); // perfomance 

    setDockNestingEnabled (true);

    subWindowActivated(0); // init actions

  }

    //loadForm("c:\\kbasic16\\kbide/examples/projects\\sql.kbasic_project\\gg.kbasic_form");

//  loadReport("c:\\kbasic16\\kbide/examples/projects\\sql.kbasic_project\\test3.kbasic_report");
//
  //loadToolBar("c:\\kbasic16\\kbide/examples/projects\\sql.kbasic_project\\iiiii.kbasic_toolbar");
//  loadMenuBar("c:\\kbasic16\\kbide/examples/projects\\sql.kbasic_project\\i.kbasic_menubar");



  if (splash) splash->showMessage(tr("Done"), Qt::AlignBottom | Qt::AlignRight);

  readSettings();

  QString r = getPreference("Stylesheet");
  if (r.length()){
    r += ".qss";
    r = r.toLower();
    r = r.prepend("ide/");
    QFile file(kbasicPath(r));
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
  }

  if (getPreference("TabBar").isEmpty()){
    workspace->setViewMode(QMdiArea::TabbedView);//TabbedView  SubWindowView
  } else {    
    workspace->setViewMode(getPreference("TabBar") == "Yes" ? QMdiArea::TabbedView : QMdiArea::SubWindowView);//TabbedView  SubWindowView
  }
 // workspace->setTabShape(QTabWidget::Triangular);
  //workspace->setTabPosition(QTabWidget::West);

  subWindowActivated(0);
  updateRunActions();

  nCurrentBookmark = 0;

  // ACTIVATE
  if (/*false && */getPreference("License").isEmpty()/* && getPreference("License") != "2"*/){

    setWindowTitle(tr(MYAPP) + " - " + tr("N O T  R E G I S T E R E D"));

#ifdef LINUX
}
/*
    QMessageBox::information(this, tr("Thanks for using KBasic."), tr(
"The Linux version is free of charge for open source (GPL) Software, if \n"
"you would like to use it for open source development released under the \n"
"terms of GNU GPL Version 3 as published by the Free Software Foundation.\n"
"\n"
"If you use the Linux version, there are certain licensing conditions that \n"
"the GNU GPL imposes on you.\n"
"\n"
"This means that you cannot use the FREE Linux version if your software \n"
"must be built with any modules that impose conditions on you that \n"
"contradict the conditions of the GNU GPL, including, but not limited \n"
"to, software patents, commercial license agreements, copyrighted \n"
"interface definitions or any sort of non-disclosure agreement. \n"
"\n"
"In these circumstances you must use a commercial edition of KBasic. \n"
));
*/
#else

    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Thanks for trying KBasic."));
#ifdef LINUX
    QPushButton *ok = msgBox.addButton(tr("Use GPL Version"), QMessageBox::ActionRole);
#else
    QPushButton *ok = msgBox.addButton(tr("Trial"), QMessageBox::ActionRole);
#endif
    QPushButton *enterkey = msgBox.addButton(tr("Enter key"), QMessageBox::ActionRole);
    QPushButton *buynow = msgBox.addButton(tr("Buy now!"), QMessageBox::ActionRole);

    msgBox.setText(tr(
"This program is not free. It is an evaluation version of copyrighted software.\n"
"If you use it beyond the evaluation period, you are expected to register it\n"
"with KBasic Software. Please check www.kbasic.com for details.\n"
"\n"
"This trial version comes without the EXE/APP creator.\n"
));
    msgBox.exec();

    if (msgBox.clickedButton() == ok){
	#ifndef MAC
      
      if (isPreferenceSet("WelcomeScreen")){
        _welcome *k = new _welcome (this);
      }
      
	  #endif
    } else if (msgBox.clickedButton() == enterkey){
      event_FILE_PREFERENCES();      
    } else if (msgBox.clickedButton() == buynow){
      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
      QDesktopServices::openUrl(QUrl("http://www.kbasic.com/"));
      QApplication::restoreOverrideCursor();

#ifndef MAC
      if (isPreferenceSet("WelcomeScreen")){
        _welcome *k = new _welcome (this);
      }
#endif

    }

  } else {
#ifndef MAC
    if (isPreferenceSet("WelcomeScreen")){
      _welcome *k = new _welcome (this);
    }
#endif
  }
#endif
    //_importproject *o = new _importproject(this);      
    //o->importCSV("c:\\kbasic16\\kbide\\examples\\test\\test_with_title.csv");     

  //_qbe *kk = new _qbe (this);
#ifdef WINDOWS
  QApplication::setStyle(new QtDotNetStyle(QtDotNetStyle::Standard)); // HIDE
#endif


}


_mainwindow::~_mainwindow()
{  
  writeSettings();
  if (translator) delete translator;

  if (my_infoconsole){ delete my_infoconsole; my_infoconsole = 0; }
  if (my_log){ delete my_log; my_log = 0; }

  if (trayIcon){ delete trayIcon; trayIcon = 0; }
  if (my_resources){ delete my_resources; my_resources = 0; }

#ifdef MAC
    if (macmenuBar) delete macmenuBar; // HIDE
#endif
}

void _mainwindow::loadDefaultFiles()
{

  if (!bRuntime){
    if (getPreference("DefaultProject").length()){
      if (QFile::exists(getPreference("DefaultProject"))){
        loadProject(getPreference("DefaultProject"));
      }
    }

    if (getPreference("DefaultFile").length()){
      if (QFile::exists(getPreference("DefaultFile"))){
        loadFileFullscreen(getPreference("DefaultFile"));
      }
    }
  }
}

void _mainwindow::closeEvent(QCloseEvent *event)
{
    event_RUN_STOP();
    workspace->closeAllSubWindows();
    
    
    QMdiSubWindow *activeSubWindow = workspace->activeSubWindow();

    if (activeSubWindow && activeSubWindow->widget()){
        event->ignore();
        return;
    } else {
        writeSettings();
        event->accept();
    }


    if (event->isAccepted()){

      if (this->isProject()) closeProject();

      // *** close opened screen
      foreach (QWidget *w, QApplication::allWidgets()){
        if (w->objectName() == "Console"){
          w->close();
        }
        else if (w->objectName() == "Log"){
          w->close();
        }
        else if (w->objectName() == "Virtual Machine Info"){
          w->close();
        }
      }
/*
      qApp->processEvents();
     foreach (QWidget *w, QApplication::topLevelWidgets ()){
         if (w != this) w->close();
      }
*/
    }
}


void _mainwindow::updateWindowMenu()
{
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
#ifndef MAC
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
#endif
    
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addAction(separatorAct);

    QList<QMdiSubWindow *> windows = workspace->subWindowList();

    QString s = "";
    QWidget *w = 0;
    QMdiSubWindow *subw = 0;
    QString text;
    int i = 0;

    QMdiSubWindow *aw = workspace->activeSubWindow();
    for (; i < windows.size(); ++i) {
        subw = windows.at(i);
        w = subw->widget();

        if (w == 0){
         // w = w;
          continue;
        }

        _sourcecodeeditor *my_sourcecodeeditor;
        _form *my_form;
        _report *my_report;
        _menubar *my_menubar;
        _toolbar *my_toolbar;
        _table *my_table;
        _qbe *my_qbe;
        _tableviewer *my_tableviewer;

        if ((my_sourcecodeeditor = qobject_cast<_sourcecodeeditor *>(w))){
          w = my_sourcecodeeditor;
          s = getFilenameWithoutPathAndExtension(my_sourcecodeeditor->getFilenameWithoutPath());
          if (s.isEmpty()) s = tr("unnamed document");
          s += tr(" : Code Editor");
          /*
          if (s.endsWith(".kbasic_form")) s+= " (Source Code)";
          if (s.endsWith(".kbasic_report")) s+= " (Source Code)";
          if (s.endsWith(".kbasic_menubar")) s+= " (Source Code)";
          if (s.endsWith(".kbasic_toolbar")) s+= " (Source Code)";
          */
        } else if ((my_form = qobject_cast<_form  *>(w))){
          w = my_form;
          s = my_form->getFilenameWithoutPathAndExtension();
          if (s.isEmpty()) s = tr("unnamed document");
          if (my_form->isReport()) s += tr(" : Report"); else s += tr(" : Form");
        } else if ((my_report = qobject_cast<_report  *>(w))){
          w = my_report;
          s = my_report->getFilenameWithoutPathAndExtension();
          if (s.isEmpty()) s = tr("unnamed document");
          s += tr(" : Report");
        } else if ((my_menubar = qobject_cast<_menubar  *>(w))){
          w = my_menubar;
          s = my_menubar->getFilenameWithoutPathAndExtension();
          if (s.isEmpty()) s = tr("unnamed document");
          s += tr(" : MenuBar");
        } else if ((my_toolbar = qobject_cast<_toolbar  *>(w))){
          w = my_toolbar;
          s = my_toolbar->getFilenameWithoutPathAndExtension();
          if (s.isEmpty()) s = tr("unnamed document");
          s += tr(" : ToolBar");
        } else if ((my_table = qobject_cast<_table  *>(w))){
          w = my_table;
          s = my_table->getFilenameWithoutPathAndExtension();
          if (s.isEmpty()) s = tr("unnamed document");
          s += tr(" : Table");
        } else if ((my_tableviewer = qobject_cast<_tableviewer  *>(w))){
          w = my_tableviewer;
          s = my_tableviewer->windowTitle();
        } else if ((my_qbe = qobject_cast<_qbe *>(w))){
          w = my_qbe;
          s = my_qbe->getFilenameWithoutPathAndExtension();
          if (s.isEmpty()) s = tr("unnamed document");
          s += tr(" : Query");
        } else {
          //w = 0;
          s = w->windowTitle();
        }

        if (s.length() == 0) s = tr("unnamed document");
        
		#ifdef MAC
          text = s;
		#else
		 if (i < 9) {
          text = tr("&%1 %2").arg(i + 1).arg(s);
        } else {
          text = tr("%1 %2").arg(i + 1).arg(s);
        }
		#endif

        QAction *action = windowMenu->addAction(text);
        action->setCheckable(true);
        action->setChecked(subw == aw);
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, subw);
    }
    

    separatorAct->setVisible(i != 0);   

    
}

void _mainwindow::createActions()
{
  
    QAction *a = 0;


    a = PROJECTLIST = new QAction(
//#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECTLIST.png")), 
//#endif
    tr("&Files"), this);

    //PROJECTLIST->setShortcut(tr("CTRL+RETURN"));
    connect(PROJECTLIST, SIGNAL(triggered()), this, SLOT(event_PROJECTLIST()));




    a = FILE_NEW_PROJECT = new QAction(
    #ifndef MAC
    kbasicIcon(kbasicPath("ide/FILE_NEW_PROJECT.png")), 
    #endif
    tr("Ne&w Project   ( KBasic | Forms | Classes | Modules... )"), this);
    
    FILE_NEW_PROJECT->setShortcut(tr("CTRL+SHIFT+N"));
    //FILE_NEW_PROJECT->setStatusTip(tr("Create a new project"));
    connect(FILE_NEW_PROJECT, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_PROJECT()));

    a = FILE_OPEN_PROJECT = new QAction(
   #ifndef MAC
    kbasicIcon(kbasicPath("ide/FILE_OPEN_PROJECT.png")), 

 #endif
                                        tr("Open Pro&ject"), this);

    
    FILE_OPEN_PROJECT->setShortcut(tr("CTRL+SHIFT+O"));
    //FILE_OPEN_PROJECT->setStatusTip(tr("Opens a project"));
    connect(FILE_OPEN_PROJECT, SIGNAL(triggered()), this, SLOT(event_FILE_OPEN_PROJECT()));

    a = FILE_CLOSE_PROJECT = new QAction(/*kbasicIcon(kbasicPath("ide/FILE_CLOSE_PROJECT.png")), */tr("Close Project"), this);
    //FILE_CLOSE_PROJECT->setStatusTip(tr("Closes a project"));

    connect(FILE_CLOSE_PROJECT, SIGNAL(triggered()), this, SLOT(event_FILE_CLOSE_PROJECT()));

    a = FILE_CLOSE = new QAction(/*kbasicIcon(kbasicPath("ide/FILE_CLOSE.png")), */tr("&Close File"), this);
    //FILE_CLOSE->setStatusTip(tr("&Closes a file"));


    connect(FILE_CLOSE, SIGNAL(triggered()), this, SLOT(event_FILE_CLOSE()));

    a = FILE_IMPORT_PROJECT = new QAction(tr("&Import VB6 Project..."), this);
    //FILE_IMPORT_PROJECT->setStatusTip(tr("Imports a VB6 project"));


    connect(FILE_IMPORT_PROJECT, SIGNAL(triggered()), this, SLOT(event_FILE_IMPORT_PROJECT()));


    a = FILE_EXPORT_CSV = new QAction(tr("&Export CSV File..."), this);
    connect(FILE_EXPORT_CSV, SIGNAL(triggered()), this, SLOT(event_FILE_EXPORT_CSV()));

/*
    FILE_EXPORT_PROJECT = new QAction(tr("&Export Project..."), this);
    FILE_EXPORT_PROJECT->setStatusTip(tr("Exports a project"));
    connect(FILE_EXPORT_PROJECT, SIGNAL(triggered()), this, SLOT(event_FILE_EXPORT_PROJECT()));*/
/*
    FILE_CLOSE_PROJECT = new QAction(tr("&Close Project"), this);
    FILE_CLOSE_PROJECT->setStatusTip(tr("Closes a project"));
    connect(FILE_CLOSE_PROJECT, SIGNAL(triggered()), this, SLOT(event_FILE_CLOSE_PROJECT()));
*/

    a = FILE_NEW_FILE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FILE_NEW_FILE.png")), 
#endif
    tr("&New File"), this);

    FILE_NEW_FILE->setShortcut(tr("CTRL+N"));
    //FILE_NEW_FILE->setStatusTip(tr("Creates a new file"));
    connect(FILE_NEW_FILE, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_FILE()));

    a = FILE_OPEN_FILE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FILE_OPEN_FILE.png")),
#endif
    tr("&Open File      ( KBasic | BASIC )"), this);

    FILE_OPEN_FILE->setShortcut(tr("CTRL+O"));
    //FILE_OPEN_FILE->setStatusTip(tr("Opens a file"));
    connect(FILE_OPEN_FILE, SIGNAL(triggered()), this, SLOT(event_FILE_OPEN_FILE()));

    a = FILE_SAVE = new QAction(
 //   #ifndef MAC
    kbasicIcon(kbasicPath("ide/FILE_SAVE.png")), 
//#endif
    tr("&Save"), this);
    
    FILE_SAVE->setShortcut(tr("CTRL+S"));
    //FILE_SAVE->setStatusTip(tr("Saves a file"));
    connect(FILE_SAVE, SIGNAL(triggered()), this, SLOT(event_FILE_SAVE()));

    a = FILE_SAVE_AS = new QAction(tr("Save &As..."), this);

    //FILE_SAVE_AS->setStatusTip(tr("Saves files as..."));
    connect(FILE_SAVE_AS, SIGNAL(triggered()), this, SLOT(event_FILE_SAVE_AS()));

    a = FILE_SAVE_ALL = new QAction(tr("Sa&ve All"), this);

    FILE_SAVE->setShortcut(tr("CTRL+SHIFT+S"));
    //FILE_SAVE_ALL->setStatusTip(tr("Saves all files"));
    connect(FILE_SAVE_ALL, SIGNAL(triggered()), this, SLOT(event_FILE_SAVE_ALL()));
/*
    FILE_CLOSE = new QAction(tr("&Close"), this);
    FILE_CLOSE->setStatusTip(tr("Close file"));
    connect(FILE_CLOSE, SIGNAL(triggered()), this, SLOT(event_FILE_CLOSE()));
*/

    a = FILE_IMPORT_CSV = new QAction(tr("Imp&ort CSV File..."), this);

    //FILE_IMPORT_FILE->setStatusTip(tr("Imports a VB6 file"));
    connect(FILE_IMPORT_CSV, SIGNAL(triggered()), this, SLOT(event_FILE_IMPORT_CSV()));


    a = FILE_IMPORT_FILE = new QAction(tr("Im&port VB6 File..."), this);

    //FILE_IMPORT_FILE->setStatusTip(tr("Imports a VB6 file"));
    connect(FILE_IMPORT_FILE, SIGNAL(triggered()), this, SLOT(event_FILE_IMPORT_FILE()));
/*
    FILE_EXPORT_FILE = new QAction(tr("E&xport File..."), this);
    FILE_EXPORT_FILE->setStatusTip(tr("Exports a file"));
    connect(FILE_EXPORT_FILE, SIGNAL(triggered()), this, SLOT(event_FILE_EXPORT_FILE()));
*/
    a = FILE_SET_AS_DEFAULT = new QAction(tr("Set As Default File"), this);

    //FILE_SET_AS_DEFAULT->setStatusTip(tr("Sets a file to be loaded on startup"));
    connect(FILE_SET_AS_DEFAULT, SIGNAL(triggered()), this, SLOT(event_FILE_SET_AS_DEFAULT()));

    a = FILE_SAVE_HTML = new QAction(/*kbasicIcon(kbasicPath("ide/FILE_PRINT.png")), */tr("&Save As HTML..."), this);

    //FILE_PRINT->setStatusTip(tr("Saves a file in HTML format"));
    connect(FILE_SAVE_HTML, SIGNAL(triggered()), this, SLOT(event_FILE_SAVE_HTML()));

    FILE_PRINT = new QAction(
    #ifndef MAC
    kbasicIcon(kbasicPath("ide/FILE_PRINT.png")), 
#endif
    tr("&Print..."), this);
    //FILE_PRINT->setStatusTip(tr("Saves a file in HTML format"));
    connect(FILE_PRINT, SIGNAL(triggered()), this, SLOT(event_FILE_PRINT()));

    a = FILE_EXIT = new QAction(/*kbasicIcon(kbasicPath("ide/FILE_EXIT.png")), */tr("E&xit"), this);

    //FILE_EXIT->setStatusTip(tr("Saves a file in HTML format"));
    connect(FILE_EXIT, SIGNAL(triggered()), this, SLOT(event_FILE_EXIT()));




    EDIT_UNDO = new QAction(
    #ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_UNDO.png")), 
#endif
        tr("&Undo"), this);
    EDIT_UNDO->setShortcut(tr("CTRL+Z"));
    //EDIT_UNDO->setStatusTip(tr("Undoes last command"));
    connect(EDIT_UNDO, SIGNAL(triggered()), this, SLOT(event_EDIT_UNDO()));

    EDIT_REDO = new QAction(
                            #ifndef MAC
                            kbasicIcon(kbasicPath("ide/EDIT_REDO.png")), 
#endif
                            tr("&Redo"), this);
    EDIT_REDO->setShortcut(tr("CTRL+Y"));
    //EDIT_REDO->setStatusTip(tr("Redos last command"));
    connect(EDIT_REDO, SIGNAL(triggered()), this, SLOT(event_EDIT_REDO()));

    EDIT_CUT = new QAction(
                           #ifndef MAC
                           kbasicIcon(kbasicPath("ide/EDIT_CUT.png")), 
#endif
                           tr("Cu&t"), this);
    EDIT_CUT->setShortcut(tr("CTRL+X"));
    //EDIT_CUT->setStatusTip(tr("Cuts"));
    connect(EDIT_CUT, SIGNAL(triggered()), this, SLOT(event_EDIT_CUT()));

    EDIT_COPY = new QAction(
                            #ifndef MAC
                            kbasicIcon(kbasicPath("ide/EDIT_COPY.png")), 
#endif
                            tr("&Copy"), this);
    EDIT_COPY->setShortcut(tr("CTRL+C"));
    //EDIT_COPY->setStatusTip(tr("Copies"));
    connect(EDIT_COPY, SIGNAL(triggered()), this, SLOT(event_EDIT_COPY()));

    EDIT_PASTE = new QAction(
                             #ifndef MAC
                             kbasicIcon(kbasicPath("ide/EDIT_PASTE.png")), 
#endif
                             tr("&Paste"), this);
    EDIT_PASTE->setShortcut(tr("CTRL+V"));
    //EDIT_PASTE->setStatusTip(tr("Pastes"));
    connect(EDIT_PASTE, SIGNAL(triggered()), this, SLOT(event_EDIT_PASTE()));

    EDIT_DELETE = new QAction(/*kbasicIcon(kbasicPath("ide/EDIT_DELETE.png")), */tr("&Delete"), this);
    //EDIT_DELETE->setStatusTip(tr("Deletes"));
    connect(EDIT_DELETE, SIGNAL(triggered()), this, SLOT(event_EDIT_DELETE()));

    a = EDIT_SELECT_ALL = new QAction(tr("Select &All"), this);

    EDIT_SELECT_ALL->setShortcut(tr("CTRL+A"));
    //EDIT_SELECT_ALL->setStatusTip(tr("Selects all"));
    connect(EDIT_SELECT_ALL, SIGNAL(triggered()), this, SLOT(event_EDIT_SELECT_ALL()));

    EDIT_APPLY = new QAction(
                            #ifndef MAC
                            kbasicIcon(kbasicPath("ide/EDIT_APPLY.png")), 
#endif
                            tr("&Apply Properties"), this);
    EDIT_APPLY->setShortcut(tr("CTRL+SPACE"));
    connect(EDIT_APPLY, SIGNAL(triggered()), this, SLOT(event_EDIT_APPLY()));

    EDIT_FIND = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_FIND.png")), 
#endif
    tr("&Find..."), this);

    EDIT_FIND->setShortcut(tr("CTRL+F"));
    //EDIT_FIND->setStatusTip(tr("Finds"));
    connect(EDIT_FIND, SIGNAL(triggered()), this, SLOT(event_EDIT_FIND()));

//#ifndef MAC
    EDIT_FIND_FILE = new QAction(
    kbasicIcon(kbasicPath("ide/EDIT_FIND_FILE.png")), 
    tr("&Find In Files..."), this);

    EDIT_FIND_FILE->setShortcut(tr("Finds in files"));
    //EDIT_FIND_FILE->setStatusTip(tr("Pastes"));
    connect(EDIT_FIND_FILE, SIGNAL(triggered()), this, SLOT(event_EDIT_FIND_FILE()));

    a = EDIT_REPLACE_FILE = new QAction(tr("Replace In Files..."), this);

    //EDIT_REPLACE_FILE->setStatusTip(tr("Replaces in files"));
    connect(EDIT_REPLACE_FILE, SIGNAL(triggered()), this, SLOT(event_EDIT_REPLACE_FILE()));
//#endif

    a = EDIT_REPLACE = new QAction(tr("Replace..."), this);

    EDIT_REPLACE->setShortcut(tr("CTRL+R"));
    //EDIT_REPLACE->setStatusTip(tr("Replaces"));
    connect(EDIT_REPLACE, SIGNAL(triggered()), this, SLOT(event_EDIT_REPLACE()));

    EDIT_COMMENT_LINES = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_COMMENT_LINES.png")), 
#endif
    tr("Comment Lines"), this);
    EDIT_COMMENT_LINES->setShortcut(tr("ALT+C"));
    //EDIT_COMMENT_LINES->setStatusTip(tr("Comments lines"));
    connect(EDIT_COMMENT_LINES, SIGNAL(triggered()), this, SLOT(event_EDIT_COMMENT_LINES()));

    EDIT_UNCOMMENT_LINES = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_UNCOMMENT_LINES.png")),
#endif
    tr("Uncomment Lines"), this);

    EDIT_UNCOMMENT_LINES->setShortcut(tr("CTRL+ALT+C"));
    //EDIT_UNCOMMENT_LINES->setStatusTip(tr("Uncomments lines"));
    connect(EDIT_UNCOMMENT_LINES, SIGNAL(triggered()), this, SLOT(event_EDIT_UNCOMMENT_LINES()));

    EDIT_UNINDENT_LINES = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_UNINDENT_LINES.png")), 
#endif
    tr("Unindent Lines"), this);
    EDIT_UNINDENT_LINES->setShortcut(tr("SHIFT+Tab"));
    //EDIT_UNINDENT_LINES->setStatusTip(tr("Unindents lines"));
    connect(EDIT_UNINDENT_LINES, SIGNAL(triggered()), this, SLOT(event_EDIT_UNINDENT_LINES()));

    EDIT_INDENT_LINES = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_INDENT_LINES.png")), 
#endif
    tr("Indent Lines"), this);
    //EDIT_INDENT_LINES->setShortcut(tr("Tab")); // setting Tab as shortcut breaks find dialog tab handling
    //EDIT_INDENT_LINES->setStatusTip(tr("Indents lines"));
    connect(EDIT_INDENT_LINES, SIGNAL(triggered()), this, SLOT(event_EDIT_INDENT_LINES()));

    EDIT_MARK_LINES = new QAction(
#ifndef MAC
//    kbasicIcon(kbasicPath("ide/EDIT_MARK_LINES.png")), 
#endif
    tr("Mark Lines"), this);
    //EDIT_MARK_LINES->setStatusTip(tr("Marks lines"));
    connect(EDIT_MARK_LINES, SIGNAL(triggered()), this, SLOT(event_EDIT_MARK_LINES()));


    EDIT_BACKGROUND = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_BACKGROUND.png")), 
#endif
    tr("Background"), this);
    connect(EDIT_BACKGROUND, SIGNAL(triggered()), this, SLOT(event_EDIT_BACKGROUND()));

    EDIT_FONTNAME = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_FONTNAME.png")), 
#endif
    tr("Font Name"), this);
    connect(EDIT_FONTNAME, SIGNAL(triggered()), this, SLOT(event_EDIT_FONTNAME()));

    EDIT_FONTCOLOR = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_FONTCOLOR.png")), 
#endif
    tr("Font Color"), this);
    connect(EDIT_FONTCOLOR, SIGNAL(triggered()), this, SLOT(event_EDIT_FONTCOLOR()));

    EDIT_BOLD = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_BOLD.png")), 
#endif
    tr("Bold"), this);
    connect(EDIT_BOLD, SIGNAL(triggered()), this, SLOT(event_EDIT_BOLD()));

    EDIT_ITALIC = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_ITALIC.png")), 
#endif
    tr("Italic"), this);
    connect(EDIT_ITALIC, SIGNAL(triggered()), this, SLOT(event_EDIT_ITALIC()));

    EDIT_UNDERLINE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_UNDERLINE.png")), 
#endif
    tr("Underline"), this);
    connect(EDIT_UNDERLINE, SIGNAL(triggered()), this, SLOT(event_EDIT_UNDERLINE()));


    EDIT_FONTSIZE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_FONTSIZE.png")), 
#endif
    tr("Font Size"), this);
    connect(EDIT_FONTSIZE, SIGNAL(triggered()), this, SLOT(event_EDIT_FONTSIZE()));


    EDIT_UPPER = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_UPPER.png")), 
#endif
    tr("Uppercase"), this);
    //EDIT_UPPER->setStatusTip(tr("Makes uppercase"));
    connect(EDIT_UPPER, SIGNAL(triggered()), this, SLOT(event_EDIT_UPPER()));

    EDIT_LOWER = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_LOWER.png")), 
#endif
    tr("Lowercase"), this);
    //EDIT_LOWER->setStatusTip(tr("Makes lowercase"));
    connect(EDIT_LOWER, SIGNAL(triggered()), this, SLOT(event_EDIT_LOWER()));

    EDIT_GOTO = new QAction(tr("&Go To..."), this);
    EDIT_GOTO->setShortcut(tr("CTRL+G"));
    //EDIT_GOTO->setStatusTip(tr("Go to line..."));
    connect(EDIT_GOTO, SIGNAL(triggered()), this, SLOT(event_EDIT_GOTO()));

    a = EDIT_FINDDEFINITION = new QAction(/*kbasicIcon(kbasicPath("ide/EDIT_COMMENT_LINES.png")), */tr("Find Definition"), this);

#ifdef LINUX
    EDIT_FINDDEFINITION->setShortcut(tr("F12"));
#else
    EDIT_FINDDEFINITION->setShortcut(tr("ALT+F12"));
#endif
    //EDIT_COMMENT_LINES->setStatusTip(tr("Comments lines"));
    connect(EDIT_FINDDEFINITION, SIGNAL(triggered()), this, SLOT(event_EDIT_FINDDEFINITION()));

    EDIT_INSERT_FILE = new QAction(tr("Insert File As Text..."), this);
    //EDIT_INSERT_FILE->setStatusTip(tr("Inserts file as text..."));
    connect(EDIT_INSERT_FILE, SIGNAL(triggered()), this, SLOT(event_EDIT_INSERT_FILE()));

    a = EDIT_CLEAR_ALL_BOOKMARKS = new QAction(tr("Clear All Bookmarks"), this);

    //EDIT_CLEAR_ALL_BOOKMARKS->setStatusTip(tr("Clears all bookmarks"));
    connect(EDIT_CLEAR_ALL_BOOKMARKS, SIGNAL(triggered()), this, SLOT(event_EDIT_CLEAR_ALL_BOOKMARKS()));

    EDIT_SET_BOOKMARK = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_SET_BOOKMARK.png")), 
#endif
    tr("Set/Unset Bookmark"), this);
    EDIT_SET_BOOKMARK->setShortcut(tr("F4"));
    //EDIT_SET_BOOKMARK->setStatusTip(tr("Sets/Unsets bookmark"));
    connect(EDIT_SET_BOOKMARK, SIGNAL(triggered()), this, SLOT(event_EDIT_SET_BOOKMARK()));

    EDIT_NEXT_BOOKMARK = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_NEXT_BOOKMARK.png")), 
#endif
    tr("Next Bookmark"), this);
    EDIT_NEXT_BOOKMARK->setShortcut(tr("SHIFT+F4"));
    //EDIT_NEXT_BOOKMARK->setStatusTip(tr("Next bookmark"));
    connect(EDIT_NEXT_BOOKMARK, SIGNAL(triggered()), this, SLOT(event_EDIT_NEXT_BOOKMARK()));

    EDIT_PREVIOUS_BOOKMARK = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EDIT_PREVIOUS_BOOKMARK.png")), 
#endif
    tr("Previous Bookmark"), this);
    EDIT_PREVIOUS_BOOKMARK->setShortcut(tr("CTRL+SHIFT+F4"));
    //EDIT_PREVIOUS_BOOKMARK->setStatusTip(tr("Previous bookmark"));
    connect(EDIT_PREVIOUS_BOOKMARK, SIGNAL(triggered()), this, SLOT(event_EDIT_PREVIOUS_BOOKMARK()));


    VIEW_DESIGN = new QAction(
//#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_FORM.png")), 
//#endif
    tr("&Form"), this);
#ifndef MAC
    VIEW_DESIGN->setShortcut(tr("F10"));
#else
    VIEW_DESIGN->setShortcut(tr("ALT+F10"));    
#endif
    connect(VIEW_DESIGN, SIGNAL(triggered()), this, SLOT(event_VIEW_DESIGN()));

    VIEW_SOURCE_CODE = new QAction(
//#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_SOURCE_CODE.png")), 
//#endif
    tr("&Source Code"), this);
#ifndef MAC
    VIEW_SOURCE_CODE->setShortcut(tr("F11"));
#else
    VIEW_SOURCE_CODE->setShortcut(tr("ALT+F11"));
#endif
    //VIEW_SOURCE_CODE->setStatusTip(tr("Source Code"));
    connect(VIEW_SOURCE_CODE, SIGNAL(triggered()), this, SLOT(event_VIEW_SOURCE_CODE()));
/*
    VIEW_REPORT = new QAction(kbasicIcon(kbasicPath("ide/VIEW_REPORT.png")), tr("&Report"), this);
    connect(VIEW_REPORT, SIGNAL(triggered()), this, SLOT(event_VIEW_REPORT()));
*/
    VIEW_REPORTPREVIEW = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_REPORTPREVIEW.png")), 
#endif
    tr("&Preview"), this);
    connect(VIEW_REPORTPREVIEW, SIGNAL(triggered()), this, SLOT(event_VIEW_REPORTPREVIEW()));
/*
    VIEW_MENUBAR = new QAction(kbasicIcon(kbasicPath("ide/VIEW_MENUBAR.png")), tr("&MenuBar"), this);
    connect(VIEW_MENUBAR, SIGNAL(triggered()), this, SLOT(event_VIEW_MENUBAR()));

    VIEW_TOOLBAR = new QAction(kbasicIcon(kbasicPath("ide/VIEW_TOOLBAR.png")), tr("&ToolBar"), this);
    connect(VIEW_TOOLBAR, SIGNAL(triggered()), this, SLOT(event_VIEW_TOOLBAR()));
*/
    VIEW_FULLSCREEN = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_FULLSCREEN.png")), 
#endif
    tr("&Full Screen"), this);
    VIEW_FULLSCREEN->setShortcut(tr("F7"));
    connect(VIEW_FULLSCREEN, SIGNAL(triggered()), this, SLOT(event_VIEW_FULLSCREEN()));

    VIEW_QBE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_QBE.png")), 
#endif
    tr("&Query By Example"), this);
    connect(VIEW_QBE, SIGNAL(triggered()), this, SLOT(event_VIEW_QBE()));

    VIEW_RELATION = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_RELATION.png")), 
#endif
    tr("&Relations"), this);
    connect(VIEW_RELATION, SIGNAL(triggered()), this, SLOT(event_VIEW_RELATION()));

    VIEW_QUICKCODE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_QUICKCODE.png")), 
#endif
    tr("&Console"), this);
    connect(VIEW_QUICKCODE, SIGNAL(triggered()), this, SLOT(event_VIEW_QUICKCODE()));

    VIEW_FOCUSORDER = new QAction(tr("&Focus Order"), this);
    VIEW_FOCUSORDER->setCheckable(true);
    VIEW_FOCUSORDER->setChecked(false);
    connect(VIEW_FOCUSORDER, SIGNAL(triggered()), this, SLOT(event_VIEW_FOCUSORDER()));

    VIEW_SQLSETTINGS = new QAction(tr("&SQL Binding"), this);
    VIEW_SQLSETTINGS->setCheckable(true);
    VIEW_SQLSETTINGS->setChecked(false);
    connect(VIEW_SQLSETTINGS, SIGNAL(triggered()), this, SLOT(event_VIEW_SQLSETTINGS()));

    VIEW_SQLTABLES = new QAction(tr("Database T&ables"), this);
    //VIEW_SQLTABLES->setCheckable(true);
    //VIEW_SQLTABLES->setChecked(false);
    connect(VIEW_SQLTABLES, SIGNAL(triggered()), this, SLOT(event_VIEW_SQLTABLES()));

/*
    VIEW_PROJECT_OVERVIEW = new QAction(kbasicIcon(kbasicPath("ide/VIEW_PROJECT_OVERVIEW.png")), tr("Project &Window"), this);
    VIEW_PROJECT_OVERVIEW->setShortcut(tr("CTRL+I"));
    VIEW_PROJECT_OVERVIEW->setStatusTip(tr("Project window"));
    connect(VIEW_PROJECT_OVERVIEW, SIGNAL(triggered()), this, SLOT(event_VIEW_PROJECT_OVERVIEW()));

    VIEW_TOOLBOX = new QAction(kbasicIcon(kbasicPath("ide/VIEW_TOOLBOX.png")), tr("&Toolbox"), this);
    VIEW_TOOLBOX->setShortcut(tr("CTRL+T"));
    VIEW_TOOLBOX->setStatusTip(tr("Toolbox"));
    connect(VIEW_TOOLBOX, SIGNAL(triggered()), this, SLOT(event_VIEW_TOOLBOX()));

    VIEW_PROPERTY_WINDOW = new QAction(kbasicIcon(kbasicPath("ide/VIEW_PROPERTY_WINDOW.png")), tr("&Property Window"), this);
    VIEW_PROPERTY_WINDOW->setShortcut(tr("CTRL+P"));
    VIEW_PROPERTY_WINDOW->setStatusTip(tr("Property Window"));
    connect(VIEW_PROPERTY_WINDOW, SIGNAL(triggered()), this, SLOT(event_VIEW_PROPERTY_WINDOW()));
*/

/*
    VIEW_LOG = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_LOG.png")), 
#endif
    tr("Log"), this);
    //VIEW_LOG->setShortcut(tr("F2"));
    //VIEW_LOG->setStatusTip(tr("Screen"));
    connect(VIEW_LOG, SIGNAL(triggered()), this, SLOT(event_VIEW_LOG()));
*/

    VIEW_RUNINFO = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_RUNINFO.png")), 
#endif
    tr("Virtual Machine Info"), this);
    //VIEW_RUNINFO->setShortcut(tr("F7"));
    //VIEW_RUNINFO->setStatusTip(tr("Virtual Machine Info"));
    connect(VIEW_RUNINFO, SIGNAL(triggered()), this, SLOT(event_VIEW_RUNINFO()));

    VIEW_KONSOLE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_KONSOLE.png")), 
#endif
    tr("Screen"), this);
    VIEW_KONSOLE->setShortcut(tr("Shift+F2"));
    //VIEW_KONSOLE->setStatusTip(tr("Screen"));
    connect(VIEW_KONSOLE, SIGNAL(triggered()), this, SLOT(event_VIEW_KONSOLE()));


    VIEW_LOG = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/VIEW_LOG.png")), 
#endif
    tr("Log"), this);
    VIEW_LOG->setShortcut(tr("F2"));
    connect(VIEW_LOG, SIGNAL(triggered()), this, SLOT(event_VIEW_LOG()));



    a = PROJECT_ADD_EXISTING = new QAction(tr("Add Existing..."), this);
    connect(PROJECT_ADD_EXISTING, SIGNAL(triggered()), this, SLOT(event_PROJECT_ADD_EXISTING()));

    a = PROJECT_REFRESH = new QAction(tr("Refresh"), this);
    connect(PROJECT_REFRESH, SIGNAL(triggered()), this, SLOT(event_PROJECT_REFRESH()));

    PROJECT_NEW_TABLE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE.png")), 
#endif
    tr("Table..."), this);
    //PROJECT_NEW_CLASS->setStatusTip(tr("Class..."));
    connect(PROJECT_NEW_TABLE, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_TABLE()));

    PROJECT_NEW_QUERY = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")), 
#endif
    tr("Query..."), this);
    connect(PROJECT_NEW_QUERY, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_QUERY()));
   // PROJECT_NEW_QUERY->setEnabled(false);

    PROJECT_NEW_CLASS = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")), 
#endif
    tr("Class..."), this);
    //PROJECT_NEW_CLASS->setStatusTip(tr("Class..."));
    connect(PROJECT_NEW_CLASS, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_CLASS()));

    PROJECT_NEW_MODULE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")), 
#endif
    tr("Module..."), this);
    //PROJECT_NEW_MODULE->setStatusTip(tr("Module..."));
    connect(PROJECT_NEW_MODULE, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_MODULE()));

    PROJECT_NEW_DIALOG = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_DIALOG.png")), 
#endif
    tr("Dialog..."), this);
    //PROJECT_NEW_FORM->setStatusTip(tr("Form..."));
    connect(PROJECT_NEW_DIALOG, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_DIALOG()));

    PROJECT_NEW_TOOLWINDOW = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_TOOLWINDOW.png")), 
#endif
    tr("Tool Window..."), this);
    //PROJECT_NEW_FORM->setStatusTip(tr("Form..."));
    connect(PROJECT_NEW_TOOLWINDOW, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_TOOLWINDOW()));

    PROJECT_NEW_DOCKWINDOW = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_DOCKWINDOW.png")), 
#endif
    tr("Dock Window..."), this);
    //PROJECT_NEW_FORM->setStatusTip(tr("Form..."));
    connect(PROJECT_NEW_DOCKWINDOW, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_DOCKWINDOW()));

    PROJECT_NEW_FORM = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_FORM.png")), 
#endif
    tr("Form..."), this);
    //PROJECT_NEW_FORM->setStatusTip(tr("Form..."));
    connect(PROJECT_NEW_FORM, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_FORM()));

    PROJECT_NEW_REPORT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_REPORT.png")), 
#endif
    tr("Report..."), this);
    //PROJECT_NEW_FORM->setStatusTip(tr("Form..."));
    connect(PROJECT_NEW_REPORT, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_REPORT()));

    PROJECT_NEW_MENUBAR = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_MENUBAR.png")), 
#endif
    tr("MenuBar..."), this);
    //PROJECT_NEW_MENUBAR->setStatusTip(tr("MenuBar..."));
    connect(PROJECT_NEW_MENUBAR, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_MENUBAR()));

    PROJECT_NEW_TOOLBAR = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_TOOLBAR.png")), 
#endif
    tr("ToolBar..."), this);
    //PROJECT_NEW_TOOLBAR->setStatusTip(tr("ToolBar..."));
    connect(PROJECT_NEW_TOOLBAR, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_TOOLBAR()));


    PROJECT_WIZARD_FORM = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_WIZARD_FORM.png")), 
#endif
    tr("Wizard For Form..."), this);
    connect(PROJECT_WIZARD_FORM, SIGNAL(triggered()), this, SLOT(event_PROJECT_WIZARD_FORM()));

    PROJECT_WIZARD_REPORT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_WIZARD_REPORT.png")), 
#endif
    tr("Wizard For Report..."), this);
    connect(PROJECT_WIZARD_REPORT, SIGNAL(triggered()), this, SLOT(event_PROJECT_WIZARD_REPORT()));

    PROJECT_NEW_FILE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_NEW_FILE.png")), 
#endif
    tr("&File..."), this);
    //PROJECT_NEW_FILE->setStatusTip(tr("File..."));
    connect(PROJECT_NEW_FILE, SIGNAL(triggered()), this, SLOT(event_FILE_NEW_FILE()));

    INSERT_SELECT2 = new QAction(/*kbasicIcon(kbasicControlPath("pointer.png")), */tr("&Select"), this);
    //INSERT_LABEL->setStatusTip(tr("Label"));
    connect(INSERT_SELECT2, SIGNAL(triggered()), this, SLOT(event_INSERT_SELECT2()));

    a = INSERT_LABEL = new QAction(/*kbasicIcon(kbasicControlPath("label.png")), */tr("&Label"), this);
    //INSERT_LABEL->setStatusTip(tr("Label"));
    connect(INSERT_LABEL, SIGNAL(triggered()), this, SLOT(event_INSERT_LABEL()));

    a = INSERT_COMMANDBUTTON = new QAction(/*kbasicIcon(kbasicControlPath("commandbutton.png")), */tr("&CommandButton"), this);
    //INSERT_COMMANDBUTTON->setStatusTip(tr("CommandButton"));
    connect(INSERT_COMMANDBUTTON, SIGNAL(triggered()), this, SLOT(event_INSERT_COMMANDBUTTON()));

    a = INSERT_CHECKBOX = new QAction(/*kbasicIcon(kbasicControlPath("checkbox.png")), */tr("&CheckBox"), this);
    //INSERT_CHECKBOX->setStatusTip(tr("CheckBox"));
    connect(INSERT_CHECKBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_CHECKBOX()));

    a = INSERT_RADIOBUTTON = new QAction(/*kbasicIcon(kbasicControlPath("radiobutton.png")), */tr("&RadioButton"), this);
    //INSERT_RADIOBUTTON->setStatusTip(tr("RadioButton"));
    connect(INSERT_RADIOBUTTON, SIGNAL(triggered()), this, SLOT(event_INSERT_RADIOBUTTON()));

    a = INSERT_TEXTBOX = new QAction(/*kbasicIcon(kbasicControlPath("textbox.png")), */tr("&TextBox"), this);
    //INSERT_TEXTBOX->setStatusTip(tr("TextBox"));
    connect(INSERT_TEXTBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_TEXTBOX()));

    a = INSERT_FRAME = new QAction(/*kbasicIcon(kbasicControlPath("frame.png")), */tr("&Frame"), this);
    //INSERT_FRAME->setStatusTip(tr("Frame"));
    connect(INSERT_FRAME, SIGNAL(triggered()), this, SLOT(event_INSERT_FRAME()));

    a = INSERT_LISTBOX = new QAction(/*kbasicIcon(kbasicControlPath("listbox.png")), */tr("&ListBox"), this);
    //INSERT_LISTBOX->setStatusTip(tr("ListBox"));
    connect(INSERT_LISTBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_LISTBOX()));

    a = INSERT_COMBOBOX = new QAction(/*kbasicIcon(kbasicControlPath("combobox.png")), */tr("&ComboBox"), this);
    //INSERT_COMBOBOX->setStatusTip(tr("ComboBox"));
    connect(INSERT_COMBOBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_COMBOBOX()));

    a = INSERT_CHILDCONTROL = new QAction(/*kbasicIcon(kbasicControlPath("childcontrol.png")), */tr("&FormView"), this);
    //INSERT_OPTIONBUTTON->setStatusTip(tr("OptionButton"));
    connect(INSERT_CHILDCONTROL, SIGNAL(triggered()), this, SLOT(event_INSERT_CHILDCONTROL()));

    a = INSERT_BROWSER = new QAction(/*kbasicIcon(kbasicControlPath("browser.png")), */tr("&HtmlView"), this);
    connect(INSERT_BROWSER, SIGNAL(triggered()), this, SLOT(event_INSERT_BROWSER()));

    a = INSERT_EDITOR = new QAction(/*kbasicIcon(kbasicControlPath("editor.png")), */tr("&RichTextBox"), this);
    connect(INSERT_EDITOR, SIGNAL(triggered()), this, SLOT(event_INSERT_EDITOR()));

    a = INSERT_DATEBOX = new QAction(/*kbasicIcon(kbasicControlPath("datebox.png")), */tr("&DateBox"), this);
    connect(INSERT_DATEBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_DATEBOX()));

    a = INSERT_TIMEBOX = new QAction(/*kbasicIcon(kbasicControlPath("timebox.png")), */tr("&TimeBox"), this);
    connect(INSERT_TIMEBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_TIMEBOX()));

    a = INSERT_DATETIMEBOX = new QAction(/*kbasicIcon(kbasicControlPath("datetimebox.png")), */tr("&DateTimeBox"), this);
    connect(INSERT_DATETIMEBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_DATETIMEBOX()));


    a = INSERT_PROGRESSBAR = new QAction(/*kbasicIcon(kbasicControlPath("progressbar.png")), */tr("&ProgressBar"), this);
    //INSERT_PROGRESSBAR->setStatusTip(tr("ProgressBar"));
    connect(INSERT_PROGRESSBAR, SIGNAL(triggered()), this, SLOT(event_INSERT_PROGRESSBAR()));


    a = INSERT_COMBOBOX_EDITABLE = new QAction(/*kbasicIcon(kbasicControlPath("progressbar.png")), */tr("&ComboBox (Editable)"), this);
    connect(INSERT_COMBOBOX_EDITABLE, SIGNAL(triggered()), this, SLOT(event_INSERT_COMBOBOX_EDITABLE()));

    a = INSERT_PROGRESSBAR_SPINNING = new QAction(/*kbasicIcon(kbasicControlPath("progressbar.png")), */tr("&ProgressBar (Spinning)"), this);
    connect(INSERT_PROGRESSBAR_SPINNING, SIGNAL(triggered()), this, SLOT(event_INSERT_PROGRESSBAR_SPINNING()));

    a = INSERT_TREEVIEW_LISTVIEW = new QAction(tr("&ListView (TreeView)"), this);
    connect(INSERT_TREEVIEW_LISTVIEW, SIGNAL(triggered()), this, SLOT(event_INSERT_TREEVIEW_LISTVIEW()));

    a = INSERT_LISTBOX_ICONMODE = new QAction(tr("&ListBox (IconMode)"), this);
    connect(INSERT_LISTBOX_ICONMODE, SIGNAL(triggered()), this, SLOT(event_INSERT_LISTBOX_ICONMODE()));

    a = INSERT_IMAGE = new QAction(/*kbasicIcon(kbasicControlPath("image.png")), */tr("&ImageBox"), this);
    //INSERT_IMAGE->setStatusTip(tr("Image"));
    connect(INSERT_IMAGE, SIGNAL(triggered()), this, SLOT(event_INSERT_IMAGE()));

    a = INSERT_TEXTBOX_PASSWORD = new QAction(tr("&Password (TextBox)"), this);
    connect(INSERT_TEXTBOX_PASSWORD, SIGNAL(triggered()), this, SLOT(event_INSERT_TEXTBOX_PASSWORD()));

    a = INSERT_LABEL_LINK = new QAction(tr("&Link (Label)"), this);
    connect(INSERT_LABEL_LINK, SIGNAL(triggered()), this, SLOT(event_INSERT_LABEL_LINK()));

    a = INSERT_LINE_VERTICAL = new QAction(tr("Vertic&al Line"), this);
    connect(INSERT_LINE_VERTICAL, SIGNAL(triggered()), this, SLOT(event_INSERT_LINE_VERTICAL()));

    a = INSERT_LINE_HORIZONTAL = new QAction(tr("Horizonta&l Line"), this);
    connect(INSERT_LINE_HORIZONTAL, SIGNAL(triggered()), this, SLOT(event_INSERT_LINE_HORIZONTAL()));

    // CONTROL
    a = INSERT_UDPSOCKET = new QAction(tr("&UdpSocket"), this);
    connect(INSERT_UDPSOCKET, SIGNAL(triggered()), this, SLOT(event_INSERT_UDPSOCKET()));

    a = INSERT_SCROLLBAR = new QAction(tr("&ScrollBar"), this);
    connect(INSERT_SCROLLBAR, SIGNAL(triggered()), this, SLOT(event_INSERT_SCROLLBAR()));

    a = INSERT_SPINBOX = new QAction(tr("&SpinBox"), this);
    connect(INSERT_SPINBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_SPINBOX()));

    a = INSERT_TOOLBUTTON = new QAction(tr("&ToolButton"), this);
    connect(INSERT_TOOLBUTTON, SIGNAL(triggered()), this, SLOT(event_INSERT_TOOLBUTTON()));

    a = INSERT_SLIDER = new QAction(tr("&Slider"), this);
    connect(INSERT_SLIDER, SIGNAL(triggered()), this, SLOT(event_INSERT_SLIDER()));

    a = INSERT_TOOLBARVIEW = new QAction(tr("&ToolBarView"), this);
    connect(INSERT_TOOLBARVIEW, SIGNAL(triggered()), this, SLOT(event_INSERT_TOOLBARVIEW()));

    a = INSERT_FORMSVIEW = new QAction(tr("&FormsView"), this);
    connect(INSERT_FORMSVIEW, SIGNAL(triggered()), this, SLOT(event_INSERT_FORMSVIEW()));

    a = INSERT_SVG = new QAction(tr("&SvgBox"), this);
    connect(INSERT_SVG, SIGNAL(triggered()), this, SLOT(event_INSERT_SVG()));

    a = INSERT_COMMANDLINKBUTTON = new QAction(tr("&CommandLinkButton"), this);
    connect(INSERT_COMMANDLINKBUTTON, SIGNAL(triggered()), this, SLOT(event_INSERT_COMMANDLINKBUTTON()));

    a = INSERT_RESIZEBOX = new QAction(tr("&ResizeBox"), this);
    connect(INSERT_RESIZEBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_RESIZEBOX()));

    a = INSERT_HEADER = new QAction(/*kbasicIcon(kbasicControlPath("vsplit.png")), */tr("&Header"), this);
    connect(INSERT_HEADER, SIGNAL(triggered()), this, SLOT(event_INSERT_HEADER()));

    a = INSERT_SERIALPORT = new QAction(/*kbasicIcon(kbasicControlPath("vsplit.png")), */tr("&SerialPort"), this);
    connect(INSERT_SERIALPORT, SIGNAL(triggered()), this, SLOT(event_INSERT_SERIALPORT()));
    
    a = INSERT_FOOTER = new QAction(/*kbasicIcon(kbasicControlPath("vsplit.png")), */tr("&Footer"), this);
    connect(INSERT_FOOTER, SIGNAL(triggered()), this, SLOT(event_INSERT_FOOTER()));
    
    a = INSERT_VSPLIT = new QAction(/*kbasicIcon(kbasicControlPath("vsplit.png")), */tr("&VSplit"), this);
    connect(INSERT_VSPLIT, SIGNAL(triggered()), this, SLOT(event_INSERT_VSPLIT()));
    
    a = INSERT_HSPLIT = new QAction(/*kbasicIcon(kbasicControlPath("hsplit.png")), */tr("&HSplit"), this);
    connect(INSERT_HSPLIT, SIGNAL(triggered()), this, SLOT(event_INSERT_HSPLIT()));
    
    a = INSERT_VBOX = new QAction(/*kbasicIcon(kbasicControlPath("vbox.png")), */tr("&VBox"), this);
    connect(INSERT_VBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_VBOX()));

    a = INSERT_VBOX = new QAction(/*kbasicIcon(kbasicControlPath("vbox.png")), */tr("&VBox"), this);
    connect(INSERT_VBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_VBOX()));
    
    a = INSERT_VHBOX = new QAction(/*kbasicIcon(kbasicControlPath("vhbox.png")), */tr("(&VHBox)"), this);
    connect(INSERT_VHBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_VHBOX()));

    a = INSERT_HBOX = new QAction(/*kbasicIcon(kbasicControlPath("hbox.png")), */tr("&HBox"), this);
    connect(INSERT_HBOX, SIGNAL(triggered()), this, SLOT(event_INSERT_HBOX()));

    a = INSERT_BOX = new QAction(/*kbasicIcon(kbasicControlPath("box.png")), */tr("&Box"), this);
    connect(INSERT_BOX, SIGNAL(triggered()), this, SLOT(event_INSERT_BOX()));
    
    a = INSERT_HIDDEN = new QAction(/*kbasicIcon(kbasicControlPath("hidden.png")), */tr("&Hidden"), this);
    //INSERT_HIDDEN->setStatusTip(tr("Hidden"));
    connect(INSERT_HIDDEN, SIGNAL(triggered()), this, SLOT(event_INSERT_HIDDEN()));
/*
    INSERT_ACTIVEX = new QAction(kbasicIcon(kbasicControlPath("activex.png")), tr("&(ActiveX)"), this);
    INSERT_ACTIVEX->setStatusTip(tr("ActiveX"));
    connect(INSERT_ACTIVEX, SIGNAL(triggered()), this, SLOT(event_INSERT_ACTIVEX()));*/

    a = INSERT_TREEVIEW = new QAction(/*kbasicIcon(kbasicControlPath("treeview.png")), */tr("&TreeView"), this);
    //INSERT_TREEVIEW->setStatusTip(tr("TreeView"));
    connect(INSERT_TREEVIEW, SIGNAL(triggered()), this, SLOT(event_INSERT_TREEVIEW()));

    a = INSERT_TAB = new QAction(/*kbasicIcon(kbasicControlPath("tab.png")), */tr("&TabView"), this);
    //INSERT_TAB->setStatusTip(tr("Tab"));
    connect(INSERT_TAB, SIGNAL(triggered()), this, SLOT(event_INSERT_TAB()));

    a = INSERT_SOUND = new QAction(/*kbasicIcon(kbasicControlPath("timer.png")), */tr("&Sound"), this);
    connect(INSERT_SOUND, SIGNAL(triggered()), this, SLOT(event_INSERT_SOUND()));

    a = INSERT_MOVIE = new QAction(/*kbasicIcon(kbasicControlPath("timer.png")), */tr("&MovieBox"), this);
    connect(INSERT_MOVIE, SIGNAL(triggered()), this, SLOT(event_INSERT_MOVIE()));

    a = INSERT_WEB = new QAction(/*kbasicIcon(kbasicControlPath("timer.png")), */tr("&WebView"), this);
    connect(INSERT_WEB, SIGNAL(triggered()), this, SLOT(event_INSERT_WEB()));

    a = INSERT_TIMER = new QAction(/*kbasicIcon(kbasicControlPath("timer.png")), */tr("&Timer"), this);
    //INSERT_TIMER->setStatusTip(tr("Timer"));
    connect(INSERT_TIMER, SIGNAL(triggered()), this, SLOT(event_INSERT_TIMER()));

    a = INSERT_IMAGEBUTTON = new QAction(/*kbasicIcon(kbasicControlPath("imagebutton.png")), */tr("&ImageButton"), this);
    //INSERT_IMAGEBUTTON->setStatusTip(tr("ImageButton"));
    connect(INSERT_IMAGEBUTTON, SIGNAL(triggered()), this, SLOT(event_INSERT_IMAGEBUTTON()));

    a = INSERT_MENU = new QAction(/*kbasicIcon(kbasicControlPath("menu.png")), */tr("&Menu"), this);
    //INSERT_MENU->setStatusTip(tr("Menu"));
    connect(INSERT_MENU, SIGNAL(triggered()), this, SLOT(event_INSERT_MENU()));

    a = INSERT_CHILDMENU = new QAction(/*kbasicIcon(kbasicControlPath("CHILDMENU.png")), */tr("&ChildMenu"), this);
    //INSERT_CHILDMENU->setStatusTip(tr("CHILDMENU"));
    connect(INSERT_CHILDMENU, SIGNAL(triggered()), this, SLOT(event_INSERT_CHILDMENU()));

    a = INSERT_MENUBARITEM = new QAction(/*kbasicIcon(kbasicControlPath("menuitem.png")), */tr("&MenuBarItem"), this);
    //INSERT_MENUBARITEM->setStatusTip(tr("MenuItem"));
    connect(INSERT_MENUBARITEM, SIGNAL(triggered()), this, SLOT(event_INSERT_MENUBARITEM()));

    a = INSERT_MOVE = new QAction(/*kbasicIcon(kbasicControlPath("move.png")), */tr("&Move"), this);    
    //INSERT_MOVE->setStatusTip(tr("Move"));
    connect(INSERT_MOVE, SIGNAL(triggered()), this, SLOT(event_INSERT_MOVE()));

    a = INSERT_DELETE = new QAction(/*kbasicIcon(kbasicControlPath("delete.png")), */tr("&Delete"), this);
    //INSERT_DELETE->setStatusTip(tr("Delete"));
    connect(INSERT_DELETE, SIGNAL(triggered()), this, SLOT(event_INSERT_DELETE()));

    a = INSERT_TOOLBARITEM = new QAction(/*kbasicIcon(kbasicControlPath("toolbaritem.png")), */tr("&ToolBarItem"), this);
    //INSERT_TOOLBARITEM->setStatusTip(tr("ToolBarItem"));
    connect(INSERT_TOOLBARITEM, SIGNAL(triggered()), this, SLOT(event_INSERT_TOOLBARITEM()));

    a = INSERT_OPTION_KBASIC = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_OPTION_KBASIC.png")), */tr("Option KBasic (Default)"), this);
    //INSERT_OPTION_KBASIC->setStatusTip(tr("Option KBasic (Default)"));
    connect(INSERT_OPTION_KBASIC, SIGNAL(triggered()), this, SLOT(event_INSERT_OPTION_KBASIC()));

    a = INSERT_OPTION_OLDBASIC = new QAction(tr("Option OldBasic"), this);
    //INSERT_OPTION_OLDBASIC->setStatusTip(tr("Option OldBasic"));
    connect(INSERT_OPTION_OLDBASIC, SIGNAL(triggered()), this, SLOT(event_INSERT_OPTION_OLDBASIC()));

    a = INSERT_OPTION_VERYOLDBASIC = new QAction(tr("Option VeryOldBasic"), this);
    //INSERT_OPTION_VERYOLDBASIC->setStatusTip(tr("Option VeryOldBasic"));
    connect(INSERT_OPTION_VERYOLDBASIC, SIGNAL(triggered()), this, SLOT(event_INSERT_OPTION_VERYOLDBASIC()));

    a = INSERT_STATEMENT = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_STATEMENT.png")), */tr("&Statement..."), this);
    //INSERT_STATEMENT->setStatusTip(tr("Statement..."));
    connect(INSERT_STATEMENT, SIGNAL(triggered()), this, SLOT(event_INSERT_STATEMENT()));

    a = INSERT_ASSIGNMENT = new QAction(tr("&Assignment..."), this);
    //INSERT_ASSIGNMENT->setStatusTip(tr("Assignment..."));
    connect(INSERT_ASSIGNMENT, SIGNAL(triggered()), this, SLOT(event_INSERT_ASSIGNMENT()));

    a = INSERT_EXPRESSION = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_EXPRESSION.png")), */tr("E&xpression..."), this);
    //INSERT_EXPRESSION->setStatusTip(tr("Expression..."));
    connect(INSERT_EXPRESSION, SIGNAL(triggered()), this, SLOT(event_INSERT_EXPRESSION()));

    a = INSERT_OPERATOR = new QAction(tr("&Operator..."), this);
    //INSERT_OPERATOR->setStatusTip(tr("Operator..."));
    connect(INSERT_OPERATOR, SIGNAL(triggered()), this, SLOT(event_INSERT_OPERATOR()));

    a = INSERT_IF = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_IF.png")), */tr("Single Decision: If Then Else"), this);
    //INSERT_IF->setStatusTip(tr("Single Decision: If Then Else"));
    connect(INSERT_IF, SIGNAL(triggered()), this, SLOT(event_INSERT_IF()));

    a = INSERT_SELECT = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_SELECT.png")), */tr("Multi Decision: Select Case"), this);
    //INSERT_SELECT->setStatusTip(tr("Multi Decision: Select Case"));
    connect(INSERT_SELECT, SIGNAL(triggered()), this, SLOT(event_INSERT_SELECT()));

    a = INSERT_FORNEXT = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_FORNEXT.png")), */tr("Count Loop: For Next"), this);
    //INSERT_FORNEXT->setStatusTip(tr("Count Loop: For Next"));
    connect(INSERT_FORNEXT, SIGNAL(triggered()), this, SLOT(event_INSERT_FORNEXT()));

    a = INSERT_WHILELOOP = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_WHILELOOP.png")), */tr("Head Loop: Do While ... Loop"), this);
    //INSERT_WHILELOOP->setStatusTip(tr("Head Loop: Do While ... Loop"));
    connect(INSERT_WHILELOOP, SIGNAL(triggered()), this, SLOT(event_INSERT_WHILELOOP()));

    a = INSERT_LOOPWHILE = new QAction(tr("Foot Loop: Do ... Loop While"), this);
    //INSERT_LOOPWHILE->setStatusTip(tr("Foot Loop: Do ... Loop While"));
    connect(INSERT_LOOPWHILE, SIGNAL(triggered()), this, SLOT(event_INSERT_LOOPWHILE()));

    a = INSERT_EXCEPTION = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_EXCEPTION.png")), */tr("&Exception..."), this);
    //INSERT_EXCEPTION->setStatusTip(tr("Exception"));
    connect(INSERT_EXCEPTION, SIGNAL(triggered()), this, SLOT(event_INSERT_EXCEPTION()));

    a = INSERT_VARIABLE = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_VARIABLE.png")), */tr("&Dim..."), this);
    //INSERT_VARIABLE->setStatusTip(tr("Dim..."));
    connect(INSERT_VARIABLE, SIGNAL(triggered()), this, SLOT(event_INSERT_VARIABLE()));

    a = INSERT_CONST = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_CONST.png")), */tr("&Const..."), this);
    //INSERT_CONST->setStatusTip(tr("Const..."));
    connect(INSERT_CONST, SIGNAL(triggered()), this, SLOT(event_INSERT_CONST()));

    a = INSERT_FIELDS_LINE = new QAction(tr("Current &Line"), this);
    //INSERT_FIELDS_LINE->setStatusTip(tr("Current Line"));
    connect(INSERT_FIELDS_LINE, SIGNAL(triggered()), this, SLOT(event_INSERT_FIELDS_LINE()));

    a = INSERT_FIELDS_SCOPE = new QAction(tr("Current S&cope Name"), this);
    //INSERT_FIELDS_SCOPE->setStatusTip(tr("Current Scope Name"));
    connect(INSERT_FIELDS_SCOPE, SIGNAL(triggered()), this, SLOT(event_INSERT_FIELDS_SCOPE()));

    a = INSERT_FIELDS_CLASS = new QAction(tr("Current &Class Name"), this);
    //INSERT_FIELDS_CLASS->setStatusTip(tr("Current Class Name"));
    connect(INSERT_FIELDS_CLASS, SIGNAL(triggered()), this, SLOT(event_INSERT_FIELDS_CLASS()));

    a = INSERT_FIELDS_MODULE = new QAction(tr("Current &Module Name"), this);
    //INSERT_FIELDS_MODULE->setStatusTip(tr("Current Module Name"));
    connect(INSERT_FIELDS_MODULE, SIGNAL(triggered()), this, SLOT(event_INSERT_FIELDS_MODULE()));

    a = INSERT_FIELDS_SUB = new QAction(tr("Current &Sub Name"), this);
    //INSERT_FIELDS_SUB->setStatusTip(tr("Current Sub Name"));
    connect(INSERT_FIELDS_SUB, SIGNAL(triggered()), this, SLOT(event_INSERT_FIELDS_SUB()));

    a = INSERT_SUB = new QAction(
                                 #ifndef MAC
                                 kbasicIcon(kbasicPath("ide/INSERT_SUB.png")), 
#endif
                                 tr("&Sub..."), this);
    //INSERT_SUB->setStatusTip(tr("Sub..."));
    connect(INSERT_SUB, SIGNAL(triggered()), this, SLOT(event_INSERT_SUB()));

    a = INSERT_FUNCTION = new QAction(
    #ifndef MAC
    kbasicIcon(kbasicPath("ide/INSERT_FUNCTION.png")), 
#endif
    tr("&Function..."), this);
    //INSERT_FUNCTION->setStatusTip(tr("Function..."));
    connect(INSERT_FUNCTION, SIGNAL(triggered()), this, SLOT(event_INSERT_FUNCTION()));

    a = INSERT_PROPERTY = new QAction(tr("&Property..."), this);
    //INSERT_PROPERTY->setStatusTip(tr("Property"));
    connect(INSERT_PROPERTY, SIGNAL(triggered()), this, SLOT(event_INSERT_PROPERTY()));

    a = INSERT_TYPE = new QAction(
    #ifndef MAC
    kbasicIcon(kbasicPath("ide/INSERT_TYPE.png")), 
#endif
                                  tr("&Type..."), this);
    //INSERT_TYPE->setStatusTip(tr("Type..."));
    connect(INSERT_TYPE, SIGNAL(triggered()), this, SLOT(event_INSERT_TYPE()));

    a = INSERT_ENUM = new QAction(
                                  #ifndef MAC
                                  kbasicIcon(kbasicPath("ide/INSERT_ENUM.png")), 
#endif
                                  
                                  tr("E&num..."), this);
    //INSERT_ENUM->setStatusTip(tr("Enum..."));
    connect(INSERT_ENUM, SIGNAL(triggered()), this, SLOT(event_INSERT_ENUM()));

    a = INSERT_REMARK = new QAction(/*kbasicIcon(kbasicPath("ide/INSERT_REMARK.png")), */tr("&Rem..."), this);
    //INSERT_REMARK->setStatusTip(tr("Rem..."));
    connect(INSERT_REMARK, SIGNAL(triggered()), this, SLOT(event_INSERT_REMARK()));


    FORMAT_ALIGN_TOP = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_ALIGN_TOP.png")), 
#endif
    tr("Align &Top"), this);
    //FORMAT_ALIGN_TOP->setStatusTip(tr("Align Top"));
    connect(FORMAT_ALIGN_TOP, SIGNAL(triggered()), this, SLOT(event_FORMAT_ALIGN_TOP()));

    FORMAT_ALIGN_BOTTOM = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_ALIGN_BOTTOM.png")), 
#endif
    tr("Align &Bottom"), this);
    //FORMAT_ALIGN_BOTTOM->setStatusTip(tr("Align Bottom"));
    connect(FORMAT_ALIGN_BOTTOM, SIGNAL(triggered()), this, SLOT(event_FORMAT_ALIGN_BOTTOM()));

    FORMAT_ALIGN_LEFT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_ALIGN_LEFT.png")), 
#endif
    tr("Align &Left"), this);
    //FORMAT_ALIGN_LEFT->setStatusTip(tr("Align Left"));
    connect(FORMAT_ALIGN_LEFT, SIGNAL(triggered()), this, SLOT(event_FORMAT_ALIGN_LEFT()));

    FORMAT_ALIGN_RIGHT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_ALIGN_RIGHT.png")), 
#endif
    tr("Align &Right"), this);
    //FORMAT_ALIGN_RIGHT->setStatusTip(tr("Align Right"));
    connect(FORMAT_ALIGN_RIGHT, SIGNAL(triggered()), this, SLOT(event_FORMAT_ALIGN_RIGHT()));

    FORMAT_SET_SAME_WIDTH = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_SET_SAME_WIDTH.png")), 
#endif
    tr("Set Same &Width"), this);
    //FORMAT_SET_SAME_WIDTH->setStatusTip(tr("Set Same Width"));
    connect(FORMAT_SET_SAME_WIDTH, SIGNAL(triggered()), this, SLOT(event_FORMAT_SET_SAME_WIDTH()));

    FORMAT_SET_SAME_HEIGHT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_SET_SAME_HEIGHT.png")), 
#endif
    tr("Set Same H&eight"), this);
    //FORMAT_SET_SAME_HEIGHT->setStatusTip(tr("Set Same Height"));
    connect(FORMAT_SET_SAME_HEIGHT, SIGNAL(triggered()), this, SLOT(event_FORMAT_SET_SAME_HEIGHT()));

    a = FORMAT_SET_SAME_SIZE = new QAction(tr("Set Same &Size"), this);
    //FORMAT_SET_SAME_SIZE->setStatusTip(tr("Set Same Size"));
    connect(FORMAT_SET_SAME_SIZE, SIGNAL(triggered()), this, SLOT(event_FORMAT_SET_SAME_SIZE()));

    FORMAT_LAYOUT_HORIZONTALLY = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_LAYOUT_HORIZONTALLY.png")), 
#endif
    tr("Lay Out &Horizontally"), this);
    //FORMAT_LAYOUT_HORIZONTALLY->setStatusTip(tr("Lay Out Horizontally"));
    connect(FORMAT_LAYOUT_HORIZONTALLY, SIGNAL(triggered()), this, SLOT(event_FORMAT_LAYOUT_HORIZONTALLY()));

    FORMAT_LAYOUT_VERTICALLY = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_LAYOUT_VERTICALLY.png")), 
#endif
    tr("Lay Out &Vertically"), this);
    //FORMAT_LAYOUT_VERTICALLY->setStatusTip(tr("Lay Out Vertically"));
    connect(FORMAT_LAYOUT_VERTICALLY, SIGNAL(triggered()), this, SLOT(event_FORMAT_LAYOUT_VERTICALLY()));

    FORMAT_MOVE_TO_FRONT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_MOVE_TO_FRONT.png")), 
#endif
    tr("ZOrder: Move To Top"), this);
    //FORMAT_MOVE_TO_FRONT->setStatusTip(tr("Move To Top"));
    connect(FORMAT_MOVE_TO_FRONT, SIGNAL(triggered()), this, SLOT(event_FORMAT_MOVE_TO_FRONT()));

    FORMAT_MOVE_TO_BACK = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_MOVE_TO_BACK.png")), 
#endif
    tr("ZOrder: Move To Back"), this);
    //FORMAT_MOVE_TO_BACK->setStatusTip(tr("Move To Back"));
    connect(FORMAT_MOVE_TO_BACK, SIGNAL(triggered()), this, SLOT(event_FORMAT_MOVE_TO_BACK()));


    FORMAT_MOVE_UP = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_MOVE_UP.png")), 
#endif
    tr("Move Up"), this);
    connect(FORMAT_MOVE_UP, SIGNAL(triggered()), this, SLOT(event_FORMAT_MOVE_UP()));



    FORMAT_MOVE_DOWN = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_MOVE_DOWN.png")), 
#endif
    tr("Move Down"), this);
    connect(FORMAT_MOVE_DOWN, SIGNAL(triggered()), this, SLOT(event_FORMAT_MOVE_DOWN()));


    FORMAT_MOVE_LEFT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_MOVE_LEFT.png")), 
#endif
    tr("Move Left"), this);
    connect(FORMAT_MOVE_LEFT, SIGNAL(triggered()), this, SLOT(event_FORMAT_MOVE_LEFT()));


    FORMAT_MOVE_RIGHT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/FORMAT_MOVE_RIGHT.png")), 
#endif
    tr("Move Right"), this);
    connect(FORMAT_MOVE_RIGHT, SIGNAL(triggered()), this, SLOT(event_FORMAT_MOVE_RIGHT()));



    TRANSLATION_ADD = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/TRANSLATION_ADD.png")), 
#endif
    tr("Add Language"), this);
    connect(TRANSLATION_ADD, SIGNAL(triggered()), this, SLOT(event_TRANSLATION_ADD()));


    TRANSLATION_REMOVE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/TRANSLATION_REMOVE.png")), 
#endif
    tr("Remove Language"), this);
    connect(TRANSLATION_REMOVE, SIGNAL(triggered()), this, SLOT(event_TRANSLATION_REMOVE()));



    PROJECT_DATABASE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/PROJECT_DATABASE.png")), 
#endif
    tr("&Database Connection..."), this);

    //PROJECT_DATABASE->setStatusTip(tr("Database Connection..."));
    connect(PROJECT_DATABASE, SIGNAL(triggered()), this, SLOT(event_PROJECT_DATABASE()));

    PROJECT_TRANSLATION = new QAction(/*kbasicIcon(kbasicPath("ide/PROJECT_TRANSLATION.png")), */tr("&Translation..."), this);
    connect(PROJECT_TRANSLATION, SIGNAL(triggered()), this, SLOT(event_PROJECT_TRANSLATION()));


    a = PROJECT_SET_AS_DEFAULT = new QAction(tr("Set As Default Project"), this);
    //PROJECT_SET_AS_DEFAULT->setStatusTip(tr("Set As Default Project"));
    connect(PROJECT_SET_AS_DEFAULT, SIGNAL(triggered()), this, SLOT(event_PROJECT_SET_AS_DEFAULT()));

    a = PROJECT_PROPERTIES_OF_PROJECT = new QAction(tr("&Properties Of Project"), this);
    //PROJECT_PROPERTIES_OF_PROJECT->setStatusTip(tr("Properties Of Project"));
    connect(PROJECT_PROPERTIES_OF_PROJECT, SIGNAL(triggered()), this, SLOT(event_PROJECT_PROPERTIES_OF_PROJECT()));



    a = RUN_RUN_PROJECT = new QAction(/*kbasicIcon(kbasicPath("ide/RUN_RUN_PROJECT.png")), */tr("&Run Current Project"), this);
    //RUN_RUN_PROJECT->setStatusTip(tr("Run Always Project"));
    connect(RUN_RUN_PROJECT, SIGNAL(triggered()), this, SLOT(event_RUN_RUN_PROJECT()));

    RUN_RUN_PCODE2 = new QAction(
//#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_RUN_PCODE2.png")), 
//#endif
    tr("&Start"), this);
    RUN_RUN_PCODE2->setShortcut(tr("F5"));
    //RUN_RUN_PCODE2->setStatusTip(tr("Start"));
    connect(RUN_RUN_PCODE2, SIGNAL(triggered()), this, SLOT(event_RUN_RUN_PCODE2()));

    RUN_CONTINUE_PCODE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_CONTINUE_PCODE.png")), 
#endif
    tr("&Continue"), this);
    RUN_CONTINUE_PCODE->setShortcut(tr("F5"));
    connect(RUN_CONTINUE_PCODE, SIGNAL(triggered()), this, SLOT(event_RUN_CONTINUE_PCODE()));

    RUN_PAUSE = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_PAUSE.png")), 
#endif
    tr("Pause"), this);
    //RUN_PAUSE->setStatusTip(tr("Pause"));
    //connect(RUN_PAUSE, SIGNAL(triggered()), this, SLOT(event_RUN_PAUSE()));

    RUN_STOP = new QAction(
//#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_STOP.png")), 
//#endif
    tr("Stop"), this);
    RUN_STOP->setShortcut(tr("SHIFT+F5"));//CTRL+Pause
    //RUN_STOP->setStatusTip(tr("Stop"));
    connect(RUN_STOP, SIGNAL(triggered()), this, SLOT(event_RUN_STOP()));

    RUN_BUILD = new QAction(
//#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_BUILD.png")), 
//#endif
    tr("Bui&ld"), this);
    RUN_BUILD->setShortcut(tr("F6"));
    //RUN_BUILD->setStatusTip(tr("Build"));
    connect(RUN_BUILD, SIGNAL(triggered()), this, SLOT(event_RUN_BUILD()));

    a = RUN_BUILD_ALL = new QAction(tr("Rebui&ld All"), this);
    //RUN_BUILD_ALL->setStatusTip(tr("Rebuild All"));
    connect(RUN_BUILD_ALL, SIGNAL(triggered()), this, SLOT(event_RUN_BUILD_ALL()));

    a = RUN_SUB = new QAction(/*kbasicIcon(kbasicPath("ide/RUN_SUB.png")), */tr("Run Current &Sub"), this);
    //RUN_SUB->setStatusTip(tr("Run Sub"));
    connect(RUN_SUB, SIGNAL(triggered()), this, SLOT(event_RUN_SUB()));

    a = RUN_FORM = new QAction(/*kbasicIcon(kbasicPath("ide/RUN_SUB.png")), */tr("Run Current &Form"), this);

    //RUN_SUB->setStatusTip(tr("Run Sub"));
    connect(RUN_FORM, SIGNAL(triggered()), this, SLOT(event_RUN_FORM()));


    /*
    RUN_PCODEVIEWER = new QAction(kbasicIcon(kbasicPath("ide/RUN_PCODEVIEWER.png")), tr("&PCode Viewer"), this);
    RUN_PCODEVIEWER->setStatusTip(tr("PCode Viewer"));
    connect(RUN_PCODEVIEWER, SIGNAL(triggered()), this, SLOT(event_RUN_PCODEVIEWER()));
*/
    /*
    RUN_RUN_PCODE = new QAction(tr("&Run With Virtual Machine Info"), this);
    //RUN_RUN_PCODE->setStatusTip(tr("Run With Virtual Machine Info"));
    connect(RUN_RUN_PCODE, SIGNAL(triggered()), this, SLOT(event_RUN_RUN_PCODE()));
    */

    a = RUN_RUN_PCODE3 = new QAction(tr("&Debug With Virtual Machine Info"), this);

    //RUN_RUN_PCODE3->setStatusTip(tr("Debug With Virtual Machine Info"));
    connect(RUN_RUN_PCODE3, SIGNAL(triggered()), this, SLOT(event_RUN_RUN_PCODE3()));

    RUN_RUN = new QAction(/*kbasicIcon(kbasicPath("ide/RUN_RUN.png")), */tr("Run &With Virtual Machine Info (slowest mode)"), this);
    //RUN_RUN->setStatusTip(tr("Run With Virtual Machine Info (slowest mode)"));
    connect(RUN_RUN, SIGNAL(triggered()), this, SLOT(event_RUN_RUN()));

#if defined(WINDOWS)
    a = PROJECT_MAKE_RUNTIME_WINDOWS = new QAction(kbasicIcon(kbasicPath("ide/RUN_BINARY.png")), tr("Compile For Windows (on Windows only)"), this);
#else
    a = PROJECT_MAKE_RUNTIME_WINDOWS = new QAction(tr("Compile For Windows (on Windows only)"), this);
#endif

    //PROJECT_MAKE_RUNTIME_WINDOWS->setStatusTip(tr("Compile For Windows"));
    connect(PROJECT_MAKE_RUNTIME_WINDOWS, SIGNAL(triggered()), this, SLOT(event_PROJECT_MAKE_RUNTIME_WINDOWS()));
    
#if defined(WINDOWS)
    PROJECT_MAKE_RUNTIME_WINDOWS->setEnabled(true);
#elif defined(LINUX)
    PROJECT_MAKE_RUNTIME_WINDOWS->setEnabled(false);
#elif defined(MAC)
    PROJECT_MAKE_RUNTIME_WINDOWS->setEnabled(false);
#endif


#if defined(LINUX)
    a = PROJECT_MAKE_RUNTIME_LINUX = new QAction(kbasicIcon(kbasicPath("ide/RUN_BINARY.png")), tr("Compile For Linux (on Linux only)"), this);
#else
    a = PROJECT_MAKE_RUNTIME_LINUX = new QAction(/*kbasicIcon(kbasicPath("ide/PROJECT_MAKE_RUNTIME_LINUX.png")), */tr("Compile For Linux (on Linux only)"), this);
#endif

    //PROJECT_MAKE_RUNTIME_LINUX->setStatusTip(tr("Compile For Linux (on Linux only)"));
    connect(PROJECT_MAKE_RUNTIME_LINUX, SIGNAL(triggered()), this, SLOT(event_PROJECT_MAKE_RUNTIME_LINUX()));
    
#if defined(WINDOWS)
    PROJECT_MAKE_RUNTIME_LINUX->setEnabled(false);
#elif defined(LINUX)
    PROJECT_MAKE_RUNTIME_LINUX->setEnabled(true);
#elif defined(MAC)
    PROJECT_MAKE_RUNTIME_LINUX->setEnabled(false);
#endif



#if defined(MAC)
    a = PROJECT_MAKE_RUNTIME_MACOS = new QAction(kbasicIcon(kbasicPath("ide/RUN_BINARY.png")), tr("Compile For Mac OS X (on Mac only)"), this);
#else
    a = PROJECT_MAKE_RUNTIME_MACOS = new QAction(/*kbasicIcon(kbasicPath("ide/PROJECT_MAKE_RUNTIME_MACOS.png")), */tr("Compile For Mac OS X (on Mac only)"), this);
#endif

    //PROJECT_MAKE_RUNTIME_MACOS->setStatusTip(tr("Compile For Mac OS X (on Mac only)"));
    connect(PROJECT_MAKE_RUNTIME_MACOS, SIGNAL(triggered()), this, SLOT(event_PROJECT_MAKE_RUNTIME_MACOS()));
    
    
#if defined(WINDOWS)
    PROJECT_MAKE_RUNTIME_MACOS->setEnabled(false);
#elif defined(LINUX)
    PROJECT_MAKE_RUNTIME_MACOS->setEnabled(false);
#elif defined(MAC)
    PROJECT_MAKE_RUNTIME_MACOS->setEnabled(true);
#endif


    a = RUN_RUN_IN_DEBUG = new QAction(/*kbasicIcon(kbasicPath("ide/RUN_RUN_IN_DEBUG.png")), */tr("Run In &Debug"), this);

    RUN_RUN_IN_DEBUG->setShortcut(tr("CTRL+F5"));
    //RUN_RUN_IN_DEBUG->setStatusTip(tr("Run In Debug"));
    connect(RUN_RUN_IN_DEBUG, SIGNAL(triggered()), this, SLOT(event_RUN_RUN_IN_DEBUG()));

    a = RUN_RUN_IN_DEBUG2 = new QAction(tr("&Debug From Beginning"), this);
    RUN_RUN_IN_DEBUG2->setShortcut(tr("CTRL+SHIFT+F5"));
    //RUN_RUN_IN_DEBUG2->setStatusTip(tr("Debug From Beginning"));
    connect(RUN_RUN_IN_DEBUG2, SIGNAL(triggered()), this, SLOT(event_RUN_RUN_IN_DEBUG2()));

    RUN_SINGLE_STEP = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_SINGLE_STEP.png")), 
#endif
    tr("Step &Into"), this);
    RUN_SINGLE_STEP->setShortcut(tr("F8"));
    //RUN_SINGLE_STEP->setStatusTip(tr("Step Into"));
    connect(RUN_SINGLE_STEP, SIGNAL(triggered()), this, SLOT(event_RUN_SINGLE_STEP()));

    RUN_STEP_OVER = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_STEP_OVER.png")), 
#endif
    tr("Step &Over"), this);
    RUN_STEP_OVER->setShortcut(tr("SHIFT+F8"));
    //RUN_STEP_OVER->setStatusTip(tr("Step Over"));
    connect(RUN_STEP_OVER, SIGNAL(triggered()), this, SLOT(event_RUN_STEP_OVER()));

    RUN_STEP_OUT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_STEP_OUT.png")), 
#endif
    tr("Step O&ut"), this);
    RUN_STEP_OUT->setShortcut(tr("CTRL+SHIFT+F8"));
    //RUN_STEP_OUT->setStatusTip(tr("Step Out"));
    connect(RUN_STEP_OUT, SIGNAL(triggered()), this, SLOT(event_RUN_STEP_OUT()));

    RUN_TO_CURSOR = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_TO_CURSOR.png")), 
#endif
    tr("Run &To Cursor"), this);
    RUN_TO_CURSOR->setShortcut(tr("CTRL+F8"));
    //RUN_TO_CURSOR->setStatusTip(tr("Step Out"));
    connect(RUN_TO_CURSOR, SIGNAL(triggered()), this, SLOT(event_RUN_TO_CURSOR()));
/*
    VIEW_LOCAL = new QAction(tr("Local Scope"), this);
    VIEW_LOCAL->setStatusTip(tr("Local Scope"));
    connect(VIEW_LOCAL, SIGNAL(triggered()), this, SLOT(event_VIEW_LOCAL()));

    VIEW_GLOBAL = new QAction(tr("Global Scope"), this);
    VIEW_GLOBAL->setStatusTip(tr("Global Scope"));
    connect(VIEW_GLOBAL, SIGNAL(triggered()), this, SLOT(event_VIEW_GLOBAL()));

    VIEW_STACK = new QAction(kbasicIcon(kbasicPath("ide/VIEW_STACK.png")), tr("Calling Stack"), this);
    VIEW_STACK->setStatusTip(tr("Calling Stack"));
    connect(VIEW_STACK, SIGNAL(triggered()), this, SLOT(event_VIEW_STACK()));
*/
    a = RUN_CLEAR_ALL_BREAKPOINTS = new QAction(tr("Clear All Breakpoints"), this);

    //RUN_CLEAR_ALL_BREAKPOINTS->setStatusTip(tr("Clears all breakpoints"));
    connect(RUN_CLEAR_ALL_BREAKPOINTS, SIGNAL(triggered()), this, SLOT(event_EDIT_CLEAR_ALL_BREAKPOINTS()));

    RUN_SET_BREAKPOINT = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/RUN_SET_BREAKPOINT.png")), 
#endif
    tr("Set/Unset Breakpoint"), this);
#ifdef MAC
    RUN_SET_BREAKPOINT->setShortcut(tr("ALT+F9"));
#else
    RUN_SET_BREAKPOINT->setShortcut(tr("F9"));
#endif
    //RUN_SET_BREAKPOINT->setStatusTip(tr("Sets/Unsets breakpoint"));
    connect(RUN_SET_BREAKPOINT, SIGNAL(triggered()), this, SLOT(event_EDIT_SET_BREAKPOINT()));

    a = RUN_NEXT_BREAKPOINT = new QAction(tr("Next Breakpoint"), this);
#ifdef MAC
    RUN_NEXT_BREAKPOINT->setShortcut(tr("ALT+SHIFT+F9"));
#else
    RUN_NEXT_BREAKPOINT->setShortcut(tr("SHIFT+F9"));
#endif
    //RUN_NEXT_BREAKPOINT->setStatusTip(tr("Next Breakpoint"));
    connect(RUN_NEXT_BREAKPOINT, SIGNAL(triggered()), this, SLOT(event_EDIT_NEXT_BREAKPOINT()));

    a = RUN_PREVIOUS_BREAKPOINT = new QAction(tr("Previous Breakpoint"), this);
#ifdef MAC
    RUN_PREVIOUS_BREAKPOINT->setShortcut(tr("ALT+CTRL+SHIFT+F9"));
#else
    RUN_PREVIOUS_BREAKPOINT->setShortcut(tr("CTRL+SHIFT+F9"));
#endif
    //RUN_PREVIOUS_BREAKPOINT->setStatusTip(tr("Previous Breakpoint"));
    connect(RUN_PREVIOUS_BREAKPOINT, SIGNAL(triggered()), this, SLOT(event_EDIT_PREVIOUS_BREAKPOINT()));

/*
    TOOLS_EXTERN_TOOLS = new QAction(tr("Extern T&ools..."), this);
    TOOLS_EXTERN_TOOLS->setStatusTip(tr("Extern Tools..."));
    connect(TOOLS_EXTERN_TOOLS, SIGNAL(triggered()), this, SLOT(event_TOOLS_EXTERN_TOOLS()));
*/
    a = TOOLS_SELFTEST = new QAction(tr("S&elf Test..."), this);
    //TOOLS_SELFTEST->setStatusTip(tr("Self Test..."));
    connect(TOOLS_SELFTEST, SIGNAL(triggered()), this, SLOT(event_TOOLS_SELFTEST()));

    TOOLS_RESOURCES = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/TOOLS_RESOURCES.png")), 
#endif
    tr("&Resources"), this);
    //FILE_PREFERENCES->setStatusTip(tr("Preferences"));
    connect(TOOLS_RESOURCES, SIGNAL(triggered()), this, SLOT(event_TOOLS_RESOURCES()));

    FILE_PREFERENCES = new QAction(tr("Preferen&ces"), this);
    //FILE_PREFERENCES->setStatusTip(tr("Preferences"));
    connect(FILE_PREFERENCES, SIGNAL(triggered()), this, SLOT(event_FILE_PREFERENCES()));



    EXAMPLE_BROWSER = new QAction(
#ifndef MAC
    kbasicIcon(kbasicPath("ide/EXAMPLE_BROWSER.png")), 
#endif
    tr("Example Browser"), this);
    connect(EXAMPLE_BROWSER, SIGNAL(triggered()), this, SLOT(event_EXAMPLE_BROWSER()));


    HELP_WEBSITE = new QAction(/*kbasicIcon(kbasicPath("ide/HELP_LANGUAGE_REFERENCE.png")), */tr("&KBasic Website"), this);
    //HELP_LANGUAGE_REFERENCE->setStatusTip(tr("Language Reference"));
    connect(HELP_WEBSITE, SIGNAL(triggered()), this, SLOT(event_HELP_WEBSITE()));

    HELP_FRAMEWORK = new QAction(/*kbasicIcon(kbasicPath("ide/HELP_LANGUAGE_REFERENCE.png")), */tr("&KBasic Framework"), this);
    //HELP_LANGUAGE_REFERENCE->setStatusTip(tr("Language Reference"));
    connect(HELP_FRAMEWORK, SIGNAL(triggered()), this, SLOT(event_HELP_FRAMEWORK()));

    HELP_LANGUAGE_REFERENCE = new QAction(/*kbasicIcon(kbasicPath("ide/HELP_LANGUAGE_REFERENCE.png")), */tr("&Language Reference"), this);
    //HELP_LANGUAGE_REFERENCE->setStatusTip(tr("Language Reference"));
    connect(HELP_LANGUAGE_REFERENCE, SIGNAL(triggered()), this, SLOT(event_HELP_LANGUAGE_REFERENCE()));

    HELP_KBASIC_BOOK = new QAction(tr("&Manual: The KBasic Book"), this);
    //HELP_KBASIC_BOOK->setStatusTip(tr("The KBasic Book"));
    connect(HELP_KBASIC_BOOK, SIGNAL(triggered()), this, SLOT(event_HELP_KBASIC_BOOK()));

    HELP_SYNTAX = new QAction(/*kbasicIcon(kbasicPath("ide/HELP_SYNTAX.png")), */tr("Synta&x"), this);
    //HELP_SYNTAX->setStatusTip(tr("Synta&x"));
    connect(HELP_SYNTAX, SIGNAL(triggered()), this, SLOT(event_HELP_SYNTAX()));

    HELP_KBASIC_BUG = new QAction(tr("Bug Report"), this);
    //HELP_KBASIC_BUG->setStatusTip(tr("Bug Report"));
    connect(HELP_KBASIC_BUG, SIGNAL(triggered()), this, SLOT(event_HELP_KBASIC_BUG()));
    
    HELP_KBASIC_CONTRIBUTE = new QAction(tr("Contribute"), this);
    connect(HELP_KBASIC_CONTRIBUTE, SIGNAL(triggered()), this, SLOT(event_HELP_KBASIC_CONTRIBUTE()));
    
    HELP_ABOUT = new QAction(tr("A&bout KBasic"), this);
    //HELP_ABOUT->setStatusTip(tr("About KBasic"));
    connect(HELP_ABOUT, SIGNAL(triggered()), this, SLOT(event_HELP_ABOUT()));    


    HELP_OFFLINE_DESCRIPTION = new QAction(tr("&Description"), this);
    connect(HELP_OFFLINE_DESCRIPTION, SIGNAL(triggered()), this, SLOT(event_HELP_OFFLINE_DESCRIPTION()));    

    HELP_OFFLINE_OVERVIEW = new QAction(tr("&Overview"), this);
    connect(HELP_OFFLINE_OVERVIEW, SIGNAL(triggered()), this, SLOT(event_HELP_OFFLINE_OVERVIEW()));    

    HELP_OFFLINE_FRAMEWORK = new QAction(tr("&KBasic Framework"), this);
    connect(HELP_OFFLINE_FRAMEWORK, SIGNAL(triggered()), this, SLOT(event_HELP_OFFLINE_FRAMEWORK()));    

    HELP_OFFLINE_KEYWORDS = new QAction(tr("Language Reference: &Keywords"), this);
    connect(HELP_OFFLINE_KEYWORDS, SIGNAL(triggered()), this, SLOT(event_HELP_OFFLINE_KEYWORDS()));    

    HELP_OFFLINE_BUILTINS = new QAction(tr("Language Reference: &Builtin Functions"), this);
    connect(HELP_OFFLINE_BUILTINS, SIGNAL(triggered()), this, SLOT(event_HELP_OFFLINE_BUILTINS()));    

    HELP_OFFLINE_MANUAL = new QAction(tr("&Manual: The KBasic Book"), this);
    connect(HELP_OFFLINE_MANUAL, SIGNAL(triggered()), this, SLOT(event_HELP_OFFLINE_MANUAL()));    

    HELP_OFFLINE_SYNTAX = new QAction(tr("Synta&x"), this);
    connect(HELP_OFFLINE_SYNTAX, SIGNAL(triggered()), this, SLOT(event_HELP_OFFLINE_SYNTAX()));    

    HELP_OFFLINE_MISC = new QAction(tr("&Misc. Issues"), this);
    connect(HELP_OFFLINE_MISC, SIGNAL(triggered()), this, SLOT(event_HELP_OFFLINE_MISC()));    



    closeAct = new QAction(tr("Cl&ose"), this);
#ifndef LINUX
    closeAct->setShortcut(tr("Ctrl+F4"));
#endif
    //closeAct->setStatusTip(tr("Close the active window"));
    connect(closeAct, SIGNAL(triggered()), workspace, SLOT(closeActiveSubWindow()));


    closeAllAct = new QAction(tr("Close &All"), this);
    //closeAllAct->setStatusTip(tr("Close all the windows"));
    connect(closeAllAct, SIGNAL(triggered()), workspace, SLOT(closeAllSubWindows()));

    tileAct = new QAction(tr("&Tile"), this);
    //tileAct->setStatusTip(tr("Tile the windows"));
    connect(tileAct, SIGNAL(triggered()), workspace, SLOT(tileSubWindows()));

    cascadeAct = new QAction(tr("&Cascade"), this);
    //cascadeAct->setStatusTip(tr("Cascade the windows"));
    connect(cascadeAct, SIGNAL(triggered()), workspace, SLOT(cascadeSubWindows()));
/*
    arrangeAct = new QAction(tr("Arrange &icons"), this);
    //arrangeAct->setStatusTip(tr("Arrange the icons"));
    connect(arrangeAct, SIGNAL(triggered()), workspace, SLOT(arrangeIcons()));
*/

    nextAct = new QAction(tr("Ne&xt"), this);    
    nextAct->setShortcut(tr("CTRL+F6"));
    //nextAct->setStatusTip(tr("Move the focus to the next window"));
    connect(nextAct, SIGNAL(triggered()), workspace, SLOT(activateNextSubWindow()));

    previousAct = new QAction(tr("Pre&vious"), this);
    previousAct->setShortcut(tr("CTRL+SHIFT+F6"));
    //previousAct->setStatusTip(tr("Move the focus to the previous window"));
    connect(previousAct, SIGNAL(triggered()), workspace, SLOT(activatePreviousSubWindow()));

    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);
/*
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));*/
}

void _mainwindow::createMenus()
{
#ifdef MAC
    //macmenuBar = new QMenuBar(0);
    //qApp->setMenuBar(macmenuBar);
#endif

    for (int i = 0; i < 27; i++){
      QString k = "";
      k = k.sprintf("%c", i + 65);
      abc[i] = new QMenu(k);
    }

    QMenu *projects = new QMenu(tr("&KBasic Projects   ( KBasic | Forms | Classes | Modules... )"));    
    buildExampleMenu(kbasicPath("examples/projects"), projects);

    QMenu *kbasic = new QMenu(tr("&KBasic                 ( KBasic | Classes | Modules )"));    
    buildExampleMenu(kbasicPath("examples/kbasic"), kbasic);

    QMenu *newbasic = new QMenu(tr("&New Basic           ( VB.NET like )"));    
    buildExampleMenu(kbasicPath("examples/newbasic"), newbasic);

    QMenu *oldbasic = new QMenu(tr("&Old Basic             ( VB6 like )"));    
    buildExampleMenu(kbasicPath("examples/oldbasic"), oldbasic);

    QMenu *veryoldbasic = new QMenu(tr("&Very Old Basic     ( BASIC | QBasic like )"));    
    buildExampleMenu(kbasicPath("examples/veryoldbasic"), veryoldbasic);

    QMenu *category = new QMenu(tr("By &Category"));    
    buildExampleMenu(kbasicPath("examples/category"), category);

    QMenu *language = new QMenu(tr("Lang&uage"));
    category->addMenu(language);
/*
    QMenu *database = new QMenu(tr("&Database"));
    category->addMenu(database);

    QMenu *misc = new QMenu(tr("&Miscellaneous"));
    category->addMenu(misc);
*/
    QMenu *alpha = new QMenu(tr("&Alphabetically"));    
    buildExampleMenu(kbasicPath("examples/alpha"), alpha);

    for (int i = 0; i < 27; i++){
      alpha->addMenu(abc[i]);
    }
    
    FILE = menuBar()->addMenu(tr("&File"));

    QMenu *file_new = new QMenu(tr("New"));    

    file_new->addAction(FILE_NEW_PROJECT);
    file_new->addSeparator();
    file_new->addAction(PROJECT_NEW_FORM);
    file_new->addAction(PROJECT_NEW_CLASS);
    file_new->addAction(PROJECT_NEW_MODULE);
    file_new->addSeparator();
    file_new->addAction(PROJECT_NEW_TABLE);
    file_new->addAction(PROJECT_NEW_QUERY);
    file_new->addAction(PROJECT_NEW_REPORT);
    file_new->addSeparator();
    file_new->addAction(PROJECT_NEW_MENUBAR);
    file_new->addAction(PROJECT_NEW_TOOLBAR);
    file_new->addSeparator();
    file_new->addAction(PROJECT_WIZARD_FORM);
    file_new->addAction(PROJECT_WIZARD_REPORT);    
    file_new->addSeparator();
    file_new->addAction(PROJECT_NEW_DIALOG);
    file_new->addAction(PROJECT_NEW_TOOLWINDOW);
    file_new->addAction(PROJECT_NEW_DOCKWINDOW);
    file_new->addSeparator();
    file_new->addAction(FILE_NEW_FILE);
    //file_new->addSeparator();
    
    //QMenu *file_objects = new QMenu(tr("(Object)"));    

    //file_objects->addAction(FILE_NEW_FILE);

    //file_new->addMenu(file_objects);    

    FILE->addMenu(file_new);

    QMenu *file_open = new QMenu(tr("Open"));    

    file_open->addAction(FILE_OPEN_PROJECT);
    file_open->addSeparator();
    file_open->addAction(FILE_OPEN_FILE);

    QMenu *file_openexample = new QMenu(tr("Open Example"));    

    file_openexample->addAction(EXAMPLE_BROWSER);
    file_openexample->addSeparator();
    file_openexample->addMenu(projects);
    file_openexample->addSeparator();
    file_openexample->addMenu(kbasic);
    file_openexample->addMenu(newbasic);
    file_openexample->addMenu(oldbasic);
    file_openexample->addMenu(veryoldbasic);
    file_openexample->addSeparator();

    language->addMenu(projects);
    language->addSeparator();
    language->addMenu(kbasic);
    language->addMenu(newbasic);
    language->addMenu(oldbasic);
    language->addMenu(veryoldbasic);

    file_openexample->addMenu(category);
    file_openexample->addMenu(alpha);

    file_open->addMenu(file_openexample);

    FILE->addMenu(file_open);        

    QMenu *file_close = new QMenu(tr("Close"));    

    file_close->addAction(FILE_CLOSE_PROJECT);
    file_close->addAction(FILE_CLOSE);

    FILE->addMenu(file_close);
    FILE->addSeparator();
    
    FILE->addAction(FILE_NEW_PROJECT);
    FILE->addAction(FILE_OPEN_PROJECT);
    //FILE->addAction(FILE_EXPORT_PROJECT);
    FILE->addSeparator();

    FILE->addAction(FILE_NEW_FILE);
    FILE->addAction(FILE_OPEN_FILE);
    FILE->addAction(FILE_SAVE);
    FILE->addAction(FILE_SAVE_AS);
    FILE->addAction(FILE_SAVE_ALL);
    FILE->addSeparator();

    QMenu *file_import = new QMenu(tr("Import"));    
    file_import->addAction(FILE_IMPORT_PROJECT);
    file_import->addAction(FILE_IMPORT_FILE);
    file_import->addSeparator();
    file_import->addAction(FILE_IMPORT_CSV);
    FILE->addMenu(file_import);

    QMenu *file_export = new QMenu(tr("Export"));    
    file_export->addAction(FILE_EXPORT_CSV);
    FILE->addMenu(file_export);

    FILE->addSeparator();
    
    //FILE->addAction(FILE_EXPORT_FILE);
    FILE->addAction(FILE_SET_AS_DEFAULT);
    FILE->addAction(FILE_SAVE_HTML);
    //FILE->addSeparator();
    FILE->addAction(FILE_PRINT);
    FILE->addSeparator();
    QAction *action = FILE->addAction(tr("Switch Layout Direction"));
    connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));


    FILE->addSeparator();
    FILE->addAction(FILE_EXIT);
   
    EDIT = menuBar()->addMenu(tr("&Edit"));

    EDIT->addAction(EDIT_UNDO);
    EDIT->addAction(EDIT_REDO);
    EDIT->addSeparator();
    EDIT->addAction(EDIT_CUT);
    EDIT->addAction(EDIT_COPY);
    EDIT->addAction(EDIT_PASTE);
    EDIT->addAction(EDIT_DELETE);
    EDIT->addAction(EDIT_SELECT_ALL);
    EDIT->addSeparator();
    EDIT->addAction(EDIT_APPLY);
    EDIT->addSeparator();
#ifndef MAC
    EDIT->addAction(EDIT_FIND);
//#ifndef MAC
    EDIT->addAction(EDIT_FIND_FILE);
//#endif
    EDIT->addAction(EDIT_REPLACE);
//#ifndef MAC
    EDIT->addAction(EDIT_REPLACE_FILE);
//#endif

    EDIT->addSeparator();
    EDIT->addAction(EDIT_COMMENT_LINES);
    EDIT->addAction(EDIT_UNCOMMENT_LINES);
    EDIT->addAction(EDIT_UNINDENT_LINES);
    EDIT->addAction(EDIT_INDENT_LINES);
    EDIT->addAction(EDIT_MARK_LINES);
    EDIT->addSeparator();
    QMenu *EDITmore = new QMenu(tr("More"));    
    EDITmore->addAction(EDIT_UPPER);
    EDITmore->addAction(EDIT_LOWER);
    EDITmore->addSeparator();
    EDITmore->addAction(EDIT_FINDDEFINITION);
    EDIT->addMenu(EDITmore);

    EDIT->addSeparator();
    EDIT->addAction(EDIT_GOTO);
#endif
    EDIT->addAction(EDIT_INSERT_FILE);

    EDIT->addSeparator();
    QMenu *bookmarks = new QMenu(tr("Bookmarks"));    
    bookmarks->addAction(EDIT_CLEAR_ALL_BOOKMARKS);
    bookmarks->addSeparator();
    bookmarks->addAction(EDIT_SET_BOOKMARK);
    bookmarks->addAction(EDIT_NEXT_BOOKMARK);
    bookmarks->addAction(EDIT_PREVIOUS_BOOKMARK);
    EDIT->addMenu(bookmarks);

#ifdef MAC
    QMenu *FIND = menuBar()->addMenu(tr("&Find"));
    FIND->addAction(EDIT_FIND);
//#ifdef WINDOWS
    FIND->addAction(EDIT_FIND_FILE);
	FIND->addSeparator();
//#endif
    FIND->addAction(EDIT_REPLACE);
//#ifdef WINDOWS
    FIND->addAction(EDIT_REPLACE_FILE);
//#endif
    
    FIND->addSeparator();
    QMenu *EDITmore = new QMenu(tr("More"));    
    EDITmore->addAction(EDIT_UPPER);
    EDITmore->addAction(EDIT_LOWER);
    EDITmore->addSeparator();
    EDITmore->addAction(EDIT_FINDDEFINITION);
    FIND->addMenu(EDITmore);
    
    FIND->addSeparator();
    FIND->addAction(EDIT_GOTO);
    
#endif
    QAction *a = 0;

    VIEW = menuBar()->addMenu(tr("&View"));

    //VIEW->addAction(VIEW_NORMAL);
    VIEW->addAction(VIEW_DESIGN);
    VIEW->addAction(VIEW_SOURCE_CODE);
    //VIEW->addSeparator();
//    VIEW->addAction(VIEW_REPORT);
    VIEW->addAction(VIEW_REPORTPREVIEW);
    /*
    VIEW->addSeparator();   
    VIEW->addAction(VIEW_MENUBAR);
    VIEW->addAction(VIEW_TOOLBAR);*/


    //VIEW->addSeparator();
    //VIEW->addAction(VIEW_DATA_SHEET);
    //VIEW->addAction(VIEW_SQL);

    VIEW->addSeparator();    

    a = new QAction(tr("Project Window"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_ProjectWindow()));
    VIEW->addAction(a);

    a = new QAction(tr("Browser"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_ParserWindow()));
    VIEW->addAction(a);

    a = new QAction(tr("Property Window"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_PropertyWindow()));
    VIEW->addAction(a);   

    VIEW->addSeparator();  
#ifdef WINDOWS
    VIEW->addAction(VIEW_FULLSCREEN);
    VIEW->addSeparator();
#endif
    VIEW->addAction(VIEW_RELATION);
    VIEW->addAction(VIEW_QBE);
    VIEW->addAction(VIEW_SQLTABLES);
#ifndef MAC
    VIEW->addSeparator();
    VIEW->addAction(VIEW_QUICKCODE);
#endif
    VIEW->addSeparator();
    QMenu *VIEWmore = new QMenu(tr("More"));   

    a = new QAction(tr("Toggle Tab Bar"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_TABBAR()));
    VIEWmore->addAction(a);

    VIEWmore->addSeparator();


/*
    a = new QAction(tr("Help"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_HelpWindow()));
    VIEWmore->addAction(a);
*/


    a = new QAction(tr("Form"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_ToolboxForm()));
    VIEWmore->addAction(a);

    a = new QAction(tr("MenuBar"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_ToolboxMenuBar()));
#ifndef MAC
    VIEWmore->addAction(a);
#endif
    
    a = new QAction(tr("ToolBar"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_ToolboxToolBar()));
    VIEWmore->addAction(a);
    
    a = new QAction(tr("Report"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_ToolboxReport()));
    VIEWmore->addAction(a);
    /*
    a = new QAction(tr("SQL"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_ToolboxSql()));
    VIEWmore->addAction(a);
*/

    VIEWmore->addSeparator();

    a = new QAction(tr("Syntax"), this); 
    connect(a, SIGNAL(triggered()), this, SLOT(event_VIEW_Helpwindow_shortcut()));
    VIEWmore->addAction(a);
    

   // VIEWmore->addSeparator();
   // VIEWmore->addAction(VIEW_SQLTABLES);



    VIEW->addMenu(VIEWmore);
    VIEW->addSeparator();

    VIEW->addAction(VIEW_FOCUSORDER);
    VIEW->addAction(VIEW_SQLSETTINGS);
    
    
    VIEW->addSeparator();
    /*
    VIEW->addAction(VIEW_PROJECT_OVERVIEW);
    VIEW->addAction(VIEW_TOOLBOX);
    VIEW->addAction(VIEW_PROPERTY_WINDOW);
    VIEW->addSeparator();*/
   // VIEW->addAction(VIEW_LOG);
    VIEW->addAction(VIEW_KONSOLE);
    VIEW->addAction(VIEW_RUNINFO);
    VIEW->addSeparator();
    VIEW->addAction(VIEW_LOG);

    INSERT = menuBar()->addMenu(tr("&Insert"));
/*
    QMenu *INSERTobjects = new QMenu(tr("Object"));    
    INSERTobjects->addAction(PROJECT_NEW_FORM);
    INSERTobjects->addAction(PROJECT_NEW_CLASS);
    INSERTobjects->addAction(PROJECT_NEW_MODULE);
    //INSERTobjects->addSeparator();
    //INSERTobjects->addAction(PROJECT_NEW_MENUBAR);
    //INSERTobjects->addAction(PROJECT_NEW_TOOLBAR);
    //INSERTobjects->addSeparator();
    //INSERTobjects->addMenu(file_objects);  

    INSERT->addMenu(INSERTobjects);*/
/*
#ifdef MAC
    INSERT->addSeparator();
    INSERT->addAction(EDIT_COMMENT_LINES);
    INSERT->addAction(EDIT_UNCOMMENT_LINES);
    INSERT->addAction(EDIT_UNINDENT_LINES);
    INSERT->addAction(EDIT_INDENT_LINES);
    INSERT->addAction(EDIT_MARK_LINES);
    EDIT->addSeparator();
    EDIT->addAction(EDIT_FINDDEFINITION);
    INSERT->addSeparator();
    QMenu *EDITmore = new QMenu(tr("More"));    
    EDITmore->addAction(EDIT_UPPER);
    EDITmore->addAction(EDIT_LOWER);
    INSERT->addMenu(EDITmore);
    INSERT->addSeparator();
    INSERT->addAction(EDIT_INSERT_FILE);
#endif*/

    QMenu *INSERTform = new QMenu(tr("Form"));    
    
    INSERTform->addAction(INSERT_SELECT2);
    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_COMMANDBUTTON);
    INSERTform->addAction(INSERT_LABEL);
    INSERTform->addAction(INSERT_TEXTBOX);
    INSERTform->addAction(INSERT_COMMANDLINKBUTTON);
    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_CHECKBOX);
    INSERTform->addAction(INSERT_RADIOBUTTON);
    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_LINE_VERTICAL);
    INSERTform->addAction(INSERT_LINE_HORIZONTAL);    
    INSERTform->addAction(INSERT_FRAME);
    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_LISTBOX);
    INSERTform->addAction(INSERT_LISTBOX_ICONMODE);
    INSERTform->addAction(INSERT_COMBOBOX);
    INSERTform->addAction(INSERT_COMBOBOX_EDITABLE);
    INSERTform->addSeparator();
   // INSERTform->addAction(INSERT_OPTIONBUTTON);
    INSERTform->addAction(INSERT_TOOLBUTTON);
    INSERTform->addAction(INSERT_TAB);
    INSERTform->addAction(INSERT_PROGRESSBAR);
    INSERTform->addAction(INSERT_PROGRESSBAR_SPINNING);        
    INSERTform->addAction(INSERT_IMAGE);
    INSERTform->addAction(INSERT_SVG);
    INSERTform->addAction(INSERT_LABEL_LINK);    
    INSERTform->addAction(INSERT_TEXTBOX_PASSWORD);    
    INSERTform->addSeparator();
    //INSERTform->addAction(INSERT_HIDDEN);
   // INSERTform->addSeparator();
//    INSERTform->addAction(INSERT_ACTIVEX);
    //INSERTform->addSeparator();
    INSERTform->addAction(INSERT_TIMER);
    INSERTform->addAction(INSERT_TREEVIEW);
    INSERTform->addAction(INSERT_TREEVIEW_LISTVIEW);
    INSERTform->addAction(INSERT_TOOLBARVIEW);
    //INSERTform->addAction(INSERT_LISTVIEW);
    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_MOVIE);
    INSERTform->addAction(INSERT_SOUND);
    //INSERTform->addAction(INSERT_SUBFORM);
    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_IMAGEBUTTON);
   // INSERTform->addAction(INSERT_CANVAS);
    INSERTform->addSeparator();
    /*
    INSERTform->addAction(INSERT_VBOX);
    INSERTform->addAction(INSERT_HBOX);
    //INSERTform->addAction(INSERT_VHBOX);
    INSERTform->addAction(INSERT_VSPLIT);
    INSERTform->addAction(INSERT_HSPLIT);
    INSERTform->addSeparator();*/

    INSERTform->addAction(INSERT_BOX);
    INSERTform->addAction(INSERT_RESIZEBOX);
    INSERTform->addAction(INSERT_CHILDCONTROL);
    INSERTform->addAction(INSERT_FORMSVIEW);
    INSERTform->addAction(INSERT_SLIDER);
    INSERTform->addAction(INSERT_SCROLLBAR);
    //INSERTform->addAction(INSERT_CUSTOMCONTROL);
    //INSERTform->addAction(INSERT_SCROLLBOX);
    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_BROWSER);
    INSERTform->addAction(INSERT_EDITOR);
    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_DATEBOX);
    INSERTform->addAction(INSERT_TIMEBOX);
    INSERTform->addAction(INSERT_DATETIMEBOX);
    INSERTform->addAction(INSERT_SPINBOX);

    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_UDPSOCKET);
    INSERTform->addAction(INSERT_SERIALPORT);
    INSERTform->addSeparator();
    INSERTform->addAction(INSERT_WEB);

    // CONTROL


    QMenu *INSERTmenubar = new QMenu(tr("MenuBar"));    
    
    INSERTmenubar->addAction(INSERT_SELECT2);
    INSERTmenubar->addSeparator();
    INSERTmenubar->addAction(INSERT_MENU);
    INSERTmenubar->addAction(INSERT_CHILDMENU);
    INSERTmenubar->addSeparator();
    INSERTmenubar->addAction(INSERT_MENUBARITEM);
    INSERTmenubar->addSeparator();
    INSERTmenubar->addAction(INSERT_MOVE);
    INSERTmenubar->addAction(INSERT_DELETE);
    
    QMenu *INSERTtoolbar = new QMenu(tr("ToolBar"));    

    INSERTtoolbar->addAction(INSERT_SELECT2);
    INSERTtoolbar->addSeparator();
    INSERTtoolbar->addAction(INSERT_TOOLBARITEM);
    INSERTtoolbar->addSeparator();
    INSERTtoolbar->addAction(INSERT_MOVE);
    INSERTtoolbar->addAction(INSERT_DELETE);

  //  INSERT->addSeparator();


    QMenu *INSERTreport = new QMenu(tr("Report"));    
    
    INSERTreport->addAction(INSERT_SELECT2);
    INSERTreport->addSeparator();
    //INSERTreport->addAction(INSERT_COMMANDBUTTON);
    INSERTreport->addAction(INSERT_LABEL);
    INSERTreport->addAction(INSERT_TEXTBOX);
    INSERTreport->addSeparator();
    INSERTreport->addAction(INSERT_CHECKBOX);
    //INSERTform->addAction(INSERT_RADIOBUTTON);
    INSERTreport->addSeparator();
    INSERTreport->addAction(INSERT_FRAME);
    //INSERTform->addAction(INSERT_LISTBOX);
    //INSERTform->addAction(INSERT_COMBOBOX);
    //INSERTform->addSeparator();
   // INSERTform->addAction(INSERT_OPTIONBUTTON);
    //INSERTform->addAction(INSERT_TAB);
    //INSERTreport->addAction(INSERT_PROGRESSBAR);
    INSERTreport->addAction(INSERT_IMAGE);
    //INSERTform->addSeparator();
    //INSERTform->addAction(INSERT_HIDDEN);
    //INSERTform->addSeparator();
//    INSERTform->addAction(INSERT_ACTIVEX);
    //INSERTform->addSeparator();
    //INSERTform->addAction(INSERT_TIMER);
    //INSERTform->addAction(INSERT_TREEVIEW);
    //INSERTform->addAction(INSERT_LISTVIEW);
    //INSERTform->addSeparator();
    //INSERTform->addAction(INSERT_SUBFORM);
    //INSERTform->addAction(INSERT_IMAGEBUTTON);
   // INSERTform->addAction(INSERT_CANVAS);
    INSERTreport->addSeparator();
    /*
    INSERTform->addAction(INSERT_VBOX);
    INSERTform->addAction(INSERT_HBOX);
    //INSERTform->addAction(INSERT_VHBOX);
    INSERTform->addAction(INSERT_VSPLIT);
    INSERTform->addAction(INSERT_HSPLIT);
    INSERTform->addSeparator();*/

    //INSERTreport->addAction(INSERT_BOX);
    //INSERTform->addAction(INSERT_CHILDCONTROL);
    //INSERTform->addAction(INSERT_CUSTOMCONTROL);
    //INSERTform->addAction(INSERT_SCROLLBOX);
    //INSERTreport->addSeparator();
    //INSERTreport->addAction(INSERT_BROWSER);
    INSERTreport->addAction(INSERT_EDITOR);
    INSERTreport->addSeparator();
    INSERTreport->addAction(INSERT_DATEBOX);
    INSERTreport->addAction(INSERT_TIMEBOX);
    //INSERTreport->addAction(INSERT_DATETIMEBOX);
    INSERTreport->addSeparator();
    INSERTreport->addAction(INSERT_HEADER);
    INSERTreport->addAction(INSERT_FOOTER);
    

    INSERT->addMenu(INSERTform);
#ifndef MAC
    INSERT->addMenu(INSERTmenubar);
#endif
    INSERT->addMenu(INSERTtoolbar);
    INSERT->addSeparator();
    INSERT->addMenu(INSERTreport);

    QMenu *INSERTcode = new QMenu(tr("Source Code"));    

    INSERTcode->addAction(INSERT_SUB);
    INSERTcode->addAction(INSERT_FUNCTION);
    INSERTcode->addAction(INSERT_PROPERTY);
    INSERTcode->addSeparator();
    INSERTcode->addAction(INSERT_TYPE);
    INSERTcode->addAction(INSERT_ENUM);
    INSERTcode->addSeparator();
    INSERTcode->addAction(INSERT_OPTION_KBASIC);
    INSERTcode->addAction(INSERT_OPTION_OLDBASIC);
    INSERTcode->addAction(INSERT_OPTION_VERYOLDBASIC);
    INSERTcode->addSeparator();
    INSERTcode->addAction(INSERT_STATEMENT);
    INSERTcode->addAction(INSERT_EXPRESSION);    
    INSERTcode->addAction(INSERT_ASSIGNMENT);
    INSERTcode->addAction(INSERT_OPERATOR);
    INSERTcode->addSeparator();
    INSERTcode->addAction(INSERT_IF);
    INSERTcode->addAction(INSERT_SELECT);
    INSERTcode->addSeparator();
    INSERTcode->addAction(INSERT_FORNEXT);
    INSERTcode->addAction(INSERT_WHILELOOP);
    INSERTcode->addAction(INSERT_LOOPWHILE);
    INSERTcode->addSeparator();
    INSERTcode->addAction(INSERT_EXCEPTION);
    INSERTcode->addSeparator();
    INSERTcode->addAction(INSERT_VARIABLE);
    INSERTcode->addAction(INSERT_CONST);
    INSERTcode->addSeparator();
    INSERTcode->addAction(INSERT_FIELDS_LINE);
    INSERTcode->addAction(INSERT_FIELDS_SCOPE);
    INSERTcode->addAction(INSERT_FIELDS_CLASS);
    INSERTcode->addAction(INSERT_FIELDS_MODULE);
    INSERTcode->addAction(INSERT_FIELDS_SUB);
    INSERTcode->addSeparator();
    INSERTcode->addAction(INSERT_REMARK);    

    INSERT->addSeparator();

    INSERT->addMenu(INSERTcode);

    FORMAT = menuBar()->addMenu(tr("F&ormat"));
#ifdef MAC
    FORMAT->addAction(EDIT_COMMENT_LINES);
    FORMAT->addAction(EDIT_UNCOMMENT_LINES);
    FORMAT->addAction(EDIT_UNINDENT_LINES);
    FORMAT->addAction(EDIT_INDENT_LINES);
    FORMAT->addAction(EDIT_MARK_LINES);
    FORMAT->addSeparator();
#endif
/*
    FORMAT->addAction(EDIT_FONTNAME);
    FORMAT->addSeparator();
    FORMAT->addAction(EDIT_BOLD);
    FORMAT->addAction(EDIT_ITALIC);
    FORMAT->addAction(EDIT_UNDERLINE);
    FORMAT->addSeparator();
    FORMAT->addAction(EDIT_FONTSIZE);
    FORMAT->addAction(EDIT_FONTCOLOR);
    FORMAT->addAction(EDIT_BACKGROUND);
    FORMAT->addSeparator();
*/
    FORMAT->addAction(FORMAT_ALIGN_TOP);
    FORMAT->addAction(FORMAT_ALIGN_BOTTOM);
    FORMAT->addAction(FORMAT_ALIGN_LEFT);
    FORMAT->addAction(FORMAT_ALIGN_RIGHT);
    FORMAT->addSeparator();
    FORMAT->addAction(FORMAT_SET_SAME_WIDTH);
    FORMAT->addAction(FORMAT_SET_SAME_HEIGHT);
    FORMAT->addAction(FORMAT_SET_SAME_SIZE);
    FORMAT->addSeparator();
    FORMAT->addAction(FORMAT_LAYOUT_HORIZONTALLY);
    FORMAT->addAction(FORMAT_LAYOUT_VERTICALLY);
    FORMAT->addSeparator();
    FORMAT->addAction(FORMAT_MOVE_TO_FRONT);
    FORMAT->addAction(FORMAT_MOVE_TO_BACK);
    FORMAT->addSeparator();
    FORMAT->addAction(FORMAT_MOVE_UP);
    FORMAT->addAction(FORMAT_MOVE_DOWN);
    FORMAT->addAction(FORMAT_MOVE_LEFT);
    FORMAT->addAction(FORMAT_MOVE_RIGHT);

    PROJECT = menuBar()->addMenu(tr("&Project"));

    QMenu *INSERTnew = new QMenu(tr("New"));

    INSERTnew->addAction(PROJECT_NEW_FORM);
    INSERTnew->addAction(PROJECT_NEW_CLASS);
    INSERTnew->addAction(PROJECT_NEW_MODULE);
    INSERTnew->addSeparator();
    INSERTnew->addAction(PROJECT_NEW_TABLE);
    INSERTnew->addAction(PROJECT_NEW_QUERY);
    INSERTnew->addAction(PROJECT_NEW_REPORT);
    INSERTnew->addSeparator();
    INSERTnew->addAction(PROJECT_NEW_MENUBAR);
    INSERTnew->addAction(PROJECT_NEW_TOOLBAR);
    INSERTnew->addSeparator();
    INSERTnew->addAction(PROJECT_WIZARD_FORM);
    INSERTnew->addAction(PROJECT_WIZARD_REPORT);    
    INSERTnew->addSeparator();
    INSERTnew->addAction(PROJECT_NEW_DIALOG);
    INSERTnew->addAction(PROJECT_NEW_TOOLWINDOW);
    INSERTnew->addAction(PROJECT_NEW_DOCKWINDOW);
    //INSERTnew->addSeparator();
    //INSERTnew->addMenu(file_objects);  

    PROJECT->addMenu(INSERTnew);
    PROJECT->addAction(PROJECT_ADD_EXISTING);
    PROJECT->addAction(PROJECT_REFRESH);

    PROJECT->addSeparator();
    PROJECT->addAction(PROJECT_DATABASE);
    PROJECT->addAction(PROJECT_TRANSLATION);
    PROJECT->addSeparator();

    PROJECT->addAction(PROJECT_SET_AS_DEFAULT);
    PROJECT->addAction(PROJECT_PROPERTIES_OF_PROJECT);
    PROJECT->addSeparator();
    PROJECT->addAction(PROJECTLIST);

    RUN = menuBar()->addMenu(tr("&Run"));

    RUN->addAction(RUN_RUN_PCODE2);
    //RUN->addAction(RUN_PAUSE);
    RUN->addAction(RUN_STOP);
    RUN->addSeparator();
    RUN->addAction(RUN_BUILD);
    
    

    RUN->addSeparator();
    QMenu *RUNmore = new QMenu(tr("More"));

//    RUNmore->addAction(RUN_PCODEVIEWER);
  //  RUNmore->addSeparator();
    //RUNmore->addAction(RUN_RUN_PCODE);
    
    //RUNmore->addAction(RUN_RUN_PROJECT);
    //RUNmore->addSeparator();
    //RUNmore->addAction(RUN_BUILD_ALL);    

//    RUNmore->addSeparator();   
    RUNmore->addAction(RUN_BUILD_ALL);
    RUNmore->addSeparator();       
    //RUNmore->addAction(RUN_FORM);
    //RUNmore->addAction(RUN_SUB);
    //RUNmore->addSeparator(); 
    RUNmore->addAction(RUN_RUN);
    RUNmore->addAction(RUN_RUN_PCODE3);
    
    

    //RUNmore->addSeparator();
    

 //   RUN->addSeparator();
    RUN->addMenu(RUNmore);

   // RUN->addSeparator();


    DEBUG2 = menuBar()->addMenu(tr("&Debug"));
    
    DEBUG2->addAction(RUN_RUN_IN_DEBUG);
    DEBUG2->addAction(RUN_RUN_IN_DEBUG2);
    DEBUG2->addSeparator();    
    DEBUG2->addAction(RUN_CONTINUE_PCODE);
    DEBUG2->addAction(RUN_SINGLE_STEP);
    DEBUG2->addAction(RUN_STEP_OVER);
    DEBUG2->addAction(RUN_STEP_OUT);
    DEBUG2->addAction(RUN_TO_CURSOR);

    DEBUG2->addSeparator();
    
    QMenu *DEBUG2breakpoints = new QMenu(tr("Breakpoints"));
    DEBUG2breakpoints->addAction(RUN_CLEAR_ALL_BREAKPOINTS);
    DEBUG2breakpoints->addSeparator();
    DEBUG2breakpoints->addAction(RUN_SET_BREAKPOINT);
    DEBUG2breakpoints->addAction(RUN_NEXT_BREAKPOINT);
    DEBUG2breakpoints->addAction(RUN_PREVIOUS_BREAKPOINT);
    
    DEBUG2->addMenu(DEBUG2breakpoints);

//#ifndef MAC
    EXAMPLES = menuBar()->addMenu(tr("E&xamples"));

    EXAMPLES->addAction(EXAMPLE_BROWSER);
    EXAMPLES->addSeparator();
    EXAMPLES->addMenu(projects);
    EXAMPLES->addSeparator();
    EXAMPLES->addMenu(kbasic);
    EXAMPLES->addMenu(newbasic);
    EXAMPLES->addMenu(oldbasic);
    EXAMPLES->addMenu(veryoldbasic);
    EXAMPLES->addSeparator();

    EXAMPLES->addMenu(category);
    EXAMPLES->addMenu(alpha);
//#endif

#ifndef MAC
    TOOLS = menuBar()->addMenu(tr("&Tools"));
#else
    RUN->addSeparator(); 
    TOOLS = RUN->addMenu(tr("&Tools"));
#endif
    //TOOLS->addAction(TOOLS_EXTERN_TOOLS);
    //TOOLS->addSeparator();

    TOOLS->addAction(TOOLS_RESOURCES);
    TOOLS->addSeparator();
    QMenu *RUNbinary = TOOLS->addMenu(
                                       // #ifndef MAC
                                     //   kbasicIcon(kbasicPath("ide/RUN_BINARY.png")), 
//#endif
                                        tr("Create Binary"));
    RUNbinary->addAction(PROJECT_MAKE_RUNTIME_WINDOWS);
    RUNbinary->addSeparator();
    RUNbinary->addAction(PROJECT_MAKE_RUNTIME_LINUX);
    RUNbinary->addAction(PROJECT_MAKE_RUNTIME_MACOS);
    TOOLS->addSeparator();


    TOOLS->addAction(TOOLS_SELFTEST);



#ifdef MAC
    FILE->addAction(FILE_PREFERENCES);
#else
    TOOLS->addSeparator();
    TOOLS->addAction(FILE_PREFERENCES);
#endif

    windowMenu = menuBar()->addMenu(tr("&Window"));
    updateWindowMenu();
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    //WINDOW = menuBar()->addMenu(tr("W&indow"));
    menuBar()->addSeparator();

    HELP = menuBar()->addMenu(tr("&Help"));
    
    //HELP->addAction(HELP_CONTENTS);
    //HELP->addSeparator();
    
    QMenu *HELOnline = new QMenu(tr("Online Documentation (In English)")); //  (Newest)

    HELOnline->addAction(HELP_FRAMEWORK);
    HELOnline->addAction(HELP_LANGUAGE_REFERENCE);
    HELOnline->addSeparator();
    HELOnline->addAction(HELP_KBASIC_BOOK);
    HELOnline->addAction(HELP_SYNTAX);
    HELOnline->addSeparator();
    HELOnline->addAction(HELP_WEBSITE);

    HELP->addMenu(HELOnline);

    /*
    QMenu *HELOffline = new QMenu(tr("Offline Documentation (In English Only)"));

    HELOffline->addAction(HELP_OFFLINE_FRAMEWORK);
    HELOffline->addAction(HELP_OFFLINE_KEYWORDS);
    HELOffline->addAction(HELP_OFFLINE_BUILTINS);
    HELOffline->addSeparator();
    HELOffline->addAction(HELP_OFFLINE_MANUAL);
    HELOffline->addAction(HELP_OFFLINE_SYNTAX);
    HELOffline->addSeparator();
    HELOffline->addAction(HELP_OFFLINE_MISC);
    HELOffline->addSeparator();
    HELOffline->addAction(HELP_OFFLINE_DESCRIPTION);
    HELOffline->addAction(HELP_OFFLINE_OVERVIEW);

    
    HELP->addMenu(HELOffline);
    HELP->addSeparator();*/


    //QMenu *HELPmore = new QMenu(tr("More"));

    //HELPmore->addAction(HELP_RELEASE);
    //HELPmore->addSeparator();
    //HELPmore->addAction(HELP_HOW_TO_PURCHASE);
    //HELPmore->addSeparator();
    //HELPmore->addAction(HELP_KBASIC_BUG);
    //HELPmore->addSeparator();
    //HELPmore->addAction(HELP_IS_BASIC_USEFUL);
    //HELPmore->addAction(HELP_HISTORY_OF_BASIC);
    //HELPmore->addAction(HELP_KBASIC_LICENSE);
    //HELPmore->addSeparator();
    //HELPmore->addAction(HELP_MIGRATING);

    //HELP->addSeparator();
    HELP->addAction(HELP_KBASIC_CONTRIBUTE);
    HELP->addAction(HELP_KBASIC_BUG);
    
    //HELP->addMenu(HELPmore);


    //HELP->addSeparator();
    //HELP->addAction(HELP_SQL_DOCUMENTATION);
    
/*
    QMenu *HELPhowtos = new QMenu(tr("HOWTOs"));

    HELPhowtos->addAction(HELP_HOWTO01);
    HELPhowtos->addAction(HELP_HOWTO02);
    HELPhowtos->addAction(HELP_HOWTO03);
    HELPhowtos->addAction(HELP_HOWTO04);*/
    
    //HELP->addSeparator();
   // HELP->addMenu(HELPhowtos);

    HELP->addSeparator();
    HELP->addAction(HELP_ABOUT);



/*
    fileMenu = menuBar()->addMenu(tr("&File"));
    
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    windowMenu = menuBar()->addMenu(tr("&Window"));
    updateWindowMenu();
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);*/
}

void _mainwindow::createToolBars()
{
    tbFile = addToolBar(tr("Toolbar"));
//    tbFile = addToolBar(tr("File"));

    tbRun = tbFile;
    tbInsert = tbFile;
    tbEdit = tbFile;
    tbView = tbFile;
    tbFormat = tbFile;
    tbTranslation = tbFile;

#ifdef MAC
    tbFile->setMovable(false);
#endif
//    tbFile->setObjectName("Toolbar File");
    tbFile->setObjectName("Toolbar");
    tbFile->setIconSize(QSize(16, 16));
#ifdef MAC
    tbFile->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
#endif

#ifndef MAC
    tbFile->addAction(PROJECTLIST);
    tbFile->addSeparator();
    //tbFile->addAction(FILE_NEW_FILE);
    //tbFile->addAction(FILE_OPEN_FILE);
    tbFile->addAction(FILE_SAVE);
#else
    //tbFile->addAction(PROJECTLIST);
    //tbFile->addSeparator();
    tbFile->addAction(FILE_SAVE);
#endif

#ifdef MAC
#else
    tbFile->addSeparator();
    tbFile->addAction(EDIT_CUT);
    tbFile->addAction(EDIT_COPY);
    tbFile->addAction(EDIT_PASTE);
    tbFile->addSeparator();
    tbFile->addAction(EDIT_UNDO);
    tbFile->addAction(EDIT_REDO);
    tbFile->addSeparator();
    tbFile->addAction(EDIT_APPLY);
#endif

    tbFile->addSeparator();
    //tbRun = addToolBar(tr("Run"));
#ifdef MAC
    tbRun->setMovable(false);
#endif    
    //tbRun->setObjectName("Toolbar Run");
    tbRun->setIconSize(QSize(16, 16));
#ifdef MAC
    tbRun->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
#endif
    
    /*
    tbRun->addAction(RUN_RUN_PROJECT);
    tbRun->addSeparator();*/
    tbRun->addAction(RUN_RUN_PCODE2);
    //tbRun->addAction(RUN_PAUSE);
    tbRun->addAction(RUN_STOP);
    tbRun->addSeparator();
    tbRun->addAction(RUN_BUILD);
#ifdef MAC
#else
    tbRun->addSeparator();    
    tbRun->addAction(RUN_CONTINUE_PCODE);
    tbRun->addAction(RUN_SINGLE_STEP);
    tbRun->addAction(RUN_STEP_OVER);
    tbRun->addAction(RUN_STEP_OUT);
    tbRun->addAction(RUN_TO_CURSOR);
    tbRun->addAction(RUN_SET_BREAKPOINT);
    /*tbRun->addSeparator();    
    
#ifdef WINDOWS
  tbRun->addAction(PROJECT_MAKE_RUNTIME_WINDOWS); // HIDE
#endif
#ifdef LINUX
  tbRun->addAction(PROJECT_MAKE_RUNTIME_LINUX);
#endif
#ifdef MAC
  tbRun->addAction(PROJECT_MAKE_RUNTIME_MACOS); // HIDE
#endif*/
#endif
  




    //tbRun->addSeparator();
    //tbRun->addAction(RUN_RUN);
    /*
    tbRun->addSeparator();
    //tbRun->addAction(RUN_SET_BREAKPOINT);
    //tbRun->addSeparator();
    //tbRun->addAction(RUN_RUN_IN_DEBUG);   
    
    tbRun->addAction(RUN_SINGLE_STEP);   
    tbRun->addAction(RUN_STEP_OVER);   
    tbRun->addAction(RUN_STEP_OUT);   
    tbRun->addAction(RUN_TO_CURSOR);  */


    //addToolBarBreak();

    tbRun->addSeparator();

    //tbEdit = addToolBar(tr("Edit"));
#ifdef MAC
    tbEdit->setMovable(false);
#endif    
    //tbEdit->setObjectName("Toolbar Edit");
    tbEdit->setIconSize(QSize(16, 16));
#ifdef MAC
    tbEdit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
#endif
    //tbEdit->addAction(VIEW_NORMAL);   
    tbEdit->addAction(VIEW_DESIGN);   
    tbEdit->addAction(VIEW_SOURCE_CODE);   
    //tbEdit->addAction(VIEW_REPORT);   
#ifdef MAC
#else
    tbEdit->addAction(VIEW_REPORTPREVIEW);   
    //tbEdit->addAction(VIEW_MENUBAR);   
    //tbEdit->addAction(VIEW_TOOLBAR);   
    tbEdit->addSeparator();    
    tbEdit->addAction(EDIT_COMMENT_LINES);   
    tbEdit->addAction(EDIT_UNCOMMENT_LINES);   
    tbEdit->addAction(EDIT_UNINDENT_LINES);   
    tbEdit->addAction(EDIT_INDENT_LINES);   
    tbEdit->addSeparator();
    tbEdit->addAction(EDIT_SET_BOOKMARK);   
    tbEdit->addAction(EDIT_NEXT_BOOKMARK);   
    tbEdit->addAction(EDIT_PREVIOUS_BOOKMARK);  
    tbEdit->addSeparator(); 
    tbEdit->addAction(EDIT_FIND);   
    //tbEdit->addAction(VIEW_RUNINFO);   
    //tbEdit->addAction(VIEW_KONSOLE);    
    tbEdit->addAction(VIEW_LOG);    
   // tbEdit->addAction(EXAMPLE_BROWSER);    
#endif
/*
    QToolBar *tbDebug = addToolBar(tr("Debug"));
    tbDebug->setObjectName("Toolbar Debug");
    tbDebug->setIconSize(QSize(16, 16));
    tbDebug->addSeparator();
    //tbEdit->addAction(VIEW_FULLSCREEN);   */
#ifdef MAC
#else
    //tbFormat = addToolBar(tr("Format"));

   tbEdit->addSeparator();

#ifdef MAC
    tbFormat->setMovable(false);
#endif   
    //tbFormat->setObjectName("Toolbar Format");
    tbFormat->setIconSize(QSize(16, 16));
    
/*
    tbFormat->addAction(EDIT_FONTNAME);   
    tbFormat->addSeparator();
    tbFormat->addAction(EDIT_BOLD);   
    tbFormat->addAction(EDIT_ITALIC);   
    tbFormat->addAction(EDIT_UNDERLINE);   
    tbFormat->addSeparator();
    tbFormat->addAction(EDIT_FONTSIZE);   
    tbFormat->addAction(EDIT_FONTCOLOR);   
    tbFormat->addAction(EDIT_BACKGROUND);   
    tbFormat->addSeparator();
*/
    tbFormat->addAction(FORMAT_ALIGN_TOP);   
    tbFormat->addAction(FORMAT_ALIGN_BOTTOM);   
    tbFormat->addAction(FORMAT_ALIGN_LEFT);   
    tbFormat->addAction(FORMAT_ALIGN_RIGHT);   
    tbFormat->addSeparator();
    tbFormat->addAction(FORMAT_SET_SAME_WIDTH);   
    tbFormat->addAction(FORMAT_SET_SAME_HEIGHT);   
    tbFormat->addSeparator();
    tbFormat->addAction(FORMAT_LAYOUT_HORIZONTALLY);   
    tbFormat->addAction(FORMAT_LAYOUT_VERTICALLY);   
    tbFormat->addSeparator();
    tbFormat->addAction(FORMAT_MOVE_TO_FRONT);   
    tbFormat->addAction(FORMAT_MOVE_TO_BACK);   
    tbFormat->addSeparator();
    tbFormat->addAction(FORMAT_MOVE_UP);   
    tbFormat->addAction(FORMAT_MOVE_DOWN);   
    tbFormat->addAction(FORMAT_MOVE_LEFT);   
    tbFormat->addAction(FORMAT_MOVE_RIGHT);   


#endif

    tbFormat->addSeparator();

    //tbTranslation = addToolBar(tr("Translation"));
#ifdef MAC
    tbTranslation->setMovable(false);
#endif    
    //tbTranslation->setObjectName("Toolbar Translation");
    tbTranslation->setIconSize(QSize(16, 16));
#ifdef MAC
    tbTranslation->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
#endif

    TRANSLATION = new QComboBox();
    TRANSLATION->addItem("");
    TRANSLATION->setMinimumWidth(100);

    connect(TRANSLATION, SIGNAL(currentIndexChanged (const QString &)), this, SLOT(TRANSLATION_currentIndexChanged (const QString &))); 

#ifdef MAC
    tbTranslation->addWidget(new QLabel(tr("Select Language: "))); // HIDE
#endif
    tbTranslation->addWidget(TRANSLATION);   
    tbTranslation->addSeparator();
    tbTranslation->addAction(TRANSLATION_ADD);   
    tbTranslation->addAction(TRANSLATION_REMOVE);   

}

void _mainwindow::createStatusBar()
{
  statusBar()->setHidden(true);
  oPercentInfo = new QProgressBar();
#ifdef MAC
  oPercentInfo->setMaximumHeight(20);
#else
  oPercentInfo->setMaximumHeight(12);
#endif
  oPercentInfo->setValue(0);
  
  statusBar()->addPermanentWidget(oPercentInfo);

  connect(statusBar(), SIGNAL(messageChanged(const QString &)), this, SLOT(statusbar_messageChanged(const QString &)));


}

void _mainwindow::statusbar_messageChanged(const QString & message)
{
  if (message.isEmpty()) statusBar()->hide();
}

void _mainwindow::createDockWindows()
{
    QDockWidget *dock;    


    EXTERN_PropertyWindow = dock  = new QDockWidget(
#ifdef MAC
      tr("Property")
#else
      tr("Property Window")
#endif
      , this);
    dock->setObjectName("Property Window");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //customerList = new QListWidget(dock);
    EXTERN_my_propertywindow = new _propertywindow(dock);
    dock->setWidget(EXTERN_my_propertywindow);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    EXTERN_my_propertywindow->showProperties(false); // preload for speeding up


    EXTERN_ProjectWindow = dock  = new QDockWidget(
#ifdef MAC
      tr("Project")
#else
      tr("Project Window")
#endif
      , this);
    dock->setObjectName("Project Window");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(EXTERN_my_projectwindow);
    addDockWidget(Qt::LeftDockWidgetArea, dock);


/*
  EXTERN_ProjectWindow->setAutoFillBackground(true);
  QPalette p = EXTERN_ProjectWindow->palette();
  QColor c = QColor(0, 0, 0, 155);
  p.setColor(QPalette::Window, c);  
  EXTERN_ProjectWindow->setPalette(p);

*/
    EXTERN_ParserWindow = dock  = new QDockWidget(tr("Browser"), this);
    dock->setObjectName("Browser");
//    dock->setWindowIcon(kbasicIcon("c:\\kbasic15\\ide/flag.png")));
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    EXTERN_my_parserwindow = new _parserwindow(dock);
    dock->setWidget(EXTERN_my_parserwindow);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    /*
    EXTERN_HelpWindow = dock  = new QDockWidget(tr("Help"), this);
    dock->setObjectName("Help");
//    dock->setWindowIcon(kbasicIcon("c:\\kbasic15\\ide/flag.png")));
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    EXTERN_my_helpwindow = new _helpwindow(dock);
    dock->setWidget(EXTERN_my_helpwindow);
    addDockWidget(Qt::RightDockWidgetArea, dock);
*/
    /*
    QDockWidget *ContextHelp = dock  = new QDockWidget(tr("Context Help"), this);
    dock->setObjectName("Context Help");
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    //customerList = new QListWidget(dock);
    dock->setWidget(new QWidget(dock));
    addDockWidget(Qt::BottomDockWidgetArea, dock);*/


    /*
    QDockWidget *ToolboxSourceCode = dock  = new QDockWidget(tr("Source Code"), this);
    dock->setObjectName("Toolbox Source Code");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //customerList = new QListWidget(dock);
    _toolboxwindow_sourcecode *my_toolboxwindow_sourcecode = new _toolboxwindow_sourcecode(dock);
    dock->setWidget(my_toolboxwindow_sourcecode);
    addDockWidget(Qt::LeftDockWidgetArea, dock);*/

    EXTERN_ToolboxForm = dock  = new QDockWidget(tr("Form"), this);    
   // dock->setMaximumHeight(36 * 5);
    dock->setObjectName("Toolbox Form");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //customerList = new QListWidget(dock);
    EXTERN_toolboxwindow_form = new _toolboxwindow_form(dock);
    
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(EXTERN_toolboxwindow_form);
    scrollArea->setFrameStyle(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);

    QTabWidget *tab = new QTabWidget();
    tab->setUsesScrollButtons(true);
    tab->addTab(scrollArea, tr("Default"));

    EXTERN_toolboxwindow_vista = new _toolboxwindow_vista(dock);
    scrollArea = new QScrollArea;
    scrollArea->setWidget(EXTERN_toolboxwindow_vista);
    scrollArea->setFrameStyle(QFrame::NoFrame);
    //scrollArea->setWidgetResizable(true);

    tab->addTab(scrollArea, tr("Vista"));

    EXTERN_toolboxwindow_leopard = new _toolboxwindow_leopard(dock);
    scrollArea = new QScrollArea;
    scrollArea->setWidget(EXTERN_toolboxwindow_leopard);
    scrollArea->setFrameStyle(QFrame::NoFrame);
    //scrollArea->setWidgetResizable(true);

    tab->addTab(scrollArea, tr("Leopard"));


    dock->setWidget(tab);    
    //my_toolboxwindow->setHidden(true);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    //dock->setFloating(true);

    EXTERN_ToolboxMenuBar = dock  = new QDockWidget(tr("MenuBar"), this);
    dock->setMaximumHeight(36 * 5);
    dock->setObjectName("Toolbox MenuBar");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //customerList = new QListWidget(dock);
    EXTERN_toolboxwindow_menubar = new _toolboxwindow_menubar(dock);
    dock->setWidget(EXTERN_toolboxwindow_menubar);    
    //my_toolboxwindow->setHidden(true);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    //dock->setFloating(true);

    EXTERN_ToolboxToolBar = dock  = new QDockWidget(tr("ToolBar"), this);
    dock->setMaximumHeight(36 * 5);
    dock->setObjectName("Toolbox ToolBar");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //customerList = new QListWidget(dock);
    EXTERN_toolboxwindow_toolbar = new _toolboxwindow_toolbar(dock);
    dock->setWidget(EXTERN_toolboxwindow_toolbar);    
    //my_toolboxwindow->setHidden(true);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    //dock->setFloating(true);

    EXTERN_ToolboxReport = dock  = new QDockWidget(tr("Report"), this);
    dock->setMaximumHeight(36 * 5);
    dock->setObjectName("Toolbox Report");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    EXTERN_toolboxwindow_report = new _toolboxwindow_report(dock);
    dock->setWidget(EXTERN_toolboxwindow_report);    
    addDockWidget(Qt::RightDockWidgetArea, dock);
    //dock->setFloating(true);

    EXTERN_DatabaseTables = dock  = new QDockWidget(tr("Database Tables"), this);

    dock->setObjectName("Database Tables");
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    EXTERN_qbe_tables = new _qbe_tables(0, 0, 0);
    dock->setWidget(EXTERN_qbe_tables);    
    addDockWidget(Qt::RightDockWidgetArea, dock);
    EXTERN_DatabaseTables->setShown(false);
    EXTERN_DatabaseTables->setFloating(true);
   

    

    

    

/*
    EXTERN_ToolboxSql = dock  = new QDockWidget(tr("SQL"), this);
    dock->setMaximumHeight(36 * 5);
    dock->setObjectName("Toolbox SQL");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    EXTERN_toolboxwindow_sql = new _toolboxwindow_sql(dock);
    dock->setWidget(EXTERN_toolboxwindow_sql);    
    addDockWidget(Qt::RightDockWidgetArea, dock);
*/

    /*
    QDockWidget *ToolboxMenuBar = dock  = new QDockWidget(tr("MenuBar"), this);
    dock->setObjectName("Toolbox MenuBar");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //customerList = new QListWidget(dock);
    dock->setWidget(new _toolboxwindow_menubar(dock));
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    QDockWidget *ToolboxToolBar = dock  = new QDockWidget(tr("ToolBar"), this);
    dock->setObjectName("Toolbox ToolBar");
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //customerList = new QListWidget(dock);
    dock->setWidget(new _toolboxwindow_toolbar(dock));
    addDockWidget(Qt::LeftDockWidgetArea, dock);*/


    EXTERN_Quickcode = dock  = new QDockWidget(tr("Console"), this);
    dock->setObjectName("Console");
    EXTERN_quickcode = new _quickcode(dock);
    dock->setWidget(EXTERN_quickcode);
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);

    EXTERN_FileFind = dock = new QDockWidget(tr("File Find"), this);
    dock->setObjectName("File Find");
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    //customerList = new QListWidget(dock);
    EXTERN_findfilelist = new _findfilelist(dock);
    dock->setWidget(EXTERN_findfilelist);
/*
    customerList = new QListWidget(dock);
    dock->setWidget(customerList);*/
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);

    EXTERN_FileReplace = dock  = new QDockWidget(tr("File Replace"), this);
    dock->setObjectName("File Replace");
    //customerList = new QListWidget(dock);
    EXTERN_replacefilelist = new _replacefilelist(dock);
    dock->setWidget(EXTERN_replacefilelist);

    //paragraphsList = new QListWidget(dock);
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);
   // viewMenu->addAction(dock->toggleViewAction());

    
    EXTERN_Local = dock  = new QDockWidget(tr("Local"), this);
    dock->setObjectName("Local");
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    EXTERN_locallist = new _locallist(dock);
    dock->setWidget(EXTERN_locallist);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);

    
    EXTERN_Me = dock  = new QDockWidget(tr("Me"), this);
    dock->setObjectName("Me");
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    EXTERN_melist = new _melist(dock);
    dock->setWidget(EXTERN_melist);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);

    EXTERN_Global = dock  = new QDockWidget(tr("Global"), this);
    dock->setObjectName("Global");
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    EXTERN_globallist = new _globallist(dock);
    dock->setWidget(EXTERN_globallist);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);

    EXTERN_Stack = dock  = new QDockWidget(tr("Call Stack"), this);
    dock->setObjectName("Call Stack");
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    EXTERN_stacklist = new _stacklist(dock);
    dock->setWidget(EXTERN_stacklist);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);


   // viewMenu->addAction(dock->toggleViewAction());

    /*
    QDockWidget *Helpwindow_keyword = dock  = new QDockWidget(tr("Keyword"), this);
    dock->setObjectName("Help Keyword");
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);    
    _helpwindow_keyword *my_helpwindow_keyword = new _helpwindow_keyword(dock);
    dock->setWidget(my_helpwindow_keyword);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);

    QDockWidget *Helpwindow_builtin = dock  = new QDockWidget(tr("Builtin"), this);
    dock->setObjectName("Help Builtin");
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);    
    _helpwindow_builtin *my_helpwindow_builtin = new _helpwindow_builtin(dock);
    dock->setWidget(my_helpwindow_builtin);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);

    QDockWidget *Helpwindow_type = dock  = new QDockWidget(tr("Type"), this);
    dock->setObjectName("Help Type");
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);    
    _helpwindow_type *my_helpwindow_type = new _helpwindow_type(dock);
    dock->setWidget(my_helpwindow_type);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);

    QDockWidget *Helpwindow_operator = dock  = new QDockWidget(tr("Operator"), this);
    dock->setObjectName("Help Operator");
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);    
    _helpwindow_operator *my_helpwindow_operator = new _helpwindow_operator(dock);
    dock->setWidget(my_helpwindow_operator);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    dock->setHidden(true);*/

    EXTERN_Helpwindow_shortcut = dock  = new QDockWidget(tr("Syntax"), this);
    dock->setMaximumHeight(36 * 5);
    dock->setObjectName("Help Shortcut");
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);    
    EXTERN_my_helpwindow_shortcut = new _helpwindow_shortcut(dock);
    dock->setWidget(EXTERN_my_helpwindow_shortcut);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    //dock->setFloating(true);


    //tabifyDockWidget(EXTERN_ProjectWindow, EXTERN_PropertyWindow);
    //tabifyDockWidget(EXTERN_ProjectWindow, EXTERN_ParserWindow);
    EXTERN_ProjectWindow->setHidden(true);
    EXTERN_ParserWindow->setHidden(true);
    EXTERN_Helpwindow_shortcut->setHidden(true);
    //tabifyDockWidget(EXTERN_ProjectWindow, EXTERN_HelpWindow);

    //tabifyDockWidget(ToolboxSourceCode, ToolboxForm);
    //tabifyDockWidget(ToolboxSourceCode, ToolboxMenuBar);
    //tabifyDockWidget(ToolboxSourceCode, ToolboxToolBar);

    //tabifyDockWidget(ProjectWindow, ToolboxForm);
    //tabifyDockWidget(ProjectWindow, PropertyWindow);
//    tabifyDockWidget(EXTERN_ToolboxForm, EXTERN_ToolboxSql);
    
    tabifyDockWidget(EXTERN_ToolboxForm, EXTERN_ToolboxReport);
    tabifyDockWidget(EXTERN_ToolboxForm, EXTERN_ToolboxMenuBar);
    tabifyDockWidget(EXTERN_ToolboxForm, EXTERN_ToolboxToolBar);
    //tabifyDockWidget(EXTERN_ToolboxForm, EXTERN_Helpwindow_shortcut);

    //tabifyDockWidget(Helpwindow_shortcut, ToolboxForm);

    /*
    tabifyDockWidget(EXTERN_Local, EXTERN_Global);
    tabifyDockWidget(EXTERN_Local, EXTERN_Stack);*/

/*    
    tabifyDockWidget(FileFind, FileReplace);
    tabifyDockWidget(FileFind, Local);
    tabifyDockWidget(FileFind, Global);
    tabifyDockWidget(FileFind, CallingStack);

    */
/*    tabifyDockWidget(FileFind, Helpwindow_keyword);
    tabifyDockWidget(FileFind, Helpwindow_builtin);
    tabifyDockWidget(FileFind, Helpwindow_type);
    tabifyDockWidget(FileFind, Helpwindow_operator);*/
    //tabifyDockWidget(FileFind, Helpwindow_shortcut);

    //FileFind->hide();
//    tabifyDockWidget(Local, FileFind);

   

}


void _mainwindow::readSettings()
{
  //return; 

  QSettings settings(QSettings::IniFormat, QSettings::UserScope, MYAPP);
  QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
  QSize size = settings.value("size", QSize(400, 400)).toSize();    

  if (restoreState(settings.value("saveState").toByteArray())){
    move(pos);
    resize(size);
  }

  _preferences::load(this);

}

void _mainwindow::writeSettings()
{
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, MYAPP);
  settings.setValue("pos", pos());
  settings.setValue("size", size());

  settings.remove("saveState");
  settings.setValue("saveState", saveState());
}


void _mainwindow::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        qApp->setLayoutDirection(Qt::RightToLeft);
    else
        qApp->setLayoutDirection(Qt::LeftToRight);
}

void _mainwindow::subWindowActivated(QMdiSubWindow *w)
{
  if (w == 0){
    updateGeneralActions(
   true,  false,  false,  false, 
   false,  false,  false,  false,  false,   
   false,  false,  false, 
   false,  false,  false,  false, 
   false, "");
/*
    QMessageBox::information( this, tr(MYAPP),
        tr(
            "w == 0"
            )
            );
*/
  } else {
    qApp->setActiveWindow(w);
    w->setFocus();
  }
}

void _mainwindow::updateGeneralActions(
  bool bMainWindow, bool bForm, bool bReport, bool bProjectWindow, 
  bool bQuery, bool bSourceCodeEditor, bool bTable, bool bMenuBar, bool bToolBar, 
  
  bool bShowFocusOrder, bool bShowSQLSettings, bool bShowSQLTables, 
  bool bCanCopy, bool bCanPaste, bool bCanRedo, bool bCanUndo, 
  bool bIsFormClassSourceCode, QString sFileName
)
{

    bool bProject = EXTERN_my_mainwindow->isProject();
    bool bDefaultWindow = bForm || bReport || bSourceCodeEditor || bTable || bMenuBar || bToolBar || bQuery;
  
    PROJECTLIST->setEnabled(bProject);
    FILE_CLOSE->setEnabled(!bMainWindow && !bProjectWindow);
    PROJECT_ADD_EXISTING->setEnabled(bProject);
    PROJECT_REFRESH->setEnabled(bProject);      
    FILE_CLOSE_PROJECT->setEnabled(bProject);
    FILE_SAVE->setEnabled(!bMainWindow && !bProjectWindow && bDefaultWindow && !(bTable && bIsFormClassSourceCode));
    FILE_SAVE_AS->setEnabled(!bMainWindow && !bProjectWindow && bDefaultWindow && !(bTable && bIsFormClassSourceCode) && !sCurrentLanguage.isEmpty());    
    FILE_SAVE_HTML->setEnabled(bSourceCodeEditor);    
    FILE_SET_AS_DEFAULT->setEnabled(bSourceCodeEditor);
    FILE_PRINT->setEnabled(bSourceCodeEditor);      

    EDIT_SELECT_ALL->setEnabled(bForm || bReport || bSourceCodeEditor);

//#ifndef MAC
    EDIT_FIND_FILE->setEnabled(bProject);
    EDIT_REPLACE_FILE->setEnabled(bProject);
//#endif

    EDIT_FIND->setEnabled(bSourceCodeEditor);
    EDIT_REPLACE->setEnabled(bSourceCodeEditor);
    EDIT_GOTO->setEnabled(bSourceCodeEditor);
    EDIT_INSERT_FILE->setEnabled(bSourceCodeEditor);

    bool bbb = bCanCopy && (bForm || bReport || bSourceCodeEditor || bProjectWindow);
    bool bbb2 = bCanPaste && (bForm || bReport || bSourceCodeEditor || bProjectWindow);

    EDIT_FINDDEFINITION->setEnabled(bSourceCodeEditor);
    EDIT_APPLY->setEnabled(bbb && (bForm || bReport));
    EDIT_CUT->setEnabled(bbb);
    EDIT_COPY->setEnabled(bbb);
    EDIT_PASTE->setEnabled(bbb2);
    EDIT_DELETE->setEnabled(bCanCopy);
    EDIT_COMMENT_LINES->setEnabled(bbb && bSourceCodeEditor);
    EDIT_UNCOMMENT_LINES->setEnabled(bbb && bSourceCodeEditor);
    EDIT_INDENT_LINES->setEnabled(/*bbb && */bSourceCodeEditor);
    EDIT_UNINDENT_LINES->setEnabled(bbb && bSourceCodeEditor);
    EDIT_MARK_LINES->setEnabled(bbb && bSourceCodeEditor);
    EDIT_UPPER->setEnabled(bbb && bSourceCodeEditor);
    EDIT_LOWER->setEnabled(bbb && bSourceCodeEditor);
    EDIT_REDO->setEnabled(bCanRedo);
    EDIT_UNDO->setEnabled(bCanUndo);

    EDIT_BACKGROUND->setEnabled(bCanCopy & (bForm | bReport));
    EDIT_FONTNAME->setEnabled(bCanCopy & (bForm | bReport));
    EDIT_FONTCOLOR->setEnabled(bCanCopy & (bForm | bReport));
    EDIT_BOLD->setEnabled(bCanCopy & (bForm | bReport));
    EDIT_ITALIC->setEnabled(bCanCopy & (bForm | bReport));
    EDIT_UNDERLINE->setEnabled(bCanCopy & (bForm | bReport));
    EDIT_FONTSIZE->setEnabled(bCanCopy & (bForm | bReport));

    EDIT_SET_BOOKMARK->setEnabled(bSourceCodeEditor);
    RUN_SET_BREAKPOINT->setEnabled(bSourceCodeEditor);

    VIEW_DESIGN->setEnabled(bSourceCodeEditor);    

  
    if (bSourceCodeEditor){
      if (sFileName.endsWith(".kbasic_form", Qt::CaseInsensitive)){
        VIEW_DESIGN->setEnabled(bIsFormClassSourceCode);
        VIEW_DESIGN->setText(tr("Form"));
        VIEW_DESIGN->setToolTip(tr("Form"));
        VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_FORM.png")));
        VIEW_REPORTPREVIEW->setEnabled(false);
        EXTERN_my_sourcecodeeditor->events->setDisabled(false);
      } else if (sFileName.endsWith(".kbasic_report", Qt::CaseInsensitive)){
        VIEW_DESIGN->setEnabled(bIsFormClassSourceCode);
        VIEW_DESIGN->setText(tr("Report"));
        VIEW_DESIGN->setToolTip(tr("Report"));
        VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_REPORT.png")));    
        VIEW_REPORTPREVIEW->setEnabled(bIsFormClassSourceCode);
        EXTERN_my_sourcecodeeditor->events->setDisabled(false);
      } else if (sFileName.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){
        VIEW_DESIGN->setEnabled(bIsFormClassSourceCode);
        VIEW_DESIGN->setText(tr("MenuBar"));
        VIEW_DESIGN->setToolTip(tr("MenuBar"));
        VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_MENUBAR.png")));
        VIEW_REPORTPREVIEW->setEnabled(false);
        EXTERN_my_sourcecodeeditor->events->setDisabled(false);
      } else if (sFileName.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){
        VIEW_DESIGN->setEnabled(bIsFormClassSourceCode);
        VIEW_DESIGN->setText(tr("ToolBar"));
        VIEW_DESIGN->setToolTip(tr("ToolBar"));
        VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_TOOLBAR.png")));
        VIEW_REPORTPREVIEW->setEnabled(false);
        EXTERN_my_sourcecodeeditor->events->setDisabled(false);
      } else {
        VIEW_DESIGN->setEnabled(bIsFormClassSourceCode);
        VIEW_REPORTPREVIEW->setEnabled(false);
        EXTERN_my_sourcecodeeditor->events->setDisabled(true);
      }
    }

    if (bReport){
      VIEW_DESIGN->setText(tr("Report"));
      VIEW_DESIGN->setToolTip(tr("Report"));
      VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_REPORT.png")));

      VIEW_SOURCE_CODE->setText(tr("&Source Code"));
    } else if (bForm){ 
      VIEW_DESIGN->setText(tr("Form"));
      VIEW_DESIGN->setToolTip(tr("Form"));
      VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_FORM.png")));

      VIEW_SOURCE_CODE->setText(tr("&Source Code"));
    } else if (bTable){ 
      VIEW_DESIGN->setEnabled(bIsFormClassSourceCode);
      
      VIEW_DESIGN->setText(tr("Table"));
      VIEW_DESIGN->setToolTip(tr("Table"));
      VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_TABLE.png")));

      VIEW_SOURCE_CODE->setText(tr("&Data"));
      
    } else if (bQuery){ 
      VIEW_DESIGN->setText(tr("Query"));
      VIEW_DESIGN->setToolTip(tr("Query"));
      VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_QUERY.png")));

    //  VIEW_REPORTPREVIEW->setEnabled(true);

      VIEW_SOURCE_CODE->setText(tr("&Source Code"));
    } else if (bMenuBar){ 
      VIEW_DESIGN->setText(tr("Menubar"));
      VIEW_DESIGN->setToolTip(tr("Menubar"));
      VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_MENUBAR.png")));

      VIEW_SOURCE_CODE->setText(tr("&Source Code"));
    } else if (bToolBar){ 
      VIEW_DESIGN->setText(tr("Toolbar"));
      VIEW_DESIGN->setToolTip(tr("Toolbar"));
      VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_TOOLBAR.png")));

      VIEW_SOURCE_CODE->setText(tr("&Source Code"));
    } else {
      VIEW_DESIGN->setText(tr("Form"));
      VIEW_DESIGN->setToolTip(tr("Form"));
      VIEW_DESIGN->setIcon(kbasicIcon(kbasicPath("ide/VIEW_FORM.png")));
    }
    
    VIEW_FOCUSORDER->setEnabled(bForm);
    VIEW_FOCUSORDER->setChecked(bShowFocusOrder);
    VIEW_SQLSETTINGS->setEnabled(bForm | bReport);
    VIEW_SQLSETTINGS->setChecked(bShowSQLSettings);
    //VIEW_SQLTABLES->setEnabled(bForm | bQuery);
    //VIEW_SQLTABLES->setChecked(bShowSQLTables);

    VIEW_SOURCE_CODE->setEnabled(bForm | bReport | bMenuBar | bToolBar | (bTable && !bIsFormClassSourceCode));
    //VIEW_REPORT->setEnabled(false);
    VIEW_REPORTPREVIEW->setEnabled(bReport);
    //VIEW_MENUBAR->setEnabled(false);
    //VIEW_TOOLBAR->setEnabled(false);

    VIEW_FULLSCREEN->setEnabled(bSourceCodeEditor);
    VIEW_QBE->setEnabled(bProject);
    VIEW_RELATION->setEnabled(bProject);
    
    FORMAT_ALIGN_BOTTOM->setEnabled(bForm | bReport);
    FORMAT_ALIGN_TOP->setEnabled(bForm | bReport);
    FORMAT_ALIGN_LEFT->setEnabled(bForm | bReport);
    FORMAT_ALIGN_RIGHT->setEnabled(bForm | bReport);
    FORMAT_SET_SAME_WIDTH->setEnabled(bForm | bReport);
    FORMAT_SET_SAME_HEIGHT->setEnabled(bForm | bReport);
    FORMAT_SET_SAME_SIZE->setEnabled(bForm | bReport);
    FORMAT_LAYOUT_HORIZONTALLY->setEnabled(bForm | bReport);
    FORMAT_LAYOUT_VERTICALLY->setEnabled(bForm | bReport);
    FORMAT_MOVE_TO_FRONT->setEnabled(bForm | bReport);
    FORMAT_MOVE_TO_BACK->setEnabled(bForm | bReport);
    FORMAT_MOVE_UP->setEnabled(bForm | bReport | (bTable && !bIsFormClassSourceCode));
    FORMAT_MOVE_DOWN->setEnabled(bForm | bReport | (bTable && !bIsFormClassSourceCode));
    FORMAT_MOVE_LEFT->setEnabled(bForm | bReport | bQuery);
    FORMAT_MOVE_RIGHT->setEnabled(bForm | bReport | bQuery);



    INSERT_OPTION_KBASIC->setEnabled(bSourceCodeEditor);
    INSERT_OPTION_OLDBASIC->setEnabled(bSourceCodeEditor);
    INSERT_OPTION_VERYOLDBASIC->setEnabled(bSourceCodeEditor);
    INSERT_STATEMENT->setEnabled(bSourceCodeEditor);
    INSERT_ASSIGNMENT->setEnabled(bSourceCodeEditor);
    INSERT_EXPRESSION->setEnabled(bSourceCodeEditor);    
    INSERT_OPERATOR->setEnabled(bSourceCodeEditor);
    INSERT_IF->setEnabled(bSourceCodeEditor);
    INSERT_SELECT->setEnabled(bSourceCodeEditor);
    INSERT_FORNEXT->setEnabled(bSourceCodeEditor);
    INSERT_WHILELOOP->setEnabled(bSourceCodeEditor);
    INSERT_LOOPWHILE->setEnabled(bSourceCodeEditor);
    INSERT_EXCEPTION->setEnabled(bSourceCodeEditor);
    INSERT_VARIABLE->setEnabled(bSourceCodeEditor);
    INSERT_CONST->setEnabled(bSourceCodeEditor);
    INSERT_FIELDS_LINE->setEnabled(bSourceCodeEditor);
    INSERT_FIELDS_SCOPE->setEnabled(bSourceCodeEditor);
    INSERT_FIELDS_CLASS->setEnabled(bSourceCodeEditor);
    INSERT_FIELDS_MODULE->setEnabled(bSourceCodeEditor);
    INSERT_FIELDS_SUB->setEnabled(bSourceCodeEditor);
    INSERT_SUB->setEnabled(bSourceCodeEditor);
    INSERT_FUNCTION->setEnabled(bSourceCodeEditor);
    INSERT_PROPERTY->setEnabled(bSourceCodeEditor);
    INSERT_TYPE->setEnabled(bSourceCodeEditor);
    INSERT_ENUM->setEnabled(bSourceCodeEditor);
    INSERT_REMARK->setEnabled(bSourceCodeEditor);

    

    INSERT_SELECT2->setEnabled(bForm | bReport | bMenuBar | bToolBar);
    INSERT_LABEL->setEnabled(bForm | bReport);
    INSERT_TOOLBUTTON->setEnabled(bForm);
    INSERT_COMMANDBUTTON->setEnabled(bForm);
    INSERT_CHECKBOX->setEnabled(bForm | bReport);
    INSERT_RADIOBUTTON->setEnabled(bForm);
    INSERT_TEXTBOX->setEnabled(bForm | bReport);
    INSERT_FRAME->setEnabled(bForm | bReport);    
    INSERT_TEXTBOX_PASSWORD->setEnabled(bForm/* | bReport*/);
    INSERT_LABEL_LINK->setEnabled(bForm/* | bReport*/);
    INSERT_LINE_VERTICAL->setEnabled(bForm/* | bReport*/);
    INSERT_LINE_HORIZONTAL->setEnabled(bForm/* | bReport*/);
    INSERT_LISTBOX->setEnabled(bForm);
    INSERT_LISTBOX_ICONMODE->setEnabled(bForm);    
    INSERT_COMBOBOX->setEnabled(bForm);
    INSERT_PROGRESSBAR->setEnabled(bForm);
    INSERT_PROGRESSBAR_SPINNING->setEnabled(bForm);
    INSERT_TREEVIEW_LISTVIEW->setEnabled(bForm);
    INSERT_COMBOBOX_EDITABLE->setEnabled(bForm);    
    INSERT_IMAGE->setEnabled(bForm | bReport);

    INSERT_CHILDCONTROL->setEnabled(bForm);
    INSERT_BROWSER->setEnabled(bForm);
    INSERT_EDITOR->setEnabled(bForm | bReport);
    INSERT_DATEBOX->setEnabled(bForm | bReport);
    INSERT_TIMEBOX->setEnabled(bForm | bReport);
    INSERT_DATETIMEBOX->setEnabled(bForm | bReport);
    INSERT_UDPSOCKET->setEnabled(bForm);
    INSERT_SERIALPORT->setEnabled(bForm);

    // CONTROL
    INSERT_SPINBOX->setEnabled(bForm);
    INSERT_SCROLLBAR->setEnabled(bForm);
    INSERT_SLIDER->setEnabled(bForm);
    INSERT_FORMSVIEW->setEnabled(bForm);
    INSERT_TOOLBARVIEW->setEnabled(bForm);
    INSERT_SVG->setEnabled(bForm);
    INSERT_COMMANDLINKBUTTON->setEnabled(bForm);
    INSERT_RESIZEBOX->setEnabled(bForm);
    INSERT_HEADER->setEnabled(bReport);
    INSERT_FOOTER->setEnabled(bReport);
    INSERT_VSPLIT->setEnabled(bForm);
    INSERT_HSPLIT->setEnabled(bForm);
    INSERT_VBOX->setEnabled(bForm);
    INSERT_HBOX->setEnabled(bForm);
    INSERT_VHBOX->setEnabled(bForm);
    INSERT_BOX->setEnabled(bForm | bReport);
    INSERT_HIDDEN->setEnabled(bForm);
    INSERT_TREEVIEW->setEnabled(bForm);
    INSERT_TAB->setEnabled(bForm);
    INSERT_MOVIE->setEnabled(bForm);
    INSERT_SOUND->setEnabled(bForm);
    INSERT_WEB->setEnabled(bForm);
    INSERT_TIMER->setEnabled(bForm);
    INSERT_IMAGEBUTTON->setEnabled(bForm);

    INSERT_MENU->setEnabled(bMenuBar);
    INSERT_CHILDMENU->setEnabled(bMenuBar);
    INSERT_MENUBARITEM->setEnabled(bMenuBar);
    INSERT_MOVE->setEnabled(bMenuBar | bToolBar);
    INSERT_DELETE->setEnabled(bMenuBar | bToolBar);
    INSERT_TOOLBARITEM->setEnabled(bToolBar);

    PROJECT_DATABASE->setEnabled(bProject);
    PROJECT_TRANSLATION->setEnabled(bProject);
    PROJECT_SET_AS_DEFAULT->setEnabled(bProject);
    PROJECT_PROPERTIES_OF_PROJECT->setEnabled(bProject);
    
    FILE_IMPORT_CSV->setEnabled(bProject);
    EXTERN_my_mainwindow->FILE_EXPORT_CSV->setEnabled(bProject && bTable);

    updateRunActions();

#ifndef LINUX
    if (!bRersourcesAreSelected) EXTERN_my_propertywindow->setEnabled((bForm | bReport | bMenuBar | bToolBar | bTable | bSourceCodeEditor) && !(bTable && bIsFormClassSourceCode));
#endif
    EXTERN_my_helpwindow_shortcut->setEnabled(bSourceCodeEditor);

    closeAct->setEnabled(!bMainWindow && !bProjectWindow);

  
}

void _mainwindow::updateRunActions()
{
  bool b = EXTERN_my_mainwindow->isRunning() | EXTERN_my_mainwindow->isCompiling() | EXTERN_my_mainwindow->isDebugging();

  EXTERN_my_mainwindow->RUN_RUN_PROJECT->setEnabled(!b);
  EXTERN_my_mainwindow->RUN_RUN_PCODE2->setEnabled(!b);
  EXTERN_my_mainwindow->RUN_PAUSE->setEnabled(b);
  EXTERN_my_mainwindow->RUN_STOP->setEnabled(b);

#ifdef WINDOWS
  EXTERN_my_mainwindow->PROJECT_MAKE_RUNTIME_WINDOWS->setEnabled(!b);
#endif
#ifdef LINUX
  EXTERN_my_mainwindow->PROJECT_MAKE_RUNTIME_LINUX->setEnabled(!b);
#endif
#ifdef MAC
  EXTERN_my_mainwindow->PROJECT_MAKE_RUNTIME_MACOS->setEnabled(!b);
#endif

  EXTERN_my_mainwindow->RUN_BUILD->setEnabled(!b);
  EXTERN_my_mainwindow->RUN_BUILD_ALL->setEnabled(!b);    
  EXTERN_my_mainwindow->RUN_SUB->setEnabled(!b);
  EXTERN_my_mainwindow->RUN_RUN_PCODE3->setEnabled(!b);
  EXTERN_my_mainwindow->RUN_RUN->setEnabled(!b);


  EXTERN_my_mainwindow->RUN_RUN_IN_DEBUG->setEnabled(!b);
  EXTERN_my_mainwindow->RUN_RUN_IN_DEBUG2->setEnabled(!b);
        
  b = EXTERN_my_mainwindow->isDebugging();  
  EXTERN_my_mainwindow->RUN_CONTINUE_PCODE->setEnabled(b);
  EXTERN_my_mainwindow->RUN_SINGLE_STEP->setEnabled(b);
  EXTERN_my_mainwindow->RUN_STEP_OVER->setEnabled(b);
  EXTERN_my_mainwindow->RUN_STEP_OUT->setEnabled(b);
  EXTERN_my_mainwindow->RUN_TO_CURSOR->setEnabled(b);

  EXTERN_my_mainwindow->VIEW_KONSOLE->setEnabled(!b);
  EXTERN_my_mainwindow->VIEW_LOG->setEnabled(!b);

}

void _mainwindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    workspace->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}
