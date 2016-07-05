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

#include "_stacklist.h"
#include "_mainwindow.h"

extern _mainwindow *EXTERN_my_mainwindow;

_stacklist::_stacklist(QWidget *parent) : QListWidget(parent)
{
}

void _stacklist::add(QString s1, QString s2, QString s3)
{
  QString s = s1;
  QListWidgetItem  *l = new QListWidgetItem(s);
  l->setToolTip(l->text());
  addItem(l);
}
