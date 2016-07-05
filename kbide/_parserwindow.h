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


#ifndef _parserwindow_H
#define _parserwindow_H


#include <QTreeWidget>
#include <QLabel>
#include <QTextEdit>
#include <QActionGroup>



class QTreeWidgetItem;

class _mainwindow;




class _parserwindow : public QWidget
{
  Q_OBJECT
public:
  _parserwindow(QWidget *parent);  
  
  void refresh(QString sFile);
  void refreshControl();

  void refreshProject(QString sIgnoreFile = "");

private slots:
  void itemSelectionChanged();
  void itemDoubleClicked(QTreeWidgetItem *item, int column);

  void itemDoubleClicked2(QTreeWidgetItem *item, int column);

  void actionSelected();

private:

  void createTree();  

  QTreeWidget *tree;

  QTreeWidgetItem *_all;
  QTreeWidgetItem *_framework;
  QTreeWidgetItem *_builtin;
  QTreeWidgetItem *_custom;
  //QTreeWidgetItem *_file;
  QTreeWidgetItem *_form;
  QTreeWidgetItem *_report;

  QTreeWidgetItem *_all2;
  QTreeWidgetItem *_constants;
  QTreeWidgetItem *_variables;
  QTreeWidgetItem *_methods;
  QTreeWidgetItem *_properties;
  QTreeWidgetItem *_enums;
  QTreeWidgetItem *_types;
  QActionGroup *ag;

  QTextEdit *te;
};



#endif