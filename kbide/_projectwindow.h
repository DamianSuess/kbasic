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


#ifndef _projectwindow_H
#define _projectwindow_H


#include <QTreeWidget>
#include <QLabel>
#include <QPushButton>
#include <QSqlDatabase>
#include <QToolBar>
#include <QActionGroup>



extern QSqlDatabase CurrentDatabase;



class QTreeWidgetItem;

class _mainwindow;




class _projectwindow : public QWidget
{
  Q_OBJECT
public:
  _projectwindow(QWidget *parent);
  
  bool load();
  
  void refresh();
  void closeProject();  

  bool pasteAvailable();

  bool bInit;

  void showProjectName(const QString &s);

private slots:

  void settingdb();

  void actionSelected();
//  void currentChanged(int index);
  void itemChanged(QTreeWidgetItem *item, int column);
  void itemDoubleClicked(QTreeWidgetItem *item, int column);
  void itemSelectionChanged();
  void currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

  void customContextMenuRequested ( const QPoint & pos );
  

  void event_EDIT_CUT();
  void event_EDIT_COPY();
  void event_EDIT_PASTE();
  void event_EDIT_DELETE();
  void event_REFRESH();
  void event_RENAME();
  void event_OPEN();
  void event_OPEN2();

  

private:
  QTreeWidgetItem *getParentTreeWidgetItem(QTreeWidgetItem *normal, QString & sFilename, int pass, QString & sLanguage);

  void focusInEvent(QFocusEvent *e);
  void focusOutEvent(QFocusEvent *e);
  

  void createTree();  

  bool cutAvailable();
  bool copyAvailable(){ return cutAvailable(); }
  bool deleteAvailable(){ return cutAvailable(); }

  QLabel *currentprojectname;
  QPushButton *setdb;
  QToolBar *tb;
  QAction *aAll;
  QActionGroup *ag;
};



#endif