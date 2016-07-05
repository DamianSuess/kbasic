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
#include "../kbshared/cache.h"


/* *
[EXPLANATION]
NAME: SCOPE
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: SCOPE CLASS LOCAL STATIC
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: SCOPE CLASS LOCAL INSTANCE
DESC:
SEEALSO:
*/


// ***
// global parts of class: global class vars (instance, static)
bool parser::isScopeClass(){ return strcmp(getClass(), "") != 0; } 
// global static code part of class
bool parser::isScopeClassStaticCode(){ return strcmp(getClass(), "") != 0 && bCurrentClassStatic; } 
// local parts of class
bool parser::isScopeClassLocalStatic(){	return isScopeClass() && strcmp(getMethod(), "") != 0 && bScopeClassStatic; }
bool parser::isScopeClassLocalInstance(){	return isScopeClass() && strcmp(getMethod(), "") != 0 && !isScopeClassLocalStatic(); }

bool parser::isScopeClassPropertySet(){	return isScopeClass() && isScopeClassLocalInstance() && bScopeClassPropertySet; }
bool parser::isScopeClassPropertyGet(){	return isScopeClass() && isScopeClassLocalInstance() && bScopeClassPropertyGet; }



// ***


/* *
[EXPLANATION]
NAME: SCOPE MODULE LOCAL STATIC
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: SCOPE MODULE LOCAL
DESC:
SEEALSO:
*/
// ***
// global parts of module: global module vars
bool parser::isScopeModule(){	return !isScopeClass(); }
// local parts of module
bool parser::isScopeModuleLocal(){ return isScopeModule() && strcmp(getSub(), "") != 0 && !isScopeModuleLocalStatic(); }
bool parser::isScopeModuleLocalStatic(){ return isScopeModule() && strcmp(getSub(), "") != 0 && bIsLocalStatic; }
// ***

/* *
[EXPLANATION]
NAME: SCOPE GLOBAL
DESC:
SEEALSO:
*/
// ***
// neither class nor module
//bool parser::isScopeGlobal(){ return (strcmp(getModule(), acDefaultModuleName) == 0 && !isScopeClass(); }

bool parser::isScopeDefaultGlobal(){ return strcmp(getModule(), acDefaultModuleName) == 0 && !isScopeClass(); }
// ***

// class global vars/consts, module global vars/consts
bool parser::isScopeGlobal()
{
  return !isScopeLocal() && !isScopeDefaultGlobal();
}

bool parser::isScopeLocal(){ return (strcmp(getSub(), "") != 0 || strcmp(getMethod(), "") != 0); } // && !isScopeDefaultGlobal(); }

bool parser::setScopeModule(const char *acModule, const char *acSub, const char *acRealSub)
{
  sCurrentSub = acSub;
  sCurrentRealSub = acRealSub;
  sCurrentClass = "";
  sCurrentModule = acModule;
  bCurrentClassStatic = false;

  return true;
}

bool parser::setScopeClass(const char *acParentClass, const char *acClass, const char *acSub, const char *acRealSub)
{
  sCurrentSub = acSub;
  sCurrentRealSub = acRealSub; 
  sCurrentClass = acClass;
  sCurrentModule = acDefaultModuleName;
  bCurrentClassStatic = false;

  return true;
}
bool parser::setScopeClassStatic(bool b)
{
  bCurrentClassStatic = b;

  return true;
}

bool parser::setScopeDefaultGlobal()
{
  sCurrentSub = "";
  sCurrentRealSub = "";
  bSubVarStatic = false; // register global
  sCurrentClass = "";
  sCurrentModule = acDefaultModuleName;
  bCurrentClassStatic = false;

  return true;
}

const char *parser::getScope	()
{	
	if (strcmp(getModule(), acDefaultModuleName) != 0){
		return getModule();
	} else if (strcmp(getClass(), "") != 0){
		return getClass();
	}
	return acDefaultModuleName; 
}

const char *parser::getModule	(){	return sCurrentModule.ascii(); }
const char *parser::getSub		(){	return sCurrentSub.ascii(); }
const char *parser::getRealSub		(){	return sCurrentRealSub.ascii(); }
const char *parser::getMethod		(){	return sCurrentSub.ascii(); }
const char *parser::getRealMethod		(){	return getRealSub(); }
const char *parser::getClass		(){	return sCurrentClass.ascii(); }

bool parser::isSubVarStatic		(){	return bSubVarStatic; }

int parser::getBlockNo		(){	return nCurrentBlockNo; } //  dim in blöcken realisieren

/* *
[EXPLANATION]
NAME: PARENT CLASS
DESC:
SEEALSO:
*/
const char *parser::getParentClass		(){	return myClass->getParentName(myClass->getId(getClass())); }

bool parser::nextToken(bool b)
{
  static t_token nLastToken = 0;
  static t_token nTest = 0;
  //register int nn = b ? getTokenPos() : myToken->getPos();

  nLastToken = nTest;
  nTest = myToken->rd_Token( b ? getTokenPos() : myToken->getPos() );
  
  // test for WITH 
  switch (nTest){
    case token__REM_MULTILINE_STOP: 	
    case token__REM_MULTILINE:    
    case token__REM_DOCUMENTATION:  
   	case token__MSC_EOL: 		 
		case token__MSC_LABEL:
		case token__MSC_LINE:
		case token__SYM_COLON: 	
      with.WithToken = token__MSC_EOL;
			break;
		default:
      with.WithToken = 0;
			break;
	}

  switch (nTest){
	  case token__KB_LINE:
		  	nCurrentLine = myToken->rd_Integer( b ? getTokenPos() : myToken->getPos() );
			  return true;					
    }

  setCurrentRow(myToken->getRowStart());

  //int p = b ? getTokenPos() : myToken->getPos();

//	if (parser::not_supported(nTest)){ semanticError(token__KEYWORD, utility::con(nTest, " Sorry! Keyword or Builtin not supported yet") ); _ERROR_ }
  //if (deprecated(nTest)){ semanticError(token__KEYWORD,  utility::con(nTest, " keyword/builtin is deprecated") ); }
	//if (not_implemented(nTest)){ semanticError(token__KEYWORD,  utility::con(nTest, " keyword/builtin has not been implemented yet") ); _ERROR_ }
//	if (unstable(nTest)){ semanticError(token__KEYWORD,  utility::con(nTest, " is unstable; ready only for testing purpose") ); _ERROR_ }

  switch (nTest){

		// all kbasic keywords and builtin, in alphabetic order      
    case token____CLASS__: 	     break;
    case token____LINE__: 	     break;
    case token____MODULE__: 	     break;
    case token____SCOPE__: 	     break;
    case token____SUB__: 	     break;
    case token____ISLINUX__: 	     break;
    case token____ISWINDOWS__: 	     break;
    case token____ISMACOS__: 	     break;
    case token____FILE__: 	     break;
    case token____ISCLASS__: 	     break;
    case token____ISMODULE__: 	     break;
    case token____ISSUB__: 	     break;

    case token___DYNAMIC: 			break;
    case token___STATIC: 			break;
    case token___ELSE: 			break;
    case token___END: 			break;
    case token___EXTERNALSOURCE:     break;
    case token___IF:
    case token___REGION:     break;
    case token__ABS: 	   break;
    case token__ABSOLUTE:     break; 
    case token__ABSTRACT: 	    break;
    case token__ACCESS: 	   break;
    case token__ACS: 	   break;
    case token__ADDHANDLER:   break;
    case token__ADDRESSOF: 				break;
    case token__ALIAS:     break; 	
    case token__ANSI:     break; 	
    case token__APPACTIVATE:   break;
    case token__APPEND: 	   break;
    case token__ARRAY: 	   break;
    case token__AS: 				break;
    case token__ASC: 	   break;
    case token__ASN: 	   break;
    case token__ASSEMBLY:     break; 
    case token__ATN: 	   break;
    case token__AUTO:     break; 	
    case token__BASE: 		break;
    case token__BEEP: 	    break;
    case token__BIN_: 	    break;
    case token__BIN: 	    break;
    case token__BINARY: 	    break;
    case token__BLOAD: 	    break;
    case token__BSAVE: 	    break;
    case token__BY_REF: 		break;
    case token__BY_VAL: 		break;
    case token__CALL: 			break;
    case token__CALLBYNAME:     break; 
    case token__CASE: 			break;
    case token__CATCH: 	    break;
    case token__CBOOL:  	    break;
    case token__CBCD: 	    break;
    case token__CBYTE: 	    break;
    case token__CCHAR:   break; 
    case token__CCUR: 	    break;
    case token__CDATE: 	    break;
    case token__CDBL: 	    break;
    case token__CDEC:   break; 
    case token__CEXT:   break; 
    case token__CFIX:   break; 
    case token__CHAIN:     break; 	
    case token__CHDIR: 	     break;
    case token__CHDRIVE:   break;
    case token__CHOOSE: 	     break;
    case token__CHR_: 	   break;
    case token__CHR: 	   break;
    case token__CINT: 	    break;
    case token__CIRCLE: 	    break;
    case token__CLASS_INITIALIZE: 	    break;
    case token__CLASS_TERMINATE: 	    break;
    case token__CLASS: 	      break;
    case token__CLEAR: 	    break; 
    case token__CLNG: 	    break;
    case token__CLOSE: 	     break;
    case token__CLS: 	   break;
    case token__COBJ:   break; 
    case token__COLOR: 	     break;
    case token__COM:     break; 		
    case token__COMMAND_: 	     break;
    case token__COMMAND:     break; 		
    case token__COMMON:     break; 		
    case token__COMPARE: 	break;
    case token__CONNECT: 	break;
    case token__CONST: 	break;
    case token__CONSTRUCTOR:	    break;
    case token__COS: 	   break;
    case token__CREATEOBJECT:     break; 
    case token__CSHORT:   break; 
    case token__CSNG: 	    break;
    case token__CSRLIN: 	   break;
    case token__CTYPE:   break; 
    case token__CURDIR_: 	     break;
    case token__CURDIR: 	     break;
    case token__CVD:   break; 
    case token__CVDMBF:   break; 
    case token__CVERR: 	     break;
    case token__CVI:   break; 
    case token__CVL:   break; 
    case token__CVS:   break; 
    case token__CVSMBF:   break; 
    case token__CQUD:   break; 
    case token__DATA: 			break;
    case token__DATABASE:     break; 		      
    case token__DATETIME:     break; 		      
    case token__DATE: 	   break;
    case token__DATE_: 	   break;
    case token__DATEADD: 	   break;
    case token__DATEDIFF: 	   break;
    case token__DATEPART: 	   break;
    case token__DATESERIAL: 	   break;
    case token__DATEVALUE: 	   break;
    case token__DAY: 	   break;
    case token__DDB:   break; 
    case token__DEBUG: 				break;
    case token__DECIMAL:     break; 		
    case token__DECLARE:     break; 	
    case token__DEF: 			break;
    case token__DEFAULT:     break; 	
    case token__DEFBOOL: 			break;
    case token__DEFBYTE: 			break;
    case token__DEFCUR: 			break;
    case token__DEFDATE: 			break;
    case token__DEFDBL: 			break;
    case token__DEFINT: 			break;
    case token__DEFLNG: 			break;
    case token__DEFOBJ: 			break;
    case token__DEFSNG: 			break;
    case token__DEFSTR: 			break;
    case token__DEFVAR: 			break;
    case token__DEG: 	   break;
    case token__DELEGATE:     break; 
    case token__DELETESETTING:   break; 
    case token__DESTRUCTOR:	    break;
    case token__DIM: 			break;
    case token__DIR_: 	   break;
    case token__DIR: 	   break;
    case token__DIRECTCAST:     break;
    case token__DISCONNECT:     break;
    case token__DO: 				break;
    case token__DOEVENTS: 	     break;
    case token__DOF: 	   break;
    case token__DRAW:   break; 
    case token__EACH: 			break;
    case token__ECHO: 			break;
    case token__ELSE: 			break;
    case token__ELSEIF: 		break;
    case token__EMPTY:     break; 	
    case token__END: 			break;
    case token__ENDIF:			break;
    case token__ENUM:	    break;
    case token__ENVIRON_:     break; 	
    case token__ENVIRON:     break; 		
    case token__EOF_: 	    break;
    case token__ERASE:			break;
    case token__ERDEV:     break; 		
    case token__ERL:			break;
    case token__ERR:			break;
    case token__ERROR_:			break;
    case token__ERROR:			break;
    case token__EVENT:     break; 		
    case token__EXIT:			break;
    case token__EXP: 	   break;
    case token__EXPLICIT:	break;
    case token__FACT: 	    break;
    case token__FIELD: 	     break;
    case token__FILE: 	     break;
    case token__FILEATTR: 	     break;
    case token__FILECOPY:   break; 
    case token__FILEDATETIME: 	     break;
    case token__FILELEN: 	     break;
    case token__FILES: 	     break;
    case token__FILTER:   break; 
    case token__FINALLY: 				break;
    case token__FIX: 	   break;
    case token__FN: 				break;
    case token__FOR: 			break;
    case token__FORMAT_: 	   break;
    case token__FORMAT: 	   break;
    case token__FORMATCURRENCY:   break; 
    case token__FORMATDATETIME:   break; 
    case token__FORMATNUMBER:   break; 
    case token__FORMATPERCENT:   break;
    case token__FRAC: 	    break;
    case token__FRE: 	    break;
    case token__FREEFILE: 	    break;
    case token__FRIEND:
    case token__FUNCTION:	break;
    case token__FV:   break; 
    case token__GET: 	    break;
    case token__GETALLSETTINGS:   break; 
    case token__GETATTR: 	     break;			
    case token__GETAUTOSERVERSETTINGS:   break; 
    case token__GETOBJECT:   break; 
    case token__GETSETTING:   break; 
    case token__GETTYPE:   break; 
    case token__GLOBAL:   break; 
    case token__GOSUB: 		break;
    case token__GOTO: 			break;
    case token__HANDLES:     break; 	
    case token__HEX_: 	   break;
    case token__HEX: 	   break;
    case token__HOUR: 				break;
    case token__HYPOT: 	     break;
    case token__IF: 				break;
    case token__IIF: 				break;
    case token__IMESTATUS:   break; 
    case token__IMPLEMENTS:     break; 
    case token__IMPORTS:     break; 	
    case token__IN: 				break;
    case token__INHERITS:     break; 	
    case token__INKEY_: 	     break;
    case token__INKEY: 	     break;
    case token__INP:   break; 
    case token__INPUT: 	     break;
    case token__INPUT_: 	     break;      
    case token__INPUTBOX: 				break;
    case token__INSTR: 	     break;
    case token__INSTREV:   break;
    case token__INT: 				break;
    case token__INTERFACE: 	   break;
    case token__IOCTL_:   break;
    case token__IOCTL:   break;
    case token__IPMT:   break; 
    case token__IRR:   break; 
    case token__IS: 				break;

    case token__ISARRAY: break;
    case token__ISBOOLEAN: break;
    case token__ISBYTE: break;
    case token__ISCSTRING:  break;
    case token__ISCURRENCY: break;
    case token__ISDATE: break;
    case token__ISDOUBLE:  break;
    case token__ISEMPTY:  break;
    case token__ISERROR:  break;
    case token__ISINTEGER:  break;
    case token__ISMISSING: break;
    case token__ISNULL: break;
    case token__ISNUMERIC:  break;
    case token__ISOBJECT:  break;
    case token__ISSHORT:  break;
    case token__ISSINGLE:  break;
    case token__ISLONG: break;
    case token__ISSTRING: break;
    case token__ISVARIANT: break;

    case token__ISLINUX: break;
    case token__ISMAC: break;
    case token__ISWINDOWS: break;

    case token__ITERATE: 				break;
    case token__JOIN:   break; 
    case token__KBASIC:	break;
    case token__KEY:     break; 		
    case token__KBASICDIR: 	    break;
    case token__KILL: 	    break;
    case token__LBOUND: 			break;
    case token__LCASE_: 	     break;
    case token__LCASE: 	     break;
    case token__LEFT_: 	    break;
    case token__LEFT: 	    break;
    case token__LEN: 	   break;
    case token__LET: 			break;
    case token__LIB:     break; 	
    case token__LIKE: 			break;
    case token__LINE:   break; 
    case token__LN: 	  break;
    case token__LOAD:   break; 
    case token__LOADPICTURE:   break; 
    case token__LOADRESDATA:   break; 
    case token__LOADRESPICTURE:   break;
    case token__LOADRESSTRING:
    case token__LOC: 	      break;
    case token__LOCATE: 	      break;
    case token__LOCK:   break;
    case token__LOF: 	   break;
    case token__LOG: 	   break;
    case token__LOGB: 	    break;
    case token__LOOP: 			break;
    case token__LPOS:   break;
    case token__LPRINT:   break; 
    case token__LSET: 			break;
    case token__LTRIM_: 	     break;
    case token__LTRIM: 	     break;
    case token__MAX: 	   break;
    case token__ME: 				break;
    case token__MID_: 	   break;
    case token__MID: 			break;
    case token__MIN: 	   break;
    case token__MINUTE: 	    break;
    case token__MIRR:   break;
    case token__MKD_:   break;
    case token__MKDIR: 	     break;
    case token__MKDMBF_:   break; 
    case token__MKL_:   break;
    case token__MKS_:   break;
    case token__MKSMBF_:   break; 
    case token__MODULE: 		break;
    case token__MONTH: 	    break;
    case token__MONTHNAME:   break; 
    case token__MSGBOX: 	    break;
    case token__MUSTINHERIT:     break; 
    case token__MUSTOVERRIDE:     break; 
    case token__MY:     break; 
    case token__MYBASE:     break; 
    case token__MYCLASS:     break; 
    case token__NAME: 	    break;
    case token__NAMESPACE: 				break;
    case token__NEW: 			break;
    case token__NEXT: 			break;
    case token__NOTHING: 			break;
    case token__NOTINHERITABLE:     break;
    case token__NOTOVERRIDABLE:     break;
    case token__NOW: 	    break;
    case token__NPER:   break; 
    case token__NPV:   break; 
    case token__NULL: 		break;
    case token__NZ:  	    break;
    case token__OCT_: 	    break;
    case token__OCT: 	    break;
    case token__OFF: 		break;
    case token__OLDBASIC:	break;      
    case token__ON:		 		break;
    case token__OPEN: 	    break;
    case token__OPTION: 		break;
    case token__OPTIONAL: 		break;
    case token__OUT:   break; 
    case token__OUTPUT: 	    break;
    case token__OVERLOADS:     break; 	
    case token__OVERRIDABLE:     break;
    case token__OVERRIDES:     break; 		
    case token__PAINT:   break;
    case token__PALETTE:   break;
    case token__PARAMARRAY:		break;
    case token__PARENT: 		break;
    case token__PARTITION:   break; 
    case token__PCOPY:   break;
    case token__PEEK:   break;
    case token__PEN:     break; 	
    case token__PLAY:     break; 	
    case token__PMAP:   break;
    case token__PMT:   break; 
    case token__POINT:   break; 
    case token__POKE:   break; 
    case token__POS: 	     break;
    case token__PPMT:   break;
    case token__PRESERVE:		break;
    case token__PRESET:   break; 
    case token__PRINT: 	     break;
    case token__PRINTSCREEN: 	     break;
    case token__PRIVATE: 	break;
    case token__PROPERTY: 	break;
    case token__PROTECTED:	    break;
    case token__PSET:   break; 
    case token__PUBLIC:      break;
    case token__PUT: 	    break;
    case token__PV:   break; 
    case token__QBCOLOR:   break;
    case token__RAD: 	   break;
    case token__RAISE: 	     break;
    case token__RAISEEVENT:
    case token__RAISESIGNAL:   break;
    case token__RANDOMIZE: 	   break;
    case token__RANDOM: 	   break;
    case token__RANGE: 		break;
    case token__RATE:   break; 
    case token__READ: 		break;
    case token__READONLY:     break; 	
    case token__REDIM: 		break;
    case token__REMOVEHANDLER:   break; 
    case token__REPLACE:   break; 
    case token__RESET: 	     break;
    case token__RESTORE: 		break;
    case token__RESUME: 		break;
    case token__RETURN: 		break;
    case token__RGB: 	    break;
    case token__RIGHT_: 	     break;
    case token__RIGHT: 	     break;
    case token__RMDIR: 	     break;
    case token__RND: 	   break;
    case token__ROUND:   break; 
    case token__RSET: 	     break;
    case token__RTRIM_: 	     break;
    case token__RTRIM: 	     break;
    case token__RUN:     break; 	
    case token__SAVEPICTURE:   break; 
    case token__SAVESETTING:   break; 
    case token__SCREEN:   break;
    case token__SEC: 	   break;
    case token__SECOND: 	    break;
    case token__SEEK: 	    break;
    case token__SELECT: 		break;
    case token__SENDKEYS:   break; 
    case token__SET:   break;
    case token__SETATTR:   break;
    case token__SGN: 	   break;
    case token__SHADOWS:     break; 
    case token__SHARED:     break; 
    case token__SHELL: 	     break;
    case token__SIGNAL:     break; 		
    case token__SIN: 	   break;
    case token__SIZE: 		break;
    case token__SLEEP: 	   break;
    case token__SLN:   break; 
    case token__SLOT:     break; 		
    case token__SOUND:   break; 
    case token__SPACE_: 	     break;
    case token__SPACE: 	     break;
    case token__SPC: 	    break;
    case token__SPLIT:   break; 
    case token__SQR: 	    break;
    case token__STATIC: 			break;
    case token__STEP: 			break;
    case token__STICK:   break; 
    case token__STOP: 			break;
    case token__STR_: 	   break;
    case token__STR: 	   break;
    case token__STRCOMP: 	   break;
    case token__STRCONV:   break; 
    case token__STRIG:     break; 	
    case token__STRING_: 	      break;
    case token__STRING: 	      break;
    case token__STRREVERSE:   break; 
    case token__STRUCTURE: 	   break;
    case token__SUB:     break;
    case token__SWAP:     break; 	
    case token__SWITCH: 	      break;
    case token__SYD:   break; 
    case token__SYNCLOCK:     break;
    case token__SYSTEM: 			break;
    case token__TAB: 	   break;
    case token__TAN: 	   break;
    case token__TEXT: 			break;
    case token__THEN: 			break;
    case token__THROW: 	    break;
    case token__THROWS: 	    break;
    case token__TIME: 	   break;
    case token__TIME_: 	   break;
    case token__TIMER:     break; 	
    case token__TIMESERIAL: 	     break;
    case token__TIMEVALUE: 	     break;
    case token__TO: 				break;
    case token__TRIM_: 	    break;
    case token__TRIM: 	    break;
    case token__TROFF:     break; 	
    case token__TRON:     break; 	
    case token__TRY: 	    break;
    case token__TYPE:			break;
    case token__TYPEDEF:		break;
    case token__TYPENAME: 	     break;
    case token__TYPEOF: 	    break;
    case token__UBOUND: 		break;
    case token__UCASE_: 	     break;
    case token__UCASE: 	     break;
    case token__UNICODE:     break;
    case token__UNLOAD:   break; 
    case token__UNLOCK:   break;
    case token__UNTIL: 		break;
    case token__UTF8: 	     break;
    case token__UTF16: 	     break;
    case token__USING: 	     break;
    case token__VAL: 	   break;
    case token__VARPTR_:     break; 
    case token__VARPTR:     break; 
    case token__VARSEG:     break; 
    case token__VARTYPE: 	   break;
    case token__VERYOLDBASIC:	break;
    case token__VIEW:   break; 
    case token__WAIT:     break; 	
    case token__WEEKDAY: 	     break;
    case token__WEEKDAYNAME:   break;
    case token__WEND: 			break;
    case token__WHILE: 		break;
    case token__WIDTH:   break; 
    case token__WINDOW:   break;
    case token__WITH: 			break;
    case token__WITHEVENTS:
    case token__WRITE: 	     break;
    case token__WRITEONLY:
    case token__ENCODE:
    case token__DECODE:
    case token__YEAR: 	     break;

    case token__LENGTH:
//    case token__COMPARE:
    case token__CONTAINS:
    case token__COUNT:
    case token__INDEXOF:
    case token__ENDSWITH:
    case token__STARTSWITH:
    case token__FILL:
    case token__INSERT:
    case token__LASTINDEXOF:
    case token__LEFTJUSTIFIED:
    case token__PREPEND:
    case token__REMOVE:
    case token__RIGHTJUSTIFIED:
    case token__SECTION:
    case token__SIMPLIFIED:
    case token__UPPER:
    case token__LOWER:
    case token__TRIMMED:
    case token__TRUNCATE:
//    case token__UNICODE:
    case token__VALUE:
    case token__REVERSED:
    case token__READBINARY:
    case token__WRITEBINARY:
    case token__SEEKBINARY:

    case token__DAYOFWEEK:      
    case token__DAYOFYEAR:     
    case token__DAYSINMONTH:  
    case token__DAYSINYEAR:   
    case token__WEEKNUMBER:   
    case token__ISLEAPYEAR:   
    case token__DIFFDAY:    
    case token__DIFFSECONDS:  
//    case token__ADDDATE:     
    case token__ADDDAYS:    
    case token__ADDMONTHS:  
    case token__ADDYEARS:   
    //case token__SUBDATE:    
    case token__SUBDAYS:   
    case token__SUBMONTHS: 
    case token__SUBYEARS:  
    //case token__ADDTIME:  
    case token__ADDHOURS: 
    case token__ADDMINUTES:  
    case token__ADDSECONDS: 
    //case token__SUBTIME: 
    case token__SUBHOURS: 
    case token__SUBMINUTES: 
    case token__SUBSECONDS:
    case token__ISDATEVALID:
    case token__ISTIMEVALID: 
    case token__ISDATETIMEVALID: 
    case token__DAYNAME:  


      break;


    case token__REM_MULTILINE_STOP: 	     break;

    case token__REM_MULTILINE:    
    case token__REM_DOCUMENTATION:  
				myToken->rd_CString( b ? getTokenPos() : myToken->getPos() );

       {
      	  t_token nTest = myToken->rd_Token( b ? getTokenPos() : myToken->getPos() );

         if (nTest != token__REM_MULTILINE_STOP){ internalError(utility::con(nTest, " token__REM_MULTILINE_STOP not found after token__REM_MULTILINE/token__REM_DOCUMENTATION")); }
       }
				break;

    case token__REM:
		case token__REM_SHORT:
				myToken->rd_CString( b ? getTokenPos() : myToken->getPos() );
				break;

    // all constants
		case token__LITERAL_BOOLEAN:
				myToken->rd_Char( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__LITERAL_BYTE:
				myToken->rd_Byte( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__LITERAL_INTEGER:
				myToken->rd_Integer( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__LITERAL_LONG:
				myToken->rd_Long( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__LITERAL_SINGLE:
				myToken->rd_Single( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__LITERAL_DOUBLE:
				myToken->rd_Double( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__LITERAL_STRING:
				myToken->rd_CString( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__LITERAL_CURRENCY:
  			//internalError(utility::con(nTest, "token__LITERAL_CURRENCY not supported yet"));
				myToken->rd_Currency( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__LITERAL_DATE:
  			//internalError(utility::con(nTest, "token__LITERAL_DATE not supported yet"));
        //return false;
        myToken->rd_Date( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__LITERAL_TIME:
  			//internalError(utility::con(nTest, "token__LITERAL_TIME not supported yet"));
        //return false;
				myToken->rd_Date( b ? getTokenPos() : myToken->getPos() );
				break;


		// all kbasic types
		case token__TYP_DOUBLE: 		break;
		case token__TYP_SINGLE: 		break;
		case token__TYP_INTEGER: 	break;
		case token__TYP_LONG: 			break;
		case token__TYP_CSTRING: 		break;
		case token__TYP_QSTRING: 		break;
		case token__TYP_BOOLEAN:		break;
		case token__TYP_BYTE:		break;
		case token__TYP_VARIANT:		break;
//		case token__TYP_CSTRING: 		break;
		case token__TYP_SHORT: 		break;
    //case token__TYP_COLLECTION:  break;
    case token__TYP_OBJECT:  break;
    case token__TYP_CURRENCY:  break;
    case token__TYP_DATE:  break;
    case token__TYP_ANY:  break;
    case token__TYP_CASTEXCEPTION:  break;
    case token__TYP_QTEXCEPTION:  break;
    case token__TYP_EXCEPTION:  break;
      

      

		// all misc.
		case token__MSC_EXTIDENTIFIER:
		case token__MSC_IDENTIFIER:
		case token__MSC_ID_INTEGER:
		case token__MSC_ID_DOUBLE:
		case token__MSC_ID_SINGLE:
		case token__MSC_ID_QSTRING:
		case token__MSC_ID_LONG:
		    myToken->rd_CString( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__MSC_EOL: 		 
        break;
		case token__MSC_LABEL:
		    myToken->rd_CString( b ? getTokenPos() : myToken->getPos() );
				break;
		case token__MSC_LINE:
		    myToken->rd_CString( b ? getTokenPos() : myToken->getPos() );
				break;

		case token__KB_FILENAME:
      {
        const char *ac = myToken->rd_CString( b ? getTokenPos() : myToken->getPos() );

				setCurrentFile(ac);
//        CONSOLE printKBFILE(ac);
                
      }

				break;
/*
		case token__KB_CONST: 		  break;
		case token__KB_IF: 		  break;
		case token__KB_ELSEIF: 		  break;
		case token__KB_ELSE: 		  break;
		case token__KB_END: 		  break;*/
		case token__KB_VERSION: 		 
				myToken->rd_Single( b ? getTokenPos() : myToken->getPos() );
				break;

		// all operators
		case token__OP_ADD: 						break;
		case token__OP_SUB: 						break;
		case token__OP_MUL: 						break;
		case token__OP_DIV: 						break;
		case token__OP_IDIV: 					break;
		case token__OP_MOD: 						break;
		case token__OP_EQUAL: 					break;
		case token__OP_UNEQUAL: 				break;
		case token__OP_GREATER: 				break;
		case token__OP_LESSER: 				break;
		case token__OP_GREATER_EQUAL: 	break;
		case token__OP_LESSER_EQUAL: 	break;
		case token__OP_AND: 						break;
		case token__OP_ANDALSO: 						break;
		case token__OP_OR: 						break;
		case token__OP_ORELSE: 						break;
		case token__OP_NOT: 						break;
		case token__OP_POWER: 			break;
		case token__OP_XOR: 						break;
		case token__OP_EQV: 						break;
		case token__OP_IMP: 						break;
		case token__OP_STR_CAT: 				break;
    case token__OP_SHL:				break;
//    case token__OP_SHL_:				break;
    case token__OP_SHR:				break;
    //case token__OP_SHR_:				break;
    case token__OP_INC:				break;
    //case token__OP_INC_:				break;
    case token__OP_DEC:				break;
    //case token__OP_DEC_:				break;
      /*
    case token__OP_ADD_EQUAL:				break;
    case token__OP_SUB_EQUAL:				break;
    case token__OP_DIV_EQUAL:				break;
    case token__OP_MUL_EQUAL:				break;

    case token__OP_ADD_ADD:				break;
    case token__OP_SUB_SUB:				break;*/

//    case token__OP_OR_EQUAL:				break;
    //case token__OP_AND_EQUAL:				break;
    case token__OP_BIT_AND:				break;
    case token__OP_BIT_OR:				break;
    case token__OP_BIT_XOR:				break;
    case token__OP_BIT_NOT:				break;
/*
    case token__OP_OR2:				break;
    case token__OP_NOT2:				break;
    case token__OP_EQUAL2:				break;
    case token__OP_UNEQUAL2:				break;
    case token__OP_AND_EQUAL:				break;
    case token__OP_OR_EQUAL:				break;
    case token__OP_XOR_EQUAL:				break;
    case token__OP_LESSER_LESSER:				break;
    case token__OP_GREATER_GREATER:				break;*/


		// all symbols
		case token__SYM_BR_OP: 						break;
		case token__SYM_BR_CL: 						break;
		case token__SYM_BC_OP: 						break;
		case token__SYM_BC_CL: 						break;
		case token__SYM_BS_OP: 						break;
		case token__SYM_BS_CL: 						break;
		case token__SYM_COMMA: 						break;
		case token__SYM_COLON: 	
      break;
		case token__SYM_DOT: 							
      break;

		case token__SYM_EXCLAMATION:			break;
		case token__SYM_HASH:							break;
		case token__SYM_QM: 							break;
		case token__SYM_SEMICOL: 					break;
		case token__SYM_TILDE: 				  	break;      

		case token__SYM_UL:
				// if _ occurs before EOL, ignore EOL and go to the next token
				{
					_TBEGIN_

					if (!(fEOL(0))){ syntaxError(token__SYM_UL, "EOL missing after _"); _TERROR_}

				}
				break;

		// all constants
		case token__KB_EOF:
		case token__KB_EOF2:
			break;

		default:
      /*
      if (not_supported(nTest))
      { 

        if (nTest == token__MSC_EXTIDENTIFIER){
          { semanticError(token__KEYWORD,  " Sorry! This source code contains a non-ASCII code, which is not supported by KBasic yet or contains an unidentified symbol" ); _ERROR_ }
        } else {
          static const char *ac = "";
          
          ac = token::keyword_(nTest);
          if (strcmp(ac, "") == 0) ac = token::builtin_(nTest);
          if (strcmp(ac, "") == 0) ac = token::operator_(nTest);
        }
      }*/

			internalError(utility::con(nTest, " undefined token"));
			return false;
			break;

	}

	nTest = myToken->peekToken( b ? getTokenPos() : myToken->getPos() );

  switch (nTest){
		case token__KB_LINE:
				nTest = myToken->rd_Token( b ? getTokenPos() : myToken->getPos() );
				nCurrentLine = myToken->rd_Integer( b ? getTokenPos() : myToken->getPos() );
				break;
  }

	return true;
}

// ****

// find class...

int parser::findClass(const char *acName)
{ 
  static int n;

  // find user defined class
  n = myClass->getId(acName);
  if (n > 0) return n;

  // finding binding class
  n = myMemory_type->getId(getScope(), acName);
  if (n > 0 && memory_type::isBinding(n)) return n;

  return 0; 
}

int parser::findClassConst(const char *acClass, const char *name)
{
  return myClass->getIdConst(acClass, name); 
}

int parser::findClassStaticVar(const char *acClass, const char *name)
{
  return myClass->getIdStaticVar(acClass, name); 
}

int parser::findClassVar(const char *acClass, const char *name)
{
  return myClass->getIdVar(acClass, name); 
}

int parser::findClassLocalVar(const char *acClass, const char *acSub, int nBlockNo, const char *name)
{
  return myClass->getIdMethodVar(acClass, acSub, name);
}

// find module...
int parser::findModuleConst(const char *acModule, const char *name)
{
  return myModule->getIdConst(acModule, name);
}

int parser::findModuleVar(const char *acModule, const char *name)
{
  return myModule->getIdVar(acModule, name); 
}

int parser::findModulePublicVar(const char *acModule, const char *name)
{
  int nId = 0;
  int nType = 0;
  t_array *a = 0;
  int nScope = 0;

  if (myModule->getVar(myModule->getId(acModule), name, &nId, &nType, &a, &nScope)){
    if (nScope == token__PUBLIC){
      return nId;
    }
  }

  return 0;
}


int parser::findModuleLocalVar(const char *acModule, const char *acSub, int nBlockNo, const char *name)
{
  return myModule->getIdSubVar(acModule, acSub, name);
}

// find module/class localVar
int parser::findLocalVar(const char *acModule, const char *acSub, int nBlockNo, const char *name)
{
  if (isScopeModule()){
    return findModuleLocalVar(acModule, acSub, nBlockNo, name);
  } else {
    return findClassLocalVar(acModule, acSub, nBlockNo, name);
  }
}

// ****

// register class...
int parser::registerClassVar(const char *acClass, const char *acName, int _type, t_array *a, bool bStatic, int nScope, int nLStringLen)
{ 
  /*
  if (strcmp(acClass, "myForm") == 0 && strcmp(acName, "Label0") == 0){
    acClass = acClass;
  }
  */
	int nClassId = myClass->getId(acClass);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existConst(nClassId, acName)){
    semanticError(token__DIM, utility::con(acName, " is already declared as const at some place"));
  }  

  // staticvar und classvar müssen eindeutig sein
  if (myClass->existStaticVar(nClassId, acName)){
    semanticError(token__DIM, utility::con(acName, " is already declared as static variable at some place"));
  }  

  if (utility::my_stricmp(acName, getRealSub()) == 0){
    semanticError(token__DIM, utility::con(acName, " is already used as sub/function/method name at some place"));
  }

  int nID = myClass->addVar(nClassId, acName, _type, a, bStatic, nScope, nLStringLen); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addVar(acCurrentFile, memory_class_addVar, nID, nClassId, acName, _type, a, bStatic, nScope, nLStringLen);

	return nID;
}

int parser::registerClassStaticVar(const char *acClass, const char *acName, int _type, t_array *a, bool bStatic, int nScope, int nLStringLen)
{ 
	int nClassId = myClass->getId(acClass);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existConst(nClassId, acName)){
    semanticError(token__DIM, utility::con(acName, " is already declared as const at some place"));
  }  

  // staticvar und classvar müssen eindeutig sein
  if (myClass->existVar(nClassId, acName)){
    semanticError(token__DIM, utility::con(acName, " is already declared as instance variable at some place"));
  }  

  int nID = myClass->addStaticVar(nClassId, acName, _type, a, bStatic, nScope, nLStringLen); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addStaticVar(acCurrentFile, memory_class_addStaticVar, nID, nClassId, acName, _type, a, bStatic, nScope, nLStringLen);

	return nID;
}

int parser::registerClassLocalConst(const char *acClass, const char *acSub, int nBlockNo, const char *name)
{ 
	int nClassId = myClass->getId(acClass);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existMethodVar(nClassId, acSub, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as variable at some place"));
  }  

  if (utility::my_stricmp(name, getRealSub()) == 0){
    semanticError(token__DIM, utility::con(name, " is already used as sub/function/method name at some place"));
  }


  int nID = myClass->addMethodConst(nClassId, acSub, name); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addMethodConst(acCurrentFile, memory_class_addMethodConst, nID, nClassId, acSub, name);

	return nID;
}

int parser::registerClassLocalPropertyGetConst(const char *acClass, const char *acSub, int nBlockNo, const char *name)
{ 
	int nClassId = myClass->getId(acClass);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existPropertyGetVar(nClassId, acSub, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as variable at some place"));
  }  

  if (utility::my_stricmp(name, getRealSub()) == 0){
    semanticError(token__DIM, utility::con(name, " is already used as sub/function/method name at some place"));
  }


  int nID = myClass->addPropertyGetConst(nClassId, acSub, name); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addPropertyGetConst(acCurrentFile, memory_class_addPropertyGetConst, nID, nClassId, acSub, name);

	return nID;
}

int parser::registerClassLocalPropertySetConst(const char *acClass, const char *acSub, int nBlockNo, const char *name)
{ 
	int nClassId = myClass->getId(acClass);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existPropertySetVar(nClassId, acSub, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as variable at some place"));
  }  

  if (utility::my_stricmp(name, getRealSub()) == 0){
    semanticError(token__DIM, utility::con(name, " is already used as sub/function/method name at some place"));
  }


  int nID = myClass->addPropertySetConst(nClassId, acSub, name); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addPropertySetConst(acCurrentFile, memory_class_addPropertyGetConst, nID, nClassId, acSub, name);

	return nID;
}

int parser::registerClassLocalVar(const char *acClass, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck)
{ 
	int nClassId = myClass->getId(acClass);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existMethodConst(nClassId, acSub, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as const at some place"));
  }  

  if (!bNoNameCheck && utility::my_stricmp(name, getRealSub()) == 0){
    semanticError(token__DIM, utility::con(name, " is already used as sub/function/method name at some place"));
  }


  int nID = myClass->addMethodVar(nClassId, acSub, name, _type, a, bStatic, nScope, nLStringLen); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addMethodVar(acCurrentFile, memory_class_addMethodVar, nID, nClassId, acSub, name, _type, a, bStatic, nScope, nLStringLen);

	return nID;
}

int parser::registerClassLocalPropertyGetVar(const char *acClass, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck)
{ 
	int nClassId = myClass->getId(acClass);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existPropertyGetConst(nClassId, acSub, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as const at some place"));
  }  


  int nID = myClass->addPropertyGetVar(nClassId, acSub, name, _type, a, bStatic, nScope, nLStringLen); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addPropertyGetVar(acCurrentFile, memory_class_addPropertyGetVar, nID, nClassId, acSub, name, _type, a, bStatic, nScope, nLStringLen);

	return nID;
}

int parser::registerClassLocalPropertySetVar(const char *acClass, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck)
{ 
	int nClassId = myClass->getId(acClass);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existPropertySetConst(nClassId, acSub, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as const at some place"));
  }  


  int nID = myClass->addPropertySetVar(nClassId, acSub, name, _type, a, bStatic, nScope, nLStringLen); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addPropertySetVar(acCurrentFile, memory_class_addPropertySetVar, nID, nClassId, acSub, name, _type, a, bStatic, nScope, nLStringLen);

	return nID;
}

int parser::registerClassConst(const char *acClass, const char *name, int nScope/*, int _type*/)
{ 
	int nClassId = myClass->getId(acClass);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existVar(nClassId, name) || myClass->existStaticVar(nClassId, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as variable at some place"));
  }  


  int nID = myClass->addConst(nClassId, name, nScope);

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addConst(acCurrentFile, memory_class_addConst, nID, nClassId, name, nScope);

	return nID;
}

// register module...
int parser::registerModuleVar(const char *acModule, const char *name, int _type, t_array *a, int nScope, int nLStringLen)
{ 
	int nModuleId = myModule->getId(acModule);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myModule->existConst(nModuleId, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as const at some place"));
  }  


  int nID = myModule->addVar(nModuleId, name, _type, a, nScope, nLStringLen);
  
  XString s = acCurrentFile;
  if (my_cache && s.endsWith("/default.kbasic")){
    my_cache->wr_memory_module_addVar_defaultkbasic(acCurrentFile, memory_module_addVar, nID, nModuleId, name, _type, a, nScope, nLStringLen);
  }
  else if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_addVar(acCurrentFile, memory_module_addVar, nID, nModuleId, name, _type, a, nScope, nLStringLen);

	return nID;
}

int parser::registerModuleLocalVar(const char *acModule, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck)
{ 
	int nModuleId = myModule->getId(acModule);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myModule->existSubConst(nModuleId, acSub, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as const at some place"));
  }  

  if (!bNoNameCheck && utility::my_stricmp(name, getRealSub()) == 0){
    semanticError(token__DIM, utility::con(name, " is already used as sub/function/method name"));
  }


  int nID = myModule->addSubVar(nModuleId, acSub, name, _type, a, bStatic, nScope, nLStringLen); 

  if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_addSubVar(acCurrentFile, memory_module_addSubVar, nID, nModuleId, acSub, name, _type, a, bStatic, nScope, nLStringLen);

	return nID;
}


int parser::registerModuleLocalConst(const char *acModule, const char *acSub, int nBlockNo, const char *name)
{ 
	int nModuleId = myModule->getId(acModule);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myModule->existSubVar(nModuleId, acSub, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as variable at some place"));
  }  

  if (utility::my_stricmp(name, getRealSub()) == 0){
    semanticError(token__DIM, utility::con(name, " is already used as sub/function/method name at some place"));
  }


  int nID = myModule->addSubConst(nModuleId, acSub, name); 

  if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_addSubConst(acCurrentFile, memory_module_addSubConst, nID, nModuleId, acSub, name);

	return nID;
}

int parser::registerModuleConst(const char *acModule, const char *acName, int nScope)
{ 
	int nModuleId = myModule->getId(acModule);

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myModule->existVar(nModuleId, acName)){
    semanticError(token__CONST, utility::con(acName, " is already declared as variable at some place"));
  }  


  int nID = myModule->addConst(nModuleId, acName, nScope);// == token__PUBLIC);

  if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_addConst(acCurrentFile, memory_module_addConst, nID, nModuleId, acName, nScope);

  return nID;
}

// only used for builtin consts
bool parser::registerConstPublic(const char *acName, int nValue)
{ 
	int nModuleId = myModule->getId(acDefaultModuleName);
  int nScope = token__PUBLIC;

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myModule->existVar(nModuleId, acName)){
    semanticError(token__CONST, utility::con(acName, " is already declared as variable at some place"));
  }


  int nID = myModule->addConst(nModuleId, acName, nScope);

  if (!(nID > 0)){ internalError("registerConstPublic"); return false; }

  if (bProducePcode){
		myPcode->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nValue);
    myPcode->wr_CONST(pcode__CONST, nID, global);
    myPcode->wr_MOV_CONST(pcode__MOV_CONST, nID, global); // write pcode
  }
  return true;
}

// only used for builtin consts
bool parser::registerConstPublic(const char *acName, const char *sValue)
{ 
	int nModuleId = myModule->getId(acDefaultModuleName);
  int nScope = token__PUBLIC;

  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myModule->existVar(nModuleId, acName)){
    semanticError(token__CONST, utility::con(acName, " is already declared as variable at some place"));
  }


  int nVar = myModule->addConst(nModuleId, acName, nScope);

  if (!(nVar > 0)){ internalError("registerConstPublic"); return false; }

  int nStatics = registerStringLiteral(sValue, true);
  if (nStatics == 0){ internalError( utility::con(sValue, " string literal not declared") ); _ERROR_ }             

  if (bProducePcode){
		myPcode->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStatics); 
    myPcode->wr_CONST(pcode__CONST, nVar, global);
    myPcode->wr_MOV_CONST(pcode__MOV_CONST, nVar, global); // write pcode
  }
  return true;
}

// register module/class localVar
int parser::registerLocalVar(const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck)
{
  if (isScopeModule()){
    return registerModuleLocalVar(getModule(), getSub(), getBlockNo(), name, _type, a, bByVal, bStatic, nScope, nLStringLen, bNoNameCheck);
  } else {
    if (isScopeClassPropertyGet()){
      return registerClassLocalPropertyGetVar(getClass(), getMethod(), getBlockNo(), name, _type, a, bByVal, bStatic, nScope, nLStringLen, bNoNameCheck);
    } else if (isScopeClassPropertySet()){
      return registerClassLocalPropertySetVar(getClass(), getMethod(), getBlockNo(), name, _type, a, bByVal, bStatic, nScope, nLStringLen, bNoNameCheck);
    } else {
      return registerClassLocalVar(getClass(), getMethod(), getBlockNo(), name, _type, a, bByVal, bStatic, nScope, nLStringLen, bNoNameCheck);
    }
  }
}

int parser::registerClassStaticCodeVar(const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen)
{

	int nClassId = myClass->getId(getClass());

  /*
  // beim erstellen einer var/const test ob name schon vergeben als const/var
  if (myClass->existConst(nClassId, name)){
    semanticError(token__DIM, utility::con(name, " is already declared as const"));
  }  
  */

  int nID = myClass->addStaticCodeVar(nClassId, name, _type, a, bStatic, nScope, nLStringLen);

  // we do not have wr_memory_class_addStaticCodeVar, so we use wr_memory_class_addVar
  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addVar(acCurrentFile, memory_class_addVar, nID, nClassId, name, _type, a, bStatic, nScope, nLStringLen);

	return nID;
}

// register module/class globalVar
int parser::registerGlobalVar(const char *name, int _type, t_array *a, int nScope, int nLStringLen)
{
  if (isScopeModule() || isScopeDefaultGlobal()){
    return registerModuleVar(getModule(), name, _type, a, nScope, nLStringLen);
  } else {
    return 0;
  }
}

// register module/class var
int parser::registerVar(const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck)
{
  if (isScopeDefaultGlobal() && !isScopeLocal()/*(strcmp(getSub(), "") == 0 && strcmp(getMethod(), "") == 0)*/){
    return registerGlobalVar(name, _type, a, nScope, nLStringLen);
  } else if (isScopeClassStaticCode()){
    return registerClassStaticCodeVar(name, _type, a, bByVal, bStatic, nScope, nLStringLen);
  } else {
    return registerLocalVar(name, _type, a, bByVal, bStatic, nScope, nLStringLen, bNoNameCheck);
  }
}

// ****

int parser::registerStringLiteral(const char *name, bool bBuiltin)
{ 
  int nId = myMemory_stringliteral->declare(name); 

  if (!bBuiltin && my_cache && strcmp(name, "") != 0 && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_stringliteral_declare(acCurrentFile, memory_stringliteral_declare, nId, name, nId);

  return nId; 
}

const char *parser::findStringLiteral(int id){ return myMemory_stringliteral->getName(id); }
int parser::findStringLiteral(const char *name){ return myMemory_stringliteral->getId(name); }

int parser::registerBinding(bool bSupported, const char *name, int id)
{ 
  return myMemory_type->addType(getScope(), name, token__PUBLIC, id); 
}

int parser::registerTypePublic(const char *name, int id){ 
  return myMemory_type->addType(getScope(), name, token__PUBLIC, id); 
}
int parser::registerType(const char *name, int nScope)
{  
  int nId = myMemory_type->addType(getScope(), name, nScope);

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_type_addType(acCurrentFile, memory_type_addType, nId, getScope(), name, nScope, nId);
  return nId; 
}
int parser::registerType(const char *name, int nScope, int id)
{ 
  int nId = myMemory_type->addType(getScope(), name, nScope, id);

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_type_addType(acCurrentFile, memory_type_addType, nId, getScope(), name, nScope, nId);
  return nId; 
}
const char *parser::findType(int id){ return myMemory_type->getName(id); }
int parser::findType(const char *acModule, const char *name){ return myMemory_type->getId(acModule, name); }
int parser::findType(const char *name)
{ 
  int n = 0;

#ifdef KBDEBUG
  if (stopAtLine(5)){
    int i = 9;
    i++;
  }
#endif

  // search in current scope for type
  n = myMemory_type->getId(getScope(), name); 
  if (n > 0) return n;
  
  // search in global scope for type
	if (myMemory_type->first()){
		do {

      if (utility::my_stricmp(name, myMemory_type->getName()) == 0){

       // test for scope validity
       if (bParserPhase2 && myMemory_type->getScope() == token__PRIVATE){ semanticError(token__AS, "TYPE name cannot be used, because it is declared as PRIVATE"); return 0; };              

				return myMemory_type->getId();
			}

		} while (myMemory_type->next());
	}

  return n;
}

bool	parser::registerTypeElement(int nId, const char *acElementName, const char *acElementType, int nElementSize, t_array *a)
{ 
  int ID = myMemory_type->addElement(nId, acElementName, acElementType, nElementSize, a, 0);

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_type_addElement(acCurrentFile, memory_type_addElement, ID, nId, acElementName, acElementType, nElementSize, a, 0);
  return ID; 
}

const char *parser::findTypeElement(int myMemory_typeid, int field_id){ return myMemory_type->findElement(myMemory_typeid, field_id); }

int parser::registerEnum(const char *name, int nScope)
{ 

  int nId = myMemory_enum->addEnum(getScope(), name, nScope); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_enum_addEnum(acCurrentFile, memory_enum_addEnum, nId, getScope(), name, nScope, nId);
  return nId; 
}

int parser::findEnum(const char *acModule, const char *name)
{
  return myMemory_enum->getId(acModule, name);
}

bool	parser::registerEnumElement(int nEnumId, const char *acIdentifier,  const char *acType)
{ 
  int ID = myMemory_enum->addElement(nEnumId, acIdentifier, acType, 0, 0, findType(acType)); 

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_enum_addElement(acCurrentFile, memory_enum_addElement, ID, nEnumId, acIdentifier, acType, 0, findType(acType));
  return ID; 
}

int parser::findEnumElement(int nEnumId, const char *acElementName){ return myMemory_enum->findEnumElement(nEnumId, acElementName); }
const char *parser::findEnumElement(int nEnumId, int field_id){ return myMemory_enum->findEnumElement(nEnumId, field_id); }
int parser::enumElementType		(int nEnumId, int nElement)
{
  char *acElementName; char *acElementType;

  myMemory_enum->findEnumElement(nEnumId, nElement, &acElementName, &acElementType);
  int nType = findType(acElementType);
  if (nType == 0){ internalError(utility::con(acElementType, " not defined") ); }

  return nType;
}

//int parser::registerStructure(const char *name, int nScope, int id){ return myMemory_structure->addStructure(getScope(), name, nScope, id); }
//bool	parser::registerStructureElement(int id, const char *acIdentifier,  const char *acType){ return myMemory_structure->addElement(id, acIdentifier, acType, 0, 0); }
				

int 		parser::registerClass		(
 const char *acName, 
 pcode *myPcode, 
 pcode *myClassStaticPcode, 
 const char *acExtendName, 
 bool bIsAbstract
 )
{
  int n = myClass->addClass(acName, myPcode, myClassStaticPcode, acExtendName, acCurrentFile, bIsAbstract);
  if (n > 0){

    // alle sub classes aktualisieren auf neue parent id
    if (myClass->first()){
      do {
         int nClassId = myClass->getId();

         if (utility::my_stricmp(myClass->getParentName(nClassId), acName) == 0){
            myClass->setParentId(nClassId, n);
         }
      } while (myClass->next());
    }
  }

  if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addClass(acCurrentFile, memory_class_addClass, n, acName, myPcode, myClassStaticPcode, acExtendName, bIsAbstract);

  return n;
}

int parser::registerModule( const char *acName)
{
 int nID = myModule->addModule(acName, 0, 0, acCurrentFile);

 if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_addModule(acCurrentFile, memory_module_addModule, nID, acName, 0/*myPcode*/, 0);

 return nID;
}

int parser::registerModuleSub(
																				const char *acModuleName, 
																				const char *acRealName, 
																				const char *acName, 
																				const char *acSuffix, 
																				const char *acReturnType, 
																				int nReturnSize, 
																				pcode *myPcode, 
																				bool function, 
																				int pc_pos, 
																				int nScope, 
																				int nTokenPos,
																				int nTokenLinePos,
																				bool bStatic,
																				bool bAbstract,
                                        const char *acFile,
                                        int nLine,
                                        bool bDeclare,
                                        const char *acAlias,
                                        const char *acLib,
                                        const char *acLibCallSignature        
                                        )
{
 int nID = myModule->addModuleSub(
																				acModuleName, 
																				acRealName, 
																				acName, 
																				acSuffix, 
																				acReturnType, 
																				nReturnSize, 
																				myPcode, 
																				function, 
																				pc_pos, 
																				nScope, 
																				nTokenPos,
																				nTokenLinePos,
																				bStatic,
																				bAbstract,
                                        acFile,
                                        nLine,
                                        bDeclare,
                                        acAlias,
                                        acLib,
                                        acLibCallSignature        
   );

 if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_addModuleSub(acCurrentFile, memory_module_addModuleSub, nID, 
																				acModuleName, 
																				acRealName, 
																				acName, 
																				acSuffix, 
																				acReturnType, 
																				nReturnSize, 
																				myPcode, 
																				function, 
																				pc_pos, 
																				nScope, 
																				nTokenPos,
																				nTokenLinePos,
																				bStatic,
																				bAbstract,
                                        acFile,
                                        nLine,
                                        bDeclare,
                                        acAlias,
                                        acLib,
                                        acLibCallSignature        
  );

 return nID;
}

bool parser::classExists( const char *acName)
{
  return myClass->getId(acName) > 0; 
}

bool parser::moduleExists( const char *acName)
{
  return myModule->getId(acName) > 0; 
}

t_array *parser::arrayVar(int id)
{

  // class
  t_array *t = myClass->getArrayVar(myClass->getId(getScope()), id); if (t != 0) return t;

  t = myClass->getArrayStaticVar(myClass->getId(getScope()), id); if (t != 0) return t;
	t = myClass->getArrayMethodVar(myClass->getId(getScope()), getMethod(), id); if (t != 0) return t;

  // default global
	t = myModule->getArraySubVar(myModule->getId(acDefaultModuleName), getSub(), id); if (t != 0) return t;
	t = myModule->getArrayVar(myModule->getId(acDefaultModuleName), id); if (t != 0) return t;
  
  // module
	t = myModule->getArraySubVar(myModule->getId(getScope()), getSub(), id); if (t != 0) return t;
	t = myModule->getArrayVar(myModule->getId(getScope()), id); if (t != 0) return t;

  if (myModule->first()){
    do {
      int nModuleId = myModule->getId();

    	t = myModule->getArrayVar(nModuleId, id); if (t != 0) return t;

    } while (myModule->next());
  }

 internalError("parser_interface::arrayVar() --> variable not found");
 return 0;

}

int parser::arrayType(int id)
{

  // class
  int t = myClass->typeVar(myClass->getId(getScope()), id); if (t != 0) return t;

  t = myClass->typeStaticVar(myClass->getId(getScope()), id); if (t != 0) return t;
	t = myClass->typeMethodVar(getScope(), getMethod(), id); if (t != 0) return t;

  // default global
	t = myModule->typeSubVar(acDefaultModuleName, getSub(), id); if (t != 0) return t;
	t = myModule->typeVar(myModule->getId(acDefaultModuleName), id); if (t != 0) return t;
  
  // module
	t = myModule->typeSubVar(getScope(), getSub(), id); if (t != 0) return t;
	t = myModule->typeVar(myModule->getId(getScope()), id); if (t != 0) return t;

  if (myModule->first()){
    do {
      int nModuleId = myModule->getId();

    	t = myModule->typeVar(nModuleId, id); if (t != 0) return t;

    } while (myModule->next());
  }

 internalError("parser_interface::arrayType() --> variable not found");
 return 0;

}

bool parser::findVar(int nId, const char **acModule, const char **acSub, const char **acName){


  // class
  if (myClass->findVar(nId, acModule, acSub, acName)) return true;

  // default global & module
  if (myModule->findVar(nId, acModule, acSub, acName)) return true;

 internalError("parser_interface::findVar() --> variable not found");

  return false; 
}

bool parser::findConst(int nId, const char **acModule, const char **acSub, const char **acName)
{ 

  // class
  if (myClass->findConst(nId, acModule, acSub, acName)) return true;

  // default global & module
  if (myModule->findConst(nId, acModule, acSub, acName)) return true;

 internalError("parser_interface::findConst() --> const not found");

 return false;
}

bool parser::findScope(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub)
{
  
  if (bPropertyGet){

    // class
    if (myClass->existPropertyGet(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getNamePropertyGet(nModuleId, nSubId);
      return true;
    }
  } else if (bPropertySet){

    // class
    if (myClass->existPropertySet(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getNamePropertySet(nModuleId, nSubId);
      return true;
    }
  } else {

  // class
  if (myClass->existMethod(nModuleId, nSubId)){
    *acModule = myClass->getName(nModuleId);
    *acSub = myClass->getNameMethod(nModuleId, nSubId);
    return true;
  }

  // module
  if (myModule->existSub(nModuleId, nSubId)){
    *acModule = myModule->getName(nModuleId);
    *acSub = myModule->getNameSub(nModuleId, nSubId);
    return true;
  }
  }

 internalError("parser_interface::findScope() --> scope not found");

 return false;
}

bool parser::findScope2(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub)
{

  if (bPropertyGet){

    // class
    if (myClass->existPropertyGet(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getNamePropertyGet(nModuleId, nSubId);
      return true;
    }
  } else if (bPropertySet){

    // class
    if (myClass->existPropertySet(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getNamePropertySet(nModuleId, nSubId);
      return true;
    }
  } else {

    // class
    if (myClass->existMethod(nModuleId, nSubId)){
      *acModule = myClass->getName(nModuleId);
      *acSub = myClass->getRealNameMethod(nModuleId, nSubId);
      return true;
    }

    // module
    if (myModule->existSub(nModuleId, nSubId)){
      *acModule = myModule->getName(nModuleId);
      *acSub = myModule->getRealNameSub(nModuleId, nSubId);
      return true;
    }
  }

 internalError("parser_interface::findScope() --> scope not found");

 return false;
}

t_scope parser::getScopeCode()
{
  if (isScopeClassStaticCode()) return global; // must be called before isScopeClass()
  if (isScopeLocal()) return local;
  if (isScopeClass()) return me;

	return global;
}


void parser::addDependency(const char *acFile, const char *acDependency)
{
  if (strcmp(acFile, acDependency) == 0) return;
  if (strcmp(acDependency, acDefaultModuleName) == 0) return;
  if (strcmp(acFile, "") == 0) return;

  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_dependency(acFile, dependency, acDependency);
}

void parser::addDependencyGlobalVar(const char *acFile, int nId)
{
  if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_dependency_globalvar(acFile, dependency_globalvar, nId);
}

