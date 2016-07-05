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

#ifndef __qbe_browser_H
#define __qbe_browser_H


#include <QtGui>


class QSqlQueryModel;
class QSqlDatabase;

class _qbe_browser : public QTableView
{
    Q_OBJECT

public:
   _qbe_browser(QWidget *_parent, QString _sSQL, QString _sSQLREAL);
   ~_qbe_browser();

public slots:

protected:
  virtual void keyPressEvent(QKeyEvent *e);

private:

  QWidget *parent;

  QSqlDatabase *mydb;

QString sSQL;
QString sSQLREAL;

QSqlQueryModel *model;
};

#endif