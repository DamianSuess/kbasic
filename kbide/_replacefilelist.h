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

#include <QListWidget>

class _replacefilelist : public QListWidget
{
  Q_OBJECT
public:
  _replacefilelist(QWidget *parent);

private slots:
  void itemActivated(QListWidgetItem *item);

};
