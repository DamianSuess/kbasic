/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software (Bernd Noetscher, Boseweg 9, 60529 Frankfurt / Germany).  All rights reserved.

pcode.h
---------------------------------------------------------------------------
19.02.2004 - new header for this file (BN)
***************************************************************************
*/



#ifndef PCODE_H
#define PCODE_H

#include "../kbshared/typedef.h"

#ifdef KBC
#include "../kbc/XString.h"
#elif defined(RUN)
#endif

#include "console.h"

#include "pcode_kbasic_binding.h"


#include "bytearray.h"

class _syntaxError;

const int pcode__user_defined_class		= 100000;
const int pcode__user_defined_module	= 200000;


const t_pcode pcode__NOP   		= 0;

// operators
const t_pcode pcode__ADD			  = 1;
const t_pcode pcode__SUB			  = 2;
const t_pcode pcode__DIV			  = 3;
const t_pcode pcode__MUL			  = 4;
const t_pcode pcode__MOD			  = 5;
const t_pcode pcode__AND			  = 6;
const t_pcode pcode__OR			  = 7;
const t_pcode pcode__XOR			  = 8;
const t_pcode pcode__POWER	= 9;
const t_pcode pcode__IDIV			= 10;
const t_pcode pcode__IMP			  = 11;
const t_pcode pcode__NOT			  = 12;
const t_pcode pcode__SHL			  = 13;
const t_pcode pcode__SHR			  = 14;
const t_pcode pcode__INC			  = 15;
const t_pcode pcode__DEC			  = 16;

// identifier declaration
const t_pcode pcode__DIM			  = 17;
const t_pcode pcode__DIM_STATIC = 18;

// additional
const t_pcode pcode__CJMP			= 19; // conditional jump
const t_pcode pcode__JMP			  = 20; // uncoditional jump
const t_pcode pcode__STOP		  = 21;
const t_pcode pcode__END			  = 22;

// misc.
const t_pcode pcode__VER			  = 23;
const t_pcode pcode__KBASIC		= 24;
const t_pcode pcode__BUILTIN		  = 25;

// stack operators
const t_pcode pcode__PUSH_BOOLEAN			= 26;
const t_pcode pcode__PUSH_BYTE			= 27;
const t_pcode pcode__PUSH_INTEGER			= 28;
const t_pcode pcode__PUSH_LONG			= 29;
const t_pcode pcode__PUSH_SINGLE			= 30;
const t_pcode pcode__PUSH_DOUBLE			= 31;
const t_pcode pcode__PUSH_QSTRING			= 32;
const t_pcode pcode__PUSH_CSTRING		= 33;
//const t_pcode pcode__PUSH_WSTRING		= 34;
const t_pcode pcode__PUSH_VARIANT			= 35;
const t_pcode pcode__PUSH_CURRENCY			= 36;

/*
const t_pcode pcode__OUTPUT			= 37;
const t_pcode pcode__INPUT			= 38;
const t_pcode pcode__APPEND			= 39;*/
const t_pcode pcode__BINARY			= 40;
const t_pcode pcode__RANDOM			= 41;

/*
const t_pcode pcode__PUSH_CHARACTER			= 37;
const t_pcode pcode__PUSH_INT16		= 38;
const t_pcode pcode__PUSH_INT32		= 39;
const t_pcode pcode__PUSH_INT64		= 40;
const t_pcode pcode__PUSH_UINT16		= 41;
const t_pcode pcode__PUSH_UINT32		= 42;
const t_pcode pcode__PUSH_UINT64		= 43;*/
const t_pcode pcode__PUSH_SHORT		= 261;
const t_pcode pcode__PUSH_COLLECTION		= 257;

const t_pcode pcode__PUSH_ID		= 44;
const t_pcode pcode__PUSH_CONST		= 45;
const t_pcode pcode__PUSH_ME		  = 46; 
const t_pcode pcode__PUSH_PARENT		  = 47; 
const t_pcode pcode__PUSH_ENUM		  = 258; 

  // needed for fields in user defined types or structures
const t_pcode pcode__PUSH_BOOLEAN_ID = 48;
const t_pcode pcode__PUSH_BYTE_ID = 49;
const t_pcode pcode__PUSH_INTEGER_ID = 50;
const t_pcode pcode__PUSH_LONG_ID = 51;
const t_pcode pcode__PUSH_SINGLE_ID = 52;
const t_pcode pcode__PUSH_DOUBLE_ID = 53;
const t_pcode pcode__PUSH_QSTRING_ID = 54;
const t_pcode pcode__PUSH_CSTRING_ID = 55;
//const t_pcode pcode__PUSH_WSTRING_ID = 56;
const t_pcode pcode__PUSH_VARIANT_ID = 57;
const t_pcode pcode__PUSH_CURRENCY_ID = 58;
const t_pcode pcode__PUSH_DATE_ID = 59;
/*
const t_pcode pcode__PUSH_CHARACTER_ID = 59;
const t_pcode pcode__PUSH_INT16_ID = 60;
const t_pcode pcode__PUSH_INT32_ID = 61;
const t_pcode pcode__PUSH_INT64_ID = 62;
const t_pcode pcode__PUSH_UINT16_ID = 63;
const t_pcode pcode__PUSH_UINT32_ID = 64;
const t_pcode pcode__PUSH_UINT64_ID = 65;*/
const t_pcode pcode__PUSH_SHORT_ID = 262;
const t_pcode pcode__PUSH_COLLECTION_ID = 259;

// needed for call by reference
const t_pcode pcode__PUSH_NULL = 66;
const t_pcode pcode__SEEK2 = 67;
const t_pcode pcode__DATE2 = 68;
const t_pcode pcode__SCREEN = 69;
const t_pcode pcode__NZ = 70;
const t_pcode pcode__GET = 71;
const t_pcode pcode__GET2 = 72;
const t_pcode pcode__PUT = 73;
const t_pcode pcode__PUT2 = 74;
const t_pcode pcode__INSTREV = 75;
const t_pcode pcode__REPLACE = 76;
const t_pcode pcode__SPLIT = 77;
const t_pcode pcode__ROUND = 78;
const t_pcode pcode__STRREVERSE = 79;
const t_pcode pcode__FIELD = 80;
const t_pcode pcode__SPC = 81;
const t_pcode pcode__TIMER_ON = 82;
const t_pcode pcode__TIMER_OFF = 83;
const t_pcode pcode__TIMER_STOP = 263;
const t_pcode pcode__DOEVENTS = 274;
//const t_pcode pcode__ = 275;
const t_pcode pcode__CHDRIVE = 276;
const t_pcode pcode__SETATTR = 277;
const t_pcode pcode__CLEAR = 278;
const t_pcode pcode__POINT = 279;
const t_pcode pcode__SCREEN2 = 280;
const t_pcode pcode__CIRCLE = 281;
const t_pcode pcode__DRAW = 282;
const t_pcode pcode__PCOPY = 283;
const t_pcode pcode__PMAP = 284;
const t_pcode pcode__WIDTH = 285;
const t_pcode pcode__PRESET = 286;
const t_pcode pcode__PSET = 287;
const t_pcode pcode__PAINT = 288;
const t_pcode pcode__WINDOW = 289;
const t_pcode pcode__LINE = 290;
const t_pcode pcode__VIEW = 291;
const t_pcode pcode__VIEWPRINT = 292;




const t_pcode pcode__PUSH_IDREF		= 84;

// needed for C/C++ binding
const t_pcode pcode__PUSH_BOOLEAN_IDPOINTER  		= 85;
const t_pcode pcode__PUSH_BYTE_IDPOINTER  		= 86;
const t_pcode pcode__PUSH_INTEGER_IDPOINTER  		= 87;
const t_pcode pcode__PUSH_LONG_IDPOINTER  		= 88;
const t_pcode pcode__PUSH_SINGLE_IDPOINTER  		= 89;
const t_pcode pcode__PUSH_DOUBLE_IDPOINTER  		= 90;
const t_pcode pcode__PUSH_CSTRING_IDPOINTER  		= 91;
const t_pcode pcode__PUSH_QSTRING_IDPOINTER  		= 92;
//const t_pcode pcode__PUSH_WSTRING_IDPOINTER  		= 93;
/*
const t_pcode pcode__PUSH_INT16_IDPOINTER  		= 92;
const t_pcode pcode__PUSH_INT32_IDPOINTER  		= 93;
const t_pcode pcode__PUSH_INT64_IDPOINTER  		= 94;
const t_pcode pcode__PUSH_UINT16_IDPOINTER  		= 95;
const t_pcode pcode__PUSH_UINT32_IDPOINTER  		= 96;
const t_pcode pcode__PUSH_UINT64_IDPOINTER  		= 264;*/
const t_pcode pcode__PUSH_SHORT_IDPOINTER  		= 265;
const t_pcode pcode__PUSH_IDPOINTER  		= 266;


// comparision
const t_pcode pcode__EQUAL			= 99;
const t_pcode pcode__UNEQUAL		= 100;
const t_pcode pcode__GREATER		= 101;
const t_pcode pcode__LESSER		= 102;
const t_pcode pcode__GREATER_EQUAL	 = 103;
const t_pcode pcode__LESSER_EQUAL	 = 104;

// data types for stack
// --> are defined in typedef.h

const t_pcode pcode__BOOLEAN_POINTER     = 105;
const t_pcode pcode__BYTE_POINTER     = 106;
const t_pcode pcode__INTEGER_POINTER     = 107;
const t_pcode pcode__LONG_POINTER    		= 108;
const t_pcode pcode__SINGLE_POINTER  		= 109;
const t_pcode pcode__DOUBLE_POINTER  		= 110;
const t_pcode pcode__CSTRING_POINTER  		= 111;
//const t_pcode pcode__WSTRING_POINTER  		= 112;
const t_pcode pcode__QSTRING_POINTER  		= 113;
/*
const t_pcode pcode__INT16_POINTER  		= 112;
const t_pcode pcode__INT32_POINTER  		= 113;
const t_pcode pcode__INT64_POINTER  		= 114;
const t_pcode pcode__UINT16_POINTER  		= 115;
const t_pcode pcode__UINT32_POINTER  		= 116;
const t_pcode pcode__UINT64_POINTER  		= 117;
*/
const t_pcode pcode__SHORT_POINTER  		= 267;


// additional
const t_pcode pcode__CALL				= 118;

const t_pcode pcode__OPTION_RANGE = 119;


// ***
const t_pcode pcode__MOV_BOOLEAN = 120;
const t_pcode pcode__MOV_BYTE = 121;
const t_pcode pcode__MOV_INTEGER = 122;
const t_pcode pcode__MOV_LONG = 123;
const t_pcode pcode__MOV_QSTRING = 124;
const t_pcode pcode__MOV_CSTRING = 125;
//const t_pcode pcode__MOV_WSTRING = 126;
const t_pcode pcode__MOV_SINGLE = 127;
const t_pcode pcode__MOV_DOUBLE = 128;
const t_pcode pcode__MOV_CURRENCY = 129;
const t_pcode pcode__MOV_DATE = 130;

const t_pcode pcode__OPTION_KBASIC = 131;

/*
const t_pcode pcode__MOV_CHARACTER = 130;
const t_pcode pcode__MOV_INT16 = 131;
const t_pcode pcode__MOV_INT32 = 132;
const t_pcode pcode__MOV_INT64 = 133;
const t_pcode pcode__MOV_UINT16 = 134;
const t_pcode pcode__MOV_UINT32 = 135;
const t_pcode pcode__MOV_UINT64 = 136;
*/
const t_pcode pcode__MOV_SHORT = 268;
const t_pcode pcode__MOV_COLLECTION = 269;

const t_pcode pcode__MOV		  = 137;
const t_pcode pcode__MOV_ID			  = 138;
const t_pcode pcode__MOV_TYPE		 = 139;
const t_pcode pcode__MOV_CONST		= 140;
const t_pcode pcode__MOV_ENUM		= 141;
//const t_pcode pcode__MOV_STRUCTURE		= 142;
const t_pcode pcode__MOV_LQSTRING		  = 143;
const t_pcode pcode__MOV_RQSTRING		  = 144;
const t_pcode pcode__MOV_LCSTRING		  = 145;
const t_pcode pcode__MOV_RCSTRING		  = 146;
//const t_pcode pcode__MOV_LWSTRING		  = 147;
//const t_pcode pcode__MOV_RWSTRING		  = 148;

// needed for call by reference

const t_pcode pcode__MOV_IDREF			  = 164;



const t_pcode pcode__SYSTEM = 175;

const t_pcode pcode__DATA = 176;
const t_pcode pcode__RESTORE = 177;
const t_pcode pcode__READ = 178;

const t_pcode pcode__LBOUND = 179;
const t_pcode pcode__UBOUND = 180;

// keywords
const t_pcode pcode__ERL  			 = 181;
const t_pcode pcode__ERR  			 = 182;
const t_pcode pcode__REDIM			  = 183;

const t_pcode pcode__ARRAY		  = 184;
const t_pcode pcode__REGISTER_ARRAY		  = 185; 

const t_pcode pcode__TYPE		  = 186; 
const t_pcode pcode__TYPE_ELEMENT		  = 187; 

const t_pcode pcode__ENUM		  = 188; 
const t_pcode pcode__ENUM_ELEMENT		  = 189; 

//const t_pcode pcode__STRUCTURE		  = 190; 
//const t_pcode pcode__STRUCTURE_ELEMENT		  = 191; 

const t_pcode pcode__RETURN		  = 192;
const t_pcode pcode__MID2  			 = 193;
//const t_pcode pcode__ERROR  			 = 194;
const t_pcode pcode__CLASSMETHOD		= 195;
const t_pcode pcode__CALL_RETURN		= 196;


const t_pcode pcode__SUB2		  = 197; 
const t_pcode pcode__SUB2_PARAM		  = 198; 

const t_pcode pcode__ONERRORGOTO		  = 199; 
const t_pcode pcode__ONERRORGOTORESUMENEXT		  = 200; 
const t_pcode pcode__RESUME		  = 201; 
const t_pcode pcode__STATEMENT		  = 202; 


const t_pcode pcode__VARTYPE = 203;

const t_pcode pcode__TYPEOF = 204;

const t_pcode pcode__ERASE = 205;

const t_pcode pcode__LIKE = 206;


const t_pcode pcode__CHOOSE = 207;
const t_pcode pcode__SWITCH = 208;
const t_pcode pcode__IIF = 209;

const t_pcode pcode__IS			= 210;
const t_pcode pcode__CLASSSTATICMETHOD		= 211;

const t_pcode pcode__STACKPOP		= 213;

const t_pcode pcode__CLASS		  = 214; 
const t_pcode pcode__CLASS_METHOD		  = 215; 
const t_pcode pcode__CLASS_METHODPARAM		  = 216; 

const t_pcode pcode__CALLMETHOD				= 217;

const t_pcode pcode__binding_CLASSSTATICMETHOD		= 218;
const t_pcode pcode__binding_CLASSMETHOD		  = 219; 

const t_pcode pcode__OPTION_BASE = 220;
const t_pcode pcode__OPTION_COMPARE = 221;

const t_pcode pcode___DYNAMIC = 222;
const t_pcode pcode___STATIC = 223;


const t_pcode pcode__CJMP2			= 273; // conditional jump with stack restore

const t_pcode pcode__PUSH_EMPTY = 293;
const t_pcode pcode__PUSH_ERROR = 294;
const t_pcode pcode__EQV = 295;
const t_pcode pcode__SILENTMODE = 296;
const t_pcode pcode__SEPARATOR = 297;

const t_pcode pcode__ENTER_LOCAL = 299;
const t_pcode pcode__EXIT_LOCAL = 300;

const t_pcode pcode__PUSH_IDREFVAL		= 301;
const t_pcode pcode__MOV_IDREFVAL			  = 302;
const t_pcode pcode__MOV_ISMISSING			  = 303;
const t_pcode pcode__PUSH_RETURNVAR			  = 304;
const t_pcode pcode__SET_ME			  = 305;
const t_pcode pcode__MOV_ME			  = 306;
const t_pcode pcode__MOV_PARENT			  = 307;
const t_pcode pcode__FOR_GREATER_EQUAL			  = 308;
const t_pcode pcode__CATCH			  = 309;
const t_pcode pcode__BREAKPOINT		  = 37; 

const t_pcode pcode__binding_CLASSOPERATOR		  = 311; 
const t_pcode pcode__binding_FUNCTIONOPERATOR		  = 312; 
const t_pcode pcode__binding_FUNCTION		  = 313; 

const t_pcode pcode__PROJECTFILE		  = 315; 
const t_pcode pcode__binding_SET_ME			  = 316;
const t_pcode pcode__PUSH__binding_ME		  = 317; 
const t_pcode pcode__binding_PUSH_ID		= 318;
const t_pcode pcode__PUSH__binding_PARENT		  = 319; 
const t_pcode pcode__CLASS_BINDINGPARAM		  = 320; 
const t_pcode pcode__CONNECT		  = 321; 
const t_pcode pcode__DISCONNECT		  = 322; 

const t_pcode pcode__CLASSPROPERTYGET		= 323;
const t_pcode pcode__CLASSPROPERTYSET		= 324;

const t_pcode pcode__ENTER_PROPERTYGET = 325;
const t_pcode pcode__ENTER_PROPERTYSET = 326;

const t_pcode pcode__binding_CLASSPROPERTY		  = 327; 

const t_pcode pcode__STATEMENT_OUT		  = 328; 
const t_pcode pcode__STATEMENT_OVER		  = 329; 
const t_pcode pcode__STATEMENT_CURSOR		  = 330; 

const t_pcode pcode__ONTIMERGOSUB		  = 331; 
const t_pcode pcode__LIBCALL		  = 332; 

const t_pcode pcode__binding_CLASSSTATICPROPERTY		  = 333; 
const t_pcode pcode__PUSH_POINTERPOINTER		  = 334; 

const t_pcode pcode__TRANSLATION = 335;

const t_pcode pcode__PRINTSCREEN = 336;
const t_pcode pcode__SQL = 337;
const t_pcode pcode__MENU = 338;

const t_pcode pcode__PUSH_LCSTRING_ID = 339;
//const t_pcode pcode__PUSH_LWSTRING_ID = 340;
const t_pcode pcode__PUSH_LQSTRING_ID = 341;

const t_pcode pcode__PUSH_DATE			= 342;

const t_pcode pcode__CJMP3			= 343;
const t_pcode pcode__TRY			= 344;
const t_pcode pcode__ENDCATCH			= 345;


// *** more pcode in typedef.h


// builtin
const t_builtin pcode__ABS  			 = 400; // has to be bigger than the last pcode id
const t_builtin pcode__ACCESS  			 = 401;
const t_builtin pcode__ACS  			 = 402;
const t_builtin pcode__APPEND  			 = 403;
const t_builtin pcode__ASC  			 = 404;
const t_builtin pcode__ASN  			 = 405;
const t_builtin pcode__ATN  			 = 406;
const t_builtin pcode__BEEP  			 = 407;
const t_builtin pcode__BIN  			 = 408;
const t_builtin pcode__CHDIR  		 = 409;
const t_builtin pcode__CHR  			 = 410;
const t_builtin pcode__CINT  			 = 411;
const t_builtin pcode__CLNG  			 = 412;
const t_builtin pcode__CLOSE  			 = 413;
const t_builtin pcode__CLS  			 = 414;
const t_builtin pcode__COLOR  			 = 415;
const t_builtin pcode__COS  			 = 416;
const t_builtin pcode__DEG  			 = 417;
const t_builtin pcode__DOF  			 = 418;
const t_builtin pcode__EOF_  			 = 419;
const t_builtin pcode__EXP  			 = 420;
const t_builtin pcode__FACT  			 = 421;
const t_builtin pcode__FILES  			 = 422;
const t_builtin pcode__FIX  			 = 423;
const t_builtin pcode__FRAC  			 = 424;
const t_builtin pcode__HEX  			 = 425;
const t_builtin pcode__HYPOT  			 = 426;
const t_builtin pcode__INPUT  			 = 427;
const t_builtin pcode__INKEY 			 = 428;
const t_builtin pcode__INSTR  			 = 429;
const t_builtin pcode__INT  			 	= 430;
const t_builtin pcode__KILL  			 = 431;
const t_builtin pcode__LCASE 			 = 432;
const t_builtin pcode__LEFT  			 = 433;
const t_builtin pcode__LEN  			 = 434;
const t_builtin pcode__LINEINPUT  = 435;
const t_builtin pcode__LN  			 = 436;
const t_builtin pcode__LOCATE  			 = 437;
const t_builtin pcode__LOF  			 = 438;
const t_builtin pcode__LOG  			 = 439;
const t_builtin pcode__LOGB  			 = 440;
const t_builtin pcode__LTRIM  			 = 441;
const t_builtin pcode__MAX  			 = 442;
const t_builtin pcode__MID  			 = 443;
const t_builtin pcode__MIN  			 = 444;
const t_builtin pcode__MKDIR  			 = 445;
const t_builtin pcode__NAME  			 = 446;
const t_builtin pcode__OCT  			 = 447;
const t_builtin pcode__OPEN  			 = 448;
const t_builtin pcode__OUTPUT  			 = 449;
const t_builtin pcode__PRINT  			 = 450;
const t_builtin pcode__RAD  			 = 451;
const t_builtin pcode__RANDOMIZE	 = 452;
const t_builtin pcode__READ2  			 = 453;
const t_builtin pcode__RESET  			 = 454;
const t_builtin pcode__RIGHT  			 = 455;
const t_builtin pcode__RMDIR  			 = 456;
const t_builtin pcode__RND  			 = 457;
const t_builtin pcode__RTRIM  			 = 458;
const t_builtin pcode__SEC  			 = 459;
const t_builtin pcode__SEEK  			 = 460;
const t_builtin pcode__SIN  			 = 461;
const t_builtin pcode__SGN  			 = 462;
const t_builtin pcode__SHELL  			 = 463;
const t_builtin pcode__SPACE  			 = 464;
const t_builtin pcode__SQR  			 = 465;
const t_builtin pcode__STR  			 = 466;
const t_builtin pcode__STRING2  			 = 467;
const t_builtin pcode__TAN  			 = 468;
const t_builtin pcode__TRIM  			 = 469;
const t_builtin pcode__UCASE  			 = 470;
const t_builtin pcode__VAL  			 = 471;
const t_builtin pcode__WRITE  			 = 472;
const t_builtin pcode__POS      = 473;
const t_builtin pcode__CSRLIN      = 474;

const t_builtin pcode__OPEN2  			 = 475;

const t_builtin pcode__TIME      = 476;
const t_builtin pcode__SLEEP      = 477;
const t_builtin pcode__ISDATE = 478;
const t_builtin pcode__ISEMPTY = 479;
const t_builtin pcode__ISNULL = 480;
const t_builtin pcode__ISNUMERIC = 481;
const t_builtin pcode__STRCOMP = 482;
const t_builtin pcode__CSNG = 483;
const t_builtin pcode__CDBL = 484;
const t_builtin pcode__CCUR = 485;
const t_builtin pcode__CVAR = 486;
const t_builtin pcode__CBOOL = 487;
const t_builtin pcode__CBYTE = 488;
const t_builtin pcode__CDATE = 489;
const t_builtin pcode__ISMISSING = 490;
const t_builtin pcode__ISARRAY = 491;
const t_builtin pcode__ISOBJECT = 492;
const t_builtin pcode__ARRAY2 = 493;
const t_builtin pcode__COMMAND = 494;
const t_builtin pcode__CURDIR = 495;
const t_builtin pcode__CVERR = 496;

const t_builtin pcode__DATEADD = 497;
const t_builtin pcode__DATEDIFF = 498;
const t_builtin pcode__DATEPART = 499;
const t_builtin pcode__DATESERIAL = 500;
const t_builtin pcode__DATEVALUE = 501;

const t_builtin pcode__DAY = 502;
const t_builtin pcode__DIR = 503;
const t_builtin pcode__FILEATTR = 504;
const t_builtin pcode__FILEDATETIME = 505;
const t_builtin pcode__FREEFILE = 506;
const t_builtin pcode__HOUR = 507;
const t_builtin pcode__INPUTBOX = 508;

const t_builtin pcode__LOC= 509;
const t_builtin pcode__MINUTE = 510;
const t_builtin pcode__MONTH = 511;
const t_builtin pcode__MSGBOX = 512;

const t_builtin pcode__NOW = 513;
const t_builtin pcode__RGB = 514;
const t_builtin pcode__SECOND = 515;
const t_builtin pcode__TIMER = 516;

const t_builtin pcode__TIMESERIAL = 517;
const t_builtin pcode__TIMEVALUE = 518;
const t_builtin pcode__TYPENAME = 519;
const t_builtin pcode__WEEKDAY = 520;
const t_builtin pcode__YEAR = 521;
const t_builtin pcode__FORMAT = 522;
const t_builtin pcode__ISERROR = 523;
const t_builtin pcode__FILELEN = 524;
const t_builtin pcode__GETATTR = 525;

const t_builtin pcode__FREE = 526;
const t_builtin pcode__FRE = 527;
const t_builtin pcode__CLOSEALL = 528;

const t_builtin pcode__INPUT2 = 529;

const t_builtin pcode__ISBOOLEAN = 530;
const t_builtin pcode__ISBYTE = 531;
const t_builtin pcode__ISDOUBLE = 532;
const t_builtin pcode__ISINTEGER = 533;
const t_builtin pcode__ISINT16 = 534;
const t_builtin pcode__ISINT32 = 535;
const t_builtin pcode__ISINT64 = 536;
const t_builtin pcode__ISUINT16 = 537;
const t_builtin pcode__ISUINT32 = 538;
const t_builtin pcode__ISUINT64 = 539;
const t_builtin pcode__ISSHORT = 540;
const t_builtin pcode__ISLONG = 541;
const t_builtin pcode__ISSTRING = 542;
const t_builtin pcode__ISVARIANT = 543;
const t_builtin pcode__ISSINGLE = 544;
const t_builtin pcode__FILECOPY = 545;
const t_builtin pcode__ISCURRENCY = 546;

const t_builtin pcode__FORMATCURRENCY = 547;
const t_builtin pcode__FORMATDATETIME = 548;
const t_builtin pcode__FORMATNUMBER = 549;
const t_builtin pcode__FORMATPERCENT = 550;
const t_builtin pcode__WEEKDAYNAME = 551;
const t_builtin pcode__MONTHNAME = 552;

const t_builtin pcode__KBASICDIR = 553;

const t_builtin pcode__UTF8 = 554;
const t_builtin pcode__UTF16 = 555;

const t_builtin pcode__CAST = 556;
const t_builtin pcode__POKE = 557;
const t_builtin pcode__PEEK = 558;

const t_builtin pcode__COMPARE = 559;
const t_builtin pcode__CONTAINS = 560;
const t_builtin pcode__COUNT = 561;
const t_builtin pcode__ENDSWITH = 562;
const t_builtin pcode__STARTSWITH = 563;
const t_builtin pcode__LEFTJUSTIFIED = 564;
const t_builtin pcode__RIGHTJUSTIFIED = 565;
const t_builtin pcode__SECTION = 566;
const t_builtin pcode__SIMPLIFIED = 567;
const t_builtin pcode__TRIMMED = 568;
const t_builtin pcode__REVERSED = 569;
const t_builtin pcode__UNICODE = 570;


const t_builtin pcode__PREPEND = 571;
const t_builtin pcode__APPEND2 = 572;
const t_builtin pcode__REMOVE = 573;
const t_builtin pcode__TRUNCATE = 574;
const t_builtin pcode__INSERT = 575;
const t_builtin pcode__FILL = 576;

const t_builtin pcode__READBINARY = 577;
const t_builtin pcode__WRITEBINARY = 578;
const t_builtin pcode__SEEKBINARY = 579;

const t_builtin pcode__DAYOFWEEK = 580;
const t_builtin pcode__DAYOFYEAR = 581;
const t_builtin pcode__DAYSINMONTH = 582;
const t_builtin pcode__DAYSINYEAR = 583;
const t_builtin pcode__WEEKNUMBER = 584;
const t_builtin pcode__ISLEAPYEAR = 585;
const t_builtin pcode__DIFFDAY = 586;
const t_builtin pcode__DIFFSECONDS = 587;
const t_builtin pcode__ISDATEVALID = 588;
const t_builtin pcode__ISTIMEVALID = 589;
const t_builtin pcode__ISDATETIMEVALID = 590;
const t_builtin pcode__DAYNAME = 591;

const t_builtin pcode__ADDDATE = 592;
const t_builtin pcode__ADDDAYS = 593;
const t_builtin pcode__ADDMONTHS = 594;
const t_builtin pcode__ADDYEARS = 595;
const t_builtin pcode__SUBDATE = 596;
const t_builtin pcode__SUBDAYS = 597;
const t_builtin pcode__SUBMONTHS = 598;
const t_builtin pcode__SUBYEARS = 599;
const t_builtin pcode__ADDTIME = 600;
const t_builtin pcode__ADDHOURS = 601;
const t_builtin pcode__ADDMINUTES = 602;
const t_builtin pcode__ADDSECONDS = 603;
const t_builtin pcode__SUBTIME = 605;
const t_builtin pcode__SUBHOURS = 606;
const t_builtin pcode__SUBMINUTES = 607;
const t_builtin pcode__SUBSECONDS = 608;

const t_builtin pcode__ENCODE = 609;
const t_builtin pcode__DECODE = 610;


class _mainwindow;

class pcode {
public:
	pcode(const char *acCurrentFile/* = ""*/);
	~pcode();

static const char *pcode_(int n)
{
	switch(n)
	{

    
  case pcode__NOP: return "NOP";
    
  case pcode__CLEAR: return "CLEAR";
  case pcode__DOEVENTS: return "DOEVENTS";
  case pcode__TIMER_ON: return "TIMER_ON";
  case pcode__TIMER_OFF: return "TIMER_OFF";
  case pcode__TIMER_STOP: return "TIMER_STOP";

	// operators
  case pcode__ADD: return "ADD";
  case pcode__SUB: return "SUB";
  case pcode__DIV: return "DIV";
  case pcode__MUL: return "MUL";
  case pcode__MOD: return "MOD";
  case pcode__AND: return "AND";
  case pcode__OR: return "OR";
  case pcode__XOR: return "XOR";
  case pcode__POWER: return "POWER";
  case pcode__IDIV: return "IDIV";
  case pcode__IMP: return "IMP";
  case pcode__NOT: return "NOT";
  case pcode__SHL: return "SHL";
  case pcode__SHR: return "SHR";
  case pcode__INC: return "INC";
  case pcode__DEC: return "DEC";
    
  case pcode__PROJECTFILE: return "PROJECTFILE";

  case pcode__FRE: return "FRE";

  case pcode___DYNAMIC: return "$DYNAMIC";
  case pcode___STATIC: return "$STATIC";

	// identifier declaration
  case pcode__DIM: return "DIM";
  case pcode__DIM_STATIC: return "DIM_STATIC";
  case pcode__ARRAY: return "ARRAY";

  case pcode__ENTER_LOCAL: return "ENTER_LOCAL";
  case pcode__ENTER_PROPERTYGET: return "ENTER_PROPERTYGET";
  case pcode__ENTER_PROPERTYSET: return "ENTER_PROPERTYSET";
    
  case pcode__EXIT_LOCAL: return "EXIT_LOCAL";    
/*
  case pcode__OUTPUT: return "OUTPUT";
  case pcode__INPUT: return "INPUT";
  case pcode__APPEND: return "APPEND";*/
  case pcode__BINARY: return "BINARY";
  case pcode__RANDOM: return "RANDOM";

  case pcode__TRY: return "TRY";
  case pcode__ENDCATCH: return "ENDCATCH";

	// additional
  case pcode__CJMP: return "CJMP";
  case pcode__CJMP2: return "CJMP2";
  case pcode__CJMP3: return "CJMP3";
  case pcode__JMP: return "JMP";
  case pcode__STOP: return "STOP";
  case pcode__END: return "END";
  case pcode__CALL: return "CALL";
  case pcode__CALLMETHOD: return "CALLMETHOD";
  case pcode__CATCH: return "CATCH";

  case pcode__BREAKPOINT: return "BREAKPOINT";    

  case pcode__RETURN: return "RETURN";

  case pcode__SUB2: return "SUB2";
  case pcode__SUB2_PARAM: return "SUB2_PARAM";

  case pcode__CLASS: return "CLASS";
  case pcode__CLASS_METHOD: return "CLASS_METHOD";
  case pcode__CLASS_METHODPARAM: return "CLASS_METHODPARAM";
  case pcode__CLASS_BINDINGPARAM: return "CLASS_BINDINGPARAM";    

  case pcode__TRANSLATION: return "TRANSLATION";    
  case pcode__SQL: return "SQL";    

  case pcode__CONNECT: return "CONNECT";    
  case pcode__DISCONNECT: return "DISCONNECT";    

  case pcode__STACKPOP: return "STACKPOP";

  // misc.
  case pcode__VER: return "VER";
  case pcode__KBASIC: return "KBASIC";
  case pcode__BUILTIN: return "BUILTIN";

	// stack operators
  case pcode__PUSH_BOOLEAN: return "PUSH_BOOLEAN";
  case pcode__PUSH_BYTE: return "PUSH_BYTE";
  case pcode__PUSH_INTEGER: return "PUSH_INTEGER";
  case pcode__PUSH_LONG: return "PUSH_LONG";
  case pcode__PUSH_SINGLE: return "PUSH_SINGLE";
  case pcode__PUSH_DOUBLE: return "PUSH_DOUBLE";

  case pcode__PUSH_QSTRING: return "PUSH_QSTRING";
  case pcode__PUSH_CSTRING: return "PUSH_CSTRING";
 // case pcode__PUSH_WSTRING: return "PUSH_WSTRING";

  case pcode__PUSH_POINTERPOINTER: return "PUSH_POINTERPOINTER";    
  case pcode__PUSH_VARIANT: return "PUSH_VARIANT";
  case pcode__PUSH_CURRENCY: return "PUSH_CURRENCY";
  case pcode__PUSH_DATE: return "PUSH_DATE";
    /*
  case pcode__PUSH_CHARACTER: return "PUSH_CHARACTER";
  case pcode__PUSH_INT16: return "PUSH_INT16";
  case pcode__PUSH_INT32: return "PUSH_INT32";
  case pcode__PUSH_INT64: return "PUSH_INT64";
  case pcode__PUSH_UINT16: return "PUSH_UINT16";
  case pcode__PUSH_UINT32: return "PUSH_UINT32";
  case pcode__PUSH_UINT64: return "PUSH_UINT64";*/
  case pcode__PUSH_SHORT: return "PUSH_SHORT";
  case pcode__PUSH_COLLECTION: return "PUSH_COLLECTION";

  case pcode__binding_PUSH_ID: return "binding_PUSH_ID";
  case pcode__PUSH_ID: return "PUSH_ID";
  case pcode__PUSH_CONST: return "PUSH_CONST";
  case pcode__PUSH_ENUM: return "PUSH_ENUM";
  case pcode__PUSH_ME: return "PUSH_ME";
  case pcode__PUSH__binding_ME: return "PUSH__binding_ME";
  case pcode__PUSH__binding_PARENT: return "PUSH__binding_PARENT";
    
  case pcode__PUSH_PARENT: return "PUSH_PARENT";

  // needed for fields in user defined types or structures
  case pcode__PUSH_BOOLEAN_ID: return "PUSH_BOOLEAN_ID";
  case pcode__PUSH_BYTE_ID: return "PUSH_BYTE_ID";
  case pcode__PUSH_INTEGER_ID: return "PUSH_INTEGER_ID";
  case pcode__PUSH_LONG_ID: return "PUSH_LONG_ID";
  case pcode__PUSH_SINGLE_ID: return "PUSH_SINGLE_ID";
  case pcode__PUSH_DOUBLE_ID: return "PUSH_DOUBLE_ID";

  case pcode__PUSH_QSTRING_ID: return "PUSH_QSTRING_ID";
  case pcode__PUSH_CSTRING_ID: return "PUSH_CSTRING_ID";
//  case pcode__PUSH_WSTRING_ID: return "PUSH_WSTRING_ID";
  case pcode__PUSH_LQSTRING_ID: return "PUSH_LQSTRING_ID";
  case pcode__PUSH_LCSTRING_ID: return "PUSH_LCSTRING_ID";
 // case pcode__PUSH_LWSTRING_ID: return "PUSH_LWSTRING_ID";

  case pcode__PUSH_VARIANT_ID: return "PUSH_VARIANT_ID";
  case pcode__PUSH_CURRENCY_ID: return "PUSH_CURRENCY_ID";
  case pcode__PUSH_DATE_ID: return "PUSH_DATE_ID";
    /*
  case pcode__PUSH_CHARACTER_ID: return "PUSH_CHARACTER_ID";
  case pcode__PUSH_INT16_ID: return "PUSH_INT16_ID";
  case pcode__PUSH_INT32_ID: return "PUSH_INT32_ID";
  case pcode__PUSH_INT64_ID: return "PUSH_INT64_ID";
  case pcode__PUSH_UINT16_ID: return "PUSH_UINT16_ID";
  case pcode__PUSH_UINT32_ID: return "PUSH_UINT32_ID";
  case pcode__PUSH_UINT64_ID: return "PUSH_UINT64_ID";*/
  case pcode__PUSH_SHORT_ID: return "PUSH_SHORT_ID";
  case pcode__PUSH_COLLECTION_ID: return "PUSH_COLLECTION_ID";
    

  // needed for call by reference

  case pcode__PUSH_IDREF: return "PUSH_IDREF";
  case pcode__PUSH_IDREFVAL: return "PUSH_IDREFVAL";

  // needed for C/C++ binding
  case pcode__PUSH_BOOLEAN_IDPOINTER: return "PUSH_BOOLEAN_IDPOINTER";
  case pcode__PUSH_BYTE_IDPOINTER: return "PUSH_BYTE_IDPOINTER";
  case pcode__PUSH_INTEGER_IDPOINTER: return "PUSH_INTEGER_IDPOINTER";
  case pcode__PUSH_LONG_IDPOINTER: return "PUSH_LONG_IDPOINTER";
  case pcode__PUSH_SINGLE_IDPOINTER: return "PUSH_SINGLE_IDPOINTER";
  case pcode__PUSH_DOUBLE_IDPOINTER: return "PUSH_DOUBLE_IDPOINTER";

  case pcode__PUSH_QSTRING_IDPOINTER: return "PUSH_QSTRING_IDPOINTER";
  case pcode__PUSH_CSTRING_IDPOINTER: return "PUSH_CSTRING_IDPOINTER";
 // case pcode__PUSH_WSTRING_IDPOINTER: return "PUSH_WSTRING_IDPOINTER";
    /*
  case pcode__PUSH_INT16_IDPOINTER: return "PUSH_INT16_IDPOINTER";
  case pcode__PUSH_INT32_IDPOINTER: return "PUSH_INT32_IDPOINTER";
  case pcode__PUSH_INT64_IDPOINTER: return "PUSH_INT64_IDPOINTER";
  case pcode__PUSH_UINT16_IDPOINTER: return "PUSH_UINT16_IDPOINTER";
  case pcode__PUSH_UINT32_IDPOINTER: return "PUSH_UINT32_IDPOINTER";
  case pcode__PUSH_UINT64_IDPOINTER: return "PUSH_UINT64_IDPOINTER";
  */
  case pcode__PUSH_SHORT_IDPOINTER: return "PUSH_SHORT_IDPOINTER";

  case pcode__PUSH_IDPOINTER: return "PUSH_IDPOINTER";


  case pcode__BOOLEAN_POINTER:  return "BOOLEAN_POINTER";
  case pcode__BYTE_POINTER:  return "BYTE_POINTER";
  case pcode__INTEGER_POINTER:  return "INTEGER_POINTER";
  case pcode__LONG_POINTER:  return "LONG_POINTER";
  case pcode__SINGLE_POINTER:  return "SINGLE_POINTER";
  case pcode__DOUBLE_POINTER:  return "DOUBLE_POINTER";

  case pcode__QSTRING_POINTER:  return "QSTRING_POINTER";
  case pcode__CSTRING_POINTER:  return "CSTRING_POINTER";
 // case pcode__WSTRING_POINTER:  return "WSTRING_POINTER";
    /*
  case pcode__INT16_POINTER:  return "INT16_POINTER";
  case pcode__INT32_POINTER:  return "INT32_POINTER";
  case pcode__INT64_POINTER:  return "INT64_POINTER";
  case pcode__UINT16_POINTER:  return "UINT16_POINTER";
  case pcode__UINT32_POINTER:  return "UINT32_POINTER";
  case pcode__UINT64_POINTER:  return "UINT64_POINTER";
  */
  case pcode__SHORT_POINTER:  return "SHORT_POINTER";

  case pcode__SET_ME: return "SET_ME";
  case pcode__binding_SET_ME: return "binding_SET_ME";    

  case pcode__MOV_ME: return "MOV_ME";
  case pcode__MOV_PARENT: return "MOV_PARENT";


		// comparision
  case pcode__EQUAL: return "EQUAL";
  case pcode__UNEQUAL: return "UNEQUAL";
  case pcode__GREATER: return "GREATER";
  case pcode__LESSER: return "LESSER";
  case pcode__GREATER_EQUAL: return "GREATER_EQUAL";
  case pcode__LESSER_EQUAL: return "LESSER_EQUAL";

  case pcode__FOR_GREATER_EQUAL: return "FOR_GREATER_EQUAL";    


	// buildin data types for stack
  case pcode__ANY: return "ANY";
  case pcode__DOUBLE: return "DOUBLE";
  case pcode__INTEGER: return "INTEGER";
  case pcode__QSTRING:  return "QSTRING";
  case pcode__CSTRING:  return "CSTRING";
 // case pcode__WSTRING:  return "WSTRING";

  case pcode__LQSTRING:  return "LQSTRING";
  case pcode__LCSTRING:  return "LCSTRING";
  //case pcode__LWSTRING:  return "LWSTRING";
//  case pcode__RSTRING:  return "RSTRING";
//  case pcode__LCSTRING:  return "LCSTRING";
//  case pcode__RCSTRING:  return "RCSTRING";

  case pcode__BOOLEAN: return "BOOLEAN";
  case pcode__LONG: 	 return "LONG";
  case pcode__SINGLE:  return "SINGLE";
  case pcode__ID:  return "ID";
  case pcode__CONST:  return "CONST";
  case pcode__REFERENCE:  return "REFERENCE";
  case pcode__BYTE:  return "BYTE";
  case pcode__VARIANT:  return "VARIANT";
  case pcode__CURRENCY:  return "CURRENCY";
  case pcode__DATE:  return "DATE";
  case pcode__DATE2:  return "DATE2";
	case pcode__OBJECT:  return "OBJECT";
	case pcode__QTEXCEPTION:  return "QTEXCEPTION";
	case pcode__CASTEXCEPTION:  return "CASTEXCEPTION";
	case pcode__EXCEPTION:  return "EXCEPTION";
    
	case pcode__PARAMARRAY:  return "PARAMARRAY";    
	//case pcode__CSTRING:  return "CSTRING";
	case pcode__CHARACTER:  return "CHARACTER";
    /*
	case pcode__INT16:  return "INT16";
	case pcode__INT32:  return "INT32";
	case pcode__INT64:  return "INT64";
	case pcode__UINT16:  return "UINT16";
	case pcode__UINT32:  return "UINT32";
	case pcode__UINT64:  return "UINT64";
  */
	case pcode__SHORT:  return "SHORT";
	case pcode__COLLECTION:  return "COLLECTION";
	case pcode__BUFFER:  return "BUFFER";
	case pcode__POINTER:  return "POINTER";


  // ***
  case pcode__MOV_BOOLEAN:  return "MOV_BOOLEAN";
  case pcode__MOV_BYTE:  return "MOV_BYTE";
  case pcode__MOV_INTEGER:  return "MOV_INTEGER";
  case pcode__MOV_LONG:  return "MOV_LONG";
  
  case pcode__MOV_QSTRING:  return "MOV_QSTRING";
  case pcode__MOV_CSTRING:  return "MOV_CSTRING";
 // case pcode__MOV_WSTRING:  return "MOV_WSTRING";

  case pcode__MOV_SINGLE:  return "MOV_SINGLE";
  
  case pcode__MOV_DOUBLE:  return "MOV_DOUBLE";
  case pcode__MOV_CURRENCY:  return "MOV_CURRENCY";
  case pcode__MOV_DATE:  return "MOV_DATE";
    /*
  case pcode__MOV_CHARACTER:  return "MOV_CHARACTER";
  case pcode__MOV_INT16:  return "MOV_INT16";
  case pcode__MOV_INT32:  return "MOV_INT32";
  case pcode__MOV_INT64:  return "MOV_INT64";
  case pcode__MOV_UINT16:  return "MOV_UINT16";
  case pcode__MOV_UINT32:  return "MOV_UINT32";
  case pcode__MOV_UINT64:  return "MOV_UINT64";*/
  case pcode__MOV_SHORT:  return "MOV_SHORT";
  case pcode__MOV_COLLECTION:  return "MOV_COLLECTION";


  case pcode__MOV: return "MOV";
  case pcode__MOV_ID:  return "MOV_ID";
  case pcode__MOV_TYPE:  return "MOV_TYPE";
  case pcode__MOV_CONST:  return "MOV_CONST";
  case pcode__MOV_ENUM:  return "MOV_ENUM";
//  case pcode__MOV_STRUCTURE:  return "MOV_STRUCTURE";

  case pcode__MOV_LQSTRING:  return "MOV_LQSTRING";
  case pcode__MOV_RQSTRING:  return "MOV_RQSTRING";
  case pcode__MOV_LCSTRING:  return "MOV_LCSTRING";
  case pcode__MOV_RCSTRING:  return "MOV_RCSTRING";
  //case pcode__MOV_LWSTRING:  return "MOV_LWSTRING";
  //case pcode__MOV_RWSTRING:  return "MOV_RWSTRING";

  case pcode__MOV_ISMISSING:  return "MOV_ISMISSING";

    

  // ***
  case pcode__MOV_IDREF:  return "MOV_IDREF";
  case pcode__MOV_IDREFVAL:  return "MOV_IDREFVAL";

  case pcode__FORMATCURRENCY:  return "FORMATCURRENCY";
  case pcode__FORMATDATETIME:  return "FORMATDATETIME";
  case pcode__FORMATNUMBER:  return "FORMATNUMBER";
  case pcode__FORMATPERCENT:  return "FORMATPERCENT";
  case pcode__WEEKDAYNAME:  return "WEEKDAYNAME";
  case pcode__MONTHNAME:  return "MONTHNAME";

  case pcode__KBASICDIR:  return "KBASICDIR";

  case pcode__UTF8:  return "UTF8";
  case pcode__UTF16:  return "UTF16";

  case pcode__CAST:  return "CAST";
  case pcode__POKE:  return "POKE";
  case pcode__PEEK:  return "PEEK";


  case pcode__COMPARE:  return "COMPARE";
  case pcode__CONTAINS:  return "CONTAINS";
  case pcode__COUNT:  return "COUNT";
  case pcode__ENDSWITH:  return "ENDSWITH";
  case pcode__STARTSWITH:  return "STARTSWITH";
  case pcode__LEFTJUSTIFIED:  return "LEFTJUSTIFIED";
  case pcode__RIGHTJUSTIFIED:  return "RIGHTJUSTIFIED";
  case pcode__SECTION:  return "SECTION";
  case pcode__SIMPLIFIED:  return "SIMPLIFIED";
  case pcode__TRIMMED:  return "TRIMMED";
  case pcode__REVERSED:  return "REVERSED";
  case pcode__UNICODE:  return "UNICODE";

  case pcode__PREPEND:  return "PREPEND";
  case pcode__APPEND2:  return "APPEND2";
  case pcode__REMOVE:  return "REMOVE";
  case pcode__TRUNCATE:  return "TRUNCATE";
  case pcode__INSERT:  return "INSERT";
  case pcode__FILL:  return "FILL";
  
  case pcode__READBINARY:  return "READBINARY";
  case pcode__WRITEBINARY:  return "WRITEBINARY";
  case pcode__SEEKBINARY:  return "SEEKBINARY";

  case pcode__DAYOFWEEK:  return "DAYOFWEEK";
  case pcode__DAYOFYEAR:  return "DAYOFYEAR";
  case pcode__DAYSINMONTH:  return "DAYSINMONTH";
  case pcode__DAYSINYEAR:  return "DAYSINYEAR";
  case pcode__WEEKNUMBER:  return "WEEKNUMBER";
  case pcode__ISLEAPYEAR:  return "ISLEAPYEAR";
  case pcode__DIFFDAY:  return "DIFFDAY";
  case pcode__DIFFSECONDS:  return "DIFFSECONDS";
  case pcode__ISDATEVALID:  return "ISDATEVALID";
  case pcode__ISTIMEVALID:  return "ISTIMEVALID";
  case pcode__ISDATETIMEVALID:  return "ISDATETIMEVALID";
  case pcode__DAYNAME:  return "DAYNAME";

  case pcode__ADDDATE:  return "ADDDATE";
  case pcode__ADDDAYS:  return "ADDDAYS";
  case pcode__ADDMONTHS:  return "ADDMONTHS";
  case pcode__ADDYEARS:  return "ADDYEARS";
  case pcode__SUBDATE:  return "SUBDATE";
  case pcode__SUBDAYS:  return "SUBDAYS";
  case pcode__SUBMONTHS:  return "SUBMONTHS";
  case pcode__SUBYEARS:  return "SUBYEARS";
  case pcode__ADDTIME:  return "ADDTIME";
  case pcode__ADDHOURS:  return "ADDHOURS";
  case pcode__ADDMINUTES:  return "ADDMINUTES";
  case pcode__ADDSECONDS:  return "ADDSECONDS";
  case pcode__SUBHOURS:  return "SUBHOURS";
  case pcode__SUBMINUTES:  return "SUBMINUTES";
  case pcode__SUBSECONDS:  return "SUBSECONDS";

  case pcode__ENCODE:  return "ENCODE";
  case pcode__DECODE:  return "DECODE";

  // options
  case pcode__OPTION_KBASIC:  return "OPTION KBASIC";
  case pcode__OPTION_RANGE:  return "OPTION RANGE";
  case pcode__OPTION_BASE:  return "OPTION BASE";
  case pcode__OPTION_COMPARE:  return "OPTION COMPARE";  
    
  case pcode__SILENTMODE:  return "SILENTMODE";
  case pcode__SEPARATOR:  return "SEPARATOR";
    
  // ***

  case pcode__SYSTEM:  return "SYSTEM";
  case pcode__MID2: return "MID2";

  case pcode__DATA:  return "DATA";
  case pcode__RESTORE:  return "RESTORE";
  case pcode__READ:  return "READ";

  case pcode__LBOUND:  return "LBOUND";
  case pcode__UBOUND:  return "UBOUND";

  case pcode__ERL: return "ERL";
  case pcode__ERR: return "ERR";
  case pcode__REDIM: return "REDIM";

  case pcode__REGISTER_ARRAY: return "REG.ARRAY";

  case pcode__TYPE: return "TYPE";
  case pcode__TYPE_ELEMENT: return "TYPE_ELEMENT";

//  case pcode__STRUCTURE: return "STRUCTURE";
  //case pcode__STRUCTURE_ELEMENT: return "STRUCTURE_ELEMENT";

  case pcode__ENUM: return "ENUM";
  case pcode__ENUM_ELEMENT: return "ENUM_ELEMENT";

  //case pcode__REALCSTRING: return "REALCSTRING";
  case pcode__ERROR: return "ERROR";

  case pcode__CLASSMETHOD: return "CLASSMETHOD";
  case pcode__CLASSPROPERTYGET: return "CLASSPROPERTYGET";
  case pcode__CLASSPROPERTYSET: return "CLASSPROPERTYSET";
  case pcode__VOID: return "VOID";
  case pcode__CALL_RETURN: return "CALL_RETURN";
  //case pcode__CATCH_RETURN: return "CATCH_RETURN";


  case pcode__ONERRORGOTO: return "ONERRORGOTO";
  case pcode__ONERRORGOTORESUMENEXT: return "ONERRORGOTORESUMENEXT";
  case pcode__RESUME: return "RESUME";

  case pcode__STATEMENT: return "STATEMENT";
  case pcode__STATEMENT_OUT: return "STATEMENT_OUT";
  case pcode__STATEMENT_OVER: return "STATEMENT_OVER";
  case pcode__STATEMENT_CURSOR: return "STATEMENT_CURSOR";
  
  case pcode__ONTIMERGOSUB: return "ONTIMERGOSUB";
  
  case pcode__LIBCALL: return "LIBCALL";
    
	//case pcode__EMPTY:  return "EMPTY";

	case pcode__VARTYPE:  return "VARTYPE";

	case pcode__TYPEOF:  return "TYPEOF";

	case pcode__ERASE:  return "ERASE";

	case pcode__LIKE:  return "LIKE";

	case pcode__CHOOSE:  return "CHOOSE";
	case pcode__SWITCH:  return "SWITCH";
	case pcode__IIF:  return "IIF";

	case pcode__NULL:  return "NULL";

	case pcode__PUSH_EMPTY:  return "PUSH_EMPTY";
	case pcode__PUSH_ERROR:  return "PUSH_ERROR";
	case pcode__PUSH_NULL:  return "PUSH_NULL";
  case pcode__PUSH_RETURNVAR: return "PUSH_RETURNVAR";

	case pcode__IS:  return "IS";
	case pcode__CLASSSTATICMETHOD:  return "CLASSSTATICMETHOD";

	case pcode__EQV:  return "EQV";    

	default: return pcode_kbasic_binding::methodname_(n);
	}
}

static const char *builtin_(int n)
{
	switch(n)
	{
	// buildin functions           
  case pcode__PRINTSCREEN: return "PRINTSCREEN";
  case pcode__VIEW: return "VIEW";
  case pcode__VIEWPRINT: return "VIEWPRINT";
  case pcode__LINE: return "LINE";
  case pcode__WINDOW: return "WINDOW";
  case pcode__PAINT: return "PAINT";
  case pcode__PSET: return "PSET";
  case pcode__PRESET: return "PRESET";
  case pcode__WIDTH: return "WIDTH";
  case pcode__PMAP: return "PMAP";
  case pcode__PCOPY: return "PCOPY";
  case pcode__DRAW: return "DRAW";
  case pcode__CIRCLE: return "CIRCLE";
  case pcode__SCREEN2: return "SCREEN2";
  case pcode__POINT: return "POINT";
  case pcode__SETATTR: return "SETATTR";
  case pcode__CHDRIVE: return "CHDRIVE";
  case pcode__FILECOPY: return "FILECOPY";
  case pcode__SPC: return "SPC";
  case pcode__FIELD: return "FIELD";
  case pcode__STRREVERSE: return "STRREVERSE";
  case pcode__ROUND: return "ROUND";
  case pcode__REPLACE: return "REPLACE";
  case pcode__SPLIT: return "SPLIT";
  case pcode__INSTREV: return "INSTREV";
  case pcode__GET: return "GET";
  case pcode__GET2: return "GET2";
  case pcode__PUT: return "PUT";
  case pcode__PUT2: return "PUT2";
  case pcode__NZ: return "NZ";
  case pcode__ABS: return "ABS";
  case pcode__ACCESS: return "ACCESS";
  case pcode__ACS: return "ACS";
  case pcode__APPEND: return "APPEND";
  case pcode__ASC: return "ASC";
  case pcode__ASN: return "ASN";
  case pcode__ATN: return "ATN";
  case pcode__BEEP: return "BEEP";
  case pcode__BIN: return "BIN";
  case pcode__CHDIR: return "CHDIR";
  case pcode__CHR: return "CHR";
  case pcode__CINT: return "CINT";
  case pcode__CLNG: return "CLNG";
  case pcode__CLOSE: return "CLOSE";
  case pcode__CLOSEALL: return "CLOSEALL";
  case pcode__CLS: return "CLS";
  case pcode__COLOR: return "COLOR";
  case pcode__COS: return "COS";
  case pcode__CSRLIN: return "CSRLIN";
  case pcode__DATE: return "DATE";
  case pcode__DATE2: return "DATE2";
  case pcode__DEG: return "DEG";
  case pcode__DOF: return "DOF";
  case pcode__EOF_: return "EOF";
  case pcode__EXP: return "EXP";
  case pcode__FACT: return "FACT";
  case pcode__FILES: return "FILES";
  case pcode__FIX: return "FIX";
  case pcode__FRAC: return "FRAC";
  case pcode__HEX: return "HEX";
  case pcode__SCREEN: return "SCREEN";
  case pcode__HYPOT: return "HYPOT";
  case pcode__INKEY: return "INKEY";
  case pcode__INPUT: return "INPUT";
  case pcode__INPUT2: return "INPUT2";
  case pcode__INSTR: return "INSTR";
  case pcode__INT: return "INT";
  case pcode__KILL: return "KILL";
  case pcode__LCASE: return "LCASE";
  case pcode__LEFT: return "LEFT";
  case pcode__LEN: return "LEN";
  case pcode__LINEINPUT: return "LINEINPUT";
  case pcode__LN: return "LN";
  case pcode__LOCATE: return "LOCATE";
  case pcode__LOF: return "LOF";
  case pcode__LOG: return "LOG";
  case pcode__LOGB: return "LOGB";
  case pcode__LTRIM: return "LTRIM";
  case pcode__MAX: return "MAX";
  case pcode__MID: return "MID";
  case pcode__MIN: return "MIN";
  case pcode__MKDIR: return "MKDIR";
  case pcode__NAME: return "NAME";
  case pcode__OCT: return "OCT";
  case pcode__OPEN: return "OPEN";
  case pcode__OPEN2: return "OPEN2";    
  case pcode__OUTPUT: return "OUTPUT";
  case pcode__POS: return "POS";
  case pcode__PRINT: return "PRINT";
  case pcode__RAD: return "RAD";
  case pcode__RANDOMIZE: return "RANDOMIZE";
  //case pcode__READ: return "READ";
  case pcode__RESET: return "RESET";
  case pcode__RIGHT: return "RIGHT";
  case pcode__RMDIR: return "RMDIR";
  case pcode__RND: return "RND";
  case pcode__RTRIM: return "RTRIM";
  case pcode__SEC: return "SEC";
  case pcode__SEEK: return "SEEK";
  case pcode__SEEK2: return "SEEK2";
  case pcode__SIN: return "SIN";
  case pcode__SGN: return "SGN";
  case pcode__SHELL: return "SHELL";
  case pcode__SPACE: return "SPACE";
  case pcode__SQR: return "SQR";
  case pcode__STR: return "STR";
  case pcode__STRING2: return "STRING";
  case pcode__TAN: return "TAN";
  case pcode__TIME: return "TIME";
  case pcode__TRIM: return "TRIM";
  case pcode__UCASE: return "UCASE";
  case pcode__VAL: return "VAL";
  case pcode__WRITE: return "WRITE";

	case pcode__ISDATE:  return "ISDATE";
	case pcode__ISEMPTY:  return "ISEMPTY";
	case pcode__ISNULL:  return "ISNULL";
	case pcode__ISNUMERIC:  return "ISNUMERIC";

	case pcode__CSNG:  return "CSNG";
	case pcode__CDBL:  return "CDBL";
	case pcode__CCUR:  return "CCUR";
	case pcode__CVAR:  return "CVAR";
	case pcode__CBOOL:  return "CBOOL";
	case pcode__CBYTE:  return "CBYTE";
	case pcode__CDATE:  return "CDATE";

  case pcode__STRCOMP: return "STRCOMP";
  case pcode__ISMISSING: return "ISMISSING";
  case pcode__ISARRAY: return "ISARRAY";
  case pcode__ISOBJECT: return "ISOBJECT";
  case pcode__ISCURRENCY: return "ISCURRENCY";    

  case pcode__ISBOOLEAN: return "ISBOOLEAN";
  case pcode__ISBYTE: return "ISBYTE";
  case pcode__ISDOUBLE: return "ISDOUBLE";

  case pcode__ISINTEGER: return "ISINTEGER";
  case pcode__ISINT16: return "ISINT16";
  case pcode__ISINT32: return "ISINT32";
  case pcode__ISINT64: return "ISINT64";

  case pcode__ISUINT16: return "ISUINT16";
  case pcode__ISUINT32: return "ISUINT32";
  case pcode__ISUINT64: return "ISUINT64";

  case pcode__ISSHORT: return "ISSHORT";
  case pcode__ISSINGLE: return "ISSINGLE";    
  case pcode__ISLONG: return "ISLONG";
  case pcode__ISSTRING: return "ISSTRING";
  case pcode__ISVARIANT: return "ISVARIANT";

  case pcode__ARRAY2: return "ARRAY2";
  case pcode__COMMAND: return "COMMAND";
  case pcode__CURDIR: return "CURDIR";
  case pcode__CVERR: return "CVERR";
  case pcode__MSGBOX: return "MSGBOX";

  case pcode__DATEADD: return "DATEADD";
  case pcode__DATEDIFF: return "DATEDIFF";
  case pcode__DATEPART: return "DATEPART";
  case pcode__DATESERIAL: return "DATESERIAL";
  case pcode__DATEVALUE: return "DATEVALUE";
  case pcode__DIR: return "DIR";
  case pcode__FILEATTR: return "FILEATTR";
  case pcode__FILEDATETIME: return "FILEDATETIME";
  case pcode__FORMAT: return "FORMAT";
  case pcode__FREEFILE: return "FREEFILE";
  case pcode__HOUR: return "HOUR";
  case pcode__LOC: return "LOC";
  case pcode__MINUTE: return "MINUTE";
  case pcode__MONTH: return "MONTH";
  case pcode__NOW: return "NOW";
  case pcode__RGB: return "RGB";
  case pcode__SECOND: return "SECOND";
  case pcode__TIMER: return "TIMER";

  case pcode__TIMESERIAL: return "TIMESERIAL";
  case pcode__TIMEVALUE: return "TIMEVALUE";
  case pcode__TYPENAME: return "TYPENAME";
  case pcode__WEEKDAY: return "WEEKDAY";
  case pcode__YEAR: return "YEAR";
  case pcode__ISERROR: return "ISERROR";
  case pcode__FILELEN: return "FILELEN";
  case pcode__GETATTR: return "GETATTR";

  case pcode__KBASICDIR: return "KBASICDIR";

    


	default: return pcode_kbasic_binding::methodname_(n);
	}
}

// ****************************
// * description:
// * prints an error
// *
// * parameter:
// * the error messages to print
// *
// * return:
// * false
// ****************************
static const bool internalError(const char *acError)
{
 	CONSOLE printError(acError);
//  showError(acText);

	return false;
}

static const int len(int n)
{
	switch(n)
	{

  case pcode__PUSH_INTEGER: return sizeof(pcode__PUSH_INTEGER) + sizeof(t_integer);
  case pcode__JMP: return sizeof(pcode__JMP) + sizeof(t_integer);
  case pcode__CJMP: return sizeof(pcode__CJMP) + sizeof(t_integer) + sizeof(t_boolean);
  case pcode__CJMP2: return sizeof(pcode__CJMP2) + sizeof(t_integer);
  case pcode__CJMP3: return sizeof(pcode__CJMP3) + sizeof(t_integer);
  case pcode__CALL: return sizeof(pcode__CALL) + sizeof(t_integer) + sizeof(t_integer);


  default: pcode::internalError("missing length in pcode.h"); return 0;
	}
}


// maybe parameter types for rd and wr should be all pointers




void rd_FRE(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bNUMERIC_EXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean(); *bNUMERIC_EXPRESSION = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_FRE(t_builtin c, t_boolean bEXPRESSION, t_boolean bNUMERIC_EXPRESSION, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bNUMERIC_EXPRESSION) ; wr_Boolean(bReturn); }



void rd_MOV_ME(t_pcode *c){ *c = rd_PCode(); }
void wr_MOV_ME(t_pcode c){	wr_PCode(c); }

void rd_MOV_PARENT(t_pcode *c){ *c = rd_PCode(); }
void wr_MOV_PARENT(t_pcode c){	wr_PCode(c); }


void rd_SET_ME(t_pcode *c, t_integer *identifier, t_scope *scope, t_boolean *bAssignment){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bAssignment = rd_Boolean(); }
void wr_SET_ME(t_pcode c, t_integer identifier, t_scope scope, t_boolean bAssignment){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bAssignment); }

void rd_binding_SET_ME(t_pcode *c){ *c = rd_PCode(); }
void wr_binding_SET_ME(t_pcode c){	wr_PCode(c); }


void rd_binding_PUSH_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); }
void wr_binding_PUSH_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_ID(t_pcode *c, t_integer *identifier, t_scope *scope, t_boolean *bAssignment){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bAssignment = rd_Boolean(); }
void wr_PUSH_ID(t_pcode c, t_integer identifier, t_scope scope, t_boolean bAssignment){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bAssignment); }

void rd_PUSH_CONST(t_pcode *c, t_integer *identifier){ *c = rd_PCode(); *identifier = rd_Integer(); }
void wr_PUSH_CONST(t_pcode c, t_integer identifier){	wr_PCode(c) ; wr_Integer(identifier); }

void rd_PUSH_ENUM(t_pcode *c, t_integer *identifier, t_integer *elementId){ *c = rd_PCode(); *identifier = rd_Integer(); *elementId = rd_Integer(); }
void wr_PUSH_ENUM(t_pcode c, t_integer identifier, t_integer elementId){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer(elementId); }


void rd_CLEAR(t_pcode *c, t_boolean *bExpression){ *c = rd_PCode(); *bExpression = rd_Boolean(); }
void wr_CLEAR(t_pcode c, t_boolean bExpression){	wr_PCode(c) ; wr_Boolean(bExpression); }

void rd_ERASE(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); }
void wr_ERASE(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_TYPEOF(t_pcode *c, t_integer *identifier, t_scope *scope, t_integer *nType, t_boolean *bReturn){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *nType = rd_Integer(); *bReturn = rd_Boolean(); }
void wr_TYPEOF(t_pcode c, t_integer identifier, t_scope scope, t_integer nType, t_boolean bReturn){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Integer(nType) ; wr_Boolean(bReturn); }

void rd_CHOOSE(t_pcode *choose, t_integer *count, t_boolean *bReturn){ *choose = rd_PCode(); *count = rd_Integer(); *bReturn = rd_Boolean(); }
void wr_CHOOSE(t_pcode choose, t_integer count, t_boolean bReturn){ wr_PCode(choose) ; wr_Integer(count) ; wr_Boolean(bReturn); }


void rd_FIELD(t_pcode *c, t_boolean *bEXPRESSION2, t_integer *count){ *c = rd_PCode(); *bEXPRESSION2 = rd_Boolean(); *count = rd_Integer(); }
void wr_FIELD(t_pcode c, t_boolean bEXPRESSION2, t_integer count){ wr_PCode(c) ; wr_Boolean(bEXPRESSION2) ; wr_Integer(count); }

void rd_SWITCH(t_pcode *switch_, t_integer *count, t_boolean *bReturn){ *switch_ = rd_PCode(); *count = rd_Integer(); *bReturn = rd_Boolean(); }
void wr_SWITCH(t_pcode switch_, t_integer count, t_boolean bReturn){ wr_PCode(switch_) ; wr_Integer(count) ; wr_Boolean(bReturn); }

void rd_IIF(t_pcode *iif, t_boolean *bReturn){ *iif = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_IIF(t_pcode iif, t_boolean bReturn){	wr_PCode(iif) ; wr_Boolean(bReturn); }

void rd_STACKPOP(t_pcode *c){ *c = rd_PCode(); }
void wr_STACKPOP(t_pcode c){	wr_PCode(c); }


void rd_ENTER_LOCAL(t_pcode *c, t_integer *nModuleId, t_integer *nSubId){ *c = rd_PCode(); *nModuleId = rd_Integer(); *nSubId = rd_Integer(); }
void wr_ENTER_LOCAL(t_pcode c, t_integer nModuleId, t_integer nSubId){	wr_PCode(c) ; wr_Integer(nModuleId) ; wr_Integer(nSubId); }

void rd_ENTER_PROPERTYGET(t_pcode *c, t_integer *nModuleId, t_integer *nSubId){ *c = rd_PCode(); *nModuleId = rd_Integer(); *nSubId = rd_Integer(); }
void wr_ENTER_PROPERTYGET(t_pcode c, t_integer nModuleId, t_integer nSubId){	wr_PCode(c) ; wr_Integer(nModuleId) ; wr_Integer(nSubId); }

void rd_ENTER_PROPERTYSET(t_pcode *c, t_integer *nModuleId, t_integer *nSubId){ *c = rd_PCode(); *nModuleId = rd_Integer(); *nSubId = rd_Integer(); }
void wr_ENTER_PROPERTYSET(t_pcode c, t_integer nModuleId, t_integer nSubId){	wr_PCode(c) ; wr_Integer(nModuleId) ; wr_Integer(nSubId); }


void rd_EXIT_LOCAL(t_pcode *c){ *c = rd_PCode(); }
void wr_EXIT_LOCAL(t_pcode c){	wr_PCode(c); }



void rd_CVERR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_CVERR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }


void rd_POINT(t_builtin *c, t_boolean *bColor, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bColor = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_POINT(t_builtin c, t_boolean bColor, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bColor) ; wr_Boolean(bReturn); }

void rd_NOW(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_NOW(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_DAY(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_DAY(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_FREEFILE(t_builtin *c, t_boolean *bRange, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bRange = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_FREEFILE(t_builtin c, t_boolean bRange, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bRange) ; wr_Boolean(bReturn); }

void rd_INSTREV(t_builtin *c, t_boolean *bStart, t_boolean *bLastIndexOf, t_boolean *bCase, t_boolean *bReturn, t_boolean *bObjectFake){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bStart = rd_Boolean(); *bLastIndexOf = rd_Boolean(); *bCase = rd_Boolean(); *bReturn = rd_Boolean(); *bObjectFake = rd_Boolean(); }
void wr_INSTREV(t_builtin c, t_boolean bStart, t_boolean bLastIndexOf, t_boolean bCase, t_boolean bReturn, t_boolean bObjectFake){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bStart) ; wr_Boolean(bLastIndexOf) ; wr_Boolean(bCase) ; wr_Boolean(bReturn) ; wr_Boolean(bObjectFake); }

void rd_LINEINPUT(t_builtin *c, t_integer *identifier, t_scope *scope){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); }
void wr_LINEINPUT(t_builtin c, t_integer identifier, t_scope scope){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_GETATTR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_GETATTR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_HOUR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_HOUR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_RGB(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_RGB(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SECOND(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SECOND(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_TIMER(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_TIMER(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }


void rd_TIMESERIAL(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_TIMESERIAL(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_TIMEVALUE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_TIMEVALUE(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_TYPENAME(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_TYPENAME(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }


void rd_WEEKDAY(t_builtin *c, t_boolean *firstdayofweek, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *firstdayofweek = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_WEEKDAY(t_builtin c, t_boolean firstdayofweek, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(firstdayofweek) ; wr_Boolean(bReturn); }

void rd_YEAR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_YEAR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }



void rd_INPUTBOX(t_builtin *c, t_boolean *title, t_boolean *default_, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *title = rd_Boolean(); *default_ = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_INPUTBOX(t_builtin c, t_boolean title, t_boolean default_, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(title) ; wr_Boolean(default_) ; wr_Boolean(bReturn); }

void rd_MSGBOX(t_builtin *c, t_boolean *buttons, t_boolean *title, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *buttons = rd_Boolean(); *title = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_MSGBOX(t_builtin c, t_boolean buttons, t_boolean title, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(buttons) ; wr_Boolean(title) ; wr_Boolean(bReturn); }

void rd_DATEADD(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_DATEADD(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_DATEDIFF(t_builtin *c, t_boolean *firstdayofweek, t_boolean *firstweekofyear, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *firstdayofweek = rd_Boolean(); *firstweekofyear = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_DATEDIFF(t_builtin c, t_boolean firstdayofweek, t_boolean firstweekofyear, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(firstdayofweek) ; wr_Boolean(firstweekofyear) ; wr_Boolean(bReturn); }

void rd_DATEPART(t_builtin *c, t_boolean *firstdayofweek, t_boolean *firstweekofyear, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *firstdayofweek = rd_Boolean(); *firstweekofyear = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_DATEPART(t_builtin c, t_boolean firstdayofweek, t_boolean firstweekofyear, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(firstdayofweek) ; wr_Boolean(firstweekofyear) ; wr_Boolean(bReturn); }

void rd_DATEVALUE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_DATEVALUE(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_DATESERIAL(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_DATESERIAL(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_FORMAT(t_builtin *c, t_boolean *bFORMAT, t_boolean *fillchar, t_boolean *rightaligned, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bFORMAT = rd_Boolean(); *fillchar = rd_Boolean(); *rightaligned = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_FORMAT(t_builtin c, t_boolean bFORMAT, t_boolean fillchar, t_boolean rightaligned, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bFORMAT) ; wr_Boolean(fillchar) ; wr_Boolean(rightaligned) ; wr_Boolean(bReturn); }

//void rd_FORMAT(t_builtin *c, t_boolean *bFORMAT, t_boolean *firstdayofweek, t_boolean *firstweekofyear, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bFORMAT = rd_Boolean(); *firstdayofweek = rd_Boolean(); *firstweekofyear = rd_Boolean(); *bReturn = rd_Boolean(); }
//void wr_FORMAT(t_builtin c, t_boolean bFORMAT, t_boolean firstdayofweek, t_boolean firstweekofyear, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bFORMAT) ; wr_Boolean(firstdayofweek) ; wr_Boolean(firstweekofyear) ; wr_Boolean(bReturn); }


void rd_FORMATCURRENCY(t_builtin *c, t_boolean *bFORMAT, t_boolean *firstdayofweek, t_boolean *firstweekofyear, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bFORMAT = rd_Boolean(); *firstdayofweek = rd_Boolean(); *firstweekofyear = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_FORMATCURRENCY(t_builtin c, t_boolean bFORMAT, t_boolean firstdayofweek, t_boolean firstweekofyear, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bFORMAT) ; wr_Boolean(firstdayofweek) ; wr_Boolean(firstweekofyear) ; wr_Boolean(bReturn); }

void rd_FORMATDATETIME(t_builtin *c, t_boolean *bFORMAT, t_boolean *firstdayofweek, t_boolean *firstweekofyear, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bFORMAT = rd_Boolean(); *firstdayofweek = rd_Boolean(); *firstweekofyear = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_FORMATDATETIME(t_builtin c, t_boolean bFORMAT, t_boolean firstdayofweek, t_boolean firstweekofyear, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bFORMAT) ; wr_Boolean(firstdayofweek) ; wr_Boolean(firstweekofyear) ; wr_Boolean(bReturn); }

void rd_FORMATNUMBER(t_builtin *c, t_boolean *bFORMAT, t_boolean *firstdayofweek, t_boolean *firstweekofyear, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bFORMAT = rd_Boolean(); *firstdayofweek = rd_Boolean(); *firstweekofyear = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_FORMATNUMBER(t_builtin c, t_boolean bFORMAT, t_boolean firstdayofweek, t_boolean firstweekofyear, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bFORMAT) ; wr_Boolean(firstdayofweek) ; wr_Boolean(firstweekofyear) ; wr_Boolean(bReturn); }

void rd_FORMATPERCENT(t_builtin *c, t_boolean *bFORMAT, t_boolean *firstdayofweek, t_boolean *firstweekofyear, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bFORMAT = rd_Boolean(); *firstdayofweek = rd_Boolean(); *firstweekofyear = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_FORMATPERCENT(t_builtin c, t_boolean bFORMAT, t_boolean firstdayofweek, t_boolean firstweekofyear, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bFORMAT) ; wr_Boolean(firstdayofweek) ; wr_Boolean(firstweekofyear) ; wr_Boolean(bReturn); }

void rd_WEEKDAYNAME(t_builtin *c, t_boolean *bShorty, t_boolean *firstdayofweek, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bShorty = rd_Boolean(); *firstdayofweek = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_WEEKDAYNAME(t_builtin c, t_boolean bShorty, t_boolean firstdayofweek, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bShorty) ; wr_Boolean(firstdayofweek) ; wr_Boolean(bReturn); }

void rd_MONTHNAME(t_builtin *c, t_boolean *bFORMAT, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bFORMAT = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_MONTHNAME(t_builtin c, t_boolean bFORMAT, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bFORMAT) ; wr_Boolean(bReturn); }

void rd_DAYNAME(t_builtin *c, t_boolean *bFORMAT, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bFORMAT = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_DAYNAME(t_builtin c, t_boolean bFORMAT, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bFORMAT) ; wr_Boolean(bReturn); }


void rd_DAYOFWEEK(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_DAYOFWEEK(t_builtin c, t_boolean bEXPRESSION, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION); wr_Boolean(bReturn); }

void rd_DAYOFYEAR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_DAYOFYEAR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_DAYSINMONTH(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_DAYSINMONTH(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_DAYSINYEAR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_DAYSINYEAR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_WEEKNUMBER(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_WEEKNUMBER(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ISLEAPYEAR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISLEAPYEAR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_DIFFDAY(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_DIFFDAY(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_DIFFSECONDS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_DIFFSECONDS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ISDATEVALID(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISDATEVALID(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ISTIMEVALID(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISTIMEVALID(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ISDATETIMEVALID(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISDATETIMEVALID(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }


void rd_ADDDATE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ADDDATE(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ADDDAYS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ADDDAYS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ADDMONTHS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ADDMONTHS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ADDYEARS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ADDYEARS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SUBDATE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SUBDATE(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SUBDAYS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SUBDAYS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SUBMONTHS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SUBMONTHS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SUBYEARS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SUBYEARS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ADDTIME(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ADDTIME(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ADDHOURS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ADDHOURS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ADDMINUTES(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ADDMINUTES(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ADDSECONDS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ADDSECONDS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SUBTIME(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SUBTIME(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SUBHOURS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SUBHOURS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SUBMINUTES(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SUBMINUTES(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SUBSECONDS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SUBSECONDS(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }



void rd_PAINT(t_builtin *c, t_boolean *color, t_boolean *pattern, t_boolean *bordercolor, t_boolean *background){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *color = rd_Boolean(); *pattern = rd_Boolean(); *bordercolor = rd_Boolean(); *background = rd_Boolean(); }
void wr_PAINT(t_builtin c, t_boolean color, t_boolean pattern, t_boolean bordercolor, t_boolean background){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(color) ; wr_Boolean(pattern) ; wr_Boolean(bordercolor) ; wr_Boolean(background); }

void rd_COMMAND(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_COMMAND(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_CURDIR(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_CURDIR(t_builtin c, t_boolean bEXPRESSION, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bReturn); }

void rd_DIR(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bEXPRESSION2, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean(); *bEXPRESSION2 = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_DIR(t_builtin c, t_boolean bEXPRESSION, t_boolean bEXPRESSION2, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bEXPRESSION2) ; wr_Boolean(bReturn); }

void rd_CIRCLE(t_builtin *c, t_boolean *color, t_boolean *start, t_boolean *end, t_boolean *aspect){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *color = rd_Boolean(); *start = rd_Boolean(); *end = rd_Boolean(); *aspect = rd_Boolean(); }
void wr_CIRCLE(t_builtin c, t_boolean color, t_boolean start, t_boolean end, t_boolean aspect){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(color) ; wr_Boolean(start) ; wr_Boolean(end) ; wr_Boolean(aspect); }

void rd_DRAW(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_DRAW(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_LINE(t_builtin *c, t_boolean *bSTEP, t_boolean *bEXPRESSION, t_boolean *bSTEP2, t_boolean *color, t_boolean *b, t_boolean *bf, t_boolean *style){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bSTEP = rd_Boolean(); *bEXPRESSION = rd_Boolean(); *bSTEP2 = rd_Boolean(); *color = rd_Boolean(); *b = rd_Boolean(); *bf = rd_Boolean(); *style = rd_Boolean(); }
void wr_LINE(t_builtin c, t_boolean bSTEP, t_boolean bEXPRESSION, t_boolean bSTEP2, t_boolean color, t_boolean b, t_boolean bf, t_boolean style){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bSTEP) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bSTEP2) ; wr_Boolean(color) ; wr_Boolean(b) ; wr_Boolean(bf) ; wr_Boolean(style); }

void rd_VIEW(t_builtin *c, t_boolean *bSCREEN, t_boolean *color, t_boolean *border){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bSCREEN = rd_Boolean(); *color = rd_Boolean(); *border = rd_Boolean(); }
void wr_VIEW(t_builtin c, t_boolean bSCREEN, t_boolean color, t_boolean border){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bSCREEN) ; wr_Boolean(color) ; wr_Boolean(border); }

void rd_WINDOW(t_builtin *c, t_boolean *bScreen, t_boolean *bExpression){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bScreen = rd_Boolean(); *bExpression = rd_Boolean(); }
void wr_WINDOW(t_builtin c, t_boolean bScreen, t_boolean bExpression){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bScreen) ; wr_Boolean(bExpression); }

void rd_PSET(t_builtin *c, t_boolean *bStep, t_boolean *bColor){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bStep = rd_Boolean(); *bColor = rd_Boolean(); }
void wr_PSET(t_builtin c, t_boolean bStep, t_boolean bColor){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bStep) ; wr_Boolean(bColor); }

void rd_PRESET(t_builtin *c, t_boolean *bStep, t_boolean *bColor){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bStep = rd_Boolean(); *bColor = rd_Boolean(); }
void wr_PRESET(t_builtin c, t_boolean bStep, t_boolean bColor){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bStep) ; wr_Boolean(bColor); }

void rd_SCREEN2(t_builtin *c, t_boolean *bColor, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bColor = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_SCREEN2(t_builtin c, t_boolean bColor, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bColor) ; wr_Boolean(bReturn); }

void rd_ROUND(t_builtin *c, t_boolean *bDigit, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bDigit = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_ROUND(t_builtin c, t_boolean bDigit, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bDigit) ; wr_Boolean(bReturn); }

void rd_SPLIT(t_builtin *c, t_boolean *bKeepEmptyParts, t_boolean *bCaseSensitive, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bKeepEmptyParts = rd_Boolean(); *bCaseSensitive = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_SPLIT(t_builtin c, t_boolean bKeepEmptyParts, t_boolean bCaseSensitive, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bKeepEmptyParts) ; wr_Boolean(bCaseSensitive) ; wr_Boolean(bReturn); }

void rd_VIEWPRINT(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_VIEWPRINT(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_WIDTH(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_WIDTH(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_PMAP(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_PMAP(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_PCOPY(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_PCOPY(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_SETATTR(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_SETATTR(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_CHDRIVE(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_CHDRIVE(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_PRINTSCREEN(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_PRINTSCREEN(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_SPC(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_SPC(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_STRREVERSE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_STRREVERSE(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_CSNG(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_CSNG(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_CDBL(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_CDBL(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_CCUR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_CCUR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_CVAR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_CVAR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_CBOOL(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_CBOOL(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_CBYTE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_CBYTE(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_CDATE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_CDATE(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }


void rd_ARRAY2(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ARRAY2(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_LOC(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_LOC(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_MINUTE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_MINUTE(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_MONTH(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_MONTH(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ISDATE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISDATE(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ISEMPTY(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISEMPTY(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISNULL(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISNULL(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ISNUMERIC(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISNUMERIC(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ISMISSING(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISMISSING(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISARRAY(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISARRAY(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISBOOLEAN(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISBOOLEAN(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISBYTE(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISBYTE(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISDOUBLE(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISDOUBLE(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISINTEGER(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISINTEGER(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISINT16(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISINT16(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISINT32(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISINT32(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISINT64(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISINT64(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISUINT16(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISUINT16(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISUINT32(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISUINT32(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISUINT64(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISUINT64(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISSINGLE(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISSINGLE(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISSHORT(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISSHORT(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISLONG(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISLONG(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISSTRING(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISSTRING(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }

void rd_ISVARIANT(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_ISVARIANT(t_builtin c, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }


void rd_ISOBJECT(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISOBJECT(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ISCURRENCY(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISCURRENCY(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_REPLACE(t_builtin *c, t_boolean *bCase, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bCase = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_REPLACE(t_builtin c, t_boolean bCase, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bCase); wr_Boolean(bReturn); }

void rd_ISERROR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_ISERROR(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_NZ(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_NZ(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_GET(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bRecordNo, t_boolean *bIDENTIFIER){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bRecordNo = rd_Boolean(); *bIDENTIFIER = rd_Boolean(); }
void wr_GET(t_builtin c, t_integer identifier, t_scope scope, t_boolean bRecordNo, t_boolean bIDENTIFIER){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bRecordNo) ; wr_Boolean(bIDENTIFIER); }

void rd_GET2(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bStep1, t_boolean *bStep2){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bStep1 = rd_Boolean(); *bStep2 = rd_Boolean(); }
void wr_GET2(t_builtin c, t_integer identifier, t_scope scope, t_boolean bStep1, t_boolean bStep2){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bStep1) ; wr_Boolean(bStep2); }

void rd_PUT(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bRecordNo){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bRecordNo = rd_Boolean(); }
void wr_PUT(t_builtin c, t_integer identifier, t_scope scope, t_boolean bRecordNo){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bRecordNo); }

void rd_PUT2(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bStep, t_integer *nMode){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bStep = rd_Boolean(); *nMode = rd_Integer(); }
void wr_PUT2(t_builtin c, t_integer identifier, t_scope scope, t_boolean bStep, t_integer nMode){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bStep) ; wr_Integer(nMode); }

void rd_POKE(t_builtin *c/*, t_integer *identifier, t_scope *scope*//*, t_boolean *bObjectFake*/){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); /**identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *//**bObjectFake = rd_Boolean();*/}
void wr_POKE(t_builtin c/*, t_integer identifier, t_scope scope*//*, t_boolean bObjectFake*/){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; /*wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; *//*wr_Boolean(bObjectFake) ;*/}

void rd_PEEK(t_builtin *c, t_integer *identifier, t_scope *scope/*, t_boolean *bObjectFake*/){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); /**bObjectFake = rd_Boolean();*/}
void wr_PEEK(t_builtin c, t_integer identifier, t_scope scope/*, t_boolean bObjectFake*/){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ;/*wr_Boolean(bObjectFake) ; */}


void rd_COMPARE(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean();  *bReturn = rd_Boolean(); }
void wr_COMPARE(t_builtin c, t_boolean bEXPRESSION, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bReturn); }

void rd_CONTAINS(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean();  *bReturn = rd_Boolean(); }
void wr_CONTAINS(t_builtin c, t_boolean bEXPRESSION, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bReturn); }

void rd_COUNT(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean();  *bReturn = rd_Boolean(); }
void wr_COUNT(t_builtin c, t_boolean bEXPRESSION, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bReturn); }

void rd_ENDSWITH(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean();  *bReturn = rd_Boolean(); }
void wr_ENDSWITH(t_builtin c, t_boolean bEXPRESSION, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bReturn); }

void rd_STARTSWITH(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean();  *bReturn = rd_Boolean(); }
void wr_STARTSWITH(t_builtin c, t_boolean bEXPRESSION, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bReturn); }

void rd_LEFTJUSTIFIED(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bEXPRESSION2, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean(); *bEXPRESSION2 = rd_Boolean();  *bReturn = rd_Boolean(); }
void wr_LEFTJUSTIFIED(t_builtin c, t_boolean bEXPRESSION, t_boolean bEXPRESSION2, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bEXPRESSION2) ; wr_Boolean(bReturn); }

void rd_RIGHTJUSTIFIED(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bEXPRESSION2, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean(); *bEXPRESSION2 = rd_Boolean();  *bReturn = rd_Boolean(); }
void wr_RIGHTJUSTIFIED(t_builtin c, t_boolean bEXPRESSION, t_boolean bEXPRESSION2, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bEXPRESSION2) ; wr_Boolean(bReturn); }

void rd_SECTION(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bEXPRESSION2, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean(); *bEXPRESSION2 = rd_Boolean();  *bReturn = rd_Boolean(); }
void wr_SECTION(t_builtin c, t_boolean bEXPRESSION, t_boolean bEXPRESSION2, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bEXPRESSION2) ; wr_Boolean(bReturn); }

void rd_SIMPLIFIED(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode();  *bReturn = rd_Boolean(); }
void wr_SIMPLIFIED(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_TRIMMED(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode();  *bReturn = rd_Boolean(); }
void wr_TRIMMED(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_REVERSED(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode();  *bReturn = rd_Boolean(); }
void wr_REVERSED(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_UNICODE(t_builtin *c, t_boolean *bEXPRESSION, t_boolean *bEXPRESSION2, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION = rd_Boolean(); *bEXPRESSION2 = rd_Boolean();  *bReturn = rd_Boolean(); }
void wr_UNICODE(t_builtin c, t_boolean bEXPRESSION, t_boolean bEXPRESSION2, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bEXPRESSION2) ; wr_Boolean(bReturn); }

void rd_READBINARY(t_builtin *c, t_integer *identifier, t_scope *scope, t_integer *nType, t_boolean *bEXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *nType = rd_Integer(); *bEXPRESSION = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_READBINARY(t_builtin c, t_integer identifier, t_scope scope, t_integer nType, t_boolean bEXPRESSION, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); wr_Integer(nType); wr_Boolean(bEXPRESSION); wr_Boolean(bReturn); }

void rd_WRITEBINARY(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bEXPRESSION){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bEXPRESSION = rd_Boolean(); }
void wr_WRITEBINARY(t_builtin c, t_integer identifier, t_scope scope, t_boolean bEXPRESSION){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); wr_Boolean(bEXPRESSION); }

void rd_SEEKBINARY(t_builtin *c, t_integer *identifier, t_scope *scope, t_boolean *bEXPRESSION, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bEXPRESSION = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_SEEKBINARY(t_builtin c, t_integer identifier, t_scope scope, t_boolean bEXPRESSION, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); wr_Boolean(bEXPRESSION); wr_Boolean(bReturn);  }


void rd_PREPEND(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_PREPEND(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; }

void rd_APPEND2(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_APPEND2(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; }

void rd_REMOVE(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_REMOVE(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; }

void rd_TRUNCATE(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_TRUNCATE(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; }

void rd_INSERT(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); }
void wr_INSERT(t_builtin c){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; }

void rd_FILL(t_builtin *c, t_boolean *bEXPRESSION){ t_pcode builtin = rd_PCode(); *c = rd_PCode();  *bEXPRESSION = rd_Boolean(); }
void wr_FILL(t_builtin c, t_boolean bEXPRESSION){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION); }




void rd_FILELEN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_FILELEN(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }



void rd_VARTYPE(t_pcode *vartype, t_integer *identifier, t_scope *scope, t_boolean *bReturn){ *vartype = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bReturn = rd_Boolean(); }
void wr_VARTYPE(t_pcode vartype, t_integer identifier, t_scope scope, t_boolean bReturn){	wr_PCode(vartype) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bReturn); }



void rd_SILENTMODE(t_pcode *c, t_boolean *on_off){ *c = rd_PCode(); *on_off = rd_Boolean(); }
void wr_SILENTMODE(t_pcode c, t_boolean on_off){	wr_PCode(c) ; wr_Boolean(on_off); }

void rd_SEPARATOR(t_pcode *c, t_cstring *s){ *c = rd_PCode(); *s = rd_CString(); }
void wr_SEPARATOR(t_pcode c, t_cstring s = ""){	wr_PCode(c) ; wr_CString(s); }



void rd_OPTION_KBASIC(t_pcode *c){ *c = rd_PCode(); }
void wr_OPTION_KBASIC(t_pcode c){	wr_PCode(c) ; }

void rd_OPTION_RANGE(t_pcode *option_range, t_boolean *on_off){ *option_range = rd_PCode(); *on_off = rd_Boolean(); }
void wr_OPTION_RANGE(t_pcode option_range, t_boolean on_off){	wr_PCode(option_range) ; wr_Boolean(on_off); }
/*
void rd_OPTION_COMPARE(t_pcode *c, t_boolean *bBinary){ *c = rd_PCode(); *bBinary = rd_Boolean(); }
void wr_OPTION_COMPARE(t_pcode c, t_boolean bBinary){	wr_PCode(c) ; wr_Boolean(bBinary); }

void rd_OPTION_BASE(t_pcode *c, t_integer *nStartArrayIndex){ *c = rd_PCode(); *nStartArrayIndex = rd_Integer(); }
void wr_OPTION_BASE(t_pcode c, t_integer nStartArrayIndex){	wr_PCode(c) ; wr_Integer(nStartArrayIndex); }
*/

void rd_ONTIMERGOSUB(t_pcode *c, t_integer *new_pc){ *c = rd_PCode(); *new_pc = rd_Integer(); }
void wr_ONTIMERGOSUB(t_pcode c, t_integer new_pc){ wr_PCode(c) ; wr_Integer(new_pc); }

void rd_TIMER_ON(t_pcode *c){ *c = rd_PCode(); }
void wr_TIMER_ON(t_pcode c){	wr_PCode(c); }

void rd_TIMER_OFF(t_pcode *c){ *c = rd_PCode(); }
void wr_TIMER_OFF(t_pcode c){	wr_PCode(c); }

void rd_TIMER_STOP(t_pcode *c){ *c = rd_PCode(); }
void wr_TIMER_STOP(t_pcode c){	wr_PCode(c); }

void rd_STOP(t_pcode *c){ *c = rd_PCode(); }
void wr_STOP(t_pcode stop){	wr_PCode(stop); }

void rd_DOEVENTS(t_pcode *c){ *c = rd_PCode(); }
void wr_DOEVENTS(t_pcode c){	wr_PCode(c); }



void rd___STATIC(t_pcode *c){ *c = rd_PCode(); }
void wr___STATIC(t_pcode _static){	wr_PCode(_static); }

void rd___DYNAMIC(t_pcode *c){ *c = rd_PCode(); }
void wr___DYNAMIC(t_pcode _dynamic){	wr_PCode(_dynamic); }


void rd_SYSTEM(t_pcode *c){ *c = rd_PCode(); }
void wr_SYSTEM(t_pcode system){	wr_PCode(system); }


void rd_END(t_pcode *c){ *c = rd_PCode(); }
void wr_END(t_pcode end){	wr_PCode(end); }

void rd_CALL(t_pcode *call, t_integer *new_pc, t_integer *return_pc){ *call = rd_PCode(); *new_pc = rd_Integer(); *return_pc = rd_Integer(); }
void wr_CALL(t_pcode call, t_integer new_pc, t_integer return_pc){	wr_PCode(call) ; wr_Integer(new_pc) ; wr_Integer(return_pc); }

void rd_LIBCALL(t_pcode *c, t_cstring *lib, t_cstring *function, t_integer *return_type, t_integer *count, t_cstring *signature){ *c = rd_PCode(); *lib = rd_CString(); *function = rd_CString();  *return_type = rd_Integer();  *count = rd_Integer();  *signature = rd_CString(); }
void wr_LIBCALL(t_pcode c, t_cstring lib, t_cstring function, t_integer return_type, t_integer count, t_cstring signature){	wr_PCode(c) ; wr_CString(lib) ; wr_CString(function) ; wr_Integer(return_type) ; wr_Integer(count) ; wr_CString(signature); }


void rd_CATCH(t_pcode *c, t_integer *class_id, t_integer *catch_pc){ *c = rd_PCode(); *class_id = rd_Integer(); *catch_pc = rd_Integer();  }
void wr_CATCH(t_pcode c, t_integer class_id, t_integer catch_pc){	wr_PCode(c) ; wr_Integer(class_id) ; wr_Integer(catch_pc); }

void rd_CALLMETHOD(t_pcode *c, int *new_pc){ *c = rd_PCode(); *new_pc = rd_PCode(); }
void wr_CALLMETHOD(t_pcode c, int new_pc){	wr_PCode(c) ; wr_Integer(new_pc); }

void rd_RETURN(t_pcode *c){ *c = rd_PCode(); }
void wr_RETURN(t_pcode return_){	wr_PCode(return_); }

void rd_CALL_RETURN(t_pcode *c, t_boolean *bMethod){ *c = rd_PCode(); *bMethod = rd_Boolean(); }
void wr_CALL_RETURN(t_pcode call_return_, t_boolean bMethod){	wr_PCode(call_return_) ; wr_Boolean(bMethod); }


void rd_NOP(t_pcode *c){ *c = rd_PCode(); }
void wr_NOP(t_pcode nop){	wr_PCode(nop); }



void rd_TYPE(t_pcode *type, t_integer *identifier, t_integer *element_count)
{ *type = rd_PCode(); *identifier = rd_Integer(); *element_count = rd_Integer(); }

void wr_TYPE(t_pcode type, t_integer identifier, t_integer element_count)
{	wr_PCode(type) ; wr_Integer(identifier) ; wr_Integer(element_count); }

void rd_TYPE_ELEMENT(t_pcode *type_element, t_integer *identifier, t_integer *type, t_array *a, t_integer *lstring_size)
{ *type_element = rd_PCode(); *identifier = rd_Integer(); *type = rd_Integer(); rd_Array(a); *lstring_size = rd_Integer(); }

void wr_TYPE_ELEMENT(t_pcode type_element, t_integer identifier, t_integer type, t_array *a, t_integer lstring_size)
{	wr_PCode(type_element) ; wr_Integer(identifier) ; wr_Integer(type) ; wr_Array(a) ; wr_Integer(lstring_size); }




void rd_ENUM(t_pcode *c, t_integer *identifier, t_integer *element_count)
{ *c = rd_PCode(); *identifier = rd_Integer(); *element_count = rd_Integer(); }

void wr_ENUM(t_pcode c, t_integer identifier, t_integer element_count)
{	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer(element_count); }

void rd_ENUM_ELEMENT(t_pcode *c, t_integer *identifier, t_integer *element_id, t_integer *type)
{ *c = rd_PCode(); *identifier = rd_Integer(); *element_id = rd_Integer(); *type = rd_Integer(); }

void wr_ENUM_ELEMENT(t_pcode c, t_integer identifier, t_integer element_id, t_integer type)
{	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer(element_id) ; wr_Integer(type); }




void rd_STRUCTURE(t_pcode *c, t_integer *identifier, t_integer *element_count)
{ *c = rd_PCode(); *identifier = rd_Integer(); *element_count = rd_Integer(); }

void wr_STRUCTURE(t_pcode c, t_integer identifier, t_integer element_count)
{	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer(element_count); }

void rd_STRUCTURE_ELEMENT(t_pcode *c, t_integer *identifier, t_integer *type, t_array *a, t_integer *lstring_size)
{ *c = rd_PCode(); *identifier = rd_Integer(); *type = rd_Integer(); rd_Array(a); *lstring_size = rd_Integer();  }

void wr_STRUCTURE_ELEMENT(t_pcode c, t_integer identifier, t_integer type, t_array *a, t_integer lstring_size)
{	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer(type) ; wr_Array(a) ; wr_Integer(lstring_size); }



void rd_CJMP(t_pcode *cjmp, t_integer *new_pc, t_boolean *conditional){ *cjmp = rd_PCode(); *new_pc = rd_Integer(); *conditional = rd_Boolean(); }
void wr_CJMP(t_pcode cjmp, t_integer new_pc, t_boolean conditional){	wr_PCode(cjmp) ; wr_Integer(new_pc) ; wr_Boolean(conditional); }

void rd_CJMP2(t_pcode *cjmp, t_integer *new_pc, t_boolean *conditional){ *cjmp = rd_PCode(); *new_pc = rd_Integer(); *conditional = rd_Boolean(); }
void wr_CJMP2(t_pcode cjmp, t_integer new_pc, t_boolean conditional){	wr_PCode(cjmp) ; wr_Integer(new_pc) ; wr_Boolean(conditional); }

void rd_CJMP3(t_pcode *cjmp, t_integer *new_pc, t_boolean *andalso){ *cjmp = rd_PCode(); *new_pc = rd_Integer(); *andalso = rd_Boolean(); }
void wr_CJMP3(t_pcode cjmp, t_integer new_pc, t_boolean andalso){	wr_PCode(cjmp) ; wr_Integer(new_pc) ; wr_Boolean(andalso); }


// * PUSH - functions

//  rd_PUSH__binding_ME --> rd_binding_PUSH_ME umbenennen
void rd_PUSH__binding_ME(t_pcode *c){ *c = rd_PCode(); }
void wr_PUSH__binding_ME(t_pcode c){	wr_PCode(c); }

//  rd_PUSH__binding_ME --> rd_binding_PUSH_ME umbenennen
void rd_PUSH__binding_PARENT(t_pcode *c){ *c = rd_PCode(); }
void wr_PUSH__binding_PARENT(t_pcode c){	wr_PCode(c); }


void rd_PUSH_ME(t_pcode *c){ *c = rd_PCode(); }
void wr_PUSH_ME(t_pcode c){	wr_PCode(c); }


void rd_PUSH_PARENT(t_pcode *c){ *c = rd_PCode(); }
void wr_PUSH_PARENT(t_pcode c){	wr_PCode(c); }


void rd_PUSH_BYTE(t_pcode *d, t_byte *c){ *d = rd_PCode(); *c = rd_Byte(); }
void wr_PUSH_BYTE(t_pcode d, t_byte c){	wr_PCode(d) ; wr_Byte(c); }

void rd_PUSH_SHORT(t_pcode *d, t_short *c){ *d = rd_PCode(); *c = rd_Short(); }
void wr_PUSH_SHORT(t_pcode d, t_short c){	wr_PCode(d) ; wr_Short(c); }

void rd_PUSH_INTEGER(t_pcode *d, t_integer *c){ *d = rd_PCode(); *c = rd_Integer(); }
void wr_PUSH_INTEGER(t_pcode d, t_integer c){	wr_PCode(d) ; wr_Integer(c); }

void rd_PUSH_LONG(t_pcode *d, t_long *c){ *d = rd_PCode(); *c = rd_Long(); }
void wr_PUSH_LONG(t_pcode d, t_long c){	wr_PCode(d) ; wr_Long(c); }

void rd_PUSH_SINGLE(t_pcode *d, t_single *c){ *d = rd_PCode(); *c = rd_Single(); }
void wr_PUSH_SINGLE(t_pcode d, t_single c){	wr_PCode(d) ; wr_Single(c); }

void rd_PUSH_DOUBLE(t_pcode *d, t_double *c){ *d = rd_PCode(); *c = rd_Double(); }
void wr_PUSH_DOUBLE(t_pcode d, t_double c){	wr_PCode(d) ; wr_Double(c); }


void rd_PUSH_CURRENCY(t_pcode *d, t_currency *c){ *d = rd_PCode(); *c = rd_Currency(); }
void wr_PUSH_CURRENCY(t_pcode d, t_currency c){	wr_PCode(d) ; wr_Currency(c); }
/*
void rd_PUSH_CHARACTER(t_pcode *d, t_character *c){ *d = rd_PCode(); *c = rd_Character(); }
void wr_PUSH_CHARACTER(t_pcode d, t_character c){	wr_PCode(d) ; wr_Character(c); }
*/

void rd_PUSH_DATE(t_pcode *c, t_date *d){ *c = rd_PCode(); *d = rd_Date(); }
void wr_PUSH_DATE(t_pcode c, t_date d){	wr_PCode(c) ; wr_Date(d); }


//void rd_PUSH_VARIANT(t_pcode *d, t_variant *c){ *d = rd_PCode(); *c = rd_Variant();  }
//void wr_PUSH_VARIANT(t_pcode d, t_variant c){	wr_PCode(d) ; wr_Variant(c); }

/*void rd_PUSH_INT16(t_pcode *c, t_int16 *d){ *c = rd_PCode(); *d = rd_Int16(); }
void wr_PUSH_INT16(t_pcode c, t_int16 d){	wr_PCode(c) ; wr_Int16(d); }

void rd_PUSH_INT32(t_pcode *c, t_int32 *d){ *c = rd_PCode(); *d = rd_Int32(); }
void wr_PUSH_INT32(t_pcode c, t_int32 d){	wr_PCode(c) ; wr_Int32(d); }

void rd_PUSH_INT64(t_pcode *c, t_int64 *d){ *c = rd_PCode(); *d = rd_Int64(); }
void wr_PUSH_INT64(t_pcode c, t_int64 d){	wr_PCode(c) ; wr_Int64(d); }

void rd_PUSH_UINT16(t_pcode *c, t_uint16 *d){ *c = rd_PCode(); *d = rd_UInt16(); }
void wr_PUSH_UINT16(t_pcode c, t_uint16 d){	wr_PCode(c) ; wr_UInt16(d); }

void rd_PUSH_UINT32(t_pcode *c, t_uint32 *d){ *c = rd_PCode(); *d = rd_UInt32(); }
void wr_PUSH_UINT32(t_pcode c, t_uint32 d){	wr_PCode(c) ; wr_UInt32(d); }

void rd_PUSH_UINT64(t_pcode *c, t_uint64 *d){ *c = rd_PCode(); *d = rd_UInt64(); }
void wr_PUSH_UINT64(t_pcode c, t_uint64 d){	wr_PCode(c) ; wr_UInt64(d); }
*/

void rd_PUSH_NULL(t_pcode *c){ *c = rd_PCode(); }
void wr_PUSH_NULL(t_pcode c){	wr_PCode(c); }

void rd_PUSH_RETURNVAR(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); }
void wr_PUSH_RETURNVAR(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_EMPTY(t_pcode *c){ *c = rd_PCode(); }
void wr_PUSH_EMPTY(t_pcode c){	wr_PCode(c); }

void rd_PUSH_ERROR(t_pcode *c){ *c = rd_PCode(); }
void wr_PUSH_ERROR(t_pcode c){	wr_PCode(c); }

void rd_PUSH_POINTERPOINTER(t_pcode *c){ *c = rd_PCode(); }
void wr_PUSH_POINTERPOINTER(t_pcode c){	wr_PCode(c); }

void rd_PUSH_BOOLEAN(t_pcode *c, t_boolean *boolean){ *c = rd_PCode(); *boolean = rd_Boolean(); }
void wr_PUSH_BOOLEAN(t_pcode c, t_boolean boolean){	wr_PCode(c) ; wr_Boolean(boolean); }

void rd_PUSH_QSTRING(t_pcode *c, t_integer *string){ *c = rd_PCode(); *string = rd_Integer(); }
void wr_PUSH_QSTRING(t_pcode c, t_integer string){	wr_PCode(c) ; wr_Integer(string); }

void rd_PUSH_CSTRING(t_pcode *c, t_integer *string){ *c = rd_PCode(); *string = rd_Integer(); }
void wr_PUSH_CSTRING(t_pcode c, t_integer string){	wr_PCode(c) ; wr_Integer(string); }


void rd_ARRAY(t_pcode *array, t_integer *indexes_count, t_integer *type, t_integer *identifier, t_scope *scope, t_integer *elementid, t_boolean *bAssignment, t_boolean *bTo){ 
	*array = rd_PCode(); *indexes_count = rd_Integer();  
	*type = rd_Integer(); *identifier = rd_Integer(); 
	*scope = (t_scope) rd_Integer(); *elementid = rd_Integer(); *bAssignment = rd_Boolean(); *bTo = rd_Boolean();
	}

void wr_ARRAY(t_pcode array, t_integer indexes_count, t_integer type, t_integer identifier, t_scope scope, t_integer elementid, t_boolean bAssignment, t_boolean bTo){	
	wr_PCode(array) ; wr_Integer(indexes_count) 
		; wr_Integer(type) ; wr_Integer(identifier) 
		; wr_Integer((t_integer) scope) ; wr_Integer(elementid) ; wr_Boolean(bAssignment) ; wr_Boolean(bTo); }



void rd_REGISTER_ARRAY(t_pcode *register_array, t_integer *indexes_count, t_integer *type, t_integer *identifier, t_scope *scope, t_boolean *bTo, t_integer *nBaseOfArray){ *register_array = rd_PCode(); *indexes_count = rd_Integer();  *type = rd_Integer(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bTo = rd_Boolean(); *nBaseOfArray = rd_Integer(); }
void wr_REGISTER_ARRAY(t_pcode register_array, t_integer indexes_count, t_integer type, t_integer identifier, t_scope scope, t_boolean bTo, t_integer nBaseOfArray){	wr_PCode(register_array) ; wr_Integer(indexes_count) ; wr_Integer(type) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bTo); wr_Integer(nBaseOfArray) ; }




void rd_PUSH_BOOLEAN_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); }
void wr_PUSH_BOOLEAN_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_BYTE_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_BYTE_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_INTEGER_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_INTEGER_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_LONG_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_LONG_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_SINGLE_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_SINGLE_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_DOUBLE_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_DOUBLE_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_QSTRING_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_QSTRING_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_CSTRING_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_CSTRING_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_LQSTRING_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_LQSTRING_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_LCSTRING_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_LCSTRING_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_VARIANT_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_VARIANT_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_CURRENCY_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_CURRENCY_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_DATE_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_DATE_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }
/*
void rd_PUSH_CHARACTER_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_CHARACTER_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }
*/
void rd_PUSH_INT16_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_INT16_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_INT32_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_INT32_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_INT64_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_INT64_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_UINT16_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_UINT16_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_UINT32_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_UINT32_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_UINT64_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_UINT64_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_SHORT_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_SHORT_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_COLLECTION_ID(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_COLLECTION_ID(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }



void rd_PUSH_IDREF(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_IDREF(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_IDREFVAL(t_pcode *c, t_integer *identifier, t_scope *scope, t_integer *nVarType){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *nVarType = rd_Integer();  }
void wr_PUSH_IDREFVAL(t_pcode c, t_integer identifier, t_scope scope, t_integer nVarType){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Integer(nVarType); }


/*
void rd_PUSH_BOOLEAN_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_BOOLEAN_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_BYTE_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_BYTE_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_INTEGER_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_INTEGER_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_LONG_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_LONG_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_SINGLE_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_SINGLE_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_DOUBLE_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_DOUBLE_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_QSTRING_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_QSTRING_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_CSTRING_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_CSTRING_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

//void rd_PUSH_VARIANT_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
//void wr_PUSH_VARIANT_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

//  verschieden pushidpointer werden doch garnicht gebraucht oder? standard pushid langt doch?
//void rd_PUSH_CURRENCY_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
//void wr_PUSH_CURRENCY_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

//void rd_PUSH_DATE_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
//void wr_PUSH_DATE_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

//void rd_PUSH_CHARACTER_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
//void wr_PUSH_CHARACTER_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_INT16_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_INT16_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_INT32_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_INT32_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_INT64_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_INT64_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_UINT16_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_UINT16_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_UINT32_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_UINT32_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_UINT64_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_UINT64_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_PUSH_SHORT_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_SHORT_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

*/

void rd_PUSH_IDPOINTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_PUSH_IDPOINTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }







void rd_MOV_ISMISSING(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_ISMISSING(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }


void rd_MOV_BOOLEAN(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_BOOLEAN(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_BYTE(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_BYTE(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_INTEGER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_INTEGER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_LONG(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_LONG(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_SINGLE(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_SINGLE(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_DOUBLE(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_DOUBLE(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_QSTRING(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_QSTRING(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_CSTRING(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_CSTRING(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_CURRENCY(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_CURRENCY(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_DATE(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_DATE(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }
/*
void rd_MOV_CHARACTER(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_CHARACTER(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }
*/
/*
void rd_MOV_INT16(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_INT16(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_INT32(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_INT32(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_INT64(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_INT64(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_UINT16(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_UINT16(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_UINT32(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_UINT32(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_UINT64(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_UINT64(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }
*/
void rd_MOV_SHORT(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_SHORT(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

/*
void rd_MOV_COLLECTION(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_COLLECTION(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }
*/

void rd_MOV(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_TYPE(t_pcode *c, t_integer *identifier, t_scope *scope, t_boolean *bAllSize, t_integer *size){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bAllSize = rd_Boolean(); *size = rd_Integer();  }
void wr_MOV_TYPE(t_pcode c, t_integer identifier, t_scope scope, t_boolean bAllSize, t_integer size){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bAllSize) ; wr_Integer(size); }

void rd_MOV_CONST(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_CONST(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_ENUM(t_pcode *c, t_integer *identifier, t_integer *element){ *c = rd_PCode(); *identifier = rd_Integer(); *element = rd_Integer();  }
void wr_MOV_ENUM(t_pcode c, t_integer identifier, t_integer element){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer(element); }

void rd_MOV_STRUCTURE(t_pcode *c, t_integer *identifier, t_integer *element){ *c = rd_PCode(); *identifier = rd_Integer(); *element = rd_Integer();  }
void wr_MOV_STRUCTURE(t_pcode c, t_integer identifier, t_integer element){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer(element); }

void rd_MOV_LQSTRING(t_pcode *c, t_integer *identifier, t_scope *scope, t_integer *len){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *len = rd_Integer();  }
void wr_MOV_LQSTRING(t_pcode c, t_integer identifier, t_scope scope, t_integer len){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Integer(len); }

void rd_MOV_RQSTRING(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_RQSTRING(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_LCSTRING(t_pcode *c, t_integer *identifier, t_scope *scope, t_integer *len){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *len = rd_Integer();  }
void wr_MOV_LCSTRING(t_pcode c, t_integer identifier, t_scope scope, t_integer len){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Integer(len); }

void rd_MOV_RCSTRING(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_RCSTRING(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }


void rd_MOV_IDREF(t_pcode *c, t_integer *identifier, t_scope *scope){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_MOV_IDREF(t_pcode c, t_integer identifier, t_scope scope){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_MOV_IDREFVAL(t_pcode *c, t_integer *identifier, t_scope *scope, t_integer *nVarType, t_boolean *bAllSize, t_integer *size){ *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *nVarType = rd_Integer(); *bAllSize = rd_Boolean(); *size = rd_Integer();  }
void wr_MOV_IDREFVAL(t_pcode c, t_integer identifier, t_scope scope, t_integer nVarType, t_boolean bAllSize, t_integer size){	wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Integer(nVarType) ; wr_Boolean(bAllSize) ; wr_Integer(size); }




void rd_DATA(t_pcode *data_, t_integer *count){ *data_ = rd_PCode(); *count = rd_Integer();  }
void wr_DATA(t_pcode data_, t_integer count){ wr_PCode(data_) ; wr_Integer(count); }

void rd_RESTORE(t_pcode *c){ *c = rd_PCode(); }
void wr_RESTORE(t_pcode restore_){ wr_PCode(restore_); }

void rd_READ(t_pcode *read_, t_integer *count){ *read_ = rd_PCode(); *count = rd_Integer();  }
void wr_READ(t_pcode read_, t_integer count){ wr_PCode(read_) ; wr_Integer(count); }


// * operator functions

void rd_XOR(t_pcode *c){ *c = rd_PCode(); }
void wr_XOR(t_pcode xor_){ wr_PCode(xor_); }


void rd_IMP(t_pcode *c){ *c = rd_PCode(); }
void wr_IMP(t_pcode imp_){ wr_PCode(imp_); }


void rd_EQV(t_pcode *c){ *c = rd_PCode(); }
void wr_EQV(t_pcode c){ wr_PCode(c); }


void rd_AND(t_pcode *c){ *c = rd_PCode(); }
void wr_AND(t_pcode and_){ wr_PCode(and_); }


void rd_OR(t_pcode *c){ *c = rd_PCode(); }
void wr_OR(t_pcode or_){ wr_PCode(or_); }


void rd_NOT(t_pcode *c){ *c = rd_PCode(); }
void wr_NOT(t_pcode not_){ wr_PCode(not_); }


void rd_POWER(t_pcode *c){ *c = rd_PCode(); }
void wr_POWER(t_pcode c){ wr_PCode(c); }


void rd_MUL(t_pcode *c){ *c = rd_PCode(); }
void wr_MUL(t_pcode mul){ wr_PCode(mul); }


void rd_DIV(t_pcode *c){ *c = rd_PCode(); }
void wr_DIV(t_pcode div){ wr_PCode(div); }


void rd_LIKE(t_pcode *c){ *c = rd_PCode(); }
void wr_LIKE(t_pcode like){ wr_PCode(like); }


void rd_IDIV(t_pcode *c){ *c = rd_PCode(); }
void wr_IDIV(t_pcode idiv){ wr_PCode(idiv); }


void rd_MOD(t_pcode *c){ *c = rd_PCode(); }
void wr_MOD(t_pcode mod){ wr_PCode(mod); }


void rd_ADD(t_pcode *c){ *c = rd_PCode(); }
void wr_ADD(t_pcode add){ wr_PCode(add); }


void rd_SUB(t_pcode *c){ *c = rd_PCode(); }
void wr_SUB(t_pcode sub){ wr_PCode(sub); }


void rd_SHL(t_pcode *c){ *c = rd_PCode(); }
void wr_SHL(t_pcode c){ wr_PCode(c); }


void rd_SHR(t_pcode *c){ *c = rd_PCode(); }
void wr_SHR(t_pcode c){ wr_PCode(c); }


void rd_INC(t_pcode *c){ *c = rd_PCode(); }
void wr_INC(t_pcode c){ wr_PCode(c); }


void rd_DEC(t_pcode *c){ *c = rd_PCode(); }
void wr_DEC(t_pcode c){ wr_PCode(c); }


void rd_CONNECT(t_pcode *c){ *c = rd_PCode(); }
void wr_CONNECT(t_pcode c){ wr_PCode(c); }

void rd_DISCONNECT(t_pcode *c){ *c = rd_PCode(); }
void wr_DISCONNECT(t_pcode c){ wr_PCode(c); }



void rd_EQUAL(t_pcode *equal, t_boolean *remove){ *equal = rd_PCode(); *remove = rd_Boolean();  }
void wr_EQUAL(t_pcode equal, t_boolean remove){ wr_PCode(equal) ; wr_Boolean(remove); }


void rd_LIKE(t_pcode *like, t_boolean *remove, t_boolean *bOptionCompareBinary){ *like = rd_PCode(); *remove = rd_Boolean(); *bOptionCompareBinary = rd_Boolean();  }
void wr_LIKE(t_pcode like, t_boolean remove, t_boolean bOptionCompareBinary){ wr_PCode(like) ; wr_Boolean(remove); wr_Boolean(bOptionCompareBinary); }


void rd_IS(t_pcode *is, t_boolean *remove){ *is = rd_PCode(); *remove = rd_Boolean();  }
void wr_IS(t_pcode is, t_boolean remove){ wr_PCode(is) ; wr_Boolean(remove); }


void rd_UNEQUAL(t_pcode *unequal, t_boolean *remove){ *unequal = rd_PCode(); *remove = rd_Boolean();  }
void wr_UNEQUAL(t_pcode unequal, t_boolean remove){ wr_PCode(unequal) ; wr_Boolean(remove); }


void rd_GREATER(t_pcode *greater, t_boolean *remove){ *greater = rd_PCode(); *remove = rd_Boolean();  }
void wr_GREATER(t_pcode greater, t_boolean remove){ wr_PCode(greater) ; wr_Boolean(remove); }


void rd_LESSER(t_pcode *lesser, t_boolean *remove){ *lesser = rd_PCode(); *remove = rd_Boolean();  }
void wr_LESSER(t_pcode lesser, t_boolean remove){ wr_PCode(lesser) ; wr_Boolean(remove); }


void rd_GREATER_EQUAL(t_pcode *greater_equal, t_boolean *remove){ *greater_equal = rd_PCode(); *remove = rd_Boolean();  }
void wr_GREATER_EQUAL(t_pcode greater_equal, t_boolean remove){ wr_PCode(greater_equal) ; wr_Boolean(remove); }


void rd_FOR_GREATER_EQUAL(t_pcode *c, t_boolean *remove){ *c = rd_PCode(); *remove = rd_Boolean();  }
void wr_FOR_GREATER_EQUAL(t_pcode c, t_boolean remove){ wr_PCode(c) ; wr_Boolean(remove); }


void rd_LESSER_EQUAL(t_pcode *lesser_equal, t_boolean *remove){ *lesser_equal = rd_PCode(); *remove = rd_Boolean();  }
void wr_LESSER_EQUAL(t_pcode lesser_equal, t_boolean remove){ wr_PCode(lesser_equal) ; wr_Boolean(remove); }




void rd_KBASIC(t_pcode *kbasic, char *magic, t_cstring *projectname, t_cstring *projecttype, t_cstring *login){ *kbasic = rd_PCode(); magic[0] = rd_Char(); magic[1] = rd_Char(); magic[2] = rd_Char(); magic[3] = rd_Char(); magic[4] = rd_Char(); magic[5] = rd_Char(); *projectname = rd_CString(); *projecttype = rd_CString(); *login = rd_CString(); }
void wr_KBASIC(t_pcode kbasic, const char magic[6], t_cstring projectname, t_cstring projecttype, t_cstring login){	wr_PCode(pcode__KBASIC) ; wr_Char(magic[0]) ; wr_Char(magic[1]) ; wr_Char(magic[2]) ; wr_Char(magic[3]) ; wr_Char(magic[4]) ; wr_Char(magic[5]); wr_CString(projectname); wr_CString(projecttype); wr_CString(login); }

void rd_VER(t_pcode *ver, t_single *version){ *ver = rd_PCode(); *version = rd_Single();  }
void wr_VER(t_pcode ver, t_single version){ wr_PCode(ver) ; wr_Single(version); }

void rd_JMP(t_pcode *jmp, t_integer *new_pc){ *jmp = rd_PCode(); *new_pc = rd_Integer();  }
void wr_JMP(t_pcode jmp, t_integer new_pc){ wr_PCode(jmp) ; wr_Integer(new_pc); }

void rd_ONERRORGOTO(t_pcode *onerrorgoto, t_integer *new_pc){ *onerrorgoto = rd_PCode(); *new_pc = rd_Integer();  }
void wr_ONERRORGOTO(t_pcode onerrorgoto, t_integer new_pc){ wr_PCode(onerrorgoto) ; wr_Integer(new_pc); }

void rd_ONERRORGOTORESUMENEXT(t_pcode *c){ *c = rd_PCode(); }
void wr_ONERRORGOTORESUMENEXT(t_pcode onerrorgotoresumenext){ wr_PCode(onerrorgotoresumenext); }

void rd_RESUME(t_pcode *resume, t_integer *new_pc){ *resume = rd_PCode(); *new_pc = rd_Integer();  }
void wr_RESUME(t_pcode resume, t_integer new_pc){ wr_PCode(resume) ; wr_Integer(new_pc); }


void rd_STATEMENT(t_pcode *statement, t_integer *new_pc, t_integer *new_pc2, t_cstring *s, t_integer *line){ *statement = rd_PCode(); *new_pc = rd_Integer(); *new_pc2 = rd_Integer(); *s = rd_CString(); *line = rd_Integer();  }
void wr_STATEMENT(t_pcode statement, t_integer new_pc, t_integer new_pc2, t_cstring s, t_integer line){ wr_PCode(statement) ; wr_Integer(new_pc) ; wr_Integer(new_pc2) ; wr_CString(s) ; wr_Integer(line); }

void rd_STATEMENT_OUT(t_pcode *statement, t_cstring *s, t_integer *line){ *statement = rd_PCode(); *s = rd_CString(); *line = rd_Integer();  }
void wr_STATEMENT_OUT(t_pcode statement, t_cstring s, t_integer line){ wr_PCode(statement) ; wr_CString(s) ; wr_Integer(line); }

void rd_STATEMENT_OVER(t_pcode *statement, t_cstring *s, t_integer *line){ *statement = rd_PCode(); *s = rd_CString(); *line = rd_Integer();  }
void wr_STATEMENT_OVER(t_pcode statement, t_cstring s, t_integer line){ wr_PCode(statement) ; wr_CString(s) ; wr_Integer(line); }

void rd_STATEMENT_CURSOR(t_pcode *statement, t_cstring *s, t_integer *line){ *statement = rd_PCode(); *s = rd_CString(); *line = rd_Integer();  }
void wr_STATEMENT_CURSOR(t_pcode statement, t_cstring s, t_integer line){ wr_PCode(statement) ; wr_CString(s) ; wr_Integer(line); }



void rd_DIM(t_pcode *dim, t_integer *identifier, t_scope *scope, t_integer *type, t_boolean *_new, t_boolean *bReference, t_boolean *bArray, t_boolean *bStatic, t_integer *nLStringLen, t_integer *parent_type, t_cstring *varname, t_boolean *globalform){ *dim = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *type = rd_Integer(); *_new = rd_Boolean(); *bReference = rd_Boolean(); *bArray = rd_Boolean(); *bStatic = rd_Boolean(); *nLStringLen = rd_Integer(); *parent_type = rd_Integer(); *varname = rd_CString();  *globalform = rd_Boolean();  }
void wr_DIM(t_pcode dim, t_integer identifier, t_scope scope, t_integer type, t_boolean _new, t_boolean bReference, t_boolean bArray, t_boolean bStatic, t_integer nLStringLen, t_integer parent_type, t_cstring varname, t_boolean globalform){ 
  wr_PCode(dim) ; wr_Integer(identifier) ; 
  wr_Integer((t_integer) scope) ; wr_Integer(type) ; wr_Boolean(_new) ; wr_Boolean(bReference) ; wr_Boolean(bArray) ; wr_Boolean(bStatic) ; wr_Integer(nLStringLen);  wr_Integer(parent_type);   wr_CString(varname);   wr_Boolean(globalform); 
}

void rd_REDIM(t_pcode *redim, t_integer *identifier, t_scope *scope, t_boolean *preserve){ *redim = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *preserve = rd_Boolean();  }
void wr_REDIM(t_pcode redim, t_integer identifier, t_scope scope, t_boolean preserve){ wr_PCode(redim) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(preserve); }



void rd_CONST(t_pcode *const_, t_integer *identifier, t_scope *scope){ *const_ = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer();  }
void wr_CONST(t_pcode const_, t_integer identifier, t_scope scope){ wr_PCode(const_) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope); }

void rd_STRING_LITERAL(t_pcode *dim_static, t_cstring *value, t_integer *reference){ *dim_static = rd_PCode(); *value = rd_CString(); *reference = rd_Integer();  }
void wr_STRING_LITERAL(t_pcode dim_static, t_cstring value, t_integer reference){ wr_PCode(dim_static) ; wr_CString(value) ; wr_Integer(reference); }

// ***

void rd_CLASS(t_pcode *c, t_integer *identifier, t_cstring *name, t_integer *method_count, t_integer *propertyget_count, t_integer *propertyset_count, t_integer *pc_pos, t_integer *pc_len, t_integer *nExtend, t_integer *destructor_id)
{ *c = rd_PCode(); *identifier = rd_Integer(); *name = rd_CString(); *method_count = rd_Integer(); *propertyget_count = rd_Integer(); *propertyset_count = rd_Integer(); *pc_pos = rd_Integer(); *pc_len = rd_Integer(); *nExtend = rd_Integer(); *destructor_id = rd_Integer();
 }

void wr_CLASS(t_pcode c, t_integer identifier, t_cstring name, t_integer method_count, t_integer propertyget_count, t_integer propertyset_count, t_integer pc_pos, t_integer pc_len, t_integer nExtend, t_integer destructor_id){ 
	wr_PCode(c) ; wr_Integer(identifier) ; wr_CString(name) ; wr_Integer(method_count) ; wr_Integer(propertyget_count) ; wr_Integer(propertyset_count) ; wr_Integer(pc_pos) ; wr_Integer(pc_len) ; wr_Integer(nExtend) ; wr_Integer(destructor_id); }

void rd_CLASS_METHOD(t_pcode *c, t_integer *class_identifier, t_integer *identifier, t_cstring *realname, t_cstring *name, t_integer *param_count, t_integer *return_type, t_integer *pc_pos, t_integer *pc_len)
{ *c = rd_PCode(); *class_identifier = rd_Integer(); *identifier = rd_Integer(); *realname = rd_CString(); *name = rd_CString(); *param_count = rd_Integer(); *return_type = rd_Integer(); *pc_pos = rd_Integer(); *pc_len = rd_Integer();
 }

void wr_CLASS_METHOD(t_pcode c, t_integer class_identifier, t_integer identifier, t_cstring realname, t_cstring name, t_integer param_count, t_integer return_type, t_integer pc_pos, t_integer pc_len){ 
	wr_PCode(c) ; wr_Integer(class_identifier) ; wr_Integer(identifier) ; wr_CString(realname) ; wr_CString(name) ; wr_Integer(param_count) ; wr_Integer(return_type) ; wr_Integer(pc_pos) ; wr_Integer(pc_len); }
// ***


void rd_LBOUND(t_pcode *lbound, t_integer *identifier, t_scope *scope, t_boolean *expression, t_boolean *bReturn){ *lbound = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *expression = rd_Boolean(); *bReturn = rd_Boolean();  }
void wr_LBOUND(t_pcode lbound, t_integer identifier, t_scope scope, t_boolean expression, t_boolean bReturn){ wr_PCode(lbound) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(expression) ; wr_Boolean(bReturn); }

void rd_UBOUND(t_pcode *ubound, t_integer *identifier, t_scope *scope, t_boolean *expression, t_boolean *bReturn){ *ubound = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *expression = rd_Boolean(); *bReturn = rd_Boolean();  }
void wr_UBOUND(t_pcode ubound, t_integer identifier, t_scope scope, t_boolean expression, t_boolean bReturn){ wr_PCode(ubound) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(expression) ; wr_Boolean(bReturn); }

void rd_TRY(t_pcode *c){ *c = rd_PCode();    }
void wr_TRY(t_pcode c){ wr_PCode(c) ; }

void rd_ENDCATCH(t_pcode *c){ *c = rd_PCode();    }
void wr_ENDCATCH(t_pcode c){ wr_PCode(c) ; }


void rd_ERL(t_pcode *erl, t_boolean *bReturn){ *erl = rd_PCode(); *bReturn = rd_Boolean();   }
void wr_ERL(t_pcode erl, t_boolean bReturn){ wr_PCode(erl) ; wr_Boolean(bReturn); }

void rd_ERR(t_pcode *err, t_boolean *bReturn){ *err = rd_PCode(); *bReturn = rd_Boolean();   }
void wr_ERR(t_pcode err, t_boolean bReturn){ wr_PCode(err) ; wr_Boolean(bReturn); }

void rd_ERROR(t_pcode *c, t_boolean *bErrorNo){ *c = rd_PCode(); *bErrorNo = rd_Boolean();  }
void wr_ERROR(t_pcode c, t_boolean bErrorNo){ wr_PCode(c) ; wr_Boolean(bErrorNo); }

void rd_FILEDATETIME(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_FILEDATETIME(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_FILEATTR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_FILEATTR(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }




// builtin functions
void rd_UTF8(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_UTF8(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_UTF16(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_UTF16(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ABS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_ABS(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_ACS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_ACS(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_ASC(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_ASC(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_ASN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_ASN(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_ATN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_ATN(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_BEEP(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); } 		void wr_BEEP(t_builtin c){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }
void rd_BIN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_BIN(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_CHDIR(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); } 		void wr_CHDIR(t_builtin c){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }
void rd_CHR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_CHR(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_CINT(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_CINT(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_CLNG(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_CLNG(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_CLOSE(t_builtin *c, t_integer *nCount){ 
 t_pcode builtin = rd_PCode(); *c = rd_PCode(); *nCount = rd_Integer(); } 		

void wr_CLOSE(t_builtin c, t_integer nCount){ 
	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(nCount); }

void rd_CLOSEALL(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_Integer(); } 		
void wr_CLOSEALL(t_builtin c){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_CLS(t_builtin *c, t_boolean *bEXPRESSION){ t_pcode builtin = rd_PCode(); *c = rd_Integer(); *bEXPRESSION = rd_Boolean(); } 		
void wr_CLS(t_builtin c, t_boolean bEXPRESSION){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION); }

void rd_COLOR(t_builtin *c, t_boolean *bFORE, t_boolean *bBACK){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bFORE = rd_Boolean(); *bBACK = rd_Boolean(); }
void wr_COLOR(t_builtin c, t_boolean bFORE, t_boolean bBACK){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bFORE) ; wr_Boolean(bBACK); }

void rd_COS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_COS(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_CSRLIN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_CSRLIN(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_DATE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_DATE(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_DATE2(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_DATE2(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_DEG(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_DEG(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_DOF(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_DOF(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_EOF(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_EOF(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_EXP(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_EXP(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_FACT(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_FACT(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_FIX(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_FIX(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_FILES(t_builtin *c, t_boolean *bDirectory, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bDirectory = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_FILES(t_builtin c, t_boolean bDirectory, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bDirectory); wr_Boolean(bReturn);  }

void rd_FRAC(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_FRAC(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_HEX(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_HEX(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_HYPOT(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_HYPOT(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_INPUT(t_builtin *c, t_boolean *bEXPRESSION0, t_boolean *bSEMICOL, t_boolean *bSTRING_EXPRESSION, t_boolean *bCOMMA, t_boolean *bSEMICOL2, t_integer *nID, t_scope *scope, t_integer *nType, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bEXPRESSION0 = rd_Boolean(); *bSEMICOL = rd_Boolean(); *bSTRING_EXPRESSION = rd_Boolean(); *bCOMMA = rd_Boolean(); *bSEMICOL2 = rd_Boolean(); *nID = rd_Integer(); *scope = (t_scope) rd_Integer(); *nType = rd_Integer(); *bReturn = rd_Boolean(); }
void wr_INPUT(t_builtin c, t_boolean bEXPRESSION0, t_boolean bSEMICOL, t_boolean bSTRING_EXPRESSION, t_boolean bCOMMA, t_boolean bSEMICOL2, t_integer nID, t_scope scope, t_integer nType, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bEXPRESSION0) ; wr_Boolean(bSEMICOL) ; wr_Boolean(bSTRING_EXPRESSION) ; wr_Boolean(bCOMMA) ; wr_Boolean(bSEMICOL2) ; wr_Integer(nID) ; wr_Integer((t_integer) scope) ; wr_Integer(nType) ; wr_Boolean(bReturn); }

void rd_INPUT2(t_builtin *c, t_boolean *bFIRST, t_integer *identifier, t_scope *scope, t_integer *count, t_boolean *bReturn)
{ 
  t_pcode builtin = rd_PCode(); 

  *c = rd_PCode(); 
  *bFIRST = rd_Boolean(); 
  *identifier = rd_Integer(); 
  *scope = (t_scope) rd_Integer(); 
  *count = rd_Integer(); 
  *bReturn = rd_Boolean();   
} 		

void wr_INPUT2(t_builtin c, t_boolean bFIRST, t_integer identifier, t_scope scope, t_integer count, t_boolean bReturn)
{ 
wr_PCode(pcode__BUILTIN) 

  ; wr_PCode(c)
  ; wr_Boolean(bFIRST) 
  ; wr_Integer(identifier) 
  ; wr_Integer((t_integer) scope) 
  ; wr_Integer(count) 
  ; wr_Boolean(bReturn); 
}

void rd_INKEY(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_INKEY(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_INSTR(t_builtin *c, t_boolean *bBegin, t_boolean *bIndexOf, t_boolean *bCase, t_boolean *bReturn, t_boolean *bObjectFake){ t_pcode builtin = rd_PCode();  *c = rd_Integer(); *bBegin = rd_Boolean(); *bIndexOf = rd_Boolean(); *bCase = rd_Boolean(); *bReturn = rd_Boolean(); *bObjectFake = rd_Boolean(); }
void wr_INSTR(t_builtin c, t_boolean bBegin, t_boolean bIndexOf, t_boolean bCase, t_boolean bReturn, t_boolean bObjectFake){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bBegin) ; wr_Boolean(bIndexOf) ;wr_Boolean(bCase) ; wr_Boolean(bReturn) ; wr_Boolean(bObjectFake); }

void rd_INT(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_INT(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_KILL(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); } 		void wr_KILL(t_builtin c){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }
void rd_LCASE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_LCASE(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_LEFT(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_LEFT(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_ENCODE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_ENCODE(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_DECODE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_DECODE(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_LEN(t_builtin *c, t_boolean *bSTRING_EXPRESSION, t_boolean *bReturn){ 
  t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bSTRING_EXPRESSION = rd_Boolean(); *bReturn = rd_Boolean(); } 		

void wr_LEN(t_builtin c, t_boolean bSTRING_EXPRESSION, t_boolean bReturn){ 
  wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bSTRING_EXPRESSION) ; wr_Boolean(bReturn); }

void rd_LN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_LN(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_LOCATE(t_builtin *c, t_boolean *bY, t_boolean *bX, t_boolean *bCursor){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bY = rd_Boolean(); *bX = rd_Boolean(); *bCursor = rd_Boolean(); }
void wr_LOCATE(t_builtin c, t_boolean bY, t_boolean bX, t_boolean bCursor){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bY) ; wr_Boolean(bX) ; wr_Boolean(bCursor); }

void rd_LOF(t_builtin *c, t_boolean *bReturn){ 
 t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		

void wr_LOF(t_builtin c, t_boolean bReturn){ 
	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_LOG(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_LOG(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_LOGB(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_LOGB(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_LTRIM(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_LTRIM(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_MAX(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_MAX(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }


void rd_STRCOMP(t_builtin *c, t_boolean *bMode, t_boolean *bOptionCompareBinary, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bMode = rd_Boolean(); *bOptionCompareBinary = rd_Boolean(); *bReturn = rd_Boolean(); }
void wr_STRCOMP(t_builtin c, t_boolean bMode, t_boolean bOptionCompareBinary, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bMode) ; wr_Boolean(bOptionCompareBinary) ; wr_Boolean(bReturn); }


void rd_SCREEN(t_builtin *c, t_boolean *bColor, t_boolean *bOutputpage, t_boolean *bVisiblepage){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bColor = rd_Boolean(); *bOutputpage = rd_Boolean(); *bVisiblepage = rd_Boolean(); }
void wr_SCREEN(t_builtin c, t_boolean bColor, t_boolean bOutputpage, t_boolean bVisiblepage){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bColor) ; wr_Boolean(bOutputpage) ; wr_Boolean(bVisiblepage); }


void rd_MID(t_builtin *c, t_boolean *bReturn, t_boolean *bLen){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); *bLen = rd_Boolean(); }
void wr_MID(t_builtin c, t_boolean bReturn, t_boolean bLen){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn) ; wr_Boolean(bLen); }

void rd_MID2(t_builtin *c, t_integer *identifier, t_scope *scope,  t_boolean *bLen){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *identifier = rd_Integer(); *scope = (t_scope) rd_Integer(); *bLen = rd_Boolean(); }
void wr_MID2(t_builtin c, t_integer identifier, t_scope scope, t_boolean bLen){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(identifier) ; wr_Integer((t_integer) scope) ; wr_Boolean(bLen); }

void rd_MIN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_MIN(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_MKDIR(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); } 		void wr_MKDIR(t_builtin c){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }
void rd_NAME(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); } 		void wr_NAME(t_builtin c){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }
void rd_OCT(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_OCT(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_OPEN(t_builtin *c, t_integer *nMode, t_integer *nLock, t_integer *nAccess, t_boolean *bLEN){ 
	t_pcode builtin = rd_PCode(); *c = rd_PCode(); *nMode = rd_Integer(); *nLock = rd_Integer(); *nAccess = rd_Integer(); *bLEN = rd_Boolean(); } 		

void wr_OPEN(t_builtin c, t_integer nMode, t_integer nLock, t_integer nAccess, t_boolean bLEN){
	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(nMode) ; wr_Integer(nLock) ; wr_Integer(nAccess) ; wr_Boolean(bLEN); }

void rd_OPEN2(t_builtin *c, t_boolean *bLEN){ 
	t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bLEN = rd_Boolean(); } 		

void wr_OPEN2(t_builtin c, t_boolean bLEN){
	wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bLEN); }

void rd_POS(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_POS(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_PRINT(t_builtin *c, t_boolean *bFIRST, t_boolean *bFILEHANDLE, t_boolean *bUSING, t_boolean *bEXPRESSION, t_boolean *bSPC, t_boolean *bTAB, t_boolean *bCOMMA, t_boolean *bSEMICOL, t_boolean *bEcho, t_boolean *bLog){ 
t_pcode builtin = rd_PCode(); 
*c = rd_PCode(); 
*bFIRST = rd_Boolean(); 
*bFILEHANDLE = rd_Boolean(); 
*bUSING = rd_Boolean(); 
*bEXPRESSION = rd_Boolean(); 
*bSPC = rd_Boolean(); 
*bTAB = rd_Boolean(); 
*bCOMMA = rd_Boolean(); 
*bSEMICOL = rd_Boolean(); 
*bEcho = rd_Boolean(); 
*bLog = rd_Boolean(); 
}

void wr_PRINT(t_builtin c, t_boolean bFIRST, t_boolean bFILEHANDLE, t_boolean bUSING, t_boolean bEXPRESSION, t_boolean bSPC, t_boolean bTAB, t_boolean bCOMMA, t_boolean bSEMICOL, t_boolean bEcho, t_boolean bLog){ 
  wr_PCode(pcode__BUILTIN) ; wr_PCode(c) 
    ; wr_Boolean(bFIRST) ; wr_Boolean(bFILEHANDLE) ; wr_Boolean(bUSING) 
    ; wr_Boolean(bEXPRESSION) ; wr_Boolean(bSPC) 
    ; wr_Boolean(bTAB) ; wr_Boolean(bCOMMA) ; wr_Boolean(bSEMICOL) ; wr_Boolean(bEcho) ; wr_Boolean(bLog); }

void rd_RAD(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_RAD(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_RANDOMIZE(t_builtin *c, t_boolean *bExpression, t_boolean *bAuto){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bExpression = rd_Boolean(); *bAuto = rd_Boolean(); } 		void wr_RANDOMIZE(t_builtin c, t_boolean bExpression, t_boolean bAuto){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bExpression); wr_Boolean(bAuto); }

void rd_READ2(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_READ2(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_RESET(t_builtin *c){ t_pcode builtin = rd_PCode(); } 		void wr_RESET(t_builtin c){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }
void rd_RIGHT(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_RIGHT(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_RMDIR(t_builtin *c){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); } 		void wr_RMDIR(t_builtin c){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c); }

void rd_RND(t_builtin *c, t_boolean *bReturn, t_boolean *bExpression){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); *bExpression = rd_Char(); }
void wr_RND(t_builtin c, t_boolean bReturn, t_boolean bExpression){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn) ; wr_Boolean(bExpression); }

void rd_RTRIM(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_RTRIM(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_SEC(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_SEC(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_SEEK(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_SEEK(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_SEEK2(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_SEEK2(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_SGN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_SGN(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_SIN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_SIN(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_SLEEP(t_builtin *c, t_boolean *bExpression){ t_pcode builtin = rd_PCode(); *c = rd_Integer(); *bExpression = rd_Boolean(); } 		
void wr_SLEEP(t_builtin c, t_boolean bExpression){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bExpression); }

void rd_FILECOPY(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_Integer(); *bReturn = rd_Boolean();  }
void wr_FILECOPY(t_builtin c, t_boolean bReturn){	wr_PCode(pcode__BUILTIN) ; wr_PCode(c);wr_Boolean(bReturn); }

void rd_SHELL(t_builtin *c, t_boolean *bCommand, t_boolean *bSynchron, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bCommand = rd_Boolean() ;*bSynchron = rd_Boolean() ; *bReturn = rd_Boolean(); }
void wr_SHELL(t_builtin c, t_boolean bCommand, t_boolean bSynchron, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bCommand); wr_Boolean(bSynchron); wr_Boolean(bReturn); }

void rd_CAST(t_builtin *c, t_integer *nType, t_integer *nType2, t_boolean *bEXPRESSION, t_boolean *bEXPRESSION2, t_boolean *bEXPRESSION3, t_boolean *bEXPRESSION4, t_boolean *bEXPRESSION5, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *nType = rd_Integer(); *nType2 = rd_Integer() ;*bEXPRESSION = rd_Boolean() ; *bEXPRESSION2 = rd_Boolean() ; *bEXPRESSION3 = rd_Boolean() ; *bEXPRESSION4 = rd_Boolean() ; *bEXPRESSION5 = rd_Boolean() ; *bReturn = rd_Boolean(); }
void wr_CAST(t_builtin c, t_integer nType, t_integer nType2, t_boolean bEXPRESSION, t_boolean bEXPRESSION2, t_boolean bEXPRESSION3, t_boolean bEXPRESSION4, t_boolean bEXPRESSION5, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Integer(nType); wr_Integer(nType2);  wr_Boolean(bEXPRESSION); wr_Boolean(bEXPRESSION2); wr_Boolean(bEXPRESSION3); wr_Boolean(bEXPRESSION4); wr_Boolean(bEXPRESSION5); wr_Boolean(bReturn); }

void rd_SPACE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_SPACE(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_SQR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_SQR(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_STR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_STR(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_STRING2(t_builtin *c, t_boolean *bReturn, t_boolean *bAscii, t_boolean *bString){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); *bAscii = rd_Char(); *bString = rd_Char(); }
void wr_STRING2(t_builtin c, t_boolean bReturn, t_boolean bAscii, t_boolean bString){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn) ; wr_Boolean(bAscii) ; wr_Boolean(bString); }

void rd_KBASICDIR(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); }
void wr_KBASICDIR(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn) ; }

void rd_TAN(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_TAN(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_TIME(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_TIME(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_TRIM(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_TRIM(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_UCASE(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_UCASE(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }
void rd_VAL(t_builtin *c, t_boolean *bReturn){ t_pcode builtin = rd_PCode(); *c = rd_PCode(); *bReturn = rd_Boolean(); } 		void wr_VAL(t_builtin c, t_boolean bReturn){ wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(bReturn); }

void rd_WRITE(t_builtin *c, t_boolean *fileno, t_integer *expression_count){ 
  t_pcode builtin = rd_PCode(); *c = rd_PCode(); *fileno = rd_Boolean(); *expression_count = rd_Integer();
 } 		

void wr_WRITE(t_builtin c, t_boolean fileno, t_integer expression_count){ 
  wr_PCode(pcode__BUILTIN) ; wr_PCode(c) ; wr_Boolean(fileno) ; wr_Integer(expression_count); }


void rd_binding_ClassMethod(t_pcode *cc, t_integer *c, t_boolean *bReturn){ 
	*cc = rd_PCode(); 
	*c = rd_Integer(); 
	*bReturn = rd_Boolean(); 
	 
} 		

void wr_binding_ClassMethod(t_pcode cc, t_integer c, t_boolean bReturn){ 
	wr_PCode(cc) ; wr_Integer(c) ; wr_Boolean(bReturn); }



void rd_binding_ClassProperty(t_pcode *cc, t_integer *c, t_boolean *bReturn){ 
	*cc = rd_PCode(); 
	*c = rd_Integer(); 
	*bReturn = rd_Boolean(); 
	 
} 		

void wr_binding_ClassProperty(t_pcode cc, t_integer c, t_boolean bReturn){ 
	wr_PCode(cc) ; wr_Integer(c) ; wr_Boolean(bReturn); }


void rd_binding_ClassStaticProperty(t_pcode *cc, t_integer *c, t_boolean *bReturn){ 
	*cc = rd_PCode(); 
	*c = rd_Integer(); 
	*bReturn = rd_Boolean(); 
	 
} 		

void wr_binding_ClassStaticProperty(t_pcode cc, t_integer c, t_boolean bReturn){ 
	wr_PCode(cc) ; wr_Integer(c) ; wr_Boolean(bReturn); }



void rd_binding_Function(t_pcode *cc, t_integer *c, t_boolean *bReturn){ 
	*cc = rd_PCode(); 
	*c = rd_Integer(); 
	*bReturn = rd_Boolean(); 
	 
} 		

void wr_binding_Function(t_pcode cc, t_integer c, t_boolean bReturn){ 
	wr_PCode(cc) ; wr_Integer(c) ; wr_Boolean(bReturn); }


void rd_binding_ClassOperator(t_pcode *cc, t_integer *c){ 
	*cc = rd_PCode(); 
	*c = rd_Integer(); 
	 
} 		

void wr_binding_ClassOperator(t_pcode cc, t_integer c){ 
	wr_PCode(cc) ; wr_Integer(c); }


void rd_binding_FunctionOperator(t_pcode *cc, t_integer *c){ 
	*cc = rd_PCode(); 
	*c = rd_Integer(); 
	 
} 		

void wr_binding_FunctionOperator(t_pcode cc, t_integer c){ 
	wr_PCode(cc) ; wr_Integer(c); }


void rd_binding_ClassStaticMethod(t_pcode *cc, t_integer *c, t_boolean *bReturn){ 
	*cc = rd_PCode(); 
	*c = rd_Integer(); 
	*bReturn = rd_Boolean(); 
	 
} 		

void wr_binding_ClassStaticMethod(t_pcode cc, t_integer c, t_boolean bReturn){ 
	cc = pcode__binding_CLASSSTATICMETHOD;
	wr_PCode(cc) ; wr_Integer(c) ; wr_Boolean(bReturn); }




void rd_ClassMethod(t_pcode *cc, t_integer *classid, t_integer *c, t_cstring *signature, t_boolean *bConstructor, t_boolean *bDestructor, t_boolean *bParent, t_boolean *bReturn){ 
	*cc = rd_PCode(); 
	*classid = rd_Integer(); 
	*c = rd_Integer(); 
	*signature = rd_CString(); 
	*bConstructor = rd_Boolean(); 
	*bDestructor = rd_Boolean(); 
	*bParent = rd_Boolean(); 
	*bReturn = rd_Boolean(); 
	 
} 		

void wr_ClassMethod(t_pcode cc, t_integer classid, t_integer c, t_cstring signature, t_boolean bConstructor, t_boolean bDestructor, t_boolean bParent, t_boolean bReturn){ 
	wr_PCode(cc) ; wr_Integer(classid) ; wr_Integer(c) 
    ; wr_CString(signature) ; wr_Boolean(bConstructor) 
    ; wr_Boolean(bDestructor) ; wr_Boolean(bParent) ; wr_Boolean(bReturn); }



void rd_ClassPropertyGet(t_pcode *cc, t_integer *classid, t_integer *c, t_cstring *signature, t_boolean *bConstructor, t_boolean *bDestructor, t_boolean *bParent, t_boolean *bReturn){ 
	*cc = rd_PCode(); 
	*classid = rd_Integer(); 
	*c = rd_Integer(); 
	*signature = rd_CString(); 
	*bConstructor = rd_Boolean(); 
	*bDestructor = rd_Boolean(); 
	*bParent = rd_Boolean(); 
	*bReturn = rd_Boolean(); 
	 
} 		

void wr_ClassPropertyGet(t_pcode cc, t_integer classid, t_integer c, t_cstring signature, t_boolean bConstructor, t_boolean bDestructor, t_boolean bParent, t_boolean bReturn){ 
	wr_PCode(cc) ; wr_Integer(classid) ; wr_Integer(c) 
    ; wr_CString(signature) ; wr_Boolean(bConstructor) 
    ; wr_Boolean(bDestructor) ; wr_Boolean(bParent) ; wr_Boolean(bReturn); }


void rd_ClassPropertySet(t_pcode *cc, t_integer *classid, t_integer *c, t_cstring *signature, t_boolean *bConstructor, t_boolean *bDestructor, t_boolean *bParent, t_boolean *bReturn){ 
	*cc = rd_PCode(); 
	*classid = rd_Integer(); 
	*c = rd_Integer(); 
	*signature = rd_CString(); 
	*bConstructor = rd_Boolean(); 
	*bDestructor = rd_Boolean(); 
	*bParent = rd_Boolean(); 
	*bReturn = rd_Boolean(); 
	 
} 		

void wr_ClassPropertySet(t_pcode cc, t_integer classid, t_integer c, t_cstring signature, t_boolean bConstructor, t_boolean bDestructor, t_boolean bParent, t_boolean bReturn){ 
	wr_PCode(cc) ; wr_Integer(classid) ; wr_Integer(c) 
    ; wr_CString(signature) ; wr_Boolean(bConstructor) 
    ; wr_Boolean(bDestructor) ; wr_Boolean(bParent) ; wr_Boolean(bReturn); }



void rd_CLASS_BINDINGPARAM(t_pcode *cc, t_integer *classid, t_cstring *classmethodno, t_integer *no, t_integer *identifier){ 
	*cc = rd_PCode(); 
	*classid = rd_Integer(); 
	*classmethodno = rd_CString(); 
	*no = rd_Integer(); 
	*identifier = rd_Integer(); 

	 
} 		

void wr_CLASS_BINDINGPARAM(t_pcode cc, t_integer classid, t_cstring classmethodno, t_integer no, t_integer identifier){ 
	wr_PCode(cc) ; wr_Integer(classid)
    ; wr_CString(classmethodno) ; wr_Integer(no) ; wr_Integer(identifier); }



void rd_TRANSLATION(t_pcode *cc, t_cstring *s){ 
	*cc = rd_PCode(); 
	*s = rd_CString(); 
} 		

void wr_TRANSLATION(t_pcode cc, t_cstring s){ 
	wr_PCode(cc) ;
    ; wr_CString(s) ; 

}

t_cstring encode(t_cstring s);
t_cstring decode(t_cstring s);

void rd_SQL(t_pcode *cc, t_cstring *s){ 
	*cc = rd_PCode(); 
	*s = decode(rd_CString()); 
} 		

void wr_SQL(t_pcode cc, t_cstring s){ 
	wr_PCode(cc) ;  
    ; wr_CString(encode(s)) ; 

}

void rd_MENU(t_pcode *cc, t_cstring *s){ 
	*cc = rd_PCode(); 
	*s = rd_CString(); 
} 		

void wr_MENU(t_pcode cc, t_cstring s){ 
	wr_PCode(cc) ;  
    ; wr_CString(s) ; 

}

void wr_BREAKPOINT(t_pcode cc, t_cstring file, t_integer line){ 
	wr_PCode(cc) ; ; wr_CString(file) ; wr_Integer(line); }


void rd_BREAKPOINT(t_pcode *cc, t_cstring *file, t_integer *line){ 
	*cc = rd_PCode(); 
	*file = rd_CString(); 
	*line = rd_Integer();  
}



void rd_ProjectFile(t_pcode *cc, t_cstring *path, t_cstring *filename, t_integer *filesize, t_pointer *data)
{ 
	*cc = rd_PCode(); 
	*path = rd_CString(); 
	*filename = rd_CString(); 
	*filesize = rd_Integer(); 
	*data = rd_Struct2(*filesize); 
	 
} 		

void wr_ProjectFile(t_pcode cc, t_cstring path, t_cstring filename, t_integer filesize, t_pointer data)
{ 
	wr_PCode(cc) ; wr_CString(path) ; wr_CString(filename)  ; wr_Integer(filesize) 
    ; wr_Struct(filesize, data)
    ; 
}



void rd_ClassStaticMethod(t_pcode *cc, t_integer *classid, t_integer *c, t_boolean *bReturn){ 
	*cc = rd_PCode(); 
	*classid = rd_Integer(); 
	*c = rd_Integer(); 
	*bReturn = rd_Boolean(); 
	 
} 		

void wr_ClassStaticMethod(t_pcode cc, t_integer classid, t_integer c, t_boolean bReturn){ 
	wr_PCode(cc) ; wr_Integer(classid) ; wr_Integer(c) ; wr_Boolean(bReturn); }




void wr_BYTE(t_byte C)
{
	(ba->wr_PCode(pcode__BYTE));
	(ba->wr_Byte(C));

}

void wr_CURRENCY(t_currency c)
{
	(ba->wr_PCode(pcode__CURRENCY));
	(ba->wr_Currency(c));

}

void wr_DATE(t_date d)
{
	(ba->wr_PCode(pcode__DATE));
	(ba->wr_Date(d));

}
/*
void wr_CHARACTER(t_character d)
{
	(ba->wr_PCode(pcode__CHARACTER));
	(ba->wr_Character(d));

}*/
/*
void wr_INT16(t_int16 d)
{
	 (ba->wr_PCode(pcode__INT16));
	 (ba->wr_Int16(d));

}

void wr_INT32(t_int32 d)
{
	 (ba->wr_PCode(pcode__INT32));
	 (ba->wr_Int32(d));

}

void wr_INT64(t_int64 d)
{
	 (ba->wr_PCode(pcode__INT64));
	 (ba->wr_Int64(d));

}

void wr_UINT16(t_uint16 d)
{
	 (ba->wr_PCode(pcode__UINT16));
	 (ba->wr_UInt16(d));
;
}

void wr_UINT32(t_uint32 d)
{
	 (ba->wr_PCode(pcode__UINT32));
	 (ba->wr_UInt32(d));
;
}

void wr_UINT64(t_uint64 d)
{
	 (ba->wr_PCode(pcode__UINT64));
	 (ba->wr_UInt64(d));

}
*/
void wr_BOOLEAN(t_boolean c)
{
	 (ba->wr_PCode(pcode__BOOLEAN));
	 (ba->wr_Boolean(c));

}

void wr_INTEGER(t_integer b)
{
	 (ba->wr_PCode(pcode__INTEGER));
	 (ba->wr_Integer(b));

}

void wr_LONG(t_long l)
{
	 (ba->wr_PCode(pcode__LONG));
	 (ba->wr_Long(l));

}

void wr_CSTRING(t_cstring acValue)
{
	 (ba->wr_PCode(pcode__CSTRING));
	 (ba->wr_CString(acValue));

}

void wr_DOUBLE(t_double d)
{
	 (ba->wr_PCode(pcode__DOUBLE));
	 (ba->wr_Double(d));

}

void wr_SINGLE(t_single c)
{
	 (ba->wr_PCode(pcode__SINGLE));
	 (ba->wr_Single(c));

}

void wr_SHORT(t_short d)
{
	 (ba->wr_PCode(pcode__SHORT));
	 (ba->wr_Short(d));

}

// ****************************
void wr_Integer(t_integer nInt)
{
	 (ba->wr_Integer(nInt));

}

// ****************************
// * void wr_Char(unsigned char cChar)
// *
// * parameter:
// * unsigned unsigned char cChar = the unsigned char to add to the array
// *
// * return:
// * true, if a unsigned char could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_Char(unsigned char cChar)
{
	 (ba->wr_Char(cChar));

}

// ****************************
// * return:
// * true, if a unsigned char could be added to the array okay
// * false, if couldn't get more memory to extend array
// ****************************
void wr_Boolean(t_boolean b)
{
	 (ba->wr_Boolean(b));

}

// ****************************
void wr_Byte(t_byte b)
{
	 (ba->wr_Byte(b));

}

// ****************************
void wr_Currency(t_currency c)
{
	 (ba->wr_Currency(c));

}

// ****************************
void wr_Date(t_date d)
{
	 (ba->wr_Date(d));

}

// ****************************
void wr_Variant(t_variant d)
{
	 (ba->wr_Variant(d));

}

/*
// ****************************
void wr_Character(t_character d)
{
	 (ba->wr_Character(d));

}
*/

// ****************************
void wr_CString(t_cstring acChar)
{
	wr_CString(acChar, strlen(acChar));
}

// ****************************
void wr_CString(t_cstring acChar, int nLen)
{
	 (ba->wr_CString(acChar, nLen));

}

/*
// ****************************
void wr_CString(t_cstring d, int nLen)
{
	 (ba->wr_CString(d, nLen));

}

// ****************************
void wr_CString(t_cstring d)
{
	wr_CString(d, strlen(d));
}
*/
// ****************************
void wr_Single(t_single fSingle)
{
	 (ba->wr_Single(fSingle));

}

// ****************************
void wr_Double(t_double dDouble)
{
	 (ba->wr_Double(dDouble));

}

// ****************************
void wr_Long(t_long lLong)
{
	 (ba->wr_Long(lLong));

}
/*
// ****************************
void wr_Int16(t_int16 d)
{
	 (ba->wr_Int16(d));

}

// ****************************
void wr_Int32(t_int32 d)
{
	 (ba->wr_Int32(d));

}

// ****************************
void wr_Int64(t_int64 d)
{
	 (ba->wr_Int64(d));

}

// ****************************
void wr_UInt16(t_uint16 d)
{
	 (ba->wr_UInt16(d));

}

// ****************************
void wr_UInt32(t_uint32 d)
{
	 (ba->wr_UInt32(d));

}

// ****************************
void wr_UInt64(t_uint64 d)
{
	 (ba->wr_UInt64(d));

}
*/
void wr_Short(t_short d)
{
	 (ba->wr_Short(d));

}

void wr_PCode(t_pcode d)
{
	 (ba->wr_PCode(d));

}

void wr_Struct(int nSizeOf, void *s)
{
	 (ba->wr_Struct(nSizeOf, s));

}

void wr_Array(t_array *a)
{
  // kein wr_Struct() verwenden, da so kompakter
	ba->wr_Integer(a->count);
	for (register int i = 0; i < a->count; i++){
		ba->wr_Integer(a->idx[i]);
		ba->wr_Integer(a->idxTo[i]);
	}
 	return ;
}

bytearray *getBytearray()
{
	return ba;
}

int getSize()
{
	return ba->getSize();
}

bool pcodeWritePcode(pcode *p, int nOffset = 0);

/*
void dumpPcode()
{
//	myInfoConsole->print("-- dump pcode --\n\n");
	ba->dump();
	//myInfoConsole->pcodePrintCR();
}*/

t_pcode peekPCode(int nPos = -1)
{
	return ba->peekPCode(nPos);
}

t_integer peekInteger(int nPos = -1)
{
	return ba->peekInteger(nPos);
}

t_byte rd_Byte()
{
	return ba->rd_Byte();
}

unsigned char rd_Char()
{
	return ba->rd_Char();
}

t_boolean rd_Boolean()
{
	return ba->rd_Boolean();
}

t_cstring rd_CString()
{
	return ba->rd_CString();
}

t_single rd_Single()
{
	return ba->rd_Single();
}

t_currency rd_Currency()
{
	return ba->rd_Currency();
}

t_date rd_Date()
{
	return ba->rd_Date();
}

t_variant rd_Variant()
{
	return ba->rd_Variant();
}
/*
t_character rd_Character()
{
	return ba->rd_Character();
}
*/
t_double rd_Double()
{
	return ba->rd_Double();
}

t_integer rd_Integer()
{
	return ba->rd_Integer();
}

t_long rd_Long()
{
	return ba->rd_Long();
}
/*
t_int16 rd_Int16()
{
	return ba->rd_Int16();
}

t_int32 rd_Int32()
{
	return ba->rd_Int32();
}

t_int64 rd_Int64()
{
	return ba->rd_Int64();
}

t_uint16 rd_UInt16()
{
	return ba->rd_UInt16();
}

t_uint32 rd_UInt32()
{
	return ba->rd_UInt32();
}

t_uint64 rd_UInt64()
{
	return ba->rd_UInt64();
}*/

t_short rd_Short()
{
	return ba->rd_Short();
}

t_pcode rd_PCode()
{
	return ba->rd_PCode();
}

void rd_Struct(int nSizeOf, void *s)
{
  ba->rd_Struct(nSizeOf, s);
}

void *rd_Struct2(int nSizeOf)
{
  return ba->rd_Struct2(nSizeOf);
}


void rd_Array(t_array *a)
{
  // kein rd_Struct() verwenden, da so kompakter
	a->count = ba->rd_Integer();
  //  geschwindigkeitsoptimierung, durch einmal lesen der count idx, memcpy auf idx[i]
	for (register int i = 0; i < a->count; i++){
		a->idx[i] = ba->rd_Integer();
		a->idxTo[i] = ba->rd_Integer();
	}
}


t_byte rd_BYTE()
{
	if (ba->rd_PCode() == pcode__BYTE){}
	return ba->rd_Byte();
}

t_currency rd_CURRENCY()
{
	if (ba->rd_PCode() == pcode__CURRENCY){}
	return ba->rd_Currency();
}

t_date rd_DATE()
{
	if (ba->rd_PCode() == pcode__DATE){}
	return ba->rd_Date();
}
/*
t_character rd_CHARACTER()
{
	if (ba->rd_PCode() == pcode__CHARACTER){}
	return ba->rd_Character();
}
*/
t_boolean rd_BOOLEAN()
{
	if (ba->rd_PCode() == pcode__BOOLEAN){}
	return ba->rd_Boolean();
}

t_integer rd_INTEGER()
{
	if (ba->rd_PCode() == pcode__INTEGER){}
	return ba->rd_Integer();
}

t_long rd_LONG()
{
	if (ba->rd_PCode() == pcode__LONG){}
	return ba->rd_Long();
}
/*
t_cstring rd_CString()
{
	if (ba->rd_PCode() == pcode__STRING){}
	return ba->rd_CString();
}
*/
t_cstring rd_CSTRING()
{
	if (ba->rd_PCode() == pcode__CSTRING){}
	return ba->rd_CString();
}

t_single rd_SINGLE()
{
	if (ba->rd_PCode() == pcode__SINGLE){}
	return ba->rd_Single();
}

t_double rd_DOUBLE()
{
	if (ba->rd_PCode() == pcode__DOUBLE){}
	return ba->rd_Double();
}
/*
t_int16 rd_INT16()
{
	if (ba->rd_PCode() == pcode__INT16){}
	return ba->rd_Int16();
}

t_int32 rd_INT32()
{
	if (ba->rd_PCode() == pcode__INT32){}
	return ba->rd_Int32();
}

t_int64 rd_INT64()
{
	if (ba->rd_PCode() == pcode__INT64){}
	return ba->rd_Int64();
}
*/
t_short rd_SHORT()
{
	if (ba->rd_PCode() == pcode__SHORT){}
	return ba->rd_Short();
}

// reset current index to start
void resetPos()
{
  nAppendOffset = 0;
  nAppendOffset2 = 0;
  nAppendOffset3 = 0;
  nAppendOffset4 = 0;
  nDeclarationSize = 0;
#ifdef KBC
  sCurrentFile = "";
#endif

	ba->resetPos();
}

// reset current index to start
int getPos()
{
	return ba->getPos();
}

// reset current index to start
void setPos(int nPos)
{
	ba->setPos(nPos);
}


bytearray *ba;
int nIndent;
/*
bool setErrorWindow(_syntaxError *serroroutw);
bool setInfoWindow(_infoconsole *info);
bool showError(QString s);

_syntaxError *serroroutw;
_infoconsole *myInfoConsole;
*/




int nAppendOffset; // used for sub callings repositioning
int nAppendOffset2; // used for caching
int nAppendOffset3; // used for caching
int nAppendOffset4; // used for caching
int nDeclarationSize; // used for caching

#ifdef KBC
XString sCurrentFile; // used for caching
#endif

private:


//_mainwindow *my_mainwindow;

};
#endif

