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

#include <QWidget>
#include <QDialog>
#include <QMap>
#include <QLineEdit>


class QWidget;
class QString;
class QLabel;
class QComboBox;
class QTabWidget;
class QLabel;
class QComboBox;



class _mainwindow;


class _newproject : public QDialog
{
  Q_OBJECT
public:
  _newproject(QWidget* parent, int *nType);

  QString getPath()
  {
    QString s = destination->text();
    if (!s.isEmpty() && !s.endsWith("\\") && !s.endsWith("/")) s += "/";
    return s;
  }
  
  QString getName()
  {
    return source->text();
  }

private slots:
  void clicked2();
  
  void ok();
  void cancel();

private:
  void setupGeneral(); 

  _mainwindow *my_mainwindow;

  QLineEdit *source;
  QLineEdit *destination;
  QComboBox *ptype;


  QWidget *parent;
  int *nType;
};

#pragma once
