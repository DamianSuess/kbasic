/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) 
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#include <QObject>
#include <QtGui>
#include <QtSql>



#include "interpreter_kbasic_binding.h"

#include "interpreter.h"
#include "screen.h"


QTableView *view;

screen *myScreen;

extern bool bGlobalCalledByIDE;

QString sKBasicPath;


int MAIN_argc;
char **MAIN_argv;

     
void test_screen()
{
  int argc = 0;// char *argv[];
  QApplication a(argc, 0);

  screen h;

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


QString sQtException = "";   
bool bPrintQtException2stderr;

void myMessageOutput(QtMsgType type, const char *msg)
{
   sQtException = msg;
   if (bPrintQtException2stderr){
     switch (type) {
     case QtDebugMsg:
         fprintf(stderr, "Debug: %s\n", msg);
         break;
     case QtWarningMsg:
         fprintf(stderr, "Warning: %s\n", msg);
         break;
     case QtCriticalMsg:
         fprintf(stderr, "Critical: %s\n", msg);
         break;
     case QtFatalMsg:
         fprintf(stderr, "Fatal: %s\n", msg);
         abort();
     }
   }
}

int kbasic_runtime()
{  


  qInstallMsgHandler(myMessageOutput);
  QApplication a(MAIN_argc, MAIN_argv);

  qApp->addLibraryPath(qApp->applicationDirPath() + "/plugins");
  qApp->setApplicationName("KBasic"); // prevent DBUS warning message on some systems

  bool bSilent = false;
  bool bDebug = false;
  bool bDebugAtBeginning = false;   
  bool bCalledByIDE = false;   
  bool bPcode = false;   
 // char *acPcode = "";
  QString sPcode = "";

  QString sFirst = "";


  QStringList ls = a.arguments(); 

  bool bFirst = true;
  foreach(QString m, ls){

    if (bFirst){
      bFirst = false;
      sFirst = m;      
    }


    if (m.compare("-Silent", Qt::CaseInsensitive) == 0) bSilent = true;
    else if (m.compare("-Debug", Qt::CaseInsensitive) == 0) bDebug = true;
    else if (m.compare("-DebugAtBeginning", Qt::CaseInsensitive) == 0) bDebugAtBeginning = true;
    else if (m.compare("-CalledByIDE", Qt::CaseInsensitive) == 0) bCalledByIDE = true;

    else if (m.startsWith("-Pcode", Qt::CaseInsensitive)){
      bPcode = true;
     
      sPcode = m.mid(6);

    }
  }

  bPrintQtException2stderr = bCalledByIDE;


  bGlobalCalledByIDE = bCalledByIDE;

  if (bCalledByIDE){
    sKBasicPath = sFirst;
    bool bDebug2 = false;

    sKBasicPath = sKBasicPath.replace("\\", "/");

#ifdef WINDOWS
    bDebug2 = sKBasicPath.contains("Debug"); // HIDE
    sKBasicPath = sKBasicPath.replace("/Debug", "", Qt::CaseInsensitive); // HIDE
    sKBasicPath = sKBasicPath.replace("/Release", "", Qt::CaseInsensitive); // HIDE
#endif

    
    sKBasicPath = sKBasicPath.replace(".exe", "", Qt::CaseInsensitive);

    int n = sKBasicPath.lastIndexOf("/");
    if (n >= 0) sKBasicPath = sKBasicPath.left(n);

    if (bDebug2){
    } else {
      sKBasicPath = sKBasicPath.replace("kbrun", "");
    }

    sFirst = cachePath("runtime.pcode");
    
  } else {
    sKBasicPath = "";

    bSilent = true;
    bDebug = false;
  }

  

  pcode *myPcode = new pcode("");

  if (bPcode){
    sFirst = sPcode;

  }

re:
  QFile m (sFirst);
  if (m.open( QFile::ReadOnly)){

     // QMessageBox::information(0,"2", sFirst);  

    if (bCalledByIDE || bPcode){

  //// QMessageBox::information(0,"1111", ac);   

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
      char acKBASIC[10];
      memset(acKBASIC, 0, sizeof(acKBASIC));
       
      m.seek(nSize - 6);     
      m.read((char *) &acKBASIC, 6); 

      if (strncmp("KBASIC", acKBASIC, 6) == 0){ // pcode containted in exe

          m.seek(nSize - 1 - 6);     
          m.read((char *) &bProject, 1 - 6); 

          m.seek(nSize - 4 - 1 - 6);     
          m.read((char *) &nSize2, 4); 

          b = m.seek(nSize - nSize2 - 4 - 1 - 6);
          //if (b) // QMessageBox::information(0,"seek ok", "");     

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
    //        // QMessageBox::information(0,"7777777", "");     

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
            // QMessageBox::information(0,"", ss);           
            */
            myPcode->ba->append((t_pointer) acBuffer, i2);
//      } else {
    //    QMessageBox::information(0,"1111", ac);
      }
  } else {
    sFirst = qApp->applicationDirPath() + "/runtime.pcode";
    bPcode = true;
    m.close();
    goto re;
  }
        

  
      /*
        ss = ss.sprintf("%d", i);  
        // QMessageBox::information(0,"i", ss);          */ 
        
      myPcode->ba->resetPos();
      m.close();
    }




//    // QMessageBox::information(0,"", "0");           

    myScreen = new screen();


    interpreter *myInterpreter = new interpreter(myScreen);
    
    bool b = myInterpreter->interpret(myPcode, bSilent, bDebug, bDebugAtBeginning, bCalledByIDE);
     

    delete myInterpreter;   
    delete myPcode;

//    // QMessageBox::information(0, "bernd", "");
    delete myScreen;

//    // QMessageBox::information(0,"", "3333333"); 

    return b ? 0 : -1;;
   
  }

}



class testit : public QWidget
{
 // Q_OBJECT
public:

void paintEvent(QPaintEvent *e)
{
  for (int i = 0; i < 1000000; i++){ i = i; }
  QPainter p( this );

    QRect r = e->rect();

    for (int y = 0; y < r.bottom() + 11 + nScrollY; y += 10){
      for (int x = 0; x < r.right() + 11 + nScrollX; x += 10){
       if (y % 20 && !(x % 20)){
         p.setPen(Qt::gray);
       } else {
         p.setPen(Qt::black);
       }
       p.drawPoint(x - nScrollX, y - nScrollY);
      }
    }

}

  void timerEvent ( QTimerEvent * e)
  {
    nScrollX++;
    repaint();
  }

  int nScrollX;
  int nScrollY;

};

int main(int argc, char *argv[])
{

	MAIN_argc = argc;
	MAIN_argv = argv;

  return kbasic_runtime(); 

/*
  int nRet = 0;

  QApplication a(MAIN_argc, MAIN_argv);

  testit w;
  w.nScrollX = 0;
  w.nScrollY = 0;
  w.showMaximized();
  w.startTimer(150); 


  return qApp->exec();
*/
  //test_screen();

  //return kbasic_runtime(); 


}



