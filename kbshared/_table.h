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

#ifndef _table_H
#define _table_H

#include <QTableWidget>
#include <QSqlRelationalDelegate>
#include <QStringList>
#include <QModelIndex>


#include "../kbide/_qbe_workspace.h"


#include "../kbshared/_tableitem.h"

class _mainwindow;
class QSqlRelationalTableModel ;
class QTableView;
class _tableviewer;

extern _mainwindow *EXTERN_my_mainwindow;


class TableView : public QTableView
 {
     Q_OBJECT
 public:
     TableView(_tableviewer *f);
private:
     void focusInEvent(QFocusEvent *e);
     void currentChanged ( const QModelIndex & current, const QModelIndex & previous );

     

     _tableviewer *my_tableviewer; 
 };


class TableDelegate;

class _tableviewer : public QWidget
{
  Q_OBJECT
public:
  _tableviewer(QWidget *parent, QString s);
  ~_tableviewer();
  
  QLineEdit *SQLGoTo;
  TableView *view;
  void focusInEvent(QFocusEvent *e);
  void focusOutEvent(QFocusEvent *e);
  

  bool bDirty;

  QModelIndex oldEditIndex;  
  bool bSetTimerPos;
  bool bBlockTimer;

public slots:

  void SQLGoto();
  void SQLFirst();
  void SQLBackward();
  void SQLForward();
  void SQLLast();
  void SQLAddNew();
  void SQLAddNew100();
  void SQLDelete();
  void SQLDeleteAll();

 
private:

  void timerEvent ( QTimerEvent * event );
  
  

  int nTimer;
  QString sGlobalFields;
  QString sGlobalValues;


  
  TableDelegate *tg;

  QLabel *SQLInfo;
  QSqlRelationalTableModel  *model;
  QString sTable;

  QVector<RelationRule>RelationRules;    

};



class TableDelegate : public QSqlRelationalDelegate
{
    Q_OBJECT
public:
    TableDelegate(QStringList l, QObject *parent = 0, QSqlRelationalTableModel *_showData = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
        const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
private slots:
    void commitAndCloseEditor();
private:

  bool eventFilter ( QObject * editor, QEvent * event );

  QSqlRelationalTableModel  *showData;
  QStringList l;
  
};

class _table : public QTableWidget
{
  Q_OBJECT

public:
  _table();


#include "_table_property.h"
#include "_table_loadsave.h"

    QStringList load( const QString& fn, bool bListOnly = false);
    void save(bool saveAs = false);
    void saveAs();

    void showData();

    void updateCaption(QString s, bool bSaving = true);

    void closeEvent( QCloseEvent * );
    void focusInEvent(QFocusEvent *e);

    QString getFilename();

    QString getFilenameWithoutPath()
    { 
      QString s = filename;
      int i = s.lastIndexOf('/');
      s = s.right(s.length() - i - 1);
      return s; 
    }

    QString getPath()
    { 
      QString s = filename;
      int i = s.lastIndexOf('/');
      s = s.left(i + 1);
      return s; 
    }

  QString getFilenameWithoutPathAndExtension()
  {       
    QString k = getFilenameWithoutPath();

    int i = k.lastIndexOf('.');

    k = k.left(i);
    return k; 
  }


t_boolean METHOD_insertControl(_tableitem *c, _controlType controlType, QString s2 = "")
{
  QString s = s2; 

  switch(controlType){
    case t_tableitem:
      if (!s2.length()) tableitems.uniqueName(&s);
      tableitems.add(tableitems.count(), s, (_tableitem *) c);

      ((_tableitem *) c)->SETPROPERTY_Name(s);
      break;

  }

  return true;
}
_controlType controlType(_tableitem *c)
{
  return t_tableitem;
}

_controlType insertType;
void setInsertControlType(_controlType t)
{
  insertType = t;
}

bool 		deleteControl(_tableitem *c)
{
  bool b = false;
  
  b = tableitems.del2((_tableitem *) c);
  if (b) return true;

  return false;
}


void selectControl(_tableitem *c)
{
  bool b = c->acceptDrops();
  c->setAcceptDrops(!b); // missused as selected flag
}

void unselectControl(_tableitem *c)
{
  c->setAcceptDrops(false); // missused as selected flag
}

void selectControlAlways(_tableitem *c)
{
  c->setAcceptDrops(true); // missused as selected flag
}

void unselectAllControls()
{
  _tableitem *c;


  if (firstControl(&c)){

    do {
      c->setAcceptDrops(false); // missused as selected flag
    } while (nextControl(&c)); 

  }

}           



bool firstControl(_tableitem **c)
{
  bool b = false;  

  tableitems.reset();
  
  b = tableitems.first((_tableitem**) c);
  if (b){ return true; }

  return false;
}

bool nextControl(_tableitem **c)
{ 
  bool b = false;     
  
  b = tableitems.next((_tableitem**) c);
  if (b){ return true; }

  return false;
}


void event_FORMAT_MOVE_UP();   
void event_FORMAT_MOVE_DOWN();   




void moveIt(bool up);

public slots:
  void currentCellChanged ( int currentRow, int currentColumn, int previousRow, int previousColumn ) ;
  void cellChanged( int row, int column );

private:

   QString sCREATETABLE;

  _tableitems tableitems;

   QString filename;
   bool bIsModified;
   bool bLoading;

   int nCurrentRow;

   

};


#endif