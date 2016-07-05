
#include <QtGui>
#include <QtSql>

#include "_qbe_browser.h"

extern QSqlDatabase CurrentDatabase;
extern const QIcon &kbasicIcon(QString s);
extern QString kbasicPath(QString sPath);

_qbe_browser::_qbe_browser(QWidget *_parent, QString _sSQL, QString _sSQLREAL) : QTableView(0)
{
  parent = _parent;
  sSQL = _sSQL;
  sSQLREAL = _sSQLREAL;
  

  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle(_sSQLREAL);
  setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_QUERY.png")));

 // bool bb  = CurrentDatabase.open();
/*  QSqlQuery query("", db);
  bb = query.exec("SELECT * FROM address");
  while (query.next()){
    QMessageBox::information(this, "", query.value(0).toString());
  }
  QMessageBox::information(this, "Database Error", query.lastError().text());
*/

  
 
//  QSqlQuery *query = new QSqlQuery("", CurrentDatabase);
//  bb = query->exec(sSQL);

  //mydb = CurrentDatabase.cloneDatabase();

  model = new QSqlQueryModel();
  model->setQuery(sSQL, CurrentDatabase);
  setWindowTitle(tr("#") + QString("%1").arg(model->rowCount()) + " : " + windowTitle());

  //model->clear();
 // query->clear();

  QSqlError e = CurrentDatabase.lastError();
  if (e.type() != QSqlError::NoError){
    QMessageBox::information(this, "Database Error",  e.text());
    //if (model) delete model; model = 0;
    //query.clear();
    close();
    return;
  }

  this->setModel(model);
  //int n = 0;
  //bool b = model->query().exec();

  if (model->lastError().type() != QSqlError::NoError){
      QMessageBox::information(this, "Database Error", (model->lastError().text()));
      //query.clear();
      //if (model) delete model; model = 0;
      close();
      return;
  }
  showMaximized();
/*
  if (model->query().isSelect());
      //QMessageBox::information(this, MYAPP, (tr("Query OK.")));
  else
      QMessageBox::information(this, MYAPP, (tr("Query OK, number of affected rows: %1").arg(
                        model->query().numRowsAffected())));
*/
  
}

_qbe_browser::~_qbe_browser()
{
  //parent->activateWindow();

  if (model) delete model; model = 0;  
}

void _qbe_browser::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Escape){
    close();
    //return;
  }
  QTableView::keyPressEvent(e);
}