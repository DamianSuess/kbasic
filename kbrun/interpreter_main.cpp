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


#include <QtSql>

#include "../kbshared/_err.h"
#include "../kbshared/_forms.h"

#include "interpreter.h"

#include "interpreter_kbasic_binding.h"
#include "../kbshared/_sounds.h"

#include <phonon/phononnamespace.h>
#include <phonon/audiooutput.h>


#include "../kbshared/_log.h"
extern _log *my_log;

void MYLOG(QString s)
{
  my_log->METHOD_Print(s);
}

t_pointer myGcLock2 = 0;

QMap<t_integer, QDataStream *> qdatastream;
QMap<QDataStream *, QByteArray *>qdatastream_bytearray;

extern QString sQtException;   
extern QString cachePath(QString s);
extern QString idePath(QString s);

bool bProject = false;

bool bBlock_qApp_processEvents;

_sounds2 *EXTERN_my_sounds;

QMap<QString, t_sound2>sounds_map;
QMap<Phonon::MediaObject*, Phonon::AudioOutput*>sounds_playing;
QList<Phonon::MediaObject*>sounds_to_be_deleted;
QMap<Phonon::MediaObject*, Phonon::MediaSource*>sounds_playing2;
QMap<Phonon::MediaObject*, Phonon::Path>sounds_playing3;



QString ProgressDialog_Caption;
QString ProgressDialog_CancelCaption;
t_integer ProgressDialog_Value;
t_integer ProgressDialog_Minimum;
t_integer ProgressDialog_Maximum;
t_integer ProgressDialog_Wait;

QString sCurrentLanguage;
QString sCurrentCountry;

extern interpreter* EXTERN_myInterpreter;
extern int nCurrentFormId;

class _toolbar;
extern _toolbar *EXTERN_my_toolbar;

QColor qcolor;
QFont qfont;
QProgressDialog *qprogressdialog = 0;
QMessageBox *qmessagebox = 0;



QLocale *qlocale;

QDir dir;
QFile qfile;

extern QMap<int,QString>forms;
extern QMap<QString,int>forms2;

extern QMap<QString,int>menubaritems;
extern QMap<QString,int>toolbaritems;

bool bGlobalCalledByIDE = false;

QTextEdit *log_te = 0;

QString sProjectName = "KBasic";
QString sLogin = "";
QString sProjectType;

QString sTranslation;
QString sSQL;
QString sMENU;

_log *my_log;

bool menuRecords = false;
bool menuWindow = false;
bool menuHelp = false;

bool bOpenonrun_forms;

int kbEventId;
memory_variable2 *kbEventScope;

extern QPainter *EXTERN_myQPainter;

bool bNotApplicationRun;

QString dbdriver = "";

extern QString highlightSQL(QString);

extern int kbFormId;
extern int kbMenuBarId;
extern int kbToolBarId;

_statusbar *EXTERN_my_statusbar;

QSettings *settings;

QMap<QString, QSqlDatabase> databases;
QMap<QString, QSqlQuery *> records;
QMap<QString, QString> records_database;
QMap<QString, QString> records_table;

QSqlDatabase CurrentDatabase;

QSqlDatabase db;


class kb_form;
kb_form *FORMPARENT;

bool _inputdialog_ok;

interpreter **EXTERN_myInterpreter2;

// ****************************
// * bool interpret()
// *
// * description:
// * entry point for this module
// * the given pseudo-codes will be processed
// *
// * interpreter_parameter:
// * none
// *
// * return:
// * true, if no error occured
// * false, if something went wrong
// ****************************

bool interpreter::interpret(pcode *p, bool _bSilent, bool _bDebug, bool _bDebugAtBeginning, bool _bCalledByIDE)
{
  qApp->setApplicationName("KBasic");

#ifdef MAC
  qApp->setAttribute(Qt::AA_DontShowIconsInMenus); // HIDE
#endif

  qlocale = &QLocale::system();

  EXTERN_myInterpreter2 = 0;
  EXTERN_my_toolbar = 0;
  EXTERN_my_statusbar = 0;

  EXTERN_my_sounds = new _sounds2();

  ProgressDialog_Caption = ""; 
  ProgressDialog_CancelCaption = "";
  ProgressDialog_Value = 0;
  ProgressDialog_Minimum = 0;
  ProgressDialog_Maximum = 100;
  ProgressDialog_Wait = 4000;
  
  _inputdialog_ok = false;

  settings = 0;

  sCurrentLanguage = "";
  sCurrentCountry = "";
 
  nCurrentLine = 0;
  acCurrentFile = "";
  
  highlightSQL(""); // set up highlighting

  dbdriver = "";

  bOpenonrun_forms = true;

  bNotApplicationRun = true;

  breakpoints.clear();

  //bDbOpen = false;

  kbEventId = 0;
  kbEventScope = 0;


  bCalledByIDE = _bCalledByIDE;
  bSilent = _bSilent;
  bDebug = _bDebug | _bDebugAtBeginning; 

  if (bDebug){
    my_stdin.setFileName(cachePath("runtime.interpreter"));  
    debuginfo.setFileName(cachePath("ide.debuginfo"));  
  }

  kbFormId = 0;

  sSQL = "";
  sTranslation = "";

  bStepIn = _bDebugAtBeginning;
  bStepOut = false;
  bStepOver = false;
  bStepToCursor = false;

  sStepToCursorFile = "";
  nStepToCursorLine = 0;

#ifdef HAS_CONSOLE
  if (!bSilent){
    CONSOLE print("\nKBasic Interpreter - highly optimized virtual machine for Windows(R), Linux(R) and Mac OS X(R)\n(C) Copyright KBasic Software 2000 - 2006\n");
    CONSOLE header("\n-- interpret --\n\n");
  }    
#endif

//  bDebugStepModeOn = true;
  bDebugStepModeOn = false;

  bRunPcode = true;
  bBreakpointAtPcode = false;
  bNoError = true; // runtime error occured
  
  bCatchBuiltinException = false;
  nExceptionCountParamToRemove = 0;
  sRuntimeErrorTxt = "";
  nRuntimeErrorPos = -1;
  nRuntimeErrorPos1 = -1;
  nRuntimeErrorPos2 = -1;
  nRuntimeErrorNo = -1;
  nRuntimeErrorLine = -1;
  sRuntimeErrorFile = "";
  nRuntimeErrorLine2 = -1;
  sRuntimeErrorFile2 = "";

  EXTERN_myQPainter = 0;

  my_log = new _log(0);


//  nOptionBase = 0; // arrays start with 1 if not explictly declared or OPTION BASE
  bOptionRange = false; // under/overflow range check on/off
  bOptionComparyBinary = true; // compare binary, binary is default

  array_offset = 0;
  movType_offset = 0;

  local_counter = 0;
  
  bPcodePrint_SilentMode = bSilentMode = false; // interpreter's debug output on/off

  myGc = new memory_gc(this);
  myType = new memory_type();
  myEnum = new memory_enum();
//  myStructure = new memory_structure();
  mySub = new memory_sub();
  myClass = new memory_class2();

  // gleiche typen mssen jeweils parser und interpreter bekannt sein

  // register builtin types
  registerBuiltinTypes();

  // qt_binding
//  binding_registerType_qt_binding();

  // kbasic_binding
  binding_registerType_kbasic_binding();

  bPushPointerPointer = false;

  myParser = new parser();

  myStack->resetStack();
  myData->resetStack();

  nMyDataPos = myData->getPos();

  stringliterals = new memory_stringliteral();


  globalVars = new memory_variable2();
  meVars = 0;
  OldmeVars = 0;
  bSetMe = false;

  
  nBaseOfArray = 0; // default array start = 0 like vb6: 0..10 --> 11 entries
  
  forms.clear();
  openonrun_forms.clear();
  projectfiles.clear();
  projectfiles2.clear();
  myLocalFrame.clear();
  array_offset2.clear();
  myArray2.clear();

  // initial frame = main frame
  local_frame_ *lf = new local_frame_();
  lf->bGlobal = true;
	memcpy(lf->acName, "Global", 6);
	lf->acName[6] = '\0';
  lf->subPcodeOffset = 0;
  lf->onErrorGotoPos = 0;
  myLocalFrame.append(lf);

  err2 = 0; // for OBJECT for raising erros; old style

  consts = new memory_const2;
  estatics = new memory_variable2;

  // new classes static, variable, estatic, const
  
  myPcode = p;
  myPcode->resetPos();
  myArray = new t_array();

  memory_variable2::resetIdCounter(); // important
  memory_const::resetIdCounter(); // important


  fKBASIC();
  if (myPcode->peekPCode() == pcode__VER){
    fVER();


    interpret();

    if (projectfiles.size()){ // deinit QMainWindow environment
      _forms::deinit();
    }    

    // * ON TIMER GOSUB
    bOnTimer = false;
    nOnTimerPos = -1;
    nOnTimerIntervall = 0;
    if (my_ontimer->isActive()) my_ontimer->stop();
    // *

    myGc->deleteAll(); // gc
    myGc->deleteAll2(); // gc

    // *** alle variable löschen, alle offenen sub calls und global scope

    delete globalVars; globalVars = 0;

    local_frame_ *lf;
    
    lf = myLocalFrame.last();

    if (lf){

      do {
        memory_variable2 *v = lf->localVars;

        if (v && v->first()){
          do {
            if (memory_type::isClass(v->type(v->getId()))){
              myGc->dec((memory_variable2 *) v->getObject(v->getId(), 0)); 

            }
          } while (v->next());

          delete v;
        }

        myLocalFrame.removeLast();
        delete lf;

        if (myLocalFrame.count()) lf = myLocalFrame.last(); else lf = 0;
      } while (lf);


    }
    // *** 


  } // } else return pcodeError("corrupted pcode start block");


  if (qprogressdialog) delete qprogressdialog;
  //if (qmessagebox) delete qmessagebox;  

  delete stringliterals;
  delete consts;
  delete estatics;
  delete myArray;
  delete myType;
  delete myEnum;
//  delete myStructure;
  delete mySub;
  delete myClass;

  delete myGc;
  delete myParser;

  if (my_stdin.isOpen()) my_stdin.close();
  if (debuginfo.isOpen()) debuginfo.close();

  if (my_log){ 

    QFile f(idePath("log.html"));
    if (!f.open(QIODevice::WriteOnly)){
      //QMessageBox::information(0, "KBasic", QString("Could not write to %1").arg(idePath("log.html")));
      //  errormessage
    } else {
      QTextStream t(&f);    
      t.setCodec("UTF-8");
      t.setAutoDetectUnicode(true);
      t.setGenerateByteOrderMark(true);

      t << _log::toHtml();
      f.close();
      
    }

    delete my_log; my_log = 0; 
  }

  if (!bGlobalCalledByIDE /*&& bDbOpen*/ && db.isOpen()){
    db.close();
   // delete db;
  }

  extern QMap<QString, QSqlDatabase> databases;

  foreach(QSqlDatabase d, databases){
    d.close();
    //delete d;
  }
  databases.clear();

  foreach(QDataStream *ds, qdatastream){
    delete ds;
  }
  qdatastream.clear();
  


  delete EXTERN_my_sounds;
  if (settings) delete settings;

  //delete myErr; // TODO2 delete myErr in interpreter.h

//  myPcode->dumpPcode();

#ifdef HAS_CONSOLE
  if (!bSilent) CONSOLE print("\n");
#endif

  return bNoError;
}

void interpreter::stop_interpret()
{
  bRunPcode = false;
  bBreakpointAtPcode = false;
  qApp->exit();

}

void interpreter::interrupt_interpret()
{
  bBreakpointAtPcode = true;


}

void interpreter::continue_interpret(bool _bStepIn)
{
  bStepIn = _bStepIn;
  bBreakpointAtPcode = false;

  QWidget *w = qApp->activeWindow();
  if (w){
    w->activateWindow();
    w->setFocus();
  }

  
}

bool interpreter::interpret(bool bEvent)
{ 
  if (!bEvent){
    a = new t_array();

  }

  bParentCalled = false;
 
  bool b = interpret2(bEvent);
  bRunPcode = false;
  qApp->exit();

  if (!bEvent){

    delete a;
  }

  return b;
}

void interpreter::interpretContinue()
{
  bStepIn = false;
  bStepOut = false;
  bStepOver = false;
  bStepToCursor = false;

  continue_interpret();
  
}

void interpreter::interpretStepIn()
{
  bStepIn = true;
  bStepOut = false;
  bStepOver = false;
  bStepToCursor = false;

  continue_interpret(true);

}

void interpreter::interpretStepOut()
{
  if (myLocalFrame.count() == 1){
    bStepIn = false;
    bStepOut = false;
    bStepOver = false;
    bStepToCursor = false;
  } else {
    bStepIn = false;
    bStepOut = true;
    bStepOver = false;
    bStepToCursor = false;

    nStepToCursorLine = myLocalFrame.count() - 1;
  }
  continue_interpret();

}

void interpreter::interpretStepOver(QString file, t_integer line)
{
  bStepIn = false;
  bStepOut = false;
  bStepOver = true;
  bStepToCursor = false;

  sStepToCursorFile = file;
  nStepToCursorLine = myLocalFrame.count();

  continue_interpret();

}

void interpreter::interpretRunToCursor(QString file, t_integer line)
{
  bStepIn = false;
  bStepOut = false;
  bStepOver = false;
  bStepToCursor = true;

  sStepToCursorFile = file;
  nStepToCursorLine = line;

  continue_interpret();

}
    
void interpreter::interpretAddBreakpoint(QString file, t_integer line)
{
  file = file + QString("%1").arg(line);
  breakpoints.insert(file, true);

}

void interpreter::interpretRemoveBreakpoint(QString file, t_integer line)
{
  file = file + QString("%1").arg(line);
  breakpoints.remove(file);
}

void interpreter::interpretUpdateBreakpoint(QString file, QStringList Lines)
{

re:
  QMapIterator<QString, bool> i(breakpoints);
  while (i.hasNext()) {
     i.next();
     if (i.value()){
        if (i.key().startsWith(file, Qt::CaseInsensitive)){
          breakpoints.remove(i.key());
          goto re;
        }
     }
  }

  foreach(QString ss, Lines){
    interpretAddBreakpoint(file, ss.toInt());
  }

}

extern _form *EXTERN_my_form_test;

bool interpreter::interpret2(bool bEvent, bool bConstructor, int nInterpretLen)
{
  int nJMP = 0;
  t_pcode cPcode;// = 0;
  t_builtin nBuiltin;// = 0;

  int nSubCall = 1;
  int n = 0;
  bool bReturn = false;


	int nPos = myPcode->getPos();


      
//QMessageBox::information(0,"", bCalledByIDE ? "!!!" : "");   
/*
  if (bEvent){
    bEvent = bEvent;
  }*/

  do {

    if (bCalledByIDE){
      if (n % 1000 == 0 && QFile::exists(idePath("stopinterpret"))){ // QFile::exists bug, dieser Codeblock frisst 4 bytes RAM
        myScreen->aboutToQuit();
        QFile::remove(idePath("stopinterpret"));
      }

      while(bBreakpointAtPcode){
        if (n % 1000 == 0){    
          if (QFile::exists(idePath("stopinterpret"))){

            //QMessageBox::information(0, "stopinterpret", "");

            myScreen->aboutToQuit();
            QFile::remove(idePath("stopinterpret"));
          }

          my_stdin.open(QFile::ReadOnly);
          if (my_stdin.isOpen()){
            QString s = my_stdin.readAll();
            my_stdin.close();
            if (!s.isEmpty()){
              performStdin(s);           
              QFile::remove(my_stdin.fileName());
            }
          }
        
          qApp->processEvents();
        }
        n++;
      }
    }

    if (interpretPcode() == false) break;

    if (nInterpretLen >= 0){
      if (myPcode->getPos() >= nPos + nInterpretLen) break;
    }

    int uu = myPcode->getPos();
    cPcode = myPcode->peekPCode();

    switch(cPcode){
      case pcode__CALL:
        fCALL(); 
        if (bEvent){
          nSubCall++;
        }
        break;
      case pcode__RETURN:
        if (bEvent){
          fRETURN(); // for ON TIMER GOSUB
          return true;
        } else {
          fRETURN();
        }
        break;
      case pcode__CALL_RETURN:
        {
  #ifdef HAS_CONSOLE
    register int nPos = myPcode->getPos();
  #endif


	        t_pcode call_return_;
	        t_boolean bMethod;


	        myPcode->rd_CALL_RETURN(&call_return_, &bMethod);

          
          int m = 0;
          if (myStack->getPos() > 0) m = myStack->peekPCode();
          
          if (memory_type::isBinding(m)){

            void *p;
            myStack->popPCode();
            bool b44 = myStack->popBoolean();
            bool memory_variable2 = myStack->popBoolean();
            p = myStack->popPointer(); 

            if (p){
           
              myGcLock2 = p;
              myGc->dec2(p); // gc
            }

            myStack->pushPointer(m, p, b44, memory_variable2);
          }

          if (bMethod && nInterpretLen > 0){            
            goto re; // methods returns
          }

          t_integer nValue; 
          nValue = myLocalFrame.last()->return_pos;

  #ifdef HAS_CONSOLE
		  if (!bSilent) info(nPos, pcode__CALL_RETURN, nValue);
  #endif    

          exitLocal();
  		   
			    myPcode->setPos(nValue);		    

          if (bEvent){
            nSubCall--;
            if (nSubCall == 0){ 
              bReturn = true;
              goto re;
            }
          }
        }
        break;
      case pcode__PUSH_IDREF: fPUSH_IDREF(pcode__PUSH_IDREF); break;
      case pcode__PUSH_IDPOINTER: fPUSH_IDPOINTER(pcode__PUSH_IDPOINTER); break;
      case pcode__CLASSMETHOD: callMethod(bConstructor); break;
      case pcode__CLASSPROPERTYGET: callPropertyGet(); break;
      case pcode__CLASSPROPERTYSET: callPropertySet(); break;

      default:
         (this->*lpFunc[cPcode])();

    }
 /*
QString q;
  
    if (EXTERN_my_form_test)q = EXTERN_my_form_test->GETPROPERTY_Flag();

    if (EXTERN_my_form_test && !q.isEmpty()){
      q = q;
    }

    if (EXTERN_my_form_test && q.isEmpty()){
      q = q;
    }
*/
    if (bProject == false && n % 100 == 0 && EXTERN_myQPainter == 0 && bBlock_qApp_processEvents == false){
      qApp->processEvents();; // IMPORTANT: process gui events 100 msec
    }
    if (n && n % 2000 == 0){
      myGc->deleteOld(); // IMPORTANT: process gc
      myGc->deleteOld2(); // IMPORTANT: process gc
    }
    n++;

    

  } while (bNoError && bRunPcode && ((bNotApplicationRun || bEvent || nInterpretLen) && cPcode != pcode__END) && cPcode != pcode__STOP && cPcode != pcode__SYSTEM); 

  switch(cPcode){
    case pcode__END:
    case pcode__STOP:
    case pcode__SYSTEM:
      bRunPcode = false;
      qApp->exit();
      break;
  }


re:
  return bReturn;
}

void interpreter::fTRANSLATION()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode nop;
  t_cstring s;
  myPcode->rd_TRANSLATION(&nop, &s);
  {
#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__TRANSLATION);
#endif
    sTranslation = s;

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__NOP), " missing"));

}

bool bDbsettablesforruntime = false;
QString dbtables = "";

void interpreter::fSQL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode nop;
  t_cstring s;
  myPcode->rd_SQL(&nop, &s);
  {
#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__SQL);
#endif
    // QMessageBox::information(0, "", s);

    sSQL = s;

    QString dbhost = "";
    QString dbname = "";
    QString dbuser = "";
    QString dbuserpassword = "";
    QString dbconnectoptions = "";
    QString dbport = "";
    QString dbsettablesforruntime = "";

    QStringList l = sSQL.split(";");
    QString s = "";
    int i = 0;

    foreach(s, l){
      switch(i++){
        case 0: dbdriver = s;  break;
        case 1: dbhost = s;  break;
        case 2: dbname = s;  break;
        case 3: dbuser = s;  break;
        case 4: dbuserpassword = s;  break;
        case 5: dbconnectoptions = s;  break;
        case 6: dbport = s;  break;
        case 7: dbsettablesforruntime = s;  break;
        case 8: dbtables = s;  break;
      }
    }    

    if (!dbdriver.isEmpty()){

      db = QSqlDatabase::addDatabase(dbdriver);
      db.setHostName(dbhost);
      db.setDatabaseName(dbname);
      db.setUserName(dbuser);
      db.setPassword(dbuserpassword);
      if (!dbport.isEmpty()) db.setPort(dbport.toInt());
      db.setConnectOptions(dbconnectoptions);
      if (db.open()){       
        //bDbOpen = true;
        CurrentDatabase = db;
        databases[dbname] = CurrentDatabase;
      } else {
        //bDbOpen = false;
        QSqlError e = db.lastError();
        QMessageBox::information(0, "Error While Connecting To Database",  e.text());  
      }

      // create all non-existing tables automatically
      if (dbsettablesforruntime == "Yes"){
        bDbsettablesforruntime = true;
      }
    }


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__NOP), " missing"));

}

void interpreter::fMENU()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif

  t_pcode nop;
  t_cstring s;
  myPcode->rd_MENU(&nop, &s);
  {
#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__MENU);
#endif

    sMENU = s;

    menuRecords = false;
    menuWindow = false;
    menuHelp = false;

    QStringList l = sMENU.split(";");
    QString s = "";
    int i = 0;

    foreach(s, l){
      switch(i++){
        case 0: menuRecords = s == "Yes";  break;
        case 1: menuWindow = s == "Yes";  break;
        case 2: menuHelp = s == "Yes";  break;
      }
    }    

  }

}

void interpreter::fOPTION_KBASIC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode nop;
  myPcode->rd_OPTION_KBASIC(&nop);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__OPTION_KBASIC);
#endif
    if (projectfiles.size()){ // init QMainWindow environment
      _forms::init();
    }


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__NOP), " missing"));

}

void interpreter::fNOP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode nop;
  myPcode->rd_NOP(&nop);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__NOP);
#endif


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__NOP), " missing"));

}

void interpreter::fMOV_ENUM()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer identifier; int nElement;

  myPcode->rd_MOV_ENUM(&c, &identifier, &nElement);
  {

    const char *ac;

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(c));
      CONSOLE pcodePrint(identifier);
      CONSOLE pcodePrint(". ");
      CONSOLE pcodePrint(nElement);

      ac = findFieldInEnum(identifier, nElement);
    }   
#endif




    {
        t_integer integer_;// = 0;
  
          integer_ = popStackInteger(); 
          myEnum->setInteger(identifier, nElement, integer_);
#ifdef HAS_CONSOLE
          if (!bSilent) sprintf(acStringOutputBuffer, "%s = %d", ac, integer_);
#endif
         
      
    }
#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrint(acStringOutputBuffer);
      CONSOLE pcodePrintCR();
    }
#endif

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__MOV_ENUM), " missing"));

}

void interpreter::fMOV_CONST(){ return fMOV(pcode__MOV_CONST); }
void interpreter::fMOV_TYPE(){  return fMOV(pcode__MOV_TYPE); }

void interpreter::fMOV_BOOLEAN(){ return fMOV(pcode__MOV_BOOLEAN); }

void interpreter::fMOV_QSTRING(){  return fMOV(pcode__MOV_QSTRING); }
void interpreter::fMOV_LQSTRING(){ return fMOV(pcode__MOV_LQSTRING); }
void interpreter::fMOV_RQSTRING(){ return fMOV(pcode__MOV_RQSTRING); }

void interpreter::fMOV_CSTRING(){  return fMOV(pcode__MOV_CSTRING); }
void interpreter::fMOV_LCSTRING(){ return fMOV(pcode__MOV_LCSTRING); }
void interpreter::fMOV_RCSTRING(){ return fMOV(pcode__MOV_RCSTRING); }

void interpreter::fMOV_SINGLE(){  return fMOV(pcode__MOV_SINGLE); }
void interpreter::fMOV_DOUBLE(){  return fMOV(pcode__MOV_DOUBLE); }

void interpreter::fMOV_BYTE(){  return fMOV(pcode__MOV_BYTE); }
void interpreter::fMOV_SHORT(){ return fMOV(pcode__MOV_SHORT); }
void interpreter::fMOV_INTEGER(){ return fMOV(pcode__MOV_INTEGER); }
void interpreter::fMOV_LONG(){  return fMOV(pcode__MOV_LONG); }


//void interpreter::fMOV_VARIANT(){ return fMOV(pcode__MOV_VARIANT); }
void interpreter::fMOV_DATE(){  return fMOV(pcode__MOV_DATE); }
void interpreter::fMOV_CURRENCY(){  return fMOV(pcode__MOV_CURRENCY); }

void interpreter::fMOV_IDREF(){ return fMOV(pcode__MOV_IDREF); }
void interpreter::fMOV_IDREFVAL(){  return fMOV(pcode__MOV_IDREFVAL); }


void interpreter::fMOV_BOOLEAN(int nID, t_scope scope){ return fMOV(pcode__MOV_BOOLEAN, nID, scope); }

void interpreter::fMOV_QSTRING(int nID, t_scope scope, QByteArray *ba, int nBinaryPos){  return fMOV(pcode__MOV_QSTRING, nID, scope, ba, nBinaryPos); }

void interpreter::fMOV_QSTRING(int nID, t_scope scope){  return fMOV(pcode__MOV_QSTRING, nID, scope); }
void interpreter::fMOV_CSTRING(int nID, t_scope scope){  return fMOV(pcode__MOV_CSTRING, nID, scope); }

void interpreter::fMOV_SINGLE(int nID, t_scope scope){  return fMOV(pcode__MOV_SINGLE, nID, scope); }
void interpreter::fMOV_DOUBLE(int nID, t_scope scope){  return fMOV(pcode__MOV_DOUBLE, nID, scope); }

void interpreter::fMOV_BYTE(int nID, t_scope scope){  return fMOV(pcode__MOV_BYTE, nID, scope); }
void interpreter::fMOV_SHORT(int nID, t_scope scope){ return fMOV(pcode__MOV_SHORT, nID, scope); }
void interpreter::fMOV_INTEGER(int nID, t_scope scope){ return fMOV(pcode__MOV_INTEGER, nID, scope); }
void interpreter::fMOV_LONG(int nID, t_scope scope){  return fMOV(pcode__MOV_LONG, nID, scope); }

void interpreter::fMOV_CURRENCY(int nID, t_scope scope){  return fMOV(pcode__MOV_CURRENCY, nID, scope); }
void interpreter::fMOV_DATE(int nID, t_scope scope){  return fMOV(pcode__MOV_DATE, nID, scope); }
   
void interpreter::fBUILTIN()
{
  register int nBuiltin = myPcode->peekInteger(myPcode->getPos() + sizeof(t_pcode));

  (this->*lpFunc[nBuiltin])();
}

void interpreter::fARRAY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode array_; t_integer indexes_count; t_integer type; t_integer identifier; t_scope scope; t_integer elementid; t_boolean bAssignment; t_boolean bTo;

  myPcode->rd_ARRAY(&array_, &indexes_count, &type, &identifier, &scope, &elementid, &bAssignment, &bTo);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__ARRAY));
    }
#endif


    a->count = indexes_count;
    a->type = type;

    for (int i = indexes_count - 1; i >= 0; i--){

      int nFrom;
      nFrom = 0;

      int nTo;
      nTo = popStackInteger();

      if (bTo){
        nFrom = nTo;
      }

      a->idxTo[i] = nFrom;
      a->idx[i] = nTo;
     
      //  check auf obergrenze muss > untergrenze und > 0 sein
  
     if (bTo && nTo < nFrom && nTo != 0) runtimeError( "array error: UBound < LBound" ); 

    }

    
#ifdef HAS_CONSOLE
    if (!bSilent){
      if (bAssignment){
        CONSOLE pcodePrint("Assignment ");
      }
      if (indexes_count > 1){
        CONSOLE pcodePrint(indexes_count);
      }
      CONSOLE pcodePrintCR();
    }
#endif

    int offset;
    offset = 0;
#ifdef HAS_CONSOLE
    const char *acModule, *acSub, *acVar = "";
#endif
    if (a->count > 0){

#ifdef HAS_CONSOLE
      
      if (!bSilent){
        acModule = ""; acSub = ""; acVar = "";
      }
#endif
      t_array *ab;
      ab = 0;

      if (elementid == 0 && getVar(scope) != NULL){
#ifdef HAS_CONSOLE
        if (!bSilent){
          findVars(identifier, &acModule, &acSub, &acVar);
        }
#endif
        ab = getVar(scope)->getArray(identifier); // array definition from DIM
      } else {
        ab = myType->getArray(identifier, elementid); // array definition from user defined type
      }

      if (ab == 0){ 
        if (elementid - 1 > 0){
          offset += myType->getOffset(identifier, elementid - 1);

          ab = myType->getArray(identifier, elementid - 1);
          offset += myType->getElementSize(identifier, elementid - 1) * ab->typeSizeMulitplierOfArray();


        }
      } else {
        if (elementid - 1 > 0){
          offset += myType->getOffset(identifier, elementid);
       }
        int nSize;
        nSize = myType->getSize(type); // 
       
        int n;
        n = 0;

        if (t_array::getOffset(&n, a, ab, nSize) == false){ 
#ifdef HAS_CONSOLE
          runtimeError( utility::con(acVar, " (array) index out of bounds"), 99); 
#else
          runtimeError("(array) index out of bounds", 99); 
#endif
        }
        offset += n;

      }
   
    } else { // the a inside ).a.isbn(...
      offset += myType->getOffset(identifier, elementid);
    }

    // for MOV
    if (bAssignment){
      array_offset += offset;
      return;

    // for PUSHID
    } else {
      if (elementid == 0 || array_offset2.isEmpty()){ // new array part
        array_offset2.append(0);
      }
      (array_offset2.last()) += offset;
      movType_offset = (array_offset2.last());
      return ;
    }
    
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ARRAY), " missing"));

  
}


// 1 TO 10
void interpreter::fREGISTER_ARRAY()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode register_array_; t_integer indexes_count; t_integer type; t_integer identifier; t_scope scope; t_boolean bTo99; t_integer nBaseOfArray; 

  myPcode->rd_REGISTER_ARRAY(&register_array_, &indexes_count, &type, &identifier, &scope, &bTo99, &nBaseOfArray);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__REGISTER_ARRAY));
    }
#endif

    t_array *a;
    a = new t_array();

    a->count = indexes_count;
    a->type = type;

    for (int i = indexes_count - 1; i >= 0; i--){

      int nFrom;
      nFrom = nBaseOfArray;

      bool bToNew;
      bToNew = popStackBoolean();

      int nTo;
      nTo = popStackInteger();

      if (bToNew){
        nFrom = popStackInteger();        
      }

      a->idx[i] = nFrom;
      a->idxTo[i] = nTo;

    }

    myArray2.append(a);

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrint(" ");
      CONSOLE pcodePrint(indexes_count);
      CONSOLE pcodePrintCR();
    }
#endif

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__REGISTER_ARRAY), " missing"));


}

void interpreter::fTYPE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode type; t_integer identifier; t_integer element_count;
  
  myPcode->rd_TYPE(&type, &identifier, &element_count);
  {

#ifdef HAS_CONSOLE    
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__TYPE));
      CONSOLE pcodePrint(identifier);
      CONSOLE pcodePrintVar(findTypes(identifier));

      CONSOLE pcodePrintCR();
    }    
#endif

    int nId;
    nId = myType->addType("", utility::toString(identifier), 0, identifier); // "type-no. "

    t_pcode type_element2; t_integer identifier2; t_integer type2; t_array a; t_integer lstring_size;

    for (int i = 0; i < element_count; i++){

#ifdef HAS_CONSOLE
      if (!bSilent){
        CONSOLE pcodePrintSep("");
        CONSOLE pcodePrintPos(myPcode->getPos());
      }
#endif

      myPcode->rd_TYPE_ELEMENT(&type_element2, &identifier2, &type2, &a, &lstring_size);
      {

#ifdef HAS_CONSOLE
        if (!bSilent){
          CONSOLE pcodePrintOpc(pcode::pcode_(pcode__TYPE_ELEMENT));
          CONSOLE pcodePrint(identifier2);
          CONSOLE pcodePrintVar(findFieldInType(identifier, i + 1));
        
          if (a.count > 0){
            CONSOLE pcodePrint("( ");

            for (int i = 0; i < a.count; i++){
              CONSOLE pcodePrint(a.idx[i]);
              CONSOLE pcodePrint("TO ");
              CONSOLE pcodePrint(a.idxTo[i]);
            }

            CONSOLE pcodePrint(")");
          }

          CONSOLE pcodePrint("AS");
          CONSOLE pcodePrint(findTypes(type2));

          CONSOLE pcodePrintCR();
       }
#endif

       int nSize;
       nSize = 0;
       
       if (type2 == pcode__LQSTRING || type2 == pcode__LCSTRING){
         nSize = lstring_size;
       } else {
         nSize = myType->getSize(type2); 
       }

        bool b;
        b = myType->addElement(nId, utility::toString(i + 1), type2 > MAX_SKALAR_TYPE_ID ? utility::toString2(type2): pcode::pcode_(type2), nSize, &a, type2);

      } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TYPE_ELEMENT), " missing"));

    }


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TYPE), " missing"));
}

void interpreter::fENUM()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer identifier; t_integer element_count;
  
  myPcode->rd_ENUM(&c, &identifier, &element_count);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(myPcode->getPos());
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__ENUM));
      CONSOLE pcodePrint(identifier);
      CONSOLE pcodePrint(findTypes(identifier));

      CONSOLE pcodePrintCR();
    }
#endif
    

    int nId;
    nId = myEnum->addEnum("", utility::toString(identifier), 0, identifier); // "type-no. "

    return;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ENUM), " missing"));
}

void interpreter::fENUM_ELEMENT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif


  

  t_pcode c; t_integer identifier; t_integer element_id; t_integer type2;

  myPcode->rd_ENUM_ELEMENT(&c, &identifier, &element_id, &type2);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(myPcode->getPos());
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__ENUM_ELEMENT));
      CONSOLE pcodePrint(identifier);
      CONSOLE pcodePrint(findTypes(identifier));
      CONSOLE pcodePrint(". ");
      CONSOLE pcodePrint(element_id);
      CONSOLE pcodePrint(findFieldInEnum(identifier, element_id));

      CONSOLE pcodePrint("AS");
      CONSOLE pcodePrint(findTypes(type2));

      CONSOLE pcodePrintCR();
    }    
#endif

    int nEnums;
    nEnums = myEnum->addElement(identifier, utility::toString(element_id + 1), pcode::pcode_(type2), 0, 0, 0);
    if (nEnums == -1){ internalError(utility::con(findFieldInEnum(identifier, element_id), " (enum field) could not be declared") ); return; }

    return;

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ENUM_ELEMENT), " missing"));
    
}


void interpreter::fCLASS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  
  t_pcode class_; t_integer identifier; t_cstring classname; t_integer method_count; t_integer propertyget_count; t_integer propertyset_count; t_integer pc_pos; t_integer pc_len; t_integer nExtend; t_integer destructor_id;
  
  myPcode->rd_CLASS(&class_, &identifier, &classname, &method_count, &propertyget_count, &propertyset_count, &pc_pos, &pc_len, &nExtend, &destructor_id);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(myPcode->getPos());
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__CLASS));
      CONSOLE pcodePrintVar(classname);
      CONSOLE pcodePrint("at ");
      CONSOLE pcodePrint(pc_pos);
      
      CONSOLE pcodePrintCR();
    }
#endif

    if (interpretPcode()) fJMP();
    if (interpretPcode()) fSEPARATOR();

    int nClassId;
    nClassId = myClass->addClass  (identifier, classname, pc_pos, pc_len, nExtend, destructor_id);

    
        

    for (int z = 0; z < method_count; z++){

      t_pcode class_method; t_integer class_identifier; t_integer identifier; t_cstring realname; t_cstring name; t_integer param_count; t_integer return_type; t_integer pc_pos; t_integer pc_len;
      
      myPcode->rd_CLASS_METHOD(&class_method, &class_identifier, &identifier, &realname, &name, &param_count, &return_type, &pc_pos, &pc_len);
      {
      

#ifdef HAS_CONSOLE
        if (!bSilent){
        CONSOLE pcodePrintSep("");
          CONSOLE pcodePrintPos(myPcode->getPos());
          CONSOLE pcodePrintOpc(pcode::pcode_(pcode__CLASS_METHOD));
          CONSOLE pcodePrintVar(realname);
          CONSOLE pcodePrint("at ");
          CONSOLE pcodePrint(pc_pos);
          
          CONSOLE pcodePrintCR();
       }
#endif

        int nId;
        nId = myClass->addClassMethod (class_identifier, identifier, realname, name, pc_pos, pc_len);

        if (interpretPcode()) fJMP();
        if (myPcode->peekPCode() == pcode__SEPARATOR && interpretPcode()) fSEPARATOR();

      } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CLASS_METHOD), " missing"));
    
    }

    for (int z = 0; z < propertyget_count; z++){

      t_pcode class_method; t_integer class_identifier; t_integer identifier; t_cstring realname; t_cstring name; t_integer param_count; t_integer return_type; t_integer pc_pos; t_integer pc_len;
      
      myPcode->rd_CLASS_METHOD(&class_method, &class_identifier, &identifier, &realname, &name, &param_count, &return_type, &pc_pos, &pc_len);
      {

#ifdef HAS_CONSOLE
        if (!bSilent){
        CONSOLE pcodePrintSep("");
          CONSOLE pcodePrintPos(myPcode->getPos());
          CONSOLE pcodePrintOpc(pcode::pcode_(pcode__CLASS_METHOD));
          CONSOLE pcodePrintVar(realname);
          CONSOLE pcodePrint("at ");
          CONSOLE pcodePrint(pc_pos);
          
          CONSOLE pcodePrintCR();
       }
#endif

        int nId;
        nId = myClass->addClassPropertyGet (class_identifier, identifier, realname, name, pc_pos, pc_len);

        if (interpretPcode()) fJMP();
        if (myPcode->peekPCode() == pcode__SEPARATOR && interpretPcode()) fSEPARATOR();

      } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CLASS_METHOD), " missing"));
    
    }

    for (int z = 0; z < propertyset_count; z++){

      t_pcode class_method; t_integer class_identifier; t_integer identifier; t_cstring realname; t_cstring name; t_integer param_count; t_integer return_type; t_integer pc_pos; t_integer pc_len;
      
      myPcode->rd_CLASS_METHOD(&class_method, &class_identifier, &identifier, &realname, &name, &param_count, &return_type, &pc_pos, &pc_len);
      {

#ifdef HAS_CONSOLE
        if (!bSilent){
        CONSOLE pcodePrintSep("");
          CONSOLE pcodePrintPos(myPcode->getPos());
          CONSOLE pcodePrintOpc(pcode::pcode_(pcode__CLASS_METHOD));
          CONSOLE pcodePrintVar(realname);
          CONSOLE pcodePrint("at ");
          CONSOLE pcodePrint(pc_pos);
          
          CONSOLE pcodePrintCR();
       }
#endif

        int nId;
        nId = myClass->addClassPropertySet (class_identifier, identifier, realname, name, pc_pos, pc_len);

        if (interpretPcode()) fJMP();
        if (myPcode->peekPCode() == pcode__SEPARATOR && interpretPcode()) fSEPARATOR();

      } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CLASS_METHOD), " missing"));
    
    }
    return ;

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CLASS), " missing"));
}

void interpreter::fLBOUND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode lbound; t_integer identifier; t_scope scope; t_boolean expression; t_boolean bReturn;

  myPcode->rd_LBOUND(&lbound, &identifier, &scope, &expression, &bReturn);
  {

    
#ifdef HAS_CONSOLE
    const char *acModule, *acSub, *acVar = "";
    if (!bSilent){     
      acModule = ""; acSub = "";
      findVars(identifier, &acModule, &acSub, &acVar);

      info(nPos, pcode__LBOUND);
      
    }
#endif

    int n;
    n = 1;

    t_array *a;
    a = getVar(scope)->getArray(identifier);

    if (a == NULL){ 
#ifdef HAS_CONSOLE
      runtimeError( utility::con(acVar, " not an array\n") ); return; }
#else
      runtimeError("not an array\n" ); return; }
#endif

    if (expression){
      n = popStackInteger();
    }

    if (n > a->count){
#ifdef HAS_CONSOLE
      runtimeError( utility::con(acVar, " index out of bounds\n"), 99 );return;  
#else
      runtimeError( " index out of bounds\n", 99 );return;  
#endif
    }

    
    if (bReturn){
      myStack->pushLong(a->idx[n - 1]);
    }

    return ;
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__LBOUND), " missing"));
}

void interpreter::fUBOUND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode ubound; t_integer identifier; t_scope scope; t_boolean expression; t_boolean bReturn;

  myPcode->rd_UBOUND(&ubound, &identifier, &scope, &expression, &bReturn);
  {
    
#ifdef HAS_CONSOLE
    const char *acModule, *acSub, *acVar = "";    
    if (!bSilent){     
      acModule = ""; acSub = "";
      findVars(identifier, &acModule, &acSub, &acVar);

      info(nPos, pcode__UBOUND);
      
    }
#endif

    int n;
    n = 1;
    t_array *a;
    a = getVar(scope)->getArray(identifier);

    if (a == NULL){ 
#ifdef HAS_CONSOLE
      runtimeError( utility::con(acVar, "not an array\n") ); return;
#else
      runtimeError( "not an array\n" ); return;
#endif
    }

    if (expression){
      n = popStackInteger();
    }

    if (n > a->count){ 
#ifdef HAS_CONSOLE
      runtimeError( utility::con(acVar, " index out of bounds\n"), 99 ); return;}
#else
      runtimeError( " index out of bounds\n", 99 ); return;}
#endif

    
    if (bReturn){
      myStack->pushLong(a->idxTo[n - 1]);
    }


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__UBOUND), " missing"));
}

void interpreter::fVARTYPE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer identifier; t_scope scope; t_boolean bReturn;

  myPcode->rd_VARTYPE(&c, &identifier, &scope, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule = "", *acSub = "", *acVar = "";
      findVars(identifier, &acModule, &acSub, &acVar);

      info(nPos, pcode__VARTYPE);
      
    }
#endif

    memory_variable *v;
    v = getVar(scope);

    int n;
    n = v->type(identifier);

    int r;
    r = 0;

    t_array *a = 0;
/*
kbEmpty 0
kbNull 1
kbInteger 2
kbLong 3
kbSingle 4
kbDouble 5
kbCurrency 6
kbDate 7
kbString 8
kbObject 9
kbError 10
kbBoolean 11
kbVariant 12
kbDataObject 13
kbDecimal 14
kbByte 17
kbArray 8192
*/
    switch(n){
      case pcode__BOOLEAN: r = 11; break;

      case pcode__QSTRING: r = 8; break;
      case pcode__CSTRING: r = 8; break;

      case pcode__BYTE: r = 17; break;
      case pcode__SHORT: r = 18; break;
      case pcode__INTEGER: r = 2; break;
      case pcode__LONG: r = 3; break;

      case pcode__SINGLE: r = 4; break;
      case pcode__DOUBLE: r = 5; break;
/*
      case pcode__INT16: r = 18; break;
      case pcode__INT32: r = 19; break;
      case pcode__INT64: r = 20; break;
      case pcode__UINT16: r = 21; break;
      case pcode__UINT32: r = 22; break;
      case pcode__UINT64: r = 23; break;
*/
      case pcode__VARIANT: 
        switch (v->getVariantType(identifier)){
          case pcode__ERROR: r = 10; goto o;
          case pcode__EMPTY: r = 0; goto o;
          default:
            if (v->getVariant_Object(identifier, 0) == 0){
              r = 1; 
              goto o;
            } else {
              r = 12; 
            }
            break;
        }
        break;

      case pcode__OBJECT: r = 9; break;

      case pcode__CURRENCY: r = 6; break;

      case pcode__DATE: r = 7; break;

      default:
        if (memory_type::isBinding(n)){
          r = n;
        } else if (memory_type::isClass(n)){
          r = n;
        } else if (memory_type::isEnum(n)){
          r = n;
        } else if (memory_type::isType(n)){
          r = n;
        }        
        break;
    }

    a = v->getArray(identifier);
    if (a->count){
      r = 8192;
    }
o:
    if (bReturn){
      myStack->pushInteger(r);
    }


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__VARTYPE), " missing"));
}

void interpreter::fTYPEOF()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer identifier; t_scope scope; t_integer nType; t_boolean bReturn;

  myPcode->rd_TYPEOF(&c, &identifier, &scope, &nType, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule = "", *acSub = "", *acVar = "";
      findVars(identifier, &acModule, &acSub, &acVar);

      info(nPos, pcode__TYPEOF);
      
    }
#endif

    if (bReturn){
      myStack->pushBoolean(getVar(scope)->type(identifier) == nType);
    }


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TYPEOF), " missing"));
}

void interpreter::f_STATIC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c;

  myPcode->rd___STATIC(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode___STATIC);
#endif

   
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode___STATIC), " missing"));
}

void interpreter::f_DYNAMIC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c;

  myPcode->rd___DYNAMIC(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode___DYNAMIC);
#endif


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode___DYNAMIC), " missing"));
}

void interpreter::fCLEAR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_boolean bStack;

  myPcode->rd_CLEAR(&c, &bStack);
  
  {


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CLEAR), " missing"));


}

void interpreter::fERASE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode erase; t_integer identifier; t_scope scope;

  myPcode->rd_ERASE(&erase, &identifier, &scope);
  {

    
#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule = "", *acSub = "", *acVar = "";
      findVars(identifier, &acModule, &acSub, &acVar);
 
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__ERASE));
      CONSOLE pcodePrintVar(acModule, acSub, acVar);
      CONSOLE pcodePrintCR();

   }
#endif

    memory_variable *v;
    v = getVar(scope);

    t_array a;
    if (scope == global){
      t_array *b = v->getArray(identifier);
      if (b) b->copyArray(&a);
    }
    v->redeclare(identifier, v->type(identifier), &a, false);


    // eigentlich je nach $static  $dynamic wenn veryoldbasic
    /*
    Fr statische Datenfelder setzt ERASE alle Elemente eines numerischen
Datenfelds auf Null und alle Elemente eines Zeichenfolgen-Datenfelds
auf eine Null-Zeichenfolge ("").
Fr dynamische Datenfelder gibt ERASE den vom Datenfeld benutzten
Speicher wieder frei. Vor der Verwendung von ERASE mssen Sie das
Datenfeld mit REDIM oder DIM neu dimensionieren.
    */
    // itereriere ber alle felder und setzte auf 0 oder ""

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ERASE), " missing"));


}

void interpreter::fCONST()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode const_; t_integer identifier; t_scope scope;

  myPcode->rd_CONST(&const_, &identifier, &scope);
  {

    t_pcode cType;
    cType = 0; 

    const char *acModule, *acSub, *acVar;
    acModule = ""; acSub = ""; acVar = "";
    
    cType = myStack->peekPCode();
    if (cType == pcode__EQSTRING) cType = pcode__QSTRING;
    else if (cType == pcode__ECSTRING) cType = pcode__CSTRING;

#ifdef HAS_CONSOLE
    if (!bSilent){     
      
      findConsts(identifier, &acModule, &acSub, &acVar); // 

      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__CONST));
      CONSOLE pcodePrintVar(acModule, acSub, acVar);


      CONSOLE pcodePrint("AS");

      CONSOLE pcodePrint(findTypes(cType));
      CONSOLE pcodePrintCR();
    }     
#endif

    if (memory_type::scalar(cType)){
      consts->declare(acModule, acSub, acVar, cType, 0, 0, true, false, false, true, 0, identifier);
    } else {
      runtimeError("not a skalar datatype for const\n");
      return;
    }

    
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CONST), " missing"));
}

void interpreter::fTIMER_ON()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c;

  myPcode->rd_TIMER_ON(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__TIMER_ON);
#endif

    my_ontimer->start(nOnTimerIntervall * 1000);    
    bOnTimer = true;

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TIMER_ON), " missing"));

}
    
void interpreter::fONTIMERGOSUB()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer new_pc;


  myPcode->rd_ONTIMERGOSUB(&c, &new_pc);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__ONTIMERGOSUB);
#endif

    nOnTimerPos = new_pc;

    nOnTimerIntervall = popStackInteger(); 


  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ONTIMERGOSUB), " missing"));

}
    
void interpreter::fTIMER_OFF()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c;


  myPcode->rd_TIMER_OFF(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__TIMER_OFF);
#endif

    my_ontimer->stop();

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TIMER_OFF), " missing"));
  
}
    
void interpreter::fTIMER_STOP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c;


  myPcode->rd_TIMER_STOP(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__TIMER_STOP);
#endif
    
    bOnTimer = false;

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__TIMER_STOP), " missing"));
  
}
          
void interpreter::fDOEVENTS()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c;

  myPcode->rd_DOEVENTS(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__DOEVENTS);
#endif

    {
      myFunction->fDOEVENTS(); // call the associated function
    }

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DOEVENTS), " missing"));
  
}

void interpreter::fSTOP()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode stop;

  myPcode->rd_STOP(&stop);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__STOP, "execution stopped");
#endif

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__STOP), " missing"));
  
}

void interpreter::fEND()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode end;

  myPcode->rd_END(&end);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__END, "execution has ended");
#endif

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__END), " missing"));
  
}

void interpreter::fSYSTEM()
{
  #ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode system;

  myPcode->rd_SYSTEM(&system);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__SYSTEM, "execution has ended");
#endif

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__SYSTEM), " missing"));
  
}


void interpreter::fCLASS_BINDINGPARAM()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer classid; t_cstring classmethodno; t_integer identifier; t_integer no;

  myPcode->rd_CLASS_BINDINGPARAM(&c, &classid, &classmethodno, &no, &identifier);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__CLASS_BINDINGPARAM));
      CONSOLE pcodePrintCR();
    }
#endif
    {
      class_bindingparam[classmethodno] = identifier;
    }

    

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__CLASS_BINDINGPARAM), " missing"));
}

void interpreter::fVER()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode ver; t_single version;

  myPcode->rd_VER(&ver, &version);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__VER, version);
#endif

    {
      if (version > interpreter__KBASIC_VERSION){  pcodeError("pcode version is newer than interpreter version"); return;}
    }
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__VER), " missing"));

  
}

void interpreter::fKBASIC()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode kbasic; char magic[7]; t_cstring projectname; t_cstring projecttype; t_cstring login;


  myPcode->rd_KBASIC(&kbasic, &magic[0], &projectname, &projecttype, &login);
  {

    magic[6] = '\0';
    sProjectName = QString::fromUtf8(projectname);
    sProjectType = projecttype;
    sLogin = login;



#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__KBASIC, magic);
#endif    

    {
      const char *s;
      s = pcode::pcode_(pcode__KBASIC);

      if (strncmp(magic, s, 6) != 0){
         pcodeError("corrupted pcode: magic is not 'KBASIC'");
         return;
      }
    }
  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__KBASIC), " missing"));

  
}

void interpreter::fOPTION_RANGE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode option_range; t_boolean on_off;

  myPcode->rd_OPTION_RANGE(&option_range, &on_off);
  {

#ifdef HAS_CONSOLE
    if (on_off) if (!bSilent) info(nPos, pcode__OPTION_RANGE, "ON");
    else if (!bSilent) info(nPos, pcode__OPTION_RANGE, "OFF");
#endif

    {
      bOptionRange = (on_off == true); // under/overflow range check on/off
    }

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__OPTION_RANGE), " missing"));

  
}

void interpreter::fSILENTMODE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_boolean on_off;

  myPcode->rd_SILENTMODE(&c, &on_off);
  {

#ifdef HAS_CONSOLE
    if (on_off) if (!bSilent) info(nPos, pcode__SILENTMODE, "ON");
    else if (!bSilent) info(nPos, pcode__SILENTMODE, "OFF");
#endif

    {
      bPcodePrint_SilentMode = bSilentMode = (on_off == true); // interpreter's debug output on/off
    }

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__SILENTMODE), " missing"));

  
}

void interpreter::fSEPARATOR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_cstring s;

  myPcode->rd_SEPARATOR(&c, &s);

  

    //QMessageBox::information(0, s, "");

  //return;
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      if (s[0] == 0){
        CONSOLE pcodePrintSep(s);
      } else {        
        CONSOLE pcodePrintSep((const char *) (s + 1)); // cut off the leading f in the names like fBuiltin...
      }
      CONSOLE pcodePrintPos(nPos);
    
      static char ac[1024]; // 
      
      CONSOLE pcodePrintPos(" ");
//      sprintf(ac, " ");
//      sprintf(ac, "___________________________ ");
//      sprintf(ac, "___________________________ [%d]", myStack->count());
//      CONSOLE pcodePrintPos(ac);
      CONSOLE pcodePrintCR(); 
    }
#endif

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__SEPARATOR), " missing"));

  
}
/*
void interpreter::fOPTION_COMPARE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_boolean bBinary;

  myPcode->rd_OPTION_COMPARE(&c, &bBinary);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__OPTION_COMPARE, bBinary);
#endif
    {
      bOptionComparyBinary = bBinary;
    }

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__OPTION_COMPARE), " missing"));

  
}*/


/*void interpreter::fOPTION_BASE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer n;

  myPcode->rd_OPTION_BASE(&c, &n);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__OPTION_BASE, n);
#endif

    {
      nBaseOfArray = nOptionBase = n; // arrays start with 1 if not explictly declared or OPTION BASE
    }

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__OPTION_BASE), " missing"));

  
}*/

void interpreter::fDATA()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode data_; t_integer count;

  myPcode->rd_DATA(&data_, &count);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__DATA));

    }
#endif
    
    int n;
    n = myData->getPos();

    myData->setPos(nMyDataPos);

    for (int i = 0; i < count; i++){
      switch (myPcode->peekPCode()){
        // andere datentypen werden vom scanner nicht benutzt
        case pcode__BOOLEAN:  myData->pushBoolean(myPcode->rd_BOOLEAN()); break;
        case pcode__INTEGER:  myData->pushInteger(myPcode->rd_INTEGER());; break;
        case pcode__LONG:     myData->pushLong(myPcode->rd_LONG());    break;
        case pcode__SINGLE:   myData->pushSingle(myPcode->rd_SINGLE());  break;
        case pcode__DOUBLE:   myData->pushDouble(myPcode->rd_DOUBLE());  break;
        case pcode__CSTRING:  myData->pushRealCString(myPcode->rd_CSTRING());  break;
        default:
          pcodeError("wrong datatype");
          break;
      }
    }

    nMyDataPos = myData->getPos();

    myData->setPos(n);



#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrint("(");
      CONSOLE pcodePrint(count);
      CONSOLE pcodePrint(")");

      CONSOLE pcodePrintCR();
    }
#endif

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DATA), " missing"));

  
}

void interpreter::fRESTORE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode restore;

  myPcode->rd_RESTORE(&restore);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__RESTORE);
#endif

    {
      myData->setPos(0);

    }

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__RESTORE), " missing"));

  
}

void interpreter::fREAD()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode read; t_integer count;

  myPcode->rd_READ(&read, &count);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__READ));

    }
#endif


    static int mm = 0; 

    mm++;
    int oo = mm;

    for (int i = 0; i < count; i++){
      int n = myData->popPCode();
      switch (n){
        // andere datentypen werden vom scanner nicht benutzt
        case pcode__BOOLEAN:  myStack->pushBoolean(myData->popBoolean()); break;
        case pcode__INTEGER:  myStack->pushInteger(myData->popInteger()); break;
        case pcode__LONG:     myStack->pushLong(myData->popLong());    break;
        case pcode__SINGLE:   myStack->pushSingle(myData->popSingle());  break;
        case pcode__DOUBLE:   myStack->pushDouble(myData->popDouble());  break;
        case pcode__REALCSTRING:   
            myStack->pushRealCString(myData->popRealCString());  break; 
        default:
          pcodeError("wrong datatype");
          break;
      }


    }
#ifdef HAS_CONSOLE
    if (!bSilent){

/*
      CONSOLE pcodePrint("(");
      CONSOLE pcodePrint(count);
      CONSOLE pcodePrint(")");
  */
      CONSOLE pcodePrintCR();
    }
#endif

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__READ), " missing"));

  
}

void interpreter::fERROR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode error; t_boolean bErrorNo;

  myPcode->rd_ERROR(&error, &bErrorNo);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__ERROR);
#endif

    myFunction->fERROR(popStackInteger()); // call the associated function

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__ERROR), " missing"));

  
}

void interpreter::fENTER_LOCAL()
{
  return fENTER_LOCAL2();
}

void interpreter::fENTER_LOCAL2(t_integer SoftOpen_classid, t_integer SoftOpen_methodid)
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer nModuleId; t_integer nSubId;

  if (SoftOpen_classid){
    c = pcode__ENTER_LOCAL;
    nModuleId = SoftOpen_classid;
    nSubId = SoftOpen_methodid;
  } else {
    myPcode->rd_ENTER_LOCAL(&c, &nModuleId,  &nSubId);
  }
  {

    const char *ac;

    ac = "";
    
#ifdef HAS_CONSOLE
    const char *acModule = ""; const char *acSub = "";
    if (!bSilent){          
      findScope(nModuleId, nSubId, false, false, &acModule, &acSub);

      ac = utility::ident(acModule, acSub);
      info(nPos, pcode__ENTER_LOCAL, ac);      
    }

    if (bDebug){
      findScope2(nModuleId, nSubId, false, false, &acModule, &acSub);
      ac = utility::ident(acModule, acSub);
    }
#endif

      enterLocal(ac);

    if (memory_type::isClass(nModuleId)){

      myLocalFrame.last()->subPcodeOffset = myClass->getPcodePosMethod(nModuleId, nSubId);
      myLocalFrame.last()->onErrorGotoPos = 0;
      myLocalFrame.last()->return_pos = 0;  // wird bei classes nicht benutzt
    }

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ENTER_LOCAL), " missing"));
  
}

// used for properties
void interpreter::fENTER_PROPERTYGET()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer nModuleId; t_integer nSubId;

  myPcode->rd_ENTER_PROPERTYGET(&c, &nModuleId,  &nSubId);
  {

    const char *acModule, *acSub, *acVar;   
    const char *ac;

    ac = "";
    
#ifdef HAS_CONSOLE
    if (!bSilent){     
      acModule = ""; acSub = ""; acVar = "";
    
      findScope(nModuleId, nSubId, false, true, &acModule, &acSub);

      ac = utility::ident(acModule, acSub);
      info(nPos, pcode__ENTER_PROPERTYGET, ac);
      
    }

    if (bDebug){
      findScope2(nModuleId, nSubId, false, true, &acModule, &acSub);
      ac = utility::ident(acModule, acSub);
    }
#endif

    enterLocal(ac);

    if (memory_type::isClass(nModuleId)){

      myLocalFrame.last()->subPcodeOffset = myClass->getPcodePosPropertyGet(nModuleId, nSubId);
      myLocalFrame.last()->onErrorGotoPos = 0;
      myLocalFrame.last()->return_pos = 0;  // wird bei classes nicht benutzt
    }

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ENTER_LOCAL), " missing"));
  
}

// used for properties
void interpreter::fENTER_PROPERTYSET()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c; t_integer nModuleId; t_integer nSubId;

  myPcode->rd_ENTER_PROPERTYSET(&c, &nModuleId,  &nSubId);
  {

    const char *acModule, *acSub, *acVar;   
    const char *ac;

    ac = "";

#ifdef HAS_CONSOLE
    if (!bSilent){     
     acModule = ""; acSub = ""; acVar = "";
      findScope(nModuleId, nSubId, true, false, &acModule, &acSub);

      ac = utility::ident(acModule, acSub);
      info(nPos, pcode__ENTER_PROPERTYSET, ac);
      
    }

    if (bDebug){
      findScope2(nModuleId, nSubId, true, false, &acModule, &acSub);
      ac = utility::ident(acModule, acSub);
    }
#endif

    enterLocal(ac);

    if (memory_type::isClass(nModuleId)){

      myLocalFrame.last()->subPcodeOffset = myClass->getPcodePosPropertySet(nModuleId, nSubId);
      myLocalFrame.last()->onErrorGotoPos = 0;
      myLocalFrame.last()->return_pos = 0;  // wird bei classes nicht benutzt
    }

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__ENTER_LOCAL), " missing"));
  
}

void interpreter::fEXIT_LOCAL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode c;

  myPcode->rd_EXIT_LOCAL(&c);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__EXIT_LOCAL);
#endif

    exitLocal();

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__EXIT_LOCAL), " missing"));
  
}

void interpreter::fERR()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode ERR; t_boolean bReturn;

  myPcode->rd_ERR(&ERR, &bReturn);
  {
  
#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__ERR);
#endif


    if (bReturn){
      pushStackInteger(nRuntimeErrorNo);
    }   

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__ERR), " missing"));

  
}

void interpreter::fERL()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode ERL; t_boolean bReturn;

  myPcode->rd_ERL(&ERL, &bReturn);
  {

#ifdef HAS_CONSOLE
    if (!bSilent) info(nPos, pcode__ERL);
#endif


    if (bReturn){
      pushStackInteger(nRuntimeErrorLine2);
    }   

  } // } else return pcodeError(utility::con(pcode::builtin_(pcode__ERL), " missing"));

  
}

int interpreter::getOffset(t_integer identifier, t_scope scope)
{
  int offset;


  memory_variable2 *v;
  if (scope != outofscope) v = getVar(scope); else return 0;

  offset = 0;

  if (array_offset2.count() && v && (v->isArray(identifier) 
    || (memory_type::isType(v->type(identifier)) || memory_type::isEnum(v->type(identifier)) ) )){
    offset = (array_offset2.last());
    array_offset2.removeLast();
 
#ifdef HAS_CONSOLE
    if (!bSilent){
      //if (!memory_type::scalar(identifier))
      {
        CONSOLE pcodePrint("(");
        CONSOLE pcodePrint(offset);
        CONSOLE pcodePrint(")");
      }
    }
#endif
  }
  return offset;
}

void interpreter::binding_callStaticMethod()
{
  t_pcode c; t_integer m; t_boolean bReturn;

  myPcode->rd_binding_ClassStaticMethod(&c, &m, &bReturn);
  {

    if (binding_callStaticMethod_kbasic_binding(m, bReturn)) return;
    //if (binding_callStaticMethod_qt_binding(m, bReturn)) return true;
  
    runtimeError( "static method is not binded" );
  }

  
}

void interpreter::binding_callMethod()
{
  t_pcode c; t_integer m; t_boolean bReturn;

  myPcode->rd_binding_ClassMethod(&c, &m, &bReturn);
  {

    
    if (binding_callMethod_kbasic_binding(m, bReturn)) return;
//    if (binding_callMethod_qt_binding(m, bReturn)) return true;
  
    runtimeError( "method is not binded" );
  }

  
}

void interpreter::binding_callProperty()
{
  t_pcode c; t_integer m; t_boolean bReturn;

  myPcode->rd_binding_ClassProperty(&c, &m, &bReturn);
  {
    
/*
    if (m == 3036){
      m = m;
    }*/
    if (binding_callMethod_kbasic_binding(m, bReturn)) return;
//    if (binding_callMethod_qt_binding(m, bReturn)) return true;
  
    runtimeError( "property is not binded" );
  }

  
}


void interpreter::binding_callStaticProperty()
{
  t_pcode c; t_integer m; t_boolean bReturn;

  myPcode->rd_binding_ClassStaticProperty(&c, &m, &bReturn);
  {
    
/*
    if (m == 3036){
      m = m;
    }*/
    if (binding_callStaticMethod_kbasic_binding(m, bReturn)) return;
//    if (binding_callStaticMethod_qt_binding(m, bReturn)) return true;
  
    runtimeError( "property is not binded" );
  }

  
}


void interpreter::binding_callFunction()
{
  t_pcode c; t_integer m; t_boolean bReturn;

  myPcode->rd_binding_Function(&c, &m, &bReturn);
  {
    

    if (binding_callFunction_kbasic_binding(m, bReturn)) return;
//    if (binding_callFunction_qt_binding(m, bReturn)) return true;
  
    runtimeError( "function is not binded" );
  }

  
}

void interpreter::binding_callOperator()
{
  t_pcode c; t_integer m;

  myPcode->rd_binding_ClassOperator(&c, &m);
  {
    

    if (binding_callOperator_kbasic_binding(m)) return ;
    //if (binding_callOperator_qt_binding(m)) return true;
  
    runtimeError( "operator is not binded" );
  }

  
}

void interpreter::binding_callFunctionOperator()
{
  t_pcode c; t_integer m;

  myPcode->rd_binding_FunctionOperator(&c, &m);
  {
    

    if (binding_callFunctionOperator_kbasic_binding(m)) return;
   // if (binding_callFunctionOperator_qt_binding(m)) return true;
  
    runtimeError( "operator is not binded" );
  }

  
}

void interpreter::callStaticMethod()
{
  t_pcode c; t_integer classid; t_integer methodid; t_boolean bReturn;

  myPcode->rd_ClassStaticMethod(&c, &classid, &methodid, &bReturn);
  {
    

     int m = myPcode->getPos();

     // call desired method
     int n = myClass->getPcodePosMethod(classid, methodid);
     int nInterpretLen = myClass->getPcodeLenMethod(classid, methodid);

     myPcode->setPos(n);

     interpret2(false, false, nInterpretLen);
     exitLocal();

     myPcode->setPos(m);
     return;

//    return runtimeError( "static method does not exist" );
  }

  
}

void interpreter::constructClassInstanceVariables (int classid)
{
  

  int nParentClassId = myClass->getParentId(classid);

  int n = myClass->getPcodePos(classid);
  int nInterpretLen = myClass->getPcodeLen(classid);

  myPcode->setPos(n);

  interpret2(false, false, nInterpretLen);

  
}
      
bool interpreter::callDestructor(int nClassId, int nMethodId, bool b)
{
  

  int m = myPcode->getPos();

#ifdef HAS_CONSOLE
  if (!bSilent){

    CONSOLE pcodePrintSep("");
    CONSOLE pcodePrintPos("");
    CONSOLE pcodePrintOpc("");

    static char ac[1024];
    sprintf(ac, "--> &H%X (Release Object)", meVars);
    CONSOLE pcodePrint(ac);

    CONSOLE pcodePrintCR();
  }
#endif

  // call desired destructor
  int n = myClass->getPcodePosMethod(nClassId, nMethodId);
  int nInterpretLen = myClass->getPcodeLenMethod(nClassId, nMethodId);

  // delete binding-object in destructor
  /*
  if (meVars){
    t_pointer o = meVars->getBindingParentClassPointer();
    if (o){
      delete o;    
    }
  }*/

  if (nInterpretLen){
    myPcode->setPos(n);

 
    {
      enterLocal("");
    }
    interpret2(false, false, nInterpretLen);
    exitLocal();

  #ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos("");
      CONSOLE pcodePrintOpc("");
      CONSOLE pcodePrintCR();
    }
  #endif

    myPcode->setPos(m);

  }

  return true;
}

bool interpreter::callMethod(bool bConstructor2, t_integer SoftOpen_classid, t_integer SoftOpen_methodid, t_cstring SoftOpen_signature, memory_variable2 **SoftOpen_returnvar)
{
  t_pcode c; t_integer classid; t_integer methodid; t_cstring signature; t_boolean bConstructor; t_boolean bDestructor; t_boolean bParent; t_boolean bReturn;

  
  if (SoftOpen_classid){ // called by Forms.Open(...)
    c = pcode__CLASSMETHOD;
    classid = SoftOpen_classid;
    methodid = SoftOpen_methodid;
    signature = SoftOpen_signature;
    bConstructor = true;
    bDestructor = false;
    bParent = false;
    bReturn = false;
  } else {
    myPcode->rd_ClassMethod(&c, &classid, &methodid, &signature, &bConstructor, &bDestructor, &bParent, &bReturn);
  }

  {

    

    if (bConstructor){

      int m = myPcode->getPos();

      bool b = !bConstructor2;

      memory_variable2 *v = meVars;

      if (b){
         meVars = new memory_variable2();
         meVars->setClassId(classid); //  needed for destructor calls

         myGc->add(meVars); // gc
         myGc->inc(meVars); // gc
      }

      if (SoftOpen_classid) *SoftOpen_returnvar = meVars;

#ifdef HAS_CONSOLE
      if (!bSilent){

         CONSOLE pcodePrintSep("");
         CONSOLE pcodePrintPos("");
         CONSOLE pcodePrintOpc("");

        static char ac[1024];
        if (b){
          sprintf(ac, "--> &H%X (Create Object)", meVars);
        } else {
          sprintf(ac, "--> &H%X (Object)", meVars);
        }
        CONSOLE pcodePrint(ac);

        CONSOLE pcodePrintCR();
      }
#endif

      // 1. construct class instance variables 
      constructClassInstanceVariables(classid);

      // 2. call desired constructor
      int n = myClass->getPcodePosMethod(classid, methodid);
      int nInterpretLen = myClass->getPcodeLenMethod(classid, methodid);

      myPcode->setPos(n);

      if (nInterpretLen > 0){


        interpret2(false, b || bConstructor2, nInterpretLen);
      }
      exitLocal();

#ifdef HAS_CONSOLE
      if (!bSilent){
         CONSOLE pcodePrintSep("");
         CONSOLE pcodePrintPos("");
         CONSOLE pcodePrintOpc("");
         CONSOLE pcodePrintCR();
      }
#endif

      if (b){
        myStack->pushPointer(pcode__OBJECT, meVars, false, true);
      }

      myPcode->setPos(m);
      meVars = v;

      return true;
    } else if (bDestructor){

      callDestructor(classid, methodid, false);

      return true;

    } else {

      int m = myPcode->getPos();
      memory_variable2 *v = meVars;

      int h = myStack->popPCode();

      switch(h){
        case pcode__OBJECT:
          {
            bool b44 = myStack->popBoolean();
            bool memory_variable2_ = myStack->popBoolean();
				    meVars = (memory_variable2 *) myStack->popPointer();
          }
          break;
        default:
          if (memory_type::isClass(h)){
             bool b44 = myStack->popBoolean();
             bool memory_variable2_ = myStack->popBoolean();
             meVars = (memory_variable2 *) myStack->popPointer();
          } else {
            pcodeError("method call: object type not on stack");
          }
          break;
      }

#ifdef HAS_CONSOLE
      if (!bSilent){

         CONSOLE pcodePrintSep("");
         CONSOLE pcodePrintPos("");
         CONSOLE pcodePrintOpc("");

        static char ac[1024];
        sprintf(ac, "--> &H%X (Object)", meVars);
        CONSOLE pcodePrint(ac);

        CONSOLE pcodePrintCR();
      }
#endif

      if (meVars == 0) return runtimeError("null pointer exception");

      int nObjectClassId = meVars->getClassId();

      // call desired method
      int n;
      // object hat methode?, ansonsten call der methode des parents
      if (!bParent && myClass->hasMethodWithName(nObjectClassId, signature)){
        n = myClass->getPcodePosMethod(nObjectClassId, methodid);
      } else {
        n = myClass->getPcodePosMethod(classid, methodid);
        nObjectClassId = classid;
      }

      int nInterpretLen = myClass->getPcodeLenMethod(nObjectClassId, methodid);

      myPcode->setPos(n);

      interpret2(false, false, nInterpretLen);
      exitLocal();

#ifdef HAS_CONSOLE
      if (!bSilent){
         CONSOLE pcodePrintSep("");
         CONSOLE pcodePrintPos("");
         CONSOLE pcodePrintOpc("");
         CONSOLE pcodePrintCR();
      }
#endif

      myPcode->setPos(m);
      meVars = v;
      return true;

    }

  }

  return false;
}

void interpreter::callPropertySet()
{
  t_pcode c; t_integer classid; t_integer methodid; t_cstring signature; t_boolean bConstructor; t_boolean bDestructor; t_boolean bParent; t_boolean bReturn;

  
  //if (
      myPcode->rd_ClassPropertySet(&c, &classid, &methodid, &signature, &bConstructor, &bDestructor, &bParent, &bReturn);
      {

    {
      

      int m = myPcode->getPos();
      memory_variable2 *v = meVars;

      int h = myStack->popPCode();

      switch(h){
        case pcode__OBJECT:
          {
            bool b44 = myStack->popBoolean();
            bool memory_variable2_ = myStack->popBoolean();
				    meVars = (memory_variable2 *) myStack->popPointer();
          }
          break;
        default:
          if (memory_type::isClass(h)){
             bool b44 = myStack->popBoolean();
             bool memory_variable2_ = myStack->popBoolean();
             meVars = (memory_variable2 *) myStack->popPointer();
          } else {
            pcodeError("property set call: object type not on stack");
          }          
          break;
      }

#ifdef HAS_CONSOLE
      if (!bSilent){

         CONSOLE pcodePrintSep("");
         CONSOLE pcodePrintPos("");
         CONSOLE pcodePrintOpc("");

        static char ac[1024];
        sprintf(ac, "--> &H%X (Object)", meVars);
        CONSOLE pcodePrint(ac);

        CONSOLE pcodePrintCR();
      }
#endif

      int nObjectClassId = meVars->getClassId();

      // call desired method
      int n;
      // object hat methode?, ansonsten call der methode des parents
      if (!bParent && myClass->hasPropertySetWithName(nObjectClassId, signature)){
        n = myClass->getPcodePosPropertySet(nObjectClassId, methodid);
      } else {
        n = myClass->getPcodePosPropertySet(classid, methodid);
        nObjectClassId = classid;
      }

      int nInterpretLen = myClass->getPcodeLenPropertySet(nObjectClassId, methodid);

      myPcode->setPos(n);

      interpret2(false, false, nInterpretLen);
      exitLocal();

#ifdef HAS_CONSOLE
      if (!bSilent){
         CONSOLE pcodePrintSep("");
         CONSOLE pcodePrintPos("");
         CONSOLE pcodePrintOpc("");
         CONSOLE pcodePrintCR();
      }
#endif

      myPcode->setPos(m);
      meVars = v;
      return;

    }

  }

  
}

void interpreter::callPropertyGet()
{
  t_pcode c; t_integer classid; t_integer methodid; t_cstring signature; t_boolean bConstructor; t_boolean bDestructor; t_boolean bParent; t_boolean bReturn;

  
  //if (
      myPcode->rd_ClassPropertyGet(&c, &classid, &methodid, &signature, &bConstructor, &bDestructor, &bParent, &bReturn);
      {

    {
      

      int m = myPcode->getPos();
      memory_variable2 *v = meVars;

      int h = myStack->popPCode();

      switch(h){
        case pcode__OBJECT:
          {
            bool b44 = myStack->popBoolean();
            bool memory_variable2_ = myStack->popBoolean();
				    meVars = (memory_variable2 *) myStack->popPointer();
          }
          break;
        default:
          if (memory_type::isClass(h)){
             bool b44 = myStack->popBoolean();
             bool memory_variable2_ = myStack->popBoolean();
             meVars = (memory_variable2 *) myStack->popPointer();
          } else {
            pcodeError("property get call: object type not on stack");
          }                
          break;
      }

#ifdef HAS_CONSOLE
      if (!bSilent){

         CONSOLE pcodePrintSep("");
         CONSOLE pcodePrintPos("");
         CONSOLE pcodePrintOpc("");

        static char ac[1024];
        sprintf(ac, "--> &H%X (Object)", meVars);
        CONSOLE pcodePrint(ac);

        CONSOLE pcodePrintCR();
      }
#endif

      int nObjectClassId = meVars->getClassId();

      // call desired method
      int n;
      // object hat methode?, ansonsten call der methode des parents
      if (!bParent && myClass->hasPropertyGetWithName(nObjectClassId, signature)){
        n = myClass->getPcodePosPropertyGet(nObjectClassId, methodid);
      } else {
        n = myClass->getPcodePosPropertyGet(classid, methodid);
        nObjectClassId = classid;
      }

      int nInterpretLen = myClass->getPcodeLenPropertyGet(nObjectClassId, methodid);

      myPcode->setPos(n);

      interpret2(false, false, nInterpretLen);
      exitLocal();

#ifdef HAS_CONSOLE
      if (!bSilent){
         CONSOLE pcodePrintSep("");
         CONSOLE pcodePrintPos("");
         CONSOLE pcodePrintOpc("");
         CONSOLE pcodePrintCR();
      }
#endif

      myPcode->setPos(m);
      meVars = v;
      return;

    }

  }

  
}

/*
interpreter scopes:
  static class
  instance class
  local
  global
*/
void interpreter::fDIM()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode dim; t_integer identifier; t_scope scope; t_integer type; t_boolean _new; t_boolean bReference; t_boolean bArray; t_boolean bStatic; t_integer nLStringSize; t_integer parent_type; t_cstring varname; t_boolean globalform; 

  myPcode->rd_DIM(&dim, &identifier, &scope, &type, &_new, 
    &bReference, &bArray, &bStatic, &nLStringSize, &parent_type, &varname, &globalform);
  {
    bool bb = parent_type != pcode___form && parent_type != pcode___menubar && parent_type != pcode___toolbar && type != pcode___err; // WORKAROUND because default.kbasic creates no parser information for runtime
    
    if (scope == global){
      if (type == pcode___menubaritem){
        menubaritems[varname] = identifier;
      } else if (type == pcode___toolbaritem){
        toolbaritems[varname] = identifier;
      } else if (globalform){
        forms[identifier] = varname;
        forms2[varname] = identifier;
      }
    }
/*
    if (identifier == 22){
      identifier = identifier;
    }
*/
    if (parent_type == pcode___form){
      kbFormId = identifier;
    }
    else if (parent_type == pcode___menubar){
      kbMenuBarId = identifier;
    }
    else if (parent_type == pcode___toolbar){
      kbToolBarId = identifier;
    }
    else if (parent_type == pcode___event){
      kbEventId = identifier;
    }
/*
    if (identifier == 17){
      identifier = identifier;
    }*/

    if (bStatic){
      scope = global;
    }
    memory_variable2 *v;
    v = getVar(scope);

#ifdef HAS_CONSOLE
    const char *acModule, *acSub, *acVar;
    acModule = ""; acSub = ""; acVar = "???";

    if (bb && (bDebug || !bSilent)){
      findVars(identifier, &acModule, &acSub, &acVar);
    }

     if (bb && !bSilent){

      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      if (scope == param){
        if (bReference){
          CONSOLE pcodePrint("DIM (BYREF)");
        } else {
          CONSOLE pcodePrint("DIM (BYVAL)");
        }
      } else {
        CONSOLE pcodePrintOpc(pcode::pcode_(pcode__DIM));
      }
      static char ac[1024];
      sprintf(ac, "id=%d   &H%X::", identifier, v);
      CONSOLE pcodePrint(ac);
      CONSOLE pcodePrintVar(acModule, acSub, acVar);
    }
#endif

    t_array *a;
    a = 0;
    if (bArray) a = myArray2.first();

    if (bb && !bSilent){

      if (bArray && a != 0){

        if (a->count > 0){
          CONSOLE pcodePrint("( ");

          for (int i = 0; i < a->count; i++){
            if (i > 0){
              CONSOLE pcodePrint(", ");
            }
            CONSOLE pcodePrint(a->idx[i]);
            CONSOLE pcodePrint("TO ");
            CONSOLE pcodePrint(a->idxTo[i]);
          }

          CONSOLE pcodePrint(")");
        }
      }
    } else {
      if (bArray && a != 0){
      }
    }
#ifdef HAS_CONSOLE
    if (bb && !bSilent){
      const char *t = findTypes(type);
      if (t){
        CONSOLE pcodePrint("AS");
        CONSOLE pcodePrint(t);   
      } else {
        CONSOLE pcodePrint(type);   
      }

      if (bReference){
        CONSOLE pcodePrint("REFERENCE");
      }
    }
#endif


    int nTypeSize;
    nTypeSize = myType->getSize(type);
    if (nLStringSize) nTypeSize = nLStringSize;
 
    if (bb && !bSilent){
      CONSOLE pcodePrint("( typesize = ");
      CONSOLE pcodePrint(nTypeSize);
      CONSOLE pcodePrint(")");
      CONSOLE pcodePrint("( allsize = ");
      if (a) CONSOLE pcodePrint(nTypeSize * a->typeSizeMulitplierOfArray()); else CONSOLE pcodePrint(nTypeSize);
      CONSOLE pcodePrint(")");
      CONSOLE pcodePrintCR();
    }

    // if var already declared, then maybe it is declared inside a loop --> no error
#ifdef HAS_CONSOLE
    v->declare(acModule, acSub, acVar, type, a, true, bReference, false, true, 0, nTypeSize, identifier);
#else
    v->declare("", "", "", type, a, true, bReference, false, true, 0, nTypeSize, identifier);
#endif

/*
  QString ss;
  ss = ss.sprintf("dim");
  QMessageBox::information(0, "", ss);
*/

    if (!memory_type::scalar(type)){

      if (_new){

        void *p;// = 0;

        if (type == pcode__OBJECT){

          memory_variable2 *v2;
          v2 = new memory_variable2();
          v2->setClassId(pcode__OBJECT); //  needed for destructor calls

          getVar(scope)->setObject(identifier, v2, getOffset(identifier, scope));

          myGc->add(v2); // gc
          myGc->inc(v2); // gc

        } else if (myStack->peekPCode() == pcode__OBJECT){ 
          myStack->popPCode();
   
          
          bool b44 = myStack->popBoolean();
          bool memory_variable2_ = myStack->popBoolean();
				  memory_variable2 *v2 = (memory_variable2 *) myStack->popPointer();
    
          getVar(scope)->setObject(identifier, v2, getOffset(identifier, scope));

          if (parent_type == pcode___event){
            kbEventScope = v2;
          }

          if (v2->getBindingParentClassPointer()){
            if (memory_type::isKBasic(v2->getBindingParentClassType())){    
              int n = v2->getBindingParentClassType();
              if (n == pcode___form || n == pcode___menubar || n == pcode___toolbar){
                 kbasic_binding_setKbId(v2->getBindingParentClassPointer(), v2, identifier, v2->getBindingParentClassType());
              } else {
                 kbasic_binding_setKbId(v2->getBindingParentClassPointer(), getVar(scope), identifier, v2->getBindingParentClassType());
              }              
            } else {
               kbasic_binding_setKbId(v2->getBindingParentClassPointer(), getVar(scope), identifier, v2->getBindingParentClassType());
            }
          }

        } else if (myStack->peekPCode() == type){ 
          myStack->popPCode();
          bool b44 = myStack->popBoolean();
          bool memory_variable2 = myStack->popBoolean();
          p = myStack->popPointer(); 

          // qt binding
          if (/*memory_type::isClass(type) || memory_type::isBinding(type) || */memory_type::isKBasic(type)){
            kbasic_binding_setKbId(p, getVar(scope), identifier, type);
          }


          switch(type){
            case pcode___strings:
            case pcode___stringsstrings:
            case pcode___array:
            case pcode___bits:
              myGc->dec2(getVar(scope)->getPointer(identifier, getOffset(identifier, scope))); // gc
              myGc->add2(p, type); // gc
              myGc->inc2(p); // gc
              break;
          }

          getVar(scope)->setPointer(identifier, p, getOffset(identifier, scope));
  

        } else {
          pcodeError("pointer or object missing");
          return;
        }

      }


      if (type == pcode___err){
        err2 = (_err *) v->getPointer(identifier);
      }
    }

    if (bArray && a != 0){
      myArray2.removeFirst();
    }

    

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DIM), " missing"));
}

void interpreter::fREDIM()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode redim; t_integer identifier; t_scope scope; t_boolean preserve;

  myPcode->rd_REDIM(&redim, &identifier, &scope, &preserve);
  {

    memory_variable2 *v;
    v = getVar(scope);


#ifdef HAS_CONSOLE
    if (!bSilent){
      const char *acModule, *acSub, *acVar;
      acModule = ""; acSub = ""; acVar = "???";

      findVars(identifier, &acModule, &acSub, &acVar);

      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__REDIM));

      static char ac[1024];
      sprintf(ac, "&H%X::", v);
      CONSOLE pcodePrint(ac);
      CONSOLE pcodePrintVar(acModule, acSub, acVar);
    }
#endif

    bool bArray = true;
    t_array *a;
    a = myArray2.first();


#ifdef HAS_CONSOLE
    if (!bSilent){

      if (bArray && a != 0){

        if (a->count > 0){
          CONSOLE pcodePrint("( ");

          for (int i = 0; i < a->count; i++){
            if (i > 0){
              CONSOLE pcodePrint(", ");
            }
            CONSOLE pcodePrint(a->idx[i]);
            CONSOLE pcodePrint("TO ");
            CONSOLE pcodePrint(a->idxTo[i]);
          }

          CONSOLE pcodePrint(")");
        }
      } else {
       a = new t_array();
      }
    }
#else
      if (bArray && a != 0){
      } else {
        a = new t_array();
      }
    
#endif
    int type = v->type(identifier);

    int nTypeSize;
    nTypeSize = myType->getSize(type);
 
#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrint("( typesize = ");
      CONSOLE pcodePrint(nTypeSize);
      CONSOLE pcodePrint(")");
      CONSOLE pcodePrint("( allsize = ");
      CONSOLE pcodePrint(nTypeSize * a->typeSizeMulitplierOfArray());
      CONSOLE pcodePrint(")");
      CONSOLE pcodePrintCR();
    }
#endif
    

    v->redeclare(identifier, type, a, preserve);

    if (bArray && a != 0){
      myArray2.removeFirst();
    }

    

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__REDIM), " missing"));
}

void interpreter::enterLocal(const char *ac)
{
  local_counter++;

  if (local_counter > interpreter__MAX_STACK){ runtimeError("stack overflow - try to increase the available stack memory", 28); return; }

  local_frame_ *lf = new local_frame_();

  lf->localVars = new memory_variable2();  
  lf->bGlobal = false;

#ifdef HAS_CONSOLE
  register int n = strlen(ac);

	memcpy(lf->acName, ac, n);
	lf->acName[n] = '\0';
#endif

  myLocalFrame.append(lf);

#ifdef HAS_CONSOLE
  if (!bSilent) CONSOLE setSub(true);
#endif

  
}

void interpreter::exitLocal()
{
  local_counter--;

  if (local_counter < 0){ runtimeError("stack underflow"); return; }

  // alle lokalen objectvariablen mit gc sync
  local_frame_ *lf = myLocalFrame.takeLast();
  memory_variable2 *v = lf->localVars;

  if (v->first()){
    do {
      int n = v->type(v->getId());
      if (memory_type::isClass(n)){
        myGc->dec((memory_variable2 *) v->getObject(v->getId(), 0)); 

      } else if (memory_type::isBinding(n)){
        t_pointer p = v->getPointer(v->getId(), 0);
        if (p != myGcLock2){
          myGc->dec2(p); 
        }
      }
    } while (v->next());
  }

  myGcLock2 = 0;

  v->removeAllExceptObjects();

  delete v;

  delete lf;
 
#ifdef HAS_CONSOLE
  if (!bSilent) CONSOLE setSub(false);
#endif
  
}

void interpreter::registerBuiltinTypes()
{
  registerTypePublic(pcode::pcode_(pcode__BOOLEAN), pcode__BOOLEAN);

  registerTypePublic(pcode::pcode_(pcode__QSTRING), pcode__QSTRING);
  registerTypePublic(pcode::pcode_(pcode__LQSTRING), pcode__LQSTRING);
  registerTypePublic(pcode::pcode_(pcode__CSTRING), pcode__CSTRING);
  registerTypePublic(pcode::pcode_(pcode__LCSTRING), pcode__LCSTRING);
  
  registerTypePublic(pcode::pcode_(pcode__BYTE), pcode__BYTE);
  registerTypePublic(pcode::pcode_(pcode__SHORT), pcode__SHORT);
  registerTypePublic(pcode::pcode_(pcode__INTEGER), pcode__INTEGER);
  registerTypePublic(pcode::pcode_(pcode__LONG), pcode__LONG);

  registerTypePublic(pcode::pcode_(pcode__SINGLE), pcode__SINGLE);
  registerTypePublic(pcode::pcode_(pcode__DOUBLE), pcode__DOUBLE);
/*
  registerTypePublic(pcode::pcode_(pcode__INT16), pcode__INT16);
  registerTypePublic(pcode::pcode_(pcode__INT32), pcode__INT32);
  registerTypePublic(pcode::pcode_(pcode__INT64), pcode__INT64);
  registerTypePublic(pcode::pcode_(pcode__UINT16), pcode__UINT16);
  registerTypePublic(pcode::pcode_(pcode__UINT32), pcode__UINT32);
  registerTypePublic(pcode::pcode_(pcode__UINT32), pcode__UINT32);
*/
  registerTypePublic(pcode::pcode_(pcode__CONST), pcode__CONST);

  registerTypePublic(pcode::pcode_(pcode__REFERENCE), pcode__REFERENCE);

  registerTypePublic(pcode::pcode_(pcode__VARIANT), pcode__VARIANT);

  registerTypePublic(pcode::pcode_(pcode__CURRENCY), pcode__CURRENCY);
  registerTypePublic(pcode::pcode_(pcode__DATE), pcode__DATE);

  registerTypePublic(pcode::pcode_(pcode__OBJECT), pcode__OBJECT);

  registerTypePublic(pcode::pcode_(pcode__VOID), pcode__VOID); // 

//  registerTypePublic(pcode::pcode_(pcode__CHARACTER), pcode__CHARACTER);
  
}

// BINDING
void interpreter::binding_registerType_kbasic_binding()
{
  registerTypePublic("CheckBox", pcode___checkbox);  
  registerTypePublic("Form", pcode___form);  

  
  // CONTROL
  registerTypePublic("UdpSocket", pcode___udpsocket);  
  registerTypePublic("RichTextBox", pcode___editor);  
  registerTypePublic("HtmlView", pcode___browser);  
  registerTypePublic("ScrollBar", pcode___scrollbar);  
  registerTypePublic("SpinBox", pcode___spinbox);  
  registerTypePublic("Slider", pcode___slider);  
  registerTypePublic("FormsView", pcode___formsview);  
  registerTypePublic("ToolBarView", pcode___toolbarview);  
  registerTypePublic("SvgBox", pcode___svg);  
  registerTypePublic("CommandLinkButton", pcode___commandlinkbutton);  
  registerTypePublic("ResizeBox", pcode___resizebox);  
  registerTypePublic("ToolButton", pcode___toolbutton);  
  registerTypePublic("FontDialog", pcode___fontdialog);  
  registerTypePublic("ProgressDialog", pcode___progressdialog);  
  registerTypePublic("ColorDialog", pcode___colordialog);  
  registerTypePublic("SaveDialog", pcode___savedialog);  
  registerTypePublic("Label", pcode___label);  
  registerTypePublic("Application", pcode___application);  
  registerTypePublic("MainWindow", pcode___mainwindow);    
  registerTypePublic("ComboBox", pcode___combobox);  
  registerTypePublic("CommandButton", pcode___commandbutton);  
  registerTypePublic("Frame", pcode___frame);  
  registerTypePublic("Image", pcode___image);  
 // registerTypePublic("Key", pcode___key);  
  registerTypePublic("ListBox", pcode___listbox);  
 // registerTypePublic("Mouse", pcode___mouse);  
//  registerTypePublic("OptionButton", pcode___optionbutton);  
  registerTypePublic("ProgressBar", pcode___progressbar);  
  registerTypePublic("RadioButton", pcode___radiobutton);  
 // registerTypePublic("TextArea", pcode___textarea);  
  registerTypePublic("TextBox", pcode___textbox);  
  registerTypePublic("Event", pcode___event);  
  registerTypePublic("FormView", pcode___childcontrol);  
  registerTypePublic("SerialPort", pcode___serialport);  
  registerTypePublic("StatusBar", pcode___statusbar);  
  registerTypePublic("OpenDialog", pcode___opendialog);  
  registerTypePublic("CMath", pcode___opendialog);  
  registerTypePublic("MovieBox", pcode___movie);  
  registerTypePublic("Sound", pcode___sound);  
  registerTypePublic("WebView", pcode___web);  
  registerTypePublic("DatabaseDialog", pcode___databasedialog);  
  registerTypePublic("Database", pcode___database);  
  registerTypePublic("Table", pcode___table);  
  registerTypePublic("Record", pcode___record);  
  registerTypePublic("Query", pcode___query);  
  registerTypePublic("TabView", pcode___tab);  
  registerTypePublic("FormView", pcode___childcontrol);  

  //registerTypePublic("Report", pcode___report);  
//  registerTypePublic("ActiveX", pcode___activex);  
//  registerTypePublic("ByteArray", pcode___bytearray);  
//  registerTypePublic("Collection", pcode___collection);  

  


/*

registerTypePublic("scanner", pcode__scanner);
registerTypePublic("parser", pcode__parser);
registerTypePublic("interpreter", pcode__interpreter);
registerTypePublic("pcode", pcode__pcode);
registerTypePublic("token", pcode__token);
*/
}
/*
bool interpreter::binding_registerType_qt_binding()
{
  // 
  registerTypePublic("QAccel", pcode__QAccel);
  registerTypePublic("QAccessible", pcode__QAccessible);
  registerTypePublic("QAccessibleInterface", pcode__QAccessibleInterface);
  registerTypePublic("QAccessibleObject", pcode__QAccessibleObject);
  registerTypePublic("QAction", pcode__QAction);
  registerTypePublic("QActionGroup", pcode__QActionGroup);
  registerTypePublic("QApplication", pcode__QApplication);
  registerTypePublic("QAsciiCache", pcode__QAsciiCache);
  registerTypePublic("QAsciiCacheIterator", pcode__QAsciiCacheIterator);
  registerTypePublic("QAsciiDict", pcode__QAsciiDict);
  registerTypePublic("QAsciiDictIterator", pcode__QAsciiDictIterator);
  registerTypePublic("QAssistantClient", pcode__QAssistantClient);
  registerTypePublic("QAxAggregated", pcode__QAxAggregated);
  registerTypePublic("QAxBase", pcode__QAxBase);
  registerTypePublic("QAxBindable", pcode__QAxBindable);
  registerTypePublic("QAxFactory", pcode__QAxFactory);
  registerTypePublic("QAxObject", pcode__QAxObject);
  registerTypePublic("QAxScript", pcode__QAxScript);
  registerTypePublic("QAxScriptEngine", pcode__QAxScriptEngine);
  registerTypePublic("QAxScriptManager", pcode__QAxScriptManager);
  registerTypePublic("QAxWidget", pcode__QAxWidget);
  registerTypePublic("QBig5Codec", pcode__QBig5Codec);
  registerTypePublic("QBig5hkscsCodec", pcode__QBig5hkscsCodec);
  registerTypePublic("QBitArray", pcode__QBitArray);
  registerTypePublic("QBitmap", pcode__QBitmap);
  registerTypePublic("QBitVal", pcode__QBitVal);
  registerTypePublic("QBoxLayout", pcode__QBoxLayout);
  registerTypePublic("QBrush", pcode__QBrush);
  registerTypePublic("QBuffer", pcode__QBuffer);
  registerTypePublic("QButton", pcode__QButton);
  registerTypePublic("QButtonGroup", pcode__QButtonGroup);
  registerTypePublic("QByteArray", pcode__QByteArray);
  registerTypePublic("QCache", pcode__QCache);
  registerTypePublic("QCacheIterator", pcode__QCacheIterator);
  registerTypePublic("QCanvas", pcode__QCanvas);
  registerTypePublic("QCanvasEllipse", pcode__QCanvasEllipse);
  registerTypePublic("QCanvasItem", pcode__QCanvasItem);
  registerTypePublic("QCanvasItemList", pcode__QCanvasItemList);
  registerTypePublic("QCanvasLine", pcode__QCanvasLine);
  registerTypePublic("QCanvasPixmap", pcode__QCanvasPixmap);
  registerTypePublic("QCanvasPixmapArray", pcode__QCanvasPixmapArray);
  registerTypePublic("QCanvasPolygon", pcode__QCanvasPolygon);
  registerTypePublic("QCanvasPolygonalItem", pcode__QCanvasPolygonalItem);
  registerTypePublic("QCanvasRectangle", pcode__QCanvasRectangle);
  registerTypePublic("QCanvasSpline", pcode__QCanvasSpline);
  registerTypePublic("QCanvasSprite", pcode__QCanvasSprite);
  registerTypePublic("QCanvasText", pcode__QCanvasText);
  registerTypePublic("QCanvasView", pcode__QCanvasView);
  registerTypePublic("QCDEStyle", pcode__QCDEStyle);
  registerTypePublic("QChar", pcode__QChar);
  registerTypePublic("QCharRef", pcode__QCharRef);
  registerTypePublic("QCheckBox", pcode__QCheckBox);
  registerTypePublic("QCheckListItem", pcode__QCheckListItem);
  registerTypePublic("QCheckTableItem", pcode__QCheckTableItem);
  registerTypePublic("QChildEvent", pcode__QChildEvent);
  registerTypePublic("QClipboard", pcode__QClipboard);
  registerTypePublic("QCloseEvent", pcode__QCloseEvent);
  registerTypePublic("QColor", pcode__QColor);
  registerTypePublic("QColorDialog", pcode__QColorDialog);
  registerTypePublic("QColorDrag", pcode__QColorDrag);
  registerTypePublic("QColorGroup", pcode__QColorGroup);
  registerTypePublic("QComboBox", pcode__QComboBox);
  registerTypePublic("QComboTableItem", pcode__QComboTableItem);
  registerTypePublic("QCommonStyle", pcode__QCommonStyle);
  registerTypePublic("QConstString", pcode__QConstString);
  registerTypePublic("QContextMenuEvent", pcode__QContextMenuEvent);
  registerTypePublic("QCopChannel", pcode__QCopChannel);
  registerTypePublic("QCString", pcode__QCString);
  registerTypePublic("QCursor", pcode__QCursor);
  registerTypePublic("QCustomEvent", pcode__QCustomEvent);
  registerTypePublic("QCustomMenuItem", pcode__QCustomMenuItem);
  registerTypePublic("QDataBrowser", pcode__QDataBrowser);
  registerTypePublic("QDataStream", pcode__QDataStream);
  registerTypePublic("QDataTable", pcode__QDataTable);
  registerTypePublic("QDataView", pcode__QDataView);
  registerTypePublic("QDate", pcode__QDate);
  registerTypePublic("QDateEdit", pcode__QDateEdit);
  registerTypePublic("QDateTime", pcode__QDateTime);
  registerTypePublic("QDateTimeEdit", pcode__QDateTimeEdit);
  registerTypePublic("QDateTimeEditBase", pcode__QDateTimeEditBase);
  registerTypePublic("QDeepCopy", pcode__QDeepCopy);
  registerTypePublic("QDesktopWidget", pcode__QDesktopWidget);
  registerTypePublic("QDial", pcode__QDial);
  registerTypePublic("QDialog", pcode__QDialog);
  registerTypePublic("QDict", pcode__QDict);
  registerTypePublic("QDictIterator", pcode__QDictIterator);
  registerTypePublic("QDir", pcode__QDir);
  registerTypePublic("QDirectPainter", pcode__QDirectPainter);
  registerTypePublic("QDns", pcode__QDns);
  registerTypePublic("QDockArea", pcode__QDockArea);
  registerTypePublic("QDockWindow", pcode__QDockWindow);
  registerTypePublic("QDomAttr", pcode__QDomAttr);
  registerTypePublic("QDomCDATASection", pcode__QDomCDATASection);
  registerTypePublic("QDomCharacterData", pcode__QDomCharacterData);
  registerTypePublic("QDomComment", pcode__QDomComment);
  registerTypePublic("QDomDocument", pcode__QDomDocument);
  registerTypePublic("QDomDocumentFragment", pcode__QDomDocumentFragment);
  registerTypePublic("QDomDocumentType", pcode__QDomDocumentType);
  registerTypePublic("QDomElement", pcode__QDomElement);
  registerTypePublic("QDomEntity", pcode__QDomEntity);
  registerTypePublic("QDomEntityReference", pcode__QDomEntityReference);
  registerTypePublic("QDomImplementation", pcode__QDomImplementation);
  registerTypePublic("QDomNamedNodeMap", pcode__QDomNamedNodeMap);
  registerTypePublic("QDomNode", pcode__QDomNode);
  registerTypePublic("QDomNodeList", pcode__QDomNodeList);
  registerTypePublic("QDomNotation", pcode__QDomNotation);
  registerTypePublic("QDomProcessingInstruction", pcode__QDomProcessingInstruction);
  registerTypePublic("QDomText", pcode__QDomText);
  registerTypePublic("QDoubleValidator", pcode__QDoubleValidator);
  registerTypePublic("QDragEnterEvent", pcode__QDragEnterEvent);
  registerTypePublic("QDragLeaveEvent", pcode__QDragLeaveEvent);
  registerTypePublic("QDragMoveEvent", pcode__QDragMoveEvent);
  registerTypePublic("QDragObject", pcode__QDragObject);
  registerTypePublic("QDropEvent", pcode__QDropEvent);
  registerTypePublic("QEditorFactory", pcode__QEditorFactory);
  registerTypePublic("QErrorMessage", pcode__QErrorMessage);
  registerTypePublic("QEucJpCodec", pcode__QEucJpCodec);
  registerTypePublic("QEucKrCodec", pcode__QEucKrCodec);
  registerTypePublic("QEvent", pcode__QEvent);
  registerTypePublic("QEventLoop", pcode__QEventLoop);
  registerTypePublic("QFile", pcode__QFile);
  registerTypePublic("QFileDialog", pcode__QFileDialog);
  registerTypePublic("QFileIconProvider", pcode__QFileIconProvider);
  registerTypePublic("QFileInfo", pcode__QFileInfo);
  registerTypePublic("QFilePreview", pcode__QFilePreview);
  registerTypePublic("QFocusData", pcode__QFocusData);
  registerTypePublic("QFocusEvent", pcode__QFocusEvent);
  registerTypePublic("QFont", pcode__QFont);
  registerTypePublic("QFontDatabase", pcode__QFontDatabase);
  registerTypePublic("QFontDialog", pcode__QFontDialog);
  registerTypePublic("QFontInfo", pcode__QFontInfo);
  registerTypePublic("QFontManager", pcode__QFontManager);
  registerTypePublic("QFontMetrics", pcode__QFontMetrics);
  registerTypePublic("QFrame", pcode__QFrame);
  registerTypePublic("QFtp", pcode__QFtp);
  registerTypePublic("QGb18030Codec", pcode__QGb18030Codec);
  registerTypePublic("QGb2312Codec", pcode__QGb2312Codec);
  registerTypePublic("QGbkCodec", pcode__QGbkCodec);
  registerTypePublic("QGfxDriverFactory", pcode__QGfxDriverFactory);
  registerTypePublic("QGfxDriverPlugin", pcode__QGfxDriverPlugin);
  registerTypePublic("QGL", pcode__QGL);
  registerTypePublic("QGLayoutIterator", pcode__QGLayoutIterator);
  registerTypePublic("QGLColormap", pcode__QGLColormap);
  registerTypePublic("QGLContext", pcode__QGLContext);
  registerTypePublic("QGLFormat", pcode__QGLFormat);
  registerTypePublic("QGLWidget", pcode__QGLWidget);
  registerTypePublic("QGrid", pcode__QGrid);
  registerTypePublic("QGridLayout", pcode__QGridLayout);
  registerTypePublic("QGridView", pcode__QGridView);
  registerTypePublic("QGroupBox", pcode__QGroupBox);
  registerTypePublic("QGuardedPtr", pcode__QGuardedPtr);
  registerTypePublic("QHBox", pcode__QHBox);
  registerTypePublic("QHBoxLayout", pcode__QHBoxLayout);
  registerTypePublic("QHButtonGroup", pcode__QHButtonGroup);
  registerTypePublic("QHeader", pcode__QHeader);
  registerTypePublic("QHebrewCodec", pcode__QHebrewCodec);
  registerTypePublic("QHGroupBox", pcode__QHGroupBox);
  registerTypePublic("QHideEvent", pcode__QHideEvent);
  registerTypePublic("QHostAddress", pcode__QHostAddress);
  registerTypePublic("QHttp", pcode__QHttp);
  registerTypePublic("QHttpHeader", pcode__QHttpHeader);
  registerTypePublic("QHttpRequestHeader", pcode__QHttpRequestHeader);
  registerTypePublic("QHttpResponseHeader", pcode__QHttpResponseHeader);
  registerTypePublic("QIconDrag", pcode__QIconDrag);
  registerTypePublic("QIconDragEvent", pcode__QIconDragEvent);
  registerTypePublic("QIconDragItem", pcode__QIconDragItem);
  registerTypePublic("QIconFactory", pcode__QIconFactory);
  registerTypePublic("QIconSet", pcode__QIconSet);
  registerTypePublic("QIconView", pcode__QIconView);
  registerTypePublic("QIconViewItem", pcode__QIconViewItem);
  registerTypePublic("QImage", pcode__QImage);
  registerTypePublic("QImageConsumer", pcode__QImageConsumer);
  registerTypePublic("QImageDecoder", pcode__QImageDecoder);
  registerTypePublic("QImageDrag", pcode__QImageDrag);
  registerTypePublic("QImageFormat", pcode__QImageFormat);
  registerTypePublic("QImageFormatPlugin", pcode__QImageFormatPlugin);
  registerTypePublic("QImageFormatType", pcode__QImageFormatType);
  registerTypePublic("QImageIO", pcode__QImageIO);
  registerTypePublic("QIMEvent", pcode__QIMEvent);
  registerTypePublic("QInputDialog", pcode__QInputDialog);
  registerTypePublic("QIntCache", pcode__QIntCache);
  registerTypePublic("QIntCacheIterator", pcode__QIntCacheIterator);
  registerTypePublic("QIntDict", pcode__QIntDict);
  registerTypePublic("QIntDictIterator", pcode__QIntDictIterator);
  registerTypePublic("QIntValidator", pcode__QIntValidator);
  registerTypePublic("QIODevice", pcode__QIODevice);
  registerTypePublic("QJisCodec", pcode__QJisCodec);
  registerTypePublic("QKbdDriverFactory", pcode__QKbdDriverFactory);
  registerTypePublic("QKbdDriverPlugin", pcode__QKbdDriverPlugin);
  registerTypePublic("QKeyEvent", pcode__QKeyEvent);
  registerTypePublic("QKeySequence", pcode__QKeySequence);
  registerTypePublic("QLabel", pcode__QLabel);
  registerTypePublic("QLayout", pcode__QLayout);
  registerTypePublic("QLayoutItem", pcode__QLayoutItem);
  registerTypePublic("QLayoutIterator", pcode__QLayoutIterator);
  registerTypePublic("QLCDNumber", pcode__QLCDNumber);
  registerTypePublic("QLibrary", pcode__QLibrary);
  registerTypePublic("QLineEdit", pcode__QLineEdit);
  registerTypePublic("QListBox", pcode__QListBox);
  registerTypePublic("QListBoxItem", pcode__QListBoxItem);
  registerTypePublic("QListBoxPixmap", pcode__QListBoxPixmap);
  registerTypePublic("QListBoxText", pcode__QListBoxText);
  registerTypePublic("QListView", pcode__QListView);
  registerTypePublic("QListViewItem", pcode__QListViewItem);
  registerTypePublic("QListViewItemIterator", pcode__QListViewItemIterator);
  registerTypePublic("QLocale", pcode__QLocale);
  registerTypePublic("QLocalFs", pcode__QLocalFs);
  registerTypePublic("QMacMime", pcode__QMacMime);
  registerTypePublic("QMacStyle", pcode__QMacStyle);
  registerTypePublic("QMainWindow", pcode__QMainWindow);
  registerTypePublic("QMap", pcode__QMap);
  registerTypePublic("QMapConstIterator", pcode__QMapConstIterator);
  registerTypePublic("QMapIterator", pcode__QMapIterator);
  registerTypePublic("QMemArray", pcode__QMemArray);
  registerTypePublic("QMenuBar", pcode__QMenuBar);
  registerTypePublic("QMenuData", pcode__QMenuData);
  registerTypePublic("QMessageBox", pcode__QMessageBox);
  registerTypePublic("QMetaObject", pcode__QMetaObject);
  registerTypePublic("QMetaProperty", pcode__QMetaProperty);
  registerTypePublic("QMimeSource", pcode__QMimeSource);
  registerTypePublic("QMimeSourceFactory", pcode__QMimeSourceFactory);
  registerTypePublic("QMotif", pcode__QMotif);
  registerTypePublic("QMotifDialog", pcode__QMotifDialog);
  registerTypePublic("QMotifPlusStyle", pcode__QMotifPlusStyle);
  registerTypePublic("QMotifStyle", pcode__QMotifStyle);
  registerTypePublic("QMotifWidget", pcode__QMotifWidget);
  registerTypePublic("QMouseDriverFactory", pcode__QMouseDriverFactory);
  registerTypePublic("QMouseDriverPlugin", pcode__QMouseDriverPlugin);
  registerTypePublic("QMouseEvent", pcode__QMouseEvent);
  registerTypePublic("QMoveEvent", pcode__QMoveEvent);
  registerTypePublic("QMovie", pcode__QMovie);
  registerTypePublic("QMutex", pcode__QMutex);
  registerTypePublic("QMutexLocker", pcode__QMutexLocker);
  registerTypePublic("QNetworkOperation", pcode__QNetworkOperation);
  registerTypePublic("QNetworkProtocol", pcode__QNetworkProtocol);
  registerTypePublic("QNPInstance", pcode__QNPInstance);
  registerTypePublic("QNPlugin", pcode__QNPlugin);
  registerTypePublic("QNPStream", pcode__QNPStream);
  registerTypePublic("QNPWidget", pcode__QNPWidget);
  registerTypePublic("QObject", pcode__QObject);
  registerTypePublic("QObjectCleanupHandler", pcode__QObjectCleanupHandler);
  registerTypePublic("QObjectList", pcode__QObjectList);
  registerTypePublic("QObjectListIterator", pcode__QObjectListIterator);
  registerTypePublic("QPaintDevice", pcode__QPaintDevice);
  registerTypePublic("QPaintDeviceMetrics", pcode__QPaintDeviceMetrics);
  registerTypePublic("QPainter", pcode__QPainter);
  registerTypePublic("QPaintEvent", pcode__QPaintEvent);
  registerTypePublic("QPair", pcode__QPair);
  registerTypePublic("QPalette", pcode__QPalette);
  registerTypePublic("QPen", pcode__QPen);
  registerTypePublic("QPicture", pcode__QPicture);
  registerTypePublic("QPixmap", pcode__QPixmap);
  registerTypePublic("QPixmapCache", pcode__QPixmapCache);
  registerTypePublic("QPlatinumStyle", pcode__QPlatinumStyle);
  registerTypePublic("QPNGImagePacker", pcode__QPNGImagePacker);
  registerTypePublic("QPocketPCStyle", pcode__QPocketPCStyle);
  registerTypePublic("QPoint", pcode__QPoint);
  registerTypePublic("QPointArray", pcode__QPointArray);
  registerTypePublic("QPopupMenu", pcode__QPopupMenu);
  registerTypePublic("QPrinter", pcode__QPrinter);
  registerTypePublic("QProcess", pcode__QProcess);
  registerTypePublic("QProgressBar", pcode__QProgressBar);
  registerTypePublic("QProgressDialog", pcode__QProgressDialog);
  registerTypePublic("QPtrCollection", pcode__QPtrCollection);
  registerTypePublic("QPtrDict", pcode__QPtrDict);
  registerTypePublic("QPtrDictIterator", pcode__QPtrDictIterator);
  registerTypePublic("QList", pcode__QList);
  registerTypePublic("QListIterator", pcode__QListIterator);
  registerTypePublic("QPtrQueue", pcode__QPtrQueue);
  registerTypePublic("QPtrStack", pcode__QPtrStack);
  registerTypePublic("QPtrVector", pcode__QPtrVector);
  registerTypePublic("QPushButton", pcode__QPushButton);
  registerTypePublic("QRadioButton", pcode__QRadioButton);
  registerTypePublic("QRangeControl", pcode__QRangeControl);
  registerTypePublic("QRect", pcode__QRect);
  registerTypePublic("QRegExp", pcode__QRegExp);
  registerTypePublic("QRegExpValidator", pcode__QRegExpValidator);
  registerTypePublic("QRegion", pcode__QRegion);
  registerTypePublic("QResizeEvent", pcode__QResizeEvent);
  registerTypePublic("QScreen", pcode__QScreen);
  registerTypePublic("QScrollBar", pcode__QScrollBar);
  registerTypePublic("QScrollView", pcode__QScrollView);
  registerTypePublic("QSemaphore", pcode__QSemaphore);
  registerTypePublic("QServerSocket", pcode__QServerSocket);
  registerTypePublic("QSessionManager", pcode__QSessionManager);
  registerTypePublic("QSettings", pcode__QSettings);
  registerTypePublic("QSGIStyle", pcode__QSGIStyle);
  registerTypePublic("QShowEvent", pcode__QShowEvent);
  registerTypePublic("QSignal", pcode__QSignal);
  registerTypePublic("QSignalMapper", pcode__QSignalMapper);
  registerTypePublic("QSimpleRichText", pcode__QSimpleRichText);
  registerTypePublic("QSize", pcode__QSize);
  registerTypePublic("QSizeGrip", pcode__QSizeGrip);
  registerTypePublic("QSizePolicy", pcode__QSizePolicy);
  registerTypePublic("QSjisCodec", pcode__QSjisCodec);
  registerTypePublic("QSlider", pcode__QSlider);
  registerTypePublic("QSocket", pcode__QSocket);
  registerTypePublic("QSocketDevice", pcode__QSocketDevice);
  registerTypePublic("QSocketNotifier", pcode__QSocketNotifier);
  registerTypePublic("QSound", pcode__QSound);
  registerTypePublic("QSpacerItem", pcode__QSpacerItem);
  registerTypePublic("QSpinBox", pcode__QSpinBox);
  registerTypePublic("QSplashScreen", pcode__QSplashScreen);
  registerTypePublic("QSplitter", pcode__QSplitter);
  registerTypePublic("QSql", pcode__QSql);
  registerTypePublic("QSqlCursor", pcode__QSqlCursor);
  registerTypePublic("QSqlDatabase", pcode__QSqlDatabase);
  registerTypePublic("QSqlDriver", pcode__QSqlDriver);
  registerTypePublic("QSqlDriverPlugin", pcode__QSqlDriverPlugin);
  registerTypePublic("QSqlEditorFactory", pcode__QSqlEditorFactory);
  registerTypePublic("QSqlError", pcode__QSqlError);
  registerTypePublic("QSqlField", pcode__QSqlField);
  registerTypePublic("QSqlFieldInfo", pcode__QSqlFieldInfo);
  registerTypePublic("QSqlForm", pcode__QSqlForm);
  registerTypePublic("QSqlIndex", pcode__QSqlIndex);
  registerTypePublic("QSqlPropertyMap", pcode__QSqlPropertyMap);
  registerTypePublic("QSqlQuery", pcode__QSqlQuery);
  registerTypePublic("QSqlRecord", pcode__QSqlRecord);
  registerTypePublic("QSqlRecordInfo", pcode__QSqlRecordInfo);
  registerTypePublic("QSqlResult", pcode__QSqlResult);
  registerTypePublic("QSqlSelectCursor", pcode__QSqlSelectCursor);
  registerTypePublic("QStatusBar", pcode__QStatusBar);
  registerTypePublic("QStoredDrag", pcode__QStoredDrag);
  registerTypePublic("QStrIList", pcode__QStrIList);
  registerTypePublic("QString", pcode__QString);
  registerTypePublic("QStringList", pcode__QStringList);
  registerTypePublic("QStrList", pcode__QStrList);
  registerTypePublic("QStrListIterator", pcode__QStrListIterator);
  registerTypePublic("QStyle", pcode__QStyle);
  registerTypePublic("QStyleFactory", pcode__QStyleFactory);
  registerTypePublic("QStyleOption", pcode__QStyleOption);
  registerTypePublic("QStylePlugin", pcode__QStylePlugin);
  registerTypePublic("QStyleSheet", pcode__QStyleSheet);
  registerTypePublic("QStyleSheetItem", pcode__QStyleSheetItem);
  registerTypePublic("QSyntaxHighlighter", pcode__QSyntaxHighlighter);
  registerTypePublic("Qt", pcode__Qt);
  registerTypePublic("QTab", pcode__QTab);
  registerTypePublic("QTabBar", pcode__QTabBar);
  registerTypePublic("QTabDialog", pcode__QTabDialog);
  registerTypePublic("QTable", pcode__QTable);
  registerTypePublic("QTableItem", pcode__QTableItem);
  registerTypePublic("QTableSelection", pcode__QTableSelection);
  registerTypePublic("QTabletEvent", pcode__QTabletEvent);
  registerTypePublic("QTabWidget", pcode__QTabWidget);
  registerTypePublic("QTextBrowser", pcode__QTextBrowser);
  registerTypePublic("QTextCodec", pcode__QTextCodec);
  registerTypePublic("QTextCodecPlugin", pcode__QTextCodecPlugin);
  registerTypePublic("QTextDecoder", pcode__QTextDecoder);
  registerTypePublic("QTextDrag", pcode__QTextDrag);
  registerTypePublic("QTextEdit", pcode__QTextEdit);
  registerTypePublic("QTextEncoder", pcode__QTextEncoder);
  registerTypePublic("QTextIStream", pcode__QTextIStream);
  registerTypePublic("QTextOStream", pcode__QTextOStream);
  registerTypePublic("QTextStream", pcode__QTextStream);
  registerTypePublic("QThread", pcode__QThread);
  registerTypePublic("QThreadStorage", pcode__QThreadStorage);
  registerTypePublic("QTime", pcode__QTime);
  registerTypePublic("QTimeEdit", pcode__QTimeEdit);
  registerTypePublic("QTimer", pcode__QTimer);
  registerTypePublic("QTimerEvent", pcode__QTimerEvent);
  registerTypePublic("QToolBar", pcode__QToolBar);
  registerTypePublic("QToolBox", pcode__QToolBox);
  registerTypePublic("QToolButton", pcode__QToolButton);
  registerTypePublic("QToolTip", pcode__QToolTip);
  registerTypePublic("QToolTipGroup", pcode__QToolTipGroup);
  registerTypePublic("QTranslator", pcode__QTranslator);
  registerTypePublic("QTranslatorMessage", pcode__QTranslatorMessage);
  registerTypePublic("QTsciiCodec", pcode__QTsciiCodec);
  registerTypePublic("QUriDrag", pcode__QUriDrag);
  registerTypePublic("QUrl", pcode__QUrl);
  registerTypePublic("QUrlInfo", pcode__QUrlInfo);
  registerTypePublic("QUrlOperator", pcode__QUrlOperator);
  registerTypePublic("QUuid", pcode__QUuid);
  registerTypePublic("QValidator", pcode__QValidator);
  registerTypePublic("QValueList", pcode__QValueList);
  registerTypePublic("QValueListConstIterator", pcode__QValueListConstIterator);
  registerTypePublic("QValueListIterator", pcode__QValueListIterator);
  registerTypePublic("QValueStack", pcode__QValueStack);
  registerTypePublic("QValueVector", pcode__QValueVector);
  registerTypePublic("QVariant", pcode__QVariant);
  registerTypePublic("QVBox", pcode__QVBox);
  registerTypePublic("QVBoxLayout", pcode__QVBoxLayout);
  registerTypePublic("QVButtonGroup", pcode__QVButtonGroup);
  registerTypePublic("QVGroupBox", pcode__QVGroupBox);
  registerTypePublic("QWaitCondition", pcode__QWaitCondition);
  registerTypePublic("QWhatsThis", pcode__QWhatsThis);
  registerTypePublic("QWheelEvent", pcode__QWheelEvent);
  registerTypePublic("QWidget", pcode__QWidget);
  registerTypePublic("QWidgetFactory", pcode__QWidgetFactory);
  registerTypePublic("QWidgetItem", pcode__QWidgetItem);
  registerTypePublic("QWidgetPlugin", pcode__QWidgetPlugin);
  registerTypePublic("QWidgetStack", pcode__QWidgetStack);
  registerTypePublic("QWindowsMime", pcode__QWindowsMime);
  registerTypePublic("QWindowsStyle", pcode__QWindowsStyle);
  registerTypePublic("QWizard", pcode__QWizard);
  registerTypePublic("QWMatrix", pcode__QWMatrix);
  registerTypePublic("QWorkspace", pcode__QWorkspace);
  registerTypePublic("QWSDecoration", pcode__QWSDecoration);
  registerTypePublic("QWSInputMethod", pcode__QWSInputMethod);
  registerTypePublic("QWSKeyboardHandler", pcode__QWSKeyboardHandler);
  registerTypePublic("QWSMouseHandler", pcode__QWSMouseHandler);
  registerTypePublic("QWSServer", pcode__QWSServer);
  registerTypePublic("QWSWindow", pcode__QWSWindow);
  registerTypePublic("QXmlAttributes", pcode__QXmlAttributes);
  registerTypePublic("QXmlContentHandler", pcode__QXmlContentHandler);
  registerTypePublic("QXmlDeclHandler", pcode__QXmlDeclHandler);
  registerTypePublic("QXmlDefaultHandler", pcode__QXmlDefaultHandler);
  registerTypePublic("QXmlDTDHandler", pcode__QXmlDTDHandler);
  registerTypePublic("QXmlEntityResolver", pcode__QXmlEntityResolver);
  registerTypePublic("QXmlErrorHandler", pcode__QXmlErrorHandler);
  registerTypePublic("QXmlInputSource", pcode__QXmlInputSource);
  registerTypePublic("QXmlLexicalHandler", pcode__QXmlLexicalHandler);
  registerTypePublic("QXmlLocator", pcode__QXmlLocator);
  registerTypePublic("QXmlNamespaceSupport", pcode__QXmlNamespaceSupport);
  registerTypePublic("QXmlParseException", pcode__QXmlParseException);
  registerTypePublic("QXmlReader", pcode__QXmlReader);
  registerTypePublic("QXmlSimpleReader", pcode__QXmlSimpleReader);

  
}
*/

QString interpreter::printableVariable(const char *acText)
{
  QString s = acText;
  s = s.simplified();

  // suffix
       if (s.endsWith("%")) s = s.left(s.length() - 1);
  else if (s.endsWith("#")) s = s.left(s.length() - 1);
  else if (s.endsWith("!")) s = s.left(s.length() - 1);
  else if (s.endsWith("$")) s = s.left(s.length() - 1);
  else if (s.endsWith("&")) s = s.left(s.length() - 1);
  else if (s.endsWith("@")) s = s.left(s.length() - 1);

  QString sName;
  QString sType; 
  QString sValue;
  int nType;

  // locals
  {    
    if (myLocalFrame.count()){

      local_frame_ *lf = myLocalFrame.last();
      if (lf){
         memory_variable2 *v = lf->localVars;

         if (v && v->first()){
            do {
              int nId = v->getId();

               sName = v->getName(nId);
               sValue = v->toQString(nId);
               nType = v->type(nId);

               switch(nType){
                   case pcode__QSTRING:
                   case pcode__CSTRING:
                   case pcode__LQSTRING:
                   case pcode__LCSTRING:
                   case pcode__VARIANT:
                    if (sValue.startsWith("\"") && sValue.length() > 2){
                        sValue = sValue.mid(1, sValue.length() - 2);
                        sValue = "<font color='blue'>\"</font>" + sValue + "<font color='blue'>\"</font>";
                    }
                    break;
                   default:
                    break;
               }
               sType = findTypes(nType);
               
               if (s == sName){
                  return sName + " = <b>" + sValue + " ";
               }

             } while (v->next());
         }
      }
    }
  }

  // globals
  {    
    memory_variable2 *v = getGlobalVar();

    if (v->first()){
      do {
        int nId = v->getId();

        sName = v->getName(nId);
        sValue = v->toQString(nId);
        nType = v->type(nId);

        switch(nType){
          case pcode__QSTRING:
          case pcode__CSTRING:
          case pcode__LQSTRING:
          case pcode__LCSTRING:
          case pcode__VARIANT:
             if (sValue.startsWith("\"") && sValue.length() > 2){
                 sValue = sValue.mid(1, sValue.length() - 2);
                 sValue = "<font color='blue'>\"</font>" + sValue + "<font color='blue'>\"</font>";
             }
             break;
           default:
             break;
        }
        sType = findTypes(nType);

        if (s == sName){
           return sName + " = <b>" + sValue + " ";
        }

      } while (v->next());
    }
  }

  return "";    
} 

void interpreter::fPROJECTFILE()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; t_cstring path; t_cstring filename; t_integer filesize; t_pointer data;
	myPcode->rd_ProjectFile(&c, &path, &filename, &filesize, &data);
  {
    QString s = getFilenameWithoutPath(filename);


    data = utility::eatUTF16DOM((char * ) data);

    bProject = true;

    projectfiles[s] = data;
    projectfiles2[s] = filesize;
    if (s.endsWith(".kbasic_form")){
      QString ss = (const char *) data;
      if (ss.contains("OpenOnRun = True", Qt::CaseInsensitive)){
        openonrun_forms[s] = s;
      }
    }

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__PROJECTFILE));
      CONSOLE pcodePrint(filename);

		  CONSOLE pcodePrintCR();
    }
#endif

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PROJECTFILE), " missing"));

	
}

void interpreter::fBREAKPOINT()
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



	t_pcode c; t_cstring file; t_integer line;

	myPcode->rd_BREAKPOINT(&c, &file, &line);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
	 	  CONSOLE pcodePrintPos(nPos);
		  CONSOLE pcodePrintOpc(pcode::pcode_(pcode__BREAKPOINT));
      CONSOLE pcodePrint(file);
      CONSOLE pcodePrint(" in ");
      CONSOLE pcodePrint(line);

		  CONSOLE pcodePrintCR();
    }
#endif

    QString s = file;
    s = s + QString("%1").arg(line);
    s = s.trimmed();
    breakpoints.insert(s, true);

 //   bool b = breakpoints.contains(s);
  //  b = b;

	} // } else return pcodeError(utility::con(pcode::pcode_(pcode__PROJECTFILE), " missing"));

	
}

const char * interpreter::loadProjectFile(QString sFile)
{
  const char *ac = (const char *) projectfiles[sFile];
  if (ac) return ac;

  return "";
}

t_pointer loadProjectFile(QString sFile, t_integer *nSize)
{
  return EXTERN_myInterpreter->loadProjectFile(sFile, nSize);
}

t_pointer interpreter::loadProjectFile(QString sFile, t_integer *nSize)
{
  t_pointer p = projectfiles[sFile];
  *nSize = projectfiles2[sFile];
  if (p) return p;

  return 0;
}


bool interpreter::hasBreakpoint(const char *file, int line)
{
  QString s = file;
  s = s + QString("%1").arg(line);
  return breakpoints.contains(s);
}

void interpreter::performStdin(QString s)
{
  if (s.startsWith("interpretContinue")){
    interpretContinue();
  } else if (s.startsWith("interpretStepIn")){
    interpretStepIn();
  } else if (s.startsWith("interpretStepOut")){
    interpretStepOut();

  } else if (s.startsWith("interpretStepOver")){

    int n = s.indexOf("interpretStepOver|");
    if (n >= 0){       
      n += QString("interpretStepOver|").length();
      int n2 = s.indexOf("|", n);
      QString sCurrentFile = s.mid(n, n2 - n);
      n = s.indexOf("|", n2 + 1);
      n2++;
      QString sLine = s.mid(n2, n - n2);

      interpretStepOver(sCurrentFile, sLine.toInt());
    }

  } else if (s.startsWith("interpretRunToCursor")){

    int n = s.indexOf("interpretRunToCursor|");
    if (n >= 0){       
      n += QString("interpretRunToCursor|").length();
      int n2 = s.indexOf("|", n);
      QString sCurrentFile = s.mid(n, n2 - n);
      n = s.indexOf("|", n2 + 1);
      n2++;
      QString sLine = s.mid(n2, n - n2);
      //QMessageBox::information(0, sCurrentFile, sLine);

      interpretRunToCursor(sCurrentFile, sLine.toInt());
    }

  } else if (s.startsWith("interpretAddBreakpoint")){

    int n = s.indexOf("interpretAddBreakpoint|");
    if (n >= 0){       
      n += QString("interpretAddBreakpoint|").length();
      int n2 = s.indexOf("|", n);
      QString sCurrentFile = s.mid(n, n2 - n);
      n = s.indexOf("|", n2 + 1);
      n2++;
      QString sLine = s.mid(n2, n - n2);
      //QMessageBox::information(0, sCurrentFile, sLine);

      interpretAddBreakpoint(sCurrentFile, sLine.toInt());
    }

  } else if (s.startsWith("interpretRemoveBreakpoint")){

    int n = s.indexOf("interpretRemoveBreakpoint|");
    if (n >= 0){       
      n += QString("interpretRemoveBreakpoint|").length();
      int n2 = s.indexOf("|", n);
      QString sCurrentFile = s.mid(n, n2 - n);
      n = s.indexOf("|", n2 + 1);
      n2++;
      QString sLine = s.mid(n2, n - n2);
      //QMessageBox::information(0, sCurrentFile, sLine);

      interpretRemoveBreakpoint(sCurrentFile, sLine.toInt());
    }

  } else if (s.startsWith("interpretUpdateBreakpoint")){

    int n = s.indexOf("interpretUpdateBreakpoint|");
    if (n >= 0){       
      n += QString("interpretUpdateBreakpoint|").length();
      int n2 = s.indexOf("|", n);
      QString sCurrentFile = s.mid(n, n2 - n);
      n = s.indexOf("|", n2 + 1);
      n2++;
      QStringList Lines = s.mid(n2, n - n2).split(",");
      //QMessageBox::information(0, sCurrentFile, sLine);

      interpretUpdateBreakpoint(sCurrentFile, Lines);
    }
  }
}

QString interpreter::getFilenameWithoutPath(QString s)
{       
  int i = s.lastIndexOf('\\');
  if (i == -1){
    i = s.lastIndexOf('/');
  }
  s = s.right(s.length() - i - 1);
  return s; 
}

memory_variable2 *SoftOpen_returnvar;

QString sChildControlParentOverwrite = "";

kb_form *interpreter::openForm(QString k, kb_form *parent_form, int x, int y, int h, int w, bool bOpenHidden, bool bOpenFullScreen, bool bOpenCentered, bool bOpenMaximized, bool bOpenMinimized, bool bOpenCenteredOnlyOnce, bool bOpenOnlyOnce, bool bOpenHiddenOnlyOnce)
{
  

  QString s = k;
  s += "00033";
  QString ss = k;
  ss += "00033";
  ss = "." + ss;

  static QByteArray a; a = s.toAscii();

  

  t_integer SoftOpen_classid = EXTERN_myInterpreter->myClass->getClassId(k);
  if (SoftOpen_classid == 0){
    QByteArray a; a = k.toAscii();
    EXTERN_myInterpreter->runtimeError( utility::con("Could not open form ", a.data()) ); 
    return 0;
  }

  ss = QString("%1").arg(SoftOpen_classid) + ss;
  t_integer SoftOpen_methodid = EXTERN_myInterpreter->myClass->getClassMethodId(SoftOpen_classid, s);
  t_cstring SoftOpen_signature = a.data();

  memory_variable2 *SoftOpen_returnvar_SAVE= SoftOpen_returnvar;
  
  FORMPARENT = parent_form;

  EXTERN_myInterpreter->fENTER_LOCAL2(SoftOpen_classid, SoftOpen_methodid);
  
  EXTERN_myInterpreter->callMethod(false, SoftOpen_classid, SoftOpen_methodid, SoftOpen_signature, &SoftOpen_returnvar);
  

  kb_form *f = (kb_form *) SoftOpen_returnvar->getBindingParentClassPointer();

  if (f){

    EXTERN_myInterpreter->kbasic_binding_setKbId(f, SoftOpen_returnvar, SoftOpen_classid, pcode___form);    

    memory_variable2 *v = EXTERN_myInterpreter->getVar(global);

    if (SoftOpen_returnvar){
      SoftOpen_returnvar->setBindingParentClassPointer(f);
      SoftOpen_returnvar->setBindingParentClassType(pcode___form);
      /*
      if (nCurrentFormId == 0){
        nCurrentFormId = forms2[k];
      }*/
      if (nCurrentFormId){
        v->setObject(nCurrentFormId, SoftOpen_returnvar, 0);
        f->nFormId = nCurrentFormId;
      }
    }

    f->setAttribute(Qt::WA_DeleteOnClose, false);

    if (FORMPARENT) f->setGeometry(x, y, w, h);
    if (bOpenHidden){
      f->METHOD_OpenHidden();

    } else if (bOpenFullScreen){
      f->METHOD_OpenFullScreen();
    
    } else if (bOpenMaximized){
      f->METHOD_OpenMaximized();
    
    } else if (bOpenMinimized){
      f->METHOD_OpenMinimized();
    
    } else if (bOpenCentered){
      f->METHOD_OpenCentered();
    
    } else if (bOpenCenteredOnlyOnce){
      f->METHOD_OpenCenteredOnlyOnce();
    
    } else if (bOpenOnlyOnce){
      f->METHOD_OpenOnlyOnce();
    
    } else if (bOpenHiddenOnlyOnce){
      f->METHOD_OpenHiddenOnlyOnce();
    
    } else {
      if (FORMPARENT == 0 && (w > 0 || h > 0)){
        f->METHOD_Open(x, y, w, h);
      } else if (FORMPARENT == 0 && (x > 0 || y > 0)){
        f->METHOD_Open(x, y);
      } else {
        f->METHOD_Open();
      }
    }

    FORMPARENT = 0;
  }

  if (SoftOpen_returnvar_SAVE != 0) SoftOpen_returnvar = SoftOpen_returnvar_SAVE;

  return f;

} 

void interpreter::fDIM_STATIC() 
{
#ifdef HAS_CONSOLE
	register int nPos = myPcode->getPos();
#endif



  t_pcode dim_static; t_cstring value; t_integer reference;

  myPcode->rd_STRING_LITERAL(&dim_static, &value, &reference);
  {

#ifdef HAS_CONSOLE
    if (!bSilent){
      CONSOLE pcodePrintSep("");
      CONSOLE pcodePrintPos(nPos);
      CONSOLE pcodePrintOpc(pcode::pcode_(pcode__DIM_STATIC));
      CONSOLE pcodePrint3(value);
//      CONSOLE pcodePrint2(value);
      //CONSOLE pcodePrint(reference);
      CONSOLE pcodePrintCR();
    }
#endif

    {
      stringliterals->declare(value/*utility::toString(reference)*/, reference);
      
    }

    

  } // } else return pcodeError(utility::con(pcode::pcode_(pcode__DIM_STATIC), " missing"));
}


