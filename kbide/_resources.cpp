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


#include "_resources.h"
#include "_mainwindow.h"
#include "_projectwindow.h"
#include "_typedef.h"
extern QString idePath(QString s);
extern const QIcon &kbasicIcon(QString s);
extern _mainwindow *EXTERN_my_mainwindow;
extern _projectwindow *EXTERN_my_projectwindow;

QString sSelectedResource;

_resources::_resources(QWidget* _parent) : QDialog(_parent)
{
  
  setWindowFlags(windowFlags() | Qt::Dialog);

  sButton = "";
  sSelectedResource = "";

  QVBoxLayout *j = new QVBoxLayout();
  
    setLayout(j);
    j->setMargin(0);
    j->setSpacing(0);


  tab = new QTabWidget(); j->addWidget(tab);



  my_mainwindow = EXTERN_my_mainwindow;

  resize(480, 480);
  setWindowTitle(tr("Resources"));
  setModal(true);
  
  QWidget *f = new QWidget();
  QHBoxLayout *fj = new QHBoxLayout();
  f->setLayout(fj);
  j->addWidget(f);
 
  QPushButton *p;
  p = new QPushButton(tr("&Copy into project folder"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(performSave()) );

  p = new QPushButton(tr("&Close"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(performClose()) );

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  kbasic(); 
  vista(); 
  actions(); 
  apps(); 
  devices(); 
  filesystems(); 
  mimetypes(); 
  kids_apps(); 
  kids_devices(); 
  kids_filesystems(); 
  kids_mimetypes(); 

  

 
  move(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2);
  show();

  QApplication::restoreOverrideCursor();
  
}

_resources::~_resources()
{
  sSelectedResource = "KBASIC_EXIT.XYZ";
}

void _resources::kbasic()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        if (!ss.endsWith(".png", Qt::CaseInsensitive)) continue;
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, MYAPP);
}

void _resources::vista()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/vista/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        if (!ss.endsWith(".png", Qt::CaseInsensitive)) continue;
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("Vista"));
}

void _resources::actions()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/actions/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("actions"));
}


void _resources::apps()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/apps/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("apps"));
}

void _resources::devices()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/devices/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("devices"));
}

void _resources::filesystems()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/filesystems/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("filesystems"));
}

void _resources::mimetypes()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/mimetypes/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("mimetypes"));
}


void _resources::kids_apps()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/kids_apps/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("kids_apps"));
}

void _resources::kids_devices()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/kids_devices/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("kids_devices"));
}

void _resources::kids_filesystems()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/kids_filesystems/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("kids_filesystems"));
}

void _resources::kids_mimetypes()
{
  QWidget *w = new QWidget();
  setAutoFillBackground(true);

  QScrollArea *a = new QScrollArea(this);
  a->setWidget(w);
  a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  a->setWidgetResizable(true);

  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  p.setColor(QPalette::Base, Qt::white);  
  p.setColor(QPalette::Button, Qt::white);            
  w->setPalette(p);

  QGridLayout *grid = new QGridLayout(this);
  grid->setMargin(1);
  grid->setSpacing(1);
  w->setLayout(grid);

  QPushButton *b;
  int x = 0;
  int y = 0;

  QDir thisDir( idePath("user_icons/kids_mimetypes/") );	
  QFileInfoList files = thisDir.entryInfoList();

  if (files.size()){

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i){
      fi = files.at(i);

      if (fi.fileName() == "." || fi.fileName() == "..");
      else if (fi.isSymLink());
      else if (fi.isDir());
      else {
        
        QString ss = fi.fileName();
        QString s = fi.absoluteFilePath();

        b = new QPushButton(kbasicIcon(s), tr(""), w); b->setToolTip(ss); b->setStatusTip(s); b->setFlat(true); b->setIconSize(QSize(16, 16)); b->setFixedSize(QSize(18, 18)); grid->addWidget(b, y, x); x++; if (x > 10){ x = 0; y++; }; connect(b, SIGNAL(clicked(bool)), this, SLOT(clicked()));

      }		    
	  }
  
  }   
  
  tab->addTab(a, tr("kids_mimetypes"));
}



void _resources::clicked()
{
  QWidget *w = QApplication::focusWidget();
  QPushButton *o = qobject_cast<QPushButton *>(w);
  if (o){
    sButton = o->statusTip();
  }
}

void _resources::performSave()
{
  QWidget *w = QApplication::focusWidget();
  QPushButton *o = qobject_cast<QPushButton *>(w);
  if (o){
    QString sPath = EXTERN_my_mainwindow->getProjectPath();
    sPath += "/";
    sPath += EXTERN_my_mainwindow->getFilenameWithoutPath(sButton);

    EXTERN_my_mainwindow->copyFile(sButton, sPath);
    EXTERN_my_projectwindow->refresh();

    sSelectedResource = sButton;
  }

  close();  
}

void _resources::performClose()
{  
  close();  
}  
