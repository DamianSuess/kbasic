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

#ifndef _CHOICEDIALOG_H
#define _CHOICEDIALOG_H


#include <QWidget>
#include <QDialog>
#include <QMap>

class QCheckBox;
class QString;


class _mainwindow;


class _choicedialog : public QDialog
{
  Q_OBJECT
public:
    static QString get(QString _sAllowed, QString _sSet);

private slots:
  void performClose();
private:
  _choicedialog(QWidget* _parent, QString _sAllowed);
   QMap<QString, QCheckBox*> pref;

};


#endif