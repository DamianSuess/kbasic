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


#ifndef PARSER_H
#define PARSER_H



#include <ctype.h>

#include "XIntVector.h"

#include "../kbshared/typedef.h"

#include "../kbshared/pcode.h"


#include "../kbshared/pcode_kbasic_binding.h"

#include "token.h"

#include "memory_variable.h"
#include "memory_label.h"
#include "memory_stringliteral.h"
#include "memory_const.h"
#include "memory_type.h"
#include "memory_enum.h"
#include "memory_sub.h"
#include "memory_class.h"
#include "memory_module.h"

#include "utility.h"
#include "scanner.h"
#include "../kbshared/console.h"


// needed for rollback, if walk through parse tree failed,
// hint: but most time avoid macros and use it only for exceptions like here
#define _BLOCK_BEGIN_	 int nCurrentToken; nCurrentToken = getTokenPos(); int nCurrentPcode; nCurrentPcode = p->getPos(); t_with2 currentWith = with; /*p->nIndent++;*/
#define _BEGIN_	 int nCurrentToken; nCurrentToken = getTokenPos(); int nCurrentPcode; nCurrentPcode = p->getPos(); t_with2 currentWith = with; /*p->nIndent++;*/
#define _BEGIN2_	nCurrentToken = getTokenPos(); nCurrentPcode = p->getPos(); currentWith = with; /*p->nIndent++;*/
#define _BEGIN3_	int nCurrentToken3; nCurrentToken3 = getTokenPos(); int nCurrentPcode3; nCurrentPcode3 = p->getPos(); currentWith = with; /*p->nIndent++;*/
#define _BLOCK_END_ { setTokenPos(nCurrentToken); p->setPos(nCurrentPcode); with = currentWith; /*p->nIndent--;*/ return false; }
#define _END_ { setTokenPos(nCurrentToken); p->setPos(nCurrentPcode); with = currentWith; /*p->nIndent--;*/ return false; }
#define _END2_ { setTokenPos(nCurrentToken); p->setPos(nCurrentPcode); with = currentWith; /*p->nIndent--;*/ }
#define _END3_ { setTokenPos(nCurrentToken3); p->setPos(nCurrentPcode3); with = currentWith; /*p->nIndent--;*/ }

#define _PEND_ { p->setPos(nCurrentPcode); with = currentWith; /*p->nIndent--;*/ }

#define _BLOCK_DONE_ { /*p->nIndent--;*/ return true; }
#define _DONE_ { /*p->nIndent--;*/ return true; }
#define _ERROR_ { /*p->nIndent--;*/ return false; }

#define _TBEGIN_	int nCurrentToken; nCurrentToken = getTokenPos(); t_with2 currentWith = with;
#define _TEND_ { setTokenPos(nCurrentToken); with = currentWith; return false; }
#define _TEND2_ { setTokenPos(nCurrentToken); with = currentWith; }
#define _TDONE_ { return true; }
#define _TERROR_ { return false; }

#define _SCANBEGIN_	int nCurrentToken99; nCurrentToken99 = getTokenPos(); int nCurrentLine99 = getCurrentLine(); int nCurrentRow99 = getCurrentRow(); t_with2 currentWith = with;
#define _SCANEND_ { setTokenPos(nCurrentToken99); setCurrentLine(nCurrentLine99);	setCurrentRow(nCurrentRow99); with = currentWith; }


#define _BEGIN_fVARIABLE_ _BEGIN_ /* if gescheitert && !neuesTokenGelesen _END_*/
#define _END_fVARIABLE_ _END_ /*gescheitert = true*/


extern XIntMap binding_map_class;
extern XIntMap binding_map_method;



struct t_exception 
{
public:
  const char *acName;
  int nLine;
  int nRow;
};



#define exception XIntVector




struct t_with {
public:
	int from;
	int to;

  t_with(int _from, int _to){
    from = _from;
    to = _to;
  }

};


struct t_with2 {
public:
int nWithOldPos;
int nWithCurrentLine;
int nWithCurrentRow;
int nWithStringPos;
int nWithRowStart;
int nWithRowEnd;
t_with *With;
t_token WithToken;
};




struct parser_parameter {
public:
	parser_parameter(const char *acName, int nType, bool bOptional);
	parser_parameter(const char *acName, int nType, bool bOptional, bool bDefault);
	parser_parameter(const char *acName, int nType, bool bOptional, float fDefault);
	parser_parameter(const char *acName, int nType, bool bOptional, double dDefault);
	parser_parameter(const char *acName, int nType, bool bOptional, int nDefault);
	parser_parameter(const char *acName, int nType, bool bOptional, long lDefault);
	parser_parameter(const char *acName, int nType, bool bOptional, const char *sDefault); // gab problem mit XString als default statt const char *


	XString sName;
	int nType;
	bool bOptional;
	bool bDefault;
	
		float		single_;
		double 		double_;
		int			integer_;
		long			long_;
		char		boolean_;
	
	
	XString cstring_;
};

struct parser_method {
public:
	parser_method(bool bSupported, int nClassMethodId, int nReturnType, XIntVector *pp, bool bSignal, bool bSlot, bool bStatic, bool bEvent);
	~parser_method();

	int nClassMethodId;
	int nReturnType;
  bool bSignal;
  bool bSlot;
  bool bStatic;
  bool bEvent;
  bool bSupported;

	XIntVector *myParser_parameter;

};

/*
struct parser_operator {
public:
	parser_operator(bool bSupported, int nClassMethodId, int nReturnType, int nOperatorType, XIntVector *pp);
	~parser_operator();

	int nClassOperatorId;
	int nOperatorType;
	int nReturnType;
  bool bSupported;

	XIntVector *myParser_parameter;

};*/

struct parser_class2 {
public:
	parser_class2(int nParentClassId, int nParentClassId2, int nClassId, bool bAbstract);
	~parser_class2();

	int nParentClassId;
	int nParentClassId2;
	int nClassId;
  bool bAbstract;
  int nNamespace;

	XIntMap myParser_const;
	XIntMap myParser_method;
	XIntMap myParser_staticmethod;
	XIntMap myParser_property_get;
	XIntMap myParser_property_set;
	XIntMap myParser_staticproperty_get;
	XIntMap myParser_staticproperty_set;
  /*
	XIntMap myParser_function;
	XIntMap myParser_operator;
	XIntMap myParser_function_operator;
	XIntMap myParser_slot;
	XIntMap myParser_signal;
	XIntMap myParser_protected;
	XIntMap myParser_property;
	XIntMap myParser_enum;
  */

};

struct parser_classMethod {
public:
	parser_classMethod();
	~parser_classMethod();

	bool setNamespace(int p1);

	bool new_class(int p1, int p2, int p3, bool bAbstract = false);
	bool new_param(char *p1, int p2, bool p3);
	bool new_param(char *p1, int p2, bool p3, bool p4);
	bool new_param(char *p1, int p2, bool p3, float p4);
	bool new_param(char *p1, int p2, bool p3, double p4);
	bool new_param(char *p1, int p2, bool p3, int p4);
	bool new_param(char *p1, int p2, bool p3, long p4);
	bool new_param(char *p1, int p2, bool p3, const char *p4); // gab probleme mit XString

	bool new_const(int p1, int p2);
	bool new_method(bool bSupported, int p1, int p2, int p3, bool bSignal = false, bool bSlot = false, bool bStatic = false, bool bEvent = false);
	bool new_staticmethod(bool bSupported, int p1, int p2, int p3);

  bool new_property_get(int p1, int p2, int p3);
  bool new_property_set(int p1, int p2, int p3);

  bool new_staticproperty_get(int p1, int p2, int p3);
  bool new_staticproperty_set(int p1, int p2, int p3);
	/*
  bool new_operator(bool bSupported, int p1, int p2, int p3, int p4);


  bool new_function(bool bSupported, int p1, int p2);
	bool new_function_operator(bool bSupported, int p0, int p1, int p2, int p3);
	//bool new_protected(int p1, int p2, int p3);
	bool new_slot(bool bSupported, int p1, int p2, int p3);
	bool new_signal(bool bSupported, int p1, int p2, int p3);

	bool new_enum(int p1, char *p2, int p3);
*/
	XIntMap myParser_class;

  int nNamespace;

private:
	XIntVector *pp_list;

};


class _cache;
class _mainwindow;


class parser {
public:
	parser(pcode *p, cache *my_cache = 0);
	parser(){ parser(0); }
	~parser();

	bool parse(token *t, bool bSilent, bool bDebug, bool bUseCache = true);
	bool parse2(token *t, bool bSilent, bool bDebug, bool bUseCache = true);

  bool parseVeryOldBasic(token *t, bool bSilent, bool bDebug, bool bUseCache = true);
	bool parseOldBasic(token *t, bool bSilent, bool bDebug, bool bUseCache = true);
	bool parseKBasic(token *t, bool bSilent, bool bDebug, bool bUseCache = true);


  memory_stringliteral *myMemory_stringliteral;
  memory_type *myMemory_type;
  memory_enum *myMemory_enum;
  memory_class *myClass;
  memory_module *myModule;

	int nPeekVar; t_scope PeekScope; int nPeekType;

  bool bParseToken;
  bool bNoError;

  int nProceedPercent;

	bool findConst(int id, const char **acModule, const char **acSub, const char **name);
	const char *findStringLiteral(int id);
	bool findVar(int id, const char **acModule, const char **acSub, const char **acVar);
  bool findScope(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub);
  bool findScope2(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub);

  const char *findTypeElement(int type_id, int field_id);
	const char *findType(int id);

  const char *findEnum(int id);
  int findEnumElement(int nEnumId, const char *acElementName);
  const char *findEnumElement(int nEnumId, int field_id);
  int enumElementType		(int nEnumId, int nElement);

  bool	registerEnumElement(int nEnumId, const char *acIdentifier, const char *acType);
  int registerBinding(bool bSupported, const char *name, int id);

    			/*
  const char *findStructure(int id);
  bool	registerStructureElement(int id, const char *acIdentifier,  const char *acType);
  const char *findStructureElement(int myMemory_structureid, int field_id);
				*/


  pcode *getPcode(){ return myPcode; }

  const char *acDefaultModuleName; // standard module name if no module or class scope has been entered

private:

  int key; 
  int value;

	bool fNULL 	  	        	();

  // literals
	bool fBOOLEAN 	  	     	(t_boolean *cBoolean);

  bool fSTRING	 	  	     	(t_cstring acString);

	bool fBYTE 			  	     	(t_byte *ucByte);
	bool fINTEGER 	  	     	(t_integer *nInteger);
	bool fLONG								(t_long *lLongInteger);

  bool fDOUBLE	 	  	     	(t_double *dNumeric);
  bool fSINGLE	 	  	     	(t_single *fNumeric);
	bool fSTRING							(t_cstring *acString, bool bAdd = true);

	bool fCURRENCY 	  	     	(t_currency *c);

	bool fDATE		 	  	     	(t_date *d);

	bool fTIME		 	  	     	(t_date *d);

	//bool fCHARACTER	  	     	(t_character *d); 

	// misc
	bool fID_ALL							(const char **acIdentifier);

	bool fID									(const char **acIdentifier, int nID, bool bKeywordBuiltin, bool bParseInfo = true, bool bLower = false, bool bAll = false);
	bool fID									(const char **acIdentifier, bool bParseInfo = true);
	bool fID_KEYWORD_OR_BUILTIN (const char **acIdentifier, bool bLower = false);
	bool fID_INTEGER					(const char **acIdentifier);  
	bool fID_DOUBLE						(const char **acIdentifier);
	bool fID_SINGLE						(const char **acIdentifier);
	bool fID_STRING						(const char **acIdentifier);
	bool fID_LONG							(const char **acIdentifier);
	bool fID_CURRENCY					(const char **acIdentifier);
  
  bool fMODULENAME         (pcode *p, const char **acIdentifier);
  bool fCLASSNAME          (pcode *p, const char **acIdentifier);

  bool fTYPE              (const char **acType, int *nSize);
  bool fTYPE              (pcode *p, const char **acType, bool bNew = false);
	bool fTYPE								(pcode *p, const char **acType, bool bNew, int *nSize);


	bool fSELECTOR_CLASS_VAR	(pcode *p, int *nVar, int *nIdType, int *nType, 
                          t_arrayVariable *a, t_scope *scope, 
                          const char **acIdentifier, bool *bARRAY2, 
                          bool bAssignment, int *nAccessScopeId, int *nAccessScope, int *nStringLen
                          );
  
	bool fSELECTOR_CLASS_PROPERTY	(pcode *p, int nClassId,  
                          const char *acIdentifier, bool bAssignment,
                          bool *binding_fPROPERTY_ASSIGNMENT,
                          int *nReturnId, int *nReturnType
                          );
  
	bool fARRAY								(pcode *p, t_array *a, int nType, int nIdentifier, int nElementId, bool bAssignment, bool bEmptyAllowed, bool bTestForError, t_scope scope);
	bool fREGISTER_ARRAY			(pcode *p, t_array *a, int nType, int nIdentifier);
	bool fREGISTER_ARRAY_CONST(pcode *p, t_array *a, int nType, int nIdentifier, t_scope scope);
	bool fREGISTER_ARRAY_CONST(pcode *p, const char *acIdentifier, t_array *a, bool bTestDimension = true);
	bool fARRAY								(const char *acIdentifier, t_array *a); // static array size, index is a fix integer

  // other
	bool fKBASIC   			    	();
	bool fSTATEMENTSEQUENCE		(pcode *p, bool bDebugStatements = false, bool bNoStatementIsError = false, bool bTestEndIf = false);
	bool fSTATEMENTSEQUENCEONELINE	(pcode *p);
//	bool fSTATEMENT						(pcode *p, bool bEOL);
//	bool fSTATEMENT						(pcode *p, bool bDebugStatement);
	bool fSTATEMENT						(pcode *p, bool bEOL = true, bool bDebugStatement = false, bool bNoStatementIsError = false, bool *bErrorRecovering = 0);
	bool fCONDITION	        	(pcode *p, int *nType);
/*
	bool fADD_ASSIGNMENT      (pcode *p);
	bool fSUB_ASSIGNMENT      (pcode *p);
	bool fDIV_ASSIGNMENT      (pcode *p);
	bool fMUL_ASSIGNMENT      (pcode *p);
	bool fOR_ASSIGNMENT       (pcode *p);
	bool fXOR_ASSIGNMENT      (pcode *p);
	bool fAND_ASSIGNMENT      (pcode *p);*/

	bool fASSIGNMENT        	(pcode *p);
	bool fTHROW								(pcode *p);
	bool fTRY									(pcode *p);
	bool fIF									(pcode *p);
	bool fEOL     			    	(bool bPos = true);
	bool fEOL2    			    	(bool bPos = true);
	bool fEOF2    			    	();
	bool peekEOLREM						();
	bool fEOLREM							(bool bPos = true);
	bool fCOL     			    	(bool bPos = true);
	bool fDIM     			    	(pcode *p);
	bool fREDIM    			    	(pcode *p);
	bool fCLASS_VAR			    	();
	bool fMODULE_VAR			   	();
	bool fSTOP     			    	(pcode *p);
	bool fEND     			    	(pcode *p);
	bool f_END     			    	(pcode *p);
	bool fWITH								(pcode *p);
	bool fFOR									(pcode *p);
	bool fFOREACH							(pcode *p);
	bool fDOWHILELOOP					(pcode *p);
	bool fDOUNTILLOOP					(pcode *p);
	bool fDOLOOPWHILE					(pcode *p);
	bool fDOLOOPUNTIL					(pcode *p);
	bool fWHILEWEND						(pcode *p);
	bool fWHILEENDWHILE  			(pcode *p);
	bool fSELECTCASE					(pcode *p);
	bool fFUNCTION_RETURN			(pcode *p); // function return

  bool isVERYOLDBASIC(){ return bVeryOldBasic; } // qbasic
  bool isOLDBASIC(){ return bOldBasic; }// vb6
  bool isKBASIC(){ return bKBasic; }
  /*
  bool fOPERATOR_OVERLOADING(pcode *p, int nVar, t_scope scope, int nType, int nOperatorType);
  bool fOPERATOR_OVERLOADING(pcode *p, int nType, int nOperatorType, int *nReturnExpressionType);  
  bool fOPERATOR_OVERLOADING(pcode *p, int nVar, t_scope scope, int nType, int nOperatorType, int *nReturnExpressionType);  
*/

  bool fMETHOD_CALL        (pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, bool bStaticMethodOnly, bool bBothMethods);
  bool fCONSTRUCTOR_CALL   (pcode *p, int nClassId);
  bool fDESTRUCTOR_CALL    (pcode *p, int nClassId);
	bool fFUNCTION_CALL				(pcode *p, const char **acIdentifier, 
                           int *nReturnExpressionType, 
                           bool bReturn, bool *bUnknownFunction); // sub call

	bool fSUB_CALL						(pcode *p, const char **acIdentifier, 
                          int *nReturnExpressionType, bool bConstructor, bool bDestructor,
                          bool *bUnknownFunction, bool bReturn = false, bool bClassMethod = false, 
                          int nClassId = 0, bool bStaticMethod = false, bool bBothMethods = false, 
                          bool bExplicitConstructorCall = false, 
                          bool bExplicitDestructorCall = false, 
                          bool bSignalSlotDefinition = false); // sub call

	bool fSUB_CALL						(pcode *p, const char **acIdentifier); // sub call

	bool fSUB_NAME						(const char **acIdentifier);
	bool fPROPERTY_NAME				(const char **acIdentifier);
 	

	bool fME_METHOD_CALL			(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fME_METHOD_CALL			(pcode *p, int *nReturnExpressionType, bool bReturn, bool bParent);
	bool fPARENT_METHOD_CALL	(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fNEW_METHOD_CALL			(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fNEW									(pcode *p);

	bool fME			(pcode *p, int *nReturnExpressionType, bool bReturn, bool bBinding);
	bool fME			(pcode *p, int *nReturnExpressionType, bool bReturn, bool bParent, bool bBinding);
	bool fPARENT	(pcode *p, int *nReturnExpressionType, bool bReturn, bool bBinding);

	bool fREM									(bool bParseEOL = true);
	bool fVERSION           ();
	bool fFILENAME           ();
	bool fLABEL								(pcode *p);
	bool fERASE								(pcode *p);
	bool fCLEAR								(pcode *p);
	bool fLINE								(pcode *p);
	bool fGOTO								(pcode *p, bool bParseGotoKeyword = true);
	bool fGOSUB								(pcode *p);
	bool fRETURN							(pcode *p);
	bool fEXIT								(pcode *p);
	bool fITERATE							(pcode *p);
	bool fCLASS_METHOD_BODY		(); // method body
	bool fCLASS_PROPERTY_BODY	();
	bool fCLASS_STATICSCOPE	  ();  
	bool fPROPERTY_BODY				();
	bool fPROPERTY_BODY				(bool bClassMethod);

  bool findMatchingMethod  (const char *acSignature, int nClassId, int *nParentClassId, int *nParentSubId, bool bConstructor, bool bDestructor);

	bool fSUB_BODY						(); // sub body
	bool fSUB_BODY						(bool bClassMethod); // sub body
	bool fCLASS_BODY					(); // class body
	bool fTYPE_BODY					  (); // type body
	bool fENUM_BODY					  ();
	//bool fSTRUCTURE_BODY		  ();
  //bool fINTERFACE_BODY		  ();

	bool fREGISTER_SUB				(bool bClassMethod, bool *bAbstract, bool *bDeclare);
	bool fREGISTER_SUB				();
	bool fREGISTER_METHOD			(bool *bAbstract, bool *bDeclare);  

	bool fREGISTER_PROPERTY 	();


	bool fREGISTER_CLASS_METHOD		();
	bool fREGISTER_CLASS_PROPERTY		();
	bool fREGISTER_CLASS_STATICSCOPE	(pcode *p);
  bool fREGISTER_CLASS_VAR			(pcode *p);
	bool fREGISTER_CLASS_CONST		(pcode *p);
	bool fREGISTER_CLASS_ENUM		();
	bool fREGISTER_CLASS_TYPE		();
	bool fREGISTER_CLASS_DEFAULT	(bool bConstructor, bool bDestructor);  
	bool fREGISTER_CLASS_DEFAULT_CONSTRUCTOR	();  
	bool fREGISTER_CLASS_DEFAULT_DESTRUCTOR	();  
  bool fREGISTER_CLASS			();

	bool fREGISTER_MODULE_SUB 	();
  bool fREGISTER_MODULE_VAR			(pcode *p);
	bool fREGISTER_MODULE_CONST		(pcode *p);
	bool fREGISTER_MODULE_ENUM		();
	bool fREGISTER_MODULE_TYPE		();
  bool fREGISTER_MODULE			();

	bool fREGISTER_TYPE				(pcode *p);
	bool fREGISTER_ENUM				(pcode *p);

//	bool fIMPORTS 						();
//	bool fNAMESPACE						();
	bool fOPTION							(pcode *p);
	bool fCONST								(pcode *p);
	bool fCLASS_CONST					();
	bool fMODULE_CONST				();
	bool fSYSTEM							(pcode *p);
	bool fMID2								(pcode *p);
	//bool fSIZEOF							(pcode *p, int *nReturnExpressionType);
	bool fLBOUND							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fUBOUND							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fONERROR							(pcode *p);
	bool fONGOSUB							(pcode *p);
	bool fONTIMER							(pcode *p);  
	bool fONGOTO							(pcode *p);
	bool fRESUME							(pcode *p);
	bool fRANDOMIZE						(pcode *p);
	bool fFRE 								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fERROR								(pcode *p);
	bool fFILEATTR						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fFILEDATETIME				(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fFILELEN							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fFORMAT							(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fFREEFILE						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fGETATTR							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fHOUR								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fINPUTBOX						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISERROR							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISARRAY							(pcode *p, int *nReturnExpressionType, bool bReturn);

	bool fPEEK							(pcode *p, bool bObjectFake = false);
	bool fPOKE							(pcode *p, bool bObjectFake = false);

	bool fISBOOLEAN							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISBYTE							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISDOUBLE							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISINTEGER							(pcode *p, int *nReturnExpressionType, bool bReturn);
  /*
	bool fISINT16							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISINT32							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISINT64							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISUINT16						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISUINT32						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISUINT64						(pcode *p, int *nReturnExpressionType, bool bReturn);
  */
	bool fISSHORT							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISLONG    					(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISSTRING   					(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISVARIANT  					(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISSINGLE  					(pcode *p, int *nReturnExpressionType, bool bReturn);

	bool fLOC									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fMINUTE							(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fMONTH								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fMSGBOX							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fNOW									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fRGB									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSECOND							(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fTIMER								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fGET									(pcode *p);
	bool fPUT									(pcode *p);
/*
	bool fFORMATCURRENCY			(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fFORMATDATETIME			(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fFORMATNUMBER				(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fFORMATPERCENT				(pcode *p, int *nReturnExpressionType, bool bReturn);
  */
	bool fWEEKDAYNAME					(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fMONTHNAME					  (pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fDAYNAME					    (pcode *p, int *nReturnExpressionType, bool bReturn);


	bool fTIMESERIAL					(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fTIMEVALUE						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fTYPENAME						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fWEEKDAY							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fYEAR								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);

	bool f_STATIC							(pcode *p);
	bool f_DYNAMIC						(pcode *p);
	bool fCLS									(pcode *p);
	bool fLOCATE							(pcode *p);

	bool fCAST									(pcode *p, int *nReturnExpressionType, bool bReturn);
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

	bool fABS									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCOLOR								(pcode *p);
	bool fKBASICDIR						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fKILL								(pcode *p);
	bool fCINT								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSTRING							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fPRINT								(pcode *p);
	bool fCLNG								(pcode *p, int *nReturnExpressionType, bool bReturn);

	bool fCHOOSE							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSWITCH							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fIIF									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCVERR								(pcode *p, int *nReturnExpressionType, bool bReturn);

	bool fCSNG								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCDBL								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCCUR								(pcode *p, int *nReturnExpressionType, bool bReturn);

  bool fCBOOL								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCBYTE								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCDATE								(pcode *p, int *nReturnExpressionType, bool bReturn);

	bool fSPACE								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fINSTR								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);

	bool fDAYOFWEEK								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fDAYOFYEAR								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fDAYSINMONTH								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fDAYSINYEAR								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fWEEKNUMBER								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fISLEAPYEAR								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fDIFFDAY								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fDIFFSECONDS								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fISDATEVALID								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fISTIMEVALID								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fISDATETIMEVALID								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);

	bool fOPEN								(pcode *p);
//	bool fREAD								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fWRITE								(pcode *p);
	bool fCLOSE								(pcode *p);
	bool fSEEK								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fRESET								(pcode *p);
	bool fEOF									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCHDIR								(pcode *p);
	bool fRMDIR								(pcode *p);
	bool fMKDIR								(pcode *p);
	bool fNAME								(pcode *p);
	bool fFILES								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fLOF									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fINPUT								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fLINEINPUT						(pcode *p);
	bool fLEN									(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fLN									(pcode *p, int *nReturnExpressionType, bool bReturn);


  bool fCOMPARE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fCONTAINS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fCOUNT(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fENDSWITH(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fSTARTSWITH(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fLEFTJUSTIFIED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fRIGHTJUSTIFIED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fSECTION(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fSIMPLIFIED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fTRIMMED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fREVERSED(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fUNICODE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);

  bool fREADBINARY(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fWRITEBINARY(pcode *p, bool bObjectFake = false);
  bool fSEEKBINARY(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);

  //bool fADDDATE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fADDDAYS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fADDMONTHS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fADDYEARS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  //bool fSUBDATE(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fSUBDAYS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fSUBMONTHS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fSUBYEARS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  //bool fADDTIME(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fADDHOURS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fADDMINUTES(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fADDSECONDS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  //bool fSUBTIME(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fSUBHOURS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fSUBMINUTES(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
  bool fSUBSECONDS(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);

  bool fPREPEND(pcode *p, bool bObjectFake = false);
  bool fAPPEND(pcode *p, bool bObjectFake = false);
  bool fREMOVE(pcode *p, bool bObjectFake = false);
  bool fTRUNCATE(pcode *p, bool bObjectFake = false);
  bool fINSERT(pcode *p, bool bObjectFake = false);
  bool fFILL(pcode *p, bool bObjectFake = false);

	bool fENCODE							(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fDECODE							(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);


	bool fUTF8								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fUTF16								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);

	bool fVAL									(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fASC									(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fLEFT								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fRIGHT								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
//	bool fMID								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSTR									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCHR									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fLCASE								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fUCASE								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fBEEP								(pcode *p);
	bool fSLEEP								(pcode *p);
	bool fDOEVENTS						(pcode *p);

	bool fPRINTSCREEN	  			(pcode *p);

  bool fCHDRIVE			  			(pcode *p);
	bool fFILECOPY						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSETATTR				  		(pcode *p);

	bool fHEX									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSTRCOMP							(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fBIN									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fRAD									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fATN									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCOS									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSIN									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fEXP									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fLOG									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSGN									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fFIX									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fINT									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSQR									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fTAN									(pcode *p, int *nReturnExpressionType, bool bReturn);
	//bool fFACT								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fLOGB								(pcode *p, int *nReturnExpressionType, bool bReturn);
	//bool fFRAC								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fERR 								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fERL 								(pcode *p, int *nReturnExpressionType, bool bReturn);
	//bool fHYPOT								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fMAX									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fMIN									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSEC									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fLTRIM								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fRTRIM								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fTRIM								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fSHELL								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fRND									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fINKEY								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fOCT									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fMID									(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fSCREEN							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fPOS									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCSRLIN							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fDATE								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fTIME								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fVARTYPE							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fTYPEOF							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fNZ									(pcode *p, int *nReturnExpressionType, bool bReturn);
	//bool fPOINT								(pcode *p, int *nReturnExpressionType, bool bReturn);

	//bool fCIRCLE							(pcode *p);
//	bool fLINE							  (pcode *p);
	//bool fDRAW							  (pcode *p);
	//bool fPAINT							  (pcode *p);
	//bool fPCOPY							  (pcode *p);
	//bool fPMAP							  (pcode *p);
	//bool fPRESET							(pcode *p);
	//bool fPSET							  (pcode *p);
	//bool fVIEW							  (pcode *p);
	//bool fVIEWPRINT						(pcode *p);
	//bool fWINDOW							(pcode *p);
	//bool fWIDTH							  (pcode *p);

	bool fCOMMAND							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fINSTREV							(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fREPLACE							(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fROUND								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fSPLIT								(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fSTRREVERSE					(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);

	bool fISDATE							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISEMPTY							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISNULL							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISNUMERIC						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISMISSING						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISOBJECT						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fISCURRENCY						(pcode *p, int *nReturnExpressionType, bool bReturn);
  
	bool fARRAY								(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fCURDIR							(pcode *p, int *nReturnExpressionType, bool bReturn);
	//bool fFIELD 							(pcode *p);

	bool fSPC   							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fDATEADD							(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fDATEDIFF						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fDATEPART						(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fDATESERIAL					(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fDATEVALUE						(pcode *p, int *nReturnExpressionType, bool bReturn);

	bool fDAY									(pcode *p, int *nReturnExpressionType, bool bReturn, bool bObjectFake = false);
	bool fDIR									(pcode *p, int *nReturnExpressionType, bool bReturn);
	bool fMACRO								(pcode *p, int *nReturnExpressionType, bool bReturn);
  //bool fCOLLECTION          (pcode *p, int nVar, t_scope scope, int *nReturnExpressionType, bool bReturn);


	bool fDECLARE							();

	//bool fMODULE							(pcode *pp, pcode *p, const char **acIdentifier, int *nReturnExpressionType, bool bReturn);
	bool fMODULE_BODY					();
	bool fDATA								(pcode *p);
	bool fRESTORE							(pcode *p);
	bool fREAD								(pcode *p);

	bool fDEFINT							();
	bool fDEFLNG							();
	bool fDEFSNG							();
	bool fDEFDBL							();
	bool fDEFSTR							();
	bool fDEFCUR							();
	bool fDEFVAR							();
	bool fDEFBOOL							();
	bool fDEFBYTE							();
	bool fDEFDATE							();
	bool fDEFOBJ							();
	bool fDEF									(int nDefType);

//	bool fINC		    					(pcode *p);
	//bool fINC_	    					(pcode *p);
//	bool fDEC   							(pcode *p);
	//bool fDEC_   							(pcode *p);

//  bool fSHL   							(pcode *p);
//	bool fSHR   							(pcode *p);
  //bool fSHL_   							(pcode *p);
	//bool fSHR_   							(pcode *p);

	bool fFACTOR							(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding);
	bool fEXPONENT						(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding);
	bool fTERM								(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding);
	bool fSIMPLEEXPRESSION		(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding);
	bool fSHIFT           		(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding);
	bool fCOMPARISION					(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding);
	bool fAND									(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding);
	bool fOR									(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding);
	bool fANDALSO							(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding);
	bool fORELSE							(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum = false, bool bBinding = false);

  bool fENUM_EXPRESSION		    (pcode *p, int *nReturnExpressionType);
  bool fCONST_EXPRESSION		    (pcode *p);
	bool fCONST_NUMERIC_EXPRESSION(pcode *p);
	bool fCONST_LONG_EXPRESSION		(pcode *p);

  bool fEXPRESSION					(pcode *p);
	bool fEXPRESSION					(pcode *p, int *nReturnExpressionType);
	bool fEXPRESSION					(pcode *p, int *nReturnExpressionType, t_arrayVariable *a);
	bool fEXPRESSION					(pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding = false);
	bool fEXPRESSION					(pcode *pp, pcode *p, int *nReturnExpressionType, t_arrayVariable *a, bool bConstExpression, bool bWithoutBuiltin, bool bEnum, bool bBinding = false);

	bool fCONST_EXPRESSION		    (pcode *p, int *nReturnExpressionType);
	bool fCONST_NUMERIC_EXPRESSION(pcode *p, int *nReturnExpressionType);
	bool fCONST_LONG_EXPRESSION		(pcode *p, int *nReturnExpressionType);

	bool fEXPRESSION2					(pcode *p, int nType, bool bWithoutBuiltin = false, bool bBinding = false);
	bool fEXPRESSION3					(pcode *p, int nMustType, bool bWithoutBuiltin = false);
	bool fDOUBLE_EXPRESSION		(pcode *p);
	bool fINTEGER_EXPRESSION	(pcode *p);
	bool fSTRING_EXPRESSION	(pcode *p, bool bWithoutBuiltin = false);
	bool fQSTRING_EXPRESSION	(pcode *p, bool bWithoutBuiltin = false);
	bool fCSTRING_EXPRESSION	(pcode *p, bool bWithoutBuiltin = false);
	bool fBOOLEAN_EXPRESSION	(pcode *p);
	bool fLONG_EXPRESSION			(pcode *p);
	bool fSINGLE_EXPRESSION		(pcode *p);
	bool fBYTE_EXPRESSION			(pcode *p);
	bool fSHORT_EXPRESSION			(pcode *p);
	bool fVARIANT_EXPRESSION	(pcode *p);
	bool fDATE_EXPRESSION			(pcode *p);
	bool fCURRENCY_EXPRESSION	(pcode *p);
	bool fOBJECT_EXPRESSION	(pcode *p, int *nExpressionType);
	bool fNUMERIC_EXPRESSION		(pcode *p);
	//bool fCSTRING_EXPRESSION		(pcode *p);


  bool fBOOLEAN_REFERENCE(pcode *p);
  bool fBYTE_REFERENCE(pcode *p);
  bool fSTRING_REFERENCE(pcode *p, int *nType);
  bool fQSTRING_REFERENCE(pcode *p, int *nType);
  bool fCSTRING_REFERENCE(pcode *p, int *nType);
  bool fCSTRING_REFERENCE(pcode *p);
  bool fINTEGER_REFERENCE(pcode *p);
  bool fSHORT_REFERENCE(pcode *p);
  bool fLONG_REFERENCE(pcode *p);
  bool fSINGLE_REFERENCE(pcode *p);
  bool fDOUBLE_REFERENCE(pcode *p);
  /*
  bool fINT16_REFERENCE(pcode *p);
  bool fINT32_REFERENCE(pcode *p);
  bool fINT64_REFERENCE(pcode *p);
  bool fUINT16_REFERENCE(pcode *p);
  bool fUINT32_REFERENCE(pcode *p);
  bool fUINT64_REFERENCE(pcode *p);
  */
  bool fDATE_REFERENCE(pcode *p);
  bool fCURRENCY_REFERENCE(pcode *p);
 // bool fCHARACTER_REFERENCE(pcode *p);
  bool fVARIANT_REFERENCE(pcode *p);
  bool fREFERENCE(pcode *p, int nReferenceType, int *nType = 0);
/*
  bool fBOOLEAN_POINTER(pcode *p);
  bool fBYTE_POINTER(pcode *p);
  bool fQSTRING_POINTER(pcode *p);
  bool fCSTRING_POINTER(pcode *p);
  bool fINTEGER_POINTER(pcode *p);
  bool fLONG_POINTER(pcode *p);
  bool fSINGLE_POINTER(pcode *p);
  bool fDOUBLE_POINTER(pcode *p);*/
  /*
  bool fINT16_POINTER(pcode *p);
  bool fINT32_POINTER(pcode *p);
  bool fINT64_POINTER(pcode *p);
  bool fUINT16_POINTER(pcode *p);
  bool fUINT32_POINTER(pcode *p);
  bool fUINT64_POINTER(pcode *p);*/

  bool fADDRESSOF(pcode *p, bool bParseTermAddressOf = true);
  bool fPOINTER(pcode *p, int nReferenceType);

	bool binding_fVARIABLE_OR_CLASSNAME(pcode *p, int *nType);
	bool fVARIABLE_OR_CLASSNAME(pcode *p, int *nType);
  bool fVARIABLE_DIM(pcode *pp, pcode *p, int nVar, t_scope scope, 
                    int nIdType, int nType, bool bImplicitDIM, bool bReturn, 
                    int *nReturnExpressionType, bool bReference,
                    bool bAssignment);

  bool existStaticVar(const char *acClass, const char *acIdentifier, 
                           int *nVar, int *nIdType, int *nType, t_array *a,
                           t_scope *scope, int *nAccessScopeId, int *nAccessScope, int *nLStringLen);

  bool existVar(const char *acClass, const char *acIdentifier, 
                           int *nVar, int *nIdType, int *nType, t_array *a,
                           t_scope *scope, int *nAccessScopeId, int *nAccessScope, int *nLStringLen);

  bool existPropertyGet(const char *acClass, const char *acIdentifier, 
                           int *nVar, int *nIdType, int *nType, t_array *a,
                           t_scope *scope, int *nAccessScopeId, int *nAccessScope, int *nLStringLen);

  bool existPropertySet(const char *acClass, const char *acIdentifier, 
                           int *nVar, int *nIdType, int *nType, t_array *a,
                           t_scope *scope, int *nAccessScopeId, int *nAccessScope, int *nLStringLen);

  //bool fVARIABLE(pcode *p, int *nVar, bool *bLocalScope);
  bool fENUM(pcode *p, int *nEnumId, int *nElement);
  bool fCONST(pcode *p, int *nConst, t_scope *scope);
  bool fCONST(pcode *p, int *nReturnExpressionType);

	bool fENUM(pcode *p, int *nReturnExpressionType);

  bool fSELECTOR_TYPE				(
                            pcode *p, 
                            int nParentVar, 
                            int nParentIdType, 
                            int nParentType, 
                            const char *acIdentifier, 
                            int *nIdType, 
                            int *nType, 
                            t_arrayVariable *a3, 
                            bool bAssignment,   
                            bool *bSizeAll,                                                           
                            int *nLStringLen,
                            bool bClassVar,
                            t_scope scope,
                            bool bARRAY2,
                            bool bTestProperty
                          );

	bool fVARIABLE(pcode *pp, pcode *p, int *nReturnExpressionType);
	bool fVARIABLE(pcode *pp, pcode *p, int *nReturnExpressionType, t_scope *scope);
	bool fVARIABLE(pcode *pp, pcode *p, int *nReturnExpressionType, t_scope *scope, 
               t_arrayVariable *a);

	bool fARGUMENT(pcode *p, int *nVar, t_scope *scope, int *nType);
	bool fVARIABLE(pcode *p, int *nVar, t_scope *scope, int *nType);
	bool fVARIABLE_REDIM(pcode *p, int *nVar, t_scope *scope);
	bool fVARIABLE_DECLARED(pcode *p, int *nVar, t_scope *scope, int *nType);  

	bool fVARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, 
                t_arrayVariable *a, bool *bReference, bool *bProperty, bool bTestProperty);

	bool fVARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, 
                t_arrayVariable *a);

	bool fVARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, 
                bool *bImplicitDIM, bool bTestImplicitDim, t_arrayVariable *a,
                bool *bSizeAll, int *nLStringLen, 
                bool *bReference, bool *bProperty, bool bTestProperty,                 
                bool bClassVar = false, int nClassId = 0, 
                bool bArgumentOnly = false, bool bAssignment = false, 
                bool bRedim = false);

  bool fVARIABLE_ASSIGNMENT(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, 
                          bool *bImplicitDIM, bool bTestImplicitDim, t_arrayVariable *a,
                          bool *bSizeAll, int *nLStringLen, bool *bReference, bool *bProperty, bool bTestProperty                 
                          );
  
  bool fPROPERTY_ASSIGNMENT(pcode *p, int *nClassId, int *nId, bool *binding_fPROPERTY_ASSIGNMENT);
  
  bool fPROPERTY(pcode *p, int *nReturnExpressionType);

  bool fTYPE_Class(pcode *p, const char **acType, bool bNew = false);
	bool fTYPE_Type(pcode *p, const char **acType, bool bNew = false);
	bool fTYPE_Enum(pcode *p, const char **acType, bool bNew = false);

	bool fCLASS_STATICMETHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn = true);
	bool fCLASS_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn = true);


  bool fBOOLEAN_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);
	
  bool fSTRING_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);
	
  bool fBYTE_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);
  bool fSHORT_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);
	bool fINTEGER_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);
	bool fLONG_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);
	
  bool fSINGLE_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);
	bool fDOUBLE_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);

  bool fVARIANT_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);
	
  bool fOBJECT_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);

  bool fCURRENCY_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);
	bool fDATE_VARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, t_arrayVariable *a3);


	bool parseInfo(pcode *p, const char *acParseInfo, bool bPos = false, int nPos = -1);

	bool syntaxError(int nProductionId, const char *acSyntaxError, int nErrorId = -1);
	bool semanticError(int nProductionId, const char *acSemanticError, int nErrorId = -1); // int _nCurrentLine = -1, int _nCurrentRow = -1);
	bool internalError(const char *acInternalError);//, int _nCurrentLine = -1, int _nCurrentRow = -1);

  //bool errorRecovering();

	bool nextToken(bool b = true);

  bool stopAtLine(int nLine, const char *acFile = "");

  bool cleanUpLabels();

	bool registerAll();
	bool registerAll2();

	bool registerAllTypes();
	bool registerAllEnums();
//	bool registerAllInterfaces();

	bool appendAllModulesStatic();
	bool appendAllModules(pcode *myPcodeSubRegister); // append the pcode of all subs

	bool appendAllClasses(pcode *myPcodeSubRegister); // append the pcode of all subs
	bool appendAllClassesStatic();

  bool appendAllProjectFiles(pcode *myPcodeSubRegister);

  bool appendAllBreakpoints(pcode *myPcodeSubRegister);

	bool isSub(char *acModule, char *acIdentifier);

	bool gotoNextStatement();


bool defaultFunctionReturnExpression(pcode *p, int nReturnExpressionType);
bool autoCallParentConstructorDestructor(pcode *p, bool bConstructor, bool bDestructor, int nId, memory_sub *s);

bool nextTokenIsKeyword();
bool nextTokenIsOperator();
bool nextTokenIsSymbol();

bool catchFinally(pcode *p, bool bTry);

int registerClassVar(const char *acClass, const char *name, int _type, t_array *a, bool bStatic, int nScope, int nLStringLen);
int registerClassStaticVar(const char *acClass, const char *name, int _type, t_array *a, bool bStatic, int nScope, int nLStringLen);
int registerClassLocalPropertyGetConst(const char *acClass, const char *acSub, int nBlockNo, const char *name);
int registerClassLocalPropertySetConst(const char *acClass, const char *acSub, int nBlockNo, const char *name);
int registerClassLocalConst(const char *acClass, const char *acSub, int nBlockNo, const char *name);
int registerClassLocalVar(const char *acClass, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck = false);
int registerClassLocalPropertyGetVar(const char *acClass, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck = false);
int registerClassLocalPropertySetVar(const char *acClass, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck = false);
int registerClassConst(const char *acClass, const char *name, int nScope);

int findClassConst(const char *acClass, const char *name);
int findClassStaticVar(const char *acClass, const char *name);
int findClassVar(const char *acClass, const char *name);
int findClassLocalVar(const char *acClass, const char *acSub, int nBlockNo, const char *name);


int registerModuleVar(const char *acModule, const char *name, int _type, t_array *a, int nScope, int nLStringLen);
int registerModuleLocalVar(const char *acModule, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck = false);
//int registerModuleLocalPropertyGetVar(const char *acModule, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen);
//int registerModuleLocalPropertySetVar(const char *acModule, const char *acSub, int nBlockNo, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen);
int registerModuleLocalConst(const char *acModule, const char *acSub, int nBlockNo, const char *name);
int registerModuleConst(const char *acModule, const char *name, int nScope);

bool registerConstPublic(const char *acName, int nValue);
bool registerConstPublic(const char *acName, const char *s);

int findModuleConst(const char *acModule, const char *name);
int findModuleVar(const char *acModule, const char *name);
int findModulePublicVar(const char *acModule, const char *name);
int findModuleLocalVar(const char *acModule, const char *acSub, int nBlockNo, const char *name);
int findModuleLocalConst(const char *acModule, const char *acSub, const char *name);


int registerVar(const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck = false);
int registerGlobalVar(const char *name, int _type, t_array *a, int nScope, int nLStringLen);
int registerLocalVar   (const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen, bool bNoNameCheck = false);
int registerClassStaticCodeVar   (const char *name, int _type, t_array *a, bool bByVal, bool bStatic, int nScope, int nLStringLen);


int findLocalVar(const char *acModule, const char *acSub, int nBlockNo, const char *name);

/*
int registerVar(const char *acModule, const char *acSub, const char *name, int _type, t_array *a, bool bByVal, bool bStatic, bool bPrivate);
int typeVar(int id);
bool isByVal(int id);
*/

int nExpectedType;

t_array *arrayVar(int id);
int arrayType(int id);

/*
int registerConst(const char *acModule, const char *acSub, const char *name, bool bPublic, int _type);
int findConst(const char *acModule, const char *acSub, const char *name);
*/
int findClass(const char *acNam);


//int registerEntity(const char *name, int id);
int registerTypePublic(const char *name, int id);
int registerType(const char *name, int nScope);
int registerType(const char *name, int nScope, int id);
bool registerTypeElement	(int nId, const char *acElementName, const char *acElementType, int nElementSize, t_array *a);
int findType(const char *acModule, const char *name);
int findType(const char *name);

void registerCatch(int nId2, memory_sub *s2, int nSubId2, pcode *p, int nType);

//int registerEnum(const char *name, int nScope);
int registerEnum(const char *name, int nScope);
int findEnum(const char *acModule, const char *name);
				
//int registerStructure(const char *name, int nScope);
//int registerStructure(const char *name, int nScope, int id);
//int findStructure(const char *acModule, const char *name);
				

int 		registerClass		(
 const char *acName, 
 pcode *myPcode, 
 pcode *myClassStaticPcode,  
 const char *acExtendName, 
 bool bIsAbstract 
 );

int registerModule( const char *acName);//, pcode *myPcode)

int registerModuleSub (
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
		);

//int registerEntity(const char *name, int nScope, int nType);
//int findEntity(const char *acModule, const char *name);
//int findEntity(const char *name);

/*
int registerLabel(const char *name);
const char *findLabel(int id);
int findLabel(const char *name);
*/
bool isScopeClass();
bool isScopeClassStaticCode();
bool isScopeClassLocalStatic();
bool isScopeClassLocalInstance();
bool isScopeClassPropertySet();
bool isScopeClassPropertyGet();


bool isScopeModule();
bool isScopeModuleLocal();
bool isScopeModuleLocalStatic();

bool isScopeGlobal(); // class global vars/consts, module global vars/consts
bool isScopeDefaultGlobal();
bool isScopeLocal();


bool setScopeModule(const char *acModule, const char *acSub = "", const char *acRealSub = "");
bool setScopeClass(const char *acParentClass, const char *acClass, const char *acSub = "", const char *acRealSub = "");
bool setScopeClassStatic(bool b);
bool setScopeDefaultGlobal();

const char *getScope	();
const char *getClass	();
const char *getParentClass	();
const char *getModule	();
const char *getSub			();
const char *getRealSub			();
const char *getMethod			();
const char *getRealMethod			();
bool isSubVarStatic			();
int         getBlockNo	();


//bool getVar(const char *acIdentifier, int *nId, bool *bLocalScope, int *nType);

bool pushParam(pcode *p, int nSubId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, bool bClassMethod, int nClassId, int nParamId, bool *bEXPRESSION, bool *bISMISSING, int *nReferenceType);
bool popParam(pcode *p, int nSubId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, bool bClassMethod, int nClassId, int nParamId, bool bEXPRESSION, bool bISMISSING, int nReferenceType);

XString sCurrentLib; // used for Inherits DLL("kernel32.dll") e.g.
XString sCurrentSub;
XString sCurrentRealSub; // real name of sub
XString sCurrentClass;
XString sCurrentModule;
bool bCurrentClassStatic;
int nCurrentBlockNo;
bool bSubVarStatic;

//codeInsight myCodeInsight;

void addDependency(const char *acFile, const char *acDependency);
void addDependencyGlobalVar(const char *acFile, int nId);
//QMap<XString, QPtrList> dependency3;

// defaults
const char *acBaseClassName; // standard class if no parent class explicitly declared
t_pcode nDefaultType; // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT


token *getToken();

const char *getCurrentFile();
const char *getCurrentEnum();
int getCurrentLine();
int getCurrentRow();

bool setCurrentEnum(const char *f);
bool setCurrentFile(const char *f);
bool setCurrentLine(int n);
bool setCurrentRow(int n);

const char *acCurrentFile;
const char *acCurrentEnum;

cache *my_cache;

bool bIsLocalStatic;


bool classExists(const char *acName);
bool moduleExists(const char *acName);


bool findSub			(const char *acMod, const char *acNa, const char **acModule, const char **acName, const char **acSuffix, const char **acReturnType, int *nReturnSize, pcode **myPcode, bool *builtin);

token *myToken;

bool appendAllStringLiterals();
int registerStringLiteral(const char *name, bool bBuiltin = false);
int findStringLiteral(const char *name);



void setVERYOLDBASIC(); // qbasic
void setOLDBASIC(); // vb6
void setKBASIC();

bool bVeryOldBasic; // set declare n/off, qbasic allows commands outside of subs/functions
bool bOldBasic; // set declare on/off, Visual Basic has old style programming like "on error goto" ...
bool bKBasic;

void setExplicit(bool b);

t_scope getScopeCode();


pcode *pDim; // needed for rollback

pcode *myPcode;
pcode *myPcodeDefault; // used for the default.kbasic file
pcode *myPcodeDefault2; // used for the default2.kbasic file

public:
pcode *myPcodeAll;
pcode *myPcodeData;
private:
XIntMap pcs;

exception myException;

bool bScopeClassStatic;
bool bScopeClassPropertySet;
bool bScopeClassPropertyGet;


bool bUseCache;






memory_label *myMemory_label;

parser_classMethod *myParser_classMethod;


t_with *with_pos_list[parser__MAX_WITH];
int with_pos_list_POS;

bool bGLOBAL_EOL;
bool bGLOBAL_SYM_UL;


	

memory_label *myExitFor;
memory_label *myExitDo;
memory_label *myIterateDo;
memory_label *myIterateFor;


bool compatibleType(int n, int n2, bool bRetrySwapped = true);



bool bExplicit; // set declare explicit on/off
int nBaseOfArray; // arrays start with 1 if not explictly declared or OPTION BASE
bool bOptionCompareBinary;


int nCurrentRow;
int nCurrentLine;

int nLastStatementPcode;

bool bProducePcode;

t_pcode nDEF[parser__MAX_nDEF]; // for DEFINT, DEFLNG, DEFSNG, DEFDBL, DEFSTR...  pcode__INTEGER, pcode__VARIANT
               
bool bParserPhase0;
bool bParserPhase1;
bool bParserPhase2;

bool bSilent;
bool bDebug;
//bool bDisableStringAutoCast;


int nDataCount;

int nFORNEXT;

textbuffer *myTextbuffer;



// *** used for WITH
t_with2 with;
// ***

// needed for rollback in fINPUT  -> undeclare variable 
void prepareRollbackVariable();
bool rollbackVariable();

int nLastVarId;
int nLastVarScope;
int nLastModuleId;
int nLastSubId;

int nIfStatement;


	// binding

  bool binding_fPROPERTY_ASSIGNMENT(pcode *p, int *nClassId, int *nId, int *nReturnType);
  bool binding_fPROPERTY_ASSIGNMENT2(pcode *p, int nClassId, const char *acMethod, int *nMethodId, int *nReturnType);
  
  bool binding_fSTATICPROPERTY_ASSIGNMENT(pcode *p, int *nClassId, int *nId, int *nReturnType);
  bool binding_fSTATICPROPERTY_ASSIGNMENT2(pcode *p, int nClassId, const char *acMethod, int *nMethodId, int *nReturnType);
  
  bool binding_fPROPERTY(pcode *p, int *nReturnExpressionType);
  bool binding_fPROPERTY2(pcode *p, int nClassId, const char *acMethod, int *nMethodId, int *nReturnType);

  bool binding_fSTATICPROPERTY(pcode *p, int *nReturnExpressionType, int *nId);
  bool binding_fSTATICPROPERTY2(pcode *p, int nClassId, const char *acMethod, int *nMethodId, int *nReturnType);

  bool binding_fSELECTOR_CLASS_PROPERTY	(pcode *p, int nClassId,  
                          const char *acIdentifier, bool bAssignment
                          );
/*
	bool binding_fCONNECT(pcode *p);
	bool binding_fDISCONNECT(pcode *p);

  bool binding_fSIGNAL(pcode *p, int nType);
	bool binding_fSLOT(pcode *p, int nType);
	*/

	bool binding_fCLASS_ENUM(pcode *p, int *nReturnExpressionType, bool bReturn = true);
	bool binding_fCLASS_ENUM(pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, const char *acEnum);

	bool binding_fCLASS_CONST(pcode *p, int *nReturnExpressionType, bool bReturn = true);
	bool binding_fCLASS_CONST(pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, const char *acMethod);

  bool binding_fCLASS_STATICMETHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn = true);
	bool binding_fCLASS_STATICMETHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, const char *acMethod);
	
  bool binding_fFUNCTION_CALL(pcode *p, int *nReturnExpressionType, bool bReturn = true);

	bool binding_fCLASS_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn = true, bool bPrintError = true, bool bInnerCall = false);
	bool binding_fCLASS_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, const char *acMethod, bool bPrintError, bool bSignalSlotDefinition = false);

	//bool binding_fCLASS_OPERATOR(pcode *p, int *nReturnExpressionType, int nClassId, int nOperatorType);
	//bool binding_fFUNCTION_OPERATOR(pcode *p, int *nReturnExpressionType);
	
  bool binding_fClassMethod_default(pcode *p, parser_parameter *pp);
	bool binding_fTYPE_Class(pcode *p, const char **acType, bool bNew = false);

	bool binding_createMapClass();
	bool binding_createMapMethod();
  bool registerBindingTypes();

  bool registerBuiltinConsts();
  bool registerBuiltinTypes();
  bool registerBuiltinClasses();  

bool isLastToken()
{
	return peekToken() == token__KB_EOF/* || peekToken() == token__KB_EOF2*/;
}

// interface for token.cpp and doing some special test for _
bool peekTokens(int n, int n2)
{
  if (peekToken() == n) if (peekToken(1) == n2) return true; 
  return false;
}

t_token peekToken(int nTokenPos = 0)
{
  if (nTokenPos == 0){
    static int nPos = 0;
    register int nPos2 = 0;
	  static t_token n = 0;

    nPos2 = getTokenPos();

	  while ((n = myToken->peekToken( getTokenPos() )) == token__REM_MULTILINE){
		  nextToken();
      nPos2 = getTokenPos();
	  }

	  while ((n = myToken->peekToken( getTokenPos() )) == token__REM_DOCUMENTATION){
		  nextToken();
      nPos2 = getTokenPos();
	  }

	  while ((n = myToken->peekToken( getTokenPos() )) == token__SYM_TILDE){
		  nextToken();
      nPos2 = getTokenPos();
	  }

	  while ((n = myToken->peekToken( getTokenPos() )) == token__SYM_UL){
      bGLOBAL_SYM_UL = true;
		  nextToken();
      nPos2 = getTokenPos();
	  }

    nPos = nPos2;//getTokenPos();

    setCurrentRow(myToken->getRowStart());

	  return n;
  } else {
    int m = nTokenPos;
    _TBEGIN_
    for (int i = 0; i < m; i++){
      nextToken();
    }
    
    int y = peekToken();
    _TEND2_
    return y;
    
  }

  return 0;
}


// exactly the same as peekToken, but without setting position, used for WITH...END WITH
t_token peekToken2()
{
	static t_token n = 0;

	while ((n = myToken->peekToken()) == token__REM_MULTILINE){
		nextToken(false);
	}

	while ((n = myToken->peekToken()) == token__REM_DOCUMENTATION){
		nextToken(false);
	}

	while ((n = myToken->peekToken()) == token__SYM_UL){
    bGLOBAL_SYM_UL = true;
		nextToken(false);
	}

  setCurrentRow(myToken->getRowStart());

	return n;
}

bool parseTerms(int nTerm, int nTerm2)
{
  _TBEGIN_
  if (parseTerm(nTerm)) if (parseTerm(nTerm2)) return true;
  _TEND_
  return false;
}

// parse and goto next token
bool parseTerm(int nTerm)
{
	if (proceedParse()){

    register int n = peekToken();

   /*
  	if (n == token__TYPE){
  		n = token__TYPE;  		
  	}*/
  	if (n == nTerm){
  		nextToken();
  		return true;
  	}

	}

	return false;
}

bool peekTerm(int nTerm)
{
	if (proceedParse()){

    register int n = peekToken();

  	if (n == nTerm){
  		return true;
  	}

	}

	return false;
}

bool peekTerm2(int nTerm) // used for peekEOLREM
{
	//if (proceedParse())
  {

    register int n = peekToken();

  	if (n == nTerm){
  		return true;
  	}

	}

	return false;
}

/* *
[EXPLANATION]
NAME: default type
DESC:
SEEALSO:
*/
// first character of identifier shows the identifier type using the DEF...
int defaultType(const char *acIdentifier) // for DEFINT, DEFLNG, DEFSNG, DEFDBL, DEFSTR ...
{
  register char c = 0;

  if (acIdentifier[0] == '_'){
    c = toupper('A') - 'A';
  } else if (acIdentifier[0] == '$'){
    c = toupper('A') - 'A';
  } else {
    c = toupper(acIdentifier[0]) - 'A';
  }

  if (c >= parser__MAX_nDEF || c < 0){ internalError("setting DEFINT, DEFLNG, DEFSNG, DEFDBL, DEFSTR ... out of boundery "); return 0; }
  
  if (nDEF[c] == nDefaultType){
    if (isOLDBASIC()) return pcode__VARIANT; // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT   
    if (isVERYOLDBASIC()) return pcode__DOUBLE; // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT   
  }
  return nDEF[c];
}
// if something went wrong or we are finished, it returns false; else true
bool proceedParse()
{
	return bNoError && bParseToken && !isLastToken();
}

bool peekfCOL(bool bPos = true)
{
	//_TBEGIN_

	//register bool bTerm_COL = false;

	if (/*bTerm_COL = */peekTerm(token__SYM_COLON)){
		//return bTerm_COL;
    return true;
	}
  return false;

	//_TEND_
}

bool peekfEOL2(bool bPos = true)
{
	//_TBEGIN_

	//register bool bTerm_EOL = false;

	if (/*bTerm_EOL = */peekTerm(token__MSC_EOL)){
		//return bTerm_EOL;
    return true;
	} else if (/*bTerm_EOL = */isLastToken()){
    return true;
		//return bTerm_EOL;
	}

  return false;
	//_TEND_
}

bool peekfEOL(bool bPos = true)
{
	//_TBEGIN_

	if (peekfEOL2(bPos)) return true;
	else if (peekfCOL(bPos)) return true;

  return false;
	//_TEND_
}

bool peekfREM()
{
	//_TBEGIN_

	//register bool bTerm_REM = false;

  if ((/*bTerm_REM = */peekTerm(token__REM)) || (/*bTerm_REM = */peekTerm(token__REM_SHORT))){
		return true;
	}

  return false;
	//_TEND_
}

bool setTokenPos(int nPos)
{
  myToken->setPos(nPos);

  return true;
}

int getTokenPos()
{
  if (bParserPhase2 && with.WithToken == token__MSC_EOL && with_pos_list_POS > -1){

    if (peekToken2() == token__SYM_DOT){
      t_with *t;
      
      t = with_pos_list[0];

      with.nWithOldPos = myToken->getPos();

      with.nWithCurrentLine = getCurrentLine();
      with.nWithCurrentRow = getCurrentRow();    

      with.WithToken = 0;
      with.With = t;   
      myToken->setPos(t->from);
      return t->from;
    }
 
  }

  if (bParserPhase2 && with.With != 0){

    // drüber gelesen?
    if (myToken->getPos() >= with.With->to){

      // get current item
      
      int n = 0;
      t_with *t = with_pos_list[n];
      while (t->from != with.With->from){
        t = with_pos_list[++n];
        if (n > with_pos_list_POS){
          internalError("with list outside bounds"); return false;
        }
      }

      t_with *t2 = 0;
      if (++n <= with_pos_list_POS){
        t2 = with_pos_list[n];
      }

      // nächstes with
      if (t != t2 && t2 != 0){

        with.With = t2;   
        myToken->setPos(t2->from);
        return t2->from;

        // normal wieder herstellen
      } else {
//        t2 = with_pos_list[--n];

        myToken->setPos(with.nWithOldPos);
        
        setCurrentLine(with.nWithCurrentLine);
        setCurrentRow(with.nWithCurrentRow);   

        //if (!bWithMeMethodCall)
       // {
          with.With = 0;        
       // }
        
      }

    }
  }

  return myToken->getPos();
}

//bool bWithMeMethodCall;

bool fBUILTIN_SUB(pcode *p)
{
	_BEGIN_

	if (!proceedParse()) _END_ 

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fBUILTIN", getCurrentLine() - 1));
  }

  switch(peekToken()){

    case token__PREPEND: if (fPREPEND(p)) _DONE_; break;
    case token__APPEND: if (fAPPEND(p)) _DONE_; break;
    case token__REMOVE: if (fREMOVE(p)) _DONE_; break;
    case token__TRUNCATE: if (fTRUNCATE(p)) _DONE_; break;
    case token__INSERT: if (fINSERT(p)) _DONE_; break;
    case token__FILL: if (fFILL(p)) _DONE_; break;

    case token__BEEP: if (fBEEP(p)) _DONE_; break;
    case token__CHDRIVE: if (fCHDRIVE(p)) _DONE_; break;
    case token__CLS: if (fCLS(p)) _DONE_; break;
    case token__COLOR: if (fCOLOR(p)) _DONE_; break;
    case token__DOEVENTS: if (fDOEVENTS(p)) _DONE_; break;
    case token__LOCATE: if (fLOCATE(p)) _DONE_; break;
    case token__MID: if (fMID2(p)) _DONE_; break;
    case token__NAME: if (fNAME(p)) _DONE_; break;

    case token__PRINT: 
    case token__SYM_QM:       
    case token__ECHO: 
    case token__LOG: 
      if (fPRINT(p)) _DONE_; break;
    
    case token__PRINTSCREEN: 
      if (fPRINTSCREEN(p)) _DONE_; break;

    case token__RANDOMIZE: if (fRANDOMIZE(p)) _DONE_; break;
    case token__RESET: if (fRESET(p)) _DONE_; break;
    case token__SETATTR: if (fSETATTR(p)) _DONE_; break;
    case token__SLEEP: if (fSLEEP(p)) _DONE_; break;
    case token__CHDIR: if (fCHDIR(p)) _DONE_; break;
    case token__CLOSE: if (fCLOSE(p)) _DONE_; break;
    case token__ERROR_: if (fERROR(p)) _DONE_; break;
    case token__ERROR: if (fERROR(p)) _DONE_; break;
//    case token__FIELD: if (fFIELD(p)) _DONE_; break;
    case token__GET: if (fGET(p)) _DONE_; break;
    case token__PUT: if (fPUT(p)) _DONE_; break;
    case token__PEEK: if (fPEEK(p)) _DONE_; break;
    case token__POKE: if (fPOKE(p)) _DONE_; break;
    case token__KILL: if (fKILL(p)) _DONE_; break;
    case token__LINE: if (fLINEINPUT(p)) _DONE_; break;
    case token__MKDIR: if (fMKDIR(p)) _DONE_; break;
    case token__OPEN: if (fOPEN(p)) _DONE_; break;
    case token__RMDIR: if (fRMDIR(p)) _DONE_; break;
    case token__WRITE: if (fWRITE(p)) _DONE_; break;

    case token__WRITEBINARY: if (fWRITEBINARY(p)) _DONE_; break;

 //   case token__CIRCLE: if (fCIRCLE(p)) _DONE_; break;
 //   case token__DRAW: if (fDRAW(p)) _DONE_; break;
 //   case token__PAINT: if (fPAINT(p)) _DONE_; break;
 //   case token__PCOPY: if (fPCOPY(p)) _DONE_; break;
 //   case token__PMAP: if (fPMAP(p)) _DONE_; break;
 //   case token__PRESET: if (fPRESET(p)) _DONE_; break;
 //   case token__PSET: if (fPSET(p)) _DONE_; break;
 //   case token__VIEW: if (fVIEW(p)) _DONE_; break;
    //case token__VIEWPRINT: if (fVIEWPRINT(p)) _DONE_; break;
 //   case token__WINDOW: if (fWINDOW(p)) _DONE_; break;
 //   case token__WIDTH: if (fWIDTH(p)) _DONE_; break;
    default: 
      //return false; 
      _END_
  }

  //return false;
	_END_
}

bool fBUILTIN_FUNCTION(pcode *p, int *nReturnExpressionType, bool bReturn = true)
{
	_BEGIN_

	if (!proceedParse()) _END_

  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fBUILTIN", getCurrentLine() - 1));
  }

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

    case token__FILECOPY: if (fFILECOPY(p, nReturnExpressionType, bReturn)) _DONE_; break;


    case token__ABS: if (fABS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ARRAY: if (fARRAY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ASC: if (fASC(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ATN: if (fATN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__BIN_: if (fBIN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__BIN: if (fBIN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CBOOL: if (fCBOOL(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CBYTE: if (fCBYTE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CCUR: if (fCCUR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CDATE: if (fCDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CDBL: if (fCDBL(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CHOOSE: if (fCHOOSE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CHR_: if (fCHR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CHR: if (fCHR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CINT: if (fCINT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CLNG: if (fCLNG(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__COMMAND_: if (fCOMMAND(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__COMMAND: if (fCOMMAND(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__COS: if (fCOS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CSNG: if (fCSNG(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CSRLIN: if (fCSRLIN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CURDIR_: if (fCURDIR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CURDIR: if (fCURDIR(p, nReturnExpressionType, bReturn)) _DONE_; break;
//    case token__CVAR: if (fCVAR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CVERR: if (fCVERR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DATE_: if (fDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DATE: if (fDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DATEADD: if (fDATEADD(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DATEDIFF: if (fDATEDIFF(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DATEPART: if (fDATEPART(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DATESERIAL: if (fDATESERIAL(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DATEVALUE: if (fDATEVALUE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DAY: if (fDAY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DIR_: if (fDIR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DIR: if (fDIR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__EOF_: if (fEOF(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ERL: if (fERL(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ERR: if (fERR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__EXP: if (fEXP(p, nReturnExpressionType, bReturn)) _DONE_; break;
//    case token__FACT: if (fFACT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__FILEATTR: if (fFILEATTR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__FILEDATETIME: if (fFILEDATETIME(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__FILELEN: if (fFILELEN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__FILES: if (fFILES(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__FIX: if (fFIX(p, nReturnExpressionType, bReturn)) _DONE_; break;
    //case token__FORMAT: if (fFORMAT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    //case token__FORMATCURRENCY: if (fFORMATCURRENCY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    //case token__FORMATDATETIME: if (fFORMATDATETIME(p, nReturnExpressionType, bReturn)) _DONE_; break;
    //case token__FORMATNUMBER: if (fFORMATNUMBER(p, nReturnExpressionType, bReturn)) _DONE_; break;
    //case token__FORMATPERCENT: if (fFORMATPERCENT(p, nReturnExpressionType, bReturn)) _DONE_; break;
//    case token__FRAC: if (fFRAC(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__FRE: if (fFRE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__FREEFILE: if (fFREEFILE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__GETATTR: if (fGETATTR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__HEX_: if (fHEX(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__HEX: if (fHEX(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__HOUR: if (fHOUR(p, nReturnExpressionType, bReturn)) _DONE_; break;
//    case token__HYPOT: if (fHYPOT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__IIF: if (fIIF(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__INKEY_: if (fINKEY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__INKEY: if (fINKEY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__INPUT: if (fINPUT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__INPUTBOX: if (fINPUTBOX(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__INSTR: 
    case token__INDEXOF: 
      if (fINSTR(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__INSTREV: 
    case token__LASTINDEXOF:       
      if (fINSTREV(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__INT: if (fINT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISARRAY: if (fISARRAY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    
    case token__ISBOOLEAN: if (fISBOOLEAN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISBYTE: if (fISBYTE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISDOUBLE: if (fISDOUBLE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISINTEGER: if (fISINTEGER(p, nReturnExpressionType, bReturn)) _DONE_; break;


    case token__ISSHORT: if (fISSHORT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISSINGLE: if (fISSINGLE(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__ISLONG: if (fISLONG(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISSTRING: if (fISSTRING(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISVARIANT: if (fISVARIANT(p, nReturnExpressionType, bReturn)) _DONE_; break;   

    case token__ISDATE: if (fISDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISEMPTY: if (fISEMPTY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISERROR: if (fISERROR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISMISSING: if (fISMISSING(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISNULL: if (fISNULL(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISNUMERIC: if (fISNUMERIC(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISOBJECT: if (fISOBJECT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ISCURRENCY: if (fISCURRENCY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__FORMAT: if (fFORMAT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__KBASICDIR: if (fKBASICDIR(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__LCASE_: if (fLCASE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LCASE: 
    case token__LOWER: 
      if (fLCASE(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__COMPARE: if (fCOMPARE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__CONTAINS: if (fCONTAINS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__COUNT: if (fCOUNT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ENDSWITH: if (fENDSWITH(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__STARTSWITH: if (fSTARTSWITH(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LEFTJUSTIFIED: if (fLEFTJUSTIFIED(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__RIGHTJUSTIFIED: if (fRIGHTJUSTIFIED(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SECTION: if (fSECTION(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SIMPLIFIED: if (fSIMPLIFIED(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TRIMMED: if (fTRIMMED(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__REVERSED: if (fREVERSED(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__UNICODE: if (fUNICODE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__READBINARY: if (fREADBINARY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SEEKBINARY: if (fSEEKBINARY(p, nReturnExpressionType, bReturn)) _DONE_; break;


    //case token__ADDDATE: if (fADDDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ADDDAYS: if (fADDDAYS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ADDMONTHS: if (fADDMONTHS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ADDYEARS: if (fADDYEARS(p, nReturnExpressionType, bReturn)) _DONE_; break;
//    case token__SUBDATE: if (fSUBDATE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SUBDAYS: if (fSUBDAYS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SUBMONTHS: if (fSUBMONTHS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SUBYEARS: if (fSUBYEARS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    //case token__ADDTIME: if (fADDTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ADDHOURS: if (fADDHOURS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ADDMINUTES: if (fADDMINUTES(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ADDSECONDS: if (fADDSECONDS(p, nReturnExpressionType, bReturn)) _DONE_; break;
//    case token__SUBTIME: if (fSUBTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;
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

    case token__ENCODE: if (fENCODE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__DECODE: if (fDECODE(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__LEFT_: if (fLEFT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LEFT: if (fLEFT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SIZE: 
    case token__LEN: 
    case token__LENGTH: 
      if (fLEN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LN: if (fLN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LOC: if (fLOC(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LOF: if (fLOF(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LOG: if (fLOG(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LOGB: if (fLOGB(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LTRIM_: if (fLTRIM(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__LTRIM: if (fLTRIM(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__MAX: if (fMAX(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__MID_: if (fMID(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__MID: if (fMID(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__MIN: if (fMIN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__MINUTE: if (fMINUTE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__MONTH: if (fMONTH(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__MONTHNAME: if (fMONTHNAME(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__MSGBOX: if (fMSGBOX(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__NOW: if (fNOW(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__NZ: if (fNZ(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__OCT_: if (fOCT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__OCT: if (fOCT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__POS: if (fPOS(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__RAD: if (fRAD(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__REPLACE: if (fREPLACE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__RGB: if (fRGB(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__RIGHT_: if (fRIGHT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__RIGHT: if (fRIGHT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__RND: 
    case token__RANDOM: 
      if (fRND(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__ROUND: if (fROUND(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__RTRIM_: if (fRTRIM(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__RTRIM: if (fRTRIM(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SCREEN: if (fSCREEN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SEC: if (fSEC(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SECOND: if (fSECOND(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SEEK: if (fSEEK(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SGN: if (fSGN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SHELL: if (fSHELL(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SIN: if (fSIN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SPACE_: if (fSPACE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SPACE: if (fSPACE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SPLIT: if (fSPLIT(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SQR: if (fSQR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__STR_: if (fSTR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__STR: if (fSTR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__STRCOMP: if (fSTRCOMP(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__STRING_: if (fSTRING(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__STRREVERSE: if (fSTRREVERSE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SWITCH: if (fSWITCH(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TAN: if (fTAN(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TIME_: if (fTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TIME: if (fTIME(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TIMER: if (fTIMER(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TIMESERIAL: if (fTIMESERIAL(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TIMEVALUE: if (fTIMEVALUE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TRIM_: if (fTRIM(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TRIM: if (fTRIM(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__TYPE: 
    case token__TYPENAME: 
      if (fTYPENAME(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__UCASE_: if (fUCASE(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__UCASE: 
    case token__UPPER: 
      if (fUCASE(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__VAL: 
    case token__VALUE: 
      if (fVAL(p, nReturnExpressionType, bReturn)) _DONE_; break;

    case token__VARTYPE: if (fVARTYPE(p, nReturnExpressionType, bReturn)) _DONE_; break;      
    case token__WEEKDAY: if (fWEEKDAY(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__WEEKDAYNAME: if (fWEEKDAYNAME(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__YEAR: if (fYEAR(p, nReturnExpressionType, bReturn)) _DONE_; break;
    case token__SPC: if (fSPC(p, nReturnExpressionType, bReturn)) _DONE_; break;
    //case token__POINT: if (fPOINT(p, nReturnExpressionType, bReturn)) _DONE_; break;  
    case token__UTF8: if (fUTF8(p, nReturnExpressionType, bReturn)) _DONE_ break;
    case token__UTF16: if (fUTF16(p, nReturnExpressionType, bReturn)) _DONE_ break;
    default: //return false;
      _END_
      
  }

  //return false;
	_END_
}



	//QMap<XString, int> binding_map_class;
	//QMap<XString, int> binding_map_method;

	//bool fNAMESPACECLASS(pcode *p, const char *acNamespaceClass);

/*
  // kbasic.DIR
  #define KBASIC_DIR "kbasic.DIR"
  bool fKBASIC_DIR(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_DIR_CONSTRUCTOR(pcode *p);
  bool fKBASIC_DIR_DESTRUCTOR(pcode *p);
  bool fKBASIC_DIR_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_DIR_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.FILE
  #define KBASIC_FILE "kbasic.FILE"
  bool fKBASIC_FILE(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_FILE_CONSTRUCTOR(pcode *p);
  bool fKBASIC_FILE_DESTRUCTOR(pcode *p);
  bool fKBASIC_FILE_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_FILE_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.COLLECTION
  #define KBASIC_COLLECTION "kbasic.COLLECTION"
  bool fKBASIC_COLLECTION(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_COLLECTION_CONSTRUCTOR(pcode *p);
  bool fKBASIC_COLLECTION_DESTRUCTOR(pcode *p);
  bool fKBASIC_COLLECTION_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_COLLECTION_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.CAST
  #define KBASIC_CAST "kbasic.CAST"
  bool fKBASIC_CAST(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CAST_CONSTRUCTOR(pcode *p);
  bool fKBASIC_CAST_DESTRUCTOR(pcode *p);
  bool fKBASIC_CAST_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CAST_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.DEBUG
  #define KBASIC_DEBUG "kbasic.DEBUG"
  bool fKBASIC_DEBUG(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_DEBUG_CONSTRUCTOR(pcode *p);
  bool fKBASIC_DEBUG_DESTRUCTOR(pcode *p);
  bool fKBASIC_DEBUG_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_DEBUG_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.UTIL
  #define KBASIC_UTIL "kbasic.UTIL"
  bool fKBASIC_UTIL(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UTIL_CONSTRUCTOR(pcode *p);
  bool fKBASIC_UTIL_DESTRUCTOR(pcode *p);
  bool fKBASIC_UTIL_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UTIL_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);
*/
  // kbasic.math
  #define KBASIC_MATH	"Math"
  bool fKBASIC_MATH_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);

  
  bool fKBASIC_DATETIME_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UTILITY_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_MY_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CAST_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);

  bool fKBASIC_STRING_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  /*
  // kbasic.CONSOLE
  #define KBASIC_CONSOLE "kbasic.CONSOLE"
  bool fKBASIC_CONSOLE(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CONSOLE_CONSTRUCTOR(pcode *p);
  bool fKBASIC_CONSOLE_DESTRUCTOR(pcode *p);
  bool fKBASIC_CONSOLE_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CONSOLE_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.IO
  #define KBASIC_IO "kbasic.IO"
  bool fKBASIC_IO(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_IO_CONSTRUCTOR(pcode *p);
  bool fKBASIC_IO_DESTRUCTOR(pcode *p);
  bool fKBASIC_IO_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_IO_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.UI
  #define KBASIC_UI "kbasic.UI"
  bool fKBASIC_UI(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UI_CONSTRUCTOR(pcode *p);
  bool fKBASIC_UI_DESTRUCTOR(pcode *p);
  bool fKBASIC_UI_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UI_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.OBJECT
  #define KBASIC_OBJECT "kbasic.OBJECT"
  bool fKBASIC_OBJECT(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_OBJECT_CONSTRUCTOR(pcode *p);
  bool fKBASIC_OBJECT_DESTRUCTOR(pcode *p);
  bool fKBASIC_OBJECT_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_OBJECT_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.DOUBLE
  #define KBASIC_DOUBLE "kbasic.DOUBLE"
  bool fKBASIC_DOUBLE(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_DOUBLE_CONSTRUCTOR(pcode *p);
  bool fKBASIC_DOUBLE_DESTRUCTOR(pcode *p);
  bool fKBASIC_DOUBLE_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_DOUBLE_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.INTEGER
  #define KBASIC_INTEGER "kbasic.INTEGER"
  bool fKBASIC_INTEGER(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_INTEGER_CONSTRUCTOR(pcode *p);
  bool fKBASIC_INTEGER_DESTRUCTOR(pcode *p);
  bool fKBASIC_INTEGER_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_INTEGER_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.SHORT
  #define KBASIC_SHORT "kbasic.SHORT"
  bool fKBASIC_SHORT(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_SHORT_CONSTRUCTOR(pcode *p);
  bool fKBASIC_SHORT_DESTRUCTOR(pcode *p);
  bool fKBASIC_SHORT_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_SHORT_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);
*/
  // kbasic.STRING
  bool fKBASIC_DATETIME_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_STRING_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);
/*
  // kbasic.CSTRING
  #define KBASIC_CSTRING "kbasic.CSTRING"
  bool fKBASIC_CSTRING(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CSTRING_CONSTRUCTOR(pcode *p);
  bool fKBASIC_CSTRING_DESTRUCTOR(pcode *p);
  bool fKBASIC_CSTRING_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CSTRING_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.BOOLEAN
  #define KBASIC_BOOLEAN "kbasic.BOOLEAN"
  bool fKBASIC_BOOLEAN(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_BOOLEAN_CONSTRUCTOR(pcode *p);
  bool fKBASIC_BOOLEAN_DESTRUCTOR(pcode *p);
  bool fKBASIC_BOOLEAN_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_BOOLEAN_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.LONG
  #define KBASIC_LONG "kbasic.LONG"
  bool fKBASIC_LONG(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_LONG_CONSTRUCTOR(pcode *p);
  bool fKBASIC_LONG_DESTRUCTOR(pcode *p);
  bool fKBASIC_LONG_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_LONG_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.SINGLE
  #define KBASIC_SINGLE "kbasic.SINGLE"
  bool fKBASIC_SINGLE(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_SINGLE_CONSTRUCTOR(pcode *p);
  bool fKBASIC_SINGLE_DESTRUCTOR(pcode *p);
  bool fKBASIC_SINGLE_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_SINGLE_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.BYTE
  #define KBASIC_BYTE "kbasic.BYTE"
  bool fKBASIC_BYTE(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_BYTE_CONSTRUCTOR(pcode *p);
  bool fKBASIC_BYTE_DESTRUCTOR(pcode *p);
  bool fKBASIC_BYTE_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_BYTE_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);
*/
/*
  // kbasic.VARIANT
  #define KBASIC_VARIANT "kbasic.VARIANT"
  bool fKBASIC_VARIANT(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_VARIANT_CONSTRUCTOR(pcode *p);
  bool fKBASIC_VARIANT_DESTRUCTOR(pcode *p);
  bool fKBASIC_VARIANT_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_VARIANT_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);
*/
/*
  // kbasic.CURRENCY
  #define KBASIC_CURRENCY "kbasic.CURRENCY"
  bool fKBASIC_CURRENCY(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CURRENCY_CONSTRUCTOR(pcode *p);
  bool fKBASIC_CURRENCY_DESTRUCTOR(pcode *p);
  bool fKBASIC_CURRENCY_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CURRENCY_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.DATE
  #define KBASIC_DATE "kbasic.DATE"
  bool fKBASIC_DATE(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_DATE_CONSTRUCTOR(pcode *p);
  bool fKBASIC_DATE_DESTRUCTOR(pcode *p);
  bool fKBASIC_DATE_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_DATE_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.CHAR
  #define KBASIC_CHAR "kbasic.CHAR"
  bool fKBASIC_CHAR(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CHAR_CONSTRUCTOR(pcode *p);
  bool fKBASIC_CHAR_DESTRUCTOR(pcode *p);
  bool fKBASIC_CHAR_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_CHAR_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.INT16
  #define KBASIC_INT16 "kbasic.INT16"
  bool fKBASIC_INT16(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_INT16_CONSTRUCTOR(pcode *p);
  bool fKBASIC_INT16_DESTRUCTOR(pcode *p);
  bool fKBASIC_INT16_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_INT16_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.INT32
  #define KBASIC_INT32 "kbasic.INT32"
  bool fKBASIC_INT32(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_INT32_CONSTRUCTOR(pcode *p);
  bool fKBASIC_INT32_DESTRUCTOR(pcode *p);
  bool fKBASIC_INT32_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_INT32_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.INT64
  #define KBASIC_INT64 "kbasic.INT64"
  bool fKBASIC_INT64(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_INT64_CONSTRUCTOR(pcode *p);
  bool fKBASIC_INT64_DESTRUCTOR(pcode *p);
  bool fKBASIC_INT64_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_INT64_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.UINT16
  #define KBASIC_UINT16 "kbasic.UINT16"
  bool fKBASIC_UINT16(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UINT16_CONSTRUCTOR(pcode *p);
  bool fKBASIC_UINT16_DESTRUCTOR(pcode *p);
  bool fKBASIC_UINT16_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UINT16_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.UINT32
  #define KBASIC_UINT32 "kbasic.UINT32"
  bool fKBASIC_UINT32(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UINT32_CONSTRUCTOR(pcode *p);
  bool fKBASIC_UINT32_DESTRUCTOR(pcode *p);
  bool fKBASIC_UINT32_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UINT32_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic.UINT64
  #define KBASIC_UINT64 "kbasic.UINT64"
  bool fKBASIC_UINT64(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UINT64_CONSTRUCTOR(pcode *p);
  bool fKBASIC_UINT64_DESTRUCTOR(pcode *p);
  bool fKBASIC_UINT64_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_UINT64_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // kbasic
  #define KBASIC "kbasic"
  bool fKBASIC_CONSTRUCTOR(pcode *p);
  bool fKBASIC_DESTRUCTOR(pcode *p);
  */
  bool fKBASIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fKBASIC_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  /*
  // veryoldbasic
  #define VERYOLDBASIC "veryoldbasic"
  bool fVERYOLDBASIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fVERYOLDBASIC_CONSTRUCTOR(pcode *p);
  bool fVERYOLDBASIC_DESTRUCTOR(pcode *p);
  bool fVERYOLDBASIC_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fVERYOLDBASIC_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);

  // oldbasic
  #define OLDBASIC "oldbasic"
  bool fOLDBASIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fOLDBASIC_CONSTRUCTOR(pcode *p);
  bool fOLDBASIC_DESTRUCTOR(pcode *p);
  bool fOLDBASIC_STATIC(pcode *p, int *nReturnExpressionType, bool bReturn);
  bool fOLDBASIC_INSTANCE(pcode *p, int *nReturnExpressionType, bool bReturn);
  */

public:

static bool is_kbasic(t_token n)
{
	switch(n){
  // keyword
  //case token__CONNECT:
  //case token__DISCONNECT:
  case token___ELSE:
  case token___END:
  case token___IF:
  case token__ABSTRACT:
  case token__ADDRESSOF:
  case token__AS:
  case token__BY_REF:
  case token__BY_VAL:
  case token__CASE:
  case token__CATCH:
  case token__CHOOSE:
  case token__CLASS:
  case token__CONST:
  case token__CONSTRUCTOR:
  case token__DECLARE:
  case token__DESTRUCTOR:
  case token__DIM:
  case token__DIRECTCAST:
  case token__DO:
  case token__EACH:
  case token__ECHO:
  case token__ELSE:
  case token__ELSEIF:
  case token__EMPTY:
  case token__END:
  case token__ENDIF:
  case token__ENUM:
  case token__EVENT:
  case token__EXIT:
  case token__FINALLY:
  case token__FOR:
  case token__FUNCTION:
  case token__IF:
  case token__IIF:
  case token__IMPLEMENTS:
  case token__IMPORTS:
  case token__IN:
  case token__INHERITS:
  case token__INTERFACE:
  case token__IS:
  case token__ITERATE:
  case token__KBASIC:
  case token__LBOUND:
  case token__LIKE:
  case token__LOOP:
  case token__ME:
  case token__MID:
  case token__MODULE:
  case token__NAMESPACE:
  case token__NEW:
  case token__NEXT:
  //case token__NOTHING:
  case token__NULL:
  case token__OFF:
  case token__ON:
  case token__OPTION:
  case token__OPTIONAL:
  case token__PARENT:
  case token__PRESERVE:
  case token__PRIVATE:
  case token__PROPERTY:
  case token__PROTECTED:
  case token__PUBLIC:
  case token__VERYOLDBASIC:
  case token__REDIM:
  case token__REM:
  case token__REM_MULTILINE:
  case token__REM_MULTILINE_STOP:
  case token__REM_DOCUMENTATION:
  case token__REM_SHORT:
  case token__RETURN:
  case token__SELECT:
  //case token__SHORT:
  case token__SIGNAL:
  case token__SLOT:
  case token__STATIC:
  case token__STEP:
  case token__STOP:
  case token__SUB:
  case token__SWITCH:
  //case token__SYSTEM:
  case token__THEN:
  case token__THROW:
  case token__THROWS:
  case token__TO:
  case token__TRY:
  case token__TYPE:
  case token__UBOUND:
  case token__UNTIL:
  case token__OLDBASIC:
  case token__WHILE:
  case token__WITH:
  // builtin
  case token__RAISEEVENT:
  case token____CLASS__:
  case token____LINE__:
  case token____MODULE__:
  case token____SCOPE__:
  case token____SUB__:
  case token____ISLINUX__:
  case token____ISWINDOWS__:
  case token____ISMACOS__:
  case token____FILE__:
  case token____ISCLASS__:
  case token____ISMODULE__:
  case token____ISSUB__:
  case token__ABS:
  case token__CBOOL:
  case token__CBYTE:
  case token__CCHAR:
  case token__CCUR:
  case token__CDATE:
  case token__CDBL:
  case token__CHR:
  //case token__CHR_:
  case token__CINT:
  case token__CLNG:
  case token__CLS:
  case token__COBJ:
  case token__COLOR:
  case token__COS:
  case token__CSHORT:
  case token__CSNG:
  case token__CSRLIN:
  case token__CTYPE:
  case token__DOEVENTS:
  case token__EXP:
  case token__FACT:
  case token__FILECOPY:
  case token__FILEDATETIME:
  case token__FILELEN:
  case token__FIX:
  case token__FRAC:
  case token__HEX:
  //case token__HEX_:
  case token__INKEY:
  //case token__INKEY_:
  case token__INPUT:
  //case token__INPUT_:
  case token__INSTR:
  case token__INSTREV:
  case token__INT:
  case token__ISARRAY:
  case token__ISBOOLEAN:
  case token__ISBYTE:
  case token__ISCSTRING:
  case token__ISCURRENCY:
  case token__ISDATE:
  case token__ISDOUBLE:
  case token__ISEMPTY:

  case token__ISINTEGER:
  case token__ISNULL:
  case token__ISNUMERIC:
  case token__ISOBJECT:
  case token__ISSHORT:
  case token__ISSINGLE:

  case token__LCASE:
  //case token__LCASE_:
  case token__LEFT:
  //case token__LEFT_:
  case token__LEN:
  case token__LOC:
  case token__LOCATE:
  case token__LOG:
  case token__LOGB:
  case token__LTRIM:
  //case token__LTRIM_:
  case token__MAX:
  case token__MID_:
  case token__MIN:
  case token__NOW:
  case token__OCT:
  //case token__OCT_:
  case token__POS:
  case token__PRINT:
  case token__PRINTSCREEN:
  case token__RAD:
  case token__RAISE:
  case token__RAISESIGNAL:
  case token__RANDOM:
  case token__RANDOMIZE:
  case token__REPLACE:
  case token__RIGHT:
  //case token__RIGHT_:
  case token__RND:
  case token__RTRIM:
  //case token__RTRIM_:
  case token__SEC:
  case token__SGN:
  case token__SIN:
  case token__SPACE:
  //case token__SPACE_:
  case token__SQR:
  case token__STR:
  //case token__STR_:
  case token__TAN:
  case token__TRIM:
  //case token__TRIM_:
  case token__TYPENAME:
  case token__TYPEOF:
  case token__UCASE:
  case token__UTF8:
  case token__UTF16:
  //case token__UCASE_:
  case token__VAL:
  case token__VARTYPE:

  // type
  case token__TYP_BOOLEAN:
  case token__TYP_BYTE:
  //case token__TYP_COLLECTION:
  case token__TYP_CSTRING:
  case token__TYP_CURRENCY:
  case token__TYP_DATE:
  case token__TYP_DOUBLE:
  case token__TYP_INTEGER:
  case token__TYP_LONG:
  case token__TYP_OBJECT:
  case token__TYP_CASTEXCEPTION:
  case token__TYP_QTEXCEPTION:
  case token__TYP_EXCEPTION:
  case token__TYP_SHORT:
  case token__TYP_SINGLE:
  case token__TYP_QSTRING:
  case token__TYP_ANY:
  // operator
  case token__OP_SHL:
//  case token__OP_SHL_:
  case token__OP_SHR:
//  case token__OP_SHR_:
  case token__OP_INC:
//  case token__OP_INC_:
  case token__OP_DEC:
//  case token__OP_DEC_:
    /*
  case token__OP_ADD_EQUAL:
  case token__OP_SUB_EQUAL:
  case token__OP_DIV_EQUAL:
  case token__OP_MUL_EQUAL:
  case token__OP_ADD_ADD:		
  case token__OP_SUB_SUB:		
*/
//  case token__OP_OR_EQUAL:
  //case token__OP_AND_EQUAL:
  case token__OP_BIT_AND:
  case token__OP_BIT_OR:
  case token__OP_BIT_XOR:
  case token__OP_BIT_NOT:

  case token__OP_ADD:
  case token__OP_SUB:
  case token__OP_MUL:
  case token__OP_DIV:
  case token__OP_MOD:
  case token__OP_EQUAL:
  case token__OP_UNEQUAL:
  case token__OP_GREATER_EQUAL:
  case token__OP_LESSER_EQUAL:
  case token__OP_GREATER:
  case token__OP_LESSER:
  case token__OP_AND:
  case token__OP_ANDALSO:
  case token__OP_OR:
  case token__OP_ORELSE:
  case token__OP_NOT:
  case token__OP_POWER:
  case token__OP_STR_CAT:
  case token__OP_XOR:
  case token__OP_IDIV:
    return true;
  }
  return false;
}

private:
  /*
static bool not_supported_kbasic(t_token n)
{
	switch(n){    
  //case token__ARRAY:
  //case token__ISOBJECT:
  //case token__ISNUMERIC:
  //case token__STRUCTURE:

  //case token__COMMAND:  
  //case token__RSET:  
  //case token__DOEVENTS:  
  //case token__REDIM:  
  //case token__PRESERVE:  
  //case token__CHDIR:  
  //case token__CHDRIVE:
  //case token__CURDIR:
  //case token__CURDIR_:
  //case token__DIR:
  //case token__DIR_:
  //case token__FILEATTR:
  //case token__FILEDATETIME:
  //case token__GETATTR:
  //case token__SEEK:
  case token__SETATTR:

  //case token__ISERROR:  
  //case token__CLEAR:  
  //case token__CVERR:  
  //case token__ERR:  
  //case token__ERL:  
  //case token__RESTORE:  
  //case token__RESUME:  

  case token__SIGNAL:  
  //case token__FILES:

//  case token__STRUCTURE:

  case token__MSC_EXTIDENTIFIER:
  //case token__BEEP:
  case token__RANGE:
  //case token__PROPERTY:
  //case token__DECLARE:
  //case token__VARTYPE:
  //case token__LIKE:
  case token__SIZEOF:

  //case token__TYP_COLLECTION:
  //case token__TYP_CSTRING:
  //case token__TYP_CURRENCY:

  //case token__OP_SHL:
//  case token__OP_SHL_:
  //case token__OP_SHR:
//  case token__OP_SHR_:
  //case token__OP_INC:
//  case token__OP_INC_:
  //case token__OP_DEC:
//  case token__OP_DEC_:
//  case token__OP_ADD_EQUAL:
  //case token__OP_SUB_EQUAL:
  //case token__OP_DIV_EQUAL:
//  case token__OP_MUL_EQUAL:

//  case token__OP_OR_EQUAL:
  //case token__OP_AND_EQUAL:
  //case token__OP_BIT_AND:
  //case token__OP_BIT_OR:
  //case token__OP_BIT_XOR:
  //case token__OP_BIT_NOT:

  case token__INTERFACE:
  case token__NAMESPACE:

  //case token____ISMACOS__:
  //case token__CCUR:
  case token__CCHAR:

  //case token__TYP_DATE:
  //case token__CDATE:  
    / *
  case token__DATEADD:
  case token__DATEDIFF:
  case token__DATEPART:
  case token__DATESERIAL:
  case token__DATEVALUE:
  case token__DAY:
  case token__DEFDATE:
  case token__MINUTE:
  case token__HOUR:
  case token__SEC:
  case token__MONTH:
  case token__SECOND:
  case token__TIMESERIAL:
  case token__TIMEVALUE:
  case token__WEEKDAY:
  case token__YEAR:
  case token__NOW:
  case token__ISDATE:

* /
  //case token__DOEVENTS:

  case token__DRAW:

  case token__EACH:
  case token__IMPORTS:
  //case token__DEFCUR:
  //case token__DEFVAR:
//  case token__FILEDATETIME:
  case token__IN:
  case token__ISCSTRING:
  //case token__ISCURRENCY:
  
  case token__PAINT:
  case token__PCOPY:
  //case token__RAISE:
  case token__RAISESIGNAL:
  case token__RAISEEVENT:
  case token__VIEW:
  case token__WINDOW:
  case token__HYPOT:
  //case token__TYPENAME:
  case token__WIDTH:
  //case token__FORMAT:
  //case token__FORMAT_:
  //case token__INPUTBOX:
  //case token__MSGBOX:
  //case token__USING:
  //case token__PROTECTED:

//  case token__ASC:
  case token__ASN:
  case token__ATN:


  return true;
	break;
	default: return false;
	}
}


//   liste die zwar von vb, aber nicht von kbasic supported werden
static bool not_supported_vb(t_token n)
{
	switch(n){    
  case token__ACS:
  //case token__CIRCLE:
  case token__LOGB:
  case token__POINT:
  case token__PRESET:
//  case token__POINT:
  //case token__PSET:
  //case token__RANDOMIZE:
  //case token__RND:
  case token__SCREEN:
  //case token__SPC:
  case token__SPLIT:
  //case token__TAB:

  case token__FACT:
  case token__FRAC:
  case token__DOF:
  case token__DEG:
  case token__CBCD:
  case token__CEXT:
  case token__CFIX:  
  case token__CQUD:  
  case token__DATABASE:  
  case token__MKS:  
  case token__MKI_:  
  case token__MKDMBF_:      
  case token__MTIMER:      
  case token__PMAP:
  case token__REPEAT:
  //case token__TEXT:
  case token__TYPEDEF:
  case token__FN:

  case token__RAISEEVENT:
  case token__QBCOLOR:
  case token__LOAD:
  case token__UNLOAD:
  case token__CALLBYNAME:
  case token__CREATEOBJECT:
  case token__DDB:
  case token__ENVIRON:
  case token__WITHEVENTS:
  case token__FILTER:
  case token__FRIEND:
  //case token__FORMATCURRENCY:
  //case token__FORMATDATETIME:
  //case token__FORMATNUMBER:
  //case token__FORMATPERCENT: 
  case token__FV:
  case token__GETALLSETTINGS:
  case token__GETAUTOSERVERSETTINGS:
  case token__GETOBJECT:
  case token__GETSETTING: 
  case token__IMESTATUS:
  case token__IPMT:
  case token__IRR:
  case token__JOIN: 
  case token__LOADPICTURE:
  case token__LOADRESDATA:
  case token__LOADRESPICTURE:
  case token__LOADRESSTRING:
  case token__MIRR:
  //case token__MONTHNAME:
  case token__NPER:
  case token__NPV:
  case token__PARTITION:
  case token__PMT:
  case token__PPMT:
  case token__PV:
  case token__RATE:
  case token__SLN:
  case token__STRCONV:
  case token__SYD:
  //case token__WEEKDAYNAME:
  case token__APPACTIVATE:
//  case token__DECLARE:
  case token__DELETESETTING:
  case token__IMPLEMENTS:
  case token__LOCK:
  case token__UNLOCK:
  case token__DECIMAL:
  case token__SAVEPICTURE:
  case token__SAVESETTING: 
  case token__SENDKEYS:
  case token___IF:
  case token___ELSE:
//  case token___ENDIF:
  return true;
	break;
	default: return false;
	}
}

static bool not_supported_vbnet(t_token n)
{
	switch(n){
  case token__ADDHANDLER:
  case token__ALIAS:
  case token__ANSI:
  case token__ASSEMBLY:
  case token__AUTO:
  case token__CDEC:
  case token__COBJ:
  //case token__CSHORT:
  case token__CTYPE:
  case token__DECIMAL:
  case token__DEFAULT:
  case token__DELEGATE:
  case token__DIRECTCAST:
  case token__EVENT:
  case token__GETTYPE:
  case token__HANDLES:
  case token__IMPLEMENTS:
  case token__LIB:
  case token__MUSTINHERIT:
  case token__MUSTOVERRIDE:
  case token__MYBASE:
  case token__MYCLASS:
  case token__NOTINHERITABLE:
  case token__NOTOVERRIDABLE:
  case token__OVERLOADS:
  case token__OVERRIDABLE:
  case token__OVERRIDES:
  case token__RAISEEVENT:
  case token__READONLY:
  case token__REMOVEHANDLER:
  case token__SHADOWS:
  //case token__SHARED:
//  case token__SHORT: 
  case token__SYNCLOCK:
  case token__UNICODE:  
  case token__WRITEONLY:
  case token___EXTERNALSOURCE:
  case token___REGION:
  return true;
	break;
	default: return false;
	}
}

static bool not_supported_qbasic(t_token n)
{
	switch(n){
  //case token__RANDOM:
  case token__FIELD:
  case token__LN:

  case token__DEF:
  case token__SEG:
  case token__ENVIRON:
  case token__ENVIRON_:
  case token__ERDEV:
  case token__ERDEV_:
  //case token__ON:
  case token__COM:
  case token__KEY:
  case token__PEN:
  case token__PLAY:
  case token__STRIG:
  //case token__INPUT_:
  //case token__TIMER:
  case token__SWAP:
  case token__VARSEG:
  case token__VARPTR:
  case token__VARPTR_:
  case token__WAIT:
  case token__ABSOLUTE:
  case token__BLOAD:
  case token__BSAVE:
  case token__CVD:
  case token__CVDMBF:
  case token__CVI:
  case token__CVL:
  case token__CVS:
  case token__CVSMBF:
  //case token__GET:
  case token__INP:
  case token__IOCTL:
  case token__IOCTL_:
  //case token__LINE:
  case token__LOCK:
  case token__UNLOCK:
  //case token__CIRCLE:
  //case token__DRAW:
  case token__LPOS:
  case token__LPRINT:
  //case token__USING:
  case token__MKD_:
  case token__MKDMBF_:
  case token__MKL_:
  case token__MKS_:
  case token__MKSMBF_:
  case token__OUT:
  //case token__PAINT:
  case token__PALETTE:
  //case token__PCOPY:
  case token__PEEK:
  //case token__PMAP:
  //case token__POINT:
  case token__POKE:
  //case token__PRESET:
  //case token__PSET:
  //case token__PUT:
  case token__RUN:
  case token__CHAIN:
  //case token__SCREEN:
  case token__SOUND:
  case token__STICK:
  case token__TROFF:
  case token__TRON:
  //case token__VIEW:
  //case token__WIDTH:
  //case token__WINDOW:
  return true;
	break;
	default: return false;
	}
}

*/
public:
  /*
static bool not_supported(t_token n)
{
  return not_supported_vbnet(n) || not_supported_vb(n) || not_supported_qbasic(n) || not_supported_kbasic(n);
}*/

private:


/*
// liste alter BASIC befehle (deprecated) aber fr rckw�tskompatibilit� noch untersttzt
static bool deprecated(t_token n)
{
	switch(n){
  case token__FREEFILE: 
	return true;
	break;
	default: return false;
	}
}

// liste noch nicht untersttzter BASIC befehle
static bool not_implemented(t_token n)
{
	switch(n){
  case token__FREEFILE: 

	return true;
	break;
	default: return false;
	}
}

// liste nicht getesteter bzw. nicht stabiler BASIC befehle
static bool unstable(t_token n)
{
	switch(n){
  case token__FREEFILE: 

	return true;
	break;
	default: return false;
	}
}
*/

};

#endif
