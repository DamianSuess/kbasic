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
#include "_compile.h"

#include "_qbe.h"
#include "_relation.h"

#include "_resources.h"

#include "interpreter.h"
#include "_translation.h"


//#include "_query.h"
#include "../kbshared/_table.h"
#include "../kbshared/_form.h"
#include "../kbshared/_report.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"

#include "../kbshared/_property.h"
#include "../kbshared/_log.h"

#include "_help.h"

#include "_insert.h"
#include "_preferences.h"
#include "_compileproject.h"
#include "_projectproperties.h"
#include "_dbcondialog.h"
#include "_importproject.h"
#include "_newproject.h"
#include "_findfile.h"
#include "_replacefile.h"
#include "_infoconsole.h"
#include "_quickcode.h"

#include "_projectwindow.h"
#include "_parserwindow.h"

#ifdef MAC
#include <Carbon/Carbon.h>
#endif

extern _parserwindow *EXTERN_my_parserwindow;

extern QDockWidget *EXTERN_Quickcode;

extern _parserwindow *EXTERN_my_parserwindow;

extern bool checkObjectName(QString s);

extern _projectwindow *EXTERN_my_projectwindow;
extern const QIcon &kbasicIcon(QString s);

extern QString sFindText;

extern QDockWidget *EXTERN_Global;
extern QDockWidget *EXTERN_Stack;
extern QDockWidget *EXTERN_Local;
extern QDockWidget *EXTERN_Me;

extern QString idePath(QString s);
extern QString cachePath(QString s);
extern QString kbcPath(QString s);
extern QString runPath(QString s);



extern QDockWidget *EXTERN_ParserWindow;
extern QDockWidget *EXTERN_HelpWindow;
extern QDockWidget *EXTERN_PropertyWindow;
extern QDockWidget *EXTERN_ProjectWindow;
extern QDockWidget *EXTERN_ToolboxForm;
extern QDockWidget *EXTERN_ToolboxMenuBar;
extern QDockWidget *EXTERN_ToolboxToolBar;
extern QDockWidget *EXTERN_ToolboxSql;
extern QDockWidget *EXTERN_ToolboxReport;
extern QDockWidget *EXTERN_Helpwindow_shortcut;
extern QDockWidget *EXTERN_DatabaseTables;

QString EXTERN_sError;











void _mainwindow::event_VIEW_TABBAR()
{
  if (workspace->viewMode() == QMdiArea::SubWindowView){
    workspace->setViewMode(QMdiArea::TabbedView);

    EXTERN_my_mainwindow->setPreference("TabBar", "No");
    _preferences c(this, true);  

  } else {
    workspace->setViewMode(QMdiArea::SubWindowView);

    EXTERN_my_mainwindow->setPreference("TabBar", "Yes");
    _preferences c(this, true);  
  }
}

void _mainwindow::event_VIEW_PropertyWindow()
{
  EXTERN_PropertyWindow->setShown(true);
}

void _mainwindow::event_VIEW_ProjectWindow()
{
  EXTERN_ProjectWindow->setShown(true);
}

void _mainwindow::event_VIEW_ParserWindow()
{
  EXTERN_ParserWindow->setShown(true);
}

void _mainwindow::event_VIEW_HelpWindow()
{
  EXTERN_HelpWindow->setShown(true);
}

void _mainwindow::event_VIEW_ToolboxForm()
{
  EXTERN_ToolboxForm->setShown(true);
}

void _mainwindow::event_VIEW_ToolboxMenuBar()
{
  EXTERN_ToolboxMenuBar->setShown(true);
}

void _mainwindow::event_VIEW_ToolboxToolBar()
{
  EXTERN_ToolboxToolBar->setShown(true);
}

void _mainwindow::event_VIEW_ToolboxSql()
{
  //EXTERN_ToolboxSql->setShown(true);
}

void _mainwindow::event_VIEW_ToolboxReport()
{
  EXTERN_ToolboxReport->setShown(true);
}

void _mainwindow::event_VIEW_Helpwindow_shortcut()
{
  EXTERN_Helpwindow_shortcut->setShown(true);
}


void _mainwindow::event_FILE_SET_AS_DEFAULT()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QString k = o->getFilename();
    if (k.endsWith(".kbasic_form", Qt::CaseInsensitive) || 
      k.endsWith(".kbasic_menubar", Qt::CaseInsensitive) || 
      k.endsWith(".kbasic_toolbar", Qt::CaseInsensitive) || 
      k.endsWith(".kbasic_report", Qt::CaseInsensitive))
    {
     QMessageBox::information(this, MYAPP,
       tr("Only *.kbasic or *.kbasic_class files may be set as default file on start up.\n"));
      return;
    }      

    setPreference("DefaultFile", k);

    _preferences c(this, true);  
  }
}

void _mainwindow::event_PROJECT_SET_AS_DEFAULT()
{
  setPreference("DefaultProject", sProjectFilename);
  _preferences c(this, true);  
}

void _mainwindow::event_PROJECT_REFRESH()
{
  if (bProject){
    EXTERN_my_projectwindow->refresh();
  }
}

void _mainwindow::event_PROJECT_ADD_EXISTING()
{

  QString s = QFileDialog::getOpenFileName(this, tr("Add Existing File"));
  if (!s.isEmpty()){

    if (isProjectFile(s)){ 
     QMessageBox::information(this, MYAPP,
       tr(
    "Sorry. You cannot add a project file to an active project.\n"
    "You have to add manually each wanted file of it instead." ));
      return;
    }
         if (isClassFile(s)) insertClass(s);
    else if (isModuleFile(s)) insertModule(s);
    else if (isFormFile(s)) insertForm(s);
    else if (isMenuBarFile(s)) insertMenuBar(s);
    else if (isToolBarFile(s)) insertToolBar(s);
    else if (isImageFile(s)) insertImage(s);
    else if (isOtherFile(s)) insertOther(s);

    EXTERN_my_projectwindow->refresh();
  }
}

void _mainwindow::event_VIEW_KONSOLE()
{
  foreach (QWidget *w, QApplication::allWidgets()){
    if (w->objectName() == "Console" && w->isVisible()){
      QPixmap m2;
      QBrush b;
      if (m2.load(idePath("screen.png"))){
        b = QBrush(m2);
        w->setFixedSize(m2.size());
      } else {
        b = QBrush(Qt::black);
        w->setFixedSize(790, 570);
      }
      QPalette p = w->palette();
      p.setBrush(QPalette::Window, b);  
      w->setPalette(p);
      w->showNormal();
      w->activateWindow();
      w->setFocus();
      w->show();
      return;
    }
  }

  static bool bFirstTime = true;
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, MYAPP,
     tr(
    "The 'Screen' shows you information made by PRINT or other output operation.\n"
    "Basically, it is useful for input and output commands.\n"
    "It is like the old BASIC used to have console applications.\n"
    "\n"
    "Just try a PRINT \"Hello World!\" to see what is happening...\n"
    )
    );

   bFirstTime = false;
  }

  
#ifdef MAC
  QDialog *w = new QDialog(this); // HIDE
//  w->setWindowFlags(windowFlags() | Qt::Tool); // HIDE
#else
  QWidget *w = new QWidget(0);
  w->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
#endif  
  w->setObjectName("Console");
  w->setWindowTitle("Screen");
  w->setWindowIconText("Screen");
  w->setWindowIcon(kbasicIcon(kbasicPath("ide/VIEW_KONSOLE.png")));
  w->setAttribute(Qt::WA_DeleteOnClose);
  w->setAutoFillBackground(true);
  QPixmap m2;
  QBrush b;
  if (m2.load(idePath("screen.png"))){
    b = QBrush(m2);
    w->setFixedSize(m2.size());
  } else {
    b = QBrush(Qt::black);
    w->setFixedSize(790, 570);
  }
  QPalette p = w->palette();
  p.setBrush(QPalette::Window, b);  
  w->setPalette(p);
  QRect r = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
  w->move((r.width() / 2) - (w->width() / 2), (r.height() / 2) - (w->height() / 2));


  w->show(); 

/*
 OpenDialog()/SaveDialog()/PrintDialog()

 startPrinting()
 bool Printing()
*/

}

void _mainwindow::event_VIEW_LOG()
{
  foreach (QWidget *w, QApplication::allWidgets()){
    if (w->objectName() == "Log" && w->isVisible()){

      QTextEdit *te = (QTextEdit *) w;

      QString s = "";
      if (QFile::exists(idePath("log.html"))) loadStringFromFile(idePath("log.html"), s);
      te->setHtml(s);

      w->showNormal();
      w->activateWindow();
      w->setFocus();
      return;
    }
  }

  static bool bFirstTime = true;
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, MYAPP,
     tr(
    "The 'Log' shows you information made by LOG.\n"
    "Basically, it is useful for output commands.\n"
    "It supports Unicode output.\n"
    "\n"
    "Just try a LOG \"Hello World!\" to see what is happening...\n"
    )
    );

   bFirstTime = false;
  }

  
  QTextEdit *w = new QTextEdit(0);
#ifdef MAC
 // w->setWindowFlags(Qt::CustomizeWindowHint | Qt::Sheet);
#endif  

  w->setObjectName("Log");
  w->setWindowTitle("Log");
  w->setWindowIconText("Log");
  w->setWindowIcon(kbasicIcon(kbasicPath("ide/VIEW_LOG.png")));
  w->setAttribute(Qt::WA_DeleteOnClose);
  w->setReadOnly(true);

  QString s = "";
  if (QFile::exists(idePath("log.html"))) loadStringFromFile(idePath("log.html"), s);
  w->setHtml(s);

  w->resize(640, 480);

  QRect r = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
  w->move((r.width() / 2) - (w->width() / 2), (r.height() / 2) - (w->height() / 2));


  w->show(); 

}

void _mainwindow::event_VIEW_SOURCE_CODE()
{
  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      if (!isFormClassFileOpened(o->getFilename(), true)){
        o->openFormClassSourceCode();
      }
      return;
    }
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      if (!isReportClassFileOpened(o->getFilename(), true)){
        o->openFormClassSourceCode();
      }
      return;
    }
  }
  {
    _menubar *o = qobject_cast<_menubar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      if (!isMenuBarClassFileOpened(o->getFilename(), true)){
        o->openMenuBarClassSourceCode();
      }
      return;
    }
  }
  {
    _toolbar *o = qobject_cast<_toolbar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      if (!isToolBarClassFileOpened(o->getFilename(), true)){
        o->openToolBarClassSourceCode();
      }
      return;
    }
  }
  {
    _table *o = qobject_cast<_table *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->showData();
    }
  }
}

void _mainwindow::event_VIEW_DESIGN()
{
  {
    _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      QString s = o->getFilename();
      if (s.endsWith(".kbasic_form", Qt::CaseInsensitive)){      
        if (!isFormFileOpened(o->getFilename(), true)){
          openForm(o->getFilename());
        }      
        return;
      }
    }
  }
  {
    _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      QString s = o->getFilename();
      if (s.endsWith(".kbasic_report", Qt::CaseInsensitive)){      
        if (!isReportFileOpened(o->getFilename(), true)){
          openReport(o->getFilename());
        }      
        return;
      }
    }
  }
  {
    _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      QString s = o->getFilename();
      if (s.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){      
        if (!isMenuBarFileOpened(o->getFilename(), true)){
          openMenuBar(o->getFilename());
        }      
        return;
      }
    }
  }
  {
    _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      QString s = o->getFilename();
      if (s.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){      
        if (!isToolBarFileOpened(o->getFilename(), true)){
          openToolBar(o->getFilename());
        }      
        return;
      }
    }
  }

  {
    _tableviewer *o = qobject_cast<_tableviewer *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      QString s = o->windowTitle();
      s = s.left(s.indexOf(tr(" : Table Data"), Qt::CaseInsensitive));

      if (!isTableFileOpened(o->objectName(), true)){
        openTable(o->objectName());
      }      
      return;
      
    }
  }
}


void _mainwindow::event_VIEW_REPORTPREVIEW()
{
  {
    _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      QString s = o->getFilename();
      if (s.endsWith(".kbasic_report", Qt::CaseInsensitive)){      
        if (!isReportFileOpened(o->getFilename(), true)){
          openReport(o->getFilename());
        }      

      }
    }
  }
  {    
    _report *oo = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (oo){
      oo->previewReport();
      return;
    }
  }
 
}

void _mainwindow::event_FILE_EXIT()
{
 
  EXTERN_my_mainwindow->close();
/*
  _preferences c(this, true);  
  qApp->quit();  
  */
}

void _mainwindow::event_FILE_CLOSE()
{
  workspace->closeActiveSubWindow();
  EXTERN_my_parserwindow->refreshProject();
  
}

void _mainwindow::event_FILE_SAVE_HTML()
{  
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    static bool bFirstTime = true;

    if (bFirstTime && isPreferenceSet("IntroductionHelp")){
      QMessageBox::information(this, tr("Save As HTML..."),
      tr("The Internet is so importanted today, that KBasic has got an interesting feature:\n\n"
      "It is possible to save KBasic source codes files as HTML files with syntax highlighting, "
      "so that you can easily deploy and show your KBasic source codes on your website...\n"
      ));

      bFirstTime = false;
    }

    o->save();
    o->saveAsHTML();
    EXTERN_my_parserwindow->refreshProject();
  }
}


void _mainwindow::event_FILE_SAVE()
{  

  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  QWidget *o = 0;
 // QString s = "";

  if ((o = qobject_cast<_sourcecodeeditor *>(w))){
    ((_sourcecodeeditor *) o)->save();
  } else if ((o = qobject_cast<_form *>(w))){
    ((_form *) o)->save();
  } else if ((o = qobject_cast<_report *>(w))){   
    ((_report *) o)->save();
  } else if ((o = qobject_cast<_menubar *>(w))){
    ((_menubar *) o)->save();
  } else if ((o = qobject_cast<_toolbar *>(w))){
    ((_toolbar *) o)->save();
  } else if ((qobject_cast<_table *>(w))){
    ((_table *) w)->save(true);

    EXTERN_my_projectwindow->refresh();

  } else if ((qobject_cast<_qbe *>(w))){
    ((_qbe *) w)->save();
  }

  EXTERN_my_parserwindow->refreshProject();
}

void _mainwindow::event_FILE_SAVE_AS()
{

  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  QWidget *o = 0;

  if ((o = qobject_cast<_sourcecodeeditor *>(w))){
    ((_sourcecodeeditor *) o)->saveAs();
  } else if ((o = qobject_cast<_form *>(w))){
   
    ((_form *) o)->saveAs();
  } else if ((o = qobject_cast<_report *>(w))){
   
    ((_report *) o)->saveAs();
  } else if ((o = qobject_cast<_menubar *>(w))){
   
  ((_menubar *) o)->saveAs();
  } else if ((o = qobject_cast<_toolbar *>(w))){
   
 ((_toolbar *) o)->saveAs();
  } else if ((o = qobject_cast<_table *>(w))){
   
 ((_table *) o)->saveAs();
  } else if ((o = qobject_cast<_qbe *>(w))){
   
 ((_qbe *) o)->saveAs();
  }

  EXTERN_my_parserwindow->refreshProject();
  
}

void _mainwindow::event_FILE_SAVE_ALL(bool bAll)
{
  QList<QMdiSubWindow *>windows = workspace->subWindowList();
  for (int i = 0; i < windows.size(); i++){

    QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();    
    QWidget *o = 0;

    if ((o = qobject_cast<_sourcecodeeditor *>(w))){
      QString s = ((_sourcecodeeditor *) o)->getFilename();

      if (bAll == false){ // only projectfiles
        if (!isFileInProject(s)){
          continue;
        }
      }

      if (bAll || ((_sourcecodeeditor *) o)->isModified()) ((_sourcecodeeditor *) o)->save();
    } else if ((o = qobject_cast<_form *>(w))){
    
      ((_form *) o)->save();
    } else if ((o = qobject_cast<_report *>(w))){
    
      ((_report *) o)->save();
    } else if ((o = qobject_cast<_menubar *>(w))){
      ((_menubar *) o)->save();
    } else if ((o = qobject_cast<_toolbar *>(w))){
      ((_toolbar *) o)->save();
    } else if ((o = qobject_cast<_table *>(w))){
      ((_table *) o)->save();
    } else if ((o = qobject_cast<_qbe *>(w))){
      ((_qbe *) o)->save();
    }
    EXTERN_my_parserwindow->refreshProject();

  }

}



void _mainwindow::event_FILE_NEW_DIALOG()
{    
  static bool bFirstTime = true;

  if (!bProject){
    QMessageBox::information( this, tr("New Dialog"),
      tr(
           "In order to create a dialog you have to create a project first.\n"       
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
      goto goo;
    }
  } else {
    goto goo;
  }

  return;

goo:  
  bool b;
  QString text = QInputDialog::getText(this, tr("New Dialog"), tr("Enter the name of the new dialog:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){

    if (!checkObjectName(text)) goto goo;
    
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    QString s = "";

s = ""
"\nBegin Form *\n"
"  Flag = \"Dialog;SystemMenu\"\n"
"  Modal = True\n"
"End Form\n\n"
"";

    insertForm(text, s);
    openForm(getProjectPath()+ "/" + text + ".kbasic_form");
    QApplication::restoreOverrideCursor();  
    EXTERN_my_parserwindow->refreshProject();
  }
}

void _mainwindow::event_FILE_NEW_TOOLWINDOW()
{
  static bool bFirstTime = true;

  if (!bProject){
    QMessageBox::information( this, tr("New Tool Window"),
      tr(
           "In order to create a tool window you have to create a project first.\n"       
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
      goto goo;
    }
  } else {
    goto goo;
  }

  return;

goo:  
  bool b;
  QString text = QInputDialog::getText(this, tr("New Tool Window"), tr("Enter the name of the new tool window:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){

    if (!checkObjectName(text)) goto goo;
    
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    QString s = "";

s = ""
"\nBegin Form *\n"
"  Flag = \"Tool;SystemMenu\"\n"
"End Form\n\n"
"";

    insertForm(text, s);
    openForm(getProjectPath()+ "/" + text + ".kbasic_form");
    QApplication::restoreOverrideCursor();   
    EXTERN_my_parserwindow->refreshProject();
  }  
}
void _mainwindow::event_FILE_NEW_DOCKWINDOW()
{
  static bool bFirstTime = true;

  if (!bProject){
    QMessageBox::information( this, tr("New Dock Window"),
      tr(
           "In order to create a dock window you have to create a project first.\n"       
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
      goto goo;
    }
  } else {
    goto goo;
  }

  return;

goo:  
  bool b;
  QString text = QInputDialog::getText(this, tr("New Dock Window"), tr("Enter the name of the new dock window:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){

    if (!checkObjectName(text)) goto goo;
    
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    QString s = "";

s = ""
"\nBegin Form *\n"
"  Dock = \"All;AllFeatures;SetLeft;\"\n"
"End Form\n\n"
"";

    insertForm(text, s);
    openForm(getProjectPath()+ "/" + text + ".kbasic_form");
    QApplication::restoreOverrideCursor();    
    EXTERN_my_parserwindow->refreshProject();
  }    
}

void _mainwindow::event_FILE_NEW_FORM()
{
  event_FILE_NEW_FORM(false);
}

void _mainwindow::event_FILE_NEW_FORM(bool bWizard)
{
  
  static bool bFirstTime = true;

  if (!bProject){
    QMessageBox::information( this, tr("New Form"),
      tr(
           "In order to create a form you have to create a project first.\n"       
           "Inside a project all your forms are listed."
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
      goto goo;
    }
  } else {
    goto goo;
  }

  return;

goo:
  
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("New Form"),
      tr(
"Inside a KBasic application forms are not only input masks editing data, but "
"there are also the main role being the graphical user interface of your program. "
"Through the eyes of the users of your program, the forms are the application, actually. "
"With creating new forms around your application, you control the flow of your program "
"with the help of events, which occurs in your forms.\n"
"\n"
"The important roles:\n\n"
"Every form in your KBasic application has got an integrated form module with event procedures. "
"These procedures reacts on events, which occures in your form. \n"
"Additionally, class files and module files can contain generic functions and subs for your form. "
"A form module is a intergrated part of a form, if you copy a form, the form module will be copied, as well. "
"\n"
"Forms hold your KBasic program together!\n"
"\n"
"Let's create a new form file...\n"
)
    );

    bFirstTime = false;
  }

  bool b;
  QString text = QInputDialog::getText(this, tr("New Form"), tr("Enter the name of the new Form:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){

    if (!checkObjectName(text)) goto goo;
    
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    insertForm(text);
    openForm(getProjectPath()+ "/" + text + ".kbasic_form");
    QApplication::restoreOverrideCursor();
    
    if (bWizard){
      QMessageBox::information( this, tr("Wizard"),
        tr(
            "Please select in the following list the table you wish to\n"       
            "use for your SQL database form by double clicking on one item."
            )
            );
        event_VIEW_SQLTABLES();
    }
    
  }
  EXTERN_my_parserwindow->refreshProject();
}


void _mainwindow::event_FILE_NEW_REPORT()
{
  event_FILE_NEW_REPORT(false);
}

void _mainwindow::event_FILE_NEW_REPORT(bool bWizard)
{
  
  static bool bFirstTime = true;

  if (!bProject){
    QMessageBox::information( this, tr("New Report"),
      tr(
           "In order to create a report you have to create a project first.\n"       
           "Inside a project all your reports are listed."
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
      goto goo;
    }
  } else {
    goto goo;
  }

  return;

goo:
  /*
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("New Form"),
      tr(
"Inside a KBasic application forms are not only input masks editing data, but "
"there are also the main role being the graphical user interface of your program. "
"Through the eyes of the users of your program, the forms are the application, actually. "
"With creating new forms around your application, you control the flow of your program "
"with the help of events, which occurs in your forms.\n"
"\n"
"The important roles:\n\n"
"Every form in your KBasic application has got an integrated form module with event procedures. "
"These procedures reacts on events, which occures in your form. \n"
"Additionally, class files and module files can contain generic functions and subs for your form. "
"A form module is a intergrated part of a form, if you copy a form, the form module will be copied, as well. "
"\n"
"Forms hold your KBasic program together!\n"
"\n"
"Let's create a new form file...\n"
)
    );

    bFirstTime = false;
  }*/

  bool b;
  QString text = QInputDialog::getText(this, tr("New Report"), tr("Enter the name of the new Report:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){

    if (!checkObjectName(text)) goto goo;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    insertReport(text);
    openReport(getProjectPath()+ "/" + text + ".kbasic_report");
    QApplication::restoreOverrideCursor();

    if (bWizard){
      QMessageBox::information( this, tr("Wizard"),
        tr(
            "Please select in the following list the table you wish to\n"       
            "use for your SQL database report by double clicking on one item."
            )
            );
        event_VIEW_SQLTABLES();
    }   
  }
  EXTERN_my_parserwindow->refreshProject();
}

void _mainwindow::event_FILE_NEW_MENUBAR()
{
  if (!bProject){
    QMessageBox::information( this, tr("New MenuBar"),
      tr(
           "In order to create a menubar you have to create a project first.\n"       
           "Inside a project all your menubars are listed."
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
goo:
      bool b;
      QString text = QInputDialog::getText(this, tr("New MenuBar"), tr("Enter the name of the new MenuBar:"), QLineEdit::Normal, "myMenuBar", &b);
      if (b && !text.isEmpty()){

        if (!checkObjectName(text)) goto goo;

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        insertMenuBar(text);
#ifndef MAC
        openMenuBar(getProjectPath()+ "/" + text + ".kbasic_menubar");
        QApplication::restoreOverrideCursor();
#else
        QApplication::restoreOverrideCursor();

    QMessageBox::information( this, tr("Menubar Designer"),
      tr(
           "I am sorry, but the menubar designer on Mac is still under construction, \n"       
           "because menubars on Mac work differently, so that Qt in its newest version, "
           "does support native Mac menubars. Therefore only one menubar for an application"
           "is visible on top of the application window, but the menubar designer uses two"
           "menubars at one time on other platforms."
           )
           );
#endif
        
      }
    }
  } else {
goo2:
      bool b;
      QString text = QInputDialog::getText(this, tr("New Menubar"), tr("Enter the name of the new MenuBar:"), QLineEdit::Normal, "myMenuBar", &b);
      if (b && !text.isEmpty()){

        if (!checkObjectName(text)) goto goo2;

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        insertMenuBar(text);
#ifndef MAC
        openMenuBar(getProjectPath()+ "/" + text + ".kbasic_menubar");
        QApplication::restoreOverrideCursor();
#else
        QApplication::restoreOverrideCursor();

     QMessageBox::information( this, tr("Menubar Designer"),
      tr(
           "I am sorry, but the menubar designer on Mac is still under construction, \n"       
           "because menubars on Mac work differently, so that Qt in its newest version, "
           "does support native Mac menubars. Therefore only one menubar for an application"
           "is visible on top of the application window, but the menubar designer uses two"
           "menubars at one time on other platforms."
           )
           );
#endif
      
      }  
  }
  EXTERN_my_parserwindow->refreshProject();
}

void _mainwindow::event_FILE_NEW_TOOLBAR()
{
  if (!bProject){
    QMessageBox::information( this, tr("New Toolbar"),
      tr(
           "In order to create a toolbar you have to create a project first.\n"       
           "Inside a project all your toolbars are listed."
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
goo:
      bool b;
      QString text = QInputDialog::getText(this, tr("New ToolBar"), tr("Enter the name of the new ToolBar:"), QLineEdit::Normal, "myToolBar", &b);
      if (b && !text.isEmpty()){

        if (!checkObjectName(text)) goto goo;

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        insertToolBar(text);
        openToolBar(getProjectPath()+ "/" + text + ".kbasic_toolbar");

        QApplication::restoreOverrideCursor();
        
      }    }
  } else {

goo2:
      bool b;
      QString text = QInputDialog::getText(this, tr("New ToolBar"), tr("Enter the name of the new ToolBar:"), QLineEdit::Normal, "myToolBar", &b);
      if (b && !text.isEmpty()){

        if (!checkObjectName(text)) goto goo2;

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        insertToolBar(text);
        openToolBar(getProjectPath()+ "/" + text + ".kbasic_toolbar");

        QApplication::restoreOverrideCursor();
        
      }  
  }
  EXTERN_my_parserwindow->refreshProject();
}

void _mainwindow::event_PROJECT_WIZARD_FORM()
{  
  event_FILE_NEW_FORM(true);
}

void _mainwindow::event_PROJECT_WIZARD_REPORT()
{  
  event_FILE_NEW_REPORT(true);
}

void _mainwindow::event_FILE_NEW_TABLE()
{

  static bool bFirstTime = true;

  if (!bProject){
    QMessageBox::information( this, tr("New Table"),
      tr(
           "In order to create a table you should create a project first.\n"       
           "Inside a project all your tables are listed."
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
      goto goo;
    }
  } else {
    goto goo;
  }


  return;

goo:
  /*
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("New Table"),
tr(
""
    );

    bFirstTime = false;
  }
  */
  
  {

    bool b;
    QString text = QInputDialog::getText(this, tr("New Table"), tr("Enter the name of the new table:"), QLineEdit::Normal, QString::null, &b);
    if (b && !text.isEmpty()){

      if (!checkObjectName(text)) goto goo;

      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
      insertTable(text);
      openTable(getProjectPath()+ "/" + text + ".kbasic_table");
      QApplication::restoreOverrideCursor();
      EXTERN_my_projectwindow->refresh();

    }  
  }

  EXTERN_my_parserwindow->refreshProject();

}

void _mainwindow::event_FILE_NEW_QUERY()
{
  static bool bFirstTime = true;

  if (!bProject){
    QMessageBox::information( this, tr("New Query"),
      tr(
           "In order to create a query you should create a project first.\n"       
           "Inside a project all your queries are listed."
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
      goto goo;
    }
  } else {
    goto goo;
  }


  return;

goo:
  /*
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("New Query"),
tr(
""
    );

    bFirstTime = false;
  }
  */
goo2:
  bool b;
  QString text = QInputDialog::getText(this, tr("New Query"), tr("Enter the name of the new query:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){
     
    if (!checkObjectName(text)) goto goo2;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    insertQuery(text);
    openQuery(getProjectPath()+ "/" + text + ".kbasic_query");
    QApplication::restoreOverrideCursor();

  }  
  EXTERN_my_parserwindow->refreshProject();
}

void _mainwindow::event_FILE_NEW_CLASS()
{

  static bool bFirstTime = true;

  if (!bProject){
    QMessageBox::information( this, tr("New Class"),
      tr(
           "In order to create a class you should create a project first.\n"       
           "Inside a project all your classes are listed."
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
      goto goo;
    }
  } else {
    goto goo;
  }


  return;

goo:
  
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("New Class"),
tr(
"A small application can consists of one form, while all source code is inside the form class file, but if your applications grows bigger and bigger "
"it is useful to place some generic subs and functions inside class files or module files.\n"
"\n"
"So most often your program's source codes is placed inside class files or module files.\n\n"
"A class can consist of: \n"
"- declarations for variables and constants, \n"
"- subs and functions (which are called methods inside classes),\n"
"  These are methods which are not related to an event procedure. You can add generic subs and functions inside your class. Functions can return values as well.\n\n"
"- signal/slots methods\n"
"These are methods, which are related to the Qt-Bindings. More information can be found inside the Qt documentation.\n\n"
"- properties are special variables of the class, which have got two methods to read and write the variable's value.\n\n\n"
"Let's create a new class file...\n"
)
    );

    bFirstTime = false;
  }
  

  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("New Class"),
      tr(
"A small application can consists of one form, while all source code is inside the form class file, but if your applications grows bigger and bigger "
"it is useful to place some generic subs and functions inside class files or module files.\n"
"\n"
"So most often your program's source codes is placed inside class files or module files.\n\n"
"A class can consist of: \n"
"- declarations for variables and constants, \n"
"- subs and functions (which are called methods inside classes),\n"
"  These are methods which are not related to an event procedure. You can add generic subs and functions inside your class. Functions can return values as well.\n\n"
"- signal/slots methods\n"
"These are methods, which are related to the Qt-Bindings. More information can be found inside the Qt documentation.\n\n"
"- properties are special variables of the class, which have got two methods to read and write the variable's value.\n\n\n"
"Let's create a new class file...\n"
)
    );

    bFirstTime = false;
  }
goo2:
  bool b;
  QString text = QInputDialog::getText(this, tr("New Class"), tr("Enter the name of Class:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){

    if (!checkObjectName(text)) goto goo2;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    insertClass(text);
    openClass(getProjectPath()+ "/" + text + ".kbasic_class");
    QApplication::restoreOverrideCursor();


  }  
  EXTERN_my_parserwindow->refreshProject();
}

void _mainwindow::event_FILE_NEW_MODULE()
{
  static bool bFirstTime = true;

  if (!bProject){
    QMessageBox::information( this, tr("New Module"),
      tr(
           "In order to create a module you should create a project first.\n"       
           "Inside a project all your modules are listed."
           )
           );

    event_FILE_NEW_PROJECT();
    if (bProject){
      goto goo;
    }
  } else {
    goto goo;
  }


  return;

goo:
  
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("New Module"),
tr(
"A small application can consists of one form, while all source code is inside the form class file, but if your applications grows bigger and bigger "
"it is useful to place some generic subs and functions inside class files or module files.\n"
"\n"
"So most often your program's source codes is placed inside class files or module files.\n\n"
"A module can consist of: \n"
"- declarations for variables and constants, \n"
"- subs and functions\n"
"  You can add generic subs and functions inside your module. Functions can return values as well.\n\n\n"
"Let's create a new module file...\n"
)
    );

    bFirstTime = false;
  }
  
  
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("New Module"),
tr(
"A small application can consists of one form, while all source code is inside the form class file, but if your applications grows bigger and bigger "
"it is useful to place some generic subs and functions inside class files or module files.\n"
"\n"
"So most often your program's source codes is placed inside class files or module files.\n\n"
"A module can consist of: \n"
"- declarations for variables and constants, \n"
"- subs and functions\n"
"  You can add generic subs and functions inside your module. Functions can return values as well.\n\n\n"
"Let's create a new module file...\n"    
)
    );

    bFirstTime = false;
  }
goo2:
  bool b;
  QString text = QInputDialog::getText(this, tr("New Module"), tr("Enter the name of Module:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){

    if (!checkObjectName(text)) goto goo2;

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    insertModule(text);
    openModule(getProjectPath()+ "/" + text + ".kbasic_module");
    QApplication::restoreOverrideCursor();
    //loadFile(text);
  }
  EXTERN_my_parserwindow->refreshProject();
}


void _mainwindow::event_PROJECTLIST()
{
}

void _mainwindow::event_FILE_NEW_PROJECT()
{
  static bool bFirstTime = true;

  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("New Project"),
      tr(
    "Projects keep your work together. When developing an application in KBasic, you work "
    "mainly with projects. A project is a collection of files that make up your KBasic "
    "application. \n\nYou create a project to manage and organize these files. KBasic provides "
    "an easy yet sophisticated system to manage the collection of files that make up a "
    "project. The project window shows each item in a project. \nStarting a new application "
    "with KBasic begins with the creation of a project. So before you can construct an "
    "application with KBasic, you need to create a new project. A project consists of "
    "many separate files collected in one project directory, where one *.kbasic_project"
    "file is and many other files: \n\n"
    "   *.kbasic_module\n"
    "   *.kbasic_class \n"
    "   *.kbasic_form \n"
    )
    );

    bFirstTime = false;
  }

  int nProjectType = 0;
  _newproject *w = new _newproject(this, &nProjectType);
  int n = w->exec();
  
  if (n == 1){

    switch(nProjectType){
      case 0:
        QMessageBox::information(this, tr("New Project Created"),
          tr(
        "The new project is empty.\n"
        )
        );
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        setProjectPreference("menuRecords", "Yes");
        setProjectPreference("menuWindow", "Yes");
        setProjectPreference("menuHelp", "Yes");

        saveProjectPreferences();

        break;
      case 1:
        {
        QMessageBox::information(this, tr("New Project Created"),
          tr(
        "The new project will contain several items, e.g. a form named 'myForm' "
        "and a class named 'myEvent'.\n"
        "\n"
        "Now, I'm creating the items...\n"
        )
        );

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        insertForm("myForm");
        insertMenuBar("myMenuBar");
        insertToolBar("myToolBar");

        QString s = "";

s = ""
"Sub Forms_OnFormGotFocus(FormName As String)\n"
"End Sub\n"
"";

        insertClass("myEvent", s);

s = ""
"Function Main()\n"
"  Dim kbEvent As New myEvent()\n"
"  ' Place your custom start up code here\n"
"  Forms.Open(\"myForm\")\n"
"  Application.Run() ' do not delete this line or write code after it\n" 
"End Function\n\n"
"";
        insertModule("myModule", s);

        setProjectPreference("projectmainformname", "Function Main()");
        setProjectPreference("projecttype", tr("With MDI MainWindow (you must have myMenuBar created)"));

        setProjectPreference("menuRecords", "Yes");
        setProjectPreference("menuWindow", "Yes");
        setProjectPreference("menuHelp", "Yes");

        saveProjectPreferences();

        openForm(getProjectPath() + "/" + "myForm.kbasic_form");


    }
        break;
      case 2:
        {
        QMessageBox::information(this, tr("New Project Created"),
          tr(
        "The new project will contain several items, e.g. a form named 'myForm' "
        "and a class named 'myEvent'.\n"
        "\n"
        "Now, I'm creating the items...\n"
        )
        );

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        insertForm("myForm");
        insertMenuBar("myMenuBar");
        insertToolBar("myToolBar");

        QString s = "";


s = ""
"Sub Forms_OnFormGotFocus(FormName As String)\n"
"End Sub\n"
"";

        insertClass("myEvent", s);

s = ""
"Function Main()\n"
"  Dim kbEvent As New myEvent()\n"
"  ' Place your custom start up code here\n"
"  Forms.Open(\"myForm\")\n"
"  Application.Run() ' do not delete this line or write code after it\n" 
"End Function\n\n"
"";
        insertModule("myModule", s);


        setProjectPreference("projectmainformname", "Function Main()");
        setProjectPreference("projecttype", tr("With SDI MainWindow (you must have myMenuBar created)"));

        setProjectPreference("menuRecords", "No");
        setProjectPreference("menuWindow", "No");
        setProjectPreference("menuHelp", "No");

        saveProjectPreferences();

        openForm(getProjectPath() + "/" + "myForm.kbasic_form");

    }
        break;
      case 3:
        QMessageBox::information(this, tr("New Project Created"),
          tr(
        "The new project will contain at least two items: a form named 'Form1' "
        "and a module named 'Module1'.\n"
        "\n"
        "Now, I'm creating and opening 'Form1' and 'Module1'...\n"
        )
        );
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

        insertForm("Form1");
        insertModule("Module1");

        setProjectPreference("menuRecords", "Yes");
        setProjectPreference("menuWindow", "No");
        setProjectPreference("menuHelp", "Yes");

        saveProjectPreferences();

        openForm(getProjectPath() + "/" + "Form1.kbasic_form");
        break;
    }
    QApplication::restoreOverrideCursor();



  }
}


void _mainwindow::event_FILE_OPEN_PROJECT()
{
  static QString sDir = "";

  QString fn = QFileDialog::getOpenFileName(    
    this, tr("Open Project"), sDir, "Projects (*.kbasic_project)");

  if (!fn.isEmpty()){
    loadProject(fn);
    sDir = this->getFilenamePath(fn);
  	
  }
  
  
}

void _mainwindow::event_FILE_CLOSE_PROJECT()
{
  closeProject();
}

void _mainwindow::event_FILE_NEW_FILE()
{  
  static bool bFirstTime = true;

  if (bFirstTime && isPreferenceSet("IntroductionHelp")){

    QMessageBox::information(this, tr("New File"),
      tr(
    "You activated 'New File', which makes KBasic "
    "to create a new empty file for typing KBasic source code in. "
    "If you have already opened a project, this new file will not be part of this "
    "active project.\n\nIf you want to add more source codes files to the opened project, "
    "use 'New Module' or 'New Class' instead.\n"
    )
    );

    bFirstTime = false;
  }

  _sourcecodeeditor* w = new_sourcecodeeditor();
  EXTERN_my_parserwindow->refreshProject();
}

void _mainwindow::event_INSERT_SELECT2()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please select the control now."       
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_SELECT2();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_SELECT2();
    } 
  }
  {
    _menubar *o = qobject_cast<_menubar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_SELECT2();
    } 
  }
  {
    _toolbar *o = qobject_cast<_toolbar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_SELECT2();
    } 
  }
}

void _mainwindow::event_INSERT_LABEL()
{
  static bool bFirstTime = true; if (!bFirstTime) bFirstTime = false; else static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );
  

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_LABEL();
    }
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_LABEL();
    }
  }
}

// CONTROL

void _mainwindow::event_INSERT_UDPSOCKET()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_UDPSOCKET();
  } 
}

void _mainwindow::event_INSERT_SCROLLBAR()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_SCROLLBAR();
  } 
}

void _mainwindow::event_INSERT_SPINBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_SPINBOX();
  } 
}

void _mainwindow::event_INSERT_SLIDER()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_SLIDER();
  } 
}

void _mainwindow::event_INSERT_FORMSVIEW()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_FORMSVIEW();
  } 
}

void _mainwindow::event_INSERT_TOOLBARVIEW()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_TOOLBARVIEW();
  } 
}

void _mainwindow::event_INSERT_SVG()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_SVG();
  } 
}

void _mainwindow::event_INSERT_RESIZEBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_RESIZEBOX();
  } 
}

void _mainwindow::event_INSERT_COMMANDLINKBUTTON()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_COMMANDLINKBUTTON();
  } 
}

void _mainwindow::event_INSERT_TOOLBUTTON()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_TOOLBUTTON();
  } 
}


void _mainwindow::event_INSERT_COMMANDBUTTON()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_COMMANDBUTTON();
  } 
}

void _mainwindow::event_INSERT_CHECKBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_CHECKBOX();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_CHECKBOX();
    } 
  }
}

void _mainwindow::event_INSERT_RADIOBUTTON()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_RADIOBUTTON();
  } 
}

void _mainwindow::event_INSERT_TEXTBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_TEXTBOX();
    }
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_TEXTBOX();
    }
  }
}

void _mainwindow::event_INSERT_FRAME()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_FRAME();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_FRAME();
    } 
  }
}

void _mainwindow::event_INSERT_LISTBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_LISTBOX();
  } 
}

void _mainwindow::event_INSERT_COMBOBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_COMBOBOX();
  } 
}

void _mainwindow::event_INSERT_PROGRESSBAR()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_PROGRESSBAR();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_PROGRESSBAR();
    } 
  }
}



void _mainwindow::event_INSERT_COMBOBOX_EDITABLE()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_COMBOBOX_EDITABLE();
    } 
  }
}

void _mainwindow::event_INSERT_LISTBOX_ICONMODE()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_LISTBOX_ICONMODE();
    } 
  }
}


void _mainwindow::event_INSERT_TREEVIEW_LISTVIEW()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_TREEVIEW_LISTVIEW();
    } 
  }
}

void _mainwindow::event_INSERT_PROGRESSBAR_SPINNING()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_PROGRESSBAR_SPINNING();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_PROGRESSBAR_SPINNING();
    } 
  }
}

void _mainwindow::event_INSERT_IMAGE()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_IMAGE();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_IMAGE();
    } 
  }
}

void _mainwindow::event_INSERT_CHILDCONTROL()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_CHILDCONTROL();
  } 
}

void _mainwindow::event_INSERT_BROWSER()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),
        tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            )
            );

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_BROWSER();
    }
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_BROWSER();
    }
  }
}

void _mainwindow::event_INSERT_SERIALPORT()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_SERIALPORT();
    }
  }
}

void _mainwindow::event_INSERT_HEADER()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_HEADER();
    }
  }
}

void _mainwindow::event_INSERT_FOOTER()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_FOOTER();
    }
  }
}

void _mainwindow::event_INSERT_EDITOR()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_EDITOR();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_EDITOR();
    } 
  }
}

void _mainwindow::event_INSERT_DATEBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_DATEBOX();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_DATEBOX();
    } 
  }
}

void _mainwindow::event_INSERT_TIMEBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_TIMEBOX();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_TIMEBOX();
    } 
  }
}

void _mainwindow::event_INSERT_DATETIMEBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_DATETIMEBOX();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_DATETIMEBOX();
    } 
  }
}



void _mainwindow::event_INSERT_TEXTBOX_PASSWORD()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_TEXTBOX_PASSWORD();
    } 
  }

}
void _mainwindow::event_INSERT_LABEL_LINK()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_LABEL_LINK();
    } 
  }

}

void _mainwindow::event_INSERT_LINE_VERTICAL()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_LINE_VERTICAL();
    } 
  }

}


void _mainwindow::event_INSERT_LINE_HORIZONTAL()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_LINE_HORIZONTAL();
    } 
  }

}

void _mainwindow::event_INSERT_VSPLIT()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_VSPLIT();
  } 
}

void _mainwindow::event_INSERT_HSPLIT()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_HSPLIT();
  } 
}

void _mainwindow::event_INSERT_VBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_VBOX();
  } 
}

void _mainwindow::event_INSERT_HBOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_HBOX();
  } 
}

void _mainwindow::event_INSERT_VHBOX()
{

 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_VHBOX();
  } 
}

void _mainwindow::event_INSERT_BOX()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_BOX();
    } 
  }
  {
    _report *o = qobject_cast<_report *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_BOX();
    } 
  }
}

void _mainwindow::event_INSERT_HIDDEN()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_HIDDEN();
  } 
}

void _mainwindow::event_INSERT_TREEVIEW()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_TREEVIEW();
  } 
}

void _mainwindow::event_INSERT_TAB()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_TAB();
  } 
}

void _mainwindow::event_INSERT_MOVIE()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_MOVIE();
  } 
}

void _mainwindow::event_INSERT_SOUND()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_SOUND();
  } 
}

void _mainwindow::event_INSERT_WEB()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_WEB();
  } 
}

void _mainwindow::event_INSERT_TIMER()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_TIMER();
  } 
}

void _mainwindow::event_INSERT_IMAGEBUTTON()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the control is to be inserted."
            ));

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_IMAGEBUTTON();
  } 
}

void _mainwindow::event_INSERT_MENU()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the menu is to be inserted."
            ));

  _menubar *o = qobject_cast<_menubar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_MENU();
  } 
}

void _mainwindow::event_INSERT_CHILDMENU()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position of an existing menu, \n"       
            "where the child menu is to be inserted."
            ));

  _menubar *o = qobject_cast<_menubar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_CHILDMENU();
  } 
}

void _mainwindow::event_INSERT_MENUBARITEM()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position of an existing menu, \n"       
            "where the menubar item is to be inserted."
            ));

  _menubar *o = qobject_cast<_menubar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_MENUBARITEM();
  } 
}

void _mainwindow::event_INSERT_MOVE()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the item is to be moved."
            ));

  {
    _menubar *o = qobject_cast<_menubar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_MOVE();
      return;
    } 
  }
    {
    _toolbar *o = qobject_cast<_toolbar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_MOVE();
      return;
    } 
  }
}

void _mainwindow::event_INSERT_DELETE()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position \n"       
            "of the item, which is to be deleted."
            ));

  {
    _menubar *o = qobject_cast<_menubar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_DELETE();
      return;
    } 
  }
    {
    _toolbar *o = qobject_cast<_toolbar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_INSERT_DELETE();
      return;
    } 
  }
}

void _mainwindow::event_INSERT_TOOLBARITEM()
{
 static bool bFirstTime = true; if (bFirstTime) bFirstTime = false; else QMessageBox::information( this, tr(MYAPP),  tr(
            "Please click on the position, \n"       
            "where the toolbar item is to be inserted."
            ));

  _toolbar *o = qobject_cast<_toolbar *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_INSERT_TOOLBARITEM();
  } 
}


void _mainwindow::event_FORMAT_ALIGN_BOTTOM()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_ALIGN_BOTTOM();
  } 
}


void _mainwindow::event_FORMAT_ALIGN_TOP()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_ALIGN_TOP();
  } 
}

void _mainwindow::event_FORMAT_ALIGN_LEFT()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_ALIGN_LEFT();
  } 
}

void _mainwindow::event_FORMAT_ALIGN_RIGHT()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_ALIGN_RIGHT();
  } 
}

void _mainwindow::event_FORMAT_SET_SAME_WIDTH()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_SET_SAME_WIDTH();
  } 
}

void _mainwindow::event_FORMAT_SET_SAME_HEIGHT()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_SET_SAME_HEIGHT();
  } 
}

void _mainwindow::event_FORMAT_SET_SAME_SIZE()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_SET_SAME_SIZE();
  } 
}

void _mainwindow::event_FORMAT_LAYOUT_HORIZONTALLY()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_LAYOUT_HORIZONTALLY();
  } 
}

void _mainwindow::event_FORMAT_LAYOUT_VERTICALLY()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_LAYOUT_VERTICALLY();
  } 
}

void _mainwindow::event_FORMAT_MOVE_TO_FRONT()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_MOVE_TO_FRONT();
  } 
}

void _mainwindow::event_FORMAT_MOVE_TO_BACK()
{
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_MOVE_TO_BACK();
  } 
}

void _mainwindow::event_FORMAT_MOVE_UP()
{
  _table *o = qobject_cast<_table *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_MOVE_UP();
  } 
  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_FORMAT_ALIGN_MOVEUP();
      return;
    }
  }
}

void _mainwindow::event_FORMAT_MOVE_DOWN()
{
  {
    _table *o = qobject_cast<_table *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_FORMAT_MOVE_DOWN();
      return;
    }
  }
  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_FORMAT_ALIGN_MOVEDOWN();
      return;
    }
  }
}

void _mainwindow::event_FORMAT_MOVE_LEFT()
{
  _qbe *o = qobject_cast<_qbe *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_MOVE_LEFT();
  } 
  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_FORMAT_ALIGN_MOVELEFT();
      return;
    }
  }
}

void _mainwindow::event_FORMAT_MOVE_RIGHT()
{
  _qbe *o = qobject_cast<_qbe *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_FORMAT_MOVE_RIGHT();
  } 
  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->event_FORMAT_ALIGN_MOVERIGHT();
      return;
    }
  }
}

void _mainwindow::event_TRANSLATION_ADD()
{
  bool b;
  QString text = QInputDialog::getText(this, tr("New Language"), tr("Enter the name of the new language:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){
    TRANSLATION->addItem(text);
    TRANSLATION->setCurrentIndex(TRANSLATION->findText(text));

   QString s = "";
    for (int i = 0; i < TRANSLATION->count(); i++){
      s += TRANSLATION->itemText(i);
      s += ";";
    }
    EXTERN_my_mainwindow->setProjectPreference("Translation", s);
    EXTERN_my_mainwindow->saveProjectPreferences();

  }
}

void _mainwindow::event_TRANSLATION_REMOVE()
{

  QString s = TRANSLATION->currentText();
  if (s.isEmpty()) return;

	  switch( QMessageBox::question( this, tr("Delete current selected language"), 
	      tr("Do you really want to delete %1? All translation data will be lost.").arg( s ),
	      QMessageBox::Yes | QMessageBox::No )){
	    case QMessageBox::Yes:
	        {
            TRANSLATION->removeItem(TRANSLATION->findText(s));
            TRANSLATION->setCurrentIndex(0);

             QString s = "";
              for (int i = 0; i < TRANSLATION->count(); i++){
                s += TRANSLATION->itemText(i);
                s += ";";
              }
              EXTERN_my_mainwindow->setProjectPreference("Translation", s);
              EXTERN_my_mainwindow->saveProjectPreferences();
  

          }
	        break;    

	  }
}

void _mainwindow::event_FILE_OPEN_FILE()
{
  static QString sDir = "";

  QString fn = QFileDialog::getOpenFileName(this, tr("Open File"), sDir,
    "Files (*.kbasic_class *.kbasic_module *.kbasic *.bas)" );

  if (!fn.isEmpty()){
    loadFile(fn, false);
    sDir = this->getFilenamePath(fn);
    EXTERN_my_parserwindow->refreshProject();
  }
//  updateActions();
}

void _mainwindow::event_INSERT_FIELDS_CLASS()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    _insert_general *k = new _insert_general (o, 
      "__Class__", 
      "__CLASS__"     
      );    

  }
  
}

void _mainwindow::event_INSERT_FIELDS_LINE()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    _insert_general *k = new _insert_general (o,
      "__Line__", 
      "__LINE__"     
      );    

  }
  
}

void _mainwindow::event_INSERT_FIELDS_SCOPE()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    _insert_general *k = new _insert_general (o,
      "__Scope__", 
      "__SCOPE__"     
      );    

  }
  
}

void _mainwindow::event_INSERT_FIELDS_MODULE()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    _insert_general *k = new _insert_general (o,
      "__Module__", 
      "__MODULE__"     
      );    

  }
  
}

void _mainwindow::event_INSERT_FIELDS_SUB()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    _insert_general *k = new _insert_general (o,
      "__Sub__", 
      "__SUB__"     
      );    

  }
  
}

void _mainwindow::event_INSERT_REMARK()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_remark *k = new _insert_remark (this, o, tr("Rem"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"Kommentare\">" : "<H2><A NAME=\"Comments\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_STATEMENT()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_statement *k = new _insert_statement (this, o, tr("Statement"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"AnweisungenundAusdr&uuml;cke\">" : "<H2><A NAME=\"Statementsandexpressions\">"
      ,"<H2>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_ASSIGNMENT()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_assignment *k = new _insert_assignment (this, o, tr("Assignment"), kbasicIcon(kbasicPath("ide/DUMMY.png"))      
      ,_mainwindow::locale() == "de" ? "<H3><A NAME=\"Zuweisungsanweisungen\">" : "<H3><A NAME=\"Assignment-statement\">"
      , "<H3>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_EXPRESSION()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_expression *k = new _insert_expression (this, o, tr("Expression"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"Ausdr&uuml;cke\">" : "<H2><A NAME=\"Expressions\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }
}

void _mainwindow::event_INSERT_OPERATOR()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_operator *k = new _insert_operator (this, o, tr("Operator"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"\"><FONT CLASS=\"h2\"><B>" : "<H2><A NAME=\"\"><FONT CLASS=\"h2\"><B>"
      , _mainwindow::locale() == "de" ? "<H3><A NAME=\"VermeidenvonNamenskonflikten\">" : "<H3><A NAME=\"Avoidingnamecollision\">"
      );
    QApplication::restoreOverrideCursor();


  }
  
}

void _mainwindow::event_INSERT_OPTION_KBASIC()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_option_kbasic *k = new _insert_option_kbasic (this, o, tr("Mode / Option KBasic"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"The applicationistnichtnureineProgrammiersprache,sonderndrei\">" : "<H2><A NAME=\"The applicationisnotonlyoneprogramminglanguagebutalsothree.\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();
  }  
}


void _mainwindow::event_INSERT_OPTION_OLDBASIC()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_option_oldbasic *k = new _insert_option_oldbasic (this, o, tr("Mode / Option OldBasic"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"The applicationistnichtnureineProgrammiersprache,sonderndrei\">" : "<H2><A NAME=\"The applicationisnotonlyoneprogramminglanguagebutalsothree.\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }  
}

void _mainwindow::event_INSERT_OPTION_VERYOLDBASIC()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_option_veryoldbasic *k = new _insert_option_veryoldbasic (this, o, tr("Mode / Option VeryOldBasic"), kbasicIcon(kbasicPath("ide/DUMMY.png")), 
      _mainwindow::locale() == "de" ? "<H2><A NAME=\"The applicationistnichtnureineProgrammiersprache,sonderndrei\">" : "<H2><A NAME=\"The applicationisnotonlyoneprogramminglanguagebutalsothree.\">"
      ,"<H2>");    
    QApplication::restoreOverrideCursor();

  }  
}


void _mainwindow::event_INSERT_IF()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_if *k = new _insert_if (this, o, tr("If Then Else"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H3><A NAME=\"EinfacheEntscheidung\">" : "<H3><A NAME=\"Singledecision-If\">"
      , "<H3>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_SELECT()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    _insert_select *k = new _insert_select (this, o, tr("Select Case"), kbasicIcon(kbasicPath("ide/dissociatecell.png"))
      , _mainwindow::locale() == "de" ? "<H3><A NAME=\"Mehrfachauswahl\">" : "<H3><A NAME=\"SelectCase\">"
      , "<H3>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_FORNEXT()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_fornext *k = new _insert_fornext (this, o, tr("For Next"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H3><A NAME=\"ForNext\">" : "<H3><A NAME=\"ForNext\">"
      , "<H3>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_WHILELOOP()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_whileloop *k = new _insert_whileloop (this, o, tr("Do While ... Loop"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H3><A NAME=\"'DoWhile...Loop'\">" : "<H3><A NAME=\"DoWhile...Loop\">"
      , "<H3>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_LOOPWHILE()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_loopwhile *k = new _insert_loopwhile (this, o, tr("Do ... Loop While"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H3><A NAME=\"Do...LoopWhile\">" : "<H3><A NAME=\"Do...LoopWhile\">"
      , "<H3>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_EXCEPTION()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_exception *k = new _insert_exception (this, o, tr("Exception"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"Errorhandling(inEnglisch)\">" : "<H2><A NAME=\"Errorhandling\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_VARIABLE()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_variable *k = new _insert_variable (this, o, tr("Dim"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"VariablenundDatentypen\">" : "<H2><A NAME=\"VariablesandDataTypes\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_CONST()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_const *k = new _insert_const (this, o, tr("Const"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"Konstanten\">" : "<H2><A NAME=\"Constants\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }
  
}



void _mainwindow::event_INSERT_SUB()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_sub *k = new _insert_sub (this, o, tr("Sub"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"Prozeduren\">" : "<H2><A NAME=\"Procedures\">"
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"Funktionen\">" : "<H2><A NAME=\"Functions\">"
      );    
    QApplication::restoreOverrideCursor();

  }
  
}


void _mainwindow::event_INSERT_FUNCTION()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_function *k = new _insert_function (this, o, tr("Function"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"Funktionen\">" : "<H2><A NAME=\"Functions\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }
  
}


void _mainwindow::event_INSERT_PROPERTY()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_property *k = new _insert_property (this, o, tr("Property"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"Properties\">" : "<H2><A NAME=\"Properties\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_TYPE()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_type *k = new _insert_type (this, o, tr("Type"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"BenutzerdefinierterDatentyp\">" : "<H2><A NAME=\"Userdefinedtypes\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_INSERT_ENUM()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _insert_enum *k = new _insert_enum (this, o, tr("Enum"), kbasicIcon(kbasicPath("ide/DUMMY.png"))
      , _mainwindow::locale() == "de" ? "<H2><A NAME=\"Aufz&auml;hlungstyp\">" : "<H2><A NAME=\"Enumeration(Enum...EndEnum)\">"
      , "<H2>");    
    QApplication::restoreOverrideCursor();

  }
  
}

void _mainwindow::event_VIEW_FOCUSORDER()
{ 
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->showFocusOrder();
  }
}

void _mainwindow::event_VIEW_SQLSETTINGS()
{ 
  if (!CurrentDatabase.isOpen()){
    QMessageBox::information(this, MYAPP, "You are not connected to a database.");  
    return;
  }

  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->showSQLSettings();
  }
}

void _mainwindow::event_VIEW_SQLTABLES()
{ 

  if (!CurrentDatabase.isOpen()){
    QMessageBox::information(this, MYAPP, "You are not connected to a database.");  
    return;
  }

  EXTERN_DatabaseTables->setShown(true); EXTERN_DatabaseTables->setFloating(true);
  qApp->setActiveWindow(EXTERN_DatabaseTables);

}

void _mainwindow::event_VIEW_RELATION()
{   
  if (!CurrentDatabase.isOpen()){
    QMessageBox::information(this, MYAPP, "You are not connected to a database.");  
    return;
  }

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  EXTERN_DatabaseTables->setShown(false);

  QList<QMdiSubWindow *>windows = workspace->subWindowList();
  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      if (windows.at(i)->widget()->objectName() == "Relations"){
        workspace->setActiveSubWindow(windows.at(i));
        QApplication::restoreOverrideCursor();
        return;
      }
    }

  }
  _relation *kk = new _relation (this);
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_VIEW_QUICKCODE()
{ 
  EXTERN_Quickcode->show(); 
  EXTERN_Quickcode->widget()->setFocus();
}

void _mainwindow::event_VIEW_QBE()
{ 
  if (!CurrentDatabase.isOpen()/* || CurrentDatabase.isOpenError()*/){
    QMessageBox::information(this, MYAPP, "You are not connected to a database.");      
    return;
  }

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  EXTERN_DatabaseTables->setShown(false);

  _qbe *kk = new _qbe (this);
  QApplication::restoreOverrideCursor();
  
}

void _mainwindow::event_VIEW_FULLSCREEN()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->setFullscreen();
  }
}

void _mainwindow::event_EDIT_FIND()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));  
    o->performFind();  
    QApplication::restoreOverrideCursor();
  }
}

void _mainwindow::event_EDIT_REPLACE()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));  
    o->performReplace();   
    QApplication::restoreOverrideCursor();
  }
}

void _mainwindow::event_EDIT_NEXT_BOOKMARK()
{ 
  {

    if (!bookmarks.isEmpty()){
      if (nCurrentBookmark >= bookmarks.size()) nCurrentBookmark = 0;
      if (nCurrentBookmark < 0) nCurrentBookmark = bookmarks.size() - 1;

      _bookmark b;

      b = bookmarks[nCurrentBookmark++];

      QString s = b.sFile;
      //if (s != o->getFilename())
      {
        if (s.endsWith(".kbasic_class", Qt::CaseInsensitive)) openClass(s);
        else if (s.endsWith(".kbasic_module", Qt::CaseInsensitive)) openModule(s);
        else if (s.endsWith(".kbasic_form", Qt::CaseInsensitive)) openFormClassSourceCode(s);        
        else if (s.endsWith(".kbasic", Qt::CaseInsensitive)) openModule(s);
        
        _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
        if (o){
          o->setCurrentLineAndSelectLine(b.nLine);
        }
     }
      
    }
  }
}

void _mainwindow::event_EDIT_PREVIOUS_BOOKMARK()
{ 
   {

    if (!bookmarks.isEmpty()){
      if (nCurrentBookmark >= bookmarks.size()) nCurrentBookmark = 0;
      if (nCurrentBookmark < 0) nCurrentBookmark = bookmarks.size() - 1;

      _bookmark b;

      b = bookmarks[nCurrentBookmark--];

      QString s = b.sFile;
      {
        if (s.endsWith(".kbasic_class", Qt::CaseInsensitive)) openClass(s);
        else if (s.endsWith(".kbasic_module", Qt::CaseInsensitive)) openModule(s);
        else if (s.endsWith(".kbasic_form", Qt::CaseInsensitive)) openFormClassSourceCode(s);        
        else if (s.endsWith(".kbasic", Qt::CaseInsensitive)) openModule(s);
        
        _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
        if (o){
          o->setCurrentLineAndSelectLine(b.nLine);
        }
      }
    }
  }
}

void _mainwindow::event_EDIT_SET_BOOKMARK()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    // set
    if (o->setUnsetBookmarkSelection()){
      _bookmark b;

      b.sFile = o->getFilename();
      b.nLine = o->getCurrentLine();
      bookmarks.append(b);

    // unset
    } else {

      QString sCurrentFile = o->getFilename();
      int nCurrentLine = o->getCurrentLine();

      _bookmark b;

      for (int i = 0; i < bookmarks.size(); i++){
        b = bookmarks[i];

        if (b.sFile == sCurrentFile && b.nLine == nCurrentLine){
          bookmarks.removeAt(i);
          break;
        }
      } 
    }
  }
}

void _mainwindow::event_EDIT_CLEAR_ALL_BOOKMARKS()
{ 
  bookmarks.clear();
  nCurrentBookmark = 0;  

  QList<QMdiSubWindow *>windows = workspace->subWindowList();
  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
      if (o){
        o->clearBookmarkSelection();
       }
    }
  }  
}

void _mainwindow::event_EDIT_NEXT_BREAKPOINT()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    if (!breakpoints.isEmpty()){
      if (nCurrentBreakpoint >= breakpoints.size()) nCurrentBreakpoint = 0;
      if (nCurrentBreakpoint < 0) nCurrentBreakpoint = breakpoints.size() - 1;

      _breakpoint b;

      b = breakpoints[nCurrentBreakpoint++];

      QString s = b.sFile;
      if (s != o->getFilename()){
        if (s.endsWith(".kbasic_class", Qt::CaseInsensitive)) openClass(s);
        else if (s.endsWith(".kbasic_module", Qt::CaseInsensitive)) openModule(s);
        else if (s.endsWith(".kbasic_form", Qt::CaseInsensitive)) openFormClassSourceCode(s);        
        else if (s.endsWith(".kbasic", Qt::CaseInsensitive)) openModule(s);
        
        _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
        if (o){
          o->setCurrentLineAndSelectLine(b.nLine);
        }
      } else {
        o->setCurrentLineAndSelectLine(b.nLine);
      }
      
    }
  }
}

void _mainwindow::event_EDIT_PREVIOUS_BREAKPOINT()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    if (!breakpoints.isEmpty()){
      if (nCurrentBreakpoint >= breakpoints.size()) nCurrentBreakpoint = 0;
      if (nCurrentBreakpoint < 0) nCurrentBreakpoint = breakpoints.size() - 1;

      _breakpoint b;

      b = breakpoints[nCurrentBreakpoint--];

      QString s = b.sFile;
      if (s != o->getFilename()){
        if (s.endsWith(".kbasic_class", Qt::CaseInsensitive)) openClass(s);
        else if (s.endsWith(".kbasic_module", Qt::CaseInsensitive)) openModule(s);
        else if (s.endsWith(".kbasic_form", Qt::CaseInsensitive)) openFormClassSourceCode(s);        
        else if (s.endsWith(".kbasic", Qt::CaseInsensitive)) openModule(s);
        
        _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
        if (o){
          o->setCurrentLineAndSelectLine(b.nLine);
        }
      } else {
        o->setCurrentLineAndSelectLine(b.nLine);
      }
    }
  }
}

void _mainwindow::updateBreakpointsByEditor()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QString sLines = o->getBreakpointsAsString();

    if (bDebugging && myInterpreter) myInterpreter->interpretUpdateBreakpoint(o->getFilename(), sLines);

  re:
    for (int i = 0; i < breakpoints.size(); ++i) {
      _breakpoint br = breakpoints.at(i);

      if (br.sFile.startsWith(o->getFilename(), Qt::CaseInsensitive)){
        breakpoints.removeAt(i);
        goto re;
      }
    }

    QStringList l = sLines.split(",");

    foreach(QString ss, l){

      _breakpoint b;

      b.sFile = o->getFilename();
      b.nLine = ss.toInt();

      if (o->getFilename().endsWith(".kbasic_form", Qt::CaseInsensitive)) b.nLine--; // sub extra line
      else if (o->getFilename().endsWith(".kbasic_report", Qt::CaseInsensitive)) b.nLine--; // sub extra line
      else if (o->getFilename().endsWith(".kbasic_menubar", Qt::CaseInsensitive)) b.nLine--; // sub extra line
      else if (o->getFilename().endsWith(".kbasic_toolbar", Qt::CaseInsensitive)) b.nLine--; // sub extra line

      breakpoints.append(b);

    }

  }
}

void _mainwindow::event_EDIT_SET_BREAKPOINT()
{ 
  if (this->isRunning()){
 
    QMessageBox::information(this, MYAPP,
       tr(
    "Sorry. You cannot add or remove a breakpoint while execution.\n"
    "You have to add or remove it before you run your program." ));
      return;

  }
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

    // set
    if (o->setUnsetBreakpointSelection()){
      _breakpoint b;

      b.sFile = o->getFilename();
      b.nLine = o->getCurrentLine();

      breakpoints.append(b);

      if (b.sFile.endsWith(".kbasic_form", Qt::CaseInsensitive)) b.nLine++; // add extra line
      else if (b.sFile.endsWith(".kbasic_report", Qt::CaseInsensitive)) b.nLine++; // add extra line
      else if (b.sFile.endsWith(".kbasic_menubar", Qt::CaseInsensitive)) b.nLine++; // add extra line
      else if (b.sFile.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)) b.nLine++; // add extra line

      if (bDebugging && myInterpreter) myInterpreter->interpretAddBreakpoint(o->getFilename(), b.nLine);

    // unset
    } else {

      QString sCurrentFile = o->getFilename();
      int nCurrentLine = o->getCurrentLine();

      _breakpoint b;

      for (int i = 0; i < breakpoints.size(); i++){
        b = breakpoints[i];

        if (b.sFile == sCurrentFile && b.nLine == nCurrentLine){
          breakpoints.removeAt(i);
          if (bDebugging && myInterpreter){

            int n = nCurrentLine;

            if (sCurrentFile.endsWith(".kbasic_form", Qt::CaseInsensitive)) n++; // add extra line
            else if (sCurrentFile.endsWith(".kbasic_report", Qt::CaseInsensitive)) n++; // add extra line
            else if (sCurrentFile.endsWith(".kbasic_menubar", Qt::CaseInsensitive)) n++; // add extra line
            else if (sCurrentFile.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)) n++; // add extra line

            myInterpreter->interpretRemoveBreakpoint(o->getFilename(), n);
          }
          break;
        }
      } 
    }
  }
}

void _mainwindow::event_EDIT_CLEAR_ALL_BREAKPOINTS()
{ 
  breakpoints.clear();
  nCurrentBreakpoint = 0;

  QList<QMdiSubWindow *>windows = workspace->subWindowList();
  if (int(windows.count())){    

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
      if (o){
        o->clearBreakpointSelection();
       }
    }
  }  
}

void _mainwindow::event_EDIT_GOTO()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->performGotoLine();
  }
}

void _mainwindow::event_EDIT_INSERT_FILE()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    //QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));  
    o->performInsertFile();
    //QApplication::restoreOverrideCursor();
  }
}

void _mainwindow::event_EDIT_UNDO()
{ 
  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
  if (o){
    o->performUndo();
    return;
  }
  _form *f = qobject_cast<_form *>(w);
  if (f){
    f->performUndo();
    //f->event_INSERT_COMMANDBUTTON();
    return;
  } 
}

void _mainwindow::event_EDIT_REDO()
{ 
  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
  if (o){
    o->performRedo();
    return;
  }
  _form *f = qobject_cast<_form *>(w);
  if (f){
    f->performRedo();
    return;
  } 
}

void _mainwindow::event_EDIT_CUT()
{ 
  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
  if (o && o->hasFocus()){
    o->performCut();
    return;
  }
  _form *f = qobject_cast<_form *>(w);
  if (f && f->hasFocus()){
    f->_event_EDIT_CUT();
    return;
  } 
  cutFile();
  EDIT_PASTE->setEnabled(EXTERN_my_projectwindow->pasteAvailable());
}

void _mainwindow::event_EDIT_COPY()
{ 
  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
  if (o && o->hasFocus()){
    o->performCopy();
    return;
  }
  _form *f = qobject_cast<_form *>(w);
  if (f && f->hasFocus()){
    f->_event_EDIT_COPY();
    return;
  } 
  copyFile();
  EDIT_PASTE->setEnabled(EXTERN_my_projectwindow->pasteAvailable());
}


void _mainwindow::event_EDIT_APPLY()
{ 
  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  _form *o = qobject_cast<_form *>(w);
  if (o/* && o->hasFocus()*/){
    o->_event_EDIT_APPLY();
  }
}

void _mainwindow::event_EDIT_PASTE()
{ 
  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
  if (o && o->hasFocus()){
    o->performPaste();
    return;
  }
  _form *f = qobject_cast<_form *>(w);
  if (f && f->hasFocus()){
    f->_event_EDIT_PASTE();
    return;
  } 
  pasteFile();
}

void _mainwindow::event_EDIT_DELETE()
{ 
  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(w);
  if (o && o->hasFocus()){
    o->performDelete();
    return;
  }
  _form *f = qobject_cast<_form *>(w);
  if (f && f->hasFocus()){
    f->_event_EDIT_DELETE();
    return;
  } 
  deleteFile();
}

void _mainwindow::event_EDIT_SELECT_ALL()
{ 
  {
    _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->performSelectAll();
    }
  }

  {
    _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->performSelectAll();
    }
  }
}

void _mainwindow::event_EDIT_MARK_LINES()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->performMark();
  }
}

void _mainwindow::event_EDIT_UPPER()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->performUpper();
  }
}

void _mainwindow::event_EDIT_BACKGROUND()
{ 
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_EDIT_BACKGROUND();
  }
}

void _mainwindow::event_EDIT_FONTNAME()
{ 
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_EDIT_FONTNAME();
  }
}

void _mainwindow::event_EDIT_FONTCOLOR()
{ 
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_EDIT_FONTCOLOR();
  }
}

void _mainwindow::event_EDIT_BOLD()
{ 
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_EDIT_BOLD();
  }
}

void _mainwindow::event_EDIT_ITALIC()
{ 
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_EDIT_ITALIC();
  }
}

void _mainwindow::event_EDIT_UNDERLINE()
{ 
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_EDIT_UNDERLINE();
  }
}

void _mainwindow::event_EDIT_FONTSIZE()
{ 
  _form *o = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->event_EDIT_FONTSIZE();
  }
}

void _mainwindow::event_EDIT_LOWER()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->performLower();
  }
}

void _mainwindow::event_EDIT_FINDDEFINITION()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));  

    EXTERN_my_mainwindow->ci_parse(o->getFilename(), o->my_sourcecodeeditor_editor->document()->toPlainText());

    o->performFindDefinition();
    QApplication::restoreOverrideCursor();
  }
}

void _mainwindow::event_EDIT_COMMENT_LINES()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->performComment();
  }
}

void _mainwindow::event_EDIT_UNCOMMENT_LINES()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->performUncomment();
  }
}

void _mainwindow::event_EDIT_UNINDENT_LINES()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->performUnindent();
  }
}

void _mainwindow::event_EDIT_INDENT_LINES()
{ 
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    o->performIndent();
  }
}

void _mainwindow::event_HELP_LANGUAGE_REFERENCE()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  QDesktopServices::openUrl(QUrl("http://www.kbasic.com/doku.php?id=language_reference"));
  QApplication::restoreOverrideCursor();
//  _help_reference *h = new _help_reference(this, kbasicPath("docs/languagereference/home.html"), QUrl(""));  
}


void _mainwindow::event_VIEW_RUNINFO()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  my_infoconsole->view();
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_EDIT_FIND_FILE()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  // be sure to make only one window visible
  foreach (QWidget *widget, QApplication::allWidgets()){
    if (widget->objectName() == "FindFile"){
      widget->activateWindow();
      widget->setFocus();
      QApplication::restoreOverrideCursor();
      return;
    }
  }

  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QTextCursor f = o->my_sourcecodeeditor_editor->textCursor(); 
    sFindText = f.selectedText();
  } else {
    sFindText = "";
  }


  _findfile *ff = new _findfile(this); 
  ff->activateWindow();
  ff->setFocus();
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_EDIT_REPLACE_FILE()
{
  event_FILE_SAVE_ALL(true);

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  // be sure to make only one window visible
  foreach (QWidget *widget, QApplication::allWidgets()){
    if (widget->objectName() == "ReplaceFile"){
      widget->activateWindow();
      widget->setFocus();
      QApplication::restoreOverrideCursor();
      return;
    }
  }

  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QTextCursor f = o->my_sourcecodeeditor_editor->textCursor(); 
    sFindText = f.selectedText();
  } else {
    sFindText = "";
  }

  _replacefile *ff = new _replacefile(this);      
  QApplication::restoreOverrideCursor();
}






void _mainwindow::event_FILE_IMPORT_PROJECT()
{

  if (!bProject){
    QMessageBox::information( this, tr("Import File"),
      tr(
           "In order to import a file  you have to create a project first.\n"       
           "Inside a project all your files are listed."
           )
           );

    return;
  }

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _importproject *o = new _importproject(this);      
  o->show();
  qApp->setActiveWindow(o);
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_FILE_EXPORT_CSV()
{
  QString sTable = "";
  QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;
  _table *o = qobject_cast<_table *>(w);
  if (o){
    sTable = o->getFilenameWithoutPathAndExtension();
  } else {

    _tableviewer *o = qobject_cast<_tableviewer *>(w);
    if (o){
      sTable = getFilenameWithoutPathAndExtension(o->objectName());
    }

  }


  if (!sTable.isEmpty()){

    QString fn = QFileDialog::getSaveFileName(this);
     if (!fn.isEmpty()){

        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

         QString k = "";

          QSqlQuery r;
          QString s = "SELECT * FROM " + sTable;
          if (r.exec(s)){

              if (r.first()){

                QString sFields = "";            
                QSqlRecord a = r.record();

                int n = a.count();
                for (int i = 0; i < n; i++){
                  if (i > 0) sFields += ", ";
                  sFields += a.fieldName(i);                 
               }

                k += sFields;
#ifdef WINDOWS
                k += "\r\n"; // HIDE
#else
                k += "\n";
#endif

                do {
                  a = r.record();

                  QString sValues = "";

                  for (int i = 0; i < n; i++){
                    QVariant f = a.value(i);
                    QString value = f.toString();

                    switch(f.type()){
                      case QVariant::Bool:
                        if (value.isEmpty()) value = "";
                        break;
                      case QVariant::Date: 
                        if (value.isEmpty()) value = ""; else value = value;
                        break;
                      case QVariant::Time: 
                        if (value.isEmpty()) value = ""; else value = value;
                        break;
                      case QVariant::Double:
                        if (value.isEmpty()) value = ""; else value = value;
                        break;
                      case QVariant::Int:
                        if (value.isEmpty()) value = ""; else value = value;
                        break;
                      case QVariant::String: 
                        if (value.isEmpty()) value = ""; else value = "\"" + value + "\"";
                        break;
                      default:
                        if (value.isEmpty()) value = ""; else value = value;
                        break;
                    }

                    if (i > 0) sValues += ", ";
                    sValues += value;
                  }

                  k += sValues;
#ifdef WINDOWS
                  k += "\r\n"; // HIDE
#else
                  k += "\n";
#endif

                } while (r.next());
              }
            }

        QFile f(fn);
        if (!f.open(QIODevice::WriteOnly )){
          QApplication::restoreOverrideCursor();
          QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(fn));
          return;
        } else {
          QTextStream t(&f);
          
          t.setCodec("UTF-8");
          t.setAutoDetectUnicode(true);
          t.setGenerateByteOrderMark(true);

          t << k;
          f.close();
         }

        QApplication::restoreOverrideCursor();

        
   QMessageBox::information(this, tr("Export finished"),
    tr(
  "All needed data rows have been exported.<br>"
  )
  );

      }

  }
  EXTERN_my_parserwindow->refreshProject();

  
}

void _mainwindow::event_FILE_IMPORT_FILE()
{
  
  if (!bProject){
    QMessageBox::information( this, tr("Import File"),
      tr(
           "In order to import a file  you have to create a project first.\n"       
           "Inside a project all your files are listed."
           )
           );

    return;
  }
  QString fn = QFileDialog::getOpenFileName(this);
  if (!fn.isEmpty()){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _importproject *o = new _importproject(this);      
    QApplication::restoreOverrideCursor();

    if (fn.endsWith(".frm", Qt::CaseInsensitive)) o->importFrm(fn);
    else o->importBas(fn);    

    EXTERN_my_parserwindow->refreshProject();

  }
  
}

void _mainwindow::event_FILE_IMPORT_CSV()
{
  
  if (!bProject){
    QMessageBox::information( this, tr("Import CSV File"),
      tr(
           "In order to import a CSV file you have to create a project first.\n"       
           "Inside a project all your files are listed."
           )
           );

    return;
  }

  static bool bFirstTime = true;

  if (bFirstTime && isPreferenceSet("IntroductionHelp")){

    QMessageBox::information(this, tr("Import CSV"),
      tr(
    "You activated 'Import CSV', which makes KBasic "
    "to create a new database table description file (.kbasic_table) as well\n"
    "a real database table filled with the data from that text file."
    "\n\nIt is possible to import files with separator ',' or ';'.\n"
    )
    );

    bFirstTime = false;
  }

  QString fn = QFileDialog::getOpenFileName(this);
  if (!fn.isEmpty()){

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _importproject *o = new _importproject(this);      
    QApplication::restoreOverrideCursor();

    o->importCSV(fn);     
    EXTERN_my_parserwindow->refreshProject();

  }
  
}

void _mainwindow::event_PROJECT_DATABASE()
{
  if (bProject){
     QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    _dbcondialog *o = new _dbcondialog(this);
    QApplication::restoreOverrideCursor();
  }
  else QMessageBox::information(this, tr(MYAPP),
tr(
"Before you may configure the database settings,\n "
"you need to open a project first.\n"
));

}

void _mainwindow::event_PROJECT_TRANSLATION()
{
  EXTERN_my_mainwindow->event_FILE_SAVE_ALL(true);

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _translation *o = new _translation(this);
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_PROJECT_PROPERTIES_OF_PROJECT()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _projectproperties *o = new _projectproperties(this);
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_PROJECT_MAKE_RUNTIME_WINDOWS()
{

  if (getPreference("License").isEmpty()){

    QMessageBox::information(this, tr("Thanks for trying KBasic."), tr(
"This program is not free. It is an evaluation version of copyrighted software.\n"
"If you use it beyond the evaluation period, you are expected to register it\n"
"with KBasic Software. Please check www.kbasic.com for details.\n"
"\n"
"This trial version comes without the EXE builder.\n"
));
    return;

  }

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _compileproject *o = new _compileproject (this, true, false, false);
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_PROJECT_MAKE_RUNTIME_LINUX()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _compileproject *o = new _compileproject (this, false, true, false);
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_PROJECT_MAKE_RUNTIME_MACOS()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _compileproject *o = new _compileproject (this, false, false, true);
  QApplication::restoreOverrideCursor();
}

bool bSelfTest;

void _mainwindow::event_TOOLS_SELFTEST()
{  

QMessageBox::information(this, tr("Self Test"),
tr(
"The application is about to compile every example program shipped. "
"Each program should compile without errors.\n\n"
"If not, please report to bugs@kbasic.com. Thanks. ")
);


    bSelfTest = true; 

   if (!selfTest(kbasicPath("examples/kbasic"))){

   }
   bSelfTest = false; 
}

void _mainwindow::event_HELP_KBASIC_BOOK()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  QDesktopServices::openUrl(QUrl("http://www.kbasic.com/doku.php?id=manual"));
  QApplication::restoreOverrideCursor();

}

_resources *my_resources = 0;
void _mainwindow::event_TOOLS_RESOURCES()
{
  if (EXTERN_my_mainwindow->isProject()){
    if (my_resources == 0) my_resources = new _resources(this); else 
    {
      QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
      my_resources->show();
      qApp->setActiveWindow(my_resources);
      QApplication::restoreOverrideCursor();
    }
  } else {
    QMessageBox::information(this, tr("Resources"),
        tr(
      "Resources are available only, if you open a project."
      )
      );
  }
}

void _mainwindow::event_FILE_PREFERENCES()
{
 // QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _preferences *o = new _preferences(this);
//  QApplication::restoreOverrideCursor();
}

 void _mainwindow::event_FILE_PRINT()
 {
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    QTextDocument *document = o->my_sourcecodeeditor_editor->document();
    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Print Document"));
    QApplication::restoreOverrideCursor();
    if (dialog->exec() != QDialog::Accepted)
        return;

    document->print(&printer);
  }
 }

void _mainwindow::event_EXAMPLE_BROWSER()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _examplebrowser *o = new _examplebrowser(this);
  QApplication::restoreOverrideCursor();
}
 
void _mainwindow::event_HELP_OFFLINE_DESCRIPTION()
{
  QDesktopServices::openUrl(QUrl("file:///" + kbasicPath("docs/description.pdf")));
}

void _mainwindow::event_HELP_OFFLINE_FRAMEWORK()
{
  QDesktopServices::openUrl(QUrl("file:///" + kbasicPath("docs/framework.pdf")));
}

void _mainwindow::event_HELP_OFFLINE_OVERVIEW() 
{
  QDesktopServices::openUrl(QUrl("file:///" + kbasicPath("docs/overview.pdf")));
}

void _mainwindow::event_HELP_OFFLINE_KEYWORDS()
{
  QDesktopServices::openUrl(QUrl("file:///" + kbasicPath("docs/keywords.pdf")));
}

void _mainwindow::event_HELP_OFFLINE_BUILTINS()
{
  QDesktopServices::openUrl(QUrl("file:///" + kbasicPath("docs/builtins.pdf")));
}

void _mainwindow::event_HELP_OFFLINE_MANUAL()
{
  QDesktopServices::openUrl(QUrl("file:///" + kbasicPath("docs/manual.pdf")));
}

void _mainwindow::event_HELP_OFFLINE_SYNTAX()
{
  QDesktopServices::openUrl(QUrl("file:///" + kbasicPath("docs/syntax.pdf")));
}

void _mainwindow::event_HELP_OFFLINE_MISC()
{
  QDesktopServices::openUrl(QUrl("file:///" + kbasicPath("docs/misc.pdf")));
}

void _mainwindow::event_HELP_WEBSITE()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  QDesktopServices::openUrl(QUrl("http://www.kbasic.com/"));
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_HELP_FRAMEWORK()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  QDesktopServices::openUrl(QUrl("http://www.kbasic.com/doku.php?id=framework"));
  QApplication::restoreOverrideCursor();
//  _help_syntax *h = new _help_syntax(this, kbasicPath("docs/syntax/home.html"), QUrl(""));  
}

void _mainwindow::event_HELP_SYNTAX()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  QDesktopServices::openUrl(QUrl("http://www.kbasic.com/doku.php?id=syntax"));
  QApplication::restoreOverrideCursor();
//  _help_syntax *h = new _help_syntax(this, kbasicPath("docs/syntax/home.html"), QUrl(""));  
}

void _mainwindow::event_HELP_KBASIC_BUG()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _help *h = new _help(this, kbasicPath("docs/bugreport/home.html"), 540, 354);  
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_HELP_KBASIC_CONTRIBUTE()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  QDesktopServices::openUrl(QUrl("http://www.kbasic.com/doku.php?id=kde#contribute"));
  QApplication::restoreOverrideCursor();
}

void _mainwindow::event_HELP_ABOUT()
{
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  _help *h = new _help(this, kbasicPath("docs/aboutkbasic_professional/index.html"), 540, 354);  
  QApplication::restoreOverrideCursor();
}


void _mainwindow::event_RUN_RUN()
{
  static bool bFirstTime = true;

  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("Start"),
      tr(
    "The application is about to execute your program, but before that you should know, that "
    "when you have written something wrong like missing a dot or a quotation mark, "
    "The application will show you an error (a syntax error or semantic error) and stops the execution.\n\n"
    "If you would like to know what is happening behind, watch the 'Virtual Machine Info' while "
    "your KBasic program is executed. There you can find information about the three "
    "different executions steps.\n"
    "\n"
    "Now, let's execute your program...\n"
    )
    );

    bFirstTime = false;
  }      

  runRun(!isPreferenceSet("ConsoleInfo"), false, false, true); 
}

bool _mainwindow::event_RUN_BUILD()
{
  bool b = runRun(true, false, false, true, false, true); 
  return b;
}

bool _mainwindow::event_RUN_BUILD_ALL()
{
  bool b = runRun(false, false, false, false, false, true); 
  return b;
}

void _mainwindow::event_RUN_SUB()
{  

  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){

      QString s = o->getCurrentLineAsString();
      
      int n = 0;
      int k = 0;

      s = s.simplified();

      n = s.lastIndexOf("Function", -1, Qt::CaseInsensitive);
      int n2 = s.lastIndexOf("Sub", -1, Qt::CaseInsensitive);
      int n3 = 0;
      int j = 0;

      if (n2 != -1 && n2 > n){
        n3 = n2 + 1;
        j = 3;
      } else if (n != -1){
        n3 = n + 1;
        j = 8;
      } else {
        return;
      }
      s = s.mid(n3);

      n = s.length();
      n2 = s.indexOf(" ", j);
      if (n2 != -1){
        n3 = n2;
      } else if (n != -1){
        n3 = n;
      } else {
        return;
      }
      s = s.mid(j, n3 - j - 1);
      s = s.replace("(", "");
      s = s.replace(")", "");

      if (s.length()){
        runRun(!isPreferenceSet("ConsoleInfo"), false, false, true, false, false, s); 
      }

    }
  
}

void _mainwindow::event_RUN_FORM()
{
  _form *f = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (f){
    runRun(!isPreferenceSet("ConsoleInfo"), false, false, true, true, false); 
  }

  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o && o->getFilename().endsWith(".kbasic_form", Qt::CaseInsensitive)){
    runRun(!isPreferenceSet("ConsoleInfo"), false, false, true, true, false); 
  }
}

void _mainwindow::event_RUN_RUN_IN_DEBUG()
{ 
  static bool bFirstTime = true;
  
  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("Run In Debug"),
      tr(
    "The application is about to debug your program, but before you should know, that "
    "when you have written something wrong like missing a dot or a quotation mark, "
    "The application will show you the error (a syntax error or semantic error) and stops debugging.\n"
    "\n"
    "Debugging means that KBasic allows you to follow the execution of your program "
    "line by line. Additionally, you can watch the variable of your program, "
    "which let you read its values.\n"
    "\n"
    "Let's debug your program...\n"
    )
    );

    bFirstTime = false;
  }  

  runRun(true/*!isPreferenceSet("ConsoleInfo")*/, true, false, true); 
}

void _mainwindow::event_RUN_RUN_IN_DEBUG2()
{
  static bool bFirstTime = true;

  if (bFirstTime && isPreferenceSet("IntroductionHelp")){
    QMessageBox::information(this, tr("Run In Debug"),
      tr(
    "The application is about to debug your program, but before you should know, that "
    "when you have written something wrong like missing a dot or a quotation mark, "
    "The application will show you the error (a syntax error or semantic error) and stops debugging.\n"
    "\n"
    "Debugging means that KBasic allows you to follow the execution of your program "
    "line by line. Additionally, you can watch the variable of your program, "
    "which let you read its values.\n"
    "\n"
    "Let's debug your program...\n"
    )
    );

    bFirstTime = false;
  }  

  runRun(true/*!isPreferenceSet("ConsoleInfo")*/, true, true, true);
}

void _mainwindow::event_RUN_STOP()
{
 
  if (my_compile){
    my_compile->terminate();
    QFile f(idePath("stopinterpret"));
    if (f.open(QIODevice::WriteOnly)) f.close();
    my_compile->waitForFinished(250);
    delete my_compile;
    QFile::remove(idePath("stopinterpret"));
    
    my_compile = 0;
  }

     if (bDebugging){
      EXTERN_Me->setHidden(true);
      EXTERN_Local->setHidden(true);
      EXTERN_Global->setHidden(true);
      EXTERN_Stack->setHidden(true);
    
      delete myInterpreter;
      myInterpreter = 0;
    }

    bRunning = false;
    bDebugging = false;
    bCompiling = false;


    updateRunActions();


    
}

void _mainwindow::event_RUN_CONTINUE_PCODE()
{
  if (myInterpreter) myInterpreter->interpretContinue();  
}

void _mainwindow::event_RUN_SINGLE_STEP()
{
  if (myInterpreter) myInterpreter->interpretStepIn();  
}

void _mainwindow::event_RUN_STEP_OVER()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o){
    if (myInterpreter) myInterpreter->interpretStepOver(o->getFilename(), o->getCurrentLine());
  }

}

void _mainwindow::event_RUN_STEP_OUT()
{
  if (myInterpreter) myInterpreter->interpretStepOut();
}

void _mainwindow::event_RUN_TO_CURSOR()
{
  _sourcecodeeditor *o = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (o && this->bDebugging){
    if (myInterpreter) myInterpreter->interpretRunToCursor(o->getFilename(), o->getCurrentLine());
  }
}

void _mainwindow::event_RUN_RUN_PCODE()
{  
  runRun(false, false, false, true);
}

void _mainwindow::event_RUN_RUN_PCODE2()
{  
  runRun(true, false, false, true);
}

void _mainwindow::event_RUN_RUN_PROJECT()
{  
  runRun(true, false, false, true, false, false, "", "", true);
}

void _mainwindow::event_RUN_RUN_PCODE3()
{  
  runRun(false, true, false, true);

 
}


bool _mainwindow::runRun(bool bSilent, bool bDebug, bool bDebugAtBeginning, bool bUseCache, bool bCurrentForm, bool bBuildOnly, QString sCurrentSub, QString sRunString, bool bAlwaysRunProject)
{
  if (bRunning) return false;
 // bUseCache = bUseCache;

  _sourcecodeeditor *s = qobject_cast<_sourcecodeeditor *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (s){
    event_FILE_SAVE();
    if (s->windowTitle().endsWith("*")){
      QMessageBox::information(this, MYAPP, tr("Could not run, because current source file is not saved.\n"));
      return false;
    }
  }
  //bSilent = !bSilent;

  bRunning = true; 
  bDebugging = bDebug | bDebugAtBeginning;
  //bSilent = bDebugging ? false : bSilent;
  
  updateRunActions();
  if (bDebugging){
    statusBar()->showMessage(tr("Debugging..."));
  } else if (!bBuildOnly){
    statusBar()->showMessage(tr("Running..."));
  } else {
    statusBar()->showMessage(tr("Compiling..."));
  }
  
  oPercentInfo->show();
  statusBar()->setHidden(false);
  qApp->processEvents(); // udpate the change of the statusbar on screen

  QString trans = "";
  QString sql = "";
  QString menu = "";
  QStringList arguments;

#ifdef WINDOWS
  QString program = kbcPath("kbc.exe"); // HIDE
#else
  QString program = kbcPath("kbc");
#endif

  my_infoconsole->reset();

  // *** close opened screen
  foreach (QWidget *w, QApplication::allWidgets()){
    if (w->objectName() == "Console"){
      w->hide();
      w->close();
      qApp->processEvents();
      break;
    }
  }
  // ***
  QThread *th = 0;
  bool isFocusSourceCodeEditor = s ? true : false;
  bool bRunIt = false;


  bool bReturn = false;
  bUseCache = bUseCache & true;//isPreferenceSet("CachedCompilation");

  if (bUseCache == false){

  }


  QFile::remove(cachePath("default.kbasic"));
  QFile::remove(cachePath("default2.kbasic"));

  // five different ways to execute
  // 1. run form in form design mode
  // 2. run form in source code mode
  // 3. run entirely project, when opening project in function main() or formname
  // 4. run whole file
  // 5. run string containing source code

  bool bRunProject = false;
  bool bRunForm = bCurrentForm;
  bool bRunFile = false;
  bool bRunString = !sRunString.isEmpty();
  bool isFocusForm = qobject_cast<_form *>(workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0);
  if (s && s->getFilename().endsWith(".kbasic_form", Qt::CaseInsensitive)) isFocusForm = true;

  bool bMenuBar = true;
  //bool bToolBar = true;
  bool bAlreadyBuilt = false;

  QString sTargetPath = "";
  

  QString sName = "";
  if (s){
    sName = s->getFilename();
  }
  QStringList trl = EXTERN_my_mainwindow->getProjectPreference("Translation").split(";");

  QString sProjectMainFormName = "";
  QString sDefault = "";    
  QString sDefault2 = "";    
  QString sFiles = "";    
  QString sAllFiles = "";   
  QString sForms = "";
  QString sMenuBarItems = "";
  QString sToolBarItems = "";

  EXTERN_sError = "";

  bool bbdbsettablesforruntime = false;

  QString ss = "";
  
   oPercentInfo->setValue(5);
  event_FILE_SAVE_ALL(true);

  // run entirely project, when opening project in function main() or formname
  if ((bProject && ((isFileInProject(sName) || sName.endsWith("default.kbasic", Qt::CaseInsensitive) || sName.endsWith("default2.kbasic", Qt::CaseInsensitive)) || (sName.isEmpty() && !isFocusForm)))){
    
    bRunProject = true;

    sProjectMainFormName = getProjectPreference("projectmainformname").simplified();

    if (!sProjectMainFormName.contains("Function Main()", Qt::CaseInsensitive) && !QFile::exists(this->getProjectPath() + "/" + sProjectMainFormName + ".kbasic_form")){
      QMessageBox::information(this, tr("Project's Main Form Name"),
        tr(
      "Something with your project property 'Project's Main Form Name' is wrong.\n"
      "There is no form named as set in the project properties.\n"
      )
      );
      goto retfalse;
    }

    // critical hint
    if (sProjectMainFormName.isEmpty() && bProject){
      QMessageBox::information(this, tr("Project's Main Form Name"),
        tr(
      "Something with your project property 'Project's Main Form Name' is wrong.\n"
      "You do not have typed in a proper form name or the main function:\n"
      "Try to create a function named 'Function Main()' in which you call "
      "the initial code of your program. Check the project property window for details.\n\n If no project is opened, you cannot run a form."
      )
      );
      goto retfalse;
    }

goto rr;
  // run form in form design mode
  } else if (isFocusForm && bProject){
    bRunForm = true;
    //event_FILE_SAVE_ALL(true);
rr:
    bool bFirst = true;
    bool bFirst2 = true;
    
    sName = "";
    if (EXTERN_my_mainwindow->isProject()){
      sName = first();
    } else {

    // critical hint
      QMessageBox::information(this, tr("Current Form"),
        tr(
     "If no project is opened, you cannot run a form. "
     )
      );
    
       QMessageBox::information(this, MYAPP, tr("Running a form outside of project is not allowed"));

    }
    QString sDefault = "";
    QString sDefault2 = "";

    if (sName.length()){

      sDefault.append("' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
      sDefault.append("\n\n");
      sDefault.append("Option KBasic\n"); // needed for attaching forms::init() to code
      sDefault.append("Dim Err As New Err2");
      sDefault.append("\n");              
      sDefault.append("\n' --- End: Inserted by KBasic Atelier automatically  ---\n");

      do {
        processGUI();     


        if (sName.endsWith(".kbasic_translation", Qt::CaseInsensitive)){
          sAllFiles += sName;
          sAllFiles += "\n";
        } else if (sName.endsWith(".kbasic_table", Qt::CaseInsensitive)){
          sAllFiles += sName;
          sAllFiles += "\n";
        } else if (sName.endsWith(".kbasic_query", Qt::CaseInsensitive)){
          sAllFiles += sName;
          sAllFiles += "\n";
        } else {
          if (sName.endsWith(".kbasic_form", Qt::CaseInsensitive)){

            bool bAddForm = true;

            {
              QString sExt = EXTERN_my_mainwindow->getFilenameExtension(sName);
              QString q = sName.left(sName.length() - sExt.length() - 1);

              if (q.count(".") > 1){

                QString sLanguage = getFilenameExtension(q);
                if (trl.contains(sLanguage)){        
                   bAddForm = false;
                }
              }
            }

            if (bAddForm){
              QString g = this->getFilenameWithoutPathAndExtension(sName);
              sForms += "Dim " + g + " As " + g + "\n";
            }
          }
          sAllFiles += sName;
          sAllFiles += "\n";
        }

        if (sName.endsWith(".kbasic_class", Qt::CaseInsensitive) || sName.endsWith(".kbasic_module", Qt::CaseInsensitive) || sName.endsWith(".kbasic", Qt::CaseInsensitive)){

          if (
            sName.endsWith("/myEvent.kbasic_class", Qt::CaseInsensitive)
            || sName.endsWith("/myEvent.kbasic_class", Qt::CaseInsensitive))
          {
            QString e;
            e.append("\n\n' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
            e.append("Dim kbEvent As New myEvent()\n");
            e.append("\n\n' --- End: Inserted by KBasic Atelier automatically  ---\n");
            sDefault.prepend(e);
          }

          sFiles += sName;
          sFiles += "\n";

        } else if (sName.endsWith(".kbasic_report", Qt::CaseInsensitive)){
          
          sFiles += sName;
          sFiles += "\n";

        } else if (sName.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){

          if (bMenuBar){
            sMenuBarItems.append("\nDim MenuBarItem0 As MenuBarItem\n");
            sMenuBarItems += _menubar::getMenuBarItems(sName);
            sDefault.prepend("\n");

            sDefault.prepend(sMenuBarItems);              

            bMenuBar = false;
            QString s = "";
            s.append("\n\n' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
            s.append("\n\nDim kbMenuBar As New ");
            s.append(getFilenameWithoutPathAndExtension(sName));                           
            s.append("\n\n' --- End: Inserted by KBasic Atelier automatically  ---\n");
            sDefault.prepend(s);
          }                   

          sFiles += sName;
          sFiles += "\n";

        } else if (sName.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){
          
          
          {
            if (getFilenameWithoutPathAndExtension(sName).toLower() == "mytoolbar"){
              sToolBarItems = _toolbar::getToolBarItems(sName);
              sDefault.prepend("\n");
              sDefault.prepend(sToolBarItems);              

              QString s = "";
              s.append("\n\n' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
              s.append("\n\nDim kbToolBar As New ");
              s.append(getFilenameWithoutPathAndExtension(sName));                           
              s.append("\n\n' --- End: Inserted by KBasic Atelier automatically  ---\n");
              sDefault.prepend(s);
            }
          }                

          sFiles += sName;
          sFiles += "\n";

        } else if (sName.endsWith(".kbasic_form", Qt::CaseInsensitive)){
          
          sFiles += sName;
          sFiles += "\n";

          if (bRunForm){

            QWidget *w = workspace->activeSubWindow() ? workspace->activeSubWindow()->widget() : 0;

            _form *f = qobject_cast<_form *>(w);

            if (f && f->getFilename() == sName){
            
              sDefault2.append("\n\n' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
              sDefault2.append("\nDim kbCurrentForm As New ");
              sDefault2.append(f->getFilenameWithoutPathAndExtension());             
              sDefault2.append(
                "\n\n"
                "kbCurrentForm.Open()\n"
                );
              sDefault2.append("Application.Run()\n");
              sDefault2.append("\n' --- End: Inserted by KBasic Atelier automatically  ---\n");
            }

          }

        } else {
          goto o;
        }

        if (bFirst2 && bRunString){
          bFirst2 = false;

          sDefault2.append("\n\n' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
          sDefault2.append("\n");
          sDefault2.append(sRunString);
          sDefault2.append("\n");
          sDefault2.append("\n' --- End: Inserted by KBasic Atelier automatically  ---\n");

        } else if (bFirst2 && bRunProject && (sProjectMainFormName.contains("Function ", Qt::CaseInsensitive) || sProjectMainFormName.contains("Sub ", Qt::CaseInsensitive) || sCurrentSub.length())){
          sProjectMainFormName = sProjectMainFormName.replace("Function ", "", Qt::CaseInsensitive);
          sProjectMainFormName = sProjectMainFormName.replace("Sub ", "", Qt::CaseInsensitive);

          bFirst2 = false;
          sDefault2.append("\n\n' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
          sDefault2.append("\n\n");
          if (sCurrentSub.length()){
            sDefault2.append(sCurrentSub);
          } else {
            sDefault2.append(sProjectMainFormName);
          }
          sDefault2.append("\n");              
          sDefault2.append("\n' --- End: Inserted by KBasic Atelier automatically  ---\n");
        } else if (bFirst2 && bRunProject){

          bFirst2 = false;
          sDefault2.append("\n\n' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
          sDefault2.append("\n\n");

          sDefault2.append(sProjectMainFormName);
          sDefault2.append(" = New ");
          sDefault2.append(sProjectMainFormName);
          sDefault2.append("\n");
          sDefault2.append(sProjectMainFormName);
          sDefault2.append(".Open()\n\n");

          sDefault2.append("Application.Run()\n");
          sDefault2.append("\n");              
          sDefault2.append("\n' --- End: Inserted by KBasic Atelier automatically  ---\n");             

        }

                   
o:
        sName = next();

      } while (sName.length());     

      sDefault.prepend("\n' --- End: Inserted by KBasic Atelier automatically  ---\n");
      sDefault.prepend("\n");              
      sDefault.prepend(sForms);              
      sDefault.prepend("\n");              
      sDefault.prepend("' --- Begin: Inserted by KBasic Atelier automatically  ---\n");

      saveStringInFile(cachePath("default.kbasic"), sDefault);
      saveStringInFile(cachePath("default2.kbasic"), sDefault2);

    } 
   
  // run whole file
  } else if (isFocusSourceCodeEditor){
    event_FILE_SAVE();
    bRunFile = true;

    sDefault.append("' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
    sDefault.append("\n\n");
    sDefault.append("Option KBasic\n"); // needed for attaching forms::init() to code
    sDefault.append("Dim Err As New Err2");
    sDefault.append("\n");              
    sDefault.append("\n' --- End: Inserted by KBasic Atelier automatically  ---\n");

    if (sCurrentSub.length()){
      sDefault2.append("\n\n' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
      sDefault2.append("\n\n");
      sDefault2.append(sCurrentSub);
      sDefault2.append("() ' run current sub \n");              
      sDefault2.append("\n' --- End: Inserted by KBasic Atelier automatically  ---\n");
    }

    if (bRunString){

      sDefault2.append("\n\n' --- Begin: Inserted by KBasic Atelier automatically  ---\n");
      sDefault2.append(sRunString);
      sDefault2.append("\n' --- End: Inserted by KBasic Atelier automatically  ---\n");
    }
    sFiles += s->getFilename();

    //sSource.append(s->my_sourcecodeeditor_editor->toPlainText());

    saveStringInFile(cachePath("default.kbasic"), sDefault);
    saveStringInFile(cachePath("default2.kbasic"), sDefault2);

    //#saveStringInFile(cachePath(getFilenameWithoutPathAndExtension(s->getFilename()) + ".compiler"), sSource);    

  }


  if (bRunProject && getProjectPreference("projecttype").contains("MDI", Qt::CaseInsensitive)){
    bool bNoMenuBar = !sAllFiles.contains("myMenuBar.kbasic_menubar");
    if (bNoMenuBar){
      if (QMessageBox::question(this, tr(MYAPP),      
        tr("To run a MDI application, you need a MenuBar. Would you like to add a MenuBar now?"),    
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
      {
        event_FILE_NEW_MENUBAR();      
      }
      goto retfalse;
    }    
  }

  oPercentInfo->setValue(15);

  QFile::remove(cachePath("compiler.output"));

  QFile::remove(cachePath("compiler.input"));
  saveStringInFile(cachePath("compiler.input"), sFiles);

  QFile::remove(cachePath("project.files"));
  saveStringInFile(cachePath("project.files"), sAllFiles);
  if (QFile::exists(cachePath("target.path"))) loadStringFromFile(cachePath("target.path"), sTargetPath);


  if (bProject && (sTargetPath != getProjectPath() || bBuildOnly)){
    sTargetPath = getProjectPath();
    saveStringInFile(cachePath("target.path"), sTargetPath);
  } else if (bRunFile && (sTargetPath != s->getFilename() || bBuildOnly)){
    sTargetPath = s->getFilename();
    saveStringInFile(cachePath("target.path"), sTargetPath);
  } else {

    bAlreadyBuilt = !sAllFiles.isEmpty();

    QStringList lAllFiles = sAllFiles.split("\n");
    foreach(QString w, lAllFiles){
      QFileInfo info(w);
      QFileInfo info2(cachePath("runtime.pcode"));
      if (info.lastModified() > info2.lastModified()){
        bAlreadyBuilt = false;
        break;
      }
    }
    if (bAlreadyBuilt){
      goto gAlreadbuilt;   
    }
  }
  
  if (bDebug){ // write breakpoints in file for compiler
    QFile f(cachePath("compiler.breakpoints"));
    if (f.open(QFile::Truncate | QFile::WriteOnly)){
      foreach(_breakpoint b, breakpoints){
        if (!f.write(b.sFile.toAscii())) break;
        if (!f.write("|")) break;
        int n = 0;
        if (
          b.sFile.endsWith(".kbasic_form", Qt::CaseInsensitive) 
          || b.sFile.endsWith(".kbasic_report", Qt::CaseInsensitive) 
          || b.sFile.endsWith(".kbasic_menubar", Qt::CaseInsensitive) 
          || b.sFile.endsWith(".kbasic_toolbar", Qt::CaseInsensitive) 
          ) n = 1; // set the correct line numbers for sources extended by the compiler
        
        QString s = QString("%1").arg(b.nLine + n);
        if (!f.write(s.toAscii())) break;
        if (!f.write("\n")) break;
      }
    }
  }

  if (my_compile){ 
    my_compile->terminate();
    my_compile->waitForFinished(1000);
    delete my_compile; 
    my_compile = 0; 
  }
  my_compile = new _compile(this);


  if (bRunProject){
    trans = getProjectPreference("Translation");
   
    if (EXTERN_my_mainwindow->getProjectPreference("dbsetforruntime") == "Yes"){
      sql += getProjectPreference("dbdriver"); sql += ";";
      sql += getProjectPreference("dbhost"); sql += ";";

      bool bSQLite = false;
      if (CurrentDatabase.driverName().contains("sqlite", Qt::CaseInsensitive)){
        bSQLite = true;
      }

      if (bSQLite){
        QString q = getProjectPreference("dbname");
        if (q.startsWith("./")){
          q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + q.mid(1);
        } else if (q.startsWith("../")){
          q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + q.mid(2);
        }
//        QString q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + "/sqlite/" + getProjectPreference("dbname");
        sql += q; sql += ";";
      } else {
        sql += getProjectPreference("dbname"); sql += ";";      
      }
      
      sql += getProjectPreference("dbuser"); sql += ";";
      sql += getProjectPreference("dbuserpassword"); sql += ";";
      sql += getProjectPreference("dbconnectoptions"); sql += ";";
      sql += getProjectPreference("dbport"); sql += ";";
      sql += getProjectPreference("dbsettablesforruntime"); sql += ";";

      QString sName = first();
      if (sName.length()){
        do {
          if (sName.endsWith(".kbasic_table", Qt::CaseInsensitive)){
            sql += this->getFilenameWithoutPathAndExtension(sName);
            sql += "|";
            if (getProjectPreference("dbsettablesforruntime") == "Yes"){
              bbdbsettablesforruntime = true;
            }
          }
          sName = next();
        } while (sName.length());  
        sql += ";";
      }

      //QStringList l = CurrentDatabase.tables();
      //sql += l.join("|"); sql += ";";

    }

    menu += getProjectPreference("menuRecords"); menu += ";";
    menu += getProjectPreference("menuWindow"); menu += ";";
    menu += getProjectPreference("menuHelp"); menu += ";";
  }

  if (bSilent) arguments << "-Silent";
  if (bDebug) arguments << "-Debug";
  if (bUseCache) arguments << "-UseCache";
  arguments << "-License" + getPreference("License");


  QFile::remove(cachePath("project.name"));
  if (bRunProject){
    saveStringInFile(cachePath("project.name"), getProjectPreference("projectname"));

     arguments << "-ProjectType" + getProjectPreference("projecttype");    
    arguments << "-Login" + getProjectPreference("login");
    arguments << "-Translation" + trans;
    arguments << "-SQL" + sql;
    arguments << "-Menu" + menu;
  }


  oPercentInfo->setValue(20);

  QFile::remove(cachePath("compiler.done"));
  QFile::remove(cachePath("runtime.pcode"));

  my_compile->start(program, arguments, QIODevice::ReadWrite | QIODevice::Unbuffered);

  if (!my_compile->waitForStarted()){
    QMessageBox::information(this, MYAPP, tr("Could not launch the KBasic compiler (kbc).\n"));
    QMessageBox::information(this, MYAPP, program);
    goto retfalse; 
  }

  th = QThread::currentThread();
  th->setPriority(QThread::LowestPriority);

  while (my_compile/* && my_compile->isOpen()*/){
    
    if (QFile::exists(cachePath("compiler.done"))){

      th->setPriority(QThread::NormalPriority);

      QFile::remove(cachePath("compiler.done"));
      if (my_compile) my_compile->close();
      goto we;
    }
    qApp->processEvents();
  }

  th->setPriority(QThread::NormalPriority);

  if (my_compile && my_compile->exitCode() == 0){
gAlreadbuilt:
    if (my_compile == 0) my_compile = new _compile(this);
we:

    if (QFile::exists(cachePath("runtime.pcode"))){

      bRunIt = true;
      oPercentInfo->setValue(100);
      if (bBuildOnly) goto rettrue;


    //QMessageBox::information(0, "The application Software", "22222");

      QFile::remove(idePath("screen.png"));

      bool bCalledByIDE = true;

  #ifdef WINDOWS
    QString program = runPath("kbrun.exe"); // HIDE
  #else
    QString program = runPath("kbrun");
  #endif
      
      QStringList arguments;
      if (bSilent) arguments << "-Silent";
      if (bDebug) arguments << "-Debug";
      if (bDebugAtBeginning) arguments << "-DebugAtBeginning";
      if (bCalledByIDE) arguments << "-CalledByIDE";    
      arguments << cachePath("runtime.pcode");

      //QMessageBox::information(0, "The application Software", program);
/*
      // copy sqlite to the path where kbrun is
      ss = getProjectPreference("dbdriver");
      if (!ss.isEmpty()){
        bool bSQLite = false;
        if (CurrentDatabase.driverName().contains("sqlite", Qt::CaseInsensitive)){
          bSQLite = true;
        }

        if (bSQLite){
          QString q = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + "/" + getProjectPreference("dbname");
          EXTERN_my_mainwindow->statusBar()->showMessage(tr("Copying sqlite database to the path of runtime..."));
          if (!copyFile(q, runPath(getProjectPreference("dbname")))){
            EXTERN_sError = "Could not copy sqlite file to the path of runtime (kbrun)";
            goto retfalse;
          }
        }
      }*/
      EXTERN_my_mainwindow->statusBar()->showMessage(tr("Running..."));

      my_compile->start(program, arguments, QIODevice::ReadWrite | QIODevice::Unbuffered);

      if (bDebug || bDebugAtBeginning){
        myInterpreter = new interpreter(my_compile);

        EXTERN_Me->setHidden(false);
        EXTERN_Local->setHidden(false);
        EXTERN_Global->setHidden(false);
        EXTERN_Stack->setHidden(false);
      }

      if (!my_compile->waitForStarted()){
        QMessageBox::information(this, MYAPP, tr("Could not launch the KBasic runtime (kbrun).\n"));
        QMessageBox::information(this, MYAPP, program);
        goto retfalse; 
      }


#ifdef MAC
    while(my_compile->pid() <= 0){
    }
   ProcessSerialNumber psn;
        OSStatus st;
        do {
          st = GetProcessForPID(my_compile->pid(), &psn);
        } while (st == -600);
        
      //  QMessageBox::information(this, "st", QString("my_compile->pid() %1").arg(my_compile->pid()));
     //  QMessageBox::information(this, "st", QString("%1").arg(st));
  if (st >=0 ){
  SetFrontProcess(&psn);
}
#endif


      while (my_compile && my_compile->isOpen()){
        qApp->processEvents(QEventLoop::WaitForMoreEvents);
      }

      if (my_compile && my_compile->exitCode() == 0){
        goto rettrue;
      }
      if (my_compile && bRunIt) QMessageBox::information(this, MYAPP, tr("Unknow exception in KBasic runtime (kbrun).\n"));

    }
    

  }

  

 
retfalse:
  
  oPercentInfo->hide();
  oPercentInfo->setValue(0);
  if (EXTERN_sError.isEmpty()){
    statusBar()->setHidden(true);
  } else {
    statusBar()->setHidden(false);
    statusBar()->showMessage(EXTERN_sError);
  }
  event_RUN_STOP();

  if (bbdbsettablesforruntime) EXTERN_my_projectwindow->refresh(); // maybe the runtime created non-existing tables

  return false;
rettrue:
  oPercentInfo->setValue(0);
  statusBar()->setHidden(true);
  event_RUN_STOP();
  bRunning = false; updateRunActions();
  if (bBuildOnly == false && QFile::exists(idePath("screen.png"))) event_VIEW_KONSOLE();
  
  if (bbdbsettablesforruntime) EXTERN_my_projectwindow->refresh(); // maybe the runtime created non-existing tables

  return true;



  
  return bReturn;

}

void _mainwindow::closeAllWindows()
{
  
  workspace->closeAllSubWindows();
}
