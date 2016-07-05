/*
***************************************************************************
Copyright (C) 2000-2006 KBasic Software.  All rights reserved.

main.cpp
---------------------------------------------------------------------------
READY
19.02.2004 - new header for this file (BN)
***************************************************************************



*/

/*
BUGS
files.kbasic - cannot paint on paint device... something related to screen.cpp maybe a curious qt bug
*/
#include <QObject>
#include <QtGui>
#include <QtSql>

#include "interpreter.h"
#include "screen.h"


QTableView *view;

screen *myScreen;

extern bool bGlobalCalledByIDE;

class TableViewModel : public QSqlTableModel
{

Q_OBJECT
public:
  TableViewModel()
  {
    /*
    connect(this, SIGNAL(beforeInsert(QSqlRecord &)), this, SLOT(EVENT_On2BeforeInsert(QSqlRecord &)));
    connect(this, SIGNAL(beforeUpdate(int, QSqlRecord &)), this, SLOT(EVENT_On2BeforeUpdate(int, QSqlRecord &)));
    connect(this, SIGNAL(beforeDelete(int)), this, SLOT(EVENT_On2BeforeDelete(int)));*/
  }
  /*
  QVariant headerData ( int section, Qt::Orientation orientation, int role) const 
  {
    if (role ==Qt::DisplayRole && orientation == Qt::Horizontal){
      if (fieldIndex("Label") == section){
        return QVariant("this is my label");
      }
      return QSqlTableModel::headerData(section, orientation, role);
    }
    return QSqlTableModel::headerData(section, orientation, role);
  }*/

       /* 
  QVariant data ( const QModelIndex & item, int role = Qt::DisplayRole ) const   
  {
   // item.setIndex(0);
    return QSqlTableModel::data(item, role);
  }*/

public slots:


void EVENT_On2BeforeInsert(QSqlRecord & record)
{ 
//#ifdef RUN
//  _form::setSQL2(record);
  t_boolean Cancel = false;
  EVENT_OnBeforeInsert(&Cancel); 
  if (&Cancel) return;
  //METHOD_Insert();
  //EVENT_OnAfterInsert(); 
//#endif
}

void EVENT_On2BeforeUpdate(int row, QSqlRecord & record)
{ 
//#ifdef RUN
  //_form::setSQL2(record);
  t_boolean Cancel = false;
  EVENT_OnBeforeUpdate(&Cancel); 
  if (&Cancel) return;
  //METHOD_Update();
  //EVENT_OnAfterUpdate(); 
//#endif
}

void EVENT_On2BeforeDelete(int row)
{ 
//#ifdef RUN
  //_form::setSQL2(record(row));
  t_boolean Cancel = false;
  EVENT_OnBeforeDelete(&Cancel); 
  if (&Cancel) return;
  //METHOD_Delete();
  //EVENT_OnAfterDelete(); 
//#endif
}

public:

virtual void EVENT_OnBeforeInsert(t_boolean *Cancel)
{
}

virtual void EVENT_OnAfterInsert()
{
}

virtual void EVENT_OnBeforeUpdate(t_boolean *Cancel)
{
}

virtual void EVENT_OnAfterUpdate()
{
}

virtual void EVENT_OnBeforeDelete(t_boolean *Cancel)
{
}

virtual void EVENT_OnAfterDelete()
{
}

t_boolean METHOD_First()
{
  QModelIndexList l = view->horizontalHeader()->selectionModel()->selectedColumns();
  int n = l.first().column();
  view->horizontalHeader()->selectionModel()->setCurrentIndex(index(0, n), QItemSelectionModel::NoUpdate);
  return false;
}

t_boolean METHOD_Next()
{
}

t_boolean METHOD_Previous()
{
}

t_boolean METHOD_Last()
{
}

t_boolean METHOD_GoTo(t_long l)
{
}

t_long METHOD_Len()
{ 
//#ifdef RUN
  return rowCount();
//#endif
  return 0;
}

t_long METHOD_Pos()
{ 
#ifdef RUN
//  return q.at() + 1;
#endif
  return 0;
}

t_variant METHOD_Record(QString sFieldName)
{
  return 0;//_form::rd_Record(QSqlRecord & a, sFieldName);
}

void METHOD_SetRecord(QString FieldName, t_variant Value)
{
}

t_boolean stopByQuestion()
{ 
#ifdef RUN
  /*
  //if (bDirty)
  {
    if (QMessageBox::question(this, tr("Current Record changed"), tr("Would you like to skip the changes?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
      return true;
    }
    return false;
  }*/
#endif
  return false;
}

t_boolean METHOD_IsDirty()
{ 
#ifdef RUN
#endif
  return false;
}

t_boolean METHOD_Insert()
{
}

t_boolean METHOD_Update()
{
}

t_boolean METHOD_Delete()
{
}

t_boolean METHOD_AddNew()
{
}
t_boolean METHOD_Requery()
{ 
#ifdef RUN
  if (stopByQuestion()) return false;
  select();
#endif
  return false;
}

};
 
 //#include "moc_main.cpp"


QString sKBasicPath;


int MAIN_argc;
char **MAIN_argv;

     
void test_screen()
{
  int argc = 0;// char *argv[];
  QApplication a(argc, 0);

  screen h;
//  a.setMainWidget( &h );
//  h.setCaption( "KBasic Software Atelier - Personal Edition" );

  //h.showFullScreen();

//  h.setScreen(12);
  h.activate();
  //h.test1();
  h.test2();
/*
  for (int i = 0; i < 100; i++){
    h.line(false, 11 + i, 22, false, false, 33 + i, 33 + i, true, i, false, false, false, 0);
  }*/


  a.exec();
}     



QString idePath(QString s)
{
  QString k = sKBasicPath + "/ide/" + s; 
  k.replace("kbrun", "kbide");
  return k;
}

QString cachePath(QString s)
{
  QString k = sKBasicPath + "/ide/cache/" + s; 
  k.replace("kbrun", "kbide");
  return k;
}

   
int kbasic_runtime()
{  

  //MAIN_argv[0] = "c:\\kbasic15\\examples\\projects\\test.kbasic_project\\test.exe";

  QApplication a(MAIN_argc, MAIN_argv);

 // QMessageBox::information(0,"", qApp->applicationDirPath() + "/plugins");   
  
  /*
#ifdef MAC
  qApp->addLibraryPath(qApp->applicationDirPath() + "/../PlugIns");
#endif
#ifdef WINDOWS*/
  qApp->addLibraryPath(qApp->applicationDirPath() + "/plugins");
//#endif
 


/*
   QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
     db.setHostName("localhost");
     db.setDatabaseName("test");
     db.setUserName("postgres");
     db.setPassword("test");
     bool ok = db.open();
*/

/*


bool QSqlTableModel::removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() )   
QSqlRecord QSqlTableModel::record ( int row ) const
bool QSqlTableModel::isDirty ( const QModelIndex & index ) const
virtual bool select ()

QModelIndexList QItemSelectionModel::selectedColumns ( int row = 0 ) const
QModelIndexList QItemSelectionModel::selectedRows ( int column = 0 ) const



*/
    /*
     TableViewModel model;
     model.setEditStrategy(QSqlTableModel::OnRowChange);
     model.setTable("sql");
     model.removeColumn(0); // don't show the ID

    // model.setHeaderData(0, Qt::Horizontal, ("Name"));
    // model.setHeaderData(1, Qt::Horizontal, ("Salary"));

     //model.setFilter("\"TextBox\"='Hepp'");
     model.setSort(5, Qt::AscendingOrder);
     model.select();

     

  view = new QTableView;
     view->setModel(&model);
     view->setColumnWidth(0, 50);
     QHeaderView *h = view->horizontalHeader();


    // view->setBackgroundColor(Qt::green);
     h->setMovable(true);
     view->setItemDelegate(new TableViewDelegate());


     h->moveSection(0, 3);
      view->showMaximized();
    view->setFocus();
      h->selectionModel()->setCurrentIndex(model.index(0, 1), QItemSelectionModel::NoUpdate);

      h->selectionModel()->setCurrentIndex(model.index(2, 1), QItemSelectionModel::Select);//, QItemSelectionModel::NoUpdate);
*/

  //QMessageBox::information(0,"776887", "");  
/*
  QWidget *w = new QWidget();
  w->resize(555,555);


 QLabel    *l = new QLabel(w);
 l->setText("<a href=\"http://www.kbasic.com/\">hallo</a>");
// l->setText("<html><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\"><head><title>Qt 4.2: QLabel Class Reference</title></head><body>http://www.kbasic.com/</body></html>");
 l->setTextInteractionFlags(Qt::TextBrowserInteraction);
 l->setOpenExternalLinks(true);
  l->move(100, 300);
 

  w->showMaximized();
  
 


 int nn = a.exec();

 do {
   qApp->processEvents(); // IMPORTANT: process gui events 100 msec
 } while (true);
*/

 // sKBasicPath = a.applicationDirPath();

  //sKBasicPath = "c:\\kbasic16\\examples\\projects\\test.kbasic_project\\";//a.applicationDirPath();

  char ac[1024];

  bool bSilent = false;
  bool bDebug = false;
  bool bDebugAtBeginning = false;   
  bool bCalledByIDE = false;   
  bool bPcode = false;   
  char *acPcode = "";

  int i = 1;
  for (; i < MAIN_argc; i++){
    const char *ac = MAIN_argv[i];
    if (utility::my_stricmp(ac, "-Silent") == 0) bSilent = true;
    else if (utility::my_stricmp(ac, "-Debug") == 0) bDebug = true;
    else if (utility::my_stricmp(ac, "-DebugAtBeginning") == 0) bDebugAtBeginning = true;
    else if (utility::my_stricmp(ac, "-CalledByIDE") == 0) bCalledByIDE = true;

    else if (utility::my_strnicmp(ac, "-Pcode", 6) == 0){
      bPcode = true;
      acPcode = (char *) ac + 6;
      if (acPcode == 0) acPcode = "";

    } else {
      break;
    }
  }
  /*
  bSilent = false;
  bCalledByIDE = false;
*/
  

  //sprintf(ac, "");

  //printf("!!!%d %s", MAIN_argc, ac);
  //while(true);
    

  bGlobalCalledByIDE = bCalledByIDE;

  if (bCalledByIDE){
    sKBasicPath = MAIN_argv[0];
    bool bDebug2 = false;

    sKBasicPath = sKBasicPath.replace("\\", "/");

#ifdef WINDOWS
    bDebug2 = sKBasicPath.contains("Debug");
    sKBasicPath = sKBasicPath.replace("/Debug", "", Qt::CaseInsensitive);
    sKBasicPath = sKBasicPath.replace("/Release", "", Qt::CaseInsensitive);
#endif

    
    sKBasicPath = sKBasicPath.replace(".exe", "", Qt::CaseInsensitive);

    int n = sKBasicPath.lastIndexOf("/");
    if (n >= 0) sKBasicPath = sKBasicPath.left(n);

    if (bDebug2){
    } else {
      sKBasicPath = sKBasicPath.replace("kbrun", "");
    }

    sprintf(ac, cachePath("runtime.pcode").toAscii().data());
  } else {
    sKBasicPath = "";
    sprintf(ac, "%s", MAIN_argv[0]);
   // printf(ac);

    bSilent = true;
    bDebug = false;
  }

  


  //sprintf(ac, "%s", MAIN_argv[0]); // TODO2 arg ist unter windows dosfenster ohne .exe und pfad
	
//  _infoconsole* myInfoConsole = new _infoconsole(); 

  pcode *myPcode = new pcode("");
 // myPcode->setInfoWindow(myInfoConsole);

  //sprintf(ac, "%d %d %d", (int) bSilent, (int) bDebug, (int) bDebugAtBeginning);
  //QMessageBox::information(0,"", ac);   
  if (bPcode){
    sprintf(ac, "%s", acPcode);
  }

  QFile m (ac);
  if (m.open( QFile::ReadOnly)){

    if (bCalledByIDE || bPcode){

  //QMessageBox::information(0,"1111", ac);   

      char acBuffer[10240];
      int i = 0;
      while ((i = m.read(acBuffer, 10240)) > 0){              
        myPcode->ba->append((t_pointer) acBuffer, i);
      }
      myPcode->ba->resetPos();
      m.close();

    } else {

      int nSize = m.size();
      int nSize2 = 0;
      bool bProject = false;
      bool b = false;
       
      m.seek(nSize - 1);     
      m.read((char *) &bProject, 1); 

      m.seek(nSize - 5);     
      m.read((char *) &nSize2, 4); 

      b = m.seek(nSize - nSize2 - 5);
      //if (b) QMessageBox::information(0,"seek ok", "");     

/*
            QString ss = "";    
        ss = ss.sprintf("%d", nSize);  
        QMessageBox::information(0,"nSize", ss);     

        ss = ss.sprintf("%d", nSize - nSize2 - 5);  
        QMessageBox::information(0,"nSize - nSize2 - 5", ss);     
*/
      char acBuffer[10240];
      int i = 0;
      while (nSize2 > 0 && (i = m.read(acBuffer, 10240)) > 0){        
//        QMessageBox::information(0,"7777777", "");     

        int i2 = 0;
        if (nSize2 > i){
          i2 = i;
        } else {
          i2 = nSize2;
        }
        nSize2 -= i2;
     /*
        QString ss = "";    
        ss = ss.sprintf("%d", i2);  
        QMessageBox::information(0,"", ss);           
        */
        myPcode->ba->append((t_pointer) acBuffer, i2);
        

      }
      /*
        ss = ss.sprintf("%d", i);  
        QMessageBox::information(0,"i", ss);          */ 
        
      myPcode->ba->resetPos();
      m.close();
    }




//    QMessageBox::information(0,"", "0");           

    myScreen = new screen();
//    a.setMainWidget( &myScreen );
    //myScreen.show();

    interpreter *myInterpreter = new interpreter(myScreen);
    //myInterpreter->setInfoWindow(myInfoConsole);
    //myInterpreter->setGUIRuntime(&a);
    //if (h) h->myInterpreter = myInterpreter;



    
   // quitme quitter(myInterpreter);

    //bool b = QObject::connect(&a, SIGNAL(aboutToQuit ( )), &myScreen, SLOT(aboutToQuit()));

    bool b = myInterpreter->interpret(myPcode, bSilent, bDebug, bDebugAtBeginning, bCalledByIDE);
     
    
    //while(true){  }
//    a.exit_loop();
    //a.exit_loop();

    //if (h) delete h;

    delete myInterpreter;   
    delete myPcode;

//    QMessageBox::information(0, "bernd", "");
    delete myScreen;
       //qApp->processEvents();
//    QMessageBox::information(0,"", "3333333"); 

    return b ? 0 : -1;;
   // delete myInfoConsole;
  }

}

// main routine: calls the different parts of the kbasic compiler
//void kbasic(char *acDir, char *acFilename)




int main(int argc, char *argv[])
{

	MAIN_argc = argc;
	MAIN_argv = argv;



int nRet = 0;


  //test_screen();

  return kbasic_runtime(); // !!! RUNTIME !!! ACTIVATE
//  kbasic_runtime(); // !!! RUNTIME !!! ACTIVATE

}



