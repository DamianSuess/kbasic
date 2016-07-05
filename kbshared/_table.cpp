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

#include "_table.h"
#include "../kbide/_help.h"

#include "../kbide/_mainwindow.h"
#include "../kbide/_propertywindow.h"
#include "../kbide/_helpwindow_shortcut.h"

#include "../kbide/_qbe_workspace.h"

extern QString kbasicPath(QString sPath);
extern _mainwindow *EXTERN_my_mainwindow;

extern _helpwindow_shortcut *EXTERN_my_helpwindow_shortcut;
extern _propertywindow *EXTERN_my_propertywindow;

extern QString idePath(QString sPath);

extern const QIcon &kbasicIcon(QString s);
extern int nPropertyWindowForWhat;

extern QSqlDatabase CurrentDatabase;

//extern _helpwindow *EXTERN_my_helpwindow;

extern QDockWidget *EXTERN_DatabaseTables;

_table *EXTERN_my_table;



 _table::_table() : QTableWidget(64, 3)
 {
  setAttribute(Qt::WA_DeleteOnClose);

  setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_TABLE.png")));

  nCurrentRow = 0;

  filename = "";
  updateCaption("");

  sCREATETABLE = "";
  
  bIsModified = false;
  bLoading = false;
  EXTERN_my_table = this;

  resize(500, 450);  

  setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
  setHorizontalHeaderItem(1, new QTableWidgetItem("Type"));
  setHorizontalHeaderItem(2, new QTableWidgetItem("Description"));
  QHeaderView *hh = horizontalHeader();
  hh->resizeSection(0, 100);
  hh->resizeSection(1, 150);
  hh->resizeSection(2, 300);
  hh->setClickable(false);

  QHeaderView *vv = verticalHeader();
  vv->setClickable(false);
  vv->setHidden(true);

  //setItemPrototype(table->item(rows - 1, cols - 1));
  setItemDelegate(new TableDelegate(QStringList()));
  setGridStyle(Qt::DashLine);

  //setItem(1, 0, new QTableWidgetItem("firma"));

  connect(this, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(currentCellChanged(int, int, int, int)));
  connect(this, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
   
  // EXTERN_my_mainwindow->workspace->setActiveSubWindow((QMdiSubWindow *) parent());


  
 }

void _table::event_FORMAT_MOVE_UP()
{
  moveIt(true);
}

void _table::event_FORMAT_MOVE_DOWN()
{
  moveIt(false);
}

void _table::moveIt(bool up)
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

  QTableWidgetItem *it = item(Y, 0);
  if (it) s = it->data(Qt::DisplayRole).toString();

  QTableWidgetItem *it2 = item(YY, 0);
  if (it2) s2 = it2->data(Qt::DisplayRole).toString();

  QTableWidgetItem *dit = item(Y, 1);
  if (dit) ds = dit->data(Qt::DisplayRole).toString();

  QTableWidgetItem *dit2 = item(YY, 1);
  if (dit2) ds2 = dit2->data(Qt::DisplayRole).toString();

  QTableWidgetItem *eit = item(Y, 2);
  if (eit) es = eit->data(Qt::DisplayRole).toString();

  QTableWidgetItem *eit2 = item(YY, 2);
  if (eit2) es2 = eit2->data(Qt::DisplayRole).toString();

  _tableitem *c;

  if (!s.isEmpty() && firstControl(&c)){

    do {

      if (((_tableitem *) c)->GETPROPERTY_Name() == s/* && ((_tableitem *) c)->bDeleted == false*/){
        c->nRow = YY;
        break;
      }

    } while (nextControl(&c));
    
  }

  if (!s2.isEmpty() && firstControl(&c)){

    do {

      if (((_tableitem *) c)->GETPROPERTY_Name() == s2/* && ((_tableitem *) c)->bDeleted == false*/){
        c->nRow = Y;
        break;
      }

    } while (nextControl(&c));
    
  }

  setItem(YY, 0, new QTableWidgetItem(s));
  setItem(YY, 1, new QTableWidgetItem(ds));
  setItem(YY, 2, new QTableWidgetItem(es));

  setItem(Y, 0, new QTableWidgetItem(s2));
  setItem(Y, 1, new QTableWidgetItem(ds2));
  setItem(Y, 2, new QTableWidgetItem(es2));

  unselectAllControls();



  if (firstControl(&c)){

    do {

      if (c->GETPROPERTY_Name() == s){

        QHeaderView *m = horizontalHeader();
        setFocus();
        m->setCurrentIndex(m->currentIndex().sibling(m->currentIndex().row() + (up ? -1 : 1), m->currentIndex().column()));    
        scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
        
        c->setAcceptDrops(true); // missused as selected flag
        break;
      }

    } while (nextControl(&c));

  }

  updatePropertyWindow();

}

QStringList _table::load( const QString& fn, bool bListOnly)
{
  bLoading = true;
  filename  = fn;
  loadTable(filename);

  QSqlRecord r = CurrentDatabase.record(getFilenameWithoutPathAndExtension());

  bool bDiffers = false;

  for (int i = 0; i < r.count(); ++i){
    QSqlField f = r.field(i);

    _tableitem *c = 0;

    if (firstControl(&c)){

      do {

        if (c->GETPROPERTY_Name() == f.name()){
          goto nex;
        }

      } while (nextControl(&c));

    }

    if (f.name() == "kbrecordid") continue;

    bDiffers = true;

    c = new _tableitem();
    METHOD_insertControl(c, t_tableitem);
    c->SETPROPERTY_Name(f.name());
    c->SETPROPERTY_LoadedName(f.name());

    switch(f.type()){
      case QVariant::Bool:
        c->SETPROPERTY_Type("Boolean");
        break;
      case QVariant::Date: 
      case QVariant::DateTime: 
        c->SETPROPERTY_Type("DateTime");        
        break;
      case QVariant::Double:
        c->SETPROPERTY_Type("Double");
        break;
      case QVariant::Int:
        c->SETPROPERTY_Type("Integer");
        break;
      case QVariant::LongLong:
        c->SETPROPERTY_Type("Long");
        break;
      case QVariant::String: 
        c->SETPROPERTY_Type("String");
        break;
      default:
        c->SETPROPERTY_Type("String");
        break;
    }

    
nex:
;
  }

  int i = 0;
  _tableitem *c;

  QStringList l;

  if (firstControl(&c)){

    do {

      if (bListOnly){
        l.append(c->GETPROPERTY_Name());
        l.append(c->GETPROPERTY_Type());
        l.append(c->GETPROPERTY_Index() ? "Index" : "");
        l.append(c->GETPROPERTY_Null() ? "Null" : "");
      } else {

        c->SETPROPERTY_LoadedName(c->GETPROPERTY_Name());
        c->SETPROPERTY_LoadedType(c->GETPROPERTY_Type());
        c->SETPROPERTY_LoadedIndex(c->GETPROPERTY_Index());
        c->SETPROPERTY_LoadedNull(c->GETPROPERTY_Null());

        setItem(i, 0, new QTableWidgetItem(c->GETPROPERTY_Name()));
        setItem(i, 1, new QTableWidgetItem(c->GETPROPERTY_Type()));
        setItem(i, 2, new QTableWidgetItem(c->GETPROPERTY_Tag()));
        c->nRow = i;
        i++;
      }

    } while (nextControl(&c));

  }

  updateCaption(getFilenameWithoutPath());
  bLoading = false;
/*
  QString s = "";

  filename  = fn;
  if (!filename.isEmpty()){
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly)){
      QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(filename));
      filename = "";
      return;
    }
    
	  QTextStream t(&f);
         t.setCodec("UTF-8");
         t.setAutoDetectUnicode(true);
         t.setGenerateByteOrderMark(true);
	  s = t.readAll();
    s = s.replace("\r", "");
	  f.close();   

    updateCaption(getFilenameWithoutPath());
    
  }
  */

  bool bFirst = true;

    if (bFirst && bDiffers){
      bFirst = false;

      QApplication::restoreOverrideCursor();

    QMessageBox::information( this, tr("Database Table Is Asynchron"),
      tr(
           "The table definition in KBasic differs from the table definition stored in the database.\n"       
           )
           );

    }

  return l;
}

void _table::save(bool bAlwaysSave)
{
  if (!bAlwaysSave && !bIsModified) return;


    bool bSQLite = false;
    bool bMySQL = false;
    bool bPSQL = false;
    bool bODBC = false;

    QSqlDriver *driver = CurrentDatabase.driver();

    if (CurrentDatabase.driverName().contains("sqlite", Qt::CaseInsensitive)){
      bSQLite = true;
    } else if (CurrentDatabase.driverName().contains("mysql", Qt::CaseInsensitive)){
      bMySQL = true;
    } else if (CurrentDatabase.driverName().contains("psql", Qt::CaseInsensitive)){
      bPSQL = true;
    } else if (CurrentDatabase.driverName().contains("odbc", Qt::CaseInsensitive)){
      bODBC = true;
    }
/*
   if (bSQLite){
     if (QMessageBox::question(this, tr("Change Database Table"), tr("Would you like to apply the changes to the database (WARNING! All data of that table will be lost)?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) return;
   }*/

   bool b = true;

  
  //if (QMessageBox::question(this, tr("Change Database Table"), tr("Would you like to apply the changes to the database (WARNING! Data of renamed or changed fields might be lost)?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) return;

  if (saveTable(getFilename())){

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

   QSqlQuery r;

   QString sTable = getFilenameWithoutPathAndExtension();

   QString s = "";
   QStringList l = CurrentDatabase.tables();

   
   QList< QMap<QString, QVariant> > sqlite_values;

   if (bSQLite && l.contains(sTable)){
     s = "SELECT * FROM " + sTable + ";";
     
     if (r.exec(s)){ 
       if (r.first()){
         do {

           QMap<QString, QVariant> sqlite_record;

           QSqlRecord rr = r.record();
           for (int i = 0; i < rr.count(); i++){
              QString sKey = rr.fieldName(i);
              //if (sKey.compare("kbrecordid", Qt::CaseInsensitive) == 0) continue;

              sqlite_record[sKey] = rr.value(i);
              int m = sqlite_record[sKey].type();
              m = m;
           }
           sqlite_values.append(sqlite_record);
      
         } while (r.next());
       }
     }

     s = "DROP TABLE " + sTable + ";";
     if (!r.exec(s)){ 
     //  QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); return; 
     }     
     goto sqlite;
   }

   foreach(QString k, l){
     if (sTable == k){

        _tableitem *c;

        if (firstControl(&c)){

          do {


            QString sOld = c->GETPROPERTY_LoadedName();
            QString sNew = c->GETPROPERTY_Name();

            if (!bSQLite && sNew.simplified().isEmpty()){
              s = "ALTER TABLE " + sTable + " DROP " + sOld;
              if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }
              continue;
            }

            QString sType = c->GETPROPERTY_Type();
            QString sOldType = c->GETPROPERTY_LoadedType();

            // check if field information changed
           // if (sOld == sNew && sType == c->GETPROPERTY_LoadedType() && c->GETPROPERTY_Null() == c->GETPROPERTY_LoadedNull() && c->GETPROPERTY_Index() == c->GETPROPERTY_LoadedIndex()) continue;            

            if (sType == "Integer"){
              sType = "integer";
            } else if (sType == "Byte"){
              if (bSQLite){
                sType = "integer";
              } else if (bPSQL){
                sType = "smallint";
              } else {
                sType = "tinyint";
              }              
            } else if (sType == "Short"){
              if (bSQLite){
                sType = "integer";
              } else {
                sType = "smallint";
              }                       
            } else if (sType == "Long"){
              if (bSQLite){
                sType = "integer";
              } else {
                sType = "bigint";
              }       
            } else if (sType == "Single"){
              if (bSQLite){
                sType = "real";
              } else if (bPSQL){
                sType = "real";
              } else {
                sType = "float";
              }                    
            } else if (sType == "Double"){
              if (bSQLite){
                sType = "real";
              } else {
                sType = "double";
              }     
            } else if (sType == "Boolean)"){
              if (bSQLite){
                sType = "integer";
              } else if (bODBC){
                sType = "smallint";
              } else {
                sType = "boolean";
              }
            } else if (sType == "DateTime"){
              if (bSQLite){
                sType = "text";
              } else if (bPSQL || bODBC){
                sType = "timestamp";
              } else {
                sType = "datetime";
              }      
            } else if (sType == "Decimal"){
              if (bSQLite){
                sType = "text";
              } else if (bPSQL){
                sType = "decimal";
              } else {
                sType = "decimal(10,4)";
              }      
            } else {              
              if (bMySQL){
                sType = "longtext";
              } else {
                sType = "text";
              }
            }

            // create temporary copy
            if (!sOld.isEmpty()){

              s = "DROP TABLE kbtmp_table;";
              if (!r.exec(s)){ 
              //  QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); return; 
              }

              s = "CREATE TABLE kbtmp_table (\n";
              s += "\nkbrecordid int NOT NULL,\nCONSTRAINT kbtmp_table_kbrecordid PRIMARY KEY (kbrecordid)\n);";
              if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }

              if (bSQLite){
                s = "CREATE INDEX kbtmp_table_idx_kbrecordid ON kbtmp_table (kbrecordid);";
              } else if (bMySQL){
                s = "CREATE INDEX kbtmp_table_idx_kbrecordid USING btree ON kbtmp_table (kbrecordid);";
              } else {
                s = "CREATE INDEX kbtmp_table_idx_kbrecordid ON kbtmp_table USING btree (kbrecordid);";
              }

              s = "ALTER TABLE kbtmp_table ADD kbchange_" + sNew + " " + sType + ";";
              if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }

              /*
              bool bString = false;
              bool bBoolean = false;
              bool bDouble = false;

              if (sType.contains("date", Qt::CaseInsensitive)){
                bString = true;
              } else if (sType.contains("time", Qt::CaseInsensitive)){
                bString = true;
              } else if (sType.contains("text", Qt::CaseInsensitive)){
                bString = true;
              } else if (sType.contains("boolean", Qt::CaseInsensitive)){
                bBoolean = true;
              } else if (sType.contains("float", Qt::CaseInsensitive)){
                bDouble = true;
              }*/

              QString s = "SELECT kbrecordid, " + sOld + " FROM " + sTable + " ORDER BY kbrecordid desc;";

              QSqlField f;

              if (r.exec(s)){
                QSqlRecord ri = r.record();
                if (r.first()){
                  do {
                    int n = ri.indexOf("kbrecordid");
                    qulonglong kbrecordid = r.value(n).toLongLong();
                    n = ri.indexOf(sOld);
                    //QString k = r.value(n).toString();

                    //if (k.isEmpty()) continue;

                    f.setValue(QVariant(r.value(n)));
                    k = driver->formatValue(f);

                    /*
                    if (bDouble){
                      //k = k + ".0";
                    } else if (bBoolean){
                      QVariant v = k;

                      switch(v.type()){
                        case QVariant::Bool:
                          break;
                        case QVariant::Date: 
                          k = "False";
                          break;
                        case QVariant::Time: 
                          k = "False";
                          break;
                        case QVariant::Double:
                          k = v.toDouble() != 0 ? "True" : "False";
                          break;
                        case QVariant::Int:
                          k = v.toInt() != 0 ? "True" : "False";
                          break;
                        case QVariant::String: 
                          k = v.toString().length() ? "True" : "False";
                          break;
                        default:
                          break;
                      }
                    }
                    */
                    //if (bString) k = "'" + k + "'";

                    QSqlQuery rr;
                    s = "INSERT INTO kbtmp_table ( kbrecordid, kbchange_" + sNew + ") VALUES (" + QString("%1").arg(kbrecordid) + ", " + k + ");";
                    if (!rr.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + rr.lastError().text()); goto ende; }

                  } while (r.next());
                }
              } else { QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }

            }

            QString sNotNull = c->GETPROPERTY_Null() ? "" : "NOT NULL";

            if (!bSQLite && !sOld.isEmpty()){
              s = "ALTER TABLE " + sTable + " DROP " + sOld;
              if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }
            }

            s = "ALTER TABLE " + sTable + " ADD " + sNew + " " + sType + " " + sNotNull + ";";
            if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }

            if (!sOld.isEmpty()){
              s = "DROP INDEX " + sTable + "_idx_" + sOld + ";";
              r.exec(s);
            }
            
            if (c->GETPROPERTY_Index()){

              if (bSQLite){
                s = "CREATE INDEX " + sTable + "_idx_" + sNew + " ON " + sTable + " (" + sNew + ");";
              } else if (bMySQL){
                s = "CREATE INDEX " + sTable + "_idx_" + sNew + " USING btree ON " + sTable + " (" + sNew + ");";
              } else {
                s = "CREATE INDEX " + sTable + "_idx_" + sNew + " ON " + sTable + " USING btree (" + sNew + ");";
              }
              
              if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }
            }

            // fill from temporary copy
            if (!sOld.isEmpty()){

              QString s = "SELECT kbrecordid, kbchange_" + sNew + " FROM kbtmp_table ORDER BY kbrecordid desc;";
/*
              bool bString = false;
              bool bBoolean = false;
              bool bDouble = false;

              if (sType.contains("date", Qt::CaseInsensitive)){
                bString = true;
              } else if (sType.contains("time", Qt::CaseInsensitive)){
                bString = true;
              } else if (sType.contains("text", Qt::CaseInsensitive)){
                bString = true;
              } else if (sType.contains("boolean", Qt::CaseInsensitive)){
                bBoolean = true;
              } else if (sType.contains("float", Qt::CaseInsensitive)){
                bDouble = true;
              }
*/
              if (r.exec(s)){
                QSqlRecord ri = r.record();
                if (r.first()){
                  do {
                    int n = ri.indexOf("kbrecordid");
                    qulonglong kbrecordid = r.value(n).toLongLong();
                    n = ri.indexOf("kbchange_" + sNew);

                    QSqlField f; 
                    f.setValue(QVariant(r.value(n)));
                    k = driver->formatValue(f);

                    /*
                    QString k = r.value(n).toString();

                    if (k.isEmpty()) continue;

                    if (bDouble){
                      //k = k + ".0";
                    } else if (bString) k = "'" + k + "'";*/

                    QSqlQuery rr;
                    s = "UPDATE " + sTable + " SET " + sNew + " = " + k + " WHERE kbrecordid = " + QString("%1").arg(kbrecordid);
                    if (!rr.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + rr.lastError().text()); goto ende; }

                  } while (r.next());
                }
              } else { QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }

              s = "DROP TABLE kbtmp_table;";
              if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }

              c->SETPROPERTY_LoadedName(c->GETPROPERTY_Name());

            }

          } while (nextControl(&c));

        }

       QApplication::restoreOverrideCursor();
       goto ende;
     }
   }
sqlite:
    s = "CREATE TABLE " + sTable + " (\n";

    _tableitem *c;


    if (firstControl(&c)){

      do {

        QString sNew = c->GETPROPERTY_Name();
        if (sNew.isEmpty()) continue;

        if (!b) s += ",\n";
        if (b) b = false;

        QString sType = c->GETPROPERTY_Type();

        if (sType == "Integer"){
          sType = "integer";
        } else if (sType == "Byte"){
          if (bSQLite){
            sType = "integer";
          } else if (bPSQL){
            sType = "smallint";
          } else {
            sType = "tinyint";
          }              
        } else if (sType == "Short"){
          if (bSQLite){
            sType = "integer";
          } else {
            sType = "smallint";
          }                       
        } else if (sType == "Long"){
          if (bSQLite){
            sType = "integer";
          } else {
            sType = "bigint";
          }       
        } else if (sType == "Single"){
          if (bSQLite){
            sType = "real";
          } else if (bPSQL){
            sType = "real";
          } else {
            sType = "float";
          }                    
        } else if (sType == "Double"){
          if (bSQLite){
            sType = "real";
          } else {
            sType = "double";
          }     
        } else if (sType == "Boolean)"){
          if (bSQLite){
            sType = "integer";
          } else if (bODBC){
            sType = "smallint";
          } else {
            sType = "boolean";
          }
        } else if (sType == "DateTime"){
          if (bSQLite){
            sType = "text";
          } else if (bPSQL || bODBC){
            sType = "timestamp";
          } else {
            sType = "datetime";
          }      
        } else if (sType == "Decimal"){
          if (bSQLite){
            sType = "text";
          } else if (bPSQL){
            sType = "decimal";
          } else {
            sType = "decimal(10,4)";
          }      
        } else {              
          if (bMySQL){
            sType = "longtext";
          } else {
            sType = "text";
          }
        }

        QString sNotNull = c->GETPROPERTY_Null() ? "" : "NOT NULL";

        s += sNew;
        s += " ";
        s += sType;
        s += " ";
        s += sNotNull;

      } while (nextControl(&c)); 

    }

    if (!b) s += ",\n";
    s += "\nkbrecordid integer NOT NULL,\nCONSTRAINT " + sTable + "_kbrecordid PRIMARY KEY (kbrecordid)\n);";
    if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }

    if (bSQLite){
      s = "CREATE INDEX " + sTable + "_idx_kbrecordid ON " + sTable + " (kbrecordid);";
    } else if (bMySQL){
      s = "CREATE INDEX " + sTable + "_idx_kbrecordid USING btree ON " + sTable + " (kbrecordid);";
    } else {
      s = "CREATE INDEX " + sTable + "_idx_kbrecordid ON " + sTable + " USING btree (kbrecordid);";
    }
    if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }       

    if (firstControl(&c)){

      do {

        QString sOld = c->GETPROPERTY_LoadedName();
        QString sNew = c->GETPROPERTY_Name();
        QString sType = c->GETPROPERTY_Type();

        if (sType == "Integer"){
          sType = "integer";
        } else if (sType == "Byte"){
          if (bSQLite){
            sType = "integer";
          } else if (bPSQL){
            sType = "smallint";
          } else {
            sType = "tinyint";
          }              
        } else if (sType == "Short"){
          if (bSQLite){
            sType = "integer";
          } else {
            sType = "smallint";
          }                       
        } else if (sType == "Long"){
          if (bSQLite){
            sType = "integer";
          } else {
            sType = "bigint";
          }       
        } else if (sType == "Single"){
          if (bSQLite){
            sType = "real";
          } else if (bPSQL){
            sType = "real";
          } else {
            sType = "float";
          }                    
        } else if (sType == "Double"){
          if (bSQLite){
            sType = "real";
          } else {
            sType = "double";
          }     
        } else if (sType == "Boolean)"){
          if (bSQLite){
            sType = "integer";
          } else if (bODBC){
            sType = "smallint";
          } else {
            sType = "boolean";
          }
        } else if (sType == "DateTime"){
          if (bSQLite){
            sType = "text";
          } else if (bPSQL || bODBC){
            sType = "timestamp";
          } else {
            sType = "datetime";
          }      
        } else if (sType == "Decimal"){
          if (bSQLite){
            sType = "text";
          } else if (bPSQL){
            sType = "decimal";
          } else {
            sType = "decimal(10,4)";
          }      
        } else {              
          if (bMySQL){
            sType = "longtext";
          } else {
            sType = "text";
          }
        }

        QString sNotNull = c->GETPROPERTY_Null() ? "" : "NOT NULL";

        s = "DROP INDEX " + sTable + "_idx_" + sOld + ";";
        r.exec(s);
        
        if (c->GETPROPERTY_Index()){
          if (bMySQL){
            s = "CREATE INDEX " + sTable + "_idx_" + sNew + " USING btree ON " + sTable + "(" + sNew + ");";
          } else {
            s = "CREATE INDEX " + sTable + "_idx_" + sNew + " ON " + sTable + (bSQLite ? "" : " USING btree ") + "(" + sNew + ");";
          }
          if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }
        }

        c->SETPROPERTY_LoadedName(c->GETPROPERTY_Name());

      } while (nextControl(&c));

      if (sqlite_values.count()){
        for (int i = 0; i < sqlite_values.size(); ++i){
           QMap<QString, QVariant> sqlite_record = sqlite_values[i];

           QString fields = "";
           QString values = "";

           int x = 0;
           QMapIterator<QString, QVariant> ii(sqlite_record);
           while (ii.hasNext()) {
               ii.next();
               if (x) fields += ", ";
               fields += ii.key();
               if (x) values += ", ";

               QSqlField f; 
               f.setValue(ii.value());
               f.setType(ii.value().type());
              // int m = ii.value().type();
               values += driver->formatValue(f);

               x++;
           }

           s = "INSERT INTO " + sTable + "(" + fields + ") VALUES (" + values + ")";      
           if (!r.exec(s)){ QApplication::restoreOverrideCursor(); QMessageBox::information(this, MYAPP, tr("An error occured! Could not save or change the database table completely: \n\n") + s + "\n\n" + r.lastError().text()); goto ende; }
      
        }

      }
    }
    QApplication::restoreOverrideCursor();

ende:
    // set table data dirty
    QList<QMdiSubWindow *> windows = EXTERN_my_mainwindow->workspace->subWindowList();
    if (int(windows.count())){    
      for (int i = 0; i < windows.count(); i++){	    
        QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

        _tableviewer *o = qobject_cast<_tableviewer *>(w);
        if (o && o->objectName() == getFilename()){
          o->bDirty = true;
          break;
        }
      }
    }  


  }

}

void _table::saveAs()
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

void _table::updateCaption(QString s, bool bSaving)
{
  if (s.isEmpty()){
    s = tr("unnamed document");    
  }
   
  if (!bSaving && bIsModified){
    s = s + "*";
  }

  setWindowTitle(s);
}

void _table::closeEvent( QCloseEvent *e )
{
  if (bIsModified){
      
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
 // 

a:
  EXTERN_my_table = 0;
  e->accept();

  if (parentWidget()){
    QMdiSubWindow *mdis = qobject_cast<QMdiSubWindow *>(parentWidget());
    EXTERN_my_mainwindow->workspace->removeSubWindow(mdis);
  }

  QWidget::closeEvent(e);
}


void _table::focusInEvent(QFocusEvent *e)
{
  EXTERN_my_mainwindow->workspace->setActiveSubWindow((QMdiSubWindow *) parentWidget());

  EXTERN_my_mainwindow->updateGeneralActions(
   false,  false,  false,  false, 
   false,  false,  true,  false,  false,   
   false,  false,  false, 
   false,  false,  false,  false, 
   false, ""
  );

  updatePropertyWindow();
  EXTERN_my_table = this;

//  EXTERN_my_helpwindow->setText("Edit your your table here. Changes are translated into SQL statements.");

  if (e) QWidget::focusInEvent(e);

  EXTERN_DatabaseTables->setShown(false);
}

QString _table::getFilename(){ return filename; }

void _table::updatePropertyWindow()
{
  EXTERN_my_propertywindow->setform->setHidden(true);
  EXTERN_my_propertywindow->showControlName("");

  _tableitem *c;
  
  //int nn = p.count();
  p.clear();

  //if (!bObjectEditor) _property::addProperties(&p, &EXTERN_my_mainwindow->allProperties);

 // bool bForm = true;
  bool bb = true;

  if (firstControl(&c)){

    do {

      if (c->acceptDrops()){ // missused as selected flag        
      //  bForm = false;

      #define SWITCH getProperties();
      #define SWITCH3 p2
      #include "_table_property_switch.h" 
      #undef SWITCH3

        if (bb){
          bb = false;

          _property::addProperties(&p, p2);

        } else {

          _property::mergeProperties(&p, p2);
        }

      }

    } while (nextControl(&c));
    
  }
/*
  if (bForm){    
    //if (!bObjectEditor) _property::mergeProperties(&p, this->getProperties());
    //else 
    _property::addProperties(&p, this->getProperties());
  }*/

  updatePropertyWindow2(true);  

}


void _table::updatePropertyWindow2(bool bb, QString sProperty)
{

  
/*
  if (my_propertywindow == 0){
    showUpdatePropertyWindow();
    return;
  }
*/
  t_properties::Iterator it;
  t_properties *a;
  t_property *d =  0;
  bool b = false;
  QString ss = "";
/*
  if (sProperty.length()){ // speed optimization
   

    b = true;
    d = (t_property *) 1;

         if (sProperty == "X"){ d = (*a)["X"]; if (d) goto _X; }
    else if (sProperty == "Y"){ d = (*a)["Y"]; if (d) goto _Y; }
    else if (sProperty == "Width"){ d = (*a)["Width"]; if (d) goto _Width; }
    else if (sProperty == "Height"){ d = (*a)["Height"]; if (d) goto _Height; }

    if (d == 0){
//      showUpdatePropertyWindow();
      return;
    }

    b = false;
  }

  //EXTERN_my_propertywindow->SETPROPERTY_Name(d->display, d->set, d->v_qstring);*/
  if (bb){
    EXTERN_my_propertywindow->setEnabled(false);
    EXTERN_my_propertywindow->showProperties(false);
/*
    EXTERN_my_propertywindow->SETPROPERTY_Name(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_ControlType(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_Caption(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_StatusTip(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_WhatsThis(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_Icon(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_Caption(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_Icon(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_Key(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_Enabled(false, false, false);
    EXTERN_my_propertywindow->SETPROPERTY_ParentIndex(false, false, 0);
    EXTERN_my_propertywindow->SETPROPERTY_Tag(false, false, "");
    EXTERN_my_propertywindow->SETPROPERTY_Visible(false, false, false);*/
  }

  EXTERN_my_propertywindow->setUpdatesEnabled(false);
  for ( it = p.begin(); it != p.end(); ++it){

    ss = it.key();
    d = *it;

    if (ss == "Name"){
     EXTERN_my_propertywindow->SETPROPERTY_Name(d->display, d->set, d->v_qstring);


    } else if (ss == "ControlType"){
     EXTERN_my_propertywindow->SETPROPERTY_ControlType(d->display, d->set, d->v_qstring);
    
  //  } else if (ss == "Null"){ EXTERN_my_propertywindow->SETPROPERTY_Null(d->display, d->set, d->v_boolean);
  //  } else if (ss == "Index"){ EXTERN_my_propertywindow->SETPROPERTY_Index(d->display, d->set, d->v_boolean);

    /*
    } else if (ss == "Caption"){
     EXTERN_my_propertywindow->SETPROPERTY_Caption(d->display, d->set, d->v_qstring);

    } else if (ss == "StatusTip"){ EXTERN_my_propertywindow->SETPROPERTY_StatusTip(d->display, d->set, d->v_qstring);
    } else if (ss == "ToolTip"){ EXTERN_my_propertywindow->SETPROPERTY_ToolTip(d->display, d->set, d->v_qstring);
    //} else if (ss == "StyleSheet"){ EXTERN_my_propertywindow->SETPROPERTY_StyleSheet(d->display, d->set, d->v_qstring);
    } else if (ss == "WhatsThis"){ EXTERN_my_propertywindow->SETPROPERTY_WhatsThis(d->display, d->set, d->v_qstring);

    //} else if (ss == "Flag"){ EXTERN_my_propertywindow->SETPROPERTY_Flag(d->display, d->set, d->v_qstring);
    } else if (ss == "Icon"){ EXTERN_my_propertywindow->SETPROPERTY_Icon(d->display, d->set, d->v_qstring);
    //} else if (ss == "IconCaption"){ EXTERN_my_propertywindow->SETPROPERTY_IconCaption(d->display, d->set, d->v_qstring);
    //} else if (ss == "Caption"){ EXTERN_my_propertywindow->SETPROPERTY_Caption(d->display, d->set, d->v_qstring);

    //} else if (ss == "Icon"){ EXTERN_my_propertywindow->SETPROPERTY_Icon(d->display, d->set, d->v_qstring);
   // } else if (ss == "InputControl"){ EXTERN_my_propertywindow->SETPROPERTY_InputControl(d->display, d->set, d->v_qstring);

    } else if (ss == "Space"){ EXTERN_my_propertywindow->SETPROPERTY_Space(d->display, d->set, d->v_integer);
    } else if (ss == "Border"){ EXTERN_my_propertywindow->SETPROPERTY_Border(d->display, d->set, d->v_integer);

    } else if (ss == "Flat"){ EXTERN_my_propertywindow->SETPROPERTY_Flat(d->display, d->set, d->v_boolean);
*/
    //} else if (ss == "Key"){ EXTERN_my_propertywindow->SETPROPERTY_Key(d->display, d->set, d->v_qstring);

    // EVENT
    } 
    
    // ***

  }

  EXTERN_my_propertywindow->setUpdatesEnabled(true);
  if (bb){
    EXTERN_my_propertywindow->setEnabled(p.count()); nPropertyWindowForWhat = -1;
    //EXTERN_my_propertywindow->showProperties(true);
  }

  


}


void _table::currentCellChanged ( int currentRow, int currentColumn, int previousRow, int previousColumn )   
{
  if (bLoading) return;

  nCurrentRow = currentRow;

  if (currentRow != previousRow){
    unselectAllControls();

    _tableitem *c;
    
    bool b = false;
    QString s = "";
    QTableWidgetItem *it = item(currentRow, 0);
    if (it) s = it->data(Qt::DisplayRole).toString();

    if (!s.isEmpty() && firstControl(&c)){

      do {

        if (((_tableitem *) c)->GETPROPERTY_Name() == s/* && ((_tableitem *) c)->bDeleted == false*/){
          c->setAcceptDrops(true); // missused as selected flag        
          b = true;
          break;
        }

      } while (nextControl(&c));
      
    }

    if (b == false) unselectAllControls();

    updatePropertyWindow();

  }
}

void _table::cellChanged( int row, int column )
{
  if (bLoading) return;

  _tableitem *c;      
  QString s = "";
  QTableWidgetItem *it = item(row, column);
  if (it) s = it->data(Qt::DisplayRole).toString();

  bIsModified = true;

  if (column == 0){    

    if (firstControl(&c)){

      do {

        if (!s.isEmpty() && c->GETPROPERTY_Name() == s/* && c->bDeleted == false*/){
          setAcceptDrops(false); // missused as selected flag        
          updatePropertyWindow();
          return;
        }

      } while (nextControl(&c));

    }

    if (firstControl(&c)){

      do {

        if (c->nRow == row){
          if (c->GETPROPERTY_LoadedName().isEmpty()) c->SETPROPERTY_LoadedName(c->GETPROPERTY_Name());
          c->SETPROPERTY_Name(s);   
          if (s.isEmpty()){
            unselectAllControls();
            updatePropertyWindow();
          }
          return;
        }

      } while (nextControl(&c));

    }
    if (s.isEmpty()) return;

    // create new one
    unselectAllControls();
    _tableitem *t = new _tableitem();
    t->setAcceptDrops(true); // missused as selected flag        
    //t->SETPROPERTY_OldName(t->GETPROPERTY_Name());
    t->nRow = row;
    METHOD_insertControl(t, t_tableitem, s);
    updatePropertyWindow();
      
  } else if (column == 1){

    if (firstControl(&c)){

      do {

        if (c->nRow == row){
          c->SETPROPERTY_Type(s);
          return;
        }

      } while (nextControl(&c));
    }
 
  } else if (column == 2){

    if (firstControl(&c)){

      do {

        if (c->nRow == row){
          c->SETPROPERTY_Tag(s);
          return;
        }

      } while (nextControl(&c));
    }
  }
}


// ****************************

bool bBlock = false;

 TableDelegate::TableDelegate(QStringList _l, QObject *parent, QSqlRelationalTableModel *_showData)
     : QSqlRelationalDelegate(parent)
{ 
       bBlock = false; 
       showData = _showData;
       l = _l;
}

 QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& ii,
     const QModelIndex &index) const
 {
   if (showData){

     int n = index.column();
     QSqlRelation r = showData->relation(n);
     if (!r.isValid()){

        QSqlRecord r = showData->record();
        QSqlField f = r.field(n);

        QString k = f.name();

        bool bName = true;
        bool bFound = false;

        QString t = "";
        for (int y = 0; y < l.size(); y += 4){ 
          if (l.at(y + 0) == k){
            t = l.at(y + 1);
            bFound = true;
            break;
          }
        }

        if (bFound){
          if (t.contains("Double", Qt::CaseInsensitive)){
            QLineEdit *editor = new QLineEdit(parent);
            editor->setValidator(new QDoubleValidator(editor));
            connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
            return editor;
          }
         

            if (t.contains("Big String", Qt::CaseInsensitive)/* || t.contains("HtmlView", Qt::CaseInsensitive)*/){
                QTextEdit *editor = new QTextEdit(parent);
                editor->setTabChangesFocus(false);
                return editor;
            }
          }
     }
     
 /*
      switch(f.type()){
        case QVariant::Double:
          {
            QLineEdit *editor = new QLineEdit(parent);
            editor->setValidator(new QDoubleValidator(editor));
            connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
            return editor;
          }
          break;
         

      }*/

      /*
    if ( == n){

                QSqlRecord ri = r.record();
                    int nn = ri.indexOf("kbrecordid");
                    qulonglong kbrecordid = r.value(n).toLongLong();

*/



      return QSqlRelationalDelegate::createEditor(parent, ii, index);

   } else {

      if(index.column() == 1){
          QComboBox *editor = new QComboBox(parent);
           
          editor->addItem("");
          editor->addItem("Boolean");
          editor->addItem("");
          editor->addItem("String");
          editor->addItem("");
          editor->addItem("Byte");
          editor->addItem("Short");
          editor->addItem("Integer");
          editor->addItem("Long");
          editor->addItem("");
          editor->addItem("Single");
          editor->addItem("Double");

     //     editor->addItem("");
     //     editor->addItem("TextBox (Big String)");
/*
          editor->addItem("");
          editor->addItem("ListBox (Integer)");
          editor->addItem("ComboBox (Integer)");

          editor->addItem("");

          editor->addItem("Editor (String)");

          editor->addItem("Browser (String)");
          editor->addItem("");*/
          editor->addItem("");
          editor->addItem("Decimal");
          editor->addItem("DateTime");
          editor->addItem("");
/*
          editor->addItem("");
          editor->addItem("ImageBox");
          editor->addItem("Video");
          editor->addItem("File");

          editor->addItem("String");
          editor->addItem("Boolean");
          editor->addItem("Integer");
          editor->addItem("Double");
  */

          connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(commitAndCloseEditor()));



          return editor;
      }
      QLineEdit *editor = new QLineEdit(parent);

      connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
      return editor;
   }
 }

 void TableDelegate::commitAndCloseEditor()
 {
  {
    QComboBox *editor = qobject_cast<QComboBox *>(sender());
    if (bBlock == false && editor){
      emit commitData(editor);
      emit closeEditor(editor);
     // emit closeEditor(editor, showData ? QAbstractItemDelegate::EditNextItem : QAbstractItemDelegate::NoHint);
      return;
    }
  }

  {
    QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
    if (editor){
      emit commitData(editor);
      emit closeEditor(editor);
     // emit closeEditor(editor, showData ? QAbstractItemDelegate::EditNextItem : QAbstractItemDelegate::NoHint);
      return;
    }
  }

//  return QSqlRelationalDelegate::commitAndCloseEditor();


 }

bool TableDelegate::eventFilter ( QObject * editor, QEvent * event )
{
  if (showData){
    QTextEdit *e = qobject_cast<QTextEdit *>(editor);
    if (e){

      if (event->type() == QEvent::KeyPress){
        QKeyEvent *event2 = (QKeyEvent *) event;
        if (event2){
          int n = event2->key();

          if ((n == Qt::Key_Return || n == Qt::Key_Enter)){

            int nn = event2->modifiers();
            if (event2->modifiers() == Qt::ControlModifier){
              return false; // ignore CTRL+RETURN 
            }
          }
          
        }
      }

      
    }
  }

  return QSqlRelationalDelegate::eventFilter(editor, event);
}


 void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
 {
     int n = index.column();
     QSqlRelation r;
     if (showData) r = showData->relation(n);
     if (!r.isValid()){

        QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
        if (edit) {
            edit->setText(index.model()->data(index, Qt::EditRole).toString());
            /*
            if (showData){
              //QModelIndex idx = m->currentIndex();
              parent()->setCurrentIndex(index.sibling(index.row(), index.column() + 1));    
              view->scrollTo(showData->currentIndex(), QAbstractItemView::PositionAtCenter);             
            }           */
            return;
        }
        else {
            QComboBox *e = qobject_cast<QComboBox *>(editor);
            if (e) {
              QString s = index.model()->data(index, Qt::EditRole).toString();
              bBlock = true;
              e->setCurrentIndex(e->findText(s));
              bBlock = false;
              return;
            }

            {
                QTextEdit *e = qobject_cast<QTextEdit *>(editor);
                if (e) {
                  QString s = index.model()->data(index, Qt::EditRole).toString();
                  e->setPlainText(s);
                  return;
                }
            }
        }
     }
     QSqlRelationalDelegate::setEditorData(editor, index);
 }

 void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
     const QModelIndex &index) const
 {
     int n = index.column();
     QSqlRelation r;
     if (showData) r = showData->relation(n);
     if (!r.isValid()){

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
            {
                QTextEdit *e = qobject_cast<QTextEdit *>(editor);
                if (e) {
                  model->setData(index, e->toPlainText());
                  return;
                }
            }
        }
     }
     QSqlRelationalDelegate::setModelData(editor, model, index);
 }

 void _table::showData()
 {
 

  QString sTable = getFilenameWithoutPathAndExtension();

  QList<QMdiSubWindow *> windows = EXTERN_my_mainwindow->workspace->subWindowList();

  if (int(windows.count())){    
    QString kk = sTable;
    kk += tr(" : Table Data");

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i); QWidget *w = ww->widget();

      _tableviewer *o = qobject_cast<_tableviewer *>(w);
      if (o){
        QString k = o->windowTitle();
        if (kk == k){
          o->show();  
          o->activateWindow();
          o->setFocus();
          return;
        }
      }
    }
  }

 save();

  if (!CurrentDatabase.isOpen()/* || CurrentDatabase.isOpenError()*/){
    QMessageBox::information(this, MYAPP, "You are not connected to a database.");      
    return;
  }

  new _tableviewer(0, getFilename());

}

 
 
_tableviewer::_tableviewer(QWidget *parent, QString ss) : QWidget(parent)
{
  bDirty = false;
  bSetTimerPos = false;
  bBlockTimer = false;

  sTable = EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(ss);
  this->setObjectName(ss);
  
  _table o; 
  QStringList l = o.load(ss, true);

  sGlobalFields = "";
  sGlobalValues = "";


  model = new QSqlRelationalTableModel ;
  model->setTable(sTable);
  model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
  model->setSort(model->fieldIndex("kbrecordid"), Qt::AscendingOrder);

  { // set relations
    RelationRules.clear();
    QString s = EXTERN_my_mainwindow->getProjectPreference("RELATIONS");
    QStringList l = s.split(";", QString::SkipEmptyParts);

    for (int i = 0; i < l.size(); i++){
      s = l.at(i);
      int n = s.indexOf("->");
      QString le = s.left(n);
      QString ri = s.mid(n + 2);

      n = le.indexOf(".");
      QString sTable99 = le.left(n);
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

      if (sTable == sTable99){
        int k = model->fieldIndex(sField);
        if (k >= 0) model->setRelation(k, QSqlRelation(sTable2, sField2, sForeignKeyReplacement));
        QSqlRelation r = model->relation(k);
        bool b = r.isValid();

        if (b){
          sGlobalFields += ", ";
          sGlobalFields += sField;
          sGlobalValues += ", ";
          sGlobalValues += "0";
        }
      }
    }
  }
  model->select();

  

  view = new TableView(this);
  
  
//  view->setItemDelegate(new QSqlRelationalDelegate());
  tg = new TableDelegate(l, 0, model);
  view->setItemDelegate(tg);
  view->setModel(model);
  view->setSelectionMode(QAbstractItemView::SingleSelection);

  QHeaderView *horizontalHeader = view->horizontalHeader();
  int m = model->fieldIndex("kbrecordid");
  if (m >= 0) horizontalHeader->hideSection(m);

  //view->setEditTriggers(QAbstractItemView::EditKeyPressed | QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
#ifdef MAC
  view->setAlternatingRowColors(true); // HIDE
#endif

  
  //setFocusProxy(view);


  QHeaderView *hh = view->horizontalHeader();

  hh->setMovable(true);
  QSqlRecord r = model->record();
  int n = r.indexOf("kbrecordid");
  hh->moveSection(hh->visualIndex(n), 0);
  for (int i = 0; i < l.size() / 4; i++){
    QString u = l.at(i * 4 + 0);
    if (u == "kbrecordid" || u.isEmpty()) continue;

    n = r.indexOf(u);
    hh->moveSection(hh->visualIndex(n), i + 1);
  }
  hh->setClickable(false);
  
  QHeaderView *vv = view->verticalHeader();
  //vv->setMinimumSectionSize(200);
  //vv->setHidden(true);
 // vv->setResizeMode(QHeaderView::ResizeToContents);

  //QWidget *window = new QWidget();
  QVBoxLayout *vl = new QVBoxLayout();
  vl->setSpacing(0);
  vl->setMargin(0);

  QHBoxLayout *hl = new QHBoxLayout();
  hl->setSpacing(0);
  hl->setMargin(0);

  this->setLayout(vl);
  vl->addWidget(view);
  vl->addLayout(hl);

  QLabel *ll = new QLabel(tr(" Recordset:")); ll->setFixedWidth(80);
  hl->addWidget(ll);

  SQLGoTo = new QLineEdit(); SQLGoTo->setFixedWidth(70); connect(SQLGoTo, SIGNAL(editingFinished()), this, SLOT(SQLGoto())); SQLGoTo->setToolTip(tr("GoTo"));

  QPushButton *p;

  SQLInfo = new QLabel(tr(" of ") + QString("%1").arg(model->rowCount()) + tr(" record(s)")); SQLInfo->setFixedWidth(150);

  
  p = new QPushButton(QIcon(idePath("SQLFirst.png")), ""); p->setToolTip(tr("First")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLFirst())); p->setFixedSize(20, 20); hl->addWidget(p);
  p = new QPushButton(QIcon(idePath("SQLPrevious.png")), ""); p->setToolTip(tr("Previous")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLBackward())); p->setFixedSize(20, 20); hl->addWidget(p);
  hl->addWidget(SQLGoTo);
  p = new QPushButton(QIcon(idePath("SQLNext.png")), ""); p->setToolTip(tr("Next")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLForward())); p->setFixedSize(20, 20); hl->addWidget(p);
  p = new QPushButton(QIcon(idePath("SQLLast.png")), ""); p->setToolTip(tr("Last")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLLast())); p->setFixedSize(20, 20); hl->addWidget(p);
  p = new QPushButton(QIcon(idePath("SQLAddNew.png")), ""); p->setToolTip(tr("Add New")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLAddNew())); p->setFixedSize(20, 20); hl->addWidget(p);
  p = new QPushButton(QIcon(idePath("SQLAddNew100.png")), ""); p->setToolTip(tr("Add 100 New")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLAddNew100())); p->setFixedSize(20, 20); hl->addWidget(p);
  //p = new QPushButton(QIcon(idePath("SQLUpdate.png")), ""); p->setToolTip(tr("SQLUpdate")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLUpdate())); p->setFixedSize(20, 20); hl->addWidget(p);
  hl->addWidget(SQLInfo);  
  p = new QPushButton(QIcon(idePath("SQLDelete.png")), ""); p->setToolTip(tr("Delete Current")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLDelete())); p->setFixedSize(20, 20); hl->addWidget(p);

  QLabel *lll = new QLabel(""); lll->setFixedWidth(40); hl->addWidget(lll);

  p = new QPushButton(QIcon(idePath("SQLDeleteAll.png")), ""); p->setToolTip(tr("Delete All")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLDeleteAll())); p->setFixedSize(20, 20); hl->addWidget(p);
  /*
  p = new QPushButton(QIcon(idePath("SQLCut.png")), ""); p->setToolTip(tr("Cut")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLCut())); p->setFixedSize(20, 20); hl->addWidget(p);
  p = new QPushButton(QIcon(idePath("SQLCopy.png")), ""); p->setToolTip(tr("Copy")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLCopy())); p->setFixedSize(20, 20); hl->addWidget(p);
  p = new QPushButton(QIcon(idePath("SQLPaste.png")), ""); p->setToolTip(tr("Paste")); connect(p, SIGNAL( clicked() ), this, SLOT(SQLPaste())); p->setFixedSize(20, 20); hl->addWidget(p);
  */
  #ifndef MAC
  hl->addStretch(2000);

  #endif

  this->setWindowTitle(sTable + tr(" : Table Data"));
  this->setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")));

  /*
  QSqlQuery rr;
  QString s = "SELECT kbrecordid FROM " + sTable + " ORDER BY kbrecordid desc";
  if (!rr.exec(s)){    
    SQLAddNew100();
  } else if (!rr.first()){
    SQLAddNew100();
  }*/

  SQLFirst();


  QMdiSubWindow *w = new QMdiSubWindow(); // do it this way cause of Qt bug
  w->setAttribute(Qt::WA_DeleteOnClose);
  w->setWidget(this);
  EXTERN_my_mainwindow->workspace->addSubWindow(w);


  //nTimer = startTimer(50);

  showMaximized();
  setFocus();

  EXTERN_my_mainwindow->workspace->setActiveSubWindow(w);
  
}


_tableviewer::~_tableviewer()
{
  delete model;
  delete tg;
}


extern bool bLockDirectoryChanged;

void _tableviewer::focusOutEvent(QFocusEvent *e)
{
 // bLockDirectoryChanged = false;
}

void _tableviewer::focusInEvent(QFocusEvent *e)
{
 // bLockDirectoryChanged = true;

  EXTERN_my_mainwindow->updateGeneralActions(
   false,  false,  false,  false, 
   false,  false,  true,  false,  false,   
   false,  false,  false, 
   false,  false,  false,  false, 
   true, ""
  );


//  EXTERN_my_helpwindow->setText("Changes are immediatelly updated and stored in the database table.");

  if (e) view->setFocus();

  EXTERN_DatabaseTables->setShown(false);

  if (bDirty){
    bDirty = false;
    QMessageBox::information(this, tr("Table Structure Changed"), tr("If you would like to update the view close and reopen it, please."));  
  }

  if (e) QWidget::focusInEvent(e);
}

void _tableviewer::SQLGoto()
{
  static QString sSave = "";

  QHeaderView *m = view->horizontalHeader();
  int x = SQLGoTo->text().toInt() - 1;
  view->setFocus();

  if (x < 0){ 
    SQLGoTo->setText(sSave);
    return;
  }

  if (x + 1 > model->rowCount()){
    SQLGoTo->setText(sSave);
    return;
  }

  sSave = SQLGoTo->text();
  int nn = m->currentIndex().row();
  if (nn == -1){
    m->setCurrentIndex(m->model()->index(x, 0));    
//    nn = m->currentIndex().row();
  } else {
    m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
//    nn = m->currentIndex().row();
  }
  if (m->currentIndex().row() == x){
    view->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
//    SQLGoTo->setText(QString("%1").arg(x + 1));
  }
}

void _tableviewer::SQLFirst()
{
  QHeaderView *m = view->horizontalHeader();
  int x = 0;
  view->setFocus();
  if (x < 0) return;
  int nn = m->currentIndex().row();
  if (nn == -1){
    nn = x;
    m->setCurrentIndex(m->model()->index(x, 0));    
//    nn = m->currentIndex().row();
  } else {
    m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
//    nn = m->currentIndex().row();
  }
  if (nn == x){
    view->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
    SQLGoTo->setText(QString("%1").arg(x + 1));
  }
}

void _tableviewer::SQLBackward()
{
  QHeaderView *m = view->horizontalHeader();
  int x = m->currentIndex().row() - 1;
  view->setFocus();
  if (x < 0) return;
  int nn = m->currentIndex().row();
  if (nn == -1){
    m->setCurrentIndex(m->model()->index(x, 0));    
//    nn = m->currentIndex().row();
  } else {
    m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
//    nn = m->currentIndex().row();
  }
  if (m->currentIndex().row() == x){
    view->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
    SQLGoTo->setText(QString("%1").arg(x + 1));
  }
}

void _tableviewer::SQLForward()
{
  QHeaderView *m = view->horizontalHeader();
  int x = m->currentIndex().row() + 1;
  view->setFocus();
  if (x + 1 > model->rowCount()) return;
  int nn = m->currentIndex().row();
  if (nn == -1){
    m->setCurrentIndex(m->model()->index(x, 0));    
//    nn = m->currentIndex().row();
  } else {
    m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
//    nn = m->currentIndex().row();
  }
  view->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
  SQLGoTo->setText(QString("%1").arg(x + 1));
}

void _tableviewer::SQLLast()
{
  QHeaderView *m = view->horizontalHeader();
  int x = model->rowCount() - 1;
  view->setFocus();
  if (x < 0) return;
  int nn = m->currentIndex().row();
  if (nn == -1){
    m->setCurrentIndex(m->model()->index(x, 0));    
//    nn = m->currentIndex().row();
  } else {
    m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
  //  nn = m->currentIndex().row();
  }
  if (m->currentIndex().row() == x){
    view->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
    SQLGoTo->setText(QString("%1").arg(x + 1));
  }
}

void _tableviewer::SQLAddNew100()
{
  if (QMessageBox::question(this, tr("Add 100 New Empty Records"), tr("Would you like to add 100 new empty records?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
    bBlockTimer = true;

    for (int i = 0; i < 100; i++){
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

      QString sql = "INSERT INTO " + sTable + "(" + fields + sGlobalFields + ") VALUES (" + values + sGlobalValues + ")";      
      
      if (!rr.exec(sql)){
        QMessageBox::information(this, MYAPP, rr.lastError().text());
        bBlockTimer = false;
        return;
      }
    }
    model->select();

    SQLInfo->setText(tr(" of ") + QString("%1").arg(model->rowCount()) + tr(" record(s)"));

    {
      QHeaderView *m = view->horizontalHeader();
      int x = model->rowCount() - 1;
      view->setFocus();
      if (x < 0) return;
      int nn = m->currentIndex().row();
      if (nn == -1){
        m->setCurrentIndex(m->model()->index(x, 1));    
//        nn = m->currentIndex().row();
      } else {
        m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
//        nn = m->currentIndex().row();
      }
      if (m->currentIndex().row() == x){
        view->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
        SQLGoTo->setText(QString("%1").arg(x + 1));
      }
    }

    bBlockTimer = false;

  }
}

void _tableviewer::SQLAddNew()
{
  bBlockTimer = true;

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

  QString sql = "INSERT INTO " + sTable + "(" + fields + sGlobalFields + ") VALUES (" + values + sGlobalValues + ")";      

  if (!rr.exec(sql)){
    QMessageBox::information(this, MYAPP, rr.lastError().text());

    bBlockTimer = false;
    return;
  }
  model->select();

  SQLInfo->setText(tr(" of ") + QString("%1").arg(model->rowCount()) + tr(" record(s)"));

  {
    QHeaderView *m = view->horizontalHeader();
    int x = model->rowCount() - 1;
    view->setFocus();
    if (x < 0) return;
    int nn = m->currentIndex().row();
    if (nn == -1){
      m->setCurrentIndex(m->model()->index(x, 1));    
//      nn = m->currentIndex().row();
    } else {
      m->setCurrentIndex(m->currentIndex().sibling(x, m->currentIndex().column()));    
//      nn = m->currentIndex().row();
    }
    if (m->currentIndex().row() == x){
      view->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
      SQLGoTo->setText(QString("%1").arg(x + 1));
    }
  }

  bBlockTimer = false;
}

void _tableviewer::SQLDeleteAll()
{
  if (QMessageBox::question(this, tr("Delete All Records"), tr("Would you like to delete ALL records? WARNING! All data will be lost."), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
     QString s = "DELETE FROM " + sTable + ";";
     QSqlQuery r;
     if (!r.exec(s)){ 
       QMessageBox::information(this, MYAPP, r.lastError().text());
     } else {
       model->select();
       SQLInfo->setText(tr(" of ") + QString("%1").arg(model->rowCount()) + tr(" record(s)"));
       SQLFirst();
     }
  }
}

void _tableviewer::SQLDelete()
{
  if (QMessageBox::question(this, tr("Delete Record"), tr("Would you like to delete the current record?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
    QHeaderView *m = view->horizontalHeader();
    int n = m->currentIndex().row();
    const QModelIndex & index = m->currentIndex().sibling(n, m->currentIndex().column());

    model->removeRows(n, 1);

    if (n - 1 >= 0){
      SQLGoTo->setText(QString("%1").arg(n));
      SQLInfo->setText(tr(" of ") + QString("%1").arg(model->rowCount()) + tr(" record(s)"));

      m->setCurrentIndex(index);    
      view->scrollTo(index, QAbstractItemView::PositionAtCenter);

    } else {
      int k = model->rowCount();
      if (k > 0){
        SQLGoTo->setText(QString("%1").arg(n));
        SQLInfo->setText(tr(" of ") + QString("%1").arg(model->rowCount()) + tr(" record(s)"));
      } else {
        SQLGoTo->setText("");
        SQLInfo->setText(tr(" of ") + QString("%1").arg(model->rowCount()) + tr(" record(s)"));
      }
    }

  }
  view->setFocus();
}

TableView::TableView(_tableviewer *f) : QTableView(f)
{
  my_tableviewer = f;
}
 
void _tableviewer::timerEvent ( QTimerEvent * event )
{
  /*
  if (bSetTimerPos && !bBlockTimer){
    bSetTimerPos = false;
    
    QHeaderView *m = view->horizontalHeader();
    int x = oldEditIndex.column() + 1;
    int y = oldEditIndex.row();
    if (x >= m->count()){
      x = 1;
      y++;
    }
    m->setCurrentIndex(m->model()->index(y, x));    
  }*/

}

void TableView::currentChanged ( const QModelIndex & current, const QModelIndex & previous )
{
 // static QModelIndex oldEditIndex;  
  

  if (current.row() != previous.row()){
    if (!my_tableviewer->bBlockTimer && current.row() == -1){      

      my_tableviewer->oldEditIndex = previous;
      my_tableviewer->bSetTimerPos = true;

      //QHeaderView *m = my_tableviewer->view->horizontalHeader();
     // my_tableviewer->view->setFocus();
//      m->setCurrentIndex(m->model()->index(previous.row(), previous.column() + 1));    
      //m->setCurrentIndex(previous.sibling(previous.row(), previous.column() + 1));    
      //m->reset();
      //m->setCurrentIndex(m->model()->index(previous.row(), previous.column() + 1));    

      //my_tableviewer->SQLLast();



     // m->setCurrentIndex(m->model()->index(0, 0));    
       //my_tableviewer->SQLLast();
      
      

      //my_tableviewer->view->scrollTo(m->currentIndex(), QAbstractItemView::PositionAtCenter);
      //my_tableviewer->SQLGoTo->setText(QString("%1").arg(previous.row() + 1));
    } else {
      my_tableviewer->view->scrollTo(current, QAbstractItemView::PositionAtCenter);
      my_tableviewer->SQLGoTo->setText(QString("%1").arg(current.row() + 1));
    }
  }

 // oldEditIndex = current;
}

void TableView::focusInEvent(QFocusEvent *e)
{
  my_tableviewer->focusInEvent(0);
}
