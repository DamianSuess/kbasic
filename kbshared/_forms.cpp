/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use forms_mainwindow source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#include "_forms.h"


#include "typedef.h"

#ifdef RUN
#include "../kbasic_binding/_menubar/kb_menubar.h"
#include "../kbasic_binding/_toolbar/kb_toolbar.h"
#include "../kbasic_binding/_menubaritem/kb_menubaritem.h"

extern QString idePath(QString s);

extern int nCurrentFormId;
extern QMap<QString,int>forms2;

extern QMap<QString,QString>trs;

#include "../kbasic_binding/_form/kb_form.h"

#include "../kbrun/interpreter.h"

#include "../kbasic_binding/_application/kb_application.h"
#include "../kbasic_binding/_mainwindow/kb_mainwindow.h"

extern interpreter *EXTERN_myInterpreter;

extern QSettings *settings;

extern QString sProjectName;
extern QString sProjectType;


extern QString sLogin;

extern QString dbdriver;

extern QMap<int,QString>forms;
extern QMap<QString,int>menubaritems;
extern QMap<QString,int>toolbaritems;



extern screen *myScreen;

extern bool menuRecords;
extern bool menuWindow;
extern bool menuHelp;

#include <QMainWindow>
//#include <QWorkspace>
#include <QSignalMapper>

bool bLogin = false;

QSystemTrayIcon *trayIcon;
QMovie *trayIcon_movie; QByteArray *trayIcon_moviea; QBuffer *trayIcon_movieb;
QString sSystemTrayIcon;
QString sSystemTrayContextMenu;


QSignalMapper *windowMapper = 0;
QMdiArea *forms_workspace = 0;
QMainWindow *forms_mainwindow = 0;
QMenu *windowMenu = 0;
QMenu *recordMenu = 0;

QAction *aWindow = 0;
QAction *aHelp = 0;
QAction *aRecords = 0;
QAction *aContents = 0;
QAction *aAbout = 0;

QAction *aCloseAct = 0;
QAction *aCloseAllAct = 0;
QAction *aTileAct = 0;
QAction *aCascadeAct = 0;
//QAction *arrangeAct;
QAction *aNextAct = 0;
QAction *aPreviousAct = 0;
QAction *aSeparatorAct = 0;


QAction *aAddFilter = 0;
QAction *aAddNotFilter = 0;

QAction *aSetFilter = 0;
QAction *aSetNotFilter = 0;

QAction *aClearFilter = 0;
QAction *aSortAscending = 0;

QAction *aSortDescending = 0;
QAction *aSeek = 0;

QAction *aRequery = 0;
QAction *aAddNew = 0;
QAction *aUpdate = 0;
QAction *aDelete = 0;

QAction *aCut = 0;
QAction *aCopy = 0;
QAction *aPaste = 0;



_forms *my_forms = 0;

bool bInit = false;


class _mainwindow : public QMainWindow
{
public:

void closeEvent(QCloseEvent *e)
{
  EXTERN_myInterpreter->stop_interpret();
  e->accept();
} 

};


extern const QPixmap &interpreter_loadPixmap(QString fn);
extern const QString interpreter_loadFileAsString(QString fn);


QString getFilenameWithoutPath(QString s)
{       
  int i = s.lastIndexOf('\\');
  if (i == -1){
    i = s.lastIndexOf('/');
  }
  s = s.right(s.length() - i - 1);
  return s; 
}

QString getFilenameWithoutPathAndExtension(QString s)
{       
  QString k = getFilenameWithoutPath(s);

  int i = k.lastIndexOf('.');

  k = k.left(i);
  return k; 
}

//QTranslator *defaultTranslator = 0;

bool bMDI = false;
bool bSDI = false;

extern bool bDbsettablesforruntime;
extern QString dbtables;

void _forms::init()
{
  if (bInit) return;
  QPixmap p = interpreter_loadPixmap("application_splash.png");

  myScreen->setWindowIcon2(); // set the black screen icon here, because png was just loaded
  
  QSplashScreen *splash = 0;

  if (!p.isNull()) splash = new QSplashScreen(p);
  if (splash) splash->show();


  my_forms = new _forms();

  trayIcon = new QSystemTrayIcon();
  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), my_forms, SLOT(activated(QSystemTrayIcon::ActivationReason)));
  connect(trayIcon, SIGNAL(messageClicked()), my_forms, SLOT(messageClicked()));
   
  trayIcon_movie = 0; trayIcon_moviea = 0; trayIcon_movieb = 0;


  bMDI = sProjectType.contains(" MDI ", Qt::CaseInsensitive);
  bSDI = sProjectType.contains(" SDI ", Qt::CaseInsensitive);
 

  if (!bSDI && !bMDI){
    bMDI = sProjectType.contains("With Forms", Qt::CaseInsensitive);
  }


  if (!bSDI && !bMDI){
    QString qss = interpreter_loadFileAsString("application.qss");
    if (!qss.isEmpty()) qApp->setStyleSheet(qss);
  }


  if (bSDI || bMDI) forms_mainwindow = (QMainWindow *) new _mainwindow(); else forms_mainwindow = 0;
  forms_workspace = 0;
    
  kb_menubar *my_menubar = 0;
  kb_toolbar *my_toolbar = 0;

  
  
  settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, sProjectName.isNull() ? MYAPP : sProjectName);
  sCurrentLanguage = settings->value("Language").toString();
  sCurrentCountry = settings->value("Country").toString();

  if (!sLogin.isEmpty()){
    if (splash){
      delete splash;
      splash = 0;
    }

    bLogin = true;
    nCurrentFormId = forms2[sLogin];
    interpreter::openForm(sLogin);
    bLogin = false;
    
  }

        


  QString trWindow = "&Window"; if (trs.contains(trWindow)){ QString ss = trs[trWindow]; if (!ss.isEmpty()) trWindow = ss; }
  QString trHelp = "&Help"; if (trs.contains(trHelp)){ QString ss = trs[trHelp]; if (!ss.isEmpty()) trHelp = ss; }
  QString trContents = "C&ontents"; if (trs.contains(trContents)){ QString ss = trs[trContents]; if (!ss.isEmpty()) trContents = ss; }
  QString trAbout = "A&bout"; if (trs.contains(trAbout)){ QString ss = trs[trAbout]; if (!ss.isEmpty()) trAbout = ss; }


  QString trClose = "Cl&ose"; if (trs.contains(trClose)){ QString ss = trs[trClose]; if (!ss.isEmpty()) trClose = ss; }
  QString trCloseAll = "Close &All"; if (trs.contains(trCloseAll)){ QString ss = trs[trCloseAll]; if (!ss.isEmpty()) trCloseAll = ss; }
  QString trTile = "&Tile"; if (trs.contains(trTile)){ QString ss = trs[trTile]; if (!ss.isEmpty()) trTile = ss; }
  QString trCascade = "&Cascade"; if (trs.contains(trCascade)){ QString ss = trs[trCascade]; if (!ss.isEmpty()) trCascade = ss; }
  QString trNext = "Ne&xt"; if (trs.contains(trNext)){ QString ss = trs[trNext]; if (!ss.isEmpty()) trNext = ss; }
  QString trPrevious = "Pre&vious"; if (trs.contains(trPrevious)){ QString ss = trs[trPrevious]; if (!ss.isEmpty()) trPrevious = ss; }

  QString trRecord = "&Records"; if (trs.contains(trRecord)){ QString ss = trs[trRecord]; if (!ss.isEmpty()) trRecord = ss; }
  QString trRequery = "&Requery"; if (trs.contains(trRequery)){ QString ss = trs[trRequery]; if (!ss.isEmpty()) trRequery = ss; }
  QString trAddNew = "Add &New"; if (trs.contains(trAddNew)){ QString ss = trs[trAddNew]; if (!ss.isEmpty()) trAddNew = ss; }
  QString trUpdate = "&Update"; if (trs.contains(trUpdate)){ QString ss = trs[trUpdate]; if (!ss.isEmpty()) trUpdate = ss; }
  QString trDelete = "&Delete"; if (trs.contains(trDelete)){ QString ss = trs[trDelete]; if (!ss.isEmpty()) trDelete = ss; }
  QString trSeek = "&Seek"; if (trs.contains(trSeek)){ QString ss = trs[trSeek]; if (!ss.isEmpty()) trSeek = ss; }
  QString trAddFilter = "&Add Filter"; if (trs.contains(trAddFilter)){ QString ss = trs[trAddFilter]; if (!ss.isEmpty()) trAddFilter = ss; }
  QString trAddNotFilter = "Add &NotFilter"; if (trs.contains(trAddNotFilter)){ QString ss = trs[trAddNotFilter]; if (!ss.isEmpty()) trAddNotFilter = ss; }
  QString trSetFilter = "&Set Filter"; if (trs.contains(trSetFilter)){ QString ss = trs[trSetFilter]; if (!ss.isEmpty()) trSetFilter = ss; }
  QString trSetNotFilter = "Set &NotFilter"; if (trs.contains(trSetNotFilter)){ QString ss = trs[trSetNotFilter]; if (!ss.isEmpty()) trSetNotFilter = ss; }
  QString trClearFilter = "&Clear Filter"; if (trs.contains(trClearFilter)){ QString ss = trs[trClearFilter]; if (!ss.isEmpty()) trClearFilter = ss; }
  QString trSortAscending = "Sort Ascen&ding"; if (trs.contains(trSortAscending)){ QString ss = trs[trSortAscending]; if (!ss.isEmpty()) trSortAscending = ss; }
  QString trSortDescending = "Sort Desce&nding"; if (trs.contains(trSortDescending)){ QString ss = trs[trSortDescending]; if (!ss.isEmpty()) trSortDescending = ss; }
/*
  QString trCut = "Cut";
  QString trCopy = "Copy";
  QString trPaste = "Paste";
*/


#ifdef MAC
  qApp->setAttribute(Qt::AA_DontShowIconsInMenus); // HIDE
#endif

  qApp->setQuitOnLastWindowClosed(true);


  qApp->connect(qApp, SIGNAL(lastWindowClosed()), my_forms, SLOT(lastWindowClosed()));

  if (forms_mainwindow){
    
    if (bMDI){
      forms_workspace = new QMdiArea;  
#ifdef MAC
  //QFont f = workspace->font(); f.setPixelSize(12); workspace->setFont(f); 
  forms_workspace->setDocumentMode(true);
#endif
    }

    if (splash) splash->finish(forms_mainwindow);  
    
      

    if (EXTERN_my_menubar){
      my_menubar = (kb_menubar *) EXTERN_my_menubar;
      my_menubar->loadMenubar("myMenuBar");
      my_menubar->setObjectName("myMenuBar");

      // set the global menubaritems automatically
      {
        _menubaritem *c;

        if (EXTERN_my_menubar->firstControl(&c)){
         
          do {

            QString s = c->GETPROPERTY_Name();
            int id = menubaritems[s];

            memory_variable2 *v = EXTERN_myInterpreter->getVar(global);

            kb_menubaritem *it = (kb_menubaritem *) c;

            v->setPointer(id, it, 0);

          } while (EXTERN_my_menubar->nextControl(&c)); 
        }
      }

    }

    if (EXTERN_my_toolbar){
      my_toolbar = (kb_toolbar *) EXTERN_my_toolbar;
      my_toolbar->loadToolbar("myToolBar");
      my_toolbar->setWindowTitle(tr("Toolbar"));
      my_toolbar->setObjectName("myToolBar");
      
#ifdef MAC
    my_toolbar->setMovable(false);
#endif    
    


      // set the global menubaritems automatically
      {
        _toolbaritem *c;

        if (EXTERN_my_toolbar->firstControl(&c)){
         
          do {

            QString s = c->GETPROPERTY_Name();
            int id = toolbaritems[s];

            memory_variable2 *v = EXTERN_myInterpreter->getVar(global);

            kb_toolbar *it = (kb_toolbar *) c;

            v->setPointer(id, it, 0);

          } while (EXTERN_my_toolbar->nextControl(&c)); 
        }
      }
    }
  }

  qApp->setApplicationName(sProjectName.isNull() ? MYAPP : sProjectName); // project property project name


  if (my_menubar){
    if (bMDI){
      QAction *a;

      if (!dbdriver.isEmpty() && menuRecords){
        recordMenu = my_menubar->addMenu((trRecord));
        aRecords = recordMenu->menuAction();


        aAddFilter = new QAction(QIcon(interpreter_loadPixmap("SQLAddFilter.png")), (trAddFilter), forms_mainwindow);
        QObject::connect(aAddFilter, SIGNAL(triggered()), my_forms, SLOT(SLOT_AddFilter()));    
        recordMenu->addAction(aAddFilter);

        aAddNotFilter = new QAction(QIcon(interpreter_loadPixmap("SQLAddNotFilter.png")), (trAddNotFilter), forms_mainwindow);
        QObject::connect(aAddNotFilter, SIGNAL(triggered()), my_forms, SLOT(SLOT_AddNotFilter()));    
        recordMenu->addAction(aAddNotFilter);

        aClearFilter = new QAction(QIcon(interpreter_loadPixmap("SQLClearFilter.png")), (trClearFilter), forms_mainwindow);
        QObject::connect(aClearFilter, SIGNAL(triggered()), my_forms, SLOT(SLOT_ClearFilter()));    
        recordMenu->addAction(aClearFilter);

        recordMenu->addSeparator();

        aSetFilter = new QAction(QIcon(interpreter_loadPixmap("SQLSetFilter.png")), (trSetFilter), forms_mainwindow);
        QObject::connect(aSetFilter, SIGNAL(triggered()), my_forms, SLOT(SLOT_SetFilter()));    
        recordMenu->addAction(aSetFilter);

        aSetNotFilter = new QAction(QIcon(interpreter_loadPixmap("SQLSetNotFilter.png")), (trSetNotFilter), forms_mainwindow);
        QObject::connect(aSetNotFilter, SIGNAL(triggered()), my_forms, SLOT(SLOT_SetNotFilter()));    
        recordMenu->addAction(aSetNotFilter);

        recordMenu->addSeparator();

        aSortAscending = new QAction(QIcon(interpreter_loadPixmap("SQLSortAscending.png")), (trSortAscending), forms_mainwindow);
        QObject::connect(aSortAscending, SIGNAL(triggered()), my_forms, SLOT(SLOT_SortAscending()));    
        recordMenu->addAction(aSortAscending);

        aSortDescending = new QAction(QIcon(interpreter_loadPixmap("SQLSortDescending.png")), (trSortDescending), forms_mainwindow);
        QObject::connect(aSortDescending, SIGNAL(triggered()), my_forms, SLOT(SLOT_SortDescending()));    
        recordMenu->addAction(aSortDescending);

        recordMenu->addSeparator();

        aSeek = new QAction(QIcon(interpreter_loadPixmap("SQLSeek.png")), (trSeek), forms_mainwindow);
        QObject::connect(aSeek, SIGNAL(triggered()), my_forms, SLOT(SLOT_Seek()));    
        recordMenu->addAction(aSeek);

        recordMenu->addSeparator();

        aRequery = new QAction(QIcon(interpreter_loadPixmap("SQLRequery.png")), (trRequery), forms_mainwindow);
        QObject::connect(aRequery, SIGNAL(triggered()), my_forms, SLOT(SLOT_Requery()));    
        recordMenu->addAction(aRequery);
      }

/*
      recordMenu->addSeparator();

      aCut = new QAction(QIcon(interpreter_loadPixmap("SQLCut.png")), (trCut), forms_mainwindow);
      QObject::connect(aCut, SIGNAL(triggered()), my_forms, SLOT(SLOT_Cut()));    
      recordMenu->addAction(aCut);

      aCopy = new QAction(QIcon(interpreter_loadPixmap("SQLCopy.png")), (trCopy), forms_mainwindow);
      QObject::connect(aCopy, SIGNAL(triggered()), my_forms, SLOT(SLOT_Copy()));    
      recordMenu->addAction(aCopy);

      aPaste = new QAction(QIcon(interpreter_loadPixmap("SQLPaste.png")), (trPaste), forms_mainwindow);
      QObject::connect(aPaste, SIGNAL(triggered()), my_forms, SLOT(SLOT_Paste()));    
      recordMenu->addAction(aPaste);*/
/*
      recordMenu->addSeparator();

      aAddNew = new QAction(QIcon(interpreter_loadPixmap("SQLAddNew.png")), (trAddNew), forms_mainwindow);
      QObject::connect(aAddNew, SIGNAL(triggered()), my_forms, SLOT(SLOT_AddNew()));    
      recordMenu->addAction(aAddNew);

      aUpdate = new QAction(QIcon(interpreter_loadPixmap("SQLUpdate.png")), (trUpdate), forms_mainwindow);
      QObject::connect(aUpdate, SIGNAL(triggered()), my_forms, SLOT(SLOT_Update()));    
      recordMenu->addAction(aUpdate);

      aDelete = new QAction(QIcon(interpreter_loadPixmap("SQLDelete.png")), (trDelete), forms_mainwindow);
      QObject::connect(aDelete, SIGNAL(triggered()), my_forms, SLOT(SLOT_Delete()));    
      recordMenu->addAction(aDelete);
*/


      if (menuWindow && bMDI){
        windowMenu = my_menubar->addMenu((trWindow));
        aWindow = windowMenu->menuAction();
      }

      if (menuHelp){

        QMenu *HELP;
        


        HELP = my_menubar->addMenu((trHelp));  
        aHelp = HELP->menuAction();

        aContents = new QAction((trContents), forms_mainwindow);
        QObject::connect(aContents, SIGNAL(triggered()), my_forms, SLOT(CONTENTS()));    

        HELP->addAction(aContents);

        HELP->addSeparator();


        aAbout = new QAction((trAbout), forms_mainwindow);
        QObject::connect(aAbout, SIGNAL(triggered()), my_forms, SLOT(ABOUT()));    

        HELP->addAction(aAbout);

      }


      if (menuWindow){

        aCloseAct = new QAction((trClose), forms_mainwindow);
        aCloseAct->setShortcut(QObject::tr("Ctrl+F4"));
        QObject::connect(aCloseAct, SIGNAL(triggered()), forms_workspace, SLOT(closeActiveSubWindow()));

        aCloseAllAct = new QAction((trCloseAll), forms_mainwindow);
        QObject::connect(aCloseAllAct, SIGNAL(triggered()), forms_workspace, SLOT(closeAllSubWindows()));

        aTileAct = new QAction((trTile), forms_mainwindow);
        QObject::connect(aTileAct, SIGNAL(triggered()), forms_workspace, SLOT(tileSubWindows()));

        aCascadeAct = new QAction((trCascade), forms_mainwindow);
        QObject::connect(aCascadeAct, SIGNAL(triggered()), forms_workspace, SLOT(cascadeSubWindows()));


        aNextAct = new QAction((trNext), forms_mainwindow);    
        aNextAct->setShortcut(QObject::tr("CTRL+F6"));
        QObject::connect(aNextAct, SIGNAL(triggered()), forms_workspace, SLOT(activateNextSubWindow()));

        aPreviousAct = new QAction((trPrevious), forms_mainwindow);
        aPreviousAct->setShortcut(QObject::tr("CTRL+SHIFT+F6"));
        QObject::connect(aPreviousAct, SIGNAL(triggered()), forms_workspace, SLOT(activatePreviousSubWindow()));

        aSeparatorAct = new QAction(forms_mainwindow);
        aSeparatorAct->setSeparator(true);
      }
    }

    forms_mainwindow->setWindowTitle(sProjectName.isNull() ? MYAPP : sProjectName); // project property project name
    p = interpreter_loadPixmap("application_icon.png");
    if (!p.isNull()){
      forms_mainwindow->setWindowIcon(QIcon(p));
    } else {
#ifdef MAC
      forms_mainwindow->setWindowIcon(QIcon(idePath("APPLICATION_ICON.png")));
#endif
    }

    QString qss = interpreter_loadFileAsString("application.qss");
    if (!qss.isEmpty()) qApp->setStyleSheet(qss);
/*
    p = interpreter_loadPixmap("application_icon.png");
    if (!p.isNull()) forms_mainwindow->setWindowIcon(QIcon(p));
*/
    if (bMDI){
      forms_workspace->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
      forms_workspace->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

      forms_mainwindow->setCentralWidget(forms_workspace);
      QObject::connect(forms_workspace, SIGNAL(subWindowActivated(QMdiSubWindow *)), my_forms, SLOT(subWindowActivated(QMdiSubWindow *)));    

      windowMapper = new QSignalMapper(forms_mainwindow);
      QObject::connect(windowMapper, SIGNAL(mapped(QWidget *)), my_forms, SLOT(setActiveSubWindow(QWidget *)));

      if (menuWindow) QObject::connect(windowMenu, SIGNAL(aboutToShow()), my_forms, SLOT(updateWindowMenu()));

    } else {
      forms_mainwindow->setCentralWidget(0);
    }

    if (!my_menubar->isEmpty()) forms_mainwindow->setMenuBar(my_menubar);
  }

  if (my_toolbar){ 
    if (!my_toolbar->isEmpty()) forms_mainwindow->addToolBar(my_toolbar);
    if (bMDI){
      if (!dbdriver.isEmpty()){
/*
        QToolBar *t = new QToolBar();
        t->setWindowTitle(tr("Records"));
        t->setObjectName("ToolBarRecords");

        forms_mainwindow->addToolBar(t);
        
        t->addAction(aAddFilter);
        t->addAction(aAddNotFilter);
        t->addAction(aSetFilter);
        t->addAction(aSetNotFilter);
        t->addAction(aClearFilter);
        t->addSeparator();
        t->addAction(aSortAscending);
        t->addAction(aSortDescending);
        t->addSeparator();
        t->addAction(aSeek);
        */
        /*t->addSeparator();
        t->addAction(aRequery);
        
        t->addSeparator();
        t->addAction(aAddNew);
        t->addAction(aUpdate);
        t->addAction(aDelete);*/
      }

    }

  }

  if (!sCurrentCountry.isEmpty()){
    _application::METHOD_SetCountry(sCurrentCountry); // must be called before _application::METHOD_SetLanguage
  }


  if (splash){
    delete splash;
    splash = 0;
  }

  if (forms_mainwindow){ // readSettings
    QSettings settings(sProjectName.isNull() ? MYAPP : sProjectName, "Settings");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();    
    forms_mainwindow->restoreState(settings.value("saveState").toByteArray());
    if (pos.x() < 0) pos.setX(0);
    if (pos.y() < 0) pos.setY(0);
    if (size.width() < 0) size.setWidth(50);
    if (size.height() < 0) size.setHeight(50);
    forms_mainwindow->move(pos);
    forms_mainwindow->resize(size);
  }
   if (forms_mainwindow) forms_mainwindow->show();

    if (bDbsettablesforruntime){
      QStringList l = dbtables.split("|");
      foreach(QString q, l){
        if (!_table2::METHOD_Exists1(q)){
          _table2::METHOD_Create3(q);
        }
      }
    }

  bInit = true;
}


void _forms::deinit()
{  
  if (my_forms) delete my_forms;
  //if (defaultTranslator) delete defaultTranslator;

  bInit = false;  
  if (forms_mainwindow){// writeSettings
    QSettings settings(sProjectName.isNull() ? MYAPP : sProjectName, "Settings");
    settings.setValue("pos", forms_mainwindow->pos());
    settings.setValue("size", forms_mainwindow->size());
    settings.remove("saveState");
    settings.setValue("saveState", forms_mainwindow->saveState());
  }

  delete forms_mainwindow; forms_mainwindow = 0;

  trayIcon->hide();
  delete trayIcon;
  if (trayIcon_movie) delete trayIcon_movie; if (trayIcon_moviea) delete trayIcon_moviea; if (trayIcon_movieb) delete trayIcon_movieb;
}

void _forms::updateWindowMenu()
{
  windowMenu->clear();
  windowMenu->addAction(aCloseAct);
  windowMenu->addAction(aCloseAllAct);
  windowMenu->addSeparator();
  windowMenu->addAction(aTileAct);
  windowMenu->addAction(aCascadeAct);
  //windowMenu->addAction(arrangeAct);
  windowMenu->addSeparator();
  windowMenu->addAction(aNextAct);
  windowMenu->addAction(aPreviousAct);
  windowMenu->addAction(aSeparatorAct);

  int i = 0;
  if (forms_workspace){

    QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

    QString s = "";
    QWidget *w = 0;
    QMdiSubWindow *subw = 0;
    QString text;

    QMdiSubWindow *aw = forms_workspace->activeSubWindow();
    for (; i < windows.size(); ++i) {
        subw = windows.at(i);
        w = subw->widget();

        if (w == 0){          
          continue;
        }

        _form *f;
        if ((f = qobject_cast<_form *>(w))){
          w = f;
          s = f->GETPROPERTY_Caption();
          if (s.length() == 0){
            s = f->getFilenameWithoutPathAndExtension();
          }
        }

        if (s.length() == 0){
          s = QObject::tr("unnamed document");
        }
        
        if (i < 9) {
          text = QObject::tr("&%1 %2").arg(i + 1).arg(s);
        } else {
          text = QObject::tr("%1 %2").arg(i + 1).arg(s);
        }
        QAction *action = windowMenu->addAction(text);
        action->setCheckable(true);
        action->setChecked(subw == aw);
       QObject::connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, subw);
    }

  }
  
  aSeparatorAct->setVisible(i != 0);   

} 



kb_form *_forms::METHOD_Form(QString s)
{
  if (forms_mainwindow == 0) return 0;

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();
  

   

  int i = 0;
  for (; i < windows.size(); ++i) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
      if (s == f->GETPROPERTY_Name()){
        return (kb_form *) f;
      }
    }
  }  

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){
        return (kb_form *) f;
      }
    }
  }
  return 0;
}

void _forms::METHOD_OpenForm(QString k)
{
  if (forms_mainwindow == 0) return;

  nCurrentFormId = forms2[k];
  interpreter::openForm(k);
} 

void _forms::METHOD_CloseForm(QString s)
{
  if (forms_mainwindow == 0) return;

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  for (int i = 0; i < windows.size(); ++i) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
      if (s == f->GETPROPERTY_Name()){
        f->close();        
        return;
      }
    }
  }  

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      if (s == f->GETPROPERTY_Name()){
        f->close();
        return;
      }
    }
  }
} 
/*
void _forms::METHOD_SetMenuBar(QString k)
{
} 

void _forms::METHOD_AppendToolBar(QString k)
{
} 

void _forms::METHOD_InsertToolBarBreak()
{
} 

void _forms::METHOD_RemoveToolBar(QString k)
{
} 

QString _forms::METHOD_ActiveControl()
{
  return "";
} */

QString _forms::METHOD_FocusForm()
{
  if (forms_mainwindow == 0) return "";
  if (forms_workspace->activeSubWindow() == 0) return "";

  _form *o = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (o){
    return o->GETPROPERTY_Name();
  }
  return "";
} 

int ii = 0;
QString _forms::METHOD_FirstForm()
{
  if (forms_mainwindow == 0) return "";

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  ii = 0;
  if (ii < windows.size()){
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(ii)))){
      ii++;
      return f->GETPROPERTY_Name();
    }
  }  
/*
  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    / *kb* /_form *f;
    if ((f = qobject_cast</ *kb* /_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){
        return f->GETPROPERTY_Name();
      }
    }
  }
*/
  return "";
} 

QString _forms::METHOD_NextForm()
{
  if (forms_mainwindow == 0) return "";

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  for (; ii > 0 && ii < windows.size(); ) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(ii)))){
      ii++;
      return f->GETPROPERTY_Name();
    } else {
      ii++;
    }
  }  
/*
  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    / *kb* /_form *f;
    if ((f = qobject_cast</ *kb * /_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){
        return f->GETPROPERTY_Name();
      }
    }
  }
*/
  ii = 0;
  return "";
} 

void _forms::METHOD_SetFocusForm(QString s)
{
  if (forms_mainwindow == 0) return;

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  for (int i = 0; i < windows.size(); ++i) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
      if (s == f->GETPROPERTY_Name()){
        f->activateWindow();
        f->setFocus();
        return;
      }
    }
  }  

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){
        f->activateWindow();
        f->setFocus();
        return;
      }
    }
  }

} 

t_boolean _forms::METHOD_IsOpen(QString s)
{
  if (forms_mainwindow){
    QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

    for (int i = 0; i < windows.size(); ++i) {
      _form *f;
      if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
        if (s == f->GETPROPERTY_Name()){
          return true;
        }
      }
    }
  }

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k && f->isVisible()){ // WORKAROUND isVisible(), widgets don't seem to be closed() for qApp
        return true;
      }
    }
  }
  return false;
}

void _forms::CONTENTS()
{  
  kb_menubar *my_menubar = (kb_menubar *) EXTERN_my_menubar;
  my_menubar->callCustomEvent("Contents");
}

void _forms::ABOUT()
{
  kb_menubar *my_menubar = (kb_menubar *) EXTERN_my_menubar;
  my_menubar->callCustomEvent("About");
}

void _forms::SLOT_AddFilter()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_AddFilter("=", true);
  }
}

void _forms::SLOT_AddNotFilter()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_AddFilter("<>", true);
  }
}

void _forms::SLOT_SetFilter()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_SetFilter("=");
  }
}

void _forms::SLOT_SetNotFilter()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_SetFilter("<>");
  }
}

void _forms::SLOT_ClearFilter()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_ClearFilter();
  }
}

void _forms::SLOT_SortAscending()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_SortAsc("");
  }
}

void _forms::SLOT_SortDescending()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_SortDesc("");
  }
}

void _forms::SLOT_Seek()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_Seek("", "", "", "", "", "");
  }
}

void _forms::SLOT_Requery()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_Requery();
  }
}

void _forms::SLOT_AddNew()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_AddNew();
  }
}

void _forms::SLOT_Update()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_Update();
  }
}

void _forms::SLOT_Delete()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_Delete();
  }
}

void _forms::SLOT_Cut()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_Cut();
  }
}

void _forms::SLOT_Copy()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_Copy();
  }
}

void _forms::SLOT_Paste()
{
  if (forms_mainwindow == 0) return;
  if (forms_workspace->activeSubWindow() == 0) return;

  _form *f;
  f = qobject_cast<_form *>(forms_workspace->activeSubWindow()->widget());
  if (f){
    f->METHOD_Paste();
  }
}

void _forms::subWindowActivated(QMdiSubWindow *w)
{
  if (w == 0){
    _application::EVENT_Forms_OnFormGotFocus("");
    return;
  }

  _form *f;
  f = qobject_cast<_form *>((/*(QMdiSubWindow *)*/ w)->widget());
  if (f){
    _application::EVENT_Forms_OnFormGotFocus(f->GETPROPERTY_Name());
  } else {
    _application::EVENT_Forms_OnFormGotFocus("");
  }
} 

void _forms::lastWindowClosed()
{
  EXTERN_myInterpreter->stop_interpret();
} 

void _forms::METHOD_FormShowFullScreen(QString s)
{
  if (forms_mainwindow == 0) return;

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  for (int i = 0; i < windows.size(); ++i) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
      if (s == f->GETPROPERTY_Name()){
        f->METHOD_ShowFullScreen();
        return;
      }
    }
  }

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){
        f->showFullScreen();
        return;
      }
    }
  }
}

void _forms::METHOD_FormShowMaximized(QString s)
{
  if (forms_mainwindow == 0) return;

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  for (int i = 0; i < windows.size(); ++i) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
      if (s == f->GETPROPERTY_Name()){
        f->showMaximized();
        return;
      }
    }
  }

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){
        f->showMaximized();
        return;
      }
    }
  }
}

void _forms::METHOD_FormShowMinimized(QString s)
{
  if (forms_mainwindow == 0) return;

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  for (int i = 0; i < windows.size(); ++i) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
      if (s == f->GETPROPERTY_Name()){
        f->showMinimized();
        return;
      }
    }
  }

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){
        f->showMinimized();
        return;
      }
    }
  }
}

void _forms::METHOD_FormShowNormal(QString s)
{
  if (forms_mainwindow == 0) return;

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  for (int i = 0; i < windows.size(); ++i) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
      if (s == f->GETPROPERTY_Name()){
        f->showNormal();
        return;
      }
    }
  }

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){
        f->showNormal();
        return;
      }
    }
  }
}

void _forms::METHOD_FormShow(QString s)
{
  if (forms_mainwindow == 0) return;

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  for (int i = 0; i < windows.size(); ++i) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
      if (s == f->GETPROPERTY_Name()){

       if (f->dock) f->dock->show(); 
       if (f->parentWidget() && qobject_cast<QMdiSubWindow *>(f->parentWidget())){
         f->parentWidget()->show(); 
       }    

        f->show();
        return;
      }
    }
  }

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){

       if (f->dock) f->dock->show(); 
       if (f->parentWidget() && qobject_cast<QMdiSubWindow *>(f->parentWidget())){
         f->parentWidget()->show(); 
       }    

        f->show();
        return;
      }
    }
  }
}

void _forms::METHOD_FormHide(QString s)
{
  if (forms_mainwindow == 0) return;

  QList<QMdiSubWindow *> windows = forms_workspace->subWindowList();

  for (int i = 0; i < windows.size(); ++i) {
    _form *f;
    if ((f = qobject_cast<_form *>(windows.at(i)->widget()))){
      if (s == f->GETPROPERTY_Name()){

      if (f->dock) f->dock->hide(); 
       if (f->parentWidget() && qobject_cast<QMdiSubWindow *>(f->parentWidget())){
         f->parentWidget()->hide(); 
       }
        f->hide();
        return;
      }
    }
  }

  QWidgetList it = qApp->allWidgets(); // iterate over the children
  QWidget *o;
  for (int q = 0; q < it.size(); q++){
    o = it.at(q);
    _form *f;
    if ((f = qobject_cast<_form *>(o))){
      QString k = f->GETPROPERTY_Name();
      if (s == k){

      if (f->dock) f->dock->hide(); 
       if (f->parentWidget() && qobject_cast<QMdiSubWindow *>(f->parentWidget())){
         f->parentWidget()->hide(); 
       }

        f->hide();
        return;
      }
    }
  }
}


void _forms::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    forms_workspace->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void _forms::activated(QSystemTrayIcon::ActivationReason r)
{
  QString rr = "";
  if (r == QSystemTrayIcon::Unknown) rr = "Unknown";
  else if (r == QSystemTrayIcon::Context) rr = "Context";
  else if (r == QSystemTrayIcon::DoubleClick) rr = "DoubleClick";
  else if (r == QSystemTrayIcon::Trigger) rr = "Trigger";
  else if (r == QSystemTrayIcon::MiddleClick) rr = "MiddleClick";

  kb_application::EVENT_SystemTray_OnEvent(rr);
}

void _forms::messageClicked()
{
  kb_application::EVENT_SystemTray_OnEvent("PrintClicked");
}

void _forms::trayIcon_frameChanged(int)
{
  trayIcon->setIcon(trayIcon_movie->currentPixmap());
  //forms_mainwindow->setWindowIcon(movie->currentPixmap());
}

void _systemtray::PROPERTYSET_ContextMenu(QString k)
{
  kb_menubaritem *mbi = EXTERN_my_menubar->METHOD_MenuBarItem(k);
  if (mbi){
    sSystemTrayContextMenu = k;
    trayIcon->setContextMenu(mbi->my_qmenu);
  }
}

#endif