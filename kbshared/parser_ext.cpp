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

#include "XFile.h"

char ac[1024];

extern XString cachePath(XString s);
extern XString kbasicPath(XString s);



/* *
[EXPLANATION]
NAME: SUB NAME
DESC:
SEEALSO:
*/
bool parser::fSUB_NAME(const char **acIdentifier)
{
	if (fID_STRING(acIdentifier)){ return true; } // because the identifier could have a suffix $
	if (parseTerm(token__CLASS_INITIALIZE)){ *acIdentifier = token::keyword_(token__CLASS_INITIALIZE); return true; }
	if (parseTerm(token__CLASS_TERMINATE)){ *acIdentifier = token::keyword_(token__CLASS_TERMINATE); return true; }
	if (fID_KEYWORD_OR_BUILTIN(acIdentifier)){ return true; }

	return false;
}

/* *
[EXPLANATION]
NAME: PROPERTY NAME
DESC:
SEEALSO:
*/
bool parser::fPROPERTY_NAME(const char **acIdentifier)
{
	if (fID_STRING(acIdentifier)){ return true; } // because the identifier could have a suffix $
	if (fID_KEYWORD_OR_BUILTIN(acIdentifier)){ return true; }

	return false;
}


/* *
[EXPLANATION]
NAME: METHOD CALL
DESC:
SEEALSO:
*/
bool parser::fMETHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn, int nClassId, bool bStaticMethod, bool bBothMethods)
{
	_BEGIN_

  //bool bTerm_SYM_DOT = false;

	if (/*bTerm_SYM_DOT = */parseTerm(token__SYM_DOT)){

    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fMETHOD_CALL", getCurrentLine() - 1));
    }

	  const char *acMethod = "";
    bool bUnknownFunction = false;

#ifdef KBDEBUG
    if (stopAtLine(22)){
      int i = 9;
      i++;
    }
#endif

    // constructor/destructor nicht direkt aufrufbar
	  do {
		  if (fSUB_CALL(p, &acMethod, nReturnExpressionType, false, false, &bUnknownFunction, bReturn, true, nClassId, bStaticMethod, bBothMethods)){

      	if (/*bTerm_SYM_DOT = */parseTerm(token__SYM_DOT)){ // test of verschachtelung: object.method().method2()
          return fMETHOD_CALL(p, nReturnExpressionType, bReturn, *nReturnExpressionType, bStaticMethod, bBothMethods);
       }

			  return true;
		  }

      // maybe a method of a parent class, walk object hierarchy
      
      int n = nClassId;
      //const char *ac = myClass->getName(nClassId);
		  nClassId = myClass->getParentId(nClassId);

      if (n == nClassId){ internalError( "While searching inheritance tree to find right method" ); _TERROR_ }

	  } while (nClassId != 0);
  }

	_END_
}

/* *
[EXPLANATION]
NAME: CONSTRUCTOR CALL
DESC:
SEEALSO:
*/
bool parser::fCONSTRUCTOR_CALL(pcode *p, int nClassId)
{
	//_BEGIN_

  //bool bTerm_SYM_DOT = false;
  const char *acMethod = "";

  int nReturnExpressionType = 0;
  bool bReturn = false;  
  bool bUnknownFunction = false;  
  bool bExplicitConstructorCall = true;  
  
  if (!bSilent && bProducePcode){
    p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fCONSTRUCTOR_CALL", getCurrentLine() - 1));
  }

//  do {
   // keine verschachtelung erlaubt
    if (fSUB_CALL(p, &acMethod, &nReturnExpressionType, true, false, &bUnknownFunction, bReturn, true, nClassId, false, false, bExplicitConstructorCall)){

      //if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){ // test of verschachtelung: object.method().method2()
       //return fCONSTRUCTOR_CALL(p, nReturnExpressionType);
      //}

		  _DONE_
	  }

    // maybe a method of a parent class, walk object hierarchy
	  //nClassId = myClass->getParentId(nClassId);

  //} while (nClassId != 0);

  return false;
	//_END_
}

/* *
[EXPLANATION]
NAME: CONSTRUCTOR CALL
DESC:
SEEALSO:
*/
bool parser::fDESTRUCTOR_CALL(pcode *p, int nClassId)
{
	//_BEGIN_

   //bool bTerm_SYM_DOT = false;
	 const char *acMethod = "";

   int nReturnExpressionType = 0;
   bool bReturn = false;    
   bool bUnknownFunction = false;       
   bool bExplicitDestructorCall = true;  
  
   if (!bSilent && bProducePcode){
     p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fDESTRUCTOR_CALL", getCurrentLine() - 1));
   }

	 //do {

   // keine verschachtelung erlaubt
		 if (fSUB_CALL(p, &acMethod, &nReturnExpressionType, false, true, &bUnknownFunction, bReturn, true, nClassId, false, false, false, bExplicitDestructorCall)){

      //if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){ // test of verschachtelung: object.method().method2()
          //return fDESTRUCTOR_CALL(p, nReturnExpressionType);
      //}

			 return true;
		 }

     // maybe a method of a parent class, walk object hierarchy   
		 //nClassId = myClass->getParentId(nClassId);

	 //} while (nClassId != 0);

 return false;
	//_END_
}

/* *
[EXPLANATION]
NAME: FUNCTION CALL
DESC:
SEEALSO:
*/
bool parser::fFUNCTION_CALL(pcode *p, const char **acIdentifier, int *nReturnExpressionType, bool bReturn, bool *bUnknownFunction)
{
	return fSUB_CALL(p, acIdentifier, nReturnExpressionType, false, false, bUnknownFunction, bReturn);
}

/* *
[EXPLANATION]
NAME: SUB CALL
DESC:
you do not need to use () to make a call
SEEALSO:
*/
bool parser::fSUB_CALL(pcode *p, const char **acIdentifier)
{
	register int nReturnExpressionType;// = 0;
  register bool bUnknownFunction;// = false; 

	return fSUB_CALL(p, acIdentifier, &nReturnExpressionType, false, false, &bUnknownFunction);
}


// in constructor aufruf anderer constructores, einmal mit me.constrname(), implicit parent..constrname(), aber nur in constructor erlaubt, dito fr destructor
// sub call
bool parser::fSUB_CALL(pcode *p, const char **acIdentifier, int *nReturnExpressionType, 
                       bool bConstructor, bool bDestructor, bool *bUnknownFunction, 
                       bool bReturn, bool bClassMethod, int nClassId, 
                       bool bStaticMethodOnly, bool bBothMethods, 
                       bool bExplicitConstructorCall, bool bExplicitDestructorCall, 
                       bool bSignalSlotDefinition)
{
	_BEGIN_


  
  bool bIDENTIFIER = false;
  bool bIDENTIFIER2 = false;
  
  bool bTerm_CALL = false;
  const char *acModule = "";
  
  // * needed, because recursive calls would otherwise mess up the myModule->first()...  iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR > parser__MAX_ITERATOR){
    internalError("Too many recursive calls inside fSUB_CALL. Try to split line into many lines."); goto myError;
  }

  
	switch(bClassMethod){
		case false:

      if (bReturn){
       if (!bSilent && bProducePcode){
   
          p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fFUNCTION_CALL", getCurrentLine() - 1));
       }
      } else {
       if (!bSilent && bProducePcode){
         p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fSUB_CALL", getCurrentLine() - 1));
       }
      }
      _BEGIN2_

	    if (fMODULENAME(p, &acModule)){
         
        if (!(parseTerm(token__SYM_DOT))){
          _END2_
          acModule = getModule();
        
        };

      }	else {
        acModule = getModule();
      }

/* *
[QBASIC][VB]
NAME: CALL
PRINTNAME: Call
TASK: Calls a sub routine
SYNTAX: CALL subname (parameters)
DESC: 
EXAMPLES: call.kbasic
CATEGORY: KEYWORD, CONTROLFLOW
SEEALSO: SUB, FUNCTION
VERSION: PERSONAL, PROFESSIONAL
LOG: 04-02-2004 implemented
TIP: It is obsolete, just provided for convience.
*/
     if (bTerm_CALL = parseTerm(token__CALL)){} // [QBASIC][VB]
			break;
		case true:
			break;
	}

#ifdef KBDEBUG
   if (stopAtLine(17)){
     int i = 9;
     i++;
   }
#endif

	if (bIDENTIFIER = fSUB_NAME(acIdentifier)){}

  if (bIDENTIFIER && bConstructor && !bExplicitConstructorCall){
    { semanticError(token__SUB, "Direct call of constructor not allowed. Possible call only with new CLASSNAME(...). See help class entry for more details."); goto myError; }
  }
  if (bIDENTIFIER && bDestructor && !bExplicitDestructorCall){
    { semanticError(token__SUB, "Direct call of destructor not allowed. Possible call only with new CLASSNAME(...). See help class entry for more details."); goto myError; }
  }

	if (bIDENTIFIER || bConstructor || bDestructor){

  	//bool bEXPRESSION = false;
  	bool bCOMMA = false;
  	bool bTerm_SYM_BR_OP = false;
  	bool bTerm_SYM_BR_CL = false;
		int nPos = 0;

  	bool bMaybeUnknownFunction = false;
    
		memory_sub *s = 0;
   	int nId = 0;
   	int nModuleId = 0;

    if (bProducePcode){
			nPos = p->getPos();
    }

#ifdef KBDEBUG
   if (stopAtLine(32)){
     int i = 9;
     i++;
   }
#endif

   const char *ac = "";
   int n = 0;
   bool bPublic = false;
   bool b1 = false;
   bool b2 = false;
   bool b3 = false;
   bool b4 = false;
   bool b5 = false;
   bool b7 = false;
   
   bool bb1 = false;
   bool bb2a = false;
   bool bb2 = false;

		switch(bClassMethod){
			case false:

#ifdef KBDEBUG
      if (stopAtLine(12)){
       int i = 9;
       i++;
      }
#endif

			   if (myModule->first(parser__ITERATOR)){
no:
         s = 0;
         {

           nModuleId = myModule->getId();

			     if (myModule->firstSub(parser__ITERATOR)){
				     do {

              nId = myModule->getIdSub();
              ac = myModule->getRealNameSub(nModuleId, nId);

					     n = myModule->getScopeSub(nModuleId, nId);
              bPublic = ((n == token__PUBLIC));

					     // must be same module or public; sub and return == false or function 
              b1 = bPublic;
              b2 = utility::my_stricmp(acModule, getScope()) == 0;
              b3 = bReturn;
              b4 = myModule->functionSub(nModuleId, nId);

					     if (!b3 || b4)
					     if (utility::my_stricmp(*acIdentifier, ac) == 0){
                
                if (!(b1 || b2)){ semanticError(token__SUB, "sub/function to call is not public"); goto myError; }

						     {
                   

#ifdef KBDEBUG
                 if (stopAtLine(109)){
                  int i = 9;
                  i++;
                 }
#endif

							     s = myModule->getSubs(nModuleId);
                   bMaybeUnknownFunction = true;
                  goto ex;

						     }
					     }
// retry
re: int i999 = 0;
               s = 0;
               p->setPos(nPos);
				     } while (myModule->nextSub(parser__ITERATOR));
           }

         }

         if (myModule->next(parser__ITERATOR)) goto no;
         *bUnknownFunction = bMaybeUnknownFunction & true;
       }

       
				break;
      case true:
			   if (bExplicitConstructorCall || bExplicitDestructorCall || myClass->first(parser__ITERATOR)){ 
           nPos = p->getPos();
no2:
         s = 0;
         p->setPos(nPos);

        if (bConstructor){

          if (bExplicitConstructorCall){
            myClass->gotoId(nClassId, parser__ITERATOR);
          }

          if (bExplicitConstructorCall || nClassId == myClass->getId())
			     if (myClass->firstConstructor(parser__ITERATOR)){
				     do {

              nId = myClass->getIdMethod();

					    n = myClass->getScopeMethod(nClassId, nId);
              bPublic = ((n == token__PUBLIC));

					     // must be same module or public; sub and return == false or function 
              b1 = bPublic || myClass->isSubClass(myClass->getId(getClass()), nClassId);
              b7 = myClass->isAbstractMethod(nClassId, nId);

              {                
                if (!b1){ semanticError(token__SUB, "constructor to call is not public"); goto myError; }
                if (b7){ semanticError(token__SUB, "constructor to call is ABSTRACT"); goto myError; }

					       s = myClass->getMethods(nClassId);
                goto ex;
					     }
// retry
re2c:;
               s = 0;
               p->setPos(nPos);
				     } while (myClass->nextConstructor(parser__ITERATOR));
           }

           if (!bExplicitConstructorCall && !bExplicitDestructorCall && myClass->next(parser__ITERATOR)) goto no2;
          } else if (bDestructor){

          if (bExplicitDestructorCall){
            myClass->gotoId(nClassId, parser__ITERATOR);
          }

          if (bExplicitDestructorCall || nClassId == myClass->getId())
			     if (myClass->firstDestructor(parser__ITERATOR)){
				     do {
               // destructor aufrufbar nur innerhalb eines passenden destructors

              nId = myClass->getIdMethod();

					    n = myClass->getScopeMethod(nClassId, nId);
              bPublic = ((n == token__PUBLIC)) || nClassId == myClass->getId(getClass()) || myClass->isSubClass(myClass->getId(getClass()), nClassId);

					     // must be same module or public; sub and return == false or function 
              b1 = bPublic;
              b2 = myClass->isStaticMethod(nClassId, nId);
              b7 = myClass->isAbstractMethod(nClassId, nId);
              {
                
                if (!b1){ semanticError(token__SUB, "destructor to call is not public"); goto myError; }
                if (b7){ semanticError(token__SUB, "destructor to call is ABSTRACT"); goto myError; }

					       s = myClass->getMethods(nClassId);
                goto ex;
					     }
// retry
re2d:;
               s = 0;
               p->setPos(nPos);
				     } while (myClass->nextDestructor(parser__ITERATOR));
           }

           if (!bExplicitConstructorCall && !bExplicitDestructorCall && myClass->next(parser__ITERATOR)) goto no2;
           
          } else {

#ifdef KBDEBUG
           if (stopAtLine(22)){
             int i = 9;
             i++;
           }
#endif

           if (nClassId == myClass->getId()){


             bb1 = false;

             if (bSignalSlotDefinition == false){
               bb1 = myClass->firstMethod(parser__ITERATOR);
             }

             bb2a = false;
             bb2 = false;

             if (bb1 == false) bb2a = bb2 = myClass->firstSlot(parser__ITERATOR);

			       if (bb1 || bb2){
				      do {

               nId = myClass->getIdMethod();
               ac = myClass->getRealNameMethod(nClassId, nId);

					      n = myClass->getScopeMethod(nClassId, nId);
               bPublic = ((n == token__PUBLIC));

					      // must be same module or public; sub and return == false or function 
               b1 = bPublic;
               b2 = nClassId == myClass->getId(getClass()) || myClass->isSubClass(myClass->getId(getClass()), nClassId);
          
               b3 = bReturn;
               b4 = myClass->functionMethod(nClassId, nId);
               b5 = myClass->isStaticMethod(nClassId, nId);
               b7 = myClass->isAbstractMethod(nClassId, nId);

               if ((b5 == bStaticMethodOnly || bBothMethods) && (!b3 || b4))
					      if (utility::my_stricmp(*acIdentifier, ac) == 0){
                  
                 if (!(b1 || b2)){ semanticError(token__SUB, "method to call is not public"); goto myError; }
                 if (b7){ semanticError(token__SUB, "method to call is ABSTRACT"); goto myError; }

#ifdef KBDEBUG
           if (stopAtLine(27)){
             int i = 9;
             i++;
           }
#endif
					        s = myClass->getMethods(nClassId);
                 goto ex;
					      }
  // retry
  re2: int ii = 0;
                 s = 0;
                 p->setPos(nPos);
                 if (bb1){
                   bb1 = myClass->nextMethod(parser__ITERATOR);
                 }    
                 if (bb1 == false){
                   if (bb2a == false){
                     bb2a = true;
                     bb2 = myClass->firstSlot(parser__ITERATOR);
                   } else {
                    bb2 = myClass->nextSlot(parser__ITERATOR);
                   }
                 }
				      } while (bb1 || bb2);
             }
           }

           if (myClass->next(parser__ITERATOR)) goto no2;
       }

      }
 			 break;
		}
ex:
		if (s == 0){
      goto myEnd;
		}

		if (!bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){}
		if (!bTerm_CALL && (isVERYOLDBASIC() && !bTerm_SYM_BR_OP)){ syntaxError(token__SUB, "( missing"); goto myError; }
		if (bTerm_CALL && (!isVERYOLDBASIC() && !bTerm_SYM_BR_OP)){ syntaxError(token__SUB, "( missing"); goto myError; }    

   	const char *acName = "";
   	const char *acType = "";
   	int nParameterCall = 0;
   	bool bOptional = false;
   	bool bDefault = false;    
    bool bParamArray = false;
   	t_array *a = 0;
		defaultvalue *defval = 0;
    int nParamId = 0;
    int nParamLStringLen = 0;

    int nParamArray = 0;


 		*nReturnExpressionType = findType(s->type(nId));

		bool bIDENTIFIER2[MAX_PARAM];
		const char *acIdentifier2[MAX_PARAM];
		bool bEXPRESSION[MAX_PARAM];    
		bool bISMISSING[MAX_PARAM]; 
    int nReferenceType[MAX_PARAM]; 
    

		bool bTerm_OP_EQUAL = false;
 		bool bTerm_SYM_COLON = false;
		int nComma = 0;

  	bool bTerm_SYM_BR_OP2 = false;
  	bool bTerm_SYM_BR_CL2 = false;
    bool bTerm_SYM_BS_OP2 = false;
    bool bTerm_SYM_BS_CL2 = false;
    t_long lLongInteger = 0;
		int nParamIndex[MAX_PARAM];

    for (int i = 0; i < MAX_PARAM; i++){ // init array 
      nParamIndex[i] = -1;
    }


#ifdef KBDEBUG
  if (stopAtLine(133)){
    int i = 3;
    i++;
  }
#endif

		bool b = false;

   // test for const, nicht als byref erlaubt; wird als byval-expression akzeptiert

		_BEGIN2_
		do {

	    if (bIDENTIFIER2[nComma] = fID_KEYWORD_OR_BUILTIN(&acIdentifier2[nComma])){

       if ((bTerm_SYM_BR_OP2 = parseTerm(token__SYM_BR_OP))){}
       if (!bTerm_SYM_BR_OP2 && (bTerm_SYM_BS_OP2 = parseTerm(token__SYM_BS_OP))){}

       bool bParamLongInteger = false;

       if (bTerm_SYM_BR_OP2 || bTerm_SYM_BS_OP2){ // e.g. b[1] := 777   ParamArray b

         lLongInteger = -1;

         if (fLONG(&lLongInteger)){ bParamLongInteger = true; }
                    
         nParamIndex[nParamArray] = lLongInteger;

         if (lLongInteger >= MAX_PARAM){
           { internalError("index value for ParamArray variable is too big"); _ERROR_ }
         }

         if (bTerm_SYM_BR_OP2 && (bTerm_SYM_BR_CL2 = parseTerm(token__SYM_BR_CL))){ 
           _END2_ break; } // might be UDF with array */  syntaxError(token__DIM, ") missing"); _ERROR_ }
 	       if (!bTerm_SYM_BR_CL2 && !(bTerm_SYM_BS_CL2= parseTerm(token__SYM_BS_CL))){ _END2_ break; } // might be UDF with array */   syntaxError(token__DIM, "] missing"); _ERROR_ }
       }


				if (bTerm_SYM_COLON = parseTerm(token__SYM_COLON)){
					if (bTerm_OP_EQUAL = parseTerm(token__OP_EQUAL)){

			      if (!s->getParameter	(nId, acIdentifier2[nComma], &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){ 
		            switch(bClassMethod){
			            case false:   
                       goto re;
				             break;
			            case true:
                  goto re2;
				            break;
		            }
           }

			      if (nComma == 0){
				      b = true;
			      }

           if (bParamArray){
             nParamArray++;
           }

           if ((bTerm_SYM_BR_OP2 || bTerm_SYM_BS_OP2) && !bParamLongInteger){ syntaxError(token__DIM, "index value (As Long) missing, e.g. b[0] = ..."); _ERROR_ }


           if (bTerm_SYM_BR_OP2 && bTerm_SYM_BR_OP2 && !bParamArray){ semanticError(token__SUB, "( or [ not allowed after variable name except for ParamArray"); _ERROR_ }
           
						if (!pushParam(p, nId, acIdentifier2[nComma], acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, bClassMethod, nClassId, nParamId, &bEXPRESSION[nComma], &bISMISSING[nComma], &nReferenceType[nComma])){ 
		          switch(bClassMethod){
			          case false:   
              goto re;
				          break;
			          case true:
              goto re2;
				          break;
		          }
           }

					} else { syntaxError(token__SUB, " = missing" ); goto myError; }
				} else {

					_END2_
					break;

				}

		  	nComma++;
			
			} else {
				if (nComma > 0){
					syntaxError(token__SUB, "variable missing" ); goto myError; 
				}

			}
		} while (bCOMMA = parseTerm(token__SYM_COMMA));

		// 1. named calling
		if (b == true){

      if (s->declare(nId)){ // extern library function call
        semanticError(token__SUB, "Named arguments are not possible when using extern library functions. Try to call it in default manner." ); goto myError; 
      }

			// *** test if all needed parameters are called 
   		if (s->firstParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){

    		do {

					bool b = false;
					for (int i = nComma - 1; i >= 0; i--){
						if (utility::my_stricmp(acName, acIdentifier2[i]) == 0){
							b = true; break;
						}
					}
					
					if (bParamArray == false && bOptional == false && bDefault == false && b == false){ /*syntaxError(token__SUB, utility::con(acName, " parameter missing") );*/
		        switch(bClassMethod){
			        case false:   
              goto re;
				        break;
			        case true:
         goto re2;
				        break;
		        }
          }

				} while(s->nextParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen));

			}
			// ***

      if (bProducePcode){
       switch (bClassMethod){
			    case false:   
           p->wr_ENTER_LOCAL(pcode__ENTER_LOCAL, nModuleId, nId); // write pcode
				    break;
			    case true:
           p->wr_ENTER_LOCAL(pcode__ENTER_LOCAL, nClassId, nId); // write pcode
				    break;
		    }        
      }

      // return function local var  
      if (!isKBASIC() && s->function(nId)){
        int nType = findType(s->type(nId));
        t_array a;
        int nVar = 0;
        int n = 0;

			   switch(bClassMethod){
				   case false:
            n = myModule->getId(s->getModule(nId));          
            nVar = myModule->getIdSubVar(s->getModule(nId), myModule->getNameSub(n, nId), myModule->getRealNameSub(n, nId));
					   break;
				   case true:
            n = myClass->getId(s->getModule(nId));
            nVar = myClass->getIdMethodVar(s->getModule(nId), myClass->getNameMethod(n, nId), myClass->getRealNameMethod(n, nId));
					   break;
			   }

        if (bProducePcode){
          p->wr_DIM(pcode__DIM, nVar, local, nType, false, false, false, false, 0, 0, "", false); // write pcode

          switch(nType){
            case pcode__QSTRING:
            case pcode__LQSTRING:
            case pcode__CSTRING:
            case pcode__LCSTRING:
             {
				         int nStatics = registerStringLiteral("");
				         if (nStatics == 0){ internalError( utility::con("", " string literal not declared") ); _ERROR_ }
                 p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStatics); 
                 break;
             }        
            default:
              p->wr_PUSH_LONG(pcode__PUSH_LONG, 0);
              break;
          }
          p->wr_MOV(pcode__MOV, nVar, local); // write pcode
        }
        
      }

      // sub body parts which fill the params
     bool bFirst = true;
			for (int i = nComma - 1; i >= 0; i--){
				
				if (!s->getParameter	(nId, acIdentifier2[i], &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){ 
		     switch(bClassMethod){
			     case false:   
         goto re;
				     break;
			     case true:
         goto re2;
				     break;
		     }
       }

       if (bParamArray){

         if (bFirst){

           bFirst = false;

	         int nType = findType(acType);
	         if (nType == 0){ semanticError(token__KEYWORD, utility::con(acType, " not defined") ); _ERROR_ }

           int nMax = 0;

           for (int i = 0; i < MAX_PARAM; i++){
               if (nParamIndex[i] > nMax) nMax = nParamIndex[i];
                
           }

	         if (bProducePcode){

            p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 0); // write pcode
            p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nMax); // write pcode
            p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode
            p->wr_REGISTER_ARRAY(pcode__REGISTER_ARRAY, 1, nType, nParamId, param, true, nBaseOfArray); // write pcode

            p->wr_DIM(pcode__DIM, nParamId, param, nType, false, false, true, false, 0, 0, "", false); // write pcode           
       
            for (int x = nParamArray; x >= 0; x--){

              int n = nParamIndex[x];

              if (n > -1){

                 p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, n); // write pcode
                 p->wr_ARRAY(pcode__ARRAY, 1, nType, nParamId, param, 0, true, false); // write pcode
       
                 p->wr_MOV(pcode__MOV, nParamId, param); // write pcode
              }
            }

           }
         }

       } else {
        	if (!popParam(p, nId, acIdentifier2[i], acType, nParameterCall, bOptional, bDefault, bParamArray, a, bClassMethod, nClassId, nParamId, bEXPRESSION[i], bISMISSING[i], nReferenceType[i])){ goto myEnd; }
       }

			}

			// missing arguments
   		if (s->lastParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){

       bEXPRESSION[0] = true;
       bISMISSING[0] = true;

       do {

         bool b = true;

			    for (int i = nComma - 1; i >= 0 && b == true; i--){
           if (utility::my_stricmp(acIdentifier2[i], acName) == 0){
             b = false;
           }
         }
         
         if (b){

          if (bParamArray){

	          int nType = findType(acType);
	          if (nType == 0){ semanticError(token__KEYWORD, utility::con(acType, " not defined") ); _ERROR_ }

	          if (bProducePcode){
 
              p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 0); // write pcode
              p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamArray > 0 ? nParamArray - 1 : 0); // write pcode
              p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode
           	 p->wr_REGISTER_ARRAY(pcode__REGISTER_ARRAY, 1, nType, nParamId, param, true, nBaseOfArray); // write pcode

              p->wr_DIM(pcode__DIM, nParamId, param, nType, false, false, true, false, 0, 0, "", false); // write pcode

              for (int x = 0; x < nParamArray; x++){

                p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamArray - x - 1); // write pcode
           	   p->wr_ARRAY(pcode__ARRAY, 1, nType, nParamId, param, 0, true, false); // write pcode

                p->wr_MOV(pcode__MOV, nParamId, param); // write pcode
              }

            }

          } else {
     				 if (!popParam(p, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, bClassMethod, nClassId, nParamId, bEXPRESSION[0], bISMISSING[0], nReferenceType[0])){ goto myEnd; }
          }          

         }

   			} while(s->prevParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen));
     }

		} else {
      nComma = 0;

			// 2. standard calling
 			bCOMMA = true;
   		if (s->firstParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){

    		do {

  				 if (bCOMMA == false){
						  if (bCOMMA = parseTerm(token__SYM_COMMA)){}
    				  if (!bCOMMA && bOptional == false && bDefault == false && bParamArray == false){ syntaxError(token__SUB, "syntax error"); goto myError; }
					 }

          bool b = bCOMMA;
          bool b2 = false;

          if (bParamArray){ // verarbeite paramArray, sub passt auf jeden fall, da paramArray letzter parameter sein muss

           do {

					    if (bCOMMA == false){
          	    if (bCOMMA = parseTerm(token__SYM_COMMA)){}
               b = bCOMMA;
             }             
             bCOMMA = false;

             if (b){
               b2 = pushParam(p, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, bClassMethod, nClassId, nParamId, &bEXPRESSION[nComma], &bISMISSING[nComma], &nReferenceType[nComma]);
             } else {
               b2 = false;
             }

             if (b2){
               nParamArray++;
             }

           } while (b && b2);
           
          } else {

             bCOMMA = false;

					    if (!pushParam(p, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, defval, bClassMethod, nClassId, nParamId, &bEXPRESSION[nComma], &bISMISSING[nComma], &nReferenceType[nComma])){ 
		             switch(bClassMethod){
			             case false:   
                  goto re;
				             break;
			             case true:
                goto re2;
				             break;
		             }
             }
          }
          nComma++;

				} while(s->nextParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen));
			}

      if (bProducePcode){
       switch (bClassMethod){
			    case false:   
           p->wr_ENTER_LOCAL(pcode__ENTER_LOCAL, nModuleId, nId); // write pcode
				    break;
         case true:
           if (bSignalSlotDefinition == false){
             p->wr_ENTER_LOCAL(pcode__ENTER_LOCAL, nClassId, nId); // write pcode
           }
				    break;
		    }        
      }

      // return function local var  
      if (!isKBASIC() && s->function(nId)){
        int nType = findType(s->type(nId));
        t_array a;
        int nVar = 0;
        int n = 0;

			  switch(bClassMethod){
				  case false:
           n = myModule->getId( s->getModule(nId) );          
           nVar = myModule->getIdSubVar(s->getModule(nId), myModule->getNameSub(n, nId), myModule->getRealNameSub(n, nId));
					  break;
				  case true:
           n = myClass->getId(s->getModule(nId));
           nVar = myClass->getIdMethodVar(s->getModule(nId), myClass->getNameMethod(n, nId), myClass->getRealNameMethod(n, nId));
					  break;
			  }

        if (bProducePcode){
          p->wr_DIM(pcode__DIM, nVar, local, nType, false, false, false, false, 0, 0, "", false); // write pcode

          switch(nType){
            case pcode__QSTRING:
            case pcode__CSTRING:
            case pcode__LQSTRING:
            case pcode__LCSTRING:
             {
				         int nStatics = registerStringLiteral("");
				         if (nStatics == 0){ internalError( utility::con("", " string literal not declared") ); _ERROR_ }
                 p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStatics); 
                 break;
             }        
            default:
              p->wr_PUSH_LONG(pcode__PUSH_LONG, 0);
              break;
          }
          p->wr_MOV(pcode__MOV, nVar, local); // write pcode
        }
      }

			// sub body parts which fill the params
      int i = nComma - 1;
   		if (s->lastParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){

				do {

          if (bParamArray){

	          int nType = findType(acType);
	          if (nType == 0){ semanticError(token__KEYWORD, utility::con(acType, " not defined") ); _ERROR_ }

	          if (bProducePcode){
 
              p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, 0); // write pcode
              p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamArray > 0 ? nParamArray - 1 : 0); // write pcode
              p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, true); // write pcode
           	 p->wr_REGISTER_ARRAY(pcode__REGISTER_ARRAY, 1, nType, nParamId, param, true, nBaseOfArray); // write pcode

              p->wr_DIM(pcode__DIM, nParamId, param, nType, false, false, true, false, 0, 0, "", false); // write pcode

              for (int x = 0; x < nParamArray; x++){

                p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamArray - x - 1); // write pcode
           	   p->wr_ARRAY(pcode__ARRAY, 1, nType, nParamId, param, 0, true, false); // write pcode

                p->wr_MOV(pcode__MOV, nParamId, param); // write pcode
              }

            }

          } else {
     				 if (!popParam(p, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, bClassMethod, nClassId, nParamId, bEXPRESSION[i], bISMISSING[i], nReferenceType[i])){ goto myEnd; }
          }
          i--;

   			} while(s->prevParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen));

			}
		}

    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){}			

#ifdef KBDEBUG
    if (stopAtLine(43)){
      int i = 9;
      i++;
    }
#endif

    if ((bTerm_SYM_BR_OP && bTerm_SYM_BR_CL) || !bTerm_SYM_BR_OP){     
    } else {
	    switch(bClassMethod){
		    case false:   
          goto re;
			    break;
		    case true:
         if (bConstructor){
           goto re2c;
         } else if (bDestructor){
           goto re2d;
         } else {
          goto re2;
         }
			    break;
	    }
    }

		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__SUB, ") missing"); goto myError; }

     if (bProducePcode){

			 switch(bClassMethod){
				 case false:
           if (s->declare(nId)){ // extern library function call

             p->wr_LIBCALL(pcode__LIBCALL, s->getLib(nId), s->getAlias(nId), *nReturnExpressionType, nComma, s->getLibCallSignature(nId)); // extern library function call

           } else {


             int nPcodePos = p->getPos();
					    s->registerCall(nId, p, nPcodePos);//, nPos);
      		    p->wr_CALL(pcode__CALL, 0, 0); // call address and return address of sub, later it will be the real address

              if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_registerCallSub(getCurrentFile(), memory_module_registerCallSub, myModule->getId(s->getModule(nId)), nId, p, nPcodePos);

              if (my_cache && myPcode != myPcodeAll) addDependency(p->sCurrentFile.ascii(), myModule->getFile(myModule->getId(s->getModule(nId))));


           }

          if (!bReturn && s->function(nId)){ // if return value is not used by caller
             p->wr_STACKPOP(pcode__STACKPOP); // write pcode
          }
					 break;
				 case true:
           if (s->declare(nId)){ // extern library function call

             p->wr_LIBCALL(pcode__LIBCALL, s->getLib(nId), s->getAlias(nId), *nReturnExpressionType, nComma, s->getLibCallSignature(nId)); // extern library function call

           } else {

            if (bSignalSlotDefinition){
              p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, false);
              p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nId);
				        int nStringLiteral = registerStringLiteral(myClass->getRealNameMethod(nClassId, nId));
   	 		        if (nStringLiteral == 0){ internalError( utility::con(ac, " string literal not declared") ); _ERROR_ }
  			        p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);						
            } else {

              if (bExplicitConstructorCall){
                bExplicitConstructorCall = bExplicitConstructorCall;
              }

					      if (s->isStatic(nId)){
						      p->wr_ClassStaticMethod(pcode__CLASSSTATICMETHOD, nClassId, nId, bReturn);
					      } else {
                  bool bParent = nClassId == myClass->getParentId(getClass());
						      p->wr_ClassMethod(pcode__CLASSMETHOD, nClassId, nId, myClass->getNameMethod(nClassId, nId), bConstructor, bDestructor, bParent, bReturn);
					      }

                if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(s->getModule(nId))));

              if (!bReturn && s->function(nId)){ // if return value is not used by caller
                  p->wr_STACKPOP(pcode__STACKPOP); // write pcode
              }
            }
           }

					 break;
			 }


   }

		  // throw stuff, nach call test auf exception, dann sprung zu exception label, 
		  // wenn kein label dann rcksprung zu parent sub, zurcksetzten des dann ungltigen assignments
      /*
        TRY
          test()
          ' if rumba gesetzt, goto catch rumba
          ' if not catched, return caller
          ' goto finally
        CATCH (b AS rumba)
          ' dim b as rumba = rumba
          PRINT "got you!"
          ' goto finally
        FINALLY
          PRINT "will be always executed, whatever happend"  
        END CATCH
      */


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

   	 if (bSignalSlotDefinition == false && s->firstThrow	(nId, &acType)){

    	  do {

          int nType = findType(acType);

          registerCatch(nId2, s2, nSubId2, p, nType);

          // exceptions der sub in exception liste einf+gen
          t_exception *t = new t_exception();

          t->acName =  acType;
          t->nLine = getCurrentLine();
          t->nRow = getCurrentRow();

          myException.add(t);			
    			
   		  } while(s->nextThrow	(nId, &acType));
     }


     if (bConstructor){
       parseInfo(p,  utility::con ("parsed CONSTRUCTOR CALL: ", s->getName(nId)));
     } else if (bDestructor){
       parseInfo(p,  utility::con ("parsed DESTRUCTOR CALL:  ", s->getName(nId)));
     } else {

			  switch(bClassMethod){
				  case false:
            parseInfo(p,  utility::con ("parsed SUB/FUNCTION CALL: ", s->getName(nId)));
					  break;
				  case true:
           if (bSignalSlotDefinition){
             parseInfo(p,  utility::con ("parsed SIGNAL/SLOT definition: ", s->getName(nId)));
           } else {
             parseInfo(p,  utility::con ("parsed METHOD CALL: ", s->getName(nId)));
           }
					  break;
			  }
     }

   goto myDone;
 
  }
   
myEnd:
  parser__ITERATOR--;
  _END_
myDone:
  parser__ITERATOR--;
  _DONE_
myError:
  parser__ITERATOR--;
  _ERROR_ 
}



/* *
[EXPLANATION]
NAME: ARGUMENT
DESC:
SEEALSO:
*/
bool parser::pushParam(pcode *p, int nSubId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, defaultvalue *defval, bool bClassMethod, int nClassId, int nParamId, bool *bEXPRESSION, bool *bISMISSING, int *nReferenceType)
{
  _BEGIN_ 

  bool bEXPRESSION2;// = false;

  *bISMISSING = false;

	register int nType = findType(acType);
	if (nType == 0){ semanticError(token__KEYWORD, utility::con(acType, " not defined") ); _ERROR_ }

	switch(nType){
		case pcode__BOOLEAN:
			if (nParameterCall == token__BY_REF){
						 if (fBOOLEAN_REFERENCE(p)){ *bEXPRESSION = false; }
				else if ((*bEXPRESSION = bEXPRESSION2 = fBOOLEAN_EXPRESSION(p)) || bOptional || bDefault){
																	
					if (bProducePcode){											

						if (!bEXPRESSION2 && bDefault){
							p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, defval->boolean_); // default value
             *bEXPRESSION = true;
           } else if (!bEXPRESSION2 && bOptional){
             *bISMISSING = true;
           }

					}
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fBOOLEAN_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){ if (bProducePcode) p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, defval->boolean_); }
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ } // return false; maybe function overloaded
			}
			break;
		case pcode__QSTRING:
		case pcode__CSTRING:
		case pcode__LQSTRING:
		case pcode__LCSTRING:
			if (nParameterCall == token__BY_REF){
						 if (fSTRING_REFERENCE(p, nReferenceType)){ *bEXPRESSION = false; }// parserError( utility::con(acName, " variable must be of type STRING") ); _END_ }
				else if ((*bEXPRESSION = bEXPRESSION2 = fSTRING_EXPRESSION(p)) || bOptional || bDefault){
					
					if (bProducePcode){					
						
						if (!bEXPRESSION2 && bDefault){
							int nStatics = registerStringLiteral(defval->cstring_);
   	 					if (nStatics == 0){ internalError( utility::con(defval->cstring_, " string literal not declared") ); _ERROR_ }
  						p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStatics);						
             *bEXPRESSION = true;
           } else if (!bEXPRESSION2 && bOptional){
             *bISMISSING = true;
           }

					}
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fSTRING_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){
					int nStringLiteral = registerStringLiteral(defval->cstring_);
   	 			if (nStringLiteral == 0){ internalError( utility::con(defval->cstring_, " string literal not declared") ); _ERROR_ }
  				if (bProducePcode) p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStringLiteral);						
				}
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ } // return false; maybe function overloaded
			}
			break;
		case pcode__BYTE:
			if (nParameterCall == token__BY_REF){
						 if (fBYTE_REFERENCE(p)){ *bEXPRESSION = false; }
				else if ((*bEXPRESSION = bEXPRESSION2 = fBYTE_EXPRESSION(p)) || bOptional || bDefault){
					
					if (bProducePcode){						

						if (!bEXPRESSION2 && bDefault){
							p->wr_PUSH_BYTE(pcode__PUSH_BYTE, defval->byte_); // default value
             *bEXPRESSION = true;
           } else if (!bEXPRESSION2 && bOptional){
             *bISMISSING = true;
           }

         }
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fBYTE_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){ if (bProducePcode) p->wr_PUSH_BYTE(pcode__PUSH_BYTE, defval->byte_); }
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ } // return false; maybe function overloaded
			}
			break;
		case pcode__SHORT:
			if (nParameterCall == token__BY_REF){
						 if (fSHORT_REFERENCE(p)){ *bEXPRESSION = false; }
				else if ((*bEXPRESSION = bEXPRESSION2 = fSHORT_EXPRESSION(p)) || bOptional || bDefault){
					
					if (bProducePcode){						

						if (!bEXPRESSION2 && bDefault){
							p->wr_PUSH_SHORT(pcode__PUSH_SHORT, defval->short_); // default value
             *bEXPRESSION = true;
           } else if (!bEXPRESSION2 && bOptional){
             *bISMISSING = true;
           }

         }
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fSHORT_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){ if (bProducePcode) p->wr_PUSH_SHORT(pcode__PUSH_SHORT, defval->short_); }
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ } // return false; maybe function overloaded
			}
			break;
		case pcode__INTEGER:
			if (nParameterCall == token__BY_REF){
						 if (fINTEGER_REFERENCE(p)){ *bEXPRESSION = false; }
				else if ((*bEXPRESSION = bEXPRESSION2 = fINTEGER_EXPRESSION(p)) || bOptional || bDefault){
					
					if (bProducePcode){						

						if (!bEXPRESSION2 && bDefault){
							p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, defval->integer_); // default value
             *bEXPRESSION = true;
           } else if (!bEXPRESSION2 && bOptional){
             *bISMISSING = true;
           }

         }
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fINTEGER_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){ if (bProducePcode) p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, defval->integer_); }
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ } // return false; maybe function overloaded
			}
			break;
		case pcode__LONG:
			if (nParameterCall == token__BY_REF){
						 if (fLONG_REFERENCE(p)){ *bEXPRESSION = false; }
				else if ((*bEXPRESSION = bEXPRESSION2 = fLONG_EXPRESSION(p)) || bOptional || bDefault){
					
					if (bProducePcode){					
						
						if (!bEXPRESSION2 && bDefault){
							p->wr_PUSH_LONG(pcode__PUSH_LONG, defval->long_); // default value
              *bEXPRESSION = true;
            } else if (!bEXPRESSION2 && bOptional){
              *bISMISSING = true;
            }

					}
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fLONG_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){ if (bProducePcode) p->wr_PUSH_LONG(pcode__PUSH_LONG, defval->long_); }
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ } // return false; maybe function overloaded
			}
			break;
		case pcode__SINGLE:
			if (nParameterCall == token__BY_REF){
						 if (fSINGLE_REFERENCE(p)){ *bEXPRESSION = false; }
				else if ((*bEXPRESSION = bEXPRESSION2 = fSINGLE_EXPRESSION(p)) || bOptional || bDefault){
																	
					if (bProducePcode){										

						if (!bEXPRESSION2 && bDefault){
							p->wr_PUSH_SINGLE(pcode__PUSH_SINGLE, defval->single_); // default value
             *bEXPRESSION = true;
           } else if (!bEXPRESSION2 && bOptional){
             *bISMISSING = true;
           }

					}
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fSINGLE_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){ if (bProducePcode) p->wr_PUSH_SINGLE(pcode__PUSH_SINGLE, defval->single_); }
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ } // return false; maybe function overloaded
			}
			break;
		case pcode__DOUBLE:
			if (nParameterCall == token__BY_REF){
						 if (fDOUBLE_REFERENCE(p)){ *bEXPRESSION = false; }// parserError( utility::con(acName, " variable must be of type DOUBLE") ); _END_ }
				else if ((*bEXPRESSION = bEXPRESSION2 = fDOUBLE_EXPRESSION(p)) || bOptional || bDefault){
					
					if (bProducePcode){					
						
						if (!bEXPRESSION2 && bDefault){
							p->wr_PUSH_DOUBLE(pcode__PUSH_DOUBLE, defval->double_); // default value
             *bEXPRESSION = true;
           } else if (!bEXPRESSION2 && bOptional){
             *bISMISSING = true;
           }

					}
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fDOUBLE_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){ if (bProducePcode) p->wr_PUSH_DOUBLE(pcode__PUSH_DOUBLE, defval->double_); }
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ }
			}
			break;
		case pcode__CURRENCY:
			if (nParameterCall == token__BY_REF){
						 if (fCURRENCY_REFERENCE(p)){ *bEXPRESSION = false; }
				else if ((*bEXPRESSION = bEXPRESSION2 = fCURRENCY_EXPRESSION(p)) || bOptional || bDefault){
					
					if (bProducePcode){						

						if (!bEXPRESSION2 && bDefault){
							p->wr_PUSH_CURRENCY(pcode__PUSH_CURRENCY, defval->currency_); // default value
             *bEXPRESSION = true;
           } else if (!bEXPRESSION2 && bOptional){
             *bISMISSING = true;
           }

         }
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fCURRENCY_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){ if (bProducePcode) p->wr_PUSH_CURRENCY(pcode__CURRENCY, defval->currency_); }
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ } // return false; maybe function overloaded
			}
			break;
		case pcode__DATE:
			if (nParameterCall == token__BY_REF){
						 if (fDATE_REFERENCE(p)){ *bEXPRESSION = false; }
				else if ((*bEXPRESSION = bEXPRESSION2 = fDATE_EXPRESSION(p)) || bOptional || bDefault){
					
					if (bProducePcode){						

						if (!bEXPRESSION2 && bDefault){
							p->wr_PUSH_DATE(pcode__PUSH_DATE, defval->date_); // default value
             *bEXPRESSION = true;
           } else if (!bEXPRESSION2 && bOptional){
             *bISMISSING = true;
           }

         }
				}
				else { _ERROR_ } // return false; maybe function overloaded
			} else {
				if (fDATE_EXPRESSION(p)){}
				else if (bOptional){ *bISMISSING = true; }
				else if (bDefault){ if (bProducePcode) p->wr_PUSH_DATE(pcode__DATE, defval->date_); }
				else if (bParamArray){ _DONE_ }
				else { _ERROR_ } // return false; maybe function overloaded
			}
			break;

    case pcode__ANY:
			if (fADDRESSOF(p, false)){
        *bEXPRESSION = false; 
      }
			else { _ERROR_ } // return false; maybe function overloaded
  		break;

    case pcode__VARIANT:
     if (bParamArray){
			  if (fEXPRESSION(p)){}
				else { _ERROR_ } // return false; maybe function overloaded
  			break;
     } else {
			  if (nParameterCall == token__BY_VAL){
				  if (fVARIANT_EXPRESSION(p)){}
				  else if (bOptional){ *bISMISSING = true; }
         else if (bDefault){ if (bProducePcode) p->wr_PUSH_LONG(pcode__PUSH_LONG, defval->long_); }
				  else if (bParamArray){ _DONE_ }
  				else { _ERROR_ } // return false; maybe function overloaded
  			  break;
       } else {
         // FALLTHROUGH
       }
     }
   default:	
     {
       bool bBindingOrClass = memory_type::isBinding(nType) || memory_type::isClass(nType);

			  if (nParameterCall == token__BY_REF){
						  if (bBindingOrClass == false && fREFERENCE(p, nType)){
                 *bEXPRESSION = false; 
                 _DONE_ }
				  else if ((*bEXPRESSION = fEXPRESSION2(p, nType))){
           _DONE_ }
			    else if (bOptional){ semanticError(token__SUB, utility::con(acName, " (OPTIONAL and BYREF) with non-scalar type not allowed") ); _ERROR_ }
				  else if (bDefault){ semanticError(token__SUB, utility::con(acName, " (default value and BYREF) with non-scalar type not allowed") ); _ERROR_ }
				  else if (bParamArray){ _DONE_ }
				  else { _ERROR_ } // return false; maybe function overloaded
			  } else {
				  { semanticError(token__SUB, utility::con(acName, " non-scalar with BYVAL is not allowed") ); _ERROR_ }
			  }
     }
			break;
	}

  _DONE_

}

bool parser::popParam(pcode *p, int nSubId, const char *acName, const char *acType, int nParameterCall, bool bOptional, bool bDefault, bool bParamArray, t_array *a, bool bClassMethod, int nClassId, int nParamId, bool bEXPRESSION, bool bISMISSING, int nReferenceType)
{

	register int nType = findType(acType);
	if (nType == 0){ semanticError(token__KEYWORD, utility::con(acType, " not defined") ); _ERROR_ }

	if (bProducePcode){

    register bool bBindingOrClass = memory_type::isBinding(nType) || memory_type::isClass(nType);

    // if bEXPRESSION is set: it is a reference, but only an expression has been passed
    if ((bBindingOrClass || nParameterCall == token__BY_VAL || bEXPRESSION)){
 	
      p->wr_DIM(pcode__DIM, nParamId, param, nType, false, false, false, false, 0, 0, "", false); // write pcode

      if (bISMISSING){
			   p->wr_MOV_ISMISSING(pcode__MOV_ISMISSING, nParamId, param);
      } else {
			   switch (nType){
       	   case pcode__BOOLEAN: p->wr_MOV_BOOLEAN(pcode__MOV_BOOLEAN, nParamId, param); break;

         case pcode__QSTRING:
					   p->wr_MOV_QSTRING(pcode__MOV_QSTRING, nParamId, param); break;
         case pcode__CSTRING:
					   p->wr_MOV_CSTRING(pcode__MOV_CSTRING, nParamId, param); break;
//         case pcode__LSTRING:
	//				   p->wr_MOV_LSTRING(pcode__MOV_LSTRING, nParamId, param); break;

         case pcode__BYTE: p->wr_MOV_BYTE(pcode__MOV_BYTE, nParamId, param); break;
         case pcode__SHORT: p->wr_MOV_SHORT(pcode__MOV_SHORT, nParamId, param); break;
         case pcode__INTEGER: p->wr_MOV_INTEGER(pcode__MOV_INTEGER, nParamId, param); break;
     	   case pcode__LONG: p->wr_MOV_LONG(pcode__MOV_LONG, nParamId, param); break;

         case pcode__SINGLE: p->wr_MOV_SINGLE(pcode__MOV_SINGLE, nParamId, param); break;
         case pcode__DOUBLE: p->wr_MOV_DOUBLE(pcode__MOV_DOUBLE, nParamId, param); break;

				   default:
            if (bBindingOrClass){

              p->wr_MOV(pcode__MOV, nParamId, param);

            } else {
              // copy user defined type
         	     p->wr_MOV_TYPE(pcode__MOV_TYPE, nParamId, param, true, 0); break;
            }
					   break;
     	   }
      }

		} else {
      if (nReferenceType == pcode__LQSTRING || nReferenceType == pcode__LCSTRING){
  		  p->wr_DIM(pcode__DIM, nParamId, param, nReferenceType, false, true, false, false, 0, 0, "", false); // write pcode
      } else {
  		  p->wr_DIM(pcode__DIM, nParamId, param, nType, false, true, false, false, 0, 0, "", false); // write pcode
      }

      if (bISMISSING){
			   p->wr_MOV_ISMISSING(pcode__MOV_ISMISSING, nParamId, param);
      } else {
     	  p->wr_MOV_IDREF(pcode__MOV_IDREF, nParamId, param);
      }

   }
	}

	return true;
}

/* *
[EXPLANATION]
NAME: FUNCTION RETURN
DESC:
SEEALSO:
*/
// functionname = returnvalue
bool parser::fFUNCTION_RETURN(pcode *p)
{

	_BEGIN_

	bool bIDENTIFIER;// = false;
	const char *acIdentifier;// = "";



	     if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)){}
	// because the identifier has a suffix $,%,&,#,!
	else if (bIDENTIFIER = fID_STRING(&acIdentifier)){}
	else if (bIDENTIFIER = fID_INTEGER(&acIdentifier)){}
	else if (bIDENTIFIER = fID_LONG(&acIdentifier)){}
	else if (bIDENTIFIER = fID_SINGLE(&acIdentifier)){}
	else if (bIDENTIFIER = fID_DOUBLE(&acIdentifier)){}
	else if (bIDENTIFIER = fID_CURRENCY(&acIdentifier)){}
	
	if (bIDENTIFIER){

	  bool bTerm__ = false;
	  bool bEXPRESSION = false;

	  t_arrayVariable a;
	  int nExpressionType = 0;

    if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fFUNCTION_RETURN", getCurrentLine() - 1));
    }

	  if (myModule->first()){ 

      do {
        if (utility::my_stricmp(getModule(), myModule->getName(myModule->getId())) == 0){

          int nModuleId = myModule->getId();

			    if (myModule->firstSub()){
            do {

				      int nId = myModule->getIdSub();

             const char *ac = myModule->getRealNameSub(nModuleId, nId);
				      if (utility::my_stricmp(acIdentifier, ac) == 0)

  			      if (bTerm__ = parseTerm(token__OP_EQUAL)){
	  			      if (myModule->functionSub(nModuleId, nId)){      					
						      
						      if (bEXPRESSION = fEXPRESSION(p, &nExpressionType, &a)){}
						      if (bEXPRESSION){

                   if (!compatibleType(nExpressionType, findType(myModule->typeSub(nModuleId, nId)))){ semanticError(token__SUB, utility::con(acIdentifier, " function has incompatible type to expression") ); _ERROR_ }

                   if (isKBASIC()){ syntaxError(token__RETURN, "You are using the old style of returning from function. Use 'return EXPRESSION' instead. See the documentation for more details. [Or place OPTION OLDBASIC on top of your program.]"); _ERROR_ }

							      _END_
						      }

	  				      if (!bEXPRESSION){ syntaxError(token__RETURN, "return expression missing"); _ERROR_ }

                } else { semanticError(token__THROW, "sub is not a function. Only a function can return a value."); _ERROR_ }
				      }
			      } while (myModule->nextSub());
		      }
       }
	    } while (myModule->next());
    }
	}

	_END_
}


/* *
[KBASIC][VB][QBASIC]
NAME: THROW
PRINTNAME: Throw
TASK: THROW
SYNTAX: THROW
DESC: THROW
CODE:
EXAMPLES: throw.kbasic
CATEGORY: KEYWORD, CONTROLFLOW, ERROR
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fTHROW(pcode *p)
{
	
	//register bool bTerm_THROW = false;
  _BEGIN_
  if (!(/*bTerm_THROW = */parseTerm(token__THROW))){ _END_ }



   if (!bSilent && bProducePcode){
      p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fTHROW", getCurrentLine() - 1));
   }

	if (getScopeCode() != global){

		bool bEXPRESSION = false;
    int nExpressionType = 0;

		if (!(bEXPRESSION = fOBJECT_EXPRESSION(p, &nExpressionType))){ syntaxError(token__THROW, "missing expression"); _ERROR_ }

		memory_sub *s = 0;
		const char *acModule = "";
		int nId = 0;

		if (isScopeClass()){

			s = myClass->findClass(getClass())->mySub;
			nId = s->getId(getClass(), getSub());

		} else if (isScopeModule() || isScopeDefaultGlobal()){

			s = myModule->findModule(getModule())->mySub;
			nId = s->getId(getModule(), getSub());
   }

		const char *acType = "";

   	if (s->firstThrow	(nId, &acType)){

    	do {

		   	 int nType = findType(acType);

        if (nType == nExpressionType){

          if (bProducePcode){

			       p->wr_CALL_RETURN(pcode__CALL_RETURN, isScopeClass()); // return to caller pcode
            
          }

 					  parseInfo(p, "parsed THROW");
 					  _DONE_

        }
   		} while(s->nextThrow	(nId, &acType));
		  
      { semanticError(token__THROW, utility::con("sub/function/method does not throw '", findType(nExpressionType),"' in declaration")); _ERROR_ }
		} else { semanticError(token__THROW, "sub/function/method does not throw anything in declaration"); _ERROR_ }

	} else {
		{ semanticError(token__THROW, "THROW must be used inside sub/function/method"); _ERROR_ }
	}

	_END_
}


// scan sub header
bool parser::fREGISTER_SUB()
{
  register bool bAbstract = false;
  register bool bDeclare = false;

	return fREGISTER_SUB(false, &bAbstract, &bDeclare);
}

// scan sub header
bool parser::fREGISTER_METHOD(bool *bAbstract, bool *bDeclare)
{
	return fREGISTER_SUB(true, bAbstract, bDeclare);
}

// possible issues of a sub: call, body, header
// scan sub header
bool parser::fREGISTER_SUB(bool bClassMethod, bool *bAbstract, bool *bDeclare)
{
	_TBEGIN_

	bool bTerm_ALIAS = false;
	bool bTerm_LIB = false;
	bool bTerm_DECLARE = false;
	bool bTerm_PRIVATE = false;
	bool bTerm_PUBLIC = false;
	bool bTerm_PROTECTED = false;
	bool bTerm_STATIC = false;  
	bool bTerm_ABSTRACT = false;
	bool bTerm_SUB = false;
	bool bTerm_FUNCTION = false;
	bool bTerm_CONSTRUCTOR = false;
	bool bTerm_DESTRUCTOR = false;
	bool bTerm_SIGNAL = false;
	bool bTerm_SLOT = false;
	bool bIDENTIFIER = false;
  const char *acRealName = "";
  const char *acLib = ""; 
  const char *acAlias = ""; 
  static /**/ char acName[MAX_IDENTIFIER + MAX_PARAM * 64]; // name[func/sub/cons/destr][pcode_type+array(true/false)...]
  static /**/ char acLibCallSignature[MAX_IDENTIFIER + MAX_PARAM * 64];

  if (!isVERYOLDBASIC()){ 
    if ((bTerm_DECLARE = parseTerm(token__DECLARE))){}
    if (bTerm_STATIC = parseTerm(token__STATIC)){}
    if (bTerm_ABSTRACT = parseTerm(token__ABSTRACT)){}
    if (!bTerm_STATIC && (bTerm_STATIC = parseTerm(token__STATIC))){}
    if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){}
    if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){}
    if (bTerm_PROTECTED = parseTerm(token__PROTECTED)){}
    if (!bTerm_ABSTRACT && (bTerm_ABSTRACT = parseTerm(token__ABSTRACT))){}
    if (!bTerm_STATIC && (bTerm_STATIC = parseTerm(token__STATIC))){}
    if (!bTerm_ABSTRACT && (bTerm_ABSTRACT = parseTerm(token__ABSTRACT))){}
  }

  if (!bTerm_PRIVATE && !bTerm_PUBLIC && !bTerm_PROTECTED) bTerm_PUBLIC = true; // default is public

    if (!bTerm_DECLARE && (bTerm_DECLARE = parseTerm(token__DECLARE))){}

o:
    *bDeclare = bTerm_DECLARE;
    switch(peekToken()){
      case token__FUNCTION: bTerm_FUNCTION = parseTerm(token__FUNCTION); break;
      case token__SUB:      bTerm_SUB = parseTerm(token__SUB);      break;
      case token__CONSTRUCTOR:      bTerm_CONSTRUCTOR = parseTerm(token__CONSTRUCTOR);      break;
      case token__DESTRUCTOR:      bTerm_DESTRUCTOR = parseTerm(token__DESTRUCTOR);      break;
      case token__SIGNAL:      bTerm_SIGNAL = parseTerm(token__SIGNAL);      break;
      case token__SLOT:      bTerm_SLOT = parseTerm(token__SLOT);      break;
      case token__STATIC:      bTerm_STATIC = parseTerm(token__STATIC); goto o;      break;
      default:
         _TEND_ 
         break;
    }

    if (bTerm_DECLARE && bTerm_STATIC && strcmp(sCurrentLib.ascii(), "") != 0){
      bTerm_DECLARE = false; // WORKAROUND
    }

    if (bTerm_DECLARE && bTerm_PROTECTED){ syntaxError(token__DECLARE, "PROTECTED not allowed in DECLARE statement" ); _ERROR_ }
    if (bTerm_DECLARE && bTerm_STATIC){ syntaxError(token__DECLARE, "STATIC not allowed in DECLARE statement" ); _ERROR_ }
    if (bTerm_DECLARE && bTerm_ABSTRACT){ syntaxError(token__DECLARE, "ABSTRACT not allowed in DECLARE statement" ); _ERROR_ }
    if (bTerm_DECLARE && bTerm_CONSTRUCTOR){ syntaxError(token__DECLARE, "CONSTRUCTOR not allowed after DECLARE" ); _ERROR_ }
    if (bTerm_DECLARE && bTerm_DESTRUCTOR){ syntaxError(token__DECLARE, "DESTRUCTOR not allowed after DECLARE" ); _ERROR_ }
    if (bTerm_DECLARE && bTerm_SIGNAL){ syntaxError(token__DECLARE, "SIGNAL not allowed after DECLARE" ); _ERROR_ }
    if (bTerm_DECLARE && bTerm_SLOT){ syntaxError(token__DECLARE, "SLOT not allowed after DECLARE" ); _ERROR_ }



	if (bIDENTIFIER = fSUB_NAME(&acRealName)){


    if (bClassMethod && strcmp(sCurrentLib.ascii(), "") != 0){
      if (!bTerm_DECLARE && !bTerm_STATIC){ semanticError(token__DECLARE, "You must not declare non-static methods inside a ALIAS LIB class for DLL/SO accessing."); _ERROR_ }  
      if (bTerm_DECLARE && !bTerm_STATIC){ semanticError(token__DECLARE, "You must not declare non-static methods inside a ALIAS LIB class for DLL/SO accessing."); _ERROR_ }  
    }

    if (bTerm_DECLARE && (bTerm_LIB = parseTerm(token__LIB))){}
    if (bTerm_DECLARE && !bTerm_LIB){ 

      // skip line, because it is old style declare
	    do {

		    if (peekToken() == token__MSC_EOL){
          _DONE_;      
		    }

	    } while(proceedParse() && nextToken());
    }

    if (bClassMethod && !bTerm_STATIC && strcmp(sCurrentLib.ascii(), "") != 0){ semanticError(token__DECLARE, "You cannot declare non-static methods inside a ALIAS LIB class for DLL/SO accessing."); _ERROR_ }  

    if (bTerm_DECLARE || strcmp(sCurrentLib.ascii(), "") != 0){

       if (bTerm_DECLARE && fSTRING(&acLib)){ 
  	      register int nStringLiteral = findStringLiteral(acLib);
   	      if (nStringLiteral == 0){ internalError( utility::con(acLib, " string literal not declared") ); _ERROR_ }
       } else if (bTerm_DECLARE){ syntaxError(token__DECLARE, "missing library name" ); _ERROR_ }

       if (strcmp(sCurrentLib.ascii(), "") != 0){
         acLib = sCurrentLib.ascii();
  	      register int nStringLiteral = findStringLiteral(sCurrentLib.ascii());
   	      if (nStringLiteral == 0){ internalError( utility::con(sCurrentLib.ascii(), " string literal not declared") ); _ERROR_ }
          bTerm_DECLARE = true; // switch for the rest of the lines in fake DECLARE-statement old-style
       }

       if ((bTerm_ALIAS = parseTerm(token__ALIAS))){

          if (fSTRING(&acAlias)){ 
  	          register int nStringLiteral = findStringLiteral(acAlias);
   	          if (nStringLiteral == 0){ internalError( utility::con(acAlias, " string literal not declared") ); _ERROR_ }
          } else { syntaxError(token__DECLARE, "missing alias name" ); _ERROR_ }

       } else {
         acAlias = acRealName;
       }
    
    }

   

    sprintf(acName, "%s", acRealName);
    sprintf(acLibCallSignature, "");   

         if (bTerm_FUNCTION){ sprintf(ac, "%05d", token__FUNCTION); strcat(acName, ac); }
    else if (bTerm_SUB){ sprintf(ac, "%05d", token__SUB); strcat(acName, ac); }
    else if (bTerm_CONSTRUCTOR){ sprintf(ac, "%05d", token__CONSTRUCTOR); strcat(acName, ac); }
    else if (bTerm_DESTRUCTOR){ sprintf(ac, "%05d", token__DESTRUCTOR); strcat(acName, ac); }
    else if (bTerm_SIGNAL){ sprintf(ac, "%05d", token__SIGNAL); strcat(acName, ac); }
    else if (bTerm_SLOT){ sprintf(ac, "%05d", token__SLOT); strcat(acName, ac); }

    if (bTerm_CONSTRUCTOR || bTerm_DESTRUCTOR){
      if (!isScopeClass()){ semanticError(token__CLASS, "CONSTRUCTOR or DESTRUCTOR not allowed outside class" ); _ERROR_ }
      
      // muss classname sein bei constructor oder destructor
      if (utility::my_stricmp(getClass(), acRealName) != 0){ semanticError(token__CLASS, "CONSTRUCTOR or DESTRUCTOR must have the same name as the related class" ); _ERROR_ }
    }

	  bool bTerm_THROWS = false;
	  static /**/ const char *acThrow[parser__MAX_THROW];
	  int nCommaThrow = 0;
	  bool bTerm_COMMA = false;

	  bool bEOL = false;
	  bool bREM = false;
	  bool bTerm_SYM_BR_OP = false;
	  bool bTerm_SYM_BR_CL = false;
	  bool bTerm_SYM_BR_CL2 = false;
	  pcode *p = 0;

	  static /**/ bool bPARAMETER[MAX_PARAM];
	  static /**/ bool bTerm_AS[MAX_PARAM];
	  static /**/ bool bTYPE[MAX_PARAM];

	  bool bTerm_AS2 = false;
	  bool bTYPE2 = false;
	  const char *acType2 = "";
	  int nSize2 = 0;

	  static /**/ const char *acParameter[MAX_PARAM];
	  static /**/ const char *acType[MAX_PARAM];
	  static /**/ int nSize[MAX_PARAM];
	  static /**/ bool bARRAY[MAX_PARAM];
	  static /**/ t_array a[MAX_PARAM];
	  static /**/ bool bTerm_OPTIONAL[MAX_PARAM];
	  static /**/ bool bTerm_DEFVAL[MAX_PARAM];
	  static /**/ bool bTerm_BY_REF[MAX_PARAM];
	  static /**/ bool bTerm_BY_VAL[MAX_PARAM];
	  static /**/ bool bTerm_PARAMARRAY[MAX_PARAM];    
	  static /**/ int nParamId[MAX_PARAM];
    memset(nParamId, 0, sizeof(nParamId));
	  static /**/ int nParamLStringLen[MAX_PARAM];
  	
	  const char *acCurrentType = 0;
	  int nComma = 0;
	  bool b = false;
	  bool bTerm_OP_EQUAL = false;
    XString sParam = "";
    XString sParamOriginal = "";
  	
	  static /**/ defaultvalue defval[MAX_PARAM];		

    bPARAMETER[nComma] = false;

 		p = new pcode(getCurrentFile());    

    int nLine = getCurrentLine(); // muss hier festgestellt werden, damit die Zeilennr durch EOL nicht verf�scht wird

	  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))
	  if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){ // either (  )
      if (isVERYOLDBASIC()) if (bTerm_ABSTRACT = parseTerm(token__ABSTRACT)){}
      goto registerSub;
		} 
    
		if (bEOL = fEOLREM()){
      if (isVERYOLDBASIC()) if (bTerm_ABSTRACT = parseTerm(token__ABSTRACT)){}
			goto registerSub;
		} else {

#ifdef KBDEBUG
  if (strcmp(acRealName, "monique") == 0){
    int i = 9;
    i = 9;
  }
#endif

nextParamWithDifferentType:
      	while (true){

					switch(bClassMethod){
						case false:
      				if (nComma >= MAX_PARAM){ internalError("too many parameters in sub/function definition"); _TERROR_ }
							break;
						case true:
      				if (nComma >= MAX_PARAM){ internalError("too many parameters in method definition"); _TERROR_ }
							break;
					}

					if (bTerm_OPTIONAL[nComma] = parseTerm(token__OPTIONAL)){}

          if (bTerm_DECLARE && bTerm_OPTIONAL[nComma]){ semanticError(token__DECLARE, "OPTINAL not allowed in DECLARE statement"); _TERROR_ }

					bTerm_BY_VAL[nComma] = false;
					bTerm_DEFVAL[nComma] = false;
					if (bTerm_BY_REF[nComma] = parseTerm(token__BY_REF)){}
					else if (bTerm_BY_VAL[nComma] = parseTerm(token__BY_VAL)){}

					b = bTerm_OPTIONAL[nComma];
					if (b == false && (bTerm_OPTIONAL[nComma] = parseTerm(token__OPTIONAL))){
						if (b){ semanticError(token__SUB, "OPTIONAL already used for this parameter"); _TERROR_ }
					}

					if (bTerm_PARAMARRAY[nComma] = parseTerm(token__PARAMARRAY)){
						if (bTerm_OPTIONAL[nComma]){ semanticError(token__SUB, "OPTIONAL not allowed with PARAMARRAY"); _TERROR_ }
						if (bTerm_BY_REF[nComma]){ semanticError(token__SUB, "BYREF not allowed with PARAMARRAY"); _TERROR_ }
						if (bTerm_BY_VAL[nComma]){ semanticError(token__SUB, "BYVAL not allowed with PARAMARRAY"); _TERROR_ }
					}
          if (bTerm_DECLARE && bTerm_PARAMARRAY[nComma]){ semanticError(token__DECLARE, "PARAMARRAY not allowed in DECLARE statement"); _TERROR_ }

      				 if (bPARAMETER[nComma] = fID_KEYWORD_OR_BUILTIN(&acParameter[nComma])){ bTerm_AS[nComma] = false; bTYPE[nComma] = false; }
      				// because the identifier has a suffix $,%,&,#,!, AS <TYPE> is not allowed, already found out
      		else if (bPARAMETER[nComma] = fID_STRING(&acParameter[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__QSTRING))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
      		else if (bPARAMETER[nComma] = fID_INTEGER(&acParameter[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__INTEGER))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
      		else if (bPARAMETER[nComma] = fID_LONG(&acParameter[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__LONG))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
      		else if (bPARAMETER[nComma] = fID_SINGLE(&acParameter[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__SINGLE))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
      		else if (bPARAMETER[nComma] = fID_DOUBLE(&acParameter[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__DOUBLE))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
      		else if (bPARAMETER[nComma] = fID_CURRENCY(&acParameter[nComma])){ acType[nComma] = findType(findType(pcode::pcode_(pcode__CURRENCY))); bTerm_AS[nComma] = true; bTYPE[nComma] = true; }
          else if (bPARAMETER[nComma] = fID_KEYWORD_OR_BUILTIN(&acParameter[nComma])){ bTerm_AS[nComma] = false; bTYPE[nComma] = false; }

      		if (bPARAMETER[nComma]){

#ifdef KBDEBUG
  if (strcmp(acParameter[nComma], "i2") == 0){
    int i = 9;
    i = 9;
  }
#endif
						if (bTerm_PARAMARRAY[nComma]){
						  if (!( (parseTerm(token__SYM_BR_OP)) && (parseTerm(token__SYM_BR_CL)) )){ syntaxError(token__SUB, "missing () after PARAMARRAY identifier"); _TERROR_ }
             a[nComma].setIsArray(true);  // needed for Sub(ParamArray b() As Variant)
             a[nComma].setCount(1);
             if (bTerm_SIGNAL || bTerm_SLOT){ semanticError(token__SUB, "SIGNAL or SLOT must not have PARAMARRAY as argument"); _TERROR_ }//  signal and slot drfen keine excetions throwen
						} else {

							if (bARRAY[nComma] = fREGISTER_ARRAY_CONST(p, acParameter[nComma], &a[nComma], false)){}
              if (bTerm_DECLARE && bARRAY[nComma]){ semanticError(token__DECLARE, "ARRAY not allowed in DECLARE statement"); _TERROR_ }

						}

            if (bTerm_BY_REF[nComma] && (bARRAY[nComma] || bTerm_PARAMARRAY[nComma])){
              //{ semanticError(token__SUB, "array not allowed after BYREF variable"); _TERROR_ }
            }

            if (bTerm_BY_VAL[nComma] && (bARRAY[nComma])){
              { semanticError(token__SUB, "array not allowed after BYVAL variable"); _TERROR_ }
            }

      			// check for AS, if %, &, !, # or $ is used, AS is not allowed, type already known
      			if (bTerm_AS[nComma] == true && (parseTerm(token__AS))){ semanticError(token__SUB, "type already known, parameter must not end with %, &, !, # or $"); _TERROR_ }
      			if (bTerm_AS[nComma] == false && (bTerm_AS[nComma] = parseTerm(token__AS)))
      			if (bTYPE[nComma] == false && (bTYPE[nComma] = fTYPE(p, &acType[nComma], false))){}

      			if (bTerm_AS[nComma] == false){ 
            //  syntaxError(token__SUB, "AS missing"); _TERROR_ 
              bTerm_AS[nComma] = true;
              bTYPE[nComma] = true;
              // no datatype -> variant is default
              acType[nComma] = findType(findType(pcode::pcode_(pcode__VARIANT)));
            }

            if (bTerm_DECLARE){
              int n = findType(acType[nComma]);

              if (n == pcode__VARIANT){
                { semanticError(token__DECLARE, "VARIANT as type not allowed in DECLARE statement"); _TERROR_ }
              } else if (memory_type::isType(n)){
              } else {
                switch(n){
                  case pcode__ANY:
                    bTerm_BY_REF[nComma] = true;
                    bTerm_BY_VAL[nComma] = false;
                  case pcode__BOOLEAN:
                  case pcode__CSTRING:
                  case pcode__BYTE:
                  case pcode__SHORT:
                  case pcode__INTEGER:
                  case pcode__LONG:
                  case pcode__SINGLE:
                  case pcode__DOUBLE:
                    break;
                  default:
                    { semanticError(token__DECLARE, "type not allowed in DECLARE statement. Use ANY, BOOLEAN, CSTRING, BYTE, SHORT, INTEGER, LONG, SINGLE or DOUBLE instead"); _TERROR_ }
                    break;
                }

              }

              if (n == pcode__CSTRING){ // strings always byref when DECLARE
                bTerm_BY_VAL[nComma] = false;
                bTerm_BY_REF[nComma] = true;
              }
            }


            if (nComma){
             sParam += ", ";
             sParam += acParameter[nComma];

             sParamOriginal += ", ";
             sParamOriginal += acParameter[nComma];
             if (bTYPE[nComma]){
               sParamOriginal += " As ";
               sParamOriginal += acType[nComma];               
             }

            } else {
             sParam += acParameter[nComma];

             sParamOriginal += acParameter[nComma];
             if (bTYPE[nComma]){
               sParamOriginal += " As ";
               sParamOriginal += acType[nComma];               
             }
            }

      			if (bTerm_AS[nComma] && !bTYPE[nComma]){ syntaxError(token__SUB, "type name missing"); _TERROR_ }

						if (bTerm_PARAMARRAY[nComma]){

      				if (bTYPE[nComma]){

         	  		int nType = findType(acType[nComma]);
        				if (nType == 0){ semanticError(token__DIM, utility::con(acType[nComma], " not defined") ); _TERROR_ }

								if (nType != pcode__VARIANT){
									{ semanticError(token__SUB, utility::con(acParameter[nComma], " must be of type VARIANT if used with PARAMARRAY") ); _TERROR_ }
								}
							}
						
						} else {
							
              {
								if (bTerm_OP_EQUAL = parseTerm(token__OP_EQUAL)){
									if (bARRAY[nComma]){
										{ syntaxError(token__DIM, "array can not have default value"); _TERROR_ }
									}
									if (bTerm_DECLARE){
										{ syntaxError(token__DECLARE, "= not allowed in DECLARE statement"); _TERROR_ }
									}

									if (bTerm_OPTIONAL[nComma]){
										{ syntaxError(token__DIM, "OPTIONAL cannot used with default value"); _TERROR_ }
									}

         	  			int nType = findType(acType[nComma]);
        					if (nType == 0){ semanticError(token__KEYWORD, utility::con(acType[nComma], " not defined") ); _TERROR_ }

									switch(nType){
										case pcode__BOOLEAN:
											if (!fBOOLEAN(&defval[nComma].boolean_)){ syntaxError(token__SUB, "missing default value"); _TERROR_ }
											break;
										
										case pcode__LONG:
											if (!fLONG(&defval[nComma].long_)){}
											else break;
											// FALLTRHOUGH
										case pcode__INTEGER:
                    if (!fINTEGER(&defval[nComma].integer_)){}
											else break;
											// FALLTRHOUGH
										case pcode__BYTE:
											if (!fBYTE(&defval[nComma].byte_)){ syntaxError(token__SUB, "missing default value"); _TERROR_ }
											break;

										case pcode__DOUBLE:
											if (!fDOUBLE(&defval[nComma].double_)){}
											else break;
											// FALLTRHOUGH
										case pcode__SINGLE:
											if (!fSINGLE(&defval[nComma].single_)){ syntaxError(token__SUB, "missing default value"); _TERROR_ }
											break;										
										case pcode__QSTRING:
										case pcode__CSTRING:
											{
												if (!fSTRING(&defval[nComma].cstring_)){ syntaxError(token__SUB, "missing default value"); _TERROR_ }
  											int nStringLiteral = findStringLiteral(defval[nComma].cstring_);
   											if (nStringLiteral == 0){ internalError( utility::con(defval[nComma].cstring_, " string literal not declared") ); _TERROR_ }
											}
											break;
										case pcode__VARIANT:
											if (fBOOLEAN(&defval[nComma].boolean_)) break;

											if (fSTRING(&defval[nComma].cstring_)){ 
  											int nStringLiteral = findStringLiteral(defval[nComma].cstring_);
   											if (nStringLiteral == 0){ internalError( utility::con(defval[nComma].cstring_, " string literal not declared") ); _TERROR_ }
											}

                    if (fBYTE(&defval[nComma].byte_)) break;
                    //if (fSHORT(&defval[nComma].short_)) break;
                    if (fINTEGER(&defval[nComma].integer_)) break;
											if (fLONG(&defval[nComma].long_)) break;

                    if (fSINGLE(&defval[nComma].single_)) break;
											if (fDOUBLE(&defval[nComma].double_)) break;

//                    if (fINT16(&defval[nComma].int16_)) break;
//                    if (fINT32(&defval[nComma].int32_)) break;
//                    if (fINT64(&defval[nComma].int64_)) break;
//                    if (fUINT16(&defval[nComma].uint16_)) break;
//                    if (fUINT32(&defval[nComma].uint32_)) break;
//                    if (fUINT64(&defval[nComma].uint64_)) break;

											if (fCURRENCY(&defval[nComma].currency_)) break;
											if (fDATE(&defval[nComma].date_)) break;

									//	case : 
										default:
											{ semanticError(token__SUB, "non-scalar type can not have default value"); _TERROR_ }
											break;

									}

                 bTerm_DEFVAL[nComma] = true;

								}
							}
						}

            // create unique name
            sprintf(ac, "%s%05ld%01d", acName, findType(acType[nComma]), bTerm_BY_REF[nComma] ? 0 : bTerm_BY_VAL[nComma] ? 1 : 0/*, bTerm_PARAMARRAY[nComma] || bARRAY[nComma]*/);
            sprintf(acName, ac);
            sprintf(ac, "%s%08ld %01d ", acLibCallSignature, findType(acType[nComma]), bTerm_BY_REF[nComma] ? 0 : bTerm_BY_VAL[nComma] ? 1 : 0); // BYREF is default
            sprintf(acLibCallSignature, ac);

      		  if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){
							if (bTerm_PARAMARRAY[nComma]){ syntaxError(token__SUB, " PARAMARRAY must be the last param" ); _TERROR_ }
							
      				nComma++;
      			} else {

      				// check the last parameter, must end with  "... AS <TYPE>"
      				if (bTerm_PARAMARRAY[nComma] == false && bPARAMETER[nComma] == true){
      							 if (!bTerm_AS[nComma]){ syntaxError(token__SUB, "AS missing"); _TERROR_ }
      					else if (!bTYPE[nComma]){ syntaxError(token__SUB, "type name missing"); _TERROR_ }
      				}

      			  if (bTerm_SYM_BR_CL2 = parseTerm(token__SYM_BR_CL)){

registerSub:
               *bAbstract = bTerm_ABSTRACT;

								if (bTerm_FUNCTION){
            			if (bTerm_AS2 == false && (bTerm_AS2 = parseTerm(token__AS)))
									if (bTerm_AS2 && bTYPE2 == false && (bTYPE2 = fTYPE(p, &acType2, false))){}
			      			if (bTerm_AS2 && !bTYPE2){ syntaxError(token__SUB, "function return type name missing"); _TERROR_ }
         				
                 if (!bTerm_AS2 || !bTYPE2){                                              
                    bTYPE2 = true;
                    acType2 = pcode::pcode_(nDefaultType); // qbasic: pcode__DOUBLE, vb6: pcode__VARIANT, kbasic: pcode__VARIANT
                  }
                if (bTerm_DECLARE){
                  int n = findType(acType2);
                  if (n == pcode__VARIANT){
                    { semanticError(token__DECLARE, "VARIANT as type not allowed in DECLARE statement"); _TERROR_ }
                  } else if (memory_type::isType(n)){
                  } else {
                    switch(n){
                      case pcode__ANY:
                      case pcode__BOOLEAN:
                      case pcode__CSTRING:
                      case pcode__BYTE:
                      case pcode__SHORT:
                      case pcode__INTEGER:
                      case pcode__LONG:
                      case pcode__SINGLE:
                      case pcode__DOUBLE:
                        break;
                      default:
                        { semanticError(token__DECLARE, "type not allowed in DECLARE statement. Use ANY, BOOLEAN, CSTRING, BYTE, SHORT, INTEGER, LONG, SINGLE or DOUBLE instead"); _TERROR_ }
                        break;
                    }

                  }
                }
                 
                 int n = findType(acType2);
                 if (memory_type::isType(n)){ semanticError(token__SUB, "function return type must not be user defined type"); _TERROR_ }
                 
								}

              // destructor darf keine parameter haben, gibt nur einen
              if (bTerm_DESTRUCTOR){
                if (bPARAMETER[0]){ semanticError(token__SUB, "DESTRUCTOR must not have arguements"); _TERROR_ }
              }

								if (bTerm_THROWS = parseTerm(token__THROWS)){
                 if (bTerm_SIGNAL || bTerm_SLOT){ semanticError(token__SUB, "SIGNAL or SLOT must not throw exceptions"); _TERROR_ }//  signal and slot drfen keine excetions throwen
                 if (bTerm_DECLARE){ semanticError(token__DECLARE, "DECLARE must not throw exceptions"); _TERROR_ }//  signal and slot drfen keine excetions throwen

									while (true){

										if (nCommaThrow >= parser__MAX_THROW){ internalError("too many throws sub/function definition"); _TERROR_ }

										if (!fID_KEYWORD_OR_BUILTIN(&acThrow[nCommaThrow])){ syntaxError(token__THROWS, "missing throw identifier"); _TERROR_ }

									  int nId = 0;

										if (bTerm_COMMA = parseTerm(token__SYM_COMMA)){				
      								nCommaThrow++;
										} else {
											break;
										}									
									}
								}

		            switch(bClassMethod){
			            case false:
                    if (bTerm_ABSTRACT){ semanticError(token__CLASS, utility::con(acRealName, " sub/function must not be ABSTRACT outside class definition")); _TERROR_ }
                    if (bTerm_PROTECTED){ semanticError(token__CLASS, utility::con(acRealName, " sub/function must not be PROTECTED outside class definition")); _TERROR_ }                    
  			            if (myModule->registeredSub(getModule(), acName)){ semanticError(token__CLASS, utility::con(acRealName, " sub/function with these parameters already declared at some place")); _TERROR_ }
				            break;
			            case true:

  			            if (myClass->registeredMethod(getClass(), acName)){ semanticError(token__CLASS, utility::con(acRealName, " method with these parameters already declared at some place")); _TERROR_ }
                    // mehrere constructoren mit gleichen namen, aber verschiedenen parametern erlaubt, 
                    // nur ein destructor erlaubt, aber gleichen namen
  										// kann auch beliebige parameter angeben, anders als in vb6
                    // nur bestimmte attribute bei constructor, destructor erlaubt, rckgabewert verboten

                    if ((utility::my_stricmp(acRealName, token::keyword_(token__CLASS_INITIALIZE)) == 0) || 
						            (utility::my_stricmp(acRealName, token::keyword_(token__CLASS_TERMINATE)) == 0)){

					            if (!bTerm_PRIVATE){ semanticError(token__CLASS, utility::con(acRealName, " must be PRIVATE")); _TERROR_ }
					            if (bTerm_STATIC){ semanticError(token__CLASS, utility::con(acRealName, " must not be STATIC")); _TERROR_ }
					            if (bTerm_FUNCTION){ semanticError(token__CLASS, utility::con(acRealName, " must not be FUNCTION or return a value")); _TERROR_ }
					            if (bTerm_CONSTRUCTOR){ semanticError(token__CLASS, utility::con(acRealName, " must not be CONSTRUCTOR or return a value")); _TERROR_ }
					            if (bTerm_DESTRUCTOR){ semanticError(token__CLASS, utility::con(acRealName, " must not be DESTRUCTOR or return a value")); _TERROR_ }
					            if (bTerm_SIGNAL){ semanticError(token__CLASS, utility::con(acRealName, " must not be SIGNAL or return a value")); _TERROR_ }
					            if (bTerm_SLOT){ semanticError(token__CLASS, utility::con(acRealName, " must not be SLOT or return a value")); _TERROR_ }

                     // tricky; make accessable for NEW classname
                     bTerm_PRIVATE = false; // for backward compatibility it has been parsed as true
                     bTerm_PUBLIC = true; // for backward compatibility set true

                     bTerm_FUNCTION = bTerm_SUB = bTerm_SIGNAL = bTerm_SLOT = false;

                     if (utility::my_stricmp(acRealName, token::keyword_(token__CLASS_INITIALIZE)) == 0){
                       bTerm_CONSTRUCTOR = true;
                     } else if (utility::my_stricmp(acRealName, token::keyword_(token__CLASS_TERMINATE)) == 0){
                       bTerm_DESTRUCTOR = true;
                     }

				            }

                    if (bTerm_ABSTRACT && bTerm_STATIC){
                      { semanticError(token__CLASS, utility::con(acRealName, " can not be ABSTRACT and STATIC, one of them must be choosen")); _TERROR_ }
                    }

                    if (bTerm_ABSTRACT){
                      if (!myClass->isAbstract(getClass())){ semanticError(token__CLASS, utility::con(getClass(), " class must be declared as ABSTRACT, if ABSTRACT is used for method declaration")); _TERROR_ }
                    }

										if ((utility::my_stricmp(acRealName, token::keyword_(token__CLASS_INITIALIZE)) == 0) || 
												(utility::my_stricmp(acRealName, token::keyword_(token__CLASS_TERMINATE)) == 0)){
                    
											if (nComma){ syntaxError(token__CLASS, utility::con(acRealName, " as initialize/terminate must not have parameters")); _TERROR_ } 
											if (bTerm_THROWS){ syntaxError(token__CLASS, utility::con(acRealName, " must not throw an exception")); _TERROR_ }
										}
  									if (nComma && bTerm_DESTRUCTOR){ syntaxError(token__CLASS, utility::con(acRealName, " as destructor must not have parameters")); _TERROR_ } 
                  if (bTerm_THROWS && (bTerm_CONSTRUCTOR || bTerm_DESTRUCTOR)){
											{ syntaxError(token__CLASS, utility::con(acRealName, " must not throw an exception, because it is a constructor/destructor")); _TERROR_ }
                  }

				            break;
		            }

                if (!bEOL) nLine = getCurrentLine(); // muss hier festgestellt werden, damit die Zeilennr durch EOL nicht verf�scht wird

      					if (bEOL == true || (bEOL = fEOLREM())){

									int nSkipHeaderTokenPos = getTokenPos();
									int nSkipHeaderLinePos = getCurrentLine();

									int nSubId = 0;
									class_ *c = 0;

									switch(bClassMethod){
										case false:											
											nSubId = registerModuleSub(getModule(), acRealName, acName, "", bTYPE2 ? (char *) acType2 : pcode::pcode_(pcode__VOID), nSize2, p, bTerm_FUNCTION, 0, bTerm_PRIVATE ? token__PRIVATE : token__PUBLIC, nSkipHeaderTokenPos, nSkipHeaderLinePos, bTerm_STATIC, bTerm_ABSTRACT, getCurrentFile(), nLine, bTerm_DECLARE, acAlias, acLib, acLibCallSignature);
      								if (nSubId == 0){ semanticError(token__KEYWORD, utility::con(acRealName, " sub with these parameters already declared at some place") ); _TERROR_ }
											break;
										case true:	
                    nSubId = myClass->addClassMethod(getClass(), acRealName, acName, "", bTYPE2 ? (char *) acType2 : pcode::pcode_(pcode__VOID), nSize2, p, bTerm_FUNCTION, bTerm_CONSTRUCTOR, bTerm_DESTRUCTOR, bTerm_SIGNAL, bTerm_SLOT, 0, bTerm_PRIVATE ? token__PRIVATE : bTerm_PUBLIC ? token__PUBLIC : token__PROTECTED, nSkipHeaderTokenPos, nSkipHeaderLinePos, bTerm_STATIC, bTerm_ABSTRACT, getCurrentFile(), nLine, bTerm_DECLARE, acAlias, acLib, acLibCallSignature);
      								if (nSubId == 0){ 
                      if (utility::my_stricmp(acRealName, token::keyword_(token__CLASS_INITIALIZE)) == 0){
                        semanticError(token__KEYWORD,  utility::con(acRealName, " class_initialize already declared at some place") ); _TERROR_ 
                      } else if (utility::my_stricmp(acRealName, token::keyword_(token__CLASS_TERMINATE)) == 0){
                        semanticError(token__KEYWORD,  utility::con(acRealName, " class_terminate already declared at some place") ); _TERROR_ 
                      } else {
                        if (bTerm_CONSTRUCTOR){
                          semanticError(token__KEYWORD,  utility::con(acRealName, " constructor with these parameters already declared at some place") ); _TERROR_ 
                        } else if (bTerm_DESTRUCTOR){
                          semanticError(token__KEYWORD,  utility::con(acRealName, " destructor already declared at some place") ); _TERROR_ 
                        } else if (bTerm_SIGNAL){
                          semanticError(token__KEYWORD,  utility::con(acRealName, " signal with these parameters already declared at some place") ); _TERROR_ 
                        } else if (bTerm_SLOT){
                          semanticError(token__KEYWORD,  utility::con(acRealName, " slot with these parameters  already declared at some place") ); _TERROR_ 
                        } else {
                          semanticError(token__KEYWORD,  utility::con(acRealName, " method with these parameters already declared at some place") ); _TERROR_ 
                        }
                      }
                    }
                      
                    if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addClassMethod(acCurrentFile, memory_class_addClassMethod, nSubId, getClass(), acRealName, acName, "", bTYPE2 ? (char *) acType2 : pcode::pcode_(pcode__VOID), nSize2, p, bTerm_FUNCTION, bTerm_CONSTRUCTOR, bTerm_DESTRUCTOR, bTerm_SIGNAL, bTerm_SLOT, 0, bTerm_PRIVATE ? token__PRIVATE : bTerm_PUBLIC ? token__PUBLIC : token__PROTECTED, nSkipHeaderTokenPos, nSkipHeaderLinePos, bTerm_STATIC, bTerm_ABSTRACT, getCurrentFile(), nLine, bTerm_DECLARE, acAlias, acLib, acLibCallSignature);

                    if (bTerm_DESTRUCTOR){
                      // merke destructor id
                      myClass->setDestructorId(myClass->getId(getClass()), nSubId);
                    }
											break;											
									}
									
									if (bTerm_THROWS){
        						for (int i = 0; i <= nCommaThrow; i++){ // iterate from last to first

                      int nId = 0;
											switch(bClassMethod){
												case false:
											    nId = myModule->addThrowSub(getModule(), acName, acThrow[i]);
      								    if (nId <= 0){ semanticError(token__THROWS, utility::con(acThrow[i], " is already thrown") ); _TERROR_ }

                          if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_addThrowSub(acCurrentFile, memory_module_addThrowSub, myModule->getId(getModule()), nSubId, acThrow[i]);

													break;
												case true:			
											    nId = myClass->addThrowMethod(getClass(), acName, acThrow[i]);
      								    if (nId <= 0){ semanticError(token__THROWS, utility::con(acThrow[i], " is already thrown") ); _TERROR_ }

                          if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addThrowMethod(acCurrentFile, memory_class_addThrowMethod, myClass->getId(getClass()), nSubId, acThrow[i]);

													break;											
											}
										}
									}
			      			if (bTerm_SYM_BR_CL2){

  									bool bTestOptional = false;

        						if (bTYPE[0] == false){ // if the first element is not explicitly declared
                      acCurrentType = pcode::pcode_(pcode__VARIANT);
                    }

        						for (int i = 0; i <= nComma; i++){ // iterate from last to first

        							const char *acVars = acParameter[i];

  										bTestOptional |= (bTerm_OPTIONAL[i] | bTerm_DEFVAL[i] | bTerm_PARAMARRAY[i]);

											if (bTestOptional != (bTerm_OPTIONAL[i] | bTerm_DEFVAL[i] | bTerm_PARAMARRAY[i])){ semanticError(token__KEYWORD, utility::con(acVars, " must be OPTIONAL or with default value") ); _TERROR_ }

        							if (bTYPE[i] == true){
        								acCurrentType = acType[i];
        							}

         	  			  	int nType = 0;

	     	  			  	  nType = findType(acCurrentType);

											// byval scalar only
                    if (bTerm_BY_VAL[i] && !memory_type::scalar(nType)){ semanticError(token__KEYWORD, utility::con(acVars, " is not a scalar and can not be passed BY VAL") ); _TERROR_ }
                    if (bTerm_OPTIONAL[i] && !memory_type::scalar(nType)){ semanticError(token__KEYWORD, utility::con(acVars, " is not a scalar and can not be passed as OPTIONAL") ); _TERROR_ }
                    if (bTerm_DEFVAL[i] && !memory_type::scalar(nType)){ semanticError(token__KEYWORD, utility::con(acVars, " is not a scalar and can not be passed with default arguments") ); _TERROR_ }


            					int nParameterCall = token__BY_REF; // default, but vb is BY_REF default, je nachdem ob variable oder expression bergeben wird, wird val oder ref ausgew�lt, k�nte bei expression und ref eine automatisch variable einfhren
  										if (bTerm_BY_REF[i]) nParameterCall = token__BY_REF;
            					else if (bTerm_BY_VAL[i]) nParameterCall = token__BY_VAL;       

                      const char *acc = getClass();

                      switch(bClassMethod){
												case false:
													if (myModule->hasParameterSub(myModule->getId(getModule()), nSubId, acVars)){ semanticError(token__KEYWORD, utility::con(acVars, " parameter already declared at some place") ); _TERROR_ }
													myModule->addParameterSub(myModule->getId(getModule()), nSubId, acVars, (char *) acCurrentType, nParameterCall, bTerm_OPTIONAL[i], bTerm_DEFVAL[i], bTerm_PARAMARRAY[i], &a[i], &defval[i], &nParamId[i], &nParamLStringLen[i]);

                          if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_addParameterSub(p->sCurrentFile.ascii(), memory_module_addParameterSub, myModule->getId(getModule()), nSubId, acVars, (char *) acCurrentType, nParameterCall, bTerm_OPTIONAL[i], bTerm_DEFVAL[i], bTerm_PARAMARRAY[i], &a[i], defval[i], nParamId[i], nParamLStringLen[i]);

													break;
												case true:									
													if (myClass->hasParameterMethod(myClass->getId(getClass()), nSubId, acVars)){ semanticError(token__KEYWORD, utility::con(acVars, " parameter already declared at some place") ); _TERROR_ }
													myClass->addParameterMethod(myClass->getId(getClass()), nSubId, acVars, (char *) acCurrentType, nParameterCall, bTerm_OPTIONAL[i], bTerm_DEFVAL[i], bTerm_PARAMARRAY[i], &a[i], &defval[i], &nParamId[i], &nParamLStringLen[i]);

                          if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addParameterMethod(p->sCurrentFile.ascii(), memory_class_addParameterMethod, myClass->getId(getClass()), nSubId, acVars, (char *) acCurrentType, nParameterCall, bTerm_OPTIONAL[i], bTerm_DEFVAL[i], bTerm_PARAMARRAY[i], &a[i], defval[i], nParamId[i], nParamLStringLen[i]);

                        // for bindings
                        if (bProducePcode){
                          XString classmethodno = myClass->getName(myClass->getId(getClass()));
                          classmethodno += acName;
                          sprintf(ac, "%d", i);
                          XString kk = ac;
                          classmethodno += kk;
                          
                          const char *acType; int nParameterCall; bool bOptional; bool bDefault; bool bParamArray; t_array *a; defaultvalue *defval; int nParamId;
                          myClass->getParameterMethod	(myClass->getId(getClass()), nSubId, acVars, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, nParamLStringLen);
/*
                          console::print(classmethodno.ascii());
                          console::print(" ");
                          console::print(nParamId);
                          console::print("\n");
*/
                          myPcodeAll->wr_CLASS_BINDINGPARAM(pcode__CLASS_BINDINGPARAM, myClass->getId(getClass()), classmethodno.ascii(), i, nParamId);

                          if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_bindingparam(p->sCurrentFile.ascii(), memory_class_bindingparam, myClass->getId(getClass()), classmethodno.ascii(), i, nParamId);

                        }
                        
													break;											
											}
        						}
									}							
      					}
								break;

      				} else goto nextParamWithDifferentType;

      			}

      		} else { syntaxError(token__SUB, "missing name of parameter" ); _TERROR_ }

        }

		}

		if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL && !bTerm_SYM_BR_CL2){ syntaxError(token__SUB, ") missing"); _TERROR_ }
		if (!bEOL){ syntaxError(token__SUB, "EOL missing"); _TERROR_ }


    // return function local var  
    if (!isKBASIC() && bTerm_FUNCTION){
      int nType = findType(acType2);
      t_array a;

		  switch(bClassMethod){
			  case false:
         setScopeModule(getModule(), acName, acRealName);
				  break;
			  case true:			
         setScopeClass(getParentClass(), getClass(), acName, acRealName);
				  break;											
		  }

      int nVar = registerVar(acRealName, nType, &a, false, false, token__PRIVATE, 0, true);
      nVar = nVar;

    }

		switch(bClassMethod){
			case false:
       if (isScopeDefaultGlobal()){
         if (bTYPE2){
    				parseInfo(p, utility::con("registered FUNCTION ", acRealName) );
         } else {
    				parseInfo(p, utility::con("registered SUB ", acRealName) );
         }
       } else if (isScopeModule()){
         if (bTYPE2){
    				parseInfo(p, utility::con("registered MODULE FUNCTION ", acRealName) );
         } else {
    				parseInfo(p, utility::con("registered MODULE SUB ", acRealName) );
         }
       }
				break;
			case true:									
       if (bTYPE2){
  				parseInfo(p, utility::con("registered CLASS FUNCTION ", acRealName) );
       } else {
  				parseInfo(p, utility::con("registered CLASS SUB ", acRealName) );
       }
				break;											
		}									

		return true;
  }
  if (!bIDENTIFIER){ syntaxError(token__SUB, "sub/function name missing"); _TERROR_ }

	_TEND_
}

/* *
[EXPLANATION]
NAME: PROPERTY
DESC:
SEEALSO:
*/
bool parser::fREGISTER_PROPERTY()
{
	_TBEGIN_

	bool bTerm_PRIVATE = false;
	bool bTerm_PUBLIC = false;

  switch(peekToken()){
    case token__PRIVATE: bTerm_PRIVATE = parseTerm(token__PRIVATE);      break;
    case token__PUBLIC:  bTerm_PUBLIC = parseTerm(token__PUBLIC);      break;
  }


	//bool bTerm_PROPERTY = false;

  if (!(/*bTerm_PROPERTY = */parseTerm(token__PROPERTY))){ _TEND_ }

  bool bClassMethod = true;

  if (!bTerm_PRIVATE && !bTerm_PUBLIC){ bTerm_PUBLIC = true; }

  bool bTerm_GET = false;
  bool bTerm_SET = false;
  bool bTerm_SYM_BR_OP = false;
  bool bTerm_SYM_BR_CL = false;

  if (bTerm_GET = parseTerm(token__GET)){}
  else if (bTerm_SET = parseTerm(token__SET)){}

	bool bIDENTIFIER = false;
  const char *acName = "";

	if (!(bIDENTIFIER = fPROPERTY_NAME(&acName))){ syntaxError(token__PROPERTY, "name of property is missing" ); _TERROR_ }
    

	bool bEOL = false;
	bool bREM = false;
	pcode *p = 0;

	bool bTerm_AS;
	bool bTYPE;

	bool bTerm_AS2 = false;
	bool bTYPE2 = false;
	const char *acType2 = "";

  bool bPARAMETER;

	const char *acParameter;
	const char *acType;
	int nSize;
	bool bTerm_BY_REF;
	bool bTerm_BY_VAL;
	bool bIgnoreRetry = false;
	bool bTerm_GET2 = false;
	bool bTerm_SET2 = false;

  if (bTerm_GET){
    if (strcmp(sCurrentLib.ascii(), "") != 0){ semanticError(token__DECLARE, "You cannot declare properties inside a ALIAS LIB class for DLL/SO accessing."); _ERROR_ }  

get:
    p = new pcode(getCurrentFile());

    bTerm_GET2 = true;
    bTerm_SET2 = false;
		if (myClass->registeredPropertyGet(getClass(), acName)){ syntaxError(token__PROPERTY, utility::con(acName, " property (GET) already declared at some place")); _TERROR_ }

    if (bTerm_GET){ // necessary, because of get: jump
      if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))
	    if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){ // either (  )
		  } 
      if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PROPERTY, ") missing " ); _TERROR_ }

      if (bTerm_AS2 = parseTerm(token__AS))
		  if (bTYPE2 = fTYPE(p, &acType2, false)){}
		  if (bTerm_AS2 && !bTYPE2){ syntaxError(token__PROPERTY, "property return type name missing"); _TERROR_ }
          if (!bTerm_AS2){ syntaxError(token__PROPERTY, "AS missing"); _TERROR_ }
      else if (!bTYPE2){ syntaxError(token__PROPERTY, "property return type name missing"); _TERROR_ }
    }

  } else if (bTerm_SET){
    if (strcmp(sCurrentLib.ascii(), "") != 0){ semanticError(token__DECLARE, "You cannot declare properties inside a ALIAS LIB class for DLL/SO accessing."); _ERROR_ }  
set:
    p = new pcode(getCurrentFile());

    bTerm_GET2 = false;
    bTerm_SET2 = true;
		if (myClass->registeredPropertySet(getClass(), acName)){ syntaxError(token__PROPERTY, utility::con(acName, " property (SET) already declared at some place")); _TERROR_ }

	  if (!(bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP))){ syntaxError(token__PROPERTY, "( missing " ); _TERROR_ }

		bTerm_BY_VAL = false;
		if (bTerm_BY_REF = parseTerm(token__BY_REF)){ semanticError(token__PROPERTY, "BYREF not allowed for property parameter" ); _TERROR_ }
		else if (bTerm_BY_VAL = parseTerm(token__BY_VAL)){}

    if (!bTerm_BY_VAL && !bTerm_BY_REF){ bTerm_BY_VAL = true; }

      	 if (bPARAMETER = fID_KEYWORD_OR_BUILTIN(&acParameter)){ bTerm_AS = false; bTYPE = false; }
      	 // because the identifier has a suffix $,%,&,#,!, AS <TYPE> is not allowed, already found out
    else if (bPARAMETER = fID_STRING(&acParameter)){ acType = findType(findType(pcode::pcode_(pcode__QSTRING))); bTerm_AS = true; bTYPE = true; }
    else if (bPARAMETER = fID_INTEGER(&acParameter)){ acType = findType(findType(pcode::pcode_(pcode__INTEGER))); bTerm_AS = true; bTYPE = true; }
    else if (bPARAMETER = fID_LONG(&acParameter)){ acType = findType(findType(pcode::pcode_(pcode__LONG))); bTerm_AS = true; bTYPE = true; }
    else if (bPARAMETER = fID_SINGLE(&acParameter)){ acType = findType(findType(pcode::pcode_(pcode__SINGLE))); bTerm_AS = true; bTYPE = true; }
    else if (bPARAMETER = fID_DOUBLE(&acParameter)){ acType = findType(findType(pcode::pcode_(pcode__DOUBLE))); bTerm_AS = true; bTYPE = true; }
    else if (bPARAMETER = fID_CURRENCY(&acParameter)){ acType = findType(findType(pcode::pcode_(pcode__CURRENCY))); bTerm_AS = true; bTYPE = true; }

    if (bPARAMETER){

      // check for AS, if %, &, !, # or $ is used, AS is not allowed, type already known
      if (bTerm_AS == true && (parseTerm(token__AS))){ semanticError(token__SUB, "type already known, parameter must not end with %, &, !, # or $"); _TERROR_ }
      if (bTerm_AS == false && (bTerm_AS = parseTerm(token__AS)))
      if (bTYPE == false && (bTYPE = fTYPE(p, &acType, false))){}

      if (bTerm_AS && !bTYPE){ syntaxError(token__PROPERTY, "type name missing"); _TERROR_ }

		} else { syntaxError(token__PROPERTY, "parameter name missing " ); _TERROR_ }


    if (!(bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL)))){ syntaxError(token__PROPERTY, ") missing " ); _TEND_ }

  } else { // other syntax - modern

 	  bTerm_SYM_BR_OP = false;
 	  bTerm_SYM_BR_CL = false;

	  if (bTerm_SYM_BR_OP = parseTerm(token__SYM_BR_OP)){

      if (bTerm_SYM_BR_OP && (bTerm_SYM_BR_CL = parseTerm(token__SYM_BR_CL))){}
   	  if (bTerm_SYM_BR_OP && !bTerm_SYM_BR_CL){ syntaxError(token__PROPERTY, ") missing"); _ERROR_ }
    }

    if (bTerm_AS2 = parseTerm(token__AS))
		if (bTYPE2 = fTYPE(p, &acType2, false)){}
		if (bTerm_AS2 && !bTYPE2){ syntaxError(token__PROPERTY, "property return type name missing"); _TERROR_ }
         if (!bTerm_AS2){ syntaxError(token__PROPERTY, "AS missing"); _TERROR_ }
    else if (!bTYPE2){ syntaxError(token__PROPERTY, "property return type name missing"); _TERROR_ }
retry:
		do {
		
			if (proceedParse()){

					   if (parseTerm(token__GET)){ goto get; }
				else if (parseTerm(token__SET)){ goto set; }
				else if (fREM()){}
				else if (fEOL(false)){}
				else if (fCOL(false)){}
				else {
          return bTerm_GET2 || bTerm_SET2;
				}
				
			}

		} while (proceedParse());

  }

  {

    int nSize2 = 0;

		int nSkipHeaderTokenPos = getTokenPos();
  	int nSkipHeaderLinePos = getCurrentLine();

		int nId = 0;
		class_ *c = 0;

    bool bTerm_FUNCTION = false;
    bool bTerm_STATIC = false;
    bool bTerm_ABSTRACT = false;
    bool bTerm_OPTIONAL = false;
    bool bTerm_DEFVAL = false;
    bool bTerm_PARAMARRAY = false;    
	  t_array a;
	  defaultvalue defval;			
    int nParamId = 0;
    int nParamLStringLen = 0;    


		switch(bClassMethod){
			case false:								
    			break;
			case true:		
        if (bTerm_GET2){

					nId = myClass->addClassPropertyGet(getClass(), acName, "", bTYPE2 ? (char *) acType2 : pcode::pcode_(pcode__VOID), nSize2, p, bTerm_FUNCTION, 0, bTerm_PRIVATE ? token__PRIVATE : token__PUBLIC, nSkipHeaderTokenPos, nSkipHeaderLinePos, bTerm_STATIC, bTerm_ABSTRACT, getCurrentFile(), getCurrentLine());
      		if (nId == 0){ syntaxError(token__PROPERTY, utility::con(acName, " property (GET) already declared at some place") ); _TERROR_ }

          if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addClassPropertyGet(acCurrentFile, memory_class_addClassPropertyGet, nId, getClass(), acName, "", bTYPE2 ? (char *) acType2 : pcode::pcode_(pcode__VOID), nSize2, p, bTerm_FUNCTION, 0, bTerm_PRIVATE ? token__PRIVATE : token__PUBLIC, nSkipHeaderTokenPos, nSkipHeaderLinePos, bTerm_STATIC, bTerm_ABSTRACT, getCurrentFile(), getCurrentLine());

        } else if (bTerm_SET2){
					nId = myClass->addClassPropertySet(getClass(), acName, "", bTYPE2 ? (char *) acType2 : pcode::pcode_(pcode__VOID), nSize2, p, bTerm_FUNCTION, 0, bTerm_PRIVATE ? token__PRIVATE : token__PUBLIC, nSkipHeaderTokenPos, nSkipHeaderLinePos, bTerm_STATIC, bTerm_ABSTRACT, getCurrentFile(), getCurrentLine());
      		if (nId == 0){ syntaxError(token__PROPERTY, utility::con(acName, " property (SET) already declared at some place") ); _TERROR_ }

          if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addClassPropertySet(acCurrentFile, memory_class_addClassPropertySet, nId, getClass(), acName, "", bTYPE2 ? (char *) acType2 : pcode::pcode_(pcode__VOID), nSize2, p, bTerm_FUNCTION, 0, bTerm_PRIVATE ? token__PRIVATE : token__PUBLIC, nSkipHeaderTokenPos, nSkipHeaderLinePos, bTerm_STATIC, bTerm_ABSTRACT, getCurrentFile(), getCurrentLine());

        }
				break;											
		}
		
		if (bTerm_SET2){

      const char *acCurrentType = 0;

      if (bTYPE == false){ // if the first element is not explicitly declared
        acCurrentType = pcode::pcode_(pcode__VARIANT); // variant = abh�gig ob kbasic, oder oldbasic aktiviert
      } else {
        acCurrentType = acType;
      }

      const char *acVars = acParameter;

      int nType = 0;
		  nType = findType(acCurrentType);

			// byval scalar only
			if (bTerm_BY_VAL && !myMemory_type->scalar(nType)){ syntaxError(token__PROPERTY,  utility::con(acVars, " is not a scalar and can not be BY VAL") ); _TERROR_ }

      int nParameterCall = token__BY_REF; //default, but vb is BY_REF default, je nachdem ob variable oder expression bergeben wird, wird val oder ref ausgew�lt, k�nte bei expression und ref eine automatisch variable einfhren
  		if (bTerm_BY_REF) nParameterCall = token__BY_REF;
      else if (bTerm_BY_VAL) nParameterCall = token__BY_VAL;

			switch(bClassMethod){
				case false:
					break;
				case true:									
					if (myClass->hasParameterPropertySet(myClass->getId(getClass()), nId, acVars)){ syntaxError(token__PROPERTY,  utility::con(acVars, " parameter already declared") ); _TERROR_ }
					myClass->addParameterPropertySet(myClass->getId(getClass()), nId, acVars, (char *) acCurrentType, nParameterCall, bTerm_OPTIONAL, bTerm_DEFVAL, bTerm_PARAMARRAY, &a, &defval, &nParamId, &nParamLStringLen);

          if (my_cache && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_addParameterPropertySet(acCurrentFile, memory_class_addParameterPropertySet, myClass->getId(getClass()), nId, acVars, (char *) acCurrentType, nParameterCall, bTerm_OPTIONAL, bTerm_DEFVAL, bTerm_PARAMARRAY, &a, defval, nParamId, nParamLStringLen);

					break;											
			}
    }							
  	
	  switch(bClassMethod){
		  case false:
        if (bTerm_SET2){
    			  parseInfo(p, utility::con("registered MODULE PROPERTY SET", acName) );
        } else {
    			  parseInfo(p, utility::con("registered MODULE PROPERTY GET", acName) );
        }
			  break;
		  case true:
        if (bTerm_SET2){
    			  parseInfo(p, utility::con("registered CLASS PROPERTY SET", acName) );
        } else {
    			  parseInfo(p, utility::con("registered CLASS PROPERTY GET", acName) );
        }
			  break;											
	  }			  

	  int nTest = 0;
	  int nTestPrev = 0;
    bool bRet = true;
    
    if (!bTerm_GET && bTerm_GET2){ 

      // ignore all token till END GET
	    do {
		    nTest = peekToken();
		    if (nTestPrev == token__END && nTest == token__GET){
          nextToken();
			    break;
		    }
		    nTestPrev = nTest;
	    } while(proceedParse() && bRet && (bRet = nextToken()));

    } else if (!bTerm_SET && bTerm_SET2){ 

  	  nTestPrev = 0;

      // ignore all token till END SET
	    do {
		    nTest = peekToken();
		    if (nTestPrev == token__END && nTest == token__SET){
          nextToken();
			    break;
		    }
		    nTestPrev = nTest;
	    } while(proceedParse() && bRet && (bRet = nextToken()));

    }

    if (!bTerm_GET && !bTerm_SET && !bIgnoreRetry){ 
      goto retry; 
    }

		return bRet;
  }

	_TEND_
}

bool parser::fPROPERTY_BODY()
{
	return fPROPERTY_BODY(false);
}


bool parser::fPROPERTY_BODY(bool bClassMethod)
{
	_TBEGIN_

  bool bTerm_PRIVATE = false;
	bool bTerm_PUBLIC = false;
	//bool bTerm_PROPERTY = false;

  switch(peekToken()){
    case token__PRIVATE: bTerm_PRIVATE = parseTerm(token__PRIVATE);      break;
    case token__PUBLIC:  bTerm_PUBLIC = parseTerm(token__PUBLIC);      break;
  }

  if (!(/*bTerm_PROPERTY = */parseTerm(token__PROPERTY))){ _TEND_}

	bool bTerm_GET = false;
	bool bTerm_SET = false;

  if (bTerm_GET = parseTerm(token__GET)){}
  else if (bTerm_SET = parseTerm(token__SET)){}

	bool bIDENTIFIER = false;

	bool bTerm_GET2 = false;
	bool bTerm_SET2 = false;
	bool bTerm_GET3 = false;
	bool bTerm_SET3 = false;

	bool bTerm_END;
  bool bTerm_PROPERTY2 = false;

  const char *ac = "";

  if (bIDENTIFIER = fPROPERTY_NAME(&ac)){
    sCurrentSub = ac;

	  if (!bTerm_GET && !bTerm_SET){

      // skip AS TYPE
	    // ignore all until EOL or : is reached
      while(proceedParse() && peekToken() != token__MSC_EOL && peekToken() != token__SYM_COLON && nextToken());

retry:
		  do {
  		
			  if (proceedParse()){

					     if ((bTerm_GET2 = parseTerm(token__GET))){ break; }
				  else if ((bTerm_SET2 = parseTerm(token__SET))){ break; }
				  else if (fREM()){}
				  else if (fEOL(false)){}
				  else if (fCOL(false)){}
				  else {

     	      if (bTerm_END = parseTerm(token__END))
            if ((bTerm_PROPERTY2 = parseTerm(token__PROPERTY))){}

		        if (!bTerm_END && !bTerm_PROPERTY2){ syntaxError(token__PROPERTY, "END PROPERTY missing"); goto exit; }      

            return bTerm_GET3 || bTerm_SET3;
				  }
  				
			  }

		  } while (proceedParse());

    }
    
    {
      
      bool bEOL = false;
	    bool bREM = false;

	    const char *acSub;

      bool bSTATEMENTSEQUENCE = false;
	    bool bTerm_END = false;
	    pcode *p = 0;

			acSub = sCurrentSub.ascii();
      
      int nSubId = 0;
      memory_sub *s = 0;          

			switch(bClassMethod){
				case false:
          if (bTerm_GET || bTerm_GET2){
            s = myModule->findModule(getModule())->myPropertyGet;
          } else if (bTerm_SET || bTerm_SET2){
            s = myModule->findModule(getModule())->myPropertySet;
          }
   				if (!s->registered(getModule(), acSub)){ semanticError(token__KEYWORD, utility::con(acSub, " property not declared")); goto exit; }
   				if (s->pcodeBuilt(getModule(), acSub)){ semanticError(token__KEYWORD, utility::con(acSub, " property already declared & parsed")); goto exit; }
					nSubId = s->getId(getModule(), acSub);
 					p = s->getPcode(getModule(), acSub);
					setTokenPos(s->getTokenPos(nSubId)); // skip already parsed header information
 					setCurrentLine(s->getTokenLinePos(nSubId)); // currentline muss auch noch gesetzt werden
					break;
				case true:
          if (bTerm_GET || bTerm_GET2){
            s = myClass->findClass(getClass())->myPropertyGet;
          } else if (bTerm_SET || bTerm_SET2){
            s = myClass->findClass(getClass())->myPropertySet;
          }
   				if (!s->registered(getClass(), acSub)){ semanticError(token__KEYWORD, utility::con(acSub, " property not declared")); goto exit; }
   				if (s->pcodeBuilt(getClass(), acSub)){ semanticError(token__KEYWORD, utility::con(acSub, " property already declared & parsed")); goto exit; }
					nSubId = s->getId(getClass(), acSub);
 					p = s->getPcode(getClass(), acSub);
					setTokenPos(s->getTokenPos(nSubId)); // skip already parsed header information
					setCurrentLine(s->getTokenLinePos(nSubId)); // currentline muss auch noch gesetzt werden
					break;
			}

			const char *acModule = "";

			switch(bClassMethod){
				case false:
					acModule = getModule();
					break;
				case true:
					acModule = getClass();
					break;
			}

      bScopeClassStatic = false;
      bScopeClassPropertySet = bTerm_SET || bTerm_SET2;
      bScopeClassPropertyGet = bTerm_GET || bTerm_GET2;
     	sCurrentSub = acSub; // register global
      sCurrentRealSub = acSub; // register global
      bSubVarStatic = false; // register global
      exception *e = new exception;

      bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p);


      if (bTerm_GET || bTerm_SET){
     	  if (bTerm_END = parseTerm(token__END))
        if ((bTerm_PROPERTY2 = parseTerm(token__PROPERTY))){}
      } else {
        if (bTerm_GET2){
     	    if (bTerm_END = parseTerm(token__END))
          if ((bTerm_GET3 = parseTerm(token__GET))){}
        } else if (bTerm_SET2){
     	    if (bTerm_END = parseTerm(token__END))
          if ((bTerm_SET3 = parseTerm(token__SET))){}
        }
      }


      if (bTerm_PROPERTY2 || bTerm_GET3 || bTerm_SET3){

     		if (bProducePcode){

          
          if (bTerm_GET || bTerm_GET2){
          } else if (bTerm_SET || bTerm_SET2){
          }

				}

				switch(bClassMethod){
					case false:
 		  			s->setPcodeBuilt(getModule(), acSub, true);
						break;
					case true:
 		  			s->setPcodeBuilt(getClass(), acSub, true);
						break;
				}

     	}

      if (!proceedParse()){ goto exit; }

      if (bTerm_GET || bTerm_SET){
		    if (!bTerm_END && !bTerm_PROPERTY2){ syntaxError(token__PROPERTY, "END PROPERTY missing"); goto exit; }      
      } else {
        if (bTerm_GET2){
		      if (!bTerm_END && !bTerm_GET2){ syntaxError(token__PROPERTY, "END GET missing"); goto exit; }      
        } else if (bTerm_SET2){
		      if (!bTerm_END && !bTerm_SET2){ syntaxError(token__PROPERTY, "END SET missing"); goto exit; }      
        }
      }    

			switch(bClassMethod){
				case false:
					parseInfo(p,  utility::con("parsed MODULE PROPERTY ", acSub) );
					break;
				case true:
					parseInfo(p,  utility::con("parsed CLASS PROPERTY ", acSub) );
					break;
			}

      if ((bTerm_GET2 && !bTerm_SET2) || (!bTerm_GET2 && bTerm_SET2)){
        goto retry;
      }

			sCurrentSub = ""; // register global
			sCurrentRealSub = ""; // register global
      bSubVarStatic = false; // register global

			return true;
		}

		switch(bClassMethod){
			case false:
				if (!bIDENTIFIER){ syntaxError(token__PROPERTY, "property name missing"); goto exit; }
				break;
			case true:
				if (!bIDENTIFIER){ syntaxError(token__PROPERTY, "property name missing"); goto exit; }
				break;
		}
	}

exit:
	sCurrentSub = "";  // register global
	sCurrentRealSub = "";  // register global  
  bSubVarStatic = false; // register global
  bIsLocalStatic = false; // register global
	_TEND_
}
         
// used for auto-constructor/destructor calls inside constructors/destructors
bool parser::findMatchingMethod(const char *acSignature, int _nClassId, int *nParentClassId, int *nParentSubId, bool bConstructor, bool bDestructor)
{
  // * needed, because recursive calls would otherwise mess up the myModule->first()...  iterators
  static int parser__ITERATOR = -1; 
  parser__ITERATOR++;
  if (parser__ITERATOR >= parser__MAX_ITERATOR){
    internalError("Too many recursive calls inside fSUB_CALL. Try to split line into many lines."); return false;
  }
  // *
re:
  // user defined class
 	if (myClass->first(parser__ITERATOR)){
		do {

			int nClassId = myClass->getId();

      if (nClassId == *nParentClassId){

        // constructors        
			  if (bConstructor && myClass->firstConstructor(parser__ITERATOR)){
				  do {

				    int nId = myClass->getIdMethod();

           if (utility::my_stricmp(acSignature, myClass->getSignatureMethod(nClassId, nId)) == 0){
             *nParentSubId = nId;
             parser__ITERATOR--;
             return true;
           }

				  } while (myClass->nextConstructor(parser__ITERATOR));
       }

        static /**/ char acName[MAX_IDENTIFIER + MAX_PARAM * 64]; // name[func/sub/cons/destr][pcode_type+array(true/false)...]
        if (bConstructor) sprintf(acName, "%s%05d", myClass->getName(*nParentClassId), token__CONSTRUCTOR);
        else if (bDestructor) sprintf(acName, "%s%05d", myClass->getName(*nParentClassId), token__DESTRUCTOR);

       // it seems that the parent class is defined after the child class, so we must explicit create the constructor
        if (bConstructor && !myClass->registeredMethod(myClass->getName(*nParentClassId), acName)){
             
          setScopeClass(myClass->getParentName(nClassId), myClass->getName(nClassId));

		      fREGISTER_CLASS_DEFAULT_CONSTRUCTOR();
		      fREGISTER_CLASS_DEFAULT_DESTRUCTOR(); 

          nClassId = myClass->getId();

          setScopeClass(myClass->getParentName(_nClassId), myClass->getName(_nClassId));

          goto re;
        }

       // destructors
			  if (bDestructor && myClass->firstDestructor(parser__ITERATOR)){
				  do {

				    int nId = myClass->getIdMethod();

           if (utility::my_stricmp(acSignature, myClass->getSignatureMethod(nClassId, nId)) == 0){
             *nParentSubId = nId;
             parser__ITERATOR--;
             return true;
           }

				  } while (myClass->nextDestructor(parser__ITERATOR));
       }

       // it seems that the parent class is defined after the child class, so we must explicit create the destructor
        if (bDestructor && !myClass->registeredMethod(myClass->getParentName(nClassId), acName)){
             
          setScopeClass(myClass->getParentName(nClassId), myClass->getName(nClassId));

		      fREGISTER_CLASS_DEFAULT_CONSTRUCTOR();
		      fREGISTER_CLASS_DEFAULT_DESTRUCTOR(); 

          nClassId = myClass->getId();

          setScopeClass(myClass->getParentName(_nClassId), myClass->getName(_nClassId));

          goto re;

        }


/*
        if (myClass->getParentId(nClassId) > 0){
           return findMatchingMethod(acSignature, nParentClassId, nParentSubId, bConstructor, bDestructor);
        }
        */
      }

		} while (myClass->next(parser__ITERATOR));
	}
  
  parser__ITERATOR--;
	return false;
}

/* *
[EXPLANATION]
NAME: SUB
DESC:
SEEALSO: FUNCTION
*/
/* *
[EXPLANATION]
NAME: FUNCTION
DESC:
SEEALSO: SUB
*/
// sub body
bool parser::fSUB_BODY()
{
	return fSUB_BODY(false);
}

// sub body
bool parser::fSUB_BODY(bool bClassMethod)
/*
[QBASIC]

static steht am ende der zeile
STATIC          Bewirkt die Sicherung der Werte der lokalen
                 Variablen zwischen zwei Funktionsaufrufen.
 Ausdruck        Der Rckgabewert der Funktion.

[VB]

[*]
[*]
*/
{
	_TBEGIN_

	bool bIDENTIFIER = false;
	bool bTerm_SUB = false;
	bool bTerm_FUNCTION = false;
	bool bTerm_CONSTRUCTOR = false;
	bool bTerm_DESTRUCTOR = false;
	bool bTerm_SIGNAL = false;
	bool bTerm_SLOT = false;  

  bool bTerm_PRIVATE = false;
	bool bTerm_PUBLIC = false;
	bool bTerm_PROTECTED = false;
	bool bTerm_STATIC = false;
	bool bTerm_ABSTRACT = false;
	bool bTerm_DECLARE = false;


  if (bTerm_DECLARE = parseTerm(token__DECLARE)){}
  if (bTerm_STATIC = parseTerm(token__STATIC)){}
  if (bTerm_ABSTRACT = parseTerm(token__ABSTRACT)){}
  if (!bTerm_STATIC && (bTerm_STATIC = parseTerm(token__STATIC))){}
  if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){}
  if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){}
  if (bTerm_PROTECTED = parseTerm(token__PROTECTED)){}
  if (!bTerm_ABSTRACT && (bTerm_ABSTRACT = parseTerm(token__ABSTRACT))){}
  if (!bTerm_STATIC && (bTerm_STATIC = parseTerm(token__STATIC))){}
  if (!bTerm_ABSTRACT && (bTerm_ABSTRACT = parseTerm(token__ABSTRACT))){}
  if (!bTerm_DECLARE && (bTerm_DECLARE = parseTerm(token__DECLARE))){}

#ifdef KBDEBUG
  if (stopAtLine(265)){
    int i = 9;
    i++;
  }
#endif


       if (bTerm_SUB = parseTerm(token__SUB));
  else if (bTerm_FUNCTION = parseTerm(token__FUNCTION));
  else if (bClassMethod){
           if (bTerm_CONSTRUCTOR = parseTerm(token__CONSTRUCTOR));
      else if (bTerm_DESTRUCTOR = parseTerm(token__DESTRUCTOR));
      else if (bTerm_SIGNAL = parseTerm(token__SIGNAL));
      else if (bTerm_SLOT = parseTerm(token__SLOT));
  }

	if (bTerm_SUB || bTerm_FUNCTION || bTerm_CONSTRUCTOR || bTerm_DESTRUCTOR || bTerm_SIGNAL || bTerm_SLOT){
    const char *ac = "";
		if (bIDENTIFIER = fSUB_NAME(&ac)){
      sCurrentSub = ac;


      if (bTerm_DECLARE || strcmp(sCurrentLib.ascii(), "") != 0){ // is it a library declare statement, we do not need to parser sub body
        // skip line
	      do {

		      if (peekToken() == token__MSC_EOL){
            _DONE_;      
		      }

	      } while(proceedParse() && nextToken());
      }

      sCurrentRealSub = sCurrentSub;

			const char *acScope = "";
      module_ *my_module = 0;
      class_ *my_class = 0;

			switch(bClassMethod){
				case false:
					acScope = getModule();
         my_module = myModule->findModule(acScope);
					break;
				case true:
					acScope = getClass();
         my_class = myClass->findClass(acScope);
					break;
			}
	    const char *acSub = sCurrentSub.ascii();
	    const char *acSub2 = sCurrentSub.ascii();

      int nLine = getCurrentLine();
      

      // get the overloaded Name
			switch(bClassMethod){
				case false:
          {
            if (my_module == 0 || my_module->mySub == 0){ internalError(utility::con(acSub2, " (sub/function) not declared (2)")); goto exit; }
            const char *acc = 0;
            for (int i = 0; i < 100 && acc == 0; i++){ // needed if the sub declaration line is multi-line
              acc = my_module->mySub->getNameFromRealNameAndFileAndLine(acScope, sCurrentSub.ascii(), getCurrentFile(), nLine + i);
            }          
   				  sCurrentSub = acc;
          }
					break;
				case true:
          if (my_class == 0 || my_class->mySub == 0){ internalError(utility::con(acSub2, " (method) not declared (2)")); goto exit; }
          {
            const char *acc = 0;
            for (int i = 0; i < 100 && acc == 0; i++){ // needed if the sub declaration line is multi-line
              acc = my_class->mySub->getNameFromRealNameAndFileAndLine(acScope, sCurrentSub.ascii(), getCurrentFile(), nLine + i);
            }          
   				  sCurrentSub = acc;
          }
					break;
			}
      
	    static /**/ const char *acIdentifier[parser__MAX_CATCH];
	    int nComma = 0;
	    bool bTerm_CATCH = false;
	    bool bTerm_FINALLY = false;
	    bool bTerm_END = false;
 	    bool bTerm_SYM_BR_OP = false;
 	    bool bTerm_SYM_BR_CL = false;
 	    bool bTerm_AS = false;
 	    bool bTYPE = false;
	    static /**/ const char *acType2[parser__MAX_CATCH];

      bool bEOL = false;
	    bool bREM = false;

      bool bSTATEMENTSEQUENCE = false;
	    bool bTerm_SUB2 = false;
	    bool bTerm_SUB3 = false;
	    pcode *p = 0;

			acSub = sCurrentSub.ascii();
      if (!isScopeClass()){
        bIsLocalStatic = bTerm_STATIC;
      }

			bool bStatic = false;
			int nSubId = 0;

      const char *acFile = 0;
      //int nLine = 0;

			switch(bClassMethod){
				case false:
   				if (!my_module->mySub->registered(getModule(), acSub)){ internalError(utility::con(acSub2, " (sub/function) not declared")); goto exit; }
   				if (my_module->mySub->pcodeBuilt(getModule(), acSub)){ internalError(utility::con(acSub2, " (sub/function) already declared & parsed")); goto exit; }
					nSubId = my_module->mySub->getId(getModule(), acSub);
 					p = my_module->mySub->getPcode(getModule(), acSub);
					
					bStatic = my_module->mySub->isStatic(nSubId);
					acFile = my_module->mySub->getFile(nSubId);
					nLine = my_module->mySub->getLine(nSubId);

					break;
				case true:
   				if (!my_class->mySub->registered(getClass(), acSub)){ internalError(utility::con(acSub2, " (method) not declared")); goto exit; }
   				if (my_class->mySub->pcodeBuilt(getClass(), acSub)){ internalError(utility::con(acSub2, " (method) already declared & parsed")); goto exit; }
					nSubId = my_class->mySub->getId(getClass(), acSub);
 					p = my_class->mySub->getPcode(getClass(), acSub);
					
         bStatic = my_class->mySub->isStatic(nSubId);
         bScopeClassStatic = bStatic;
         bScopeClassPropertySet = false;
         bScopeClassPropertyGet = false;
					acFile = my_class->mySub->getFile(nSubId);
					nLine = my_class->mySub->getLine(nSubId);

					break;
			}

			memory_sub *s = 0;

			switch(bClassMethod){
				case false:
					s = my_module->mySub;
					break;
				case true:
					s = my_class->mySub;
					break;
			}

			int nId = s->getId(acScope, acSub);

      const char *acType = "";
    
      // exist all throw types?
   		if (s->firstThrow	(nId, &acType)){

    		do {

		   		int nType = findType(acType);
		 			if (nType == 0){ semanticError(token__KEYWORD, utility::con(acType, " not defined") ); goto exit; }

   			} while(s->nextThrow	(nId, &acType));
			}

			switch(bClassMethod){
				case false:
         setTokenPos(my_module->mySub->getTokenPos(nSubId)); // skip already parsed header information
					setCurrentLine(my_module->mySub->getTokenLinePos(nSubId)); // currentline muss auch noch gesetzt werden

         if (!bSilent && bProducePcode){
           p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fSUB_BODY", getCurrentLine() - 1));
         }

					break;
				case true:
         setTokenPos(my_class->mySub->getTokenPos(nSubId)); // skip already parsed header information
					setCurrentLine(my_class->mySub->getTokenLinePos(nSubId)); // currentline muss auch noch gesetzt werden

         if (!bSilent && bProducePcode){
           p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fMETHOD_BODY", getCurrentLine() - 1));
         }

					break;
			}

     	sCurrentSub = acSub; // register global

      if (!bTerm_ABSTRACT){
        bSubVarStatic = s->isStatic(nId) && !isScopeClassLocalStatic(); // register global
        exception *e = new exception;

        autoCallParentConstructorDestructor(p, bTerm_CONSTRUCTOR, bTerm_DESTRUCTOR, nId, s);

        bSTATEMENTSEQUENCE = fSTATEMENTSEQUENCE(p);

        catchFinally(p, false);    

        if (myException.size() > 0){ // are all exceptions catchable?

          t_exception *t;

          if (myException.first((int *) &t)){
            do {

              setCurrentLine(t->nLine);
              setCurrentRow(t->nRow);

    	          switch(bClassMethod){
				          case false:

                    if (!myModule->findModule(getModule())->mySub->hasThrow(myModule->findModule(getModule())->mySub->getId(getModule(), acSub), t->acName)){ semanticError(token__SUB, utility::con(t->acName, " must be thrown or catched inside sub/function ", s->getRealName(nId))); goto exit; }
					          break;
				          case true:
   				          if (!myClass->findClass(getClass())->mySub->hasThrow(myClass->findClass(getClass())->mySub->getId(getModule(), acSub), t->acName)){ semanticError(token__SUB, utility::con(t->acName, " must be thrown or catched inside method ", s->getRealName(nId))); goto exit; }
					          break;
			          }

            } while (myException.next((int *) &t));
          }
          // alle throws abgearbeitet
          myException.clear();

        }
      }


      //if (bTerm_ABSTRACT && bSTATEMENTSEQUENCE){ semanticError(token__SUB, "statements are not allowed, because method is ABSTRACT"); goto exit; }

     	if (bTerm_END = parseTerm(token__END))
      if (bTerm_SUB && (bTerm_SUB2 = parseTerm(token__SUB)) 
        || bTerm_FUNCTION && (bTerm_SUB2 = parseTerm(token__FUNCTION))
        || bTerm_CONSTRUCTOR && (bTerm_SUB2 = parseTerm(token__CONSTRUCTOR))
        || bTerm_DESTRUCTOR && (bTerm_SUB2 = parseTerm(token__DESTRUCTOR))
        || bTerm_SIGNAL && (bTerm_SUB2 = parseTerm(token__SIGNAL))
        || bTerm_SLOT && (bTerm_SUB2 = parseTerm(token__SLOT))
        ){}

      if (bTerm_ABSTRACT && bTerm_SUB2){ semanticError(token__SUB, "END SUB/FUNCTION is not needed/is not allowed, because method is ABSTRACT"); goto exit; }

      if (bTerm_SUB2){

     		if (bProducePcode){

         if (bTerm_FUNCTION){
            int nType = findType(s->type(s->getId(getScope(), sCurrentSub.ascii())));
            if (nType == 0){ semanticError(token__KEYWORD, utility::con(nType, " not defined") ); goto exit; }          

           // default function return expression
      			// default value return for function, egal ob irgendow implicit rcksprung erfolgt oder nicht
            defaultFunctionReturnExpression(p, nType);
         }

         {
       			p->wr_CALL_RETURN(pcode__CALL_RETURN, isScopeClass()); // return to caller pcode
         }

				}

				switch(bClassMethod){
					case false:
 		  			myModule->findModule(getModule())->mySub->setPcodeBuilt(getModule(), acSub, true);
						break;
					case true:
 		  			myClass->findClass(getClass())->mySub->setPcodeBuilt(getClass(), acSub, true);
						break;
				}

      } else if (!bTerm_ABSTRACT){
        { syntaxError(token__SUB, ""); goto exit; }
//        { syntaxError(token__SUB, "missing END SUB / FUNCTION / CONSTRUCTOR / DESTRUCTOR..."); goto exit; }
      }

      sCurrentSub = ""; // register global
      sCurrentRealSub = ""; // register global
      bSubVarStatic = false; // register global
      bIsLocalStatic = false;

      if (!bTerm_ABSTRACT){
  			if (!bTerm_END || !bTerm_SUB2){ 
         { syntaxError(token__SUB, "no syntax matching"); goto exit; }
         /*
         if (bTerm_SUB){ syntaxError(token__SUB, "END SUB missing"); goto exit; }
         if (bTerm_FUNCTION){ syntaxError(token__SUB, "END FUNCTION missing"); goto exit; }
         if (bTerm_CONSTRUCTOR){ syntaxError(token__SUB, "END CONSTRUCTOR missing"); goto exit; }
         if (bTerm_DESTRUCTOR){ syntaxError(token__SUB, "END DESTRUCTOR missing"); goto exit; }
         if (bTerm_SIGNAL){ syntaxError(token__SUB, "END SIGNAL missing"); goto exit; }
         if (bTerm_SLOT){ syntaxError(token__SUB, "END SLOT missing"); goto exit; }
         */
       }
      }

			switch(bClassMethod){
				case false:
					parseInfo(p,  utility::con("parsed SUB/FUNCTION ", getScope(), acSub) );
					break;
				case true:
					parseInfo(p,  utility::con("parsed METHOD ", getScope(), acSub) );
					break;
			}
			return true;
		}

		switch(bClassMethod){
			case false:
				if (!bIDENTIFIER){ syntaxError(token__SUB, "sub/function name missing"); goto exit; }
				break;
			case true:
				if (!bIDENTIFIER){ syntaxError(token__SUB, "method name missing"); goto exit; }
				break;
		}
	}

exit:
	sCurrentSub = "";  // register global
	sCurrentRealSub = "";  // register global
  bSubVarStatic = false; // register global
  bIsLocalStatic = false; // register global
	_TEND_
}


bool parser::autoCallParentConstructorDestructor(pcode *p, bool bConstructor, bool bDestructor, int nId, memory_sub *s)
{
  _BEGIN_

 if (bConstructor || bDestructor){

   int nClassId = myClass->getId(getClass());
   int nParentClassId = myClass->getParentId(nClassId);
 
   if (nParentClassId > 0){

     bool bTerm_PARENT = false;

     if (bTerm_PARENT = parseTerm(token__PARENT)){}

     // call directly parent constructor/destructor in source code maybe with other arguments   
     if (bTerm_PARENT){

       bool bTerm_SYM_DOT = false;

       if (!(bTerm_SYM_DOT = parseTerm(token__SYM_DOT))){ syntaxError(token__CONSTRUCTOR, "missing . after PARENT --> constructor call"); _END_ }               

       if (bProducePcode){
       	  p->wr_PUSH_PARENT(pcode__PUSH_PARENT);
       }

       if (bConstructor && !fCONSTRUCTOR_CALL(p, nParentClassId)){
          { semanticError(token__CONSTRUCTOR, "missing parent constructor call"); _END_ }               
       }
       if (bDestructor && !fDESTRUCTOR_CALL(p, nParentClassId)){
          { semanticError(token__DESTRUCTOR, "missing parent destructor call"); _END_ }               
       }
     } else {

        int nParentSubId = 0;

        bool bReturn = false;

        // qt binding
        if (memory_type::isBinding(nParentClassId)){
          _BEGIN2_

         const char *acMethod = getParentClass();

	       int nParamCount = 0;	        

	       int i = 0;
         bool b2 = false;

         const char *acName = "";
         const char *acType = "";
         int nParameterCall = 0;
         bool bOptional = false;
         bool bDefault = false;    
         bool bParamArray = false;
         t_array *a = 0;
         defaultvalue *defval = 0;
         int nParamId = 0;
         int nParamLStringLen = 0;    

         XString ss = acMethod; ss = ss.upper();

	       goto j;
       retry:
	       i++;
	       sprintf(ac, "%s%d", acMethod, i);
         ss = ac;
         ss = ss.upper();

       j:

	       parser_class2 *pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nParentClassId);

        if (nParentClassId == 1171){
         nParentClassId = nParentClassId;
        }

	      if (pc){
		       parser_method *pm = 0;

           while (pc != 0 && (pm = (parser_method *) pc->myParser_method.getString(ss.ascii())) == 0){ // search in super class, if method in current class wasn't found
			       if (pc->nParentClassId == 0) break;
			       pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId);
		       }

		       if (pm == 0){ // zweiter Versuch in anderer parent class -> Mehrfachvererbung
			       pc = (parser_class2 *) myParser_classMethod->myParser_class.get(nParentClassId);
		       }

		       while (pc != 0 && (pm = (parser_method *) pc->myParser_method.getString(ss.ascii())) == 0){ // search in super class, if method in current class wasn't found
			       if (pc->nParentClassId2 == 0) break;
			       pc = (parser_class2 *) myParser_classMethod->myParser_class.get(pc->nParentClassId2);
		       }

		       if (pm){

          // push paramater on stack again for deligating
   		       if (s->firstParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){

    		       do {
                  int nType = findType(acType);
    		           p->wr_PUSH_ID(pcode__PUSH_ID, nParamId, param, false);
                   
				       } while(s->nextParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen));
			       }

          b2 = true;

			       parser_parameter *pp;	

            parser_parameter *it;

   		       if (s->firstParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){

             parser_parameter *it;

             if (pm->myParser_parameter->first((int *) &it)){
    		       do {
                  pp = (it);

                  int nType = findType(acType);
                				
                  if (memory_type::compatibleType(nType, pp->nType)){
                   nParamCount++;
                  }
					        else if (nType == 0 && nParamCount && pp->bDefault && binding_fClassMethod_default(p, pp)){ nParamCount++; }
					        else if (nType > 0 || pp->bOptional == false){ _END2_ goto retry; }
        				    
                  pm->myParser_parameter->next((int *) &it);

                  bool b1 = it;
                  bool b2 = s->nextParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen);
                  if (b2 == false){
                    acType = "";
                  }

                  if (b1 == false && b2 == false) break;
                  if (b1 == false && b2 == true){ _END2_ goto retry; }

                   
				       } while(true);
             } else { _END2_ goto retry; }

             }
             
             int m = 0;

             // *** testen, ob alle notwendigen parameter üpergeben wurden

             if (pm->myParser_parameter->first((int *) &it, 1)){
               do {
               if (m >= nParamCount){                 
                 pp = (it);       

				         if (pp->bDefault && binding_fClassMethod_default(p, pp)){}
                 else if (pp->bOptional == false){ _END2_ goto retry; }

               }
               m++;
               } while (pm->myParser_parameter->next((int *) &it, 1));
             }

             nParamCount = m;
             

             // ***

   		       if (bProducePcode){
				        p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
				        p->wr_binding_ClassMethod(pcode__binding_CLASSMETHOD, pm->nClassMethodId, bReturn);
				        
               p->wr_binding_SET_ME(pcode__binding_SET_ME);                
               p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, pc->nClassId);                
   		       }
         } else {
           const char *acType = findType(nParentClassId);
           semanticError(token__CLASS, utility::con("no matching arguments found for constructor", acMethod, "in class", acType) );
           _ERROR_
         }

		    } else {

          const char *acType = findType(nParentClassId);
          if (b2){
   			     semanticError(token__CLASS, utility::con("no matching arguments found for constructor", acMethod, "in class", acType) );
          } else {
  			     semanticError(token__CLASS, utility::con(acMethod, "constructor not found in class", acType) );
          }
          _ERROR_
		    }

        // user defined class
        } else {        

         // finde passenden parent constructor/destructor
         bool b = findMatchingMethod(s->getSignature(nId), nClassId, &nParentClassId, &nParentSubId, bConstructor, bDestructor);

         // try default constructor with no arguments
         if (!b){ 
           b = findMatchingMethod("00033", nClassId, &nParentClassId, &nParentSubId, bConstructor, bDestructor);
         }

         if (!b){ 
             if (bDestructor){
               internalError("cannot find matching parent destructor automatically"); _END_
             } else {
               internalError("cannot find matching parent constructor automatically"); _END_
             }
         }               

         if (b && bProducePcode){

          {
   	         const char *acName = "";
   	         const char *acType = "";
   	         int nParameterCall = 0;
   	         bool bOptional = false;
   	         bool bDefault = false;    
             bool bParamArray = false;
   	         t_array *a = 0;
		         defaultvalue *defval = 0;
             int nParamId = 0;
             int nParamLStringLen = 0;    


   		      if (s->firstParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){

    		      do {

               if (nParameterCall == token__BY_REF){
    	 		             p->wr_PUSH_IDREF(pcode__PUSH_IDREF, nParamId, param);
               } else {
       		             p->wr_PUSH_ID(pcode__PUSH_ID, nParamId, param, false);
               }
             
				      } while(s->nextParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen));
			      }

           p->wr_ENTER_LOCAL(pcode__ENTER_LOCAL, nParentClassId, nParentSubId); // write pcode
                			 
   		      if (s->lastParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen)){

				      do {

               myClass->getMethods(nParentClassId)->getParameter	(nParentSubId, acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen);

   				      popParam(p, nId, acName, acType, nParameterCall, bOptional, bDefault, bParamArray, a, true, nClassId, nParamId, false, false, 0);

   			      } while(s->prevParameter	(nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &a, &defval, &nParamId, &nParamLStringLen));

			      }
         }
 

         p->wr_ClassMethod(pcode__CLASSMETHOD, nParentClassId, nParentSubId, myClass->getNameMethod(nParentClassId, nParentSubId), bConstructor, bDestructor, false, bReturn);
        }
       }
     }
   }

 }
 _DONE_
}

// default function return expression
bool parser::defaultFunctionReturnExpression(pcode *p, int nReturnExpressionType)
{

  if (bProducePcode){


    defaultvalue defval;
    t_variant c;

    if (isKBASIC()){
      switch(nReturnExpressionType){
       case pcode__BOOLEAN: p->wr_PUSH_BOOLEAN(pcode__PUSH_BOOLEAN, defval.boolean_); break;

       case pcode__QSTRING: 
       case pcode__CSTRING: 
         {
				    int nStatics = registerStringLiteral(defval.cstring_);
				    if (nStatics == 0){ internalError( utility::con(defval.cstring_, " string literal not declared") ); _ERROR_ }
           p->wr_PUSH_QSTRING(pcode__PUSH_QSTRING, nStatics); 
           break;
         }

       case pcode__BYTE: p->wr_PUSH_BYTE(pcode__PUSH_BYTE, defval.byte_); break;
       case pcode__SHORT: p->wr_PUSH_SHORT(pcode__PUSH_SHORT, defval.short_); break;
       case pcode__INTEGER: p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, defval.integer_); break;
       case pcode__LONG: p->wr_PUSH_LONG(pcode__PUSH_LONG, defval.long_); break;

       case pcode__SINGLE: p->wr_PUSH_SINGLE(pcode__PUSH_SINGLE, defval.single_); break;
       case pcode__DOUBLE: p->wr_PUSH_DOUBLE(pcode__PUSH_DOUBLE, defval.double_); break;

      default:
       p->wr_PUSH_LONG(pcode__PUSH_LONG, defval.long_); break;
       break;
      }           
    } else { // oldstyle return    subname = expressioon

      int nVar = 0;
      t_scope scope = local;        
      int n = 0;

      if (isScopeModuleLocal()){

        n = myModule->getIdSub(getModule(), getSub());
        
        nVar = myModule->getIdSubVar(getModule(), getSub(), myModule->getRealNameSub(myModule->getId(getModule()), n));

      } else if (isScopeClassLocalInstance() || isScopeClassLocalStatic()){ // static and instance

        n = myClass->getIdMethod(getClass(), getMethod());
        
        nVar = myClass->getIdMethodVar(getClass(), getMethod(), myClass->getRealNameMethod(myClass->getId(getClass()), n));

      }

      p->wr_PUSH_RETURNVAR(pcode__PUSH_RETURNVAR, nVar, scope);
    }
  }

 return true;

}

/* *
[EXPLANATION]
NAME: TYPE
DESC:
SEEALSO:
*/
// type body
// * already parsed at the beginning of parsing
bool parser::fTYPE_BODY()
{
	_TBEGIN_

	bool bTerm_PRIVATE; // = false;
	bool bTerm_PUBLIC; // = false;

			 if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){} 
	else if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){}
	
  if (!bTerm_PRIVATE && !bTerm_PUBLIC){ bTerm_PUBLIC = true; }

  //bool bTerm_TYPE = false;

  if (!(/*bTerm_TYPE = */parseTerm(token__TYPE))){ _TEND_ } // to optimize, the 'if' is one of the first statements

  bool bRet = true;
  int nTest = 0;
  int nTestPrev = 0;

	do {

		nTest = peekToken();

		if (nTestPrev == token__END && nTest == token__TYPE){
      if ((/*bTerm_TYPE = */parseTerm(token__TYPE))){ return true; }
		}

		nTestPrev = nTest;

	} while(proceedParse() && bRet && (bRet = nextToken()));

	_TEND_
}

/* *
[EXPLANATION]
NAME: ENUMERATION
DESC:
SEEALSO:
*/
// * already parsed at the beginning of parsing
bool parser::fENUM_BODY()
{
	_TBEGIN_


	bool bTerm_PRIVATE = false;
	bool bTerm_PUBLIC = false;

  switch(peekToken()){
    case token__PRIVATE: bTerm_PRIVATE = parseTerm(token__PRIVATE);      break;
    case token__PUBLIC:  bTerm_PUBLIC = parseTerm(token__PUBLIC);      break;
  }

  if (!bTerm_PRIVATE && !bTerm_PUBLIC){ bTerm_PUBLIC = true; }

  //bool bTerm_ENUM = false;

  if (!(/*bTerm_ENUM = */parseTerm(token__ENUM))){ _TEND_ } // to optimize, the 'if' is one of the first statements

  bool bRet = true;
  int nTest = 0;
  int nTestPrev = 0;

	do {

		nTest = peekToken();

		if (nTestPrev == token__END && nTest == token__ENUM){
      if ((/*bTerm_ENUM = */parseTerm(token__ENUM))){ 
        return true; 
      }
		}

		nTestPrev = nTest;

	} while(proceedParse() && bRet && (bRet = nextToken()));

	_TEND_

}

/* *
[EXPLANATION]
NAME: STRUCTURE
DESC:
SEEALSO:
*/
// * already parsed at the beginning of parsing
/*
bool parser::fSTRUCTURE_BODY()
{
	_TBEGIN_


	bool bTerm_PRIVATE = false;
	bool bTerm_PUBLIC = false;


  switch(peekToken()){
    case token__PRIVATE: bTerm_PRIVATE = parseTerm(token__PRIVATE);      break;
    case token__PUBLIC:  bTerm_PUBLIC = parseTerm(token__PUBLIC);      break;
  }
/ *
			 if (bTerm_PRIVATE = parseTerm(token__PRIVATE)){} 
	else if (bTerm_PUBLIC = parseTerm(token__PUBLIC)){}
	* /
  if (!bTerm_PRIVATE && !bTerm_PUBLIC){ bTerm_PUBLIC = true; }

  if (!(parseTerm(token__STRUCTURE))){ _TEND_ } // to optimize, the 'if' is one of the first statements

  bool bRet = true;
  int nTest = 0;
  int nTestPrev = 0;

	do {

		nTest = peekToken();

		if (nTestPrev == token__END && nTest == token__STRUCTURE){
      if ((parseTerm(token__STRUCTURE))){ return true; }
		}

		nTestPrev = nTest;

	} while(proceedParse() && bRet && (bRet = nextToken()));

	_TEND_

}

*/
/* *
[EXPLANATION]
NAME: INTERFACE
DESC:
SEEALSO:
*/
// * already parsed at the beginning of parsing
/*
bool parser::fINTERFACE_BODY()
{
	_TBEGIN_

  bool bTerm_INTERFACE = false;

  if (!(bTerm_INTERFACE = parseTerm(token__INTERFACE))){ _TEND_ } // to optimize, the 'if' is one of the first statements

  bool bRet = true;
  int nTest = 0;
  int nTestPrev = 0;

	do {

		nTest = peekToken();

		if (nTestPrev == token__END && nTest == token__INTERFACE){
      if ((bTerm_INTERFACE = parseTerm(token__INTERFACE))){ return true; }
		}

		nTestPrev = nTest;

	} while(proceedParse() && bRet && (bRet = nextToken()));

	_TEND_
}
*/

bool parser::registerAll()
{

	_SCANBEGIN_

	int nTest = 0;
	int nTestPrev = 0;
	bool bRet = true;

	int nStartPos = getTokenPos();
	int nStartPos2 = getTokenPos();

  bool bCached = false;
  bool bFirst = true;


	do {
no2:
		nTest = peekToken();
no:
		if (nTestPrev == token__MSC_EOL){ //  dangerous nur auf eol prfen? rem : 
			nStartPos = getTokenPos(); // last EOL before sub
		}

    if (nTest == token__KB_FILENAME){
      nStartPos = getTokenPos();

      bCached = false;

      int n = myToken->rd_Token();
      
      const char *acFile = myToken->rd_CString();

      if (strcmp(acFile, "") == 0){ semanticError(token__KEYWORD, "File not saved. Please save the file before start compilation." ); _ERROR_ }

      XString sFile = acFile;
      setCurrentFile(acFile);
//      CONSOLE printKBFILE(acFile);

      if (!sFile.contains("/default.kbasic") && !sFile.contains("\\default.kbasic") && !sFile.contains("/default2.kbasic") && !sFile.contains("\\default2.kbasic") && strcmp(acFile, "") != 0){

        bool bDependencyFailed = false;
        bool bVersionFailed = false;
        
/*
        if (sFile.contains("myMenuBar.kbasic_menubar")){
          sFile = sFile;
        }

*/

        if (bUseCache && my_cache) bCached = my_cache->readParserPhase0(acFile, this, bFirst, &bDependencyFailed, &bVersionFailed);
        if (bVersionFailed) bCached = false; // if it is another version of pcode, caching for this file is not allowed
        if (bFirst) bFirst = false;

        if (my_cache && bCached == false){

          // add tokens from cached scanner file
          if (bDependencyFailed){
            
            if (my_cache->readScanner(sFile.ascii(), myToken, true)){ 
              if (bSilent == false && HAS_CONSOLE){
                CONSOLE print("Dependency failed for ", console__GREEN);
                CONSOLE print(sFile.ascii(), console__GREEN);
                CONSOLE print("\nUsing scanner cache for ", console__GREEN);
                CONSOLE print(sFile.ascii(), console__GREEN);
                CONSOLE print("\n\n", console__GREEN);
              }
              goto no2;
            }

          }

          if (my_cache){
            my_cache->wr_parserOpen(this, acFile);
          }

        } else {
          if (bSilent == false && HAS_CONSOLE){ 
            CONSOLE print("Using parser cache for ", console__GREEN);
            CONSOLE print(acFile, console__GREEN);
            CONSOLE print("\n\n", console__GREEN);
          }
        }
      } else {
        myPcode = myPcodeAll;
      }

      nStartPos2 = getTokenPos(); 
      

	  }

    {

      int kkk = getTokenPos();
/*
      if (nTest == token__TYPE){
        nTest = nTest;
      }
      */
      if (nTestPrev != token__END && nTest == token__ENUM){
				  if (nStartPos != nStartPos2/* || nTestPrev == token__KB_FILENAME*/) setTokenPos(nStartPos);
          if (!/*bRet = */fREGISTER_ENUM(myPcode)){
            setTokenPos(kkk);
            nextToken();
            nextToken();
          }
          //if (bRet == false){ internalError("fREGISTER_ENUM"); return false; }
          nTest = peekToken();
		  } else if (nTestPrev != token__END && nTest == token__TYPE/* && peekToken(1) != token__SYM_BR_OP*/){
				  if (nStartPos != nStartPos2/* || nTestPrev == token__KB_FILENAME*/) setTokenPos(nStartPos);
          if (!/*bRet = */fREGISTER_TYPE(myPcode)){
            setTokenPos(kkk);
            nextToken();
            nextToken();
          }
         // if (bRet == false){ internalError("fREGISTER_TYPE"); return false; }
          nTest = peekToken();
          /*
		  } else if (nTestPrev != token__END && nTest == token__STRUCTURE){
				  if (nStartPos != nStartPos2/ * || nTestPrev == token__KB_FILENAME* /) setTokenPos(nStartPos);
		      bRet = fREGISTER_STRUCTURE(myPcode);
          nTest = peekToken();*/
      } else if (nTestPrev != token__END && nTest == token__CLASS){
        
        nextToken();
        const char *ac = "";
        if (fID_KEYWORD_OR_BUILTIN(&ac)){
          sCurrentClass = ac;
        }     

			  if (nStartPos != nStartPos2/* || nTestPrev == token__KB_FILENAME*/) setTokenPos(nStartPos);
          if (!/*bRet = */fREGISTER_CLASS()){
            setTokenPos(kkk);
            nextToken();
            nextToken();
          }
        //if (bRet == false){ internalError("fREGISTER_CLASS"); return false; }
        nTest = peekToken();
      
      } else if (nTestPrev == token__END && nTest == token__CLASS){
        sCurrentClass = "";
      
      } else if (nTestPrev != token__END && nTest == token__MODULE){       
  	
        nextToken();
        const char *ac = "";
        if (fID_KEYWORD_OR_BUILTIN(&ac)){ // module will be registered later
          sCurrentModule = ac;
        }

      } else if (nTestPrev == token__END && nTest == token__MODULE){
        sCurrentModule = acDefaultModuleName;
      }        
    }

		nTestPrev = nTest;

    nTest = peekToken();
    if (nTest == token__KB_FILENAME){ // needed, because nextToken would otherwise ignore token__KB_FILENAME
      goto no;
    }

	} while(proceedParse() && bRet && (bRet = nextToken()));

	_SCANEND_

  myPcode = myPcodeAll;  

	return true;
}

bool parser::registerAll2()
{
	_SCANBEGIN_

	int nTest = 0;
	int nTestPrev = 0;
	bool bRet = true;

	int nStartPos = getTokenPos();
	int nStartPos2 = getTokenPos();

	do {

		nTest = peekToken();
no:
		if (nTestPrev == token__MSC_EOL || nTestPrev == token__DECLARE/* || nTestPrev == token__SYM_COLON*/){ //  dangerous nur auf eol prfen? rem : 
			nStartPos = getTokenPos(); // last EOL before sub
		}

    if (nTest == token__KB_FILENAME){

      nStartPos = getTokenPos();
      

      int n = myToken->rd_Token();
      const char *acFile = myToken->rd_CString();
      setCurrentFile(acFile);
//      CONSOLE printKBFILE(acFile);

      nStartPos2 = getTokenPos();       

      bool bCached = false;

      XString sFile = acFile;
      if (!sFile.contains("/default.kbasic") && !sFile.contains("\\default.kbasic") && !sFile.contains("/default2.kbasic") && !sFile.contains("\\default2.kbasic") && strcmp(acFile, "") != 0){
        if (bUseCache && my_cache) bCached = my_cache->readParserPhase1(acFile, this, false);
      }

	  }

		if (nTestPrev == token__OPTION && nTest == token__OLDBASIC){
      setOLDBASIC();
    } else if (nTestPrev == token__OPTION && nTest == token__VERYOLDBASIC){
      setVERYOLDBASIC();
    } else if (nTestPrev == token__OPTION && nTest == token__KBASIC){
      setKBASIC();

    } 
/*
      if (nTest == token__TYPE){
        nTest = nTest;
      }
*/
    if (!my_cache || my_cache->parserOpened(getCurrentFile())){

      int kkk = getTokenPos();

      
      if (nTestPrev != token__END && nTest == token__ENUM){
        if (nStartPos != nStartPos2){
          setTokenPos(nStartPos);
        }
        if (!/*bRet = */fREGISTER_ENUM(myPcode)){ // in global pcode
          setTokenPos(kkk);
          nextToken();
          nextToken();
        }

        nTest = peekToken();
		  } else if (nTestPrev != token__END && nTest == token__TYPE/* && peekToken(1) != token__SYM_BR_OP*/){
        if (nStartPos != nStartPos2){
          setTokenPos(nStartPos);
        }
        if (!/*bRet = */fREGISTER_TYPE(myPcode)){ // in global pcode
          setTokenPos(kkk);
          nextToken();
          nextToken();
        }
        nTest = peekToken();
          /*
		  } else if (nTestPrev != token__END && nTest == token__STRUCTURE){
				  if (nStartPos != nStartPos2) setTokenPos(nStartPos);
		      bRet = fREGISTER_STRUCTURE(myPcode);
          nTest = peekToken();
          */
      } else if (nTestPrev != token__END && nTest == token__CLASS){
        if (nStartPos != nStartPos2){
          setTokenPos(nStartPos);
        }
        if (!/*bRet = */fREGISTER_CLASS()){
          setTokenPos(kkk);
          nextToken();
          nextToken();
        }
        nTest = peekToken();
      } else if (nTestPrev != token__END && nTest == token__MODULE){
        if (nStartPos != nStartPos2){
          setTokenPos(nStartPos);
        }
        if (!/*bRet = */fREGISTER_MODULE()){
          setTokenPos(kkk);
          nextToken();
          nextToken();
        }
        nTest = peekToken();
      } else if (nTestPrev != token__END && (nTest == token__SUB || nTest == token__FUNCTION || nTest == token__DECLARE)){ // global subs and functions
        if (nStartPos != nStartPos2){
          setTokenPos(nStartPos);
        }
        if (!/*bRet = */fREGISTER_MODULE_SUB()){
          setTokenPos(kkk);
          nextToken();
          nextToken();
        }
        nTest = peekToken();
		  }     
    }
    
    /*
        
		} else	if (nTestPrev != token__END && nTest == token__INTERFACE){
				setTokenPos(nInterfaceStartPos);
		    bRet = fREGISTER_INTERFACE(myPcode);
        nTest = peekToken();
		}
        */

		nTestPrev = nTest;

    nTest = peekToken();
    if (nTest == token__KB_FILENAME || nTest == token__DECLARE){ // needed, because nextToken would otherwise ignore token__KB_FILENAME
      goto no;
    }

	} while(proceedParse() && bRet && (bRet = nextToken()));

	_SCANEND_

  myPcode = myPcodeAll;

  if (my_cache) my_cache->deinitParser(); // needed to cleanup pcode map

	return true;
}

bool parser::registerAllTypes()
{
	_SCANBEGIN_

	int nTest = 0;
	int nTestPrev = 0;
	bool bRet = true;

	int nTypeStartPos = getTokenPos();

	bool bType = false;

	do {

		nTest = peekToken();

    
    if (nTestPrev == token__MSC_EOL){
     	_SCANEND_
      return false;
		}

		if (nTestPrev != token__END && nTest == token__TYPE/* && peekToken(1) != token__SYM_BR_OP*/){

				setTokenPos(nTypeStartPos);

        if (!/*bRet = */fREGISTER_TYPE(myPcode)){
     	    _SCANEND_
          return false;
        }

      //  nTest = peekToken();
        return true;
		}
/*
		if (nTestPrev == token__END && nTest == token__MODULE){
 	    _SCANEND_
      return false;
    }
		if (nTestPrev == token__END && nTest == token__CLASS){
 	    _SCANEND_
      return false;
    }
*/
		nTestPrev = nTest;

	} while(proceedParse() && bRet && (bRet = nextToken()));

	_SCANEND_

	return false;
}

bool parser::registerAllEnums()
{
	_SCANBEGIN_

	int nTest = 0;
	int nTestPrev = 0;
	bool bRet = true;

	int nStartPos = getTokenPos();

	do {

		nTest = peekToken();

		if (nTestPrev == token__MSC_EOL){
     	_SCANEND_
      return false;
		}

		if (nTestPrev != token__END && nTest == token__ENUM){
				setTokenPos(nStartPos);

        if (!/*bRet = */fREGISTER_ENUM(myPcode)){         
	        _SCANEND_
	        return false;
        }

       // nTest = peekToken();
        return true;
		}  else     
/*
		if (nTestPrev == token__END && nTest == token__ENUM){
      return true;
		}       
*/
		nTestPrev = nTest;

	} while(proceedParse() && bRet && (bRet = nextToken()));

	_SCANEND_

	return false;
}


/*
bool parser::registerAllInterfaces()
{
	_SCANBEGIN_

	int nTest = 0;
	int nTestPrev = 0;
	bool bRet = true;

	int nInterfaceStartPos = getTokenPos();

	do {

		nTest = peekToken();

		if (nTestPrev == token__MSC_EOL){
			nInterfaceStartPos = getTokenPos(); // last EOL before sub
		}

		if (nTestPrev != token__END && nTest == token__INTERFACE){
				setTokenPos(nInterfaceStartPos);
		    bRet = fREGISTER_INTERFACE(myPcode);
        nTest = peekToken();
        return true;
		}

		nTestPrev = nTest;

	} while(proceedParse() && bRet && (bRet = nextToken()));

	_SCANEND_

	return false;
}
*/

/* *
[EXPLANATION]
NAME: MODULE STATIC
DESC:
SEEALSO:
*/
bool parser::appendAllModulesStatic() //  delete this method
{
  if (bProducePcode){
	  if (myModule->first()){
		  do {

			  int nId = myModule->getId();

		  } while (myModule->next());
    }
  }

	return true;
}

int nTest;
int nTest2;

// append the pcode of all modules
bool parser::appendAllModules(pcode *myPcodeSubRegister)
{
	int nPcodeOffset = 0;
	int nReturnPcodePos = 0;
	pcode *p = 0;
  pcode *pp = 0;


 	if (myModule->first()){
		do {

      int nModuleId = myModule->getId();

      if (myModule->firstSub()){
		    do {

         int nId = myModule->getIdSub();


          pcode *pcodeCall; int nPcodeOffset;

          if (my_cache && myPcode != myPcodeAll && myModule->firstPcodeCallSub(nModuleId, nId, &pcodeCall, &nPcodeOffset)){
            memory_sub *subs = myModule->getSubs(nModuleId);

            do {              

              const char *ac = subs->getFile(nId);
              if (!my_cache->parserOpened(ac)) break;

              my_cache->wr_memory_module_registerCallSub(ac, memory_module_registerCallSub, nModuleId, nId, p, p->getPos());
            } while (myModule->nextPcodeCallSub(nModuleId, nId, &pcodeCall, &nPcodeOffset));
          }          

		 	    if (bProducePcode){
            pp = myModule->getPcodeSub(nModuleId, nId);
            //if (nModuleId == 20001 && nId == 1) myPcode->wr_PUSH_STRING(pcode__PUSH_STRING, 1);
  			    if (pp) myPcode->pcodeWritePcode(pp);            
			    }


		    } while (myModule->nextSub());
       
	    }

		} while (myModule->next());
	}


	if (myModule->first()){
		do {

      int nModuleId = myModule->getId();

	    if (myModule->firstSub()){
		    do {

         int nId = myModule->getIdSub();

          if (myModule->firstPcodeCallSub (nModuleId, nId, &p, &nPcodeOffset)){
				    do {

		 			    if (bProducePcode){
						    int n = myPcode->getPos();  

                pcode *p2 = myModule->getPcodeSub(nModuleId, nId);

                if (nId == 10){
                  nId = nId;
                }

                //if not only in myPcodeAll = automatically inserted code by Atelier
                if (p->nAppendOffset2){

                  // do it in big pcode
                  int nn = p->nAppendOffset2 + nPcodeOffset - p->nDeclarationSize;
                  myPcode->setPos(nn);
						      myPcode->wr_CALL(pcode__CALL, p2->nAppendOffset, pcode::len(pcode__CALL)); // call address of sub, later it will be the real address
						      myPcode->setPos(n);
                }

                // do it in original pcode
                {
                  n = p->getPos();  
						      p->setPos(nPcodeOffset);
						      p->wr_CALL(pcode__CALL, p2->nAppendOffset, pcode::len(pcode__CALL)); // call address of sub, later it will be the real address
						      p->setPos(n);
                }
					    }

				    } while (myModule->nextPcodeCallSub	(nModuleId, nId, &p, &nPcodeOffset));

			    }

          if (bProducePcode && my_cache && !myModule->isCachedSub(nModuleId, nId)){

            memory_sub *subs = myModule->getSubs(nModuleId);

            pp = myModule->getPcodeSub(nModuleId, nId);
            int nLen =  myPcode->getSize();
            int nPos =  myPcode->getPos();

            if (my_cache->parserOpened(subs->getFile(nId))) my_cache->wr_pcodeBlock(subs->getFile(nId), pcodeBlock, pp, pp->getSize(), sub2, myPcode, pp->nAppendOffset2);           
			    }

    			// ***

		    } while (myModule->nextSub());
       
	    }

		} while (myModule->next());
	}

	return true;
}

/* *
[EXPLANATION]
NAME: CLASS STATIC
DESC:
SEEALSO:
*/
bool parser::appendAllClassesStatic()
{

  if (bProducePcode){
    if (myClass->first()){
		  do {
			  int nClassId = myClass->getId();

        pcode *p = myClass->getClassStaticPcode(nClassId);

        if (p && p->getSize() > 0){
          myPcode->wr_SEPARATOR(pcode__SEPARATOR, utility::con(" CLASS STAT. ", myClass->getName(nClassId), false)); // leading space used for cutting of the leading f...
			     myPcode->pcodeWritePcode(p);

           if (bProducePcode && my_cache && !myClass->isCached(nClassId) && my_cache->parserOpened(myClass->getFile(nClassId))){ my_cache->wr_pcodeBlock(myClass->getFile(nClassId), pcodeBlock, p, p->getSize(), sub2); }

        }

		  } while (myClass->next());
	  }
  }
	return true;
}

// append the pcode of all methods
bool parser::appendAllClasses(pcode *myPcodeClassRegister)
{

	int nNewPcodeOffset = 0;
	pcode *p = 0;
  int n = 0;
  int n2 = 0;


 	if (myClass->first()){
		do {

			int nClassId = myClass->getId();


	   if (bProducePcode){
        myPcodeClassRegister->wr_SEPARATOR(pcode__SEPARATOR, utility::con(" CLASS ", myClass->getName(nClassId), false)); // leading space used for cutting of the leading f...
     }

     p = myClass->getPcode();

     n = myPcodeClassRegister->getPos();

		 	if (bProducePcode){
				myPcodeClassRegister->wr_CLASS(pcode__CLASS, nClassId, 
           myClass->getName(nClassId), 
           myClass->getCountMethod(nClassId), myClass->getCountPropertyGet(nClassId), myClass->getCountPropertySet(nClassId), 
           0, 0, myClass->getParentId(nClassId), myClass->getDestructorId(nClassId));

       nNewPcodeOffset = myPcodeClassRegister->getPos() + pcode::len(pcode__JMP);

       n2 = myPcodeClassRegister->getPos();
       myPcodeClassRegister->setPos(n);

       // write same, add nNewPcodeOffset
				myPcodeClassRegister->wr_CLASS(pcode__CLASS, nClassId, 
           myClass->getName(nClassId), 
           myClass->getCountMethod(nClassId), myClass->getCountPropertyGet(nClassId), myClass->getCountPropertySet(nClassId), 
           nNewPcodeOffset, p->getSize(), myClass->getParentId(nClassId), myClass->getDestructorId(nClassId));
           
       myPcodeClassRegister->setPos(n2);

       myPcodeClassRegister->wr_JMP(pcode__JMP, nNewPcodeOffset + p->getSize()); // write pcode
       myPcodeClassRegister->pcodeWritePcode(p);

       if (bProducePcode && my_cache && !myClass->isCached(nClassId) && my_cache->parserOpened(myClass->getFile(nClassId))){ 
         my_cache->wr_pcodeBlock(myClass->getFile(nClassId), pcodeBlock, p, p->getSize(), sub2); 
       }

     }

      // constructors
			if (myClass->firstConstructor()){
				do {

					  int nId = myClass->getIdMethod();

	         if (bProducePcode){
             myPcodeClassRegister->wr_SEPARATOR(pcode__SEPARATOR, utility::con("   CONSTR. ", myClass->getNameMethod(nClassId, nId), false)); // leading space used for cutting of the leading f...
           }
				
           p = myClass->getPcodeMethod(nClassId, nId);
           if (p == 0){ internalError("Unable to find code for method"); return false; }

           n = myPcodeClassRegister->getPos();

		 				if (bProducePcode){
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getRealNameMethod(nClassId, nId), 
                myClass->getNameMethod(nClassId, nId), 
                myClass->getParameterCountMethod(nClassId, nId), 
                findType(myClass->typeMethod(nClassId, nId)), 0, 0);

             nNewPcodeOffset = myPcodeClassRegister->getPos() + pcode::len(pcode__JMP);

             n2 = myPcodeClassRegister->getPos();
             myPcodeClassRegister->setPos(n);

             // write same, add nNewPcodeOffset
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getRealNameMethod(nClassId, nId), 
                myClass->getNameMethod(nClassId, nId), 
                myClass->getParameterCountMethod(nClassId, nId), 
                findType(myClass->typeMethod(nClassId, nId)), nNewPcodeOffset, p->getSize());

             myPcodeClassRegister->setPos(n2);

             myPcodeClassRegister->wr_JMP(pcode__JMP, nNewPcodeOffset + p->getSize()); // write pcode
             myPcodeClassRegister->pcodeWritePcode(p);

             if (bProducePcode && my_cache && !myClass->isCachedMethod(nClassId, nId) && my_cache->parserOpened(myClass->getFile(nClassId))){ 
               my_cache->wr_pcodeBlock(myClass->getFile(nClassId), pcodeBlock, p, p->getSize(), sub2); 
             }

            }

				} while (myClass->nextConstructor());
      }

      // destructors
			if (myClass->firstDestructor()){
				do {

					  int nId = myClass->getIdMethod();

	         if (bProducePcode){
             myPcodeClassRegister->wr_SEPARATOR(pcode__SEPARATOR, utility::con("   DESTR. ", myClass->getNameMethod(nClassId, nId), false)); // leading space used for cutting of the leading f...
           }
				
           const char *ac = myClass->getName(nClassId);

           p = myClass->getPcodeMethod(nClassId, nId);
           if (p == 0){ internalError("Unable to find code for method."); return false; }


           n = myPcodeClassRegister->getPos();

		 				if (bProducePcode){
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getRealNameMethod(nClassId, nId), 
                myClass->getNameMethod(nClassId, nId), 
                myClass->getParameterCountMethod(nClassId, nId), 
                findType(myClass->typeMethod(nClassId, nId)), 0, 0);

             nNewPcodeOffset = myPcodeClassRegister->getPos() + pcode::len(pcode__JMP);

             n2 = myPcodeClassRegister->getPos();
             myPcodeClassRegister->setPos(n);

             // write same, add nNewPcodeOffset
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getRealNameMethod(nClassId, nId), 
                myClass->getNameMethod(nClassId, nId), 
                myClass->getParameterCountMethod(nClassId, nId), 
                findType(myClass->typeMethod(nClassId, nId)), nNewPcodeOffset, p->getSize());

             myPcodeClassRegister->setPos(n2);

             myPcodeClassRegister->wr_JMP(pcode__JMP, nNewPcodeOffset + p->getSize()); // write pcode
             myPcodeClassRegister->pcodeWritePcode(p);

             if (bProducePcode && my_cache && !myClass->isCachedMethod(nClassId, nId) && my_cache->parserOpened(myClass->getFile(nClassId))){ my_cache->wr_pcodeBlock(myClass->getFile(nClassId), pcodeBlock, p, p->getSize(), sub2); }

            }

				} while (myClass->nextDestructor());
      }

      // methods
			if (myClass->firstMethod()){
				do {

					  int nId = myClass->getIdMethod();

	         if (bProducePcode){
             myPcodeClassRegister->wr_SEPARATOR(pcode__SEPARATOR, utility::con("   METHOD ", myClass->getNameMethod(nClassId, nId), false)); // leading space used for cutting of the leading f...
           }
				
           p = myClass->getPcodeMethod(nClassId, nId);
           if (p == 0){ internalError("Unable to find code for method."); return false; }

           n = myPcodeClassRegister->getPos();

		 				if (bProducePcode){
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getRealNameMethod(nClassId, nId), 
                myClass->getNameMethod(nClassId, nId), 
                myClass->getParameterCountMethod(nClassId, nId), 
                findType(myClass->typeMethod(nClassId, nId)), 0, 0);

             nNewPcodeOffset = myPcodeClassRegister->getPos() + pcode::len(pcode__JMP);

             n2 = myPcodeClassRegister->getPos();
             myPcodeClassRegister->setPos(n);

             // write same, add nNewPcodeOffset
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getRealNameMethod(nClassId, nId), 
                myClass->getNameMethod(nClassId, nId), 
                myClass->getParameterCountMethod(nClassId, nId), 
                findType(myClass->typeMethod(nClassId, nId)), nNewPcodeOffset, p->getSize());

             myPcodeClassRegister->setPos(n2);

             myPcodeClassRegister->wr_JMP(pcode__JMP, nNewPcodeOffset + p->getSize()); // write pcode
             myPcodeClassRegister->pcodeWritePcode(p);

             if (bProducePcode && my_cache && !myClass->isCachedMethod(nClassId, nId) && my_cache->parserOpened(myClass->getFile(nClassId))){ my_cache->wr_pcodeBlock(myClass->getFile(nClassId), pcodeBlock, p, p->getSize(), sub2); }

             int nClassId; int nId; pcode *pcodeCall; int nPcodeOffset;

             if (my_cache && myPcode != myPcodeAll && myClass->firstPcodeCallMethod(nClassId, nId, &pcodeCall, &nPcodeOffset)){
               do {
                 if (my_cache->parserOpened(p->sCurrentFile.ascii())) my_cache->wr_memory_class_registerCallMethod(p->sCurrentFile.ascii(), memory_module_registerCallSub, nClassId, nId, p, p->getPos());
               } while (myClass->nextPcodeCallMethod(nClassId, nId, &pcodeCall, &nPcodeOffset));
             }          

            }

				} while (myClass->nextMethod());
			}


      // methods slots
      /*
			if (myClass->firstSlot()){
				do {

					  int nId = myClass->getIdMethod();

	         if (bProducePcode){
             myPcodeClassRegister->wr_SEPARATOR(pcode__SEPARATOR, utility::con("   SLOT ", myClass->getNameMethod(nClassId, nId), false)); // leading space used for cutting of the leading f...
           }
				
           p = myClass->getPcodeMethod(nClassId, nId);
           if (p == 0){ internalError("Unable to find code for method."); return false; }

           n = myPcodeClassRegister->getPos();

           const char *ac = myClass->getNameMethod(nClassId, nId);

		 				if (bProducePcode){
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getRealNameMethod(nClassId, nId), 
                myClass->getNameMethod(nClassId, nId), 
                myClass->getParameterCountMethod(nClassId, nId), 
                findType(myClass->typeMethod(nClassId, nId)), 0, 0);

             nNewPcodeOffset = myPcodeClassRegister->getPos() + pcode::len(pcode__JMP);

             n2 = myPcodeClassRegister->getPos();
             myPcodeClassRegister->setPos(n);

             // write same, add nNewPcodeOffset
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getRealNameMethod(nClassId, nId), 
                myClass->getNameMethod(nClassId, nId), 
                myClass->getParameterCountMethod(nClassId, nId), 
                findType(myClass->typeMethod(nClassId, nId)), nNewPcodeOffset, p->getSize());

             myPcodeClassRegister->setPos(n2);

             myPcodeClassRegister->wr_JMP(pcode__JMP, nNewPcodeOffset + p->getSize()); // write pcode
             myPcodeClassRegister->pcodeWritePcode(p);

             if (bProducePcode && my_cache && !myClass->isCachedMethod(nClassId, nId) && my_cache->parserOpened(myClass->getFile(nClassId))){ my_cache->wr_pcodeBlock(myClass->getFile(nClassId), pcodeBlock, p, p->getSize(), sub2); }

             pcode *pcodeCall; int nPcodeOffset;

             if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(myClass->getFile(nClassId)) && myClass->firstPcodeCallMethod(nClassId, nId, &pcodeCall, &nPcodeOffset)){
               do {
                 if (my_cache->parserOpened(p->sCurrentFile.ascii())) my_cache->wr_memory_class_registerCallMethod(p->sCurrentFile.ascii(), memory_class_registerCallMethod, nClassId, nId, p, p->getPos());
               } while (myClass->nextPcodeCallMethod(nClassId, nId, &pcodeCall, &nPcodeOffset));
             }          

            }

				} while (myClass->nextSlot());
			}*/

      // methods property get
			if (myClass->firstPropertyGet()){
				do {

					  int nId = myClass->getIdPropertyGet();

	         if (bProducePcode){
             myPcodeClassRegister->wr_SEPARATOR(pcode__SEPARATOR, utility::con("   PROPERTY GET ", myClass->getNamePropertyGet(nClassId, nId), false)); // leading space used for cutting of the leading f...
           }
				
           p = myClass->getPcodePropertyGet(nClassId, nId);
           if (p == 0){ internalError("Unable to find code for method."); return false; }

           n = myPcodeClassRegister->getPos();

           const char *ac = myClass->getNamePropertyGet(nClassId, nId);

           if (bProducePcode){
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getNamePropertyGet(nClassId, nId), 
                myClass->getNamePropertyGet(nClassId, nId), 
                0, 
                findType(myClass->typePropertyGet(nClassId, nId)), 0, 0);

             nNewPcodeOffset = myPcodeClassRegister->getPos() + pcode::len(pcode__JMP);

             n2 = myPcodeClassRegister->getPos();
             myPcodeClassRegister->setPos(n);

             // write same, add nNewPcodeOffset
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getNamePropertyGet(nClassId, nId), 
                myClass->getNamePropertyGet(nClassId, nId), 
                0, 
                findType(myClass->typePropertyGet(nClassId, nId)), nNewPcodeOffset, p->getSize());

             myPcodeClassRegister->setPos(n2);

             myPcodeClassRegister->wr_JMP(pcode__JMP, nNewPcodeOffset + p->getSize()); // write pcode
             myPcodeClassRegister->pcodeWritePcode(p);

             if (bProducePcode && my_cache && !myClass->isCachedPropertyGet(nClassId, nId) && my_cache->parserOpened(myClass->getFile(nClassId))){ my_cache->wr_pcodeBlock(myClass->getFile(nClassId), pcodeBlock, p, p->getSize(), sub2); }

             pcode *pcodeCall; int nPcodeOffset;

             if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(myClass->getFile(nClassId)) && myClass->firstPcodeCallPropertyGet(nClassId, nId, &pcodeCall, &nPcodeOffset)){
               do {
                 if (p->sCurrentFile.ascii()) my_cache->wr_memory_class_registerCallPropertyGet(p->sCurrentFile.ascii(), memory_class_registerCallPropertyGet, nClassId, nId, p, p->getPos());
               } while (myClass->nextPcodeCallPropertyGet(nClassId, nId, &pcodeCall, &nPcodeOffset));
             }          

            }

				} while (myClass->nextPropertyGet());
			}

      // methods property set
			if (myClass->firstPropertySet()){
				do {

					  int nId = myClass->getIdPropertySet();

	         if (bProducePcode){
             myPcodeClassRegister->wr_SEPARATOR(pcode__SEPARATOR, utility::con("   PROPERTY SET ", myClass->getNamePropertySet(nClassId, nId), false)); // leading space used for cutting of the leading f...
           }
				
           p = myClass->getPcodePropertySet(nClassId, nId);
           if (p == 0){ internalError("Unable to find code for method."); return false; }

           n = myPcodeClassRegister->getPos();

           const char *ac = myClass->getNamePropertySet(nClassId, nId);

		 				if (bProducePcode){
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getNamePropertySet(nClassId, nId), 
                myClass->getNamePropertySet(nClassId, nId), 
                myClass->getParameterCountPropertySet(nClassId, nId), 
                findType(myClass->typePropertySet(nClassId, nId)), 0, 0);

             nNewPcodeOffset = myPcodeClassRegister->getPos() + pcode::len(pcode__JMP);

             n2 = myPcodeClassRegister->getPos();
             myPcodeClassRegister->setPos(n);

             // write same, add nNewPcodeOffset
							myPcodeClassRegister->wr_CLASS_METHOD(pcode__CLASS_METHOD, nClassId, 
                nId, 
                myClass->getNamePropertySet(nClassId, nId), 
                myClass->getNamePropertySet(nClassId, nId), 
                myClass->getParameterCountPropertySet(nClassId, nId), 
                findType(myClass->typePropertySet(nClassId, nId)), nNewPcodeOffset, p->getSize());

             myPcodeClassRegister->setPos(n2);

             myPcodeClassRegister->wr_JMP(pcode__JMP, nNewPcodeOffset + p->getSize()); // write pcode
             myPcodeClassRegister->pcodeWritePcode(p);

             if (bProducePcode && my_cache && !myClass->isCachedPropertySet(nClassId, nId) && my_cache->parserOpened(myClass->getFile(nClassId))){ my_cache->wr_pcodeBlock(myClass->getFile(nClassId), pcodeBlock, p, p->getSize(), sub2); }

             pcode *pcodeCall; int nPcodeOffset;

             if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(myClass->getFile(nClassId)) && myClass->firstPcodeCallPropertySet(nClassId, nId, &pcodeCall, &nPcodeOffset)){
               do {
                 if (my_cache->parserOpened(p->sCurrentFile.ascii())) my_cache->wr_memory_class_registerCallPropertySet(p->sCurrentFile.ascii(), memory_class_registerCallPropertySet, nClassId, nId, p, p->getPos());
               } while (myClass->nextPcodeCallPropertySet(nClassId, nId, &pcodeCall, &nPcodeOffset));
             }          

            }

				} while (myClass->nextPropertySet());
			}


		} while (myClass->next());
	}

	return true;
}

// append all project files as binary data
bool parser::appendAllProjectFiles(pcode *myPcodeProjectFile)
{
  if (!bProducePcode) return true;  

  XString sFiles = "";

  { // read compiler.input file
    XString m = cachePath("project.files");
    XFile f(m.ascii());
    if (!f.open(ReadOnly)){
      CONSOLE printError("Could not read project files file");
      return false;
    } else {

      int i = 0;
      char acBuffer[10240];
      int nSize = f.size();
      while (i < nSize && (i = f.readBlock(acBuffer, 10240)) > 0){  
        acBuffer[i] = 0;
        const char *ac = utility::eatUTF16DOM(acBuffer);
        sFiles += ac;
      }
      
      f.close();
    }
  }

  // builtin default png icons
  if (!sFiles.isEmpty()){
    sFiles += kbasicPath("SQLFirst.png") + "\n";
    sFiles += kbasicPath("SQLNext.png") + "\n";
    sFiles += kbasicPath("SQLPrevious.png") + "\n";
    sFiles += kbasicPath("SQLLast.png") + "\n";
    sFiles += kbasicPath("SQLUpdate.png") + "\n";
    sFiles += kbasicPath("SQLDelete.png") + "\n";
    sFiles += kbasicPath("SQLAddNew.png") + "\n";
    sFiles += kbasicPath("SQLRequery.png") + "\n";
    sFiles += kbasicPath("SQLSeek.png") + "\n";
    sFiles += kbasicPath("SQLClearFilter.png") + "\n";
    sFiles += kbasicPath("SQLAddFilter.png") + "\n";
    //sFiles += kbasicPath("SQLAddNotFilter.png") + "\n";
    //sFiles += kbasicPath("SQLSetFilter.png") + "\n";
    //sFiles += kbasicPath("SQLSetNotFilter.png") + "\n";
    sFiles += kbasicPath("SQLSortAscending.png") + "\n";
    sFiles += kbasicPath("SQLSortDescending.png") + "\n";

    sFiles += kbasicPath("FILE_PRINT.png") + "\n";
    sFiles += kbasicPath("VIEW_ZOOMIN.png") + "\n";
    sFiles += kbasicPath("VIEW_ZOOMOUT.png") + "\n";
    sFiles += kbasicPath("VIEW_ZOOM100.png") + "\n";
    sFiles += kbasicPath("VIEW_CLOSE.png") + "\n";
    sFiles += kbasicPath("VIEW_REPORTPREVIEW.png") + "\n";

    sFiles += kbasicPath("VIEW_KONSOLE.png") + "\n";

  }
  




  if (sFiles.stripWhiteSpace().isEmpty()) return true;

  int n = 0;
  int n0 = 0;

  bool bFirst = true;
  do {
    textbuffer *myTextbuffer = new textbuffer(); // needed to truncate big input strings or zero terminate them

    n = sFiles.find("\n", n);
    XString s = sFiles.mid(n0, n >= 0 ? n - n0 : s.length());
    if (n == -1 & bFirst == false) break;
    bFirst = false;
    n0 = n + 1;
    n++;
    
    char *acText;
    const char *ac99 = s.ascii();   
      


    if (s.endsWith(".kbasic_class", false) || s.endsWith(".kbasic_module", false) || s.endsWith(".kbasic", false)){
    } else {




    XFile f(ac99);
    if (!f.open(ReadOnly)){
      XString s = ac99;
      if (!s.endsWith(".kbasic_table", false)){
        CONSOLE printError("Could not read project file (open)");
        CONSOLE printError(ac99);
        return false;
      }
    } else {

      int nSize = f.size();

      if (nSize){

        char *acMem = (char *) malloc(nSize + 1);  // get some memory
        if (acMem == 0){
          CONSOLE printError("Could not get some memory for reading project file ");
          CONSOLE printError(ac99);
          return false;  // couldn't get memory
        }

        int nReaded = 0;
        if ((nReaded = f.readBlock(acMem, nSize)) <= 0){
          CONSOLE printError("Could not read project file ");
          CONSOLE printError(ac99);

          f.close();
          free(acMem);

          return false;
        }

        if (nReaded != nSize){
          CONSOLE printError("Could not read all data from project file ");
          CONSOLE printError(ac99);

          f.close();
          free(acMem);
          return false;
        }
        acMem[nReaded] = 0;

/*        XString ss = ac99;
        if (ss.contains("background.jpg")){
          ss = ss;
        }

        int nPos = myPcodeProjectFile->getPos();

        CONSOLE print(ac99);
        CONSOLE print(" ");
        CONSOLE print(nPos);
        CONSOLE print("\n");*/
        if (s.endsWith(".kbasic_form", false)){ // omit source code
          XString ss = acMem;
          ss = ss.left(ss.find("\nEnd Form\n", false) + 10);
          myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", ac99, ss.length(), (t_pointer) ss.ascii()); 

/*
          char ac[111110];
          sprintf(ac, "%s", ss.ascii());
//          sprintf(ac, "nReaded=%d nSize=%d", nReaded, nSize);

         
      { // test
        XString m = "c:\\kbasic16\\kbide\\ide\\cache\\error.txt";
        XFile k(m.ascii());
        if (!k.open(Truncate)){
        } else {   
          k.writeBlock((void *) ac, strlen(ac));
          k.close();
        }
      }*/

        } else if (s.endsWith(".kbasic_query", false)){ // omit source code
          XString ss = acMem;
          myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", ac99, ss.length(), (t_pointer) ss.ascii()); 

        } else if (s.endsWith(".kbasic_table", false)){ // omit source code
          XString ss = acMem;
          int n = ss.findRev("\nFields=", -1, false);
         // int m = ss.find("\nFields=", false);
          ss = ss.mid(n + 8);
          myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", ac99, ss.length(), (t_pointer) ss.ascii()); 

        } else if (s.endsWith(".kbasic_menubar", false)){ // omit source code
          XString ss = acMem;
          ss = ss.left(ss.find("\nEnd MenuBar\n", false) + 13);
          myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", ac99, ss.length(), (t_pointer) ss.ascii()); 

        } else if (s.endsWith(".kbasic_toolbar", false)){ // omit source code
 
          XString ss = acMem;
          ss = ss.left(ss.find("\nEnd ToolBar\n", false) + 13);
          myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", ac99, ss.length(), (t_pointer) ss.ascii()); 

        } else if (s.endsWith(".kbasic_report", false)){ // omit source code
          XString ss = acMem;
          int n = ss.find("\nEnd Report\n", false);
          ss = ss.left(n + 12);
          ss = ss.replace("Begin Report", "Begin Form", false);
          ss = ss.replace("End Report", "End Form", false);
          s = s.replace(".kbasic_report", ".kbasic_form", false);

          ac99 = s.ascii();   

          myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", ac99, ss.length(), (t_pointer) ss.ascii()); 


        } else {
          myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", ac99, nSize, (t_pointer) acMem); 
        }

        f.close();
        free(acMem);

        
      }
    }
/*
      if (!utility::readSourceFile(&acText, ac99, myTextbuffer)){
        CONSOLE printError("Could not read project file ");
        CONSOLE printError(ac99);
        return false;
      }
*/

      //if (acText) myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", ac99, myTextbuffer->getAllocatedSize(), (t_pointer) acText); 
/*
    } else if (s.endsWith(".jpg", false)
      || sName.endsWith(".gif", false)
      || sName.endsWith(".jpeg", false)
      || sName.endsWith(".bmp", false)
      || sName.endsWith(".png", false)          
      ){

        utility::readSourceFile(&acText, ac99, myTextbuffer));
      if (acText) myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", ac99, strlen(acText), (t_pointer) acText); 
        
   	      char *ac = myTextbuffer.get(f.size());
		      f.readBlock (ac, f.size()); 		          
		      
          if (ac) myPcodeProjectFile->wr_ProjectFile(pcode__PROJECTFILE, "", _projectwindow::getFilenameWithoutPath(filename), f.size(), (t_pointer) ac); 
          f.close();
              */
    }

    delete myTextbuffer;
    
  } while (true);

  
  return true;
}

bool parser::appendAllBreakpoints(pcode *myPcodeProjectFile)
{
  XFile f(cachePath("compiler.breakpoints").ascii());
  if (f.open(ReadOnly)){

    XString s = "";
   
    static char acBuffer[10240];
    int i = 0;
    int i2 = 0;
    int nSize = f.size();
    while (i2 < nSize && (i = f.readBlock(acBuffer, 10239)) > 0){    
      acBuffer[i] = 0;
      const char *ac = utility::eatUTF16DOM(acBuffer);
      s = s.append(ac);      
      i2 += i;
    }      

    int n = 0;
    int n2 = 0;
    int n3 = 0;
    while ((n2 = s.find("|", n)) >= 0){
      XString sFile = s.mid(n, n2 - n);
      n2++;
      n3 = s.find("\n", n2);
      XString sLine = s.mid(n2, n3 - n2);
      
      n = n3;
      if (bProducePcode) myPcodeProjectFile->wr_BREAKPOINT(pcode__BREAKPOINT, sFile.ascii(), sLine.toint());
    }

    f.close();
  }

  return true;
}


bool parser::isSub(char *acModule, char *acIdentifier)
{
	return myModule->existSub(acModule, acIdentifier);
}

/* *
[KBASIC][VB][QBASIC]
NAME: ME
PRINTNAME: Me
TASK: ME
SYNTAX: ME
DESC: ME
CODE:
EXAMPLES: me.kbasic
CATEGORY: KEYWORD, CLASS
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fME_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	return fME_METHOD_CALL(p, nReturnExpressionType, bReturn, false);
}

/* *
[KBASIC][VB][QBASIC]
NAME: PARENT
PRINTNAME: Parent
TASK: PARENT
SYNTAX: PARENT
DESC: PARENT
CODE:
EXAMPLES: parent.kbasic
CATEGORY: KEYWORD, CLASS
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fPARENT_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn)
{
	return fME_METHOD_CALL(p, nReturnExpressionType, bReturn, true);
}

bool parser::fME_METHOD_CALL(pcode *p, int *nReturnExpressionType, bool bReturn, bool bParent)
{
	_BEGIN_

#ifdef KBDEBUG
  if (stopAtLine(12)){
    int i = 9;
    i++;
  }
#endif

	register bool bTerm_ME = false;
	register bool bTerm_PARENT = false;

	if (!bParent && (bTerm_ME = parseTerm(token__ME))){}
	else if (bParent && (bTerm_PARENT = parseTerm(token__PARENT))){}

	if (!bTerm_ME && !bTerm_PARENT) _END_

  if (!isScopeClass()){ semanticError(token__KEYWORD, utility::con(bParent ? "Parent" : "Me", " is used outside of class") ); _ERROR_ }

  int nType = 0;
  bool bBinding = false;
  
re:
	
	if (bParent){
    const char *ac = getParentClass();
    if (ac == 0) _END_
    nType = findType(ac);
    bBinding = memory_type::isBinding(nType);
    if (bBinding){
      if (bProducePcode) p->wr_PUSH__binding_PARENT(pcode__PUSH__binding_PARENT);
    } else {
      if (bProducePcode) p->wr_PUSH_PARENT(pcode__PUSH_PARENT);
    }
    
  } else {
  	if (bProducePcode) p->wr_PUSH_ME(pcode__PUSH_ME);
    nType = findType(getClass());
  }


  if (nType == 0){ 
    _END_ // could be a property called with Me.PROPERTY, so no error
  
  }

  *nReturnExpressionType = nType;

  if (bParent && bBinding){

	  bool bTerm_SYM_DOT = false;

		if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){

      bool bMETHOD = false;
      const char *acMethod = "";

      if (bMETHOD = fID_KEYWORD_OR_BUILTIN(&acMethod)){

        // walk hierarchy
        do {

         if (binding_fCLASS_METHOD_CALL(p, nReturnExpressionType, bReturn, nType, acMethod, false)){

           do {
            _BEGIN2_

            if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){
          			if (bMETHOD = fID_KEYWORD_OR_BUILTIN(&acMethod)){
         				 if (binding_fCLASS_METHOD_CALL(p, nReturnExpressionType, bReturn, *nReturnExpressionType, acMethod, false)){
                } else {
                  _END2_
                  return true;
                }
              }
            } else {
              return true;
            }
           } while (true);
         }

         _END2_
         bMETHOD = fID_KEYWORD_OR_BUILTIN(&acMethod);

         if (bProducePcode){
           p->wr_PUSH__binding_ME(pcode__PUSH__binding_ME);
         }
         nType = myClass->getParentId(nType);      

        } while (nType > 0);
      }
    }
  } else {
    if (fMETHOD_CALL(p, nReturnExpressionType, bReturn, nType, false, true)){
      return true;
    }
    // try the parent class, when keyword Me.
    if (bParent == false){
      _PEND_
      bParent = true;
      goto re;
    }

  }

	_END_
}

/* *
[KBASIC][VB][QBASIC]
NAME: ME
PRINTNAME: Me
TASK: ME
SYNTAX: ME
DESC: ME
CODE:
EXAMPLES: me.kbasic
CATEGORY: KEYWORD, CLASS
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fME(pcode *p, int *nReturnExpressionType, bool bReturn, bool bBinding)
{
	return fME(p, nReturnExpressionType, bReturn, false, bBinding);
}

/* *
[KBASIC][VB][QBASIC]
NAME: PARENT
PRINTNAME: Parent
TASK: PARENT
SYNTAX: PARENT
DESC: PARENT
CODE:
EXAMPLES: parent.kbasic
CATEGORY: KEYWORD, CLASS
SEEALSO: 
LOG: 04-02-2004 implemented
TIP:
*/
bool parser::fPARENT(pcode *p, int *nReturnExpressionType, bool bReturn, bool bBinding)
{
	return fME(p, nReturnExpressionType, bReturn, true, bBinding);
}

bool parser::fME(pcode *p, int *nReturnExpressionType, bool bReturn, bool bParent, bool bBinding)
{
	_BEGIN_

	register bool bTerm_ME = false;
	register bool bTerm_PARENT = false;

  if (!bParent && (bTerm_ME = parseTerm(token__ME))){}
	else if (bParent && (bTerm_PARENT = parseTerm(token__PARENT))){}

	if (!bTerm_ME && !bTerm_PARENT) _END_

  if (!isScopeClass()){ semanticError(token__KEYWORD, utility::con(bParent ? "Parent" : "Me", " is used outside of class") ); _ERROR_ }

  int nType = 0;

	if (bProducePcode){
		if (bParent){
      if (bBinding){
        p->wr_PUSH__binding_ME(pcode__PUSH__binding_ME);
      } else {
  		  p->wr_PUSH_PARENT(pcode__PUSH_PARENT);
      }
      const char *ac = getParentClass();
      if (ac == 0) _END_
      nType = findType(ac);
    } else {
      if (bBinding){
      		p->wr_PUSH__binding_ME(pcode__PUSH__binding_ME);
      } else {
      		p->wr_PUSH_ME(pcode__PUSH_ME);
      }
      nType = findType(getClass());
    }
	}

  if (nType == 0){ semanticError(token__KEYWORD, utility::con(nType, " not defined") ); _ERROR_ }

  *nReturnExpressionType = nType;

	_DONE_
}

bool parser::fTYPE_Class(pcode *p, const char **acType, bool bNew)
{
	_TBEGIN_
		
	const char *acIdentifier;

	if (fID_KEYWORD_OR_BUILTIN(&acIdentifier, false)){

		int i = myClass->getId(acIdentifier);

    if (i > 0){

      //if (!bSilent && p != 0 && bProducePcode){
       //p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fTYPE_Class", getCurrentLine() - 1));
      //}

      if (bNew){

        if (myClass->isAbstract(i)){ semanticError(token__CLASS, utility::con(acIdentifier, " class is ABSTRACT and therefore can not be used to create an object") ); _TERROR_ };

			  *acType = acIdentifier;
  			
			  // p == 0, ist bei cast und typedef
			  if (p == 0){ syntaxError(token__KEYWORD, " use of class construtor not allowed here"); _TERROR_ };
        
        if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acIdentifier)));
  			
			  if (bNew == false) _TDONE_ // don't call the constructor of this class
  			
        bool b;
re:
        b = fCONSTRUCTOR_CALL(p, i);
        if (!b){
          // walk through hierarchy, find in parent class
          i = myClass->getParentId(i);
        } else {

         _TDONE_ 
       }

     } else {

       // cast und typedef oder dim ohne new
			  *acType = acIdentifier;

     }
  		
		}
	}

	_TEND_
}

void parser::registerCatch(int nId2, memory_sub *s2, int nSubId2, pcode *p, int nType)
{
  if (bProducePcode){
     if (isScopeLocal()){
	      s2->registerCatch(nSubId2, p, nType, p->getPos(), 0);//, nPos);
        if (isScopeModule()){
          if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_registerCatch(getCurrentFile(), memory_module_registerCatch, nId2/*myModule->getId(s2->getModule())*/, nSubId2, (int) p, nType, p->getPos());
        } else {
          if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_registerCatch(getCurrentFile(), memory_class_registerCatch, nId2/*myClass->getId(s2->getModule())*/, nSubId2, (int) p, nType, p->getPos());
        }

     } else {
       switch(isScopeClass()){
         case false:
             myModule->registerCatch(nId2, p, nType, p->getPos(), 0);//, nPos);
             if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_module_registerCatch(getCurrentFile(), memory_module_registerCatch, nId2/*myModule->getId(s2->getModule())*/, nSubId2, (int) p, nType, p->getPos());
             break;
         case true:
             myClass->registerCatch(nId2, p, nType, p->getPos(), 0);//, nPos);
             if (my_cache && myPcode != myPcodeAll && my_cache->parserOpened(acCurrentFile)) my_cache->wr_memory_class_registerCatch(getCurrentFile(), memory_class_registerCatch, nId2/*myClass->getId(s2->getModule())*/, nSubId2, (int) p, nType, p->getPos());
             break;
       }
     }
     // catch address = 0 --> CATCH_RETURN
      p->wr_CATCH(pcode__CATCH, nType, 0); // catch address of sub call, later it will be the real address

  }
}
