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

#include "_projectproperties.h"
#include "_mainwindow.h"
#include "_insert.h"
#include "_typedef.h"

extern _mainwindow *EXTERN_my_mainwindow;

_projectproperties::_projectproperties(QWidget* _parent) : QDialog(_parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Dialog);


  setWindowTitle(tr("Project Properties - ") + EXTERN_my_mainwindow->getProjectName());
  setModal(true);

  setupGeneral();  

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
  
}
void _projectproperties::setupGeneral()
{

  QVBoxLayout *j = new QVBoxLayout();
  setLayout(j);

  bool t = false;

  QLabel *l;
  /*
  l = new QLabel(EXTERN_my_mainwindow->getProjectName()); j->addWidget(l);
  {
    QFont f = l->font();
    f.setBold(true);
    l->setFont(f);
  }*/

  j->addWidget(new QWidget());
  l = new QLabel(tr("Change the following Properties: ")); j->addWidget(l);



  QGridLayout *g = new QGridLayout();
  j->addLayout(g);
  int y = 0;

  l = new QLabel(""); g->addWidget(l, y++, 0, 1, 1);


  l = new QLabel(tr("Name: ")); g->addWidget(l, y, 0);
  {
    QFont f = l->font();
    f.setBold(true);
    l->setFont(f);
  }


  QComboBox *d;
  projectname = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->setMinimumWidth(200);
  d->addItem(tr("Default Project"));


  l = new QLabel(tr("Project's Main Form Name: ")); g->addWidget(l, y, 0);
  {
    QFont f = l->font();
    f.setBold(true);
    l->setFont(f);
  }
  projectmainformname = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->setMinimumWidth(200);    


  if (EXTERN_my_mainwindow->isProject()){    
    QString sName = EXTERN_my_mainwindow->first();
    if (sName.length()){
      do {
        if (sName.endsWith(".kbasic_form", Qt::CaseInsensitive)){
          d->addItem(EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(sName));
        }
        sName = EXTERN_my_mainwindow->next();
      } while (sName.length());     
    }
  }
  //d->addItem("Form1");
  //d->addItem("myForm");

  d->addItem("Function Main()");

  l = new QLabel(tr("Project Type: ")); g->addWidget(l, y, 0);
  {
    QFont f = l->font();
    f.setBold(true);
    l->setFont(f);
  }
  projecttype = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(false);
  d->setMinimumWidth(200);     
  d->addItem(tr("With MDI MainWindow (you must have myMenuBar created)"));
  d->addItem(tr("With SDI MainWindow (you must have myMenuBar created)"));
  d->addItem(tr("Manually"));

  l = new QLabel(tr("Login Form: ")); g->addWidget(l, y, 0);
  login = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->setMinimumWidth(200);
  d->addItem("");
  d->addItem("Form1");
  d->addItem("myForm");

  l = new QLabel(""); g->addWidget(l, y++, 0, 1, 1);


  l = new QLabel(tr("Company / Author's Name: ")); g->addWidget(l, y, 0);
  projectcompanyname = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->setMinimumWidth(200);
  d->addItem(tr("BASIC enthusiast"));


  l = new QLabel(tr("Project License: ")); g->addWidget(l, y, 0);
  projectlicense = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->setMinimumWidth(200);
  d->addItem("GPL");
  d->addItem("LGPL");
  d->addItem("BSD");
  d->addItem("Commercial");
  d->addItem("Free");
  d->addItem("Special");

  l = new QLabel(tr("Contact Email: ")); g->addWidget(l, y, 0);
  projectcontactemail = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->setMinimumWidth(200);
  d->addItem("yourname@yourwebsite.org");


  l = new QLabel(tr("Website: ")); g->addWidget(l, y, 0);
  projectwebsite = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->setMinimumWidth(200);
  d->addItem("http://www.yourwebsite.org/");


  l = new QLabel(""); g->addWidget(l, y++, 0, 1, 1);


  l = new QLabel(tr("Activate Menu: ")); j->addWidget(l);

  menuRecords = new QCheckBox(tr("Records (for MDI only)")); j->addWidget(menuRecords);
  menuWindow = new QCheckBox(tr("Window (for MDI only)")); j->addWidget(menuWindow);
  menuHelp = new QCheckBox(tr("Help (for MDI only)")); j->addWidget(menuHelp);

  
  QFrame *ff = new QFrame(); ff->setFrameShape(QFrame::HLine); ff->setFrameShadow(QFrame::Sunken); j->addWidget(ff);

  
  QWidget *f = new QWidget(); j->addWidget(f);
  QHBoxLayout *fj = new QHBoxLayout();
  f->setLayout(fj);
  
  QPushButton *p;
#ifdef MAC

  p = new QPushButton(tr("&Cancel"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(cancel()) );
  p->setMaximumWidth(80);

  p = new QPushButton(tr("&Save"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(ok()) );
  p->setMaximumWidth(80);


#else
  p = new QPushButton(tr("&Save"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(ok()) );
  p->setMaximumWidth(80);

  p = new QPushButton(tr("&Cancel"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(cancel()) );
  p->setMaximumWidth(80);


#endif


  if (EXTERN_my_mainwindow->getProjectPreference("projectname").length()){
    projectname->setEditText (EXTERN_my_mainwindow->getProjectPreference("projectname"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("projectcompanyname").length()){
    projectcompanyname->setEditText (EXTERN_my_mainwindow->getProjectPreference("projectcompanyname"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("projectlicense").length()){
    projectlicense->setEditText (EXTERN_my_mainwindow->getProjectPreference("projectlicense"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("projectmainformname").length()){
    projectmainformname->setEditText (EXTERN_my_mainwindow->getProjectPreference("projectmainformname"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("projecttype").length()){
    QString s = EXTERN_my_mainwindow->getProjectPreference("projecttype");

    if (s.contains(tr("With MDI MainWindow (you must have myMenuBar created)"))) projecttype->setCurrentIndex(0);
    else if (s.contains(tr("With SDI MainWindow (you must have myMenuBar created)"))) projecttype->setCurrentIndex(1);
    else if (s.contains(tr("Manually"))) projecttype->setCurrentIndex(2);

  }

  if (EXTERN_my_mainwindow->getProjectPreference("projectcontactemail").length()){
    projectcontactemail->setEditText (EXTERN_my_mainwindow->getProjectPreference("projectcontactemail"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("projectwebsite").length()){
    projectwebsite->setEditText (EXTERN_my_mainwindow->getProjectPreference("projectwebsite"));
  }

  menuRecords->setChecked(EXTERN_my_mainwindow->getProjectPreference("menuRecords") == "Yes");
  menuWindow->setChecked(EXTERN_my_mainwindow->getProjectPreference("menuWindow") == "Yes");
  menuHelp->setChecked(EXTERN_my_mainwindow->getProjectPreference("menuHelp") == "Yes");

  if (EXTERN_my_mainwindow->getProjectPreference("login").length()){
    login->setEditText (EXTERN_my_mainwindow->getProjectPreference("login"));
  }


}

void _projectproperties::ok()
{

  EXTERN_my_mainwindow->setProjectPreference("projectname", projectname->currentText());
  EXTERN_my_mainwindow->setProjectPreference("projectcompanyname", projectcompanyname->currentText());
  EXTERN_my_mainwindow->setProjectPreference("projectlicense", projectlicense->currentText());
  EXTERN_my_mainwindow->setProjectPreference("projectmainformname", projectmainformname->currentText());
  EXTERN_my_mainwindow->setProjectPreference("projecttype", projecttype->currentText());  
  EXTERN_my_mainwindow->setProjectPreference("projectcontactemail", projectcontactemail->currentText());
  EXTERN_my_mainwindow->setProjectPreference("projectwebsite", projectwebsite->currentText());
  EXTERN_my_mainwindow->setProjectPreference("menuRecords", menuRecords->isChecked() ? "Yes" : "No");
  EXTERN_my_mainwindow->setProjectPreference("menuWindow", menuWindow->isChecked() ? "Yes" : "No");
  EXTERN_my_mainwindow->setProjectPreference("menuHelp", menuHelp->isChecked() ? "Yes" : "No");

  EXTERN_my_mainwindow->setProjectPreference("login", login->currentText());

  EXTERN_my_mainwindow->saveProjectPreferences();

  accept();
}

void _projectproperties::cancel()
{
  close();
}
