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



#ifndef TOKEN_H
#define TOKEN_H

#include "XString.h"
#include "utility.h"

#include "../kbshared/bytearray.h"

/*
  tokenizer:
  read/write tokens, e.g.

  LINE 0003 DIM ID n AS INTEGER EOL
  LINE 0004 DIM ID i AS INTEGER EOL
  LINE 0005 DIM ID x AS INTEGER EOL

*/
class _mainwindow;


const int MAX_TOKEN_ID = 4096;

/**
[EXPLANATION]
NAME: KEYWORD
DESC: A keyword is a reserved word with special meaning.
SEEALSO:
*/

// all kbasic KEYWORDS, in alphabetic order, 
// enth�t die summe aller keywords und funktionen, operatoren... aus qbasic, vb, vbnet, kbasic
const t_token token__KEYWORD = 0; 
const t_token token___DYNAMIC     = token__KEYWORD + 1;
const t_token token___ELSE     = token___DYNAMIC + 1;
const t_token token___END         = token___ELSE + 1;
const t_token token___EXTERNALSOURCE     = token___END + 1;
const t_token token___IF     = token___EXTERNALSOURCE + 1;
const t_token token___REGION     = token___IF + 1;
const t_token token___STATIC      = token___REGION + 1;
const t_token token__ABSOLUTE        = token___STATIC + 1;
const t_token token__ABSTRACT        = token__ABSOLUTE + 1;
const t_token token__ADDRESSOF         = token__ABSTRACT + 1;
const t_token token__ALIAS       = token__ADDRESSOF + 1;
const t_token token__ANSI        = token__ALIAS + 1;
const t_token token__AS        = token__ANSI + 1; 
const t_token token__ASSEMBLY        = token__AS + 1;
const t_token token__AUTO        = token__ASSEMBLY + 1;
const t_token token__BASE      = token__AUTO + 1;
const t_token token__BY_REF      = token__BASE + 1; 
const t_token token__BY_VAL      = token__BY_REF + 1; 
const t_token token__CALL         = token__BY_VAL + 1;
const t_token token__CALLBYNAME        = token__CALL + 1;
const t_token token__CASE         = token__CALLBYNAME + 1;
const t_token token__CATCH         = token__CASE + 1;
const t_token token__CHAIN        = token__CATCH + 1;
const t_token token__CHOOSE      = token__CHAIN + 1;
const t_token token__CLASS         = token__CHOOSE + 1;
const t_token token__CLASS_INITIALIZE        = token__CLASS + 1; // Attention! must be before CLASS
const t_token token__CLASS_TERMINATE         = token__CLASS_INITIALIZE + 1; // Attention! must be before CLASS
const t_token token__COM       = token__CLASS_TERMINATE + 1;
const t_token token__COMMON     = token__COM + 1; 
const t_token token__COMPARE      = token__COMMON + 1;
const t_token token__CONNECT      = token__COMPARE + 1;
const t_token token__CONST      = token__CONNECT + 1;
const t_token token__CONSTRUCTOR         = token__CONST + 1;
const t_token token__DATA         = token__CONSTRUCTOR + 1;
const t_token token__DATABASE      = token__DATA + 1;
const t_token token__DATETIME      = token__DATABASE + 1;
const t_token token__DEBUG       = token__DATETIME + 1;
const t_token token__DECIMAL       = token__DEBUG + 1;
const t_token token__DECLARE          = token__DECIMAL + 1; 
const t_token token__DEF          = token__DECLARE + 1;
const t_token token__DEFAULT       = token__DEF + 1;
const t_token token__DEFBOOL          = token__DEFAULT + 1;
const t_token token__DEFBYTE          = token__DEFBOOL + 1;
const t_token token__DEFCUR         = token__DEFBYTE + 1;
const t_token token__DEFDATE          = token__DEFCUR + 1;
const t_token token__DEFDBL         = token__DEFDATE + 1;
const t_token token__DEFINT         = token__DEFDBL + 1;
const t_token token__DEFLNG         = token__DEFINT + 1;
const t_token token__DEFOBJ         = token__DEFLNG + 1;
const t_token token__DEFSNG         = token__DEFOBJ + 1;
const t_token token__DEFSTR         = token__DEFSNG + 1;
const t_token token__DEFVAR         = token__DEFSTR + 1;
const t_token token__DELEGATE        = token__DEFVAR + 1;
const t_token token__DESTRUCTOR        = token__DELEGATE + 1;
const t_token token__DIM          = token__DESTRUCTOR + 1;
const t_token token__DIRECTCAST        = token__DIM + 1;
const t_token token__DISCONNECT        = token__DIRECTCAST + 1;
const t_token token__DO           = token__DISCONNECT + 1;
const t_token token__EACH         = token__DO + 1;
const t_token token__ECHO        = token__EACH + 1;
const t_token token__ELSE         = token__ECHO + 1;
const t_token token__ELSEIF       = token__ELSE + 1;
const t_token token__EMPTY       = token__ELSEIF + 1;
const t_token token__END          = token__EMPTY + 1;
const t_token token__ENDIF        = token__END + 1;
const t_token token__ENUM        = token__ENDIF + 1;
const t_token token__ERASE        = token__ENUM + 1;
const t_token token__EVENT       = token__ERASE + 1;
const t_token token__EXIT         = token__EVENT + 1;
const t_token token__EXPLICIT     = token__EXIT + 1;
const t_token token__FINALLY         = token__EXPLICIT + 1;
const t_token token__FOR          = token__FINALLY + 1;
const t_token token__FRIEND     = token__FOR + 1;
const t_token token__FUNCTION     = token__FRIEND + 1;
const t_token token__GLOBAL       = token__FUNCTION + 1;
const t_token token__GOSUB        = token__GLOBAL + 1;
const t_token token__GOTO         = token__GOSUB + 1;
const t_token token__HANDLES       = token__GOTO + 1;
const t_token token__IF           = token__HANDLES + 1;
const t_token token__IIF          = token__IF + 1;
const t_token token__IMPLEMENTS   = token__IIF + 1;
const t_token token__IMPORTS       = token__IMPLEMENTS + 1;
const t_token token__IN           = token__IMPORTS + 1;
const t_token token__INHERITS        = token__IN + 1;
const t_token token__INTERFACE         = token__INHERITS + 1;
const t_token token__IS           = token__INTERFACE + 1;
const t_token token__ITERATE      = token__IS + 1;
const t_token token__KBASIC     = token__ITERATE + 1;
const t_token token__KEY       = token__KBASIC + 1;
const t_token token__LBOUND       = token__KEY + 1;
const t_token token__LET          = token__LBOUND + 1;
const t_token token__LIB       = token__LET + 1;
const t_token token__LIKE         = token__LIB + 1;
const t_token token__LOOP         = token__LIKE + 1;
const t_token token__LSET         = token__LOOP + 1;
const t_token token__ME       = token__LSET + 1;
const t_token token__MID          = token__ME + 1;
const t_token token__MODULE        = token__MID + 1;
const t_token token__MUSTINHERIT       = token__MODULE + 1;
const t_token token__MUSTOVERRIDE      = token__MUSTINHERIT + 1;
const t_token token__MY      = token__MUSTOVERRIDE + 1;
const t_token token__MYBASE      = token__MY + 1;
const t_token token__MYCLASS       = token__MYBASE + 1;
const t_token token__NAMESPACE         = token__MYCLASS + 1;
const t_token token__NEW          = token__NAMESPACE + 1;
const t_token token__NEXT         = token__NEW + 1;
const t_token token__NOTHING          = token__NEXT + 1;
const t_token token__NOTINHERITABLE      = token__NOTHING + 1;
const t_token token__NOTOVERRIDABLE      = token__NOTINHERITABLE + 1;
const t_token token__NULL         = token__NOTOVERRIDABLE + 1;
const t_token token__OFF        = token__NULL + 1;
const t_token token__OLDBASIC  = token__OFF + 1; // means vb
const t_token token__ON           = token__OLDBASIC + 1;
const t_token token__OPTION       = token__ON + 1;
const t_token token__OPTIONAL       = token__OPTION + 1;
const t_token token__OVERLOADS       = token__OPTIONAL + 1;
const t_token token__OVERRIDABLE       = token__OVERLOADS + 1;
const t_token token__OVERRIDES     = token__OVERRIDABLE + 1;
const t_token token__PARAMARRAY        = token__OVERRIDES + 1; 
const t_token token__PARENT        = token__PARAMARRAY + 1;
const t_token token__PEN       = token__PARENT + 1;
const t_token token__PLAY        = token__PEN + 1;
const t_token token__PRESERVE        = token__PLAY + 1; 
const t_token token__PRIVATE      = token__PRESERVE + 1;
const t_token token__PROPERTY     = token__PRIVATE + 1;
const t_token token__PROTECTED         = token__PROPERTY + 1;
const t_token token__PUBLIC       = token__PROTECTED + 1;
const t_token token__RANGE        = token__PUBLIC + 1;
const t_token token__READ         = token__RANGE + 1;
const t_token token__READONLY    = token__READ + 1;
const t_token token__REDIM        = token__READONLY + 1;
const t_token token__REM          = token__REDIM + 1;
const t_token token__REM_DOCUMENTATION    = token__REM + 1;
const t_token token__REM_MULTILINE    = token__REM_DOCUMENTATION + 1;
const t_token token__REM_MULTILINE_STOP   = token__REM_MULTILINE + 1;
const t_token token__REM_SHORT    = token__REM_MULTILINE_STOP + 1;
const t_token token__REPEAT       = token__REM_SHORT + 1;
const t_token token__RESTORE      = token__REPEAT + 1;
const t_token token__RESUME       = token__RESTORE + 1;
const t_token token__RETURN       = token__RESUME + 1;
const t_token token__RSET         = token__RETURN + 1;
const t_token token__RUN       = token__RSET + 1;
const t_token token__SELECT       = token__RUN + 1;
const t_token token__SET          = token__SELECT + 1;
const t_token token__SHADOWS     = token__SET + 1;
const t_token token__SHARED         = token__SHADOWS + 1;
//const t_token token__SHORT     = token__SHARED + 1;
const t_token token__SIGNAL        = token__SHARED + 1; 
const t_token token__SIZE         = token__SIGNAL + 1;
const t_token token__SLOT        = token__SIZE + 1; 
const t_token token__STATIC         = token__SLOT + 1;
const t_token token__STEP         = token__STATIC + 1;
const t_token token__STOP         = token__STEP + 1;
const t_token token__STRIG       = token__STOP + 1;
const t_token token__STRUCTURE         = token__STRIG + 1;
const t_token token__SUB          = token__STRUCTURE + 1;
const t_token token__SWAP         = token__SUB + 1;
const t_token token__SWITCH         = token__SWAP + 1;
const t_token token__SYNCLOCK    = token__SWITCH + 1;
const t_token token__SYSTEM      = token__SYNCLOCK + 1;
const t_token token__TEXT         = token__SYSTEM + 1;
const t_token token__THEN         = token__TEXT + 1;
const t_token token__THROW         = token__THEN + 1;
const t_token token__THROWS        = token__THROW + 1;
const t_token token__TIMER       = token__THROWS + 1;
const t_token token__TO           = token__TIMER + 1;
const t_token token__TROFF       = token__TO + 1;
const t_token token__TRON        = token__TROFF + 1;
const t_token token__TRY         = token__TRON + 1;
const t_token token__TYPE         = token__TRY + 1;
const t_token token__TYPEDEF      = token__TYPE + 1;
const t_token token__UBOUND       = token__TYPEDEF + 1;
const t_token token__UNICODE     = token__UBOUND + 1;
const t_token token__UNTIL        = token__UNICODE + 1;
const t_token token__VARPTR        = token__UNTIL + 1;
const t_token token__VARPTR_       = token__VARPTR + 1;
const t_token token__VARSEG        = token__VARPTR_ + 1;
const t_token token__VERYOLDBASIC     = token__VARSEG + 1; // means qbasic
const t_token token__WAIT        = token__VERYOLDBASIC + 1;
const t_token token__WEND         = token__WAIT + 1;
const t_token token__WHILE        = token__WEND + 1;
const t_token token__WITH       = token__WHILE + 1;
const t_token token__WITHEVENTS    = token__WITH + 1;
const t_token token__WRITEONLY     = token__WITHEVENTS + 1;



/**
[EXPLANATION]
NAME: BUILTIN
DESC:
SEEALSO:
*/

// all kbasic BUILTIN commands, functions and subs, in alphabetic order
// are already declared as keyword: MID, READ
const t_token token__BUILTIN = 500;

const t_token token____CLASS__         = token__BUILTIN + 1;
const t_token token____FILE__        = token____CLASS__ + 1;
const t_token token____ISCLASS__         = token____FILE__ + 1;
const t_token token____ISLINUX__         = token____ISCLASS__ + 1;
const t_token token____ISMACOS__         = token____ISLINUX__ + 1;
const t_token token____ISMODULE__        = token____ISMACOS__ + 1;
const t_token token____ISSUB__         = token____ISMODULE__ + 1;
const t_token token____ISWINDOWS__         = token____ISSUB__ + 1;
const t_token token____LINE__        = token____ISWINDOWS__ + 1;
const t_token token____MODULE__        = token____LINE__ + 1;
const t_token token____SCOPE__         = token____MODULE__ + 1;
const t_token token____SUB__         = token____SCOPE__ + 1;
const t_token token__ABS         = token____SUB__ + 1;
const t_token token__ACCESS        = token__ABS + 1;
const t_token token__ACS         = token__ACCESS + 1;
const t_token token__ADDHANDLER        = token__ACS + 1;
const t_token token__APPACTIVATE       = token__ADDHANDLER + 1;
const t_token token__APPEND        = token__APPACTIVATE + 1;
const t_token token__ARRAY         = token__APPEND + 1;
const t_token token__ASC         = token__ARRAY + 1;
const t_token token__ASN         = token__ASC + 1;
const t_token token__ATN         = token__ASN + 1;
const t_token token__BEEP        = token__ATN + 1;
const t_token token__BIN         = token__BEEP + 1;
const t_token token__BIN_        = token__BIN + 1;
const t_token token__BINARY        = token__BIN_ + 1;
const t_token token__BLOAD       = token__BINARY + 1;
const t_token token__BSAVE       = token__BLOAD + 1;
const t_token token__CBCD         = token__BSAVE + 1;
const t_token token__CBOOL         = token__CBCD + 1;
const t_token token__CBYTE         = token__CBOOL + 1;
const t_token token__CCHAR       = token__CBYTE + 1;
const t_token token__CCUR        = token__CCHAR + 1;
const t_token token__CDATE         = token__CCUR + 1;
const t_token token__CDBL        = token__CDATE + 1;
const t_token token__CDEC        = token__CDBL + 1;
const t_token token__CEXT         = token__CDEC + 1;
const t_token token__CFIX         = token__CEXT + 1;
const t_token token__CHDIR       = token__CFIX + 1;
const t_token token__CHDRIVE       = token__CHDIR + 1;
const t_token token__CHR         = token__CHDRIVE + 1;
const t_token token__CHR_        = token__CHR+ 1;
const t_token token__CINT        = token__CHR_+ 1;
const t_token token__CIRCLE        = token__CINT + 1;
const t_token token__CLEAR         = token__CIRCLE + 1;
const t_token token__CLNG        = token__CLEAR + 1;
const t_token token__CLOSE         = token__CLNG + 1;
const t_token token__CLS         = token__CLOSE + 1;
const t_token token__COBJ        = token__CLS + 1;
const t_token token__COLOR         = token__COBJ + 1;
const t_token token__COMMAND       = token__COLOR + 1;
const t_token token__COMMAND_     = token__COMMAND + 1;
const t_token token__COS         = token__COMMAND_ + 1;
const t_token token__CQUD         = token__COS + 1;
const t_token token__CREATEOBJECT        = token__CQUD + 1;
const t_token token__CSHORT        = token__CREATEOBJECT + 1;
const t_token token__CSNG        = token__CSHORT + 1;
const t_token token__CSRLIN        = token__CSNG + 1;
const t_token token__CTYPE       = token__CSRLIN + 1;
const t_token token__CURDIR     = token__CTYPE + 1;
const t_token token__CURDIR_      = token__CURDIR + 1;
const t_token token__CVD         = token__CURDIR_ + 1;
const t_token token__CVDMBF        = token__CVD + 1;
const t_token token__CVERR         = token__CVDMBF + 1;
const t_token token__CVI         = token__CVERR + 1;
const t_token token__CVL         = token__CVI + 1;
const t_token token__CVS         = token__CVL + 1;
const t_token token__CVSMBF        = token__CVS + 1;
const t_token token__DATE        = token__CVSMBF + 1;
const t_token token__DATE_       = token__DATE + 1;
const t_token token__DATEADD       = token__DATE_ + 1;
const t_token token__DATEDIFF        = token__DATEADD + 1;
const t_token token__DATEPART        = token__DATEDIFF + 1;
const t_token token__DATESERIAL        = token__DATEPART + 1;
const t_token token__DATEVALUE       = token__DATESERIAL + 1;
const t_token token__DAY       = token__DATEVALUE + 1;
const t_token token__DDB       = token__DAY + 1;
const t_token token__DEG         = token__DDB + 1;
const t_token token__DELETESETTING       = token__DEG + 1;
const t_token token__DIR         = token__DELETESETTING + 1;
const t_token token__DIR_        = token__DIR + 1;
const t_token token__DOEVENTS        = token__DIR_ + 1;
const t_token token__DOF         = token__DOEVENTS + 1;
const t_token token__DRAW        = token__DOF + 1;
const t_token token__ENVIRON       = token__DRAW + 1;
const t_token token__ENVIRON_        = token__ENVIRON + 1;
const t_token token__EOF_        = token__ENVIRON_ + 1;
const t_token token__ERDEV       = token__EOF_ + 1;
const t_token token__ERDEV_        = token__ERDEV + 1;
const t_token token__ERL          = token__ERDEV_ + 1;
const t_token token__ERR          = token__ERL + 1;
const t_token token__ERROR        = token__ERR + 1;
const t_token token__ERROR_         = token__ERROR + 1;
const t_token token__EXP         = token__ERROR_ + 1;
const t_token token__FACT        = token__EXP + 1;
const t_token token__FIELD       = token__FACT + 1;
const t_token token__FILE      = token__FIELD + 1;
const t_token token__FILEATTR      = token__FILE + 1;
const t_token token__FILECOPY        = token__FILEATTR + 1;
const t_token token__FILEDATETIME      = token__FILECOPY + 1;
const t_token token__FILELEN     = token__FILEDATETIME + 1;
const t_token token__FILES       = token__FILELEN + 1;
const t_token token__FILTER        = token__FILES + 1;
const t_token token__FIX         = token__FILTER + 1;
const t_token token__FN           = token__FIX + 1;
const t_token token__FORMAT        = token__FN + 1;
const t_token token__FORMAT_         = token__FORMAT + 1;
const t_token token__FORMATCURRENCY        = token__FORMAT_ + 1;
const t_token token__FORMATDATETIME        = token__FORMATCURRENCY + 1;
const t_token token__FORMATNUMBER        = token__FORMATDATETIME + 1;
const t_token token__FORMATPERCENT       = token__FORMATNUMBER + 1;
const t_token token__FRAC        = token__FORMATPERCENT + 1;
const t_token token__FRE         = token__FRAC + 1;
//const t_token token__FREE        = token__FRE + 1;
const t_token token__FREEFILE        = token__FRE + 1;
const t_token token__FV        = token__FREEFILE + 1;
const t_token token__GET         = token__FV + 1;
const t_token token__GETALLSETTINGS       = token__GET + 1;
const t_token token__GETATTR         = token__GETALLSETTINGS + 1;
const t_token token__GETAUTOSERVERSETTINGS       = token__GETATTR + 1;
const t_token token__GETOBJECT       = token__GETAUTOSERVERSETTINGS + 1;
const t_token token__GETSETTING        = token__GETOBJECT + 1;
const t_token token__GETTYPE       = token__GETSETTING + 1;
const t_token token__HEX         = token__GETTYPE + 1;
const t_token token__HEX_        = token__HEX + 1;
const t_token token__HOUR        = token__HEX_ + 1;
const t_token token__HYPOT         = token__HOUR + 1;
const t_token token__IMESTATUS       = token__HYPOT + 1;
const t_token token__INKEY       = token__IMESTATUS + 1;
const t_token token__INKEY_        = token__INKEY + 1;
const t_token token__INP         = token__INKEY_ + 1;
const t_token token__INPUT         = token__INP + 1;
const t_token token__INPUT_        = token__INPUT + 1;
const t_token token__INPUTBOX        = token__INPUT_ + 1;
const t_token token__INSTR         = token__INPUTBOX + 1;
const t_token token__INSTREV       = token__INSTR + 1;
const t_token token__INT         = token__INSTREV + 1;
const t_token token__IOCTL         = token__INT + 1;
const t_token token__IOCTL_        = token__IOCTL + 1;
const t_token token__IPMT        = token__IOCTL_ + 1;
const t_token token__IRR       = token__IPMT + 1;
const t_token token__ISARRAY         = token__IRR + 1;
const t_token token__ISBOOLEAN         = token__ISARRAY + 1;
const t_token token__ISBYTE        = token__ISBOOLEAN + 1;
//const t_token token__ISCHARACTER         = token__ISBYTE + 1;
//const t_token token__ISCOLLECTION        = token__ISBYTE + 1;
const t_token token__ISCSTRING         = token__ISBYTE + 1;
const t_token token__ISCURRENCY        = token__ISCSTRING + 1;
const t_token token__ISDATE        = token__ISCURRENCY + 1;
const t_token token__ISDOUBLE        = token__ISDATE + 1;
const t_token token__ISEMPTY         = token__ISDOUBLE + 1;
const t_token token__ISERROR         = token__ISEMPTY + 1;
/*
const t_token token__ISINT16         = token__ISERROR + 1;
const t_token token__ISINT32         = token__ISINT16 + 1;
const t_token token__ISINT64         = token__ISINT32 + 1;
*/
const t_token token__ISINTEGER         = token__ISERROR + 1;
const t_token token__ISMISSING         = token__ISINTEGER + 1;
const t_token token__ISNULL        = token__ISMISSING + 1;
const t_token token__ISNUMERIC         = token__ISNULL + 1;
const t_token token__ISOBJECT        = token__ISNUMERIC + 1;
const t_token token__ISSHORT         = token__ISOBJECT + 1;
const t_token token__ISSINGLE        = token__ISSHORT + 1;
/*
const t_token token__ISUINT16        = token__ISSINGLE + 1;
const t_token token__ISUINT32        = token__ISUINT16 + 1;
const t_token token__ISUINT64        = token__ISUINT32 + 1;
*/
const t_token token__ISLONG        = token__ISSINGLE + 1;
const t_token token__ISSTRING     =  token__ISLONG + 1;
const t_token token__ISVARIANT         = token__ISSTRING + 1;
const t_token token__ISLINUX           = token__ISVARIANT + 1;
const t_token token__ISMAC           = token__ISLINUX + 1;
const t_token token__ISWINDOWS           = token__ISMAC + 1;

const t_token token__JOIN        = token__ISWINDOWS + 1;
const t_token token__KBASICDIR       = token__JOIN + 1;
const t_token token__KILL        = token__KBASICDIR + 1;
const t_token token__LCASE       = token__KILL + 1;
const t_token token__LCASE_      = token__LCASE + 1;
const t_token token__LEFT        = token__LCASE_ + 1;
const t_token token__LEFT_       = token__LEFT + 1;
const t_token token__LEN         = token__LEFT_ + 1;
const t_token token__LINE        = token__LEN + 1;
const t_token token__LN        = token__LINE + 1;
const t_token token__LOAD        = token__LN + 1;
const t_token token__LOADPICTURE       = token__LOAD + 1;
const t_token token__LOADRESDATA       = token__LOADPICTURE + 1;
const t_token token__LOADRESPICTURE        = token__LOADRESDATA + 1;
const t_token token__LOADRESSTRING     = token__LOADRESPICTURE + 1;
const t_token token__LOC         = token__LOADRESSTRING + 1;
const t_token token__LOCATE        = token__LOC + 1;
const t_token token__LOCK        = token__LOCATE + 1;
const t_token token__LOF         = token__LOCK + 1;
const t_token token__LOG         = token__LOF + 1;
const t_token token__LOGB        = token__LOG + 1;
const t_token token__LPOS        = token__LOGB + 1;
const t_token token__LPRINT        = token__LPOS + 1;
const t_token token__LTRIM         = token__LPRINT + 1;
const t_token token__LTRIM_        = token__LTRIM + 1;
const t_token token__MAX         = token__LTRIM_ + 1;
const t_token token__MID_        = token__MAX + 1;
const t_token token__MIN         = token__MID_ + 1;
const t_token token__MINUTE        = token__MIN + 1;
const t_token token__MIRR        = token__MINUTE + 1;
const t_token token__MKD_        = token__MIRR + 1;
const t_token token__MKDIR         = token__MKD_ + 1;
const t_token token__MKDMBF_       = token__MKDIR + 1;
const t_token token__MKI_        = token__MKDMBF_ + 1;
const t_token token__MKL_        = token__MKI_ + 1;
const t_token token__MKS         = token__MKL_ + 1;
const t_token token__MKS_        = token__MKS + 1;
const t_token token__MKSMBF_       = token__MKS_ + 1;
const t_token token__MONTH         = token__MKSMBF_ + 1;
const t_token token__MONTHNAME       = token__MONTH + 1;
const t_token token__MSGBOX      = token__MONTHNAME + 1;
const t_token token__MTIMER        = token__MSGBOX + 1;
const t_token token__NAME        = token__MTIMER + 1;
const t_token token__NOW       = token__NAME + 1;
const t_token token__NPER        = token__NOW + 1;
const t_token token__NPV       = token__NPER + 1;
const t_token token__NZ        = token__NPV + 1;
const t_token token__OCT         = token__NZ + 1;
const t_token token__OCT_        = token__OCT + 1;
const t_token token__OPEN        = token__OCT_ + 1;
const t_token token__OUT         = token__OPEN + 1;
const t_token token__OUTPUT        = token__OUT + 1;
const t_token token__PAINT         = token__OUTPUT + 1;
const t_token token__PALETTE         = token__PAINT + 1;
const t_token token__PARTITION       = token__PALETTE + 1;
const t_token token__PCOPY         = token__PARTITION + 1;
const t_token token__PEEK        = token__PCOPY + 1;
const t_token token__PMAP        = token__PEEK + 1;
const t_token token__PMT       = token__PMAP + 1;
const t_token token__POINT      = token__PMT + 1;
const t_token token__POKE     = token__POINT + 1;
const t_token token__POS         = token__POKE + 1;
const t_token token__PPMT        = token__POS + 1;
const t_token token__PRESET      = token__PPMT + 1;
const t_token token__PRINT       = token__PRESET + 1;
const t_token token__PRINTSCREEN       = token__PRINT + 1;
const t_token token__PSET        = token__PRINTSCREEN + 1;
const t_token token__PUT         = token__PSET + 1;
const t_token token__PV        = token__PUT + 1;
const t_token token__QBCOLOR       = token__PV + 1;
const t_token token__RAD         = token__QBCOLOR + 1;
const t_token token__RAISE         = token__RAD + 1;
const t_token token__RAISEEVENT    = token__RAISE + 1; 
const t_token token__RAISESIGNAL       = token__RAISEEVENT + 1;
const t_token token__RANDOM        = token__RAISESIGNAL + 1;
const t_token token__RANDOMIZE         = token__RANDOM + 1;
const t_token token__RATE        = token__RANDOMIZE + 1;
const t_token token__REMOVEHANDLER     = token__RATE + 1;
const t_token token__REPLACE       = token__REMOVEHANDLER + 1;
const t_token token__RESET         = token__REPLACE + 1;
const t_token token__RGB         = token__RESET + 1;
const t_token token__RIGHT         = token__RGB + 1;
const t_token token__RIGHT_        = token__RIGHT + 1;
const t_token token__RMDIR         = token__RIGHT_ + 1;
const t_token token__RND         = token__RMDIR + 1;
const t_token token__ROUND       = token__RND + 1;
const t_token token__RTRIM         = token__ROUND + 1;
const t_token token__RTRIM_        = token__RTRIM + 1;
const t_token token__SAVEPICTURE       = token__RTRIM_ + 1;
const t_token token__SAVESETTING       = token__SAVEPICTURE + 1;
const t_token token__SCREEN        = token__SAVESETTING + 1;
const t_token token__SEC         = token__SCREEN + 1;
const t_token token__SECOND        = token__SEC + 1;
const t_token token__SEEK        = token__SECOND + 1;
const t_token token__SEG         = token__SEEK + 1;
const t_token token__SENDKEYS        = token__SEG + 1;
const t_token token__SETATTR       = token__SENDKEYS + 1;
const t_token token__SGN         = token__SETATTR + 1;
const t_token token__SHELL         = token__SGN + 1;
const t_token token__SIN         = token__SHELL + 1;
const t_token token__SLEEP       = token__SIN + 1;
const t_token token__SLN       = token__SLEEP + 1;
const t_token token__SOUND       = token__SLN + 1;
const t_token token__SPACE         = token__SOUND + 1;
const t_token token__SPACE_        = token__SPACE + 1;
const t_token token__SPC         = token__SPACE_ + 1;
const t_token token__SPLIT       = token__SPC + 1;
const t_token token__SQR         = token__SPLIT + 1;
const t_token token__STICK       = token__SQR + 1;
const t_token token__STR         = token__STICK + 1;
const t_token token__STR_        = token__STR + 1;
const t_token token__STRCOMP     = token__STR_ + 1;
const t_token token__STRCONV       = token__STRCOMP + 1;
const t_token token__STRING        = token__STRCONV + 1;
const t_token token__STRING_       = token__STRING + 1;
const t_token token__STRREVERSE        = token__STRING_ + 1;
const t_token token__SYD       = token__STRREVERSE + 1;
const t_token token__TAB         = token__SYD + 1;
const t_token token__TAN         = token__TAB + 1;
const t_token token__TIME        = token__TAN + 1;
const t_token token__TIME_         = token__TIME + 1;
const t_token token__TIMESERIAL      = token__TIME_ + 1;
const t_token token__TIMEVALUE         = token__TIMESERIAL + 1;
const t_token token__TRIM        = token__TIMEVALUE + 1;
const t_token token__TRIM_         = token__TRIM + 1;
const t_token token__TYPENAME        = token__TRIM_ + 1;
const t_token token__TYPEOF        = token__TYPENAME + 1;
const t_token token__UCASE       = token__TYPEOF + 1;
const t_token token__UCASE_        = token__UCASE + 1;
const t_token token__UNLOAD        = token__UCASE_ + 1;
const t_token token__UNLOCK        = token__UNLOAD + 1;
const t_token token__UTF8         = token__UNLOCK + 1;
const t_token token__UTF16         = token__UTF8 + 1;
const t_token token__USING         = token__UTF16 + 1;
const t_token token__VAL         = token__USING + 1;
const t_token token__VARTYPE         = token__VAL + 1;
const t_token token__VIEW        = token__VARTYPE + 1;
const t_token token__WEEKDAY         = token__VIEW + 1;
const t_token token__WEEKDAYNAME       = token__WEEKDAY + 1;
const t_token token__WIDTH         = token__WEEKDAYNAME + 1;
const t_token token__WINDOW        = token__WIDTH + 1;
const t_token token__WRITE         = token__WINDOW + 1;
const t_token token__YEAR        = token__WRITE + 1;


const t_token token__LENGTH        = token__YEAR + 1;
const t_token token__CONTAINS        = token__LENGTH + 1;
const t_token token__COUNT        = token__CONTAINS + 1;
const t_token token__INDEXOF        = token__COUNT + 1;
const t_token token__ENDSWITH        = token__INDEXOF + 1;
const t_token token__STARTSWITH        = token__ENDSWITH + 1;
const t_token token__FILL        = token__STARTSWITH + 1;
const t_token token__INSERT        = token__FILL + 1;
const t_token token__LASTINDEXOF        = token__INSERT + 1;
const t_token token__LEFTJUSTIFIED       = token__LASTINDEXOF + 1;
const t_token token__PREPEND       = token__LEFTJUSTIFIED + 1;
const t_token token__REMOVE       = token__PREPEND + 1;
const t_token token__RIGHTJUSTIFIED       = token__REMOVE + 1;
const t_token token__SECTION       = token__RIGHTJUSTIFIED + 1;
const t_token token__SIMPLIFIED       = token__SECTION + 1;
const t_token token__UPPER       = token__SIMPLIFIED + 1;
const t_token token__LOWER       = token__UPPER + 1;
const t_token token__TRIMMED       = token__LOWER + 1;
const t_token token__TRUNCATE       = token__TRIMMED + 1;
const t_token token__VALUE       = token__TRUNCATE + 1;
const t_token token__REVERSED       = token__VALUE + 1;
const t_token token__READBINARY       = token__REVERSED + 1;
const t_token token__WRITEBINARY       = token__READBINARY + 1;
const t_token token__SEEKBINARY       = token__WRITEBINARY + 1;

const t_token token__DAYOFWEEK       = token__SEEKBINARY + 1;
const t_token token__DAYOFYEAR       = token__DAYOFWEEK + 1;
const t_token token__DAYSINMONTH       = token__DAYOFYEAR + 1;
const t_token token__DAYSINYEAR       = token__DAYSINMONTH + 1;
const t_token token__WEEKNUMBER       = token__DAYSINYEAR + 1;
const t_token token__ISLEAPYEAR       = token__WEEKNUMBER + 1;
const t_token token__DIFFDAY       = token__ISLEAPYEAR + 1;
const t_token token__DIFFSECONDS       = token__DIFFDAY + 1;
//const t_token token__ADDDATE       = token__DIFFSECONDS + 1;
const t_token token__ADDDAYS       = token__DIFFSECONDS + 1;
const t_token token__ADDMONTHS       = token__ADDDAYS + 1;
const t_token token__ADDYEARS       = token__ADDMONTHS + 1;
//const t_token token__SUBDATE       = token__ADDYEARS + 1;
const t_token token__SUBDAYS       = token__ADDYEARS + 1;
const t_token token__SUBMONTHS       = token__SUBDAYS + 1;
const t_token token__SUBYEARS       = token__SUBMONTHS + 1;
//const t_token token__ADDTIME       = token__SUBYEARS + 1;
const t_token token__ADDHOURS       = token__SUBYEARS + 1;
const t_token token__ADDMINUTES       = token__ADDHOURS + 1;
const t_token token__ADDSECONDS       = token__ADDMINUTES + 1;
//const t_token token__SUBTIME       = token__ADDSECONDS + 1;
const t_token token__SUBHOURS       = token__ADDSECONDS + 1;
const t_token token__SUBMINUTES       = token__SUBHOURS + 1;
const t_token token__SUBSECONDS       = token__SUBMINUTES + 1;
const t_token token__ISDATEVALID       = token__SUBSECONDS + 1;
const t_token token__ISTIMEVALID       = token__ISDATEVALID + 1;
const t_token token__ISDATETIMEVALID       = token__ISTIMEVALID + 1;
const t_token token__DAYNAME       = token__ISDATETIMEVALID + 1;

const t_token token__ENCODE     = token__DAYNAME + 1;
const t_token token__DECODE     = token__ENCODE + 1;




/**
[EXPLANATION]
NAME: DATATYPE
DESC: Is a reserved word with special meaning.
SEEALSO:
*/
//   DATATYPES
const t_token token__NUM_TYPE     = 1300;

const t_token token__TYP_BOOLEAN     = token__NUM_TYPE + 1; // 8 bit
const t_token token__TYP_BYTE     = token__TYP_BOOLEAN + 1; // 8 bit unsigned
//const t_token token__TYP_CHARACTER      = token__TYP_BYTE + 1; // 
//const t_token token__TYP_COLLECTION     = token__TYP_CHARACTER + 1; // 
const t_token token__TYP_CSTRING     = token__TYP_BYTE + 1; // null terminated C string, needed for foreign API calls and file access
const t_token token__TYP_CURRENCY     = token__TYP_CSTRING + 1; // 
const t_token token__TYP_DATE     = token__TYP_CURRENCY + 1; // 
const t_token token__TYP_DOUBLE     = token__TYP_DATE + 1; // 64 bit
/*
const t_token token__TYP_INT16      = token__TYP_DOUBLE + 1; // 
const t_token token__TYP_INT32      = token__TYP_INT16 + 1; //
const t_token token__TYP_INT64      = token__TYP_INT32 + 1; // */
const t_token token__TYP_INTEGER     = token__TYP_DOUBLE + 1; // 32 bit, signed
const t_token token__TYP_LONG       = token__TYP_INTEGER + 1; // 64 bit, signed
const t_token token__TYP_OBJECT     = token__TYP_LONG + 1; // 
const t_token token__TYP_SHORT     = token__TYP_OBJECT + 1; // 16 bit, signed
const t_token token__TYP_SINGLE     = token__TYP_SHORT + 1; // 32 bit
const t_token token__TYP_QSTRING      = token__TYP_SINGLE + 1;
/*
const t_token token__TYP_UINT16     = token__TYP_STRING + 1; // 
const t_token token__TYP_UINT32     = token__TYP_UINT16 + 1; // 
const t_token token__TYP_UINT64     = token__TYP_UINT32 + 1; // */
const t_token token__TYP_VARIANT      = token__TYP_QSTRING + 1; // 
const t_token token__TYP_ANY      = token__TYP_VARIANT + 1; // 

const t_token token__TYP_CASTEXCEPTION     = token__TYP_ANY + 1; // 
const t_token token__TYP_QTEXCEPTION     = token__TYP_CASTEXCEPTION + 1; // 
const t_token token__TYP_EXCEPTION     = token__TYP_QTEXCEPTION + 1; // 


/**
[EXPLANATION]
NAME: LITERAL
DESC: Represents a value.
SEEALSO:
*/

//   LITERALS
const t_token token__LITERAL     = 1400;

const t_token token__LITERAL_DOUBLE       = token__LITERAL + 1;
const t_token token__LITERAL_INTEGER    = token__LITERAL_DOUBLE + 1;
const t_token token__LITERAL_STRING       = token__LITERAL_INTEGER + 1;
const t_token token__LITERAL_BYTE     = token__LITERAL_STRING + 1;
const t_token token__LITERAL_BOOLEAN      = token__LITERAL_BYTE + 1;
const t_token token__LITERAL_SINGLE     = token__LITERAL_BOOLEAN + 1;
const t_token token__LITERAL_LONG       = token__LITERAL_SINGLE + 1;
const t_token token__LITERAL_CURRENCY   = token__LITERAL_LONG + 1;
const t_token token__LITERAL_DATE   = token__LITERAL_CURRENCY + 1;
const t_token token__LITERAL_TIME   = token__LITERAL_DATE + 1;



//   SYMBOLS
const t_token token__SYMBOL     = 1500;

const t_token token__SYM_BR_OP      = token__SYMBOL + 1;    // ( [QBASIC * * *]
const t_token token__SYM_BR_CL      = token__SYM_BR_OP + 1;    // ) [QBASIC * * *]
const t_token token__SYM_BC_OP      = token__SYM_BR_CL + 1;    // {
const t_token token__SYM_BC_CL      = token__SYM_BC_OP + 1;    // }
const t_token token__SYM_BS_OP      = token__SYM_BC_CL + 1;    // [
const t_token token__SYM_BS_CL      = token__SYM_BS_OP + 1;    // ]
const t_token token__SYM_COMMA      = token__SYM_BS_CL + 1;    // , [QBASIC * * *]
const t_token token__SYM_COLON      = token__SYM_COMMA + 1;    // : [QBASIC * * *]
const t_token token__SYM_DOT        = token__SYM_COLON + 1;    // . [QBASIC * * *]
const t_token token__SYM_EXCLAMATION  = token__SYM_DOT + 1;    // ! [* * * *]
const t_token token__SYM_HASH   = token__SYM_EXCLAMATION + 1;    // # [* * * *]
const t_token token__SYM_UL         = token__SYM_HASH + 1;    // _ [QBASIC * * *]
const t_token token__SYM_QM         = token__SYM_UL + 1;    // ? [QBASIC * * *]
const t_token token__SYM_SEMICOL      = token__SYM_QM + 1;    // ; [QBASIC * * *]
const t_token token__SYM_TILDE      = token__SYM_SEMICOL + 1;    // ~

/**
[EXPLANATION]
NAME: line concatenation with _
DESC:
SEEALSO:
*/


//   OPERATORS
const t_token token__OPERATOR     = 1600;

// Attention! if you add a new operator, look at parser::nextTokenIsOperator()
const t_token token__OP_SHL          = token__OPERATOR + 1;       // SHL [* * * KBASIC]
//const t_token token__OP_SHL_           = token__OP_SHL + 1;       // << [* * * KBASIC]
const t_token token__OP_SHR          = token__OP_SHL + 1;       // SHR [* * * KBASIC]
//const t_token token__OP_SHR_           = token__OP_SHR + 1;       // >> [* * * KBASIC]
const t_token token__OP_INC          = token__OP_SHR + 1;       // INC [* * * KBASIC]
//const t_token token__OP_INC_           = token__OP_INC + 1;       // ++ [* * * KBASIC]
const t_token token__OP_DEC          = token__OP_INC + 1;       // DEC [* * * KBASIC]
//const t_token token__OP_DEC_           = token__OP_DEC + 1;       // -- [* * * KBASIC]
/*
const t_token token__OP_ADD_EQUAL          = token__OP_DEC + 1;       // += [* * * *]
const t_token token__OP_SUB_EQUAL          = token__OP_ADD_EQUAL + 1;       // -= [* * * *]
const t_token token__OP_DIV_EQUAL          = token__OP_SUB_EQUAL + 1;       // /= [* * * *]
const t_token token__OP_MUL_EQUAL          = token__OP_DIV_EQUAL + 1;       // *= [* * * *]
const t_token token__OP_ADD_ADD          = token__OP_MUL_EQUAL + 1;       // ++ [* * * *]
const t_token token__OP_SUB_SUB          = token__OP_ADD_ADD + 1;       // -- [* * * *]*/

//const t_token token__OP_OR_EQUAL           = token__OP_MUL_EQUAL + 1;       // |= [* * * *]
//const t_token token__OP_AND_EQUAL          = token__OP_OR_EQUAL + 1;       // &= [* * * *]
const t_token token__OP_BIT_AND          = token__OP_DEC + 1;       // BITAND [* * * *] same as AND
const t_token token__OP_BIT_OR           = token__OP_BIT_AND + 1;       // BITOR [* * * *] same as OR
const t_token token__OP_BIT_XOR          = token__OP_BIT_OR + 1;       // BITXOR [* * * *] same as XOR
const t_token token__OP_BIT_NOT          = token__OP_BIT_XOR + 1;       // BITNOT [* * * *] same as NOT

const t_token token__OP_ADD          = token__OP_BIT_NOT + 1;       // + [QBASIC VB * *]
const t_token token__OP_SUB          = token__OP_ADD + 1;         // - [QBASIC VB * *]
const t_token token__OP_MUL          = token__OP_SUB + 1;         // * [QBASIC VB * *]
const t_token token__OP_DIV          = token__OP_MUL + 1;         // / [QBASIC VB * *]
const t_token token__OP_MOD          = token__OP_DIV + 1;         // MOD [QBASIC VB * *]
const t_token token__OP_EQUAL        = token__OP_MOD + 1;         // = [QBASIC VB * *]
const t_token token__OP_UNEQUAL      = token__OP_EQUAL + 1;       // <> [QBASIC VB * *]
const t_token token__OP_GREATER_EQUAL = token__OP_UNEQUAL + 1;    // >=  [QBASIC VB * *] Attention: double character symbols must definded before single character symbols using same character
const t_token token__OP_LESSER_EQUAL   = token__OP_GREATER_EQUAL + 1; // <=  [QBASIC VB * *] Attention: double character symbols must definded before single character symbols using same character
const t_token token__OP_GREATER      = token__OP_LESSER_EQUAL + 1; // > [QBASIC VB * *]
const t_token token__OP_LESSER       = token__OP_GREATER + 1;     // < [QBASIC VB * *]
const t_token token__OP_AND            = token__OP_LESSER + 1;    // AND [QBASIC VB * *]
const t_token token__OP_ANDALSO        = token__OP_AND + 1;    // ANDALSO [* * * KBASIC]
const t_token token__OP_OR           = token__OP_ANDALSO + 1;         // OR [QBASIC VB * *]
const t_token token__OP_ORELSE           = token__OP_OR + 1;         // ORELSE [* * * KBASIC]
const t_token token__OP_NOT            = token__OP_ORELSE + 1;        // NOT [QBASIC VB * *]
const t_token token__OP_POWER      = token__OP_NOT + 1;       // ^ [QBASIC VB * *]
const t_token token__OP_STR_CAT      = token__OP_POWER + 1;    // &  [* VB * *]
const t_token token__OP_XOR          = token__OP_STR_CAT + 1;     // XOR [QBASIC VB * *]
const t_token token__OP_IDIV           = token__OP_XOR + 1;       // \ [QBASIC VB * *]     Integer divison, no remainder
const t_token token__OP_EQV          = token__OP_IDIV + 1;        // EQV [QBASIC VB * *]  means x EQV y = NOT (x XOR y)
const t_token token__OP_IMP          = token__OP_EQV + 1;         // IMP [QBASIC VB * *]   means x IMP y = NOT (x AND NOT y)
/*
const t_token token__OP_OR2          = token__OP_IMP + 1;                // | [* * * *]
const t_token token__OP_NOT2         = token__OP_OR2 + 1;                // ! [* * * *]
const t_token token__OP_EQUAL2       = token__OP_NOT2 + 1;               // == [* * * *]
const t_token token__OP_UNEQUAL2    = token__OP_EQUAL2 + 1;              // != [* * * *]
const t_token token__OP_AND_EQUAL    = token__OP_UNEQUAL2 + 1;           // &= [* * * *]
const t_token token__OP_OR_EQUAL    = token__OP_AND_EQUAL + 1;           // |= [* * * *]
const t_token token__OP_XOR_EQUAL    = token__OP_OR_EQUAL + 1;           // ^= [* * * *]
const t_token token__OP_LESSER_LESSER    = token__OP_XOR_EQUAL + 1;       // << [* * * *]
const t_token token__OP_GREATER_GREATER    = token__OP_LESSER_LESSER + 1;  // >> [* * * *]
*/




//   MISCELLANEOUS
const t_token token__MISC     = 1700;

const t_token token__MSC_IDENTIFIER  = token__MISC + 1;
const t_token token__MSC_EXTIDENTIFIER  = token__MSC_IDENTIFIER + 1; // mit Umlauten � ...

const t_token token__MSC_ID_INTEGER  = token__MSC_EXTIDENTIFIER + 1; // suffix % [QBASIC * * *]
const t_token token__MSC_ID_DOUBLE  = token__MSC_ID_INTEGER + 1; // suffix # [QBASIC * * *]
const t_token token__MSC_ID_SINGLE  = token__MSC_ID_DOUBLE + 1; // suffix ! [QBASIC * * *]
const t_token token__MSC_ID_QSTRING  = token__MSC_ID_SINGLE + 1; // suffix $ [QBASIC * * *]
const t_token token__MSC_ID_LONG  = token__MSC_ID_QSTRING + 1; // suffix & [QBASIC * * *]
const t_token token__MSC_ID_CURRENCY  = token__MSC_ID_LONG + 1; // suffix @

const t_token token__MSC_LABEL      = token__MSC_ID_CURRENCY + 1; // [QBASIC * * *]
const t_token token__MSC_LINE         = token__MSC_LABEL + 1; // [QBASIC * * *]
const t_token token__MSC_EOL          = token__MSC_LINE + 1;


//   KBASIC INTERN
const t_token token__NUM_KB     = 1800;

const t_token token__KB_FILENAME     = token__NUM_KB + 1;
const t_token token__KB_ROW     = token__KB_FILENAME + 1;
const t_token token__KB_LINE     = token__KB_ROW + 1;
const t_token token__KB_EOF     = token__KB_LINE + 1;
const t_token token__KB_EOF2     = token__KB_EOF + 1;
/*
const t_token token__KB_CONST     = token__KB_EOF2 + 1;
const t_token token__KB_IF     = token__KB_CONST + 1;
const t_token token__KB_ELSEIF     = token__KB_IF + 1;
const t_token token__KB_ELSE     = token__KB_ELSEIF + 1;
const t_token token__KB_END     = token__KB_ELSE + 1;
*/
const t_token token__KB_VERSION     = token__KB_EOF2 + 1;



class token {
public:
  token();
  ~token();

  //bool setGUI(_mainwindow *my_mainwindow);
  //bool processGUI(int msec);


//  bool setErrorWindow(_syntaxError *serroroutw);
  //bool setInfoWindow(_infoconsole *info);

static const char *keyword_(t_token n, bool b = true)
{
  switch(n){

  case token___DYNAMIC:         if (b) return "$DYNAMIC"; return "$Dynamic";
  case token___ELSE:            if (b) return "#ELSE"; return "#Else";
  case token___END:             if (b) return "$END"; return "$End";
  case token___EXTERNALSOURCE:  if (b) return "#EXTERNALSOURCE"; return "#ExternalSource";
  case token___IF:              if (b) return "#IF"; return "#If";
  case token___REGION:          if (b) return "#REGION"; return "#Region";    
  case token___STATIC:          if (b) return "$STATIC"; return "$Static";
  case token__ABSOLUTE:         if (b) return "ABSOLUTE"; return "Absolute";    
  case token__ABSTRACT:         if (b) return "ABSTRACT"; return "Abstract";
  case token__ADDRESSOF:        if (b) return "ADDRESSOF"; return "AddressOf";    
  case token__ALIAS:            if (b) return "ALIAS"; return "Alias";    
  case token__ANSI:             if (b) return "ANSI"; return "Ansi";    
  case token__AS:               if (b) return "AS"; return "As";
  case token__ASSEMBLY:         if (b) return "ASSEMBLY"; return "Assembly";    
  case token__AUTO:             if (b) return "AUTO"; return "Auto";    
  case token__BASE:             if (b) return "BASE"; return "Base";
  case token__BY_REF:           if (b) return "BYREF";  return "ByRef";
  case token__BY_VAL:           if (b) return "BYVAL"; return "ByVal";
  case token__CALL:             if (b) return "CALL"; return "Call";
  case token__CALLBYNAME:       if (b) return "CALLBYNAME"; return "CallByName";    
  case token__CASE:             if (b) return "CASE"; return "Case";
  case token__CATCH:            if (b) return "CATCH";  return "Catch";
  case token__CHAIN:            if (b) return "CHAIN"; return "Chain";
  case token__CHOOSE:           if (b) return "CHOOSE"; return "Choose";
  case token__CLASS_INITIALIZE: if (b) return "CLASS_INITIALIZE"; return "Class_Initialize";
  case token__CLASS_TERMINATE:  if (b) return "CLASS_TERMINATE"; return "Class_Terminate";
  case token__CLASS:            if (b) return "CLASS";  return "Class";
  case token__COM:              if (b) return "COM"; return "COM";    
  case token__COMMON:           if (b) return "COMMON"; return "Common";
  case token__COMPARE:          if (b) return "COMPARE";  return "Compare";
  case token__CONNECT:          if (b) return "CONNECT";  return "Connect";
  case token__CONST:            if (b) return "CONST"; return "Const";
  case token__CONSTRUCTOR:      if (b) return "CONSTRUCTOR";  return "Constructor";    
  case token__DATA:             if (b) return "DATA"; return "Data";
  case token__DATABASE:         if (b) return "DATABASE"; return "Database";
  case token__DATETIME:         if (b) return "DATETIME"; return "DateTime";
  case token__DEBUG:               if (b) return "DEBUG"; return "Debug";
  case token__DECIMAL:          if (b) return "DECIMAL";  return "Decimal";    
  case token__DECLARE:          if (b) return "DECLARE"; return "Declare";
  case token__DEF:              if (b) return "DEF"; return "Def";
  case token__DEFAULT:          if (b) return "DEFAULT"; return "Default";    
  case token__DEFBOOL:          if (b) return "DEFBOOL"; return "DefBool";
  case token__DEFBYTE:          if (b) return "DEFBYTE"; return "DefByte";
  case token__DEFCUR:           if (b) return "DEFCUR"; return "DefCur";
  case token__DEFDATE:          if (b) return "DEFDATE"; return "DefDate";
  case token__DEFDBL:           if (b) return "DEFDBL"; return "DefDbl";
  case token__DEFINT:           if (b) return "DEFINT"; return "DefInt";
  case token__DEFLNG:           if (b) return "DEFLNG"; return "DefLng";
  case token__DEFOBJ:           if (b) return "DEFOBJ"; return "DefObj";
  case token__DEFSNG:           if (b) return "DEFSNG"; return "DefSng";
  case token__DEFSTR:           if (b) return "DEFSTR"; return "DefStr";
  case token__DEFVAR:           if (b) return "DEFVAR"; return "DefVar";
  case token__DELEGATE:         if (b) return "DELEGATE"; return "Delegate";    
  case token__DESTRUCTOR:       if (b) return "DESTRUCTOR"; return "Destructor";    
  case token__DIM:              if (b) return "DIM"; return "Dim";
  case token__DIRECTCAST:       if (b) return "DIRECTCAST"; return "DirectCast";    
  case token__DISCONNECT:       if (b) return "DISCONNECT"; return "Disconnect";    
  case token__DO:               if (b) return "DO"; return "Do";
  case token__EACH:             if (b) return "EACH"; return "Each";
  case token__ECHO:             if (b) return "ECHO"; return "Echo";
  case token__ELSE:             if (b) return "ELSE"; return "Else";
  case token__ELSEIF:           if (b) return "ELSEIF"; return "ElseIf";
  case token__EMPTY:            if (b) return "EMPTY"; return "Empty";    
  case token__END:              if (b) return "END"; return "End";
  case token__ENDIF:            if (b) return "ENDIF"; return "EndIf";
  case token__ENUM:             if (b) return "ENUM"; return "Enum";    
  case token__ERASE:            if (b) return "ERASE"; return "Erase";
  case token__EVENT:            if (b) return "EVENT"; return "Event";    
  case token__EXIT:             if (b) return "EXIT"; return "Exit";
  case token__EXPLICIT:         if (b) return "EXPLICIT"; return "Explicit";
  //case token__EXTENDS:          if (b) return "EXTENDS"; return "Extends";
  case token__FINALLY:          if (b) return "FINALLY"; return "Finally";    
  case token__FOR:              if (b) return "FOR"; return "For";
  case token__FRIEND:           if (b) return "FRIEND"; return "Friend";
  case token__FUNCTION:         if (b) return "FUNCTION"; return "Function";
  case token__GLOBAL:           if (b) return "GLOBAL"; return "Global";
  case token__GET:              if (b) return "GET"; return "Get";
  case token__GOSUB:            if (b) return "GOSUB"; return "GoSub";
  case token__GOTO:             if (b) return "GOTO"; return "GoTo";
  case token__HANDLES:          if (b) return "HANDLES"; return "Handles";    
  case token__IF:               if (b) return "IF"; return "If";
  case token__IIF:              if (b) return "IIF"; return "IIf";
  case token__IMPLEMENTS:       if (b) return "IMPLEMENTS"; return "Implements";
  case token__IMPORTS:          if (b) return "IMPORTS"; return "Imports";    
  case token__IN:               if (b) return "IN"; return "In";
  case token__INHERITS:         if (b) return "INHERITS"; return "Inherits";    
  case token__INT:              if (b) return "INT"; return "Int";
  case token__INTERFACE:        if (b) return "INTERFACE"; return "Interface";    
  case token__IS:               if (b) return "IS"; return "Is";
  case token__ITERATE:          if (b) return "ITERATE"; return "Iterate";
  case token__KBASIC:           if (b) return "KBASIC"; return "KBasic";
  case token__KEY:              if (b) return "KEY"; return "Key";    
  case token__LBOUND:           if (b) return "LBOUND"; return "LBound";
  case token__LET:              if (b) return "LET"; return "Let";
  case token__LIB:              if (b) return "LIB"; return "Lib";    
  case token__LIKE:             if (b) return "LIKE"; return "Like";
  case token__LOOP:             if (b) return "LOOP"; return "Loop";
  case token__LSET:             if (b) return "LSET"; return "LSet";
  case token__ME:               if (b) return "ME"; return "Me";
  case token__MID:              if (b) return "MID"; return "Mid";
  case token__MODULE:           if (b) return "MODULE"; return "Module";
  case token__MUSTINHERIT:      if (b) return "MUSTINHERIT"; return "MustInherit";    
  case token__MUSTOVERRIDE:     if (b) return "MUSTOVERRIDE"; return "MustOverride";    
  case token__MY:           if (b) return "MY"; return "My";    
  case token__MYBASE:           if (b) return "MYBASE"; return "MyBase";    
  case token__MYCLASS:          if (b) return "MYCLASS"; return "MyClass";    
  case token__NAMESPACE:        if (b) return "NAMESPACE"; return "NameSpace";    
  case token__NEW:              if (b) return "NEW"; return "New";
  case token__NEXT:             if (b) return "NEXT"; return "Next";
  case token__NOTHING:          if (b) return "NOTHING"; return "Nothing";
  case token__NOTINHERITABLE:   if (b) return "NOTINHERITABLE"; return "NotInheritable";    
  case token__NOTOVERRIDABLE:   if (b) return "NOTOVERRIDABLE"; return "NotOverridable";    
  case token__NULL:             if (b) return "NULL"; return "Null";
  case token__OFF:              if (b) return "OFF"; return "Off";
  case token__OLDBASIC:         if (b) return "OLDBASIC"; return "OldBasic";
  case token__ON:               if (b) return "ON"; return "On";
  case token__OPTION:           if (b) return "OPTION"; return "Option";
  case token__OPTIONAL:         if (b) return "OPTIONAL"; return "Optional";
  case token__OVERLOADS:        if (b) return "OVERLOADS"; return "Overloads";    
  case token__OVERRIDABLE:      if (b) return "OVERRIDABLE"; return "Overriddable";    
  case token__OVERRIDES:        if (b) return "OVERRIDES"; return "Overrides";    
  case token__PARAMARRAY:       if (b) return "PARAMARRAY"; return "ParamArray";
  case token__PARENT:           if (b) return "PARENT"; return "Parent";
  case token__PEN:              if (b) return "PEN"; return "Pen";    
  case token__PLAY:             if (b) return "PLAY"; return "Play";    
  case token__PRESERVE:         if (b) return "PRESERVE"; return "Preserve";
  case token__PRIVATE:          if (b) return "PRIVATE"; return "Private";
  case token__PROPERTY:         if (b) return "PROPERTY"; return "Property";
  case token__PROTECTED:        if (b) return "PROTECTED"; return "Protected";    
  case token__PUBLIC:           if (b) return "PUBLIC"; return "Public";
  case token__RANGE:            if (b) return "RANGE"; return "Range";
  case token__READ:             if (b) return "READ"; return "Read";
  case token__READONLY:         if (b) return "READONLY"; return "ReadOnly";    
  case token__REDIM:            if (b) return "REDIM"; return "ReDim";
  case token__REM_MULTILINE:    if (b) return "/*"; return "/*";
  case token__REM_MULTILINE_STOP:  if (b) return "*/"; return "*/";    
  case token__REM_DOCUMENTATION: if (b) return "/**"; return "/**";    
  case token__REM_SHORT:        if (b) return "'"; return "'"; 
  case token__REM:              if (b) return "REM"; return "Rem"; 
  case token__REPEAT:           if (b) return "REPEAT"; return "Repeat"; 
  case token__RESTORE:          if (b) return "RESTORE"; return "Restore"; 
  case token__RESUME:           if (b) return "RESUME"; return "Resume"; 
  case token__RETURN:           if (b) return "RETURN"; return "Return"; 
  case token__RSET:             if (b) return "RSET"; return "RSet"; 
  case token__RUN:              if (b) return "RUN"; return "Run"; 
  case token__SELECT:           if (b) return "SELECT"; return "Select"; 
  case token__SET:              if (b) return "SET"; return "Set"; 
  case token__SHADOWS:          if (b) return "SHADOWS"; return "Shadows"; 
  case token__SHARED:           if (b) return "SHARED"; return "Shared"; 
  //case token__SHORT:            if (b) return "SHORT"; return "Short"; 
  case token__SIGNAL:           if (b) return "SIGNAL"; return "Signal"; 
  case token__SIZE:           if (b) return "SIZE"; return "Size"; 
  case token__SLOT:             if (b) return "SLOT"; return "Slot"; 
  case token__STATIC:           if (b) return "STATIC"; return "Static"; 
  case token__STEP:             if (b) return "STEP"; return "Step"; 
  case token__STOP:             if (b) return "STOP"; return "Stop"; 
  case token__STRIG:            if (b) return "STRIG"; return "STRIG";     
  case token__STRUCTURE:        if (b) return "STRUCTURE"; return "Structure";     
  case token__SUB:              if (b) return "SUB"; return "Sub"; 
  case token__SWAP:             if (b) return "SWAP"; return "Swap"; 
  case token__SWITCH:           if (b) return "SWITCH"; return "Switch"; 
  case token__SYNCLOCK:         if (b) return "SYNCLOCK"; return "SynClock";      
  case token__SYSTEM:           if (b) return "SYSTEM"; return "System"; 
  case token__TEXT:             if (b) return "TEXT"; return "Text"; 
  case token__THEN:             if (b) return "THEN"; return "Then"; 
  case token__THROW:            if (b) return "THROW"; return "Throw"; 
  case token__THROWS:           if (b) return "THROWS"; return "Throws"; 
  case token__TIMER:            if (b) return "TIMER"; return "Timer"; 
  case token__TO:               if (b) return "TO"; return "To"; 
  case token__TROFF:            if (b) return "TROFF"; return "TROFF"; 
  case token__TRON:             if (b) return "TRON"; return "TRON";     
  case token__TRY:              if (b) return "TRY"; return "Try"; 
  case token__TYPE:             if (b) return "TYPE"; return "Type"; 
  case token__TYPEDEF:          if (b) return "TYPEDEF"; return "TypeDef"; 
  case token__UBOUND:           if (b) return "UBOUND"; return "UBound"; 
  case token__UNICODE:          if (b) return "UNICODE"; return "UniCode";    
  case token__UNTIL:            if (b) return "UNTIL"; return "Until"; 
  case token__VARPTR_:          if (b) return "VARPTR$"; return "VARPTR$";    
  case token__VARPTR:           if (b) return "VARPTR"; return "VARPTR";    
  case token__VARSEG:           if (b) return "VARSEG"; return "VARSEG";  
  case token__VERYOLDBASIC:     if (b) return "VERYOLDBASIC"; return "VeryOldBasic"; 
  case token__WAIT:             if (b) return "WAIT"; return "Wait";    
  case token__WEND:             if (b) return "WEND"; return "Wend"; 
  case token__WHILE:            if (b) return "WHILE"; return "While"; 
  case token__WITH:             if (b) return "WITH"; return "With"; 
  case token__WITHEVENTS:       if (b) return "WITHEVENTS"; return "WithEvents"; 
  case token__WRITEONLY:        if (b) return "WRITEONLY"; return "WriteOnly"; 

  case token__ENCODE:        if (b) return "ENCODE"; return "Encode"; 
  case token__DECODE:        if (b) return "DECODE"; return "Decode"; 

  default: return "";
  }
}

static const char *builtin_(t_token n, bool b = true)
{
  switch(n){

  case token__CREATEOBJECT:     if (b) return "CREATEOBJECT"; return "CreateObject";    

  case token__ERL:              if (b) return "ERL"; return "Erl";
  case token__ERR:              if (b) return "ERR"; return "Err";
  case token__RAISEEVENT:       if (b) return "RAISEEVENT"; return "RaiseEvent";
  case token__CBCD:             if (b) return "CBCD"; return "CBCD";
  case token__CEXT:             if (b) return "CEXT"; return "CEXT";
  case token__CFIX:             if (b) return "CFIX"; return "CFIX";
  case token__CQUD:             if (b) return "CQUD"; return "CQUD";
  case token__FN:               if (b) return "FN"; return "FN";

  case token__COMMAND:          if (b) return "COMMAND";  return "Command";    
  case token__ENVIRON_:         if (b) return "ENVIRON$"; return "Environ$";    
  case token__ENVIRON:          if (b) return "ENVIRON"; return "Environ";    
  case token__LOADRESSTRING:    if (b) return "LOADRESSTRING"; return "LoadResString";

  case token____CLASS__:          if (b) return "__CLASS__";  return "__Class__";
  case token____LINE__:           if (b) return "__LINE__"; return "__Line__";
  case token____MODULE__:         if (b) return "__MODULE__";  return "__Module__";
  case token____SCOPE__:          if (b) return "__SCOPE__"; return "__Scope__";
  case token____SUB__:            if (b) return "__SUB__"; return "__Sub__";
  case token____ISLINUX__:        if (b) return "__ISLINUX__"; return "__IsLinux__";
  case token____ISWINDOWS__:      if (b) return "__ISWINDOWS__"; return "__IsWindows__";
  case token____ISMACOS__:        if (b) return "__ISMACOS__"; return "__IsMacOS__";
  case token____FILE__:           if (b) return "__FILE__"; return "__File__";
  case token____ISCLASS__:        if (b) return "__ISCLASS__"; return "__IsClass__";
  case token____ISMODULE__:       if (b) return "__ISMODULE__"; return "__IsModule__";
  case token____ISSUB__:          if (b) return "__ISSUB__"; return "__IsSub__";

  case token__ABS:                if (b) return "ABS"; return "Abs";
  case token__ABSOLUTE:           if (b) return "ABSOLUTE"; return "Absolute";
  case token__ACCESS:             if (b) return "ACCESS"; return "Access";
  case token__ACS:                if (b) return "ACS"; return "Acs";
  case token__ADDHANDLER:         if (b) return "ADDHANDLER"; return "AddHandler";
  case token__APPACTIVATE:        if (b) return "APPACTIVATE"; return "AppActiviate";
  case token__APPEND:             if (b) return "APPEND"; return "Append";
  case token__ARRAY:              if (b) return "ARRAY"; return "Array";
  case token__ASC:                if (b) return "ASC"; return "Asc";
  case token__ASN:                if (b) return "ASN"; return "Asn";
  case token__ATN:                if (b) return "ATN"; return "Atn";
  case token__BEEP:               if (b) return "BEEP"; return "Beep";
  case token__BIN_:               if (b) return "BIN$"; return "Bin$";
  case token__BIN:                if (b) return "BIN"; return "Bin";
  case token__BINARY:             if (b) return "BINARY"; return "Binary";
  case token__BLOAD:              if (b) return "BLOAD"; return "BLOAD";
  case token__BSAVE:              if (b) return "BSAVE"; return "BSAVE";
  case token__CBOOL:              if (b) return "CBOOL"; return "CBool";
  case token__CBYTE:              if (b) return "CBYTE"; return "CByte";
  case token__CCHAR:              if (b) return "CCHAR"; return "CChar";
  case token__CCUR:               if (b) return "CCUR"; return "CCur";
  case token__CDATE:              if (b) return "CDATE"; return "CDate";
  case token__CDBL:               if (b) return "CDBL"; return "CDbl";
  case token__CDEC:               if (b) return "CDEC"; return "CDec";
  case token__CHAIN:              if (b) return "CHAIN"; return "Chain";
  case token__CHDIR:              if (b) return "CHDIR"; return "ChDir";
  case token__CHDRIVE:            if (b) return "CHDRIVE"; return "ChDrive";
  case token__CHR_:               if (b) return "CHR$"; return "Chr$";
  case token__CHR:                if (b) return "CHR"; return "Chr";
  case token__CINT:               if (b) return "CINT"; return "CInt";
  case token__CIRCLE:             if (b) return "CIRCLE"; return "Circle";
  case token__CLEAR:              if (b) return "CLEAR"; return "Clear";
  case token__CLNG:               if (b) return "CLNG"; return "CLng";
  case token__CLOSE:              if (b) return "CLOSE"; return "Close";
  case token__CLS:                if (b) return "CLS"; return "CLS";
  case token__COBJ:               if (b) return "COBJ"; return "CObj";
  case token__COLOR:              if (b) return "COLOR"; return "Color";
  case token__COM:                if (b) return "COM"; return "COM";
  case token__COMMAND_:           if (b) return "COMMAND$"; return "Command$";
  case token__COMMON:             if (b) return "COMMON"; return "Common";
  case token__COS:                if (b) return "COS"; return "Cos";
  case token__CSHORT:             if (b) return "CSHORT"; return "CShort";
  case token__CSNG:               if (b) return "CSNG"; return "CSng";
  case token__CSRLIN:             if (b) return "CSRLIN"; return "CsrLin";
  case token__CTYPE:              if (b) return "CTYPE"; return "CType";
  case token__CURDIR_:            if (b) return "CURDIR$"; return "CurDir$";
  case token__CURDIR:             if (b) return "CURDIR"; return "CurDir";
  //case token__CVAR:               if (b) return "CVAR"; return "CVar";
  case token__CVD:                if (b) return "CVD"; return "CVD";
  case token__CVDMBF:             if (b) return "CVDMBF"; return "CVDMBF";
  case token__CVERR:              if (b) return "CVERR"; return "CVERR";
  case token__CVI:                if (b) return "CVI"; return "CVI";
  case token__CVL:                if (b) return "CVL"; return "CVL";
  case token__CVS:                if (b) return "CVS"; return "CVS";
  case token__CVSMBF:             if (b) return "CVSMBF"; return "CVSMBF";
  case token__DATE_:              if (b) return "DATE$"; return "Date$";
  case token__DATE:               if (b) return "DATE"; return "Date";
  case token__DATEADD:            if (b) return "DATEADD"; return "DateAdd";
  case token__DATEDIFF:           if (b) return "DATEDIFF"; return "DateDiff";
  case token__DATEPART:           if (b) return "DATEPART"; return "DatePart";
  case token__DATESERIAL:         if (b) return "DATESERIAL"; return "DateSerial";
  case token__DATEVALUE:          if (b) return "DATEVALUE"; return "DateValue";
  case token__DAY:                if (b) return "DAY"; return "Day";
  case token__DDB:                if (b) return "DDB"; return "DDB";
  case token__DECLARE:            if (b) return "DECLARE"; return "Declare";
  case token__DEG:                if (b) return "DEG"; return "Deg";
  case token__DELETESETTING:      if (b) return "DELETESETTING"; return "DeleteSetting";
  case token__DIR_:               if (b) return "DIR$"; return "Dir$";
  case token__DIR:                if (b) return "DIR"; return "Dir";
  case token__DOEVENTS:           if (b) return "DOEVENTS"; return "DoEvents";
  case token__DOF:                if (b) return "DOF"; return "DOF";
  case token__DRAW:               if (b) return "DRAW"; return "Draw";
  case token__EOF_:               if (b) return "EOF"; return "EOF";
  case token__ERDEV_:             if (b) return "ERDEV$"; return "ErDev$";
  case token__ERDEV:              if (b) return "ERDEV"; return "ErDev";
  case token__ERROR_:             if (b) return "ERROR$"; return "Error$";
  case token__ERROR:              if (b) return "ERROR"; return "Error";
  case token__EXP:                if (b) return "EXP"; return "Exp";
  case token__FACT:               if (b) return "FACT"; return "Fact";
  case token__FIELD:              if (b) return "FIELD"; return "Field";
  case token__FILE:           if (b) return "FILE"; return "File";
  case token__FILEATTR:           if (b) return "FILEATTR"; return "FileAttr";
  case token__FILECOPY:           if (b) return "FILECOPY"; return "FileCopy";
  case token__FILEDATETIME:       if (b) return "FILEDATETIME"; return "FileDateTime";
  case token__FILELEN:            if (b) return "FILELEN"; return "FileLen";
  case token__FILES:              if (b) return "FILES"; return "Files";
  case token__FILTER:             if (b) return "FILTER"; return "Filter";
  case token__FIX:                if (b) return "FIX"; return "Fix";
  case token__FORMAT_:            if (b) return "FORMAT$"; return "Format$";
  case token__FORMAT:             if (b) return "FORMAT"; return "Format";
  case token__FORMATCURRENCY:     if (b) return "FORMATCURRENCY"; return "FormatCurrency";
  case token__FORMATDATETIME:     if (b) return "FORMATDATETIME"; return "FormatDateTime";
  case token__FORMATNUMBER:       if (b) return "FORMATNUMBER"; return "FormatNumber";
  case token__FORMATPERCENT:      if (b) return "FORMATPERCENT"; return "FormatPercent";
  case token__FRAC:               if (b) return "FRAC"; return "Frac";
  case token__FRE:                if (b) return "FRE"; return "FRE";
  //case token__FREE:               if (b) return "FREE"; return "Free";
  case token__FREEFILE:           if (b) return "FREEFILE"; return "FreeFile";
  case token__FV:                 if (b) return "FV"; return "FV";
  case token__GET:                if (b) return "GET"; return "Get";
  case token__GETALLSETTINGS:     if (b) return "GETALLSETTINGS"; return "GetAllSettings";
  case token__GETATTR:            if (b) return "GETATTR"; return "GetAttr";
  case token__GETAUTOSERVERSETTINGS: if (b) return "GETAUTOSERVERSETTINGS"; return "GetAutoServerSettings";
  case token__GETOBJECT:          if (b) return "GETOBJECT"; return "GetObject";
  case token__GETSETTING:         if (b) return "GETSETTING"; return "GetSetting";
  case token__GETTYPE:            if (b) return "GETTYPE"; return "GetType";
  case token__HEX_:               if (b) return "HEX$"; return "Hex$";
  case token__HEX:                if (b) return "HEX"; return "Hex";
  case token__HOUR:               if (b) return "HOUR"; return "Hour";
  case token__HYPOT:              if (b) return "HYPOT"; return "Hypot";
  case token__IMESTATUS:          if (b) return "IMESTATUS"; return "IMEStatus";
  case token__INKEY_:             if (b) return "INKEY$"; return "Inkey$";
  case token__INKEY:              if (b) return "INKEY"; return "Inkey";
  case token__INP:                if (b) return "INP"; return "Inp";
  case token__INPUT:              if (b) return "INPUT"; return "Input";
  case token__INPUT_:              if (b) return "INPUT$"; return "Input$";    
  case token__INPUTBOX:           if (b) return "INPUTBOX"; return "InputBox";
  case token__INSTR:              if (b) return "INSTR"; return "InStr";
  case token__INSTREV:            if (b) return "INSTREV"; return "InStRev";
  case token__INT:                if (b) return "INT"; return "Int";
  case token__IOCTL_:             if (b) return "IOCTL$"; return "IOCtl$";
  case token__IOCTL:              if (b) return "IOCTL"; return "IOCtl";
  case token__IPMT:               if (b) return "IPMT"; return "IPMT";
  case token__IRR:                if (b) return "IRR"; return "IRR";
  case token__ISARRAY:            if (b) return "ISARRAY"; return "IsArray";
  case token__ISBOOLEAN:          if (b) return "ISBOOLEAN"; return "IsBoolean";
  case token__ISBYTE:             if (b) return "ISBYTE"; return "IsByte";
  //case token__ISCHARACTER:        if (b) return "ISCHARACTER"; return "IsCharacter";
  //case token__ISCOLLECTION:       if (b) return "ISCOLLECTION"; return "IsCollection";
  case token__ISCSTRING:          if (b) return "ISCSTRING"; return "IsCString";
  case token__ISCURRENCY:         if (b) return "ISCURRENCY"; return "IsCurrency";
  case token__ISDATE:             if (b) return "ISDATE"; return "IsDate";
  case token__ISDOUBLE:           if (b) return "ISDOUBLE"; return "IsDouble";
  case token__ISEMPTY:            if (b) return "ISEMPTY"; return "IsEmpty";
  case token__ISERROR:            if (b) return "ISERROR"; return "IsError";
  case token__ISINTEGER:          if (b) return "ISINTEGER"; return "IsInteger";
  case token__ISMISSING:          if (b) return "ISMISSING"; return "IsMissing";
  case token__ISNULL:             if (b) return "ISNULL"; return "IsNull";
  case token__ISNUMERIC:          if (b) return "ISNUMERIC"; return "IsNumeric";
  case token__ISOBJECT:           if (b) return "ISOBJECT"; return "IsObject";
  case token__ISSHORT:            if (b) return "ISSHORT"; return "IsShort";
  case token__ISSINGLE:           if (b) return "ISSINGLE"; return "IsSingle";
  case token__ISLONG:           if (b) return "ISLONG"; return "IsLong";
  case token__ISSTRING:           if (b) return "ISSTRING"; return "IsString";
  case token__ISVARIANT:           if (b) return "ISVARIANT"; return "IsVariant";

  case token__ISLINUX:           if (b) return "ISLINUX"; return "IsLinux";
  case token__ISMAC:           if (b) return "ISMAC"; return "IsMac";
  case token__ISWINDOWS:           if (b) return "ISWINDOWS"; return "IsWindows";

  case token__JOIN:               if (b) return "JOIN"; return "Join";
  case token__KEY:                if (b) return "KEY"; return "Key";
  case token__KBASICDIR:               if (b) return "KBASICDIR"; return "KBasicDir";
  case token__KILL:               if (b) return "KILL"; return "Kill";
  case token__LCASE_:             if (b) return "LCASE$"; return "LCase$";
  case token__LCASE:              if (b) return "LCASE"; return "LCase";
  case token__LEFT_:              if (b) return "LEFT$"; return "Left$";
  case token__LEFT:               if (b) return "LEFT"; return "Left";
  case token__LEN:                if (b) return "LEN"; return "Len";
  case token__LINE:               if (b) return "LINE"; return "Line";
  case token__LN:                 if (b) return "LN"; return "Ln";
  case token__LOAD:               if (b) return "LOAD"; return "Load";
  case token__LOADPICTURE:        if (b) return "LOADPICTURE"; return "LoadPicture";
  case token__LOADRESDATA:        if (b) return "LOADRESDATA"; return "LoadResData";
  case token__LOADRESPICTURE:     if (b) return "LOADRESPICTURE"; return "LoadResPicture";
  case token__LOC:                if (b) return "LOC"; return "Loc";
  case token__LOCATE:             if (b) return "LOCATE"; return "Locate";
  case token__LOCK:               if (b) return "LOCK"; return "Lock";
  case token__LOF:                if (b) return "LOF"; return "LOF";
  case token__LOG:                if (b) return "LOG"; return "Log";
  case token__LOGB:               if (b) return "LOGB"; return "Logb";
  case token__LPOS:               if (b) return "LPOS"; return "LPos";
  case token__LPRINT:             if (b) return "LPRINT"; return "LPrint";
  case token__LTRIM_:             if (b) return "LTRIM$"; return "LTrim$";
  case token__LTRIM:              if (b) return "LTRIM"; return "LTrim";
  case token__MAX:                if (b) return "MAX"; return "Max";
  case token__MID_:               if (b) return "MID$"; return "Mid$";
  case token__MID:                if (b) return "MID"; return "Mid";
  case token__MIN:                if (b) return "MIN"; return "Min";
  case token__MINUTE:             if (b) return "MINUTE"; return "Minute";
  case token__MIRR:               if (b) return "MIRR"; return "MIRR";
  case token__MKD_:               if (b) return "MKD$"; return "MKD$";
  case token__MKDIR:              if (b) return "MKDIR"; return "MkDir";
  case token__MKDMBF_:            if (b) return "MKDMBF$"; return "MKDMBF$";
  case token__MKI_:               if (b) return "MKI$"; return "MKI$";
  case token__MKL_:               if (b) return "MKL$"; return "MKL$";
  case token__MKS_:               if (b) return "MKS_"; return "MKS$";
  case token__MKS:                if (b) return "MKS"; return "MKS"; 
  case token__MKSMBF_:            if (b) return "MKSMBF$"; return "MKSMBF$";
  case token__MONTH:              if (b) return "MONTH"; return "Month";
  case token__MONTHNAME:          if (b) return "MONTHNAME"; return "MonthName";
  case token__MSGBOX:             if (b) return "MSGBOX"; return "MsgBox";
  case token__MTIMER:             if (b) return "MTIMER"; return "MTIMER";
  case token__NAME:               if (b) return "NAME"; return "Name";
  case token__NOW:                if (b) return "NOW"; return "Now";
  case token__NPER:               if (b) return "NPER"; return "NPER";
  case token__NPV:                if (b) return "NPV"; return "NPV"; 
  case token__NZ:                 if (b) return "NZ"; return "Nz";
  case token__OCT_:               if (b) return "OCT$"; return "Oct$";
  case token__OCT:                if (b) return "OCT"; return "Oct";
  case token__OPEN:               if (b) return "OPEN"; return "Open";
  case token__OUT:                if (b) return "OUT"; return "Out";
  case token__OUTPUT:             if (b) return "OUTPUT"; return "Output";
  case token__PAINT:              if (b) return "PAINT"; return "Paint";
  case token__PALETTE:            if (b) return "PALETTE"; return "Palette";
  case token__PARTITION:          if (b) return "PARTITION"; return "Partition";
  case token__PCOPY:              if (b) return "PCOPY"; return "PCopy";
  case token__PEEK:               if (b) return "PEEK"; return "Peek";
  case token__PEN:                if (b) return "PEN"; return "Pen";
  case token__PLAY:               if (b) return "PLAY"; return "Play";
  case token__PMAP:               if (b) return "PMAP"; return "PMAP";
  case token__PMT:                if (b) return "PMT"; return "PMT";
  case token__POINT:              if (b) return "POINT"; return "Point";
  case token__POKE:               if (b) return "POKE"; return "Poke";
  case token__POS:                if (b) return "POS"; return "Pos";
  case token__PPMT:               if (b) return "PPMT"; return "PPMT";
  case token__PRESET:             if (b) return "PRESET"; return "Preset";
  case token__PRINT:              if (b) return "PRINT"; return "Print";
  case token__PRINTSCREEN:        if (b) return "PRINTSCREEN"; return "PrintScreen";
  case token__PSET:               if (b) return "PSET"; return "PSet";
  case token__PUT:                if (b) return "PUT"; return "Put";
  case token__PV:                 if (b) return "PV"; return "PV";
  case token__QBCOLOR:            if (b) return "QBCOLOR"; return "QBCOLOR";
  case token__RAD:                if (b) return "RAD"; return "Rad";
  case token__RAISE:              if (b) return "RAISE"; return "Raise";
  case token__RAISESIGNAL:        if (b) return "RAISESIGNAL"; return "RaiseSignal";
  //case token__RAISEVENT:          if (b) return "RAISEVENT"; return "RaiseEvent";
  case token__RANDOM:             if (b) return "RANDOM"; return "Random";
  case token__RANDOMIZE:          if (b) return "RANDOMIZE"; return "Randomize";
  case token__RATE:               if (b) return "RATE"; return "Rate";
  case token__READ:               if (b) return "READ"; return "Read";
  case token__REMOVEHANDLER:      if (b) return "REMOVEHANDLER"; return "RemoveHandler";
  case token__REPLACE:            if (b) return "REPLACE"; return "Replace";
  case token__RESET:              if (b) return "RESET"; return "Reset";
  case token__RGB:                if (b) return "RGB"; return "RGB";
  case token__RIGHT_:             if (b) return "RIGHT$"; return "Right$";
  case token__RIGHT:              if (b) return "RIGHT"; return "Right";
  case token__RMDIR:              if (b) return "RMDIR"; return "RmDir";
  case token__RND:                if (b) return "RND"; return "RND";
  case token__ROUND:              if (b) return "ROUND"; return "Round";
  case token__RTRIM_:             if (b) return "RTRIM$"; return "RTrim$";
  case token__RTRIM:              if (b) return "RTRIM"; return "RTrim";
  case token__RUN:                if (b) return "RUN"; return "Run";
  case token__SAVEPICTURE:        if (b) return "SAVEPICTURE"; return "SavePicture";
  case token__SAVESETTING:        if (b) return "SAVESETTING"; return "SaveSetting";
  case token__SCREEN:             if (b) return "SCREEN"; return "Screen";
  case token__SEC:                if (b) return "SEC"; return "Sec";
  case token__SECOND:             if (b) return "SECOND"; return "Second";
  case token__SEEK:               if (b) return "SEEK"; return "Seek";
  case token__SEG:                if (b) return "SEG"; return "Seg";
  case token__SENDKEYS:           if (b) return "SENDKEYS"; return "SendKeys";
  case token__SETATTR:            if (b) return "SETATTR"; return "SetAttr";
  case token__SGN:                if (b) return "SGN"; return "Sgn";
  case token__SHARED:             if (b) return "SHARED"; return "Shared";
  case token__SHELL:              if (b) return "SHELL"; return "Shell";
  case token__SIN:                if (b) return "SIN"; return "Sin";
  case token__SLEEP:              if (b) return "SLEEP"; return "Sleep";
  case token__SLN:                if (b) return "SLN"; return "Sln";
  case token__SOUND:              if (b) return "SOUND"; return "Sound";
  case token__SPACE_:             if (b) return "SPACE$"; return "Space$";
  case token__SPACE:              if (b) return "SPACE"; return "Space";
  case token__SPC:                if (b) return "SPC"; return "Spc";
  case token__SPLIT:              if (b) return "SPLIT"; return "Split"; 
  case token__SQR:                if (b) return "SQR"; return "Sqr";
  case token__STATIC:             if (b) return "STATIC"; return "Static";
  case token__STEP:               if (b) return "STEP"; return "Step";
  case token__STICK:              if (b) return "STICK"; return "Stick";
  case token__STR_:               if (b) return "STR$"; return "Str$";
  case token__STR:                if (b) return "STR"; return "Str";
  case token__STRCOMP:            if (b) return "STRCOMP"; return "StrComp";
  case token__STRCONV:            if (b) return "STRCONV"; return "StrConv";
  case token__STRIG:              if (b) return "STRIG"; return "STRIG";
  case token__STRING_:            if (b) return "STRING$"; return "String$";
  case token__STRING:             if (b) return "STRING"; return "String";
  case token__STRREVERSE:         if (b) return "STRREVERSE"; return "StrReverse";
  case token__SYD:                if (b) return "SYD"; return "SYD";
  case token__TAB:                if (b) return "TAB"; return "Tab";
  case token__TAN:                if (b) return "TAN"; return "Tan";
  case token__TIME_:              if (b) return "TIME$"; return "Time$";
  case token__TIME:               if (b) return "TIME"; return "Time";
  case token__TIMER:              if (b) return "TIMER"; return "Timer";
  case token__TIMESERIAL:         if (b) return "TIMESERIAL"; return "TimeSerial";
  case token__TIMEVALUE:          if (b) return "TIMEVALUE"; return "TimeValue";
  case token__TRIM_:              if (b) return "TRIM$"; return "Trim$";
  case token__TRIM:               if (b) return "TRIM"; return "Trim";
  case token__TYPENAME:           if (b) return "TYPENAME"; return "TypeName";
  case token__TYPEOF:             if (b) return "TYPEOF"; return "TypeOf";
  case token__UCASE_:             if (b) return "UCASE$"; return "UCase$";
  case token__UCASE:              if (b) return "UCASE"; return "UCase";
  case token__UNLOAD:             if (b) return "UNLOAD"; return "UnLoad";
  case token__UNLOCK:             if (b) return "UNLOCK"; return "UnLock";
  case token__UTF8:               if (b) return "UTF8"; return "Utf8";
  case token__UTF16:              if (b) return "UTF16"; return "Utf16";
  case token__USING:              if (b) return "USING"; return "Using";
  case token__VAL:                if (b) return "VAL"; return "Val";
  case token__VARPTR_:            if (b) return "VARPTR$"; return "VARPTR$";
  case token__VARPTR:             if (b) return "VARPTR"; return "VARPTR";
  case token__VARSEG:             if (b) return "VARSEG"; return "VARSEG";
  case token__VARTYPE:            if (b) return "VARTYPE"; return "VarType";
  case token__VIEW:               if (b) return "VIEW"; return "View";
  case token__WAIT:               if (b) return "WAIT"; return "Wait";
  case token__WEEKDAY:            if (b) return "WEEKDAY"; return "Weekday";
  case token__WEEKDAYNAME:        if (b) return "WEEKDAYNAME"; return "WeekdayName";
  case token__WIDTH:              if (b) return "WIDTH"; return "Width";
  case token__WINDOW:             if (b) return "WINDOW"; return "Window";
  case token__WRITE:              if (b) return "WRITE"; return "Write";
  case token__YEAR:               if (b) return "YEAR"; return "Year";

  case token__LENGTH:               if (b) return "LENGTH"; return "Length";
  case token__COMPARE:               if (b) return "COMPARE"; return "Compare";
  case token__CONTAINS:               if (b) return "CONTAINS"; return "Contains";
  case token__COUNT:               if (b) return "COUNT"; return "Count";
  case token__INDEXOF:               if (b) return "INDEXOF"; return "IndexOf";
  case token__ENDSWITH:               if (b) return "ENDSWITH"; return "EndsWith";
  case token__STARTSWITH:               if (b) return "STARTSWITH"; return "StartsWith";
  case token__FILL:               if (b) return "FILL"; return "Fill";
  case token__INSERT:               if (b) return "INSERT"; return "Insert";
  case token__LASTINDEXOF:               if (b) return "LASTINDEXOF"; return "LastIndexOf";
  case token__LEFTJUSTIFIED:               if (b) return "LEFTJUSTIFIED"; return "LeftJustified";
  case token__PREPEND:               if (b) return "PREPEND"; return "Prepend";
  case token__REMOVE:               if (b) return "REMOVE"; return "Remove";
  case token__RIGHTJUSTIFIED:               if (b) return "RIGHTJUSTIFIED"; return "RightJustified";
  case token__SECTION:               if (b) return "SECTION"; return "Section";
  case token__SIMPLIFIED:               if (b) return "SIMPLIFIED"; return "Simplified";
  case token__UPPER:               if (b) return "UPPER"; return "Upper";
  case token__LOWER:               if (b) return "LOWER"; return "Lower";
  case token__TRIMMED:               if (b) return "TRIMMED"; return "Trimmed";
  case token__TRUNCATE:               if (b) return "TRUNCATE"; return "Truncate";
  //case token__UNICODE:               if (b) return "UNICODE"; return "Unicode";
  case token__VALUE:               if (b) return "VALUE"; return "Value";
  case token__REVERSED:               if (b) return "REVERSED"; return "Reversed";
  case token__READBINARY:               if (b) return "READBINARY"; return "ReadBinary";
  case token__WRITEBINARY:               if (b) return "WRITEBINARY"; return "WriteBinary";
  case token__SEEKBINARY:               if (b) return "SEEKBINARY"; return "SeekBinary";

  case token__DAYOFWEEK:               if (b) return "DAYOFWEEK"; return "DayOfWeek";
  case token__DAYOFYEAR:               if (b) return "DAYOFYEAR"; return "DayOfYear";
  case token__DAYSINMONTH:               if (b) return "DAYSINMONTH"; return "DaysInMonth";
  case token__DAYSINYEAR:               if (b) return "DAYSINYEAR"; return "DaysInYear";
  case token__WEEKNUMBER:               if (b) return "WEEKNUMBER"; return "WeekNumber";
  case token__ISLEAPYEAR:               if (b) return "ISLEAPYEAR"; return "IsLeapYear";
  case token__DIFFDAY:               if (b) return "DIFFDAY"; return "DiffDay";
  case token__DIFFSECONDS:               if (b) return "DIFFSECONDS"; return "DiffSeconds";
//  case token__ADDDATE:               if (b) return "ADDDATE"; return "AddDate";
  case token__ADDDAYS:               if (b) return "ADDDAYS"; return "AddDays";
  case token__ADDMONTHS:               if (b) return "ADDMONTHS"; return "AddMonths";
  case token__ADDYEARS:               if (b) return "ADDYEARS"; return "AddYears";
 // case token__SUBDATE:               if (b) return "SUBDATE"; return "SubDate";
  case token__SUBDAYS:               if (b) return "SUBDAYS"; return "SubDays";
  case token__SUBMONTHS:               if (b) return "SUBMONTHS"; return "SubMonths";
  case token__SUBYEARS:               if (b) return "SUBYEARS"; return "SubYears";
//  case token__ADDTIME:               if (b) return "ADDTIME"; return "AddTime";
  case token__ADDHOURS:               if (b) return "ADDHOURS"; return "AddHours";
  case token__ADDMINUTES:               if (b) return "ADDMINUTES"; return "AddMinutes";
  case token__ADDSECONDS:               if (b) return "ADDSECONDS"; return "AddSeconds";
 // case token__SUBTIME:               if (b) return "SUBTIME"; return "SubTime";
  case token__SUBHOURS:               if (b) return "SUBHOURS"; return "SubHours";
  case token__SUBMINUTES:               if (b) return "SUBMINUTES"; return "SubMinutes";
  case token__SUBSECONDS:               if (b) return "SUBSECONDS"; return "SubSeconds";
  case token__ISDATEVALID:               if (b) return "ISDATEVALID"; return "IsDateValid";
  case token__ISTIMEVALID:               if (b) return "ISTIMEVALID"; return "IsTimeValid";
  case token__ISDATETIMEVALID:               if (b) return "ISDATETIMEVALID"; return "IsDateTimeValid";
  case token__DAYNAME:               if (b) return "DAYNAME"; return "DayName";




  default: return "";
  }
}


//   DATATYPES
static const char *type_(t_token n, bool b = true)
{
  switch(n)
  {
  case token__TYP_DOUBLE:     if (b) return "DOUBLE"; return "Double";
  case token__TYP_SHORT:      if (b) return "SHORT"; return "Short";
  case token__TYP_INTEGER:    if (b) return "INTEGER"; return "Integer";
  case token__TYP_QSTRING:     if (b) return "STRING";  return "String";
  case token__TYP_CSTRING:    if (b) return "CSTRING"; return "CString";
  case token__TYP_BOOLEAN:    if (b) return "BOOLEAN"; return "Boolean";
  case token__TYP_LONG:       if (b) return "LONG"; return "Long";
  case token__TYP_SINGLE:     if (b) return "SINGLE"; return "Single";
  case token__TYP_BYTE:       if (b) return "BYTE"; return "Byte";
  case token__TYP_VARIANT:    if (b) return "VARIANT"; return "Variant";
  case token__TYP_CURRENCY:   if (b) return "CURRENCY"; return "Currency";
  case token__TYP_DATE:       if (b) return "DATE"; return "Date";
  case token__TYP_OBJECT:     if (b) return "OBJECT"; return "Object";
  case token__TYP_ANY:        if (b) return "ANY"; return "Any";
  case token__TYP_CASTEXCEPTION:     if (b) return "CASTEXCEPTION"; return "CastException";
  case token__TYP_QTEXCEPTION:     if (b) return "QTEXCEPTION"; return "QtException";
  case token__TYP_EXCEPTION:     if (b) return "EXCEPTION"; return "Exception";

  default: return "";
  }
}


//   LITERALS
static const char *literals_(t_token n)
{
  switch(n)
  {
  case token__LITERAL_DOUBLE: return "DOUBLE";
  case token__LITERAL_INTEGER: return "INTEGER";
  case token__LITERAL_STRING: return "STRING";
  case token__LITERAL_BOOLEAN: return "BOOLEAN";
  case token__LITERAL_SINGLE: return "SINGLE";
  case token__LITERAL_LONG: return "LONG";
  case token__LITERAL_CURRENCY: return "CURRENCY";
  case token__LITERAL_DATE: return "DATE";
  case token__LITERAL_TIME: return "TIME";
  case token__LITERAL_BYTE: return "BYTE";
  default: return "";
  }
}

//   SYMBOLS
static const char *symbol_(t_token n)
{
  switch(n)
  {
  case token__SYM_BR_OP: return "(";
  case token__SYM_BR_CL: return ")";
  case token__SYM_BC_OP: return "{";
  case token__SYM_BC_CL: return "}";
  case token__SYM_BS_OP: return "[";
  case token__SYM_BS_CL: return "]";
  case token__SYM_COMMA: return ",";
  case token__SYM_COLON: return ":";
  case token__SYM_DOT:   return ".";
  case token__SYM_EXCLAMATION:   return "!";
  case token__SYM_HASH:    return "#";
  case token__SYM_UL:    return "_";
  case token__SYM_QM:    return "?";
  case token__SYM_SEMICOL:  return ";";
  case token__SYM_TILDE:  return "~";         

  default: return "";
  }
}

//   OPERATORS
static const char *operator_(t_token n, bool b = true)
{
  switch(n)
  {
  case token__OP_ADD:           if (b) return "+"; return "+";
  case token__OP_SUB:           if (b) return "-"; return "-";
  case token__OP_MUL:           if (b) return "*"; return "*";
  case token__OP_DIV:           if (b) return "/"; return "/";
  case token__OP_MOD:           if (b) return "MOD"; return "Mod";
  case token__OP_EQUAL:         if (b) return "="; return "=";
  case token__OP_UNEQUAL:       if (b) return "<>"; return "<>";
  case token__OP_GREATER_EQUAL: if (b) return ">="; return ">="; // Attention: if (b)  double character symbols must definded before single character symbols using same character
  case token__OP_LESSER_EQUAL:  if (b) return "<="; return "<="; // Attention: if (b)  double character symbols must definded before single character symbols using same character
  case token__OP_GREATER:       if (b) return ">"; return ">";
  case token__OP_LESSER:        if (b) return "<"; return "<";
  case token__OP_AND:           if (b) return "AND"; return "And";
  case token__OP_ANDALSO:       if (b) return "ANDALSO"; return "AndAlso";
  case token__OP_OR:            if (b) return "OR"; return "Or";
  case token__OP_ORELSE:        if (b) return "ORELSE"; return "OrElse";
  case token__OP_NOT:           if (b) return "NOT"; return "Not";
  case token__OP_POWER:         if (b) return "^"; return "^";
  case token__OP_STR_CAT:       if (b) return "&"; return "&";
  case token__OP_XOR:           if (b) return "XOR"; return "Xor";
  case token__OP_IDIV:          if (b) return "\\"; return "\\";
  case token__OP_EQV:           if (b) return "EQV"; return "Eqv";
  case token__OP_IMP:           if (b) return "IMP"; return "Imp";
  case token__OP_SHL:          if (b) return "SHL"; return "Shl";
  //case token__OP_SHL_:           if (b) return "<<"; return "<<";
  case token__OP_SHR:          if (b) return "SHR"; return "Shr";
//  case token__OP_SHR_:           if (b) return ">>"; return ">>";
  case token__OP_INC:           if (b) return "INC"; return "Inc";
//  case token__OP_INC_:          if (b) return "++"; return "++";
  case token__OP_DEC:           if (b) return "DEC"; return "Dec";
//  case token__OP_DEC_:          if (b) return "--"; return "--";
    /*
  case token__OP_ADD_EQUAL:     if (b) return "+="; return "+=";
  case token__OP_SUB_EQUAL:     if (b) return "-="; return "-=";
  case token__OP_DIV_EQUAL:     if (b) return "/="; return "/=";
  case token__OP_MUL_EQUAL:     if (b) return "*="; return "*=";

  case token__OP_ADD_ADD:     if (b) return "++"; return "++";
  case token__OP_SUB_SUB:     if (b) return "--"; return "--";*/

  //case token__OP_OR_EQUAL:      if (b) return "|="; return "|=";
  //case token__OP_AND_EQUAL:     if (b) return "&="; return "&=";
  case token__OP_BIT_AND:       if (b) return "BITAND"; return "BitAnd";
  case token__OP_BIT_OR:        if (b) return "BITOR"; return "BitOr";
  case token__OP_BIT_XOR:       if (b) return "BITXOR"; return "BitXor";
  case token__OP_BIT_NOT:       if (b) return "BITNOT"; return "BitNot";
/*
  case token__OP_OR2:              if (b) return "|"; return "|";
  case token__OP_NOT2:             if (b) return "!"; return "!";
  case token__OP_EQUAL2:           if (b) return "=="; return "==";
  case token__OP_UNEQUAL2:         if (b) return "!="; return "!=";
  case token__OP_AND_EQUAL:        if (b) return "&="; return "&=";
  case token__OP_OR_EQUAL:         if (b) return "|="; return "|=";
  case token__OP_XOR_EQUAL:        if (b) return "^="; return "^=";
  case token__OP_LESSER_LESSER:    if (b) return "<<"; return "<<";
  case token__OP_GREATER_GREATER:  if (b) return ">>"; return ">>";
*/


  //  <<=    >>=

  default: return "";
  
  }
}


//   KBASIC INTERN
static const char *misc_(t_token n)
{
  switch(n)
  {
  case token__MSC_IDENTIFIER: return "ID";
  case token__MSC_EXTIDENTIFIER: return "EXTID";
  case token__MSC_ID_INTEGER: return "ID_INTEGER";
  case token__MSC_ID_DOUBLE: return "ID_DOUBLE";
  case token__MSC_ID_SINGLE: return "ID_SINGLE";
  case token__MSC_ID_QSTRING: return "ID_STRING";
  case token__MSC_ID_LONG: return "ID_LONG";
  case token__MSC_ID_CURRENCY: return "ID_CURRENCY";
  case token__MSC_LABEL: return "LABEL";
  case token__MSC_LINE: return "LINENO";
  case token__MSC_EOL: return "EOL";
  case token__KB_ROW: return "ROW";
  case token__KB_LINE: return "LINE";
  case token__KB_EOF: return "EOF";
  case token__KB_VERSION: return "VERSION";
/*
  case token__KB_CONST: return "#CONST";
  case token__KB_IF: return "#IF";
  case token__KB_ELSEIF: return "#ELSEIF";
  case token__KB_ELSE: return "#ELSE";
  case token__KB_END: return "#END";
  */
  default: return "";
  }
}

/*
t_token anCounter[MAX_TOKEN_ID];
int nCounter_all;


  void registerStatistics(t_token t)
  {
    if (t < 0 || t >= MAX_TOKEN_ID){
      tokenError("registerStatistics outside bounds");
      return;
    }
    anCounter[t]++; nCounter_all++;
  }*/

  void registerToken(t_token t)
  {
    nLastLastLastWrittenToken = nLastLastWrittenToken;
    nLastLastWrittenToken = nLastWrittenToken;
    nLastWrittenToken = t;
  }  

  int lastWrittenToken(){ return nLastWrittenToken; }
  int lastLastWrittenToken(){ return nLastLastWrittenToken; }
  int lastLastLastWrittenToken(){ return nLastLastLastWrittenToken; }


// ****************************
// * bool wr_Integer(int nStringPos, int nRowStart, int nRowEnd, int nTokenId, int nInt)
// *
// * parameter:
// * int nXPos = row position of token in line
// * t_token nTokenId = describe which kind of token will be written
// * t_integer nInt = the int to add to the array
// *
// * return:
// * true, if an int could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_Integer(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_integer nInt)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_Integer(nInt));

    //registerStatistics(nTokenId);
    registerToken(nTokenId);
	
}

void wr_Integer2(int n)
{
  ba->wr_Integer(n);
}

// ****************************
// * bool wr_Char(char cChar)
// *
// * parameter:
// * char cChar = the char to add to the array
// *
// * return:
// * true, if a char could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_Char(char cChar)
{
	(ba->wr_Char(cChar));

    //registerToken(cChar); not needed there -> performance

}

// ****************************
// * bool wr_Boolean(int nStringPos, int nRowStart, int nRowEnd, int nTokenId, char cChar)
// *
// * parameter:
// * t_token nTokenId = describe which kind of token will be written
// * t_boolean cChar = the char to add to the array
// *
// * return:
// * true, if a char could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_Boolean(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_boolean cChar)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_Boolean(cChar));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);
	
}

// ****************************
void wr_Byte(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_byte b)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_Byte(b));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);
	
}

// ****************************
void wr_Currency(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_currency b)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_Currency(b));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);
	
}

// ****************************
void wr_Date(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_date b)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_Date(b));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);
	
}

// ****************************
void wr_Time(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_date b)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_Time(b));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);
	
}

// ****************************
// * bool wr_String(int nStringPos, int nRowStart, int nRowEnd, int nTokenId, const char *cChar)
// *
// * parameter:
// * nStringPos, nRowStart, nRowEnd = row position of token in line
// * t_token nTokenId = describe which kind of token will be written
// * t_string s = the pointer to the string to add to the array
// *
// * return:
// * true, if the string could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_CString(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_cstring s)
{
	wr_CString(nStringPos, nRowStart, nRowEnd, nTokenId, s, strlen(s));
}

// ****************************
// * bool wr_String(int nStringPos, int nRowStart, int nRowEnd, int nTokenId, const char *cChar, int nLen)
// *
// * parameter:
// * nStringPos, nRowStart, nRowEnd = row position of token in line
// * t_token nTokenId = describe which kind of token will be written
// * t_string s = the pointer to the string to add to the array
// * int nLen = the length of the string, maybe *cChar is not zero-terminated or has different length
// *
// * return:
// * true, if the string could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_CString(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_cstring s, int nLen)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_CString(s, nLen));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);

}

void wr_CString2(t_cstring acChar, int nLen)
{
	 (ba->wr_CString2(acChar, nLen));

}
/*
void wr_CString(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_cstring s)
{
	wr_CString(nStringPos, nRowStart, nRowEnd, nTokenId, s, strlen(s));
}

void wr_CString(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_cstring s, int nLen)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_CString(s, nLen));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);
}
*/
// ****************************
// * bool wr_Single(int nStringPos, int nRowStart, int nRowEnd, int nTokenId, int fSingle)
// *
// * parameter:
// * int nXPos = row position of token in line
// * t_token nTokenId = describe which kind of token will be written
// * t_single fSingle = the float to add to the array
// *
// * return:
// * true, if a float could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_Single(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_single fSingle)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_Single(fSingle));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);

}


// ****************************
// * bool wr_Double(int nStringPos, int nRowStart, int nRowEnd, int nTokenId, double dDouble)
// *
// * parameter:
// * int nXPos = row position of token in line
// * t_token nTokenId = describe which kind of token will be written
// * t_double dDouble = the double to add to the array
// *
// * return:
// * true, if a double could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_Double(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_double dDouble)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_Double(dDouble));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);
	
}

// ****************************
// * bool wr_Long(int nStringPos, int nRowStart, int nRowEnd, int nTokenId, long lLong)
// *
// * description:
// * checks if there's enough memory in a dynamic array to add a long to
// * if not it gets more memory, then adds the long to the array
// *
// * parameter:
// * int nXPos = row position of token in line
// * t_token nTokenId = describe which kind of token will be written
// * t_long lLong = the long to add to the array
// *
// * return:
// * true, if a long could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_Long(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId, t_long lLong)
{
  wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));
	(ba->wr_Long(lLong));

//    registerStatistics(nTokenId);
    registerToken(nTokenId);

}

// ****************************
// * bool wr_Token(int nStringPos, int nRowStart, int nRowEnd, int nTokenId)
// *
// * parameter:
// * int nXPos = row position of token in line
// * t_token nTokenId = the char to add to the array
// *
// * return:
// * true, if a char could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_Token(int nStringPos, int nRowStart, int nRowEnd, t_token nTokenId)
{
	wr_XPos(nStringPos, nRowStart, nRowEnd);
	(ba->wr_Token(nTokenId));

    //registerStatistics(nTokenId);
    registerToken(nTokenId);
	
}

// ****************************
// * bool wr_XPos(int nStringPos, int nRowStart, int nRowEnd)
// *
// * description:
// * checks if there's enough memory in a dynamic array to add a long to
// * if not it gets more memory, then adds the long to the array
// *
// * parameter:
// * int nXPos = row position of token in line
// *
// * return:
// * true, if a long could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_XPos(int nStringPos, int nRowStart, int nRowEnd)
{
	(ba->wr_Token(token__KB_ROW));
	(ba->wr_Integer(nStringPos));
	(ba->wr_Integer(nRowStart));
	(ba->wr_Integer(nRowEnd));

	
}

void rd_XPos(int nPos)
{
	register int token__KB_ROW = ba->rd_Token(nPos);
  nStringPos = ba->rd_Integer();
  nRowStart = ba->rd_Integer();
  nRowEnd = ba->rd_Integer();
/*
  if (nRowStart == 6){
    nRowStart = nRowStart;
  }
*/
}

t_byte rd_Byte(int nPos = -1)
{
	return ba->rd_Byte(nPos);
}

t_boolean rd_Boolean(int nPos = -1)
{
	return ba->rd_Boolean(nPos);
}

char rd_Char(int nPos = -1)
{
	return ba->rd_Char(nPos);
}

t_cstring rd_CString(int nPos = -1)
{
	return ba->rd_CString(nPos);
}
/*
t_cstring rd_CString(int nPos = -1)
{
	return ba->rd_CString(nPos);
}
*/
t_single rd_Single(int nPos = -1)
{
	return ba->rd_Single(nPos);
}

t_double rd_Double(int nPos = -1)
{
	return ba->rd_Double(nPos);
}

t_integer rd_Integer(int nPos = -1)
{
	return ba->rd_Integer(nPos);
}

t_long rd_Long(int nPos = -1)
{
	return ba->rd_Long(nPos);
}

t_currency rd_Currency(int nPos = -1)
{
	return ba->rd_Currency(nPos);
}

t_date rd_Date(int nPos = -1)
{
	return ba->rd_Date(nPos);
}

t_date rd_Time(int nPos = -1)
{
	return ba->rd_Time(nPos);
}

t_token peekToken(int nPos = -1)
{
  register int n = ba->getPos();
  rd_XPos(nPos);

	t_token t = ba->peekToken();
  ba->setPos(n);
  return t;
}

t_token rd_Token(int nPos = -1)
{
  rd_XPos(nPos);
	return ba->rd_Token();
}

int getStringPos()
{
	return nStringPos;
}

int getRowStart()
{
	return nRowStart;
}

int getRowEnd()
{
	return nRowEnd;
}

void setStringPos(int n)
{
  nStringPos = n;
}

void setRowStart(int n)
{
  nRowStart = n;
}

void setRowEnd(int n)
{
  nRowEnd = n;
}

/*
	reset current index to start
*/
void resetPos(bool bResetSource = true)
{
	ba->resetPos();
  if (bResetSource) sSource = "";
  bError = false;
}

/*
	reset current index to start
*/
int getPos()
{
	return ba->getPos();
}

/*
	reset current index to start
*/
void setPos(int nPos)
{
	ba->setPos(nPos);
}

int getSize()
{
	return ba->getSize();
}

int getSize2()
{
	return ba->getSize2();
}

bool append(token *t)
{
  return ba->append(t->ba);
}

/*
void dump()
{
	if (HAS_CONSOLE) CONSOLE print("-- dump token --\n\n", console__RED);
	ba->dump();
	if (HAS_CONSOLE) CONSOLE pcodePrintCR();
}
*/
/*
bool showError(XString s)
{
  if (serroroutw != 0) serroroutw->showError("", 0, s);
  return true;
}*/

// ****************************
// * bool tokenError(const char *actokenError)
// *
// * description:
// * prints a token error message
// *
// * parameter:
// * char *actokenError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool tokenError(const char *actokenError)
{
  if (bError) return false;

	char *acText = myTextbuffer->get(1024 + strlen(actokenError));

	sprintf(acText, "\ntoken error: %s\n", actokenError);
	if (HAS_CONSOLE != 0) CONSOLE printError(acText);
//  showError(acText);
  bError = true;

	return false;
}
/*
bool formatOneToken(int *nStringPos, int *nRowStart, int *nRowEnd, int *color, t_token *my_token, const char **acToken, bool *bError, int *nCurrentLine)
{
  return printOneToken(true, nStringPos, nRowStart, nRowEnd, color, my_token, acToken, bError, nCurrentLine) & !(*bError);
}*/

bool printOneToken(bool *bError)
{
  int nStringPos = 0;
  int nRowStart = 0;
  int nRowEnd = 0;
  int nCurrentLine = 0;
  int color = 0;
  t_token my_token = 0;
  const char* acToken = "";

  return printOneToken(false, &nStringPos, &nRowStart, &nRowEnd, &color, &my_token, &acToken, bError, &nCurrentLine) & !(*bError);
}

// ****************************
// * bool printToken()
// *
// * description:
// * prints all scanned token (formatted)
// *
// * parameter:
// * none
// *
// * return:
// * true, if no error
// * false, if error occured
// ****************************
bool printOneToken(bool bOnlyFormat, int *nStringPos, int *nRowStart, int *nRowEnd, int *color, t_token *my_token, const char **acToken, bool *bError, int *nCurrentLine)
{
	static /**/ char *acBuffer; acBuffer = myTextbuffer->get(1024);
	static /**/ t_integer nValue;
	static /**/ t_cstring acValue;
	static /**/ t_boolean bValue;
	static /**/ t_long lValue;
	static /**/ t_single fValue;
	static /**/ t_double dValue;
	static /**/ t_currency myCurrency;
	static /**/ t_date myDate;

	static /**/ int nLen;
	static /**/ t_token nTest;

  if ((nTest = rd_Token()) != token__KB_EOF && nTest != token__KB_EOF2){

    *color = console__BLACK;
    *nStringPos = getStringPos();
    *nRowStart = getRowStart();
    *nRowEnd = getRowEnd();

		if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print("", console__BLACK); 
    //sprintf(acBuffer, "[%d/%d/%d]", *nStringPos, *nRowStart, *nRowEnd);
//		if (!bOnlyFormat) CONSOLE print(acBuffer, console__BLACK);

    *my_token = nTest;
    *acToken = "";
    switch (nTest){

			// all kbasic keywords, in alphabetic order      
      case token___DYNAMIC:
      case token___ELSE:
      case token___END:
      case token___EXTERNALSOURCE:
      case token___IF:
      case token___REGION:
      case token___STATIC:
      case token__ABSOLUTE: 
      case token__ABSTRACT:
      case token__ADDRESSOF:        
      case token__ALIAS: 		
      case token__ANSI: 	
      case token__AS:
      case token__ASSEMBLY: 
      case token__AUTO: 	
      case token__BASE:
      case token__BY_REF:
      case token__BY_VAL:
      case token__CALL:
      case token__CALLBYNAME: 
      case token__CASE:
      case token__CATCH:
      case token__CHAIN: 	
      case token__CHOOSE:
      case token__CLASS_INITIALIZE:
      case token__CLASS_TERMINATE:
      case token__CLASS:
      case token__COM: 		
      case token__COMMON:
      case token__COMPARE:
      case token__CONNECT:
      case token__CONST:
      case token__CONSTRUCTOR:
      case token__DATA:
      case token__DATABASE: 		        
      case token__DATETIME: 		        
      case token__DEBUG:
      case token__DECIMAL: 		
      case token__DECLARE: 	
      case token__DEF:
      case token__DEFAULT: 	
      case token__DEFBOOL:
      case token__DEFBYTE:
      case token__DEFCUR:
      case token__DEFDATE:
      case token__DEFDBL:
      case token__DEFINT:
      case token__DEFLNG:
      case token__DEFOBJ:
      case token__DEFSNG:
      case token__DEFSTR:
      case token__DEFVAR:
      case token__DELEGATE: 
      case token__DESTRUCTOR:
      case token__DIM:
      case token__DIRECTCAST:
      case token__DISCONNECT:
      case token__DO:
      case token__EACH:
      case token__ECHO:
      case token__ELSE:
      case token__ELSEIF:
      case token__EMPTY: 	
      case token__END:
      case token__ENDIF:
      case token__ENUM:
      case token__ERASE:
      case token__EVENT: 		
      case token__EXIT:
      case token__EXPLICIT:
      case token__FINALLY:
      case token__FOR:
      case token__FRIEND:
      case token__FUNCTION:
      case token__GET:
      case token__GLOBAL:
      case token__GOSUB:
      case token__GOTO:
      case token__HANDLES: 	
      case token__IF:
      case token__IIF:
      case token__IMPLEMENTS: 
      case token__IMPORTS: 	
      case token__IN:
      case token__INHERITS: 	
      case token__INTERFACE:
      case token__IS:
      case token__ISLINUX:
      case token__ISMAC:
      case token__ISWINDOWS:
      case token__ITERATE:
      case token__KBASIC:
      case token__KEY: 		
      case token__LBOUND:
      case token__LET:
      case token__LIB: 	
      case token__LIKE:
      case token__LOOP:
      case token__LSET:
      case token__ME:
      case token__MID:
      case token__MODULE:
      case token__MUSTINHERIT: 
      case token__MUSTOVERRIDE: 
      case token__MY: 
      case token__MYBASE: 
      case token__MYCLASS: 
      case token__NAMESPACE:
      case token__NEW:
      case token__NEXT:
      case token__NOTHING:
      case token__NOTINHERITABLE:
      case token__NOTOVERRIDABLE:
      case token__NULL:
      case token__OFF:
      case token__OLDBASIC:
      case token__ON:
      case token__OPTION:
      case token__OPTIONAL:
      case token__OVERLOADS: 	
      case token__OVERRIDABLE: 
      case token__OVERRIDES: 		
      case token__PARAMARRAY:
      case token__PARENT:
      case token__PEN: 	
      case token__PLAY: 	
      case token__PRESERVE:
      case token__PRIVATE:
      case token__PROPERTY:
      case token__PROTECTED:
      case token__PUBLIC:
      case token__RANGE:
      case token__READ:
      case token__READONLY: 	
      case token__REDIM:
      case token__REPEAT:
      case token__RESTORE:
      case token__RESUME:
      case token__RETURN:
      case token__RSET:
      case token__RUN: 	
      case token__SELECT:
      case token__SET:
      case token__SHADOWS: 
      case token__SHARED: 
      case token__SIGNAL: 		
      case token__SIZE:
      case token__SLOT: 		
      case token__STATIC:
      case token__STEP:
      case token__STOP:
      case token__STRIG: 	
      case token__STRUCTURE:
      case token__SUB:
      case token__SWAP: 	
      case token__SWITCH:
      case token__SYNCLOCK:
      case token__SYSTEM:
      case token__TEXT:
      case token__THEN:
      case token__THROW:
      case token__THROWS:
      case token__TIMER: 	
      case token__TO:
      case token__TROFF: 	
      case token__TRON: 	
      case token__TRY:
      case token__TYPE:
      case token__TYPEDEF:
      case token__UBOUND:
      case token__UNICODE:
      case token__UNTIL:
      case token__VARPTR_: 
      case token__VARPTR: 
      case token__VARSEG: 
      case token__VERYOLDBASIC:
      case token__WAIT: 	
      case token__WEND:
      case token__WHILE:
      case token__WITH:
      case token__WITHEVENTS:
      case token__WRITEONLY:
      case token__ENCODE:
      case token__DECODE:
          *color = console__BLUE;
          if (!bOnlyFormat && HAS_CONSOLE){
            CONSOLE print("");
            CONSOLE print(keyword_(nTest));
          }
          *acToken = keyword_(nTest);
          break;
//  clear und raise keine keywords mehr
      case token__REM_DOCUMENTATION:
          *color = console__GREEN;
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print("[/**]", console__GREEN);
          *acToken = "/**";
          goto t;
      case token__REM_MULTILINE:
          *color = console__GREEN;
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print("[/*]", console__GREEN);
          *acToken = "/*";
t:
					acValue = rd_CString();
			    //nLen = strlen(acValue);
					if (acValue[0] != 0){
						if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(acValue, console__GREEN);
					}
          /*
         if (acValue[nLen - 1] == '*' && acValue[nLen] == '/'){
					  if (!bOnlyFormat) CONSOLE print("[* /]", console__GREEN);
         }
         */
					break;

      case token__REM_MULTILINE_STOP:
          *acToken = "*/";
          *color = console__GREEN;
					break;

      case token__REM:
          *color = console__GREEN;
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(keyword_(token__REM), console__GREEN);
					acValue = rd_CString();
			    //nLen = strlen(acValue);
					if (acValue[0] != 0){
						if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(acValue, console__GREEN);
					}
          *acToken = keyword_(token__REM);
					break;
			case token__REM_SHORT:
          *color = console__GREEN;
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(keyword_(token__REM_SHORT), console__GREEN);
					acValue = rd_CString();
			    //nLen = strlen(acValue);
					if (acValue[0] != 0){
						if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(acValue, console__GREEN);
					}
          *acToken = keyword_(token__REM_SHORT);
					break;

		  // all builtin, in alphabetic order
      case token__CREATEOBJECT: 
      case token__RAISEEVENT:
      case token__ERDEV: 		
      case token__CBCD:
      case token__CEXT:
      case token__CFIX:        
      case token__CQUD:        
      case token__FN:
      case token__COMMAND: 		
      case token__ENVIRON_: 	
      case token__ENVIRON: 		
      case token__LOADRESSTRING:
      case token____CLASS__:
      case token____LINE__:
      case token____MODULE__:
      case token____SCOPE__:
      case token____SUB__:

      case token____FILE__:
      case token____ISCLASS__:
      case token____ISMODULE__:
      case token____ISSUB__:

      case token__ABS:
      case token__ACCESS:
      case token__ACS:
      case token__ADDHANDLER:
      case token__APPACTIVATE: 
      case token__APPEND:
      case token__ARRAY:
      case token__ASC:
      case token__ASN:
      case token__ATN:
      case token__BEEP:
      case token__BIN_:
      case token__BIN:
      case token__BINARY:
      case token__BLOAD:
      case token__BSAVE:
      case token__CBOOL:
      case token__CBYTE:
      case token__CCHAR: 
      case token__CCUR:
      case token__CDATE:
      case token__CDBL:
      case token__CDEC: 
      case token__CHDIR:
      case token__CHDRIVE:
      case token__CHR_:
      case token__CHR:
      case token__CINT:
      case token__CIRCLE:
      case token__CLEAR:
      case token__CLNG:
      case token__CLOSE:
      case token__CLS:
      case token__COBJ: 
      case token__COLOR:
      case token__COMMAND_:
      case token__COS:
      case token__CSHORT: 
      case token__CSNG:
      case token__CSRLIN:
      case token__CTYPE: 
      case token__CURDIR_:
      case token__CURDIR:
      case token__CVD: 
      case token__CVDMBF: 
      case token__CVERR:
      case token__CVI: 
      case token__CVL: 
      case token__CVS: 
      case token__CVSMBF: 
      case token__DATE_:
      case token__DATE:
      case token__DATEADD:
      case token__DATEDIFF:
      case token__DATEPART:
      case token__DATESERIAL:
      case token__DATEVALUE:
      case token__DAY:
      case token__DDB: 
      case token__DEG:
      case token__DELETESETTING: 
      case token__DIR_:
      case token__DIR:
      case token__DOEVENTS:
      case token__DOF:
      case token__DRAW:
      case token__EOF_:
      case token__ERDEV_:
      case token__ERL:
      case token__ERR:
      case token__ERROR_:
      case token__ERROR:
      case token__EXP:
      case token__FACT:
      case token__FIELD:
      case token__FILE:
      case token__FILEATTR:
      case token__FILECOPY: 
      case token__FILEDATETIME:
      case token__FILELEN:
      case token__FILES:
      case token__FILTER: 
      case token__FIX:
      case token__FORMAT_:
      case token__FORMAT:
      case token__FORMATCURRENCY: 
      case token__FORMATDATETIME: 
      case token__FORMATNUMBER: 
      case token__FORMATPERCENT:
      case token__FRAC:
      case token__FRE:
//      case token__FREE:
      case token__FREEFILE:
      case token__FV: 

      case token__GETALLSETTINGS: 
      case token__GETATTR:
      case token__GETAUTOSERVERSETTINGS: 
      case token__GETOBJECT: 
      case token__GETSETTING: 
      case token__GETTYPE: 
      case token__HEX_:
      case token__HEX:
      case token__HOUR:
      case token__HYPOT:
      case token__IMESTATUS: 
      case token__INKEY_:
      case token__INKEY:
      case token__INP:
      case token__INPUT:
      case token__INPUT_:        
      case token__INPUTBOX:
      case token__INSTR:
      case token__INSTREV:
      case token__INT:
      case token__IOCTL_:
      case token__IOCTL:
      case token__IPMT: 
      case token__IRR: 
      case token__ISARRAY:
      case token__ISBOOLEAN: 
      case token__ISBYTE: 
      case token__ISCSTRING: 
      case token__ISCURRENCY:
      case token__ISDATE:
      case token__ISDOUBLE: 
      case token__ISEMPTY: 
      case token__ISERROR: 
      case token__ISINTEGER: 
      case token__ISMISSING:
      case token__ISNULL:
      case token__ISNUMERIC: 
      case token__ISOBJECT: 
      case token__ISSHORT: 
      case token__ISSINGLE: 
      case token__ISLONG:
      case token__ISSTRING:
      case token__ISVARIANT:
      case token____ISLINUX__:
      case token____ISWINDOWS__:
      case token____ISMACOS__:
      case token__JOIN: 
      case token__KBASICDIR:
      case token__KILL:
      case token__LCASE_:
      case token__LCASE:
      case token__LEFT_:
      case token__LEFT:
      case token__LEN:
      case token__LINE:
      case token__LN:
      case token__LOAD: 
      case token__LOADPICTURE: 
      case token__LOADRESDATA: 
      case token__LOADRESPICTURE:
      case token__LOC:
      case token__LOCATE:
      case token__LOCK:
      case token__LOF:
      case token__LOG:
      case token__LOGB:
      case token__LPOS:
      case token__LPRINT:
      case token__LTRIM_:
      case token__LTRIM:
      case token__MAX:
      case token__MID_:
      case token__MIN:
      case token__MINUTE:
      case token__MIRR:
      case token__MKD_:
      case token__MKDIR:
      case token__MKDMBF_: 
      case token__MKI_:
      case token__MKL_:
      case token__MKS_:
      case token__MKS:
      case token__MKSMBF_: 
      case token__MONTH:
      case token__MONTHNAME: 
      case token__MSGBOX:
      case token__MTIMER:
      case token__NAME:
      case token__NOW:
      case token__NPER: 
      case token__NPV: 
      case token__NZ:
      case token__OCT_:
      case token__OCT:
      case token__OPEN:
      case token__OUT:
      case token__OUTPUT:
      case token__PAINT:
      case token__PALETTE:
      case token__PARTITION: 
      case token__PCOPY:
      case token__PEEK:
      case token__PMAP:
      case token__PMT: 
      case token__POINT:
      case token__POKE:
      case token__POS:
      case token__PPMT:
      case token__PRESET:
      case token__PRINT:
      case token__PRINTSCREEN:
      case token__PSET:
      case token__PUT:
      case token__PV: 
      case token__QBCOLOR:
      case token__RAD:
      case token__RAISE:
      case token__RAISESIGNAL:
      case token__RANDOM:
      case token__RANDOMIZE:
      case token__RATE: 
      case token__REMOVEHANDLER: 
      case token__REPLACE: 
      case token__RESET:
      case token__RGB:
      case token__RIGHT_:
      case token__RIGHT:
      case token__RMDIR:
      case token__RND:
      case token__ROUND: 
      case token__RTRIM_:
      case token__RTRIM:
      case token__SAVEPICTURE: 
      case token__SAVESETTING: 
      case token__SCREEN:
      case token__SEC:
      case token__SECOND:
      case token__SEEK:
      case token__SEG:
      case token__SENDKEYS: 
      case token__SETATTR:
      case token__SGN:
      case token__SHELL:
      case token__SIN:
      case token__SLEEP:
      case token__SLN: 
      case token__SOUND: 
      case token__SPACE_:
      case token__SPACE:
      case token__SPC:
      case token__SPLIT: 
      case token__SQR:
      case token__STICK:
      case token__STR_:
      case token__STR:
      case token__STRCOMP:
      case token__STRCONV: 
      case token__STRING_:
      case token__STRING:
      case token__STRREVERSE: 
      case token__SYD: 
      case token__TAB:
      case token__TAN:
      case token__TIME_:
      case token__TIME:
      case token__TIMESERIAL:
      case token__TIMEVALUE:
      case token__TRIM_:
      case token__TRIM:
      case token__TYPENAME:
      case token__TYPEOF:
      case token__UCASE_:
      case token__UCASE:
      case token__UNLOAD: 
      case token__UNLOCK:
      case token__UTF8:
      case token__UTF16:
      case token__USING:
      case token__VAL:
      case token__VARTYPE:
      case token__VIEW:
      case token__WEEKDAY:
      case token__WEEKDAYNAME:
      case token__WIDTH:
      case token__WINDOW:
      case token__WRITE:
      case token__YEAR:

      case token__LENGTH:
//      case token__COMPARE:
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
//      case token__UNICODE:
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
      //case token__ADDDATE:     
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


          *color = console__CYAN;
				//if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print("[");
				if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(builtin_(nTest));
				//if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print("]");
          *acToken = builtin_(nTest);
          break;


			// all constants
			case token__LITERAL_BYTE:
          *color = console__MAGENTA;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_BYTE), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
          }
			    nValue = rd_Byte();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%d", nValue);
					  CONSOLE print(acBuffer, console__BLACK);
          }
					break;
			case token__LITERAL_INTEGER:
          *color = console__MAGENTA;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_INTEGER), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
          }
			    nValue = rd_Integer();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%d", nValue);
					  CONSOLE print(acBuffer, console__BLACK);
          }
					break;
			case token__LITERAL_LONG:
          *color = console__MAGENTA;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_LONG), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
          }
			    lValue = rd_Long();
          if (!bOnlyFormat && HAS_CONSOLE){

#ifdef WINDOWS // HIDE
					  sprintf(acBuffer, "%I64d", lValue); // HIDE
#else // HIDE
					  sprintf(acBuffer, "%lld", lValue); // HIDE
#endif // HIDE
            // UNHIDE sprintf(acBuffer, "%lld", lValue);
					  CONSOLE print(acBuffer, console__BLACK);
          }
					break;
			case token__LITERAL_DOUBLE:
          *color = console__MAGENTA;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_DOUBLE), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
          }
			    dValue = rd_Double();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%f", dValue);
					  CONSOLE print(acBuffer, console__MAGENTA);
          }
					break;
			case token__LITERAL_SINGLE:
          *color = console__MAGENTA;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_SINGLE), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
          }
			    fValue = rd_Single();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%f", fValue);
					  CONSOLE print(acBuffer, console__MAGENTA);
          }
					break;
			case token__LITERAL_STRING:
          *color = console__BLUE;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_STRING), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
					  CONSOLE print("\"", console__BLUE);
          }
					acValue = rd_CString();
			    //nLen = strlen(acValue);
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(acValue, console__BLUE);
					  CONSOLE print("\"", console__BLUE);
          }
					break;
			case token__LITERAL_BOOLEAN:
          *color = console__MAGENTA;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_BOOLEAN), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
          }
			    bValue = rd_Boolean();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%s", bValue ? "TRUE" : "FALSE");
					  CONSOLE print(acBuffer, console__BLACK);
          }
					break;
			case token__LITERAL_CURRENCY:
          *color = console__MAGENTA;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_CURRENCY), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
          }
			    myCurrency = rd_Currency();
					sprintf(acBuffer, "%s", myCurrency.toCString());
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(acBuffer, console__BLACK);
					break;
			case token__LITERAL_DATE:
          *color = console__MAGENTA;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_DATE), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
          }
			    myDate = rd_Date();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%s", myDate.toCString());
					  CONSOLE print(acBuffer, console__BLACK);
          }
					break;
			case token__LITERAL_TIME:
          *color = console__MAGENTA;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(literals_(token__LITERAL_TIME), console__BROWN);
					  CONSOLE print(" ", console__BROWN);
          }
			    myDate = rd_Date();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%s", myDate.toCString());
					  CONSOLE print(acBuffer, console__BLACK);
          }
					break;

			// all kbasic types
			case token__TYP_DOUBLE:
			case token__TYP_SINGLE:
			case token__TYP_LONG:
			case token__TYP_INTEGER:
			case token__TYP_SHORT:
			case token__TYP_QSTRING:
			case token__TYP_CSTRING:
			case token__TYP_BOOLEAN:
			case token__TYP_BYTE:
			case token__TYP_VARIANT:
			case token__TYP_CURRENCY:
			case token__TYP_DATE:
			case token__TYP_OBJECT:
			case token__TYP_ANY:
			case token__TYP_CASTEXCEPTION:
			case token__TYP_EXCEPTION:
			case token__TYP_QTEXCEPTION:
        


        //case token__TYP_COLLECTION:
          *color = console__RED;
          if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(type_(nTest));
          *acToken = type_(nTest);
          break;

			// all misc.
			case token__MSC_IDENTIFIER:
					goto next2;
			case token__MSC_EXTIDENTIFIER:
					goto next2;
			case token__MSC_ID_INTEGER:
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(misc_(token__MSC_ID_INTEGER), console__BROWN); // suffix %
					goto next;
			case token__MSC_ID_DOUBLE:
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(misc_(token__MSC_ID_DOUBLE), console__BROWN); // suffix #
					goto next;
			case token__MSC_ID_SINGLE:
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(misc_(token__MSC_ID_SINGLE), console__BROWN); // suffix !
					goto next;
			case token__MSC_ID_QSTRING:
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(misc_(token__MSC_ID_QSTRING), console__BROWN); // suffix $
					goto next;
			case token__MSC_ID_CURRENCY:
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(misc_(token__MSC_ID_CURRENCY), console__BROWN); // suffix @
					goto next;
			case token__MSC_ID_LONG:
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(misc_(token__MSC_ID_LONG), console__BROWN); // suffix &
					goto next;
next:
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(" ", console__BROWN);
next2:
					acValue = rd_CString();
			    //nLen = strlen(acValue);
				//	if (!bOnlyFormat) CONSOLE print("ID ", console__BLUE);
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(acValue, console__BLUE);
          *color = console__BLACK;
          *acToken = acValue;
					break;
			case token__MSC_EOL: 		 
        if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(misc_(token__MSC_EOL), console__BROWN); 
        break;
			case token__MSC_LABEL:
          *color = console__BLACK;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(misc_(token__MSC_LABEL));
					  CONSOLE print(" ");
          }
					acValue = rd_CString();
			    //nLen = strlen(acValue);
					if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(acValue, console__CYAN);
          *acToken = acValue;
					break;
			case token__MSC_LINE:
          *color = console__BLACK;
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print("", console__CYAN);
					  CONSOLE print(misc_(token__MSC_LINE));
					  CONSOLE print(" ");
          }
					acValue = rd_CString();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%-4.4s", acValue);
					  CONSOLE print(acBuffer, console__CYAN);
          }
					break;

			// all operators
			case token__OP_ADD:
			case token__OP_SUB:
			case token__OP_MUL:
			case token__OP_DIV:
			case token__OP_MOD:
			case token__OP_EQUAL:
			case token__OP_UNEQUAL:
			case token__OP_GREATER:
			case token__OP_LESSER:
			case token__OP_GREATER_EQUAL:
			case token__OP_LESSER_EQUAL:
			case token__OP_AND:
			case token__OP_ANDALSO:
			case token__OP_OR:
			case token__OP_ORELSE:
			case token__OP_NOT:
			case token__OP_POWER:
			case token__OP_XOR:
			case token__OP_STR_CAT:
			case token__OP_IDIV:
			case token__OP_EQV:
			case token__OP_IMP:
      case token__OP_SHL:
//      case token__OP_SHL_:
      case token__OP_SHR:
//      case token__OP_SHR_:
      case token__OP_INC:
//      case token__OP_INC_:
      case token__OP_DEC:
//      case token__OP_DEC_:
        /*
      case token__OP_ADD_EQUAL:
      case token__OP_SUB_EQUAL:
      case token__OP_DIV_EQUAL:
      case token__OP_MUL_EQUAL:
      case token__OP_ADD_ADD:		
      case token__OP_SUB_SUB:		*/
//      case token__OP_OR_EQUAL:
      //case token__OP_AND_EQUAL:
      case token__OP_BIT_AND:
      case token__OP_BIT_OR:
      case token__OP_BIT_XOR:
      case token__OP_BIT_NOT:
/*
      case token__OP_OR2:
      case token__OP_NOT2:
      case token__OP_EQUAL2:
      case token__OP_UNEQUAL2:
      case token__OP_AND_EQUAL:
      case token__OP_OR_EQUAL:
      case token__OP_XOR_EQUAL:
      case token__OP_LESSER_LESSER:
      case token__OP_GREATER_GREATER:*/

          *color = console__BLACK;

          if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(operator_(nTest));
          *acToken = operator_(nTest);
          break;

			// all symbols
			case token__SYM_BR_OP:
			case token__SYM_BR_CL:
			case token__SYM_BC_OP:
			case token__SYM_BC_CL:
			case token__SYM_BS_OP:
			case token__SYM_BS_CL:
			case token__SYM_COMMA:       
			case token__SYM_COLON:
			case token__SYM_DOT:
			case token__SYM_EXCLAMATION:
			case token__SYM_HASH:
			case token__SYM_UL:
			case token__SYM_QM:
			case token__SYM_SEMICOL:
			case token__SYM_TILDE:
          *color = console__BLACK;
          if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(symbol_(nTest), console__BLACK);
          *acToken = symbol_(nTest);
          break;

			// all constants
			case token__KB_LINE:
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print("\n");
					  CONSOLE print(misc_(token__KB_LINE), console__GREEN);
					  CONSOLE print(" ", console__GREEN);
          }
          *nCurrentLine = rd_Integer();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%05d", *nCurrentLine);
					  CONSOLE print(acBuffer, console__GREEN);
          }
					break;

			case token__KB_FILENAME:
					acValue = rd_CString();
					break;

			case token__KB_EOF2:					
					break;

/*
			case token__KB_CONST:
			case token__KB_IF:
			case token__KB_ELSEIF:
			case token__KB_ELSE:
			case token__KB_END:
          if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(misc_(nTest), console__CYAN);
          break;*/

			// all constants
			case token__KB_VERSION:
          if (!bOnlyFormat && HAS_CONSOLE){
					  CONSOLE print(misc_(token__KB_VERSION), console__GREEN);
					  CONSOLE print(" ", console__GREEN);
          }
			    fValue = rd_Single();
          if (!bOnlyFormat && HAS_CONSOLE){
					  sprintf(acBuffer, "%.6f", fValue);
					  CONSOLE print(acBuffer, console__GREEN);
          }
					break;

			default:
        tokenError("internal error while printing scanned tokens\n");
//				dump();
       *bError = true;
				return false;
				break;
		}

 		if (!bOnlyFormat && HAS_CONSOLE) CONSOLE print(" ");
		return true;

	}
	return false;
}


  void addSource(const char *ac);
  const char *getSource();

  //XString beautifiedTokenAsString(char *acText, XString &acAdd, QMap<XString, XString> *autohelp, QMap<XString, XString> *identifiers, bool b);  

  bytearray *ba;

  bool bOutdated;

private:



  t_token nLastWrittenToken;
  t_token nLastLastWrittenToken;
  t_token nLastLastLastWrittenToken;

  int nStringPos;
  int nRowStart;
  int nRowEnd;  

  textbuffer *myTextbuffer;
  textbuffer *myTextbuffer2;

//  bool tokenError(const char *acTokenError);

  bool bError;

  XString sSource;


/*
static const char *vb_error(int n)
{
  switch(n){
  case 3: return "Return without GoSub";
  case 5: return "Invalid procedure call";
  case 6: return "Overflow";
  case 7: return "Out of memory";
  case 9: return "Subscript out of range";
  case 10: return "This array is fixed or temporarily locked";
  case 11: return "Division by zero";
  case 13: return "Type mismatch";
  case 14: return "Out of string space";
  case 16: return "Expression too complex";
  case 17: return "Can't perform requested operation";
  case 18: return "User interrupt occurred";
  case 20: return "Resume without error";
  case 28: return "Out of stack space";
  case 35: return "Sub, Function, or Property not defined";
  case 47: return "Too many DLL application clients";
  case 48: return "Error in loading DLL";
  case 49: return "Bad DLL calling convention";
  case 51: return "Internal error";
  case 52: return "Bad file name or number";
  case 53: return "File not found";
  case 54: return "Bad file mode";
  case 55: return "File already open";
  case 57: return "Device I/O error";
  case 58: return "File already exists";
  case 59: return "Bad record length";
  case 61: return "Disk full";
  case 62: return "Input past end of file";
  case 63: return "Bad record number";
  case 67: return "Too many files";
  case 68: return "Device unavailable";
  case 70: return "Permission denied";
  case 71: return "Disk not ready";
  case 74: return "Can't rename with different drive";
  case 75: return "Path/File access error";
  case 76: return "Path not found";
  case 91: return "Object variable or With block variable not set";
  case 92: return "For loop not initialized";
  case 93: return "Invalid pattern string";
  case 94: return "Invalid use of Null";
  case 97: return "Can't call Friend procedure on an object that is not an instance of the defining class";
  case 98: return "A property or method call cannot include a reference to a private object, either as an argument or as a return value";
  case 298: return "System DLL could not be loaded";
  case 320: return "Can't use character device names in specified file names";
  case 321: return "Invalid file format";
  case 322: return "Cant create necessary temporary file";
  case 325: return "Invalid format in resource file";
  case 327: return "Data value named not found";
  case 328: return "Illegal parameter; can't write arrays";
  case 335: return "Could not access system registry";
  case 336: return "Component not correctly registered";
  case 337: return "Component not found";
  case 338: return "Component did not run correctly";
  case 360: return "Object already loaded";
  case 361: return "Can't load or unload this object";
  case 363: return "Control specified not found";
  case 364: return "Object was unloaded";
  case 365: return "Unable to unload within this context";
  case 368: return "The specified file is out of date. This program requires a later version";
  case 371: return "The specified object can't be used as an owner form for Show";
  case 380: return "Invalid property value";
  case 381: return "Invalid property-array index";
  case 382: return "Property Set can't be executed at run time";
  case 383: return "Property Set can't be used with a read-only property";
  case 385: return "Need property-array index";
  case 387: return "Property Set not permitted";
  case 393: return "Property Get can't be executed at run time";
  case 394: return "Property Get can't be executed on write-only property";
  case 400: return "Form already displayed; can't show modally";
  case 402: return "Code must close topmost modal form first";
  case 419: return "Permission to use object denied";
  case 422: return "Property not found";
  case 423: return "Property or method not found";
  case 424: return "Object required";
  case 425: return "Invalid object use";
  case 429: return "Component can't create object or return reference to this object";
  case 430: return "Class doesn't support Automation";
  case 432: return "File name or class name not found during Automation operation";
  case 438: return "Object doesn't support this property or method";
  case 440: return "Automation error";
  case 442: return "Connection to type library or object library for remote process has been lost";
  case 443: return "Automation object doesn't have a default value";
  case 445: return "Object doesn't support this action";
  case 446: return "Object doesn't support named arguments";
  case 447: return "Object doesn't support current locale setting";
  case 448: return "Named argument not found";
  case 449: return "Argument not optional or invalid property assignment";
  case 450: return "Wrong number of arguments or invalid property assignment";
  case 451: return "Object not a collection";
  case 452: return "Invalid ordinal";
  case 453: return "Specified not found";
  case 454: return "Code resource not found";
  case 455: return "Code resource lock error";
  case 457: return "This key is already associated with an element of this collection";
  case 458: return "Variable uses a type not supported in Visual Basic";
  case 459: return "This component doesn't support the set of events";
  case 460: return "Invalid Clipboard format";
  case 461: return "Method or data member not found";
  case 462: return "The remote server machine does not exist or is unavailable";
  case 463: return "Class not registered on local machine";
  case 480: return "Can't create AutoRedraw image";
  case 481: return "Invalid picture";
  case 482: return "Printer error";
  case 483: return "Printer driver does not support specified property";
  case 484: return "Problem getting printer information from the system. Make sure the printer is set up correctly";
  case 485: return "Invalid picture type";
  case 486: return "Can't print form image to this type of printer";
  case 520: return "Can't empty Clipboard";
  case 521: return "Can't open Clipboard";
  case 735: return "Can't save file to TEMP directory";
  case 744: return "Search text not found";
  case 746: return "Replacements too long";
  case 31001: return "Out of memory";
  case 31004: return "No object";
  case 31018: return "Class is not set";
  case 31027: return "Unable to activate object";
  case 31032: return "Unable to create embedded object";
  case 31036: return "Error saving to file";
  case 31037: return "Error loading from file";
  default: return "";
  }
}


static const char *qbasic_error(int n)
{
  switch(n){
  case 1: return "NEXT without FOR";
  case 2: return "syntax error";
  case 3: return "RETURN without GOSUB";
  case 4: return "READ beyond DATA";
  case 5: return "invalid function call";
  case 6: return "overflow";
  case 7: return "out of memory";
  case 8: return "label not defined";
  case 9: return "index out of bounds";
  case 10: return "already defined";
  case 11: return "divide by zero";
  case 12: return "not allowed in direct mode";
  case 13: return "wrong datatype";
  case 14: return "out of string memory";
  case 37: return "wrong number of argruments";
  case 38: return "field not defined";
  case 40: return "variable necessary";
  case 50: return "FIELD-overflow";
  case 51: return "internal error";
  case 52: return "invalid file handle";
  case 53: return "file not found";
  case 54: return "wrong file access mode";
  case 55: return "file already opened";
  case 56: return "FIELD-statement active";
  case 57: return "device error while io";
  case 58: return "file already exists";
  case 59: return "invalid recordlen";
  case 61: return "harddisk full";
  case 62: return "input after eof";
  case 16: return "string calculation zu big";
  case 63: return "invalid recordnumber";
  case 64: return "invalid file name";
  case 17: return "KBasic cannot continue";
  case 67: return "too many files";
  case 18: return "KBasic-function not defined";
  case 68: return "device not available";
  case 19: return "missing RESUME";
  case 69: return "communication buffer overflow";
  case 20: return "RESUME without error";
  case 24: return "timeout of device";
  case 70: return "access denied";
  case 25: return "device error";
  case 71: return "harddisk not ready";
  case 26: return "FOR without NEXT";
  case 27: return "not enough paper";
  case 72: return "device error";
  case 29: return "WHILE without WEND";
  case 73: return "Function not available";
  case 30: return "WEND without WHILE";
  case 74: return "rename between device";
  case 33: return "double defined label";
  case 35: return "KBasic-sub not defined";
  case 75: return "path/file access error";
  case 76: return "path not found";
  default: return "";
  }
}
*/

};



#endif

