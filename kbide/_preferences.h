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
class QCheckBox;
class QLabel;
class QListWidget;


class _mainwindow;


class _preferences : public QDialog
{
  Q_OBJECT
public:
  _preferences(QWidget* parent, bool _bSaveOnly = false);

  static void load(_mainwindow *parent);
  void save(_mainwindow *parent);

private slots:

  void clicked();
  void clicked2();
  void clicked3();

  void updateExample();
  void selected(int n);

  void performSave();
  void performDefault();
  void performClose();

private:
    void setupGeneral(); 
    void setupGeneral2(); 
    void setupSave(); 
    void setupCompatibility(); 
    void setupToolbar(); 
    void setupSourceCodeEditor(); 
    void setupScanner();
    void setupParser();
    void setupInterpreter();
    void setupCompiler();

    
    static int getColor(QString);

  _mainwindow *my_mainwindow;

  QWidget* parent;
  
  QListWidget *list;
  QComboBox *fore;
  QComboBox *back;
  QCheckBox *bold;
  QLabel *example;

  QMap<QString, QWidget*> pref;
  QMap<QString, QString> pref2;

  QTabWidget *tab;

  bool bSaveOnly;

};

