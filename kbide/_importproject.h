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


class _mainwindow;


class _importproject : public QDialog
{
  Q_OBJECT
public:
  _importproject(QWidget* parent);

  void importVbp(QString s);
  void importFrm(QString s);
  void importBas(QString s);
  void importCSV(QString s);

private slots:

  void clicked();
  void clicked2();
  
  void ok();
  void cancel();

private:

    QString geValueFromVbp(QString sText, QString sKey);
    QString geValueFromFrm(QString sText, QString sKey);
    void putFormKey(QString *sText, QString sKey, QString sValue, bool bIdent = true, bool bString = false);
    void putFormKeyString(QString *sText, QString sKey, QString sValue, bool bIdent = true);


    bool insertCSV(QString & sTable, QStringList &header, QStringList &l);

  void setupGeneral(); 

  _mainwindow *my_mainwindow;

  QLineEdit *source;
  QLineEdit *source2;
  QLineEdit *destination;

  QWidget *parent;
};

#pragma once
