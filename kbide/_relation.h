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

#ifndef _relation_H
#define _relation_H


#include <QDialog>

#include "_qbe_workspace.h"


class QStandardItem;
class QStandardItemModel;
class _qbe_workspace;


class _relation : public QDialog
{
    Q_OBJECT

public:
   _relation( QWidget *parent);

   void addTable(QString sName);
   void focusInEvent(QFocusEvent *e);

_qbe_workspace *w;
public slots:

void addItem(QString sTable, QString sField);

void SLOT_close();



void loadRules(bool bApplyGeometry = true);
void saveRules();

private:
  void closeEvent( QCloseEvent *e );

  QStandardItemModel *model;

  QVector<RelationRule> *RelationRules;    



};


#endif
