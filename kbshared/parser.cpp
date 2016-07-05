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


/**
[EXPLANATION]
NAME: compatibility of the datatypes' size
DESC: VeryOldBasic (QBasic) and OldBasic (VB6) have different sizes of datatypes, 
e.g. Integer is treated as a 16bit only. This is outdated. Today, Integer are 32bit as it comes with KBasic.
If you need to run oldbasic or veryoldbasic code, just replace the variable declarations with the proper integer size:
Integer -> Int16

For further information you should compare the datatypes' size of each BASIC dialect.

Some short information on differences between KBasic <-> VB6:

KBasic:
Boolean is 1 Byte
Integer is 32bit
Long is 64bit
Decimal is not supported yet, use Double or Currency instead


SEEALSO:
*/

/**
[EXPLANATION]
NAME: ASCII-Codes
DESC:
         ASCII-Codes (codes 0 - 127)
 000   (nul)   016 ? (dle)   032 sp   048 0   064 @   080 P   096 `   112 p
 001 ? (soh)   017 ? (dc1)   033 !    049 1   065 A   081 Q   097 a   113 q
 002 ? (stx)   018 ? (dc2)   034 "    050 2   066 B   082 R   098 b   114 r
 003 ? (etx)   019 ? (dc3)   035 #    051 3   067 C   083 S   099 c   115 s
 004 ? (eot)   020 ¶ (dc4)   036 $    052 4   068 D   084 T   100 d   116 t
 005 ? (enq)   021 § (nak)   037 %    053 5   069 E   085 U   101 e   117 u
 006 ? (ack)   022 ? (syn)   038 &    054 6   070 F   086 V   102 f   118 v
 007 • (bel)   023 ? (etb)   039 '    055 7   071 G   087 W   103 g   119 w
 008 ? (bs)    024 ? (can)   040 (    056 8   072 H   088 X   104 h   120 x
 009   (tab)   025 ? (em)    041 )    057 9   073 I   089 Y   105 i   121 y
 010   (lf)    026   (eof)   042 *    058 :   074 J   090 Z   106 j   122 z
 011 ? (vt)    027 ? (esc)   043 +    059 ;   075 K   091 [   107 k   123 {
 012 ? (np)    028 ? (fs)    044 ,    060 <   076 L   092 \   108 l   124 |
 013   (cr)    029 ? (gs)    045 -    061 =   077 M   093 ]   109 m   125 }
 014 ? (so)    030 ? (rs)    046 .    062 >   078 N   094 ^   110 n   126 ~
 015 ¤ (si)    031 ? (us)    047 /    063 ?   079 O   095 _   111 o   127 ¦
SEEALSO:
*/


/**
[EXPLANATION]
NAME: Boolean operators
DESC:

 NOT                 
 AND                 
 OR                  
 XOR                 
 EQV                 
 IMP                 

 Expression1  Expression2  NOT  AND  OR   XOR  EQV  IMP
 -----------  -----------  ---  ---  ---  ---  ---  ---
 T            T            F    T    T    F    T    T
 T            F            F    F    T    T    F    F
 F            T            T    F    T    T    F    T 
 F            F            T    F    F    F    T    T
SEEALSO:
*/


/*

  P A R S E R   /   C O D E   G E N E R A T O R

If you do not know the meaning of the following words,
just take a good compiler book
and read it:


Supplied with information from the lexical scanner the parser checks the order how the tokens occur.
The parser looks in the grammar definition where all possible combination of instructions are defined.


parser
------

top-down / recursive descent parser / LL(1)

Recursion incurs overhead, and everything can be programatically done with iteration.
But lexical parsing of source code, and likewise of compiler symbols is much easier,
and due to that fact will probably result in more time available to be spent on optimizing that code.


builtin datatype / builtin operator
-----------------------------------

								| BOOLEAN - 8bit | INTEGER - 32bit signed | LONG - 64 bit signed | SINGLE - 32bit | DOUBLE - 64bit | STRING - 8bit ASCII - unlimited - zero terminated
								left right both
ADD              -    -            x
SUB              -    -            x
MUL              -    -            x
DIV              -    -            x
MOD              x    -            x
EQUAL            x    -            x
UNEQUAL          -                x
GREATER_EQUAL    -                x
LESSER_EQUAL     -                x
GREATER          -                x
LESSER           -                x
AND              x                x
OR               x                x
NOT              x                x
EXPONENT         -                x
STR_CAT          -                x
XOR              x                x
IDIV             -                x
EQV              -                x
IMP              -                x


/**
[EXPLANATION]
NAME: Expressions
DESC:

Expressions represent values. Either they direct represent values or shows the way to the result.
The compiler has to transform the abstract into concrete machine executable form.

While compilation the value type which an expression represents must be known:
- by the expression itself
- by other definition in type, sub or function
SEEALSO:
*/

/**
[EXPLANATION]
NAME: Operators
DESC:

Simple expressions can build complex expressions through combination. The combination are described through operators.
There exist two types of operators:

- unary operators, one operator and one operand (prefix)

	NOT, + (nothing done) / - (means -1 *)
- binary operators, one operator between two operands (infix)

The precedence of operators can be changed using ().

SEEALSO:
*/


/**
[EXPLANATION]
NAME: Names
DESC:

In the simplest form just an identifier, but names are used to access elements in user defined types as well.
SEEALSO:
*/

/**
[EXPLANATION]
NAME: Function
DESC:

gets a value by a unique name using a algorithm. A few parameters (or non) generate the return value.
It's not important to know the algorithm inside the function (how to get the result), only the parameters and return value type -> black box.
SEEALSO:
*/


/**
[EXPLANATION]
NAME: Assignment
DESC:

stores a value of an expression. A name of a variable shows the target. The expression value must have the type like the
variable. Type checking is done while compilation and runtime. Assignment is an action and not a comparision:

variable = expression

SEEALSO:
*/


/**
[EXPLANATION]
NAME: Recursion
DESC:

is allowed for function and sub calls.
SEEALSO:
*/


#include <ctype.h>



#include "parser.h"
#include "../kbshared/cache.h"


XIntMap binding_map_class;
XIntMap binding_map_method;

int nGlobalVarId;

parser::parser(pcode *p, cache *_my_cache)
{
  setKBASIC();

  // *** spracheinstellungen werden in anderen methoden normalerweise vorgenommen
  acBaseClassName = "Object"; // standard class if no parent class is explicitly declared
  acDefaultModuleName = "Global"; // standard module name if no module or class scope has been entered
  
  nDefaultType = pcode__VARIANT; // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT   

	for (int i = 0; i < parser__MAX_nDEF; i++){ // for DEFINT, DEFLNG, DEFSNG, DEFDBL, DEFSTR...
    nDEF[i] = nDefaultType; // default datatype
	}
  // *** 


  my_cache = _my_cache;

  bParseToken = true;

  pDim = new pcode("");

  myException.setAutoDelete(true);

  myPcodeAll = p;
  myPcodeData = new pcode("");
  myPcodeDefault = new pcode("");
  myPcodeDefault2 = new pcode("");
  myPcode = 0;

	myTextbuffer = new textbuffer(); // needed to truncate big input strings or zero terminate them

  myMemory_stringliteral = new memory_stringliteral();

  myMemory_type = new memory_type();
  myMemory_enum = new memory_enum();
  //myMemory_structure = new memory_structure();
  myMemory_label = new memory_label();

	myModule = new memory_module();
	myClass = new memory_class();


	//myInterface = new memory_interface();

	myExitFor = new memory_label();
	myExitDo = new memory_label();
	myIterateDo = new memory_label();
	myIterateFor = new memory_label();

	// binding for Qt, KDE ...
	myParser_classMethod = new parser_classMethod(); 
  if (binding_map_class.size() == 0){
	  binding_createMapClass();
	  binding_createMapMethod();
  }


  bSilent = false;

}

parser::~parser()
{
  if (my_cache) my_cache->wr_parserCloseAll(false);
  
  delete myPcodeData;
  delete myPcodeDefault;
  delete myPcodeDefault2;

  delete myMemory_stringliteral;  
  delete myMemory_type;
  delete myMemory_enum;
  //delete myMemory_structure;
  delete myMemory_label;

	delete myModule;  
	delete myClass;
  
	//delete myInterface;
	
  delete myExitFor;
	delete myExitDo;	
  delete myIterateDo;
	delete myIterateFor;

  delete myParser_classMethod;

  //delete myParser_classMethod;
  
	delete myTextbuffer;

  delete pDim;


  myException.clear();

}

const char *parser::getCurrentEnum()
{
	return acCurrentEnum;
}

const char *parser::getCurrentFile()
{
	return acCurrentFile;
}

int parser::getCurrentLine()
{
	return nCurrentLine;
}

int parser::getCurrentRow()
{
  if (with_pos_list_POS > -1){
    return 0; 
  }
	return nCurrentRow;
}

bool parser::stopAtLine(int _nLine, const char *acFile)
{
  if (_nLine == nCurrentLine){
   
    {
      if (strcmp(acFile, "") == 0){
	      return true;
      } else {
       if (strcmp(getCurrentFile(), acFile) == 0){
	       return true;
       }
      }
    }
  }

  return false;
}

bool parser::setCurrentEnum(const char *f)
{
	acCurrentEnum = f;
	return true;
}

bool parser::setCurrentFile(const char *f)
{
	acCurrentFile = f;
  XString s = acCurrentFile;

  if (s.contains("/default.kbasic") || s.contains("\\default.kbasic")
     )
  {
    myPcode = myPcodeDefault;
  } else if (s.contains("/default2.kbasic") || s.contains("\\default2.kbasic")
     )
  {
    myPcode = myPcodeDefault2;
  } else if (!s.contains("/default.kbasic") && !s.contains("\\default.kbasic") && !s.contains("/default2.kbasic") && !s.contains("\\default2.kbasic")
    && strcmp(acCurrentFile, "") != 0 && my_cache)
  {

    if (!pcs.contains(acCurrentFile)){

      pcs.addString(acCurrentFile, (int) new pcode(acCurrentFile));
    }
    myPcode = ((pcode *) pcs.getString(acCurrentFile));

  } else {
    myPcode = myPcodeAll;
  }
	return true;
}

bool parser::setCurrentLine(int n)
{
	nCurrentLine = n;
	return true;
}

bool parser::setCurrentRow(int n)
{
	nCurrentRow = n;
  if (n == 6){
    n = n;
  }
	return true;
}

token *parser::getToken()
{
	return myToken;
}

bool parser::parseInfo(pcode *p, const char *acParseInfo, bool bPos, int nPos)
{
  static char acText[1024];
  static char ac[1024];

	if (bNoError){ // print only, if no error occured before

		static char acText2[1024];

		if (bPos){
			sprintf(ac, "%s in line %d\n", acParseInfo, nPos == -1 ? getCurrentLine() : nPos);
			strcat(acText, ac);
		} else {
			sprintf(acText, " %s\n", acParseInfo);
		}
    CONSOLE print(acText);
	}
	
	return true;
}


/**
[EXPLANATION]
NAME: SYNTAX ERROR
PRINTNAME: Syntax Error
DESC: occures if you have written something KBasic can not understand completely.
SEEALSO:
*/
// nProductionId == DIM, nWRONG_TYPE--> somit kann fehlermeldungsfenster direkt link zur hilfe anbieten
// seealso kann ermittelt werden über hilfeindex und nProductionId
bool parser::syntaxError(int nProductionId, const char *acSyntaxError, int nErrorId)
{
  if (bNoError){ // throw error only, if no other error occured before
  	char *acText = myTextbuffer->get(1024 + strlen(acSyntaxError));

    XString sFile = getCurrentFile();
    int nLine = getCurrentLine();

    char acPos[128];
    char acLine[128];

    int nPos = getCurrentRow();
    if (sFile.endsWith(".kbasic_form") || sFile.endsWith(".kbasic_report") || sFile.endsWith(".kbasic_menubar") || sFile.endsWith(".kbasic_toolbar")) nLine--;
    if (nPos > 0) sprintf(acPos, " near pos %d", nPos); else sprintf(acPos, " ");
    if (nLine > 0) sprintf(acLine, " in line %d", nLine); else sprintf(acLine, " ");
  
      if (nPos > 0){
    	  sprintf(acText, "syntax error: %s%s%s in file %s\n", acSyntaxError, acLine, acPos, getCurrentFile());
      } else {
    	  sprintf(acText, "syntax error: %s%s in file %s\n", acSyntaxError, acLine, getCurrentFile());
      }
    
    
  	CONSOLE printError(acText);

    // clear parser cache file
    if (my_cache) my_cache->deleteParser(getCurrentFile());

  	bNoError = bProducePcode = false; // syntax error occured, stop producing of pcode
  }
	return false;
}

/**
[EXPLANATION]
NAME: SEMANTIC ERROR
PRINTNAME: Semantic Error
DESC: you combined something which is not allowed
SEEALSO:
*/
bool parser::semanticError(int nProductionId, const char *acSemanticError, int nErrorId)//, int _nCurrentLine, int _nCurrentRow)
{
	if (bNoError){ // throw error only, if no other error occured before
  	char *acText = myTextbuffer->get(1024 + strlen(acSemanticError));


    char acPos[128];
    char acLine[128];
    int nPos = getCurrentRow();


    XString sFile = getCurrentFile();
    int nLine = getCurrentLine();
    if (sFile.endsWith(".kbasic_form") || sFile.endsWith(".kbasic_report") || sFile.endsWith(".kbasic_menubar") || sFile.endsWith(".kbasic_toolbar")) nLine--;

    if (nPos > 0) sprintf(acPos, " near pos %d", nPos); else sprintf(acPos, " ");
    if (nLine > 0) sprintf(acLine, " in line %d", nLine); else sprintf(acLine, " ");

    if (nPos > 0){
    	sprintf(acText, "parser error: %s%s%s in file %s\n", acSemanticError, acLine, acPos, getCurrentFile());
    } else {
    	sprintf(acText, "parser error: %s%s in file %s\n", acSemanticError, acLine, getCurrentFile());
    }
  	if (HAS_CONSOLE) CONSOLE printError(acText);

    // clear parser cache file
    if (my_cache) my_cache->deleteParser(getCurrentFile());

    bNoError = bProducePcode = false; // semantic error occured, stop producing of pcode
  }
	return false;
}

/**
[EXPLANATION]
NAME: INTERNAL ERROR
PRINTNAME: Internal Error
DESC: internal error: should not occur, if so please contact www.kbasic.com - thanks
SEEALSO:
*/
bool parser::internalError(const char *acInternalError)//, int _nCurrentLine, int _nCurrentRow)
{
	if (bNoError){ // throw error only, if no other error occured before
  	char *acText = myTextbuffer->get(1024 + strlen(acInternalError));

    XString sFile = getCurrentFile();
    int nLine = getCurrentLine();
    if (sFile.endsWith(".kbasic_form") || sFile.endsWith(".kbasic_report") || sFile.endsWith(".kbasic_menubar") || sFile.endsWith(".kbasic_toolbar")) nLine--;

    char acPos[128];
    char acLine[128];
    int nPos = getCurrentRow();
    if (nPos > 0) sprintf(acPos, " near pos %d", nPos); else sprintf(acPos, " ");
    if (nLine > 0) sprintf(acLine, " in line %d", nLine); else sprintf(acLine, " ");

    sprintf(acText, "internal error: %s%s%s in file %s", acInternalError, acLine, acPos, getCurrentFile());
  	CONSOLE printError(acText);

    // clear parser cache file
    if (my_cache) my_cache->deleteParser(getCurrentFile());

  	bNoError = bProducePcode = false; // internal error occured, stop producing of pcode
  
  }
	return false;
}



void parser::setVERYOLDBASIC()
{ 
  bVeryOldBasic = true; bOldBasic = false; bKBasic = false; 
  
  {
    nDefaultType = pcode__DOUBLE; // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT   

	  for (int i = 0; i < parser__MAX_nDEF; i++){ // for DEFINT, DEFLNG, DEFSNG, DEFDBL, DEFSTR...
      nDEF[i] = nDefaultType; // default datatype
	  }
  }

  setExplicit(false); 
  nBaseOfArray = 1; // arrays start with 1 if not explictly declared or OPTION BASE  
  bOptionCompareBinary = true;
}

void parser::setOLDBASIC()
{ 
  bVeryOldBasic = false; bOldBasic = true; bKBasic = false; 

  {
    nDefaultType = pcode__VARIANT; // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT   

	  for (int i = 0; i < parser__MAX_nDEF; i++){ // for DEFINT, DEFLNG, DEFSNG, DEFDBL, DEFSTR...
      nDEF[i] = nDefaultType; // default datatype
	  }
  }
  
  setExplicit(false); 
  nBaseOfArray = 1; // arrays start with 1 if not explictly declared or OPTION BASE  
}

void parser::setKBASIC()
{ 
  bVeryOldBasic = false; bOldBasic = false; bKBasic = true; 

  {
    nDefaultType = pcode__VARIANT; // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT   

	  for (int i = 0; i < parser__MAX_nDEF; i++){ // for DEFINT, DEFLNG, DEFSNG, DEFDBL, DEFSTR...
      nDEF[i] = nDefaultType; // default datatype
	  }
  }
  
  setExplicit(true); 
  nBaseOfArray = 0; // arrays start with 0
}

void parser::setExplicit(bool b)
{
  bExplicit = b; 
}
