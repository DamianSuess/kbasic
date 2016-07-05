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


#ifndef INTERPRETER_FUNCTION_H 
#define INTERPRETER_FUNCTION_H


#include <stdlib.h>


#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <QFile>
#include <QFileInfo>
#include <QThread>


#include "interpreter_parameter.h"
#include "utility.h"


#include "screen.h"

#include "../kbshared/typedef.h"

#ifndef WINDOWS
#include <sys/errno.h>
#endif

 const unsigned char function__NEXTWIHOUTFOR  		= 0 + 1;
 const unsigned char function__SYNTAXERROR  		= function__NEXTWIHOUTFOR + 1;
 const unsigned char function__RETURNWITHOUTGOSUB  		= function__SYNTAXERROR + 1;
 const unsigned char function__READBEYONDDATA  		= function__RETURNWITHOUTGOSUB + 1;
 const unsigned char function__WRONGFUNCTIONCALL  		= function__READBEYONDDATA + 1;
 const unsigned char function__OVERFLOW2  		= function__WRONGFUNCTIONCALL + 1;
 const unsigned char function__NOTENOUGHMEMORY  		= function__OVERFLOW2 + 1;
 const unsigned char function__LABELNOTDEFINED  		= function__NOTENOUGHMEMORY + 1;
 const unsigned char function__INDEXOUTOFRANGE  		= function__LABELNOTDEFINED + 1;
 const unsigned char function__ALREADYDEFINED  		= function__INDEXOUTOFRANGE + 1;
 const unsigned char function__DIVISIONBYZERO  		= function__ALREADYDEFINED + 1;
 const unsigned char function__NOTALLOWEDINDIRECTMODE	= function__DIVISIONBYZERO + 1;
 const unsigned char function__WRONGDATATYPE	= function__NOTALLOWEDINDIRECTMODE + 1;
 const unsigned char function__NOTENOUGHSTRINGMEMORY	= function__WRONGDATATYPE + 1;
 const unsigned char function__TOOLONGSTRINGFORMULA	= function__NOTENOUGHSTRINGMEMORY + 1;
 const unsigned char function__KBASICCANNOTPROCEED	= function__TOOLONGSTRINGFORMULA + 1;
 const unsigned char function__KBASICFUNCTIONNOTDEFINED	= function__KBASICCANNOTPROCEED + 1;
 const unsigned char function__MISSINGRESUME	= function__KBASICFUNCTIONNOTDEFINED + 1;
 const unsigned char function__RESUMEWITHOUTERROR	= function__MISSINGRESUME + 1;
 const unsigned char function__DEVICETIMEOUT	= function__RESUMEWITHOUTERROR + 1;
 const unsigned char function__DEVICEERROR	= function__DEVICETIMEOUT + 1;
 const unsigned char function__FORWITHOUTNEXT	= function__DEVICEERROR + 1;
 const unsigned char function__PAPEREND	= function__FORWITHOUTNEXT + 1;
 const unsigned char function__WHILEWITHOUTWEND	= function__PAPEREND + 1;
 const unsigned char function__WENDWITHOUTWILE	= function__WHILEWITHOUTWEND + 1;
 const unsigned char function__LABELALREADYDEFINED	= function__WENDWITHOUTWILE + 1;
 const unsigned char function__KBASICSUBNOTDEFINED	= function__LABELALREADYDEFINED + 1;
 const unsigned char function__DUMMY	= function__KBASICSUBNOTDEFINED + 1;
 const unsigned char function__WRONGCOUNTOFARGUMENTS	= function__DUMMY + 1;
 const unsigned char function__FIELDNOTDEFINED	= function__WRONGCOUNTOFARGUMENTS + 1;
 const unsigned char function__VARIABLENOTNEEDED	= function__FIELDNOTDEFINED + 1;
 const unsigned char function__FIELDOVERFLOW	= function__VARIABLENOTNEEDED + 1;
 const unsigned char function__INTERNALERROR	= function__FIELDOVERFLOW + 1;
 const unsigned char function__WRONGFILEANDLE	= function__INTERNALERROR + 1;
 const unsigned char function__FILENOTFOUND	= function__WRONGFILEANDLE + 1;
 const unsigned char function__WRONGFILEACCESSMODE	= function__FILENOTFOUND + 1;
 const unsigned char function__FILEALREADYOPEN	= function__WRONGFILEACCESSMODE + 1;
 const unsigned char function__FIELDSTATEMENTACTIVE	= function__FILEALREADYOPEN + 1;
 const unsigned char function__DEVICEERRORONINOUTPUT	= function__FIELDSTATEMENTACTIVE + 1;
 const unsigned char function__FILEALREADYEXIST	= function__DEVICEERRORONINOUTPUT + 1;
 const unsigned char function__WRONGRECORDLENGTH	= function__FILEALREADYEXIST + 1;
 const unsigned char function__FILESYSTEMFULL	= function__WRONGRECORDLENGTH + 1;
 const unsigned char function__INPUTAFTEREOF	= function__FILESYSTEMFULL + 1;
 const unsigned char function__WRONGRECORDNUMBER	= function__INPUTAFTEREOF + 1;
 const unsigned char function__WRONGFILENAME = function__WRONGRECORDNUMBER + 1;
 const unsigned char function__TOOMANYFILES = function__WRONGFILENAME + 1;
 const unsigned char function__DEVICENOTREADY = function__TOOMANYFILES + 1;
 const unsigned char function__COMMUNICATIONBUFFEROVERFLOW = function__DEVICENOTREADY + 1;
 const unsigned char function__ACCESSDENIED = function__COMMUNICATIONBUFFEROVERFLOW + 1;
 const unsigned char function__FILESYSTEMNOTREADY = function__ACCESSDENIED + 1;
 const unsigned char function__DATAMEDIUMERROR = function__FILESYSTEMNOTREADY + 1;
 const unsigned char function__FUNCTIONNOTAVAILABLE = function__DATAMEDIUMERROR + 1;
 const unsigned char function__RENAMEDATAMEDIUM = function__FUNCTIONNOTAVAILABLE + 1;
 const unsigned char function__PATHFILEACCESSERROR = function__RENAMEDATAMEDIUM + 1;
 const unsigned char function__PATHNOTFOUND = function__PATHFILEACCESSERROR + 1;


static const int MAX_FILEHANDLE	= 512;

const int function__TAB_WIDTH = 14;

struct t_file2
{
  QFile f;
  t_integer nMode;
  t_integer nAccess;  
  t_integer nRecordLen;
  t_integer nRecordPos;
};


class mySystem : public QThread
{
Q_OBJECT
public:
mySystem(t_qstring acCommand)
{
  sCommand = *acCommand;
}
protected:
    void run();
    QString sCommand;
};


class interpreter;

class function {
public:
	function(screen *myScreen, interpreter *myInterpreter);
	~function();

	bool error(const char *acError);

	void	fSCREEN(t_integer no);
	void	fCLS();

  interpreter_parameter* fDATEADD(t_qstring mode, t_integer n, t_date d);
  interpreter_parameter* fDATEADD(t_cstring mode, t_integer n, t_date d);

  interpreter_parameter* fDATEDIFF(t_qstring mode, t_date d, t_date d2, t_integer firstdayofweek, t_integer firstweekofyear);
  interpreter_parameter* fDATEDIFF(t_cstring mode, t_date d, t_date d2, t_integer firstdayofweek, t_integer firstweekofyear);

  t_integer fDATEPART(t_qstring mode, t_date d, t_integer firstdayofweek, t_integer firstweekofyear);
  t_integer fDATEPART(t_cstring mode, t_date d, t_integer firstdayofweek, t_integer firstweekofyear);

  t_date fFILEDATETIME(t_qstring s);
  t_date fFILEDATETIME(t_cstring s);

 
  interpreter_parameter* fNOW();

  
  //interpreter_parameter* fADDDATE(t_date d1, t_date d2);
  interpreter_parameter* fADDDAYS(t_date d1, t_integer n);
  interpreter_parameter* fADDMONTHS(t_date d1, t_integer n);
  interpreter_parameter* fADDYEARS(t_date d1, t_integer n);
  //interpreter_parameter* fSUBDATE(t_date d1, t_date d2);
  interpreter_parameter* fSUBDAYS(t_date d1, t_integer n);
  interpreter_parameter* fSUBMONTHS(t_date d1, t_integer n);
  interpreter_parameter* fSUBYEARS(t_date d1, t_integer n);
  //interpreter_parameter* fADDTIME(t_date d1, t_date d2);
  interpreter_parameter* fADDHOURS(t_date d1, t_integer n);
  interpreter_parameter* fADDMINUTES(t_date d1, t_integer n);
  interpreter_parameter* fADDSECONDS(t_date d1, t_integer n);
  //interpreter_parameter* fSUBTIME(t_date d1, t_date d2);
  interpreter_parameter* fSUBHOURS(t_date d1, t_integer n);
  interpreter_parameter* fSUBMINUTES(t_date d1, t_integer n);
  interpreter_parameter* fSUBSECONDS(t_date d1, t_integer n);

  interpreter_parameter* fDAYOFWEEK(t_date d1, t_qstring Format);
  interpreter_parameter* fDAYOFYEAR(t_date d1);
  interpreter_parameter* fDAYSINMONTH(t_date d1);
  interpreter_parameter* fDAYSINYEAR(t_date d1);
  interpreter_parameter* fWEEKNUMBER(t_date d1);
  interpreter_parameter* fISLEAPYEAR(t_date d1);

  interpreter_parameter* fDIFFDAY(t_date d1, t_date d2);
  interpreter_parameter* fDIFFSECONDS(t_date d1, t_date d2);

  interpreter_parameter* fISDATEVALID(t_date d1);
  interpreter_parameter* fISTIMEVALID(t_date d1);
  interpreter_parameter* fISDATETIMEVALID(t_date d1);

  interpreter_parameter* fDAYNAME(t_integer month, t_qstring Format);
  interpreter_parameter* fMONTHNAME(t_integer month, t_qstring Format);

  //t_cstring fMONTHNAME(t_integer month, t_boolean shorty);

  t_qstring fWEEKDAYNAME(t_integer day, t_boolean shorty, t_integer firstdayofweek);
  //t_cstring fWEEKDAYNAME(t_integer day, t_boolean shorty, t_integer firstdayofweek);

  t_integer fWEEKDAY(t_date d);

  t_date fDATESERIAL(t_integer y, t_integer m, t_integer d);
  t_date fTIMESERIAL(t_integer y, t_integer m, t_integer d);

  

  

  t_long fDAY(t_date d);
  t_long fMONTH(t_date d);
  t_long fYEAR(t_date d);
  t_long fHOUR(t_date d);
  t_long fMINUTE(t_date d);
  t_long fSECOND(t_date d);

  void fLINE(t_boolean step, t_integer x1, t_integer y1, 
            t_boolean step2, t_boolean expression, t_integer x2, t_integer y2, 
            t_boolean bColor, t_integer color, t_boolean b, t_boolean bf, t_boolean bStyle, t_integer style);

  void fPSET(t_boolean step, t_integer x, t_integer y, t_boolean bColor, t_integer color);


	interpreter_parameter*	fRGB(t_integer red, t_integer green, t_integer blue);
	void	fCOLOR(t_boolean bFORE, t_boolean bBACK, t_integer nFORE, t_integer nBACK);
	void	fLOCATE(t_boolean bY, t_boolean bX, t_integer nY, t_integer nX);

	void	fBEEP();
	void	fDOEVENTS();
  
  bool fFILECOPY(t_qstring acFrom, t_qstring acTo);  
  bool fFILECOPY(t_cstring acFrom, t_cstring acTo);  


  void fPOKE(const char *ac, t_integer nStringLen, const char *p, int nPSize);
  void fPEEK(const char *ac, t_integer nStringLen, const char *p, int nPSize);

  void fPUT(t_integer nFILEHANDLE, t_integer nRecord, t_boolean bRecordLen, const char *ac, int nRecordLenOverwrite = 0);
  char *fGET(t_integer nFILEHANDLE, t_integer nRecord, t_boolean bRecordLen, int *nRecordLenOverwrite = 0);

  interpreter_parameter* fLINEINPUT(t_integer nFILEHANDLE);
  interpreter_parameter* fINPUT2(t_integer nFILEHANDLE);
  void fSEEK(t_integer nFILEHANDLE, t_integer nPos);
  interpreter_parameter* fSEEK2(t_integer nFILEHANDLE);

  interpreter_parameter* fFILELEN(t_qstring ac);
  interpreter_parameter* fFILELEN(t_cstring ac);

	interpreter_parameter* fCHR (t_integer n);

	interpreter_parameter* fLEN (t_qstring ac);
	interpreter_parameter* fLEN (t_cstring ac);

	interpreter_parameter* fSTRREVERSE (t_qstring ac);
	interpreter_parameter* fSTRREVERSE (t_cstring ac);

  interpreter_parameter* fINPUT(t_qstring acSTRING_EXPRESSION, t_boolean bQuestionMark, t_boolean bNewLine, t_integer nInputType);
  interpreter_parameter* fINPUT(t_cstring acSTRING_EXPRESSION, t_boolean bQuestionMark, t_boolean bNewLine, t_integer nInputType);

  void fPRINT(t_boolean bWRITE, t_boolean bWRITEStringExpression, t_boolean bFIRST, t_boolean bFILEHANDLE, t_integer nFILEHANDLE, t_qstring acUSING, t_boolean bEXPRESSION, t_boolean bSPC, t_boolean bTAB, interpreter_parameter* STRING_EXPRESSION, t_integer nSPC, t_integer nTAB, t_boolean bTabbedOutput, t_boolean bNewLine, t_boolean bEcho, t_boolean bLog);
  void fPRINT(t_boolean bWRITE, t_boolean bWRITEStringExpression, t_boolean bFIRST, t_boolean bFILEHANDLE, t_integer nFILEHANDLE, t_cstring acUSING, t_boolean bEXPRESSION, t_boolean bSPC, t_boolean bTAB, interpreter_parameter* STRING_EXPRESSION, t_integer nSPC, t_integer nTAB, t_boolean bTabbedOutput, t_boolean bNewLine, t_boolean bEcho, t_boolean bLog);

  void fPRINT(t_boolean bFIRST, t_boolean bFILEHANDLE, t_integer nFILEHANDLE, t_qstring qac, t_boolean bEcho, t_boolean bLog);
  void fPRINT(t_boolean bFIRST, t_boolean bFILEHANDLE, t_integer nFILEHANDLE, t_cstring cac, t_boolean bEcho, t_boolean bLog);


  void fCLOSEALL();
  interpreter_parameter* fFREEFILE(t_integer nRANGE);
  interpreter_parameter* fEOF(t_integer nFILEHANDLE);

  interpreter_parameter* fSPLIT(t_qstring s, t_qstring s2, t_boolean bKeepEmptyParts, t_boolean bCaseSensitive);
  //interpreter_parameter* fSPLIT(t_cstring s, t_boolean bKeepEmptyParts, t_boolean bCaseSensitive);

	interpreter_parameter* fMID (t_qstring ac, t_integer nStart, t_integer nLen = -1);
	interpreter_parameter* fMID (t_cstring ac, t_integer nStart, t_integer nLen = -1);

  void fMID2 (t_qstring ac, t_qstring sNew, t_integer nStart, t_integer nLen = -1);
  void fMID2 (t_cstring ac, t_cstring sNew, t_integer nStart, t_integer nLen = -1);

  interpreter_parameter* fVAL (t_qstring ac);
  interpreter_parameter* fVAL (t_cstring ac);

  interpreter_parameter* fUTF8 (t_qstring ac);
  interpreter_parameter* fUTF8 (t_cstring ac);

  //interpreter_parameter* fUTF16 (t_qstring ac);
  interpreter_parameter* fUTF16 (t_cstring ac, int wlen);

	interpreter_parameter* fINT(t_double d);
	interpreter_parameter* fROUND(interpreter_parameter *d, int nCount);
	void fRANDOMIZE(t_boolean bExpression, t_double dStartValue);

  t_qstring fFORMATCURRENCY	();
  t_qstring fFORMATDATETIME	();
  t_qstring fFORMATNUMBER	();
  t_qstring fFORMATPERCENT	();
  t_qstring fWEEKDAYNAME	();
  t_qstring fMONTHNAME	();

	interpreter_parameter* fTIMER ();

  t_boolean fLIKE(t_qstring acString, t_qstring acPattern, t_integer nMode);
  t_boolean fLIKE(t_cstring acString, t_cstring acPattern, t_integer nMode);

  interpreter_parameter* fRND (t_boolean bExpression, t_double dValue);
	interpreter_parameter* fCSRLIN ();
	interpreter_parameter* fPOS (t_integer nExpression);
	interpreter_parameter* fABS (t_double d);
	interpreter_parameter* fDATE();
	interpreter_parameter* fTIME();
	interpreter_parameter* fSTRING2(t_boolean bAscii, t_boolean bString, t_integer nLen, int cAscii, QChar cChar);
	interpreter_parameter* fSPACE(t_integer nLen);

	interpreter_parameter* fINSTR(t_boolean bBegin, t_integer nBegin, t_qstring acString, t_qstring acSearch, t_boolean CaseSensitive);
	interpreter_parameter* fINSTR(t_boolean bBegin, t_integer nBegin, t_cstring acString, t_cstring acSearch, t_boolean CaseSensitive);

	interpreter_parameter* fINSTREV(t_boolean bBegin, t_integer nBegin, t_qstring acString, t_qstring acSearch, t_boolean CaseSensitive);
	interpreter_parameter* fINSTREV(t_boolean bBegin, t_integer nBegin, t_cstring acString, t_cstring acSearch, t_boolean CaseSensitive);

	interpreter_parameter* fREPLACE(t_qstring acString, t_qstring acPattern, t_qstring acBy, t_boolean CaseSensitive);
	interpreter_parameter* fREPLACE(t_cstring acString, t_cstring acPattern, t_cstring acBy, t_boolean CaseSensitive);

  interpreter_parameter* fCOMMAND();

	interpreter_parameter* fENCODE (t_qstring acString);
	interpreter_parameter* fENCODE (t_cstring acString);

	interpreter_parameter* fDECODE (t_qstring acString);
	interpreter_parameter* fDECODE (t_cstring acString);

	interpreter_parameter* fLEFT (t_qstring acString, t_integer nLen);
	interpreter_parameter* fLEFT (t_cstring acString, t_integer nLen);

	interpreter_parameter* fRIGHT (t_qstring acString, t_integer nLen);
	interpreter_parameter* fRIGHT (t_cstring acString, t_integer nLen);

  interpreter_parameter* fLCASE(t_qstring acString);
  interpreter_parameter* fLCASE(t_cstring acString);

  interpreter_parameter* fUCASE(t_qstring acString);
  interpreter_parameter* fUCASE(t_cstring acString);

  interpreter_parameter* fLTRIM(t_qstring acString);
  interpreter_parameter* fLTRIM(t_cstring acString);

  interpreter_parameter* fRTRIM(t_qstring acString);
  interpreter_parameter* fRTRIM(t_cstring acString);

  interpreter_parameter* fTRIM(t_qstring acString);
  interpreter_parameter* fTRIM(t_cstring acString);

  interpreter_parameter* fFORMAT(interpreter_parameter *Expression, t_qstring sFormat, t_qstring sFillChar, t_boolean bRightAligned);

  interpreter_parameter* fASC (t_qstring acString);
  interpreter_parameter* fASC (t_cstring acString);

  interpreter_parameter* fSTRCOMP (t_qstring ac, t_qstring ac2, t_integer nMode);	
  interpreter_parameter* fSTRCOMP (t_cstring ac, t_cstring ac2, t_integer nMode);	

  interpreter_parameter* fSTR (t_double d);
	interpreter_parameter* fHEX(t_integer n);
	interpreter_parameter* fOCT(t_integer n);
	interpreter_parameter* fBIN(t_integer n);
	interpreter_parameter* fINKEY(t_integer *nKeyPressed);

  interpreter_parameter *fCOMPARE(t_qstring s, t_qstring s2, t_boolean CaseSensitive);
  interpreter_parameter *fCONTAINS(t_qstring s, t_qstring s2, t_boolean CaseSensitive);
  interpreter_parameter *fCOUNT(t_qstring s, t_qstring s2, t_boolean CaseSensitive);
  interpreter_parameter *fENDSWITH(t_qstring s, t_qstring s2, t_boolean CaseSensitive);
  interpreter_parameter *fSTARTSWITH(t_qstring s, t_qstring s2, t_boolean CaseSensitive);
  interpreter_parameter *fLEFTJUSTIFIED(t_qstring s, t_integer Width, t_qstring s2, t_boolean CaseSensitive);
  interpreter_parameter *fRIGHTJUSTIFIED(t_qstring s, t_integer Width, t_qstring s2, t_boolean CaseSensitive);
  interpreter_parameter *fSECTION(t_qstring s, t_qstring s2, t_integer Start, t_integer End, t_qstring SectionFlags);
  interpreter_parameter *fSIMPLIFIED(t_qstring s);
  interpreter_parameter *fTRIMMED(t_qstring s);
  //interpreter_parameter *fREVERSED(t_qstring s);
  interpreter_parameter *fUNICODE(t_qstring s, t_integer Position, t_boolean bEXPRESSION2, t_integer Unicode);

  void fPREPEND(t_qstring s, t_qstring s2);
  void fAPPEND(t_qstring s, t_qstring s2);
  void fREMOVE(t_qstring s, t_integer Position, t_integer Length);
  void fTRUNCATE(t_qstring s, t_integer Position);
  void fINSERT(t_qstring s, t_qstring s2, t_integer Position);
  void fFILL(t_qstring s, t_qstring s2, t_integer Position);

  void fSLEEP(t_boolean bExpression, t_integer seconds);

	interpreter_parameter* fSHELL(t_boolean bCommand, t_boolean bSynchron, t_qstring acCommand);
	interpreter_parameter* fSHELL(t_boolean bCommand, t_boolean bSynchron, t_cstring acCommand);

  interpreter_parameter* fCLNG(interpreter_parameter *p);
  interpreter_parameter* fCINT(interpreter_parameter *p);
	interpreter_parameter* fCSNG(interpreter_parameter *p);
	interpreter_parameter* fCDBL(interpreter_parameter *p);
	interpreter_parameter* fCCUR(interpreter_parameter *p);
//	interpreter_parameter* fCVAR(t_double d);
	interpreter_parameter* fCBOOL(interpreter_parameter *p);
	interpreter_parameter* fCBYTE(interpreter_parameter *p);
	interpreter_parameter* fCDATE(interpreter_parameter *p);

	interpreter_parameter* fRAD (t_double angle); //converts degrees to radians
	interpreter_parameter* fDEG (t_double angle); //converts radians to degrees
	interpreter_parameter* fACS (t_double angle); //angle is supposed to be in radians for
	interpreter_parameter* fASN (t_double angle);
	interpreter_parameter* fATN (t_double angle);
	interpreter_parameter* fCOS (t_double angle);
	interpreter_parameter* fEXP (t_double n);
	interpreter_parameter* fLOG (t_double n); //this function is the ten-based logarithmic function
	interpreter_parameter* fLN (t_double n);
	interpreter_parameter* fSGN (t_double n); //returns -1 if negative, 0 if zero, and 1 if positive
	interpreter_parameter* fFIX (t_double n);
	interpreter_parameter* fSIN(t_double angle);
	interpreter_parameter* fSQR(t_double n);
	interpreter_parameter* fTAN(t_double angle);
	interpreter_parameter* fFACT(t_double n);
	interpreter_parameter* fLOGB(t_double n, t_double base);
	interpreter_parameter* fFRAC(t_double n);
	interpreter_parameter* fHYPOT (t_double a, t_double b);
	interpreter_parameter* fMAX(t_double n, t_double m);
	interpreter_parameter* fMIN(t_double n, t_double m);
	interpreter_parameter* fSEC(t_double angle);

	void fCHDIR(t_qstring directory);
	void fCHDIR(t_cstring directory);

  void fCHDRIVE(t_qstring drive);
  void fCHDRIVE(t_cstring drive);

  void fPRINTSCREEN(t_boolean drive);

  interpreter_parameter *fCURDIR(t_qstring drive);
  interpreter_parameter *fCURDIR(t_cstring drive);

  interpreter_parameter *fDIR(t_qstring path, t_integer nAttr, t_boolean bFilesAll = false);
  interpreter_parameter *fDIR(t_cstring path, t_integer nAttr, t_boolean bFilesAll = false);

  QDir *dir;
  QFileInfoList *dirIt;

	interpreter_parameter* fRMDIR(t_qstring directory);
	interpreter_parameter* fRMDIR(t_cstring directory);

  interpreter_parameter* fMKDIR(t_qstring directory);
	interpreter_parameter* fMKDIR(t_cstring directory);

	void fOPEN(t_qstring ac, t_integer nMode, t_integer nFILEHANDLE, t_integer nLen);
	void fOPEN(t_cstring ac, t_integer nMode, t_integer nFILEHANDLE, t_integer nLen);
  
  //void fSETATTR(t_qstring ac, t_integer nAttr);
  //void fSETATTR(t_cstring ac, t_integer nAttr);

  interpreter_parameter *fGETATTR(t_qstring ac);
  interpreter_parameter *fGETATTR(t_cstring ac);

  interpreter_parameter *fFILEATTR(t_integer nFILEHANDLE, t_integer dummy);

	void fCLOSE(t_integer nFILEHANDLE);
	interpreter_parameter* fLOF(t_integer nFILEHANDLE);
	interpreter_parameter* fLOC(t_integer nFILEHANDLE);
  void closeAllFiles();

	void fRESET();

	void fFILES(t_boolean bDirectory, t_qstring acDirectory);
	void fFILES(t_boolean bDirectory, t_cstring acDirectory);

	t_integer fNAME(t_qstring file, t_qstring as);
	t_integer fNAME(t_cstring file, t_cstring as);

	t_integer fKILL(t_qstring filename);
	t_integer fKILL(t_cstring filename);

	void fERROR(t_integer n);

  //interpreter_parameter* fERR		 	();
  //interpreter_parameter* fERL	  	();

  t_integer getRecordSizeFile(t_integer nFILEHANDLE);

  int nLastFILEHANDLE;


//  Mathmatical functions

// the following are not connected to the interpreter yet
/*
	t_double	CSEC (t_double angle);
	t_double	CTAN (t_double angle);
	t_double	ASEC (t_double angle);
	t_double	ACSEC (t_double angle);
	t_double	ACTAN (t_double angle);
	t_double	HSIN (t_double angle);
	t_double	HCOS (t_double angle);
	t_double	HTAN (t_double angle);
	t_double	HSEC (t_double angle);
	t_double	HCSEC (t_double angle);
	t_double	HCTANn (t_double angle);
	t_double	HASIN (t_double angle);
	t_double	HACOS (t_double angle);
	t_double	HATAN (t_double angle);
	t_double	HASEC (t_double angle);
	t_double	HACSEC (t_double angle);
	t_double	HACTAN (t_double angle);
*/


private:

  bool setRecordPos(t_integer nFILEHANDLE, t_integer nRecordPos, int nRecordLenOverwrite = 0);

	scanner *myScanner;
  interpreter *myInterpreter;
 
	textbuffer *myTextbuffer;
	textbuffer *myTextbuffer2;

  t_file2 file[MAX_FILEHANDLE];

  char curdrive;
  QString curdir;
  QString curdir2[27];
  
  /**/ long nStartValue;
  double dLastRND;


  screen *myScreen;


public:

// ****************************
// * bool isBoolean(char *acText, t_boolean *c, bool bTestLength = true, bool bVal = false)
// *
// * description:
// * searches for a boolean literal
// * if a boolean literal has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * return:
// * true, if a boolean literal has been found
// * false, no boolean literal has been found
// ****************************
bool isBoolean(char *acText, t_boolean *c, bool bTestLength = true, bool bVal = false)
{

  static char *acTest;
	static int nLenTest;

	acTest = acText;

  int i;
  if (acTest[0] == 'T' || acTest[0] == 't') i = 0;
  else if (acTest[0] == 'F' || acTest[0] == 'f') i = 1;
  else return false;

	nLenTest = strlen(acTest);

	static const char *acPattern; acPattern = 0;
	static bool b; b = false;

  int nLen;
	for (; b == false && i < 2; i++){

		 		 if (i == 0)	acPattern = "TRUE";
		else if (i == 1)	acPattern = "FALSE";

  	nLen = strlen(acPattern);

 		if (nLenTest >= nLen){

    	if (utility::my_strnicmp(acPattern, acTest, nLen) == 0){
        
        if (!bVal && isSeparator(acTest[nLen])){
		   		b = true;
        } else {
   		  	b = false;
   			}
   		}
		}
	}

	if (b){
    // TRUE is -1 and not 1, because of TRUE = NOT FALSE (1111 1111 = NOT 0000 0000) as signed: -1 --> FALSE = 0
		*c = (utility::my_stricmp(acPattern, "TRUE") == 0 ? -1 : 0);
		return true;
	}
	return false;
}

// ****************************
// * bool isSingle(char *acText, t_single *f, bool bTestLength = true, bool bVal = false)
// *
// * description:
// * searches for a single constant
// * if a single constant has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * e.g. 21.34!
// *
// * return:
// * true, if a single constant has been found
// * false, no single constant has been found
// ****************************
bool isSingle(char *acText, t_single *f, bool bTestLength = true, bool bVal = false)
{

  static char *s, *b;
	static bool t, p;
	s = b = acText;

  static int nLen; 
  nLen = 0;

	static bool qb;
  qb = false;

	static bool bSuffix;
  bSuffix = false;

	static char cSign;
  cSign = 0;

  t = false;
	if (*s == '+' || *s == '-'){
		cSign = *s;
		s++;
		nLen++;
  }
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (p = (*s == '.')) {
    s++;
		nLen++;
    while (*s >= '0' && *s <= '9') {
      s++;
			nLen++;
      t = true;
    }
  }
  if (!t) return false;

  if (*s == 'E' || *s == 'e' || *s == '^'){
	  if (*s == '^'){
			qb = true;
		}
		s++;
		nLen++;
	}
	else if (p == true) goto ok;
	else return false;

  if (*s == '-' || *s == '+'){
		s++;
		nLen++;
	}
  t = false;
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (!t) return false;

ok:
  if (s && (*s == 'F' || *s == 'f')){
		if (qb == true){
			return false;
		}
		s++;
		nLen++;
	}
	if (*s == '!'){ bSuffix = true; }
	if (*s == '#'){ return false; } // Oops, the suffix is for double

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && (!bVal && !isSeparator(*s))) return false; // Oops, no separator = not a number

  *f = atof(mk_s(b, nLen));

	return true;
}

// ****************************
// * bool isDouble(char *acText, t_double *d, bool bTestLength = true, bool bVal = false)
// *
// * description:
// * searches for a double constant
// * if a double constant has been found, the associated token will be generated
// *
// * parameter:
// * none
// *
// * e.g. 21.34#
// *
// * return:
// * true, if a double constant has been found
// * false, no double constant has been found
// ****************************
bool isDouble(char *acText, t_double *d, bool bTestLength = true, bool bVal = false)
{

  static char *s, *b;
	static bool t, p;
	
  s = b = acText;

	static int nLen;
  nLen = 0;

	static bool qb;
  qb = false;

	static bool bSuffix;
  bSuffix = false;

	static char cSign;
  cSign = 0;

  t = false;
	if (*s == '+' || *s == '-'){
		cSign = *s;
		s++;
		nLen++;
  }
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (p = (*s == '.')) {
    s++;
		nLen++;
    while (*s >= '0' && *s <= '9') {
      s++;
			nLen++;
      t = true;
    }
  }
  if (!t){
    return false;
  }

  if (*s == '#'){ 
    goto ok2;
  }

  if (*s == 'E' || *s == 'e' || *s == '^'){
	  if (*s == '^'){
			qb = true;
		}
		s++;
		nLen++;
	}
	else if (p == true) goto ok;
	else return false;

  if (*s == '-' || *s == '+'){
		s++;
		nLen++;
	}
  t = false;
  while (*s >= '0' && *s <= '9') {
    s++;
		nLen++;
    t = true;
  }
  if (!t) return false;

ok:
  if (s && (*s == 'F' || *s == 'f')){
		if (qb == true){
			return false;
		}
		s++;
		nLen++;
	}
ok2:
	if (*s == '#'){ bSuffix = true; }

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && (!bVal && !isSeparator(*s))) return false; // Oops, no separator = not a number

  errno = 0;
  *d = strtod(mk_s(b, nLen), NULL);

	return true;
}
// ****************************
// * bool isHex(char *acText, t_long *l, bool bTestLength = true, bool bVal = false)
// *
// * description:
// * searches for a hex constant
// * if a hex constant has been found, the associated token will be generated
// *
// * isHex scans string pointer to determine if it's a hexadecimal number.
// * A valid hexadecimal number starts with '&H' and is followed
// * by up to 16 significant digits
// * comprised of 0-9, and a-f (case insensitive).
// * Values are by default unsigned
// *
// * return:
// * true, if a hex constant has been found
// * false, no hex constant has been found
// ****************************
bool isHex(char *acText, t_long *l, bool bTestLength = true, bool bVal = false)
{

  static char *s, *str, *b;
  b = s = str = acText;

	static bool bOK;
  bOK = false;

  static double dValue;
  dValue = 0;

  static bool bSigned;
  bSigned = true;

	static int nLen;
  nLen = 0;

  if ((str[0] == '&' && (str[1] == 'h' || str[1] == 'H'))) {
		str += 2;
		s = str;
		nLen += 2;
  } else return false;

	if (*s != 0){
        while ((*s >= '0' && *s <= '9') || (*s >= 'A' && *s <= 'F') || (*s >= 'a' && *s <= 'f')) {
            if (*s >= '0' && *s <= '9') dValue = dValue * 16 + *s - '0';
            if (*s >= 'A' && *s <= 'F') dValue = dValue * 16 + 10 + *s - 'A';
            if (*s >= 'a' && *s <= 'f') dValue = dValue * 16 + 10 + *s - 'a';
            s++;
						nLen++;
            if (*s == 0) break;
        }
        if (s > str) {    // make sure at least one hex character
        	bOK = true;
        }
	  	else return false;
    }

  if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && (!bVal && !isSeparator(*s))) return false; // Oops, no separator = not a number

	if (bSigned) if (dValue > 2147483647.) dValue = -(4294967296. - dValue);

	if (nLen <= 16) *l = (t_long) dValue;
	else { scannerError(" hex long number overflow > FFFFFFFFFFFFFFFF"); return false; }

	return bOK;
}
// ****************************
// * bool isOctal(char *acText, t_long *l, bool bTestLength = true, bool bVal = false)
// *
// * description:
// * searches for a octal constant
// * if a octal constant has been found, the associated token will be generated
// *
// * isOctal scans string pointer to determine if it's an octal number.
// * A valid octal number starts with '&O' and is followed by up to 11
// * significant digits
// * comprised of 0-7. Values are by default signed positive values.
// *
// * parameter:
// * none
// *
// * return:
// * true, if a octal constant has been found
// * false, no octal constant has been found
// ****************************
bool isOctal(char *acText, t_long *l, bool bTestLength = true, bool bVal = false)
{

  static char *s, *str, *b;
	
  b = s = str = acText;

	static bool bOK;
  bOK = false;

  static t_double dValue; 
  dValue = 0;

  static int nLen;
  nLen = 0;

  if (str[0] == '&' && (str[1] == 'o' || str[1] == 'O')) {
		str += 2;
		nLen += 2;
		s = str;
  } else return false;

	if (*s != 0){
    while (*s >= '0' && *s <= '7') {
        dValue = dValue * 8 + *s - '0';
        s++;
        nLen++;
        if (*s == 0) break;
    }
    if (s > str) bOK = true;    // make sure at least one octal character
	  else return false;
  }

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && (!bVal && !isSeparator(*s))) return false; // Oops, no separator = not a number

  if (nLen <= 23) *l = (t_long) dValue;
	else { scannerError(" octal long number overflow > 2^64"); return false; }

	return bOK;
}
// ****************************
// * bool isBinary(char *acText, t_long *l, bool bTestLength = true, bool bVal = false)
// *
// * description:
// * searches for a binary constant
// * if a binary constant has been found, the associated token will be generated
// *
// * isBinary scans string pointer to determine if it's a binary number.
// * A valid binary number starts with '0b' (or '0B'), or '&B'  (or '&b) and is followed
// * by up to 31 significant digits (as many leading 0's as desired are permitted)
// * comprised of 0 or 1.
// *
// * return:
// * true, if a binary constant has been found
// * false, no binary constant has been found
// ****************************
bool isBinary(char *acText, t_long *l, bool bTestLength = true, bool bVal = false)
{

 static char *s, *str, *b;
 
 b = s = str = acText;

 static bool bOK;
 bOK  = false;

 static t_long lValue;
 lValue  = 0;

 static int nLen;
 nLen = 0;

 if ((str[0] == '&' && (str[1] == 'b' || str[1] == 'B')))
 {
  str += 2;
  nLen += 2;
  s = str;
 } else return false;

 if (*s != 0){
        while (*s >= '0' && *s <= '1') {
            if (*s >= '0' && *s <= '1') lValue = (lValue << 1) + *s - '0';
            s++;
						nLen++;
            if (*s == 0) break;
        }
        if (s > str) {    // make sure at least one binary character
         bOK = true;
        }
    else return false;
    }

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  if (s[0] != 0 && (!bVal && !isSeparator(*s))) return false; // Oops, no separator = not a number

  if (nLen <= 64) *l = lValue;
	else { scannerError(" binary long number overflow > 2^64"); return false; }

  return bOK;
}
// ****************************
// * bool isLong(char *acText, t_long *l, bool bTestLength = true, bool bVal = false)
// *
// * description:
// * searches for  a long constant
// * if a long constant has been found, the associated token will be generated
// *
// * e.g. 2134&
// *
// * return:
// * true, if a long constant has been found
// * false, no long constant has been found
// ****************************
bool isLong(char *acText, t_long *l, bool bTestLength = true, bool bVal = false)
{

  static char *s, *b;
	s = b = acText;

	static int nLen;
  nLen = 1;

	static bool bOK;
  bOK = false;

	static bool bSuffix;
  bSuffix = false;

	static char cSign;
  cSign = 0;

	if (*s >= '0' && *s <= '9'){	bOK = true; s++;	}
 	else if(*s == '+' || *s == '-'){
		cSign = *s;
		s++;
	} else return false;

	if (*s >= '0' && *s <= '9'){ s++; nLen++; }
	else if (bOK == false) return false;

	while(*s != 0){
 		if (*s >= '0' && *s <= '9')	s++;
		else if (*s == '&'){ bSuffix = true; break; }
		else break;
		nLen++;
	}

  if (s[0] != 0 && (!bVal && !isSeparator(*s))) return false; // Oops, no separator = not a number

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?
	errno = 0;
  *l =  atol(mk_s(b, nLen));//atoll

	return true;
}

bool isInteger(char *acText, t_integer *n, bool bTestLength = true, bool bVal = false)
{

  static char *s, *b;
	s = b = acText;

	static int nLen;
  nLen = 1;

	static bool bOK;
  bOK = false;

	static bool bSuffix;
  bSuffix = false;

	static char cSign;
  cSign = 0;

	if (*s >= '0' && *s <= '9'){	bOK = true; s++;	}
 	else if(*s == '+' || *s == '-'){
		cSign = *s;
		s++;
	}
	else return false;

	if (*s >= '0' && *s <= '9'){ s++; nLen++; }
	else if (bOK == false) return false;

	while(*s != 0){
 		if (*s >= '0' && *s <= '9')	s++;
		else if (*s == '%'){ bSuffix = true; break; }
		else break;
		nLen++;
	}
	if (*s == '&'){ return false; } // Oops, the suffix is for long

  if (s[0] != 0 && (!bVal && !isSeparator(*s))) return false; // Oops, no separator = not a number

	if (bTestLength) if (nLen != (signed) strlen(b)) return false; // some wrong characters in trailer?

  errno = 0;
	*n = atoi(mk_s(b, nLen));

  if (*n >= 0 && b[0] == '-'){ { scannerError("integer number underflow < -2147483648"); } return false; }
  if (*n < 0 && b[0] != '-'){ { scannerError("integer number overflow > 2147483647"); } return false; }

	return true;
}


char *mk_s(char *s, int nLen, bool bUpper = false)
{
  char *c = myTextbuffer->get(s, nLen);
  if (!bUpper) return c;

	for (register unsigned int i = 0; i < nLen; i++) c[i] = toupper(c[i]);

	return c;
}

bool scannerError(const char *acScannerError)
{
	return false;
}

static bool isSeparator(char c)
{
	return isWhitespace(c) || isDelimitor(c);
}

static bool isWhitespace(char c)
{
	switch(c)
	{
  case ' ':
  case '\t':
  case '\f':
  case '\r':
  case '\v':
		return true;
    break;
  default:
    return false;
    break;
	}
	return false;
}

static bool isDelimitor(char c)
{
  return isDelimitorOperator(c) || isDelimitorSymbol(c) || isDelimitorMisc(c);
}

static bool isDelimitorOperator(char c)
{
	switch(c)
	{
  case '+':
  case '-':
  case '*':
  case '/':
  case '\\':
  case '=':
  case '>':
  case '<':
  case '^':
  case '&':
  case '|':
		return true;
  default:
    return false;
    break;
  }
	return false;
}

static bool isDelimitorSymbol(char c)
{
	switch(c)
	{
  case '.':
  case '(':
  case ')':
  case '[':
  case ']':
  case ',':
  case ':':
  case '!':
  case ';':
  case '?':
//  case '_':  HINT kann sowohl als symbol oder bestandteil eines identifiers vorkommen, deswegen auskommentiert
  case '#':
  case '{':
  case '}':
		return true;
  default:
    return false;
    break;
  }
	return false;
}

static bool isDelimitorMisc(char c)
{
	switch(c)
	{
  case '\"':
  case '\'':
  case '\n':
  case 13: // 0xd
		return true;
    break;
  default:
    return false;
    break;
  }
	return false;
}

  static const char *runtime_error(int n)
{
	switch(n){

  case function__NEXTWIHOUTFOR: return "next without for";
  case function__SYNTAXERROR: return "syntax error";
  case function__RETURNWITHOUTGOSUB: return "return without gosub";
  case function__READBEYONDDATA: return "read beyond data";
  case function__WRONGFUNCTIONCALL: return "wrong function call";
  case function__OVERFLOW2: return "overflow";
  case function__NOTENOUGHMEMORY: return "not enough memory";
  case function__LABELNOTDEFINED: return "label not defined";
  case function__INDEXOUTOFRANGE: return "index out of range";
  case function__ALREADYDEFINED: return "already defined";
  case function__DIVISIONBYZERO: return "division by zero";
  case function__NOTALLOWEDINDIRECTMODE: return "not allewd indirect mode";
  case function__WRONGDATATYPE: return "wrong datatype";
  case function__NOTENOUGHSTRINGMEMORY: return "not enough string memory";
  case function__TOOLONGSTRINGFORMULA: return "too long string formula";
  case function__KBASICCANNOTPROCEED: return "KBASICCANNOTPROCEED";
  case function__KBASICFUNCTIONNOTDEFINED: return "KBASICFUNCTIONNOTDEFINED";
  case function__MISSINGRESUME: return "missing resume";
  case function__RESUMEWITHOUTERROR: return "resume without error";
  case function__DEVICETIMEOUT: return "device timeout";
  case function__DEVICEERROR: return "device error";
  case function__FORWITHOUTNEXT: return "for without next";
  case function__PAPEREND: return "paper end";
  case function__WHILEWITHOUTWEND: return "while without wend";
  case function__WENDWITHOUTWILE: return "wend without while";
  case function__LABELALREADYDEFINED: return "label already defined";
  case function__KBASICSUBNOTDEFINED: return "kbasic sub not defined";
  case function__DUMMY: return "dummy";
  case function__WRONGCOUNTOFARGUMENTS: return "wrong count of arguments";
  case function__FIELDNOTDEFINED: return "field not defined";
  case function__VARIABLENOTNEEDED: return "variable not needed";
  case function__FIELDOVERFLOW: return "field overflow";
  case function__INTERNALERROR: return "internal error";
  case function__WRONGFILEANDLE: return "wrong filehandle";
  case function__FILENOTFOUND: return "file not found";
  case function__WRONGFILEACCESSMODE: return "wrong file access mode";
  case function__FILEALREADYOPEN: return "file already open";
  case function__FIELDSTATEMENTACTIVE: return "field statement active";
  case function__DEVICEERRORONINOUTPUT: return "device error on input / output";
  case function__FILEALREADYEXIST: return "file already exist";
  case function__WRONGRECORDLENGTH: return "wrong record length";
  case function__FILESYSTEMFULL: return "filesystem full";
  case function__INPUTAFTEREOF: return "input after end of file";
  case function__WRONGRECORDNUMBER: return "wrong record number";
  case function__WRONGFILENAME: return "wrong filename";
  case function__TOOMANYFILES: return "too many files";
  case function__DEVICENOTREADY: return "device not ready";
  case function__COMMUNICATIONBUFFEROVERFLOW: return "communication buffer overflow";
  case function__ACCESSDENIED: return "access denied";
  case function__FILESYSTEMNOTREADY: return "filesystem not ready";
  case function__DATAMEDIUMERROR: return "data medium error";
  case function__FUNCTIONNOTAVAILABLE: return "function not available";
  case function__RENAMEDATAMEDIUM: return "remame data medium";
  case function__PATHFILEACCESSERROR: return "path file access error";
  case function__PATHNOTFOUND: return "path not found";
	default: return "";
	}
}

};



#endif
