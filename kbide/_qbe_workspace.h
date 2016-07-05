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

#ifndef __qbe_workspace_H
#define __qbe_workspace_H


#include <QWorkspace>
#include <QPaintEvent>


class _qbe_table;



struct RelationRule
{
    _qbe_table *oSource;
    int nSourceIndex;
    QString sSourceName;
    QString sSourceField;

    QString sForeignKeyReplacement;

    _qbe_table *oDestination;
    int nDestinationIndex;
    QString sDestinationName;
    QString sDestinationField;


    QRegion region;
};

class _qbe_workspace : public QWorkspace
{
    Q_OBJECT

public:
   _qbe_workspace(bool _bEdit);
   ~_qbe_workspace();

QPoint getPointFor(_qbe_table *o, int nIndex);

  QVector<RelationRule>RelationRules;    
int nSelectedRule;

private:
  bool eventFilter(QObject *obj, QEvent *event);
  void mouseReleaseEvent(QMouseEvent *e);
  void mouseDoubleClickEvent(QMouseEvent *e);

  void paintEvent(QPaintEvent *e);


  bool bEdit;



};


#endif
