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

#include "_projectwindow.h"



#include "_mainwindow.h"
#include "_sourcecodeeditor.h"
#include "../kbshared/_form.h"
#include "../kbshared/_report.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"
#include "../kbshared/_table.h"

#include "_qbe_tables.h"

extern QSqlDatabase CurrentDatabase;

extern _mainwindow *EXTERN_my_mainwindow;
extern QString idePath(QString s);



extern QString kbasicPath(QString sPath);
extern const QIcon &kbasicIcon(QString s);

extern _qbe_tables *EXTERN_qbe_tables;

extern bool checkObjectName(QString s);


extern QStringList trl;

_projectwindow::_projectwindow(QWidget *parent) : QWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);

  
  QVBoxLayout *l = new QVBoxLayout();
  l->setMargin(0);
  l->setSpacing(0);
  setLayout(l);
  

  QHBoxLayout *jj = new QHBoxLayout();
  jj->setMargin(0);
  jj->setSpacing(0);

  setdb = new QPushButton(kbasicIcon(idePath("PROJECT_DATABASE.png")), tr(""), this); 
  setdb->setToolTip(tr("Database Connection...")); 
  setdb->setFlat(true); 
  setdb->setIconSize(QSize(32, 32)); 
  setdb->setFixedSize(QSize(34, 34));
  connect(setdb, SIGNAL(clicked(bool)), this, SLOT(settingdb()));  

  currentprojectname = new QLabel("");
  currentprojectname->setFixedHeight(32);
  currentprojectname->setIndent(5);
  QFont f = currentprojectname->font();
  f.setBold(true);
  currentprojectname->setFont(f);
#ifdef MAC
  f = currentprojectname->font(); f.setPixelSize(10); currentprojectname->setFont(f); 
#endif

  jj->addWidget(setdb);
  jj->addWidget(currentprojectname);

  l->addLayout(jj);

  QAction *a = 0;
  
  ag = new QActionGroup(this);
  ag->setExclusive(true);
  
  tb = new QToolBar(this); l->addWidget(tb);
   
  aAll = a = tb->addAction(tr("All"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
 /* 
#ifdef MAC
  a = tb->addAction(tr("Forms"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true); // HIDE
  a = tb->addAction(tr("Classes"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true); // HIDE
  a = tb->addAction(tr("Modules"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true); // HIDE
#else*/
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_FORM.png")), */tr("Forms"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")), */tr("Classes"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")), */tr("Modules"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE.png")), */tr("Tables"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")), */tr("Queries"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_REPORT.png")), */tr("Reports"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_MENUBAR.png")), */tr("Menubars"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_TOOLBAR.png")), */tr("Toolbars"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")), */tr("Images"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
  a = tb->addAction(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")), */tr("Others"), this, SLOT(actionSelected())); a->setActionGroup(ag); a->setCheckable(true);
//#endif
  { // add extra space
    QWidget *ww = new QWidget();
    QSizePolicy sp;
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    ww->setSizePolicy(sp);
    tb->addWidget(ww);
  }

#ifdef NICHTKOMPILIEIEREN
  tb = new QTabBar(this); l->addWidget(tb);
  
  tb->addTab(tr("All"));
  
#ifdef MAC
  tb->addTab(tr("Forms"));
  tb->addTab(tr("Classes"));
  tb->addTab(tr("Modules"));
#else
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_FORM.png")), */tr("Forms"));
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")), */tr("Classes"));
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")), */tr("Modules"));
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE.png")), */tr("Tables"));
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")), */tr("Queries"));
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_REPORT.png")), */tr("Reports"));
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_MENUBAR.png")), */tr("Menubars"));
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_TOOLBAR.png")), */tr("Toolbars"));
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")), */tr("Images"));
  tb->addTab(/*kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")), */tr("Others"));
#endif

  connect(tb, SIGNAL(currentChanged(int)), this, SLOT(currentChanged(int)));
#endif


  EXTERN_my_mainwindow->tree = new QTreeWidget(this);
  connect(EXTERN_my_mainwindow->tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem *, int)));
  connect(EXTERN_my_mainwindow->tree, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
  connect(EXTERN_my_mainwindow->tree, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(itemChanged(QTreeWidgetItem *, int)));
  connect(EXTERN_my_mainwindow->tree, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(customContextMenuRequested(const QPoint &)));

  connect(EXTERN_my_mainwindow->tree, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));


  EXTERN_my_mainwindow->tree->setContextMenuPolicy(Qt::CustomContextMenu);
  EXTERN_my_mainwindow->tree->header()->hide();


  l->addWidget(EXTERN_my_mainwindow->tree);
  EXTERN_my_mainwindow->tree->setHeaderLabel("");

#ifdef MAC
   f = EXTERN_my_mainwindow->tree->font(); f.setPixelSize(10); EXTERN_my_mainwindow->tree->setFont(f); 
  // EXTERN_my_mainwindow->tree->invisibleRootItem();
#endif
  
  createTree();
  


}

void _projectwindow::closeProject()
{
  QMenu *qmenu = EXTERN_my_mainwindow->PROJECTLIST->menu();
  if (qmenu) qmenu->clear();

  EXTERN_my_mainwindow->_form2 = 0;
  EXTERN_my_mainwindow->tree->clear();

  EXTERN_my_mainwindow->setWindowTitle(tr(MYAPP));
}

void _projectwindow::createTree()
{

  bInit = true;
  EXTERN_my_mainwindow->_form2 = 0;

  QString s = EXTERN_my_mainwindow->getProjectPath();

  if (s.length() == 0) return;

  EXTERN_my_mainwindow->tree->clear();
  EXTERN_my_mainwindow->tree->setHidden(false);

  QTreeWidgetItem *t;

  t = EXTERN_my_mainwindow->_project2 = new QTreeWidgetItem(EXTERN_my_mainwindow->tree, QStringList(tr("Project"))); 
  t->setExpanded(true);
  //EXTERN_my_mainwindow->_project2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));



  //t = new QTreeWidgetItem(_project, QStringList("(Application)"));

  EXTERN_my_mainwindow->_form2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("Forms")));
//  _form = new QTreeWidgetItem(_project, QStringList(tr("Form ............................. *.kbasic_form .......................")));
  EXTERN_my_mainwindow->_form2->setExpanded(true);
 //EXTERN_my_mainwindow->_form2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));

  //_form->setPixmap(0, _mainwindow::getPixmap(kbasicPath("ide/jabber_away.png")));  
  //_form->setSelectable(false);

  EXTERN_my_mainwindow->_class2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("Classes")));
//  _class = new QTreeWidgetItem(_project, QStringList(tr("Class ............................. *.kbasic_class .......................")));
  EXTERN_my_mainwindow->_class2->setExpanded(true);
  //EXTERN_my_mainwindow->_class2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));
  //_class->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")));
  //_class->setPixmap(0, _mainwindow::getPixmap(kbasicPath("ide/jabber_away.png")));  
  //_class->setSelectable(false);

  EXTERN_my_mainwindow->_module2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("Modules")));
//  _module = new QTreeWidgetItem(_project, QStringList(tr("Module ......................... *.kbasic_module .......................")));
  EXTERN_my_mainwindow->_module2->setExpanded(true);
  //EXTERN_my_mainwindow->_module2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));
  //_module->setPixmap(0, _mainwindow::getPixmap(kbasicPath("ide/jabber_away.png")));  
  //_module->setSelectable(false);

  EXTERN_my_mainwindow->_menubar2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("MenuBars")));
  EXTERN_my_mainwindow->_menubar2->setExpanded(true);
  //EXTERN_my_mainwindow->_menubar2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));

  EXTERN_my_mainwindow->_toolbar2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("ToolBars")));  
  EXTERN_my_mainwindow->_toolbar2->setExpanded(true);
  //EXTERN_my_mainwindow->_toolbar2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));

  EXTERN_my_mainwindow->_table2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("Tables")));  
  EXTERN_my_mainwindow->_table2->setExpanded(true);
  //EXTERN_my_mainwindow->_table2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));

  EXTERN_my_mainwindow->_query2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("Queries")));  
  EXTERN_my_mainwindow->_query2->setExpanded(true);
  //EXTERN_my_mainwindow->_query2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));

  EXTERN_my_mainwindow->_report2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("Reports")));  
  EXTERN_my_mainwindow->_report2->setExpanded(true);
  //EXTERN_my_mainwindow->_report2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));

  EXTERN_my_mainwindow->_image2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("Images")));
//  EXTERN_my_mainwindow->_image2->setExpanded(true);
  //EXTERN_my_mainwindow->_image2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));

  EXTERN_my_mainwindow->_other2 = new QTreeWidgetItem(EXTERN_my_mainwindow->_project2, QStringList(tr("Other Files")));
//  _other = new QTreeWidgetItem(_project, QStringList(tr("Other ............................ *.* .......................")));
 // EXTERN_my_mainwindow->_other2->setExpanded(true);
  //EXTERN_my_mainwindow->_other2->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_FOLDER.png")));
  //_other->setPixmap(0, _mainwindow::getPixmap(kbasicPath("ide/jabber_away.png")));  
  //_other->setSelectable(false);


  
}

bool _projectwindow::load()
{

  QMenu *qmenu = EXTERN_my_mainwindow->PROJECTLIST->menu();
  if (qmenu){ 
    qmenu->clear(); 
  } else {
    qmenu = new QMenu();  
    EXTERN_my_mainwindow->PROJECTLIST->setMenu(qmenu);
  }

  bInit = true;

  QString sPath = EXTERN_my_mainwindow->getProjectPath();

  EXTERN_my_mainwindow->setWindowTitle(QString(MYAPP) + " - " + EXTERN_my_mainwindow->getProjectName());

  QStringList l;

  if (CurrentDatabase.isOpen()) l = CurrentDatabase.tables();

  createTree();
  
  QString s = EXTERN_my_mainwindow->getProjectPreference("Translation");
  trl = s.split(";");

  QDir thisDir( sPath );	
  QFileInfoList files = thisDir.entryInfoList();

  QProgressDialog progress(tr("Loading Project..."), tr("Cancel"), 0, files.size(), EXTERN_my_mainwindow);
  progress.setWindowModality(Qt::WindowModal);
  QAction *a = 0;
  QString sLanguage = "";
  QChar c = 0;
  if (!sPath.simplified().isEmpty() && files.size()) {

    for (int pass = 0; pass < 2; pass++) {

    QFileInfo fi;
    for (int i = 0; i < files.size(); i++) {
      fi = files.at(i);
      progress.setValue(i);
      qApp->processEvents();

      
      if (progress.wasCanceled()) break;

      if (fi.fileName() == "." || fi.fileName() == ".."){
      } else if (fi.isDir()){
      } else {
        QString ext = fi.suffix();
        QString sFilename = fi.absoluteFilePath();

        if (pass == 0 && ext == "kbasic_class"){
          a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")), fi.fileName());
          connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
          EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

          QTreeWidgetItem *element = new QTreeWidgetItem(EXTERN_my_mainwindow->_class2, QStringList(""));
          element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")));          

          element->setText(0, fi.baseName());
          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);

          {
            QFile f(sFilename);
            QString sText = "";
            if (f.open(QFile::ReadOnly)){
	            QTextStream t(&f);
              
              t.setCodec("UTF-8");
              t.setAutoDetectUnicode(true);
              t.setGenerateByteOrderMark(true);

              sText = t.readAll();
              sText = sText.replace("\r", "");
	            f.close();
            }
            EXTERN_my_mainwindow->ci_parse(sFilename, sText);
          }

        } else if (pass == 0 && ext == "kbasic_project"){
          // ignore

        } else if (pass == 0 && ext == "kbasic_module"){
          a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")), fi.fileName());
          connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
          EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

          QTreeWidgetItem *element = new QTreeWidgetItem(EXTERN_my_mainwindow->_module2, QStringList(""));
          element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")));          

          element->setText(0, fi.baseName());
          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);

          {
            QFile f(sFilename);
            QString sText = "";
            if (f.open(QFile::ReadOnly)){
	            QTextStream t(&f);
              
              t.setCodec("UTF-8");
              t.setAutoDetectUnicode(true);
              t.setGenerateByteOrderMark(true);

              sText = t.readAll();
              sText = sText.replace("\r", "");
	            f.close();
            }
            EXTERN_my_mainwindow->ci_parse(sFilename, sText);
          }

          //element->setRenameEnabled (0, true);
/*
          QFile f(fi.absoluteFilePath());
          if (f.open(IO_ReadOnly)){
	          QTextStream t(&f);
              t.setCodec("UTF-8");
              t.setAutoDetectUnicode(true);
              t.setGenerateByteOrderMark(true);

              QString sText = t.read();
            if (sText.contains("Function Main", false)){
               element->setText(0, element->text(0) + tr("         has 'Function Main()'"));
            }
	          f.close();
          }*/

        } else if (pass == 0 && ext == ".kbasic"){
          a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")), fi.fileName());
          connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
          EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

          QTreeWidgetItem *element = new QTreeWidgetItem(EXTERN_my_mainwindow->_module2,  QStringList(""));
          element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")));          

          element->setText(0, fi.baseName());
          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);

          {
            QFile f(sFilename);
            QString sText = "";
            if (f.open(QFile::ReadOnly)){
	            QTextStream t(&f);
              
              t.setCodec("UTF-8");
              t.setAutoDetectUnicode(true);
              t.setGenerateByteOrderMark(true);

              sText = t.readAll();
              sText = sText.replace("\r", "");
	            f.close();
            }
            EXTERN_my_mainwindow->ci_parse(sFilename, sText);
          }

//          element->setRenameEnabled (0, true);
/*
          QFile f(fi.absoluteFilePath());
          if (f.open(IO_ReadOnly)){
	          QTextStream t(&f);
              t.setCodec("UTF-8");
              t.setAutoDetectUnicode(true);
              t.setGenerateByteOrderMark(true);

              QString sText = t.read();
            if (sText.contains("Function Main", false)){
               element->setText(0, element->text(0) + tr("         has 'Function Main()'"));
            }
            f.close();
          }*/

        } else if (ext == "kbasic_form"){
          
          QTreeWidgetItem *parent = getParentTreeWidgetItem(EXTERN_my_mainwindow->_form2, sFilename, pass, sLanguage);
          if (parent == 0) continue;
          if (pass == 0 && parent != EXTERN_my_mainwindow->_form2) continue;
          if (pass == 1 && parent == EXTERN_my_mainwindow->_form2) continue;

          QTreeWidgetItem *element = new QTreeWidgetItem(parent, QStringList(""));

          if (QFile::exists(EXTERN_my_mainwindow->trFilename(sFilename))){
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_FORM.png")), fi.fileName());
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_FORM.png")));
          } else {
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_FORM_tr.png")), fi.fileName());
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_FORM_tr.png")));
          }

          connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
          EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

          if (!sLanguage.isEmpty()){
            element->setText(0, fi.baseName() + "." + sLanguage);
          } else {
            element->setText(0, fi.baseName());
          }
          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);

          {
            QString sAllText = "";
            QString sText = _form::getFormClassSourceCode(sFilename, sAllText, false);
            EXTERN_my_mainwindow->ci_parse(sFilename, sText);
          }

          //element->setRenameEnabled (0, true);
/*
          QFile f(fi.absoluteFilePath());
          if (f.open(IO_ReadOnly)){
	          QTextStream t(&f);
              t.setCodec("UTF-8");
              t.setAutoDetectUnicode(true);
              t.setGenerateByteOrderMark(true);

              QString sText = t.read();
            if (sText.contains("Function Main", false)){
               element->setText(0, element->text(0) + tr("         has 'Function Main()'"));
            }
            f.close();
          }*/

        } else if (ext == "kbasic_menubar"){

          QTreeWidgetItem *parent = getParentTreeWidgetItem(EXTERN_my_mainwindow->_menubar2, sFilename, pass, sLanguage);
          if (parent == 0) continue;
          if (pass == 0 && parent != EXTERN_my_mainwindow->_menubar2) continue;
          if (pass == 1 && parent == EXTERN_my_mainwindow->_menubar2) continue;

          QTreeWidgetItem *element = new QTreeWidgetItem(parent, QStringList(""));

          if (QFile::exists(EXTERN_my_mainwindow->trFilename(sFilename))){
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_MENUBAR.png")), fi.fileName());
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_MENUBAR.png")));
          } else {
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_MENUBAR_tr.png")), fi.fileName());
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_MENUBAR_tr.png")));
          }
          connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
          EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

          if (!sLanguage.isEmpty()){
            element->setText(0, fi.baseName() + "." + sLanguage);
          } else {
            element->setText(0, fi.baseName());
          }          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);
          //element->setRenameEnabled (0, true);

          {
            QString sAllText = "";
            QString sText = _menubar::getMenuBarClassSourceCode(sFilename, sAllText, false);
            EXTERN_my_mainwindow->ci_parse(sFilename, sText);
          }

        } else if (ext == "kbasic_toolbar"){

          QTreeWidgetItem *parent = getParentTreeWidgetItem(EXTERN_my_mainwindow->_toolbar2, sFilename, pass, sLanguage);
          if (parent == 0) continue;
          if (pass == 0 && parent != EXTERN_my_mainwindow->_toolbar2) continue;
          if (pass == 1 && parent == EXTERN_my_mainwindow->_toolbar2) continue;

          QTreeWidgetItem *element = new QTreeWidgetItem(parent, QStringList(""));

          if (QFile::exists(EXTERN_my_mainwindow->trFilename(sFilename))){
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_TOOLBAR.png")), fi.fileName());
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_TOOLBAR.png")));
          } else {
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_TOOLBAR_tr.png")), fi.fileName());
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_TOOLBAR_tr.png")));
          }
          connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
          EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

          if (!sLanguage.isEmpty()){
            element->setText(0, fi.baseName() + "." + sLanguage);
          } else {
            element->setText(0, fi.baseName());
          }          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);
          //element->setRenameEnabled (0, true);

          {
            QString sAllText = "";
            QString sText = _toolbar::getToolBarClassSourceCode(sFilename, sAllText, false);
            EXTERN_my_mainwindow->ci_parse(sFilename, sText);
          }

        } else if (pass == 0 && ext == "kbasic_table"){


          if (l.contains(fi.baseName(), Qt::CaseInsensitive)){
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE.png")), fi.fileName());
          } else {
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE_asynchron.png")), fi.fileName());
          }

          connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
          EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

          QTreeWidgetItem *element = new QTreeWidgetItem(EXTERN_my_mainwindow->_table2, QStringList(""));

          if (l.contains(fi.baseName(), Qt::CaseInsensitive)){
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE.png")));          
          } else {
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE_asynchron.png")));          
          }

          element->setText(0, fi.baseName());
          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);

        } else if (pass == 0 && ext == "kbasic_query"){
          a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")), fi.fileName());
          connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
          EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

          QTreeWidgetItem *element = new QTreeWidgetItem(EXTERN_my_mainwindow->_query2, QStringList(""));

          element->setText(0, fi.baseName());
          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);

          QString s = "";
          QFile f(sFilename);
          if (f.open(QIODevice::ReadOnly)){
	          QTextStream t(&f);
            
            t.setCodec("UTF-8");
            t.setAutoDetectUnicode(true);
            t.setGenerateByteOrderMark(true);

	          s = t.readAll();
            s = s.replace("\r", "");
	          f.close();   

            s = s.simplified();

            if (s.startsWith("INSERT INTO ", Qt::CaseInsensitive)){
              element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_INSERT.png")));          
            } else if (s.startsWith("UPDATE ", Qt::CaseInsensitive)){
              element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_UPDATE.png")));          
            } else if (s.startsWith("DELETE ", Qt::CaseInsensitive)){
              element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_DELETE.png")));          
            } else {
              element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")));          
            }

          } else {
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")));          
          }
          

        } else if (ext == "kbasic_report"){

          QTreeWidgetItem *parent = getParentTreeWidgetItem(EXTERN_my_mainwindow->_report2, sFilename, pass, sLanguage);
          if (parent == 0) continue;
          if (pass == 0 && parent != EXTERN_my_mainwindow->_report2) continue;
          if (pass == 1 && parent == EXTERN_my_mainwindow->_report2) continue;

          QTreeWidgetItem *element = new QTreeWidgetItem(parent, QStringList(""));

          if (QFile::exists(EXTERN_my_mainwindow->trFilename(sFilename))){
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_REPORT.png")), fi.fileName());
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_REPORT.png")));
          } else {
            a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_REPORT_tr.png")), fi.fileName());
            element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_REPORT_tr.png")));
          }
          connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
          EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

          if (!sLanguage.isEmpty()){
            element->setText(0, fi.baseName() + "." + sLanguage);
          } else {
            element->setText(0, fi.baseName());
          }          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);
          //element->setRenameEnabled (0, true);

        //} else if (ext == "kbasic_formclass"){
/*
        } else if (ext == "kbasic_file"){
          QTreeWidgetItem *element = new QTreeWidgetItem(_file, QStringList(""));
          //elemen//t->setPixmap(0, _mainwindow::getPixmap(kbasicPath("ide/empty.png")));

          element->setText(0, fi.baseName());
          element->setText(1, fi.absoluteFilePath());
          element->setText(2, ext);
        //  element->setRenameEnabled (0, true);
*/
        } else if (pass == 0){
          //elemen//t->setPixmap(0, _mainwindow::getPixmap(kbasicPath("ide/folder_grey.png")));

          QTreeWidgetItem *element = 0;

          if (sFilename.endsWith(".jpg", Qt::CaseInsensitive) 
            || sFilename.endsWith(".jpeg", Qt::CaseInsensitive) 
            || sFilename.endsWith(".mng", Qt::CaseInsensitive) 
            || sFilename.endsWith(".png", Qt::CaseInsensitive) 
            || sFilename.endsWith(".bmp", Qt::CaseInsensitive) 
            || sFilename.endsWith(".gif", Qt::CaseInsensitive)

            || sFilename.endsWith(".pbm", Qt::CaseInsensitive)
            || sFilename.endsWith(".pgm", Qt::CaseInsensitive)
            || sFilename.endsWith(".ppm", Qt::CaseInsensitive)
            || sFilename.endsWith(".xbm", Qt::CaseInsensitive)
            || sFilename.endsWith(".xpm", Qt::CaseInsensitive)

            ){
                element = new QTreeWidgetItem(EXTERN_my_mainwindow->_image2, QStringList(""));
                element->setIcon(0, kbasicIcon(sFilename));   

                a = qmenu->addAction(kbasicIcon(sFilename), fi.fileName());
                connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
                EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

            } else {
                a = qmenu->addAction(fi.fileName());
                connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
                EXTERN_my_mainwindow->projectlistMapper->setMapping(a, sFilename);

                element = new QTreeWidgetItem(EXTERN_my_mainwindow->_other2, QStringList(""));

            }

          element->setText(0, fi.fileName());
          element->setText(1, sFilename);
          element->setText(2, ext);
          element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);
        //  element->setRenameEnabled (0, true);



//          element->setRenameEnabled (0, true);
/*
          QFile f(fi.absoluteFilePath());
          if (f.open(QFile::ReadOnly)){
	          QTextStream t(&f);
              t.setCodec("UTF-8");
              t.setAutoDetectUnicode(true);
              t.setGenerateByteOrderMark(true);

              s = t.readAll();
              s = s.replace("\r", "");
	          f.close();
            if (sText.contains("Function Main", false)){
               element->setText(0, element->text(0) + tr("         has 'Function Main()'"));
            }
            f.close();
          }
          */
        }
      }

    }

    }

  }

  if (EXTERN_my_mainwindow->_form2/* && CurrentDatabase.isOpen()*/){

    //QStringList l = CurrentDatabase.tables();

    foreach(QString s, l){
      s = EXTERN_my_mainwindow->getProjectPath()+ "/" + s + ".kbasic_table";
      if (!EXTERN_my_mainwindow->existsTableFile(s)){
        QTreeWidgetItem *element = new QTreeWidgetItem(EXTERN_my_mainwindow->_table2, QStringList(""));
        element->setIcon(0, kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE_asynchron.png")));          

        element->setText(0, EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(s));
        element->setText(1, s);
        element->setText(2, "kbasic_table");
        element->setFlags(Qt::ItemIsSelectable/* | Qt::ItemIsEditable*/ | Qt::ItemIsEnabled);

        a = qmenu->addAction(kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE_asynchron.png")), s);
        connect(a, SIGNAL(triggered()), EXTERN_my_mainwindow->projectlistMapper, SLOT(map()));
        EXTERN_my_mainwindow->projectlistMapper->setMapping(a, s);

      }
    }
    /*
    QString sName = EXTERN_my_mainwindow->first();
    if (sName.length()){
      do {
        if (sName.endsWith(".kbasic_table", Qt::CaseInsensitive)){
        }
        sName = EXTERN_my_mainwindow->next();
      } while (sName.length());     
    }
    */
  }


  bInit = false;
  aAll->setChecked(true);
  /*
  tb->setCurrentIndex(0);
  */
  return files.size();
}

void _projectwindow::itemDoubleClicked(QTreeWidgetItem *item, int column)
{
 
  bool bRe = true;
  QTreeWidgetItem *p = item->parent();
re:
  if (p == 0) return;
  bool bExtraFile = column == -9999;    

  if (p == EXTERN_my_mainwindow->_form2){
    EXTERN_my_mainwindow->openForm(item->text(1));
    if (bExtraFile){
      QString s = item->text(1);
      if (!EXTERN_my_mainwindow->isFormClassFileOpened(s, true)){
        EXTERN_my_mainwindow->openFormClassSourceCode(s);
      }
    }

  } else if (p == EXTERN_my_mainwindow->_table2){
    EXTERN_my_mainwindow->openTable(item->text(1));
    if (bExtraFile){
      if (!EXTERN_my_mainwindow->isDataFileOpened(item->text(1), true)){
        EXTERN_my_mainwindow->openDataFile(item->text(1));
      }
    }
  } else if (p == EXTERN_my_mainwindow->_query2){
    EXTERN_my_mainwindow->openQuery(item->text(1));

  } else if (p == EXTERN_my_mainwindow->_class2){
    EXTERN_my_mainwindow->openClass(item->text(1));
  } else if (p == EXTERN_my_mainwindow->_module2){
    EXTERN_my_mainwindow->openModule(item->text(1));
  } else if (p == EXTERN_my_mainwindow->_menubar2){
    EXTERN_my_mainwindow->openMenuBar(item->text(1));
    if (bExtraFile){
      if (!EXTERN_my_mainwindow->isMenuBarClassFileOpened(item->text(1), true)){
        EXTERN_my_mainwindow->openMenuBarClassSourceCode(item->text(1));
      }
    }
  } else if (p == EXTERN_my_mainwindow->_toolbar2){
    EXTERN_my_mainwindow->openToolBar(item->text(1));
    if (bExtraFile){
      if (!EXTERN_my_mainwindow->isToolBarClassFileOpened(item->text(1), true)){
        EXTERN_my_mainwindow->openToolBarClassSourceCode(item->text(1));
      }
    }
  } else if (p == EXTERN_my_mainwindow->_report2){
    EXTERN_my_mainwindow->openReport(item->text(1));
    if (bExtraFile){
      if (!EXTERN_my_mainwindow->isReportClassFileOpened(item->text(1), true)){
        EXTERN_my_mainwindow->openReportClassSourceCode(item->text(1));
      }
    }
  } else if (p == EXTERN_my_mainwindow->_other2 || p == EXTERN_my_mainwindow->_image2){
    QString s = item->text(1);

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
    ){
      QDesktopServices::openUrl(QUrl("file:///" + s));

    } else if (s.endsWith(".html", Qt::CaseInsensitive) 
      || s.endsWith(".htm", Qt::CaseInsensitive) 
    ){

      QDesktopServices::openUrl(QUrl("file:///" + s));
    } else {
      EXTERN_my_mainwindow->openOther(s);
    }

  } else {
    if (bRe){
      bRe = false;
      if (p) p = p->parent();
      goto re;
    }
  }

  
}

extern bool bLockDirectoryChanged;
void _projectwindow::refresh()
{
  bool b = bLockDirectoryChanged;
  bLockDirectoryChanged = true;

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  createTree();
  load();  
  EXTERN_qbe_tables->refresh();
  focusInEvent(0);
  QApplication::restoreOverrideCursor();

  bLockDirectoryChanged = b;
}

void _projectwindow::itemChanged(QTreeWidgetItem *item, int column)
{  
  
  
  if (bInit) return;

  QString s = item->text(1);
  if (s == "") return; // WORKAROUND
  bInit = true;
  QString c = EXTERN_my_mainwindow->getFilenamePath(s)+ "/" + EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(item->text(0)) + "." + EXTERN_my_mainwindow->getFilenameExtension(s);  


  QList<QMdiSubWindow *> windows = EXTERN_my_mainwindow->workspace->subWindowList();
  

  int mm = windows.size();
  for (int i = 0; i < windows.size(); i++) {
    {

      _form *o;

      if ((o = qobject_cast<_form *>(windows.at(i)->widget()))){
        QString k = o->getFilename();
        if (k == s){
          o->close();
          break;
        }
      }
    }
    {
      _sourcecodeeditor *o;

      if ((o = qobject_cast<_sourcecodeeditor *>(windows.at(i)->widget()))){
        QString k = o->getFilename();
        if (k == s){
          o->close();
          break;
        }
      }
    }
    {
      _report *o;

      if ((o = qobject_cast<_report *>(windows.at(i)->widget()))){
        QString k = o->getFilename();
        if (k == s){
          o->close();
          break;
        }
      }
    }
    {
      _menubar *o;

      if ((o = qobject_cast<_menubar *>(windows.at(i)->widget()))){
        QString k = o->getFilename();
        if (k == s){
          o->close();
          break;
        }
      }
    }
    {
      _toolbar *o;

      if ((o = qobject_cast<_toolbar *>(windows.at(i)->widget()))){
        QString k = o->getFilename();
        if (k == s){
          o->close();
          break;
        }
      }
    }
    {
      _table *o;

      if ((o = qobject_cast<_table *>(windows.at(i)->widget()))){
        QString k = o->getFilename();
        if (k == s){
          o->close();
          break;
        }
      }
    }


  }
  QString ss = s.endsWith(".kbasic_form", Qt::CaseInsensitive) ? "ide/PROJECT_NEW_FORM.png" : s.endsWith(".kbasic_class", Qt::CaseInsensitive) ? "ide/PROJECT_NEW_CLASS.png" : "";
  if (EXTERN_my_mainwindow->insertFile(item->parent(), s, EXTERN_my_mainwindow->getFilenameExtension(s), ss, "", c)){  
    EXTERN_my_mainwindow->deleteFile(s);

    if (s.endsWith(".kbasic_table", Qt::CaseInsensitive)){
      QSqlQuery r;
     
      s = "ALTER TABLE " + EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(s) + " RENAME TO " + EXTERN_my_mainwindow->getFilenameWithoutPath(item->text(0)) + ";";
      if (!r.exec(s)){ QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s); }
    }

    refresh();
  }
  bInit = false;
  
}


void _projectwindow::currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous )
{
  EXTERN_my_mainwindow->EDIT_CUT->setEnabled(cutAvailable());
  EXTERN_my_mainwindow->EDIT_COPY->setEnabled(copyAvailable());
  EXTERN_my_mainwindow->EDIT_PASTE->setEnabled(pasteAvailable());
  EXTERN_my_mainwindow->EDIT_DELETE->setEnabled(deleteAvailable());


}

void _projectwindow::itemSelectionChanged()
{
  focusInEvent(0);  
}

bool _projectwindow::cutAvailable()
{
  QTreeWidgetItem *l = 0;

  if (EXTERN_my_mainwindow->tree->hasFocus()){
    l = EXTERN_my_mainwindow->tree->currentItem();
  }

  if (
    l != EXTERN_my_mainwindow->_project2 
    && l != EXTERN_my_mainwindow->_table2 
    && l != EXTERN_my_mainwindow->_query2 
    && l != EXTERN_my_mainwindow->_form2 
    && l != EXTERN_my_mainwindow->_class2 
    && l != EXTERN_my_mainwindow->_module2 
    && l !=EXTERN_my_mainwindow->_image2
    && l !=EXTERN_my_mainwindow->_other2
    && l !=EXTERN_my_mainwindow->_menubar2
    && l !=EXTERN_my_mainwindow->_toolbar2
    && l !=EXTERN_my_mainwindow->_report2
    && l
    ){
    return true;
  }

  return false;
}

bool _projectwindow::pasteAvailable()
{
  return EXTERN_my_mainwindow->sCopy.length() > 0 || EXTERN_my_mainwindow->sCut.length() > 0;
}

void _projectwindow::customContextMenuRequested ( const QPoint & pos )
{
  if (!cutAvailable()) return;

  QMenu contextMenu(this);

  QAction *a = 0;

  a = contextMenu.addAction(kbasicIcon(kbasicPath("ide/FILE_OPEN_FILE.png")), tr("&Open"), (QWidget *) this, SLOT(event_OPEN()));
  QFont f = a->font();
  f.setBold(true);
  a->setFont(f);

  QTreeWidgetItem *t = EXTERN_my_mainwindow->tree->currentItem();
  
  QString s = t->text(1);

  if (
    s.endsWith(".kbasic_table", Qt::CaseInsensitive)
    ){
    a = contextMenu.addAction(tr("&Data"), (QWidget *) this, SLOT(event_OPEN2()));
  }  
  else if (
    s.endsWith(".kbasic_form", Qt::CaseInsensitive)
    || s.endsWith(".kbasic_report", Qt::CaseInsensitive)
    || s.endsWith(".kbasic_menubar", Qt::CaseInsensitive)
    || s.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)
    ){
    a = contextMenu.addAction(tr("&Source Code"), (QWidget *) this, SLOT(event_OPEN2()));
  }  

  contextMenu.addSeparator();

#ifdef MAC
  a = contextMenu.addAction(tr("Cu&t"), (QWidget *) this, SLOT(event_EDIT_CUT()), QKeySequence("CTRL+X"));
  a = contextMenu.addAction(tr("&Copy"), (QWidget *) this, SLOT(event_EDIT_COPY()), QKeySequence("CTRL+C"));
  a = contextMenu.addAction(tr("&Paste"), (QWidget *) this, SLOT(event_EDIT_PASTE()), QKeySequence("CTRL+V"));
#else
  a = contextMenu.addAction(kbasicIcon(kbasicPath("ide/EDIT_CUT.png")), tr("Cu&t"), (QWidget *) this, SLOT(event_EDIT_CUT()), QKeySequence("CTRL+X"));
  a = contextMenu.addAction(kbasicIcon(kbasicPath("ide/EDIT_COPY.png")), tr("&Copy"), (QWidget *) this, SLOT(event_EDIT_COPY()), QKeySequence("CTRL+C"));
  a = contextMenu.addAction(kbasicIcon(kbasicPath("ide/EDIT_PASTE.png")), tr("&Paste"), (QWidget *) this, SLOT(event_EDIT_PASTE()), QKeySequence("CTRL+V"));
#endif
  a->setEnabled(!EXTERN_my_mainwindow->sCut.isEmpty() || !EXTERN_my_mainwindow->sCopy.isEmpty());

  contextMenu.addSeparator();
  a = contextMenu.addAction(tr("R&ename"), (QWidget *) this, SLOT(event_RENAME()));
  contextMenu.addSeparator();

  a = contextMenu.addAction(tr("&Delete"), (QWidget *) this, SLOT(event_EDIT_DELETE()));    

  contextMenu.exec(QCursor::pos());
}

void _projectwindow::event_OPEN()
{ 
  QList<QTreeWidgetItem *>l = EXTERN_my_mainwindow->tree->selectedItems();
  for (int i = 0; i < l.size(); ++i) {
    QTreeWidgetItem *it = l.at(i);
    itemDoubleClicked(it, 0);
    break;
  }
}

void _projectwindow::event_OPEN2()
{ 
  QList<QTreeWidgetItem *>l = EXTERN_my_mainwindow->tree->selectedItems();
  for (int i = 0; i < l.size(); ++i) {
    QTreeWidgetItem *it = l.at(i);
    itemDoubleClicked(it, -9999);
    break;
  }
}

void _projectwindow::event_RENAME()
{ 
goo:
  bool b;
  QString text = QInputDialog::getText(this, tr("Rename"), tr("Enter the new name:"), QLineEdit::Normal, QString::null, &b);
  if (b && !text.isEmpty()){
    if (!checkObjectName(text)) goto goo;
    
    
    QList<QTreeWidgetItem *>l = EXTERN_my_mainwindow->tree->selectedItems();
    for (int i = 0; i < l.size(); ++i) {
      QTreeWidgetItem *it = l.at(i);
      it->setText(0, text);
      //itemChanged(it, 0);
      break;
    }
    
  }  
}

void _projectwindow::event_REFRESH()
{ 
  refresh();
}

void _projectwindow::event_EDIT_CUT()
{ 
  EXTERN_my_mainwindow->cutFile();
  focusInEvent(0);
}

void _projectwindow::event_EDIT_COPY()
{ 
  EXTERN_my_mainwindow->copyFile();
  focusInEvent(0);
}

void _projectwindow::event_EDIT_PASTE()
{ 
  EXTERN_my_mainwindow->pasteFile();
}

void _projectwindow::event_EDIT_DELETE()
{ 
  EXTERN_my_mainwindow->deleteFile();
  focusInEvent(0);
}

void _projectwindow::focusOutEvent(QFocusEvent *e)
{
  if (((QDockWidget *) parentWidget())->isFloating()){
    hide();
  }
  if (e) QWidget::focusOutEvent(e);
}

void _projectwindow::focusInEvent(QFocusEvent *e)
{

  EXTERN_my_mainwindow->updateGeneralActions(
   false,  false,  false,  true, 
   false,  false,  false,  false,  false,   
   false,  false,  false, 
   false,  false,  false,  false, 
   false, ""
  );

  EXTERN_my_mainwindow->EDIT_CUT->setEnabled(cutAvailable());
  EXTERN_my_mainwindow->EDIT_COPY->setEnabled(copyAvailable());
  EXTERN_my_mainwindow->EDIT_PASTE->setEnabled(pasteAvailable());
  EXTERN_my_mainwindow->EDIT_DELETE->setEnabled(deleteAvailable());


  if (e) QWidget::focusInEvent(e);
}

void _projectwindow::settingdb()
{
  EXTERN_my_mainwindow->event_PROJECT_DATABASE();  
}

void _projectwindow::showProjectName(const QString &s)
{
  QString ss = s;
  if (!ss.simplified().isEmpty()){
    if (EXTERN_my_mainwindow->getProjectPreference("dbdriver").isEmpty()){
      ss += tr("");
    } else if (!CurrentDatabase.isOpen()){
      ss += tr(" (not connected)");
    } else {
      ss += tr(" (connected)");
    }
  }

  currentprojectname->setText(ss);
}


QTreeWidgetItem *_projectwindow::getParentTreeWidgetItem(QTreeWidgetItem *normal, QString & sFilename, int pass, QString & sLanguage)
{
  QString sExt = EXTERN_my_mainwindow->getFilenameExtension(sFilename);
  QString q = sFilename.left(sFilename.length() - sExt.length() - 1);

  if (q.count(".") > 1){

    sLanguage = EXTERN_my_mainwindow->getFilenameExtension(q);
    if (trl.contains(sLanguage)){

      if (pass == 0 || !EXTERN_my_mainwindow->sCurrentLanguage.isEmpty()) return 0;

      QString sEnglish = q.left(q.length() - sLanguage.length() - 1) + "." + sExt;

      int n = normal->childCount();
      for (int i = 0; i < n; i++){
        if (normal->child(i)->text(1) == sEnglish){
//          sFilename = sEnglish;
          return normal->child(i);
        }
      }
      
      sLanguage = "";
      return 0;

    }
  }
  sLanguage = "";
  return normal;
}

void _projectwindow::actionSelected()
{
  if (EXTERN_my_mainwindow->_form2 == 0) return;

  QAction *a = ag->checkedAction();

  if (a->text().compare(tr("All"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(true);
      EXTERN_my_mainwindow->_class2->setExpanded(true);
      EXTERN_my_mainwindow->_module2->setExpanded(true);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(true);
      EXTERN_my_mainwindow->_query2->setExpanded(true);
      EXTERN_my_mainwindow->_menubar2->setExpanded(true);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(true);
      EXTERN_my_mainwindow->_report2->setExpanded(true);
   } else if (a->text().compare(tr("Forms"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(true);
      EXTERN_my_mainwindow->_class2->setExpanded(false);
      EXTERN_my_mainwindow->_module2->setExpanded(false);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(false);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(false);
      EXTERN_my_mainwindow->_report2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(false);
      EXTERN_my_mainwindow->_query2->setExpanded(false);
   } else if (a->text().compare(tr("Classes"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(false);
      EXTERN_my_mainwindow->_class2->setExpanded(true);
      EXTERN_my_mainwindow->_module2->setExpanded(false);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(false);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(false);
      EXTERN_my_mainwindow->_report2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(false);
      EXTERN_my_mainwindow->_query2->setExpanded(false);
   } else if (a->text().compare(tr("Modules"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(false);
      EXTERN_my_mainwindow->_class2->setExpanded(false);
      EXTERN_my_mainwindow->_module2->setExpanded(true);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(false);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(false);
      EXTERN_my_mainwindow->_report2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(false);
      EXTERN_my_mainwindow->_query2->setExpanded(false);
   } else if (a->text().compare(tr("Tables"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(false);
      EXTERN_my_mainwindow->_class2->setExpanded(false);
      EXTERN_my_mainwindow->_module2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(false);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(true);
      EXTERN_my_mainwindow->_query2->setExpanded(false);
      EXTERN_my_mainwindow->_report2->setExpanded(false);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
   } else if (a->text().compare(tr("Queries"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(false);
      EXTERN_my_mainwindow->_class2->setExpanded(false);
      EXTERN_my_mainwindow->_module2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(false);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(false);
      EXTERN_my_mainwindow->_query2->setExpanded(true);
      EXTERN_my_mainwindow->_report2->setExpanded(false);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
   } else if (a->text().compare(tr("Reports"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(false);
      EXTERN_my_mainwindow->_class2->setExpanded(false);
      EXTERN_my_mainwindow->_module2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(false);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(false);
      EXTERN_my_mainwindow->_report2->setExpanded(true);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(false);
      EXTERN_my_mainwindow->_query2->setExpanded(false);
   } else if (a->text().compare(tr("Menubars"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(false);
      EXTERN_my_mainwindow->_class2->setExpanded(false);
      EXTERN_my_mainwindow->_module2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(true);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(false);
      EXTERN_my_mainwindow->_report2->setExpanded(false);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(false);
      EXTERN_my_mainwindow->_query2->setExpanded(false);
   } else if (a->text().compare(tr("Toolbars"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(false);
      EXTERN_my_mainwindow->_class2->setExpanded(false);
      EXTERN_my_mainwindow->_module2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(false);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(true);
      EXTERN_my_mainwindow->_report2->setExpanded(false);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(false);
      EXTERN_my_mainwindow->_query2->setExpanded(false);
   } else if (a->text().compare(tr("Images"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(false);
      EXTERN_my_mainwindow->_class2->setExpanded(false);
      EXTERN_my_mainwindow->_module2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(false);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(false);
      EXTERN_my_mainwindow->_report2->setExpanded(false);
      EXTERN_my_mainwindow->_image2->setExpanded(true);
      EXTERN_my_mainwindow->_other2->setExpanded(false);
      EXTERN_my_mainwindow->_table2->setExpanded(false);
      EXTERN_my_mainwindow->_query2->setExpanded(false);
   } else if (a->text().compare(tr("Others"), Qt::CaseInsensitive) == 0){
      EXTERN_my_mainwindow->_form2->setExpanded(false);
      EXTERN_my_mainwindow->_class2->setExpanded(false);
      EXTERN_my_mainwindow->_module2->setExpanded(false);
      EXTERN_my_mainwindow->_menubar2->setExpanded(false);
      EXTERN_my_mainwindow->_toolbar2->setExpanded(false);
      EXTERN_my_mainwindow->_report2->setExpanded(false);
      EXTERN_my_mainwindow->_image2->setExpanded(false);
      EXTERN_my_mainwindow->_other2->setExpanded(true);
      EXTERN_my_mainwindow->_table2->setExpanded(false);
      EXTERN_my_mainwindow->_query2->setExpanded(false);
   }
}