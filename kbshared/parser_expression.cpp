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

/**
[KBASIC][VB][QBASIC]
NAME: OPERATORADD
PRINTNAME: +
TASK: adding two values
SYNTAX: EXPRESSION + EXPRESSION
DESC: 
CODE:
DIM m AS INTEGER
m = 12 + 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/

/**
[KBASIC][VB][QBASIC]
NAME: OPERATORSUB
PRINTNAME: -
TASK: substracting two values
SYNTAX: EXPRESSION - EXPRESSION
DESC: 
CODE:
DIM m AS INTEGER
m = 12 - 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORMUL
PRINTNAME: *
TASK: multiplying two values
SYNTAX: EXPRESSION * EXPRESSION
DESC: 
CODE:
DIM m AS INTEGER
m = 12 * 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORDIV
PRINTNAME: /
TASK: divides two values
SYNTAX: EXPRESSION / EXPRESSION
DESC: 
CODE:
DIM m AS INTEGER
m = 12 / 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORIDIV
PRINTNAME: \
TASK: divide two values, returns an integer value
SYNTAX: EXPRESSION \ EXPRESSION
DESC: 
CODE:
DIM m AS INTEGER
m = 12 \ 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORMOD
PRINTNAME: Mod
TASK: returns the rest of a division of two values
SYNTAX: EXPRESSION MOD EXPRESSION
DESC: 
CODE:
DIM m AS INTEGER
m = 12 MOD 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATOREQUAL
PRINTNAME: =
TASK: compares two values, if they are equal
SYNTAX: EXPRESSION = EXPRESSION
DESC: 
CODE:
PRINT 12 = 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORUNEQUAL
PRINTNAME: <>
TASK: compares two values, if they are unequal
SYNTAX: EXPRESSION <> EXPRESSION
DESC: 
CODE:
PRINT 12 <> 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORSMALLER
PRINTNAME: <
TASK: compares two values, returns true if left value is smaller
SYNTAX: EXPRESSION < EXPRESSION
DESC: 
CODE:
PRINT 12 < 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORBIGGER
PRINTNAME: >
TASK: compares two values, returns true if right value is smaller
SYNTAX: EXPRESSION > EXPRESSION
DESC: 
CODE:
PRINT 12 > 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORSMALLEREQUAL
PRINTNAME: <=
TASK: compares two values, returns true if left value is smaller or equal
SYNTAX: EXPRESSION <= EXPRESSION
DESC: 
CODE:
PRINT 12 <= 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORBIGGEREQUAL
PRINTNAME: >=
TASK: compares two values, returns true if right value is smaller or equal
SYNTAX: EXPRESSION >= EXPRESSION
DESC: 
CODE:
PRINT 12 >= 65
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORANDALSO
PRINTNAME: AndAlso
TASK: both conditions must be true
SYNTAX: EXPRESSION ANDALSO EXPRESSION
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORORELSE
PRINTNAME: OrElse
TASK: one of two conditions must be true
SYNTAX: EXPRESSION ORELSE EXPRESSION
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORAND
PRINTNAME: And
TASK: bitwise and
SYNTAX: EXPRESSION AND EXPRESSION
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATOROR
PRINTNAME: Or
TASK: bitwise or
SYNTAX: EXPRESSION OR EXPRESSION
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORXOR
PRINTNAME: Xor
TASK: bitwise xor
SYNTAX: EXPRESSION XOR EXPRESSION
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORNOT
PRINTNAME: Not
TASK: bitwise not
SYNTAX: NOT EXPRESSION
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORPOWER
PRINTNAME: ^
TASK: 
SYNTAX: BASE ^ EXPONENT
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORCONCAT
PRINTNAME: &
TASK: adds two strings
SYNTAX: EXPRESSION & EXPRESSION
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATOREQV
PRINTNAME: Eqv
TASK: means x Eqv y = Not (x Xor y)
SYNTAX: EXPRESSION EQV EXPRESSION
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/
/**
[KBASIC][VB][QBASIC]
NAME: OPERATORIMP
PRINTNAME: Imp
TASK: means x Imp y = Not (x And Not y) 
SYNTAX: EXPRESSION Imp EXPRESSION
DESC: 
CODE:
EXAMPLES: 
CATEGORY: OPERATOR
SEEALSO: 
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP:
*/


// used for addressOf()
bool parser::fADDRESSOF(pcode *p, bool bParseTermAddressOf)
{
	_BEGIN_

  if (bParseTermAddressOf && !parseTerm(token__ADDRESSOF)){ _END_ }

	bool bIDENTIFIER = false;
	int nType = 0;
	int nIdType = 0;
	bool bImplicitDIM = false;
	bool bTestImplicitDim = true;   
	int nVar = 0;
	t_scope scope = global;
	t_arrayVariable a;  
	bool bAllSize = false;
	int nLStringLen = 0;
	bool bReference = false;
	bool bProperty = false;
	bool bTestProperty = false;   

	bool bTerm_SYM_BR_OP = false;
  bool bTerm_SYM_BR_CL = false;

  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){}

	if (fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bAllSize, &nLStringLen, &bReference, &bProperty, bTestProperty)){

		if (nType == token__ME){
      { semanticError(token__KEYWORD, "ADDRESSOF not allowed in combination with ME"); _ERROR_ }
		} else if (nType == token__PARENT){
      { semanticError(token__KEYWORD, "ADDRESSOF not allowed in combination with PARENT"); _ERROR_ }
    } else {
    }

    {
  		if (bProducePcode){
 				p->wr_PUSH_IDPOINTER(pcode__PUSH_IDPOINTER, nVar, scope);

			}
		}
    if ((bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ADDRESSOF, ") missing"); _ERROR_ }

    _DONE_
	}

  
  { syntaxError(token__ADDRESSOF, " identifier missing"); _ERROR_ }

	_END_
}

bool parser::fPOINTER(pcode *p, int nPointerType)
{
	_BEGIN_


	bool bIDENTIFIER = false;
	int nType = 0;
	int nIdType = 0;
	bool bImplicitDIM = false;
	bool bTestImplicitDim = true;   
	int nVar = 0;
	t_scope scope = global;
	t_arrayVariable a;  
	bool bAllSize = false;
	int nLStringLen = 0;
	bool bReference = false;
	bool bProperty = false;
	bool bTestProperty = false;   

	bool bTerm_ADDRESSOF = false;

  if ((bTerm_ADDRESSOF = parseTerm(token__ADDRESSOF))){}

	bool bTerm_SYM_BR_OP = false;
  bool bTerm_SYM_BR_CL = false;

  // addressof nicht zwingend vor variablenname
  if (bTerm_ADDRESSOF && (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}

	if (bIDENTIFIER = fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bAllSize, &nLStringLen, &bReference, &bProperty, bTestProperty)){

		if (nType == token__ME){
      { semanticError(token__KEYWORD, "ADDRESSOF not allowed in combination with ME"); _ERROR_ }
		} else if (nType == token__PARENT){
      { semanticError(token__KEYWORD, "ADDRESSOF not allowed in combination with PARENT"); _ERROR_ }
    } else {
    }

		if (nPointerType == nType){
  		if (bProducePcode){


        p->wr_PUSH_IDPOINTER(pcode__PUSH_IDPOINTER, nVar, scope);
				_DONE_
			}
		}
    if (bTerm_ADDRESSOF && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}
	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__ADDRESSOF, ") missing"); _ERROR_ }
	}

  if (bTerm_ADDRESSOF && !bIDENTIFIER){ syntaxError(token__ADDRESSOF, " identifier missing"); _ERROR_ }

	_END_
}

bool parser::nextTokenIsKeyword()
{
  register int n = peekToken();

  return strlen(token::keyword_(n)) != 0;
}

inline bool parser::nextTokenIsOperator()
{
  //int nOperator = 0;

  register int n = peekToken();

  if (
     n == token__OP_XOR
  || n == token__OP_OR
  || n == token__OP_AND
  || n == token__OP_EQUAL
  || n == token__IS
  || n == token__LIKE
  || n == token__OP_UNEQUAL
  || n == token__OP_GREATER
  || n == token__OP_LESSER
  || n == token__OP_GREATER_EQUAL
  || n == token__OP_LESSER_EQUAL
  || n == token__OP_ADD
  || n == token__OP_SUB
  || n == token__OP_DIV
  || n == token__OP_IDIV
  || n == token__OP_EQV
  || n == token__OP_IMP
  || n == token__OP_STR_CAT
  || n == token__OP_MUL
  || n == token__OP_MOD
  || n == token__OP_POWER
  || n == token__OP_NOT
  || n == token__OP_SHL
//  || n == token__OP_SHL_
  || n == token__OP_SHR
  //|| n == token__OP_SHR_
  || n == token__OP_INC
  //|| n == token__OP_INC_
  || n == token__OP_DEC
  //|| n == token__OP_DEC_
  /*
  || n == token__OP_ADD_EQUAL
  || n == token__OP_SUB_EQUAL
  || n == token__OP_DIV_EQUAL
  || n == token__OP_MUL_EQUAL*/
  || n == token__OP_ANDALSO
  || n == token__OP_ORELSE
  //|| n == token__OP_OR_EQUAL
//  || n == token__OP_AND_EQUAL
  || n == token__OP_BIT_AND
  || n == token__OP_BIT_OR
  || n == token__OP_BIT_XOR
  || n == token__OP_BIT_NOT
/*
  || n == token__OP_OR2
  || n == token__OP_NOT2
  || n == token__OP_EQUAL2
  || n == token__OP_UNEQUAL2
  || n == token__OP_AND_EQUAL
  || n == token__OP_OR_EQUAL
  || n == token__OP_XOR_EQUAL
  || n == token__OP_LESSER_LESSER
  || n == token__OP_GREATER_GREATER*/

  ) return true; 


	return false;
}

bool parser::nextTokenIsSymbol()
{

  register int n = peekToken();

  if (
     n == token__SYM_BR_OP
  || n == token__SYM_BR_CL
  || n == token__SYM_BC_OP
  || n == token__SYM_BC_CL
  || n == token__SYM_BS_OP
  || n == token__SYM_BS_CL
  || n == token__SYM_COMMA
  || n == token__SYM_COLON
  || n == token__SYM_DOT
  || n == token__SYM_EXCLAMATION
  || n == token__SYM_HASH
  || n == token__SYM_QM
  || n == token__SYM_SEMICOL
  || n == token__SYM_UL) return true; 

	return false;
}

bool parser::fBOOLEAN_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__BOOLEAN); }
bool parser::fBYTE_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__BYTE); }
bool parser::fSTRING_REFERENCE(pcode *p, int *nType){ return fREFERENCE(p, pcode__QSTRING, nType) || fREFERENCE(p, pcode__CSTRING, nType); }
bool parser::fQSTRING_REFERENCE(pcode *p, int *nType){ return fREFERENCE(p, pcode__QSTRING, nType); }
bool parser::fCSTRING_REFERENCE(pcode *p, int *nType){ return fREFERENCE(p, pcode__CSTRING, nType); }
bool parser::fINTEGER_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__INTEGER); }
bool parser::fSHORT_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__SHORT); }
bool parser::fLONG_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__LONG); }
bool parser::fSINGLE_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__SINGLE); }
bool parser::fDOUBLE_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__DOUBLE); }

bool parser::fDATE_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__DATE); }
bool parser::fCURRENCY_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__CURRENCY); }
bool parser::fVARIANT_REFERENCE(pcode *p){ return fREFERENCE(p, pcode__VARIANT); }

/* *
[EXPLANATION]
NAME: REFERENCE
DESC:
SEEALSO:
*/
// used for ByRef
bool parser::fREFERENCE(pcode *p, int nReferenceType, int *_nType)
{
	_BEGIN_

	bool bIDENTIFIER = false;
	int nType = 0;
	int nIdType = 0;
	bool bImplicitDIM = false;
	bool bTestImplicitDim = true;   
	int nVar = 0;
  t_scope scope = global;
	t_arrayVariable a;  
	bool bAllSize = false;
  int nLStringLen = 0;
	bool bReference = false;  
	bool bProperty = false;  
  bool bTestProperty = false;   
  

	if (fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bAllSize, &nLStringLen, &bReference, &bProperty, bTestProperty)){

		if (nType == token__ME){
      { semanticError(token__KEYWORD, "REFERENCE not allowed in combination with ME"); _ERROR_ }
		} else if (nType == token__PARENT){
      { semanticError(token__KEYWORD, "REFERENCE not allowed in combination with PARENT"); _ERROR_ }
    } else {
    }

		if (nReferenceType == nType || (nReferenceType == pcode__QSTRING && nType == pcode__CSTRING && nType == pcode__LQSTRING && nType == pcode__LCSTRING)){

      if (nReferenceType == pcode__QSTRING && nType == pcode__LQSTRING){
        *_nType = pcode__LQSTRING;
      } else if (nReferenceType == pcode__CSTRING && nType == pcode__LCSTRING){
        *_nType = pcode__LCSTRING;
      } else if (_nType){
        *_nType = nType;
      }
						
			if (nextTokenIsOperator()){ _END_ } // it is supposed to be a expression

  		if (bProducePcode){
    	/*  
HINT
einzuelne felder eines types können auch per reference übergeben werden, anders als in vb6

Type t
i As Integer
m As Double
End Type

Sub kk()
Dim l As t

l.i = 9
l.m = 12
hh (l.m)
Debug.Print l.m

End Sub

Sub hh(ByRef d As Double)
d = 99
End Sub

array und type parameter immer bei ref

        */
				
				p->wr_PUSH_IDREF(pcode__PUSH_IDREF, nVar, scope);
			}

      _DONE_
		}

	}
	_END_
}
									
bool parser::fFACTOR(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	_BEGIN_

  t_integer nInteger;// = 0;
	t_long lLongInteger;// = 0;
	t_double dNumeric;// = 0;
	t_single fNumeric;// = 0;
	t_boolean bBoolean;// = false;
	t_cstring acString;// = "";
	t_byte ucByte;// = 0;
	t_currency myCurrency;
	t_date myDate;	
  int nExpressionType = 0;
  t_scope scope = global;
  bool bUnknownFunction = false;
  int nAccessScopeId = 0;
  int nAccessScope = 0;



#ifdef KBDEBUG
  if (stopAtLine(133)){
    int i = 3;
    i++;
  }
#endif
	
	const char *acIdentifier;// = "";


	// builtin functions with higher priority
  if (fBUILTIN_FUNCTION(pp, nReturnExpressionType, true)) _DONE_


  if (bWithoutBuiltin == false){
	  if (fFUNCTION_CALL(pp, &acIdentifier, nReturnExpressionType, true, &bUnknownFunction)) _DONE_ 

    // builtin classes
	  if (fKBASIC(pp, nReturnExpressionType, true)) _DONE_ // must be placed before literals checking

  }

  bool bDebug;
  if (bDebug = parseTerm(token__DEBUG)){
    if (!parseTerm(token__SYM_DOT)){ _ERROR_ }    
  }

	// literals
  switch(peekToken()){
    case token__LITERAL_BOOLEAN:
      if (!bDebug){
       if (fBOOLEAN(&bBoolean)){ if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, bBoolean); *nReturnExpressionType = pcode__BOOLEAN; _DONE_ }
      }
      break;
    case token__LITERAL_STRING:
      if (!bDebug){
       if (fSTRING(&acString)){ 
  	      int nStringLiteral = findStringLiteral(acString);
   	      if (nStringLiteral == 0){ internalError( utility::con(acString, " string literal not declared") ); _ERROR_ }
  	      if (bProducePcode) pp->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);
  	      *nReturnExpressionType = pcode__QSTRING;
  	      _DONE_
       }
       }
       break;
    case token__LITERAL_BYTE:
      if (!bDebug){
       if (fBYTE(&ucByte)){ if (bProducePcode) pp->wr_PUSH_BYTE(pcode__PUSH_BYTE, ucByte); *nReturnExpressionType = pcode__BYTE; _DONE_ }
       }
       break;
    case token__LITERAL_INTEGER:
      if (!bDebug){
       if (fINTEGER(&nInteger)){ if (bProducePcode) pp->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nInteger); *nReturnExpressionType = pcode__INTEGER; _DONE_ }
       }
       break;
    case token__LITERAL_LONG:
      if (!bDebug){
       if (fLONG(&lLongInteger)){ if (bProducePcode) pp->wr_PUSH_LONG(pcode__PUSH_LONG, lLongInteger); *nReturnExpressionType = pcode__LONG; _DONE_ }
       }
       break;
    case token__LITERAL_SINGLE:
      if (!bDebug){
       if (fSINGLE(&fNumeric)){ if (bProducePcode) pp->wr_PUSH_SINGLE(pcode__PUSH_SINGLE, fNumeric); *nReturnExpressionType = pcode__SINGLE; _DONE_ }
       }
       break;
    case token__LITERAL_DOUBLE:
      if (!bDebug){
       if (fDOUBLE(&dNumeric)){ if (bProducePcode) pp->wr_PUSH_DOUBLE(pcode__PUSH_DOUBLE, dNumeric); *nReturnExpressionType = pcode__DOUBLE; _DONE_ }
       }
       break;
    case token__LITERAL_CURRENCY:
      if (!bDebug){
       if (fCURRENCY(&myCurrency)){ if (bProducePcode) pp->wr_PUSH_CURRENCY(pcode__PUSH_CURRENCY, myCurrency); *nReturnExpressionType = pcode__CURRENCY; _DONE_ }
       }
       break;
    case token__LITERAL_DATE:
      if (!bDebug){
       if (fDATE(&myDate)){ if (bProducePcode) pp->wr_PUSH_DATE(pcode__PUSH_DATE, myDate); *nReturnExpressionType = pcode__DATE; _DONE_ }
       }
       break;
    case token__LITERAL_TIME:
      if (!bDebug){
       if (fTIME(&myDate)){ if (bProducePcode) pp->wr_PUSH_DATE(pcode__PUSH_DATE, myDate); *nReturnExpressionType = pcode__DATE; _DONE_ }
       }
       break;
    case token__NULL:
      if (!bDebug){
       if (fNULL()){ if (bProducePcode) pp->wr_PUSH_NULL(pcode__PUSH_NULL); *nReturnExpressionType = pcode__OBJECT; _DONE_ }
       }
       break;
    case token__NOTHING:
      if (!bDebug){
       if (parseTerm(token__NOTHING)){ if (bProducePcode) pp->wr_PUSH_NULL(pcode__PUSH_NULL); *nReturnExpressionType = pcode__OBJECT; _DONE_ }
       }
       break;
    case token__EMPTY:
      if (!bDebug){
       if (parseTerm(token__EMPTY)){ if (bProducePcode) pp->wr_PUSH_EMPTY(pcode__PUSH_EMPTY); *nReturnExpressionType = pcode__VARIANT; _DONE_ }
       }
       break;
    case token__ERROR:
      if (!bDebug){
       if (parseTerm(token__ERROR)){ if (bProducePcode) pp->wr_PUSH_ERROR(pcode__PUSH_ERROR); *nReturnExpressionType = pcode__VARIANT; _DONE_ }
       }
       break;
    case token__ISLINUX: // there is a copy in parser_kbasic.cpp
       if (parseTerm(token__ISLINUX)){
         #ifdef LINUX // HIDE
  					if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode // HIDE
         #else // HIDE
  					if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode // HIDE
         #endif // HIDE
         // UNHIDE if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode

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
  					if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode // HIDE
         #else
  					if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode // HIDE
         #endif // HIDE
				 // UNHIDE if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode

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
  					if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode // HIDE
         #else // HIDE
  					if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode // HIDE
         #endif // HIDE
         // UNHIDE if (bProducePcode) pp->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false); // write pcode

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
           _END2_
           break; // might be the call of class File
         }

				 if (bProducePcode) pp->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, getCurrentLine()); // write pcode
	      
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
           _END2_
           break; // might be the call of class File
         }

         const char *ac = "";

         ac = getCurrentFile();
					
				 int nStringLiteral = registerStringLiteral(ac);
				 if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
				 if (bProducePcode) pp->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
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
				 if (bProducePcode) pp->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
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
				 if (bProducePcode) pp->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
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
				 if (bProducePcode) pp->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
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
				 if (bProducePcode) pp->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);			
					
         if (parseTerm(token__SYM_BR_OP)){
 	        if (parseTerm(token__SYM_BR_CL)){ syntaxError(token__FUNCTION, ") missing"); _ERROR_ }
        }

				 *nReturnExpressionType = pcode__QSTRING;					

         _DONE_
       }
       break;
    case token__KEY:
      //if (!bDebug)
      {
       if (!bDebug && parseTerm(token__KEY)){
         if (parseTerm(token__SYM_DOT)){
           nInteger = 0;
           const char *acLiteral = "";
           if (fINTEGER(&nInteger)){
             switch(nInteger){
              case 0: nInteger = 0x30;
              case 1: nInteger = 0x31;
              case 2: nInteger = 0x32;
              case 3: nInteger = 0x33;
              case 4: nInteger = 0x34;
              case 5: nInteger = 0x35;
              case 6: nInteger = 0x36;
              case 7: nInteger = 0x37;
              case 8: nInteger = 0x38;
              case 9: nInteger = 0x39;
             }
           } else if (fID_KEYWORD_OR_BUILTIN(&acLiteral, true)){

             if (utility::my_stricmp("Escape", acLiteral) == 0) nInteger = 0x01000000;
             else if (utility::my_stricmp("Tab", acLiteral) == 0) nInteger = 0x01000001;
             else if (utility::my_stricmp("Backtab", acLiteral) == 0) nInteger = 0x01000002;
             else if (utility::my_stricmp("Return", acLiteral) == 0) nInteger = 0x01000004;
             else if (utility::my_stricmp("Enter", acLiteral) == 0) nInteger = 0x01000005;
             else if (utility::my_stricmp("Insert", acLiteral) == 0) nInteger = 0x01000006;
             else if (utility::my_stricmp("Delete", acLiteral) == 0) nInteger = 0x01000007;
             else if (utility::my_stricmp("Pause", acLiteral) == 0) nInteger = 0x01000008;
             else if (utility::my_stricmp("Print", acLiteral) == 0) nInteger = 0x01000009;
             else if (utility::my_stricmp("SysReq", acLiteral) == 0) nInteger = 0x0100000a;
             else if (utility::my_stricmp("Clear", acLiteral) == 0) nInteger = 0x0100000b;
             else if (utility::my_stricmp("Home", acLiteral) == 0) nInteger = 0x01000010;
             else if (utility::my_stricmp("End", acLiteral) == 0) nInteger = 0x01000011;
             else if (utility::my_stricmp("Left", acLiteral) == 0) nInteger = 0x01000012;
             else if (utility::my_stricmp("Up", acLiteral) == 0) nInteger = 0x01000013;
             else if (utility::my_stricmp("Right", acLiteral) == 0) nInteger = 0x01000014;
             else if (utility::my_stricmp("Down", acLiteral) == 0) nInteger = 0x01000015;
             else if (utility::my_stricmp("PageUp", acLiteral) == 0) nInteger = 0x01000016;
             else if (utility::my_stricmp("PageDown", acLiteral) == 0) nInteger = 0x01000017;
             else if (utility::my_stricmp("Shift", acLiteral) == 0) nInteger = 0x01000020;
             else if (utility::my_stricmp("Control", acLiteral) == 0) nInteger = 0x01000021;
             else if (utility::my_stricmp("Meta", acLiteral) == 0) nInteger = 0x01000022;
             else if (utility::my_stricmp("Alt", acLiteral) == 0) nInteger = 0x01000023;
             else if (utility::my_stricmp("AltGr", acLiteral) == 0) nInteger = 0x01001103;
             else if (utility::my_stricmp("CapsLock", acLiteral) == 0) nInteger = 0x01000024;
             else if (utility::my_stricmp("NumLock", acLiteral) == 0) nInteger = 0x01000025;
             else if (utility::my_stricmp("ScrollLock", acLiteral) == 0) nInteger = 0x01000026;
             else if (utility::my_stricmp("F1", acLiteral) == 0) nInteger = 0x01000030;
             else if (utility::my_stricmp("F2", acLiteral) == 0) nInteger = 0x01000031;
             else if (utility::my_stricmp("F3", acLiteral) == 0) nInteger = 0x01000032;
             else if (utility::my_stricmp("F4", acLiteral) == 0) nInteger = 0x01000033;
             else if (utility::my_stricmp("F5", acLiteral) == 0) nInteger = 0x01000034;
             else if (utility::my_stricmp("F6", acLiteral) == 0) nInteger = 0x01000035;
             else if (utility::my_stricmp("F7", acLiteral) == 0) nInteger = 0x01000036;
             else if (utility::my_stricmp("F8", acLiteral) == 0) nInteger = 0x01000037;
             else if (utility::my_stricmp("F9", acLiteral) == 0) nInteger = 0x01000038;
             else if (utility::my_stricmp("F10", acLiteral) == 0) nInteger = 0x01000039;
             else if (utility::my_stricmp("F11", acLiteral) == 0) nInteger = 0x0100003a;
             else if (utility::my_stricmp("F12", acLiteral) == 0) nInteger = 0x0100003b;
             else if (utility::my_stricmp("F13", acLiteral) == 0) nInteger = 0x0100003c;
             else if (utility::my_stricmp("F14", acLiteral) == 0) nInteger = 0x0100003d;
             else if (utility::my_stricmp("F15", acLiteral) == 0) nInteger = 0x0100003e;
             else if (utility::my_stricmp("F16", acLiteral) == 0) nInteger = 0x0100003f;
             else if (utility::my_stricmp("F17", acLiteral) == 0) nInteger = 0x01000040;
             else if (utility::my_stricmp("F18", acLiteral) == 0) nInteger = 0x01000041;
             else if (utility::my_stricmp("F19", acLiteral) == 0) nInteger = 0x01000042;
             else if (utility::my_stricmp("F20", acLiteral) == 0) nInteger = 0x01000043;
             else if (utility::my_stricmp("F21", acLiteral) == 0) nInteger = 0x01000044;
             else if (utility::my_stricmp("F22", acLiteral) == 0) nInteger = 0x01000045;
             else if (utility::my_stricmp("F23", acLiteral) == 0) nInteger = 0x01000046;
             else if (utility::my_stricmp("F24", acLiteral) == 0) nInteger = 0x01000047;
             else if (utility::my_stricmp("F25", acLiteral) == 0) nInteger = 0x01000048;
             else if (utility::my_stricmp("F26", acLiteral) == 0) nInteger = 0x01000049;
             else if (utility::my_stricmp("F27", acLiteral) == 0) nInteger = 0x0100004a;
             else if (utility::my_stricmp("F28", acLiteral) == 0) nInteger = 0x0100004b;
             else if (utility::my_stricmp("F29", acLiteral) == 0) nInteger = 0x0100004c;
             else if (utility::my_stricmp("F30", acLiteral) == 0) nInteger = 0x0100004d;
             else if (utility::my_stricmp("F31", acLiteral) == 0) nInteger = 0x0100004e;
             else if (utility::my_stricmp("F32", acLiteral) == 0) nInteger = 0x0100004f;
             else if (utility::my_stricmp("F33", acLiteral) == 0) nInteger = 0x01000050;
             else if (utility::my_stricmp("F34", acLiteral) == 0) nInteger = 0x01000051;
             else if (utility::my_stricmp("F35", acLiteral) == 0) nInteger = 0x01000052;
             else if (utility::my_stricmp("Super_L", acLiteral) == 0) nInteger = 0x01000053;
             else if (utility::my_stricmp("Super_R", acLiteral) == 0) nInteger = 0x01000054;
             else if (utility::my_stricmp("Menu", acLiteral) == 0) nInteger = 0x01000055;
             else if (utility::my_stricmp("Hyper_L", acLiteral) == 0) nInteger = 0x01000056;
             else if (utility::my_stricmp("Hyper_R", acLiteral) == 0) nInteger = 0x01000057;
             else if (utility::my_stricmp("Help", acLiteral) == 0) nInteger = 0x01000058;
             else if (utility::my_stricmp("Direction_L", acLiteral) == 0) nInteger = 0x01000059;
             else if (utility::my_stricmp("Direction_R", acLiteral) == 0) nInteger = 0x01000060;
             else if (utility::my_stricmp("Space", acLiteral) == 0) nInteger = 0x20;
             else if (utility::my_stricmp("Exclam", acLiteral) == 0) nInteger = 0x21;
             else if (utility::my_stricmp("QuoteDbl", acLiteral) == 0) nInteger = 0x22;
             else if (utility::my_stricmp("NumberSign", acLiteral) == 0) nInteger = 0x23;
             else if (utility::my_stricmp("Dollar", acLiteral) == 0) nInteger = 0x24;
             else if (utility::my_stricmp("Percent", acLiteral) == 0) nInteger = 0x25;
             else if (utility::my_stricmp("Ampersand", acLiteral) == 0) nInteger = 0x26;
             else if (utility::my_stricmp("Apostrophe", acLiteral) == 0) nInteger = 0x27;
             else if (utility::my_stricmp("ParenLeft", acLiteral) == 0) nInteger = 0x28;
             else if (utility::my_stricmp("ParenRight", acLiteral) == 0) nInteger = 0x29;
             else if (utility::my_stricmp("Asterisk", acLiteral) == 0) nInteger = 0x2a;
             else if (utility::my_stricmp("Plus", acLiteral) == 0) nInteger = 0x2b;
             else if (utility::my_stricmp("Comma", acLiteral) == 0) nInteger = 0x2c;
             else if (utility::my_stricmp("Minus", acLiteral) == 0) nInteger = 0x2d;
             else if (utility::my_stricmp("Period", acLiteral) == 0) nInteger = 0x2e;
             else if (utility::my_stricmp("Slash", acLiteral) == 0) nInteger = 0x2f;
             else if (utility::my_stricmp("Colon", acLiteral) == 0) nInteger = 0x3a;
             else if (utility::my_stricmp("Semicolon", acLiteral) == 0) nInteger = 0x3b;
             else if (utility::my_stricmp("Less", acLiteral) == 0) nInteger = 0x3c;
             else if (utility::my_stricmp("Equal", acLiteral) == 0) nInteger = 0x3d;
             else if (utility::my_stricmp("Greater", acLiteral) == 0) nInteger = 0x3e;
             else if (utility::my_stricmp("Question", acLiteral) == 0) nInteger = 0x3f;
             else if (utility::my_stricmp("At", acLiteral) == 0) nInteger = 0x40;
             
             if (utility::my_stricmp("A", acLiteral) == 0) nInteger = 0x41;
             else if (utility::my_stricmp("B", acLiteral) == 0) nInteger = 0x42;
             else if (utility::my_stricmp("C", acLiteral) == 0) nInteger = 0x43;
             else if (utility::my_stricmp("D", acLiteral) == 0) nInteger = 0x44;
             else if (utility::my_stricmp("E", acLiteral) == 0) nInteger = 0x45;
             else if (utility::my_stricmp("F", acLiteral) == 0) nInteger = 0x46;
             else if (utility::my_stricmp("G", acLiteral) == 0) nInteger = 0x47;
             else if (utility::my_stricmp("H", acLiteral) == 0) nInteger = 0x48;
             else if (utility::my_stricmp("I", acLiteral) == 0) nInteger = 0x49;
             else if (utility::my_stricmp("J", acLiteral) == 0) nInteger = 0x4a;
             else if (utility::my_stricmp("K", acLiteral) == 0) nInteger = 0x4b;
             else if (utility::my_stricmp("L", acLiteral) == 0) nInteger = 0x4c;
             else if (utility::my_stricmp("M", acLiteral) == 0) nInteger = 0x4d;
             else if (utility::my_stricmp("N", acLiteral) == 0) nInteger = 0x4e;
             else if (utility::my_stricmp("O", acLiteral) == 0) nInteger = 0x4f;
             else if (utility::my_stricmp("P", acLiteral) == 0) nInteger = 0x50;
             else if (utility::my_stricmp("Q", acLiteral) == 0) nInteger = 0x51;
             else if (utility::my_stricmp("R", acLiteral) == 0) nInteger = 0x52;
             else if (utility::my_stricmp("S", acLiteral) == 0) nInteger = 0x53;
             else if (utility::my_stricmp("T", acLiteral) == 0) nInteger = 0x54;
             else if (utility::my_stricmp("U", acLiteral) == 0) nInteger = 0x55;
             else if (utility::my_stricmp("V", acLiteral) == 0) nInteger = 0x56;
             else if (utility::my_stricmp("W", acLiteral) == 0) nInteger = 0x57;
             else if (utility::my_stricmp("X", acLiteral) == 0) nInteger = 0x58;
             else if (utility::my_stricmp("Y", acLiteral) == 0) nInteger = 0x59;
             else if (utility::my_stricmp("Z", acLiteral) == 0) nInteger = 0x5a;
             else if (utility::my_stricmp("BracketLeft", acLiteral) == 0) nInteger = 0x5b;
             else if (utility::my_stricmp("Backslash", acLiteral) == 0) nInteger = 0x5c;
             else if (utility::my_stricmp("BracketRight", acLiteral) == 0) nInteger = 0x5d;
             else if (utility::my_stricmp("AsciiCircum", acLiteral) == 0) nInteger = 0x5e;
             else if (utility::my_stricmp("Underscore", acLiteral) == 0) nInteger = 0x5f;
             else if (utility::my_stricmp("QuoteLeft", acLiteral) == 0) nInteger = 0x60;
             else if (utility::my_stricmp("BraceLeft", acLiteral) == 0) nInteger = 0x7b;
             else if (utility::my_stricmp("Bar", acLiteral) == 0) nInteger = 0x7c;
             else if (utility::my_stricmp("BraceRight", acLiteral) == 0) nInteger = 0x7d;
             else if (utility::my_stricmp("AsciiTilde", acLiteral) == 0) nInteger = 0x7e;
             else if (utility::my_stricmp("nobreakspace", acLiteral) == 0) nInteger = 0x0a0;
             else if (utility::my_stricmp("exclamdown", acLiteral) == 0) nInteger = 0x0a1;
             else if (utility::my_stricmp("cent", acLiteral) == 0) nInteger = 0x0a2;
             else if (utility::my_stricmp("sterling", acLiteral) == 0) nInteger = 0x0a3;
             else if (utility::my_stricmp("currency", acLiteral) == 0) nInteger = 0x0a4;
             else if (utility::my_stricmp("yen", acLiteral) == 0) nInteger = 0x0a5;
             else if (utility::my_stricmp("brokenbar", acLiteral) == 0) nInteger = 0x0a6;
             else if (utility::my_stricmp("section", acLiteral) == 0) nInteger = 0x0a7;
             else if (utility::my_stricmp("diaeresis", acLiteral) == 0) nInteger = 0x0a8;
             else if (utility::my_stricmp("copyright", acLiteral) == 0) nInteger = 0x0a9;
             else if (utility::my_stricmp("ordfeminine", acLiteral) == 0) nInteger = 0x0aa;
             else if (utility::my_stricmp("guillemotleft", acLiteral) == 0) nInteger = 0x0ab;
             else if (utility::my_stricmp("notsign", acLiteral) == 0) nInteger = 0x0ac;
             else if (utility::my_stricmp("hyphen", acLiteral) == 0) nInteger = 0x0ad;
             else if (utility::my_stricmp("registered", acLiteral) == 0) nInteger = 0x0ae;
             else if (utility::my_stricmp("macron", acLiteral) == 0) nInteger = 0x0af;
             else if (utility::my_stricmp("degree", acLiteral) == 0) nInteger = 0x0b0;
             else if (utility::my_stricmp("plusminus", acLiteral) == 0) nInteger = 0x0b1;
             else if (utility::my_stricmp("twosuperior", acLiteral) == 0) nInteger = 0x0b2;
             else if (utility::my_stricmp("threesuperior", acLiteral) == 0) nInteger = 0x0b3;
             else if (utility::my_stricmp("acute", acLiteral) == 0) nInteger = 0x0b4;
             else if (utility::my_stricmp("mu", acLiteral) == 0) nInteger = 0x0b5;
             else if (utility::my_stricmp("paragraph", acLiteral) == 0) nInteger = 0x0b6;
             else if (utility::my_stricmp("periodcentered", acLiteral) == 0) nInteger = 0x0b7;
             else if (utility::my_stricmp("cedilla", acLiteral) == 0) nInteger = 0x0b8;
             else if (utility::my_stricmp("onesuperior", acLiteral) == 0) nInteger = 0x0b9;
             else if (utility::my_stricmp("masculine", acLiteral) == 0) nInteger = 0x0ba;
             else if (utility::my_stricmp("guillemotright", acLiteral) == 0) nInteger = 0x0bb;
             else if (utility::my_stricmp("onequarter", acLiteral) == 0) nInteger = 0x0bc;
             else if (utility::my_stricmp("onehalf", acLiteral) == 0) nInteger = 0x0bd;
             else if (utility::my_stricmp("threequarters", acLiteral) == 0) nInteger = 0x0be;
             else if (utility::my_stricmp("questiondown", acLiteral) == 0) nInteger = 0x0bf;
             else if (utility::my_stricmp("Agrave", acLiteral) == 0) nInteger = 0x0c0;
             else if (utility::my_stricmp("Aacute", acLiteral) == 0) nInteger = 0x0c1;
             else if (utility::my_stricmp("Acircumflex", acLiteral) == 0) nInteger = 0x0c2;
             else if (utility::my_stricmp("Atilde", acLiteral) == 0) nInteger = 0x0c3;
             else if (utility::my_stricmp("Adiaeresis", acLiteral) == 0) nInteger = 0x0c4;
             else if (utility::my_stricmp("Aring", acLiteral) == 0) nInteger = 0x0c5;
             else if (utility::my_stricmp("AE", acLiteral) == 0) nInteger = 0x0c6;
             else if (utility::my_stricmp("Ccedilla", acLiteral) == 0) nInteger = 0x0c7;
             else if (utility::my_stricmp("Egrave", acLiteral) == 0) nInteger = 0x0c8;
             else if (utility::my_stricmp("Eacute", acLiteral) == 0) nInteger = 0x0c9;
             else if (utility::my_stricmp("Ecircumflex", acLiteral) == 0) nInteger = 0x0ca;
             else if (utility::my_stricmp("Ediaeresis", acLiteral) == 0) nInteger = 0x0cb;
             else if (utility::my_stricmp("Igrave", acLiteral) == 0) nInteger = 0x0cc;
             else if (utility::my_stricmp("Iacute", acLiteral) == 0) nInteger = 0x0cd;
             else if (utility::my_stricmp("Icircumflex", acLiteral) == 0) nInteger = 0x0ce;
             else if (utility::my_stricmp("Idiaeresis", acLiteral) == 0) nInteger = 0x0cf;
             else if (utility::my_stricmp("ETH", acLiteral) == 0) nInteger = 0x0d0;
             else if (utility::my_stricmp("Ntilde", acLiteral) == 0) nInteger = 0x0d1;
             else if (utility::my_stricmp("Ograve", acLiteral) == 0) nInteger = 0x0d2;
             else if (utility::my_stricmp("Oacute", acLiteral) == 0) nInteger = 0x0d3;
             else if (utility::my_stricmp("Ocircumflex", acLiteral) == 0) nInteger = 0x0d4;
             else if (utility::my_stricmp("Otilde", acLiteral) == 0) nInteger = 0x0d5;
             else if (utility::my_stricmp("Odiaeresis", acLiteral) == 0) nInteger = 0x0d6;
             else if (utility::my_stricmp("multiply", acLiteral) == 0) nInteger = 0x0d7;
             else if (utility::my_stricmp("Ooblique", acLiteral) == 0) nInteger = 0x0d8;
             else if (utility::my_stricmp("Ugrave", acLiteral) == 0) nInteger = 0x0d9;
             else if (utility::my_stricmp("Uacute", acLiteral) == 0) nInteger = 0x0da;
             else if (utility::my_stricmp("Ucircumflex", acLiteral) == 0) nInteger = 0x0db;
             else if (utility::my_stricmp("Udiaeresis", acLiteral) == 0) nInteger = 0x0dc;
             else if (utility::my_stricmp("Yacute", acLiteral) == 0) nInteger = 0x0dd;
             else if (utility::my_stricmp("THORN", acLiteral) == 0) nInteger = 0x0de;
             else if (utility::my_stricmp("ssharp", acLiteral) == 0) nInteger = 0x0df;
             else if (utility::my_stricmp("division", acLiteral) == 0) nInteger = 0x0f7;
             else if (utility::my_stricmp("ydiaeresis", acLiteral) == 0) nInteger = 0x0ff;
             else if (utility::my_stricmp("Multi_key", acLiteral) == 0) nInteger = 0x01001120;
             else if (utility::my_stricmp("Codeinput", acLiteral) == 0) nInteger = 0x01001137;
             else if (utility::my_stricmp("SingleCandidate", acLiteral) == 0) nInteger = 0x0100113c;
             else if (utility::my_stricmp("MultipleCandidate", acLiteral) == 0) nInteger = 0x0100113d;
             else if (utility::my_stricmp("PreviousCandidate", acLiteral) == 0) nInteger = 0x0100113e;
             else if (utility::my_stricmp("Mode_switch", acLiteral) == 0) nInteger = 0x0100117e;
             else if (utility::my_stricmp("Kanji", acLiteral) == 0) nInteger = 0x01001121;
             else if (utility::my_stricmp("Muhenkan", acLiteral) == 0) nInteger = 0x01001122;
             else if (utility::my_stricmp("Henkan", acLiteral) == 0) nInteger = 0x01001123;
             else if (utility::my_stricmp("Romaji", acLiteral) == 0) nInteger = 0x01001124;
             else if (utility::my_stricmp("Hiragana", acLiteral) == 0) nInteger = 0x01001125;
             else if (utility::my_stricmp("Katakana", acLiteral) == 0) nInteger = 0x01001126;
             else if (utility::my_stricmp("Hiragana_Katakana", acLiteral) == 0) nInteger = 0x01001127;
             else if (utility::my_stricmp("Zenkaku", acLiteral) == 0) nInteger = 0x01001128;
             
             if (utility::my_stricmp("Hankaku", acLiteral) == 0) nInteger = 0x01001129;
             else if (utility::my_stricmp("Zenkaku_Hankaku", acLiteral) == 0) nInteger = 0x0100112a;
             else if (utility::my_stricmp("Touroku", acLiteral) == 0) nInteger = 0x0100112b;
             else if (utility::my_stricmp("Massyo", acLiteral) == 0) nInteger = 0x0100112c;
             else if (utility::my_stricmp("Kana_Lock", acLiteral) == 0) nInteger = 0x0100112d;
             else if (utility::my_stricmp("Kana_Shift", acLiteral) == 0) nInteger = 0x0100112e;
             else if (utility::my_stricmp("Eisu_Shift", acLiteral) == 0) nInteger = 0x0100112f;
             else if (utility::my_stricmp("Eisu_toggle", acLiteral) == 0) nInteger = 0x01001130;
             else if (utility::my_stricmp("Hangul", acLiteral) == 0) nInteger = 0x01001131;
             else if (utility::my_stricmp("Hangul_Start", acLiteral) == 0) nInteger = 0x01001132;
             else if (utility::my_stricmp("Hangul_End", acLiteral) == 0) nInteger = 0x01001133;
             else if (utility::my_stricmp("Hangul_Hanja", acLiteral) == 0) nInteger = 0x01001134;
             else if (utility::my_stricmp("Hangul_Jamo", acLiteral) == 0) nInteger = 0x01001135;
             else if (utility::my_stricmp("Hangul_Romaja", acLiteral) == 0) nInteger = 0x01001136;
             else if (utility::my_stricmp("Hangul_Jeonja", acLiteral) == 0) nInteger = 0x01001138;
             else if (utility::my_stricmp("Hangul_Banja", acLiteral) == 0) nInteger = 0x01001139;
             else if (utility::my_stricmp("Hangul_PreHanja", acLiteral) == 0) nInteger = 0x0100113a;
             else if (utility::my_stricmp("Hangul_PostHanja", acLiteral) == 0) nInteger = 0x0100113b;
             else if (utility::my_stricmp("Hangul_Special", acLiteral) == 0) nInteger = 0x0100113f;
             else if (utility::my_stricmp("Dead_Grave", acLiteral) == 0) nInteger = 0x01001250;
             else if (utility::my_stricmp("Dead_Acute", acLiteral) == 0) nInteger = 0x01001251;
             else if (utility::my_stricmp("Dead_Circumflex", acLiteral) == 0) nInteger = 0x01001252;
             else if (utility::my_stricmp("Dead_Tilde", acLiteral) == 0) nInteger = 0x01001253;
             else if (utility::my_stricmp("Dead_Macron", acLiteral) == 0) nInteger = 0x01001254;
             else if (utility::my_stricmp("Dead_Breve", acLiteral) == 0) nInteger = 0x01001255;
             else if (utility::my_stricmp("Dead_Abovedot", acLiteral) == 0) nInteger = 0x01001256;
             else if (utility::my_stricmp("Dead_Diaeresis", acLiteral) == 0) nInteger = 0x01001257;
             else if (utility::my_stricmp("Dead_Abovering", acLiteral) == 0) nInteger = 0x01001258;
             else if (utility::my_stricmp("Dead_Doubleacute", acLiteral) == 0) nInteger = 0x01001259;
             else if (utility::my_stricmp("Dead_Caron", acLiteral) == 0) nInteger = 0x0100125a;
             else if (utility::my_stricmp("Dead_Cedilla", acLiteral) == 0) nInteger = 0x0100125b;
             else if (utility::my_stricmp("Dead_Ogonek", acLiteral) == 0) nInteger = 0x0100125c;
             else if (utility::my_stricmp("Dead_Iota", acLiteral) == 0) nInteger = 0x0100125d;
             else if (utility::my_stricmp("Dead_Voiced_Sound", acLiteral) == 0) nInteger = 0x0100125e;
             else if (utility::my_stricmp("Dead_Semivoiced_Sound", acLiteral) == 0) nInteger = 0x0100125f;
             else if (utility::my_stricmp("Dead_Belowdot", acLiteral) == 0) nInteger = 0x01001260;
             else if (utility::my_stricmp("Dead_Hook", acLiteral) == 0) nInteger = 0x01001261;
             else if (utility::my_stricmp("Dead_Horn", acLiteral) == 0) nInteger = 0x01001262;
             else if (utility::my_stricmp("Back", acLiteral) == 0) nInteger = 0x01000061;
             else if (utility::my_stricmp("Forward", acLiteral) == 0) nInteger = 0x01000062;
             else if (utility::my_stricmp("Stop", acLiteral) == 0) nInteger = 0x01000063;
             else if (utility::my_stricmp("Refresh", acLiteral) == 0) nInteger = 0x01000064;
             else if (utility::my_stricmp("VolumeDown", acLiteral) == 0) nInteger = 0x01000070;
             else if (utility::my_stricmp("VolumeMute", acLiteral) == 0) nInteger = 0x01000071;
             else if (utility::my_stricmp("VolumeUp", acLiteral) == 0) nInteger = 0x01000072;
             else if (utility::my_stricmp("BassBoost", acLiteral) == 0) nInteger = 0x01000073;
             else if (utility::my_stricmp("BassUp", acLiteral) == 0) nInteger = 0x01000074;
             else if (utility::my_stricmp("BassDown", acLiteral) == 0) nInteger = 0x01000075;
             else if (utility::my_stricmp("TrebleUp", acLiteral) == 0) nInteger = 0x01000076;
             else if (utility::my_stricmp("TrebleDown", acLiteral) == 0) nInteger = 0x01000077;
             else if (utility::my_stricmp("MediaPlay", acLiteral) == 0) nInteger = 0x01000080;
             else if (utility::my_stricmp("MediaStop", acLiteral) == 0) nInteger = 0x01000081;
             else if (utility::my_stricmp("MediaPrevious", acLiteral) == 0) nInteger = 0x01000082;
             else if (utility::my_stricmp("MediaNext", acLiteral) == 0) nInteger = 0x01000083;
             else if (utility::my_stricmp("MediaRecord", acLiteral) == 0) nInteger = 0x01000084;
             else if (utility::my_stricmp("HomePage", acLiteral) == 0) nInteger = 0x01000090;
             else if (utility::my_stricmp("Favorites", acLiteral) == 0) nInteger = 0x01000091;
             else if (utility::my_stricmp("Search", acLiteral) == 0) nInteger = 0x01000092;
             else if (utility::my_stricmp("Standby", acLiteral) == 0) nInteger = 0x01000093;
             else if (utility::my_stricmp("OpenUrl", acLiteral) == 0) nInteger = 0x01000094;
             else if (utility::my_stricmp("LaunchMail", acLiteral) == 0) nInteger = 0x010000a0;
             else if (utility::my_stricmp("LaunchMedia", acLiteral) == 0) nInteger = 0x010000a1;
             else if (utility::my_stricmp("Launch0", acLiteral) == 0) nInteger = 0x010000a2;
             else if (utility::my_stricmp("Launch1", acLiteral) == 0) nInteger = 0x010000a3;
             else if (utility::my_stricmp("Launch2", acLiteral) == 0) nInteger = 0x010000a4;
             else if (utility::my_stricmp("Launch3", acLiteral) == 0) nInteger = 0x010000a5;
             else if (utility::my_stricmp("Launch4", acLiteral) == 0) nInteger = 0x010000a6;
             else if (utility::my_stricmp("Launch5", acLiteral) == 0) nInteger = 0x010000a7;
             else if (utility::my_stricmp("Launch6", acLiteral) == 0) nInteger = 0x010000a8;
             else if (utility::my_stricmp("Launch7", acLiteral) == 0) nInteger = 0x010000a9;
             else if (utility::my_stricmp("Launch8", acLiteral) == 0) nInteger = 0x010000aa;
             else if (utility::my_stricmp("Launch9", acLiteral) == 0) nInteger = 0x010000ab;
             else if (utility::my_stricmp("LaunchA", acLiteral) == 0) nInteger = 0x010000ac;
             else if (utility::my_stricmp("LaunchB", acLiteral) == 0) nInteger = 0x010000ad;
             else if (utility::my_stricmp("LaunchC", acLiteral) == 0) nInteger = 0x010000ae;
             else if (utility::my_stricmp("LaunchD", acLiteral) == 0) nInteger = 0x010000af;
             else if (utility::my_stricmp("LaunchE", acLiteral) == 0) nInteger = 0x010000b0;
             else if (utility::my_stricmp("LaunchF", acLiteral) == 0) nInteger = 0x010000b1;
             else if (utility::my_stricmp("MediaLast", acLiteral) == 0) nInteger = 0x0100ffff;
             else if (utility::my_stricmp("unknown", acLiteral) == 0) nInteger = 0x01ffffff;
             else if (utility::my_stricmp("Call", acLiteral) == 0) nInteger = 0x01100004;
             else if (utility::my_stricmp("Context1", acLiteral) == 0) nInteger = 0x01100000;
             else if (utility::my_stricmp("Context2", acLiteral) == 0) nInteger = 0x01100001;
             else if (utility::my_stricmp("Context3", acLiteral) == 0) nInteger = 0x01100002;
             else if (utility::my_stricmp("Context4", acLiteral) == 0) nInteger = 0x01100003;
             else if (utility::my_stricmp("Flip", acLiteral) == 0) nInteger = 0x01100006;
             else if (utility::my_stricmp("Hangup", acLiteral) == 0) nInteger = 0x01100005;
             else if (utility::my_stricmp("No", acLiteral) == 0) nInteger = 0x01010002;
             else if (utility::my_stricmp("Select", acLiteral) == 0) nInteger = 0x01010000;
             else if (utility::my_stricmp("Yes", acLiteral) == 0) nInteger = 0x01010001;
             else if (utility::my_stricmp("Execute", acLiteral) == 0) nInteger = 0x01020003;
             else if (utility::my_stricmp("Printer", acLiteral) == 0) nInteger = 0x01020002;
             else if (utility::my_stricmp("Play", acLiteral) == 0) nInteger = 0x01020005;
             else if (utility::my_stricmp("Sleep", acLiteral) == 0) nInteger = 0x01020004;
             else if (utility::my_stricmp("Zoom", acLiteral) == 0) nInteger = 0x01020006;
             else if (utility::my_stricmp("Cancel", acLiteral) == 0) nInteger = 0x01020001;

           }


           if (bProducePcode) pp->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nInteger); *nReturnExpressionType = pcode__INTEGER; _DONE_ 

         }
        }
       }
       break;
  }

  bool bTestedForConst = false;

	if (bConstExpression == false){

	  // literals
    switch(peekToken()){
      case token__LBOUND:
        if (fLBOUND(pp, &nExpressionType, true)){ *nReturnExpressionType = nExpressionType; _DONE_ }
        break;
      case token__UBOUND:
        if (fUBOUND(pp, &nExpressionType, true)){ *nReturnExpressionType = nExpressionType; _DONE_ }
        break;
      case token__TYPEOF:
        if ((fTYPEOF(pp, &nExpressionType, true))){ *nReturnExpressionType = nExpressionType; _DONE_ }
        break;
      case token__ADDRESSOF:
        if ((fADDRESSOF(pp))){ *nReturnExpressionType = pcode__INTEGER; _DONE_ }
        break;
      case token__ERL:
        if (parseTerm(token__ERL)){ if (bProducePcode) pp->wr_ERL(pcode__ERL, true); *nReturnExpressionType = pcode__INTEGER; _DONE_ }
        break;
      case token__ERR:
        if (parseTerm(token__ERR)){ 
          if (!parseTerm(token__SYM_DOT)){
            if (bProducePcode) pp->wr_ERR(pcode__ERR, true); *nReturnExpressionType = pcode__INTEGER; _DONE_ 
          } else {
            _END2_
          }
        }
        break;
    }

#ifdef KBDEBUG
    if (stopAtLine(6)){
      int i = 9;
      i++;
    }
#endif

    static int nId = 0;



    //if (bWithoutBuiltin == false)
    {
      //
	    if (fCLASS_METHOD_CALL(pp, nReturnExpressionType)) _DONE_ 	



	    if (binding_fCLASS_METHOD_CALL(pp, nReturnExpressionType)) _DONE_ 	
	  //  if (binding_fCLASS_ENUM(pp, nReturnExpressionType)) _DONE_ 	      

      if (binding_fPROPERTY(pp, nReturnExpressionType)) _DONE_  //  must be placed before fPROPERTY
      if (binding_fSTATICPROPERTY(pp, nReturnExpressionType, &nId)) _DONE_  //  must be placed before fPROPERTY
      if (fPROPERTY(pp, nReturnExpressionType)) _DONE_  //  must be placed before fME



		  if (fME_METHOD_CALL(pp, nReturnExpressionType, true)) _DONE_ // ME.Method()
		  if (fPARENT_METHOD_CALL(pp, nReturnExpressionType, true)) _DONE_  // PARENT.Method()
		  if (fNEW_METHOD_CALL(pp, nReturnExpressionType, true)) _DONE_ 

		  if (fCLASS_STATICMETHOD_CALL(pp, nReturnExpressionType)) _DONE_ // classname or varname and .Method()
  		
      // binding
      if (binding_fCLASS_CONST(pp, nReturnExpressionType, true)){
        _DONE_
      }

        if (binding_fCLASS_STATICMETHOD_CALL(pp, nReturnExpressionType, true)){
        if (peekToken() == token__SYM_DOT){
           if (binding_fCLASS_METHOD_CALL(pp, nReturnExpressionType, true, false, true));
           //else if (binding_fPROPERTY(pp, nReturnExpressionType)) _DONE_  //  must be placed before fPROPERTY
        }
        _DONE_ 
      }
		  //if (binding_fFUNCTION_CALL(pp, nReturnExpressionType, true)) _DONE_ 
		  //if (binding_fFUNCTION_OPERATOR(pp, nReturnExpressionType)) _DONE_ 
		 // if (binding_fCLASS_ENUM(pp, nReturnExpressionType)) _DONE_    

#ifdef KBDEBUG
      if (stopAtLine(13)){
       int i = 3;
       i++;
      }
#endif
      if (fCONST(pp, nReturnExpressionType)) _DONE_ 	
      bTestedForConst = true;
      if (fVARIABLE(pp, p, nReturnExpressionType, &scope, a)) _DONE_ 	

		  if (fME(pp, nReturnExpressionType, true, bBinding)) _DONE_ // ME
		  if (fPARENT(pp, nReturnExpressionType, true, bBinding)) _DONE_ // PARENT
        
    }

	}

  if (fENUM(pp, nReturnExpressionType)) _DONE_ 	
/*
#ifdef KBDEBUG
    if (stopAtLine(340)){
      int i = 9;
      i++;
    }
#endif
    */

  if (!bTestedForConst && fCONST(pp, nReturnExpressionType)) _DONE_ 	


  if (fMACRO(pp, nReturnExpressionType, true)) _DONE_

  // using of elements of current enum definition as const expression in the current enum definition
  if (bEnum){
		const char *acIdentifier;

		if (fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

      const char *s = getCurrentEnum();
         
      int nEnumId = findEnum(getScope(), s);
      if (nEnumId == 0){ internalError(utility::con(s, " enum not declared")); _ERROR_ }

      int nElement = findEnumElement(nEnumId, acIdentifier);
      if (nElement >= 0){
         
       if (bProducePcode){
        p->wr_PUSH_ENUM(pcode__PUSH_ENUM, nEnumId, nElement);
       }

       *nReturnExpressionType = enumElementType(nEnumId, nElement); 
       _DONE_

      }
    }
    _END_
    //return false;

  }

	if (bConstExpression == false){


		if (fARRAY(pp, nReturnExpressionType, true)){ _DONE_ }
	}

  if (parseTerm(token__SYM_BR_OP)){ // (

#ifdef KBDEBUG
    if (stopAtLine(23)){
      int i = 9;
      i++;
    }
#endif

    bool bEXPRESSION;// = false;
    bool bTerm_SYM_BR_CL = false;

    if (bEXPRESSION = fEXPRESSION(pp, p, nReturnExpressionType, a, bConstExpression, bWithoutBuiltin, bEnum))
    if (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)){}

  	//*nReturnExpressionType = nExpressionType;


	   if (!bEXPRESSION && !bTerm_SYM_BR_CL && fID_KEYWORD_OR_BUILTIN(&acIdentifier)){
       	if ((bExplicit || isKBASIC()) && !bWithoutBuiltin){

        if (scope == outofscope){
    		    { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " is declared, but its scope is PRIVATE or PROTECTED and not PUBLIC") ); _ERROR_ }            
        } else {
          if (isScopeClass()){
      		    { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " not declared. Maybe this variable was declared as INSTANCE CLASS variable and not as STATIC CLASS variable. See help for more details") ); _ERROR_ }
          } else {
      		    { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " not declared. Remember that variable names are case sensitive and that you have to write OPTION OLDBASIC on top of your program for automatic declaration of variables = old style mode. See help for more details") ); _ERROR_ }
          }          
        }

       }
     }
     	if ((bExplicit || isKBASIC()) && !bWithoutBuiltin){

    	        	 if (!bEXPRESSION){ syntaxError(token__KEYWORD, "expression missing"); _ERROR_ }
           else if (!bTerm_SYM_BR_CL){ syntaxError(token__KEYWORD, ") missing"); _ERROR_ }
      }// else if (!bTerm_SYM_BR_CL){ syntaxError(token__KEYWORD, ") missing"); _ERROR_ }
      
  

    // (new Form()).show unbenannte objekterstellung oder (object).method()
    if (memory_type::isObject(*nReturnExpressionType)){

      if (fMETHOD_CALL(p, nReturnExpressionType, true, *nReturnExpressionType, false, true)){ _DONE_ }
    

       // methode

       // property

       // var

       // const

    }

    _DONE_

  } else if (parseTerm(token__OP_NOT) || parseTerm(token__OP_BIT_NOT)){
  	if (!(fFACTOR(pp, p, &nExpressionType, a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))){ 
      _END_ // might be bWithoutBuiltin = true, so there are other possibilities with NOT
    //  syntaxError(token__KEYWORD, "expression missing"); _ERROR_ 
    }

    if (!memory_type::isNumeric(nExpressionType) /*&& !memory_type::isString(nExpressionType)*/ && nExpressionType != pcode__BOOLEAN){ semanticError(token__KEYWORD, "wrong datatype for NOT"); _ERROR_ }

  	*nReturnExpressionType = nExpressionType;

  	if (bProducePcode) pp->wr_NOT(pcode__NOT);

  	_DONE_
/*
  } else if (parseTerm(token__OP_NOT2)){ // !

    if (!(fFACTOR(pp, p, &nExpressionType, a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))){ syntaxError(token__KEYWORD, "expression missing"); _ERROR_ }

      if (fOPERATOR_OVERLOADING(p, nExpressionType, token__OP_NOT2, nReturnExpressionType)){

  	  *nReturnExpressionType = nExpressionType;

  	  _DONE_
    }

  } else if (parseTerm(token__OP_ADD_ADD)){ // ++

    if (!(fFACTOR(pp, p, &nExpressionType, a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))){ syntaxError(token__KEYWORD, "expression missing"); _ERROR_ }

      if (fOPERATOR_OVERLOADING(p, nExpressionType, token__OP_ADD_ADD, nReturnExpressionType)){

  	  *nReturnExpressionType = nExpressionType;

  	  _DONE_
    }

  } else if (parseTerm(token__OP_SUB_SUB)){ // --

    if (!(fFACTOR(pp, p, &nExpressionType, a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))){ syntaxError(token__KEYWORD, "expression missing"); _ERROR_ }

      if (fOPERATOR_OVERLOADING(p, nExpressionType, token__OP_SUB_SUB, nReturnExpressionType)){

  	  *nReturnExpressionType = nExpressionType;

  	  _DONE_
    }
*/
  } else if (parseTerm(token__OP_ADD)){ // unary +

   	if (!(fFACTOR(pp, p, &nExpressionType, a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))){ syntaxError(token__KEYWORD, "expression missing"); _ERROR_ }

    if (!memory_type::isNumeric(nExpressionType)){ semanticError(token__KEYWORD, "wrong datatype, must be numeric"); _ERROR_ }

    *nReturnExpressionType = nExpressionType;

  	if (bProducePcode){
   		pp->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 1);
   		pp->wr_MUL(pcode__MUL);
  	}

   	_DONE_

  } else if (parseTerm(token__OP_SUB)){ // unary -

   	if (!(fFACTOR(pp, p, &nExpressionType, a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))){ syntaxError(token__KEYWORD, "expression missing"); _ERROR_ }

    if (!memory_type::isNumeric(nExpressionType)){ semanticError(token__KEYWORD, "wrong datatype, must be numeric"); _ERROR_ }

    *nReturnExpressionType = nExpressionType;

  	if (bProducePcode){
   		pp->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, -1);
   		pp->wr_MUL(pcode__MUL);
  	}

   	_DONE_
  }


	if (bConstExpression == false){

	   // builtin classes
    if (bWithoutBuiltin == false){ // needed to avoid endless recursive calls of fKBASIC
   
      if (fKBASIC(pp, nReturnExpressionType, true)) _DONE_
  //		  if (fOLDBASIC(pp, nReturnExpressionType, true)) _DONE_ 
	//	  if (fVERYOLDBASIC(pp, nReturnExpressionType, true)) _DONE_ 
    }
  }

	bool bIDENTIFIER;// = false;

		   if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)){}
	// because the identifier has a suffix $,%,&,#,!, AS <TYPE> is not allowed, already found out
	else if (bIDENTIFIER = fID_STRING(&acIdentifier)){}
  else if (bIDENTIFIER = fID_INTEGER(&acIdentifier)){}
	else if (bIDENTIFIER = fID_LONG(&acIdentifier)){}
	else if (bIDENTIFIER = fID_SINGLE(&acIdentifier)){}
	else if (bIDENTIFIER = fID_DOUBLE(&acIdentifier)){}
	else if (bIDENTIFIER = fID_CURRENCY(&acIdentifier)){}

	if(bIDENTIFIER){
  	if ((bExplicit || isKBASIC()) && !bWithoutBuiltin){

    register int i = peekToken();

    if (i > token__MISC){ 

      if (utility::my_stricmp(acIdentifier, "NEW") != 0){
        if (scope == outofscope){
    		    { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " is declared, but its scope is PRIVATE or PROTECTED and not PUBLIC") ); _ERROR_ }
        } else {
          if (isScopeClass()){
      		    { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " not declared. Maybe this variable was declared as INSTANCE CLASS variable and not as STATIC CLASS variable. See help for more details") ); _ERROR_ }
          } else {
      		    { semanticError(token__MSC_IDENTIFIER, utility::con(acIdentifier, " not declared. Remember that variable names are case sensitive and that you have to write OPTION OLDBASIC on top of your program for automatic declaration of variables = old style mode. See help for more details") ); _ERROR_ }
          }
        }
      }

    }

    }
  }

 // return false;
	_END_
}

bool parser::fEXPONENT(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	//_BEGIN_

	//bool bFACTOR = false;

	int nExpressionType[parser__MAX_EXPRESSION];
	*nReturnExpressionType = 0;

	if (/*bFACTOR = */fFACTOR(pp, p, &nExpressionType[0], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){
    int i = 0;
		i++;

	bool bFACTOR2 = false;
	bool bFACTOR3 = false;
	int nOperator = 0;



  if (!bWithoutBuiltin){

		do {

		 	if (i >= parser__MAX_EXPRESSION){ internalError("too many expressions in one line"); _ERROR_ }

			nOperator = 0;

      if (parseTerm(token__OP_POWER)){ 
        nOperator = token__OP_POWER; 
      }
     
			bFACTOR2 = false;
			bFACTOR3 = false;

   		if (nOperator && 
        (
        // (bFACTOR3 = fOPERATOR_OVERLOADING(p, *nReturnExpressionType, nOperator, nReturnExpressionType))
        // ||
         (bFACTOR2 = fFACTOR(pp, p, &nExpressionType[i], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))
        
        ))
      {

        if (!memory_type::compatibleTypeOperator(nExpressionType[i], nExpressionType[i - 1], nOperator)){ semanticError(token__OP_POWER, "operator can not be used with this type"); _ERROR_ }

        i++;

  			if (bFACTOR2 && bProducePcode){

          if (nOperator == token__OP_POWER) pp->wr_POWER(pcode__POWER);
          else { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }

  			}
  		}

		} while (proceedParse() && (bFACTOR2 || bFACTOR3));

  }
		*nReturnExpressionType = nExpressionType[0];
		for(int z = 0; z < i - 1; z++) if (!memory_type::mergeType(*nReturnExpressionType, nExpressionType[z + 1], nReturnExpressionType)){ semanticError(token__OP_POWER, "incompatible types in expression"); _ERROR_ }

  	_DONE_
  }

  return false;
	//_END_
}

bool parser::fTERM(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	//_BEGIN_

	//bool bEXPONENT = false;

	int nExpressionType[parser__MAX_EXPRESSION];
	

	*nReturnExpressionType = 0;

	if (/*bEXPONENT = */fEXPONENT(pp, p, &nExpressionType[0], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){
    int i = 0;
		i++;

	bool bEXPONENT2 = false;
	bool bEXPONENT3 = false;
	int nOperator = 0;

  if (!bWithoutBuiltin){

		do {

		 	if (i >= parser__MAX_EXPRESSION){ internalError("too many expressions in one line"); _ERROR_ }

			nOperator = 0;

      /*

  case token__OP_BIT_AND: 					return "BITAND";
  case token__OP_BIT_OR: 					return "BITOR";
  case token__OP_BIT_XOR: 					return "BITXOR";
  case token__OP_BIT_NOT: 					return "BITNOT";

      */


    switch(peekToken()){
      case token__OP_DIV:
         parseTerm(token__OP_DIV);
         nOperator = token__OP_DIV; 
         break;
      case token__OP_IDIV:
         parseTerm(token__OP_IDIV);
         nOperator = token__OP_IDIV; 
         break;
      case token__OP_MUL:
         parseTerm(token__OP_MUL);
         nOperator = token__OP_MUL; 
         break;
      case token__OP_MOD:
         parseTerm(token__OP_MOD);
         nOperator = token__OP_MOD; 
         break;
    }
/*
          if (parseTerm(token__OP_DIV)){ nOperator = token__OP_DIV; }
  		else if (parseTerm(token__OP_IDIV)){ nOperator = token__OP_IDIV; }
  		else if (parseTerm(token__OP_MUL)){	nOperator = token__OP_MUL; }
  		else if (parseTerm(token__OP_MOD)){	nOperator = token__OP_MOD; }
*/
			bEXPONENT2 = false;
			bEXPONENT3 = false;

   		if (nOperator && 
        (
        // (bEXPONENT3 = fOPERATOR_OVERLOADING(p, *nReturnExpressionType, nOperator, nReturnExpressionType))
       //  ||
         (bEXPONENT2 = fEXPONENT(pp, p, &nExpressionType[i], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))
        
        ))
      {

        if (!memory_type::compatibleTypeOperator(nExpressionType[i], nExpressionType[i - 1], nOperator)){ semanticError(token__KEYWORD, "operator can not be used with this type"); _ERROR_ }
 
        i++;

  			if (bEXPONENT2 && bProducePcode){

          switch(nOperator){
            case token__OP_DIV:
              pp->wr_DIV(pcode__DIV);
              break;
            case token__OP_IDIV:
              pp->wr_IDIV(pcode__IDIV);
              break;
            case token__OP_MUL:
              pp->wr_MUL(pcode__MUL);
              break;
            case token__OP_MOD:
              pp->wr_MOD(pcode__MOD);
              break;
            default:
              { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }
              break;
          }
/*
      				 if (nOperator == token__OP_DIV) pp->wr_DIV(pcode__DIV);
      		else if (nOperator == token__OP_IDIV) pp->wr_IDIV(pcode__IDIV);
      		else if (nOperator == token__OP_MUL) pp->wr_MUL(pcode__MUL);
      		else if (nOperator == token__OP_MOD) pp->wr_MOD(pcode__MOD);
         else { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }
*/
  			}
  		}

		} while (proceedParse() && (bEXPONENT2 || bEXPONENT3));
  }
		*nReturnExpressionType = nExpressionType[0];
		for(int z = 0; z < i - 1; z++) if (!memory_type::mergeType(*nReturnExpressionType, nExpressionType[z + 1], nReturnExpressionType)){ semanticError(token__KEYWORD, "incompatible types in expression"); _ERROR_ }

  	_DONE_
  }

	return false;
}

bool parser::fSIMPLEEXPRESSION(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	//_BEGIN_

	//bool bTERM = false;

	int nExpressionType[parser__MAX_EXPRESSION];
	

	*nReturnExpressionType = 0;

	if (/*bTERM = */fTERM(pp, p, &nExpressionType[0], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){
    int i = 0;
		i++;

	bool bTERM2 = false;
	bool bTERM3 = false;
	int nOperator = 0;
	int nOperator2 = 0;

  if (!bWithoutBuiltin){

		do {

		 	if (i >= parser__MAX_EXPRESSION){ internalError("too many expressions in one line"); _ERROR_ }

			nOperator = 0;
			nOperator2 = 0;


      switch(peekToken()){
        case token__OP_ADD:
          parseTerm(token__OP_ADD);
          nOperator = token__OP_ADD; nOperator2 = token__OP_ADD;
          break;
        case token__OP_STR_CAT:
          parseTerm(token__OP_STR_CAT);
          nOperator = token__OP_ADD; nOperator2 = 0; /* nOperator2 = 0; & darf hier nicht greifen */
          break;
        case token__OP_SUB:
          parseTerm(token__OP_SUB);
          nOperator = token__OP_SUB; nOperator2 = token__OP_SUB;
          break;
      }
    
          // if (parseTerm(token__OP_ADD)){ nOperator = token__OP_ADD; nOperator2 = token__OP_ADD; }
      //else if (parseTerm(token__OP_STR_CAT)){ nOperator = token__OP_ADD; nOperator2 = 0; /* nOperator2 = 0; & darf hier nicht greifen */} 
      // [VB] If an expression is not a string, it is converted to a String variant
  		//else if (parseTerm(token__OP_SUB)){ nOperator = token__OP_SUB; nOperator2 = token__OP_SUB; }

  		bTERM2 = false;
  		bTERM3 = false;

#ifdef KBDEBUG
  if (stopAtLine(18)){
    int i = 9;
    i++;
  }
#endif
/*
  if (nOperator == token__OP_ADD){
    nOperator = token__OP_ADD;
  }*/

   		if (nOperator && 
        (
       //  (bTERM3 = fOPERATOR_OVERLOADING(p, nExpressionType[i - 1], nOperator2, nReturnExpressionType))
       //  || 
         (bTERM2 = fTERM(pp, p, &nExpressionType[i], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))
        
        ))
      {

        if (!bTERM3 && !memory_type::compatibleTypeOperator(nExpressionType[i], nExpressionType[i - 1], nOperator)){ semanticError(token__KEYWORD, "operator can not be used with this type"); _ERROR_ }

        i++;

  			if (bTERM2 && bProducePcode){

          switch(nOperator){
            case token__OP_ADD:
              pp->wr_ADD(pcode__ADD);
              break;
            case token__OP_SUB:
              pp->wr_SUB(pcode__SUB);
              break;
            default:
              { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }
              break;
          }
/*
      				 if (nOperator == token__OP_ADD) pp->wr_ADD(pcode__ADD);
      		else if (nOperator == token__OP_SUB) pp->wr_SUB(pcode__SUB);
         else { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }
*/
  			}
  		}

		} while (proceedParse() && (bTERM2 || bTERM3));
  }
		*nReturnExpressionType = nExpressionType[0];
		for(int z = 0; z < i - 1; z++) if (!memory_type::mergeType(*nReturnExpressionType, nExpressionType[z + 1], nReturnExpressionType)){ semanticError(token__KEYWORD, "incompatible types in expression"); _ERROR_ }

  	_DONE_
  }

	return false;
}

bool parser::fSHIFT(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	//_BEGIN_

	//bool bSIMPLEEXPRESSION = false;

	int nExpressionType[parser__MAX_EXPRESSION];
	

	*nReturnExpressionType = 0;

	if (/*bSIMPLEEXPRESSION = */fSIMPLEEXPRESSION(pp, p, &nExpressionType[0], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){
    int i = 0;
		i++;

	bool bSIMPLEEXPRESSION2 = false;
	bool bSIMPLEEXPRESSION3 = false;
	int nOperator = 0;

  if (!bWithoutBuiltin){

		do {

		 	if (i >= parser__MAX_EXPRESSION){ internalError("too many expressions in one line"); _ERROR_ }

   		nOperator = 0;
		
           //if (parseTerm(token__OP_SHL)){ nOperator = token__OP_SHL; }
//   		else if (parseTerm(token__OP_SHL_)){ nOperator = token__OP_SHL_; }
   		//else if (parseTerm(token__OP_SHR)){ nOperator = token__OP_SHR; }
   		//else if (parseTerm(token__OP_SHR_)){ nOperator = token__OP_SHR_; }

      switch(peekToken()){
        case token__OP_IMP:
          parseTerm(token__OP_IMP);
          nOperator = token__OP_IMP;
          break;
        case token__OP_EQV:
          parseTerm(token__OP_EQV);
          nOperator = token__OP_EQV;
          break;
      }
/*
   		     if (parseTerm(token__OP_IMP)){ nOperator = token__OP_IMP; }
   		else if (parseTerm(token__OP_EQV)){ nOperator = token__OP_EQV; }
*/
  		bSIMPLEEXPRESSION2 = false;
  		bSIMPLEEXPRESSION3 = false;

   		if (nOperator && 
        (
       //  (bSIMPLEEXPRESSION3 = fOPERATOR_OVERLOADING(p, *nReturnExpressionType, nOperator, nReturnExpressionType))
       //  || 
         (bSIMPLEEXPRESSION2 = fSIMPLEEXPRESSION(pp, p, &nExpressionType[i], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))
        
        ))
      {

        if (!memory_type::compatibleTypeOperator(nExpressionType[i], nExpressionType[i - 1], nOperator)){ semanticError(token__KEYWORD, "operator can not be used with this type"); _ERROR_ }

        i++;

  			if (bSIMPLEEXPRESSION2 && bProducePcode){

          switch(nOperator){
            case token__OP_IMP:
              pp->wr_IMP(pcode__IMP);
              break;
            case token__OP_EQV:
              pp->wr_EQV(pcode__EQV);
              break;
            default:
              { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }
              break;
          }

      				 //if (nOperator == token__OP_SHL) pp->wr_SHL(pcode__SHL);
//      		else if (nOperator == token__OP_SHL_) pp->wr_IS(pcode__SHL);
      		//else if (nOperator == token__OP_SHR) pp->wr_SHR(pcode__SHR);
      		//else if (nOperator == token__OP_SHR_) pp->wr_SHR(pcode__SHR);
      		     //if (nOperator == token__OP_IMP) pp->wr_IMP(pcode__IMP);
      		//else if (nOperator == token__OP_EQV) pp->wr_EQV(pcode__EQV);
         //else { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }

  			}
  		}

		} while (proceedParse() && (bSIMPLEEXPRESSION2 || bSIMPLEEXPRESSION3));
  }
		if (*nReturnExpressionType == 0) *nReturnExpressionType = nExpressionType[0];
		for(int z = 0; z < i - 1; z++) if (!memory_type::mergeType(*nReturnExpressionType, nExpressionType[z + 1], nReturnExpressionType)){ semanticError(token__KEYWORD, "incompatible types in expression"); _ERROR_ }

  	_DONE_
  }

	return false;
}

bool parser::fCOMPARISION(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	//_BEGIN_

	//bool bSHIFT = false;

	int nExpressionType[parser__MAX_EXPRESSION];
	

	*nReturnExpressionType = 0;

	if (/*bSHIFT = */fSHIFT(pp, p, &nExpressionType[0], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){
    int i = 0;
		i++;

	bool bSHIFT2 = false;
	bool bSHIFT3 = false;
	int nOperator = 0;

  if (!bWithoutBuiltin){

		do {

#ifdef KBDEBUG
  if (stopAtLine(35)){
    int i = 9;
    i++;
  }
#endif

		 	if (i >= parser__MAX_EXPRESSION){ internalError("too many expressions in one line"); _ERROR_ }

   		nOperator = 0;

      switch(peekToken()){
        case token__OP_EQUAL:
          parseTerm(token__OP_EQUAL);
          { nOperator = token__OP_EQUAL; *nReturnExpressionType = pcode__BOOLEAN; }
          break;
        case token__IS:
          parseTerm(token__IS);
          { nOperator = token__IS; *nReturnExpressionType = pcode__BOOLEAN; }
          break;
        case token__LIKE:
          parseTerm(token__LIKE);
          { nOperator = token__LIKE; *nReturnExpressionType = pcode__BOOLEAN; }
          break;
        case token__OP_UNEQUAL:
          parseTerm(token__OP_UNEQUAL);
          { nOperator = token__OP_UNEQUAL; *nReturnExpressionType = pcode__BOOLEAN; }
          break;
        case token__OP_GREATER:
          parseTerm(token__OP_GREATER);
          { nOperator = token__OP_GREATER; *nReturnExpressionType = pcode__BOOLEAN; }
          break;
        case token__OP_LESSER:
          parseTerm(token__OP_LESSER);
          { nOperator = token__OP_LESSER; *nReturnExpressionType = pcode__BOOLEAN; }
          break;
        case token__OP_GREATER_EQUAL:
          parseTerm(token__OP_GREATER_EQUAL);
          { nOperator = token__OP_GREATER_EQUAL; *nReturnExpressionType = pcode__BOOLEAN; }
          break;
        case token__OP_LESSER_EQUAL:
          parseTerm(token__OP_LESSER_EQUAL);
          { nOperator = token__OP_LESSER_EQUAL; *nReturnExpressionType = pcode__BOOLEAN; }
          break;
          /*
          // operator overloading
        case token__OP_EQUAL2:
          parseTerm(token__OP_EQUAL2);
          { nOperator = token__OP_EQUAL2; *nReturnExpressionType = pcode__BOOLEAN; }
          break;
        case token__OP_UNEQUAL2:
          parseTerm(token__OP_UNEQUAL2);
          { nOperator = token__OP_UNEQUAL2; *nReturnExpressionType = pcode__BOOLEAN; }
          break;*/
      }
/*
           if (parseTerm(token__OP_EQUAL)){ nOperator = token__OP_EQUAL; *nReturnExpressionType = pcode__BOOLEAN; }
   		else if (parseTerm(token__IS)){ nOperator = token__IS; *nReturnExpressionType = pcode__BOOLEAN; }
   		else if (parseTerm(token__LIKE)){ nOperator = token__LIKE; *nReturnExpressionType = pcode__BOOLEAN; }
   		else if (parseTerm(token__OP_UNEQUAL)){ nOperator = token__OP_UNEQUAL; *nReturnExpressionType = pcode__BOOLEAN; }
   		else if (parseTerm(token__OP_GREATER)){ nOperator = token__OP_GREATER; *nReturnExpressionType = pcode__BOOLEAN; }
   		else if (parseTerm(token__OP_LESSER)){ nOperator = token__OP_LESSER; *nReturnExpressionType = pcode__BOOLEAN; }
   		else if (parseTerm(token__OP_GREATER_EQUAL)){ nOperator = token__OP_GREATER_EQUAL; *nReturnExpressionType = pcode__BOOLEAN; }
   		else if (parseTerm(token__OP_LESSER_EQUAL)){ nOperator = token__OP_LESSER_EQUAL; *nReturnExpressionType = pcode__BOOLEAN; }


      // operator overloading
   		else if (parseTerm(token__OP_EQUAL2)){ nOperator = token__OP_EQUAL2; *nReturnExpressionType = pcode__BOOLEAN; }
   		else if (parseTerm(token__OP_UNEQUAL2)){ nOperator = token__OP_UNEQUAL2; *nReturnExpressionType = pcode__BOOLEAN; }
      */

  		bSHIFT2 = false;
  		bSHIFT3 = false;

   		if (nOperator && 
        (
       //  (bSHIFT3 = fOPERATOR_OVERLOADING(p, *nReturnExpressionType, nOperator, nReturnExpressionType))
      //   || 
         (bSHIFT2 = fSHIFT(pp, p, &nExpressionType[i], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))
        
        ))
      {

        if (!memory_type::compatibleTypeOperator(nExpressionType[i], nExpressionType[i - 1], nOperator)){ semanticError(token__KEYWORD, "operator can not be used with this type"); _ERROR_ }

        i++;

  			if (bSHIFT2 && bProducePcode){

          switch(nOperator){
            case token__OP_EQUAL:
              pp->wr_EQUAL(pcode__EQUAL, 1);
              break;
            case token__IS: 
              pp->wr_EQUAL(pcode__EQUAL, 1);
              //pp->wr_IS(pcode__IS, 1);
              break;
            case token__LIKE:
              pp->wr_LIKE(pcode__LIKE, 1, bOptionCompareBinary);
              break;
            case token__OP_UNEQUAL:
              pp->wr_UNEQUAL(pcode__UNEQUAL, 1);
              break;
            case token__OP_GREATER:
              pp->wr_GREATER(pcode__GREATER, 1);
              break;
            case token__OP_LESSER:
              pp->wr_LESSER(pcode__LESSER, 1);
              break;
            case token__OP_GREATER_EQUAL:
              pp->wr_GREATER_EQUAL(pcode__GREATER_EQUAL, 1);
              break;
            case token__OP_LESSER_EQUAL:
              pp->wr_LESSER_EQUAL(pcode__LESSER_EQUAL, 1);
              break;
            default:
              { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }
              break;
          }
          /*
      				 if (nOperator == token__OP_EQUAL) pp->wr_EQUAL(pcode__EQUAL, 1);
      		else if (nOperator == token__IS) pp->wr_IS(token__IS, 1);
      		else if (nOperator == token__LIKE) pp->wr_LIKE(token__LIKE, 1);
      		else if (nOperator == token__OP_UNEQUAL) pp->wr_UNEQUAL(pcode__UNEQUAL, 1);
      		else if (nOperator == token__OP_GREATER) pp->wr_GREATER(pcode__GREATER, 1);
      		else if (nOperator == token__OP_LESSER) pp->wr_LESSER(pcode__LESSER, 1);
      		else if (nOperator == token__OP_GREATER_EQUAL) pp->wr_GREATER_EQUAL(pcode__GREATER_EQUAL, 1);
      		else if (nOperator == token__OP_LESSER_EQUAL) pp->wr_LESSER_EQUAL(pcode__LESSER_EQUAL, 1);
         else { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }
*/
  			}
  		}

		} while (proceedParse() && (bSHIFT2 || bSHIFT3));
  }
		if (*nReturnExpressionType == 0) *nReturnExpressionType = nExpressionType[0];
    for(int z = 0; z < i - 1; z++){
      if (!memory_type::mergeType(*nReturnExpressionType, nExpressionType[z + 1], nReturnExpressionType)){ semanticError(token__KEYWORD, "incompatible types in expression"); _ERROR_ }
    }

  	_DONE_
  }

	return false;
}

bool parser::fAND(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	//_BEGIN_

	//bool bCOMPARISION = false;

	int nExpressionType[parser__MAX_EXPRESSION];

  *nReturnExpressionType = 0;

	if (/*bCOMPARISION = */fCOMPARISION(pp, p, &nExpressionType[0], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){
  	int i = 0;
		i++;


	bool bCOMPARISION2 = false;
	bool bCOMPARISION3 = false;
	int nOperator = 0;

  if (!bWithoutBuiltin){

		do {

		 	if (i >= parser__MAX_EXPRESSION){ internalError("too many expressions in one line"); _ERROR_ }

      int nPos = myToken->getPos();

			nOperator = 0;


      switch(peekToken()){
        case token__OP_AND:
          parseTerm(token__OP_AND);
          nOperator = token__OP_AND; 
          break;
        case token__OP_BIT_AND:
          parseTerm(token__OP_BIT_AND);
          nOperator = token__OP_BIT_AND; 
          break;
          // wegen operator overloading: sonderfall & als CPP-AND oder BASIC-STR_CAT
        case token__OP_STR_CAT:
          parseTerm(token__OP_STR_CAT);
          nOperator = token__OP_STR_CAT; 
          break;
      }
      /*
 		       if (parseTerm(token__OP_AND)){ nOperator = token__OP_AND; }
 		  else if (parseTerm(token__OP_BIT_AND)){ nOperator = token__OP_BIT_AND; }

      // wegen operator overloading: sonderfall & als CPP-AND oder BASIC-STR_CAT
 		  else if (parseTerm(token__OP_STR_CAT)){ nOperator = token__OP_STR_CAT; }
*/
			bCOMPARISION2 = false;
			bCOMPARISION3 = false;

/*
   		if (nOperator && 
        (
         (bCOMPARISION3 = fOPERATOR_OVERLOADING(p, *nReturnExpressionType, nOperator, nReturnExpressionType))
        
        ))
      {
        goto w;

      } else */
      {
        if (nOperator == token__OP_STR_CAT){
          nOperator = 0;

          myToken->setPos(nPos);

        }

         if (nOperator && 
         (
          (bCOMPARISION2 = fCOMPARISION(pp, p, &nExpressionType[i], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))
          
         ))
       {
  w:
         if (!memory_type::compatibleTypeOperator(nExpressionType[i], nExpressionType[i - 1], nOperator)){ semanticError(token__KEYWORD, "operator can not be used with this type"); _ERROR_ }

         i++;

  			  if (bCOMPARISION2 && bProducePcode){


          switch(nOperator){
            case token__OP_AND:
              pp->wr_AND(pcode__AND);
              break;
            case token__OP_BIT_AND:
              pp->wr_AND(pcode__AND);
              break;
            default:
              { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet " ); _ERROR_ }
              break;
          }
/*
                 if (nOperator == token__OP_AND) pp->wr_AND(pcode__AND);
           else if (nOperator == token__OP_BIT_AND) pp->wr_AND(pcode__AND);
           else { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet " ); _ERROR_ }
*/
  			  }
  		  }
     }


		} while (proceedParse() && (bCOMPARISION2 || bCOMPARISION3));
  }

		*nReturnExpressionType = nExpressionType[0];
		for(int z = 0; z < i - 1; z++) if (!memory_type::mergeType(*nReturnExpressionType, nExpressionType[z + 1], nReturnExpressionType)){ semanticError(token__KEYWORD, "incompatible types in expression"); _ERROR_ }

  	_DONE_
  }

	return false;
}

bool parser::fOR(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	//_BEGIN_

	//bool bAND = false;

	int nExpressionType[parser__MAX_EXPRESSION];

	*nReturnExpressionType = 0;

  //register bool bTerm_SYM_BR_OP;
  //bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP);

	if (/*bAND = */fAND(pp, p, &nExpressionType[0], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){
  	int i = 0;
		i++;



	bool bAND2 = false;
	bool bAND3 = false;
	int nOperator = 0;

#ifdef KBDEBUG
  if (stopAtLine(14)){
    int i = 9;
    i++;
  }
#endif

  if (!bWithoutBuiltin){


		do {


		 	if (i >= parser__MAX_EXPRESSION){ internalError("too many expressions in one line"); _ERROR_ }

   		nOperator = 0;

      switch(peekToken()){
        case token__OP_XOR:
          parseTerm(token__OP_XOR);
          nOperator = token__OP_XOR; 
          break;
        case token__OP_OR:
          parseTerm(token__OP_OR);
          nOperator = token__OP_OR; 
          break;
        case token__OP_BIT_OR:
          parseTerm(token__OP_BIT_OR);
          nOperator = token__OP_BIT_OR; 
          break;
        case token__OP_BIT_XOR:
          parseTerm(token__OP_BIT_XOR);
          nOperator = token__OP_BIT_XOR; 
          break;
          /*
        case token__OP_OR2:
          parseTerm(token__OP_OR2);
          nOperator = token__OP_OR2;
          break;*/
      }
/*
   				 if (parseTerm(token__OP_XOR)){ nOperator = token__OP_XOR; }
   		else if (parseTerm(token__OP_OR)){ nOperator = token__OP_OR; }
   		else if (parseTerm(token__OP_BIT_OR)){ nOperator = token__OP_BIT_OR; }
   		else if (parseTerm(token__OP_BIT_XOR)){ nOperator = token__OP_BIT_XOR; }           
   		else if (parseTerm(token__OP_OR2)){ nOperator = token__OP_OR2; }           
      */

			bAND2 = false;
			bAND3 = false;

      //bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP);

   		if (nOperator && 
        (
        // (bAND3 = fOPERATOR_OVERLOADING(p, *nReturnExpressionType, nOperator, nReturnExpressionType))
        // || 
         (bAND2 = fAND(pp, p, &nExpressionType[i], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))
        
        ))
      {
        if (!memory_type::compatibleTypeOperator(nExpressionType[i], nExpressionType[i - 1], nOperator)){ semanticError(token__KEYWORD, "operator can not be used with this type"); _ERROR_ }

        //if (bTerm_SYM_BR_OP && !parseTerm(token__SYM_BR_CL)){ syntaxError(token__ERROR, ") missing"); delete pp; _ERROR_ }

        i++;

  			if (bAND2 && bProducePcode){

          switch(nOperator){
            case token__OP_XOR:
              pp->wr_XOR(pcode__XOR);
              break;
            case token__OP_OR:
              pp->wr_OR(pcode__OR);
              break;
            case token__OP_BIT_OR:
              pp->wr_OR(pcode__OR);
              break;
            case token__OP_BIT_XOR:
              pp->wr_XOR(pcode__XOR);
              break;
            default:
              { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }
              break;
          }
          /*
              if (nOperator == token__OP_XOR) pp->wr_XOR(pcode__XOR);
       		else if (nOperator == token__OP_OR) pp->wr_OR(pcode__OR);
       		else if (nOperator == token__OP_BIT_OR) pp->wr_OR(pcode__OR);
       		else if (nOperator == token__OP_BIT_XOR) pp->wr_OR(pcode__XOR);
         else { semanticError(token__KEYWORD,  " Sorry! The operator is not supported yet." ); _ERROR_ }

         */

  			}
  		}

		} while (proceedParse() && (bAND2 || bAND3));
  }

		*nReturnExpressionType = nExpressionType[0];
		for(int z = 0; z < i - 1; z++) if (!memory_type::mergeType(*nReturnExpressionType, nExpressionType[z + 1], nReturnExpressionType)){ semanticError(token__KEYWORD, "incompatible types in expression"); _ERROR_ }

  	_DONE_
  }

	return false;
}

bool parser::fANDALSO(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	//_BEGIN_

	//bool bOR = false;

	int nExpressionType[parser__MAX_EXPRESSION];



	*nReturnExpressionType = 0;

	if (/*bOR = */fOR(pp, p, &nExpressionType[0], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){
  	int i = 0;
		i++;



	bool bOR2 = false;
	int nOperator = 0;
  int nPcodeOffset_BEFORE[parser__MAX_EXPRESSION];
	int nPcodeOffset_AFTER = 0;

		do {

		 	if (i >= parser__MAX_EXPRESSION){ internalError("too many expressions in one line"); _ERROR_ }

   		nOperator = 0;
   		
      if (parseTerm(token__OP_ANDALSO)){ 
        nOperator = token__OP_ANDALSO; *nReturnExpressionType = pcode__BOOLEAN; 
      }

      if (nOperator){
	      if (bProducePcode){
		      nPcodeOffset_BEFORE[i - 1] = pp->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
		      pp->wr_CJMP3(pcode__CJMP3, 0, true); // write pcode
	      }
      }



			bOR2 = false;
      
      if (nOperator){
        /*
            char ac[888];
            sprintf(ac, "|%d %d %d|" ,(int) pp, (int) pp->ba->nMem, (int) pp->ba->nMemOffset);
    CONSOLE printError(ac);
*/
        nOperator  = nOperator;
      }
   		if (nOperator && (bOR2 = fOR(pp, p, &nExpressionType[i], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))){
        if (!memory_type::compatibleTypeOperator(nExpressionType[i], nExpressionType[i - 1], nOperator)){ semanticError(token__KEYWORD, "operator can not be used with this type"); _ERROR_ }

        i++;

  		}
      


		} while (proceedParse() && bOR2);

    int nPcodeOffset_NEW = pp->getPos();
    int n = p->getPos();

		for(int z = 0; i > 1 && z < i - 1; z++){
  	  if (bProducePcode){
			  pp->setPos(nPcodeOffset_BEFORE[z]);	pp->wr_CJMP3(pcode__CJMP3, n + nPcodeOffset_NEW, true); // write pcode, new jump destination
      }
    }
    pp->setPos(nPcodeOffset_NEW);
/*
    if (i > 1){
    char ac[888];
    sprintf(ac, "[%d]", (int) this);
    CONSOLE printError(ac);
    }
*/
		if (*nReturnExpressionType == 0) *nReturnExpressionType = nExpressionType[0];

		for(int z = 0; z < i - 1; z++) if (!memory_type::mergeType(*nReturnExpressionType, nExpressionType[z + 1], nReturnExpressionType)){ semanticError(token__KEYWORD, "incompatible types in expression"); _ERROR_ }

  	_DONE_
  }

	return false;
}

bool parser::fORELSE(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	//_BEGIN_


	//bool bANDALSO = false;
	int nExpressionType[parser__MAX_EXPRESSION];


	*nReturnExpressionType = 0;

	if (/*bANDALSO = */fANDALSO(pp, p, &nExpressionType[0], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){
  	int i = 0;
		i++;



	bool bANDALSO2 = false;
	int nOperator = 0;
	int nPcodeOffset_BEFORE[parser__MAX_EXPRESSION];
	int nPcodeOffset_AFTER = 0;

		do {

		 	if (i >= parser__MAX_EXPRESSION){ internalError("too many expressions in one line"); _ERROR_ }

   		nOperator = 0;
   		
      if (parseTerm(token__OP_ORELSE)){ nOperator = token__OP_ORELSE; *nReturnExpressionType = pcode__BOOLEAN; }

      if (nOperator){
	      if (bProducePcode){
		      nPcodeOffset_BEFORE[i - 1] = pp->getPos(); // save the position of the CJMP pcode, later the destination will be overwritten
		      pp->wr_CJMP3(pcode__CJMP3, 0, false); // write pcode
	      }
      }

			bANDALSO2 = false;
   		if (nOperator && (bANDALSO2 = fANDALSO(pp, p, &nExpressionType[i], a, bConstExpression, bWithoutBuiltin, bEnum, bBinding))){
        if (!memory_type::compatibleTypeOperator(nExpressionType[i], nExpressionType[i - 1], nOperator)){ semanticError(token__KEYWORD, "operator can not be used with this type"); _ERROR_ }

        i++;

  		}

		} while (proceedParse() && bANDALSO2);

    int nPcodeOffset_NEW = pp->getPos();
    int n = p->getPos();

		for(int z = 0; i > 1 && z < i - 1; z++){
  	  if (bProducePcode){
			  pp->setPos(nPcodeOffset_BEFORE[z]);	pp->wr_CJMP3(pcode__CJMP3, n + nPcodeOffset_NEW, false); // write pcode, new jump destination
      }
    }
    pp->setPos(nPcodeOffset_NEW);


		if (*nReturnExpressionType == 0) *nReturnExpressionType = nExpressionType[0];

		for(int z = 0; z < i - 1; z++) if (!memory_type::mergeType(*nReturnExpressionType, nExpressionType[z + 1], nReturnExpressionType)){ semanticError(token__KEYWORD, "incompatible types in expression"); _ERROR_ }

  	_DONE_
  }
  

	return false;
}

/**
[EXPLANATION]
NAME: EXPRESSION
DESC: consists of values, variables and operators. E.g. 4 + 5 + nId
SEEALSO:
*/
/*
type check in expression
every part of the expressions returns the type as parameter

expression returns back a type 
*/
bool parser::fEXPRESSION(pcode *p, int *nReturnExpressionType)
{
	_BEGIN_

	t_arrayVariable a;     

  pcode *pp = new pcode(p->sCurrentFile.ascii());

	*nReturnExpressionType = 0;
	if (fORELSE(pp, p, nReturnExpressionType, &a, false, false, false, false)){ // pp is a tmp-pcode for the expression calculation, p is used for implicit DIM

    int nNewAdded = p->getPos(); // needed to change all pcode positions of calls of subs
    
    myModule->changeRegisterCallSub(pp, p, nNewAdded);
    if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_changeRegisterCallSub(getCurrentFile(), memory_module_changeRegisterCallSub, pp, p, nNewAdded);

    // add the pp to p
		// 1. p
		// 2.pp
		p->pcodeWritePcode(pp, -1);
    delete pp;

    _DONE_
  } else {

    delete pp;
  }

	_END_
}

/* *
[EXPLANATION]
NAME: CONST EXPRESSION
DESC:
SEEALSO:
*/
bool parser::fCONST_EXPRESSION(pcode *p, int *nReturnExpressionType)
{
	_BEGIN_

	t_arrayVariable a;	

	pcode *pp = new pcode(p->sCurrentFile.ascii());

  *nReturnExpressionType = 0;
	if (fORELSE(pp, p, nReturnExpressionType, &a, true, false, false, false)){ // pp is a tmp-pcode for the expression calculation, p is used for implicit DIM
		
    int nNewAdded = p->getPos(); // needed to change all pcode positions of calls of subs
    
    myModule->changeRegisterCallSub(pp, p, nNewAdded);
    if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_changeRegisterCallSub(getCurrentFile(), memory_module_changeRegisterCallSub, pp, p, nNewAdded);

    // add the pp to p
		// 1. p
		// 2.pp
		p->pcodeWritePcode(pp, -1);
    delete pp;

    _DONE_
	}

  delete pp;

	_END_
}

/* *
[EXPLANATION]
NAME: ENUM EXPRESSION
DESC:
SEEALSO:
*/
bool parser::fENUM_EXPRESSION(pcode *p, int *nReturnExpressionType)
{
	_BEGIN_

	t_arrayVariable a;	

	pcode *pp = new pcode(p->sCurrentFile.ascii());  

  *nReturnExpressionType = 0;
	if (fORELSE(pp, p, nReturnExpressionType, &a, true, false, true, false)){ // pp is a tmp-pcode for the expression calculation, p is used for implicit DIM

    int nNewAdded = p->getPos(); // needed to change all pcode positions of calls of subs
    
    myModule->changeRegisterCallSub(pp, p, nNewAdded);
    if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_changeRegisterCallSub(getCurrentFile(), memory_module_changeRegisterCallSub, pp, p, nNewAdded);

    // add the pp to p
		// 1. p
		// 2.pp
		p->pcodeWritePcode(pp, -1);
    delete pp;

    _DONE_
	}

  delete pp;

	_END_
}

bool parser::fEXPRESSION(pcode *p)
{
	register int nReturnExpressionType = 0;

	return fEXPRESSION(p, &nReturnExpressionType);
}

// CONST_EXPRESSION with only const and literals without vars
bool parser::fCONST_EXPRESSION(pcode *p)
{
	register int nReturnExpressionType = 0;

	return fCONST_EXPRESSION(p, &nReturnExpressionType);
}

/* *
[EXPLANATION]
NAME: CONST NUMERIC EXPRESSION
DESC:
SEEALSO:
*/
// CONST_EXPRESSION with only const and literals without vars
bool parser::fCONST_NUMERIC_EXPRESSION(pcode *p)
{
	register int nReturnExpressionType = 0;

  if (fCONST_EXPRESSION(p, &nReturnExpressionType)){
    switch(nReturnExpressionType){
      case pcode__BYTE:
      case pcode__SHORT:
      case pcode__INTEGER:
      case pcode__LONG:
      case pcode__SINGLE:
      case pcode__DOUBLE:
        /*
      case pcode__INT16:
      case pcode__INT32:
      case pcode__INT64:
      case pcode__UINT16:
      case pcode__UINT32:
      case pcode__UINT64:*/
        return true;
        break;
      default:
        return false;
        break;
    }  }
  return false;
}

// CONST_EXPRESSION with only const and literals without vars
bool parser::fCONST_LONG_EXPRESSION(pcode *p)
{
	register int nReturnExpressionType = 0;

  if (fCONST_EXPRESSION(p, &nReturnExpressionType)){
    switch(nReturnExpressionType){
      case pcode__BYTE:
      case pcode__SHORT:
      case pcode__INTEGER:
      case pcode__LONG:
        /*
      case pcode__INT16:
      case pcode__INT32:
      case pcode__INT64:
      case pcode__UINT16:
      case pcode__UINT32:
      case pcode__UINT64:*/
        return true;
        break;
      default:
        return false;
        break;
    }
  }
  return false;
}

bool parser::fEXPRESSION(pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	_BEGIN_

	pcode pp(p->sCurrentFile.ascii()); // HACK avoid pointer error ?!?

//	pcode *pp = new pcode(p->sCurrentFile.ascii());

  *nReturnExpressionType = 0;
  if (fORELSE(&pp, p, nReturnExpressionType, a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){ // pp is a tmp-pcode for the expression calculation, p is used for implicit DIM

    register int nNewAdded = p->getPos(); // needed to change all pcode positions of calls of subs
    
    myModule->changeRegisterCallSub(&pp, p, nNewAdded);
    if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_changeRegisterCallSub(getCurrentFile(), memory_module_changeRegisterCallSub, &pp, p, nNewAdded);

    // add the pp to p
		// 1. p
		// 2.pp
		p->pcodeWritePcode(&pp, -1);
    /*
    char ac[888];
    sprintf(ac, "|fEXPRESSION %d |", (int) pp.ba);
//    sprintf(ac, "%d nPos=%d nMem=%d nMemOffset=%d %-10.10s", (int) this, nPos, nMem, nMemOffset, acMem);
    CONSOLE printError(ac);
*/
  //  delete pp;

    _DONE_
	}


 // delete pp;

	_END_
}

bool parser::fEXPRESSION(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding)
{
	_BEGIN_

	if (fORELSE(pp, p, nReturnExpressionType, a, bConstExpression, bWithoutBuiltin, bEnum, bBinding)){ // pp is a tmp-pcode for the expression calculation, p is used for implicit DIM

    _DONE_
	}


	_END_
}

bool parser::fEXPRESSION(pcode *p, int *nReturnExpressionType, t_arrayVariable *a)
{
	return fEXPRESSION(p, nReturnExpressionType, a, false, false, false, false);
}

bool parser::fEXPRESSION2(pcode *p, int nType, bool bWithoutBuiltin, bool bBinding)
{
	_BEGIN_

	int nExpressionType = 0;
	bool bEXPRESSION = false;  
  t_arrayVariable a;      

  //prepareRollbackVariable();

	if (bEXPRESSION = fEXPRESSION(p, &nExpressionType, &a, false, bWithoutBuiltin, false, bBinding)){

    if (bBinding && nExpressionType == pcode__VARIANT){ 
      rollbackVariable();

      { semanticError(token__KEYWORD, "argument must not be VARIANT, if used for qt bindings methods"); _ERROR_ }

    	_END_
    }

		if (!compatibleType(nType, nExpressionType)){

      rollbackVariable();

    	_END_
    }

		_DONE_
	}

	_END_
}

bool parser::fEXPRESSION3(pcode *p, int nMustType, bool bWithoutBuiltin)
{
	_BEGIN_

	int nExpressionType = 0;
	bool bEXPRESSION = false;  
  t_arrayVariable a;      

  //prepareRollbackVariable();

	if (bEXPRESSION = fEXPRESSION(p, &nExpressionType, &a, false, bWithoutBuiltin, false)){

		if (nMustType != nExpressionType){

      rollbackVariable();

    	_END_
    }

		_DONE_
	}

	_END_
}

/* *
[EXPLANATION]
NAME: NUMERIC EXPRESSION
DESC:
SEEALSO:
*/
bool parser::fNUMERIC_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__DOUBLE); }

/* *
[EXPLANATION]
NAME: DOUBLE EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: INTEGER EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: STRING EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: BOOLEAN EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: LONG EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: SINGLE EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: BYTE EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: VARIANT EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: DATE EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: CURRENCY EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: CSTRING EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: CHARACTER EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: INT16 EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: INT32 EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: INT64 EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: UINT16 EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: UINT32 EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: UINT64 EXPRESSION
DESC:
SEEALSO:
*/
/* *
[EXPLANATION]
NAME: OBJECT EXPRESSION
DESC:
SEEALSO:
*/


bool parser::fDOUBLE_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__DOUBLE); }
bool parser::fINTEGER_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__INTEGER); }
bool parser::fSTRING_EXPRESSION(pcode *p, bool bWithoutBuiltin){ return fEXPRESSION2(p, pcode__QSTRING, bWithoutBuiltin) || fEXPRESSION2(p, pcode__CSTRING, bWithoutBuiltin); }
bool parser::fQSTRING_EXPRESSION(pcode *p, bool bWithoutBuiltin){ return fEXPRESSION2(p, pcode__QSTRING, bWithoutBuiltin); }
bool parser::fCSTRING_EXPRESSION(pcode *p, bool bWithoutBuiltin){ return fEXPRESSION2(p, pcode__CSTRING, bWithoutBuiltin); }
bool parser::fBOOLEAN_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__BOOLEAN); }
bool parser::fLONG_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__LONG); }
bool parser::fSINGLE_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__SINGLE); }
bool parser::fBYTE_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__BYTE); }
bool parser::fSHORT_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__SHORT); }
bool parser::fVARIANT_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__VARIANT); }
bool parser::fDATE_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__DATE); }
bool parser::fCURRENCY_EXPRESSION(pcode *p){ return fEXPRESSION2(p, pcode__CURRENCY); }


bool parser::fOBJECT_EXPRESSION(pcode *p, int *nExpressionType)
{
	_BEGIN_

	*nExpressionType = 0;
	if (fEXPRESSION(p, nExpressionType)){
    
		if (!memory_type::isObject(*nExpressionType)){ syntaxError(token__KEYWORD, "incompatible types. Must be OBJECT"); _ERROR_ }

		_DONE_
	}

	_END_
}

/**
[EXPLANATION]
NAME: CONDITION
DESC: a condition is an expression, which is used in IF, SELECT CASE or other condition statement to decide, which code should be executed.
SEEALSO:
*/
bool parser::fCONDITION(pcode *p, int *nType)
{
	_BEGIN_


#ifdef KBDEBUG
  if (stopAtLine(133)){
    int i = 3;
    i++;
  }
#endif
	

  if (fEXPRESSION(p, nType)){

    switch(*nType){
      case pcode__QSTRING:
      case pcode__CSTRING:
      case pcode__LQSTRING:
      case pcode__LCSTRING:
        // try if it is a string expression
         _END2_
         if (fSTRING_EXPRESSION(p)){
            if (bProducePcode){
    		       p->wr_LEN(pcode__LEN, true, true);
               p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 0);
               p->wr_UNEQUAL(pcode__UNEQUAL, 1);
            }
         }
         *nType = pcode__BOOLEAN;

        break;
    }      

    // [KBASIC], nur boolean erlaubt
    if (isKBASIC()){
		  if (*nType != pcode__BOOLEAN){ semanticError(token__IF, "condition must return a boolean value"); _ERROR_ }
    } else {
      // must be numeric type
      if (!memory_type::isNumeric(*nType) && *nType != pcode__BOOLEAN){ semanticError(token__IF, "condition must return a numeric or boolean value"); _ERROR_ }
    }

		_DONE_

  }

	_END_
}

/*
bool parser::fINC(pcode *p)
{
	_BEGIN_
/ *
	register bool bTerm_OP_INC = false;

  if (bTerm_OP_INC = parseTerm(token__OP_INC)){
    
	  bool bTerm_SYM_BR_OP = false;
    bool bTerm_SYM_BR_CL = false;

    if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}

	  int nVar = 0;
	  bool scope = false;
	  bool bImplicitDIM = false;
	  int nIdType = 0;
	  int nType = 0;
	  t_array a;  

	  if (fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, &a)){

		  if (nType == token__ME){
        { semanticError(token__KEYWORD, "INC not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__KEYWORD, "INC not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

      // 
      // numeric type?
      // push id
      // push 1
      // add      

      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}

	    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__OP_INC, ") missing"); _ERROR_ }

      _DONE_
    }

  }
* /
	_END_
}*/
/*
bool parser::fINC_(pcode *p)
{
	_BEGIN_

	int nVar = 0;
	t_scope scope = global;
	int nType = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm_OP_INC_ = false;

    if (bTerm_OP_INC_ = parseTerm(token__OP_ADD_ADD)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_ADD_ADD)){
        parseInfo(p, "parsed ++ OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }

       // 
       semanticError(token__KEYWORD,  " Sorry! The ++ is not supported yet " ); _ERROR_ 

		  if (nType == token__ME){
       { semanticError(token__KEYWORD, "++ not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
       { semanticError(token__KEYWORD, "++ not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

      // 
      // numeric type?
      // push id
      // push 1
      // add
      _DONE_
    }

    
  }

	_END_
}
*/
/*
bool parser::fDEC(pcode *p)
{
	_BEGIN_
/ *
	register bool bTerm_OP_DEC = false;

  if (bTerm_OP_DEC = parseTerm(token__OP_DEC)){
    
	  bool bTerm_SYM_BR_OP = false;
    bool bTerm_SYM_BR_CL = false;

    if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}

	  int nVar = 0;
	  bool scope = false;
	  bool bImplicitDIM = false;
	  int nIdType = 0;
	  int nType = 0;
	  t_array a;  

	  if (fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, &a)){

		  if (nType == token__ME){
        { semanticError(token__KEYWORD, "DEC not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__KEYWORD, "DEC not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

      // 
      // numeric type?
      // push id
      // push 1
      // sub      

      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}

	    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__OP_INC, ") missing"); _ERROR_ }

      _DONE_
    }


  }
* /
	_END_
}
*/

/*
bool parser::fDEC_(pcode *p)
{
	_BEGIN_

	int nVar = 0;
	t_scope scope = global;
	int nType = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm_OP_DEC_ = false;

    if (bTerm_OP_DEC_ = parseTerm(token__OP_SUB_SUB)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_SUB_SUB)){
        parseInfo(p, "parsed -- OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }

       // 
       semanticError(token__KEYWORD,  " Sorry! The -- is not supported yet " ); _ERROR_ 

		  if (nType == token__ME){
       { semanticError(token__KEYWORD, "-- not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
       { semanticError(token__KEYWORD, "-- not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

      // 
      // numeric type?
      // push id
      // push 1
      // sub
      // mov id
      _DONE_
    }
    
  }

	_END_
}
*/

/*
bool parser::fSHL(pcode *p)
{
	_BEGIN_
/ *
	register bool bTerm_OP_INC = false;

  if (bTerm_OP_INC = parseTerm(token__OP_INC)){
    
	  bool bTerm_SYM_BR_OP = false;
    bool bTerm_SYM_BR_CL = false;

    if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}

	  int nVar = 0;
	  bool scope = false;
	  bool bImplicitDIM = false;
	  int nIdType = 0;
	  int nType = 0;
	  t_array a;  

	  if (fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, &a)){

		  if (nType == token__ME){
        { semanticError(token__KEYWORD, "INC not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__KEYWORD, "INC not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

      // 
      // numeric type?
      // push id
      // push 1
      // add      

      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}

	    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__OP_INC, ") missing"); _ERROR_ }

      _DONE_
    }

  }
* /
	_END_
}*/

/*
bool parser::fSHL_(pcode *p)
{
	_BEGIN_

	int nVar = 0;
	t_scope scope = global;
	int nType = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm_OP_SHL_ = false;

    if (bTerm_OP_SHL_ = parseTerm(token__OP_LESSER_LESSER)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_LESSER_LESSER)){
        parseInfo(p, "parsed << OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }

       // 
       semanticError(token__KEYWORD,  " Sorry! The << is not supported yet " ); _ERROR_ 

		  if (nType == token__ME){
       { semanticError(token__KEYWORD, "<< not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
       { semanticError(token__KEYWORD, "<< not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

      // 
      // numeric type?
      // push id
      // push 1
      // add
      _DONE_
    }

    
  }

	_END_
}
*/

/*
bool parser::fSHR(pcode *p)
{
	_BEGIN_
/ * 
	register bool bTerm_OP_DEC = false;

  if (bTerm_OP_DEC = parseTerm(token__OP_DEC)){
    
	  bool bTerm_SYM_BR_OP = false;
    bool bTerm_SYM_BR_CL = false;

    if ((bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}

	  int nVar = 0;
	  bool scope = false;
	  bool bImplicitDIM = false;
	  int nIdType = 0;
	  int nType = 0;
	  t_array a;  

	  if (fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, &a)){

		  if (nType == token__ME){
        { semanticError(token__KEYWORD, "DEC not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
        { semanticError(token__KEYWORD, "DEC not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

      // 
      // numeric type?
      // push id
      // push 1
      // sub      

      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}

	    if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__OP_INC, ") missing"); _ERROR_ }

      _DONE_
    }


  }
* /
	_END_
}*/

/*
bool parser::fSHR_(pcode *p)
{
	_BEGIN_

	int nVar = 0;
	t_scope scope = global;
	int nType = 0;

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

	  bool bTerm_OP_SHR_ = false;

    if (bTerm_OP_SHR_ = parseTerm(token__OP_GREATER_GREATER)){

      int nPos = myPcode->getPos();

      if (fOPERATOR_OVERLOADING(p, nVar, scope, nType, token__OP_GREATER_GREATER)){
        parseInfo(p, "parsed >> OPERATOR OVERLOADING" );
        _DONE_       

      } else {
        // rollback
        myPcode->setPos(nPos);
      }

       // 
       semanticError(token__KEYWORD,  " Sorry! The >> is not supported yet " ); _ERROR_ 

		  if (nType == token__ME){
       { semanticError(token__KEYWORD, ">> not allowed in combination with ME"); _ERROR_ }
		  } else if (nType == token__PARENT){
       { semanticError(token__KEYWORD, ">> not allowed in combination with PARENT"); _ERROR_ }
      } else {
      }

      // 
      // numeric type?
      // push id
      // push 1
      // sub
      // mov id
      _DONE_
    }
    
  }

	_END_
}
*/

