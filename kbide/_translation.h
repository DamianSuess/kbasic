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
class QTextEdit;
class QTabWidget;
class QTextEdit;
class QLabel;
class QListWidget;


class _mainwindow;


class _translation : public QDialog
{
  Q_OBJECT
public:
  _translation(QWidget* parent);

private slots:
  
  void add();
  void remove();
  void next();
  void mark();
  //void ok();
  void cancel();

  void currentIndexChanged  ( const QString & text ) ;
  void textChanged () ;

private:
  void setupWindow(); 
  void setupRecord(); 

  void load();
  void save();

  void updateInfo();

  void closeEvent ( QCloseEvent * e );

  QStringList parseStrings(QString s);


  QComboBox *lang;
  QLabel *info;

QTextEdit *Window;
QTextEdit *Help;
QTextEdit *Contents;
QTextEdit *About;
QTextEdit *Close;
QTextEdit *CloseAll;
QTextEdit *Tile;
QTextEdit *Cascade;
QTextEdit *Arrange;
QTextEdit *Next;
QTextEdit *Previous;

QTextEdit *Records;
QTextEdit *Requery;
QTextEdit *AddNew;
QTextEdit *Update;
QTextEdit *Delete;
QTextEdit *Seek;
QTextEdit *AddFilter;
QTextEdit *AddNotFilter;
QTextEdit *SetFilter;
QTextEdit *SetNotFilter;
QTextEdit *ClearFilter;
QTextEdit *SortAscending;
QTextEdit *SortDescending;
QTextEdit *DeleteQuestion;


QTabWidget *tab;

};

#pragma once
