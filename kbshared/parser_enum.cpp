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


bool parser::fENUM(pcode *p, int *nEnumId, int *nElement)
{
  // special keywords must be handled here to prevent using keywords as variables
  switch(peekToken()){
    case token__END:
    case token__CLASS:
    case token__MODULE:
        return false; 
  }

	_BEGIN_

	bool bTerm_DOT = false;
	bool bTerm_ME = false;
	bool bTerm_PARENT = false;
	
  /*
  modul global: modulname or direct
  class static global: classname or direct
  */

  /*
  interpreter's view:
  local vars (sub/function/method)
  global vars (module,class static, class instance) --> selector wird benötigt
  */

#ifdef KBDEBUG
   if (stopAtLine(163)){
     int i = 9;
     i++;
   }
#endif

  if (bTerm_ME = parseTerm(token__ME)){
    bTerm_DOT = parseTerm(token__SYM_DOT);
  } else if (bTerm_PARENT = parseTerm(token__PARENT)){
    bTerm_DOT = parseTerm(token__SYM_DOT);
  }

  if (bTerm_ME || bTerm_PARENT){
    if (!isScopeClassLocalInstance()){ semanticError(token__MSC_IDENTIFIER, "ME or PARENT not allowed outside class instance scope" ); _ERROR_ }
  }

  const char *acIdentifier;

	if(fID_KEYWORD_OR_BUILTIN(&acIdentifier)){

	  bool bIDENTIFIER2 = false;
	  bool bIDENTIFIER3 = false;
	  
	  const char *acIdentifier2 = "";
	  const char *acIdentifier3 = "";

  
    // ************************************************************************************************
    // global handling 1
    // ************************************************************************************************  

    if (bTerm_ME || bTerm_PARENT){

      if (isScopeClassLocalInstance()){

        if (bTerm_DOT){

          const char *acClass = "";
          
          if (bTerm_ME){
            acClass = getClass();
          } else if (bTerm_PARENT){
            acClass = getParentClass();
          }

          // class enum
          if (myMemory_enum->exist	(acClass, acIdentifier)){

           if ((bTerm_DOT = parseTerm(token__SYM_DOT))){
             if (!(bIDENTIFIER3 = fID_KEYWORD_OR_BUILTIN(&acIdentifier3))){ syntaxError(token__ENUM, "missing element name of enum"); _ERROR_ }

             *nEnumId = findEnum(acClass, acIdentifier);
             *nElement = findEnumElement(*nEnumId, acIdentifier3);
  					  if (*nElement == 0){ semanticError(token__DIM, utility::con(acIdentifier3, " not defined in enum") ); _ERROR_ }
    
             _DONE_
           }
          }
        }
      }

      _END_

    }
    // ************************************************************************************************
    // global handling 2
    // ************************************************************************************************

    // class enum
    if (isScopeClassLocalInstance() || isScopeClassLocalStatic()){
      const char *acClass = getClass();

      if (myMemory_enum->exist	(acClass, acIdentifier)){

        if ((bTerm_DOT = parseTerm(token__SYM_DOT))){
          if (!(bIDENTIFIER3 = fID_KEYWORD_OR_BUILTIN(&acIdentifier3))){ syntaxError(token__ENUM, "missing element name of enum"); _ERROR_ }

          *nEnumId = findEnum(acClass, acIdentifier);
          *nElement = findEnumElement(*nEnumId, acIdentifier3);
          if (*nElement == 0){ semanticError(token__DIM, utility::con(acIdentifier3, " not defined in enum") ); _ERROR_ }

          _DONE_
        }
      }
    }

    {

      // module enum
      {
        const char *acModule = getModule();

        if (myMemory_enum->exist	(acModule, acIdentifier)){

         if ((bTerm_DOT = parseTerm(token__SYM_DOT))){
           if (!(bIDENTIFIER3 = fID_KEYWORD_OR_BUILTIN(&acIdentifier3))){ syntaxError(token__ENUM, "missing element name of enum"); _ERROR_ }

           *nEnumId = findEnum(acModule, acIdentifier);
           *nElement = findEnumElement(*nEnumId, acIdentifier3);
           if (*nElement == 0){ semanticError(token__DIM, utility::con(acIdentifier3, " not defined in enum") ); _ERROR_ }

           _DONE_
         }
        }

        // module enum in der liste
	      if (myModule->first()){
		      do {

			      int nId = myModule->getId();

           acModule = myModule->getName(nId);

           if (myMemory_enum->exist	(acModule, acIdentifier)){

             if ((bTerm_DOT = parseTerm(token__SYM_DOT))){
                 if (!(bIDENTIFIER3 = fID_KEYWORD_OR_BUILTIN(&acIdentifier3))){ syntaxError(token__ENUM, "missing element name of enum"); _ERROR_ }

                 *nEnumId = findEnum(acModule, acIdentifier);
                 *nElement = findEnumElement(*nEnumId, acIdentifier3);
                 if (*nElement == 0){ semanticError(token__DIM, utility::con(acIdentifier3, " not defined in enum") ); _ERROR_ }

                 _DONE_
             }
           }

		      } while (myModule->next());
        }
      }

    }

    // maybe: identifier = classname/modulename . identifier2
    if ((bTerm_DOT = parseTerm(token__SYM_DOT))){
      if (bIDENTIFIER2 = fID_KEYWORD_OR_BUILTIN(&acIdentifier2)){}
    }

    if(bIDENTIFIER2){

      // modulename -> module enum
      if (myModule->exist(acIdentifier)){

        if (myMemory_enum->exist	(acIdentifier, acIdentifier2)){

          if ((bTerm_DOT = parseTerm(token__SYM_DOT))){
            if (!(bIDENTIFIER3 = fID_KEYWORD_OR_BUILTIN(&acIdentifier3))){ syntaxError(token__ENUM, "missing element name of enum"); _ERROR_ }

            *nEnumId = findEnum(acIdentifier, acIdentifier2);
            *nElement = findEnumElement(*nEnumId, acIdentifier3);
  						if (*nElement == 0){ semanticError(token__DIM, utility::con(acIdentifier3, " not defined in enum") ); _ERROR_ }
  
             _DONE_
          }
        }
      }

      // classname -> class enum
      if (myClass->exist(acIdentifier)){

        if (myMemory_enum->exist	(acIdentifier, acIdentifier2)){

         if ((bTerm_DOT = parseTerm(token__SYM_DOT))){
           if (!(bIDENTIFIER3 = fID_KEYWORD_OR_BUILTIN(&acIdentifier3))){ syntaxError(token__ENUM, "missing element name of enum"); _ERROR_ }

           *nEnumId = findEnum(acIdentifier, acIdentifier2);
           *nElement = findEnumElement(*nEnumId, acIdentifier3);
           if (*nElement == 0){ semanticError(token__DIM, utility::con(acIdentifier3, " not defined in enum") ); _ERROR_ }

           _DONE_
         }
        }

      }

    }
  }
	_END_
}

bool parser::fENUM(pcode *p, int *nReturnExpressionType)
{

  register int nEnumId;// = 0;
  register int nElement;// = 0;

  if (fENUM(p, &nEnumId, &nElement)){

    if (bProducePcode){
      	p->wr_PUSH_ENUM(pcode__PUSH_ENUM, nEnumId, nElement);
    }

    *nReturnExpressionType = myMemory_enum->getType(nEnumId, nElement);

    return true;
  }

  return false;
}
