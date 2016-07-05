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

#include "../kbshared/_table.h"

#include "_qbe.h"
#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"

#include "../kbshared/_form.h"
#include "../kbshared/_report.h"
//#include "_objecteditor.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"
#include "_projectwindow.h"
#include "_parserwindow.h"


#include "_inputtip_parser.h"
#include "_qbe_tables.h"

extern QStringList trl;

extern QString runPath(QString s);

extern _projectwindow *EXTERN_my_projectwindow;
extern const QIcon &kbasicIcon(QString s);

extern _propertywindow *EXTERN_my_propertywindow;

extern t_properties *apply_properties;

extern _form *EXTERN_my_form;
extern _report *EXTERN_my_report;

extern QSqlDatabase CurrentDatabase;

extern QList<_inputtip_info> ci_listAs;
extern QList<_inputtip_info> ci_listDot;

extern QMap<QString, _inputtip_parser> ci;
extern QList<_inputtip_info> ci_listEvents;
extern QList<_inputtip_info> ci_listDot;
extern QList<_inputtip_info> ci_listDotMethod;
extern QList<_inputtip_info> ci_listFindDefinition;


extern _qbe_tables *EXTERN_qbe_tables;

extern _parserwindow *EXTERN_my_parserwindow;

_sourcecodeeditor* _mainwindow::new_sourcecodeeditor()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _sourcecodeeditor* o = new _sourcecodeeditor();
  QSize SAVE = o->minimumSize(); // WORKAROUND to have the editor more centered
  o->setMinimumSize(500, 400);

  QMdiSubWindow *w = new QMdiSubWindow(); // do it this way cause of Qt bug
  w->setWidget(o);

  workspace->addSubWindow(w);

  o->setMinimumSize(SAVE);
  o->parentWidget()->resize(o->size());
  o->parentWidget()->setWindowIcon(o->windowIcon());
  o->showMaximized();
  //o->show();
  o->setFocus();
  workspace->setActiveSubWindow((QMdiSubWindow *) o->parentWidget());

  QApplication::restoreOverrideCursor();
  return o;
}

_table* _mainwindow::new_table(bool bNormal)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _table *o = new _table();

  QSize SAVE = o->minimumSize(); // WORKAROUND to have the editor more centered
  o->setMinimumSize(500, 400);

  QMdiSubWindow *w = new QMdiSubWindow(); // do it this way cause of Qt bug
  w->setWidget(o);
  workspace->addSubWindow(w);

  o->setMinimumSize(SAVE);

  o->parentWidget()->resize(o->size());
  o->parentWidget()->setWindowIcon(o->windowIcon());

#ifdef MAC
  o->showMaximized();
#else
  o->show();
#endif
  o->setFocus();
  workspace->setActiveSubWindow((QMdiSubWindow *) o->parentWidget());

  //o->setCurrentCell(0, 0);

  QApplication::restoreOverrideCursor();
  return o;
}

_qbe* _mainwindow::new_query(bool bNormal)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _qbe *o = new _qbe();

  QMdiSubWindow *w = new QMdiSubWindow(); // do it this way cause of Qt bug
  w->setWidget(o);
  workspace->addSubWindow(w);

  o->parentWidget()->resize(o->size());
  o->parentWidget()->setWindowIcon(o->windowIcon());

  o->showMaximized();
  o->setFocus();
  workspace->setActiveSubWindow((QMdiSubWindow *) o->parentWidget());

  QApplication::restoreOverrideCursor();
  return o;
}

_form* _mainwindow::new_form(bool bNormal)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));


  _form *o = new _form(this);

  QMdiSubWindow *w = new QMdiSubWindow();
  w->setWidget(o);

  workspace->addSubWindow (w, /*Qt::WA_DeleteOnClose | */Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  /*
  w->setAutoFillBackground(true);
  QPalette p = w->palette();
  QColor c = QColor(0, 0, 0, 155);
  p.setColor(QPalette::Window, c);  
  w->setPalette(p);
*/
 // o->setMinimumSize(SAVE);

  o->parentWidget()->installEventFilter(o); // needed for some form events

  o->parentWidget()->resize(o->size());
  o->parentWidget()->setWindowIcon(o->windowIcon());

  o->show();
  o->setFocus();
  workspace->setActiveSubWindow((QMdiSubWindow *) o->parentWidget());

  QApplication::restoreOverrideCursor();
  return o;
}

_report* _mainwindow::new_report(bool bNormal)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _report *o = new _report(this);

  QMdiSubWindow *w = new QMdiSubWindow(); // do it this way cause of Qt bug
  w->setWidget(o);
  workspace->addSubWindow(w, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  
  o->parentWidget()->installEventFilter(o); // needed for some form events

  o->parentWidget()->resize(o->size());
  o->parentWidget()->setWindowIcon(o->windowIcon());

  o->show();
  o->setFocus();
  workspace->setActiveSubWindow((QMdiSubWindow *) o->parentWidget());
  
  QApplication::restoreOverrideCursor();
  return o;
}

_menubar* _mainwindow::new_menubar()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _menubar* o = new _menubar(this);

  QMdiSubWindow *w = new QMdiSubWindow(); // do it this way cause of Qt bug
  w->setWidget(o);
  workspace->addSubWindow (w, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  
  o->parentWidget()->resize(o->size());
  o->parentWidget()->setWindowIcon(o->windowIcon());

  o->show();
  o->setFocus();
  workspace->setActiveSubWindow((QMdiSubWindow *) o->parentWidget());

  QApplication::restoreOverrideCursor();
  return o;


  return 0;
}

_toolbar* _mainwindow::new_toolbar()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  _toolbar* o = new _toolbar(this);

  QMdiSubWindow *w = new QMdiSubWindow(); // do it this way cause of Qt bug
  w->setWidget(o);
  workspace->addSubWindow(w, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  
  o->parentWidget()->resize(o->size());
  o->parentWidget()->setWindowIcon(o->windowIcon());

  o->show();
  o->setFocus();
  workspace->setActiveSubWindow((QMdiSubWindow *) o->parentWidget());

  QApplication::restoreOverrideCursor();
  return o;

  
}


void _mainwindow::loadFormClassSourceCode(QString s)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  loadFile(s, true);
  QApplication::restoreOverrideCursor();
}


void _mainwindow::loadFile(QString s, bool bClassForm)
{

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _sourcecodeeditor* o = new_sourcecodeeditor();
  bool b = isOtherFile(s);
  if (b) o->setSyntaxHighlighting(false);
  if (o->load(s, bClassForm)){

    QWidget *w = qobject_cast<QWidget *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
//#ifdef MAC
    o->showMaximized();
    QApplication::restoreOverrideCursor();
    if (!b) EXTERN_my_mainwindow->ci_parse(s, o->my_sourcecodeeditor_editor->document()->toPlainText());
  }
//#else
  //if (w && w->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
//#endif
  
  QApplication::restoreOverrideCursor();

}

void _mainwindow::loadFileFullscreen(QString s, bool bClassForm)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _sourcecodeeditor* o = new_sourcecodeeditor();
  if (o->load(s, bClassForm)){
    o->showMaximized();
  }
  QApplication::restoreOverrideCursor();
}


void _mainwindow::loadTable(QString s)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	_table* o = new_table();	
  o->load(s);
  QApplication::restoreOverrideCursor();  
}

void _mainwindow::loadData(QString s)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	_tableviewer* o = new _tableviewer(0, s);  
  QApplication::restoreOverrideCursor();  
}

void _mainwindow::loadQuery(QString s)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	_qbe* o = new_query();	
  o->load(s);
  QApplication::restoreOverrideCursor();  
}

void _mainwindow::loadForm(QString s)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	_form* o = new_form();
	
  o->load(s);
  o->SETPROPERTY_Name(getFilenameWithoutPathAndExtension(s)); // manually override, needed for newly created forms

  QApplication::restoreOverrideCursor();
  QString sAllText = "";
  EXTERN_my_mainwindow->ci_parse(s, _form::getFormClassSourceCode(s, sAllText, false)); 

  /*
  static bool bFirstTime = true;
  static bool bFirstTime2 = true;
  if (!bFirstTime && bFirstTime2 && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, MYAPP,
     tr(
    "To add new controls, just select one control in the toolbox and click on the empty form.\n"
    )
    );

   bFirstTime2 = false;
  }
  bFirstTime = false;
*/

}

void _mainwindow::loadReport(QString s)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	_report* o = new_report();
	

  o->load(s);
  o->SETPROPERTY_Name(getFilenameWithoutPathAndExtension(s)); // manually override, needed for newly created forms

  QString sAllText = "";
  EXTERN_my_mainwindow->ci_parse(s, _report::getFormClassSourceCode(s, sAllText, false));

 QApplication::restoreOverrideCursor();
    

}

void _mainwindow::loadMenuBar(QString s)
{

#ifdef MAC
  loadOther(s); // HIDE
#else
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  // *** close current menubar
  QList<QMdiSubWindow *> windows = workspace->subWindowList();
  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _menubar *o = qobject_cast<_menubar *>(w);
      if (o){
        QMessageBox::information(this, MYAPP,
          tr(
          "Closing current MenuBar. Only one menubar might be visible at one time." ));
          
          o->close();
       }
    

        
      }    
  }  

	_menubar* o = new_menubar();
	o->load(s);
  QApplication::restoreOverrideCursor();

  static bool bFirstTime = true;
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, MYAPP,
     tr(
    "To add a new menu, just select 'Menu' in the toolbox and click on the empty MenuBar.\n"
    "\nTo add a new menubar item, just select 'MenuBarItem' in the toolbox and click on the created menu in the menubar.\n"
    "\nTo move a menu or menubar item, just select 'Select' in the toolbox and click on the menu or menubar item. "
    "The menu or  menubar item gets selected. After that click on the menu or menubar item, where to move it.\n"
    )
    );

   bFirstTime = false;
  }


#endif
}

void _mainwindow::loadToolBar(QString s)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  // *** close current menubar
  QList<QMdiSubWindow *> windows = workspace->subWindowList();
  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _toolbar *o = qobject_cast<_toolbar *>(w);
      if (o){
        QMessageBox::information(this, MYAPP,
          tr(
          "Closing current MenuBar. Only one menubar might be visible at one time." ));
        o->close();
          
        }
        
      }
    
  }  

	_toolbar* o = new_toolbar();
	o->load(s);
  QApplication::restoreOverrideCursor();


  static bool bFirstTime = true;
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, MYAPP,
     tr(
    "To add a new toolbar item, just select 'ToolBarItem' in the toolbox and click on the created toolbar.\n"
    "\nTo move a toolbar item, just select 'Select' in the toolbox and click on the toolbar item. "
    "The toolbar item gets selected. After that click on the toolbar item, where to move it.\n"
    )
    );

   bFirstTime = false;
  }

}

void _mainwindow::loadOther(QString s)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	_sourcecodeeditor *o = new_sourcecodeeditor();
  
  if (o->load(s, false)){
    QWidget *w = qobject_cast<QWidget *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (w && w->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
  }
  QApplication::restoreOverrideCursor();


}
	
void _mainwindow::insertClass(QString s, QString sText)
{
  if (!s.endsWith(".kbasic_class", Qt::CaseInsensitive)) s += ".kbasic_class";
  insertFile(_class2, s, "kbasic_class", "ide/PROJECT_NEW_CLASS.png", sText);
}

void _mainwindow::insertModule(QString s, QString sText)
{
  if (!s.endsWith(".kbasic_module", Qt::CaseInsensitive)) s += ".kbasic_module";
  insertFile(_module2, s, "kbasic_module", "ide/PROJECT_NEW_MODULE.png", sText);
}
	
void _mainwindow::insertTable(QString s, QString sText)
{
  if (!s.endsWith(".kbasic_table", Qt::CaseInsensitive)) s += ".kbasic_table";
  insertFile(_table2, s, "kbasic_table", "ide/PROJECT_NEW_TABLE.png", sText);
}

void _mainwindow::insertQuery(QString s, QString sText)
{
  if (!s.endsWith(".kbasic_query", Qt::CaseInsensitive)) s += ".kbasic_query";
  insertFile(_query2, s, "kbasic_query", "ide/PROJECT_NEW_QUERY.png", sText);
}

void _mainwindow::insertForm(QString s, QString sText)
{
  if (!s.endsWith(".kbasic_form", Qt::CaseInsensitive)) s += ".kbasic_form";
  insertFile(_form2, s, "kbasic_form", "ide/PROJECT_NEW_FORM.png", sText);
}

void _mainwindow::insertReport(QString s, QString sText)
{
  if (!s.endsWith(".kbasic_report", Qt::CaseInsensitive)) s += ".kbasic_report";
  insertFile(_report2, s, "kbasic_report", "ide/PROJECT_NEW_REPORT.png", sText);
}

void _mainwindow::insertMenuBar(QString s, QString sText)
{
  if (!s.endsWith(".kbasic_menubar", Qt::CaseInsensitive)) s += ".kbasic_menubar";
  insertFile(_menubar2, s, "kbasic_menubar", "ide/PROJECT_NEW_MENUBAR.png", sText);
}

void _mainwindow::insertToolBar(QString s, QString sText)
{
  if (!s.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)) s += ".kbasic_toolbar";
  insertFile(_toolbar2, s, "kbasic_toolbar", "ide/PROJECT_NEW_TOOLBAR.png", sText);
}


void _mainwindow::insertImage(QString s, QString sText)
{
  insertFile(_image2, s, "", "", sText);
}

void _mainwindow::insertOther(QString s, QString sText)
{
  insertFile(_other2, s, "", "", sText);
}

bool _mainwindow::isTableFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _table *o = qobject_cast<_table *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  return false;    
}

bool _mainwindow::isDataFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    
    QString kk = getFilenameWithoutPathAndExtension(s);
    kk += tr(" : Table Data");

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _tableviewer *o = qobject_cast<_tableviewer *>(w);
      if (o){
        QString k = o->windowTitle();
        if (kk == k){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  return false;    
}

bool _mainwindow::isQueryFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _qbe *o = qobject_cast<_qbe *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k){
          if (bShow){
            
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  return false;    
}

bool _mainwindow::isFormFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _form *o = qobject_cast<_form *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  return false;    
}

bool _mainwindow::isReportFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _report *o = qobject_cast<_report *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  return false;    
}

/*
//_form *_mainwindow::getFormObject(QString s)
{
  
#ifdef LINUX
  processGUI(100);

  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();
      if (w->isA("_form") || w->isA("_objecteditor")){
        _form *se = (_form *) w;

        QString k = se->getFilenamePath();
        if (s == k){
          return se;
        }
      }
    }

  }
  
  return 0;
    
}*/

bool _mainwindow::isMenuBarFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _menubar *o = qobject_cast<_menubar *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  return false;    

  return false;
    
}

bool _mainwindow::isToolBarFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _toolbar *o = qobject_cast<_toolbar *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  


  return false;
    
}


bool _mainwindow::isClassFileOpened(QString & fn, bool bShow)
{
  QString s = EXTERN_my_mainwindow->getProjectPreference("Translation");
  trl = s.split(";");

  {
    QString sExt = EXTERN_my_mainwindow->getFilenameExtension(fn);
    QString q = fn.left(fn.length() - sExt.length() - 1);

    if (q.count(".") > 1){

      QString sLanguage = EXTERN_my_mainwindow->getFilenameExtension(q);
      if (trl.contains(sLanguage)){        
        fn = q.left(q.length() - sLanguage.length() - 1) + "." + sExt;
      }
    }
  }
  
  return isFileOpened2(fn, bShow);
}

bool _mainwindow::isModuleFileOpened(QString s, bool bShow)
{
  return isFileOpened2(s, bShow);
}
	
bool _mainwindow::isFormClassFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k && w->windowTitle().endsWith(tr("(Source Code)"), Qt::CaseInsensitive)){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  
  return false;
    
}

bool _mainwindow::isReportClassFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k && w->windowTitle().endsWith(tr("(Source Code)"), Qt::CaseInsensitive)){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  
  return false;
    
}

bool _mainwindow::isMenuBarClassFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k && w->windowTitle().endsWith(tr("(Source Code)"), Qt::CaseInsensitive)){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  
  return false;
}

bool _mainwindow::isToolBarClassFileOpened(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k && w->windowTitle().endsWith(tr("(Source Code)"), Qt::CaseInsensitive)){
          if (bShow){
	          if (o->windowState() & Qt::WindowMaximized) o->showMaximized(); else o->showNormal();
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  
  
  return false;
}

bool bWORKAROUNDShow = true;

bool _mainwindow::isFileOpened2(QString s, bool bShow)
{
  QList<QMdiSubWindow *> windows = workspace->subWindowList();

  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
      if (o){
        QString k = o->getFilename();
        if (s == k/* && !o->isFormClassSourceCode()*/){ // WORKAROUND isClassFormSourceCode() um verwechselung zu vermeiden mit (source code)
          if (/*bWORKAROUNDShow && */bShow){
	          o->show();  
            o->activateWindow();
            o->setFocus();
          }
          return true;
        }
      }
    }
  }  

  
  return false;
    
}

_sourcecodeeditor *_mainwindow::getMatchingSourceCodeEditor(_form *f)
{  
  if (isFormClassFileOpened(f->getFilename(), false)){
  } else {
    f->openFormClassSourceCode();
    
  }
  return qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
}

_sourcecodeeditor *_mainwindow::getMatchingSourceCodeEditor(_report *f)
{  
  if (isReportClassFileOpened(f->getFilename(), false)){
  } else {
    f->openFormClassSourceCode();
    
  }
  return qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
}

_sourcecodeeditor *_mainwindow::getMatchingSourceCodeEditor(_menubar *f)
{  
  if (isMenuBarClassFileOpened(f->getFilename(), false)){
  } else {
    f->openMenuBarClassSourceCode();
    
  }
  return qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
}

_sourcecodeeditor *_mainwindow::getMatchingSourceCodeEditor(_toolbar *f)
{  
  if (isToolBarClassFileOpened(f->getFilename(), false)){
  } else {
    f->openToolBarClassSourceCode();
    
  }
  return qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
}
 

void _mainwindow::closeProject()
{  
  if (!bProject) return;

  EXTERN_my_propertywindow->setEnabled(false);  

  if (isRunning()){
    event_RUN_STOP();
  }

  if (CurrentDatabase.open()) CurrentDatabase.close();    

  if (fsWatcher) fsWatcher->removePath(getProjectPath());


  EXTERN_qbe_tables->refresh();
  
  workspace->closeAllSubWindows();
  VIEW_QBE->setEnabled(bProject);
  VIEW_RELATION->setEnabled(bProject);
  FILE_CLOSE_PROJECT->setEnabled(bProject);
  PROJECT_ADD_EXISTING->setEnabled(bProject);
  PROJECT_DATABASE->setEnabled(bProject);
  PROJECT_SET_AS_DEFAULT->setEnabled(bProject);
  PROJECT_PROPERTIES_OF_PROJECT->setEnabled(bProject);

  sProjectFilename = "";

  EXTERN_my_projectwindow->showProjectName("");
  EXTERN_my_projectwindow->closeProject();
  EXTERN_my_projectwindow->refresh();
  
  bProject = false;

  projectPreferences.clear();
  ci_listAs.clear();
  ci_listDot.clear();
  ci.clear();

  ci_listEvents.clear();
  ci_listDot.clear();
  ci_listDotMethod.clear();
  ci_listFindDefinition.clear();
  EXTERN_my_propertywindow->setEnabled(false);

  //QApplication::restoreOverrideCursor();

  EXTERN_my_form = 0;
  EXTERN_my_report = 0;
  EXTERN_my_menubar = 0;
  EXTERN_my_toolbar = 0;

  TRANSLATION->clear();

  EXTERN_my_mainwindow->setWindowTitle(tr(MYAPP));
  EXTERN_my_parserwindow->refreshProject();

}

bool _mainwindow::isFileInProject(QString s)
{
  return existsFile(s);
}

void _mainwindow::TRANSLATION_currentIndexChanged( const QString & text ) 
{
  if (bProjectLoading) return;

  sCurrentLanguage = text;
  projectLanguageChanged();
}

void _mainwindow::projectLanguageChanged()
{    
  closeAllWindows();
  event_PROJECT_REFRESH();
}

void _mainwindow::loadProject(QString s)
{  
  s = s.replace("\\", "/");
  if (bProject) closeProject();

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  bProjectLoading = true;
#ifdef IDE
#elif defined (VM)
  tree = new QTreeWidget(0);
  tree->setHidden(true);
#endif
  sProjectFilename = s;
  loadProjectPreferences();

    bool bSQLite = false;
    QString q = "";
    bool bMySQL = false;

  QString ss = getProjectPreference("dbdriver");
  if (!ss.isEmpty()){
    CurrentDatabase = QSqlDatabase::addDatabase(ss);
    CurrentDatabase.setHostName(getProjectPreference("dbhost"));

    
    if (CurrentDatabase.driverName().contains("sqlite", Qt::CaseInsensitive)){
      bSQLite = true;
    } else if (CurrentDatabase.driverName().contains("mysql", Qt::CaseInsensitive)){
      bMySQL = true;
    }

    
    if (bSQLite){
      q = getProjectPreference("dbname");
      if (q.startsWith("./")){
        q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + q.mid(1);
      } else if (q.startsWith("../")){
        q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + q.mid(2);
      }
//      q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + "/sqlite/" + getProjectPreference("dbname");
      CurrentDatabase.setDatabaseName(q);
    } else {
      CurrentDatabase.setDatabaseName(getProjectPreference("dbname"));
    }

    
    CurrentDatabase.setUserName(getProjectPreference("dbuser"));
    CurrentDatabase.setPassword(getProjectPreference("dbuserpassword"));
    
    if (CurrentDatabase.open()){     
      EXTERN_qbe_tables->refresh();
    } else {
      QSqlError e = CurrentDatabase.lastError();
      QApplication::restoreOverrideCursor();
      QMessageBox::information(this, "Error While Connecting To Database",  e.text());  
      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    }
  }

  if (!(bProject = EXTERN_my_projectwindow->load())){
    sProjectFilename = "";
  }

  QString sSQL = "";  
  if (EXTERN_my_mainwindow->getProjectPreference("dbdriver").contains("sqlite", Qt::CaseInsensitive)){
    sSQL = EXTERN_my_mainwindow->getProjectPreference("dbdriver").isEmpty() ? "" : EXTERN_my_mainwindow->getProjectPreference("dbname");
  } else {
    sSQL = EXTERN_my_mainwindow->getProjectPreference("dbdriver").isEmpty() ? "" : EXTERN_my_mainwindow->getProjectPreference("dbhost") + "//:" + EXTERN_my_mainwindow->getProjectPreference("dbuser") + "@" + EXTERN_my_mainwindow->getProjectPreference("dbname");
  }
  EXTERN_my_projectwindow->showProjectName(" " + this->getFilenameWithoutPathAndExtension(sProjectFilename) + "      " + (sSQL.length() > 4 ? sSQL :+ " "));

  FILE_CLOSE_PROJECT->setEnabled(bProject);
  PROJECT_ADD_EXISTING->setEnabled(bProject);
  PROJECT_DATABASE->setEnabled(bProject);
  PROJECT_SET_AS_DEFAULT->setEnabled(bProject);
  PROJECT_PROPERTIES_OF_PROJECT->setEnabled(bProject);

  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->my_sourcecodeeditor_editor->updateActions();
  } else {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->updateActions();  
    } else {
      subWindowActivated(0);
    }
  }

  // make sure that at least property and project window is visible
  EXTERN_my_propertywindow->setShown(true);
  EXTERN_my_projectwindow->setShown(true);

  EXTERN_my_parserwindow->refreshProject();

  ss = getProjectPreference("projectmainformname");
  if (!ss.simplified().isEmpty()/* && !ss.contains("Function Main()", Qt::CaseInsensitive)*/){
    if (!ss.contains("Function Main()", Qt::CaseInsensitive) && QFile::exists(getProjectPath()+ "/" + ss + ".kbasic_form")) loadForm(getProjectPath()+ "/" + ss + ".kbasic_form");
    else if (QFile::exists(getProjectPath() + "/myForm.kbasic_form")) loadForm(getProjectPath()+ "/myForm.kbasic_form");
  }

  if (fsWatcher == 0){
    fsWatcher = new QFileSystemWatcher(this); 
    connect(fsWatcher, SIGNAL(fileChanged(const QString &)), this, SLOT(fileChanged(const QString &)));
    connect(fsWatcher, SIGNAL(directoryChanged(const QString &)), this, SLOT(directoryChanged(const QString &)));
    
  }
  fsWatcher->addPath(getProjectPath());
  //if (bSQLite && fsWatcher) fsWatcher->removePath(q);

  TRANSLATION->clear();
  TRANSLATION->addItem("");

  {
    QString s = EXTERN_my_mainwindow->getProjectPreference("Translation");
    trl = s.split(";");
  }

  if (trl.size()){
    foreach(QString m, trl){    
      if (!m.isEmpty()){
        TRANSLATION->addItem(m);
      }
    }
  }
  if (TRANSLATION->count() == 1){
    TRANSLATION->addItem("German");
  }

  bProjectLoading = false;
  QApplication::restoreOverrideCursor();

}

bool bLockDirectoryChanged = false;
bool bLockDirectoryChanged2 = false;
  
void _mainwindow::directoryChanged(const QString &s)
{
  if (bLockDirectoryChanged) return;
  if (bLockDirectoryChanged2){
    bLockDirectoryChanged2 = false;
    return;
  }

  EXTERN_my_projectwindow->refresh();  
}

void _mainwindow::fileChanged(const QString &s)
{
  QString q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + "/" + getProjectPreference("dbname");

  if (q == s){
    bLockDirectoryChanged2 = true;
  }
}

bool _mainwindow::insertFile(QTreeWidgetItem *p, QString file, QString ext, QString icon, QString sText, QString rename)
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  QString file2 = file;
  int i = 1;
  bool b = false;
s:
  b = false;
  QString c = rename.length() ? rename : getProjectPath()+ "/" + getFilenameWithoutPath(file);  

  if (c.endsWith(".kbasic_class", Qt::CaseInsensitive)){
    if (existsClassFile(c)) b = true;
  } else if (c.endsWith(".kbasic_module", Qt::CaseInsensitive)){
    if (existsModuleFile(c)) b = true;
  } else if (c.endsWith(".kbasic", Qt::CaseInsensitive)){
    if (existsModuleFile(c)) b = true;

  } else if (c.endsWith(".kbasic_table", Qt::CaseInsensitive)){
    if (existsTableFile(c)) b = true;
  } else if (c.endsWith(".kbasic_query", Qt::CaseInsensitive)){
    if (existsQueryFile(c)) b = true;
  } else if (c.endsWith(".kbasic_form", Qt::CaseInsensitive)){
    if (existsFormFile(c)) b = true;
  } else if (c.endsWith(".kbasic_report", Qt::CaseInsensitive)){
    if (existsReportFile(c)) b = true;
  } else if (c.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){
    if (existsMenuBarFile(c)) b = true;
  } else if (c.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){
    if (existsToolBarFile(c)) b = true;

  } else {
    if (existsOtherFile(c)) b = true;
  }      

  if (!b){
    if (file2.lastIndexOf('\\') == -1 && file2.lastIndexOf('/') == -1) createFile(c, sText);
    else copyFile(file2, c);

    bool b = EXTERN_my_projectwindow->bInit;
    EXTERN_my_projectwindow->bInit = true;

    QTreeWidgetItem *element = new QTreeWidgetItem(p, QStringList(""));
    if (!icon.isEmpty()) element->setIcon(0, kbasicIcon(kbasicPath(icon)));          

    element->setText(0, getFilenameWithoutPathAndExtension(file));
    element->setText(1, c);
    element->setText(2, ext);
    element->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    EXTERN_my_projectwindow->bInit = b;

    QApplication::restoreOverrideCursor();
    return true;
  }

  QString s = "";
  s.sprintf("%d", i);

  file = getProjectPath() + "/" + getFilenameWithoutPathAndExtension(file) + s + "." + ext;
  goto s;
}


void _mainwindow::loadProjectPreferences()
{  
  QString m = sProjectFilename;
  QString s = "";

  QFile f(m);
  if (!f.open(QFile::ReadOnly)){
     QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(m));
    return;
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s = s.replace("\r", "");
    f.close();
  }

  QStringList l = s.split("\n");

  for ( QStringList::Iterator it = l.begin(); it != l.end(); ++it ) {
    QString k = *it;

    k = k.trimmed();

    QString sKey = "";
    QString sValue = "";


    sKey = k.left(k.indexOf("="));
    sKey = sKey.trimmed();
    sValue = k.mid(k.indexOf("=") + 1);
    sValue = sValue.trimmed();

    projectPreferences[sKey.toUpper()] = sValue;

  }
    
}

void _mainwindow::saveProjectPreferences()
{  
  
  QString m =  sProjectFilename;
  QString s = "";

  QMap<QString, QString>::Iterator it;
  for ( it = projectPreferences.begin(); it != projectPreferences.end(); ++it ) {
    QString sKey = it.key();
    if (sKey.isEmpty()) continue;
    QString sValue = *it;
    if (sValue.isEmpty()) continue;
    
    s += sKey + " = " + sValue + "\n";
  }
  
  QFile f(m);
  if (!f.open(QFile::WriteOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(m));
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << s;
    f.close();
  }  

}
