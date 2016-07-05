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


#include "_qbe_tables.h"

#include "_mainwindow.h"
#include "_relation.h"
#include "_qbe.h"
#include "../kbshared/_form.h"


extern QSqlDatabase CurrentDatabase;
extern _qbe_tables *my_qbe_tables;
extern _mainwindow *EXTERN_my_mainwindow;
extern _qbe_tables *EXTERN_qbe_tables;
extern QDockWidget *EXTERN_DatabaseTables;


_qbe_tables::_qbe_tables(QWidget *parent, _relation *_my_relation, _qbe *_my_qbe/*, _form *_my_form*/) : QListWidget(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);

  my_relation = _my_relation;
  my_qbe = _my_qbe;


  //if (CurrentDatabase.open())
  {
    
    QStringList l = CurrentDatabase.tables();
    for (int i = 0; i < l.size(); ++i){
      addItem(l.at(i));
    }

//    CurrentDatabase.close();
    
  }

  if (my_relation || my_qbe){
    resize(130, 200);
    move(25, 90);
  } else {
    EXTERN_DatabaseTables->move(25, 170);
    EXTERN_DatabaseTables->resize(100, 200);
  }
  setWindowTitle(tr("Database Tables"));

  connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this , SLOT(itemDoubleClicked(QListWidgetItem*)));
  show();
  
}

void _qbe_tables::refresh()
{
  clear();

  //if (CurrentDatabase.open())
  {
    
    QStringList l = CurrentDatabase.tables();
    for (int i = 0; i < l.size(); ++i){
      addItem(l.at(i));
    }

  }
  
}

void _qbe_tables::itemDoubleClicked(QListWidgetItem *item)
{
  int i = 0; 
  i++;


  if (my_relation){
    my_relation->addTable(item->text());
    return;
  }

  if (my_qbe){
    my_qbe->addTable(item->text());
    return;
  }

  {
    _qbe *o = qobject_cast<_qbe *>(EXTERN_my_mainwindow->workspace->activeSubWindow() ? EXTERN_my_mainwindow->workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->addTable(item->text());
    }
  }

  {
    _form *o = qobject_cast<_form *>(EXTERN_my_mainwindow->workspace->activeSubWindow() ? EXTERN_my_mainwindow->workspace->activeSubWindow()->widget() : 0);
    if (o){
      o->addTable(item->text());
    }
  }
}

_qbe_tables::~_qbe_tables()
{
  /*
  my_qbe_tables = 0;
  EXTERN_my_mainwindow->VIEW_SQLTABLES->setChecked(false);
  if (my_form) my_form->bShowSQLTables = false;*/
  //QListWidget::
}



