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

#include "_newproject.h"
#include "_mainwindow.h"
#include "_typedef.h"

extern _mainwindow *EXTERN_my_mainwindow;

_newproject::_newproject(QWidget* _parent, int *_nType) : QDialog(_parent)
{
  nType = _nType;

  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Dialog);

  parent = _parent;
  my_mainwindow = (_mainwindow *) parent;

  setWindowTitle(tr("New Project"));
  setModal(true);

  setupGeneral();  

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);  
}
void _newproject::setupGeneral()
{


    

    QVBoxLayout *j = new QVBoxLayout();
    
      setLayout(j);
     

    bool t = false;

    QLabel *l;
    l = new QLabel(
    tr("'Let's start!'\n"
                  "\n"
                  "\n"
                  "Within a KBasic project you can create modules,\n"
                  "classes and forms but also menus and toolbars.\n" // 
                  ""));
     j->addWidget(l);


    QWidget *d2 = new QWidget(); j->addWidget(d2);
    QHBoxLayout *dl2 = new QHBoxLayout();
    d2->setLayout(dl2);

    
    l = new QLabel(tr("Name of project: "), d2); dl2->addWidget(l);
    l->setMinimumWidth(100);
    
    source = new QLineEdit(d2); dl2->addWidget(source);
    ((QLineEdit *) (source))->setDisabled(t);
    ((QLineEdit *) (source))->setText( "" );
    source->setMinimumWidth(200);

    QWidget *d3 = new QWidget(); j->addWidget(d3);
    QHBoxLayout *dl3 = new QHBoxLayout();
    d3->setLayout(dl3);

    l = new QLabel(tr("Path: "), d3); dl3->addWidget(l);
    l->setMinimumWidth(100);
    
    destination = new QLineEdit(d3); dl3->addWidget(destination);
    ((QLineEdit *) (destination))->setDisabled(t);

#ifdef WINDOWS
       ((QLineEdit *) (destination))->setText(QDir::homePath() + "/Desktop"); // HIDE
#else
       ((QLineEdit *) (destination))->setText(QDir::homePath());
#endif

    destination->setMinimumWidth(200);
    
    QPushButton *p;
    p = new QPushButton("...", d3); dl3->addWidget(p);
    p->setMaximumWidth(30);
    p->setDisabled(t);

    connect(p,  SIGNAL( clicked ( ) ),  this, SLOT( clicked2(  ) ) );



    QWidget *d4 = new QWidget(); j->addWidget(d4);
    QHBoxLayout *dl4 = new QHBoxLayout();
    d4->setLayout(dl4);

    l = new QLabel(tr("Project Type: "), d4); dl4->addWidget(l);
    l->setMinimumWidth(100);
    
    ptype = new QComboBox(d4); dl4->addWidget(ptype);
    ptype->addItem(tr("Empty Project"));
    ptype->addItem(tr("MDI Application with menubar and toolbar"));
    ptype->addItem(tr("SDI Application with menubar and toolbar"));
    ptype->addItem(tr("One main form and one module"));


    
    QFrame *ff = new QFrame(); ff->setFrameShape(QFrame::HLine); ff->setFrameShadow(QFrame::Sunken); j->addWidget(ff);


    QWidget *f = new QWidget(); j->addWidget(f);
    QHBoxLayout *fj = new QHBoxLayout();
    f->setLayout(fj);
    
#ifdef MAC

    p = new QPushButton(tr("&Cancel"), f); fj->addWidget(p);
    connect(p, SIGNAL( clicked() ), this, SLOT(cancel()) );

    p = new QPushButton(tr("&Create Project"), f); fj->addWidget(p);
    connect(p, SIGNAL( clicked() ), this, SLOT(ok()) );
#else
    p = new QPushButton(tr("&Create Project"), f); fj->addWidget(p);
    connect(p, SIGNAL( clicked() ), this, SLOT(ok()) );

    p = new QPushButton(tr("&Cancel"), f); fj->addWidget(p);
    connect(p, SIGNAL( clicked() ), this, SLOT(cancel()) );
#endif

    
}

void _newproject::cancel()
{
  close();
}

void _newproject::clicked2()
{     
  QString fn = QFileDialog::getExistingDirectory(this);

  if (!fn.isEmpty()){
    ((QLineEdit *) (destination))->setText(fn + "/");
  }  
}

void _newproject::ok()
{

  *nType = ptype->currentIndex();

  if (getPath().simplified().isEmpty()){
QMessageBox::information(this, tr("New Project"),
tr(
"Please enter the path for the new project first. ")
);
    destination->setFocus();
    return;
  }

  if (getName().simplified().isEmpty()){
QMessageBox::information(this, tr("New Project"),
tr(
"Please enter the name for the new project first. ")
);
    source->setFocus();
    return;
  }

  QString s = getPath() + getName() + ".kbasic_project";
  s = s.replace("\\", "/");

  if (QFile::exists(s)){
QMessageBox::information(this, tr("New Project"),
tr(
"Project already exists. Please change the project path or name. ")
);
    destination->setFocus();
    return;
  }

  EXTERN_my_mainwindow->createDir(s);
   if (!QFile::exists(s)){
QMessageBox::information(this, tr("New Project"),
tr(
"Could not create new directory. Have you selected an existing directory?")
);
     destination->setFocus();
     return;
   }

 EXTERN_my_mainwindow->closeProject();

  s = getPath() + getName() + ".kbasic_project/" + getName() + ".kbasic_project";
  s = s.replace("\\", "/");

  EXTERN_my_mainwindow->createFile(s);

  EXTERN_my_mainwindow->setProjectPreference("dbdriver", "");

  EXTERN_my_mainwindow->loadProject(s);

  EXTERN_my_mainwindow->setProjectPreference("projectmainformname", "Form1");
  EXTERN_my_mainwindow->setProjectPreference("projecttype", tr("Manually"));
  EXTERN_my_mainwindow->saveProjectPreferences();

  accept();
}

