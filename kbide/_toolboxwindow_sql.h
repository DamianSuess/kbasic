/*
***************************************************************************
Copyright (C) 2000-2007 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000 - 2007.

You may use this source codes under the terms of the GNU Public License (Version 2) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#ifndef _TOOLBOXWINDOW_SQL_H
#define _TOOLBOXWINDOW_SQL_H

#include <QWidget>

class _toolboxwindow_sql : public QWidget 
{
Q_OBJECT

public:
  _toolboxwindow_sql(QWidget *parent);


private slots:

void pointer();

void SQLInsert();
void SQLNext();
void SQLPrevious();
void SQLUpdate();
void SQLDelete();
void SQLFirst();
void SQLLast();
void SQLGoTo();
void SQLInfo();
void SQLAll();
void SQLRequery();


private:
//void currentTextChanged ( const QString & currentText );

};

#endif