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


#include "parser.h"


/*
********************************************************************************
kbasic
********************************************************************************
*/
bool parser::fKBASIC(pcode *p, int *nReturnExpressionType, bool bReturn)
{
  _BEGIN_

  if (fKBASIC_STATIC(p, nReturnExpressionType, bReturn)){ _DONE_ }
  else if (fKBASIC_INSTANCE(p, nReturnExpressionType, bReturn)){ _DONE_ }

  _END_
}

bool parser::fKBASIC_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn)
{
  if (!proceedParse()) return false;
	
#ifdef KBDEBUG
  if (stopAtLine(99)){
    int i = 9;
    i++;
  }
#endif

  //if ((fNAMESPACECLASS(p, KBASIC))){} // is optional

  // kbasic.math.*
  if (fKBASIC_STRING_STATIC(p, nReturnExpressionType, bReturn)){ return true; }
  if (fKBASIC_DATETIME_STATIC(p, nReturnExpressionType, bReturn)){ return true; }
  if (fKBASIC_CAST_STATIC(p, nReturnExpressionType, bReturn)){ return true; }
  if (fKBASIC_MY_STATIC(p, nReturnExpressionType, bReturn)){ return true; }
  if (fKBASIC_UTILITY_STATIC(p, nReturnExpressionType, bReturn)){ return true; }
  if (fKBASIC_MATH_STATIC(p, nReturnExpressionType, bReturn)){ return true; }

  return false;
	
}

bool parser::fKBASIC_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn)
{	

	if (!proceedParse()) return false;
  
  if (fKBASIC_STRING_INSTANCE(p, nReturnExpressionType, bReturn)){ return true; }
  if (fKBASIC_DATETIME_INSTANCE(p, nReturnExpressionType, bReturn)){ return true; }

	return false;
  
}

bool parser::fKBASIC_UTILITY_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	const char *acIdentifier = "";

	if (/*bIDENTIFIER = */fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

    if (utility::my_stricmp("Utility", acIdentifier) == 0 && parseTerm(token__SYM_DOT)){

      *nReturnExpressionType = 0;

      //if (!(fNAMESPACECLASS(p, KBASIC_MATH))){ return false; }

      switch(peekToken()){

        case token__FORMAT: if (fFORMAT(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__ROUND: if (fROUND(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__BIN: if (fBIN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__HEX: if (fHEX(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__RANDOM:
        case token__RND: if (fRND(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__RANDOMIZE: if (fRANDOMIZE(p)) _DONE_ break;


      }

    }
  }

	_END_
}




bool parser::fKBASIC_MY_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	const char *acIdentifier = "";

	if (/*bIDENTIFIER = */fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

    if (utility::my_stricmp("My", acIdentifier) == 0 && parseTerm(token__SYM_DOT)){

      *nReturnExpressionType = 0;

      //if (!(fNAMESPACECLASS(p, KBASIC_MATH))){ return false; }

      switch(peekToken()){

    case token__TYP_BYTE: 
    case token__TYP_SHORT: 
    case token__TYP_INTEGER: 
    case token__TYP_LONG: 
    case token__TYP_BOOLEAN: 
    //case token__TYP_QSTRING: 
    //case token__TYP_CSTRING: 
    case token__TYP_SINGLE: 
    case token__TYP_DOUBLE: 
    case token__TYP_CURRENCY: 
    //case token__TYP_DATE: 
      if (fCAST(p, nReturnExpressionType, bReturn)) _DONE_; break;    
    
    case token__STRING: if (fSTRING(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__ISLINUX: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__ISLINUX)){
         #ifdef LINUX // HIDE
  					if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode // HIDE
         #else // HIDE
  					if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode // HIDE
         #endif // HIDE
         // UNHIDE if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode

	      if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__ISLINUX, ") missing"); _ERROR_ }
        }

				 *nReturnExpressionType = pcode__BOOLEAN;

         _DONE_
       }
       break;
    case token__ISWINDOWS: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__ISWINDOWS)){
         #ifdef WINDOWS // HIDE
  					if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode // HIDE
         #else // HIDE
  					if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode // HIDE
         #endif // HIDE
         // UNHIDE if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode

	      if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__ISWINDOWS, ") missing"); _ERROR_ }
        }
				 *nReturnExpressionType = pcode__BOOLEAN;

         _DONE_
       }
       break;
    case token__ISMAC: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__ISMAC)){
         #ifdef MAC // HIDE
  					if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode // HIDE
         #else // HIDE
  					if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode // HIDE
         #endif // HIDE

         // UNHIDE if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode

	      if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__ISMAC, ") missing"); _ERROR_ }
        }
				 *nReturnExpressionType = pcode__BOOLEAN;

         _DONE_
       }
       break;
    case token__LINE: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__LINE)){

         if (peekToken() == token__SYM_DOT){
           _END_
           break; // might be the call of class File
         }

				 if (bProducePcode) p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, getCurrentLine()); // write pcode
	      
         if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__LINE, ") missing"); _ERROR_ }
        }
				 *nReturnExpressionType = pcode__INTEGER;

         _DONE_
       }
       break;
     case token__FILE: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__FILE)){

         if (peekToken() == token__SYM_DOT){
           _END_
           break; // might be the call of class File
         }

         const char *ac = "";

         ac = getCurrentFile();
					
				 int nStringLiteral = registerStringLiteral(ac);
				 if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
				 if (bProducePcode) p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
         if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__FILE, ") missing"); _ERROR_ }
        }

				 *nReturnExpressionType = pcode__QSTRING;					

         _DONE_
       }
       break;
    case token__MODULE: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__MODULE)){
         const char *ac = "";

         if (isScopeModule()){
           ac = getModule();
         }
					
				 int nStringLiteral = registerStringLiteral(ac);
				 if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
				 if (bProducePcode) p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
         if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__MODULE, ") missing"); _ERROR_ }
        }

				 *nReturnExpressionType = pcode__QSTRING;					

         _DONE_
       }
       break;
    case token__CLASS: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__CLASS)){
         const char *ac = "";

         if (isScopeClass()){
           ac = getClass();
         }
					
				 int nStringLiteral = registerStringLiteral(ac);
				 if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
				 if (bProducePcode) p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
         if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__CLASS, ") missing"); _ERROR_ }
        }

				 *nReturnExpressionType = pcode__QSTRING;					

         _DONE_
       }
       break;
    case token__SUB: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__SUB)){
         const char *ac = "";

         if (isScopeLocal()){
           if (isScopeClass()){
             ac = myClass->getRealNameMethod(myClass->getId(getClass()), myClass->getIdMethod(getClass(), getSub()));
           } else {
             ac = myModule->getRealNameSub(myModule->getId(getModule()), myModule->getIdSub(getModule(), getSub()));
           }
         }
					
				 int nStringLiteral = registerStringLiteral(ac);
				 if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
				 if (bProducePcode) p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
         if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__SUB, ") missing"); _ERROR_ }
        }

				 *nReturnExpressionType = pcode__QSTRING;					

         _DONE_
       }
       break;
    case token__FUNCTION: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__FUNCTION)){
         const char *ac = "";

         if (isScopeLocal()){
           if (isScopeClass()){
             ac = myClass->getRealNameMethod(myClass->getId(getClass()), myClass->getIdMethod(getClass(), getSub()));
           } else {
             ac = myModule->getRealNameSub(myModule->getId(getModule()), myModule->getIdSub(getModule(), getSub()));
           }
         }
					
				 int nStringLiteral = registerStringLiteral(ac);
				 if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
				 if (bProducePcode) p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
         if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__FUNCTION, ") missing"); _ERROR_ }
        }

				 *nReturnExpressionType = pcode__QSTRING;					

         _DONE_
       }
       break;

        case token__ABS: if (fABS(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__APPEND: if (fAPPEND(p)) _DONE_ break;
        case token__ASC: if (fASC(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__BIN: if (fBIN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__CBOOL: if (fCBOOL(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__CBYTE: if (fCBYTE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__CDBL: if (fCDBL(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__CHR: if (fCHR(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__CINT: if (fCINT(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__COMPARE: if (fCOMPARE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__CONTAINS: if (fCONTAINS(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__COUNT: if (fCOUNT(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__COS: if (fCOS(p, nReturnExpressionType, bReturn)) _DONE_ break;
//        case token__CLASS: if (fCLASS(p, nReturnExpressionType, bReturn)) _DONE_ break;

//        case token__CSHORT: if (fCSHORT(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__CSNG: if (fCSNG(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__DOEVENTS: if (fDOEVENTS(p)) _DONE_ break;
        case token__ENDSWITH: if (fENDSWITH(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__EXP: if (fEXP(p, nReturnExpressionType, bReturn)) _DONE_ break;
//        case token__FACT: if (fFACT(p, nReturnExpressionType, bReturn)) _DONE_ break;

       // case token__FILE: if (fFILE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__FILECOPY: if (fFILECOPY(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__FILELEN: if (fFILELEN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__FILL: if (fFILL(p)) _DONE_ break;
        case token__FIX: if (fFIX(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__FORMAT: if (fFORMAT(p, nReturnExpressionType, bReturn)) _DONE_ break;

//        case token__FUNCTION: if (fFUNCTION(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__HEX: if (fHEX(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__INPUTBOX: if (fINPUTBOX(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__INSERT: if (fINSERT(p)) _DONE_ break;

        case token__INDEXOF: 
        case token__INSTR: if (fINSTR(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__LASTINDEXOF: 
        case token__INSTREV: if (fINSTREV(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__INT: if (fINT(p, nReturnExpressionType, bReturn)) _DONE_ break;
//        case token__ISLINUX: if (fISLINUX(p, nReturnExpressionType, bReturn)) _DONE_ break;
//        case token__ISMAC: if (fISMAC(p, nReturnExpressionType, bReturn)) _DONE_ break;
//        case token__ISWINDOWS: if (fISWINDOWS(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__ISNULL: if (fISNULL(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__ENCODE: if (fENCODE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__DECODE: if (fDECODE(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__LEFT: if (fLEFT(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__LEFTJUSTIFIED: if (fLEFTJUSTIFIED(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__LENGTH: 
        case token__LEN: if (fLEN(p, nReturnExpressionType, bReturn)) _DONE_ break;
//        case token__LINE: if (fLINE(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__LOG: if (fLOG(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__LOWER: 
        case token__LCASE: 
          if (fLCASE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__LTRIM: if (fLTRIM(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__MAX: if (fMAX(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__MID: if (fMID(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__MIN: if (fMIN(p, nReturnExpressionType, bReturn)) _DONE_ break;
//        case token__MODULE: if (fMODULE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__MSGBOX: if (fMSGBOX(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__PEEK: if (fPEEK(p)) _DONE_ break;

        case token__POKE: if (fPOKE(p)) _DONE_ break;
        case token__PREPEND: if (fPREPEND(p)) _DONE_ break;

        //case token__SYM_QM: 
        case token__PRINT: if (fPRINT(p)) _DONE_ break;

        case token__RANDOMIZE: if (fRANDOMIZE(p)) _DONE_ break;

        case token__REMOVE: if (fREMOVE(p)) _DONE_ break;
        case token__REPLACE: if (fREPLACE(p, nReturnExpressionType, bReturn)) _DONE_ break;
//        case token__RETURN: if (fRETURN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__REVERSED: if (fREVERSED(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__RIGHT: if (fRIGHT(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__RIGHTJUSTIFIED: if (fRIGHTJUSTIFIED(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__RANDOM: 
        case token__RND: if (fRND(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__RTRIM: if (fRTRIM(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__SECTION: if (fSECTION(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__SGN: if (fSGN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__SIMPLIFIED: if (fSIMPLIFIED(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__SIN: if (fSIN(p, nReturnExpressionType, bReturn)) _DONE_ break;
//        case token__SIZE: if (fSIZE(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__SPACE: if (fSPACE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__SPLIT: if (fSPLIT(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__STARTSWITH: if (fSTARTSWITH(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__STR: if (fSTR(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__STRCOMP: if (fSTRCOMP(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__READBINARY: if (fREADBINARY(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__WRITEBINARY: if (fWRITEBINARY(p)) _DONE_ break;
        case token__SEEKBINARY: if (fSEEKBINARY(p, nReturnExpressionType, bReturn)) _DONE_ break;

//        case token__ADDDATE: if (fADDDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ADDDAYS: if (fADDDAYS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ADDMONTHS: if (fADDMONTHS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ADDYEARS: if (fADDYEARS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        //case token__SUBDATE: if (fSUBDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__SUBDAYS: if (fSUBDAYS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__SUBMONTHS: if (fSUBMONTHS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__SUBYEARS: if (fSUBYEARS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        //case token__ADDTIME: if (fADDTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ADDHOURS: if (fADDHOURS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ADDMINUTES: if (fADDMINUTES(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ADDSECONDS: if (fADDSECONDS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        //case token__SUBTIME: if (fSUBTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__SUBHOURS: if (fSUBHOURS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__SUBMINUTES: if (fSUBMINUTES(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__SUBSECONDS: if (fSUBSECONDS(p, nReturnExpressionType, bReturn)) _DONE_; break;  

        case token__DAYOFWEEK: if (fDAYOFWEEK(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__DAYOFYEAR: if (fDAYOFYEAR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__DAYSINMONTH:  if (fDAYSINMONTH(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__DAYSINYEAR:   if (fDAYSINYEAR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__WEEKNUMBER:   if (fWEEKNUMBER(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ISLEAPYEAR:   if (fISLEAPYEAR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__DIFFDAY:    if (fDIFFDAY(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__DIFFSECONDS:  if (fDIFFSECONDS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ISDATEVALID:if (fISDATEVALID(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ISTIMEVALID: if (fISTIMEVALID(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__ISDATETIMEVALID: if (fISDATETIMEVALID(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__DAYNAME:  if (fDAYNAME(p, nReturnExpressionType, bReturn)) _DONE_; break;  

        case token__DAY: if (fDAY(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__MONTH: if (fMONTH(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__YEAR: if (fYEAR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__HOUR: if (fHOUR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__MINUTE: if (fMINUTE(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__SECOND: if (fSECOND(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__MONTHNAME:  if (fMONTHNAME(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__DATE:  if (fDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__TIME:  if (fTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;  
        case token__NOW:  if (fNOW(p, nReturnExpressionType, bReturn)) _DONE_; break;  

        //case token__STRING: if (fSTRING(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__STRREVERSE: if (fSTRREVERSE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__SQR: if (fSQR(p, nReturnExpressionType, bReturn)) _DONE_ break;
        //case token__SUB: if (fSUB(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__TAN: if (fTAN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__TRIM: if (fTRIM(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__TRIMMED: if (fTRIMMED(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__TRUNCATE: if (fTRUNCATE(p)) _DONE_ break;

//        case token__TYPE: if (fTYPE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__UPPER: 
        case token__UCASE: if (fUCASE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__UNICODE: if (fUNICODE(p, nReturnExpressionType, bReturn)) _DONE_ break;
        //case token__USING: if (fUSING(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__VALUE:
        case token__VAL: if (fVAL(p, nReturnExpressionType, bReturn)) _DONE_ break;

        case token__UTF8: if (fUTF8(p, nReturnExpressionType, bReturn))  _DONE_ break;
        case token__UTF16: if (fUTF16(p, nReturnExpressionType, bReturn))_DONE_ break;


      }

    }
  }

	_END_
}



bool parser::fKBASIC_STRING_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	const char *acIdentifier = "";

	if (fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

    if (utility::my_stricmp("String", acIdentifier) == 0 && parseTerm(token__SYM_DOT)){

      *nReturnExpressionType = 0;

      bool bObjectFake = false;

      //if (!(fNAMESPACECLASS(p, KBASIC_MATH))){ return false; }

      switch(peekToken()){
    case token__PEEK: if (fPEEK(p, bObjectFake)){ bReturn = false; _DONE_ break; }
    case token__POKE: if (fPOKE(p, bObjectFake)){ bReturn = false; _DONE_ break; }

    case token__LEN: 
    case token__LENGTH: 
      if (fLEN(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__INSTR: 
    case token__INDEXOF: 
      if (fINSTR(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__VAL: 
    case token__VALUE: 
      if (fVAL(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__PREPEND: if (fPREPEND(p, bObjectFake)) _DONE_; break;
    case token__APPEND: if (fAPPEND(p, bObjectFake)) _DONE_; break;
    case token__REMOVE: if (fREMOVE(p, bObjectFake)) _DONE_; break;
    case token__TRUNCATE: if (fTRUNCATE(p, bObjectFake)) _DONE_; break;
    case token__INSERT: if (fINSERT(p, bObjectFake)) _DONE_; break;
    case token__FILL: if (fFILL(p, bObjectFake)) _DONE_; break;

    case token__COMPARE: if (fCOMPARE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__CONTAINS: if (fCONTAINS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__COUNT: if (fCOUNT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__ENDSWITH: if (fENDSWITH(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__STARTSWITH: if (fSTARTSWITH(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__LEFTJUSTIFIED: if (fLEFTJUSTIFIED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__RIGHTJUSTIFIED: if (fRIGHTJUSTIFIED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__SECTION: if (fSECTION(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__SIMPLIFIED: if (fSIMPLIFIED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__TRIMMED: if (fTRIMMED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__REVERSED: if (fREVERSED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__UNICODE: if (fUNICODE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;

    case token__READBINARY: if (fREADBINARY(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__WRITEBINARY: if (fWRITEBINARY(p, bObjectFake)) _DONE_ break;
    case token__SEEKBINARY: if (fSEEKBINARY(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__ASC: if (fASC(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__FORMAT: if (fFORMAT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__ENCODE: if (fENCODE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__DECODE: if (fDECODE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__LEFT: if (fLEFT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__LEFT_: if (fLEFT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;      
    case token__RIGHT: if (fRIGHT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__RIGHT_: if (fRIGHT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__LCASE: 
    case token__LOWER: 
      if (fLCASE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__LCASE_: if (fLCASE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__UCASE: 
    case token__UPPER: 
      if (fUCASE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__UCASE_: if (fUCASE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__LTRIM: if (fLTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__LTRIM_: if (fLTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__RTRIM: if (fRTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__RTRIM_: if (fRTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__TRIM: if (fTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__TRIM_: if (fTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__MID: if (fMID(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__MID_: if (fMID(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__STRCOMP: if (fSTRCOMP(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__SPLIT: if (fSPLIT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__INSTREV: 
    case token__LASTINDEXOF:       
      if (fINSTREV(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__REPLACE: if (fREPLACE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__STRREVERSE: if (fSTRREVERSE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__UTF8: if (fUTF8(p, nReturnExpressionType, bReturn, bObjectFake))  _DONE_ break;
    case token__UTF16: if (fUTF16(p, nReturnExpressionType, bReturn, bObjectFake))_DONE_ break;
      }

    }
  }

	_END_
}

bool parser::fKBASIC_DATETIME_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	const char *acIdentifier = "";

	if (fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

    if (utility::my_stricmp("DateTime", acIdentifier) == 0 && parseTerm(token__SYM_DOT)){

      *nReturnExpressionType = 0;

      bool bObjectFake = false;

      //if (!(fNAMESPACECLASS(p, KBASIC_MATH))){ return false; }

      switch(peekToken()){

//    case token__ADDDATE: if (fADDDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ADDDAYS: if (fADDDAYS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ADDMONTHS: if (fADDMONTHS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ADDYEARS: if (fADDYEARS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    //case token__SUBDATE: if (fSUBDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__SUBDAYS: if (fSUBDAYS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__SUBMONTHS: if (fSUBMONTHS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__SUBYEARS: if (fSUBYEARS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    //case token__ADDTIME: if (fADDTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ADDHOURS: if (fADDHOURS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ADDMINUTES: if (fADDMINUTES(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ADDSECONDS: if (fADDSECONDS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    //case token__SUBTIME: if (fSUBTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__SUBHOURS: if (fSUBHOURS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__SUBMINUTES: if (fSUBMINUTES(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__SUBSECONDS: if (fSUBSECONDS(p, nReturnExpressionType, bReturn)) _DONE_; break;  

    case token__DAYOFWEEK: if (fDAYOFWEEK(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__DAYOFYEAR: if (fDAYOFYEAR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__DAYSINMONTH:  if (fDAYSINMONTH(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__DAYSINYEAR:   if (fDAYSINYEAR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__WEEKNUMBER:   if (fWEEKNUMBER(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ISLEAPYEAR:   if (fISLEAPYEAR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__DIFFDAY:    if (fDIFFDAY(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__DIFFSECONDS:  if (fDIFFSECONDS(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ISDATEVALID:if (fISDATEVALID(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ISTIMEVALID: if (fISTIMEVALID(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__ISDATETIMEVALID: if (fISDATETIMEVALID(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__DAYNAME:  if (fDAYNAME(p, nReturnExpressionType, bReturn)) _DONE_; break;  

    case token__DAY: if (fDAY(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__MONTH: if (fMONTH(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__YEAR: if (fYEAR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__HOUR: if (fHOUR(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__MINUTE: if (fMINUTE(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__SECOND: if (fSECOND(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__MONTHNAME:  if (fMONTHNAME(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__DATE:  if (fDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__TIME:  if (fTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__NOW:  if (fNOW(p, nReturnExpressionType, bReturn)) _DONE_; break;  
      
      }
    }
  }

	_END_
}

bool parser::fKBASIC_CAST_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	const char *acIdentifier = "";

	if (fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

    if (utility::my_stricmp("Cast", acIdentifier) == 0 && parseTerm(token__SYM_DOT)){

      *nReturnExpressionType = 0;

      //if (!(fNAMESPACECLASS(p, KBASIC_MATH))){ return false; }

      switch(peekToken()){
    case token__TYP_BYTE: 
    case token__TYP_SHORT: 
    case token__TYP_INTEGER: 
    case token__TYP_LONG: 
    case token__TYP_BOOLEAN: 
    //case token__TYP_QSTRING: 
    //case token__TYP_CSTRING: 
    case token__TYP_SINGLE: 
    case token__TYP_DOUBLE: 
    case token__TYP_CURRENCY: 
    //case token__TYP_DATE: 
      if (fCAST(p, nReturnExpressionType, bReturn)) _DONE_; break;    
    
    case token__STRING: if (fSTRING(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DATE: if (fDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;

      }

    }
  }

	_END_
}

/**
[KBASIC]
NAME: KBASIC.MATH
PRINTNAME: KBasic.Math.*
TASK: math operations
DESC: 
DESCEND: 
METHOD1: Static Function ABS (numerical expression) AS DOUBLE METHODDESC:' Returns the absolute value of an argument.
METHOD2: Static Function ATN ( number ) AS DOUBLE METHODDESC:' returns the arctangent value of the argument 'number' in radians
METHOD3: Static Function COS ( number ) AS DOUBLE METHODDESC:' returns the cosine of the argument 'number' in radians.
METHOD4: Static Function SIN ( number ) AS DOUBLE METHODDESC:' returns the sine of the argument 'number' in radians.
METHOD5: Static Function EXP ( number ) AS DOUBLE METHODDESC:' returns the exponential value of 'number'.
METHOD6: Static Function LOG (n AS DOUBLE) AS LONG METHODDESC:' returns a the natural logaritm of a number.
METHOD7: Static Function SGN( number ) AS INTEGER METHODDESC:' returns the sign of the argument 'number'.
METHOD8: Static Function FIX( number ) AS LONG METHODDESC:' cuts off the trail of a number
METHOD9: Static Function INT( number ) AS LONG METHODDESC:' returns the next integer number <= given number
METHOD10: Static Function SQR( number ) AS LONG METHODDESC:' returns the square root of the argument 'number'.
METHOD11: Static Function TAN( number ) AS LONG METHODDESC:' returns the tangent of the argument 'number' in radians.
METHOD12: Static Function RND( number ) AS DOUBLE METHODDESC:' returns an integer pseudo-random number between 0 and int(EXPR)-1 inclusive.
METHOD13: Static Function MIN (numeric expression1, numeric expression2) METHODDESC:' returns the minor value of two values
METHOD14: Static Function MAX (numeric expression1, numeric expression2) METHODDESC:' returns the major value of two values

EXAMPLES: math.kbasic
CATEGORY: CLASS, KBASIC, KBASIC.MATH, NAMESPACE
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fKBASIC_MATH_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	const char *acIdentifier = "";

	if (fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

    if (utility::my_stricmp("Math", acIdentifier) == 0 && parseTerm(token__SYM_DOT)){

      switch(peekToken()){
        case token__ABS: if (fABS(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__ATN: if (fATN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__COS: if (fCOS(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__SIN: if (fSIN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__EXP: if (fEXP(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__LOG: if (fLOG(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__SGN: if (fSGN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__FIX: if (fFIX(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__INT: if (fINT(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__SQR: if (fSQR(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__TAN: if (fTAN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__RND: if (fRND(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__MIN: if (fMIN(p, nReturnExpressionType, bReturn)) _DONE_ break;
        case token__MAX: if (fMAX(p, nReturnExpressionType, bReturn)) _DONE_ break;
        //case token__SEC: if (fSEC(p, nReturnExpressionType, bReturn)) _DONE_ break;
    //    case token__FACT: if (fFACT(p, nReturnExpressionType, bReturn)) _DONE_ break;
    //    case token__FRAC: if (fFRAC(p, nReturnExpressionType, bReturn)) _DONE_ break;
    //    case token__LOGB: if (fLOGB(p, nReturnExpressionType, bReturn)) _DONE_ break;
    //    case token__HYPOT: if (fHYPOT(p, nReturnExpressionType, bReturn)) _DONE_ break;
        //case token__LOC: if (fLOC(p, nReturnExpressionType, bReturn)) _DONE_ break;

      }

    }
  }

	_END_
}

/**
[KBASIC]
NAME: KBASIC.STRING
PRINTNAME: KBasic.String.*
TASK: stores and manipulates text
DESC: 
DESCEND: 
METHOD1: Function Len() As Integer METHODDESC:' returns the length of a string or the size of a variable in bytes.
METHOD2: Function InStr() [start AS INTEGER ,] sub AS STRING) As Integer METHODDESC:' finds one string inside another.
METHOD3: Function Val() As Double METHODDESC:' returns the numerical value of the string.
METHOD4: Function Asc() As Integer METHODDESC:' returns the ASCII code for a character.
METHOD5: Function Left(howMany As Integer) As String METHODDESC:' returns a string containing the first characters of a string.
METHOD6: Function Right(howMany As Integer) As String METHODDESC:' returns the remaining string after truncating the source string's length according to the desired length and returns the truncated string.
METHOD7: Function LCase() As String METHODDESC:' returns a new string. It contains the source string converted to all lower case.
METHOD8: Function UCase() As String METHODDESC:' returns a new string. It contains the source string converted to all upper case.
METHOD9: Function Trim() As String METHODDESC:' removes the source string's leading and trailing spaces.
METHOD10: Function RTrim() As String METHODDESC:' function removes the source string's last spaces.
METHOD11: Function LTrim() As String METHODDESC:' removes the source string's trailing spaces, from the end of the source string.
METHOD12: Function Mid(start As Integer [, length As Integer]) As String METHODDESC:' get the part of a string
METHOD13: Function StrComp(string [, compare]) As String METHODDESC:' compares to strings
METHOD14: Function Replace(pattern As String, replace As String) As String METHODDESC:' replaces string occurances with another string
METHOD15: Function StrReverse() As String METHODDESC:' returns a given string reversed
EXAMPLES: string.kbasic
CATEGORY: CLASS, KBASIC, KBASIC.STRING, NAMESPACE
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fKBASIC_STRING_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	if (!proceedParse()) return false;

  bool bPeek = false;
  bool bReadBinary = false;
  bool bWriteBinary = false;
  bool bSeekBinary = false;

  if (with_pos_list_POS == -1){
    // *** look forward if dot is present in line
    bool bRet = true;
    int nTest = 0;

    //_BEGIN_

	  do {

		  nTest = peekToken();
      

		  if (nTest == token__MSC_EOL){
        _END_      
      } else if (nTest == token__SYM_DOT){ //  dangerous nur auf eol prfen? rem : 
        if (peekToken(1) == token__PEEK) bPeek = true;
        if (peekToken(1) == token__READBINARY) bReadBinary = true;
        if (peekToken(1) == token__WRITEBINARY) bWriteBinary = true;
        if (peekToken(1) == token__SEEKBINARY) bSeekBinary = true;
			  break;
		  }

	  } while(proceedParse() && bRet && (bRet = nextToken()));

    _END2_
    // ***
  }

#ifdef KBDEBUG
  if (stopAtLine(10)){
    int i = 9;
    i++;
  }
#endif

	if (bPeek && fVARIABLE(p, &nPeekVar, &PeekScope, &nPeekType)){ 
    if (!(parseTerm(token__SYM_DOT))){ _END_ }    
    if (peekToken() == token__PEEK){

       if (nPeekType == token__ME){
           { semanticError(token__PEEK, "PEEK not allowed in combination with ME"); _ERROR_ }
       } else if (nPeekType == token__PARENT){
           { semanticError(token__PEEK, "PEEK not allowed in combination with PARENT"); _ERROR_ }
       } else if (!memory_type::isString(nPeekType)){
           { semanticError(token__PEEK, "PEEK not allowed in combination with non-String variable"); _ERROR_ }
       } else {
         if (bProducePcode){
            p->wr_PUSH_ID(pcode__PUSH_ID, nPeekVar, PeekScope, false);
         }
       }

       if (fPEEK(p, true)){ bReturn = false; _DONE_ }
     }
    
      _ERROR_
    }

	if (bReadBinary && fVARIABLE(p, &nPeekVar, &PeekScope, &nPeekType) && nPeekType == pcode__QString){ 
    if (!(parseTerm(token__SYM_DOT))){ _END_ }    
    if (peekToken() == token__READBINARY){

       {
         if (bProducePcode){
            p->wr_PUSH_ID(pcode__PUSH_ID, nPeekVar, PeekScope, false);
         }
       }

       if (fREADBINARY(p, nReturnExpressionType, bReturn, true)){ _DONE_ }
     }
    
      _ERROR_
    }

	if (bWriteBinary && fVARIABLE(p, &nPeekVar, &PeekScope, &nPeekType) && nPeekType == pcode__QString){ 
    if (!(parseTerm(token__SYM_DOT))){ _END_ }    
    if (peekToken() == token__WRITEBINARY){
      {
         if (bProducePcode){
            p->wr_PUSH_ID(pcode__PUSH_ID, nPeekVar, PeekScope, false);
         }
       }

       if (fWRITEBINARY(p, true)){ _DONE_ }
     }
    
      _ERROR_
    }

	if (bSeekBinary && fVARIABLE(p, &nPeekVar, &PeekScope, &nPeekType) && nPeekType == pcode__QString){ 
    if (!(parseTerm(token__SYM_DOT))){ _END_ }    
    if (peekToken() == token__SEEKBINARY){
       {
         if (bProducePcode){
            p->wr_PUSH_ID(pcode__PUSH_ID, nPeekVar, PeekScope, false);
         }
       }

       if (fSEEKBINARY(p, nReturnExpressionType, bReturn, true)){ _DONE_ }
     }
    
      _ERROR_
    }


  bool bQSTRING;
  if ((bQSTRING = fEXPRESSION2(p, pcode__QSTRING, true)));
  else if (fEXPRESSION2(p, pcode__CSTRING, true)); 
  else { _END_ }


  if (!(parseTerm(token__SYM_DOT))){ _END_ }    

  static bool bObjectFake = true;

  switch(peekToken()){
    //case token__PEEK: if (fPEEK(p, bObjectFake)){ bReturn = false; _DONE_ break; }
    case token__POKE: if (fPOKE(p, bObjectFake)){ bReturn = false; _DONE_ break; }

    case token__LEN: 
    case token__LENGTH: 
      if (fLEN(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__INSTR: 
    case token__INDEXOF: 
      if (fINSTR(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__VAL: 
    case token__VALUE: 
      if (fVAL(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__PREPEND: if (fPREPEND(p, bObjectFake)) _DONE_; break;
    case token__APPEND: if (fAPPEND(p, bObjectFake)) _DONE_; break;
    case token__REMOVE: if (fREMOVE(p, bObjectFake)) _DONE_; break;
    case token__TRUNCATE: if (fTRUNCATE(p, bObjectFake)) _DONE_; break;
    case token__INSERT: if (fINSERT(p, bObjectFake)) _DONE_; break;
    case token__FILL: if (fFILL(p, bObjectFake)) _DONE_; break;

    case token__COMPARE: if (fCOMPARE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__CONTAINS: if (fCONTAINS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__COUNT: if (fCOUNT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__ENDSWITH: if (fENDSWITH(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__STARTSWITH: if (fSTARTSWITH(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__LEFTJUSTIFIED: if (fLEFTJUSTIFIED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__RIGHTJUSTIFIED: if (fRIGHTJUSTIFIED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__SECTION: if (fSECTION(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__SIMPLIFIED: if (fSIMPLIFIED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__TRIMMED: if (fTRIMMED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__REVERSED: if (fREVERSED(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
    case token__UNICODE: if (fUNICODE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;
/*
    case token__READBINARY: if (fREADBINARY(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__WRITEBINARY: if (fWRITEBINARY(p, bObjectFake)) _DONE_ break;
    case token__SEEKBINARY: if (fSEEKBINARY(p, bObjectFake)) _DONE_ break;
*/
    case token__ASC: if (fASC(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__FORMAT: if (fFORMAT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__ENCODE: if (fENCODE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__DECODE: if (fDECODE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__LEFT: if (fLEFT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__LEFT_: if (fLEFT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;      
    case token__RIGHT: if (fRIGHT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__RIGHT_: if (fRIGHT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__LCASE: 
    case token__LOWER: 
      if (fLCASE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__LCASE_: if (fLCASE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__UCASE: 
    case token__UPPER: 
      if (fUCASE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__UCASE_: if (fUCASE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__LTRIM: if (fLTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__LTRIM_: if (fLTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__RTRIM: if (fRTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__RTRIM_: if (fRTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__TRIM: if (fTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__TRIM_: if (fTRIM(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__MID: if (fMID(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__MID_: if (fMID(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__STRCOMP: if (fSTRCOMP(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__SPLIT: if (fSPLIT(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__INSTREV: 
    case token__LASTINDEXOF:       
      if (fINSTREV(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;

    case token__REPLACE: if (fREPLACE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__STRREVERSE: if (fSTRREVERSE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_ break;
    case token__UTF8: if (fUTF8(p, nReturnExpressionType, bReturn, bObjectFake)) *nReturnExpressionType = bQSTRING ? pcode__QSTRING : pcode__CSTRING; _DONE_ break;
    case token__UTF16: if (fUTF16(p, nReturnExpressionType, bReturn, bObjectFake))*nReturnExpressionType = bQSTRING ? pcode__QSTRING : pcode__CSTRING; _DONE_ break;
  }

	_END_
}


bool parser::fKBASIC_DATETIME_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	if (!proceedParse()) return false;

  if (with_pos_list_POS == -1){
    // *** look forward if dot is present in line
    bool bRet = true;
    int nTest = 0;


	  do {

		  nTest = peekToken();      

		  if (nTest == token__MSC_EOL){
        _END_
      } else if (nTest == token__SYM_DOT){ //  dangerous nur auf eol prfen? rem : 
			  break;
		  }

	  } while(proceedParse() && bRet && (bRet = nextToken()));

    _END2_
    // ***
  }

#ifdef KBDEBUG
  if (stopAtLine(10)){
    int i = 9;
    i++;
  }
#endif

  int k = peekToken();      

  if (fEXPRESSION2(p, pcode__DATE, true)); 
  else { _END_ }    

  if (!(parseTerm(token__SYM_DOT))){ _END_ }    

  static bool bObjectFake = true;

  switch(peekToken()){

//    case token__ADDDATE: if (fADDDATE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__ADDDAYS: if (fADDDAYS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__ADDMONTHS: if (fADDMONTHS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__ADDYEARS: if (fADDYEARS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    //case token__SUBDATE: if (fSUBDATE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__SUBDAYS: if (fSUBDAYS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__SUBMONTHS: if (fSUBMONTHS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__SUBYEARS: if (fSUBYEARS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    //case token__ADDTIME: if (fADDTIME(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__ADDHOURS: if (fADDHOURS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__ADDMINUTES: if (fADDMINUTES(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__ADDSECONDS: if (fADDSECONDS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    //case token__SUBTIME: if (fSUBTIME(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__SUBHOURS: if (fSUBHOURS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__SUBMINUTES: if (fSUBMINUTES(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__SUBSECONDS: if (fSUBSECONDS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  

    case token__DAYOFWEEK: if (fDAYOFWEEK(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__DAYOFYEAR: if (fDAYOFYEAR(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__DAYSINMONTH:  if (fDAYSINMONTH(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__DAYSINYEAR:   if (fDAYSINYEAR(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__WEEKNUMBER:   if (fWEEKNUMBER(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__ISLEAPYEAR:   if (fISLEAPYEAR(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__DIFFDAY:    if (fDIFFDAY(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__DIFFSECONDS:  if (fDIFFSECONDS(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  

    case token__DAY: if (fDAY(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__MONTH: if (fMONTH(p, nReturnExpressionType, bReturn), bObjectFake) _DONE_; break;  
    case token__YEAR: if (fYEAR(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__HOUR: if (fHOUR(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__MINUTE: if (fMINUTE(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  
    case token__SECOND: if (fSECOND(p, nReturnExpressionType, bReturn, bObjectFake)) _DONE_; break;  

  }

	_END_
}



