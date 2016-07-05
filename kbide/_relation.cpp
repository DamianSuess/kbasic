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

#include "_relation.h"
#include "_qbe_table.h"
#include "_qbe_tables.h"
#include "_qbe_workspace.h"

#include "_mainwindow.h"
#include "_typedef.h"
extern _qbe_workspace *EXTERN_my_qbe_workspace;
extern _mainwindow *EXTERN_my_mainwindow;

extern const QIcon &kbasicIcon(QString s);


extern _qbe_workspace *w;

extern QSqlDatabase CurrentDatabase;

#ifdef MAC
_relation::_relation( QWidget *parent) : QDialog(EXTERN_my_mainwindow) // HIDE
#else
_relation::_relation( QWidget *parent) : QDialog(0)
#endif
{

  setAttribute(Qt::WA_DeleteOnClose);

  setFocusPolicy(Qt::StrongFocus);
/*
  if (!CurrentDatabase.isOpen()){
    QApplication::restoreOverrideCursor();    
    QMessageBox::information(this, MYAPP, "You are not connected to a database.");  

  //  close();
    return;
  }*/

  _qbe_tables *zz = new _qbe_tables(this, this, 0);


  setWindowTitle(tr("Relations"));
  setWindowIcon(kbasicIcon(kbasicPath("ide/VIEW_RELATION.png")));
  setObjectName("Relations");


  QVBoxLayout *j = new QVBoxLayout();
  setLayout(j);


  w = new _qbe_workspace(true); j->addWidget(w);
  w->setScrollBarsEnabled(true);
  w->setAcceptDrops(true);
  RelationRules = &w->RelationRules;


  // ***

  QPushButton *p;
/*
  p = new QPushButton(tr("Run Query")); j->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_ok()) );
*/
  p = new QPushButton(tr("&Close")); j->addWidget(p);
  p->setFocus();
  p->setMaximumWidth(150);
  
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_close()) );

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  move(x(), 50);

  loadRules();
 // showMaximized();

  
  QMdiSubWindow *w = new QMdiSubWindow(); // do it this way cause of Qt bug
  w->setWidget(this);
  EXTERN_my_mainwindow->workspace->addSubWindow(w);

 // o->setMinimumSize(SAVE);

  this->parentWidget()->resize(this->size());
  this->parentWidget()->setWindowIcon(this->windowIcon());

  this->showMaximized();
  this->setFocus();
  EXTERN_my_mainwindow->workspace->setActiveSubWindow((QMdiSubWindow *) this->parentWidget());


}

void _relation::closeEvent( QCloseEvent *e )
{
  if (parentWidget()){
    QMdiSubWindow *mdis = qobject_cast<QMdiSubWindow *>(parentWidget());
    EXTERN_my_mainwindow->workspace->removeSubWindow(mdis);
  }

  saveRules();

  e->accept();

  QWidget::closeEvent(e);
}

/*
void _relation::SLOT_ok()
{ 
  close();
}
*/
void _relation::SLOT_close()
{
  saveRules();
  close();
}

void _relation::addTable(QString sName)
{
  QWidgetList l = w->windowList();
  for (int i = 0; i < l.size(); i++){
    if (l.at(i)->windowTitle() == sName) return;
  }

  _qbe_table *z = new _qbe_table(this, sName); 
  w->addWindow(z, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint); 
  z->parentWidget()->move(z->parentWidget()->x() + 150 + l.size() * 5, z->parentWidget()->y() + l.size() * 5);
  z->show();
  z->setFocus();
}

void _relation::loadRules(bool bApplyGeometry)
{
  RelationRules->clear();

  QString s = EXTERN_my_mainwindow->getProjectPreference("RELATIONS");

  QStringList l = s.split(";", QString::SkipEmptyParts);
  for (int i = 0; i < l.size(); i++){
    s = l.at(i);
    int n = s.indexOf("->");
    QString le = s.left(n);
    QString ri = s.mid(n + 2);

    n = le.indexOf(".");
    QString sTable = le.left(n);
    QString sField = le.mid(n + 1);

    n = ri.indexOf(".");
    QString sTable2 = ri.left(n);
    QString sField2 = ri.mid(n + 1);
    QString sForeignKeyReplacement = "";  
    if (sField2.contains("(")){
      QString k = sField2;
      sField2 = sField2.left(sField2.indexOf("("));
      k = k.mid(k.indexOf("(") + 1);
      sForeignKeyReplacement = k.left(k.length() - 1);
    }
    RelationRule rule;

    if (bApplyGeometry){
      addTable(sTable);
      addTable(sTable2);
    }

    bool b = false;

    QWidgetList l = w->windowList();
    for (int i = 0; i < l.size(); i++){
      if (l.at(i)->windowTitle() == sTable) b = true;
    }

    if(b){
      QWidgetList l = w->windowList();
      for (int i = 0; i < l.size(); i++){
        if (l.at(i)->windowTitle() == sTable2) b = true;
      }
    }
    if (b == false) return;

    l = w->windowList();

    for (int i = 0; i < l.size(); i++){

      QWidget *w = l.at(i);
      _qbe_table *o = 0;

      if ((o = qobject_cast<_qbe_table *>(w))){
        QString s = o->windowTitle();
        if (s == sTable){
          QList<QListWidgetItem *> ll = o->findItems(sField, Qt::MatchCaseSensitive);

          if (ll.count() && ll.at(0)){
            QFont f = ll.at(0)->font();
            f.setBold(true);
            ll.at(0)->setFont(f);

            rule.oSource = o;
            rule.nSourceIndex = o->row(ll.at(0));
            rule.sSourceName = sTable;
            rule.sSourceField = sField;
            break;
          }
        }

      }
    }

    l = w->windowList();
    for (int i = 0; i < l.size(); i++){

      QWidget *w = l.at(i);
      _qbe_table *o = 0;

      if ((o = qobject_cast<_qbe_table *>(w))){
        QString s = o->windowTitle();
        if (s == sTable2){
          QList<QListWidgetItem *> ll = o->findItems(sField2, Qt::MatchCaseSensitive);

          if (ll.count() && ll.at(0)){
            QFont f = ll.at(0)->font();
            f.setBold(true);
            ll.at(0)->setFont(f);

            rule.oDestination = o;
            rule.nDestinationIndex = o->row(ll.at(0));
            rule.sDestinationName = sTable2;
            rule.sDestinationField = sField2;
            rule.sForeignKeyReplacement = sForeignKeyReplacement;

            RelationRules->append(rule);
            break;
          }
        }

      }
    }
    
  }

  s = EXTERN_my_mainwindow->getProjectPreference("RELATIONWINDOWS");


  l = s.split(";", QString::SkipEmptyParts);
  for (int i = 0; bApplyGeometry && i < l.size(); i++){
    s = l.at(i);

    int n = s.indexOf("/");
    QString sName = s.left(n); s = s.mid(n + 1);

    n = s.indexOf("/");
    int x = s.left(n).toInt(); s = s.mid(n + 1);
    
    n = s.indexOf("/");
    int y = s.left(n).toInt(); s = s.mid(n + 1);
    
    n = s.indexOf("/");
    int width = s.left(n).toInt(); s = s.mid(n + 1);

    n = s.indexOf("/");
    int height = s.left(n).toInt(); s = s.mid(n + 1);
    
    QWidgetList ll = w->windowList();
    for (int i = 0; i < ll.size(); i++){

      QWidget *w = ll.at(i);
      _qbe_table *o = 0;

      if ((o = qobject_cast<_qbe_table *>(w))){
        QString s = o->windowTitle();
        if (s == sName){
          o->parentWidget()->move(x, y); o->resize(width, height);
          break;
        }
      }
    }
  }

  w->update();
}

void _relation::focusInEvent(QFocusEvent *e)
{
  EXTERN_my_mainwindow->workspace->setActiveSubWindow((QMdiSubWindow *) parentWidget());

  EXTERN_my_mainwindow->updateGeneralActions(
   false,  false,  false,  false, 
   false,  false,  false,  false,  false,   
   false,  false,  false, 
   false,  false,  false,  false, 
   false, ""
  );

  QWidget::focusInEvent(e);

}

void _relation::saveRules()
{
  QString s = "";

  for (int i = 0; i < RelationRules->size(); ++i) {
    RelationRule r = RelationRules->at(i);

    s += r.sSourceName;
    s += ".";
    s += r.sSourceField;
    s += "->";
    s += r.sDestinationName;
    s += ".";
    s += r.sDestinationField;
    if (!r.sForeignKeyReplacement.isEmpty()){
      s += "(";
      s += r.sForeignKeyReplacement;
      s += ")";
    }
    s += ";";

    RelationRules->replace(i, r);

   

  }

  EXTERN_my_mainwindow->setProjectPreference("RELATIONS", s);

  s = "";


  QWidgetList l = w->windowList();
  for (int i = 0; i < l.size(); i++){

    QWidget *w = l.at(i);
    _qbe_table *o = 0;

    if ((o = qobject_cast<_qbe_table *>(w))){
        s += o->windowTitle();
        s += "/";
        s += QString("%1").arg(o->parentWidget()->x());
        s += "/";
        s += QString("%1").arg(o->parentWidget()->y());
        s += "/";
        s += QString("%1").arg(o->parentWidget()->width());
        s += "/";
        s += QString("%1").arg(o->parentWidget()->height());
        s += ";";
    }
  }

  EXTERN_my_mainwindow->setProjectPreference("RELATIONWINDOWS", s);

  EXTERN_my_mainwindow->saveProjectPreferences();

}

void _relation::addItem(QString sTable, QString sField)
{
  //model
}

/*
addTable()
removeTable();
*/