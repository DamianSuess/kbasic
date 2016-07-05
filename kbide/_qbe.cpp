/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3)
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
***************************************************************************
*/

#include <QtGui>
#include <QtSql>

#include "_qbe.h"
#include "_qbe_table.h"
#include "_qbe_tables.h"
#include "_qbe_sql.h"
#include "_qbe_workspace.h"
#include "_qbe_browser.h"

#include "_relation.h"
#include "_projectwindow.h"




#include "_mainwindow.h"
#include "_help.h"

#include "_typedef.h"


extern QSqlDatabase CurrentDatabase;
extern _mainwindow *EXTERN_my_mainwindow;

extern const QIcon &kbasicIcon(QString s);

extern QDockWidget *EXTERN_DatabaseTables;

extern QDockWidget *EXTERN_DatabaseTables;

extern _projectwindow *EXTERN_my_projectwindow;



_qbe::_qbe( QWidget *_parent) : QWidget(0)
{
  parent = _parent;

  setAttribute(Qt::WA_DeleteOnClose);

  nCurrentRow = 0;
  bIsModified = false;


  setFocusPolicy(Qt::StrongFocus);

  if (parent) _qbe_tables *zz = new _qbe_tables(this, 0, this);


  setWindowTitle(tr("Query By Example"));
  if (qobject_cast<_mainwindow *>(parent)){
    setWindowIcon(kbasicIcon(kbasicPath("ide/VIEW_QBE.png")));
    bQBE = true;
  } else {
    bQBE = false;
    setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")));
  }

  QVBoxLayout *j = new QVBoxLayout();
  setLayout(j);


  QPushButton *p;
  QPushButton *p2;
  QPushButton *p3;

  QGroupBox *groupBox = new QGroupBox(tr("Query Mode"));

  Select = new QRadioButton(tr("Select"));
  Insert = new QRadioButton(tr("Insert"));  
  Insert->setDisabled(true);
  Update = new QRadioButton(tr("Update"));
  Delete = new QRadioButton(tr("Delete"));

  connect(Select, SIGNAL( clicked() ), this, SLOT(refreshSQL()) );
  connect(Insert, SIGNAL( clicked() ), this, SLOT(refreshSQL()) );
  connect(Update, SIGNAL( clicked() ), this, SLOT(refreshSQL()) );
  connect(Delete, SIGNAL( clicked() ), this, SLOT(refreshSQL()) );

   

  p2 = p = new QPushButton(tr("Run Query")); 
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_ok2()) );

  p3 = p = new QPushButton(tr("Show Tables")); j->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_ok3()) );
  


  p = new QPushButton(tr("Preview the selection")); j->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_ok()) );


  Select->setChecked(true);

  QHBoxLayout *vbox = new QHBoxLayout;
  vbox->addWidget(Select);
  vbox->addWidget(Insert);
  vbox->addWidget(Update);
  vbox->addWidget(Delete);
  vbox->addWidget(p2);
  vbox->addStretch(100);
  vbox->addWidget(p3);
  vbox->addStretch(50);

  vbox->addWidget(p);
  vbox->addStretch(1);
  groupBox->setLayout(vbox);
  j->addWidget(groupBox);

  QSplitter *splitter = new QSplitter(Qt::Vertical);
  j->addWidget(splitter);



  w = new _qbe_workspace(false); splitter->addWidget(w);
  w->setScrollBarsEnabled(true);
  w->setMinimumSize(680, 240);  
  w->setAcceptDrops(true);

 // setFocusProxy(w);

  tb = new QTabWidget();
  splitter->addWidget(tb);

  
  table = new QTableWidget(5, 40);  
  table->resize(width(), 300);
  QHeaderView *hh = table->horizontalHeader();
  hh->setHidden(true);

  connect(table, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(currentCellChanged(int, int, int, int)));

  splitter->addWidget(table);

  table->setItemDelegate(new QBETableDelegate());


  tb->addTab(table, "Query");

  my_qbe_sql = new _qbe_sql(this);
  connect(my_qbe_sql, SIGNAL(textChanged()), this, SLOT(textChanged()));

   
  tb->addTab(my_qbe_sql, "SQL");

  if (parent){
  } else {
    EXTERN_DatabaseTables->setShown(true); EXTERN_DatabaseTables->setFloating(true);  qApp->setActiveWindow(EXTERN_DatabaseTables);
  }

  table->setVerticalHeaderItem(0, new QTableWidgetItem("Name"));
  table->setVerticalHeaderItem(1, new QTableWidgetItem("Sort"));
  table->setVerticalHeaderItem(2, new QTableWidgetItem("Filter"));
  table->setVerticalHeaderItem(3, new QTableWidgetItem("Group"));
  table->setVerticalHeaderItem(4, new QTableWidgetItem("Data"));

  connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(refreshSQL()));
  


  // ***

  if (parent){
    p = new QPushButton(tr("&Close")); j->addWidget(p);
    p->setFocus();
    p->setMaximumWidth(150);  
    connect(p, SIGNAL( clicked() ), this, SLOT(SLOT_close()) );
  }

  //move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  //move(x(), 50);
 if (parent) showMaximized();

 // loadRules(false);
  refreshSQL();
}

void _qbe::currentCellChanged ( int currentRow, int currentColumn, int previousRow, int previousColumn )   
{
  nCurrentRow = currentColumn;
}

void _qbe::textChanged()
{ 
  bIsModified = true;
}

void _qbe::SLOT_ok3()
{ 
  if (parent){
    if (parent) _qbe_tables *zz = new _qbe_tables(this, 0, this);
  } else {
    EXTERN_DatabaseTables->setShown(true); EXTERN_DatabaseTables->setFloating(true);  qApp->setActiveWindow(EXTERN_DatabaseTables);
  }
}

void _qbe::SLOT_ok()
{ 
  QString s = sSELECT;
  if (s.isEmpty()) s = my_qbe_sql->toPlainText();
  if (!s.isEmpty()) _qbe_browser *b = new _qbe_browser(this, s, s);
}

void _qbe::SLOT_ok2()
{ 

  QString s = my_qbe_sql->toPlainText();
  if (Select->isChecked() && !s.isEmpty()){
    if (!s.isEmpty()) _qbe_browser *b = new _qbe_browser(this, s, s);
  }

  else if (Delete->isChecked() && !s.isEmpty()){
    if (QMessageBox::question(this, tr("Delete records"), tr("Would you like to delete the selected records?\n\nWARNING! Deleted records cannot be restored."), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) return;

    QSqlQuery query("", CurrentDatabase);
    if (query.exec(s)){
      int n = query.numRowsAffected();
      if (n >= 0) QMessageBox::information(this, MYAPP, tr("#") + QString("%1").arg(n) + tr(" records have been deleted."));
    } else {
      QMessageBox::information(this, MYAPP, query.lastError().text());
    }
  }

  else if (Update->isChecked() && !s.isEmpty()){
    if (QMessageBox::question(this, tr("Update records"), tr("Would you like to update the selected records?\n\nWARNING! Updated records cannot be restored."), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) return;

    QSqlQuery query("", CurrentDatabase);
    if (query.exec(s)){
      int n = query.numRowsAffected();
      if (n >= 0) QMessageBox::information(this, MYAPP, tr("#") + QString("%1").arg(n) + tr(" records have been updated."));
    } else {
      QMessageBox::information(this, MYAPP, query.lastError().text());
    }
//    if (!s.isEmpty()) _qbe_browser *b = new _qbe_browser(this, sUPDATE, sUPDATE);
  }

  else if (Insert->isChecked() && !s.isEmpty()){

    QSqlQuery query("", CurrentDatabase);
    int n = 0;

    if (query.exec(sSELECT)){
      n = query.numRowsAffected();
      if (n >= 0) QMessageBox::information(this, MYAPP, tr("#") + QString("%1").arg(n) + tr(" records have been updated."));
    } else {
      QMessageBox::information(this, MYAPP, query.lastError().text());
      return;
    }

    if (QMessageBox::question(this, tr("Insert records"), tr("Would you like to insert #%1 records?").arg(n), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) return;
  

    QString sTable = sINSERT;
    sTable = sTable.left(sTable.indexOf("("));
    sTable = sTable.simplified();

    if (query.first()){
      
      do {

        qulonglong kbrecordid = 0;

        QString values = "";

        QSqlQuery rr;
        QString s = "SELECT kbrecordid FROM " + sTable + " ORDER BY kbrecordid desc";
        if (rr.exec(s)){      

          if (rr.first()){
            QSqlRecord r = rr.record();
            int n = r.indexOf("kbrecordid");
            kbrecordid = rr.value(n).toLongLong();
            values = QString("%1").arg(++kbrecordid);
          } else {
            values += "1";
          }
        } else {
          values += "1";
        }     

        QString fields = "kbrecordid";

        //QString sql = "INSERT INTO " + sTable + "(" + fields + sGlobalFields + ") VALUES (" + values + sGlobalValues + ")";      
      
      } while (query.next());
    }
  
  
  }


  else if (Insert->isChecked() && !sINSERT.isEmpty()){
   // if (!s.isEmpty()) _qbe_browser *b = new _qbe_browser(this, sINSERT, sINSERT);
  }

}

void _qbe::SLOT_close()
{
  close();
}

void _qbe::addTable(QString sName)
{
  static int x = 0;
  QWidgetList l = w->windowList();
  for (int i = 0; i < l.size(); i++){
    if (l.at(i)->windowTitle() == sName) return;
  }

  _qbe_table *z = new _qbe_table(this, sName); 
  w->addWindow(z, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint); 
  z->parentWidget()->move(z->parentWidget()->x() + 150 + l.size() * 5 + x, z->parentWidget()->y() + l.size() * 5 + x);
  x += 80;
  if (x > 160) x = x / 9;
  z->show();
  z->setFocus();

  loadRules(false, sName);
}

void _qbe::parseSQL()
{
}

void _qbe::refreshSQL()
{
  QString s = "";
  QString sySELECT = "";
  QString sFROM = "";
  QString sWHERE = "";
  QString sGROUP = "";
  QString sORDER = "";
  QString syUPDATE = "";
  QString sUPDATETABLE = "";
  QString fields = "";
  QString values = "";
  QString sDel = "";

  int i = 0;
  for (; i < table->columnCount(); i++){
    QTableWidgetItem *it = table->item(0, i);
    if (it == 0) continue;
    QString sName = it->text();

    QString sOrder = "";
    it = table->item(1, i);
    if (it != 0) sOrder = it->text();

    QString sFilter = "";
    it = table->item(2, i);
    if (it != 0) sFilter = it->text();

    QString sGroup = "";
    it = table->item(3, i);
    if (it != 0) sGroup = it->text();

    QString sUpdate = "";
    it = table->item(4, i);
    if (it != 0) sUpdate = it->text();

    if (!sName.isEmpty()){

      if (!sySELECT.isEmpty()) sySELECT += ", ";
      sySELECT += sName;

      //
      int n = sName.indexOf(".");
      if (n == -1) return;
      QString sTable = sName.left(n);
      QString sName2 = sName.mid(n + 1);

      if (!sFROM.contains(sTable)){
        if (!sFROM.isEmpty()) sFROM += ", "; else sDel = sTable;
        sFROM += sTable;
      }


      //

      if (!sFilter.isEmpty()){
        if (!sWHERE.isEmpty()) sWHERE += " AND ";
        sWHERE += sName + " = " + sFilter;
        /*
        QVariant v = sFilter;
        if (v.canConvert(QVariant::Bool) || v.canConvert(QVariant::Double)  || v.canConvert(QVariant::Int)){
          sWHERE += sName + " = " + sFilter;
        } else {
          sWHERE += sName + " = '" + sFilter + "'";
        }*/
      }

      //

      if (!sGroup.isEmpty()){
        if (!sGROUP.isEmpty()) sGROUP += " ,";
        sGROUP += sName;
      }

      //

      if (!sUpdate.isEmpty()){
        if (!syUPDATE.isEmpty()) syUPDATE += " ,";
        syUPDATE += sName + " = " + sUpdate;
        sUPDATETABLE = sTable;

        if (!fields.isEmpty()) fields += " ,";
        fields += sName;

        if (!values.isEmpty()) fields += " ,";
        values += sUpdate;

      }

      //

      if (!sOrder.isEmpty()){
        if (!sORDER.isEmpty()) sORDER += ", ";
        if (!sName.contains("*")) sORDER += sName + " " + sOrder;
      }
    }
  }


  i = 0;
  for (; i < table->columnCount(); i++){
    QTableWidgetItem *it = table->item(0, i);
    if (it == 0) continue;
    QString sName = it->text();
/*
    it = table->item(1, i);
    if (it == 0) continue;
    QString sOrder = it->text();

    it = table->item(2, i);
    if (it == 0) continue;
    QString sFilter = it->text();

    it = table->item(2, i);
    if (it == 0) continue;
    QString sGroup = it->text();
*/
    if (!sName.isEmpty()){

      //
      int n = sName.indexOf(".");
      if (n == -1) return;
      QString sTable = sName.left(n);
      QString sName2 = sName.mid(n + 1);

      for (int i = 0; i <w->RelationRules.size(); ++i) {
        RelationRule r =w->RelationRules.at(i);

        if (r.sSourceName == sTable && sySELECT.contains(r.sDestinationName, Qt::CaseInsensitive)){
          QString k = r.sSourceName + "." + r.sSourceField + " = " + r.sDestinationName + "." + r.sDestinationField;
          if (!sWHERE.contains(k, Qt::CaseInsensitive)){
            if (!sWHERE.isEmpty()) sWHERE += " AND ";
            sWHERE += k;
          }
        }
      }
    }
  }
  sWHERE = "(" + sWHERE;
  sWHERE = sWHERE + ")";

  /*
  for (int i = 0; i <w->RelationRules.size(); ++i) {
    RelationRule &r =w->RelationRules[i];

    s += r.sSourceName;
    s += ".";
    s += r.sSourceField;
    s += "->";
    s += r.sDestinationName;
    s += ".";
    s += r.sDestinationField;
    s += ";";

  }*/

  if (i){
    if (!sySELECT.isEmpty()) s = "SELECT " + sySELECT;
    if (!sFROM.isEmpty()) s += " FROM " + sFROM;
    if (!sWHERE.isEmpty() && sWHERE.length() > 2) s += " WHERE " + sWHERE;
    if (!sGROUP.isEmpty() && sGROUP.length() > 2) s += " GROUP BY " + sGROUP;
    if (!sORDER.isEmpty()) s += " ORDER BY " + sORDER;

    sSELECT = "";
    sDELETE = "";
    sUPDATE = "";
    sINSERT = "";

    if (!sFROM.isEmpty()){
      sSELECT = s;

      sDELETE = "DELETE FROM " + sFROM;
      if (!sWHERE.isEmpty() && sWHERE.length() > 2) sDELETE += " WHERE " + sWHERE;

      if (!syUPDATE.isEmpty()){
        sUPDATE = "UPDATE " + sFROM + " SET " + syUPDATE;
        if (!sWHERE.isEmpty() && sWHERE.length() > 2) sUPDATE += " WHERE " + sWHERE;
      }
      
      if (!values.isEmpty()){
        sINSERT = "INSERT INTO " + sUPDATETABLE + " (" + fields + ") VALUES (" + values + ")";
      }
    }

  }
  

  {
    if (Select->isChecked()){ my_qbe_sql->setText(sSELECT); setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png"))); }
    else if (Insert->isChecked()){ my_qbe_sql->setText(sINSERT); setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_INSERT.png"))); }
    else if (Update->isChecked()){ my_qbe_sql->setText(sUPDATE); setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_UPDATE.png"))); }
    else if (Delete->isChecked()){ my_qbe_sql->setText(sDELETE); setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_DELETE.png"))); }
  }

}

void _qbe::addItem(QString sTable, QString sField)
{
  QString s = "";
  int n = 0;

  for (int i = 0; i < table->columnCount(); i++){
    QTableWidgetItem *it = table->item(0, i);
    if (it){
      s = it->text();
      if (s.isEmpty()){
        n = i;
        break;
      }
    } else {
      n = i + (i ? 0 : 0);
      break;
    }
  }
  if (n >= table->columnCount()) return;

  table->setItem(0, n, new QTableWidgetItem(sTable + "." + sField));
  table->setItem(1, n, new QTableWidgetItem("asc"));
  table->setItem(2, n, new QTableWidgetItem(""));

  refreshSQL();
}

void _qbe::loadRules(bool bApplyGeometry, QString sAddedTable)
{
 w->RelationRules.clear();

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

    if (sAddedTable != sTable && sAddedTable != sTable2) return;

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
//    if (b == false) return;

    bool bFound = false;
    l = w->windowList();
    for (int i = 0; i < l.size(); i++){

      QWidget *w = l.at(i);
      _qbe_table *o = 0;

      if ((o = qobject_cast<_qbe_table *>(w))){
        QString s = o->windowTitle();
        if (s == sTable){
          QList<QListWidgetItem *> ll = o->findItems(sField, Qt::MatchCaseSensitive);

          if (ll.at(0)){
            QFont f = ll.at(0)->font();
            f.setBold(true);
            ll.at(0)->setFont(f);

            rule.oSource = o;
            rule.nSourceIndex = o->row(ll.at(0));
            rule.sSourceName = sTable;
            rule.sSourceField = sField;
            bFound = true;
            break;
          }
        }        
      }
    }
    if (!bFound){
      addTable(sTable);
      return;
    }

    bFound = false;
    l = w->windowList();
    for (int i = 0; i < l.size(); i++){

      QWidget *ww = l.at(i);
      _qbe_table *o = 0;

      if ((o = qobject_cast<_qbe_table *>(ww))){
        QString s = o->windowTitle();
        if (s == sTable2){
          QList<QListWidgetItem *> ll = o->findItems(sField2, Qt::MatchCaseSensitive);

          if (ll.at(0)){
            QFont f = ll.at(0)->font();
            f.setBold(true);
            ll.at(0)->setFont(f);

            rule.oDestination = o;
            rule.nDestinationIndex = o->row(ll.at(0));
            rule.sDestinationName = sTable2;
            rule.sDestinationField = sField2;
            rule.sForeignKeyReplacement = sForeignKeyReplacement;

            w->RelationRules.append(rule);
            bFound = true;
            break;
          }
        }

      }
    }
    if (!bFound) addTable(sTable2);
    
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

void _qbe::saveRules()
{
  QString s = "";

  for (int i = 0; i <w->RelationRules.size(); ++i) {
    RelationRule &r =w->RelationRules[i];

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


void _qbe::load( const QString& fn)
{
  filename = fn;

  QString s = "";
  QFile f(filename);
  if (!f.open(QIODevice::ReadOnly)){
     QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(fn));
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s = s.replace("\r", "");
    f.close();
  }

  updateCaption(getFilenameWithoutPath());

  tb->setCurrentIndex(1);

 my_qbe_sql->setText(s);

  if (!parent){
    s = s.simplified();

    if (s.startsWith("INSERT INTO ", Qt::CaseInsensitive)){
      Insert->setChecked(true);
      setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_INSERT.png")));          
    } else if (s.startsWith("UPDATE ", Qt::CaseInsensitive)){
      Update->setChecked(true);
      setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_UPDATE.png")));          
    } else if (s.startsWith("DELETE ", Qt::CaseInsensitive)){
      Delete->setChecked(true);
      setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_DELETE.png")));          
    } else {
      Select->setChecked(true);
      setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")));          
    }
  }

  bIsModified = false;


  static bool bFirstTime = true;

  if (bFirstTime && EXTERN_my_mainwindow->isPreferenceSet("IntroductionHelp")){

    QMessageBox::information(this, tr("Queries"),
      tr(
    "When you save a query built with query by example,\n"
    "actually the sql statement is saved only.\n"
    )
    );

    bFirstTime = false;
  }
}

void _qbe::save(bool _saveAs)
{
  QString s = my_qbe_sql->toPlainText();

  QFile f(filename);
  if (!f.open(QIODevice::WriteOnly )){
    QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(filename));
    //  errormessage
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << s;
    f.close();

    bIsModified = false;


  if (!parent){
    s = s.simplified();

    if (s.startsWith("INSERT INTO ", Qt::CaseInsensitive)){
      setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_INSERT.png")));          
    } else if (s.startsWith("UPDATE ", Qt::CaseInsensitive)){
      setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_UPDATE.png")));          
    } else if (s.startsWith("DELETE ", Qt::CaseInsensitive)){
      setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY_DELETE.png")));          
    } else {
      setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")));          
    }
  }
  }

  EXTERN_my_projectwindow->refresh();

  //QMessageBox::information(this, MYAPP, tr("The SQL statement has been saved only."));
    
}

void _qbe::saveAs()
{
    QString fn = QFileDialog::getSaveFileName(this, MYAPP);
    if (!fn.isEmpty()){
      QFile f(fn);

      if (f.exists()){
	      switch( QMessageBox::warning( this, tr("Save As"), 
	          tr("File %1 already exists. Do want to overwrite?").arg( fn ),
	          tr("Yes"), tr("No"), tr("Cancel") ) ) {
	        case 0:
            bool b = filename != fn;
            filename = fn;
            save(b);            
	          break;
	      }
      } else {
        bool b = filename != fn;
        filename = fn;
        save(b);
      }

    }    
}

void _qbe::updateCaption(QString s, bool bSaving)
{


  if (s.isEmpty()){
    s = tr("unnamed document");    
  }
   
  if (!bSaving && bIsModified){
    s = s + "*";
  }

  setWindowTitle(s);
}

void _qbe::closeEvent( QCloseEvent *e )
{
  if (!parent && bIsModified){
      
	  show();
    setFocus();

	  switch( QMessageBox::question( this, tr("Save Changes"), 
	      tr("Save changes to %1?").arg( filename ),
	      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel )){
	    case QMessageBox::Yes:
	        {
		        save();
		        if (!filename.isEmpty())
		          goto a;
		        else
		          e->ignore();
	        }
	        break;
	    case QMessageBox::No:
	        goto a;
	        break;
	    default:
	        e->ignore();
          return;
	        break;
	  }

  } else {
	  goto a;
  }
//  return;

a:
  if (!parent) EXTERN_DatabaseTables->setShown(false);
  e->accept();

  if (parentWidget()){
    QMdiSubWindow *mdis = qobject_cast<QMdiSubWindow *>(parentWidget());
    EXTERN_my_mainwindow->workspace->removeSubWindow(mdis);
  }

  QWidget::closeEvent(e);


  
}

void _qbe::focusOutEvent(QFocusEvent *e)
{ 
//  EXTERN_DatabaseTables->setShown(false);
  QWidget::focusOutEvent(e);
}

void _qbe::focusInEvent(QFocusEvent *e)
{
  if (!parent){
 // EXTERN_DatabaseTables->setShown(true); EXTERN_DatabaseTables->setFloating(true);  qApp->setActiveWindow(EXTERN_DatabaseTables);


  EXTERN_my_mainwindow->workspace->setActiveSubWindow((QMdiSubWindow *) parentWidget());

  EXTERN_my_mainwindow->updateGeneralActions(
   false,  false,  false,  false, 
   true,  false,  false,  false,  false,   
   false,  false,  false, 
   false,  false,  false,  false, 
   false, ""
  );
  }

//  EXTERN_my_helpwindow->setText("Edit your your query here. Changes are translated into SQL statements.");

  QWidget::focusInEvent(e);

  if (!parent){
  EXTERN_DatabaseTables->setShown(true); EXTERN_DatabaseTables->setFloating(true);
  }
}

QString _qbe::getFilename(){ return filename; }



bool bQBEBlock = false;
 QBETableDelegate::QBETableDelegate(QObject *parent)
     : QItemDelegate(parent)
{ 
  bQBEBlock = false; 
}

 QWidget *QBETableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& ii,
     const QModelIndex &index) const
 {
      if(index.row() == 1){
          QComboBox *editor = new QComboBox(parent);
           
          editor->addItem("");
          editor->addItem("asc");
          editor->addItem("desc");

          connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(commitAndCloseEditor()));


          return editor;
      }
      if(index.row() == 3){
          QCheckBox *editor = new QCheckBox(tr("Yes"), parent);
/*          
          editor->addItem("");
          editor->addItem("asc");
          editor->addItem("desc");

          connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(commitAndCloseEditor()));
*/

          return editor;
      }
      return QItemDelegate::createEditor(parent, ii, index);


 }

 void QBETableDelegate::commitAndCloseEditor()
 {
  {
    QComboBox *editor = qobject_cast<QComboBox *>(sender());
    if (bQBEBlock == false && editor){
      emit commitData(editor);
      emit closeEditor(editor);
      return;
    }
  }

  {
    QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
    if (editor){
      emit commitData(editor);
      emit closeEditor(editor);
      return;
    }
  }

 }

 void QBETableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
 {

    QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
    if (edit) {
        edit->setText(index.model()->data(index, Qt::EditRole).toString());
        return;
    }
    else {
        QComboBox *e = qobject_cast<QComboBox *>(editor);
        if (e) {
          QString s = index.model()->data(index, Qt::EditRole).toString();
          bQBEBlock = true;
          e->setCurrentIndex(e->findText(s));
          bQBEBlock = false;
          return;
        }
    }

    QItemDelegate::setEditorData(editor, index);
 }

 void QBETableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
     const QModelIndex &index) const
 {    

        QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
        if (edit) {
            model->setData(index, edit->text());
            return;
        }
        else {
            QComboBox *e = qobject_cast<QComboBox *>(editor);
            if (e) {
              model->setData(index, e->itemText(e->currentIndex()));
              return;
            }

        }

        {
          QCheckBox *edit = qobject_cast<QCheckBox *>(editor);
          if (edit) {
              model->setData(index, edit->isChecked() ? "Yes" : "");
              return;
          }
        }

     QItemDelegate::setModelData(editor, model, index);
 }

/*
addTable()
removeTable();
*/

void _qbe::event_FORMAT_MOVE_LEFT()
{
  moveIt(true);
}

void _qbe::event_FORMAT_MOVE_RIGHT()
{
  moveIt(false);
}

void _qbe::moveIt(bool up)
{
  int Y = up ? nCurrentRow : nCurrentRow;
  int YY = up ? nCurrentRow - 1: nCurrentRow + 1;

  if (YY < 0) return;

  QString s = "";
  QString s2 = "";
  QString ds = "";
  QString ds2 = "";
  QString es = "";
  QString es2 = "";
  QString fs = "";
  QString fs2 = "";
  QString gs = "";
  QString gs2 = "";

  QTableWidgetItem *it = table->item(0, Y);
  if (it) s = it->data(Qt::DisplayRole).toString();

  QTableWidgetItem *it2 = table->item(0, YY);
  if (it2) s2 = it2->data(Qt::DisplayRole).toString();

  QTableWidgetItem *dit = table->item(1, Y);
  if (dit) ds = dit->data(Qt::DisplayRole).toString();

  QTableWidgetItem *dit2 = table->item(1, YY);
  if (dit2) ds2 = dit2->data(Qt::DisplayRole).toString();

  QTableWidgetItem *eit = table->item(2, Y);
  if (eit) es = eit->data(Qt::DisplayRole).toString();

  QTableWidgetItem *eit2 = table->item(2, YY);
  if (eit2) es2 = eit2->data(Qt::DisplayRole).toString();

  QTableWidgetItem *fit = table->item(3, Y);
  if (fit) fs = fit->data(Qt::DisplayRole).toString();

  QTableWidgetItem *fit2 = table->item(3, YY);
  if (fit2) fs2 = fit2->data(Qt::DisplayRole).toString();

  QTableWidgetItem *git = table->item(4, Y);
  if (git) gs = git->data(Qt::DisplayRole).toString();

  QTableWidgetItem *git2 = table->item(4, YY);
  if (git2) gs2 = git2->data(Qt::DisplayRole).toString();

  table->setItem(0, YY, new QTableWidgetItem(s));
  table->setItem(1, YY, new QTableWidgetItem(ds));
  table->setItem(2, YY, new QTableWidgetItem(es));
  table->setItem(3, YY, new QTableWidgetItem(fs));
  table->setItem(4, YY, new QTableWidgetItem(gs));

  table->setItem(0, Y, new QTableWidgetItem(s2));
  table->setItem(1, Y, new QTableWidgetItem(ds2));
  table->setItem(2, Y, new QTableWidgetItem(es2));
  table->setItem(3, Y, new QTableWidgetItem(fs2));
  table->setItem(4, Y, new QTableWidgetItem(gs2));

}

