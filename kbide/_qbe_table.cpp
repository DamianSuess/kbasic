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

#include <QtGui>
#include <QtSql>

#include "_qbe.h"
#include "_relation.h"
#include "_qbe_table.h"
#include "_qbe_workspace.h"

extern QString kbasicPath(QString sPath);
extern const QIcon &kbasicIcon(QString s);

extern QSqlDatabase CurrentDatabase;

_qbe_table::_qbe_table(QWidget *_parent, QString _sName) : QListWidget(_parent)
{
  w = 0;
  {
    _qbe *o = qobject_cast<_qbe *>(_parent);
    if (w == 0 && o){
      w = o->w;
      RelationRules = &w->RelationRules;
    }
  }
  {
    _relation *o = qobject_cast<_relation *>(_parent);
    if (w == 0 && o){
      w = o->w;
      RelationRules = &w->RelationRules;
    }
  }
  
  parent = _parent;
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);

  sName = _sName;

  setSortingEnabled(false);

  setDragDropMode(QAbstractItemView::DragDrop);
  setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")));

  setWindowTitle(sName);


  //if (CurrentDatabase.open())
  {
    
    if (qobject_cast<_relation *>(_parent) == 0) addItem("*");

    QSqlRecord r = CurrentDatabase.record(sName);

    QStringList l = CurrentDatabase.tables();
    for (int i = 0; i < r.count(); ++i){
      addItem(r.fieldName(i));
    }

 // } else {
 //   addItem("Error Not Connected To Database");
    //QSqlError e = CurrentDatabase.lastError();
    //QMessageBox::information(this, "Error Not Connected To Database",  e.text());    
  }

  resize(100, 100);


  
  connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this , SLOT(itemDoubleClicked(QListWidgetItem*)));


}

void _qbe_table::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Delete){
    if (w->nSelectedRule >= 0){

      RelationRule r = RelationRules->at(w->nSelectedRule);

      {
        QListWidgetItem *ll = r.oSource->item(r.nSourceIndex);
        QFont f = ll->font();
        f.setBold(false);
        ll->setFont(f);
      }
      {
        QListWidgetItem *ll = r.oDestination->item(r.nDestinationIndex);
        QFont f = ll->font();
        f.setBold(false);
        ll->setFont(f);
      }      

      RelationRules->remove(w->nSelectedRule);
      w->nSelectedRule = -1;
      w->update();
      return;
    }
    setHidden(true);
    close();
    w->update();
  }
  QListWidget::keyPressEvent(e);
}

void _qbe_table::closeEvent(QCloseEvent *e)
{
  QListWidget::closeEvent(e);
o:
  for (int i = 0; i < RelationRules->size(); ++i) {
    RelationRule r = RelationRules->at(i);
    if (r.oSource == this || r.oDestination == this){

      {
        QListWidgetItem *ll = r.oSource->item(r.nSourceIndex);
        QFont f = ll->font();
        f.setBold(false);
        ll->setFont(f);
      }
      {
        QListWidgetItem *ll = r.oDestination->item(r.nDestinationIndex);
        QFont f = ll->font();
        f.setBold(false);
        ll->setFont(f);
      }      

      RelationRules->remove(i);
      goto o;
    }
  }
  w->update();
  
}

void _qbe_table::scrollContentsBy(int dx, int dy)
{
  QListWidget::scrollContentsBy(dx, dy);
  w->update();
}

void _qbe_table::itemDoubleClicked(QListWidgetItem *item)
{

  _qbe *o = 0;

  if ((o = qobject_cast<_qbe *>(parent))){
    o->addItem(sName, item->text());
  }

}

_qbe_table *oSource;
int nSourceIndex;
QString sTable;
QString sField;


void _qbe_table::dragEnterEvent(QDragEnterEvent *e)
{
 // sTable = sName;
 // sField = currentItem()->text();
  /*
  const QMimeData *d = e->mimeData();
  QString s = d->text();
  if (!s.isEmpty()){
    s = s;
  }
  */
  QListWidget::dragEnterEvent(e);
}

void _qbe_table::dragLeaveEvent(QDragLeaveEvent *e)
{
  oSource = this;
  sTable = sName;
  QListWidgetItem *l = currentItem();
  if (l == 0) return;

  sField = l->text();
  nSourceIndex = currentRow();

  QListWidget::dragLeaveEvent(e);
}

void _qbe_table::dragMoveEvent(QDragMoveEvent *e)
{
  /*
  const QMimeData *d = e->mimeData();
  QString s = d->text();
  if (!s.isEmpty()){
    s = s;
  }*/
  e->acceptProposedAction();
  //QListWidget::dragMoveEvent(e);

}

void _qbe_table::dropEvent(QDropEvent *e)
{
  if (oSource == this) return;
  if (oSource == 0) return;
  if (sField == "*") return;

  RelationRule rule;

  rule.oSource = oSource;
  rule.nSourceIndex = nSourceIndex;
  rule.sSourceName = sTable;
  rule.sSourceField = sField;

  QPoint p = e->pos();
  QListWidgetItem *l = itemAt(p);
  if (l == 0) return;

  rule.oDestination = this;
  rule.nDestinationIndex = row(l);
  rule.sDestinationName = sName;
  rule.sDestinationField = l->text();
  if (rule.sDestinationField == "*") return;

  QListWidgetItem *ll = rule.oSource->item(rule.nSourceIndex);
  QFont f = ll->font();
  f.setBold(true);
  ll->setFont(f);

  ll = rule.oDestination->item(rule.nDestinationIndex);
  f = ll->font();
  f.setBold(true);
  ll->setFont(f);

  rule.sForeignKeyReplacement = "";

  RelationRules->append(rule);

  w->update();

}

