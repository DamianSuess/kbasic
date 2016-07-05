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

#ifndef __qbe_tables_H
#define __qbe_tables_H


#include <QListWidget>

class _relation;
class _qbe;
class _form;


class _qbe_tables : public QListWidget
{
    Q_OBJECT

public:
   _qbe_tables(QWidget *parent, _relation *_my_relation, _qbe *_my_qbe/*, _form *_my_form*/);
   ~_qbe_tables();

   void refresh();

public slots:

void itemDoubleClicked(QListWidgetItem *item);

private:

  _relation *my_relation;
  _qbe *my_qbe;
  _form *my_form;
  

};


#endif
