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

#include "_dbcondialog.h"
#include "_mainwindow.h"
#include "_projectwindow.h"
#include "_insert.h"
#include "_typedef.h"

QSqlDatabase CurrentDatabase;

extern _mainwindow *EXTERN_my_mainwindow;
extern _projectwindow *EXTERN_my_projectwindow;

_dbcondialog::_dbcondialog(QWidget* _parent) : QDialog(_parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Dialog);

  QString ss = "";

  if (EXTERN_my_mainwindow->getProjectPreference("dbdriver").isEmpty()){
    ss += tr("");
  } else if (!CurrentDatabase.isOpen()){
    ss += tr(" (not connected)");
  } else {
    ss += tr(" (connected)");
  }
  setWindowTitle(tr("Database Connection") + ss);

  setModal(true);
  setupGeneral();  

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
  qApp->setActiveWindow(this);
  

  
}
void _dbcondialog::setupGeneral()
{

  QVBoxLayout *j = new QVBoxLayout();
  setLayout(j);

  bool t = false;


  QLabel *l;
  l = new QLabel(tr("Current Project's Database Connection Properties: ")); j->addWidget(l);
  {
    QFont f = l->font();
    f.setBold(true);
    l->setFont(f);
  }


  QGridLayout *g = new QGridLayout();
  g->setColumnStretch(1, 10);

  j->addLayout(g);
  int y = 0;



  l = new QLabel(""); l->setFixedHeight(8);
  g->addWidget(l, y++, 0, 1, 2);
  QComboBox *d;

  l = new QLabel(tr("Driver: ")); g->addWidget(l, y, 0);
  dbdriver = d = new QComboBox(); g->addWidget(d, y++, 1);
  
  d->addItem("");

  QStringList drivers = QSqlDatabase::drivers();
  for (int i = 0; i < drivers.size(); ++i){
    QString k = drivers.at(i);
    if (!k.right(1).at(0).isDigit()){ // filter out old-versions marked with digits and the end
      d->addItem(k);
    }
  }
  QString s = EXTERN_my_mainwindow->getProjectPreference("dbdriver");

  int n = d->findText(s);
  if (n >= 0){
    d->setCurrentIndex(n);
  }

  l = new QLabel(tr("Database Name: ")); g->addWidget(l, y, 0);
  dbname = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->addItem(" ");

  QHBoxLayout *qq = new QHBoxLayout();
  l = new QLabel(tr("Runtime connects automatically: ")); 
  qq->addWidget(l);
  dbsetforruntime = new QCheckBox();
  dbsetforruntime->setChecked(true);
  qq->addWidget(dbsetforruntime);
  g->addLayout(qq, y++, 0, 1, 2);

  qq = new QHBoxLayout();
  l = new QLabel(tr("Runtime creates non-existing tables automatically: ")); 
  qq->addWidget(l);
  dbsettablesforruntime = new QCheckBox();
  dbsettablesforruntime->setChecked(true);
  qq->addWidget(dbsettablesforruntime);
  g->addLayout(qq, y++, 0, 1, 2);


  l = new QLabel(""); l->setFixedHeight(12);
  g->addWidget(l, y++, 0, 1, 2);

  l = new QLabel(tr("User: ")); g->addWidget(l, y, 0);
  dbuser = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->addItem(" ");

  l = new QLabel(tr("Password: ")); g->addWidget(l, y, 0);
  dbuserpassword = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->addItem("");

  l = new QLabel(tr("Host: ")); g->addWidget(l, y, 0);
  dbhost = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->addItem(tr(""));
  d->addItem(tr("localhost"));

  l = new QLabel(tr("Port: ")); g->addWidget(l, y, 0);
  dbport = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  //d->addItem(tr(""));


  l = new QLabel(tr("Options: ")); g->addWidget(l, y, 0);
  dbconnectoptions = d = new QComboBox(); g->addWidget(d, y++, 1);
  d->setEditable(true);
  d->addItem("");

  


  QFrame *ff = new QFrame(); ff->setFrameShape(QFrame::HLine); ff->setFrameShadow(QFrame::Sunken); j->addWidget(ff);

  
    
  QWidget *f = new QWidget(); j->addWidget(f);
  QHBoxLayout *fj = new QHBoxLayout();
  f->setLayout(fj);

  
  QPushButton *p;
/*
  p = new QPushButton(tr("&Save && Create Database"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(createdatabase()) );
*/
  p = new QPushButton(tr("&Embedded (SQLite)"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(embedded()) );

  p = new QPushButton(tr("&No Database"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(nodatabase()) );

  /*
  p = new QPushButton(tr("&Users && Groups"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(nodatabase()) );
  p->setDisabled(true);*/

  f = new QWidget(); j->addWidget(f);
  fj = new QHBoxLayout();
  f->setLayout(fj);

#ifdef MAC

  p = new QPushButton(tr("&Close"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(cancel()) );
  p->setAutoDefault(true);

  p = new QPushButton(tr("&Save"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(ok()) );


#else
  p = new QPushButton(tr("&Save"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(ok()) );

  p = new QPushButton(tr("&Close"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked(bool) ), this, SLOT(cancel()) );
  p->setAutoDefault(true);


#endif


  if (EXTERN_my_mainwindow->getProjectPreference("dbuser").length()){
    dbuser->setEditText (EXTERN_my_mainwindow->getProjectPreference("dbuser"));
    if (dbuser->currentText().isEmpty()) dbuser->setEditText (("kbdefault"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("dbname").length()){
    dbname->setEditText (EXTERN_my_mainwindow->getProjectPreference("dbname"));
    if (dbname->currentText().isEmpty()) dbname->setEditText (("kbdefault"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("dbdriver").length()){
    dbdriver->setEditText (EXTERN_my_mainwindow->getProjectPreference("dbdriver"));
    if (dbdriver->currentText().isEmpty()) dbdriver->setEditText (("SQLITE"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("dbhost").length()){
    dbhost->setEditText (EXTERN_my_mainwindow->getProjectPreference("dbhost"));
    if (dbhost->currentText().isEmpty()) dbhost->setEditText (("localhost"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("dbport").length()){
    dbport->setEditText (EXTERN_my_mainwindow->getProjectPreference("dbport"));
    //if (dbport->currentText().isEmpty()) dbhost->setEditText (("default"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("dbuserpassword").length()){
    dbuserpassword->setEditText (EXTERN_my_mainwindow->getProjectPreference("dbuserpassword"));
    if (dbuserpassword->currentText().isEmpty()) dbuserpassword->setEditText (("kbdefault"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("dbconnectoptions").length()){
    dbconnectoptions->setEditText (EXTERN_my_mainwindow->getProjectPreference("dbconnectoptions"));
  }

  if (EXTERN_my_mainwindow->getProjectPreference("dbsetforruntime").length()){
    dbsetforruntime->setChecked(EXTERN_my_mainwindow->getProjectPreference("dbsetforruntime") == "Yes");
  }

  if (EXTERN_my_mainwindow->getProjectPreference("dbsettablesforruntime").length()){
    dbsettablesforruntime->setChecked(EXTERN_my_mainwindow->getProjectPreference("dbsettablesforruntime") == "Yes");
  }

  
  

    
}

void _dbcondialog::createdatabase()
{
  //dbdriver->setCurrentIndex(0);

  if (!CurrentDatabase.driverName().contains("sqlite", Qt::CaseInsensitive)){

    QSqlQuery r;
    QString s = "";
    s = "CREATE DATABASE " + EXTERN_my_mainwindow->getProjectPreference("dbname") + " WITH OWNER = " + EXTERN_my_mainwindow->getProjectPreference("dbuser");
    if (!r.exec(s)){ QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database completely: \n\n") + s + "\n\n" + r.lastError().text()); return; }

  }

  /*
  

DROP DATABASE kbdb;

CREATE DATABASE kbdb WITH OWNER = kbuser;

GRANT ALL ON DATABASE kbdb TO kbuser;

CREATE USER kbuser IDENTIFIED BY PASSWORD 'kbpassword';

SET PASSWORD FOR kbuser = PASSWORD('kbpassword');

DROP USER kbuser;

*/

  ok();
}

void _dbcondialog::embedded()
{
  int n = dbdriver->findText("QSQLITE");
  if (n >= 0){
    dbdriver->setCurrentIndex(n);
    dbname->setEditText ("./sqlite/sqlite.s3db");
    dbuser->setEditText ("");    
    dbhost->setEditText ("");
    dbport->setEditText ("");    
    dbuserpassword->setEditText("");  
    dbconnectoptions->setEditText("");  

  } else {
    dbdriver->setCurrentIndex(0);
  }
  
  ok();
}


void _dbcondialog::nodatabase()
{
  dbdriver->setCurrentIndex(0); 
  ok();
}

void _dbcondialog::ok()
{
  if (CurrentDatabase.open()){  
    CurrentDatabase.close();
  }

  QString s = dbdriver->currentText();
  if (!s.isEmpty()){
    CurrentDatabase = QSqlDatabase::addDatabase(s);
    CurrentDatabase.setHostName(dbhost->currentText());

    bool bSQLite = false;
    if (CurrentDatabase.driverName().contains("sqlite", Qt::CaseInsensitive)){
      bSQLite = true;
    }

    QString k = "";
    if (bSQLite){
      k = dbname->currentText();      
      if (k.startsWith("./")){
        k = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + k.mid(1);
      } else if (k.startsWith("../")){
        k = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + k.mid(2);
      }
	  QDir d;
	  d.mkpath(EXTERN_my_mainwindow->getFilenamePath(k));
//QMessageBox::information(this, "k=",  k);  
//      k = EXTERN_my_mainwindow->getFilenamePath(EXTERN_my_mainwindow->getProjectName()) + "/sqlite/" + dbname->currentText();      
    } else {
      k = dbname->currentText();
    }

    CurrentDatabase.setDatabaseName(k);
    CurrentDatabase.setUserName(dbuser->currentText());
    CurrentDatabase.setPassword(dbuserpassword->currentText());
    if (!dbport->currentText().isEmpty()) CurrentDatabase.setPort(dbport->currentText().toInt());
    CurrentDatabase.setConnectOptions(dbconnectoptions->currentText());
    if (CurrentDatabase.open()){       
    } else {
      QSqlError e = CurrentDatabase.lastError();
      QMessageBox::information(this, "Error While Connecting To Database",  e.text());  
      return;
    }
  } else {
    CurrentDatabase.close();
  }

  EXTERN_my_mainwindow->setProjectPreference("dbuser", dbuser->currentText());
  EXTERN_my_mainwindow->setProjectPreference("dbname", dbname->currentText());
  EXTERN_my_mainwindow->setProjectPreference("dbdriver", dbdriver->currentText());
  EXTERN_my_mainwindow->setProjectPreference("dbhost", dbhost->currentText());
  EXTERN_my_mainwindow->setProjectPreference("dbport", dbport->currentText());
  EXTERN_my_mainwindow->setProjectPreference("dbuserpassword", dbuserpassword->currentText());
  EXTERN_my_mainwindow->setProjectPreference("dbconnectoptions", dbconnectoptions->currentText());
  EXTERN_my_mainwindow->setProjectPreference("dbsetforruntime", dbsetforruntime->isChecked() ? "Yes" : "No");
  EXTERN_my_mainwindow->setProjectPreference("dbsettablesforruntime", dbsettablesforruntime->isChecked() ? "Yes" : "No");
  

  EXTERN_my_mainwindow->saveProjectPreferences();

  QString sSQL = "";  
  if (EXTERN_my_mainwindow->getProjectPreference("dbdriver").contains("sqlite", Qt::CaseInsensitive)){
    sSQL = EXTERN_my_mainwindow->getProjectPreference("dbdriver").isEmpty() ? "" : EXTERN_my_mainwindow->getProjectPreference("dbname");
  } else {
    sSQL = EXTERN_my_mainwindow->getProjectPreference("dbdriver").isEmpty() ? "" : EXTERN_my_mainwindow->getProjectPreference("dbhost") + "//:" + EXTERN_my_mainwindow->getProjectPreference("dbuser") + "@" + EXTERN_my_mainwindow->getProjectPreference("dbname");
  }
  EXTERN_my_projectwindow->showProjectName(" " + EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(EXTERN_my_mainwindow->getProjectName()) + "      " + (sSQL.length() > 4 ? sSQL :+ " "));

  accept();
}

void _dbcondialog::cancel()
{
  close();
}
