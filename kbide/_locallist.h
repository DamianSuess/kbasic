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

class _locallist : public QListWidget
{
  Q_OBJECT
public:
  _locallist(QWidget *parent);

  void add(QString s1, QString s2, QString s3);

};

class _melist : public QListWidget
{
  Q_OBJECT
public:
  _melist(QWidget *parent);

  void add(QString s1, QString s2, QString s3);

};