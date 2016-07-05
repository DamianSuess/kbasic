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
#ifndef INTERPRETER_H
#define INTERPRETER_H



#include <math.h>
#include <string.h>

#include <qtimer.h>

#include <QFile>
#include <QMap>


#include "../kbshared/typedef.h"

#include "stack.h"
#include "data.h"
#include "parser.h"


#include "utility.h"
#include "../kbshared/console.h"

#include "interpreter_builtin_function.h"


#include "memory_gc.h"

#include "memory_class2.h"
#include "memory_variable2.h"
#include "memory_const2.h"
#include "memory_stringliteral.h"
#include "memory_sub.h"
#include "memory_enum.h"
#include "memory_type.h"


class screen;
class browser;

extern QString kbNullQString;


class _mainwindow;
class kberr;

extern QMap<QString,t_pointer> projectfiles;
extern QMap<QString,t_integer> projectfiles2;
extern QMap<QString,QString> openonrun_forms;



struct local_frame_{
public:
  memory_variable2 *localVars;
	int subPcodeOffset;
	int onErrorGotoPos;
	int tryCatch;
  int return_pos;	
  bool bGlobal;
  char acName[512];
};

struct connect_{
public:
  t_pointer vSender;
	int nSignal;
  bool bSenderBinding;

  t_pointer vReceiver;
  int nSlot;	
  bool bReceiverBinding;
};

/*
struct class_bindingparam_{
public:
	char classmethod[MAX_IDENTIFIER * 3];
	int identifier;
};
*/


class _ontimer : public QTimer
{
  Q_OBJECT
public:
  _ontimer(interpreter *i) : QTimer(0)
  {
    my_interpreter = i;
  }

public slots:
void onTimer();
private:
  interpreter *my_interpreter;
};



class interpreter : QObject {
  Q_OBJECT
public:
	interpreter(screen *myScreen = 0);
	~interpreter();

  void setGUIRuntime(QApplication *my_qapplication);  

 void kbasic_binding_setKbId(void *p, memory_variable2 *v, t_integer identifier, t_integer type);


  const char *loadProjectFile(QString sFile);
  t_pointer loadProjectFile(QString sFile, t_integer *nSize);

  static QString getFilenameWithoutPath(QString s);


	bool interpret(pcode *p, bool bSilent, bool bDebug, bool bDebugAtBeginning, bool bCalledByIDE);

  void interpretContinue();
  void interpretStepIn();
	void interpretStepOut();
	void interpretStepOver(QString file, t_integer line);
	void interpretRunToCursor(QString file, t_integer line);

	void interpretAddBreakpoint(QString file, t_integer line);
	void interpretRemoveBreakpoint(QString file, t_integer line);
  void interpretUpdateBreakpoint(QString file, QStringList Lines);

  void fENTER_LOCAL2  	(t_integer SoftOpen_classid = 0, t_integer SoftOpen_methodid = 0);
  void fENTER_LOCAL  	();
	bool callMethod(bool bConstructor, t_integer SoftOpen_classid = 0, t_integer SoftOpen_methodid = 0, t_cstring SoftOpen_signature = "", memory_variable2 **SoftOpen_returnvar = 0);

	void stop_interpret();

  bool isDebugMode() const;

  void interrupt_interpret();
  void continue_interpret(bool bStepIn = false);

	bool callLib(memory_variable2 *v, const char *lib, const char *function, int return_type, int count, const char *signature);

  void callSub(memory_variable2 *v, int identifier, const char *name, QList<int> *param, int return_type = pcode__VOID, interpreter_parameter *returner = 0);
	bool hasSub(memory_variable2 *v, int identifier, const char *name, QList<int> *param, int return_type = pcode__VOID);

	void callEvent(memory_variable2 *v, int identifier, const char *name, const char *group, const char *control, QList<int> *param, int return_type = pcode__VOID, interpreter_parameter *returner = 0, t_boolean *bReturnCode = 0);
	bool hasEvent(memory_variable2 *v, int identifier, const char *name, const char *group, const char *control, QList<int> *param, int return_type = pcode__VOID);
  
	interpreter_parameter *callFunction(memory_variable2 *v, int identifier, const char *name, QList<int> *param);
	bool hasFunction(memory_variable2 *v, int identifier, const char *name, QList<int> *param, int return_type);
  	
	void callSlot(memory_variable2 *v, int identifier, const char *name, QList<int> *param, int return_type = pcode__VOID);
	bool hasSlot(memory_variable2 *v, int identifier, const char *name, QList<int> *param, int return_type = pcode__VOID);
	

  bool EVENT_OnPaint(memory_variable2 *v3, int identifier2, const char *name, const char *group, QWidget *W, t_integer X, t_integer Y, t_integer Width, t_integer Height);


	void pushStack(interpreter_parameter *p);

  static kb_form *openForm(QString k, kb_form *parent_form = 0, int x = -1, int y = -1, int h = -1, int w = -1, bool bOpenHidden = false, bool bOpenFullScreen = false, bool bOpenCentered = false, bool bOpenMaximized = false, bool bOpenMinimized = false, bool bOpenCenteredOnlyOnce = false, bool bOpenOnlyOnce = false, bool bOpenHiddenOnlyOnce = false);

	void pushStackBoolean(t_boolean m);
	void pushStackInteger(t_integer m);
	void pushStackLong(t_long m);
	void pushStackQString(t_qstring m);
	void pushStackCString(t_cstring m);
	void pushStackDouble(t_double m);

	memory_variable2 *estatics;

  memory_class2 *myClass;
	bool callDestructor(int nClassId, int nMethodId, bool b);

	bool runtimeError(const char *acRuntimeError, int nErrorNo = 0, bool bRaise = true);

  QString printableVariable(const char *acText);

  function *myFunction;
	pcode *myPcode;

  bool bOnTimer;
  int nOnTimerPos;
  int nOnTimerIntervall;

 	bool interpret(bool bEvent = false);
	bool interpret2(bool bEvent = false, bool bConstructor = false, int nInterpretLen = -1);



	interpreter_parameter *popStack(int *nestatics = 0);

  inline t_boolean popStackBoolean();
  inline t_integer popStackInteger();
  inline t_long popStackLong();
  inline t_pointer popStackString(int *nestatics, t_pcode *p);
//  inline t_qstring popStackQString(int *nestatics);
  //inline t_cstring popStackCString(int *nestatics);
  inline t_double popStackDouble();

  inline t_currency popStackCurrency();
  inline t_date popStackDate();

  //inline t_pointer popStackBinding();

  stack *myStack;
  bool pcodeError(const char *acPcodeError);
  int gnestatics[interpreter__MAX_PARAM];

  inline memory_variable2 *getVar(t_scope n);

private:

  void performStdin(QString s);

  QMap<QString,bool>breakpoints;
  bool hasBreakpoint(const char *file, int line);
  QFile my_stdin;
  QFile debuginfo;

	
	bool internalError(const char *acRuntimeError);

  inline void info(int nPos, int nPcode, t_integer n);
  inline void infoCall(int nPos, int nPcode, t_integer n, t_integer n2);
  inline void infoCatch(int nPos, int nPcode, t_integer n, t_integer n2);
  inline void infoCatch2(int nPos, int nPcode, t_integer n);
  /*
  inline bool info(int nPos, int nPcode, t_uint32 n);
  inline bool info(int nPos, int nPcode, t_uint64 n);*/
  inline void info(int nPos, int nPcode, t_long l);
  inline void info(int nPos, int nPcode, t_double d);

  inline void info(int nPos, int nPcode, const char *ac = "");
  inline void info2(int nPos, int nPcode, const char *ac = "");
  inline void info3(int nPos, int nPcode);
  
	inline void info(int nPos, const char *ac, const char *s);
	inline void info(const char *ac, const char *s);
	inline void info(int nPos, const char *ac);

	bool printPcode ();

  
	void fTRANSLATION();
	void fSQL();
	void fMENU();

	void fOPTION_KBASIC();
	void fNOP();
	void fSTOP();
	void fEND();

	void fCMP();

	void fDIM();
	void fREDIM();
	void fARRAY();
	void fREGISTER_ARRAY();
	void fDIM_STATIC();
	void fJMP();
	void fCALL();
	void fLIBCALL();
	void fCATCH();
	void fCALLMETHOD();
	void fRETURN();
	//void fCALL_RETURN();
	//bool fCATCH_RETURN();



  //void fADDDATE();
  void fADDDAYS();
  void fADDMONTHS();
  void fADDYEARS();
  //void fSUBDATE();
  void fSUBDAYS();
  void fSUBMONTHS();
  void fSUBYEARS();
  //void fADDTIME();
  void fADDHOURS();
  void fADDMINUTES();
  void fADDSECONDS();
  //void fSUBTIME();
  void fSUBHOURS();
  void fSUBMINUTES();
  void fSUBSECONDS();


	void fDAYOFWEEK								();
	void fDAYOFYEAR								();
	void fDAYSINMONTH								();
	void fDAYSINYEAR								();
	void fWEEKNUMBER								();
	void fISLEAPYEAR								();
	void fDIFFDAY								();
	void fDIFFSECONDS								();
	void fISDATEVALID								();
	void fISTIMEVALID								();
	void fISDATETIMEVALID			();
	void fDAYNAME			();


	void fCONST();

	void fVER();
	void fKBASIC();

	void fSUB();
	void fDIV();
	void fLIKE();
	void fIDIV();
	void fMOD();
	void fMUL();
	void fADD();
	void fEQUAL();
	void fIS();
	void fUNEQUAL();
	void fGREATER();
	void fLESSER();
	void fGREATER_EQUAL();
	void fFOR_GREATER_EQUAL();
	void fLESSER_EQUAL();

	void fBREAKPOINT();


  void fPROJECTFILE();

	void fPUSH__binding_ME();
	void fPUSH__binding_PARENT();

	void fPUSH_ME();
  void fPUSH_PARENT();

	void fPUSH_NULL();
	void fPUSH_EMPTY();
	void fPUSH_ERROR();
	void fPUSH_RETURNVAR();
  
  void fPUSH_POINTERPOINTER();

  void fPUSH_BOOLEAN();
	
  void fPUSH_QSTRING();
  void fPUSH_CSTRING();

  void fPUSH_BYTE();
	void fPUSH_SHORT();
	void fPUSH_INTEGER();
	void fPUSH_LONG();

	void fPUSH_SINGLE();
	void fPUSH_DOUBLE();

  void fPUSH_INT16();
  void fPUSH_INT32();
  void fPUSH_INT64();
  void fPUSH_UINT16();
  void fPUSH_UINT32();
  void fPUSH_UINT64();

	void fPUSH_CURRENCY();
	void fPUSH_DATE();
	//bool fPUSH_VARIANT();

	void fPUSH_ENUM();
	void fPUSH_CONST();



	void fSET_ME();
	void fbinding_SET_ME();

  void fMOV_ME();
	void fMOV_PARENT();
  
	void fBUILTIN();
  
  void fbinding_PUSH_ID();

	void fPUSH_ID();
	void fPUSH_ID(t_pcode cPushId);

	void fPUSH_BOOLEAN_ID();
	
  void fPUSH_QSTRING_ID();
  void fPUSH_LQSTRING_ID();

  void fPUSH_CSTRING_ID();
  void fPUSH_LCSTRING_ID();

	void fPUSH_BYTE_ID();
	void fPUSH_SHORT_ID();
	void fPUSH_INTEGER_ID();
	void fPUSH_LONG_ID();

	void fPUSH_SINGLE_ID();
	void fPUSH_DOUBLE_ID();

	void fPUSH_INT16_ID();
	void fPUSH_INT32_ID();
	void fPUSH_INT64_ID();
	void fPUSH_UINT16_ID();
	void fPUSH_UINT32_ID();
	void fPUSH_UINT64_ID();

	void fPUSH_VARIANT_ID();
	void fPUSH_CURRENCY_ID();
	void fPUSH_DATE_ID();


	void fPUSH_IDREF(t_pcode cPushIdRef);
	void fPUSH_IDREFVAL();

  /*
	void fPUSH_BOOLEAN_IDREF();
	void fPUSH_INTEGER_IDREF();
	void fPUSH_LONG_IDREF();
	void fPUSH_SINGLE_IDREF();
	void fPUSH_DOUBLE_IDREF();
	void fPUSH_STRING_IDREF();
	void fPUSH_BYTE_IDREF();
	void fPUSH_VARIANT_IDREF();
	void fPUSH_CURRENCY_IDREF();
	void fPUSH_DATE_IDREF();
  */


	void fPUSH_IDPOINTER(t_pcode cPushIDPOINTER);
/*
	void fPUSH_BOOLEAN_IDPOINTER();

	void fPUSH_CSTRING_IDPOINTER();

	void fPUSH_INTEGER_IDPOINTER();
	void fPUSH_LONG_IDPOINTER();

	void fPUSH_SINGLE_IDPOINTER();
	void fPUSH_DOUBLE_IDPOINTER();
*/
	
	//	void fPUSHPOS();

	void f_DYNAMIC();
	void f_STATIC();

	void fCJMP();
	void fCJMP2();
	void fCJMP3();

	void fONERRORGOTO();
	void fONERRORGOTORESUMENEXT();
	void fRESUME();

	void fSTATEMENT();
	void fSTATEMENT_OUT();
	void fSTATEMENT_OVER();
	void fSTATEMENT_CURSOR();

	void fSYSTEM();
//	void fGOTO(bool bRun);	void fGOTO();

	void fDATA();
	void fRESTORE();
	void fREAD();

	void fAND();
	void fOR();
	void fNOT();
	void fPOWER();
	void fXOR();
	void fIMP();
	void fEQV();

	// options
	void fOPTION_RANGE();
	//void fOPTION_BASE();
	//void fOPTION_COMPARE();

//  void fSTACKPUSHINTEGER  	();
  void fSTACKPOP  	();

  void fENTER_PROPERTYGET  	();
  void fENTER_PROPERTYSET  	();
  
  void fEXIT_LOCAL  	();



	// typed movs
  
	void fMOV_ENUM();

	void fMOV_CONST();
	void fMOV_LQSTRING();
	void fMOV_RQSTRING();
	void fMOV_LCSTRING();
	void fMOV_RCSTRING();
	void fMOVSLS();
	void fMOVSRS();
	void fMOV_TYPE();

  void fMOV();
  void fMOV(t_pcode cMov, int nID = -1, t_scope scope = global, QByteArray *ba = 0, int nBinaryPos = -1);

  void fMOV_ISMISSING();
	
	void fMOV_BOOLEAN();

	void fMOV_QSTRING();
	void fMOV_CSTRING();

	void fMOV_SINGLE();
	void fMOV_DOUBLE();

	void fMOV_BYTE();
	void fMOV_SHORT();
	void fMOV_INTEGER();
	void fMOV_LONG();
/*
	void fMOV_INT16();
	void fMOV_INT32();
	void fMOV_INT64();
	void fMOV_UINT16();
	void fMOV_UINT32();
	void fMOV_UINT64();
*/
	void fMOV_VARIANT();

	void fMOV_CURRENCY();
  void fMOV_DATE();


	void fMOV_IDREF();
	void fMOV_IDREFVAL();


	void fMOV_BOOLEAN(int nID, t_scope scope);

	void fMOV_QSTRING(int nID, t_scope scope, QByteArray *ba, int nBinaryPos);

  void fMOV_QSTRING(int nID, t_scope scope);
	void fMOV_CSTRING(int nID, t_scope scope);

	void fMOV_SINGLE(int nID, t_scope scope);
	void fMOV_DOUBLE(int nID, t_scope scope);

	void fMOV_BYTE(int nID, t_scope scope);
	void fMOV_SHORT(int nID, t_scope scope);
	void fMOV_INTEGER(int nID, t_scope scope);
	void fMOV_LONG(int nID, t_scope scope);
/*
	void fMOV_INT16(int nID, t_scope scope);
	void fMOV_INT32(int nID, t_scope scope);
	void fMOV_INT64(int nID, t_scope scope);
	void fMOV_UINT16(int nID, t_scope scope);
	void fMOV_UINT32(int nID, t_scope scope);
	void fMOV_UINT64(int nID, t_scope scope);
*/
	void fMOV_CURRENCY(int nID, t_scope scope);
	void fMOV_DATE(int nID, t_scope scope);

	void fLBOUND();
	void fUBOUND();

	void fVARTYPE();
	void fISDATE();
	void fISEMPTY();
	void fISNULL();
	void fISNUMERIC();
	void fISMISSING();
	void fISARRAY();
	void fISOBJECT();
	void fISCURRENCY();
	void fISERROR();

	void fISBOOLEAN	();

	void fISSTRING		();

	void fISBYTE		();
	void fISSHORT		();
	void fISINTEGER		();
	void fISLONG		();

	void fISSINGLE		();
	void fISDOUBLE	();
/*
	void fISINT16			();
	void fISINT32			();
	void fISINT64		();
	void fISUINT16	();
	void fISUINT32	();
	void fISUINT64		();
*/
	void fISVARIANT		();


	void fARRAY2();
	void fMINUTE();
	void fMONTH();
	void fMSGBOX();
	void fNOW();
	void fRGB();
	void fSECOND();

	void fTYPEOF();
	void fERASE();
	void fLOC();

	void fCHOOSE();
	void fSWITCH();
	void fIIF();


	// builtin

  void fPEEK 	();
  void fPOKE  	();

  void fGET  	();
  void fGET2  	();


  void fCOMPARE();
  void fCONTAINS();
  void fCOUNT();
  void fENDSWITH();
  void fSTARTSWITH();
  void fLEFTJUSTIFIED();
  void fRIGHTJUSTIFIED();
  void fSECTION();
  void fSIMPLIFIED();
  void fTRIMMED();
  void fREVERSED();
  void fUNICODE();

  void fREADBINARY();
  void fWRITEBINARY();
  void fSEEKBINARY();

  void fPREPEND();
  void fAPPEND2();
  void fREMOVE();
  void fTRUNCATE();
  void fINSERT();
  void fFILL();


  void fPUT  	();
  void fPUT2  	();
  void fINSTREV  	();
  void fREPLACE  	();
  void fSPLIT 	();
  void fROUND 	();
  void fSTRREVERSE 	();
  void fFIELD 	();
  void fSPC 	();

  void fONTIMERGOSUB();
  void fTIMER_ON 	();
  void fTIMER_OFF 	();
  void fTIMER_STOP 	();

  void fDOEVENTS 	();
  void fFILECOPY 	();
  void fPRINTSCREEN 	();  
  void fCHDRIVE 	();  
  void fSETATTR 	();  
  void fCLEAR	();  
  void fPOINT	();    
  void fSCREEN2	();  
  void fCIRCLE	();  
  void fDRAW	();  
  void fPCOPY	();  
  void fPMAP	();  
  void fWIDTH	();  
  void fPRESET	();  
  void fPSET	();  
  void fPAINT	();  
  void fWINDOW	();  
  void fLINE	();  
  void fVIEWPRINT	();  
  void fVIEW	();  


  void fSTRCOMP  	();
  void fABS  	();
  void fACCESS  	();
  void fACS  	();
  void fAPPEND  	();
  void fASC  	();
  void fASN  	();
  void fATN  	();
  void fBEEP  	();
  void fBIN  	();
  void fCHDIR  	();
  void fCHR  	();
  void fCINT  	();
  void fCLNG  	();

  void fCSNG  	();
  void fCDBL  	();
  void fCCUR  	();
  void fCVAR  	();
  void fCBOOL  	();
  void fCBYTE  	();
  void fCDATE  	();
  void fCVERR  	();
  void fDAY	  	();
  void fDIR	  	();
  void fFILEATTR	();
  void fFILEDATETIME	();
  void fFILELEN	();
  void fFORMAT	();
  void fFREEFILE	();
  void fGETATTR	();
  void fHOUR	();
  void fINPUTBOX	();

  void fFORMATCURRENCY	();
  void fFORMATDATETIME	();
  void fFORMATNUMBER	();
  void fFORMATPERCENT	();
  void fWEEKDAYNAME	();
  void fMONTHNAME	();
	
  void fDATEADD  	();
  void fDATEDIFF  	();
  void fDATEPART  	();
  void fDATESERIAL  	();
  void fDATEVALUE  	();

  void fCURDIR  	();
  void fCOMMAND  	();
  void fCLOSE  	();
  void fCLOSEALL  	();
  void fCLS  	();
  void fCOLOR  	();
  void fCOS  	();
  void fCSRLIN  	();
  void fDATE 	();
  void fDEG  	();
  void fDOF  	();
  void fEOF  	();
  void fEXP  	();
  void fFACT    ();
  void fFILES  	();
  void fFIX  	();
  void fFRAC  	();
  void fHEX  	();
  void fHYPOT  	();
  void fINPUT  	();
  void fINPUT2  	();
  void fINKEY 	();
  void fINSTR  	();
  void fINT 	 	();
  void fKBASICDIR  	();
  void fTRY  	();
  void fENDCATCH  	();
  void fKILL  	();
  void fLCASE	();

  void fENCODE  	();
  void fDECODE  	();

  void fLEFT  	();
  void fLEN  	();
  void fLN  	();
  void fLOCATE  	();
  void fLOF  	();
  void fLOG  	();
  void fLOGB  	();
  void fLTRIM  	();
  void fMAX  	();
  void fMID  	();
  void fMID2  	();
  void fMIN  	();
  void fMKDIR  	();
  void fNAME  	();
  void fOCT  	();
  void fOPEN  	();
  void fOPEN2  	();
  void fOUTPUT  	();
  void fPOS  	();
  void fPRINT  	();
  void fRAD  	();
  void fRANDOMIZE  	();
  void fREAD2  	();
  void fRESET  	();
  void fRIGHT  	();
  void fRMDIR  	();
  void fRND  	();
  void fRTRIM  	();
  void fSEC  	();
  void fSEEK  	();
  void fSEEK2  	();
  void fSGN  	();
  void fSIN  	();
  void fSLEEP  	();
  void fSHELL  	();
  void fCAST  	();
  void fSPACE  	();
  void fSQR  	();
  void fSTR  	();
  void fSTRING2  	();
  void fTAN  	();
  void fTIME  	();
  void fTRIM  	();
  void fUCASE 	();
  void fVAL  	();
  void fUTF8  	();
  void fUTF16  	();
  void fWRITE  	();
  void fTIMER  	();
  void fLINEINPUT  	();
  void fDATE2  	();
  void fSCREEN  	();
  void fNZ 	();

  void fCONNECT 	(){ return; }
  void fDISCONNECT 	(){ return; }

  void fTIMESERIAL  	();
  void fTIMEVALUE  	();
  void fTYPENAME  	();
  void fWEEKDAY  	();
  void fYEAR  	();

  void fSILENTMODE  	();
  void fSEPARATOR  	();
  

  void fTYPE  	();
  void fENUM  	();
  void fENUM_ELEMENT  	();

  void fCLASS  	();
  void fERROR  	();

  void fERR		 	();
  void fERL	  	();

  void fFRE	  	();

  void fCLASS_BINDINGPARAM	  	();

  void interruptDebugAtBreakpoint(QString file, t_integer line);


  void constructClassInstanceVariables(int classid);

	void callPropertyGet();
	void callPropertySet();
	void callStaticMethod();


 //void qt_binding_setKbId(void *p, memory_variable2 *v, t_integer identifier, t_integer type);

	// ***
	int registerTypePublic(const char *name, int id);

  void operate(t_pcode cOperator);
  void operate(t_pcode cOperator, bool remove);

	bool findVars(int id, const char **acModule, const char **acSub, const char **acName);
	bool findConsts(int id, const char **acModule, const char **acSub, const char **acName);
  bool findScope(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub);
  bool findScope2(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub);
	const char *findFieldInType(int type_id, int field_id);
	const char *findFieldInEnum(int enum_id, int field_id);

	const char *findStatics(int id);
	const char *findTypes(int id);

	int getOffset(int identifier, t_scope scope);

	void pushId(t_scope scope, int identifier, int offset, int nVarType, bool bAssignment = false, memory_variable2 *v2 = 0, bool bBindingParent = false, bool bReturnVar = false);

  void enterLocal(const char *ac);
  void exitLocal();

	inline memory_variable2 *getLocalVar() const;
	inline memory_variable2 *getGlobalVar() const;
	inline memory_variable2 *getMeVar() const;

  memory_variable2 *globalVars;
  memory_variable2 *meVars;
  memory_variable2 *OldmeVars;
  bool bSetMe;

	inline bool interpretPcode() const;
	//bool debugNextStep();


  screen *myScreen;
  browser *myBrowser;

  bool bPushPointerPointer;



	data *myData;
	bool bMyDataReset;
	int nMyDataPos;

	

  _err *err2;



	memory_const2 *consts;

  memory_stringliteral *stringliterals;
	parser *myParser;

	memory_type *myType;
	memory_enum *myEnum;
	//memory_structure *myStructure;
	memory_sub *mySub;

  memory_gc *myGc;
  kberr *myErr;

  _ontimer *my_ontimer;

	
	t_array	*myArray;
	int	array_offset;
	int	movType_offset;

  int local_counter;


	typedef QLinkedList<local_frame_*> local_frame;
public:
	local_frame myLocalFrame;
  bool bRunPcode;
	bool bNoError;
private:
  
  const char *acCurrentFile;
  int nCurrentLine;

	QList<int> array_offset2;	
  QLinkedList<t_array*> myArray2;

  char acStringOutputBuffer[1024];
  char acStringConvertBuffer[1024];

	bool bDebugStepModeOn;


	bool bBreakpointAtPcode;
	
  QString sRuntimeErrorTxt;  
  bool bCatchBuiltinException;
  int nExceptionCountParamToRemove;
	int nRuntimeErrorPos;
	int nRuntimeErrorPos1;
	int nRuntimeErrorPos2;
  int nRuntimeErrorNo;
  int nRuntimeErrorLine;
  int nRuntimeErrorLine2;
  QString sRuntimeErrorFile;  
  QString sRuntimeErrorFile2;  

  QString sStepToCursorFile;
  int nStepToCursorLine;

  bool bStepIn;
  bool bStepOut;
  bool bStepOver;
  bool bStepToCursor;

	bool bSilentMode; // interpreter's debug output on/off
	bool bOptionRange; // under/overflow range check on/off
  bool bOptionComparyBinary; // compare binary, binary is default
  //int nOptionBase; // arrays start with 0 if not explictly declared or OPTION BASE

	int nStackValue;
  int nBaseOfArray; // arrays start with 1 if not explictly declared or OPTION BASE

  bool bCalledByIDE;
  bool bSilent;
  bool bDebug;


  _mainwindow *my_mainwindow;
  QApplication *my_qapplication;

  // ***
	// binding
  void registerBuiltinTypes();

  int nGetParamCount;

  void getParam(QMap<int, interpreter_parameter*> &v, int m, int nBinding)
{

#ifdef HAS_CONSOLE
  if (!bSilent) info(myPcode->getPos(), pcode_kbasic_binding::methodname_(m));
#endif

  /*
	switch(nBinding){
		case pcode__qt_binding_method:
			info(nPos, pcode_qt_binding::methodname_(m));
			break;
		case pcode__kbasic_binding_method:
			info(nPos, pcode_kbasic_binding::methodname_(m));
			break;
		default:
			//  error
			break;
	}
*/
	//interpreter_parameter *paramCount;
  //paramCount = new interpreter_parameter();

	//interpreter_parameter *identifier;
  //identifier = new interpreter_parameter();

  nGetParamCount = popStackInteger() - 1;
	for (int i = nGetParamCount; i >= 0; i--){
      gnestatics[i] = 0;
			v[i] = popStack(&gnestatics[i]);
	}

}


	void binding_callMethod();
	void binding_callProperty();
	void binding_callStaticProperty();
	void binding_callOperator();
	void binding_callFunctionOperator();
	void binding_callFunction();
	void binding_callStaticMethod();
/*
  // qt binding
  bool binding_callOperator_qt_binding(int m);
	bool binding_callFunctionOperator_qt_binding(int m);
	bool binding_callFunction_qt_binding(int m, bool bReturn);

	bool binding_callMethod_qt_binding(int m, bool bReturn);
	bool binding_callMethod_qt_binding2(int m, bool bReturn);
	bool binding_callMethod_qt_binding3(int m, bool bReturn);

	bool binding_callStaticMethod_qt_binding(int m, bool bReturn);
	bool binding_callStaticMethod_qt_binding2(int m, bool bReturn);
	bool binding_callStaticMethod_qt_binding3(int m, bool bReturn);

  bool binding_registerType_qt_binding();*/

  // kbasic binding
  bool binding_callOperator_kbasic_binding(int m);
	bool binding_callFunctionOperator_kbasic_binding(int m);
	bool binding_callFunction_kbasic_binding(int m, bool bReturn);

	bool binding_callMethod_kbasic_binding(int m, bool bReturn);
	bool binding_callMethod_kbasic_binding2(int m, bool bReturn);
	bool binding_callMethod_kbasic_binding3(int m, bool bReturn);
	bool binding_callMethod_kbasic_binding4(int m, bool bReturn);

	bool binding_callStaticMethod_kbasic_binding(int m, bool bReturn);
	bool binding_callStaticMethod_kbasic_binding2(int m, bool bReturn, QMap<int, interpreter_parameter*> &v);
	bool binding_callStaticMethod_kbasic_binding3(int m, bool bReturn, QMap<int, interpreter_parameter*> &v);

  void binding_registerType_kbasic_binding();
  // ***

  t_boolean BOOLEAN_EXPRESSION [interpreter__MAX_PARAM];  
  t_integer INTEGER_EXPRESSION [interpreter__MAX_PARAM];
  t_pointer STRING_EXPRESSION [interpreter__MAX_PARAM];
  t_double DOUBLE_EXPRESSION [interpreter__MAX_PARAM];
  t_pcode C[interpreter__MAX_PARAM];

  interpreter_parameter *DATE_EXPRESSION [interpreter__MAX_PARAM];  
  interpreter_parameter *EXPRESSION [interpreter__MAX_PARAM];  

  interpreter_parameter *p;

  bool bParentCalled; // used for ignoring overwritten qt bindings methods if original method of qt class should be called 

  t_array *a;


  void (interpreter::*lpFunc[interpreter__MAX_PCODE_ID])();

  

  QMap<QString, int> class_bindingparam;


  typedef QList<connect_*> class_bindingconnect9;
  QMap<QString, class_bindingconnect9*> class_bindingconnect;


};
 

inline bool interpreter::isDebugMode() const
{
  return bBreakpointAtPcode;
}


inline void interpreter::pushStackBoolean(t_boolean m)
{
  
  myStack->pushBoolean(m);
}

inline void interpreter::pushStackInteger(t_integer m)
{
  
  myStack->pushInteger(m);
}

inline void interpreter::pushStackLong(t_long m)
{
  
  myStack->pushLong(m);
}

inline void interpreter::pushStackQString(t_qstring m)
{
  
  myStack->pushQString(m);
}

inline void interpreter::pushStackCString(t_cstring m)
{
  
  myStack->pushCString(m);
}

inline void interpreter::pushStackDouble(t_double m)
{
  
  myStack->pushDouble(m);
}


void pushStack(interpreter_parameter *p);



inline void interpreter::info(int nPos, int nPcode, t_integer n)
{
  static char acText[1024];

	sprintf(acText, "%d", n);
	info(nPos, nPcode, acText);
}

inline void interpreter::infoCall(int nPos, int nPcode, t_integer n, t_integer n2)
{
	static char acText[1024];

	sprintf(acText, "call pos = %d, return pos = %d", n, n2);
	info(nPos, nPcode, acText);
}

inline void interpreter::infoCatch(int nPos, int nPcode, t_integer n, t_integer n2)
{
	static char acText[1024];

	sprintf(acText, "class = %d, catch pos = %d", n, n2);
	info(nPos, nPcode, acText);
}

inline void interpreter::infoCatch2(int nPos, int nPcode, t_integer n)
{
	static char acText[1024];

	sprintf(acText, "class = %d", n);
	info(nPos, nPcode, acText);
}

inline void interpreter::info(int nPos, int nPcode, t_long l)
{
	static char acText[1024]; 

#ifdef WINDOWS
	sprintf(acText, "%I64d", l); // HIDE
#else
	sprintf(acText, "%lld", l);
#endif	
	info(nPos, nPcode, acText);
}

inline void interpreter::info(int nPos, int nPcode, t_double d)
{
	static char acText[1024];

	sprintf(acText, "%.6f", d);
	info(nPos, nPcode, acText);
}

inline void interpreter::info(int nPos, const char *ac, const char *s)
{
  if (!bSilent){
	  CONSOLE pcodePrintSep("");
    CONSOLE pcodePrintPos(nPos);
 	  CONSOLE pcodePrintOpc(ac);
 	  if (s[0] != 0) CONSOLE pcodePrint(s);
 	  CONSOLE pcodePrintCR();
  }

	
}

inline void interpreter::info(const char *ac, const char *s)
{
  if (!bSilent){
    CONSOLE pcodePrintSep("");
    CONSOLE pcodePrintPos("");
 	  CONSOLE pcodePrintOpc(ac);
	  if (s[0] != 0) CONSOLE pcodePrint(s);
 	  CONSOLE pcodePrintCR();
  }

}

inline void interpreter::info(int nPos, int nPcode, const char *ac)
{
  if (!bSilent){
    CONSOLE pcodePrintSep("");
    CONSOLE pcodePrintPos(nPos);
 	  CONSOLE pcodePrintOpc(pcode::pcode_(nPcode));
 	  if (ac[0] != 0) CONSOLE pcodePrint(ac);
 	  CONSOLE pcodePrintCR();
  }

}

inline void interpreter::info2(int nPos, int nPcode, const char *ac)
{
  if (!bSilent){
    CONSOLE pcodePrintSep("");
    CONSOLE pcodePrintPos(nPos);
 	  CONSOLE pcodePrintOpc(pcode::builtin_(nPcode));
 	  if (ac[0] != 0) CONSOLE pcodePrint(ac);
 	  CONSOLE pcodePrintCR();
  }

}

inline void interpreter::info3(int nPos, int nPcode)
{
  if (!bSilent){
    CONSOLE pcodePrintSep("");
    CONSOLE pcodePrintPos(nPos);
 	  CONSOLE pcodePrintOpc(pcode::pcode_(nPcode));
  }

}

inline void interpreter::info(int nPos, const char *ac)
{
  if (!bSilent){
    CONSOLE pcodePrintSep("");
    CONSOLE pcodePrintPos(nPos);
 	  if (ac[0] != 0) CONSOLE pcodePrint(ac);
 	  CONSOLE pcodePrintCR();
  }

}


inline memory_variable2 *interpreter::getVar(t_scope n)
{
  switch(n){
    case local:
      return getLocalVar();
      break;
    case param:
      return getLocalVar();
      break;
    case global:
      return getGlobalVar();
      break;
    case me:
      return getMeVar();
      break;

  }
	internalError("getVar(t_scope n)  --> no matching scope");
  return getGlobalVar(); // eigentlich 0, aber führt so nicht zu absturz  
}

inline memory_variable2 *interpreter::getLocalVar() const
{
  return myLocalFrame.last()->localVars;
}

inline memory_variable2 *interpreter::getGlobalVar() const
{
	return globalVars;
}

inline memory_variable2 *interpreter::getMeVar() const
{
	return meVars;
}

inline bool interpreter::interpretPcode() const
{
	return bNoError && bRunPcode;
}

inline t_boolean interpreter::popStackBoolean()
{
  

  t_pcode c = myStack->popPCode();
  if (c == pcode__BOOLEAN) return myStack->popBoolean();
  if (c == pcode__BYTE) return myStack->popByte() != 0;
  if (c == pcode__INTEGER) return myStack->popInteger() != 0;
  if (c == pcode__SHORT) return myStack->popShort() != 0;
  if (c == pcode__LONG) return myStack->popLong() != 0;
  if (c == pcode__SINGLE) return myStack->popSingle() != 0;
  if (c == pcode__DOUBLE) return myStack->popDouble() != 0;
  pcodeError("wrong datatype on stack while popStack...");  
  return false;
}

inline t_integer interpreter::popStackInteger()
{
  

  t_pcode c = myStack->popPCode();
  if (c == pcode__BOOLEAN) return myStack->popBoolean();
  if (c == pcode__BYTE) return myStack->popByte();
  if (c == pcode__INTEGER) return myStack->popInteger();
  if (c == pcode__SHORT) return myStack->popShort();
  if (c == pcode__LONG) return myStack->popLong();
  if (c == pcode__SINGLE) return myStack->popSingle();
  if (c == pcode__DOUBLE) return myStack->popDouble();
  pcodeError("wrong datatype on stack while popStack...");  
  return 0;
}

inline t_long interpreter::popStackLong()
{
  

  if (myStack->popPCode() == pcode__LONG) return myStack->popLong();
  pcodeError("wrong datatype on stack while popStack...");  
  return 0;
}

inline t_pointer interpreter::popStackString(int *nestatics, t_pcode *c)
{  

  *c = myStack->popPCode();
  if (*c == pcode__QSTRING){
    *nestatics = 0;
    return myStack->popQString();
  }
  if (*c == pcode__CSTRING){
    *nestatics = 0;
    return myStack->popCString();
  }
  if (*c == pcode__EQSTRING){
    *c = pcode__QSTRING;
    *nestatics = myStack->popQStringId();
    return estatics->getQString(*nestatics, 0);
  }
  if (*c == pcode__ECSTRING){
    *c = pcode__CSTRING;
    *nestatics = myStack->popCStringId();
    return estatics->getCString(*nestatics, 0);
  }

  myStack->pushPCode(*c);

  // might be a numeric value, try to cast it
  interpreter_parameter *p = popStack(nestatics);
  *c = pcode__QSTRING;
  
  *nestatics = estatics->declare(pcode__QSTRING, 0, false, false);
  estatics->setQString(*nestatics, &p->toQString(), 0); 

  delete p;

  return estatics->getQString(*nestatics, 0);

}


inline t_double interpreter::popStackDouble()
{
  

  t_pcode c = myStack->popPCode();
  if (c == pcode__DOUBLE) return myStack->popDouble();
  if (c == pcode__BYTE) return myStack->popByte();
  if (c == pcode__INTEGER) return myStack->popInteger();
  if (c == pcode__SHORT) return myStack->popShort();
  if (c == pcode__LONG) return myStack->popLong();
  if (c == pcode__SINGLE) return myStack->popSingle();
  pcodeError("wrong datatype on stack while popStack...");  
  return 0;
}


inline t_currency interpreter::popStackCurrency()
{  
  t_pcode c = myStack->popPCode();
  if (c == pcode__CURRENCY) return myStack->popCurrency();
  pcodeError("wrong datatype on stack while popStack...");  
  return t_currency();
}

inline t_date interpreter::popStackDate()
{  
  t_pcode c = myStack->popPCode();
  if (c == pcode__DATE) return myStack->popDate();
  pcodeError("wrong datatype on stack while popStack...");  
  return t_date();
}

interpreter_parameter *popStack(int *nestatics);


#ifdef WINDOWS // HIDE
  #define MYSTDCALL __stdcall // HIDE
#else // HIDE
  #define MYSTDCALL   // HIDE
#endif // HIDE
// UNHIDE #define MYSTDCALL   


// *** used for extern library calls
typedef void (MYSTDCALL *void_c0)( );
typedef void (MYSTDCALL *void_c1)( void * );
typedef void (MYSTDCALL *void_c2)( void *, void * );
typedef void (MYSTDCALL *void_c3)( void *, void *, void * );
typedef void (MYSTDCALL *void_c4)( void *, void *, void *, void * );
typedef void (MYSTDCALL *void_c5)( void *, void *, void *, void * , void * );
typedef void (MYSTDCALL *void_c6)( void *, void *, void *, void * , void *  , void * );
typedef void (MYSTDCALL *void_c7)( void *, void *, void *, void * , void *  , void *  , void * );
typedef void (MYSTDCALL *void_c8)( void *, void *, void *, void * , void *  , void *  , void *  , void * );
typedef void (MYSTDCALL *void_c9)( void *, void *, void *, void * , void *  , void *  , void *  , void *  , void * );

typedef t_boolean (MYSTDCALL *bool_c0)( );
typedef t_boolean (MYSTDCALL *bool_c1)( void * );
typedef t_boolean (MYSTDCALL *bool_c2)( void *, void * );
typedef t_boolean (MYSTDCALL *bool_c3)( void *, void *, void * );
typedef t_boolean (MYSTDCALL *bool_c4)( void *, void *, void *, void * );
typedef t_boolean (MYSTDCALL *bool_c5)( void *, void *, void *, void * , void * );
typedef t_boolean (MYSTDCALL *bool_c6)( void *, void *, void *, void * , void * , void * );
typedef t_boolean (MYSTDCALL *bool_c7)( void *, void *, void *, void * , void * , void * , void * );
typedef t_boolean (MYSTDCALL *bool_c8)( void *, void *, void *, void * , void * , void * , void * , void * );
typedef t_boolean (MYSTDCALL *bool_c9)( void *, void *, void *, void * , void * , void * , void * , void * , void * );

typedef t_byte (MYSTDCALL *byte_c0)( );
typedef t_byte (MYSTDCALL *byte_c1)( void * );
typedef t_byte (MYSTDCALL *byte_c2)( void *, void * );
typedef t_byte (MYSTDCALL *byte_c3)( void *, void *, void * );
typedef t_byte (MYSTDCALL *byte_c4)( void *, void *, void *, void * );
typedef t_byte (MYSTDCALL *byte_c5)( void *, void *, void *, void * , void * );
typedef t_byte (MYSTDCALL *byte_c6)( void *, void *, void *, void * , void * , void * );
typedef t_byte (MYSTDCALL *byte_c7)( void *, void *, void *, void * , void * , void * , void * );
typedef t_byte (MYSTDCALL *byte_c8)( void *, void *, void *, void * , void * , void * , void * , void * );
typedef t_byte (MYSTDCALL *byte_c9)( void *, void *, void *, void * , void * , void * , void * , void * , void * );

typedef t_short (MYSTDCALL *short_c0)( );
typedef t_short (MYSTDCALL *short_c1)( void * );
typedef t_short (MYSTDCALL *short_c2)( void *, void * );
typedef t_short (MYSTDCALL *short_c3)( void *, void *, void * );
typedef t_short (MYSTDCALL *short_c4)( void *, void *, void *, void * );
typedef t_short (MYSTDCALL *short_c5)( void *, void *, void *, void * , void * );
typedef t_short (MYSTDCALL *short_c6)( void *, void *, void *, void * , void * , void * );
typedef t_short (MYSTDCALL *short_c7)( void *, void *, void *, void * , void * , void * , void * );
typedef t_short (MYSTDCALL *short_c8)( void *, void *, void *, void * , void * , void * , void * , void * );
typedef t_short (MYSTDCALL *short_c9)( void *, void *, void *, void * , void * , void * , void * , void * , void * );

typedef t_integer (MYSTDCALL *int_c0)( );
typedef t_integer (MYSTDCALL *int_c1)( void * );
typedef t_integer (MYSTDCALL *int_c2)( void *, void * );
typedef t_integer (MYSTDCALL *int_c3)( void *, void *, void * );
typedef t_integer (MYSTDCALL *int_c4)( void *, void *, void *, void * );
typedef t_integer (MYSTDCALL *int_c5)( void *, void *, void *, void * , void * );
typedef t_integer (MYSTDCALL *int_c6)( void *, void *, void *, void * , void * , void * );
typedef t_integer (MYSTDCALL *int_c7)( void *, void *, void *, void * , void * , void * , void * );
typedef t_integer (MYSTDCALL *int_c8)( void *, void *, void *, void * , void * , void * , void * , void * );
typedef t_integer (MYSTDCALL *int_c9)( void *, void *, void *, void * , void * , void * , void * , void * , void * );

typedef t_long (MYSTDCALL *long_c0)( );
typedef t_long (MYSTDCALL *long_c1)( void * );
typedef t_long (MYSTDCALL *long_c2)( void *, void * );
typedef t_long (MYSTDCALL *long_c3)( void *, void *, void * );
typedef t_long (MYSTDCALL *long_c4)( void *, void *, void *, void * );
typedef t_long (MYSTDCALL *long_c5)( void *, void *, void *, void * , void * );
typedef t_long (MYSTDCALL *long_c6)( void *, void *, void *, void * , void * , void * );
typedef t_long (MYSTDCALL *long_c7)( void *, void *, void *, void * , void * , void * , void * );
typedef t_long (MYSTDCALL *long_c8)( void *, void *, void *, void * , void * , void * , void * , void * );
typedef t_long (MYSTDCALL *long_c9)( void *, void *, void *, void * , void * , void * , void * , void * , void * );

typedef t_single (MYSTDCALL *single_c0)( );
typedef t_single (MYSTDCALL *single_c1)( void * );
typedef t_single (MYSTDCALL *single_c2)( void *, void * );
typedef t_single (MYSTDCALL *single_c3)( void *, void *, void * );
typedef t_single (MYSTDCALL *single_c4)( void *, void *, void *, void * );
typedef t_single (MYSTDCALL *single_c5)( void *, void *, void *, void * , void * );
typedef t_single (MYSTDCALL *single_c6)( void *, void *, void *, void * , void * , void * );
typedef t_single (MYSTDCALL *single_c7)( void *, void *, void *, void * , void * , void * , void * );
typedef t_single (MYSTDCALL *single_c8)( void *, void *, void *, void * , void * , void * , void * , void * );
typedef t_single (MYSTDCALL *single_c9)( void *, void *, void *, void * , void * , void * , void * , void * , void * );

typedef t_double (MYSTDCALL *double_c0)( );
typedef t_double (MYSTDCALL *double_c1)( void * );
typedef t_double (MYSTDCALL *double_c2)( void *, void * );
typedef t_double (MYSTDCALL *double_c3)( void *, void *, void * );
typedef t_double (MYSTDCALL *double_c4)( void *, void *, void *, void * );
typedef t_double (MYSTDCALL *double_c5)( void *, void *, void *, void * , void * );
typedef t_double (MYSTDCALL *double_c6)( void *, void *, void *, void * , void * , void * );
typedef t_double (MYSTDCALL *double_c7)( void *, void *, void *, void * , void * , void * , void * );
typedef t_double (MYSTDCALL *double_c8)( void *, void *, void *, void * , void * , void * , void * , void * );
typedef t_double (MYSTDCALL *double_c9)( void *, void *, void *, void * , void * , void * , void * , void * , void * );


// ***



#endif

