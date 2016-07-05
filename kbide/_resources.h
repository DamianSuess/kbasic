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


class _resources : public QDialog
{
  Q_OBJECT
public:
  _resources(QWidget* parent);
  ~_resources();

private slots:

  void performSave();
  void performClose();
  void clicked();

private:
    void kbasic(); 
    void vista(); 
    void actions(); 
    void apps(); 
    void devices(); 
    void filesystems(); 
    void mimetypes(); 
    void kids_apps(); 
    void kids_devices(); 
    void kids_filesystems(); 
    void kids_mimetypes(); 

  _mainwindow *my_mainwindow;

  QTabWidget *tab;

  QString sButton;


};

