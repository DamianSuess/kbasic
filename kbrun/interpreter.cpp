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

/**
[EXPLANATION]
NAME: STACK
PRINTNAME: Stack
DESC:
SEEALSO:
*/
/**
[EXPLANATION]
NAME: BREAKPOINT
PRINTNAME: Breakpoint
DESC:
SEEALSO:
*/


#include <QPainter>


#include "interpreter.h"
#include "../kbshared/_err.h"

interpreter *EXTERN_myInterpreter;

QMap<QString,t_pointer> projectfiles;
QMap<QString,t_integer> projectfiles2;
QMap<QString,QLibrary*>ll;
QMap<QString,QString>openonrun_forms;

QMap<int,QString>forms;
QMap<QString,int>forms2;
QMap<QString,int>menubaritems;
QMap<QString,int>toolbaritems;

QMap<QString, QColor>colors_map;
QMap<QString, QTranslator*> tr_map;
QMap<QString, QFont>fonts_map;
QMap<QString, QPixmap>pixmaps_map;

extern QSqlDatabase CurrentDatabase;

QPainter *EXTERN_myQPainter;
bool bLockingCauseOfBinaryDrawing = false;
QPainter *SAVE = 0;
QString binary;
QPixmap *binaryPixmap = 0;



#include "../kbshared/_paint.h"

QString getPrimary(QSqlDatabase &db, QString sTable)
{
  QString sPrimary = "kbrecordid";

  QSqlIndex i = db.driver()->primaryIndex(sTable);
  if (i.count()){
    sPrimary = i.fieldName(0);
  }
  return sPrimary;
}

QString getPrimary(QString sTable)
{
  return getPrimary(CurrentDatabase, sTable);
}

interpreter::interpreter(screen *_myScreen)
{
  EXTERN_myInterpreter = this;

  myScreen = _myScreen;

  my_mainwindow = 0;
  my_qapplication = 0;

	myStack = new stack();
	myData = new data(); // DATA, READ, RESTORE
	myFunction = new function(myScreen, this);


  memset(&lpFunc, 0, sizeof(lpFunc));

  my_ontimer = new _ontimer(this);
  my_ontimer->connect( my_ontimer, SIGNAL(timeout()), my_ontimer, SLOT(onTimer()) );
  bOnTimer = false;
  nOnTimerPos = -1;
  nOnTimerIntervall = 0;
  
  lpFunc[pcode__CONNECT]   = &interpreter::fCONNECT;
  lpFunc[pcode__DISCONNECT]   = &interpreter::fDISCONNECT;

  lpFunc[pcode__BREAKPOINT]   = &interpreter::fBREAKPOINT;

  lpFunc[pcode__OPTION_KBASIC]   = &interpreter::fOPTION_KBASIC;
  lpFunc[pcode__NOP]   = &interpreter::fNOP;
  lpFunc[pcode__AND]   = &interpreter::fAND;
  lpFunc[pcode__OR]   = &interpreter::fOR;
  lpFunc[pcode__NOT]   = &interpreter::fNOT;
  lpFunc[pcode__POWER]   = &interpreter::fPOWER;
  lpFunc[pcode__XOR]   = &interpreter::fXOR;
  lpFunc[pcode__IMP]   = &interpreter::fIMP;
  lpFunc[pcode__EQV]   = &interpreter::fEQV;
  lpFunc[pcode__ADD]   = &interpreter::fADD;
  lpFunc[pcode__LIKE]   = &interpreter::fLIKE;
  lpFunc[pcode__SUB]   = &interpreter::fSUB;
  lpFunc[pcode__MUL]   = &interpreter::fMUL;
  lpFunc[pcode__DIV]   = &interpreter::fDIV;
  lpFunc[pcode__IDIV]   = &interpreter::fIDIV;
  lpFunc[pcode__MOD]   = &interpreter::fMOD;
  lpFunc[pcode__EQUAL]   = &interpreter::fEQUAL;
  lpFunc[pcode__IS]   = &interpreter::fIS;
  lpFunc[pcode__UNEQUAL]   = &interpreter::fUNEQUAL;
  lpFunc[pcode__GREATER]   = &interpreter::fGREATER;
  lpFunc[pcode__LESSER]   = &interpreter::fLESSER;
  lpFunc[pcode__GREATER_EQUAL]   = &interpreter::fGREATER_EQUAL;
  lpFunc[pcode__FOR_GREATER_EQUAL]   = &interpreter::fFOR_GREATER_EQUAL;
  lpFunc[pcode__LESSER_EQUAL]   = &interpreter::fLESSER_EQUAL;

  lpFunc[pcode__TRY]   = &interpreter::fTRY;
  lpFunc[pcode__ENDCATCH]   = &interpreter::fENDCATCH;

  lpFunc[pcode__KBASICDIR]   = &interpreter::fKBASICDIR;
  lpFunc[pcode__PRINTSCREEN]   = &interpreter::fPRINTSCREEN;

  //lpFunc[pcode__ADDDATE]   = &interpreter::fADDDATE;
  lpFunc[pcode__ADDDAYS]   = &interpreter::fADDDAYS;
  lpFunc[pcode__ADDMONTHS]   = &interpreter::fADDMONTHS;
  lpFunc[pcode__ADDYEARS]   = &interpreter::fADDYEARS;
  //lpFunc[pcode__SUBDATE]   = &interpreter::fSUBDATE;
  lpFunc[pcode__SUBDAYS]   = &interpreter::fSUBDAYS;
  lpFunc[pcode__SUBMONTHS]   = &interpreter::fSUBMONTHS;
  lpFunc[pcode__SUBYEARS]   = &interpreter::fSUBYEARS;
  //lpFunc[pcode__ADDTIME]   = &interpreter::fADDTIME;
  lpFunc[pcode__ADDHOURS]   = &interpreter::fADDHOURS;
  lpFunc[pcode__ADDMINUTES]   = &interpreter::fADDMINUTES;
  lpFunc[pcode__ADDSECONDS]   = &interpreter::fADDSECONDS;
  //lpFunc[pcode__SUBTIME]   = &interpreter::fSUBTIME;
  lpFunc[pcode__SUBHOURS]   = &interpreter::fSUBHOURS;
  lpFunc[pcode__SUBMINUTES]   = &interpreter::fSUBMINUTES;
  lpFunc[pcode__SUBSECONDS]   = &interpreter::fSUBSECONDS;

  lpFunc[pcode__DAYOFWEEK]   = &interpreter::fDAYOFWEEK;
  lpFunc[pcode__DAYOFYEAR]   = &interpreter::fDAYOFYEAR;
  lpFunc[pcode__DAYSINMONTH]   = &interpreter::fDAYSINMONTH;
  lpFunc[pcode__DAYSINYEAR]   = &interpreter::fDAYSINYEAR;
  lpFunc[pcode__WEEKNUMBER]   = &interpreter::fWEEKNUMBER;
  lpFunc[pcode__ISLEAPYEAR]   = &interpreter::fISLEAPYEAR;
  lpFunc[pcode__DIFFSECONDS]   = &interpreter::fDIFFSECONDS;
  lpFunc[pcode__ISDATEVALID]   = &interpreter::fISDATEVALID;
  lpFunc[pcode__ISTIMEVALID]   = &interpreter::fISTIMEVALID;
  lpFunc[pcode__ISDATETIMEVALID]   = &interpreter::fISDATETIMEVALID;
  lpFunc[pcode__DAYNAME]   = &interpreter::fDAYNAME;


  lpFunc[pcode__READBINARY]   = &interpreter::fREADBINARY;
  lpFunc[pcode__WRITEBINARY]   = &interpreter::fWRITEBINARY;
  lpFunc[pcode__SEEKBINARY]   = &interpreter::fSEEKBINARY;

  lpFunc[pcode__TRANSLATION]   = &interpreter::fTRANSLATION;
  lpFunc[pcode__SQL]   = &interpreter::fSQL;
  lpFunc[pcode__MENU]   = &interpreter::fMENU;

  lpFunc[pcode__MOV_ENUM]   = &interpreter::fMOV_ENUM;
  lpFunc[pcode__MOV_CONST]   = &interpreter::fMOV_CONST;
  lpFunc[pcode__MOV]   = &interpreter::fMOV;
  lpFunc[pcode__MOV_LCSTRING]   = &interpreter::fMOV_LCSTRING;
  lpFunc[pcode__MOV_RCSTRING]   = &interpreter::fMOV_RCSTRING;
  lpFunc[pcode__MOV_LQSTRING]   = &interpreter::fMOV_LQSTRING;
  lpFunc[pcode__MOV_RQSTRING]   = &interpreter::fMOV_RQSTRING;
  lpFunc[pcode__MOV_TYPE]   = &interpreter::fMOV_TYPE;
  lpFunc[pcode__STOP]   = &interpreter::fSTOP;
  lpFunc[pcode__END]   = &interpreter::fEND;
  lpFunc[pcode__DOEVENTS]   = &interpreter::fDOEVENTS;

  lpFunc[pcode__ENTER_LOCAL]   = &interpreter::fENTER_LOCAL;
  lpFunc[pcode__ENTER_PROPERTYGET]   = &interpreter::fENTER_PROPERTYGET;
  lpFunc[pcode__ENTER_PROPERTYSET]   = &interpreter::fENTER_PROPERTYSET;
  lpFunc[pcode__EXIT_LOCAL]   = &interpreter::fEXIT_LOCAL;

  lpFunc[pcode__DIM]   = &interpreter::fDIM;
  lpFunc[pcode__REDIM]   = &interpreter::fREDIM;
  lpFunc[pcode__DIM_STATIC]   = &interpreter::fDIM_STATIC;
  lpFunc[pcode__CONST]   = &interpreter::fCONST;
  lpFunc[pcode___DYNAMIC]   = &interpreter::f_DYNAMIC;
  lpFunc[pcode___STATIC]   = &interpreter::f_STATIC;
  lpFunc[pcode__DATA]   = &interpreter::fDATA;
  lpFunc[pcode__RESTORE]   = &interpreter::fRESTORE;
  lpFunc[pcode__READ]   = &interpreter::fREAD;
  lpFunc[pcode__ONERRORGOTO]   = &interpreter::fONERRORGOTO;
  lpFunc[pcode__ONERRORGOTORESUMENEXT]   = &interpreter::fONERRORGOTORESUMENEXT;
  lpFunc[pcode__RESUME]   = &interpreter::fRESUME;

  lpFunc[pcode__PUSH_POINTERPOINTER]   = &interpreter::fPUSH_POINTERPOINTER;
  lpFunc[pcode__STRCOMP]   = &interpreter::fSTRCOMP;


  lpFunc[pcode__STATEMENT]   = &interpreter::fSTATEMENT;
  lpFunc[pcode__STATEMENT_OUT]   = &interpreter::fSTATEMENT_OUT;
  lpFunc[pcode__STATEMENT_OVER]   = &interpreter::fSTATEMENT_OVER;
  lpFunc[pcode__STATEMENT_CURSOR]   = &interpreter::fSTATEMENT_CURSOR;

  lpFunc[pcode__CATCH]   = &interpreter::fCATCH;
  lpFunc[pcode__JMP]   = &interpreter::fJMP;

  lpFunc[pcode__LIBCALL]   = &interpreter::fLIBCALL;

  //lpFunc[pcode__CALL]   = &interpreter::fCALL;

  lpFunc[pcode__RETURN]   = &interpreter::fRETURN;

  //lpFunc[pcode__CALL_RETURN]   = &interpreter::fCALL_RETURN;

  lpFunc[pcode__CALLMETHOD]   = &interpreter::fCALLMETHOD;
  lpFunc[pcode__PUSH_NULL]   = &interpreter::fPUSH_NULL;
  lpFunc[pcode__PUSH_EMPTY]   = &interpreter::fPUSH_EMPTY;
  lpFunc[pcode__PUSH_ERROR]   = &interpreter::fPUSH_ERROR;
  lpFunc[pcode__PUSH_BOOLEAN]   = &interpreter::fPUSH_BOOLEAN;
  lpFunc[pcode__PUSH_QSTRING]   = &interpreter::fPUSH_QSTRING;
  lpFunc[pcode__PUSH_CSTRING]   = &interpreter::fPUSH_CSTRING;
  lpFunc[pcode__PUSH_BYTE]   = &interpreter::fPUSH_BYTE;
  lpFunc[pcode__PUSH_SHORT]   = &interpreter::fPUSH_SHORT;
  lpFunc[pcode__PUSH_INTEGER]   = &interpreter::fPUSH_INTEGER;
  lpFunc[pcode__PUSH_LONG]   = &interpreter::fPUSH_LONG;

  lpFunc[pcode__PUSH_SINGLE]   = &interpreter::fPUSH_SINGLE;
  lpFunc[pcode__PUSH_DOUBLE]   = &interpreter::fPUSH_DOUBLE;

  lpFunc[pcode__PUSH_CURRENCY]   = &interpreter::fPUSH_CURRENCY;
  lpFunc[pcode__PUSH_DATE]   = &interpreter::fPUSH_DATE;

  lpFunc[pcode__PUSH_ENUM]   = &interpreter::fPUSH_ENUM;
  lpFunc[pcode__PUSH_RETURNVAR]   = &interpreter::fPUSH_RETURNVAR;

  
  lpFunc[pcode__PROJECTFILE]   = &interpreter::fPROJECTFILE;

  lpFunc[pcode__PUSH_CONST]   = &interpreter::fPUSH_CONST;
  
  lpFunc[pcode__PUSH__binding_ME]   = &interpreter::fPUSH__binding_ME;
  lpFunc[pcode__PUSH__binding_PARENT]   = &interpreter::fPUSH__binding_PARENT;

  lpFunc[pcode__PUSH_ME]   = &interpreter::fPUSH_ME;
  lpFunc[pcode__PUSH_PARENT]   = &interpreter::fPUSH_PARENT;

  lpFunc[pcode__SET_ME]   = &interpreter::fSET_ME;
  lpFunc[pcode__binding_SET_ME]   = &interpreter::fbinding_SET_ME;
  

  lpFunc[pcode__MOV_ME]   = &interpreter::fMOV_ME;
  lpFunc[pcode__MOV_PARENT]   = &interpreter::fMOV_PARENT;
  
  lpFunc[pcode__binding_PUSH_ID]   = &interpreter::fbinding_PUSH_ID;
  lpFunc[pcode__PUSH_ID]   = &interpreter::fPUSH_ID;
  lpFunc[pcode__PUSH_BOOLEAN_ID]   = &interpreter::fPUSH_BOOLEAN_ID;

  lpFunc[pcode__PUSH_QSTRING_ID]   = &interpreter::fPUSH_QSTRING_ID;
  lpFunc[pcode__PUSH_LQSTRING_ID]   = &interpreter::fPUSH_LQSTRING_ID;
  lpFunc[pcode__PUSH_CSTRING_ID]   = &interpreter::fPUSH_CSTRING_ID;
  lpFunc[pcode__PUSH_LCSTRING_ID]   = &interpreter::fPUSH_LCSTRING_ID;

  lpFunc[pcode__PUSH_BYTE_ID]   = &interpreter::fPUSH_BYTE_ID;
  lpFunc[pcode__PUSH_SHORT_ID]   = &interpreter::fPUSH_SHORT_ID;
  lpFunc[pcode__PUSH_INTEGER_ID]   = &interpreter::fPUSH_INTEGER_ID;
  lpFunc[pcode__PUSH_LONG_ID]   = &interpreter::fPUSH_LONG_ID;

  lpFunc[pcode__PUSH_SINGLE_ID]   = &interpreter::fPUSH_SINGLE_ID;
  lpFunc[pcode__PUSH_DOUBLE_ID]   = &interpreter::fPUSH_DOUBLE_ID;

  lpFunc[pcode__PUSH_VARIANT_ID]   = &interpreter::fPUSH_VARIANT_ID;

//  lpFunc[pcode__PUSH_IDREF]   = &interpreter::fPUSH_IDREF;
  lpFunc[pcode__PUSH_IDREFVAL]   = &interpreter::fPUSH_IDREFVAL;
/*
//  lpFunc[pcode__PUSH_IDPOINTER]   = &interpreter::fPUSH_IDPOINTER;
  lpFunc[pcode__PUSH_BOOLEAN_IDPOINTER]   = &interpreter::fPUSH_BOOLEAN_IDPOINTER;
  lpFunc[pcode__PUSH_CSTRING_IDPOINTER]   = &interpreter::fPUSH_CSTRING_IDPOINTER;

  lpFunc[pcode__PUSH_INTEGER_IDPOINTER]   = &interpreter::fPUSH_INTEGER_IDPOINTER;
  lpFunc[pcode__PUSH_LONG_IDPOINTER]   = &interpreter::fPUSH_LONG_IDPOINTER;

  lpFunc[pcode__PUSH_SINGLE_IDPOINTER]   = &interpreter::fPUSH_SINGLE_IDPOINTER;
  lpFunc[pcode__PUSH_DOUBLE_IDPOINTER]   = &interpreter::fPUSH_DOUBLE_IDPOINTER;
*/

  lpFunc[pcode__CJMP]   = &interpreter::fCJMP;
  lpFunc[pcode__CJMP2]   = &interpreter::fCJMP2;
  lpFunc[pcode__CJMP3]   = &interpreter::fCJMP3;
  lpFunc[pcode__SYSTEM]   = &interpreter::fSYSTEM;

  lpFunc[pcode__SILENTMODE]   = &interpreter::fSILENTMODE;
  lpFunc[pcode__SEPARATOR]   = &interpreter::fSEPARATOR;

  lpFunc[pcode__OPTION_RANGE]   = &interpreter::fOPTION_RANGE;
  //lpFunc[pcode__OPTION_BASE]   = &interpreter::fOPTION_BASE;
//  lpFunc[pcode__OPTION_COMPARE]   = &interpreter::fOPTION_COMPARE;

  lpFunc[pcode__MOV_ISMISSING]   = &interpreter::fMOV_ISMISSING;
  lpFunc[pcode__MOV_BOOLEAN]   = &interpreter::fMOV_BOOLEAN;

  lpFunc[pcode__MOV_QSTRING]   = &interpreter::fMOV_QSTRING;
  lpFunc[pcode__MOV_CSTRING]   = &interpreter::fMOV_CSTRING;
  lpFunc[pcode__MOV_SINGLE]   = &interpreter::fMOV_SINGLE;
  lpFunc[pcode__MOV_DOUBLE]   = &interpreter::fMOV_DOUBLE;

  lpFunc[pcode__MOV_BYTE]   = &interpreter::fMOV_BYTE;
  lpFunc[pcode__MOV_SHORT]   = &interpreter::fMOV_SHORT;
  lpFunc[pcode__MOV_INTEGER]   = &interpreter::fMOV_INTEGER;
  lpFunc[pcode__MOV_LONG]   = &interpreter::fMOV_LONG;

  lpFunc[pcode__MOV_IDREF]   = &interpreter::fMOV_IDREF;
  lpFunc[pcode__MOV_IDREFVAL]   = &interpreter::fMOV_IDREFVAL;

  lpFunc[pcode__LBOUND]   = &interpreter::fLBOUND;
  lpFunc[pcode__UBOUND]   = &interpreter::fUBOUND;

  lpFunc[pcode__CHOOSE]   = &interpreter::fCHOOSE;
  lpFunc[pcode__SWITCH]   = &interpreter::fSWITCH;
  lpFunc[pcode__IIF]   = &interpreter::fIIF;
  lpFunc[pcode__MID2]   = &interpreter::fMID2;

  lpFunc[pcode__ONTIMERGOSUB]   = &interpreter::fONTIMERGOSUB;
  lpFunc[pcode__TIMER_ON]   = &interpreter::fTIMER_ON;
  lpFunc[pcode__TIMER_OFF]   = &interpreter::fTIMER_OFF;
  lpFunc[pcode__TIMER_STOP]   = &interpreter::fTIMER_STOP;

  lpFunc[pcode__BUILTIN]   = &interpreter::fBUILTIN;

  lpFunc[pcode__UTF8]   = &interpreter::fUTF8;
  lpFunc[pcode__UTF16]   = &interpreter::fUTF16;

  lpFunc[pcode__EOF_]   = &interpreter::fEOF;
  lpFunc[pcode__CLS]   = &interpreter::fCLS;
  lpFunc[pcode__LOCATE]   = &interpreter::fLOCATE;
  lpFunc[pcode__INPUT]   = &interpreter::fINPUT;
  lpFunc[pcode__INPUT2]   = &interpreter::fINPUT2;
  lpFunc[pcode__PRINT]   = &interpreter::fPRINT;
  lpFunc[pcode__LEN]   = &interpreter::fLEN;
  lpFunc[pcode__MID]   = &interpreter::fMID;
  lpFunc[pcode__MID2]   = &interpreter::fMID2;
  lpFunc[pcode__FRE]   = &interpreter::fFRE;
  lpFunc[pcode__VAL]   = &interpreter::fVAL;
  lpFunc[pcode__INT]   = &interpreter::fINT;
  lpFunc[pcode__RANDOMIZE]   = &interpreter::fRANDOMIZE;
  lpFunc[pcode__RND]   = &interpreter::fRND;
  lpFunc[pcode__CSRLIN]   = &interpreter::fCSRLIN;
  lpFunc[pcode__POS]   = &interpreter::fPOS;
  lpFunc[pcode__COLOR]   = &interpreter::fCOLOR;
  lpFunc[pcode__ABS]   = &interpreter::fABS;
  lpFunc[pcode__DATE]   = &interpreter::fDATE;
  lpFunc[pcode__TIME]   = &interpreter::fTIME;
  lpFunc[pcode__STRING2]   = &interpreter::fSTRING2;
  lpFunc[pcode__SPACE]   = &interpreter::fSPACE;
  lpFunc[pcode__INSTR]   = &interpreter::fINSTR;

  lpFunc[pcode__ENCODE]   = &interpreter::fENCODE;
  lpFunc[pcode__DECODE]   = &interpreter::fDECODE;
  
  lpFunc[pcode__LEFT]   = &interpreter::fLEFT;
  lpFunc[pcode__RIGHT]   = &interpreter::fRIGHT;
  lpFunc[pcode__UCASE]   = &interpreter::fUCASE;
  lpFunc[pcode__LCASE]   = &interpreter::fLCASE;
  lpFunc[pcode__LTRIM]   = &interpreter::fLTRIM;
  lpFunc[pcode__RTRIM]   = &interpreter::fRTRIM;
  lpFunc[pcode__TRIM]   = &interpreter::fTRIM;
  lpFunc[pcode__ASC]   = &interpreter::fASC;
  lpFunc[pcode__STR]   = &interpreter::fSTR;
  lpFunc[pcode__HEX]   = &interpreter::fHEX;
  lpFunc[pcode__OCT]   = &interpreter::fOCT;
  lpFunc[pcode__BIN]   = &interpreter::fBIN;
  lpFunc[pcode__CHR]   = &interpreter::fCHR;
  lpFunc[pcode__INKEY]   = &interpreter::fINKEY;
  lpFunc[pcode__SLEEP]   = &interpreter::fSLEEP;
  lpFunc[pcode__SHELL]   = &interpreter::fSHELL;
  lpFunc[pcode__CAST]   = &interpreter::fCAST;
  lpFunc[pcode__CLNG]   = &interpreter::fCLNG;
  lpFunc[pcode__CINT]   = &interpreter::fCINT;
  lpFunc[pcode__CSNG]   = &interpreter::fCSNG;
  lpFunc[pcode__CDBL]   = &interpreter::fCDBL;
  lpFunc[pcode__CCUR]   = &interpreter::fCCUR;
  lpFunc[pcode__CVAR]   = &interpreter::fCVAR;
  lpFunc[pcode__CBOOL]   = &interpreter::fCBOOL;
  lpFunc[pcode__CBYTE]   = &interpreter::fCBYTE;
  lpFunc[pcode__CDATE]   = &interpreter::fCDATE;
  lpFunc[pcode__RAD]   = &interpreter::fRAD;
  lpFunc[pcode__DEG]   = &interpreter::fDEG;
  lpFunc[pcode__ACS]   = &interpreter::fACS;
  lpFunc[pcode__ASN]   = &interpreter::fASN;
  lpFunc[pcode__ATN]   = &interpreter::fATN;
  lpFunc[pcode__COS]   = &interpreter::fCOS;
  lpFunc[pcode__EXP]   = &interpreter::fEXP;
  lpFunc[pcode__LOG]   = &interpreter::fLOG;
  lpFunc[pcode__LN]   = &interpreter::fLN;
  lpFunc[pcode__SGN]   = &interpreter::fSGN;
  lpFunc[pcode__FIX]   = &interpreter::fFIX;
  lpFunc[pcode__SIN]   = &interpreter::fSIN;
  lpFunc[pcode__SQR]   = &interpreter::fSQR;
  lpFunc[pcode__TAN]   = &interpreter::fTAN;
  lpFunc[pcode__FACT]   = &interpreter::fFACT;
  lpFunc[pcode__LOGB]   = &interpreter::fLOGB;
  lpFunc[pcode__FRAC]   = &interpreter::fFRAC;
  lpFunc[pcode__HYPOT]   = &interpreter::fHYPOT;
  lpFunc[pcode__MAX]   = &interpreter::fMAX;
  lpFunc[pcode__MIN]   = &interpreter::fMIN;
  lpFunc[pcode__SEC]   = &interpreter::fSEC;
  lpFunc[pcode__CHDIR]   = &interpreter::fCHDIR;
  lpFunc[pcode__RMDIR]   = &interpreter::fRMDIR;
  lpFunc[pcode__MKDIR]   = &interpreter::fMKDIR;
  lpFunc[pcode__BEEP]   = &interpreter::fBEEP;
  lpFunc[pcode__RESET]   = &interpreter::fRESET;
  lpFunc[pcode__FILES]   = &interpreter::fFILES;
  lpFunc[pcode__NAME]   = &interpreter::fNAME;
  lpFunc[pcode__KILL]   = &interpreter::fKILL;
  lpFunc[pcode__SEEK]   = &interpreter::fSEEK;
  lpFunc[pcode__SEEK2]   = &interpreter::fSEEK2;
  lpFunc[pcode__OPEN]   = &interpreter::fOPEN;
  lpFunc[pcode__OPEN2]   = &interpreter::fOPEN2;
  lpFunc[pcode__CLOSE]   = &interpreter::fCLOSE;
  lpFunc[pcode__CLOSEALL]   = &interpreter::fCLOSEALL;
  lpFunc[pcode__WRITE]   = &interpreter::fWRITE;
  lpFunc[pcode__LOF]   = &interpreter::fLOF;
  lpFunc[pcode__DATE2]   = &interpreter::fDATE2;
  lpFunc[pcode__SCREEN]   = &interpreter::fSCREEN;
  lpFunc[pcode__LINEINPUT]   = &interpreter::fLINEINPUT;
  lpFunc[pcode__NZ]   = &interpreter::fNZ;
  lpFunc[pcode__GET]   = &interpreter::fGET;
  lpFunc[pcode__GET2]   = &interpreter::fGET2;

  lpFunc[pcode__PEEK]   = &interpreter::fPEEK;
  lpFunc[pcode__POKE]   = &interpreter::fPOKE;

  lpFunc[pcode__COMPARE]   = &interpreter::fCOMPARE;
  
  lpFunc[pcode__CONTAINS]   = &interpreter::fCONTAINS;
  lpFunc[pcode__COUNT]   = &interpreter::fCOUNT;
  lpFunc[pcode__ENDSWITH]   = &interpreter::fENDSWITH;
  lpFunc[pcode__STARTSWITH]   = &interpreter::fSTARTSWITH;
  lpFunc[pcode__LEFTJUSTIFIED]   = &interpreter::fLEFTJUSTIFIED;
  lpFunc[pcode__RIGHTJUSTIFIED]   = &interpreter::fRIGHTJUSTIFIED;
  lpFunc[pcode__SECTION]   = &interpreter::fSECTION;
  lpFunc[pcode__SIMPLIFIED]   = &interpreter::fSIMPLIFIED;
  lpFunc[pcode__TRIMMED]   = &interpreter::fTRIMMED;
  lpFunc[pcode__REVERSED]   = &interpreter::fREVERSED;
  lpFunc[pcode__UNICODE]   = &interpreter::fUNICODE;

  lpFunc[pcode__PREPEND]   = &interpreter::fPREPEND;
  lpFunc[pcode__APPEND2]   = &interpreter::fAPPEND;
  lpFunc[pcode__REMOVE]   = &interpreter::fREMOVE;
  lpFunc[pcode__TRUNCATE]   = &interpreter::fTRUNCATE;
  lpFunc[pcode__INSERT]   = &interpreter::fINSERT;
  lpFunc[pcode__FILL]   = &interpreter::fFILL;

  lpFunc[pcode__PUT]   = &interpreter::fPUT;
  lpFunc[pcode__PUT2]   = &interpreter::fPUT2;
  lpFunc[pcode__INSTREV]   = &interpreter::fINSTREV;
  lpFunc[pcode__REPLACE]   = &interpreter::fREPLACE;
  lpFunc[pcode__SPLIT]   = &interpreter::fSPLIT;
  lpFunc[pcode__ROUND]   = &interpreter::fROUND;
  lpFunc[pcode__STRREVERSE]   = &interpreter::fSTRREVERSE;
  lpFunc[pcode__FIELD]   = &interpreter::fFIELD;
  lpFunc[pcode__SPC]   = &interpreter::fSPC;
  lpFunc[pcode__FILECOPY]   = &interpreter::fFILECOPY;
  lpFunc[pcode__CHDRIVE]   = &interpreter::fCHDRIVE;
  lpFunc[pcode__SETATTR]   = &interpreter::fSETATTR;
  lpFunc[pcode__ISDATE]   = &interpreter::fISDATE;
  lpFunc[pcode__ISEMPTY]   = &interpreter::fISEMPTY;
  lpFunc[pcode__ISNULL]   = &interpreter::fISNULL;
  lpFunc[pcode__ISNUMERIC]   = &interpreter::fISNUMERIC;
  lpFunc[pcode__ISMISSING]   = &interpreter::fISMISSING;
  lpFunc[pcode__ISARRAY]   = &interpreter::fISARRAY;
  lpFunc[pcode__ISOBJECT]   = &interpreter::fISOBJECT;
  lpFunc[pcode__ISERROR]   = &interpreter::fISERROR;
  lpFunc[pcode__ISBOOLEAN]   = &interpreter::fISBOOLEAN;
  lpFunc[pcode__ISSTRING]   = &interpreter::fISSTRING;
  lpFunc[pcode__ISSINGLE]   = &interpreter::fISSINGLE;
  lpFunc[pcode__ISDOUBLE]   = &interpreter::fISDOUBLE;
  lpFunc[pcode__ISBYTE]   = &interpreter::fISBYTE;
  lpFunc[pcode__ISSHORT]   = &interpreter::fISSHORT;
  lpFunc[pcode__ISINTEGER]   = &interpreter::fISINTEGER;
  lpFunc[pcode__ISLONG]   = &interpreter::fISLONG;
  /*
  lpFunc[pcode__ISINT16]   = &interpreter::fISINT16;
  lpFunc[pcode__ISINT32]   = &interpreter::fISINT32;
  lpFunc[pcode__ISINT64]   = &interpreter::fISINT64;
  lpFunc[pcode__ISUINT16]   = &interpreter::fISUINT16;
  lpFunc[pcode__ISUINT32]   = &interpreter::fISUINT32;
  lpFunc[pcode__ISUINT64]   = &interpreter::fISUINT64;
  */
  lpFunc[pcode__ISVARIANT]   = &interpreter::fISVARIANT;
  lpFunc[pcode__ISCURRENCY]   = &interpreter::fISCURRENCY;  

  lpFunc[pcode__LOC]   = &interpreter::fLOC;
  lpFunc[pcode__MINUTE]   = &interpreter::fMINUTE;
  lpFunc[pcode__MONTH]   = &interpreter::fMONTH;
  lpFunc[pcode__MSGBOX]   = &interpreter::fMSGBOX;
  lpFunc[pcode__NOW]   = &interpreter::fNOW;
  lpFunc[pcode__RGB]   = &interpreter::fRGB;
  lpFunc[pcode__SECOND]   = &interpreter::fSECOND;
  lpFunc[pcode__TIMER]   = &interpreter::fTIMER;

  lpFunc[pcode__ARRAY2]   = &interpreter::fARRAY2;
  lpFunc[pcode__COMMAND]   = &interpreter::fCOMMAND;
  lpFunc[pcode__CURDIR]   = &interpreter::fCURDIR;
  lpFunc[pcode__CVERR]   = &interpreter::fCVERR;

  lpFunc[pcode__DATEADD]   = &interpreter::fDATEADD;
  lpFunc[pcode__DATEDIFF]   = &interpreter::fDATEDIFF;
  lpFunc[pcode__DATEPART]   = &interpreter::fDATEPART;
  lpFunc[pcode__DATESERIAL]   = &interpreter::fDATESERIAL;
  lpFunc[pcode__DATEVALUE]   = &interpreter::fDATEVALUE;

  lpFunc[pcode__DAY]   = &interpreter::fDAY;
  lpFunc[pcode__DIR]   = &interpreter::fDIR;
  lpFunc[pcode__FILEATTR]   = &interpreter::fFILEATTR;
  lpFunc[pcode__FILEDATETIME]   = &interpreter::fFILEDATETIME;
  lpFunc[pcode__FILELEN]   = &interpreter::fFILELEN;
  lpFunc[pcode__FORMAT]   = &interpreter::fFORMAT;
  lpFunc[pcode__FREEFILE]   = &interpreter::fFREEFILE;
  lpFunc[pcode__GETATTR]   = &interpreter::fGETATTR;
  lpFunc[pcode__HOUR]   = &interpreter::fHOUR;
  lpFunc[pcode__INPUTBOX]   = &interpreter::fINPUTBOX;

  lpFunc[pcode__FORMATCURRENCY]   = &interpreter::fFORMATCURRENCY;
  lpFunc[pcode__FORMATDATETIME]   = &interpreter::fFORMATDATETIME;
  lpFunc[pcode__FORMATNUMBER]   = &interpreter::fFORMATNUMBER;
  lpFunc[pcode__FORMATPERCENT]   = &interpreter::fFORMATPERCENT;
  lpFunc[pcode__WEEKDAYNAME]   = &interpreter::fWEEKDAYNAME;
  lpFunc[pcode__MONTHNAME]   = &interpreter::fMONTHNAME;

  lpFunc[pcode__TIMESERIAL]   = &interpreter::fTIMESERIAL;
  lpFunc[pcode__TIMEVALUE]   = &interpreter::fTIMEVALUE;
  lpFunc[pcode__TYPENAME]   = &interpreter::fTYPENAME;
  lpFunc[pcode__WEEKDAY]   = &interpreter::fWEEKDAY;
  lpFunc[pcode__YEAR]   = &interpreter::fYEAR;
  lpFunc[pcode__POINT]   = &interpreter::fPOINT;
  lpFunc[pcode__SCREEN2]   = &interpreter::fSCREEN2;
  lpFunc[pcode__CIRCLE]   = &interpreter::fCIRCLE;
  lpFunc[pcode__DRAW]   = &interpreter::fDRAW;
  lpFunc[pcode__PCOPY]   = &interpreter::fPCOPY;
  lpFunc[pcode__PMAP]   = &interpreter::fPMAP;
  lpFunc[pcode__WIDTH]   = &interpreter::fWIDTH;
  lpFunc[pcode__PRESET]   = &interpreter::fPRESET;
  lpFunc[pcode__PSET]   = &interpreter::fPSET;
  lpFunc[pcode__PAINT]   = &interpreter::fPAINT;
  lpFunc[pcode__WINDOW]   = &interpreter::fWINDOW;
  lpFunc[pcode__LINE]   = &interpreter::fLINE;
  lpFunc[pcode__VIEWPRINT]   = &interpreter::fVIEWPRINT;
  lpFunc[pcode__VIEW]   = &interpreter::fVIEW;

  lpFunc[pcode__ARRAY]   = &interpreter::fARRAY;
  lpFunc[pcode__REGISTER_ARRAY]   = &interpreter::fREGISTER_ARRAY;
  lpFunc[pcode__TYPE]   = &interpreter::fTYPE;
//  lpFunc[pcode__STRUCTURE]   = &interpreter::fSTRUCTURE;
  lpFunc[pcode__ENUM]   = &interpreter::fENUM;
  lpFunc[pcode__ENUM_ELEMENT]   = &interpreter::fENUM_ELEMENT;
  lpFunc[pcode__CLASS]   = &interpreter::fCLASS;
  lpFunc[pcode__ERROR]   = &interpreter::fERROR;
  lpFunc[pcode__ERR]   = &interpreter::fERR;
  lpFunc[pcode__ERL]   = &interpreter::fERL;
  lpFunc[pcode__VARTYPE]   = &interpreter::fVARTYPE;
  lpFunc[pcode__TYPEOF]   = &interpreter::fTYPEOF;
  lpFunc[pcode__ERASE]   = &interpreter::fERASE;
  lpFunc[pcode__CLEAR]   = &interpreter::fCLEAR;
  lpFunc[pcode__STACKPOP]   = &interpreter::fSTACKPOP;
  
  lpFunc[pcode__binding_CLASSMETHOD]   = &interpreter::binding_callMethod;
  lpFunc[pcode__binding_CLASSPROPERTY]   = &interpreter::binding_callProperty;
  lpFunc[pcode__binding_CLASSSTATICPROPERTY]   = &interpreter::binding_callStaticProperty;
  lpFunc[pcode__binding_CLASSOPERATOR]   = &interpreter::binding_callOperator;
  lpFunc[pcode__binding_FUNCTIONOPERATOR]   = &interpreter::binding_callFunctionOperator;
  lpFunc[pcode__binding_FUNCTION]   = &interpreter::binding_callFunction;
  lpFunc[pcode__binding_CLASSSTATICMETHOD]   = &interpreter::binding_callStaticMethod;
//  lpFunc[pcode__CLASSMETHOD]   = &interpreter::callMethod;//bConstructor
  lpFunc[pcode__CLASSSTATICMETHOD]   = &interpreter::callStaticMethod;

  lpFunc[pcode__CLASS_BINDINGPARAM]   = &interpreter::fCLASS_BINDINGPARAM;


}

interpreter::~interpreter()
{

  QMap<QString, QLibrary*>::Iterator it9;
  for ( it9 = ll.begin(); it9 != ll.end(); ++it9 ) {
    delete *it9;
  }
  ll.clear();

  delete my_ontimer;

  QMap<QString, class_bindingconnect9*>::Iterator it2;
  for ( it2 = class_bindingconnect.begin(); it2 != class_bindingconnect.end(); ++it2 ) {
    class_bindingconnect9 *m = *it2;

    delete m;
  }
  
  class_bindingconnect.clear();
  class_bindingparam.clear();

  myLocalFrame.clear();
  array_offset2.clear();
  myArray2.clear();


	delete myStack;
	delete myData; // DATA, READ, RESTORE
	delete myFunction;
	//delete myTextbuffer;
	//delete myTextbuffer2;
}
/*
bool interpreter::setGUI(_mainwindow *m)
{
  
  my_mainwindow = m;
  if (my_mainwindow){
    setErrorWindow(m->getErrorWindow());
    setInfoWindow(m->getInfoWindow());
  }
  
  return true;
}*/

void interpreter::setGUIRuntime(QApplication *m)
{
  my_qapplication = m;
  
}

// ****************************
// * bool interpreter::pcodeError(char *acPcodeError)
// *
// * description:
// * prints an interpreter error
// *
// * interpreter_parameter:
// * the error messages to print
// *
// * return:
// * false
// ****************************
/**
[EXPLANATION]
NAME: PCODE ERROR
PRINTNAME: PCode Error
DESC:
SEEALSO:
*/
bool interpreter::pcodeError(const char *acPcodeError)
{
  static char acText[1024];

	if (bNoError){ // throw error only, if no other error occured before
  	sprintf(acText, "\ninternal error (pcode error): %s at %d\n", acPcodeError, myPcode->getPos());
  	CONSOLE printError(acText);
//    showError(acText);

  	bNoError = bRunPcode = bBreakpointAtPcode = false; // runtime error occured, stop interpretation of pcode
    qApp->exit();
	}
	return false;
}

/**
[EXPLANATION]
NAME: INTERNAL ERROR
PRINTNAME: Internal Error
DESC:
SEEALSO:
*/
bool interpreter::internalError(const char *acPcodeError)
{
  static char acText[1024];
	//char *acText = myTextbuffer->get(1024 + strlen(acPcodeError));

	if (bNoError){ // throw error only, if no other error occured before
  	sprintf(acText, "\ninternal error: %s at %d\n", acPcodeError, myPcode->getPos());
  	CONSOLE printError(acText);
//    showError(acText);

  	bNoError = bRunPcode = bBreakpointAtPcode = false; // runtime error occured, stop interpretation of pcode
    qApp->exit();
	}
	return false;
}


// ****************************
// * bool runtimeError(char *acRuntimeError)
// *
// * description:
// * prints a runtime error message
// *
// * interpreter_parameter:
// * char *acRuntimeError = the error message to print
// *
// * return:
// * dummy
// ****************************


/**
[EXPLANATION]
NAME: RUNTIME ERROR
PRINTNAME: Runtime Error
DESC:
SEEALSO:
*/
bool interpreter::runtimeError(const char *acRuntimeError, int nErrorNo, bool bRaise)
{
  static char acText[1024];
	//char *acText = myTextbuffer->get(1024 + strlen(acRuntimeError));

	if (bNoError){ // throw error only, if no other error occured before

#ifdef HAS_CONSOLE
    if (!bSilent) CONSOLE pcodePrintCR(); 
#endif

    sRuntimeErrorTxt = acRuntimeError;
    nRuntimeErrorPos1 = nRuntimeErrorPos;
    nRuntimeErrorNo = nErrorNo;
    
    nRuntimeErrorLine2 = nRuntimeErrorLine;
    sRuntimeErrorFile2 = sRuntimeErrorFile;

    if (myLocalFrame.last()->tryCatch == 0){
      int new_pc = myLocalFrame.last()->onErrorGotoPos;    
		  if (new_pc > 0){
			  myPcode->setPos(new_pc + myLocalFrame.last()->subPcodeOffset);
        if (bRaise){

          static QByteArray a; a = sRuntimeErrorFile.toAscii();
          err2->METHOD_Raise(nErrorNo, a.data(), acRuntimeError, false);
        }
			  //myStack->printStack();
			  return true;
		  } else if (new_pc == -1){ // resume next

        myPcode->setPos(nRuntimeErrorPos2 + myLocalFrame.last()->subPcodeOffset);
        
			  return true;
      } else { // delayed error message
        if (bNoError && bRunPcode){
  	      sprintf(acText, "\nruntime error: %s in line %d in file %s\n", acRuntimeError, nCurrentLine, acCurrentFile);
      //  	fprintf(stderr, acText);
  	      CONSOLE printError(acText);
    //      showError(acText);

  		    bNoError = bRunPcode = bBreakpointAtPcode = false; // runtime error occured, stop interpretation of pcode
          qApp->exit();
        }
		  }
    }
    if (myLocalFrame.last()->tryCatch == 999999) myLocalFrame.last()->tryCatch = nErrorNo;    
	}
	return false;
}


void _ontimer::onTimer()
{
  static bool bLock = false;

  if (bLock == false && my_interpreter->bOnTimer){
    bLock = true;
    int nPos = my_interpreter->myPcode->getPos() - my_interpreter->myLocalFrame.last()->subPcodeOffset;

    my_interpreter->myPcode->setPos(my_interpreter->nOnTimerPos + my_interpreter->myLocalFrame.last()->subPcodeOffset);    
    my_interpreter->pushStackInteger(nPos); // return pc for RETURN statement

    my_interpreter->interpret2(true); // execute

    
    bLock = false;    
  }
}


const QPixmap &interpreter_loadPixmap(QString fn)
{
  static QPixmap p;

  
  if (!(fn.contains("/") || fn.contains("\\"))){
    t_integer n = 0;
    t_pointer pp = EXTERN_myInterpreter->loadProjectFile(fn, &n);
    if (pp == 0){
      p = QPixmap();
      return p;
    }
    
    bool b = p.loadFromData((const uchar *) pp, n);
    if (b == false){
      
      p = QPixmap();
    }
    int nn = p.width();
    return p;

  } else {
    if (QFile::exists(fn)){
      p = QPixmap(fn);
      return p;
    }
  }

  p = QPixmap();
  return p;
  
}


const QString interpreter_loadFileAsString(QString fn)
{  
  
  if (!(fn.contains("/") || fn.contains("\\"))){
    return EXTERN_myInterpreter->loadProjectFile(fn);
  } else {
    return EXTERN_myInterpreter->loadProjectFile(fn);
  }

  return "";
  
}


QString highlightSQL(QString k)
{  
  QString s = k;

  static QSet<QString> set;

  if (set.count() == 0){
/*
      QList<QString> l;

      l << "ABORT" << "ABS" << "ABSOLUTE" << "ACCESS" << "ACTION" << "ADA" << "ADD" << "ADMIN" << "AFTER" << "AGGREGATE" << "ALIAS" << "ALL" << "ALLOCATE" << "ALTER" << "ANALYSE" << "ANALYZE" << "AND" << "ANY" << "ARE" << "ARRAY" << "AS" << "ASC" << "ASENSITIVE" << "ASSERTION" << "ASSIGNMENT" << "ASYMMETRIC" << "AT" << "ATOMIC" << "AUTHORIZATION" << "AVG" << "BACKWARD" << "BEFORE" << "BEGIN" << "BETWEEN" << "BIGINT" << "BINARY" << "BIT" << "BITVAR" << "BIT_LENGTH" << "BLOB" << "BOOLEAN" << "BOTH" << "BREADTH" << "BY" << "CACHE" << "CALL" << "CALLED" << "CARDINALITY" << "CASCADE" << "CASCADED" << "CASE" << "CAST" << "CATALOG" << "CATALOG_NAME" << "CHAIN" << "CHAR" << "CHARACTER" << "CHARACTERISTICS" << "CHARACTER_LENGTH" << "CHARACTER_SET_CATALOG" << "CHARACTER_SET_NAME" << "CHARACTER_SET_SCHEMA" << "CHAR_LENGTH" << "CHECK" << "CHECKED" << "CHECKPOINT" << "CLASS" << "CLASS_ORIGIN" << "CLOB" << "CLOSE" << "CLUSTER" << "COALESCE" << "COBOL" << "COLLATE" << "COLLATION" << "COLLATION_CATALOG" << "COLLATION_NAME" << "COLLATION_SCHEMA" << "COLUMN" << "COLUMN_NAME" << "COMMAND_FUNCTION" << "COMMAND_FUNCTION_CODE" << "COMMENT" << "COMMIT" << "COMMITTED" << "COMPLETION" << "CONDITION_NUMBER" << "CONNECT" << "CONNECTION" << "CONNECTION_NAME" << "CONSTRAINT" << "CONSTRAINTS" << "CONSTRAINT_CATALOG" << "CONSTRAINT_NAME" << "CONSTRAINT_SCHEMA" << "CONSTRUCTOR" << "CONTAINS" << "CONTINUE" << "CONVERSION" << "CONVERT" << "COPY" << "CORRESPONDING" << "COUNT" << "CREATE" << "CREATEDB" << "CREATEUSER" << "CROSS" << "CUBE" << "CURRENT" << "CURRENT_DATE" << "CURRENT_PATH" << "CURRENT_ROLE" << "CURRENT_TIME" << "CURRENT_TIMESTAMP" << "CURRENT_USER" << "CURSOR" << "CURSOR_NAME" << "CYCLE";
      l << "DATA" << "DATABASE" << "DATE" << "DATETIME_INTERVAL_CODE" << "DATETIME_INTERVAL_PRECISION" << "DAY" << "DEALLOCATE" << "DEC" << "DECIMAL" << "DECLARE" << "DEFAULT" << "DEFERRABLE" << "DEFERRED" << "DEFINED" << "DEFINER" << "DELETE" << "DELIMITER" << "DELIMITERS" << "DEPTH" << "DEREF" << "DESC" << "DESCRIBE" << "DESCRIPTOR" << "DESTROY" << "DESTRUCTOR" << "DETERMINISTIC" << "DIAGNOSTICS" << "DICTIONARY" << "ISCONNECT" << "DISPATCH" << "DISTINCT" << "DO" << "DOMAIN" << "DOUBLE" << "DROP" << "DYNAMIC" << "DYNAMIC_FUNCTION" << "DYNAMIC_FUNCTION_CODE";
      l << "EACH" << "ELSE" << "ENCODING" << "ENCRYPTED" << "END" << "END-EXEC" << "EQUALS" << "ESCAPE" << "EVERY" << "EXCEPT" << "EXCEPTION" << "EXCLUSIVE" << "EXEC" << "EXECUTE" << "EXISTING" << "EXISTS" << "EXPLAIN" << "EXTERNAL" << "EXTRACT" << "FALSE" << "FETCH" << "FINAL" << "FIRST" << "FLOAT" << "FOR" << "FORCE" << "FOREIGN" << "FORTRAN" << "FORWARD" << "FOUND" << "FREE" << "FREEZE" << "FROM" << "FULL" << "FUNCTION";
      l << "GENERAL" << "GENERATED" << "GET" << "GLOBAL" << "GO" << "GOTO" << "GRANT" << "GRANTED" << "GROUP" << "GROUPING" << "HANDLER" << "HAVING" << "HIERARCHY" << "HOLD" << "HOST" << "HOUR" << "IDENTITY" << "IGNORE" << "ILIKE" << "IMMEDIATE" << "IMMUTABLE" << "IMPLEMENTATION" << "IMPLICIT" << "IN" << "INCREMENT" << "INDEX" << "INDICATOR" << "INFIX" << "INHERITS" << "INITIALIZE" << "INITIALLY" << "INNER" << "INOUT" << "INPUT" << "INSENSITIVE" << "INSERT" << "INSTANCE" << "INSTANTIABLE" << "INSTEAD" << "INT" << "INTEGER" << "INTERSECT" << "INTERVAL" << "INTO" << "INVOKER" << "IS" << "ISNULL" << "ISOLATION" << "ITERATE";
      l << "JOIN" << "KKEY" << "KEY_MEMBER" << "KEY_TYPE" << "LANCOMPILER" << "LANGUAGE" << "LARGE" << "LAST" << "LATERAL" << "LEADING" << "LEFT" << "LENGTH" << "LESS" << "LEVEL" << "LIKE" << "LIMIT" << "LISTEN" << "LOAD" << "LOCAL" << "LOCALTIME" << "LOCALTIMESTAMP" << "LOCATION" << "LOCATOR" << "LOCK" << "LOWER" << "MAP" << "MATCH" << "MAX" << "MAXVALUE" << "MESSAGE_LENGTH" << "MESSAGE_OCTET_LENGTH" << "MESSAGE_TEXT" << "METHOD" << "MIN" << "MINUTE" << "MINVALUE" << "MOD" << "MODE" << "MODIFIES" << "MODIFY" << "MODULE" << "MONTH" << "MORE" << "MOVE" << "MUMPS" << "NAME" << "NAMES" << "NATIONAL" << "NATURAL" << "NCHAR" << "NCLOB" << "NEW" << "NEXT" << "NO" << "NOCREATEDB" << "NOCREATEUSER" << "NONE" << "NOT" << "NOTHING" << "NOTIFY" << "NOTNULL" << "NULL" << "NULLABLE" << "NULLIF" << "NUMBER" << "NUMERIC";
      l << "OBJECT" << "OCTET_LENGTH" << "OF" << "OFF" << "OFFSET" << "OIDS" << "OLD" << "ON" << "ONLY" << "OPEN" << "OPERATION" << "OPERATOR" << "OPTION" << "OPTIONS" << "OR" << "ORDER" << "ORDINALITY" << "OUT" << "OUTER" << "OUTPUT" << "OVERLAPS" << "OVERLAY" << "OVERRIDING" << "OWNER" << "PAD" << "PARAMETER" << "PARAMETERS" << "PARAMETER_MODE" << "PARAMETER_NAME" << "PARAMETER_ORDINAL_POSITION" << "PARAMETER_SPECIFIC_CATALOG" << "PARAMETER_SPECIFIC_NAME" << "PARAMETER_SPECIFIC_SCHEMA" << "PARTIAL" << "PASCAL" << "PASSWORD" << "PATH" << "PENDANT" << "PLACING" << "PLI" << "POSITION" << "POSTFIX" << "PRECISION" << "PREFIX" << "PREORDER" << "PREPARE" << "PRESERVE" << "PRIMARY" << "PRIOR" << "PRIVILEGES" << "PROCEDURAL" << "PROCEDURE" << "PUBLIC" << "READ" << "READS" << "REAL" << "RECHECK" << "RECURSIVE" << "REF" << "REFERENCES" << "REFERENCING" << "REINDEX" << "RELATIVE" << "RENAME" << "REPEATABLE" << "REPLACE" << "RESET" << "RESTRICT" << "RESULT" << "RETURN" << "RETURNED_LENGTH" << "RETURNED_OCTET_LENGTH" << "RETURNED_SQLSTATE" << "RETURNS" << "REVOKE" << "RIGHT" << "ROLE" << "ROLLBACK" << "ROLLUP" << "ROUTINE" << "ROUTINE_CATALOG" << "ROUTINE_NAME" << "ROUTINE_SCHEMA" << "ROW" << "ROWS" << "ROW_COUNT" << "RULE";
      l << "SAVEPOINT" << "SCALE" << "SCHEMA" << "SCHEMA_NAME" << "SCOPE" << "SCROLL" << "SEARCH" << "SECOND" << "SECTION" << "SECURITY" << "SELECT" << "SELF" << "SENSITIVE" << "SEQUENCE" << "SERIALIZABLE" << "SERVER_NAME" << "SESSION" << "SESSION_USER" << "SET" << "SETOF" << "SETS" << "SHARE" << "SHOW" << "SIMILAR" << "SIMPLE" << "SIZE" << "SMALLINT" << "SOME" << "SOURCE" << "SPACE" << "SPECIFIC" << "SPECIFICTYPE" << "SPECIFIC_NAME" << "SQL" << "SQLCODE" << "SQLERROR" << "SQLEXCEPTION" << "SQLSTATE" << "SQLWARNING" << "STABLE" << "START" << "STATE" << "STATEMENT" << "STATIC" << "STATISTICS" << "STDIN" << "STDOUT" << "STORAGE" << "STRICT" << "STRUCTURE" << "STYLE" << "SUBCLASS_ORIGIN" << "SUBLIST" << "SUBSTRING" << "SUM" << "SYMMETRIC" << "SYSID" << "SYSTEM" << "SYSTEM_USER";
      l << "TABLE" << "TABLE_NAME" << "TEMP" << "TEMPLATE" << "TEMPORARY" << "TERMINATE" << "THAN" << "THEN" << "TIME" << "TIMESTAMP" << "TIMEZONE_HOUR" << "TIMEZONE_MINUTE" << "TO" << "TOAST" << "TRAILING" << "TRANSACTION" << "TRANSACTIONS_COMMITTED" << "TRANSACTIONS_ROLLED_BACK" << "TRANSACTION_ACTIVE" << "TRANSFORM" << "TRANSFORMS" << "TRANSLATE" << "TRANSLATION" << "TREAT" << "TRIGGER" << "TRIGGER_CATALOG" << "TRIGGER_NAME" << "TRIGGER_SCHEMA" << "TRIM" << "TRUE" << "TRUNCATE" << "TRUSTED" << "TYPE" << "UNCOMMITTED" << "UNDER" << "UNENCRYPTED" << "UNION" << "UNIQUE" << "UNKNOWN" << "UNLISTEN" << "UNNAMED" << "UNNEST" << "UNTIL" << "UPDATE" << "UPPER" << "USAGE" << "USER" << "USER_DEFINED_TYPE_CATALOG" << "USER_DEFINED_TYPE_NAME" << "USER_DEFINED_TYPE_SCHEMA" << "USING";
      l << "VACUUM" << "VALID" << "VALIDATOR" << "VALUE" << "VALUES" << "VARCHAR" << "VARIABLE" << "VARYING" << "VERBOSE" << "VERSION" << "VIEW" << "VOLATILE" << "WHEN" << "WHENEVER" << "WHERE" << "WITH" << "WITHOUT" << "WORK" << "WRITE" << "YEAR" << "ZONE";
      l << "ASC";

      qSort(l);  

      while(l.count()){
        set << l.takeLast();
      }*/
  }
  if (k.isEmpty()) return s;
/*
  s = s.replace("kbrecordid", "?kb#ädidrocer#");

  foreach(QString q, set){
    if (k.contains(q, Qt::CaseInsensitive)){
      s = s.replace(q, "<b>" + q + "</b>", Qt::CaseInsensitive);
    }
  }

  s = s.replace("?kb#ädidrocer#", "kbrecordid");
*/
  return s;
}


interpreter_parameter *interpreter::popStack(int *nestatics)
{
  

  interpreter_parameter *p = new interpreter_parameter();

  if (nestatics) *nestatics = 0;
 	p->pcodeType = myStack->popPCode();
  switch (p->pcodeType){

		case pcode__BOOLEAN_POINTER: 	p->pointer_ = myStack->popAddress(); return p;

 		case pcode__CSTRING_POINTER: 	p->pointer_ = myStack->popAddress(); return p;

    case pcode__INTEGER_POINTER:  p->pointer_ = myStack->popAddress(); return p;
    case pcode__LONG_POINTER: 		p->pointer_ = myStack->popAddress(); return p;

		case pcode__SINGLE_POINTER: 	p->pointer_ = myStack->popAddress(); return p;
		case pcode__DOUBLE_POINTER: 	p->pointer_ = myStack->popAddress(); return p;


		case pcode__BOOLEAN: 	p->boolean_ = myStack->popBoolean();  return p;

 		case pcode__QSTRING: 	
      {
      t_qstring ss = myStack->popQString(); 
      if (ss == 0){
        
        p->string_ = "";
      } else {
        p->string_ = *ss;
      }
      p->qstring_ = &p->string_;
      return p;
      }

 		case pcode__CSTRING: 	
      p->cstring_ = myStack->popCString(); return p;

 		case pcode__EQSTRING:
      if (nestatics){
        *nestatics = myStack->popQStringId();
			  p->string_ = *estatics->getQString(*nestatics, 0);
        p->qstring_ = &p->string_;
			  p->pcodeType = pcode__QSTRING;
        estatics->undeclare(*nestatics);
			  return p;
      } else {
        {
          int nId = myStack->popQStringId();
			    p->string_ = *estatics->getQString(nId, 0);
          p->qstring_ = &p->string_;
			    p->pcodeType = pcode__QSTRING;
          estatics->undeclare(nId);
          return p;
        }

      }

 		case pcode__ECSTRING:
      if (nestatics){
        *nestatics = myStack->popCStringId();
        char *ac = estatics->getCString(*nestatics, 0);
        int n = strlen(ac) + 1;
        p->cstring_ = (char *) malloc(n);
        memcpy(p->cstring_, ac, n);
			  p->pcodeType = pcode__CSTRING;
        estatics->undeclare(*nestatics);
			  return p;
      } else {
        {
          int nId = myStack->popCStringId();
          char *ac = estatics->getCString(nId, 0);
          int n = strlen(ac) + 1;
          p->cstring_ = (char *) malloc(n);
          memcpy(p->cstring_, ac, n);
			    p->pcodeType = pcode__CSTRING;
          estatics->undeclare(nId);
			    return p;
        }

      }

    case pcode__BYTE:  p->byte_ = myStack->popByte(); return p;
    case pcode__SHORT:  p->short_ = myStack->popShort(); return p;
    case pcode__INTEGER:  p->integer_ = myStack->popInteger(); return p;
    case pcode__LONG: 		p->long_ = myStack->popLong(); 	 return p;

		case pcode__SINGLE: 	p->single_ = myStack->popSingle();  return p;
		case pcode__DOUBLE: 	p->double_ = myStack->popDouble();  return p;

    case pcode__CURRENCY:  p->currency_ = myStack->popCurrency(); return p;

    case pcode__DATE:  p->date_ = myStack->popDate(); return p;
 		
    case pcode__ERROR:  p->integer_ = myStack->popError(); return p;

    case pcode__OBJECT:
			{
        memory_variable2 *v;
        bool b44 = myStack->popBoolean();
        bool memory_variable2_ = myStack->popBoolean();
        
        if (b44){
        } else {
          if (memory_variable2_){
            p->pointer_ = v = (memory_variable2 *) myStack->popPointer();
            if (p->pointer_){
              p->pointer_ = (v->getBindingParentClassPointer());
              p->pcodeType = v->getBindingParentClassType();
            }
          }
        }


        return p;
      }

 		case pcode__ID:
			{
        internalError("wrong PCODE on stack for MOV");
			}
			return p;

		// binding
		default:
      bool b44 = myStack->popBoolean();
      bool memory_variable2 = myStack->popBoolean();
  		p->pointer_ = myStack->popPointer();   

      return p;

  }

	return 0;
}


void interpreter::pushStack(interpreter_parameter *p)
{
  

	static int nId = 0;
  
  switch (p->pcodeType){
    
		case pcode__BOOLEAN: 	myStack->pushBoolean(p->boolean_);  delete p; return;

 		case pcode__QSTRING:
	 	  nId = estatics->declare(pcode__QSTRING, 0, false, false);
 		  estatics->setQString(nId, p->qstring_, 0);
 		  myStack->pushEQString(nId);
			delete p; return;

 		case pcode__CSTRING:
	 	  nId = estatics->declare(pcode__CSTRING, 0, false, false);
 		  estatics->setCString(nId, p->cstring_, 0, 0);
 		  myStack->pushECString(nId);
			delete p; return;
 

    case pcode__BYTE:  myStack->pushByte(p->byte_); delete p; return;
    case pcode__SHORT:  myStack->pushShort(p->short_); delete p; return;
    case pcode__INTEGER:  myStack->pushInteger(p->integer_); delete p; return;
    case pcode__LONG: 		myStack->pushLong(p->long_); 	 delete p; return;

		case pcode__SINGLE: 	myStack->pushSingle(p->single_);  delete p; return;
		case pcode__DOUBLE: 	myStack->pushDouble(p->double_);  delete p; return;

    case pcode__CURRENCY:  myStack->pushCurrency(p->currency_); delete p; return;

    case pcode__DATE:  myStack->pushDate(p->date_); delete p; return;

    case pcode__VARIANT:  
      
      switch (p->variant_.nType){
        
		    case pcode__BOOLEAN: 	myStack->pushBoolean(p->variant_.boolean_);  delete p; return;

 		    case pcode__QSTRING:
	 	      nId = estatics->declare(pcode__QSTRING, 0, false, false);
 		      estatics->setQString(nId, p->variant_.qstring_, 0);
 		      myStack->pushEQString(nId);
			    delete p; return;

 		    case pcode__CSTRING:
	 	      nId = estatics->declare(pcode__CSTRING, 0, false, false);
 		      estatics->setCString(nId, p->variant_.cstring_, 0, 0);
 		      myStack->pushECString(nId);
			    delete p; return;


        case pcode__BYTE:  myStack->pushByte(p->variant_.byte_); delete p; return;
        case pcode__SHORT:  myStack->pushShort(p->variant_.short_); delete p; return;
        case pcode__INTEGER:  myStack->pushInteger(p->variant_.integer_); delete p; return;
        case pcode__LONG: 		myStack->pushLong(p->variant_.long_); 	 delete p; return;

		    case pcode__SINGLE: 	myStack->pushSingle(p->variant_.single_);  delete p; return;
		    case pcode__DOUBLE: 	myStack->pushDouble(p->variant_.double_);  delete p; return;

        case pcode__CURRENCY:  myStack->pushCurrency(p->variant_.currency_); delete p; return;

        case pcode__DATE:  myStack->pushDate(p->variant_.date_); delete p; return;

		    default:
          if (p->variant_.pointer_ == 0){
            myStack->pushPointer(pcode__OBJECT, 0, true, false); 
            delete p; 
          } else {
            myStack->pushPointer(p->pcodeType, p->variant_.pointer_, true, false);
            delete p; 
          }


          return;
      }
      break;

		default:
      if (p->pointer_ == 0){
        myStack->pushPointer(p->pcodeType, 0, true, false); 
        delete p; 
      } else { 
        myStack->pushPointer(p->pcodeType, p->pointer_, true, false);
        delete p; 
      }
      return;
  }

	
	return;

}