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

bool parser::fCONST(pcode *p, int *nConst, t_scope *scope)
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
  modul local
  class static global: classname or direct
  class local
  */


  /*
  interpreter's view:
  all consts are global declared in one consts pool
  */
  *scope = global;

#ifdef KBDEBUG
   if (stopAtLine(171)){
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

            if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acClass)));
          }

          int nClassId = myClass->getId(acClass);

          if (myClass->existConst	(nClassId, acIdentifier)){

            *nConst = myClass->getIdConst(acClass, acIdentifier);
            _DONE_
          }
       
        }
      }

      _END_ 
    }

    // ************************************************************************************************
    // local handling
    // ************************************************************************************************

    if (isScopeModuleLocal()){

      // module local const
      if (myModule->existSubConst	(getModule(), getSub(), acIdentifier)){		  

        *nConst = myModule->getIdSubConst(getModule(), getSub(), acIdentifier);
        _DONE_
      }

    }

    if (isScopeClassLocalInstance() || isScopeClassLocalStatic()){ // static and instance
    
      if (isScopeClassPropertyGet()){
        if (myClass->existPropertyGetConst	(getClass(), getMethod(), acIdentifier)){

          *nConst = myClass->getIdPropertyGetConst(getClass(), getMethod(), acIdentifier);
          _DONE_
        }
      } else if (isScopeClassPropertySet()){
        if (myClass->existPropertySetConst	(getClass(), getMethod(), acIdentifier)){

          *nConst = myClass->getIdPropertySetConst(getClass(), getMethod(), acIdentifier);
          _DONE_
        }
      } else {
      
        // class local const
        if (myClass->existMethodConst	(getClass(), getMethod(), acIdentifier)){		  

          *nConst = myClass->getIdMethodConst(getClass(), getMethod(), acIdentifier);
          _DONE_

        }
      }
    
    }

    // ************************************************************************************************
    // local handling - VARIABLE !!! the same in parser_const.cpp
    // ************************************************************************************************

    if (isScopeModuleLocal() || isScopeModuleLocalStatic()){

      // module local var
      if (myModule->existSubVar	(getModule(), getSub(), acIdentifier)){		 
        _END_

      }

      // sub/function parameter   
      {
			  const char *acName = "";
   		  const char *acType = "";
   		  int nParameterCall = 0;
   		  bool bOptional = false;
   		  bool bDefault = false;
   		  bool bParamArray = false;
   		  t_array *array = 0;
        defaultvalue *defval = 0;
        int nParamId = 0;
        int nParamLStringLen = 0;

    	  int nModuleId = myModule->getId(getModule());
    	  int nId = myModule->getIdSub(getModule(), getSub());
         
#ifdef KBDEBUG
      if (stopAtLine(242)){
        int i = 9;
        i++;
      }
#endif

      
     	  if (myModule->firstParameterSub	(nModuleId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &array, &defval, &nParamId, &nParamLStringLen)){
    		  do {
					  if (utility::my_stricmp(acIdentifier, acName) == 0){

         	  		int n = findType(acType);
        				if (n == 0){ semanticError(token__DIM, utility::con(acType, " not defined") ); _ERROR_ }

                _END_
					  }
    		  } while(myModule->nextParameterSub	(nModuleId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &array, &defval, &nParamId, &nParamLStringLen));
    	  }
      }
    }

    if (isScopeClassLocalInstance() || isScopeClassLocalStatic()){ // static and instance

      // class local
      if (isScopeClassPropertySet()){

       if (myClass->existPropertySetVar	(getClass(), getMethod(), acIdentifier)){

         _END_
       }
      

       // property set method vars + parameter
       {
			    const char *acName = "";
   		    const char *acType = "";
   		    int nParameterCall = 0;
   		    bool bOptional = false;
   		    bool bDefault = false;        
   		    bool bParamArray = false;
   		    t_array *array = 0;
         defaultvalue *defval = 0;
         int nParamId = 0;
         int nParamLStringLen = 0;

    	    int nClassId = myClass->getId(getClass());
    	    int nId = myClass->getIdPropertySet(getClass(), getMethod());
           
     	    if (myClass->firstParameterPropertySet	(nClassId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &array, &defval, &nParamId, &nParamLStringLen)){
    		    do {
					    if (utility::my_stricmp(acIdentifier, acName) == 0){

         	  		  int n = findType(acType);
        				  if (n == 0){ semanticError(token__DIM, utility::con(acType, " not defined") ); _ERROR_ }
                
                  _END_
					    }
    		    } while(myClass->nextParameterPropertySet	(nClassId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &array, &defval, &nParamId, &nParamLStringLen));
    	    }
       }
      } else if (isScopeClassPropertyGet()){

       if (myClass->existPropertyGetVar	(getClass(), getMethod(), acIdentifier)){

        
         _END_
       }
             
      } 
      
      {


       // static or instance method var
       if (myClass->existMethodVar	(getClass(), getMethod(), acIdentifier)){

         _END_
       }
      

       // method parameter
       {
			    const char *acName = "";
   		    const char *acType = "";
   		    int nParameterCall = 0;
   		    bool bOptional = false;
   		    bool bDefault = false;        
   		    bool bParamArray = false;
   		    t_array *array = 0;
         defaultvalue *defval = 0;
         int nParamId = 0;
         int nParamLStringLen = 0;

    	    int nClassId = myClass->getId(getClass());
    	    int nId = myClass->getIdMethod(getClass(), getMethod());
           
     	    if (myClass->firstParameterMethod	(nClassId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &array, &defval, &nParamId, &nParamLStringLen)){
    		    do {
					    if (utility::my_stricmp(acIdentifier, acName) == 0){

         	  		  int n = findType(acType);
        				  if (n == 0){ semanticError(token__DIM, utility::con(acType, " not defined") ); _ERROR_ }
              
                  _END_
					    }
    		    } while(myClass->nextParameterMethod	(nClassId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &array, &defval, &nParamId, &nParamLStringLen));
    	    }
       }   
      }
    }

    // ************************************************************************************************
    // global handling 2
    // ************************************************************************************************
    {

      // global module const
      {
        const char *acModule = getModule();

        if (myModule->existConst	(acModule, acIdentifier)){

          *nConst = myModule->getIdConst(acModule, acIdentifier);                   

          _DONE_
        }

        // global module const in der liste
	      if (myModule->first()){
		      do {

			      int nId = myModule->getId();

           acModule = myModule->getName(nId);

           if (myModule->existConst	(acModule, acIdentifier)){

             *nConst = myModule->getIdConst(acModule, acIdentifier);
             
             if (my_cache) addDependency(p->sCurrentFile.ascii(), myModule->getFile(myModule->getId(acModule)));

             _DONE_

           }

		      } while (myModule->next());
        }
      }


      // global class const
      {
        const char *acClass = getClass();
        int nClassId = myClass->getId(acClass);

        if (myClass->existConst	(nClassId, acIdentifier)){
          
         *nConst = myClass->getIdConst(acClass, acIdentifier);
          _DONE_
        }
      }

    }

  	bool bIDENTIFIER2;
  	const char *acIdentifier2;

    // maybe: identifier = classname/modulename . identifier2
    if ((bTerm_DOT = parseTerm(token__SYM_DOT))){
      if (bIDENTIFIER2 = fID_KEYWORD_OR_BUILTIN(&acIdentifier2)){}
    } else {
      bIDENTIFIER2 = false;
    }

    if(bIDENTIFIER2){

      // modulename -> global module const
      if (myModule->exist(acIdentifier)){

        int nModuleId = myModule->getId(acIdentifier);

        if (myModule->existConst	(nModuleId, acIdentifier2)){

          *nConst = myModule->getIdConst(acIdentifier, acIdentifier2);

          if (my_cache) addDependency(p->sCurrentFile.ascii(), myModule->getFile(myModule->getId(acIdentifier)));

          _DONE_
        }
      }

      // classame -> global class const
      if (myClass->exist(acIdentifier)){

        int nClassId = myClass->getId(acIdentifier);

        if (myClass->existConst	(nClassId, acIdentifier2)){

          *nConst = myClass->getIdConst(acIdentifier, acIdentifier2);

          if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acIdentifier)));

          _DONE_
        }
      }

    }
 }

 _END_

}

bool parser::fCONST(pcode *p, int *nReturnExpressionType)
{

  register int nConst;// = 0;
  register t_scope scope;// = global;

  if (fCONST(p, &nConst, &scope)){

    if (bProducePcode){
      p->wr_PUSH_CONST(pcode__PUSH_CONST, nConst);
    }

    *nReturnExpressionType = pcode__CONST;

    return true;
  }

  return false;
}
