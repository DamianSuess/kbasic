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

#ifndef _mainwindow_H
#define _mainwindow_H



#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QTreeWidgetItem>
#include <QFileSystemWatcher>



#include <QMap>


class QComboBox;
class QApplication;
class QSplashScreen;
class QListWidget;
class QAction;
class QMenu;
class QMdiArea;
class QSignalMapper;
class QString;
class QLabel;
class QProgressBar;
class QPushButton;
class QMdiSubWindow;



class _inputtip_info;


class _compile;

class _sourcecodeeditor;
class _table;
class _tableviewer;
class _qbe;
class _form;
class _report;
class _menubar;
class _toolbar;

class _toolboxwindow_form;
class _toolboxwindow_vista;
class _projectwindow;

class _screen;
class _infoconsole;
class _log;

class _mainwindow;
extern _mainwindow *EXTERN_my_mainwindow;

class interpreter;



extern QString kbasicPath(QString sPath);

class _mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    _mainwindow(QApplication *app, QSplashScreen *splash, bool _bRuntime = false);
    ~_mainwindow();

    void loadDefaultFiles();

    void performInsertTextInSourceCode(QString s);

    QMdiArea *workspace;
    QSignalMapper *projectlistMapper;

    QString getForF1(QString sDot, QString sDot2);
    bool showError(QString _sFile, int _nLine, QString _sError);
    bool showDebug(QString _sFile, int _nLine);
    void gotoFileLine(QString sFile, int nLine);

    bool saveStringInFile(QString sFile, QString s);
    bool loadStringFromFile(QString sFile, QString &s);

    bool ci_bUpdatedAs;
    bool ci_bUpdatedDot;
    bool ci_bUpdatedDotMethod;


    static QString locale();

    
    bool isPreferenceSet(QString s);
    QString getPreference(QString sKey);
    void setPreference(QString sKey, QString sValue);
    void setDefaultPreferences();

    QString getProjectPreference(QString sKey);
    void setProjectPreference(QString sKey, QString sValue);

    bool isCompiling(){ return bCompiling; }
    bool isRunning(){ return bRunning; }
    bool isDebugging(){ return bDebugging; }
    bool isProject(){ return bProject; }

    void updateRunActions();
    void updateGeneralActions(
      bool bMainWindow, bool bForm, bool bReport, bool bProjectWindow, 
  bool bQuery, bool bSourceCodeEditor, bool bTable, bool bMenuBar, bool bToolBar, 
  
  bool bShowFocusOrder, bool bShowSQLSettings, bool bShowSQLTables, 
  bool bCanCopy, bool bCanPaste, bool bCanRedo, bool bCanUndo, 
  bool bIsFormClassSourceCode, QString sFileName
  );

    QMap<QString, QString> preferences;
    QMap<QString, QString> projectPreferences;

    bool runRun(bool bSilent, bool bDebug, bool bDebugAtBeginning, bool bUseCache, bool bCurrentForm = false, bool bBuildOnly = false, QString sCurrentSub = "", QString sRunString = "", bool bAlwaysRunProject = false);

    void updateBreakpointsByEditor();

protected:
    void closeEvent(QCloseEvent *event);

public slots:  
    void TRANSLATION_currentIndexChanged  ( const QString & text ) ;
    
    void trayIcon_activated();
    void statusbar_messageChanged(const QString & message);

    void directoryChanged(const QString &s);
    void fileChanged(const QString &s);
    

    void subWindowActivated(QMdiSubWindow *w);    
    void setActiveSubWindow(QWidget *window);

    void event_FILE_SET_AS_DEFAULT();
    void event_PROJECT_SET_AS_DEFAULT();

    void event_PROJECTLIST();
    void event_FILE_NEW_PROJECT();
    void event_FILE_OPEN_PROJECT();

    
    void event_FILE_EXPORT_CSV();
    void event_FILE_IMPORT_PROJECT();

    void event_FILE_CLOSE_PROJECT();
    void event_FILE_NEW_FILE();
    void event_FILE_NEW_FORM();
    void event_FILE_NEW_DIALOG();
    void event_FILE_NEW_TOOLWINDOW();
    void event_FILE_NEW_DOCKWINDOW();
    void event_FILE_NEW_FORM(bool bWizard);
    void event_FILE_NEW_REPORT();
    void event_FILE_NEW_REPORT(bool bWizard);
    void event_FILE_NEW_MENUBAR();
    void event_FILE_NEW_TOOLBAR();

    void event_PROJECT_WIZARD_FORM();
    void event_PROJECT_WIZARD_REPORT();
    
    void event_FILE_NEW_TABLE();
    void event_FILE_NEW_QUERY();
    void event_FILE_NEW_CLASS();
    void event_FILE_NEW_MODULE();
    void event_FILE_OPEN_FILE();
    void event_FILE_SAVE();
    void event_FILE_SAVE_AS();
    void event_FILE_SAVE_ALL(bool bAll = true);
    void event_FILE_SAVE_HTML();
    void event_FILE_CLOSE();
    void event_FILE_EXIT();
    void event_FILE_PREFERENCES();   
    void event_FILE_IMPORT_FILE();  
    void event_FILE_IMPORT_CSV();  
    
    void event_FILE_PRINT();

    void event_EXAMPLE_BROWSER();
    

    void event_HELP_ABOUT();
    void event_HELP_KBASIC_BUG();
    void event_HELP_KBASIC_CONTRIBUTE();
    void event_HELP_KBASIC_BOOK();    
    void event_HELP_SYNTAX();
    void event_HELP_LANGUAGE_REFERENCE();  
    void event_HELP_WEBSITE();  
    void event_HELP_FRAMEWORK();  

    void event_HELP_OFFLINE_DESCRIPTION();
    void event_HELP_OFFLINE_FRAMEWORK();
    void event_HELP_OFFLINE_OVERVIEW();    
    void event_HELP_OFFLINE_KEYWORDS();
    void event_HELP_OFFLINE_BUILTINS();  
    void event_HELP_OFFLINE_MANUAL();  
    void event_HELP_OFFLINE_SYNTAX();  
    void event_HELP_OFFLINE_MISC();  




    void event_TOOLS_SELFTEST();      
    void event_TOOLS_RESOURCES();      

    void event_EDIT_FINDDEFINITION();
    void event_EDIT_INDENT_LINES();
    void event_EDIT_UNINDENT_LINES();
    void event_EDIT_COMMENT_LINES();
    void event_EDIT_UNCOMMENT_LINES();
    void event_EDIT_MARK_LINES();
    void event_EDIT_UPPER();
    void event_EDIT_LOWER();
    void event_EDIT_DELETE();
    void event_EDIT_SELECT_ALL();
    void event_EDIT_CUT();
    void event_EDIT_COPY();
    void event_EDIT_PASTE();
    void event_EDIT_APPLY();
    void event_EDIT_UNDO();
    void event_EDIT_REDO();
    void event_EDIT_INSERT_FILE();
    void event_EDIT_GOTO();

    void event_EDIT_CLEAR_ALL_BOOKMARKS();
    void event_EDIT_SET_BOOKMARK();
    void event_EDIT_NEXT_BOOKMARK();
    void event_EDIT_PREVIOUS_BOOKMARK();
         
    void event_EDIT_CLEAR_ALL_BREAKPOINTS();
    void event_EDIT_SET_BREAKPOINT();
    void event_EDIT_NEXT_BREAKPOINT();
    void event_EDIT_PREVIOUS_BREAKPOINT();

    void event_EDIT_FIND();
    void event_EDIT_REPLACE();

    void event_EDIT_BACKGROUND();
    void event_EDIT_FONTNAME();
    void event_EDIT_FONTCOLOR();
    void event_EDIT_BOLD();
    void event_EDIT_ITALIC();
    void event_EDIT_UNDERLINE();
    void event_EDIT_FONTSIZE();


    void event_VIEW_FULLSCREEN();   
    void event_VIEW_FOCUSORDER();   
    void event_VIEW_SQLSETTINGS();   
    void event_VIEW_SQLTABLES();   
    void event_VIEW_RELATION();   
    void event_VIEW_QUICKCODE();   
    void event_VIEW_QBE();   
    void event_VIEW_SOURCE_CODE();

    void event_VIEW_DESIGN();
    //void event_VIEW_REPORT();
    void event_VIEW_REPORTPREVIEW();
    //void event_VIEW_MENUBAR();
    //void event_VIEW_TOOLBAR();

 //   void event_VIEW_LOG();
    void event_VIEW_KONSOLE();
    void event_VIEW_LOG();
    void event_VIEW_RUNINFO();

    
    void event_VIEW_TABBAR();
    void event_VIEW_PropertyWindow();
    void event_VIEW_ProjectWindow();
    void event_VIEW_ParserWindow();
    void event_VIEW_HelpWindow();

    void event_VIEW_ToolboxForm();
    void event_VIEW_ToolboxMenuBar();
    void event_VIEW_ToolboxToolBar();
    void event_VIEW_ToolboxSql();
    void event_VIEW_ToolboxReport();
    void event_VIEW_Helpwindow_shortcut();

    void event_INSERT_OPTION_KBASIC();     
    void event_INSERT_OPTION_OLDBASIC();
    void event_INSERT_OPTION_VERYOLDBASIC();
    void event_INSERT_ASSIGNMENT();    
    void event_INSERT_STATEMENT();    
    void event_INSERT_EXPRESSION();    
    void event_INSERT_OPERATOR();    
    void event_INSERT_IF();        
    void event_INSERT_SELECT();      
    void event_INSERT_FORNEXT();          
    void event_INSERT_WHILELOOP();          
    void event_INSERT_LOOPWHILE();          
    void event_INSERT_EXCEPTION();          
    void event_INSERT_VARIABLE();      
    void event_INSERT_CONST();      
    void event_INSERT_FIELDS_CLASS();          
    void event_INSERT_FIELDS_LINE();          
    void event_INSERT_FIELDS_SCOPE();          
    void event_INSERT_FIELDS_MODULE();      
    void event_INSERT_FIELDS_SUB();      
    void event_INSERT_SUB();          
    void event_INSERT_FUNCTION();          
    void event_INSERT_PROPERTY();              
    void event_INSERT_TYPE();    
    void event_INSERT_ENUM();    
    void event_INSERT_REMARK();    

    void event_PROJECT_ADD_EXISTING();
    void event_PROJECT_REFRESH();

    void event_PROJECT_MAKE_RUNTIME_WINDOWS();
    void event_PROJECT_MAKE_RUNTIME_LINUX();
    void event_PROJECT_MAKE_RUNTIME_MACOS();
    void event_PROJECT_PROPERTIES_OF_PROJECT();
    void event_PROJECT_DATABASE();
    void event_PROJECT_TRANSLATION();

    void event_EDIT_FIND_FILE();    
    void event_EDIT_REPLACE_FILE();   

    void event_RUN_RUN();
    void event_RUN_RUN_PCODE();
    void event_RUN_RUN_PCODE2();
    void event_RUN_CONTINUE_PCODE();
    void event_RUN_RUN_PROJECT();
    void event_RUN_RUN_PCODE3();

    void event_RUN_RUN_IN_DEBUG();
    void event_RUN_RUN_IN_DEBUG2();
    //void event_RUN_PAUSE();
    void event_RUN_STOP();
    bool event_RUN_BUILD();    
    bool event_RUN_BUILD_ALL();    
    void event_RUN_SUB();    
    void event_RUN_FORM();    
    //void event_RUN_STOP_DEBUGGING();    
    void event_RUN_SINGLE_STEP();
    void event_RUN_STEP_OVER();
    void event_RUN_STEP_OUT();
    void event_RUN_TO_CURSOR();   

    void event_INSERT_SELECT2();
    void event_INSERT_LABEL();
    void event_INSERT_COMMANDBUTTON();
    void event_INSERT_CHECKBOX();
    void event_INSERT_RADIOBUTTON();
    void event_INSERT_TEXTBOX();
    void event_INSERT_FRAME();
    void event_INSERT_LISTBOX();
    void event_INSERT_LISTBOX_ICONMODE();
    void event_INSERT_COMBOBOX();
    void event_INSERT_PROGRESSBAR();
    void event_INSERT_PROGRESSBAR_SPINNING();
    void event_INSERT_TREEVIEW_LISTVIEW();
    void event_INSERT_COMBOBOX_EDITABLE();
    void event_INSERT_IMAGE();

    void event_INSERT_CHILDCONTROL();
    void event_INSERT_BROWSER();
    void event_INSERT_EDITOR();
    void event_INSERT_DATEBOX();
    void event_INSERT_TIMEBOX();
    void event_INSERT_DATETIMEBOX();
    void event_INSERT_TEXTBOX_PASSWORD();
    void event_INSERT_LABEL_LINK();
    void event_INSERT_LINE_VERTICAL();
    void event_INSERT_LINE_HORIZONTAL();
    
    void event_INSERT_SERIALPORT();
    void event_INSERT_HEADER();
    // CONTROL
    void event_INSERT_UDPSOCKET();
    void event_INSERT_SCROLLBAR();
    void event_INSERT_SPINBOX();
    void event_INSERT_SLIDER();
    void event_INSERT_FORMSVIEW();
    void event_INSERT_TOOLBARVIEW();
    void event_INSERT_SVG();
    void event_INSERT_COMMANDLINKBUTTON();
    void event_INSERT_RESIZEBOX();
    void event_INSERT_TOOLBUTTON();
    void event_INSERT_FOOTER();
    void event_INSERT_VSPLIT();
    void event_INSERT_HSPLIT();
    void event_INSERT_VBOX();
    void event_INSERT_HBOX();
    void event_INSERT_VHBOX();
    void event_INSERT_BOX();
    void event_INSERT_HIDDEN();
    void event_INSERT_TREEVIEW();
    void event_INSERT_TAB();
    void event_INSERT_MOVIE();
    void event_INSERT_SOUND();
    void event_INSERT_WEB();
    void event_INSERT_TIMER();
    void event_INSERT_IMAGEBUTTON();
    void event_INSERT_MENU();
    void event_INSERT_CHILDMENU();
    void event_INSERT_MENUBARITEM();
    void event_INSERT_MOVE();
    void event_INSERT_DELETE();
    void event_INSERT_TOOLBARITEM();

    void event_FORMAT_ALIGN_BOTTOM();
    void event_FORMAT_ALIGN_TOP();
    void event_FORMAT_ALIGN_LEFT();
    void event_FORMAT_ALIGN_RIGHT();
    void event_FORMAT_SET_SAME_WIDTH();
    void event_FORMAT_SET_SAME_HEIGHT();
    void event_FORMAT_SET_SAME_SIZE();
    void event_FORMAT_LAYOUT_HORIZONTALLY();
    void event_FORMAT_LAYOUT_VERTICALLY();
    void event_FORMAT_MOVE_TO_FRONT();
    void event_FORMAT_MOVE_TO_BACK();   
    void event_FORMAT_MOVE_UP();   
    void event_FORMAT_MOVE_DOWN();   
    void event_FORMAT_MOVE_LEFT();   
    void event_FORMAT_MOVE_RIGHT();   

    void event_TRANSLATION_ADD();   
    void event_TRANSLATION_REMOVE();   

    void closeAllWindows();

private slots:

    void updateWindowMenu();
    void switchLayoutDirection();
    void openExampleFile(QString s);
    void openProjectListFile(QString s);

private:

  void projectLanguageChanged();

    // ***
public:
    bool copyDir (const QString& from, const QString& to);
    bool copyFile (const QString& from, const QString& to);
    bool deleteFile (const QString& from);
    bool createDir (const QString& from);
    bool createFile (const QString& from, QString sText = "");
    bool renameFile (const QString& from, const QString& to);
    bool processGUI();
    bool processGUI(int msec);
    void interruptDebugAtBreakpoint(QString file, int line);
    void clearLocal();
    void addLocal(QString sName, QString sType, QString sValue);
    void clearGlobal();
    void addGlobal(QString sName, QString sType, QString sValue);
    void clearStack();
    void addStack(QString sName);
    // ***


    // ***
public:

  QString sCurrentLanguage;

  QString trFilename(QString s);

  void closeProject();
  bool isFileInProject(QString s);
  void loadProject(QString s);

  void loadProjectPreferences();
  void saveProjectPreferences();

  _sourcecodeeditor* new_sourcecodeeditor();
  _table* new_table(bool bNormal = false);
  _qbe *new_query(bool bNormal = false);
  _form* new_form(bool bNormal = false);
  _report* new_report(bool bNormal = false);
  _menubar* new_menubar();
  _toolbar* new_toolbar();

  void openTable(QString s){ if (!isTableFileOpened(s, true)){ loadTable(s); } }
  void openQuery(QString s){ if (!isQueryFileOpened(s, true)){ loadQuery(s); } }
  void openForm(QString s){ if (!isFormFileOpened(s, true)){ loadForm(s); } }
  void openReport(QString s){ if (!isReportFileOpened(s, true)){ loadReport(s); } }
  void openClass(QString s){ if (!isClassFileOpened(s, true)){ loadFile(s); } }
  void openModule(QString s){ if (!isModuleFileOpened(s, true)){ loadFile(s); } }
  void openOther(QString s){ if (!isFileOpened2(s, true)){ loadFile(s); } }
  void openMenuBar(QString s){ if (!isMenuBarFileOpened(s, true)){ loadMenuBar(s); } }
  void openToolBar(QString s){ if (!isToolBarFileOpened(s, true)){ loadToolBar(s); } }
  
  void openFormClassSourceCode(QString & s){ if (!isClassFileOpened(s, true)){ loadFile(s, true); } }
  void openReportClassSourceCode(QString s){ if (!isClassFileOpened(s, true)){ loadFile(s, true); } }
  void openMenuBarClassSourceCode(QString s){ if (!isClassFileOpened(s, true)){ loadFile(s, true); } }
  void openToolBarClassSourceCode(QString s){ if (!isClassFileOpened(s, true)){ loadFile(s, true); } }
  void openDataFile(QString s){ if (!isDataFileOpened(s, true)){ loadData(s); } }

  void loadFormClassSourceCode(QString s);
  void loadReportClassSourceCode(QString s);

  void loadFile(QString s, bool bClassForm = false);
  void loadFileFullscreen(QString s, bool bClassForm = false);

  void loadTable(QString s);
  void loadData(QString s);
  void loadQuery(QString s);
  void loadForm(QString s);
  void loadReport(QString s);
  void loadMenuBar(QString s);
  void loadToolBar(QString s);
  void loadOther(QString s);

  void insertClass(QString s, QString sText = "");
  void insertModule(QString s, QString sText = "");
  void insertTable(QString s, QString sText = "");
  void insertQuery(QString s, QString sText = "");
  void insertForm(QString s, QString sText = "");
  void insertReport(QString s, QString sText = "");    
  void insertMenuBar(QString s, QString sText = "");
  void insertToolBar(QString s, QString sText = "");
  void insertOther(QString s, QString sText = "");
  void insertImage(QString s, QString sText = "");

  bool insertFile(QTreeWidgetItem *p, QString file, QString ext, QString icon, QString sText, QString rename = "");

  //_form *getFormObject(QString s);

  bool isTableFileOpened(QString s, bool bShow);
  bool isDataFileOpened(QString s, bool bShow);
  bool isQueryFileOpened(QString s, bool bShow);
  bool isFormFileOpened(QString s, bool bShow);
  bool isReportFileOpened(QString s, bool bShow);
  bool isMenuBarFileOpened(QString s, bool bShow);
  bool isToolBarFileOpened(QString s, bool bShow);
  bool isClassFileOpened(QString & s, bool bShow);
  bool isModuleFileOpened(QString s, bool bShow);
  bool isFormClassFileOpened(QString s, bool bShow);
  bool isReportClassFileOpened(QString s, bool bShow);
  bool isMenuBarClassFileOpened(QString s, bool bShow);
  bool isToolBarClassFileOpened(QString s, bool bShow);
  bool isFileOpened2(QString s, bool bShow);

  _sourcecodeeditor *getMatchingSourceCodeEditor(_form *f);
  _sourcecodeeditor *getMatchingSourceCodeEditor(_report *f);
  _sourcecodeeditor *getMatchingSourceCodeEditor(_menubar *f);
  _sourcecodeeditor *getMatchingSourceCodeEditor(_toolbar *f);

  bool isProjectDir(QString s){ return s.endsWith(".kbasic_project", Qt::CaseInsensitive); }
  bool isProjectFile(QString s){ return s.endsWith(".kbasic_project", Qt::CaseInsensitive); }
  bool isClassFile(QString s){ return s.endsWith(".kbasic_class", Qt::CaseInsensitive); }
  bool isModuleFile(QString s){ return s.endsWith(".kbasic_module", Qt::CaseInsensitive) || s.endsWith(".kbasic", Qt::CaseInsensitive); }
  bool isTableFile(QString s){ return s.endsWith(".kbasic_table", Qt::CaseInsensitive); }
  bool isQueryFile(QString s){ return s.endsWith(".kbasic_query", Qt::CaseInsensitive); }
  bool isFormFile(QString s){ return s.endsWith(".kbasic_form", Qt::CaseInsensitive); }
  bool isReportFile(QString s){ return s.endsWith(".kbasic_report", Qt::CaseInsensitive); }
  bool isMenuBarFile(QString s){ return s.endsWith(".kbasic_menubar", Qt::CaseInsensitive); }
  bool isToolBarFile(QString s){ return s.endsWith(".kbasic_toolbar", Qt::CaseInsensitive); }

  bool isImageFile(QString s){ 
    return !isProjectFile(s) 
      && !isTableFile(s)
      && !isQueryFile(s)
      && !isFormFile(s)
      && !isReportFile(s) 
      && !isMenuBarFile(s) 
      && !isToolBarFile(s)
      && !isClassFile(s) 
      && !isModuleFile(s)
       && (s.endsWith(".jpg", Qt::CaseInsensitive) 
            || s.endsWith(".jpeg", Qt::CaseInsensitive) 
            || s.endsWith(".mng", Qt::CaseInsensitive) 
            || s.endsWith(".png", Qt::CaseInsensitive) 
            || s.endsWith(".bmp", Qt::CaseInsensitive) 
            || s.endsWith(".gif", Qt::CaseInsensitive)

            || s.endsWith(".pbm", Qt::CaseInsensitive)
            || s.endsWith(".pgm", Qt::CaseInsensitive)
            || s.endsWith(".ppm", Qt::CaseInsensitive)
            || s.endsWith(".xbm", Qt::CaseInsensitive)
            || s.endsWith(".xpm", Qt::CaseInsensitive));

  }    

  bool isOtherFile(QString s){ 
    return !isProjectFile(s) 
      && !isTableFile(s)
      && !isQueryFile(s)
      && !isFormFile(s)
      && !isReportFile(s) 
      && !isMenuBarFile(s) 
      && !isToolBarFile(s)
      && !isClassFile(s) 
      && !isModuleFile(s)
      && !isImageFile(s);
  }    


  bool existsFile(QString s)
  {  
    if (existsClassFile(s)) return true;
    if (existsModuleFile(s)) return true;
    if (existsTableFile(s)) return true;
    if (existsQueryFile(s)) return true;
    if (existsFormFile(s)) return true;
    if (existsReportFile(s)) return true;
    if (existsMenuBarFile(s)) return true;
    if (existsToolBarFile(s)) return true;
    if (existsOtherFile(s)) return true;

    return false;
  }

  bool existsClassFile(QString s)
  {
    QTreeWidgetItemIterator it(_class2);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
      ++it;
    }
    return false;
  }

  bool existsModuleFile(QString s)
  {
    QTreeWidgetItemIterator it(_module2);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
      ++it;
    }
    return false;
  }
  
  bool existsTableFile(QString s)
  {
    QTreeWidgetItemIterator it(_table2);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
      ++it;
    }
    return false;
  }
  
  bool existsQueryFile(QString s)
  {
    QTreeWidgetItemIterator it(_query2);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
      ++it;
    }
    return false;
  }
  
  bool existsFormFile(QString s)
  {
    QTreeWidgetItemIterator it(_form2);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
      ++it;
    }
    return false;
  }
  
  bool existsReportFile(QString s)
  {
    QTreeWidgetItemIterator it(_report2);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
      ++it;
    }
    return false;
  }

  QString first()
  {
    QTreeWidgetItemIterator it(_project2);

    files.clear();
    nFiles = 0;

    while(*it){

      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);

      if (ss.length()){
        int n = files.count();
        files.append(ss);
      }
      ++it;
    }

    if (files.count()){
      return files.first();
    }

    return "";
  }

  QString next()
  {
    if (nFiles + 1 < files.count()){
      QString s = files[++nFiles];
      return s;
    }

    return "";
  }

  QList<QString> files;
  int nFiles;

  bool existsMenuBarFile(QString s)
  {
    QTreeWidgetItemIterator it(_menubar2);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
      ++it;
    }
    return false;
  }

  bool existsToolBarFile(QString s)
  {
    QTreeWidgetItemIterator it(_toolbar2);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
      ++it;
    }
    return false;
  }
/*
  // OBJECT
  bool existsFileFile(QString s)
  {
    QTreeWidgetItemIterator it(_file);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
    }
    return false;
  }
*/
  bool existsOtherFile(QString s)
  {
    QTreeWidgetItemIterator it(_other2);

    while(*it){
      QTreeWidgetItem *t = *it;
      QString ss = t->text(1);
      if (ss.compare(s) == 0) return true;
      ++it;
    }
    return false;
  }



bool cutFile()
{
  QTreeWidgetItem *l = 0;

  if (tree->hasFocus()){
    l = tree->currentItem();
  } else return false;

  sCut = l->text(1);
  sCopy = "";

  return true;
}

bool copyFile()
{
  QTreeWidgetItem *l = 0;

  if (tree->hasFocus()){
    l = tree->currentItem();
  } else return false;

  sCopy = l->text(1);
  sCut = "";

  return true;
}

bool deleteFile();
bool pasteFile();

  static QString getFilenamePath(QString s)
  {       
    int i = s.lastIndexOf('\\');
    if (i == -1){
      i = s.lastIndexOf('/');
    }
    s = s.left(i);
    return s; 
  }

  static QString getFilenameWithoutPath(QString s)
  {       
    int i = s.lastIndexOf('\\');
    if (i == -1){
      i = s.lastIndexOf('/');
    }
    s = s.right(s.length() - i - 1);
    return s; 
  }

  static QString getFilenameWithoutPathAndExtension(QString s)
  {       
    QString k = getFilenameWithoutPath(s);

    int i = k.lastIndexOf('.');

    k = k.left(i);
    return k; 
  }

  static QString getFilenameExtension(QString s)
  {       
    int i = s.lastIndexOf('.');

    s = s.mid(i + 1);
    return s; 
  }

  QString getProjectPath()
  {
    QString s = sProjectFilename;
    if (s.isEmpty()) return s;
    int i = s.lastIndexOf('\\');
    if (i == -1){
      i = s.lastIndexOf('/');
    }
    s = s.left(i);
    return s;     
  }

  QString getProjectName()
  {
    return sProjectFilename;     
  }


  QTreeWidget *tree;

  QTreeWidgetItem *_project2;
  QTreeWidgetItem *_class2;
  QTreeWidgetItem *_module2;
  QTreeWidgetItem *_table2;
  QTreeWidgetItem *_query2;
  QTreeWidgetItem *_form2;
  QTreeWidgetItem *_report2;
  QTreeWidgetItem *_toolbar2;
  QTreeWidgetItem *_menubar2;
  QTreeWidgetItem *_other2;
  QTreeWidgetItem *_image2;


  QString sCut;
  QString sCopy;
private:
  QString sProjectFilename;

    // ***

private:
  QMenuBar *macmenuBar;

    // misc.
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();   

    bool selfTest(QString sPath);

    void buildExampleMenu(QString sPath, QMenu *m);

    void readSettings();
    void writeSettings();

    
    

    QSignalMapper *windowMapper;
    QSignalMapper *exampleMapper;

    QMenu *FILE;
    QMenu *EDIT;
    QMenu *VIEW;
    QMenu *INSERT;
    QMenu *FORMAT;
    QMenu *PROJECT;
    QMenu *DEBUG2;
    QMenu *RUN;
    QMenu *EXAMPLES;    
    QMenu *TOOLS;
    QMenu *HELP;

    QMenu *abc[27];
    QMenu *windowMenu;

    QToolBar *tbFile;
    QToolBar *tbRun;
    QToolBar *tbInsert;
    QToolBar *tbEdit;
    QToolBar *tbView;
    QToolBar *tbFormat;
    QToolBar *tbTranslation;

public:
    QComboBox *TRANSLATION;

    QAction *PROJECTLIST;

    QAction *FILE_NEW_PROJECT;
    QAction *FILE_OPEN_PROJECT;
    QAction *FILE_CLOSE_PROJECT;
    QAction *FILE_CLOSE;
    QAction *FILE_IMPORT_PROJECT;
    QAction *FILE_EXPORT_CSV;
    
    //QAction *FILE_EXPORT_PROJECT;
    QAction *FILE_NEW_FILE;
    QAction *FILE_OPEN_FILE;
    QAction *EXAMPLE_BROWSER;    
    QAction *FILE_SAVE;
    QAction *FILE_SAVE_AS;
    QAction *FILE_SAVE_ALL;
    QAction *FILE_SAVE_HTML;
    QAction *FILE_IMPORT_FILE;
    QAction *FILE_IMPORT_CSV;
    //QAction *FILE_EXPORT_FILE;
    QAction *FILE_SET_AS_DEFAULT;
    QAction *FILE_PRINT;
    QAction *FILE_EXIT;

    QAction *EDIT_FINDDEFINITION;
    QAction *EDIT_UNDO;
    QAction *EDIT_REDO;
    QAction *EDIT_CUT;
    QAction *EDIT_COPY;
    QAction *EDIT_PASTE;
    QAction *EDIT_DELETE;
    QAction *EDIT_SELECT_ALL;
    QAction *EDIT_APPLY;
    QAction *EDIT_FIND;
    QAction *EDIT_FIND_FILE;
    QAction *EDIT_REPLACE;
    QAction *EDIT_REPLACE_FILE;
    QAction *EDIT_COMMENT_LINES;
    QAction *EDIT_UNCOMMENT_LINES;
    QAction *EDIT_UNINDENT_LINES;
    QAction *EDIT_INDENT_LINES;
    QAction *EDIT_MARK_LINES;
    QAction *EDIT_UPPER;
    QAction *EDIT_LOWER;
    QAction *EDIT_GOTO;
    QAction *EDIT_INSERT_FILE;
    QAction *EDIT_CLEAR_ALL_BOOKMARKS;
    QAction *EDIT_SET_BOOKMARK;
    QAction *EDIT_NEXT_BOOKMARK;
    QAction *EDIT_PREVIOUS_BOOKMARK;

    QAction *EDIT_BACKGROUND;
    QAction *EDIT_FONTNAME;
    QAction *EDIT_FONTCOLOR;
    QAction *EDIT_BOLD;
    QAction *EDIT_ITALIC;
    QAction *EDIT_UNDERLINE;
    QAction *EDIT_FONTSIZE;




    QAction *VIEW_DESIGN;

    //QAction *VIEW_REPORT;
    QAction *VIEW_REPORTPREVIEW;
    QAction *VIEW_SOURCE_CODE;
    //QAction *VIEW_MENUBAR;
    //QAction *VIEW_TOOLBAR;

    QAction *VIEW_FULLSCREEN;
    QAction *VIEW_QBE;
    QAction *VIEW_FOCUSORDER;
    QAction *VIEW_SQLSETTINGS;
    QAction *VIEW_SQLTABLES;
    QAction *VIEW_RELATION;
    QAction *VIEW_QUICKCODE;
   // QAction *VIEW_LOG;
    QAction *VIEW_RUNINFO;
    QAction *VIEW_KONSOLE;
    QAction *VIEW_LOG;

    QAction *PROJECT_ADD_EXISTING;
    QAction *PROJECT_REFRESH;    
    QAction *PROJECT_NEW_TABLE;
    QAction *PROJECT_NEW_QUERY;
    QAction *PROJECT_NEW_CLASS;
    QAction *PROJECT_NEW_MODULE;
    QAction *PROJECT_NEW_FORM;
    QAction *PROJECT_NEW_DIALOG;
    QAction *PROJECT_NEW_TOOLWINDOW;
    QAction *PROJECT_NEW_DOCKWINDOW;
    QAction *PROJECT_NEW_REPORT;
    QAction *PROJECT_NEW_MENUBAR;
    QAction *PROJECT_NEW_TOOLBAR;
    QAction *PROJECT_WIZARD_FORM;
    QAction *PROJECT_WIZARD_REPORT;    
    QAction *PROJECT_NEW_FILE;  

    QAction *INSERT_SELECT2;
    QAction *INSERT_LABEL;
    QAction *INSERT_COMMANDBUTTON;
    QAction *INSERT_CHECKBOX;
    QAction *INSERT_RADIOBUTTON;
    QAction *INSERT_TEXTBOX;
    QAction *INSERT_FRAME;
    QAction *INSERT_LISTBOX;
    QAction *INSERT_LISTBOX_ICONMODE;
    QAction *INSERT_COMBOBOX;
    QAction *INSERT_PROGRESSBAR;
    QAction *INSERT_PROGRESSBAR_SPINNING;
    QAction *INSERT_TREEVIEW_LISTVIEW;
    QAction *INSERT_COMBOBOX_EDITABLE;
    QAction *INSERT_IMAGE;

    QAction *INSERT_CHILDCONTROL;
    QAction *INSERT_CUSTOMCONTROL;
    QAction *INSERT_SCROLLBOX;
    QAction *INSERT_BROWSER;
    QAction *INSERT_EDITOR;
    QAction *INSERT_DATEBOX;
    QAction *INSERT_TIMEBOX;
    QAction *INSERT_DATETIMEBOX;
    QAction *INSERT_TOOLBUTTON;

    // CONTROL    
    QAction *INSERT_UDPSOCKET;
    QAction *INSERT_SCROLLBAR;
    QAction *INSERT_SPINBOX;
    QAction *INSERT_SLIDER;
    QAction *INSERT_FORMSVIEW;
    QAction *INSERT_TOOLBARVIEW;
    QAction *INSERT_SVG;
    QAction *INSERT_COMMANDLINKBUTTON;
    QAction *INSERT_RESIZEBOX;
    QAction *INSERT_TEXTBOX_PASSWORD;
    QAction *INSERT_LABEL_LINK;
    QAction *INSERT_LINE_VERTICAL;
    QAction *INSERT_LINE_HORIZONTAL;
    QAction *INSERT_SERIALPORT;
    QAction *INSERT_HEADER;
    QAction *INSERT_FOOTER;
    QAction *INSERT_VSPLIT;
    QAction *INSERT_HSPLIT;
    QAction *INSERT_VBOX;
    QAction *INSERT_HBOX;
    QAction *INSERT_VHBOX;
    QAction *INSERT_BOX;
    QAction *INSERT_HIDDEN;
    QAction *INSERT_TREEVIEW;
    QAction *INSERT_TAB;
    QAction *INSERT_MOVIE;
    QAction *INSERT_SOUND;
    QAction *INSERT_WEB;
    QAction *INSERT_TIMER;
    QAction *INSERT_IMAGEBUTTON;
    QAction *INSERT_MENU;
    QAction *INSERT_CHILDMENU;
    QAction *INSERT_MENUBARITEM;
    QAction *INSERT_MOVE;
    QAction *INSERT_DELETE;
    QAction *INSERT_TOOLBARITEM;

    QAction *INSERT_OPTION_KBASIC;
    QAction *INSERT_OPTION_OLDBASIC;
    QAction *INSERT_OPTION_VERYOLDBASIC;
    QAction *INSERT_STATEMENT;
    QAction *INSERT_ASSIGNMENT;
    QAction *INSERT_EXPRESSION;    
    QAction *INSERT_OPERATOR;
    QAction *INSERT_IF;
    QAction *INSERT_SELECT;
    QAction *INSERT_FORNEXT;
    QAction *INSERT_WHILELOOP;
    QAction *INSERT_LOOPWHILE;
    QAction *INSERT_EXCEPTION;
    QAction *INSERT_VARIABLE;
    QAction *INSERT_CONST;
    QAction *INSERT_FIELDS_LINE;
    QAction *INSERT_FIELDS_SCOPE;
    QAction *INSERT_FIELDS_CLASS;
    QAction *INSERT_FIELDS_MODULE;
    QAction *INSERT_FIELDS_SUB;
    QAction *INSERT_SUB;
    QAction *INSERT_FUNCTION;
    QAction *INSERT_PROPERTY;
    QAction *INSERT_TYPE;
    QAction *INSERT_ENUM;
    QAction *INSERT_REMARK;
    
    QAction *FORMAT_ALIGN_BOTTOM;
    QAction *FORMAT_ALIGN_TOP;
    QAction *FORMAT_ALIGN_LEFT;
    QAction *FORMAT_ALIGN_RIGHT;
    QAction *FORMAT_SET_SAME_WIDTH;
    QAction *FORMAT_SET_SAME_HEIGHT;
    QAction *FORMAT_SET_SAME_SIZE;
    QAction *FORMAT_LAYOUT_HORIZONTALLY;
    QAction *FORMAT_LAYOUT_VERTICALLY;
    QAction *FORMAT_MOVE_TO_FRONT;
    QAction *FORMAT_MOVE_TO_BACK;
    QAction *FORMAT_MOVE_UP;
    QAction *FORMAT_MOVE_DOWN;
    QAction *FORMAT_MOVE_LEFT;
    QAction *FORMAT_MOVE_RIGHT;

    QAction *TRANSLATION_ADD;
    QAction *TRANSLATION_REMOVE;

    QAction *PROJECT_DATABASE;
    QAction *PROJECT_TRANSLATION;
    QAction *PROJECT_SET_AS_DEFAULT;
    QAction *PROJECT_PROPERTIES_OF_PROJECT;

    QAction *RUN_RUN_PROJECT;
    QAction *RUN_RUN_PCODE2;
    QAction *RUN_CONTINUE_PCODE;
    QAction *RUN_PAUSE;
    QAction *RUN_STOP;
    QAction *RUN_BUILD;
    QAction *RUN_BUILD_ALL;    
    QAction *RUN_SUB;
    QAction *RUN_FORM;
    //QAction *RUN_PCODEVIEWER;
    //QAction *RUN_RUN_PCODE;
    QAction *RUN_RUN_PCODE3;
    QAction *RUN_RUN;
    QAction *PROJECT_MAKE_RUNTIME_WINDOWS;
    QAction *PROJECT_MAKE_RUNTIME_LINUX;
    QAction *PROJECT_MAKE_RUNTIME_MACOS;

    QAction *RUN_RUN_IN_DEBUG;
    QAction *RUN_RUN_IN_DEBUG2;
    QAction *RUN_SINGLE_STEP;
    QAction *RUN_STEP_OVER;
    QAction *RUN_STEP_OUT;
    QAction *RUN_TO_CURSOR;
    /*
    QAction *VIEW_LOCAL;
    QAction *VIEW_GLOBAL;
    QAction *VIEW_STACK;*/
    QAction *RUN_CLEAR_ALL_BREAKPOINTS;
    QAction *RUN_SET_BREAKPOINT;
    QAction *RUN_NEXT_BREAKPOINT;
    QAction *RUN_PREVIOUS_BREAKPOINT;

    QAction *TOOLS_EXTERN_TOOLS;
    QAction *TOOLS_SELFTEST;
    QAction *TOOLS_RESOURCES;
    QAction *FILE_PREFERENCES;

    QAction *HELP_WEBSITE;
    QAction *HELP_FRAMEWORK;
    QAction *HELP_LANGUAGE_REFERENCE;
    QAction *HELP_KBASIC_BOOK;
    QAction *HELP_SYNTAX;
    QAction *HELP_KBASIC_BUG;
    QAction *HELP_KBASIC_CONTRIBUTE;
    QAction *HELP_ABOUT;

    QAction *HELP_OFFLINE_DESCRIPTION;
    QAction *HELP_OFFLINE_FRAMEWORK;
    QAction *HELP_OFFLINE_OVERVIEW;
    QAction *HELP_OFFLINE_KEYWORDS;
    QAction *HELP_OFFLINE_BUILTINS;
    QAction *HELP_OFFLINE_MANUAL;
    QAction *HELP_OFFLINE_SYNTAX;
    QAction *HELP_OFFLINE_MISC;



    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *separatorAct;

    bool bProjectLoading;

private:

  

    // ***
    struct _bookmark
    {
        QString sFile;
        int nLine;
    };

    QList<_bookmark> bookmarks;
    int nCurrentBookmark;
    // ***

    // ***
    struct _breakpoint
    {
        QString sFile;
        int nLine;
    };

    QList<_breakpoint> breakpoints;
    int nCurrentBreakpoint;
    // ***



    QApplication *my_qapplication;

    bool bRuntime;


    bool bRunning;
    bool bCompiling;
    bool bDebugging;    
    bool bProject;    

    _compile *my_compile;


    interpreter *myInterpreter;



public:
   _log *my_log;
   _infoconsole *my_infoconsole;
   QProgressBar *oPercentInfo;
    QFileSystemWatcher *fsWatcher;

   void ci_parse(QString sFilename, QString sText);

   QList<_inputtip_info> ci_getAllForFile(QString sForFile);

   QList<_inputtip_info> ci_getAsForFile(QString sForFile, QString sScope);
   QList<_inputtip_info> ci_getDotForFile(QString sForFile, QString sScope, QString sScope2, QString sDot);
   QList<_inputtip_info> ci_getDotMethodForFile(QString sForFile, QString sScope, QString sScope2, QString sDot);
   QList<_inputtip_info> ci_getFindDefinition(QString sForFile, QString sScope, QString sScope2, QString sDot, QString sBeforeDot);

   QList<_inputtip_info> ci_getEventsForClass(QString sControlType);
   

    

};

#endif
