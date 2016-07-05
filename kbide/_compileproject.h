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


class QWidget;
class QString;
class QLabel;
class QComboBox;
class QTabWidget;
class QLineEdit;
class QLabel;
class QListWidget;
class QCheckBox;



class _mainwindow;


class _compileproject : public QDialog
{
  Q_OBJECT
public:
  _compileproject(QWidget* parent, bool _bWindows, bool _bLinux, bool _bMac);

private slots:
  void clicked2();
  
  void ok();
  void cancel();

private:
  void setupGeneral(); 
  void compile();

  QString getPath();
  QString getName();

  _mainwindow *my_mainwindow;

  QLineEdit *source;
  QLineEdit *destination;
  QWidget *parent;

  bool bWindows; bool bLinux; bool bMac;

  QCheckBox *pcodeinclude;
};

#pragma once
