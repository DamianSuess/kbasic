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



class _dbcondialog : public QDialog
{
  Q_OBJECT
public:
  _dbcondialog(QWidget* parent);

private slots:
    
  void createdatabase();
  void embedded();
  void nodatabase();
  void ok();
  void cancel();

private:
  void setupGeneral(); 


QComboBox *dbuser;
QComboBox *dbname;
QComboBox *dbdriver;
QComboBox *dbhost;
QComboBox *dbport;
QComboBox *dbuserpassword;
QComboBox *dbconnectoptions;
QCheckBox *dbsetforruntime;
QCheckBox *dbsettablesforruntime;


};

#pragma once
