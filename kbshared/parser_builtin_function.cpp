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



/**
[QBASIC][VB][KBASIC]
NAME: ABS
PRINTNAME: Abs
TASK: Returns the absolute value of an argument.
SYNTAX: ABS (numerical expression) AS DOUBLE
DESC:
The absolute value of a number is its positive value. For instance, the
absolute value of -3 equals 3 and that of +3 equals 3, too.

The required number argument can be any valid numeric expression. 

CODE:
'use ABS to find the difference
'between 2 values
value1 = 11
value2 = 17
PRINT "The difference is "; ABS(value1 - value2)

Output:
The difference is 6 

EXAMPLES: abs.kbasic
CATEGORY: FUNCTION, BUILTIN, NUMBER, MATH
SEEALSO: SGN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fABS(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ABS = false;

	_BEGIN_
  if (!(/*bTerm_ABS = */parseTerm(token__ABS))){ _END_ }


 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fDOUBLE_EXPRESSION(p))){ syntaxError(token__ABS, "number expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ABS, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){
 				 p->wr_ABS(pcode__ABS, bReturn);
   		}

   		parseInfo(p, "parsed ABS");

   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__ABS, "( missing"); _ERROR_ }

	_END_
}


bool parser::fCAST(pcode *p, int *nReturnExpressionType, bool bReturn)
{
  _BEGIN_

  int nCast = peekToken();
  nextToken(true);


 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

	  bool bEXPRESSION = false;
	  bool bEXPRESSION2 = false;
	  bool bEXPRESSION3 = false;
	  bool bEXPRESSION4 = false;
	  bool bEXPRESSION5 = false;

    int nExpressionType = 0;

    switch(nCast){
      case token__TYP_BOOLEAN:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }
        *nReturnExpressionType = pcode__BOOLEAN;
        break;

      case token__STRING:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }

  	    if (parseTerm(token__SYM_COMMA)){ 

          if ((bEXPRESSION = fSTRING_EXPRESSION(p)) || (bEXPRESSION = fBOOLEAN_EXPRESSION(p))){}
          if (!bEXPRESSION){ syntaxError(token__STRING, "expression missing"); _ERROR_ }      	
      	  
          if (parseTerm(token__SYM_COMMA)){ 

            if (!(bEXPRESSION2 = fEXPRESSION(p))){ syntaxError(token__STRING, "expression missing"); _ERROR_ }

            if (parseTerm(token__SYM_COMMA)){ 

                if (!(bEXPRESSION3 = fEXPRESSION(p))){ syntaxError(token__STRING, "expression missing"); _ERROR_ }
        	  
                           
              }
           }          
        }
        *nReturnExpressionType = pcode__QSTRING;
        break;

      case token__TYP_BYTE:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }
        *nReturnExpressionType = pcode__BYTE;
        break;
      case token__TYP_SHORT:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }
        *nReturnExpressionType = pcode__SHORT;
        break;
      case token__TYP_INTEGER:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }
        *nReturnExpressionType = pcode__INTEGER;
/*
        switch(nExpressionType){
          case token__INTEGER:
            if (!fEXPRESSION(p, &nExpressionType)){ _END_ }
            break;
            */        

        break;
      case token__TYP_LONG:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }
        *nReturnExpressionType = pcode__LONG;
        break;

      case token__TYP_SINGLE:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }
        *nReturnExpressionType = pcode__SINGLE;
        break;
      case token__TYP_DOUBLE:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }
        *nReturnExpressionType = pcode__DOUBLE;
        break;

      case token__TYP_CURRENCY:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }
        *nReturnExpressionType = pcode__CURRENCY;
        break;
      //case token__TYP_DATE:
      case token__DATE:
        if (!fEXPRESSION(p, &nExpressionType)){ _END_ }


  	    if (parseTerm(token__SYM_COMMA)){ 

          if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__DATE, "string expression missing"); _ERROR_ }      	
        }

        *nReturnExpressionType = pcode__DATE;
        break;
    }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__CAST, ") missing"); _ERROR_ }
  	
    bool bThrows = false;
    if (parseTerm(token__THROWS)){ 
      const char *acException = "";
      if (!fID_KEYWORD_OR_BUILTIN(&acException)){ syntaxError(pcode__CAST, "exception name missing (CastException)"); _ERROR_ }
      if (utility::my_stricmp(acException, "CastException") == 0){
        bThrows = true;
      } else {
        { semanticError(pcode__CAST, "exception name not allowed (require CastException)"); _ERROR_ }
      }

    }

 		if (bProducePcode){
			 p->wr_CAST(pcode__CAST, *nReturnExpressionType, nExpressionType, bEXPRESSION, bEXPRESSION2, bEXPRESSION3, bEXPRESSION4, bEXPRESSION5, bReturn);       
 		}

    if (bThrows){
      memory_sub *s2 = 0;
      int nId2 = 0;
      int nSubId2 = 0;

      switch(isScopeClass()){
				  case false:
             nId2 = myModule->getId(getScope());
   				    s2 = myModule->getSubs(nId2);
             nSubId2 = s2->getId(nId2, getSub());
					    break;
				    case true:
             nId2 = myClass->getId(getScope());
   				    s2 = myClass->getMethods(nId2);
             nSubId2 = s2->getId(nId2, getMethod());
					    break;
		  }

      registerCatch(nId2, s2, nSubId2, p, pcode__CASTEXCEPTION);
    }

 		parseInfo(p, "parsed CAST");
 		_DONE_
	}

	_END_
}

/*
	bool fCAST_BYTE									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_SHORT									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_INTEGER									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_LONG									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_BOOLEAN									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_QSTRING									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_CSTRING									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_SINGLE									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_DOUBLE									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_CURRENCY									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCAST_DATE									(pcode *p, int *nReturnExpressionType, bool bReturn);
*/

/**
[KBASIC][VB][QBASIC]
NAME: SHELL
PRINTNAME: Shell
TASK: send command to environment
SYNTAX: SHELL( command ) AS LONG
DESC: 
CODE:
SHELL("DIR")
EXAMPLES: shell.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE, OS
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSHELL(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
- windowstyle not supported
[*]
[*]
*/
{

	//bool bTerm_SHELL = false;
  _BEGIN_

  if (!(/*bTerm_SHELL = */parseTerm(token__SHELL))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bBOOLEAN_EXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (bEXPRESSION = fSTRING_EXPRESSION(p)){}

  if (parseTerm(token__SYM_COMMA)){ 
    
    if (!(bBOOLEAN_EXPRESSION = fBOOLEAN_EXPRESSION(p))){  syntaxError(token__SHELL, "boolean expression missing"); _ERROR_ }

	}


  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SHELL, ") missing"); _ERROR_ }

	{

 		if (bProducePcode){
			 p->wr_SHELL(pcode__SHELL, bEXPRESSION, bBOOLEAN_EXPRESSION, bReturn);
 		}

		*nReturnExpressionType = pcode__LONG;

 		parseInfo(p, "parsed SHELL");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CINT
PRINTNAME: CInt
TASK: CINT converts any number to an integer.
SYNTAX: CINT( numerical expression ) AS INTEGER
DESC: 
CINT takes any number and convert it to an
integer.  This will remove any precision from a single
or a double. 
CODE:
PRINT CINT(300.5012)
'
' Output:
' 300
EXAMPLES: cint.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, INTEGER
SEEALSO: CLNG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCINT(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[*]
[*]
[*]
*/
{
	//bool bTerm_CINT = false;
  _BEGIN_

  if (!(/*bTerm_CINT = */parseTerm(token__CINT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;


	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fEXPRESSION(p))){ syntaxError(token__CINT, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CINT, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){
 				 p->wr_CINT(pcode__CINT, bReturn);
   		}

   		parseInfo(p, "parsed CINT");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CINT, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SPACE
PRINTNAME: Space
TASK: SPACE function creates a string consisting of spaces.
SYNTAX: SPACE( INTEGER ) AS STRING
DESC: 
SPACE creates a string of spaces based on x length.
This function is similar to the STRING function.
CODE:
PRINT "*" + SPACE(5) + "*"

' Output:
' *     *

EXAMPLES: space.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: SPC, STRING
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSPACE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{
	//bool bTerm_SPACE = false;

  _BEGIN_

  if ((/*bTerm_SPACE = */parseTerm(token__SPACE)));
  else if (!(/*bTerm_SPACE = */parseTerm(token__SPACE_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fINTEGER_EXPRESSION(p))){ syntaxError(token__SPACE, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SPACE, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			p->wr_SPACE(pcode__SPACE, bReturn);
   		}

   		parseInfo(p, "parsed SPACE");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__SPACE, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CLNG
PRINTNAME: CLng
TASK: CLNG converts any number to a long.
SYNTAX: CLNG( numerical expression ) AS LONG
DESC: 
CLNG takes any number and tries to convert it to a
long.  This will remove any precision from a single
or a double. 
CODE: 
PRINT CLNG(300.5012)

' Output:
' 300

EXAMPLES: clng.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, LONG
SEEALSO: CINT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCLNG(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[*]
[*]
[*]
*/
{
	//bool bTerm_CLNG = false;

  _BEGIN_

  if (!(/*bTerm_CLNG = */parseTerm(token__CLNG))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fEXPRESSION(p))){ syntaxError(token__CLNG, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CLNG, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__LONG;

   		if (bProducePcode){
 				 p->wr_CLNG(pcode__CLNG, bReturn);
   		}

   		parseInfo(p, "parsed CLNG");
   		_DONE_
  	}
	}
  	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CLNG, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CSNG
PRINTNAME: CSng
TASK: CSNG converts any number to a single.
SYNTAX: CSNG( numerical expression ) AS SINGLE
DESC: 
CSNG takes any number and tries to convert it to a
single. 
CODE:
PRINT CSNG(300.5012)

' Output:
' 300.5012

EXAMPLES: csng.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, SINGLE
SEEALSO: CDBL
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCSNG(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[*]
[*]
[*]
*/
{
	//bool bTerm_CSNG = false;

  _BEGIN_
  if (!(/*bTerm_CSNG = */parseTerm(token__CSNG))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fEXPRESSION(p))){ syntaxError(token__CSNG, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CSNG, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__SINGLE;

   		if (bProducePcode){
 				 p->wr_CSNG(pcode__CSNG, bReturn);
   		}

   		parseInfo(p, "parsed CSNG");
   		_DONE_
  	}
	}
  	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CSNG, "( missing"); _ERROR_ }

	_END_
}


/**
[KBASIC][VB][QBASIC]
NAME: CDBL
PRINTNAME: CDbl
TASK: CDBL converts any number to a double.
SYNTAX: CDBL( numerical expression ) AS DOUBLE
DESC: 
CDBL takes any number and tries to convert it to a
double. 
CODE:
PRINT CDBL(300.5012)

' Output:
' 300.5012

EXAMPLES: cdbl.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, DOUBLE
SEEALSO: CSNG, CINT, CLNG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCDBL(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

  //bool bTerm_CDBL = false;

  _BEGIN_
  if (!(/*bTerm_CDBL = */parseTerm(token__CDBL))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fEXPRESSION(p))){ syntaxError(token__CDBL, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CDBL, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){
 				 p->wr_CDBL(pcode__CDBL, bReturn);
   		}

   		parseInfo(p, "parsed CDBL");
   		_DONE_
  	}
	}
  	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CDBL, "( missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: CCUR
PRINTNAME: CCur
TASK: CCUR converts any number to a currency.
SYNTAX: CCUR( numerical expression ) AS CURRENCY
DESC: 
CCUR takes any number and tries to convert it to a
currency. 
CODE:
PRINT CCUR(300.5012)

' Output:
' 300.5012

EXAMPLES: ccur.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, CURRENCY
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCCUR(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	//bool bTerm_CCUR = false;

  _BEGIN_
  if (!(/*bTerm_CCUR = */parseTerm(token__CCUR))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fEXPRESSION(p))){ syntaxError(token__CCUR, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CCUR, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__CURRENCY;

   		if (bProducePcode){
 				 p->wr_CCUR(pcode__CCUR, bReturn);
   		}

   		parseInfo(p, "parsed CCUR");
   		_DONE_
  	}
	}
  	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CCUR, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CBOOL
PRINTNAME: CBool
TASK: CBOOL converts any number to a boolean.
SYNTAX: CBOOL( numerical expression ) AS BOOLEAN
DESC: 
CBOOL takes any number and tries to convert it to a
boolean. 
CODE:
PRINT CBOOL(300.5012)

' Output:
' true

EXAMPLES: cbool.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, BOOLEAN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCBOOL(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	//bool bTerm_CBOOL = false;

  _BEGIN_

  if (!(/*bTerm_CBOOL = */parseTerm(token__CBOOL))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fEXPRESSION(p))){ syntaxError(token__CBOOL, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CBOOL, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__BOOLEAN;

   		if (bProducePcode){
 				 p->wr_CBOOL(pcode__CBOOL, bReturn);
   		}

   		parseInfo(p, "parsed CBOOL");
   		_DONE_
  	}
	}
  	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CBOOL, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CBYTE
PRINTNAME: CByte
TASK: CBYTE converts any number to a byte.
SYNTAX: CBYTE( numerical expression ) AS BYTE
DESC: 
CBYTE takes any number and tries to convert it to a
byte. 
CODE:
PRINT CBYTE(300.5012)

' Output:
' true

EXAMPLES: cbyte.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, BYTE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCBYTE(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_CBYTE = false;

  _BEGIN_
  if (!(/*bTerm_CBYTE = */parseTerm(token__CBYTE))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fEXPRESSION(p))){ syntaxError(token__CBYTE, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CBYTE, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__BYTE;

   		if (bProducePcode){
 				 p->wr_CBYTE(pcode__CBYTE, bReturn);
   		}

   		parseInfo(p, "parsed CBYTE");
   		_DONE_
  	}
	}
  	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CBYTE, "( missing"); _ERROR_ }

	_END_
}


/* *
[KBASIC][VB][QBASIC]
NAME: CDATE
PRINTNAME: CDate
TASK: CDATE converts any number to a date.
SYNTAX: CDATE( numerical expression ) AS DATE
DESC: 
CDATE takes any number and tries to convert it to a
date. 
CODE:
PRINT CDATE(300.5012)

' Output:
' true

EXAMPLES: cdate.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, DATE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCDATE(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_CDATE = false;

  _BEGIN_

  if (!(/*bTerm_CDATE = */parseTerm(token__CDATE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(fEXPRESSION(p))){ syntaxError(token__CDATE, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CDATE, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DATE;

   		if (bProducePcode){
 				 p->wr_CDATE(pcode__CDATE, bReturn);
   		}

   		parseInfo(p, "parsed CDATE");
   		_DONE_
  	}
	}
  	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CDATE, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: INSTR
PRINTNAME: InStr
TASK: INSTR finds one string inside another.
SYNTAX: INSTR([start AS INTEGER ,] src AS STRING, sub AS STRING) AS INTEGER
DESC: 
INSTR searches the src string for and occurance of the
sub string and returns the index of the sub string in
the src string.  0 is returned if the sub string is
not found. start tells the positon from which the searching starts from.

CODE:
dim x as string, y as string
x = "This is a string"
y = "str"
PRINT INSTR(x, y)

' Output:
' 11

EXAMPLES: instr.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: LEFT, RIGHT, LEN, MID, INSTREV
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fINSTR(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
- compare not supported
[*]
[*]
*/
{

	//bool bTerm_INSTR = false;

  _BEGIN_

	bool bTerm_INDEXOF = false;

  if (!(/*bTerm_INSTR = */parseTerm(token__INSTR)) && !(bTerm_INDEXOF = parseTerm(token__INDEXOF))){ _END_ }

  

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;
	bool bEXPRESSION3 = false;
	bool bCase = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (bTerm_INDEXOF){

  	  if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__INSTR, "string expression missing"); _ERROR_ }

      if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__INSTR, ", missing"); _ERROR_ }  	      

      if (!fSTRING_EXPRESSION(p)){ syntaxError(token__INSTR, "string expression missing"); _ERROR_ }

      if (parseTerm(token__SYM_COMMA)){

  	    if (bEXPRESSION = fINTEGER_EXPRESSION(p)){

          if (parseTerm(token__SYM_COMMA)){

            if (!(bCase = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__INSTREV, "boolean expression missing"); _ERROR_ }

          }

  	    }
      }

    } else {

  	  if (bEXPRESSION = fINTEGER_EXPRESSION(p)){

        if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__INSTR, ", missing"); _ERROR_ }

  	  }

  	  if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__INSTR, "string expression missing"); _ERROR_ }

      if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__INSTR, ", missing"); _ERROR_ }  	

      if (!fSTRING_EXPRESSION(p)){ syntaxError(token__INSTR, "expression missing"); _ERROR_ }

      if (parseTerm(token__SYM_COMMA)){

        if (!(bCase = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__INSTR, "boolean expression missing"); _ERROR_ }

      }

    }   

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INSTR, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){
  			p->wr_INSTR(pcode__INSTR, bEXPRESSION, bTerm_INDEXOF, bCase, bReturn, bObjectFake);
   		}

   		parseInfo(p, "parsed INSTR");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__INSTR, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SEEK
PRINTNAME: Seek
TASK: returns the current position in file or set the new position in file
SYNTAX: SEEK [#]fileno, position / SEEK([#]fileno) 
DESC: SEEK
CODE:
EXAMPLES: seek.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: OPEN, GET, PUT, WRITE, PRINT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSEEK(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_SEEK = false;

  _BEGIN_
  if (!(/*bTerm_SEEK = */parseTerm(token__SEEK))){ _END_ }

	

	bool bEXPRESSION = false;

	bool bTerm_COMMA = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

 	bool bTerm__HASH = false;
  

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
	if (bEXPRESSION = fINTEGER_EXPRESSION(p)){}

  if (!bEXPRESSION) _END_; // maybe it is Form.Seek(...)

	if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
		if (!(bEXPRESSION = fLONG_EXPRESSION(p))){ syntaxError(token__SEEK, "long expression missing"); _ERROR_ }
	}

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SEEK, ") missing"); _ERROR_ }

	{

		*nReturnExpressionType = pcode__LONG;

    if (bTerm_COMMA){
      // SEEK [#]Dateinummer%, Position&
 		  if (bProducePcode){
			  p->wr_SEEK(pcode__SEEK, bReturn);
 		  }
    } else {
      // SEEK(Dateinummer%)
 		  if (bProducePcode){
			  p->wr_SEEK2(pcode__SEEK2, bReturn);
 		  }
    }

 		parseInfo(p, "parsed SEEK");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: EOF
PRINTNAME: EOF
TASK: returns true if end of file has been reached
SYNTAX: EOF ([#]fileno)
DESC: checks if end of file has been reached and return true if it has happened
CODE:
Dim data
Open "file1" For Input As #1	' open file for reading
Do While Not EOF(1)	' test for end of file
	Line Input #1, data	' get the data from file
	Print data	
Loop
Close #1	' close file
EXAMPLES: eof.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: OPEN, WRITE, LOF, CLOSE, LOC
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fEOF(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_EOF = false;

  _BEGIN_
  if (!(/*bTerm_EOF = */parseTerm(token__EOF_))){ _END_ }

  

	bool bEXPRESSION = false;
	bool bTerm__HASH = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
	if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__EOF_, "integer expression missing"); _ERROR_ }

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__EOF_, ") missing"); _ERROR_ }

	{

		*nReturnExpressionType = pcode__BOOLEAN;

 		if (bProducePcode){
      p->wr_EOF(pcode__EOF_, bReturn);
 		}

 		parseInfo(p, "parsed EOF");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: LOF
PRINTNAME: LOF
TASK: returns the length of a file in bytes
SYNTAX: LOF ([#]fileno)
DESC:
CODE:
Dim filelen
Open "file1" For Input As #1	' open file
filelen = LOF(1)	' get the length of file
Close #1	' close file
EXAMPLES: lof.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: EOF, OPEN, WRITE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLOF(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_LOF = false;
  _BEGIN_
  if (!(/*bTerm_LOF = */parseTerm(token__LOF))){ _END_ }

	

	bool bEXPRESSION = false;
	bool bTerm__HASH = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
	if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__EOF_, "integer expression missing"); _ERROR_ }

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LOF, ") missing"); _ERROR_ }

	{

		*nReturnExpressionType = pcode__LONG;

 		if (bProducePcode){
      p->wr_LOF(pcode__LOF, bReturn);
 		}

 		parseInfo(p, "parsed LOF");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: LEN
PRINTNAME: Len
TASK: LEN returns the length of a string or the size of a variable in bytes.
SYNTAX: LEN( STRING ) AS INTEGER
DESC: 
LEN returns the length of a string or the size of a variable in bytes.
CODE:
dim x as string
x = "a string"
PRINT LEN(x)

' Output:
' 8

EXAMPLES: 
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: PRINT, INSTR, OPEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/

bool parser::fLEN(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	bool bTerm_LEN = false;

  _BEGIN_
  if (!(parseTerm(token__SIZE)) && !(bTerm_LEN = parseTerm(token__LEN)) && !(bTerm_LEN = parseTerm(token__LENGTH))){ _END_ }

	
 
 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bIDENTIFIER = false;

  int nVar = 0;
	t_scope scope = global;
  int nType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    {
    
      // user defined types: len(meintyp)
      //bDisableStringAutoCast = true;
      if (bTerm_LEN && !bObjectFake && (bEXPRESSION = fSTRING_EXPRESSION(p))){
      } else if (!bObjectFake && (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nType))){
      } else if (!bObjectFake){
        { syntaxError(token__LEN, "string expression missing"); _ERROR_ }
      }
      //bDisableStringAutoCast = false;
    }
    
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LEN, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){

        if (bObjectFake || bEXPRESSION){
 
        } else {

          int n = myMemory_type->getSize(nType);

          p->wr_PUSH_LONG(pcode__PUSH_LONG, n);
        }
   			
    		 p->wr_LEN(pcode__LEN, bObjectFake || bEXPRESSION, bReturn);

   		}

   		parseInfo(p, "parsed LEN");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__LEN, "( missing"); _ERROR_ }

	_END_
}


/* *
[KBASIC][VB][QBASIC]
NAME: LN
PRINTNAME: LN
TASK: LN returns 
SYNTAX: LN( NUMERIC ) AS DOUBLE
DESC: 
CODE:

EXAMPLES: 
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLN(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_LN = false;
  _BEGIN_
  if (!(/*bTerm_LN = */parseTerm(token__LN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bIDENTIFIER = false;

  int nVar = 0;
	t_scope scope = global;
  int nType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
    
    if (bEXPRESSION = fNUMERIC_EXPRESSION(p)){
    } else  {
      { syntaxError(token__LEN, "numeric expression missing"); _ERROR_ }
    }
    
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LN, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){
   			
  			 p->wr_LN(pcode__LN, bReturn);
   		}

   		parseInfo(p, "parsed LN");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__LN, "( missing"); _ERROR_ }

	_END_
}

bool parser::fUTF8(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
  _BEGIN_
  if (!(parseTerm(token__UTF8))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    bool bQSTRING = false;
    if (!bObjectFake && (bQSTRING = bEXPRESSION = fEXPRESSION2(p, pcode__QSTRING, false)));
    else if (!bObjectFake) bEXPRESSION = fEXPRESSION2(p, pcode__CSTRING, false); 

  	if (!bObjectFake && !(bEXPRESSION)){ syntaxError(token__UTF8, "string expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__UTF8, ") missing"); _ERROR_ }
  	{

  		*nReturnExpressionType = bQSTRING ? pcode__QSTRING : pcode__CSTRING;

   		if (bProducePcode){
  			 p->wr_UTF8(pcode__UTF8, bReturn);
   		}

   		parseInfo(p, "parsed UTF8");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fUTF16(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
  _BEGIN_
  if (!(parseTerm(token__UTF16))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    bool bQSTRING = false;
    if (!bObjectFake && (bQSTRING = bEXPRESSION = fEXPRESSION2(p, pcode__QSTRING, false)));
    else if (!bObjectFake) bEXPRESSION = fEXPRESSION2(p, pcode__CSTRING, false); 

  	if (!bObjectFake && !(bEXPRESSION)){ syntaxError(token__UTF16, "string expression missing"); _ERROR_ }

    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__UTF16, ", missing"); _ERROR_ }  	

  	if (!(bEXPRESSION = fLONG_EXPRESSION(p))){ syntaxError(token__UTF16, "long expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__UTF16, ") missing"); _ERROR_ }
  	{

      *nReturnExpressionType = bQSTRING ? pcode__QSTRING : pcode__CSTRING;

   		if (bProducePcode){
  			 p->wr_UTF16(pcode__UTF16, bReturn);
   		}

   		parseInfo(p, "parsed UTF16");
   		_DONE_
  	}
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: VAL
PRINTNAME: Val
TASK: VAL returns the numerical value of the string$.
SYNTAX: VAL ( string$ ) AS DOUBLE
DESC: 
VAL returns the numerical value of the string$. If it is not possible to convert to a
number, VAL returns 0. VAL reads from left to right and assume the number always left
not in the mid of a String.
CODE:
Print Val("344") ' --> 344
Print Val("21st day")  ' -->  21
Print Val("BASIC")  ' -->  0
EXAMPLES: val.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING, NUMBER, CONVERSION
SEEALSO: STR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fVAL(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_VAL = false;
  _BEGIN_
  if (!(/*bTerm_VAL = */parseTerm(token__VAL)) && !(parseTerm(token__VALUE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__VAL, "string expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__VAL, ") missing"); _ERROR_ }
  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){
  			 p->wr_VAL(pcode__VAL, bReturn);
   		}

   		parseInfo(p, "parsed VAL");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__VAL, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ASC
PRINTNAME: Asc
TASK: Returns the ASCII code for a character.
SYNTAX: ASC ( STRING ) AS INTEGER
DESC: 
Returns the ASCII code for the first character of STRING. A STRING of length zero returns 0.
CODE:
PRINT ASC("Bernd") ' will show 66
EXAMPLES: asc.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING, ASCII
SEEALSO: CHR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fASC(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ASC = false;
  _BEGIN_
  if (!(/*bTerm_ASC = */parseTerm(token__ASC))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

	  if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__ASC, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ASC, ") missing"); _ERROR_ }

	  {

		  *nReturnExpressionType = pcode__INTEGER;

 		  if (bProducePcode){
			  p->wr_ASC(pcode__ASC, bReturn);
 		  }

 		  parseInfo(p, "parsed ASC");
 		  _DONE_
	  }
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__ASC, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: LEFT
PRINTNAME: Left
TASK: LEFT returns a string containing the first characters of a string.
SYNTAX: LEFT(src AS STRING, n AS INTEGER) AS STRING
DESC: 
The LEFT function takes in a source string and truncates the source string
starting from left to right according the desired n characters of the source
string. The "left-over" string is then returned to the function caller.
If a negative n number is passed, the whole string is returned. Passing 0
returns an empty string.
CODE:
DIM src as string
src = "What a nice day"
PRINT LEFT( src, 4)

' Output:
' What

EXAMPLES: left.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: MID, RIGHT, INSTR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLEFT(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_LEFT = false;
  _BEGIN_
  if ((/*bTerm_LEFT = */parseTerm(token__LEFT)));
  else if (!(/*bTerm_LEFT = */parseTerm(token__LEFT_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	bool bTerm_COMMA = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__LEFT, "expression missing"); _ERROR_ }

    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__LEFT, ", missing"); _ERROR_ }

  	if (!(bEXPRESSION2 = fINTEGER_EXPRESSION(p))){ syntaxError(token__LEFT, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LEFT, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			 p->wr_LEFT(pcode__LEFT, bReturn);
   		}

   		parseInfo(p, "parsed LEFT");
   		_DONE_
  	}
	}
// 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__LEFT, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: RIGHT
PRINTNAME: Right
TASK: RIGHT returns the remaining string after truncating the source string's length according to the desired length and returns the truncated string.
SYNTAX: RIGHT(src AS STRING, n AS INTEGER) AS STRING
DESC: 
The RIGHT function takes in a source string and truncates the source string
starting at n desired length + 1.
The "left-over" string is then returned to the function caller.
If n is greater then the length of the string, the original source string is
returned. Passing 0 returns the original source string.
CODE:
DIM src as string
src = "What a nice day"
PRINT RIGHT( src, 5)

' Output:
' e day
EXAMPLES: right.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: MID, LEFT, INSTR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRIGHT(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_RIGHT = false;
  _BEGIN_
  if ((/*bTerm_RIGHT = */parseTerm(token__RIGHT)));
  else if (!(/*bTerm_RIGHT = */parseTerm(token__RIGHT_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	bool bTerm_COMMA = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__RIGHT, "expression missing"); _ERROR_ }

    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__RIGHT, ", missing"); _ERROR_ }

  	if (!(bEXPRESSION2 = fLONG_EXPRESSION(p))){ syntaxError(token__RIGHT, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__RIGHT, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			 p->wr_RIGHT(pcode__RIGHT, bReturn);
   		}

   		parseInfo(p, "parsed RIGHT");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__RIGHT, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: STR
PRINTNAME: Str
TASK: Convert number to string
SYNTAX: STR(number) AS STRING
DESC: 
CODE:
PRINT STR$(239.546)
EXAMPLES: str.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, STRING, NUMBER
SEEALSO: ASC, VAL
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSTR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_STR = false;
  _BEGIN_
  if ((/*bTerm_STR = */parseTerm(token__STR)));
  else if (!(/*bTerm_STR = */parseTerm(token__STR_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__STR, "numeric expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__STR, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			 p->wr_STR(pcode__STR, bReturn);
   		}

   		parseInfo(p, "parsed STR");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__STR, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CHR
PRINTNAME: Chr
TASK: Returns the ASCII character corresponding to the value of VAL.
SYNTAX: CHR(number) AS STRING
DESC: 
CODE:
PRINT CHR(34)
EXAMPLES: chr.kbasic
CATEGORY: FUNCTION, BUILTIN, ASCII, STRING
SEEALSO: ASC
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCHR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_CHR = false;
  _BEGIN_
  if ((/*bTerm_CHR = */parseTerm(token__CHR)));
  else if (!(/*bTerm_CHR = */parseTerm(token__CHR_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fLONG_EXPRESSION(p))){ syntaxError(token__CHR, "long expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CHR, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			 p->wr_CHR(pcode__CHR, bReturn);
   		}

   		parseInfo(p, "parsed CHR");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CHR, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: LCASE
PRINTNAME: LCase
TASK: LCASE returns a new string.  It contains the source string converted to all lower case.
SYNTAX: LCASE( STRING ) AS STRING
DESC: 
LCASE take a string and converts all its characters to
lower case.  It then returns a copy of the string.
CODE:
DIM src as string
src = "Mr. Big was HERE"
PRINT LCASE( src )

' Output:
' mr. big was here
EXAMPLES: lcase.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: UCASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLCASE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_LCASE = false;
  _BEGIN_
  if ((/*bTerm_LCASE = */parseTerm(token__LCASE)));
  else if (!(/*bTerm_LCASE = */parseTerm(token__LCASE_)) && !(parseTerm(token__LOWER))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__LCASE, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LCASE, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			 p->wr_LCASE(pcode__LCASE, bReturn);
   		}

   		parseInfo(p, "parsed LCASE");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__LCASE, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: UCASE
PRINTNAME: UCase
TASK: UCASE function converts the entire source string's characters into uppercase characters and returns the converted string to the function caller.
SYNTAX: UCASE( STRING ) AS STRING
DESC: 
The UCASE function takes in a source string and converts the entire source
string's characters into uppercase.
It then returns the converted string to the function caller.

CODE:
DIM src as string
src = "Mr. Big was HERE"
PRINT UCASE( src )

' Output:
' MR. BIG WAS HERE

EXAMPLES: ucase.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: LCASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fUCASE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_UCASE = false;
  _BEGIN_
  if ((/*bTerm_UCASE = */parseTerm(token__UCASE)));
  else if (!(/*bTerm_UCASE = */parseTerm(token__UCASE_)) && !(parseTerm(token__UPPER))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__UCASE, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__UCASE, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
 				 p->wr_UCASE(pcode__UCASE, bReturn);
   		}

   		parseInfo(p, "parsed UCASE");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__UCASE, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: HEX
PRINTNAME: Hex
TASK: HEX returns a string giving the hexadecimal (base 16) value for the 'number'.
SYNTAX: HEX$( number expression ) AS STRING
DESC: 
The 'number' can be any numeric expression. It will be rounded to the nearest
whole number before being evaluated. Integers (or results of expressions
within that range) are returned as a string of up to 4 hexadecimal
characters, long integers are returned as a string of up to 8 hexadecimal
characters.

Characters of Hex (0 - 9, A - F)

Hexadecimal -> Decimal
0 -> 0
1 -> 1
2 -> 2
3 -> 3
4 -> 4
5 -> 5
6 -> 6
7 -> 7
8 -> 8
9 -> 9
A -> 10
B -> 11
C -> 12
D -> 13
E -> 14
F -> 15
10 -> 16

CODE:
INPUT "Please type in a number: ", number
PRINT "The hexadecimal representation is "; HEX$(number)

' Output:
' 
' Please type in a number: 123456
' The hexadecimal representation is 1E240

EXAMPLES: hex.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING, CONVERSION
SEEALSO: OCT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fHEX(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_HEX = false;
  _BEGIN_
  if ((/*bTerm_HEX = */parseTerm(token__HEX)));
  else if (!(/*bTerm_HEX = */parseTerm(token__HEX_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__HEX, "numeric expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__HEX, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
 				 p->wr_HEX(pcode__HEX, bReturn);
   		}

   		parseInfo(p, "parsed HEX");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__HEX, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: POS
PRINTNAME: Pos
TASK: POS returns the current cursor position in the line.
SYNTAX: POS( numeric expression ) AS INTEGER
DESC: 
CODE:
PRINT POS(0)
EXAMPLES: pos.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: CSRLIN, LOCATE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fPOS(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	//bool bTerm_POS = false;
  _BEGIN_
  if (!(/*bTerm_POS = */parseTerm(token__POS))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__POS, "integer expression missing"); _ERROR_ }

  	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__POS, "wrong type, must be a number type"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__POS, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){
  			 p->wr_POS(pcode__POS, bReturn);
   		}

   		parseInfo(p, "parsed POS");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__POS, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CSRLIN
PRINTNAME: CSRLin
TASK: CSRLIN returns the current line of the cursor.
SYNTAX: CSRLIN
DESC: 
CODE:
PRINT CSRLIN()
EXAMPLES: csrlin.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: POS, LOCATE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCSRLIN(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	//bool bTerm_CSRLIN = false;
  _BEGIN_
  if (!(/*bTerm_CSRLIN = */parseTerm(token__CSRLIN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CSRLIN, ") missing"); _ERROR_ }

	}

	{

		*nReturnExpressionType = pcode__INTEGER;

 		if (bProducePcode){
			 p->wr_CSRLIN(pcode__CSRLIN, bReturn);
 		}

 		parseInfo(p, "parsed CSRLIN");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: OCT
PRINTNAME: Oct
TASK: OCT returns a string giving the octal (base 8) representation of 'number'.
SYNTAX: OCT( number ) AS INTEGER
DESC: 
return the octal string representation of an integer. The return string has as many
characters as necessary to represent the integer in octal, or the number specified by
the second argument, whichever is larger.
Octal numbers are just for fun and are just for fun. I really never used them before.

Oct (0 - 7)
Octal -> Decimal
0 -> 0
1 -> 1
2 -> 2
3 -> 3
4 -> 4
5 -> 5
6 -> 6
7 -> 7
10 -> 8
11 -> 9
12 -> 10

CODE:
a = 0o00007643210
a$ = OCT$(a) ' a$ = "76543210"
EXAMPLES: oct.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, STRING
SEEALSO: HEX
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fOCT(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_OCT = false;
  _BEGIN_
  if ((/*bTerm_OCT = */parseTerm(token__OCT)));
  else if (!(/*bTerm_OCT = */parseTerm(token__OCT_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__OCT, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__OCT, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  				 p->wr_OCT(pcode__OCT, bReturn);
   		}

   		parseInfo(p, "parsed OCT");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__OCT, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: BIN
PRINTNAME: Bin
TASK: BIN$ returns a string giving the binary (base 2) representation of 'number'.
SYNTAX: BIN( number ) AS INTEGER
DESC: 
return the binary string representation of an integer. The return string has as many
characters as necessary to represent the integer in binary.
CODE:
EXAMPLES: bin.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING, CONVERSION
SEEALSO: HEX
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fBIN(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_BIN = false;
  _BEGIN_
  if ((/*bTerm_BIN = */parseTerm(token__BIN)));
  else if (!(/*bTerm_BIN = */parseTerm(token__BIN_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__BIN, "expression missing"); _ERROR_ }

  	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__BIN, "wrong type, must be a number type"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__BIN, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){

  				 p->wr_BIN(pcode__BIN, bReturn);
   		}

   		parseInfo(p, "parsed BIN");
   		_DONE_
  	}
 	}
	//if (!bTerm_SYM_BR_OP){ syntaxError(token__BIN, "( missing"); _ERROR_ }

	_END_
}


/* *
[KBASIC][VB][QBASIC]
NAME: ATN
PRINTNAME: ATN
TASK: ATN returns the arctangent value of the argument 'number' in radians
SYNTAX: ATN( number ) AS DOUBLE
DESC: 
ATN returns the arctangent value of the argument 'number' in radians. Trigonometric functions: sin, cosine and arctangent.
CODE:
CONST PI=3.141592654
PRINT ATN(TAN(PI/4.0)), PI/4.0    'result:  .7853981635  .7853981635
PRINT (COS(180 * (PI / 180)))     'result:  -1
PRINT (SIN(90 * (PI / 180)))      'result:  1
PRINT (TAN(45 * (PI / 180)))      'result:  1.000000000205103
EXAMPLES: atn.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: SIN, COS, TAN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fATN(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ATN = false;
  _BEGIN_
  if (!(/*bTerm_ATN = */parseTerm(token__ATN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__ATN, "expression missing"); _ERROR_ }

  	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__ATN, "wrong type, must be a number type"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ATN, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_ATN(pcode__ATN, bReturn);
   		}

   		parseInfo(p, "parsed ATN");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__ATN, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: COS
PRINTNAME: Cos
TASK: COS returns the cosine of the argument 'number' in radians.
SYNTAX: COS( number ) AS DOUBLE
DESC: 
CODE:
CONST PI=3.141592654
PRINT ATN(TAN(PI/4.0)), PI/4.0    'result:  .7853981635  .7853981635
PRINT (COS(180 * (PI / 180)))     'result:  -1
PRINT (SIN(90 * (PI / 180)))      'result:  1
PRINT (TAN(45 * (PI / 180)))      'result:  1.000000000205103
EXAMPLES: cos.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: SIN, ATN, TAN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCOS(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_COS = false;
  _BEGIN_
  if (!(/*bTerm_COS = */parseTerm(token__COS))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__COS, "numeric expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__COS, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_COS(pcode__COS, bReturn);
   		}

   		parseInfo(p, "parsed COS");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__COS, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: RAD
PRINTNAME: Rad
TASK: 
SYNTAX: RAD( number ) AS DOUBLE
DESC: 
CODE:
EXAMPLES: rad.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: SIN, ATN, TAN, COS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRAD(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_RAD = false;
  _BEGIN_
  if (!(/*bTerm_RAD = */parseTerm(token__RAD))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__RAD, "numeric expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__RAD, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){
     	  p->wr_RAD(pcode__RAD, bReturn);
   		}

   		parseInfo(p, "parsed RAD");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__RAD, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SIN
PRINTNAME: Sin
TASK: SIN returns the sine of the argument 'number' in radians.
SYNTAX: SIN( number ) AS DOUBLE
DESC: 
CODE:
CONST PI=3.141592654
PRINT ATN(TAN(PI/4.0)), PI/4.0    'result:  .7853981635  .7853981635
PRINT (COS(180 * (PI / 180)))     'result:  -1
PRINT (SIN(90 * (PI / 180)))      'result:  1
PRINT (TAN(45 * (PI / 180)))      'result:  1.000000000205103
EXAMPLES: sin.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: COS, ATN, TAN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSIN(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_SIN = false;
  _BEGIN_
  if (!(/*bTerm_SIN = */parseTerm(token__SIN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__SIN, "numeric expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SIN, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_SIN(pcode__SIN, bReturn);
   		}

   		parseInfo(p, "parsed SIN");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__SIN, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: EXP
PRINTNAME: Exp
TASK: EXP returns the exponential value of 'number'.
SYNTAX: EXP( number ) AS DOUBLE
DESC: 
CODE:
PRINT EXP(0), EXP(1)         'result:  1  2.718282
PRINT LOG(1), LOG(EXP(1))    'result:  0  1
EXAMPLES: exp.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: LOG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fEXP(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_EXP = false;
  _BEGIN_
  if (!(/*bTerm_EXP = */parseTerm(token__EXP))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__EXP, "numeric expression missing"); _ERROR_ }


    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__EXP, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){
     		 p->wr_EXP(pcode__EXP, bReturn);
   		}

   		parseInfo(p, "parsed EXP");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__EXP, "( missing"); _ERROR_ }

	_END_
}


/**
[KBASIC][VB][QBASIC]
NAME: LOG
PRINTNAME: Log
TASK: LOG returns a the natural logaritm of a number.
SYNTAX: LOG (n AS DOUBLE) AS LONG
DESC: 
The LOG function calculates the base "e" (or natural) logaritm of a number.
Input number must be a positive (i.e. > 0).

CODE:
DIM x AS INTEGER
x = 12
PRINT LOG(x)

' Output:
' 2.48490665
EXAMPLES: log.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: EXP
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLOG(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_LOG = false;
  _BEGIN_
  if (!(/*bTerm_LOG = */parseTerm(token__LOG))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__LOG, "numeric expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LOG, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_LOG(pcode__LOG, bReturn);
   		}

   		parseInfo(p, "parsed LOG");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__LOG, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SGN
PRINTNAME: Sgn
TASK: 
SGN returns the sign of the argument 'number'.
SYNTAX: SGN( number ) AS INTEGER
DESC: 
SGN returns the sign of the argument 'number', +1 for positive numbers, 0 for 0, and -
1 for negative numbers.
CODE:
PRINT ABS(45.5 - 100!)           'result:  54.5
PRINT SGN(1), SGN(-1), SGN(0)    'result:  1  -1  0
EXAMPLES: sgn.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: ABS
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/

bool parser::fSGN(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_SGN = false;
  _BEGIN_
  if (!(/*bTerm_SGN = */parseTerm(token__SGN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__SGN, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SGN, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){

     				 p->wr_SGN(pcode__SGN, bReturn);
   		}

   		parseInfo(p, "parsed SGN");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__SGN, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: FIX
PRINTNAME: Fix
TASK: FIX cuts off the trail of a number
SYNTAX: FIX( number ) AS LONG
DESC: 
CODE:
PRINT FIX(12.49), FIX(12.54)    'result:  12  12
EXAMPLES: fix.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH, CONVERSION
SEEALSO: INT, CINT, CLNG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFIX(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_FIX = false;
  _BEGIN_
  if (!(/*bTerm_FIX = */parseTerm(token__FIX))){ _END_ }
	
  

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__FIX, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FIX, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__LONG;

   		if (bProducePcode){

     				 p->wr_FIX(pcode__FIX, bReturn);
   		}

   		parseInfo(p, "parsed FIX");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__FIX, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: INT
PRINTNAME: Int
TASK: returns the next integer number <= given number
SYNTAX: INT( number ) AS LONG
DESC: 
CODE:
PRINT INT(12.54), INT(-99.4)    'result:  12  -100
EXAMPLES: int.kbasic
CATEGORY: FUNCTION, BUILTIN, CONVERSION, INTEGER
SEEALSO: FIX, CINT, CLNG
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fINT(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_INT = false;
  _BEGIN_
  if (!(/*bTerm_INT = */parseTerm(token__INT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__INT, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INT, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__LONG;

   		if (bProducePcode){

  		 p->wr_INT(pcode__INT, bReturn);
   		}

   		parseInfo(p, "parsed INT");
   		_DONE_
  	}
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SQR
PRINTNAME: Sqr
TASK: SQR returns the square root of the argument 'number'.
SYNTAX: SQR( number ) AS LONG
DESC: 
SQR returns the square root of the argument 'number'.
And used to perform a logical conjunction on two expressions
CODE:
PRINT SQR(25), SQR(2)    'result:  5  1.414214
EXAMPLES: sqr.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSQR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_SQR = false;
  _BEGIN_
  if (!(/*bTerm_SQR = */parseTerm(token__SQR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__SQR, "numeric expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SQR, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_SQR(pcode__SQR, bReturn);
   		}

   		parseInfo(p, "parsed SQR");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__SQR, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: TAN
PRINTNAME: Tan
TASK: TAN returns the tangent of the argument 'number' in radians.
SYNTAX: TAN( number ) AS LONG
DESC: 
CODE:
CONST PI=3.141592654
PRINT ATN(TAN(PI/4.0)), PI/4.0    'result:  .7853981635  .7853981635
PRINT (COS(180 * (PI / 180)))     'result:  -1
PRINT (SIN(90 * (PI / 180)))      'result:  1
PRINT (TAN(45 * (PI / 180)))      'result:  1.000000000205103
EXAMPLES: tan.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: COS, SIN, ATN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTAN(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_TAN = false;
  _BEGIN_
  if (!(/*bTerm_TAN = */parseTerm(token__TAN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__TAN, "numeric expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__TAN, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_TAN(pcode__TAN, bReturn);
   		}

   		parseInfo(p, "parsed TAN");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__TAN, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: LTRIM
PRINTNAME: LTrim
TASK: LTRIM function removes the source string's leading spaces.
SYNTAX: LTRIM( STRING ) AS STRING
DESC: 
LTRIM function removes the source string's leading spaces,
from the beginning of the source string.

CODE:
DIM x as string
x = "  My house is on fire."
PRINT LTRIM( x )

' Output:
' My house is on fire.

EXAMPLES: ltrim.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: RTRIM, TRIM
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLTRIM(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_LTRIM = false;
  _BEGIN_
  if ((/*bTerm_LTRIM = */parseTerm(token__LTRIM)));
  else if (!(/*bTerm_LTRIM = */parseTerm(token__LTRIM_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__LTRIM, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LTRIM, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
 				 p->wr_LTRIM(pcode__LTRIM, bReturn);
   		}

   		parseInfo(p, "parsed LTRIM");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__LTRIM, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: RTRIM
PRINTNAME: RTrim
TASK: RTRIM function removes the source string's trailing spaces, from the end of the source string.
SYNTAX: RTRIM( STRING )
DESC: 
RTRIM function removes the source string's trailing spaces, from the end of
the source string.

CODE:
DIM x as string
x = "My house is on fire.   "
PRINT RTRIM( x )

' Output:
' My house is on fire.

EXAMPLES: rtrim.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: LTRIM, TRIM
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRTRIM(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_RTRIM = false;
  _BEGIN_
  if ((/*bTerm_RTRIM = */parseTerm(token__RTRIM)));
  else if (!(/*bTerm_RTRIM = */parseTerm(token__RTRIM_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__RTRIM, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__RTRIM, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			 p->wr_RTRIM(pcode__RTRIM, bReturn);
   		}

   		parseInfo(p, "parsed RTRIM");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__RTRIM, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: TRIM
PRINTNAME: Trim
TASK: TRIM function removes the source string's leading and trailing spaces.
SYNTAX: TRIM( STRING )
DESC: 
TRIM function removes the source string's leading and trailing spaces, from
the beginning and end of the source string.The "trimmed" string is return to
the function caller.


CODE:
DIM x as string
x = "   My house is on fire.   "
PRINT TRIM( x )

' Output:
' My house is on fire.

EXAMPLES: trim.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: LTRIM, RTRIM
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTRIM(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_TRIM = false;
  _BEGIN_
  if ((/*bTerm_TRIM = */parseTerm(token__TRIM)));
  else if (!(/*bTerm_TRIM = */parseTerm(token__TRIM_))){ _END_ }

	


 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__TRIM, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__TRIM, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			 p->wr_TRIM(pcode__TRIM, bReturn);
   		}

   		parseInfo(p, "parsed TRIM");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__TRIM, "( missing"); _END_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: RND
PRINTNAME: Rnd
TASK: returns an integer pseudo-random number between 0 and int(EXPR)-1 inclusive.
SYNTAX: RND( number ) AS DOUBLE
DESC: 
returns an integer pseudo-random number between 0 and int(EXPR)-1 inclusive. If
EXPR is 1, then returns a rational number between 0 (inclusive) and 1. If EXPR is
negative then EXPR seeds the random number generator.
CODE: 
RANDOMIZE TIMER
x% = INT(RND * 6) + 1
y% = INT(RND * 6) + 1
PRINT "2 turns with one dice: turn 1 ="; x%; "and turn 2 ="; y%
EXAMPLES: rnd.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: RANDOMIZE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRND(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_RND = false;
  _BEGIN_
  if (!(parseTerm(token__RANDOM)) && !(/*bTerm_RND = */parseTerm(token__RND))){ _END_ }

	

	bool bEXPRESSION = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    // optional
    if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){}// syntaxError(token__RND, "numeric expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__RND, ") missing"); _ERROR_ }

	}

 	{

 		*nReturnExpressionType = pcode__DOUBLE;

		if (bProducePcode){
 			 p->wr_RND(pcode__RND, bReturn, bEXPRESSION);
		}

		parseInfo(p, "parsed RND");
		_DONE_
 	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: INKEY
PRINTNAME: Inkey
TASK: INKEY reads the status of the keyboard, and a single keypress, if available.
SYNTAX: INKEY AS STRING
DESC: 
INKEY$ reads the status of the keyboard, and a single keypress, if available. If a
keypress is not available, then INKEY$ immediately returns a null string ("").
mid$( a$, i { , j } )
Returns a substring of a$ starting at the i'th positions and j characters in length. If the
second parameter is not specified then the substring is taken from the start position to
the end of a$.
CODE:
PRINT "Press Esc, to stop ..."
DO
LOOP UNTIL INKEY$ = CHR$(27)    '27 is the ASCII-Code for Esc.
EXAMPLES: inkey.kbasic
CATEGORY: FUNCTION, BUILTIN, KEYBOARD
SEEALSO: INPUT, PRINT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fINKEY(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	//bool bTerm_INKEY = false;
  _BEGIN_
  if ((/*bTerm_INKEY = */parseTerm(token__INKEY)));
  else if (!(/*bTerm_INKEY = */parseTerm(token__INKEY_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INKEY_, ") missing"); _ERROR_ }

	}

	{

		*nReturnExpressionType = pcode__QSTRING;

 		if (bProducePcode){
			 p->wr_INKEY(pcode__INKEY, bReturn);
 		}

 		parseInfo(p, "parsed INKEY");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: DATE
PRINTNAME: Date
TASK: DATE$ returns the current system date as a string or as date (depending on mode).
SYNTAX: DATE$ AS STRING / DATE() AS DATE (kbasic)
DESC: 
setting the date is not possible with this builtin function
CODE:
PRINT DATE
EXAMPLES: date.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: TIME
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDATE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
- set date not supported
[VB]
- internationalization not supported
- set date not supported
[*]
[*]
*/
{

	register bool bTerm_DATE = false;
	register bool bTerm_DATE2 = false;
  _BEGIN_
  if ((bTerm_DATE = parseTerm(token__DATE)));
  else if (!(bTerm_DATE2 = parseTerm(token__DATE_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (bTerm_SYM_BR_OP && (!(bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){
      _END2_
      return fCAST(p, nReturnExpressionType, bReturn);
    }
   	//if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DATE_, ") missing"); _ERROR_ }

	}

	{

    //if (isVERYOLDBASIC() || bTerm_DATE2){
      *nReturnExpressionType = pcode__QSTRING;

      if (bProducePcode){
				  p->wr_DATE(pcode__DATE, bReturn);
 		  }
      /*
    } else {
      *nReturnExpressionType = pcode__DATE;

      if (bProducePcode){
				  p->wr_DATE2(pcode__DATE2, bReturn);
 		  }
    }
    */

 		parseInfo(p, "parsed DATE");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: TIME
PRINTNAME: Time
TASK: TIME$ returns the current system time as a string.
SYNTAX: TIME$ AS STRING
DESC: 
set time is not supported as in older BASIC dialects
CODE:
PRINT TIME()
EXAMPLES: time.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: DATE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTIME(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
- set time is not supported
[VB]
- set time is not supported
[*]
[*]
*/
{

	register bool bTerm_TIME = false;
	register bool bTerm_TIME2 = false;
  _BEGIN_
  if ((bTerm_TIME = parseTerm(token__TIME)));
  else if (!(bTerm_TIME2 = parseTerm(token__TIME_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INKEY_, ") missing"); _ERROR_ }

	}

	{

//		if (isVERYOLDBASIC() || bTerm_TIME2) 
      *nReturnExpressionType = pcode__QSTRING;
    //else *nReturnExpressionType = pcode__DATE;

 		if (bProducePcode){
				 p->wr_TIME(pcode__TIME, bReturn);
 		}

 		parseInfo(p, "parsed TIME");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: STRING
PRINTNAME: String
TASK: STRING function creates a string of characters.
SYNTAX: STRING(X AS INTEGER, Y AS STRING) AS STRING
DESC: 
STRING creates a string of y characters based on x length.
The maximum length allowed is 1024 characters.

CODE:
PRINT STRING(20, "x")

' Output:
' xxxxxxxxxxxxxxxxxxxx

' 2nd form of STRING$ function:
' STRING(X AS INTEGER, Y AS INTEGER) AS STRING  (where Y goes 0-255)
PRINT STRING(20, 65)
' would output AAAAAAAAAAAAAAAAAAAA.

EXAMPLES: string2.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSTRING(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_STRING = false;
  _BEGIN_
  if ((/*bTerm_STRING = */parseTerm(token__STRING)));
  else if (!(/*bTerm_STRING = */parseTerm(token__STRING_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;
	bool bEXPRESSION3 = false;

	bool bTerm_COMMA = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (bVeryOldBasic == false && bOldBasic == false){ 
      _END2_
      return fCAST(p, nReturnExpressionType, bReturn);
    }

  	if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ 
      syntaxError(token__STRING, "numeric expression missing"); _ERROR_ 
    }

    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ 
      syntaxError(token__STRING, ", missing"); _ERROR_ 
    } else 

		if (bEXPRESSION2 = fEXPRESSION(p, &nExpressionType)){
   

			bEXPRESSION2 = false;
	   	if (memory_type::isNumeric(nExpressionType)) bEXPRESSION2 = true;
      else if (memory_type::isString(nExpressionType)){
  
        bEXPRESSION3 = true; // deactivated this, so that cast can work
      }
			else { syntaxError(token__STRING, "number expression or string expression missing"); _ERROR_ }
		}

  	if (!bEXPRESSION2 && !bEXPRESSION3){ syntaxError(token__STRING, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__STRING, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){

 				 p->wr_STRING2(pcode__STRING2, bReturn, bEXPRESSION2, bEXPRESSION3);
   		}

   		parseInfo(p, "parsed STRING");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__STRING, "( missing"); _ERROR_ }

	_END_
}

bool parser::fKBASICDIR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{
  _BEGIN_

  if (!parseTerm(token__KBASICDIR)){ _END_ }
	
 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__KBASICDIR, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){

 				 p->wr_KBASICDIR(pcode__KBASICDIR, bReturn);
   		}

   		parseInfo(p, "parsed KBASICDIR");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__KBASICDIR, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: MID
PRINTNAME: Mid
TASK: MID$ get the part of a string
SYNTAX: MID$(strvar AS STRING, start AS INTEGER [, length AS INTERGER]) AS STRING
DESC: 
CODE:
text$ = "The dog bites the cat"
text$ = MID$(text$, 10, 1)
PRINT text$
EXAMPLES: mid.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: TRIM, INSTR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fMID(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_MID = false;
  _BEGIN_
  if ((/*bTerm_MID = */parseTerm(token__MID)));
  else if (!(/*bTerm_MID = */parseTerm(token__MID_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

   	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__MID, "string expression missing"); _ERROR_ }

    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__MID, ", missing"); _ERROR_ }  	

  	if (!(bEXPRESSION = fLONG_EXPRESSION(p))){ syntaxError(token__MID, "long expression missing"); _ERROR_ }

  	if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
  		if (!(bEXPRESSION2 = fLONG_EXPRESSION(p))){ syntaxError(token__MID, "long expression missing"); _ERROR_ }
  	}

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__MID, ") missing"); _ERROR_ }
   	{
   		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
   			 p->wr_MID(pcode__MID, bReturn, bEXPRESSION2); // write pcode
   		}

   		parseInfo(p, "parsed MID");
   		_DONE_
   	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__MID, "( missing"); _ERROR_ }

	_END_
}

/**
[VB][KBASIC]
NAME: CHOOSE
PRINTNAME: Choose
TASK: Returns one value from a list of values depending on the index.
SYNTAX: CHOOSE (index, select-1[, select-2, ... [, select-n]])
DESC: 
CODE:
DIM s AS STRING
s = CHOOSE(1, "un", "deux", "troi")
PRINT s
EXAMPLES: choose.kbasic
CATEGORY: FUNCTION, KEYWORD, CONTROLFLOW
SEEALSO: IF, IIF, SELECT CASE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCHOOSE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[KBASIC]
*/
{

	//bool bTerm_CHOOSE = false;
  _BEGIN_
  if (!(/*bTerm_CHOOSE = */parseTerm(token__CHOOSE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	int nExpressionType;

	int nComma = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__CHOOSE, "numeric expression missing"); _ERROR_ }

		if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CHOOSE, ", missing"); _ERROR_ }

		while (true){

 	 		if (nComma >= parser__MAX_CHOOSE){ internalError("too many expression"); _ERROR_ }

  		if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__CHOOSE, "expression missing"); _ERROR_ }

      if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
 				nComma++;
  		} else {

				if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   			if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CHOOSE, ") missing"); _ERROR_ }

   			*nReturnExpressionType = pcode__VARIANT;

   			if (bProducePcode){
   				 p->wr_CHOOSE(pcode__CHOOSE, nComma + 1, bReturn); // write pcode
   			}
   			
   			parseInfo(p, "parsed CHOOSE");
   			_DONE_
   			
 			}
		}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__CHOOSE, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SWITCH
PRINTNAME: Switch
TASK: returns a value depending on an expression
SYNTAX: SWITCH (expression, value1[, expression2, value2, ... [expression, n, value n]])
DESC: SWITCH
CODE:
Dim s As String 
Dim i As Integer 
i = 1 
s = Switch ( i = 1 , "Der Menschen Hörigkeit" , i = 2 , "Casanova" ) 
Print s 
EXAMPLES: switch.kbasic
CATEGORY: FUNCTION, KEYWORD, CONTROLFLOW, DECISION
SEEALSO: IF, CHOOSE
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSWITCH(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_SWITCH = false;
  _BEGIN_
  if (!(/*bTerm_SWITCH = */parseTerm(token__SWITCH))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	int nExpressionType;

	int nComma = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		while (true){

 			if (nComma >= parser__MAX_SWITCH){ internalError("too many expression"); _ERROR_ }

 			if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__SWITCH, "boolean expression missing"); _ERROR_ }

			if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__SWITCH, ", missing"); _ERROR_ }
			
			if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__SWITCH, "expression missing"); _ERROR_ }

      if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
 				nComma++;
  		} else {

				if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   			if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SWITCH, ") missing"); _ERROR_ }

   			*nReturnExpressionType = pcode__VARIANT;

   			if (bProducePcode){
   				 p->wr_SWITCH(pcode__SWITCH, nComma + 1, bReturn); // write pcode
   			}
   			
   			parseInfo(p, "parsed SWITCH");
   			_DONE_
   			
 			}
		}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__SWITCH, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: IIF
PRINTNAME: IIf
TASK: returns a value depending on an expression
SYNTAX: IIf(expr, truepart, falsepart)
DESC: 
CODE:
Function testing (Test1 As Integer)
	testing = IIf(Test1 > 1000, "big", "small")
End Function
EXAMPLES: iif.kbasic
CATEGORY: FUNCTION, BUILTIN, CONTROLFLOW, DECISION
SEEALSO: IF
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fIIF(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_IIF = false;
  _BEGIN_
  if (!(/*bTerm_IIF = */parseTerm(token__IIF))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	int nExpressionType;

	int nComma = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		while (true){

 			if (nComma >= parser__MAX_SWITCH){ internalError("too many expression"); _ERROR_ }

 			if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__IIF, "boolean expression missing"); _ERROR_ }
	
			if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__IIF, ", missing"); _ERROR_ }

			if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__IIF, "expression missing"); _ERROR_ }

			if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__IIF, ", missing"); _ERROR_ }

			if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__IIF, "expression missing"); _ERROR_ }

			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__IIF, ") missing"); _ERROR_ }

   		*nReturnExpressionType = pcode__VARIANT;

   		if (bProducePcode){
   			 p->wr_IIF(pcode__IIF, bReturn); // write pcode
   		}
   		
   		parseInfo(p, "parsed IIF");
   		_DONE_
   		
		}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__IIF, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: STRCOMP
PRINTNAME: StrComp
TASK: compares to strings
SYNTAX: StrComp(string1, string2[, compare])
DESC: 
compare: defines how to compare the two strings. Do not need to be given (optional) 
Possible values are 0 and 1. The value 0 (default) means a binary compare.
The value 1 means a text-based compare. If compare is not given, Option Compare defines how to compare.
CODE:
Dim Text1, Text2, Vergl

Text1 = "ABCD": Text2 = "abcd"	' 
Verg1 = StrComp(Text1, Text2, 1)	' result:0.
Verg1 = StrComp(Text1, Text2, 0)	' result:-1.
Verg1 = StrComp(Text2, Text1)	' result:1.
EXAMPLES: strcomp.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSTRCOMP(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_STRCOMP = false;
  _BEGIN_
  if (!(/*bTerm_STRCOMP = */parseTerm(token__STRCOMP))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

   	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__STRCOMP, "string expression missing"); _ERROR_ }

  	if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__STRCOMP, ", missing"); _ERROR_ }  	

   	if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__STRCOMP, "string expression missing"); _ERROR_ }

  	if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
  		if (!(bEXPRESSION2 = fINTEGER_EXPRESSION(p))){ syntaxError(token__STRCOMP, "integer expression missing"); _ERROR_ }
  	}

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__STRCOMP, ") missing"); _ERROR_ }
   	{
   		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){
   			 p->wr_STRCOMP(pcode__STRCOMP, bEXPRESSION2, bOptionCompareBinary, bReturn); // write pcode
   		}

   		parseInfo(p, "parsed STRCOMP");
   		_DONE_
   	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__STRCOMP, "( missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: SCREEN2
PRINTNAME: Screen
TASK: returns ASCII value at desired position of the screen
SYNTAX: SCREEN (row%,column% [,color%])
DESC: 
CODE:
CLS
PRINT "Hey"
PRINT "The ASCII value at 1,1 is"; SCREEN(1, 1)
EXAMPLES: screen2.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: PRINT, LINE, SCREEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/* *
[KBASIC][VB][QBASIC]
NAME: SCREEN
PRINTNAME: Screen
TASK: switches to a desired output
SYNTAX: SCREEN modus% [,[color%] [,[outputpage%] [,visiblepage%]]]
DESC: 
no%: no of screen. Possible values are 1 - 13
color%: (obsolete)
%outputpage: where the output operations should take
%visiblepage: this page is shown on the screen
CODE:
SCREEN 13        '320 x 200 
LINE (110, 70)-(190, 120), , 15
LINE (0, 0)-(320, 200), 3, , &HFF00
EXAMPLES: screen.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: PRINT, LINE, SCREEN2
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSCREEN(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_SCREEN = false;
  _BEGIN_
  if (!(/*bTerm_SCREEN = */parseTerm(token__SCREEN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	bool color = false;
	bool outputpage = false;
	bool visiblepage = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (bReturn){
    // variante 2

	  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__SCREEN, "expression missing"); _ERROR_ }
    if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__SCREEN, ", missing"); _ERROR_ }
	  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__SCREEN, "expression missing"); _ERROR_ }
    
    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
	    if (!(bEXPRESSION2 = fINTEGER_EXPRESSION(p))){ syntaxError(token__SCREEN, "expression missing"); _ERROR_ }
    }

 		*nReturnExpressionType = pcode__INTEGER;

 		if (bProducePcode){
			p->wr_SCREEN2(pcode__SCREEN2, bEXPRESSION2, bReturn);
 		}

 		parseInfo(p, "parsed SCREEN2");
 		_DONE_

  } else {
    // variante 1

	  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__SCREEN, "expression missing"); _ERROR_ }
    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
	    if (!(color = fINTEGER_EXPRESSION(p))){ syntaxError(token__SCREEN, "expression missing"); _ERROR_ }
    }
    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
	    if (!(outputpage = fINTEGER_EXPRESSION(p))){ syntaxError(token__SCREEN, "expression missing"); _ERROR_ }
    }
    if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
	    if (!(visiblepage = fINTEGER_EXPRESSION(p))){ syntaxError(token__SCREEN, "expression missing"); _ERROR_ }
    }
  }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SCREEN, ") missing"); _ERROR_ }

	{
 		*nReturnExpressionType = pcode__VOID;

 		if (bProducePcode){
			p->wr_SCREEN(pcode__SCREEN, color, outputpage, visiblepage);
 		}

 		parseInfo(p, "parsed SCREEN");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: MIN
PRINTNAME: Min
TASK: returns the minor value of two values
SYNTAX: MIN (numeric expression1, numeric expression2)
DESC:
CODE:
PRINT MIN(45, 4)
EXAMPLES: min.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: MAX
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fMIN(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_MIN = false;
  _BEGIN_
  if (!(/*bTerm_MIN = */parseTerm(token__MIN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__MIN, "expression missing"); _ERROR_ }
  	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__MIN, "wrong type, must be a number type"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__MIN, ", missing"); _ERROR_}

  	if (!(bEXPRESSION2 = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__MIN, "expression missing"); _ERROR_ }
  	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__MIN, "wrong type, must be a number type"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__MIN, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_MIN(pcode__MIN, bReturn);
   		}

   		parseInfo(p, "parsed MIN");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__MIN, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: MAX
PRINTNAME: Max
TASK: returns the major value of two values
SYNTAX: MAX (numeric expression1, numeric expression2)
DESC: 
CODE:
PRINT MAX(44, 3)
EXAMPLES: max.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: MIN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fMAX(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_MAX = false;
  _BEGIN_
  if (!(/*bTerm_MAX = */parseTerm(token__MAX))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__MAX, "expression missing"); _ERROR_ }
  	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__MAX, "wrong type, must be a number type"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__MAX, ", missing"); _ERROR_ }

  	if (!(bEXPRESSION2 = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__MAX, "expression missing"); _ERROR_ }
  	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__MAX, "wrong type, must be a number type"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__MAX, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_MAX(pcode__MAX, bReturn);
   		}

   		parseInfo(p, "parsed MAX");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__MAX, "( missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: SEC
PRINTNAME: Sec
TASK: returns the seconds of a date
SYNTAX: SEC (date)
DESC:
CODE:
DIM d AS DATE = DATE()
PRINT SEC(d)
EXAMPLES: sec.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: HOUR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSEC(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_SEC = false;
  _BEGIN_
  if (!(/*bTerm_SEC = */parseTerm(token__SEC))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = !fDATE_EXPRESSION(p))){ syntaxError(token__SEC, "date expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SEC, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_SEC(pcode__SEC, bReturn);
   		}

   		parseInfo(p, "parsed SEC");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__SEC, "( missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: FACT
PRINTNAME: Fact
TASK: FACT
SYNTAX: FACT
DESC: FACT
CODE:
EXAMPLES: fact.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
 
bool parser::fFACT(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_FACT = false;
  _BEGIN_
  if (!(bTerm_FACT = parseTerm(token__FACT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__FACT, "expression missing"); _ERROR_ }

  	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__FACT, "wrong type, must be a number type"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FACT, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_FACT(pcode__FACT, bReturn);
   		}

   		parseInfo(p, "parsed FACT");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__FACT, "( missing"); _ERROR_ }

	_END_
}
*/

/* *
[KBASIC][VB][QBASIC]
NAME: FRAC
PRINTNAME: Frac
TASK: FRAC
SYNTAX: FRAC
DESC: FRAC
CODE:
EXAMPLES: frac.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*

bool parser::fFRAC(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_FRAC = false;
  _BEGIN_
  if (!(bTerm_FRAC = parseTerm(token__FRAC))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__FRAC, "expression missing"); _ERROR_ }

  	if (!memory_type::isNumeric(nExpressionType)){ syntaxError(token__FRAC, "wrong type, must be a number type"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FRAC, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_FRAC(pcode__FRAC, bReturn);
   		}

   		parseInfo(p, "parsed FRAC");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__FRAC, "( missing"); _ERROR_ }

	_END_
}
*/

/* *
[KBASIC][VB][QBASIC]
NAME: LOGB
PRINTNAME: LogB
TASK: LOGB
SYNTAX: LOGB
DESC: LOGB
CODE:
EXAMPLES: logb.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLOGB(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_LOGB = false;
  _BEGIN_
  if (!(/*bTerm_LOGB = */parseTerm(token__LOGB))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__LOGB, "expression missing"); _ERROR_ }
  	if (!memory_type::isNumeric(nExpressionType)){ semanticError(token__LOGB, "wrong type, must be a number type"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LOGB, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){
 				 p->wr_LOGB(pcode__LOGB, bReturn);
   		}

   		parseInfo(p, "parsed LOGB");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__LOGB, "( missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: HYPOT
PRINTNAME: Hypot
TASK: HYPOT
SYNTAX: HYPOT
DESC: HYPOT
CODE:
EXAMPLES: hypot.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*

bool parser::fHYPOT(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_HYPOT = false;
  _BEGIN_
  if (!(bTerm_HYPOT = parseTerm(token__HYPOT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	int nExpressionType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!(bEXPRESSION = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__HYPOT, "expression missing"); _ERROR_ }
  	if (!memory_type::isNumeric(nExpressionType)){ semanticError(token__HYPOT, "wrong type, must be a number type"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__HYPOT, ", missing"); _ERROR_ }

  	if (!(bEXPRESSION2 = fEXPRESSION(p, &nExpressionType))){ syntaxError(token__HYPOT, "expression missing"); _ERROR_ }
  	if (!memory_type::isNumeric(nExpressionType)){ semanticError(token__HYPOT, "wrong type, must be a number type"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__HYPOT, ") missing"); _ERROR_ }

  	{

			*nReturnExpressionType = pcode__DOUBLE;

   		if (bProducePcode){

     				 p->wr_HYPOT(pcode__HYPOT, bReturn);
   		}

   		parseInfo(p, "parsed HYPOT");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__HYPOT, "( missing"); _ERROR_ }

	_END_
}
*/

/* *
[KBASIC][VB][QBASIC]
NAME: ISDATE
PRINTNAME: IsDate
TASK: returns true if expression represents a date
SYNTAX: ISDATE (expression)
DESC:
CODE:
PRINT ISDATE(34)
PRINT ISDATE(DATE())
EXAMPLES: isdate.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME, VARIANT, OBJECT
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISDATE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISDATE = false;
  _BEGIN_
  if (!(/*bTerm_ISDATE = */parseTerm(token__ISDATE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__ISDATE, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISDATE, ") missing"); _ERROR_}

 		if (bProducePcode){
   			p->wr_ISDATE(pcode__ISDATE, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISDATE statement");
 		_DONE_ 		
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISDATE, "( missing"); _ERROR_ }
// 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISDATE, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISEMPTY
PRINTNAME: IsEmpty
TASK: returns true if expression represents a empty value
SYNTAX: ISEMPTY (expression)
DESC:
CODE:
DIM v AS VARIANT
PRINT ISEMPTY(v)
EXAMPLES: isempty.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING, VARIANT, OBJECT
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISEMPTY(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISEMPTY = false;
  _BEGIN_
  if (!(/*bTerm_ISEMPTY = */parseTerm(token__ISEMPTY))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    
    {
      if (!fEXPRESSION(p)){ syntaxError(token__ISEMPTY, "expression missing"); _ERROR_ }
    }
	
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISEMPTY, ") missing"); _ERROR_ }


 		if (bProducePcode){
   			p->wr_ISEMPTY(pcode__ISEMPTY, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISEMPTY statement");
 		_DONE_
 	
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISEMPTY, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISEMPTY, "identifier missing or identifier not declared"); _ERROR_ }
 	////else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISEMPTY, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISNULL
PRINTNAME: IsNull
TASK: returns true if expression represents a null value
SYNTAX: ISNULL (expression)
DESC:
CODE:
DIM v AS VARIANT
v = Null
PRINT ISNULL(v)
EXAMPLES: isnull.kbasic
CATEGORY: FUNCTION, BUILTIN, VARIANT, OBJECT
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISNULL(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISNULL = false;
  _BEGIN_
  if (!(/*bTerm_ISNULL = */parseTerm(token__ISNULL))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__ISNULL, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISNULL, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISNULL(pcode__ISNULL, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISNULL statement");
 		_DONE_
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISNULL, "( missing"); _ERROR_ }
// 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISNULL, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISNUMERIC
PRINTNAME: IsNumeric
TASK: returns true if expression represents a numeric value
SYNTAX: ISNUMERIC (expression)
DESC:
CODE:
PRINT ISNUMERIC(67)
EXAMPLES: isnumeric.kbasic
CATEGORY: FUNCTION, BUILTIN, VARIANT, OBJECT
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISNUMERIC(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISNUMERIC = false;

	_BEGIN_

  if (!(/*bTerm_ISNUMERIC = */parseTerm(token__ISNUMERIC))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__ISNUMERIC, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISNUMERIC, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISNUMERIC(pcode__ISNUMERIC, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISNUMERIC statement");
 		_DONE_
 		
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISNUMERIC, "( missing"); _ERROR_ }
 	////else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISNUMERIC, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISMISSING
PRINTNAME: IsMissing
TASK: returns if an optional argument of a sub/function has not been given = is missing
SYNTAX: ISMISSING (ArgName)
DESC:
CODE:
Dim result

result = doubleit()	' returns Null.
result = doubleit(2)	' returns 4.

Function doubleit(Optional A)
	If IsMissing(A) Then
		' if no argument, then return Null
		doubleit = Null
	Else
		' if argument, the return double value
		doubleit = A * 2
	End If
End Function
EXAMPLES: ismissing.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISMISSING(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISMISSING = false;
  _BEGIN_
  if (!(/*bTerm_ISMISSING = */parseTerm(token__ISMISSING))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nType = 0;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
		// idref eigentlich nur; argument einer sub/function/method nur
		if (bIDENTIFIER = fARGUMENT(p, &nVar, &scope, &nType)){

			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 			if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISMISSING, ") missing"); _ERROR_ }

		  if (nType == token__ME){
        { semanticError(token__ISMISSING, "ISMISSING not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__ISMISSING, "ISMISSING not allowed in combination with PARENT"); _ERROR_ }
     } else {
     }
 			if (bProducePcode){
   			 p->wr_ISMISSING(pcode__ISMISSING, nVar, scope, bReturn); // write pcode
 			}

			*nReturnExpressionType = pcode__BOOLEAN;

			parseInfo(p, "parsed ISMISSING statement");
 			_DONE_
 		}
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISMISSING, "( missing"); _ERROR_ }
// 	else if (!bIDENTIFIER){ syntaxError(token__ISMISSING, "identifier missing or identifier not declared"); _ERROR_ }
 	////else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISMISSING, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ARRAY
PRINTNAME: Array
TASK: creates an array of variant values
SYNTAX: Array (list of arguments)
DESC:
If no arguments are specified, an array of zero length is created.
CODE:
Dim A As Variant
A = Array(10,20,30)
B = A(2)
EXAMPLES: array2.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fARRAY(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_ARRAY = false;
  _BEGIN_
  if (!(/*bTerm_ARRAY = */parseTerm(token__ARRAY))){ _END_ }

	


	register bool bTerm_SYM_BR_OP = false;
	register bool bTerm_SYM_BS_OP = false;
	
  if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}
  if (!bTerm_SYM_BR_OP && !(bTerm_SYM_BS_OP = parseTerm(token__SYM_BS_OP))) _END_

	bool bTerm_SYM_BR_CL = false;
	bool bTerm_SYM_BS_CL = false;
  int n = 0;

  while(true){
		if (fEXPRESSION(p)){
      n++;
     if (parseTerm(token__SYM_COMMA)){
  		} else {
 			  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){
 					break;
 				}
 			  if (!bTerm_SYM_BR_CL && (bTerm_SYM_BS_CL = parseTerm(token__SYM_BS_CL))){
 					break;
 				}
      }
    }
  }

 		if (bProducePcode){
       p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, n);
   		 p->wr_ARRAY2(pcode__ARRAY2, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__VARIANT;

		parseInfo(p, "parsed ARRAY statement");
 		_DONE_
	

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: COMMAND
PRINTNAME: Command
TASK: returns the arguments which have been given to your application by the OS while starting
SYNTAX: COMMAND() AS STRING
DESC:
CODE:
PRINT COMMAND()
EXAMPLES: command.kbasic
CATEGORY: FUNCTION, BUILTIN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCOMMAND(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_COMMAND = false;
  _BEGIN_
  if (!(/*bTerm_COMMAND = */parseTerm(token__COMMAND)) && !(/*bTerm_COMMAND = */parseTerm(token__COMMAND_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

  if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}
 
	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__COMMAND, ") missing"); _ERROR_ }

 	if (bProducePcode){
   		p->wr_COMMAND(pcode__COMMAND, bReturn); // write pcode
 	}

	*nReturnExpressionType = pcode__QSTRING;

	parseInfo(p, "parsed COMMAND statement");
 	_DONE_
 	

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CURDIR
PRINTNAME: CurDir
TASK: returns the current path
SYNTAX: CurDir[(drive As STRING)]
DESC: 
CODE:
' Windows:
' current path of C: ist "C:\WINDOWS\SYSTEM32".
' current path of D: ist "D:\kbasic".
' C: is the active drive.
Dim path
path = CurDir' returns "C:\WINDOWS\SYSTEM32".
path = CurDir("C")	' returns "C:\WINDOWS\SYSTEM32".
path = CurDir("D")	' returns "D:\kbasic".
EXAMPLES: curdir.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCURDIR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_CURDIR = false;
  _BEGIN_
  if (!(/*bTerm_CURDIR = */parseTerm(token__CURDIR)) && !(/*bTerm_CURDIR = */parseTerm(token__CURDIR_))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}
 
  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){}// syntaxError(token__CURDIR, "string expression missing"); _ERROR_ }

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CURDIR, ") missing"); _ERROR_ }

 	if (bProducePcode){
   		p->wr_CURDIR(pcode__CURDIR, bEXPRESSION, bReturn); // write pcode
 	}

	*nReturnExpressionType = pcode__QSTRING;

	parseInfo(p, "parsed CURDIR statement");
 	_DONE_
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__CURDIR, "( missing"); _ERROR_ }
// 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__CURDIR, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: CVERR
PRINTNAME: CVErr
TASK: returns a user defined error
SYNTAX: CVErr(errorno) AS VARIANT
DESC: 
CODE:
Sub test()
	Print doubleit("395.45bernd")
End Sub

Function doubleit(no)
	If IsNumeric(no) Then
		doubleit = no* 2	' return result
	Else
		doubleit = CVErr(2001)	' return user defined error
	End If
End Function
EXAMPLES: cverr.kbasic
CATEGORY: FUNCTION, BUILTIN, ERROR, CONVERSION
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fCVERR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_CVERR = false;
  _BEGIN_
  if (!(/*bTerm_CVERR = */parseTerm(token__CVERR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__CVERR, "integer expression missing"); _ERROR_ } // 
	
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CVERR, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_CVERR(pcode__CVERR, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__VARIANT;

		parseInfo(p, "parsed CVERR statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__CVERR, "( missing"); _ERROR_ }
 	////else if (!bTerm_SYM_BR_CL){ syntaxError(token__CVERR, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: DATEADD
PRINTNAME: DateAdd
TASK: add something to a date
SYNTAX: DateAdd(interval, number, date)
DESC: 
interval values:
yyyy	year
q	quarter
m	month
y	day of year
d	day
w	weekday
ww	week
h	hour
n	minute
s	second
CODE:
Dim Date1 As Date
Dim Interval As String
Dim Number As Integer
Dim Msg
Interval = "m"	
Date1 = InputBox("Input the date")
Number = InputBox("Input the number of months to add")
Msg = "New date: " & DateAdd(Interval, Number, Date1)
MsgBox Msg
EXAMPLES: dateadd.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDATEADD(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_DATEADD = false;
  _BEGIN_
  if (!(/*bTerm_DATEADD = */parseTerm(token__DATEADD))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bINTERVAL = false;
	bool bNUMBER = false;
	bool bDATE = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bINTERVAL = fSTRING_EXPRESSION(p))){ syntaxError(token__DATEADD, "string expression missing"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__DATEADD, ", missing"); _ERROR_ }

		if (!(bNUMBER = fNUMERIC_EXPRESSION(p))){ semanticError(token__DATEADD, "numeric expression missing"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__DATEADD, ", missing"); _ERROR_ }

		if (!(bDATE = fDATE_EXPRESSION(p))){ syntaxError(token__DATEADD, "date expression missing"); _ERROR_ }
	
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DATEADD, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_DATEADD(pcode__DATEADD, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__DATE;

		parseInfo(p, "parsed DATEADD statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__DATEADD, "( missing"); _ERROR_ }
 	////else if (!bTerm_SYM_BR_CL){ syntaxError(token__DATEADD, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: DATEDIFF
PRINTNAME: DateDiff
TASK: returns the number of interval laying between date1 and date2
SYNTAX: DateDiff(interval As String, date1 As Date, date2 As Date[, firstdayofweek As String[, firstweekofyear As String]])
DESC: 

interval:
yyyy	year
q	quarter
m	month
y	day of year
d	day
w	weekday
ww	week
h	hour
n	minute
s	second

firstdayofweek:
kbUseSystem	0	Sunday
kbSunday	1	Sunday (default)
kbMonday	2	Monday
kbTuesday	3	Tuesday
kbWednesday	4	Wednesday
kbThursday	5	Thursday
kbFriday	6	Friday
kbSaturday	7	Saturday

firstweekofyear:
kbUseSystem	0	Start with the week of 1 January (default).
kbFirstJan1	1	Start with the week of 1 January (default).
kbFirstFourDays	2	Start with the first week, which has at least 4 days in the new year
kbFirstFullWeek	3	Start with the first complete week of the new year

CODE:
Dim Date1 As Date	
Dim Msg
Date1 = InputBox("Input the date")
Msg = "Days till today: " & DateDiff("d", Now, Date1)
MsgBox Msg

EXAMPLES: datediff.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDATEDIFF(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_DATEDIFF = false;
  _BEGIN_
  if (!(/*bTerm_DATEDIFF = */parseTerm(token__DATEDIFF))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bINTERVAL = false;
	bool bDATE = false;

	bool firstdayofweek = false;
	bool firstweekofyear = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bINTERVAL = fSTRING_EXPRESSION(p))){ syntaxError(token__DATEDIFF, "string expression missing"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__DATEDIFF, ", missing"); _ERROR_ }

		if (!(bDATE = fDATE_EXPRESSION(p))){ syntaxError(token__DATEDIFF, "date expression missing"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__DATEDIFF, ", missing"); _ERROR_ }

		if (!(bDATE = fDATE_EXPRESSION(p))){ syntaxError(token__DATEDIFF, "date expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

			if (!(firstdayofweek = fINTEGER_EXPRESSION(p))){}

			if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

				if (!(firstweekofyear = fINTEGER_EXPRESSION(p))){}

			}

			if (!firstdayofweek && !firstweekofyear){ syntaxError(token__DATEDIFF, "integer expression missing"); _ERROR_ }
		}
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DATEDIFF, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_DATEDIFF(pcode__DATEDIFF, firstdayofweek, firstweekofyear, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__LONG;

		parseInfo(p, "parsed DATEDIFF statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__DATEDIFF, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__DATEDIFF, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: DATEPART
PRINTNAME: DatePart
TASK: returns a desired part of a date
SYNTAX: DatePart(interval, date[,firstdayofweek[, firstweekofyear]])
DESC:
interval:
yyyy	year
q	quarter
m	month
y	day of year
d	day
w	weekday
ww	week
h	hour
n	minute
s	second

firstdayofweek:
kbUseSystem	0	Sunday
kbSunday	1	Sunday (default)
kbMonday	2	Monday
kbTuesday	3	Tuesday
kbWednesday	4	Wednesday
kbThursday	5	Thursday
kbFriday	6	Friday
kbSaturday	7	Saturday

firstweekofyear:
kbUseSystem	0	Start with the week of 1 January (default).
kbFirstJan1	1	Start with the week of 1 January (default).
kbFirstFourDays	2	Start with the first week, which has at least 4 days in the new year
kbFirstFullWeek	3	Start with the first complete week of the new year

CODE:
Dim Date1 As Date	
Dim Msg	
Date1 = InputBox("Input a date:")
Msg = "quarter: " & DatePart("q", Quartal)
MsgBox Msg
EXAMPLES: datepart.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDATEPART(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_DATEPART = false;
  _BEGIN_
  if (!(/*bTerm_DATEPART = */parseTerm(token__DATEPART))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bINTERVAL = false;
	bool bDATE = false;

	bool firstdayofweek = false;
	bool firstweekofyear = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

	  if (!(bINTERVAL = fSTRING_EXPRESSION(p))){ syntaxError(token__DATEPART, "string expression missing"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__DATEPART, ", missing"); _ERROR_ }

		if (!(bDATE = fDATE_EXPRESSION(p))){ syntaxError(token__DATEPART, "date expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

			if (!(firstdayofweek = fINTEGER_EXPRESSION(p))){}

			if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

				if (!(firstweekofyear = fINTEGER_EXPRESSION(p))){}

			}

			if (!firstdayofweek && !firstweekofyear){ syntaxError(token__DATEPART, "integer expression missing"); _ERROR_ }
		}
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DATEPART, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_DATEPART(pcode__DATEPART, firstdayofweek, firstweekofyear, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__INTEGER;

		parseInfo(p, "parsed DATEPART statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__DATEPART, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__DATEPART, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: DATESERIAL
PRINTNAME: DateSerial
TASK: converts a date given by year, month and day into a big number
SYNTAX: DateSerial(year As Integer, month As Integer, day As Integer) As Date
DESC: 
CODE:
Dim Date1
Date1 = DateSerial(1969, 2, 12)	' return Date1
EXAMPLES: dateserial.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDATESERIAL(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_DATESERIAL = false;
  _BEGIN_
  if (!(/*bTerm_DATESERIAL = */parseTerm(token__DATESERIAL))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bNUMBER = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
		if (!(bNUMBER = fNUMERIC_EXPRESSION(p))){ syntaxError(token__DATESERIAL, "numeric expression missing"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__DATESERIAL, ", missing"); _ERROR_ }

		if (!(bNUMBER = fNUMERIC_EXPRESSION(p))){ syntaxError(token__DATESERIAL, "numeric expression missing"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__DATESERIAL, ", missing"); _ERROR_ }

		if (!(bNUMBER = fNUMERIC_EXPRESSION(p))){ syntaxError(token__DATESERIAL, "numeric expression missing"); _ERROR_ }
	
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DATESERIAL, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_DATESERIAL(pcode__DATESERIAL, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__DATE;

		parseInfo(p, "parsed DATESERIAL statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__DATESERIAL, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__DATESERIAL, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: DATEVALUE
PRINTNAME: DateValue
TASK: converts a date given in a string into a date type
SYNTAX: DateValue(Date As String)
DESC: DATEVALUE
CODE:
Dim Date1
Date1 = DateValue("2 March 1979")
EXAMPLES: datevalue.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDATEVALUE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_DATEVALUE = false;
  _BEGIN_
  if (!(/*bTerm_DATEVALUE = */parseTerm(token__DATEVALUE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

 	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
		if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__DATEVALUE, "string expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DATEVALUE, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_DATEVALUE(pcode__DATEVALUE, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__DATE;

		parseInfo(p, "parsed DATEVALUE statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__DATEVALUE, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__DATEVALUE, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: DIR
PRINTNAME: Dir
TASK: DIR
SYNTAX: Dir[(path[, attribute])]
DESC:
attribute:
kbNormal	0	normal
kbHidden	2	hidden
kbSystem	4	system file
kbVolume	8	volume name
kbDirectory	16	directory
CODE:
file1 = Dir("C:\WINDOWS\*.INI")

Path1 = "c:\"	
Name1 = Dir(Path1, kbDirectory)	' first entry
Do While Name1 <> ""	' loop
	If Name1 <> "." And Name1 <> ".." Then
		If (GetAttr(Path1 & Name1) And kbDirectory) = kbDirectory Then
			Print Name1	
		End If
	End If
	Name1 = Dir	' next entry
Loop

EXAMPLES: dir.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDIR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_DIR = false;
  _BEGIN_
  if (!(/*bTerm_DIR = */parseTerm(token__DIR)) && !(/*bTerm_DIR = */parseTerm(token__DIR_))){ _END_ }

	if (peekToken() == token__SYM_DOT) _END_ // could be the dir class of the framework

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}
 
  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){}// syntaxError(token__DIR, "string expression missing"); _ERROR_ }
	
 	 if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

     if ((bEXPRESSION2 = fNUMERIC_EXPRESSION(p))){}
     
     if (bEXPRESSION && !bEXPRESSION2){
       //syntaxError(token__DIR, "numeric expression missing"); _ERROR_ 
     } else if (!bEXPRESSION && bEXPRESSION2){
       syntaxError(token__DIR, "string expression missing"); _ERROR_ 
     }
	
	}

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DIR, ") missing"); _ERROR_ }

 	if (bProducePcode){
   		p->wr_DIR(pcode__DIR, bEXPRESSION, bEXPRESSION2, bReturn); // write pcode
 	}

	*nReturnExpressionType = pcode__QSTRING;

	parseInfo(p, "parsed DIR statement");

  _DONE_
}

/* *
[KBASIC][VB][QBASIC]
NAME: FILES
PRINTNAME: Files
TASK: directory listing
SYNTAX: FILES
DESC: 
CODE:
PRINT "listening of directory"
FILES
EXAMPLES: files.kbasic
CATEGORY: SUB, BUILTIN, FILE
SEEALSO: MKDIR, CHDIR, RMDIR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFILES(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[*]
[*]
[*]
*/
{

	//bool bTerm_FILES = false;
  _BEGIN_
  if (!(/*bTerm_FILES = */parseTerm(token__FILES))){ _END_ }

	

	bool bEXPRESSION = false;


 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (bEXPRESSION = fSTRING_EXPRESSION(p)){}

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INKEY_, ") missing"); _ERROR_ }

	{
 		if (bProducePcode){
			 p->wr_FILES(pcode__FILES, bEXPRESSION, bReturn);
 		}

    *nReturnExpressionType = pcode__QSTRING;

 		parseInfo(p, "parsed FILES");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: FILEATTR
PRINTNAME: FileAttr
TASK: returns the access mode for an opened file
SYNTAX: FileAttr(filenumber, returntype)
DESC:
if returntype = 1 then the following values can be returned:
Input	1
Output	2
Random	4
Append	8
Binary	32
CODE:
Dim filehandle, Mode
filehandle = 1
Open "file1" For Append As filehandle
Mode = FileAttr(filehandle, 1)	' returns 8 (Append).
Close filehandle	' close file
EXAMPLES: fileattr.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: OPEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFILEATTR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_FILEATTR = false;
  _BEGIN_
  if (!(/*bTerm_FILEATTR = */parseTerm(token__FILEATTR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__FILEATTR, "expression missing"); _ERROR_ }

 	  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__FILEATTR, ", missing"); _ERROR_ }

		if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__FILEATTR, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FILEATTR, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_FILEATTR(pcode__FILEATTR, bReturn);
 		}

		*nReturnExpressionType = pcode__LONG;

 		parseInfo(p, "parsed FILEATTR");
 		_DONE_
	}

			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__FILEATTR, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__FILEATTR, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: FILEDATETIME
PRINTNAME: FileDateTime
TASK: returns the date of the last change of a file
SYNTAX: FileDateTime(pathfile)
DESC:
CODE:
Print FileDateTime("TSTFILE")
EXAMPLES: filedatetime.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME, FILE
SEEALSO: filedatetime.kbasic
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFILEDATETIME(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_FILEDATETIME = false;
  _BEGIN_
  if (!(/*bTerm_FILEDATETIME = */parseTerm(token__FILEDATETIME))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__FILEDATETIME, "string expression missing"); _ERROR_ }
	
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FILEDATETIME, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_FILEDATETIME(pcode__FILEDATETIME, bReturn);
 		}


		*nReturnExpressionType = pcode__DATE;

 		parseInfo(p, "parsed FILEDATETIME");
 		_DONE_
	}

			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__FILEDATETIME, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__FILEDATETIME, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: FILELEN
PRINTNAME: FileLen
TASK: returns the length of a file in bytes
SYNTAX: FileLen(pathfile)
DESC:
CODE:
Print FileLen("TSTFILE")
EXAMPLES: filelen.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFILELEN(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_FILELEN = false;
  _BEGIN_
  if (!(/*bTerm_FILELEN = */parseTerm(token__FILELEN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__FILELEN, "string expression missing"); _ERROR_ }
	
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FILELEN, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_FILELEN(pcode__FILELEN, bReturn);
 		}


		*nReturnExpressionType = pcode__LONG;

 		parseInfo(p, "parsed FILELEN");
 		_DONE_
	}

			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__FILELEN, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__FILELEN, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: FORMAT
PRINTNAME: Format
TASK: formats an expression
SYNTAX: Format(expression[, format[, firstdayofweek[, firstweekofyear]]])
DESC:
firstdayofweek:
kbUseSystem	0	Sunday
kbSunday	1	Sunday (default)
kbMonday	2	Monday
kbTuesday	3	Tuesday
kbWednesday	4	Wednesday
kbThursday	5	Thursday
kbFriday	6	Friday
kbSaturday	7	Saturday

firstweekofyear:
kbUseSystem	0	Start with the week of 1 January (default).
kbFirstJan1	1	Start with the week of 1 January (default).
kbFirstFourDays	2	Start with the first week, which has at least 4 days in the new year
kbFirstFullWeek	3	Start with the first complete week of the new year

CODE:
Dim Time1, Date1, s
Time1 = #17:04:23#
Date1 = #January 27, 1993#

' current system time, long format
s = Format(Time, "Long Time")

' current system date, long format
s = Format(Date, "Long Date")

s = Format(Time1, "h:m:s")	' returns "17:4:23".
s = Format(Time1, "hh:mm:ss AMPM")	' returns "17:04:23".

s = Format(Date1, "dddd, mmm d yyyy")	' returns "Wednesday,
	' 27 January 1993".
' if no format is given, the string expression is unchanged returned
s = Format(23)	' Liefert "23".

' user defined formats
s = Format(5459.4, "##,##0.00")	' returns "5.459,40".
s = Format(334.9, "###0.00")	' returns "334,90".
s = Format(5, "0.00%")	' returns "500,00%".

s = Format("BANANE", "<")	' Liefert "banane".
s = Format("apple", ">")	' Liefert "APPLE".
EXAMPLES: format.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFORMAT(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_FORMAT = false;
  _BEGIN_
  if (!(/*bTerm_FORMAT = */parseTerm(token__FORMAT))){ _END_ }

	
 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bFORMAT = false;

	bool fillchar = false;
	bool rightaligned = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!bObjectFake && (!(bEXPRESSION = fEXPRESSION(p)))){ syntaxError(token__FORMAT, "expression missing"); _ERROR_ }

    if (!bObjectFake) bTerm_COMMA = parseTerm(token__SYM_COMMA);

    if (bObjectFake || bTerm_COMMA){

			if (!(bFORMAT = fSTRING_EXPRESSION(p))){ syntaxError(token__FORMAT, "expression missing"); _ERROR_ }

 			if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

				if (!(fillchar = fSTRING_EXPRESSION(p))){}

				if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

					if (!(rightaligned = fBOOLEAN_EXPRESSION(p))){}

				}

				if (!fillchar && !rightaligned){ syntaxError(token__FORMAT, "expression missing"); _ERROR_ }
			}
		}

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FORMAT, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_FORMAT(pcode__FORMAT, bFORMAT, fillchar, rightaligned, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed FORMAT statement");
 		_DONE_
 	}
  
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__FORMAT, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__FORMAT, ") missing"); _ERROR_ }

	_END_
}

/*
bool parser::fFORMATCURRENCY(pcode *p, int *nReturnExpressionType, bool bReturn)
/ *
[*]
[VB]
[*]
[*]
* /
{
  _BEGIN_
  if (!(parseTerm(token__FORMATCURRENCY))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bFORMAT = false;

	bool firstdayofweek = false;
	bool firstweekofyear = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__FORMATCURRENCY, "expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

			if (!(bFORMAT = fSTRING_EXPRESSION(p))){ syntaxError(token__FORMATCURRENCY, "date expression missing"); _ERROR_ }

 			if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

				if (!(firstdayofweek = fINTEGER_EXPRESSION(p))){}

				if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

					if (!(firstweekofyear = fINTEGER_EXPRESSION(p))){}

				}

				if (!firstdayofweek && !firstweekofyear){ syntaxError(token__FORMATCURRENCY, "integer expression missing"); _ERROR_ }
			}
		}
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FORMATCURRENCY, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 //p->wr_FORMATCURRENCY(pcode__FORMATCURRENCY, bFORMAT, firstdayofweek, firstweekofyear, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed FORMATCURRENCY statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__FORMATCURRENCY, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__FORMATCURRENCY, ") missing"); _ERROR_ }

	_END_
}

bool parser::fFORMATDATETIME(pcode *p, int *nReturnExpressionType, bool bReturn)
/ *
[*]
[VB]
[*]
[*]
* /
{
  _BEGIN_
  if (!(parseTerm(token__FORMATDATETIME))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bFORMAT = false;

	bool firstdayofweek = false;
	bool firstweekofyear = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__FORMATDATETIME, "expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

			if (!(bFORMAT = fSTRING_EXPRESSION(p))){ syntaxError(token__FORMATDATETIME, "date expression missing"); _ERROR_ }

 			if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

				if (!(firstdayofweek = fINTEGER_EXPRESSION(p))){}

				if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

					if (!(firstweekofyear = fINTEGER_EXPRESSION(p))){}

				}

				if (!firstdayofweek && !firstweekofyear){ syntaxError(token__FORMATDATETIME, "integer expression missing"); _ERROR_ }
			}
		}
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FORMATDATETIME, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 //p->wr_FORMATDATETIME(pcode__FORMATDATETIME, bFORMAT, firstdayofweek, firstweekofyear, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed FORMATDATETIME statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__FORMATDATETIME, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__FORMATDATETIME, ") missing"); _ERROR_ }

	_END_
}

bool parser::fFORMATNUMBER(pcode *p, int *nReturnExpressionType, bool bReturn)
/ *
[*]
[VB]
[*]
[*]
* /
{
  _BEGIN_
  if (!(parseTerm(token__FORMATNUMBER))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bFORMAT = false;

	bool firstdayofweek = false;
	bool firstweekofyear = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__FORMATNUMBER, "expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

			if (!(bFORMAT = fSTRING_EXPRESSION(p))){ syntaxError(token__FORMATNUMBER, "date expression missing"); _ERROR_ }

 			if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

				if (!(firstdayofweek = fINTEGER_EXPRESSION(p))){}

				if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

					if (!(firstweekofyear = fINTEGER_EXPRESSION(p))){}

				}

				if (!firstdayofweek && !firstweekofyear){ syntaxError(token__FORMATNUMBER, "integer expression missing"); _ERROR_ }
			}
		}
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FORMATNUMBER, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 //p->wr_FORMATNUMBER(pcode__FORMATNUMBER, bFORMAT, firstdayofweek, firstweekofyear, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed FORMATNUMBER statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__FORMATNUMBER, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__FORMATNUMBER, ") missing"); _ERROR_ }

	_END_
}

bool parser::fFORMATPERCENT(pcode *p, int *nReturnExpressionType, bool bReturn)
/ *
[*]
[VB]
[*]
[*]
* /
{
  _BEGIN_
  if (!(parseTerm(token__FORMATPERCENT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bFORMAT = false;

	bool firstdayofweek = false;
	bool firstweekofyear = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__FORMATPERCENT, "expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

			if (!(bFORMAT = fSTRING_EXPRESSION(p))){ syntaxError(token__FORMATPERCENT, "date expression missing"); _ERROR_ }

 			if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

				if (!(firstdayofweek = fINTEGER_EXPRESSION(p))){}

				if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

					if (!(firstweekofyear = fINTEGER_EXPRESSION(p))){}

				}

				if (!firstdayofweek && !firstweekofyear){ syntaxError(token__FORMATPERCENT, "integer expression missing"); _ERROR_ }
			}
		}
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FORMATPERCENT, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 //p->wr_FORMATPERCENT(pcode__FORMATPERCENT, bFORMAT, firstdayofweek, firstweekofyear, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed FORMATPERCENT statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__FORMATPERCENT, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__FORMATPERCENT, ") missing"); _ERROR_ }

	_END_
}

*/
bool parser::fMONTHNAME(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{
  _BEGIN_
  if (!(parseTerm(token__MONTHNAME))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bFORMAT = false;

	bool firstdayofweek = false;
	bool firstweekofyear = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__MONTHNAME, "expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

			if (!(bFORMAT = fBOOLEAN_EXPRESSION(p))){
			  if (!(bFORMAT = fSTRING_EXPRESSION(p))){ syntaxError(token__MONTHNAME, "expression missing"); _ERROR_ }
      }
/*
 			if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

				if (!(firstdayofweek = fINTEGER_EXPRESSION(p))){}

				if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

					if (!(firstweekofyear = fINTEGER_EXPRESSION(p))){}

				}

				if (!firstdayofweek && !firstweekofyear){ syntaxError(token__MONTHNAME, "integer expression missing"); _ERROR_ }
			}
      */
		}
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__MONTHNAME, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_MONTHNAME(pcode__MONTHNAME, bFORMAT, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed MONTHNAME statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__MONTHNAME, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__MONTHNAME, ") missing"); _ERROR_ }

	_END_
}

bool parser::fDAYNAME(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{
  _BEGIN_
  if (!(parseTerm(token__DAYNAME))){ _END_ }
	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bFORMAT = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__DAYNAME, "expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

			if (!(bFORMAT = fSTRING_EXPRESSION(p))){ syntaxError(token__DAYNAME, "string expression missing"); _ERROR_ }

		}
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DAYNAME, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_DAYNAME(pcode__DAYNAME, bFORMAT, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed DAYNAME statement");
 		_DONE_
 	}
	
	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: WEEKDAYNAME
PRINTNAME: WeekdayName
TASK: returns the name of the given weekday
SYNTAX: WeekdayName (weekday,  [shortname, [firstDay]] )
DESC:
CODE:
EXAMPLES: weekdayname.kbasic
CATEGORY: FUNCTION, BUILTIN, WEEKDAY
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fWEEKDAYNAME(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{
  _BEGIN_
  if (!(parseTerm(token__WEEKDAYNAME))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bShorty = false;

	bool firstdayofweek = false;	

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
	  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__WEEKDAYNAME, "expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

      if (!(bShorty = fBOOLEAN_EXPRESSION(p))){}// syntaxError(token__WEEKDAYNAME, "boolean expression missing"); _ERROR_ }

 			if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

				if (!(firstdayofweek = fINTEGER_EXPRESSION(p))){}

			}
		}
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__WEEKDAYNAME, ") missing"); _ERROR_ }

 		if (bProducePcode){
   		 p->wr_WEEKDAYNAME(pcode__WEEKDAYNAME, bShorty, firstdayofweek, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed WEEKDAYNAME statement");
 		_DONE_
 	}
	
			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__WEEKDAYNAME, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__WEEKDAYNAME, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: FREEFILE
PRINTNAME: FreeFile
TASK: returns the next free available file handle 
SYNTAX: FreeFile[(range)]
DESC:
CODE:
Dim Index1, filehandle
For Index1 = 1 To 5

  filehandle = FreeFile	' next free available file handle 

	Open "TEST" & Index1 For Output As #filehandle
  Write #filehandle, "example text."
	Close #filehandle	
Next

EXAMPLES: freefile.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: OPEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFREEFILE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
- rangenumber not supported
[*]
[*]
*/
{

	//bool bTerm_FREEFILE = false;
  _BEGIN_
  if (!(/*bTerm_FREEFILE = */parseTerm(token__FREEFILE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){}// syntaxError(token__FREEFILE, "integer expression missing"); _ERROR_ }

 			 if (bEXPRESSION && !bTerm_SYM_BR_OP){ syntaxError(token__FREEFILE, "( missing"); _ERROR_ }
 	else if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FREEFILE, ") missing"); _ERROR_ }

 	if (bProducePcode){

   		 p->wr_FREEFILE(pcode__FREEFILE, bEXPRESSION, bReturn);
 	}

	*nReturnExpressionType = pcode__INTEGER;

 	parseInfo(p, "parsed FREEFILE");
 	_DONE_


	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: GETATTR
PRINTNAME: GetAttr
TASK: returns attributes of files or directories
SYNTAX: GetAttr(pathname)
DESC:
possible return values:
kbNormal	0	normal
kbReadOnly	1	read only file
kbHidden	2	hidden file
kbSystem	4	system file (not supported yet)
kbDirectory	16	directory (not supported yet)
kbArchive	32 (not supported yet)
CODE:
Dim Attr1
' "hidden" has been set for TSTFILE
Attr1 = GetAttr("TSTFILE")	' returns 2.
EXAMPLES: getattr.kbasic
CATEGORY: FUNCTION, BUILTIN, FILE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fGETATTR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_GETATTR = false;
  _BEGIN_
  if (!(/*bTerm_GETATTR = */parseTerm(token__GETATTR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__GETATTR, "string expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__GETATTR, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_GETATTR(pcode__GETATTR, bReturn);
 		}


		*nReturnExpressionType = pcode__INTEGER;

 		parseInfo(p, "parsed GETATTR");
 		_DONE_
	}

			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__GETATTR, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__GETATTR, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: HOUR
PRINTNAME: Hour
TASK: returns the hour part of an expression
SYNTAX: HOUR(expression)
DESC:
CODE:
Dim Time1, Hour1
Time1 = #4:35:17 PM#
Hour1 = Hour(Time1)
EXAMPLES: hour.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fHOUR(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

	//bool bTerm_HOUR = false;
  _BEGIN_
  if (!(/*bTerm_HOUR = */parseTerm(token__HOUR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(token__HOUR, "date expression missing"); _ERROR_ }

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__HOUR, ") missing"); _ERROR_ }


 	if (bProducePcode){

   		 p->wr_HOUR(pcode__HOUR, bReturn);
 	}


	*nReturnExpressionType = pcode__INTEGER;

 	parseInfo(p, "parsed HOUR");
 	_DONE_


	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: DAY
PRINTNAME: Day
TASK: returns the day part of an expression
SYNTAX: DAY(expression)
DESC:
CODE:
Dim Date1, Day1
Date1 = #12 February 1959#
Day1 = Day(Date1)	' --> 12
EXAMPLES: day.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fDAY(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_DAY = false;
  _BEGIN_
  if (!(/*bTerm_DAY = */parseTerm(token__DAY))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__DAY, "date expression missing"); _ERROR_ }

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DAY, ") missing"); _ERROR_ }


 	if (bProducePcode){
    p->wr_DAY(pcode__DAY, bReturn);
 	}


	*nReturnExpressionType = pcode__INTEGER;

 	parseInfo(p, "parsed DAY");
 	_DONE_


	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: INPUTBOX
PRINTNAME: InputBox
TASK: input box on screen
SYNTAX: InputBox(prompt[, title] [, default])
DESC:
CODE:
Dim Msg, Titel, default, Wert1

Msg = "Input value between 1 and 3"
Titel = "InputBox-Demo"
default = "1"	

Wert1 = InputBox(Msg, Titel, default)
EXAMPLES: inputbox.kbasic
CATEGORY: FUNCTION, BUILTIN, VARIABLE, SCREEN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fINPUTBOX(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_INPUTBOX = false;
  _BEGIN_
  if (!(/*bTerm_INPUTBOX = */parseTerm(token__INPUTBOX))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool prompt = false;
	bool title = false;
	bool default_ = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP));
  
  {

		if (!(prompt = fSTRING_EXPRESSION(p))){ syntaxError(token__INPUTBOX, "string expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){
			
			if ((title = fSTRING_EXPRESSION(p))){}

	 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){
	
				if ((default_ = fSTRING_EXPRESSION(p))){}

			}

			if (!title && !default_){ syntaxError(token__INPUTBOX, "string expression missing"); _ERROR_ }
		}

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INPUTBOX, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_INPUTBOX(pcode__INPUTBOX, title, default_, bReturn);
 		}

		*nReturnExpressionType = pcode__QSTRING;

 		parseInfo(p, "parsed INPUTBOX");
 		_DONE_
	}

			 ////if (!bTerm_SYM_BR_OP){ syntaxError(token__INPUTBOX, "( missing"); _ERROR_ }
 	////else if (!bTerm_SYM_BR_CL){ syntaxError(token__INPUTBOX, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: MSGBOX
PRINTNAME: MsgBox
TASK: print message in dialog box on screen
SYNTAX: MsgBox(prompt[, buttons] [, title])
DESC:
buttons:
kbOKOnly	0	  show only [OK].
kbOKCancel	1	     show [OK] and [Cancel]
kbAbortRetryIgnore	2	
kbYesNoCancel	3	
kbYesNo	4	
kbRetryCancel	5	
kbCritical	16	Stop symbol
kbQuestion	32	question mark symbol
kbExclamation	48	exclamation mark symbol
kbInformation	64	information mark symbol
kbDefaultButton1	0	
kbDefaultButton2	256	
kbDefaultButton3	512	

return values:
kbOK	1	OK
kbCancel	2 Cancel
kbAbort	3	Abort
kbRetry	4	Retry
kbIgnore	5	Ignore
kbYes	6	Yes
kbNo	7	No
CODE:
answer = MsgBox("Hi", kbOKOnly, "Question")
EXAMPLES: msgbox.kbasic
CATEGORY: FUNCTION, BUILTIN, VARIABLE, SCREEN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fMSGBOX(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_MSGBOX = false;
  _BEGIN_
  if (!(/*bTerm_MSGBOX = */parseTerm(token__MSGBOX))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool prompt = false;
	bool buttons = false;
	bool title = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP));
  
  {

		if (!(prompt = fEXPRESSION(p))){ syntaxError(token__MSGBOX, "string expression missing"); _ERROR_ }

 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){
			
			if ((buttons = fNUMERIC_EXPRESSION(p))){}

	 	  if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){
	
				if ((title = fSTRING_EXPRESSION(p))){}
        else if (!title){ syntaxError(token__MSGBOX, "string expression missing"); _ERROR_ }

			}

			//if (!buttons){ syntaxError(token__MSGBOX, "numeric expression missing"); _ERROR_ }
			
		}

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__MSGBOX, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_MSGBOX(pcode__MSGBOX, buttons, title, bReturn);
 		}

		*nReturnExpressionType = pcode__INTEGER;

 		parseInfo(p, "parsed MSGBOX");
 		_DONE_
	}

		//	 //if (!bTerm_SYM_BR_OP){ syntaxError(token__MSGBOX, "( missing"); _ERROR_ }
  //if (bTerm_SYM_BR_OP &&!bTerm_SYM_BR_CL){ syntaxError(token__MSGBOX, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISERROR
PRINTNAME: IsError
TASK: returns true if the expression represents an error type
SYNTAX: ISERROR(expression) AS BOOLEAN
DESC:
CODE:
Dim result, Test1
result = Benutzerfunktion()
Test1 = IsError(result)	' return true.
EXAMPLES: iserror.kbasic
CATEGORY: FUNCTION, BUILTIN, ERROR, VARIANT, OBJECT
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISERROR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISERROR = false;
  _BEGIN_
  if (!(/*bTerm_ISERROR = */parseTerm(token__ISERROR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__ISERROR, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISERROR, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISERROR(pcode__ISERROR, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISERROR statement");
 		_DONE_
 	
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISERROR, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISERROR, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISARRAY
PRINTNAME: IsArray
TASK: returns true if a variable represents an array type
SYNTAX: ISARRAY(variable) AS BOOLEAN
DESC:
CODE:
Dim array1(1 To 5) As Integer, array2, Test1
array2 = Array(1, 2, 3)
Test1 = IsArray(array1)	' returns True.
Test1 = IsArray(array2)	' returns True.
EXAMPLES: isarray.kbasic
CATEGORY: FUNCTION, BUILTIN, ARRAY, VARIANT, OBJECT
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISARRAY(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{
	//bool bTerm_ISARRAY = false;
  _BEGIN_
  if (!(/*bTerm_ISARRAY = */parseTerm(token__ISARRAY))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!fEXPRESSION(p)){ syntaxError(token__ISARRAY, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISARRAY, ") missing"); _ERROR_ }


 		if (bProducePcode){
   		p->wr_ISARRAY(pcode__ISARRAY, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISARRAY statement");
 		_DONE_
  
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISARRAY, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISARRAY, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISARRAY, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISBOOLEAN
PRINTNAME: IsBoolean
TASK: returns true if a variable represents a boolean type
SYNTAX: ISBOOLEAN(variable) AS BOOLEAN
DESC:
CODE:
EXAMPLES: isboolean.kbasic
CATEGORY: FUNCTION, BUILTIN, OBJECT, BOOLEAN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISBOOLEAN(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISBOOLEAN = false;
  _BEGIN_
  if (!(/*bTerm_ISBOOLEAN = */parseTerm(token__ISBOOLEAN))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
		if (!fEXPRESSION(p)){ syntaxError(token__ISBOOLEAN, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISBOOLEAN, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISBOOLEAN(pcode__ISBOOLEAN, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISBOOLEAN statement");
 		_DONE_
 	
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISBOOLEAN, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISBOOLEAN, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISBOOLEAN, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISBYTE
PRINTNAME: IsByte
TASK: returns true if a variable represents a byte type
SYNTAX: ISBYTE(variable) AS BOOLEAN
DESC:
CODE:
EXAMPLES: isbyte.kbasic
CATEGORY: FUNCTION, BUILTIN, OBJECT, BYTE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISBYTE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISBYTE = false;
  _BEGIN_
  if (!(/*bTerm_ISBYTE = */parseTerm(token__ISBYTE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
		if (!fEXPRESSION(p)){ syntaxError(token__ISBYTE, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISBYTE, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISBYTE(pcode__ISBYTE, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISBYTE statement");
 		_DONE_
 	}
	
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISBYTE, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISBYTE, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISBYTE, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISDOUBLE
PRINTNAME: IsDouble
TASK: returns true if a variable represents a double type
SYNTAX: ISDOUBLE(variable) AS BOOLEAN
DESC:
CODE:
EXAMPLES: isdouble.kbasic
CATEGORY: FUNCTION, BUILTIN, OBJECT, DOUBLE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISDOUBLE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISDOUBLE = false;
  _BEGIN_
  if (!(/*bTerm_ISDOUBLE = */parseTerm(token__ISDOUBLE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
		if (!fEXPRESSION(p)){ syntaxError(token__ISDOUBLE, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISDOUBLE, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISDOUBLE(pcode__ISDOUBLE, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISDOUBLE statement");
 		_DONE_
 	}

 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISDOUBLE, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISDOUBLE, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISDOUBLE, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISINTEGER
PRINTNAME: IsInteger
TASK: returns true if a variable represents a integer type
SYNTAX: ISINTEGER(variable) AS BOOLEAN
DESC:
CODE:
EXAMPLES: isinteger.kbasic
CATEGORY: FUNCTION, BUILTIN, OBJECT, INTEGER
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISINTEGER(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISINTEGER = false;
  _BEGIN_
  if (!(/*bTerm_ISINTEGER = */parseTerm(token__ISINTEGER))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
		if (!fEXPRESSION(p)){ syntaxError(token__ISINTEGER, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISINTEGER, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISINTEGER(pcode__ISINTEGER, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISINTEGER statement");
 		_DONE_
 	}
	
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISINTEGER, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISINTEGER, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISINTEGER, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISSHORT
PRINTNAME: IsShort
TASK: returns true if a variable represents a short type
SYNTAX: ISSHORT(variable) AS BOOLEAN
DESC:
CODE:
EXAMPLES: isshort.kbasic
CATEGORY: FUNCTION, BUILTIN, OBJECT, SHORT, INTEGER
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISSHORT(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISSHORT = false;
  _BEGIN_
  if (!(/*bTerm_ISSHORT = */parseTerm(token__ISSHORT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!fEXPRESSION(p)){ syntaxError(token__ISSHORT, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISSHORT, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISSHORT(pcode__ISSHORT, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISSHORT statement");
 		_DONE_
 	}
	
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISSHORT, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISSHORT, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISSHORT, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISSINGLE
PRINTNAME: IsSingle
TASK: returns true if a variable represents a single type
SYNTAX: ISSINGLE(variable) AS BOOLEAN
DESC:
CODE:
EXAMPLES: issingle.kbasic
CATEGORY: FUNCTION, BUILTIN, OBJECT, INTEGER
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISSINGLE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISSINGLE = false;
  _BEGIN_
  if (!(/*bTerm_ISSINGLE = */parseTerm(token__ISSINGLE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!fEXPRESSION(p)){ syntaxError(token__ISSINGLE, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISSINGLE, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISSINGLE(pcode__ISSINGLE, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISSINGLE statement");
 		_DONE_
 	}

 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISSINGLE, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISSINGLE, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISSINGLE, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISLONG
PRINTNAME: IsLong
TASK: returns true if a variable represents a long type
SYNTAX: ISLONG(variable) AS BOOLEAN
DESC:
CODE:
EXAMPLES: islong.kbasic
CATEGORY: FUNCTION, BUILTIN, OBJECT, LONG, INTEGER
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISLONG(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISLONG = false;
  _BEGIN_
  if (!(/*bTerm_ISLONG = */parseTerm(token__ISLONG))){ _END_ }

	
 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!fEXPRESSION(p)){ syntaxError(token__ISLONG, "expression missing"); _ERROR_ }

    		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISLONG, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISLONG(pcode__ISLONG, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISLONG statement");
 		_DONE_
 	}

 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISLONG, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISLONG, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISLONG, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISSTRING
PRINTNAME: IsString
TASK: returns true if a variable represents a string type
SYNTAX: ISSTRING(variable) AS BOOLEAN
DESC:
CODE:
EXAMPLES: isstring.kbasic
CATEGORY: FUNCTION, BUILTIN, OBJECT, STRING, INTEGER
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISSTRING(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISSTRING = false;
  _BEGIN_
  if (!(/*bTerm_ISSTRING = */parseTerm(token__ISSTRING))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!fEXPRESSION(p)){ syntaxError(token__ISSTRING, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISSTRING, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISSTRING(pcode__ISSTRING, nVar, scope, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISSTRING statement");
 		_DONE_
 	}

 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISSTRING, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISSTRING, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISSTRING, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISVARIANT
PRINTNAME: IsVariant
TASK: returns true if a variable represents a variant type
SYNTAX: ISVARIANT(variable) AS BOOLEAN
DESC:
CODE:
EXAMPLES: isvariant.kbasic
CATEGORY: FUNCTION, BUILTIN, OBJECT, VARIANT, INTEGER
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISVARIANT(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISVARIANT = false;
  _BEGIN_
  if (!(/*bTerm_ISVARIANT = */parseTerm(token__ISVARIANT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
   
		if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &a)){

			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 			if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISVARIANT, ") missing"); _ERROR_ }

		  if (nType == token__ME){
        { semanticError(token__ISVARIANT, "ISVARIANT not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__ISVARIANT, "ISVARIANT not allowed in combination with PARENT"); _ERROR_ }
     } else {
     }

 			if (bProducePcode){
   			 p->wr_ISVARIANT(pcode__ISVARIANT, nVar, scope, bReturn); // write pcode
 			}

			*nReturnExpressionType = pcode__BOOLEAN;

			parseInfo(p, "parsed ISVARIANT statement");
 			_DONE_
 		}
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISVARIANT, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__ISVARIANT, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISVARIANT, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: LOC
PRINTNAME: LOC
TASK: returns the current position for reading or writing in a file
SYNTAX: LOC(filehandle)
DESC:
CODE:
Dim Position1, Line1
Open "file1" For Binary As #1
Do While Not EOF(1)
	Line1 = Line1 & Input(1, #1)	
	Position1 = Loc(1)	

  Print Line1; Tab; Position1
Loop
Close #1
EXAMPLES: loc.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: EOF, SEEK
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fLOC(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{

	//bool bTerm_LOC = false;
  _BEGIN_
  if (!(/*bTerm_LOC = */parseTerm(token__LOC))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__LOC, "integer expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LOC, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_LOC(pcode__LOC, bReturn);
 		}


		*nReturnExpressionType = pcode__LONG;

 		parseInfo(p, "parsed LOC");
 		_DONE_

	}

 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__LOC, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__LOC, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: MINUTE
PRINTNAME: Minute
TASK: returns the minute part of a time expression
SYNTAX: MINUTE(date) AS INTEGER
DESC:
CODE:
Dim Time1, Minute1
Time1 = #4:35:17 PM#	
Minute1 = Minute(Time1)	' Minute1 contains 35.
EXAMPLES: minute.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fMINUTE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_MINUTE = false;
  _BEGIN_
  if (!(/*bTerm_MINUTE = */parseTerm(token__MINUTE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(token__MINUTE, "date expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__MINUTE, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_MINUTE(pcode__MINUTE, bReturn);
 		}


		*nReturnExpressionType = pcode__INTEGER;

 		parseInfo(p, "parsed MINUTE");
 		_DONE_

	}


 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__MINUTE, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__MINUTE, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: MONTH
PRINTNAME: Month
TASK: returns the month part of an expression
SYNTAX: MONTH(expression)
DESC:
CODE:
Dim Date1, Month1
Date1 = #February 12, 1979#
Month1 = Month(Date1)	' Month1 contains 2.
EXAMPLES: month.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fMONTH(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_MONTH = false;
  _BEGIN_
  if (!(/*bTerm_MONTH = */parseTerm(token__MONTH))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(token__MONTH, "date expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__MONTH, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_MONTH(pcode__MONTH, bReturn);
 		}


		*nReturnExpressionType = pcode__INTEGER;

 		parseInfo(p, "parsed MONTH");
 		_DONE_
	}


 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__MONTH, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__MONTH, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: NOW
PRINTNAME: Now
TASK: returns the current system date and time
SYNTAX: NOW() As DATE
DESC:
CODE:
PRINT NOW()
EXAMPLES: now.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fNOW(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_NOW = false;
  _BEGIN_
  if (!(/*bTerm_NOW = */parseTerm(token__NOW))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__NOW, ") missing"); _ERROR_ }


 	if (bProducePcode){

   		 p->wr_NOW(pcode__NOW, bReturn);
 	}

	*nReturnExpressionType = pcode__DATE;

 	parseInfo(p, "parsed NOW");
 	_DONE_


	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: RGB
PRINTNAME: RGB
TASK: returns a long value generated by a triple
SYNTAX: RGB(red, green, blue)
DESC:
CODE:
Dim red
red = RGB(255, 0, 0)
EXAMPLES: rgb.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fRGB(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_RGB = false;
  _BEGIN_
  if (!(/*bTerm_RGB = */parseTerm(token__RGB))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__RGB, "expression missing"); _ERROR_ }

		if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__RGB, ", missing"); _ERROR_ }

		if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__RGB, "expression missing"); _ERROR_ }

		if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__RGB, ", missing"); _ERROR_ }
		
		if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__RGB, "expression missing"); _ERROR_ }
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__RGB, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_RGB(pcode__RGB, bReturn);
 		}


		*nReturnExpressionType = pcode__LONG;

 		parseInfo(p, "parsed RGB");
 		_DONE_


	}

 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__RGB, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__RGB, ") missing"); _ERROR_ }


	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: SECOND
PRINTNAME: Second
TASK: returns the second part of a date expression
SYNTAX: SECOND(expression)
DESC:
CODE:
Dim Time1, Second1
Time1 = #4:35:47 PM#	
Second1 = Second(Time1)	' Second1 contains 47
EXAMPLES: second.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSECOND(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_SECOND = false;
  _BEGIN_
  if (!(/*bTerm_SECOND = */parseTerm(token__SECOND))){ _END_ }	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(token__SECOND, "date expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SECOND, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_SECOND(pcode__SECOND, bReturn);
 		}


		*nReturnExpressionType = pcode__INTEGER;

 		parseInfo(p, "parsed SECOND");
 		_DONE_
	}


 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__SECOND, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__SECOND, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: TIMER
PRINTNAME: Timer
TASK: returns the number of seconds by midnight
SYNTAX: TIMER()
DESC: 
CODE:
Dim length, Start, finish, all
If (MsgBox("5 seconds to pause?", 4)) = kbYes Then
	length = 5
	Start = Timer
	Do While Timer < Start + length
		DoEvents			
	Loop
	finish = Timer
	all = finish - Start	
	MsgBox "Pause was " & all & " seconds"
Else
	End
End If
EXAMPLES: timer.kbasic, timer2.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: RANDOMIZE, RND
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTIMER(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_TIMER = false;
  _BEGIN_
  if (!(/*bTerm_TIMER = */parseTerm(token__TIMER))){ _END_ }

	

  bool bTerm_ON = false;
	bool bTerm_OFF = false;
	bool bTerm_STOP = false;

  if (bTerm_ON = parseTerm(token__ON)){  
 	  if (bProducePcode){
   	  p->wr_TIMER_ON(pcode__TIMER_ON);
 	  }
	  *nReturnExpressionType = pcode__VOID;
 	  parseInfo(p, "parsed TIMER ON");
 	  _DONE_
  } else if (bTerm_OFF = parseTerm(token__OFF)){  
 	  if (bProducePcode){
   	  p->wr_TIMER_OFF(pcode__TIMER_OFF);
 	  }
	  *nReturnExpressionType = pcode__VOID;
 	  parseInfo(p, "parsed TIMER OFF");
 	  _DONE_
  } else if (bTerm_STOP = parseTerm(token__STOP)){  
 	  if (bProducePcode){
   	  p->wr_TIMER_STOP(pcode__TIMER_STOP);
 	  }
	  *nReturnExpressionType = pcode__VOID;
 	  parseInfo(p, "parsed TIMER STOP");
 	  _DONE_
  }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__TIMER, ") missing"); _ERROR_ }


 	if (bProducePcode){

   		 p->wr_TIMER(pcode__TIMER, bReturn);
 	}


	*nReturnExpressionType = pcode__SINGLE;

 	parseInfo(p, "parsed TIMER");
 	_DONE_


	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: TIMESERIAL
PRINTNAME: TimeSerial
TASK: returns a time as a integer
SYNTAX: TimeSerial(hour, minute, second)
DESC:
CODE:
Dim Time1
Time1 = TimeSerial(16, 35, 17)	' in integer format --> 16:35:17
EXAMPLES: timeserial.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTIMESERIAL(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_TIMESERIAL = false;
  _BEGIN_
  if (!(/*bTerm_TIMESERIAL = */parseTerm(token__TIMESERIAL))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__TIMESERIAL, "numeric expression missing"); _ERROR_ }

		if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__TIMESERIAL, ", missing"); _ERROR_ }

		if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__TIMESERIAL, "numeric expression missing"); _ERROR_ }

		if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__TIMESERIAL, ", missing"); _ERROR_ }
		
		if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__TIMESERIAL, "numeric expression missing"); _ERROR_ }
		
		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__TIMESERIAL, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_TIMESERIAL(pcode__TIMESERIAL, bReturn);
 		}


		*nReturnExpressionType = pcode__DATE;

 		parseInfo(p, "parsed TIMESERIAL");
 		_DONE_


	}

 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__TIMESERIAL, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__TIMESERIAL, ") missing"); _ERROR_ }


	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: TIMEVALUE
PRINTNAME: TimeValue
TASK: returns a time given in a string expression as a date
SYNTAX: TIMEVALUE(string expression) As Date
DESC:
CODE:
Dim Time1
Time1 = TimeValue("4:35:17 PM")	' return time as date
EXAMPLES: timevalue.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTIMEVALUE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_TIMEVALUE = false;
  _BEGIN_
  if (!(/*bTerm_TIMEVALUE = */parseTerm(token__TIMEVALUE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__TIMEVALUE, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__TIMEVALUE, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_TIMEVALUE(pcode__TIMEVALUE, bReturn);
 		}


		*nReturnExpressionType = pcode__DATE;

 		parseInfo(p, "parsed TIMEVALUE");
 		_DONE_
	}


 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__TIMEVALUE, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__TIMEVALUE, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: TYPENAME
PRINTNAME: TypeName
TASK: returns the type name of a variable as string
SYNTAX: TYPENAME(variable) AS STRING
DESC:
possible returns:
Byte
Integer
Long
Single
Double
Currency
Date
String
Boolean
Error
Empty
Null
Object
Nothing
CODE:
Dim NullVar, Type1, StrVar As String, IntVar As Integer, CurVar As Currency
Dim ArrayVar (1 To 5) As Integer
NullVar = Null	' Null zuweisen.
Type1 = TypeName(StrVar)	' returns "String".
Type1 = TypeName(IntVar)	' returns "Integer".
Type1 = TypeName(CurVar)	' returns "Currency".
Type1 = TypeName(NullVar)	' returns "Null".
Type1 = TypeName(ArrayVar)	' returns "Integer()"
EXAMPLES: typename.kbasic
CATEGORY: FUNCTION, BUILTIN, VARIABLE, VARIANT, OBJECT
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTYPENAME(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_TYPENAME = false;
  _BEGIN_
  if (!(parseTerm(token__TYPE)) && !(/*bTerm_TYPENAME = */parseTerm(token__TYPENAME))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bIDENTIFIER = false;

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
		if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &a)){

			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 			if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__TYPENAME, ") missing"); _ERROR_ }

		  if (nType == token__ME){
        { semanticError(token__TYPENAME, "TYPENAME not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__TYPENAME, "TYPENAME not allowed in combination with PARENT"); _ERROR_ }
     } else {
     }

 			if (bProducePcode){
   			 p->wr_TYPENAME(pcode__TYPENAME, nVar, scope, bReturn); // write pcode
 			}

			*nReturnExpressionType = pcode__QSTRING;

			parseInfo(p, "parsed TYPENAME statement");
 			_DONE_
 		}
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__TYPENAME, "( missing"); _ERROR_ }
 	//else if (!bIDENTIFIER){ syntaxError(token__TYPENAME, "identifier missing or identifier not declared"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__TYPENAME, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: WEEKDAY
PRINTNAME: Weekday
TASK: returns the weekday of a date
SYNTAX: Weekday(date, [firstdayofweek])
DESC:
firstdayofweek:
kbUseSystem	0	Sunday
kbSunday	1	Sunday (default)
kbMonday	2	Monday
kbTuesday	3	Tuesday
kbWednesday	4	Wednesday
kbThursday	5	Thursday
kbFriday	6	Friday
kbSaturday	7	Saturday

possible return values:
kbSunday	1
kbMonday	2
kbTuesday	3
kbWednesday	4
kbThursday	5
kbFriday	6
kbSaturday	7
CODE:
Dim Date1, Weekday1
Date1 = #12. Februar 1969#	
Weekday1 = Weekday(Date1)	' Weekday1 contains 4
EXAMPLES: weekday.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fWEEKDAY(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_WEEKDAY = false;
  _BEGIN_
  if (!(/*bTerm_WEEKDAY = */parseTerm(token__WEEKDAY))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool firstdayofweek = false;
	

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__WEEKDAY, "expression missing"); _ERROR_ }

	 	if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){

			if ((firstdayofweek = fINTEGER_EXPRESSION(p))){}

		}

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__WEEKDAY, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_WEEKDAY(pcode__WEEKDAY, firstdayofweek, bReturn);
 		}


		*nReturnExpressionType = pcode__INTEGER;

 		parseInfo(p, "parsed WEEKDAY");
 		_DONE_
	}


 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__WEEKDAY, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__WEEKDAY, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: YEAR
PRINTNAME: Year
TASK: returns the year of a date
SYNTAX: YEAR(date expression) AS INTEGER
DESC:
CODE:
Dim Date1, Year1
Date1 = #12. Februar 1969#	
Year1 = Year(Date1)	' Year1 contains 1969.
EXAMPLES: year.kbasic
CATEGORY: FUNCTION, BUILTIN, DATETIME
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fYEAR(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_YEAR = false;
  _BEGIN_
  if (!(/*bTerm_YEAR = */parseTerm(token__YEAR))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(token__YEAR, "date expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__YEAR, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_YEAR(pcode__YEAR, bReturn);
 		}


		*nReturnExpressionType = pcode__INTEGER;

 		parseInfo(p, "parsed YEAR");
 		_DONE_
	}


 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__YEAR, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__YEAR, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: NZ
PRINTNAME: Nz
TASK: changes to expression from null to nullstring, if needed
SYNTAX: NZ(expression)
DESC:
CODE:
function test()
  return null
end function
print nz(test) ' --> ""
EXAMPLES: nz.kbasic
CATEGORY: FUNCTION, BUILTIN, VARIANT, VARIABLE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fNZ(pcode *p, int *nReturnExpressionType, bool bReturn)
{

	//bool bTerm_NZ = false;
  _BEGIN_
  if (!(/*bTerm_NZ = */parseTerm(token__NZ))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

		if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__NZ, "expression missing"); _ERROR_ }


		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__NZ, ") missing"); _ERROR_ }


 		if (bProducePcode){

   			 p->wr_NZ(pcode__NZ, bReturn);
 		}


		*nReturnExpressionType = pcode__QSTRING;

 		parseInfo(p, "parsed NZ");
 		_DONE_
	}


 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__NZ, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__NZ, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ERR
PRINTNAME: Err
TASK: as for VeryOldBasic returns the runtime error code, as for OldBasic it is an object for error handling
SYNTAX: ERR
DESC:

properties:
Number
Source
Description
LastDLLError

methods:
Clear() - reset
Raise(number, source, description) - raise error

CODE:
Dim Msg
On Error Resume Next
Err.Clear
Err.Raise 6
If Err.Number <> 0 Then
	Msg = "Error # " & Str(Err.Number) & " " _
			& Err.Source & Chr(13) & Err.Description
	MsgBox Msg, , "Error"
End If
EXAMPLES: err.kbasic
CATEGORY: FUNCTION, BUILTIN, ERROR
SEEALSO: ERL, ERROR, ONERROR, RESUME
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fERR(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
ERR gibt den Laufzeit-Fehlercode des letzten Fehlers zurück.
[*]
[!VBNET]
[!KBASIC]
*/
{

  _BEGIN_ // muss hier oben stehen, da err object später gültige production sein könnte

	//bool bTerm_ERR = false;

  if (!(/*bTerm_ERR = */parseTerm(token__ERR))){ _END_ }
	
 	bool bTerm_SYM_BR_OP = false;
 	bool bTerm_SYM_BR_CL = false;

 	bool bEXPRESSION = false;

 	bool bTerm_COMMA = false;

 	bool bTerm_RAISE = false;
 	bool bTerm_CLEAR = false;


  if (parseTerm(token__SYM_DOT)){
  	 _END_
  }
  

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ERR, ") missing"); _ERROR_ }

 	if (bProducePcode){

   		 p->wr_ERR(pcode__ERR, bReturn);
 	}

	*nReturnExpressionType = pcode__INTEGER;

 	parseInfo(p, "parsed ERR");
 	_DONE_

}

/**
[KBASIC][VB][QBASIC]
NAME: ERL
PRINTNAME: Erl
TASK: returns the line in which the last error occured
SYNTAX: ERL
DESC:
CODE:
PRINT ERL
EXAMPLES: erl.kbasic
CATEGORY: FUNCTION, BUILTIN, ERROR
SEEALSO: ERROR, RESUME, ERR, ONERROR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fERL(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
ERL gibt die Nummer der Zeile, in der der Fehler auftrat, zurück, oder die
Nummer der letzten Zeile, die abgearbeitet wurde, bevor der Fehler auftrat
[*]
[!VBNET]
[!KBASIC]
*/
{

	//bool bTerm_ERL = false;
  _BEGIN_
  if (!(/*bTerm_ERL = */parseTerm(token__ERL))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INKEY_, ") missing"); _ERROR_ }
  }


 	if (bProducePcode){

   		 p->wr_ERL(pcode__ERL, bReturn);
 	}

	*nReturnExpressionType = pcode__INTEGER;

 	parseInfo(p, "parsed ERL");
 	_DONE_

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: FRE
PRINTNAME: Fre
TASK: returns the available memory
SYNTAX: FRE(expression)
DESC: FRE(-1)
CODE:
PRINT FRE
EXAMPLES: fre.kbasic
CATEGORY: FUNCTION, BUILTIN, OS
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFRE(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[!VB]
[!VBNET]
[!KBASIC]
*/
{

	//bool bTerm_FRE = false;
  _BEGIN_
  if (!(/*bTerm_FRE = */parseTerm(token__FRE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;
	
	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){}
  if (!(bEXPRESSION2 = fNUMERIC_EXPRESSION(p))){}// syntaxError(token__FRE, "expression missing"); _ERROR_ }

	if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FRE, ") missing"); _ERROR_ }

 	if (bProducePcode){
		p->wr_FRE(pcode__FRE, bEXPRESSION, bEXPRESSION2, bReturn);
 	}

	*nReturnExpressionType = pcode__LONG;

 	parseInfo(p, "parsed FRE");
 	_DONE_
}

/**
[KBASIC][VB][QBASIC]
NAME: INSTREV
PRINTNAME: InStRev
TASK: INSTREV finds one string inside another.
SYNTAX: INSTREV([start AS INTEGER ,] src AS STRING, sub AS STRING) AS INTEGER
DESC: 
INSTREV searches the src string for and occurance of the
sub string and returns the index of the sub string in
the src string.  0 is returned if the sub string is
not found. start tells the positon from which the searching starts from.

CODE:
dim x as string, y as string
x = "This is a string"
y = "s"
PRINT INSTREV(x, y)

' Output:
' 11

EXAMPLES: instrev.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: INSTR
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fINSTREV(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[*]
[*]
[KBasic]
*/
{

	bool bTerm_LASTINDEXOF = false;
  _BEGIN_
  if (!(/*bTerm_INSTREV = */parseTerm(token__INSTREV)) && !(bTerm_LASTINDEXOF = parseTerm(token__LASTINDEXOF))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;
	bool bEXPRESSION3 = false;
	bool bCase = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){


    if (bTerm_LASTINDEXOF){

  	  if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__INSTREV, "string expression missing"); _ERROR_ }

      if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__INSTREV, ", missing"); _ERROR_ }  	      

      if (!fSTRING_EXPRESSION(p)){ syntaxError(token__INSTREV, "string expression missing"); _ERROR_ }

      if (parseTerm(token__SYM_COMMA)){

  	    if (bEXPRESSION = fINTEGER_EXPRESSION(p)){

          if (parseTerm(token__SYM_COMMA)){

            if (!(bCase = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__INSTREV, "boolean expression missing"); _ERROR_ }

          }

  	    }
      }

    } else {

  	  if (bEXPRESSION = fINTEGER_EXPRESSION(p)){

        if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__INSTREV, ", missing"); _ERROR_ }

  	  }

  	  if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__INSTREV, "string expression missing"); _ERROR_ }

      if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__INSTREV, ", missing"); _ERROR_ }
  	
      if (!fSTRING_EXPRESSION(p)){ syntaxError(token__INSTREV, "expression missing"); _ERROR_ }

      if (parseTerm(token__SYM_COMMA)){

        if (!(bCase = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__INSTREV, "boolean expression missing"); _ERROR_ }

      }

    }   

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INSTREV, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){
  			p->wr_INSTREV(pcode__INSTREV, bEXPRESSION, bTerm_LASTINDEXOF, bCase, bReturn, bObjectFake);
   		}

   		parseInfo(p, "parsed INSTREV");
   		_DONE_
  	}
	}
 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__INSTREV, "( missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISOBJECT
PRINTNAME: IsObject
TASK: returns true if expression is an object
SYNTAX: ISOBJECT(expression)
DESC:
DIM m AS OBJECT
PRINT ISOBJECT(m)
CODE:
EXAMPLES: isobject.kbasic
CATEGORY: FUNCTION, BUILTIN, , VARIABLE, VARIANT, OBJECT
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISOBJECT(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISOBJECT = false;
  _BEGIN_
  if (!(/*bTerm_ISOBJECT = */parseTerm(token__ISOBJECT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__ISOBJECT, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISOBJECT, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISOBJECT(pcode__ISOBJECT, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISOBJECT statement");
 		_DONE_
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISOBJECT, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISOBJECT, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ISCURRENCY
PRINTNAME: IsCurrency
TASK: returns true if expression is a currency
SYNTAX: ISCURRENCY(expression)
DESC:
CODE:
EXAMPLES: iscurrency.kbasic
CATEGORY: FUNCTION, BUILTIN, VARIABLE, VARIANT, OBJECT
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fISCURRENCY(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_ISOBJECT = false;
  _BEGIN_
  if (!(/*bTerm_ISOBJECT = */parseTerm(token__ISCURRENCY))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!(bEXPRESSION = fEXPRESSION(p))){ syntaxError(token__ISCURRENCY, "expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ISCURRENCY, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ISCURRENCY(pcode__ISCURRENCY, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__BOOLEAN;

		parseInfo(p, "parsed ISCURRENCY statement");
 		_DONE_
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ISOBJECT, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ISOBJECT, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: REPLACE
PRINTNAME: Replace
TASK: replaces string occurances with another string
SYNTAX: REPLACE(s AS STRING, pattern AS STRING, replace AS STRING)
DESC:
CODE:
DIM s = "Das ist alles was wir brauchen. Fang nochmal von vorne an."
DIM pattern = vorne"
DIM replace = "hinten"
PRINT REPLACE(s, pattern, replace)
EXAMPLES: replace.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fREPLACE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

	//bool bTerm_REPLACE = false;
  _BEGIN_
  if (!(/*bTerm_REPLACE = */parseTerm(token__REPLACE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;
	bool bCase = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__REPLACE, "string expression missing"); _ERROR_ }
  if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__REPLACE, ", missing"); _ERROR_ }
	if (!(bEXPRESSION2 = fSTRING_EXPRESSION(p))){ syntaxError(token__REPLACE, "string expression missing"); _ERROR_ }
  if (!(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__REPLACE, ", missing"); _ERROR_ }
	if (!(bEXPRESSION2 = fSTRING_EXPRESSION(p))){ syntaxError(token__REPLACE, "string expression missing"); _ERROR_ }

  if (parseTerm(token__SYM_COMMA)){ 
	  if (!(bCase = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__REPLACE, "boolean expression missing"); _ERROR_ }
  }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__REPLACE, ") missing"); _ERROR_ }

	{
 		*nReturnExpressionType = pcode__QSTRING;

 		if (bProducePcode){
			p->wr_REPLACE(pcode__REPLACE, bCase, bReturn);
 		}

 		parseInfo(p, "parsed REPLACE");
 		_DONE_
	}

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: SPLIT
PRINTNAME: Split
TASK: returns an array of strings, origin string has been separated by a separator string
SYNTAX: SPLIT(s AS STRING, separator AS STRING, keepemptyparts as boolean, casesensitive as boolean) 
DESC:
CODE:

DIM s = "So much more I have to say. And I wonder if you know, how it feels to be leftside out alone."
DIM separator = "."

PRINT SPLIT(s, separator)

EXAMPLES: split.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSPLIT(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__SPLIT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bTerm_COMMA = false;
	bool bKeepEmptyParts = false;
	bool bCaseSensitive = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__SPLIT, "string expression missing"); _ERROR_ }

  if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__REPLACE, ", missing"); _ERROR_ }
	if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__SPLIT, "string expression missing"); _ERROR_ }

  if (parseTerm(token__SYM_COMMA)){
    if (!(bKeepEmptyParts = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__SPLIT, "expression missing"); _ERROR_ }
  }
  if (parseTerm(token__SYM_COMMA)){
    if (!(bCaseSensitive = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__SPLIT, "expression missing"); _ERROR_ }
  }
  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SPLIT, ") missing"); _ERROR_ }

	{
 		*nReturnExpressionType = pcode___strings;

 		if (bProducePcode){
			p->wr_SPLIT(pcode__SPLIT, bKeepEmptyParts, bCaseSensitive, bReturn);
 		}

 		parseInfo(p, "parsed SPLIT");
 		_DONE_
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: ROUND
PRINTNAME: Round
TASK: rounds a value
SYNTAX: ROUND(numeric expression[, afterdigit] AS DOUBLE
DESC:
1.1 between 1.4 -> 1
1.5 between 1.9 -> 2
CODE:
Dim n = 1.1
PRINT ROUND(n)
EXAMPLES: round.kbasic
CATEGORY: FUNCTION, BUILTIN, MATH
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fROUND(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

  _BEGIN_
  if (!(parseTerm(token__ROUND))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;
	bool bTerm_COMMA = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__ROUND, "numeric expression missing"); _ERROR_ }

    if ((bTerm_COMMA = parseTerm(token__SYM_COMMA))){
	    if (!(bEXPRESSION = fNUMERIC_EXPRESSION(p))){ syntaxError(token__ROUND, "numeric expression missing"); _ERROR_ }
    }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ROUND, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_ROUND(pcode__ROUND, bTerm_COMMA, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__DOUBLE;

		parseInfo(p, "parsed ROUND statement");
 		_DONE_
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__ROUND, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__ROUND, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: STRREVERSE
PRINTNAME: StrReverse
TASK: returns a given string reversed
SYNTAX: STRREVERSE(STRINGEXPRESSION) AS STRING
DESC:
CODE:
DIM s = "Mondscheinsonate von Beethoven"
PRINT STRREVERSE(s) ' --> nevohteeB nov etanosniehcsdnoM
EXAMPLES: strreverse.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSTRREVERSE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_STRREVERSE = false;
  _BEGIN_
  if (!(/*bTerm_STRREVERSE = */parseTerm(token__STRREVERSE))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__STRREVERSE, "string expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__STRREVERSE, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_STRREVERSE(pcode__STRREVERSE, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed STRREVERSE statement");
 		_DONE_
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__STRREVERSE, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__STRREVERSE, ") missing"); _ERROR_ }

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: SPC
PRINTNAME: Spc
TASK: returns a string with a number of spaces
SYNTAX: SPC(count%) AS STRING
DESC:
CODE:
PRINT "Text1"; SPC(10); "Text2"
EXAMPLES: spc.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING
SEEALSO: SPACE, PRINT
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fSPC(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_SPC = false;
  _BEGIN_
  if (!(/*bTerm_SPC = */parseTerm(token__SPC))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__SPC, "integer expression missing"); _ERROR_ }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SPC, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_SPC(pcode__SPC, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed SPC statement");
 		_DONE_
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__SPC, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__SPC, ") missing"); _ERROR_ }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: POINT
PRINTNAME: Point
TASK: returns the color at the desired point or graphical cursor position
SYNTAX: POINT {(n%) | (x%,y%)}
DESC:
CODE:
  SCREEN 13
  LINE (0, 0)-(100, 100), 2
  LOCATE 14, 1
  FOR y% = 1 TO 10
      FOR x% = 1 TO 10
          PRINT POINT(x%, y%);
      NEXT x%
      PRINT
  NEXT y%
EXAMPLES: point.kbasic
CATEGORY: FUNCTION, BUILTIN, SCREEN
SEEALSO: COLOR, PMAP, SCREEN, VIEW, WINDOW
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/*
bool parser::fPOINT(pcode *p, int *nReturnExpressionType, bool bReturn)
/ *
[*]
[VB]
[*]
[*]
* /
{

	//bool bTerm_POINT = false;
  _BEGIN_
  if (!(parseTerm(token__POINT))){ _END_ }

	

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

  bool bTerm_SYM_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
 
    if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__POINT, "integer expression missing"); _ERROR_ }

    if (bTerm_SYM_COMMA = parseTerm(token__SYM_COMMA)){
      if (!(bEXPRESSION2 = fINTEGER_EXPRESSION(p))){ syntaxError(token__POINT, "integer expression missing"); _ERROR_ }
    }

		if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__POINT, ") missing"); _ERROR_ }

 		if (bProducePcode){
   			p->wr_POINT(pcode__POINT, bEXPRESSION2, bReturn); // write pcode
 		}

		*nReturnExpressionType = pcode__QSTRING;

		parseInfo(p, "parsed POINT statement");
 		_DONE_
	}
 			 //if (!bTerm_SYM_BR_OP){ syntaxError(token__POINT, "( missing"); _ERROR_ }
 	//else if (!bTerm_SYM_BR_CL){ syntaxError(token__POINT, ") missing"); _ERROR_ }

	_END_
}
*/

/**
[KBASIC][VB][QBASIC]
NAME: INPUT
PRINTNAME: Input
TASK: combined screen output and keyboard input
SYNTAX: INPUT [;]["string"{;|,}] varname [,varname2 ...]
DESC: 
into variable 'number1%'  {1/23} ; 
1. semicolon prevent EOL after pressing return.
If the 2. semicolon is replaced by a comma, no question mark will be displayed

The INPUT command prompts for a value to be stored in a variable. Values are entered
with the keyboard. The simplest way to use it is just followed by a variable name which
will hold the value entered:
INPUT n

prompts a quotation mark at the beginning of a line and waits until the user has typed
a value and pressed the RETURN key.

KBasic does not make any control whether the variable has been previously used with
another value or not and therefore, destroys the previous value of the variable. Because
variables need not to be declared (only veryoldbasic or oldbasic with option explicit off) 
INPUT serves also as initialization for the variable,
which assumes value of 0 (zero) when only RETURN is pressed.
It is often convenient to explain a bit more what we want from the user so it is
preferable to prompt an explanation message on what kind of input we're expecting.
This is done by just placing a double quoted text after the keyword, like:

INPUT "How many seconds"; s

As shown the prompt is now clearer and we know what kind of input is expected. The
message can be as long as wanted and must be inside double quotes, single quotes are
not allowed. Instead of the semicolon a comma can be used to separate message
prompt and the variable name, like:

INPUT "Enter time (in seconds): ", s

in this case the usual question mark is suppressed and the cursor is placed immediately
afterwards the last character of the message string. The use of one or the other is a
choice of the developer but the message and the variable name must be separated by
one of the two characters.
A semicolon can be used immediately after the INPUT command, like:

INPUT; "Enter age"; a
INPUT " and height"; b

this will cause the second INPUT command prompt to be placed immediately after the
last character typed by the user:

Enter age? 156 and height?
INPUT permits also to enter as many different values as we want. The different values are stored in different variables:
INPUT "age and height: ", age, height

this prompts the message and waits till the user has entered the coordinates separate
with a comma. It is not possible to use any other separation character here. The two
(or three, four, etc.) may be variables of different type, like:

INPUT "Enter full longitude coords (degree, cardinal): ", long, card$

Whenever the number of variables expected is different from the entered ones or a
variable type mismatch occurs a "redo from start" warning message is displayed and
the command is prompted again to the user.
CODE:
INPUT "How many seconds"; s
INPUT; "Enter longitude"; a
INPUT " and latitude"; b
INPUT "longitude and latitude: ", longitude, latitude
INPUT "Enter full longitude coords (degree, cardinal): ", long, card$
EXAMPLES: input.kbasic
CATEGORY: FUNCTION, BUILTIN, STRING, VARIABLE, SCREEN, KEYBOARD
SEEALSO: INKEY, OPEN
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fINPUT(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[QBASIC]
[VB]
[*]
[*]
*/
{
	_BEGIN_

	//bool bTerm_INPUT = false;

  // nReturnExpressionType == 0, then it is called by fLINEINPUT
  if (nReturnExpressionType != 0) if (!(/*bTerm_INPUT = */parseTerm(token__INPUT))){ _END_ }

 	_BEGIN3_

	bool bTerm_SEMICOL = false;
	bool bTerm_SEMICOL2 = false;
	bool bTerm_COMMA = false;

	bool bIDENTIFIER = false;
	bool bSTRING_EXPRESSION = false;
	bool bEXPRESSION = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

 	bool bTerm__HASH = false;
 	bool bEXPRESSION0 = false;


  bool bImplicitDIM = false;
  bool bTestImplicitDim = true;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bAssignment = false;  
  bool bProperty = false;  
  bool bTestProperty = false;  

	int nVar = 0; t_scope scope = global; int nIdType = 0; int nType = 0; t_arrayVariable a;
  int nVar2[parser__MAX_INPUT]; t_scope scope2[parser__MAX_INPUT]; 
  int nComma = 0;

  prepareRollbackVariable();

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  // 2. variante mit return as 'INPUT #1, recordno'
  {
    if (nReturnExpressionType && (bTerm__HASH = parseTerm(token__SYM_HASH))){}
    if (nReturnExpressionType && (bEXPRESSION0 = fINTEGER_EXPRESSION(p))){
 	    if (bTerm_COMMA = parseTerm(token__SYM_COMMA));      

      if (!bEXPRESSION0){ syntaxError(token__INPUT, "record no. missing"); _ERROR_ }
      if (!bTerm_COMMA){ 
        _END3_ 
        p->ba->append(pDim->ba); // rollback
        goto var; 
      }
re:

	if ((bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar2[nComma], &scope2[nComma], &nIdType, &nType, &bImplicitDIM, 
                                  bTestImplicitDim, &a, 
                                  &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty                 
                                  ))){ bIDENTIFIER = memory_type::isString(nType); }

      if (!bIDENTIFIER){ syntaxError(token__INPUT, "string variable missing"); _ERROR_ }

      if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
        nComma++;
        goto re;
      } else {
        nComma++;
      }

		  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INPUT, ") missing"); _ERROR_ }

      for (int i = 0; i < nComma; i++){
   	    if (bProducePcode){
  		    p->wr_INPUT2(pcode__INPUT2, i == 0, nVar2[i], scope2[i], nComma, bReturn);
   	    }
      }

		  *nReturnExpressionType = pcode__QSTRING;

      _DONE_

    }

  }

  if (bTerm__HASH = parseTerm(token__SYM_HASH)){}
  if ((bEXPRESSION0 = fINTEGER_EXPRESSION(p))){
 	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA));
   	if (!bTerm_COMMA){ 
      if (bTerm__HASH){
        { syntaxError(token__INPUT, ", missing"); _ERROR_ }
      } else {
        rollbackVariable();
        _END3_  // rollback bEXPRESSION0 wird verworfen und variable wird erwartet
      }
    }
  }

	if (bTerm_SEMICOL = parseTerm(token__SYM_SEMICOL)){}
var:
	if ((bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, 
                                  bTestImplicitDim, &a, 
                                  &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty                 
                                  ))){

    switch(nType){
  		case pcode__BOOLEAN:

      case pcode__QSTRING: 
      case pcode__CSTRING: 

      case pcode__INTEGER:
      case pcode__LONG:

  		case pcode__SINGLE:
  		case pcode__DOUBLE:
        break;
      default:
         { semanticError(token__INPUT, "INPUT variable must be of type BOOLEAN, STRING, INTEGER, LONG, SINGLE or DOUBLE"); _ERROR_ }
        break;
    }
    if (nType == token__ME){
       { semanticError(token__INPUT, "INPUT not allowed in combination with ME"); _ERROR_ }
		} else if (nType == token__PARENT){
       { semanticError(token__INPUT, "INPUT not allowed in combination with PARENT"); _ERROR_ }
   } else {
     if (bProducePcode && bImplicitDIM){
       p->wr_DIM(pcode__DIM, nVar, scope, nType, false, false, a.var.use.count, false, 0, 0, "", false); // write pcode
     }

   }

		goto ident; // because STRING_EXPRESSION implicates identifier !!
 	} else if (bSTRING_EXPRESSION = fSTRING_EXPRESSION(p)){

 	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA));
 	  else if (bTerm_SEMICOL2 = parseTerm(token__SYM_SEMICOL)){}

   	if (!bTerm_COMMA && !bTerm_SEMICOL2){ syntaxError(token__INPUT, ", or ; missing"); _ERROR_ }

 	}

	if ((bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, 
                                  bTestImplicitDim, &a, 
                                  &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty                 
                                  ))){

    switch(nType){
  		case pcode__BOOLEAN:

      case pcode__QSTRING: 
      case pcode__CSTRING: 

      case pcode__INTEGER:
      case pcode__LONG:

  		case pcode__SINGLE:
  		case pcode__DOUBLE:
        break;
      default:
         { semanticError(token__INPUT, "INPUT variable must be of type BOOLEAN, STRING, INTEGER, LONG, SINGLE or DOUBLE"); _ERROR_ }
        break;
    }

		if (nType == token__ME){
       { semanticError(token__INPUT, "INPUT not allowed in combination with ME"); _ERROR_ }
		} else if (nType == token__PARENT){
       { semanticError(token__INPUT, "INPUT not allowed in combination with PARENT"); _ERROR_ }
   } else {
     if (bProducePcode && bImplicitDIM){
       p->wr_DIM(pcode__DIM, nVar, scope, nType, false, false, a.var.use.count, false, 0, 0, "", false); // write pcode
     }

   }

ident:

		{
   		if (bProducePcode){
  			p->wr_INPUT(pcode__INPUT, bEXPRESSION0, bTerm_SEMICOL, bSTRING_EXPRESSION, bTerm_COMMA, bTerm_SEMICOL2, nVar, scope, nType, bReturn);
   		}

			while (true){
				if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){

	        if ((bIDENTIFIER = fVARIABLE_ASSIGNMENT(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, 
                                          bTestImplicitDim, &a, 
                                          &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty                 
                                          ))){

		       if (nType == token__ME){
              { semanticError(token__INPUT, "INPUT not allowed in combination with ME"); _ERROR_ }
		       } else if (nType == token__PARENT){
              { semanticError(token__INPUT, "INPUT not allowed in combination with PARENT"); _ERROR_ }
           } else {
              if (bProducePcode && bImplicitDIM){
                p->wr_DIM(pcode__DIM, nVar, scope, nType, false, false, a.var.use.count, false, 0, 0, "", false); // write pcode
              }
           }

			   		if (bProducePcode){
  						p->wr_INPUT(pcode__INPUT, bEXPRESSION0, false, false, true, false, nVar, scope, nType, bReturn);
   					}
					} else break;
				} else break;
			}

			if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__INPUT, ") missing"); _ERROR_ }

  		if (nReturnExpressionType) *nReturnExpressionType = pcode__VOID;

   		parseInfo(p, "parsed INPUT");
   		_DONE_
  	}

 	} else { syntaxError(token__INPUT, "identifier missing or identifier not declared"); _ERROR_ }

	_END_
}

bool parser::fCOMPARE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__COMPARE))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__COMPARE, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__COMPARE, ", missing"); _ERROR_ }

  	if (!fSTRING_EXPRESSION(p)){ syntaxError(token__COMPARE, "string expression missing"); _ERROR_ }

  	if (parseTerm(token__SYM_COMMA)){ 

      if (!(bEXPRESSION = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__COMPARE, "boolean expression missing"); _ERROR_ }
  	  
    }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__COMPARE, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){
  			p->wr_COMPARE(pcode__COMPARE, bEXPRESSION, bReturn);
   		}

   		parseInfo(p, "parsed COMPARE");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fCONTAINS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__CONTAINS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__CONTAINS, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__CONTAINS, ", missing"); _ERROR_ }

    if (!fSTRING_EXPRESSION(p)){ syntaxError(token__COMPARE, "string expression missing"); _ERROR_ }

  	if (parseTerm(token__SYM_COMMA)){ 

      if (!(bEXPRESSION = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__CONTAINS, "boolean expression missing"); _ERROR_ }
  	  
    }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__CONTAINS, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__BOOLEAN;

   		if (bProducePcode){
  			p->wr_CONTAINS(pcode__CONTAINS, bEXPRESSION, bReturn);
   		}

   		parseInfo(p, "parsed CONTAINS");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fCOUNT(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__COUNT))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__COUNT, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__COUNT, ", missing"); _ERROR_ }

    if (!fSTRING_EXPRESSION(p)){ syntaxError(token__COUNT, "string expression missing"); _ERROR_ }

  	if (parseTerm(token__SYM_COMMA)){ 

      if (!(bEXPRESSION = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__COUNT, "boolean expression missing"); _ERROR_ }
  	  
    }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__COUNT, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__INTEGER;

   		if (bProducePcode){
  			p->wr_COUNT(pcode__COUNT, bEXPRESSION, bReturn);
   		}

   		parseInfo(p, "parsed COUNT");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fENDSWITH(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__ENDSWITH))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__ENDSWITH, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__ENDSWITH, ", missing"); _ERROR_ }

  	if (!fSTRING_EXPRESSION(p)){ syntaxError(token__ENDSWITH, "string expression missing"); _ERROR_ }

  	if (parseTerm(token__SYM_COMMA)){ 

      if (!(bEXPRESSION = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__ENDSWITH, "boolean expression missing"); _ERROR_ }
  	  
    }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ENDSWITH, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__BOOLEAN;

   		if (bProducePcode){
  			p->wr_ENDSWITH(pcode__ENDSWITH, bEXPRESSION, bReturn);
   		}

   		parseInfo(p, "parsed ENDSWITH");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fSTARTSWITH(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__STARTSWITH))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__STARTSWITH, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__STARTSWITH, ", missing"); _ERROR_ }

  	if (!fSTRING_EXPRESSION(p)){ syntaxError(token__STARTSWITH, "string expression missing"); _ERROR_ }

  	if (parseTerm(token__SYM_COMMA)){ 

      if (!(bEXPRESSION = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__STARTSWITH, "boolean expression missing"); _ERROR_ }
  	  
    }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__STARTSWITH, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__BOOLEAN;

   		if (bProducePcode){
  			p->wr_STARTSWITH(pcode__STARTSWITH, bEXPRESSION, bReturn);
   		}

   		parseInfo(p, "parsed STARTSWITH");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fLEFTJUSTIFIED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__LEFTJUSTIFIED))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__LEFTJUSTIFIED, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__LEFTJUSTIFIED, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__LEFTJUSTIFIED, "expression missing"); _ERROR_ }  	     

  	if (parseTerm(token__SYM_COMMA)){

      if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__LEFTJUSTIFIED, "expression missing"); _ERROR_ }
   
  	  if (parseTerm(token__SYM_COMMA)){

        if (!(bEXPRESSION2 = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__LEFTJUSTIFIED, "expression missing"); _ERROR_ }
     
      }
    }  	      

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__LEFTJUSTIFIED, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			p->wr_LEFTJUSTIFIED(pcode__LEFTJUSTIFIED, bEXPRESSION, bEXPRESSION2, bReturn);
   		}

   		parseInfo(p, "parsed LEFTJUSTIFIED");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fRIGHTJUSTIFIED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__RIGHTJUSTIFIED))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__RIGHTJUSTIFIED, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__RIGHTJUSTIFIED, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__RIGHTJUSTIFIED, "expression missing"); _ERROR_ }  	     

  	if (parseTerm(token__SYM_COMMA)){

      if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__RIGHTJUSTIFIED, "expression missing"); _ERROR_ }
   
  	  if (parseTerm(token__SYM_COMMA)){

        if (!(bEXPRESSION2 = fBOOLEAN_EXPRESSION(p))){ syntaxError(token__RIGHTJUSTIFIED, "expression missing"); _ERROR_ }
     
      }
    }  	      

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__RIGHTJUSTIFIED, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			p->wr_RIGHTJUSTIFIED(pcode__RIGHTJUSTIFIED, bEXPRESSION, bEXPRESSION2, bReturn);
   		}

   		parseInfo(p, "parsed RIGHTJUSTIFIED");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fSECTION(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__SECTION))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__SECTION, "string expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(bTerm_COMMA = parseTerm(token__SYM_COMMA))){ syntaxError(token__SECTION, ", missing"); _ERROR_ }

    if (!fSTRING_EXPRESSION(p)){ syntaxError(token__SECTION, "string expression missing"); _ERROR_ }  	     

  	if (!parseTerm(token__SYM_COMMA)){ syntaxError(token__SECTION, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__SECTION, "expression missing"); _ERROR_ }  	     

  	if (parseTerm(token__SYM_COMMA)){

      if (!(bEXPRESSION = fINTEGER_EXPRESSION(p))){ syntaxError(token__SECTION, "expression missing"); _ERROR_ }
   
  	  if (parseTerm(token__SYM_COMMA)){

        if (!(bEXPRESSION2 = fSTRING_EXPRESSION(p))){ syntaxError(token__SECTION, "expression missing"); _ERROR_ }
     
      }
    }  	      

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SECTION, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			p->wr_SECTION(pcode__SECTION, bEXPRESSION, bEXPRESSION2, bReturn);
   		}

   		parseInfo(p, "parsed SECTION");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fSIMPLIFIED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__SIMPLIFIED))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__SIMPLIFIED, "string expression missing"); _ERROR_ }
  	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SIMPLIFIED, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			p->wr_SIMPLIFIED(pcode__SIMPLIFIED, bReturn);
   		}

   		parseInfo(p, "parsed SIMPLIFIED");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fTRIMMED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__TRIMMED))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__TRIMMED, "string expression missing"); _ERROR_ }
  	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__TRIMMED, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			p->wr_TRIMMED(pcode__TRIMMED, bReturn);
   		}

   		parseInfo(p, "parsed TRIMMED");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fREVERSED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__REVERSED))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	bool bEXPRESSION2 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__REVERSED, "string expression missing"); _ERROR_ }
  	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__REVERSED, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			p->wr_REVERSED(pcode__REVERSED, bReturn);
   		}

   		parseInfo(p, "parsed REVERSED");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fUNICODE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__UNICODE))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;

	bool bEXPRESSION = false;
	//bool bEXPRESSION2 = false;
	//bool bEXPRESSION3 = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
    
    if (!bObjectFake && (bEXPRESSION = fINTEGER_EXPRESSION(p))){ 

      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__UNICODE, ") missing"); _ERROR_ }

    } else {

      if (!bObjectFake && !(fSTRING_EXPRESSION(p))){ syntaxError(token__UNICODE, "string expression missing"); _ERROR_ }
    	
      if (!fINTEGER_EXPRESSION(p)){ syntaxError(token__UNICODE, "expression missing"); _ERROR_ }

      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__UNICODE, ") missing"); _ERROR_ }

    }

  	{

      *nReturnExpressionType = bEXPRESSION ? pcode__QSTRING : pcode__INTEGER; 

   		if (bProducePcode){
  			p->wr_UNICODE(pcode__UNICODE, false, bEXPRESSION, bReturn);
   		}

   		parseInfo(p, "parsed UNICODE");
   		_DONE_
  	}
	}

	_END_
}

/**
[KBASIC][VB][QBASIC]
NAME: FILECOPY
PRINTNAME: FileCopy
TASK: copies a file from source to destination
SYNTAX: FILECOPY
DESC: FILECOPY source$, destination$
CODE:
FILECOPY "test.dat", "test2.dat"
FILECOPY "test2.dat", "test.dat"
EXAMPLES: filecopy.kbasic
CATEGORY: SUB, BUILTIN, FILE
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fFILECOPY(pcode *p, int *nReturnExpressionType, bool bReturn)
/*
[*]
[VB]
[*]
[*]
*/
{

	//bool bTerm_FILECOPY = false;
	_BEGIN_
  if (!(/*bTerm_FILECOPY = */parseTerm(token__FILECOPY))){ _END_ }

	

	bool bEXPRESSION = false;

	bool bEXPRESSION2 = false;

	bool bTerm_COMMA = false;

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

  if (!(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__FILECOPY, "expression missing"); _ERROR_ }

 	if (!(parseTerm(token__SYM_COMMA))){
		{ syntaxError(token__FILECOPY, ", missing"); _ERROR_ }
	}

	if (!(bEXPRESSION2 = fSTRING_EXPRESSION(p))){ syntaxError(token__FILECOPY, "expression missing"); _ERROR_ }

  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
 	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__FILECOPY, ") missing"); _ERROR_ }

	{
      *nReturnExpressionType = pcode__BOOLEAN; 

 		if (bProducePcode){
   		p->wr_FILECOPY(pcode__FILECOPY, bReturn);
 		}

 		parseInfo(p, "parsed FILECOPY");
 		_DONE_
	}

	_END_
}


bool parser::fREADBINARY(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{

  _BEGIN_
  if (!(parseTerm(token__READBINARY))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
	bool bTerm_COMMA = false;
	bool bEXPRESSION = false;
  

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){
    
    if (!bObjectFake){
      if (!fVARIABLE(p, &nPeekVar, &PeekScope, &nPeekType)){ syntaxError(token__PEEK, "string variable missing"); _ERROR_ }

	     if (nPeekType == token__ME){
           { semanticError(token__READBINARY, "READBINARY not allowed in combination with ME"); _ERROR_ }
	     } else if (nPeekType == token__PARENT){
           { semanticError(token__READBINARY, "READBINARY not allowed in combination with PARENT"); _ERROR_ }
	     } else if (nPeekType != pcode__QString){
           { semanticError(token__READBINARY, "wrong datatype"); _ERROR_ }
       } else {
         if (bProducePcode){
            p->wr_PUSH_ID(pcode__PUSH_ID, nPeekVar, PeekScope, false);
         }
       }
    }

    if (nExpectedType <= 0){
      { semanticError(token__READBINARY, "READBINARY: Could not determine the right type for return"); _ERROR_ }
    }

    switch(nExpectedType){
      case pcode__BOOLEAN:
        break;
      case pcode__QSTRING:
      //case pcode__CSTRING:
        if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__WRITEBINARY, ", missing"); _ERROR_ }
        //if (bEXPRESSION = fNUMERIC_EXPRESSION(p)){}
          //syntaxError(token__READBINARY, "expression missing"); _ERROR_ }
        break;
      case pcode__BYTE:
      case pcode__SHORT:
      case pcode__INTEGER:
      case pcode__LONG:
        break;
      case pcode__SINGLE:
      case pcode__DOUBLE:
        break;
      case pcode__CURRENCY:
      case pcode__DATE:
        break;
    }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
 	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__READBINARY, ") missing"); _ERROR_ }

    bool bThrows = false;
    if (parseTerm(token__THROWS)){ 
      const char *acException = "";
      if (!fID_KEYWORD_OR_BUILTIN(&acException)){ syntaxError(pcode__CAST, "exception name missing (Exception)"); _ERROR_ }
      if (utility::my_stricmp(acException, "Exception") == 0){
        bThrows = true;
      } else {
        { semanticError(pcode__CAST, "exception name not allowed (require Exception)"); _ERROR_ }
      }

    }

    if (bThrows){
      memory_sub *s2 = 0;
      int nId2 = 0;
      int nSubId2 = 0;

      switch(isScopeClass()){
				  case false:
             nId2 = myModule->getId(getScope());
   				    s2 = myModule->getSubs(nId2);
             nSubId2 = s2->getId(nId2, getSub());
					    break;
				    case true:
             nId2 = myClass->getId(getScope());
   				    s2 = myClass->getMethods(nId2);
             nSubId2 = s2->getId(nId2, getMethod());
					    break;
		  }

      registerCatch(nId2, s2, nSubId2, p, pcode__EXCEPTION);
    }

  	{

      *nReturnExpressionType = pcode__VARIANT; 

   		if (bProducePcode){
  			p->wr_READBINARY(pcode__READBINARY, nPeekVar, PeekScope, nExpectedType, bEXPRESSION, bReturn);
   		}

   		parseInfo(p, "parsed READBINARY");
   		_DONE_
  	}
	}

	_END_
}

bool parser::fSEEKBINARY(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__SEEKBINARY))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
  bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){


    if (!bObjectFake){
      if (!fVARIABLE(p, &nPeekVar, &PeekScope, &nPeekType)){ syntaxError(token__PEEK, "string variable missing"); _ERROR_ }

	     if (nPeekType == token__ME){
           { semanticError(token__SEEKBINARY, "SEEKBINARY not allowed in combination with ME"); _ERROR_ }
	     } else if (nPeekType == token__PARENT){
           { semanticError(token__SEEKBINARY, "SEEKBINARY not allowed in combination with PARENT"); _ERROR_ }
	     } else if (nPeekType != pcode__QString){
           { semanticError(token__SEEKBINARY, "wrong datatype"); _ERROR_ }
       } else {
         if (bProducePcode){
            p->wr_PUSH_ID(pcode__PUSH_ID, nPeekVar, PeekScope, false);
         }
       }
    }

  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__SEEKBINARY, ", missing"); _ERROR_ }

    if (bEXPRESSION = fNUMERIC_EXPRESSION(p)){}// syntaxError(token__SEEKBINARY, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SEEKBINARY, ") missing"); _ERROR_ }
 
    bool bThrows = false;
    if (parseTerm(token__THROWS)){ 
      const char *acException = "";
      if (!fID_KEYWORD_OR_BUILTIN(&acException)){ syntaxError(pcode__CAST, "exception name missing (Exception)"); _ERROR_ }
      if (utility::my_stricmp(acException, "Exception") == 0){
        bThrows = true;
      } else {
        { semanticError(pcode__CAST, "exception name not allowed (require Exception)"); _ERROR_ }
      }

    }

    if (bThrows){
      memory_sub *s2 = 0;
      int nId2 = 0;
      int nSubId2 = 0;

      switch(isScopeClass()){
				  case false:
             nId2 = myModule->getId(getScope());
   				    s2 = myModule->getSubs(nId2);
             nSubId2 = s2->getId(nId2, getSub());
					    break;
				    case true:
             nId2 = myClass->getId(getScope());
   				    s2 = myClass->getMethods(nId2);
             nSubId2 = s2->getId(nId2, getMethod());
					    break;
		  }

      registerCatch(nId2, s2, nSubId2, p, pcode__EXCEPTION);
    }

    *nReturnExpressionType = pcode__INTEGER; 

 	  if (bProducePcode){
       p->wr_SEEKBINARY(pcode__SEEKBINARY, nPeekVar, PeekScope, bEXPRESSION, bReturn);
 	  }

 	  parseInfo(p, "parsed SEEKBINARY");
 	  _DONE_

  }
  
	_END_
}

bool parser::fDAYOFWEEK(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__DAYOFWEEK))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;
 	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__DAYOFWEEK, "date expression missing"); _ERROR_ }
 	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__DAYOFWEEK, ", missing"); _ERROR_ }
  
    if (bEXPRESSION = fSTRING_EXPRESSION(p)){}

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__DAYOFWEEK, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__QSTRING; 

 	  if (bProducePcode){
       p->wr_DAYOFWEEK(pcode__DAYOFWEEK, bEXPRESSION, bReturn);
 	  }

 	  parseInfo(p, "parsed DAYOFWEEK");
 	  _DONE_

  }
  
	_END_
}

bool parser::fDAYOFYEAR(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__DAYOFYEAR))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__DIFFDAY, "date expression missing"); _ERROR_ }
 	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DAYOFYEAR, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__INTEGER; 

 	  if (bProducePcode){
       p->wr_DAYOFYEAR(pcode__DAYOFYEAR, bReturn);
 	  }

 	  parseInfo(p, "parsed DAYOFYEAR");
 	  _DONE_

  }
  
	_END_
}

bool parser::fDAYSINMONTH(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__DAYSINMONTH))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__DIFFDAY, "date expression missing"); _ERROR_ }
 	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__DAYSINMONTH, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__INTEGER; 

 	  if (bProducePcode){
       p->wr_DAYSINMONTH(pcode__DAYSINMONTH, bReturn);
 	  }

 	  parseInfo(p, "parsed DAYSINMONTH");
 	  _DONE_

  }
  
	_END_
}

bool parser::fDAYSINYEAR(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__DAYSINYEAR))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__DIFFDAY, "date expression missing"); _ERROR_ }
 	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__DAYSINYEAR, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__INTEGER; 

 	  if (bProducePcode){
       p->wr_DAYSINYEAR(pcode__DAYSINYEAR, bReturn);
 	  }

 	  parseInfo(p, "parsed DAYSINYEAR");
 	  _DONE_

  }
  
	_END_
}

bool parser::fWEEKNUMBER(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__WEEKNUMBER))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__DIFFDAY, "date expression missing"); _ERROR_ }
 	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__WEEKNUMBER, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__INTEGER; 

 	  if (bProducePcode){
       p->wr_WEEKNUMBER(pcode__WEEKNUMBER, bReturn);
 	  }

 	  parseInfo(p, "parsed WEEKNUMBER");
 	  _DONE_

  }
  
	_END_
}

bool parser::fISLEAPYEAR(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ISLEAPYEAR))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__DIFFDAY, "date expression missing"); _ERROR_ }
 	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ISLEAPYEAR, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__BOOLEAN; 

 	  if (bProducePcode){
       p->wr_ISLEAPYEAR(pcode__ISLEAPYEAR, bReturn);
 	  }

 	  parseInfo(p, "parsed ISLEAPYEAR");
 	  _DONE_

  }
  
	_END_
}

bool parser::fDIFFDAY(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__DIFFDAY))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__DIFFDAY, "date expression missing"); _ERROR_ }
 	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__DIFFDAY, ", missing"); _ERROR_ }

    if (fDATE_EXPRESSION(p)){ syntaxError(pcode__DIFFDAY, "date expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__DIFFDAY, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__INTEGER; 

 	  if (bProducePcode){
       p->wr_DIFFDAY(pcode__DIFFDAY, bReturn);
 	  }

 	  parseInfo(p, "parsed DIFFDAY");
 	  _DONE_

  }
  
	_END_
}

bool parser::fDIFFSECONDS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__DIFFSECONDS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__DIFFSECONDS, "date expression missing"); _ERROR_ }
 	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__DIFFSECONDS, ", missing"); _ERROR_ }

    if (fDATE_EXPRESSION(p)){ syntaxError(pcode__DIFFSECONDS, "date expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__DIFFSECONDS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__INTEGER; 

 	  if (bProducePcode){
       p->wr_DIFFSECONDS(pcode__DIFFSECONDS, bReturn);
 	  }

 	  parseInfo(p, "parsed DIFFSECONDS");
 	  _DONE_

  }
  
	_END_
}

bool parser::fISDATEVALID(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ISDATEVALID))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__ISDATEVALID, "date expression missing"); _ERROR_ }
 	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ISDATEVALID, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__BOOLEAN; 

 	  if (bProducePcode){
       p->wr_ISDATEVALID(pcode__ISDATEVALID, bReturn);
 	  }

 	  parseInfo(p, "parsed ISDATEVALID");
 	  _DONE_

  }
  
	_END_
}

bool parser::fISTIMEVALID(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ISTIMEVALID))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__ISTIMEVALID, "date expression missing"); _ERROR_ }
 	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ISTIMEVALID, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__BOOLEAN; 

 	  if (bProducePcode){
       p->wr_ISTIMEVALID(pcode__ISTIMEVALID, bReturn);
 	  }

 	  parseInfo(p, "parsed ISTIMEVALID");
 	  _DONE_

  }
  
	_END_
}
  
bool parser::fISDATETIMEVALID(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ISDATETIMEVALID))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !fDATE_EXPRESSION(p)){ syntaxError(pcode__ISDATETIMEVALID, "date expression missing"); _ERROR_ }
 	
    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ISDATETIMEVALID, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__BOOLEAN; 

 	  if (bProducePcode){
       p->wr_ISDATETIMEVALID(pcode__ISDATETIMEVALID, bReturn);
 	  }

 	  parseInfo(p, "parsed ISDATETIMEVALID");
 	  _DONE_

  }
  
	_END_
}

/*
bool parser::fADDDATE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ADDDATE))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(token__ADDDATE, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__ADDDATE, ", missing"); _ERROR_ }

    if (!fDATE_EXPRESSION(p)){ syntaxError(token__ADDDATE, "date expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ADDDATE, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_ADDDATE(pcode__ADDDATE, bReturn);
   	  }

   	  parseInfo(p, "parsed ADDDATE");
   	  _DONE_
  }
  
	_END_
}*/

bool parser::fADDDAYS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ADDDAYS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__ADDDAYS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__ADDDAYS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__ADDDAYS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ADDDAYS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_ADDDAYS(pcode__ADDDAYS, bReturn);
   	  }

   	  parseInfo(p, "parsed ADDDAYS");
   	  _DONE_
  }
  
	_END_
}

bool parser::fADDMONTHS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ADDMONTHS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__ADDMONTHS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__ADDMONTHS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__ADDMONTHS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ADDMONTHS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_ADDMONTHS(pcode__ADDMONTHS, bReturn);
   	  }

   	  parseInfo(p, "parsed ADDMONTHS");
   	  _DONE_
  }
  
	_END_
}

bool parser::fADDYEARS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ADDYEARS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__ADDYEARS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__ADDYEARS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__ADDYEARS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ADDYEARS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_ADDYEARS(pcode__ADDYEARS, bReturn);
   	  }

   	  parseInfo(p, "parsed ADDMONTHS");
   	  _DONE_
  }
  
	_END_
}

/*
bool parser::fSUBDATE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__SUBDATE))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(token__SUBDATE, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(token__SUBDATE, ", missing"); _ERROR_ }

    if (!fDATE_EXPRESSION(p)){ syntaxError(token__SUBDATE, "date expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SUBDATE, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_SUBDATE(pcode__SUBDATE, bReturn);
   	  }

   	  parseInfo(p, "parsed SUBDATE");
   	  _DONE_
  }
  
	_END_
}
*/

bool parser::fSUBDAYS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__SUBDAYS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__SUBDAYS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__SUBDAYS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__SUBDAYS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__SUBDAYS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_SUBDAYS(pcode__SUBDAYS, bReturn);
   	  }

   	  parseInfo(p, "parsed SUBDAYS");
   	  _DONE_
  }
  
	_END_
}

bool parser::fSUBMONTHS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__SUBMONTHS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__SUBMONTHS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__SUBMONTHS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__SUBMONTHS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__SUBMONTHS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_SUBMONTHS(pcode__SUBMONTHS, bReturn);
   	  }

   	  parseInfo(p, "parsed SUBMONTHS");
   	  _DONE_
  }
  
	_END_
}

bool parser::fSUBYEARS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__SUBYEARS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__SUBYEARS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__SUBYEARS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__SUBYEARS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__SUBYEARS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_SUBYEARS(pcode__SUBYEARS, bReturn);
   	  }

   	  parseInfo(p, "parsed SUBMONTHS");
   	  _DONE_
  }
  
	_END_
}

/*
bool parser::fADDTIME(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ADDTIME))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__ADDTIME, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__ADDTIME, ", missing"); _ERROR_ }

    if (!fDATE_EXPRESSION(p)){ syntaxError(pcode__ADDTIME, "date expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ADDTIME, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_ADDTIME(pcode__ADDTIME, bReturn);
   	  }

   	  parseInfo(p, "parsed ADDTIME");
   	  _DONE_
  }
  
	_END_
}*/

bool parser::fADDHOURS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ADDHOURS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__ADDHOURS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__ADDHOURS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__ADDHOURS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ADDHOURS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_ADDHOURS(pcode__ADDHOURS, bReturn);
   	  }

   	  parseInfo(p, "parsed ADDHOURS");
   	  _DONE_
  }
  
	_END_
}

bool parser::fADDMINUTES(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ADDMINUTES))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__ADDMINUTES, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__ADDMINUTES, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__ADDMINUTES, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ADDMINUTES, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_ADDMINUTES(pcode__ADDMINUTES, bReturn);
   	  }

   	  parseInfo(p, "parsed ADDMINUTES");
   	  _DONE_
  }
  
	_END_
}

bool parser::fADDSECONDS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__ADDSECONDS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__ADDSECONDS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__ADDSECONDS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__ADDSECONDS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__ADDSECONDS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_ADDSECONDS(pcode__ADDSECONDS, bReturn);
   	  }

   	  parseInfo(p, "parsed ADDSECONDS");
   	  _DONE_
  }
  
	_END_
}

/*
bool parser::fSUBTIME(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__SUBTIME))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__SUBTIME, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__SUBTIME, ", missing"); _ERROR_ }

    if (!fDATE_EXPRESSION(p)){ syntaxError(pcode__SUBTIME, "date expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__SUBTIME, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_SUBTIME(pcode__SUBTIME, bReturn);
   	  }

   	  parseInfo(p, "parsed SUBTIME");
   	  _DONE_
  }
  
	_END_
}*/

bool parser::fSUBHOURS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__SUBHOURS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__SUBHOURS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__SUBHOURS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__SUBHOURS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__SUBHOURS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_SUBHOURS(pcode__SUBHOURS, bReturn);
   	  }

   	  parseInfo(p, "parsed SUBHOURS");
   	  _DONE_
  }
  
	_END_
}

bool parser::fSUBMINUTES(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__SUBMINUTES))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__SUBMINUTES, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__SUBMINUTES, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__SUBMINUTES, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__SUBMINUTES, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_SUBMINUTES(pcode__SUBMINUTES, bReturn);
   	  }

   	  parseInfo(p, "parsed SUBMINUTES");
   	  _DONE_
  }
  
	_END_
}

bool parser::fSUBSECONDS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
	_BEGIN_

  if (!(parseTerm(token__SUBSECONDS))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

    if (!bObjectFake && !(fDATE_EXPRESSION(p))){ syntaxError(pcode__SUBSECONDS, "date expression missing"); _ERROR_ }
  	
    if (!bObjectFake && !(parseTerm(token__SYM_COMMA))){ syntaxError(pcode__SUBSECONDS, ", missing"); _ERROR_ }

    if (!fINTEGER_EXPRESSION(p)){ syntaxError(pcode__SUBSECONDS, "expression missing"); _ERROR_ }  	     

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(pcode__SUBSECONDS, ") missing"); _ERROR_ }
 
    *nReturnExpressionType = pcode__DATE; 

   	  if (bProducePcode){
         p->wr_SUBSECONDS(pcode__SUBSECONDS, bReturn);
   	  }

   	  parseInfo(p, "parsed SUBSECONDS");
   	  _DONE_
  }
  
	_END_
}

bool parser::fENCODE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
  _BEGIN_
  
  if (!(parseTerm(token__ENCODE))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__ENCODE, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ENCODE, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			 p->wr_ENCODE(pcode__ENCODE, bReturn);
   		}

   		parseInfo(p, "parsed ENCODE");
   		_DONE_
  	}
	}
// 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__ENCODE, "( missing"); _ERROR_ }

	_END_
}

bool parser::fDECODE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake)
{
  _BEGIN_
  
  if (!(parseTerm(token__DECODE))){ _END_ }

 	bool bTerm_SYM_BR_OP;
 	bool bTerm_SYM_BR_CL;

	bool bEXPRESSION = false;

	if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

  	if (!bObjectFake && !(bEXPRESSION = fSTRING_EXPRESSION(p))){ syntaxError(token__DECODE, "expression missing"); _ERROR_ }

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__DECODE, ") missing"); _ERROR_ }

  	{

  		*nReturnExpressionType = pcode__QSTRING;

   		if (bProducePcode){
  			 p->wr_DECODE(pcode__DECODE, bReturn);
   		}

   		parseInfo(p, "parsed DECODE");
   		_DONE_
  	}
	}
// 	//if (!bTerm_SYM_BR_OP){ syntaxError(token__DECODE, "( missing"); _ERROR_ }

	_END_
}
