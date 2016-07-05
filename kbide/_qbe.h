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

#ifndef _qbe_H
#define _qbe_H


#include <QDialog>
#include <QItemDelegate>



class QRadioButton;
class QStandardItem;
class QStandardItemModel;
class QTableWidget;
class QTabWidget;



class _qbe_workspace;
class _qbe_sql;



class _qbe : public QWidget
{
    Q_OBJECT

public:
   _qbe( QWidget *parent = 0);
   void addTable(QString sName);

   _qbe_workspace *w;

void event_FORMAT_MOVE_LEFT();   
void event_FORMAT_MOVE_RIGHT();   


public slots:

  void currentCellChanged ( int currentRow, int currentColumn, int previousRow, int previousColumn ) ;

  
void textChanged();

void SLOT_ok();
void SLOT_ok2();
void SLOT_ok3();
void SLOT_close();

void refreshSQL();

public:

void parseSQL();


void addItem(QString sTable, QString sField);

void loadRules(bool bApplyGeometry = true, QString sAddedTable = "");
void saveRules();

    void load( const QString& fn);
    void save(bool saveAs = false);
    void saveAs();

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

private:

//  void focusInEvent(QFocusEvent *e);
  void focusOutEvent(QFocusEvent *e);

  bool bQBE;

  void moveIt(bool up);

  QStandardItemModel *model;
  bool bIsModified;
  QString filename;

  QWidget *parent;


  QRadioButton *Select;
  QRadioButton *Insert;
  QRadioButton *Update;
  QRadioButton *Delete;

  QString sSELECT;
  QString sINSERT;
  QString sUPDATE;
  QString sDELETE;

  QTabWidget *tb;
  

_qbe_sql *my_qbe_sql;

QTableWidget *table;

int nCurrentRow;

};

class QBETableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QBETableDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
        const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const;
private slots:
    void commitAndCloseEditor();
private:
  
};


#endif
