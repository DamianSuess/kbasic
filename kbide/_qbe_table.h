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

#ifndef __qbe_table_H
#define __qbe_table_H


#include <QListWidget>

#include "_qbe_workspace.h"

class _qbe_workspace;

class _qbe_table : public QListWidget
{
    Q_OBJECT

public:
   _qbe_table(QWidget *_parent, QString _sName);

public slots:

void itemDoubleClicked(QListWidgetItem *item);

protected:
  virtual void keyPressEvent(QKeyEvent *e);
  virtual void closeEvent(QCloseEvent *e);
  virtual void dragEnterEvent(QDragEnterEvent *e);
  virtual void dragLeaveEvent(QDragLeaveEvent *e);
  virtual void dragMoveEvent(QDragMoveEvent *e);
  virtual void dropEvent(QDropEvent *e);
  virtual void scrollContentsBy(int dx, int dy);  

private:
QWidget *parent;
QString sName;

_qbe_workspace *w;

QVector<RelationRule> *RelationRules;    
};


#endif
