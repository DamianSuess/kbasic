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
#include "../kbshared/pcode.h"
#include "../kbshared/cache.h"


/**
[EXPLANATION]
NAME: CLASS INSTANCE SCOPE
DESC: sub/function/method/variable/const is only useable inside an object
SEEALSO:
*/
/**
[EXPLANATION]
NAME: CLASS STATIC SCOPE
DESC: sub/function/method/variable/const can be used without an object
SEEALSO:
*/
// scan static scope part of class
bool parser::fREGISTER_CLASS_STATICSCOPE(pcode *p)
{
  _BEGIN_

  //register bool bTerm_STATIC = false;

  if (!(/*bTerm_STATIC = */parseTerm(token__STATIC))){ _END_ }	

  switch(peekToken()){
    case token__SUB:
    case token__FUNCTION:
    case token__CONSTRUCTOR:
    case token__DESTRUCTOR:
    case token__SLOT:
    case token__SIGNAL:
    case token__PRIVATE:
    case token__PUBLIC:
    case token__PROTECTED:
    case token__ABSTRACT:
      _END_
  }

	int nTest = 0;
	int nTestPrev = 0;
	bool bRet = true;
  bool bSTATEMENTSEQUENCE = false;

  goto re;

	do {

		nTest = peekToken();

		
		if ((nTestPrev != token__END 				
			&& (nTest == token__STATIC))
		){
re:
      nextToken();

      exception *e = new exception;

      setScopeClassStatic(true);

      bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p, true);

      if (myException.size() > 0){ // all exceptions are catchable?

        t_exception *t;
        if (myException.first((int *) &t)){

         setCurrentLine(t->nLine);
         setCurrentRow(t->nRow);

          semanticError(token__SUB, utility::con(t->acName, " catch statement missing inside static part of class"));
          _ERROR_

        }

			}		


     setScopeClassStatic(false);

    nTestPrev = peekToken();
    nextToken();
    nTest = peekToken();

  	if (nTestPrev == token__END && nTest == token__STATIC){
     parseInfo(p, "parsed CLASS STATICSCOPE\n");

     nextToken();
			_DONE_
    } else {

      syntaxError(token__KEYWORD, "END STATIC missing. Maybe you used methods or variables which are declared after this statement\n");

      _ERROR_
    }

   }    
		

		nTestPrev = nTest;		

	} while(proceedParse() && bRet && (bRet = nextToken()));

  syntaxError(token__KEYWORD, "END STATIC missing\n");

  _ERROR_
}


/**
[EXPLANATION]
NAME: CLASS METHOD
DESC: useable with an object
SEEALSO:
*/
/**
[EXPLANATION]
NAME: CLASS SUB
DESC: useable with an object of sub's class
SEEALSO:
*/
/**
[EXPLANATION]
NAME: CLASS FUNCTION
DESC: useable with an object of function's class
SEEALSO:
*/
/**
[EXPLANATION]
NAME: CLASS CONSTRUCTOR
DESC: creates an object using a class as a template
SEEALSO:
*/
/**
[EXPLANATION]
NAME: CLASS DESTRUCTOR
DESC: destructs and frees an object
SEEALSO:
*/
// scan method header
bool parser::fREGISTER_CLASS_METHOD()
{
  _TBEGIN_

	register int nTest = 0;
	register int nTestPrev = 0;
	bool bRet = true;
	bool bMethodDone = false;
	int nSubStartPos = getTokenPos();
	int nPrevTokenPos = 0;
  bool bAbstract = false;
  bool bDeclare = false;

	do {

		nTest = peekToken();

		if (nTest == token__PROPERTY){		  
			_TEND_
		}

    if (bAbstract){ // wenn die methode abstrakt ist, dann gibt es kein END SUB/FUNCTION...
		  setTokenPos(nPrevTokenPos);
			return bMethodDone;
    }

    if (nTestPrev == token__END && nTest == token__CLASS){
		  setTokenPos(nPrevTokenPos);
			return bMethodDone;
		}

		if (nTestPrev == token__END && nTest == token__FUNCTION){
			nextToken();
			return bMethodDone;
		}

		if (nTestPrev == token__END && nTest == token__SUB){
			nextToken();
			return bMethodDone;
		}

		if (nTestPrev == token__END && nTest == token__CONSTRUCTOR){
			nextToken();
			return bMethodDone;
		}

		if (nTestPrev == token__END && nTest == token__DESTRUCTOR){
			nextToken();
			return bMethodDone;
		}

		if (nTestPrev == token__END && nTest == token__SIGNAL){
			nextToken();
			return bMethodDone;
		}

		if (nTestPrev == token__END && nTest == token__SLOT){
			nextToken();
			return bMethodDone;
		}

		if (nTest == token__MSC_EOL){
			nSubStartPos = getTokenPos(); // last EOL before sub
		}

		if (bMethodDone == false){

			if ((nTestPrev != token__EXIT 
				&& nTestPrev != token__END 
				&& (nTest == token__FUNCTION || nTest == token__SUB || nTest == token__CONSTRUCTOR || nTest == token__DESTRUCTOR || nTest == token__SIGNAL || nTest == token__SLOT))
			){
			    int uu  = getTokenPos();
				 setTokenPos(nSubStartPos);
				 bRet = fREGISTER_METHOD(&bAbstract, &bDeclare); // only header line parsed
				 bMethodDone = true;

         if (strcmp(sCurrentLib.ascii(), "") != 0 || bDeclare){
           return bMethodDone;
         }

         nTest = peekToken();
			}
		}

		nTestPrev = nTest;
		nPrevTokenPos = getTokenPos();

	} while(proceedParse() && bRet && (bRet = nextToken()));

	return false;
}

/**
[EXPLANATION]
NAME: CLASS TYPE
DESC: user defined type inside a class. Is accessable depending on declaration with PRIVATE or PUBLIC
SEEALSO:
*/
bool parser::fREGISTER_CLASS_TYPE()
{	
  return registerAllTypes();
}


/**
[EXPLANATION]
NAME: CLASS ENUMERATION
DESC: user defined enumartion inside a class. Is accessable depending on declaration with PRIVATE or PUBLIC
SEEALSO:
*/
bool parser::fREGISTER_CLASS_ENUM()
{
  return registerAllEnums();
}

/**
[EXPLANATION]
NAME: CLASS PROPERTY
DESC: user defined property inside a class. Is accessable depending on declaration with PRIVATE or PUBLIC
SEEALSO:
*/
// scan property header
bool parser::fREGISTER_CLASS_PROPERTY()
{
	register int nTest = 0;
	register int nTestPrev = 0;
	bool bRet = true;
	bool bMethodDone = false;
	int nSubStartPos = getTokenPos();
	int nPrevTokenPos = getTokenPos();

	do {

		nTest = peekToken();

		if (nTestPrev == token__END && nTest == token__CLASS){
		  setTokenPos(nPrevTokenPos);
			return bMethodDone;
		}

		if (nTestPrev == token__END && nTest == token__PROPERTY){
			nextToken();
			return bMethodDone;
		}

		if (nTestPrev == token__MSC_EOL){
			nSubStartPos = getTokenPos(); // last EOL before sub
		}

		if (bMethodDone == false){

			if ((nTestPrev != token__EXIT 
				&& nTestPrev != token__END 
				&& (nTest == token__PROPERTY))
			){
				 setTokenPos(nSubStartPos);
				 bRet = fREGISTER_PROPERTY();
				 bMethodDone = true;
         nTest = peekToken();
			}
		}

		nTestPrev = nTest;
		nPrevTokenPos = getTokenPos();

	} while(proceedParse() && bRet && (bRet = nextToken()));

	return false;
}

/**
[EXPLANATION]
NAME: CLASS VARIABLE
DESC: variable inside a class. Is accessable depending on declaration with PRIVATE, PROTECTED or PUBLIC
SEEALSO:
*/
bool parser::fREGISTER_CLASS_VAR(pcode *p)
{
	_BEGIN_

	static /**/ bool bTerm_PRIVATE;// = false;	
	static /**/ bool bTerm_PUBLIC;// = false;
	static /**/ bool bTerm_PROTECTED;// = false;
	static /**/ bool bTerm_STATIC;// = false;
	static /**/ bool bTerm_DIM;// = false;

	if ((bTerm_STATIC = parseTerm(token__STATIC))){}

  bool bb = false;

  switch(peekToken()){
    case token__PRIVATE:
      if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){ bTerm_PUBLIC = false; bTerm_PROTECTED = false; bTerm_DIM = false; } 
      break;
    case token__PUBLIC:
      if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){ bTerm_PRIVATE = false; bTerm_PROTECTED = false; bTerm_DIM = false; }
      break;
    case token__PROTECTED:
      if (bTerm_PROTECTED = parseTerm(token__PROTECTED)){ bTerm_PUBLIC = false; bTerm_PRIVATE = false; bTerm_DIM = false; }
      break;
    case token__DIM:
      if (bTerm_DIM = parseTerm(token__DIM)){ bTerm_PUBLIC = false; bTerm_PRIVATE = false; bTerm_PROTECTED = false; }
      break;
    default:
      bb = true;
      break;
  }


	if ((!bTerm_STATIC && (bTerm_STATIC = parseTerm(token__STATIC)))){}
	
  if (bb && !bTerm_STATIC){ _END_ }
 
  switch(peekToken()){
    case token__ABSTRACT:// maybe it's a method
    case token__DECLARE:// maybe it's a method
    case token__CONST:
    case token__FUNCTION:
    case token__SUB:
    case token__PROPERTY:
    //case token__STRUCTURE:
    case token__TYPE:
    case token__ENUM:
    case token__CONSTRUCTOR:
    case token__DESTRUCTOR:
    case token__SIGNAL:
    case token__SLOT:
      _END_
  }

	static /**/ bool bIDENTIFIER[parser__MAX_DIM];
	static /**/ bool bTerm_AS[parser__MAX_DIM];
	static /**/ bool bTerm_NEW[parser__MAX_DIM];
	static /**/ bool bTYPE[parser__MAX_DIM];
	bool bTerm_COMMA = false;
	bool bTerm__ = false;
	static /**/ const char *acIdentifier[parser__MAX_DIM];
	static /**/ const char *acType[parser__MAX_DIM];
	static /**/ int nSize[parser__MAX_DIM];
	const char *acCurrentType = "";

	static /**/ bool bARRAY[parser__MAX_DIM];
	static /**/ t_array a[parser__MAX_DIM];

	int nComma = 0;

	bTerm_AS[nComma] = false;
	bTYPE[nComma] = false;
	bARRAY[nComma] = false;
	bTerm_NEW[nComma] = false;  
  pcode *p2 = 0;
  
  if (bTerm_STATIC){    
    p2 = myClass->getClassStaticPcode(myClass->getId(getClass())); // myPcode represents global vars and consts, all consts are like static vars, also static vars
  } else {
    p2 = p;
  }


  if (bTerm_STATIC == false && strcmp(sCurrentLib.ascii(), "") != 0){ semanticError(token__DECLARE, "You cannot declare non-static variables inside a ALIAS LIB class for DLL/SO accessing."); _ERROR_ }  

	while (true){

	 	if (nComma >= parser__MAX_DIM){ internalError("too many DIM in one line"); _ERROR_ }

				 if (bIDENTIFIER[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(defaultType(acIdentifier[nComma])))); bTerm_AS[nComma] = false; bTYPE[nComma] = true; }
		// because the identifier has a suffix $,%,&,#,!, AS <TYPE> is not allowed, already found out
		else if (bIDENTIFIER[nComma] = fID_STRING(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__QSTRING))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_INTEGER(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__INTEGER))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; } 
		else if (bIDENTIFIER[nComma] = fID_LONG(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__LONG))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_SINGLE(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__SINGLE))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_DOUBLE(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__DOUBLE))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
		else if (bIDENTIFIER[nComma] = fID_CURRENCY(&acIdentifier[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__CURRENCY))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }

		if (bIDENTIFIER[nComma]){

 		  if (bARRAY[nComma] = fREGISTER_ARRAY_CONST(p2, &a[nComma], 0, 0, bTerm_STATIC ? global : me)){}

     	if (bTerm__ = parseTerm(token__OP_EQUAL)){
        { semanticError(token__DIM, "expression after DIM not allowed in global class declaration scope"); _ERROR_ }
      }

			// check for AS, if %, &, !, # or $ is used, AS is not allowed, type already known
			if (bTerm_AS[nComma] == true && (parseTerm(token__AS))){ semanticError(token__DIM, "type already known, identifier may not stop with %, &, !, # or $"); _ERROR_ }
			if (bTerm_AS[nComma] == false){
				if (bTerm_AS[nComma] = parseTerm(token__AS)){

					if (bTerm_NEW[nComma] = parseTerm(token__NEW)){ semanticError(token__DIM, "NEW after DIM not allowed in global declaration scope"); _ERROR_ }

     
#ifdef KBDEBUG
  if (stopAtLine(111)){
    int i = 9;
    i++;
  }
#endif
					if (bTYPE[nComma] = fTYPE(p2, &acType[nComma], bTerm_NEW[nComma])){}
					if (bTerm_AS[nComma] && !bTYPE[nComma]){ syntaxError(token__DIM, "type name missing"); _ERROR_ }
				}

			}

     	if (bTerm__ = parseTerm(token__OP_EQUAL)){
        { semanticError(token__DIM, "expression after DIM not allowed in global declaration scope"); _ERROR_ }
      }

		  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
				nComma++;
			} else {

				{

					for (int i = nComma; i >= 0; i--){

						if (bTYPE[i] == true){
							acCurrentType = (char *) acType[i];
						}

	  		  	int nTypes = findType(acCurrentType);
						if (nTypes == 0){ semanticError(token__DIM, utility::con(acCurrentType, " type not defined") ); _ERROR_ }


           int nVar = 0;

           // static var und var name müssen eindeutig sein
           if (bTerm_STATIC){
             if (findClassVar(getClass(), acIdentifier[i]) > 0){ semanticError(token__DIM, utility::con(utility::ident(getClass(), acIdentifier[i]), " already declared at some place") ); _ERROR_ }
           } else {
             if (findClassStaticVar(getClass(), acIdentifier[i]) > 0){ semanticError(token__DIM, utility::con(utility::ident(getClass(), acIdentifier[i]), " already declared at some place") ); _ERROR_ }
           }
 					
           int nTypeSize = 0;
           if (nTypes == pcode__LQSTRING || nTypes == pcode__LCSTRING) nTypeSize = nSize[i]; // myMemory_type->getSize(nTypes);

           if (bTerm_STATIC){
             nVar = registerClassStaticVar(getClass(), acIdentifier[i], nTypes, &a[i], bTerm_STATIC, bTerm_PRIVATE ? token__PRIVATE : bTerm_PUBLIC ? token__PUBLIC : bTerm_DIM ? token__PUBLIC : token__PROTECTED, nTypeSize);
           } else {
             nVar = registerClassVar(getClass(), acIdentifier[i], nTypes, &a[i], bTerm_STATIC, bTerm_PRIVATE ? token__PRIVATE : bTerm_PUBLIC ? token__PUBLIC : bTerm_DIM ? token__PUBLIC : token__PROTECTED, nTypeSize);
           }

 					  if (nVar == 0){ semanticError(token__DIM, utility::con(utility::ident(getClass(), acIdentifier[i]), " already declared at some place") ); _ERROR_ }
 					  //if (nVar == 0){ internalError(utility::con(utility::ident(getClass(), acIdentifier[i]), " could not be declared") ); _ERROR_ }

						if (bProducePcode){

              p2->wr_DIM(pcode__DIM, nVar, bTerm_STATIC ? global : me, nTypes, bTerm_NEW[i], false, bARRAY[i], false, nTypeSize, 0, "", false); // write pcode

						}

            parseInfo(p2,  utility::con("parsed CLASS DIM", acIdentifier[i], "") );

					}

					_DONE_


				}
				break;
			}
		} else break;
	}

	// no error, maybe it's a method

	_END_
}

/**
[EXPLANATION]
NAME: CLASS CONST
DESC: constant inside a class. Is accessable depending on declaration with PRIVATE, PROTECTED or PUBLIC
SEEALSO:
*/
bool parser::fREGISTER_CLASS_CONST(pcode *p)
{
	_BEGIN_

	static /**/ bool bTerm_PRIVATE;// = false;
	static /**/ bool bTerm_PUBLIC;// = false;
	static /**/ bool bTerm_PROTECTED;// = false;

  switch(peekToken()){
    case token__PRIVATE:
      if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){ bTerm_PUBLIC = false; bTerm_PROTECTED = false; } 
      break;
    case token__PUBLIC:
      if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){ bTerm_PRIVATE = false; bTerm_PROTECTED = false; }
      break;
    case token__PROTECTED:
      if (bTerm_PROTECTED = parseTerm(token__PROTECTED)){ bTerm_PUBLIC = false; bTerm_PRIVATE = false; }
      break;
    default:
      { bTerm_PUBLIC = true; }
      break;
  }


	//bool bTerm_CONST = false;

  if (!(/*bTerm_CONST = */parseTerm(token__CONST))){ _END_ }

	bool bTerm_COMMA = false;
	bool bTerm__ = false;
	static /**/ bool bIDENTIFIER[parser__MAX_CONST];
	static /**/ const char *acIdentifier[parser__MAX_CONST];
	static /**/ bool bEXPRESSION[parser__MAX_CONST];
	int nExpressionType = 0;
	bool bTYPE = false;
	bool bTerm_AS = false;  
  static /**/ const char *acType[parser__MAX_CONST];

	int nComma = 0;

	bEXPRESSION[nComma] = false;


	while (true){

	 	if (nComma >= parser__MAX_CONST){ internalError("too many CONST in one line"); _ERROR_ }

		if (bIDENTIFIER[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier[nComma])){}

		if (bIDENTIFIER[nComma])
    if (bTerm__ = parseTerm(token__OP_EQUAL)){
		  if (bEXPRESSION[nComma] = fCONST_EXPRESSION(p, &nExpressionType)) if (!memory_type::scalar(nExpressionType)){ semanticError(token__CONST, "CONST must be of type BYTE, CURRENCY, DATE, INTEGER, LONG, BOOLEAN, SINGLE, DOUBLE or STRING"); _ERROR_ }
    } else {
      if (bTerm_AS = parseTerm(token__AS)){
			  if (bTYPE = fTYPE(p, &acType[nComma], false)){}

        if (bTerm_AS && !bTYPE){ syntaxError(token__TRY, "type name missing"); _ERROR_ }

        if (bTerm__ = parseTerm(token__OP_EQUAL)){
		      if (bEXPRESSION[nComma] = fCONST_EXPRESSION(p)){}

          if (!bEXPRESSION[nComma]){ semanticError(token__CONST, "const expression missing"); _ERROR_ }     
        }
      }
    }    

				 if (!bIDENTIFIER[nComma]){ syntaxError(token__CONST, "identifier missing or identifier not declared"); _ERROR_ }
		else if (!bTerm__){ syntaxError(token__CONST, "= missing"); _ERROR_ }
	  else if (!bEXPRESSION[nComma]){ syntaxError(token__CONST, "const expression missing"); _ERROR_ }

	  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
			nComma++;
		} else {

			for (int i = nComma; i >= 0; i--){

        int nVar = registerClassConst(getClass(), acIdentifier[i], bTerm_PUBLIC ? token__PUBLIC : token__PRIVATE);
    		if (nVar == 0){ semanticError(token__CONST, utility::con(utility::ident(getClass(), acIdentifier[i]), " already declared at some place") ); _ERROR_ }
			  //if (nVar == 0){ internalError(utility::con(utility::ident(getClass(), acIdentifier[i]), " could not be declared") ); _ERROR_ }

     		if (bProducePcode){
     			 p->wr_CONST(pcode__CONST, nVar, getScopeCode());
      		 p->wr_MOV_CONST(pcode__MOV_CONST, nVar, getScopeCode()); // write pcode
     		}

     		parseInfo(p, utility::con("parsed CLASS CONST", acIdentifier[i], "") );

			}

   		return true;

 		}
	}

	_END_
}

/**
[EXPLANATION]
NAME: CLASS
DESC: A class is used to create objects. It contains functions and subs and the related data definitions.
SEEALSO:
*/
// scan class header
bool parser::fREGISTER_CLASS()
{
	_TBEGIN_

	//_SCANBEGIN_

  if (fEOLREM());
  if (fEOF2());
  if (fVERSION());
  if (fFILENAME());  

	static /**/ bool bTerm_ABSTRACT;// = false;

  if (bTerm_ABSTRACT = parseTerm(token__ABSTRACT)){}

	static /**/ bool bTerm_PRIVATE;// = false;
	static /**/ bool bTerm_PUBLIC;// = false;

  
  
  switch(peekToken()){
    case token__PRIVATE:
      if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){ bTerm_PUBLIC = false; } 
      break;
    case token__PUBLIC:
      if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){ bTerm_PRIVATE = false; }
      break;
  }

  if (!bTerm_ABSTRACT && (bTerm_ABSTRACT = parseTerm(token__ABSTRACT))){}

	if (!(/*bTerm_CLASS = */parseTerm(token__CLASS))){ _TEND_ }

	static /**/ bool bTerm_CLASS;// = false;

	if (!bTerm_ABSTRACT && (bTerm_ABSTRACT = parseTerm(token__ABSTRACT))){}

	bool bIDENTIFIER = false;
	bool bIDENTIFIER2 = false;
	bool bTerm_INHERITS = false;
	bool bTerm_THROWS = false;
	bool bREM = false;
	bool bEOL = false;
	const char *acClass;
	const char *acExtend = acBaseClassName;
	pcode *p = 0;
	pcode *p_static = 0;
	
	bool bTerm_COMMA = false;
	bool bTerm_END = false;
	int nClass = 0;

	if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acClass)){
    static int nAgainstPointerLoss = 0;
    if (nAgainstPointerLoss >= 1024) _TEND_
    static XString sAgainstPointerLoss[1024];
    sAgainstPointerLoss[nAgainstPointerLoss] = acClass;
    acClass = sAgainstPointerLoss[nAgainstPointerLoss++].ascii();

/*
    if (strcmp(acClass, "frmAnmelden") == 0){
      acClass = acClass;
    }*/

  	if (bParserPhase0 && myClass->registered(acClass)){ semanticError(token__KEYWORD, utility::con(acClass, " class already declared at some place")); _TERROR_ }

    parseInfo(p, utility::con("------ CLASS ", acClass, " ------ ") );

	  int nType = findType(acClass);
		if (bParserPhase0 && nType > 0){ semanticError(token__KEYWORD, utility::con(acClass, " type/class already defined") ); _TERROR_ }
    
		if (bTerm_INHERITS = parseTerm(token__INHERITS)){
			if (!(bIDENTIFIER2 = fID_KEYWORD_OR_BUILTIN(&acExtend))){ syntaxError(token__CLASS, " missing parent class identifier after INHERITS" ); _TERROR_ }
    } else {
      acExtend = acBaseClassName;
    }
    if (strcmp(acExtend, "EVENT") == 0) acExtend = "Event"; // WORKAROUND binding name

		if (parseTerm(token__ALIAS)){ // new style of DLL including
  		if (!parseTerm(token__LIB)){ syntaxError(token__CLASS, " missing LIB after ALIAS" ); _TERROR_ }

      const char *ac = "";
	    if (!fSTRING(&ac)){ syntaxError(token__CLASS, " missing name of library after LIB" ); _TERROR_ }
      sCurrentLib = ac;

    } else {
      sCurrentLib = "";
    }

    
    
    if ((bEOL = fEOLREM())){			

      if (moduleExists(acClass)){ semanticError(token__KEYWORD, utility::con(acClass, ": The name already exists as a module. Rename your class.") ); _TERROR_ }
      
      int nId = 0;

      if (bParserPhase0){

		    p = new pcode(getCurrentFile());
		    p_static = new pcode(getCurrentFile());
        /*
        if (strcmp(acClass, "building") == 0){
          int i = 0;
          i++;
        }
*/
			  nId = registerClass(acClass, p, p_static, acExtend, bTerm_ABSTRACT);
       if (nId == 0){ semanticError(token__KEYWORD, utility::con(acClass, " class already declared at some place") ); _TERROR_ }

			  int n = registerType(acClass, token__PUBLIC, nId);
       if (n == 0){ internalError(utility::con(acClass, " class could not be registered as type") ); _TERROR_ }
      } else {
        nId = findClass(acClass);
        p = myClass->getPcode(nId);;
        p_static = myClass->getClassStaticPcode(nId);	 
      //  p_static->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nId);
      }

      if (bParserPhase0){
       _DONE_
      }

      int nParentId = myClass->getId(acExtend); // user defined parent class
      if (nParentId == 0) nParentId = (int) binding_map_class.getString(acExtend); // qt binding class

      // alle klassen werden am ende der registrierung nochmal durchgegangen um nParentId zu setzen, notwendig wenn reihenfolge der classendef. vertauscht ist
      myClass->setParentId(nId, nParentId);
      
      setScopeClass(acExtend, acClass);

			do {

       // eine klasse darf nur einen destructor haben 
       // und hat mind. einen constructor, der zur parent class passt 
       // = default constructor ohne parameter

				if (p && proceedParse()){          

          switch(peekToken()){
            case token__OPTION:
              if (fOPTION(0)) continue; // myPcode
              break;
            case token__CONST:
            case token__DIM:
            case token__PUBLIC:
            case token__PROTECTED:
            case token__PRIVATE:
            case token__STATIC:
                    if (fREGISTER_CLASS_CONST(myPcode)){ continue; } // attention! const before var
	              else if (fREGISTER_CLASS_VAR(p)){ continue; }
	              else if (fREGISTER_CLASS_STATICSCOPE(p_static)){ continue; } // myPcode represents global vars and consts, all consts are like static vars    
            case token__ABSTRACT:
            case token__TYPE:
              if (fREGISTER_CLASS_TYPE()){ continue; }
            case token__ENUM:
              if (fREGISTER_CLASS_ENUM()){ continue; }
            case token__PROPERTY:
            case token__SUB:
            case token__FUNCTION:
            case token__DECLARE:
            case token__CONSTRUCTOR:
            case token__DESTRUCTOR:
            case token__SIGNAL:
            case token__SLOT:            
				       if (fREGISTER_CLASS_METHOD()){ continue; }		 // must be the 2nd last!!		
              else if (fREGISTER_CLASS_PROPERTY()){ continue; } // must be the last!!
          }

					     if (fREM()){ continue; }
					else if (fEOL(false)){ continue; }
					else if (fCOL(false)){ continue; }
					else {
						if (bTerm_END = parseTerm(token__END))
						if (bTerm_CLASS = parseTerm(token__CLASS)){}
						break;
          }
/*

					     if (fREGISTER_CLASS_CONST(myPcode)){ continue; } // attention! const before var
                                                     // myPcode represents global vars and consts, all consts are like static vars
					else if (fREGISTER_CLASS_VAR(p)){ continue; }
					else if (fREGISTER_CLASS_STATICSCOPE(p_static)){ continue; } // myPcode represents global vars and consts, all consts are like static vars
					else if (fREGISTER_CLASS_ENUM()){ continue; }
					else if (fREGISTER_CLASS_TYPE()){ continue; }
				//	else if (fREGISTER_CLASS_STRUCTURE()){ continue; }
					else if (fREM()){ continue; }
					else if (fEOL(false)){ continue; }
					else if (fCOL(false)){ continue; }
					else if (fREGISTER_CLASS_METHOD()){ continue; }
					else if (fREGISTER_CLASS_PROPERTY()){ continue; } // must be the last!!
					else {
						if (bTerm_END = parseTerm(token__END))
						if (bTerm_CLASS = parseTerm(token__CLASS)){}
						break;
					}
					*/
				}

			} while (p && proceedParse());

      sCurrentLib = "";
      setScopeDefaultGlobal();

					 if (!bTerm_END){ syntaxError(token__CLASS, ""/*"missing END"*/); _TERROR_ }
			else if (!bTerm_CLASS){ syntaxError(token__CLASS, "missing CLASS"); _TERROR_ }
			
		}

  	if (!bIDENTIFIER){ syntaxError(token__CLASS, "class name missing"); _TERROR_ }
  	if (bTerm_INHERITS && !bIDENTIFIER2){ syntaxError(token__CLASS, "parent class name missing"); _TERROR_ }
		if (!bEOL){ syntaxError(token__CLASS, "EOL missing"); _TERROR_ }


    parseInfo(p, utility::con("registered CLASS ", acClass) );

		_TDONE_
		
  }

	sCurrentLib = "";
	_TEND_
}

// method body
bool parser::fCLASS_METHOD_BODY()
{
	return fSUB_BODY(true);
}

// method body
bool parser::fCLASS_PROPERTY_BODY()
{
	return fPROPERTY_BODY(true);
}

// ignore var, will be done later
bool parser::fCLASS_VAR()
{
	_TBEGIN_

	bool bTerm_PRIVATE = false;
	bool bTerm_PROTECTED = false;
	bool bTerm_PUBLIC = false;
	bool bTerm_STATIC = false;
	bool bTerm_DIM = false;


	if ((bTerm_STATIC = parseTerm(token__STATIC))){}

  bool bb = false;

  switch(peekToken()){
    case token__PUBLIC:
      if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){}
      break;
    case token__PROTECTED:
      if (bTerm_PROTECTED = parseTerm(token__PROTECTED)){}
      break;
    case token__PRIVATE:
      if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){} 
      break;
    case token__DIM:
      if (bTerm_DIM = parseTerm(token__DIM)){}
      break;
    default:
      bb = true;
      break;
  }


	if ((!bTerm_STATIC && (bTerm_STATIC = parseTerm(token__STATIC)))){}
	
  if (bb && !bTerm_STATIC){ _TEND_ }

  switch(peekToken()){
    case token__ABSTRACT:
    case token__SUB:
    case token__FUNCTION:
    case token__PROPERTY:
    //case token__STRUCTURE:
    case token__TYPE:
    case token__ENUM:
    case token__SIGNAL:
    case token__SLOT:
    case token__CONSTRUCTOR:
    case token__DESTRUCTOR:
      _TEND_
  }
/*
	if (parseTerm(token__SUB)){ _TEND_ }
	if (parseTerm(token__FUNCTION)){ _TEND_ }
	if (parseTerm(token__PROPERTY)){ _TEND_ }
  if (parseTerm(token__STRUCTURE)){ _TEND_ }
  if (parseTerm(token__TYPE)){ _TEND_ }
  if (parseTerm(token__ENUM)){ _TEND_ }
  if (parseTerm(token__SIGNAL)){ _TEND_ }
  if (parseTerm(token__SLOT)){ _TEND_ }
  if (parseTerm(token__CONSTRUCTOR)){ _TEND_ }
  if (parseTerm(token__DESTRUCTOR)){ _TEND_ }

*/
	// ignore all until EOL or : is reached 
  while(proceedParse() && peekToken() != token__MSC_EOL && peekToken() != token__SYM_COLON && nextToken());

	_DONE_

}

// ignore const, will be done later
bool parser::fCLASS_CONST()
{
	_TBEGIN_


  switch(peekToken()){
    case token__PUBLIC:
      if (parseTerm(token__PUBLIC)){}
      break;
    case token__PROTECTED:
      if (parseTerm(token__PROTECTED)){}
      break;
    case token__PRIVATE:
      if (parseTerm(token__PRIVATE)){} 
      break;
  }

 
	//bool bTerm_CONST = false;

  if (!(/*bTerm_CONST = */parseTerm(token__CONST))){ _TEND_ }

	// ignore all until EOL or : is reached
  while(proceedParse() && peekToken() != token__MSC_EOL && peekToken() != token__SYM_COLON && nextToken());

	_DONE_

}

/* *
[EXPLANATION]
NAME: METHOD CALL
DESC:
SEEALSO:
*/
bool parser::fCLASS_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;

#ifdef KBDEBUG
  if (stopAtLine(26, "C:/kbasic17/kbide/examples/projects/demo_winzip.kbasic_project/configuration.kbasic_form")){
     int i = 9;
     i++;
  }
#endif

	if (fVARIABLE_DECLARED(p, &nVar, &scope, &nType)){

#ifdef KBDEBUG
    if (stopAtLine(114)){
      int i = 9;
      i++;
    }
#endif

    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fCLASS_METHOD_CALL", getCurrentLine() - 1));
    }


		 if (nType == token__ME){
			   if (bProducePcode) p->wr_PUSH_ME(pcode__PUSH_ME);
         nType = myClass->getId(getClass());
		 } else if (nType == token__PARENT){
			   if (bProducePcode) p->wr_PUSH_PARENT(pcode__PUSH_PARENT);        
         nType = myClass->getParentId(getClass());
     } else {        
 				 if (bProducePcode) p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
     }
			
   	 

    // constructor/destructor nicht direkt aufrufbar
    if (fMETHOD_CALL(p, nReturnExpressionType, bReturn, nType, false, false)){
  	   return true;
    }
	}


	const char *acMethod = "";
  bool bUnknownFunction = false;

#ifdef KBDEBUG
  if (stopAtLine(37)){
    int i = 9;
    i++;
  }
#endif


  if (bProducePcode){
	  p->wr_PUSH_ME(pcode__PUSH_ME);
  }
  nType = myClass->getId(getClass());

  // walk hierarchy
  do {

    // constructor/destructor nicht direkt aufrufbar
    if (fSUB_CALL(p, &acMethod, nReturnExpressionType, false, false, false, bReturn, true, nType, false, false)){
  	    return true;
    }
    _END2_

    if (bProducePcode){
	    p->wr_PUSH_ME(pcode__PUSH_ME);
    }
    nType = myClass->getParentId(nType);      

  } while (nType > 0);

  _END2_

  if (bProducePcode){
	  p->wr_PUSH_PARENT(pcode__PUSH_PARENT);        
  }
  nType = myClass->getParentId(getClass());


  // walk hierarchy
  do {

    // constructor/destructor nicht direkt aufrufbar
    if (fSUB_CALL(p, &acMethod, nReturnExpressionType, false, false, false, bReturn, true, nType, false, false)){
  	    return true;
    }
    _END2_

    if (bProducePcode){
	    p->wr_PUSH_PARENT(pcode__PUSH_PARENT);        
    }
    nType = myClass->getParentId(nType);      

  } while (nType > 0);

	_END_

}

/* *
[EXPLANATION]
NAME: STATIC METHOD CALL
DESC:
SEEALSO:
*/
bool parser::fCLASS_STATICMETHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	_BEGIN_

	int nType = 0;

  if (fVARIABLE_OR_CLASSNAME(p, &nType)){

    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fCLASS_STATICMETHOD_CALL", getCurrentLine() - 1));
    }

#ifdef KBDEBUG
      if (stopAtLine(22)){
       int i = 9;
       i++;
      }
#endif

     if (fMETHOD_CALL(p, nReturnExpressionType, bReturn, nType, true, false)){
  	     return true;
     }
   }

	_END_
}

// class body
bool parser::fCLASS_BODY()
{
	_TBEGIN_

	static /**/ bool bTerm_ABSTRACT;// = false;
  //bool bTerm_CLASS = false;

  if (bTerm_ABSTRACT = parseTerm(token__ABSTRACT)){}

	if (/*bTerm_CLASS = */parseTerm(token__CLASS)){

	  bool bIDENTIFIER = false;
	  bool bEOL = false;
	  bool bREM = false;

	  const char *acClass;
	  bool bTerm_SYM_BR_OP = false;
	  bool bTerm_SYM_BR_CL = false;
	  bool bTerm_SYM_BR_CL2 = false;
	  bool bSTATEMENTSEQUENCE = false;
	  bool bTerm_END = false;
	  bool bTerm_SUB2 = false;
	  pcode *p = 0;

	  bool bTerm_AS2 = false;
	  bool bTerm_CLASS2 = false;

	  bool bTerm_INHERITS = false;
	  bool bIDENTIFIER2 = false;
	  const char *acInherits = acBaseClassName;

		if (!bTerm_ABSTRACT && (bTerm_ABSTRACT = parseTerm(token__ABSTRACT))){}

		if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acClass)){

			if (bTerm_INHERITS = parseTerm(token__INHERITS)){
				if (!(bIDENTIFIER2 = fID_KEYWORD_OR_BUILTIN(&acInherits))){ syntaxError(token__CLASS, " missing class identifier after inherits" ); goto exit; }
				
    		int nClass = findClass(acInherits);
		 		if (nClass == 0){ semanticError(token__KEYWORD, utility::con(acInherits, " class not defined") ); goto exit; }

      } else {

		    if (parseTerm(token__ALIAS)){ // new style of DLL including
  		    if (!parseTerm(token__LIB)){ syntaxError(token__CLASS, " missing LIB after ALIAS" ); _TERROR_ }

          const char *ac = "";
	        if (!fSTRING(&ac)){ syntaxError(token__CLASS, " missing name of library after LIB" ); _TERROR_ }

          sCurrentLib = ac;

        } else {
          sCurrentLib = "";
        }
      }

      setScopeClass(acInherits, acClass);


   		if (!myClass->registered(acClass)){ semanticError(token__KEYWORD, utility::con(acClass, " class not declared")); goto exit; }
   		if (myClass->pcodeBuilt(acClass)){ semanticError(token__KEYWORD, utility::con(acClass, " class already declared & parsed")); goto exit; }

 			p = myClass->getPcode(acClass);

			if (bEOL = fEOLREM()){

        setScopeClass(acInherits, acClass);


        do {

  			        if (fREM()){}   
          else if (fOPTION(p)){} 

		      else if (fDEFINT());
		      else if (fDEFLNG());
		      else if (fDEFSNG());
		      else if (fDEFDBL());
		      else if (fDEFSTR());
		      else if (fDEFBOOL());
		      else if (fDEFBYTE());
		      else if (fDEFOBJ());
		      else if (fDEFVAR());
		      else if (fDEFCUR());
		      else if (fDEFDATE());

          else if (fEOL(false)){} // parse stand-alone EOL's - ATTENTION must be the last PRODUCTION of all here!
				   else if (fCOL(false)){} // parse stand-alone EOL's - ATTENTION must be the last PRODUCTION of all here!

				   else {
					    break;
				    }

	       } while (proceedParse());
          p = p;

					do {

  							 if (fREM()){}                
					  else if (fCLASS_STATICSCOPE()){} // myPcode represents global vars and consts, all consts are like static vars
                                             // ATTENTION must be the first here

            else if (fTYPE_BODY()); // already parsed
            else if (fENUM_BODY()); // already parsed
           // else if (fSTRUCTURE_BODY()); // already parsed

            else if (fCLASS_VAR()){} // already parsed
  					else if (fCLASS_CONST()){} // already parsed
						else if (fCLASS_METHOD_BODY()){} // method body
						else if (fCLASS_PROPERTY_BODY()){}

            //else if (fOPTION(p)){ syntaxError(token__OPTION, "OPTION must be before all other statements"); goto exit; } 

            else if (fEOL(false)){} // parse stand-alone EOL's - ATTENTION must be the last PRODUCTION of all here!
						else if (fCOL(false)){} // parse stand-alone EOL's - ATTENTION must be the last PRODUCTION of all here!
						else {
			     		if (bTerm_END = parseTerm(token__END))
							if (bTerm_CLASS2 = parseTerm(token__CLASS)){}
							if (!bTerm_END || !bTerm_CLASS2){ syntaxError(token__CLASS, "END CLASS missing"); goto exit; }
							break;
						}

					} while (proceedParse());
				


				myClass->setPcodeBuilt(acClass, true);

        sCurrentLib = "";
        setScopeDefaultGlobal();

				//parseInfo(p,  utility::con("parsed CLASS ", acClass) );
				return true;
			}

 		  if (!bEOL){ syntaxError(token__CLASS, "EOL missing"); goto exit; }
		}
		
		if (!bIDENTIFIER){ syntaxError(token__CLASS, "" /*sub name missing*/); goto exit; }
	}

exit:
  sCurrentLib = "";
  setScopeDefaultGlobal();
	_TEND_
}

// used if no constructor exists at all for the class
bool parser::fREGISTER_CLASS_DEFAULT_CONSTRUCTOR()
{
  return fREGISTER_CLASS_DEFAULT(true, false);
}

// used if no constructor exists at all for the class
bool parser::fREGISTER_CLASS_DEFAULT_DESTRUCTOR()
{
  return fREGISTER_CLASS_DEFAULT(false, true);
}

// used if no constructor exists at all for the class
bool parser::fREGISTER_CLASS_DEFAULT(bool bConstructor, bool bDestructor)
{
  const char *acClass = getClass();

  const char *acRealName = acClass;
  static /**/ char acName[MAX_IDENTIFIER + MAX_PARAM * 64]; // name[func/sub/cons/destr][pcode_type+array(true/false)...]


  if (bConstructor) sprintf(acName, "%s", token::keyword_(token__CLASS_INITIALIZE, false));
  if (bDestructor) sprintf(acName, "%s", token::keyword_(token__CLASS_TERMINATE, false));
  static char ac[1024];
  if (bConstructor){
    sprintf(ac, "%05d", token__SUB);
    strcat(acName, ac);
  }
  else if (bDestructor){
    sprintf(ac, "%05d", token__SUB);
    strcat(acName, ac);
  }
  
  if (myClass->registeredMethod(acClass, acName)) return true;


  if (bConstructor) sprintf(acName, "%s", token::keyword_(token__CLASS_INITIALIZE));
  if (bDestructor) sprintf(acName, "%s", token::keyword_(token__CLASS_TERMINATE));
  if (bConstructor){
    sprintf(ac, "%05d", token__SUB);
    strcat(acName, ac);
  }
  else if (bDestructor){
    sprintf(ac, "%05d", token__SUB);
    strcat(acName, ac);
  }
  
  if (myClass->registeredMethod(acClass, acName)) return true;


  sprintf(acName, "%s", acRealName);
  if (bConstructor){
    sprintf(ac, "%05d", token__CONSTRUCTOR);
    strcat(acName, ac);
  }
  else if (bDestructor){
    sprintf(ac, "%05d", token__DESTRUCTOR);
    strcat(acName, ac);
  }
  
  if (!myClass->registeredMethod(acClass, acName)){

    bool bTerm_FUNCTION = false;
    bool bTerm_SIGNAL = false;
    bool bTerm_SLOT = false;
    int nSkipHeaderTokenPos = 0;
    int nSkipHeaderLinePos = 0;  

    bool bTerm_STATIC = false;
    bool bTerm_ABSTRACT = false;

    int nClassId = myClass->getId(getClass());
    int nParentClassId = myClass->getParentId(nClassId);
    memory_sub *s = myClass->getMethods(acClass);

    if (memory_type::isBinding(nParentClassId) && s->exist(acClass, acName) == false){ // qt bindings sollen keinen default constructor haben
      if (s->first() && s->constructor(s->getId())){ // at least one constructor
        return true;
      }
    }

    const char *ac = myClass->getPcode()->sCurrentFile.ascii();

    pcode *p = new pcode(ac);
    int nId = myClass->addClassMethod(acClass, acRealName, acName, "", 
      pcode::pcode_(pcode__VOID), 0, p, 
      bTerm_FUNCTION, bConstructor, bDestructor, bTerm_SIGNAL, bTerm_SLOT, 
      0, token__PUBLIC, nSkipHeaderTokenPos, nSkipHeaderLinePos, bTerm_STATIC, bTerm_ABSTRACT, 
      ac, 0, false, "", "", "");

    if (my_cache && my_cache->parserOpened(ac)) my_cache->wr_memory_class_addClassMethod(ac, memory_class_addClassMethod, nId, acClass, acRealName, acName, "",
      pcode::pcode_(pcode__VOID), 0, p, bTerm_FUNCTION, bConstructor, bDestructor, bTerm_SIGNAL, bTerm_SLOT, 0, 
      token__PUBLIC, nSkipHeaderTokenPos, nSkipHeaderLinePos, bTerm_STATIC, bTerm_ABSTRACT, 
      ac, 0, false, "", "", "");

    if (nId == 0){ 
           if (bConstructor){ internalError("fREGISTER_CLASS_DEFAULT_CONSTRUCTOR"); _ERROR_ }
      else if (bDestructor){ internalError("fREGISTER_CLASS_DEFAULT_DESTRUCTOR"); _ERROR_ }
    }   
    
    autoCallParentConstructorDestructor(p, bConstructor, bDestructor, nId, s);
 
  	if (bConstructor) parseInfo(0, utility::con("registered CLASS DEFAULT CONSTRUCTOR ", acRealName) );
    else if (bDestructor) parseInfo(0, utility::con("registered CLASS DEFAULT DESTRUCTOR ", acRealName) );

  }

  return true;
}

// ignore already parsed static part of class
bool parser::fCLASS_STATICSCOPE()
{

  //register bool bTerm_STATIC = false;
  _TBEGIN_

  if (!(/*bTerm_STATIC = */parseTerm(token__STATIC))){ _TEND_ }

  if (!(fEOLREM())){ _TEND_ }

	register int nTest = 0;
	register int nTestPrev = 0;
	bool bRet = true;
	bool b = false;

  goto re;

	do {

		nTest = peekToken();

  	if (b && (nTestPrev == token__END && nTest == token__STATIC)){
 			nextToken();
			_DONE_
		}
		
		if ((nTestPrev != token__END 				
			&& (nTest == token__STATIC))
		){
re:
      b = true;
    }    
		
		nTestPrev = nTest;		

	} while(proceedParse() && bRet && (bRet = nextToken()));

  syntaxError(token__KEYWORD, "END STATIC missing");

  _TERROR_
}

bool parser::fCLASSNAME(pcode *p, const char **acIdentifier)
{
	_BEGIN_

	if (fID_KEYWORD_OR_BUILTIN(acIdentifier, false)){	

   if (myClass->exist(*acIdentifier) > 0) _DONE_

  }

  _END_
}
