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



bool parser::fSELECTOR_TYPE(
                            pcode *p, 
                            int nParentVar, 
                            int nParentIdType, 
                            int nParentType, 
                            const char *acIdentifier, 
                            int *nIdType, 
                            int *nType, 
                            t_arrayVariable *a, 
                            bool bAssignment,
                            bool *bSizeAll,                            
                            int *nLStringLen,
                            bool bClassVar,
                            t_scope scope,
                            bool bARRAY2,
                            bool bTestProperty

                         )
{
	_BEGIN_

	bool bSELECTOR[parser__MAX_ID];
	bool bTerm_SYM_DOT = false;

	const char *acSelector[parser__MAX_ID];
	int nSelector = 0;
	bool bARRAY[MAX_TYPE];

 	bool bTerm_SYM_BR_OP = false;
 	bool bTerm_SYM_BR_CL = false;

  int nType2 = 0;
  int nAllSize = 0;  
  


	int nId = nParentVar; 
	*nIdType =  nParentIdType; 
 	*nType = *nIdType;

  a->element.def.count = 0;
  a->element.use.count = 0;

#ifdef KBDEBUG
  if (stopAtLine(13)){
    int i = 9;
    i++;
  }
#endif


  // only if user defined structure or user defined type
  if (nId > 0 && !myMemory_type->scalar(*nIdType) && (memory_type::isType(*nIdType) || !bClassVar)){ 

#ifdef KBDEBUG
  if (stopAtLine(84)){
    int i = 9;
    i++;
  }
#endif

    *bSizeAll = true;

		int type = 0;

    if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){

  		bSELECTOR[0] = false;

      do {

    		if (nSelector < parser__MAX_ID){

					if (bSELECTOR[nSelector] = fID_KEYWORD_OR_BUILTIN(&acSelector[nSelector])){

						int parent_type = 0;
						int myMemory_typeelement = 0;

#ifdef KBDEBUG
          if (stopAtLine(64)){
           int i = 9;
           i++;
          }
#endif

           // wenn erste ebene muss treffen  
           bool bOnlyFirstLevel = nSelector == 0;

						type = myMemory_type->getType2(*nIdType, acSelector[nSelector], &parent_type, &myMemory_typeelement, &nAllSize, nLStringLen, bOnlyFirstLevel);

            if (type > 0){
             myMemory_type->getArray(parent_type, myMemory_typeelement)->copyArray(&a->element.def);

             if (bARRAY[nSelector] = fARRAY(p, &a->element.use, type, parent_type, myMemory_typeelement, bAssignment, false, false, scope)){
               *bSizeAll = false;

							  if (t_array::isArray(&a->element.def) == false){ semanticError(token__SYM_DOT, utility::con(acSelector[nSelector], " is not an array") ); _ERROR_ }
               
               // test for a->count == b->count
							  if (t_array::dimensionsEqual(&a->element.use, &a->element.def) == false){ semanticError(token__SYM_DOT, utility::con(acSelector[nSelector], " different count of dimensions") ); _ERROR_ }

             } else { 

							  if (bProducePcode){
 								  p->wr_ARRAY(pcode__ARRAY, 0, type, parent_type, getScopeCode(), myMemory_typeelement, bAssignment, false); // write pcode
							  }		
						  }
           }

					}

			    if (bTerm_SYM_DOT = parseTerm(token__SYM_DOT)){}

    		}
    	} while (bSELECTOR[nSelector++] && bTerm_SYM_DOT);

			nSelector--; // the last

			if (bSELECTOR[nSelector]){

       int n = peekToken();

				if (nSelector == 0 && (n == token__SYM_BR_OP)){
         
          // class method ?

					_END_

				} else if (type == 0){
                    
         _END_
				}

				*nType = myMemory_type->getType(*nIdType, acSelector[nSelector]); 

   			if (bARRAY2){

					if (t_array::isArray(&a->var.def) == false && t_array::isArray(&a->class_.def) == false){ semanticError(token__SYM_DOT, utility::con(acIdentifier, " is not an array") ); _ERROR_ }

          // test for a->count == b->count
          if (t_array::dimensionsEqual(&a->var.use, &a->var.def) == false || t_array::dimensionsEqual(&a->class_.use, &a->class_.def) == false){ semanticError(token__SYM_DOT, utility::con(acIdentifier, " different count of dimensions") ); _ERROR_ }

				}

				_DONE_

			}

    } else {

			if (bARRAY2){

  			if (t_array::isArray(&a->var.def) == false && t_array::isArray(&a->class_.def) == false){ 
          switch(*nType){
            case pcode___strings: _END_
            case pcode___stringsstrings: _END_
            case pcode___array: _END_
          }
    
          {
            semanticError(token__SYM_DOT, utility::con(acIdentifier, " is not an array") ); _ERROR_ 
          }
        }

       // test for a->count == b->count
       if (t_array::dimensionsEqual(&a->var.use, &a->var.def) == false || t_array::dimensionsEqual(&a->class_.use, &a->class_.def) == false){ semanticError(token__SYM_DOT, utility::con(acIdentifier, " different count of dimensions") ); _ERROR_ }

  			_DONE_

			}
		}

	} else if (nId > 0){ // only if acIdentifier is already declared		

    *bSizeAll = true;
	   
		if (bARRAY2){

			if (nId > 0){ // only if acIdentifier is already declared
        nType2 = bClassVar ? a->class_.def.type : a->var.def.type;

       /*
        A Variant that is not declared as an array can still contain an array.
        A Variant variable can contain an array of any type, except fixed-length strings and user-defined types. 
        */
  			if (nType2 != pcode__VARIANT && (t_array::isArray(&a->var.def) == false && t_array::isArray(&a->class_.def) == false)){ 
          

          int i;
          const char *ac;

          i = token__KEYWORD + 1;
          ac = token::keyword_(i++);
          while(strlen(ac)){
            if (utility::my_stricmp(ac, acIdentifier) == 0){
              _END_
            }
            ac = token::keyword_(i++);
          }

          i = token__BUILTIN + 1;
          ac = token::builtin_(i++);
          while(strlen(ac)){
            if (utility::my_stricmp(ac, acIdentifier) == 0){
              _END_
            }
            ac = token::builtin_(i++);
          }

          i = token__NUM_TYPE + 1;
          ac = token::type_(i++);
          while(strlen(ac)){
            if (utility::my_stricmp(ac, acIdentifier) == 0){
              _END_
            }
            ac = token::type_(i++);
          }

          i = token__LITERAL + 1;
          ac = token::literals_(i++);
          while(strlen(ac)){
            if (utility::my_stricmp(ac, acIdentifier) == 0){
              _END_
            }
            ac = token::literals_(i++);
          }

          i = token__SYMBOL + 1;
          ac = token::symbol_(i++);
          while(strlen(ac)){
            if (utility::my_stricmp(ac, acIdentifier) == 0){
              _END_
            }
            ac = token::symbol_(i++);
          }

          i = token__OPERATOR + 1;
          ac = token::operator_(i++);
          while(strlen(ac)){
            if (utility::my_stricmp(ac, acIdentifier) == 0){
              _END_
            }
            ac = token::operator_(i++);
          }
          
          semanticError(token__SYM_DOT, utility::con(acIdentifier, " is not an array") ); _ERROR_ }

        if (*nType == pcode__VARIANT && nType2 == pcode__VARIANT){}
        // test for a->count == b->count
        else if (t_array::dimensionsEqual(&a->var.use, &a->var.def) == false || t_array::dimensionsEqual(&a->class_.use, &a->class_.def) == false){           

          semanticError(token__SYM_DOT, utility::con(acIdentifier, " different count of dimensions") ); _ERROR_ }

			} else {
        a->var.use.copyArray(&a->var.def);				
        a->class_.use.copyArray(&a->class_.def);				
			}

      _DONE_
			
 		}
	}

	_END_
}


bool parser::fSELECTOR_CLASS_VAR(pcode *p, int *nVar, int *nIdType, int *nType, 
                                 t_arrayVariable *a, t_scope *scope, 
                                 const char **acIdentifier, bool *bARRAY2, 
                                 bool bAssignment, 
                                 int *nAccessScopeId, int *nAccessScope, int *nLStringLen)
{
	_BEGIN_

  a->class_.def.count = 0;
  a->class_.use.count = 0;

	//bool bTerm_DOT = false;

  if (/*bTerm_DOT = */parseTerm(token__SYM_DOT)){

    bool bTerm_DOT = false;

#ifdef KBDEBUG
   if (stopAtLine(129)){
     int i = 9;
     i++;
   }
#endif

  	//bool bIDENTIFIER = false;
  	const char *acClass = myClass->getName(*nType);
    if (acClass == 0) _END_
    const char *acClass2 = "";
    bool b = false;
    int nPos = 0;

   do {

  	  if (fID_KEYWORD_OR_BUILTIN(acIdentifier)){


       do {
   
         int nId = myClass->getId(acClass);
         int nVar2 = *nVar;
         int nType2 = *nType;
         t_scope scope2 = *scope;

         // class static var
         if (existStaticVar(acClass, *acIdentifier, 
                          nVar, nIdType, nType, 
                          &a->class_.def, scope, nAccessScopeId, nAccessScope, nLStringLen))
         {        
           acClass2 = acClass;

	         if (bProducePcode){
				      p->wr_SET_ME(pcode__SET_ME, nVar2, scope2, bAssignment);            
           }

           acClass = myClass->getName(*nType);

           if (*bARRAY2 = fARRAY(p, &a->class_.use, *nIdType, *nVar, 0, bAssignment, false, true, *scope)){}
           b = true;
           nPos = getTokenPos();

           if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acClass2)));
           break;

         // class instance var
         } else if (existVar(acClass, *acIdentifier, 
                          nVar, nIdType, nType, 
                          &a->class_.def, scope, nAccessScopeId, nAccessScope, nLStringLen))
         {    

           acClass2 = acClass;

	         if (bProducePcode){
   				    p->wr_SET_ME(pcode__SET_ME, nVar2, scope2, bAssignment);
           }

           acClass = myClass->getName(*nType);
           if (*bARRAY2 = fARRAY(p, &a->class_.use, *nIdType, *nVar, 0, bAssignment, false, true, *scope)){}
           b = true;
           nPos = getTokenPos();

           if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acClass2)));
           break;
           
         }

         // walk through inheritance tree
         acClass = myClass->getParentName(nId);
       } while (acClass != 0);
           
      } else {
        break;
      }

      bTerm_DOT = parseTerm(token__SYM_DOT);

    } while (bTerm_DOT && acClass != 0);

    if (b){
      setTokenPos(nPos); // could be a method call and not a class var
      _DONE_
    }

  }

	_END_
}



bool parser::fSELECTOR_CLASS_PROPERTY(pcode *p, int nClassId,
                                 const char *acIdentifier,
                                 bool bAssignment,
                                 bool *binding_fPROPERTY_ASSIGNMENT,
                                 int *nReturnId, int *nReturnType
                                 )
{
	_BEGIN_

//#ifdef KBDEBUG
   if (stopAtLine(7)){
     int i = 9;
     i++;
   }
//#endif
   *binding_fPROPERTY_ASSIGNMENT = false;
      
   do {
     if (memory_type::isBinding(nClassId)){

        if (!bAssignment){

          XString s = acIdentifier;
          s = s.prepend("GETPROPERTY_");

          
          if (binding_fPROPERTY2(p, nClassId, s.ascii(), nReturnId, nReturnType)){

            *binding_fPROPERTY_ASSIGNMENT = true;

            if (bProducePcode){

              static int nParamCount = 0;
              static bool bReturn = true;

              p->wr_PUSH_INTEGER(pcode__PUSH_INTEGER, nParamCount);
			        p->wr_binding_ClassProperty(pcode__binding_CLASSPROPERTY, *nReturnId, bReturn);                
            }

            // access test private, public... not needed
            _DONE_
          }

        } else {

          XString s = acIdentifier;
          s = s.prepend("SETPROPERTY_");

          if (binding_fPROPERTY_ASSIGNMENT2(p, nClassId, s.ascii(), nReturnId, nReturnType)){

            *binding_fPROPERTY_ASSIGNMENT = true;

            // access test private, public... not needed
            _DONE_
          }
        }

     } else {

        if (!bAssignment){
          bool bParent = nClassId == myClass->getParentId(getClass());   

          int nId = myClass->getIdPropertyGet(nClassId, acIdentifier);
          if (nId > 0){

              if (bProducePcode){
                p->wr_ENTER_PROPERTYGET(pcode__ENTER_PROPERTYGET, nClassId, nId); // write pcode
  	            p->wr_ClassPropertyGet(pcode__CLASSPROPERTYGET, nClassId, nId, (char *) acIdentifier, false, false, bParent, true);
              }

              _DONE_
          }

        } else {

          if (myClass->existPropertySet(nClassId, acIdentifier) > 0){         
              _DONE_
          }

        }

     }

      nClassId = myClass->getParentId(nClassId);
   } while (nClassId > 0);

	_END_
}


bool parser::fVARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, 
                     bool *bImplicitDIM, bool bTestImplicitDim, t_arrayVariable *a, 
                     bool *bSizeAll, int *nLStringLen, bool *bReference, bool *bProperty, bool bTestProperty, 
                     bool bClassVar, int nClassId, bool bArgumentOnly, bool bAssignment, bool bRedim)                     
{

  // special keywords must be handled here to prevent using keywords as variables  

  switch(peekToken()){
    case token__END:
    case token__CLASS:
    case token__MODULE:
      return false;
  }


	//_BEGIN_
  _BEGIN_fVARIABLE_

   if (!proceedParse()) _END_fVARIABLE_;

    // * optimize
   static pcode *__p = 0;
   static int __nCurrentToken = -1;
   static bool __bTestImplicitDim = false;
   static bool __bTestProperty = false;
   static bool __bClassVar = false;
   static int __nClassId = false;
   static bool __bArgumentOnly = false;
   static bool __bAssignment = false;
   static bool __bRedim = false;
   static bool __bDone = false;


   static int _nCurrentToken = -1;
   static int _nCurrentPcode = -1;
   static t_with2 _currentWith;

   static int _nVar = -1;
   static t_scope _scope = global;
   static int _nIdType = -1;
   static int _nType = -1;
   static bool _bImplicitDIM = *bImplicitDIM;
   static t_arrayVariable _a;
   static bool _bSizeAll = false;
   static int _nLStringLen = -1;
   static bool _bReference = false;
   static bool _bProperty = false;

   if (__nCurrentToken == nCurrentToken && __bDone &&      
     __p == p &&
     __bTestImplicitDim == bTestImplicitDim &&
     __bTestProperty == bTestProperty &&
     __bClassVar == bClassVar &&
     __nClassId == nClassId &&
     __bArgumentOnly == bArgumentOnly &&
     __bAssignment == bAssignment &&
     __bRedim == bRedim     
     )
   {
     setTokenPos(_nCurrentToken); 
     p->setPos(_nCurrentPcode); 
     with = _currentWith; 

     *nVar = _nVar;
     *scope = _scope;
     *nIdType = _nIdType;
     *nType = _nType;
     *bImplicitDIM = _bImplicitDIM;
     *a = _a;
     *bSizeAll = _bSizeAll;
     *nLStringLen = _nLStringLen;
     *bReference = _bReference;
     *bProperty = _bProperty;
     *bProperty = _bProperty;

     _DONE_
   } else {
     __bDone = false;

     __nCurrentToken = nCurrentToken;

     __p = p;
     __bTestImplicitDim = bTestImplicitDim;
     __bTestProperty = bTestProperty;
     __bClassVar = bClassVar;
     __nClassId = nClassId;
     __bArgumentOnly = bArgumentOnly;
     __bAssignment = bAssignment;
     __bRedim = bRedim;


   }
   // *
 
  /*
  possibilities:

  modul global: modulname or direct
  modul local

  class instance global: me, parent or direct
  class static global: classname or direct
  class local

  param

  */

  *bImplicitDIM = false;
  *bProperty = false;
  *nLStringLen = 0;

  // nLastVarId+nLastVarScope needed for rollback in fINPUT ->  undeclare variable 
  nLastVarId = 0; 


  a->var.def.count = 0;
  a->var.use.count = 0;

  a->class_.def.count = 0;
  a->class_.use.count = 0;

  a->element.def.count = 0;
  a->element.use.count = 0;


  /*
  interpreter's view:
  local vars (sub/function/method)
  global vars (module,class static, class instance) --> selector wird benötigt
  */


	bool bTerm_DOT = false;
	bool bTerm_ME = false;
	bool bTerm_PARENT = false;

  int nAccessScopeId = 0;
  int nAccessScope = 0;  
  int nImplicitType = 0;
	bool bSELECTOR_TYPE = false;
	bool bSELECTOR_CLASS_VAR = false;
	//bool bSELECTOR_CLASS_PROPERTY = false;
	bool bARRAY2 = false;
  const char *acIdentifier2 = "";

  int n = p->getPos();

#ifdef KBDEBUG
   if (stopAtLine(7)){
     int i = 9;
     i++;
   }
#endif

  if (bTerm_ME = parseTerm(token__ME)){   
  } else if (bTerm_PARENT = parseTerm(token__PARENT)){    
  }
  _BEGIN3_


  if (bTerm_ME || bTerm_PARENT){
    bTerm_DOT = parseTerm(token__SYM_DOT);
    if (bArgumentOnly) _END_

    if (!isScopeClassLocalInstance()){ semanticError(token__MSC_IDENTIFIER, "ME or PARENT not allowed outside class instance scope" ); _ERROR_ }
  }

  bool bIDENTIFIER;
	const char *acIdentifier;

       if (bIDENTIFIER = fID_KEYWORD_OR_BUILTIN(&acIdentifier)){ nImplicitType = defaultType(acIdentifier); }
	// because the identifier has a suffix $,%,&,#,!, AS <TYPE> is not allowed, already found out
	else if (bIDENTIFIER = fID_STRING(&acIdentifier)){ nImplicitType = pcode__QSTRING; }
	else if (bIDENTIFIER = fID_INTEGER(&acIdentifier)){ nImplicitType = pcode__INTEGER; }
	else if (bIDENTIFIER = fID_LONG(&acIdentifier)){ nImplicitType = pcode__LONG; }
	else if (bIDENTIFIER = fID_SINGLE(&acIdentifier)){ nImplicitType = pcode__SINGLE; }
	else if (bIDENTIFIER = fID_DOUBLE(&acIdentifier)){ nImplicitType = pcode__DOUBLE; }
	else if (bIDENTIFIER = fID_CURRENCY(&acIdentifier)){ nImplicitType = pcode__CURRENCY; }

	if(bIDENTIFIER){

	bool bIDENTIFIER2 = false;




#ifdef KBDEBUG
   if (stopAtLine(4)){
     int i = 9;
     i++;
   }
#endif

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

          // global class static var
          if (existStaticVar(acClass, acIdentifier, 
                           nVar, nIdType, nType, 
                           &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
          {      
            a->var.def.type = *nIdType;
            acIdentifier2 = acIdentifier;

            if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acClass)));
            goto selector; 
          }

          // global class instance var
          if (existVar(acClass, acIdentifier, 
                           nVar, nIdType, nType, 
                           &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
          {        
            a->var.def.type = *nIdType;
            acIdentifier2 = acIdentifier;

            if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acClass)));
            goto selector; 
          }

          // global class property var
          if (!bAssignment && existPropertyGet(acClass, acIdentifier, 
                           nVar, nIdType, nType, 
                           &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
          {        
            *bProperty = true;
            _END3_
            *nIdType = -200; // workaorund nIdType == -200

		         if (bTerm_ME){
			          if (bProducePcode) p->wr_PUSH_ME(pcode__PUSH_ME);
		         } else if (bTerm_PARENT){
			          if (bProducePcode) p->wr_PUSH_PARENT(pcode__PUSH_PARENT);        
             }

            if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acClass)));
            goto selector2; 
          }
          
          // global class property var
          if (bAssignment && existPropertySet(acClass, acIdentifier, 
                           nVar, nIdType, nType, 
                           &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
          {        
            *bProperty = true;
            _END3_
            *nIdType = -200; // workaorund nIdType == -200

		         if (bTerm_ME){
			          if (bProducePcode) p->wr_PUSH_ME(pcode__PUSH_ME);
		         } else if (bTerm_PARENT){
			          if (bProducePcode) p->wr_PUSH_PARENT(pcode__PUSH_PARENT);        
             }
             
             if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acClass)));
             goto selector2; 
          }
          
        } else {
          // me oder parent auch gültig
          *nVar = 0;
          if (bTerm_ME){
  		      *nIdType = *nType = token__ME;
          } else if (bTerm_PARENT){
            *nIdType = *nType = token__PARENT;
          }
          *scope = me; 
          
          _DONE_
        }
      }

      _END_fVARIABLE_ // maybe it's a method call

    }


    // ************************************************************************************************
    // local handling - VARIABLE !!! the same in parser_const.cpp
    // ************************************************************************************************

    if (isScopeModuleLocal() || isScopeModuleLocalStatic()){

      // module local var
      if (!bArgumentOnly && myModule->existSubVar	(getModule(), getSub(), acIdentifier)){		  

        *nVar = myModule->getIdSubVar(getModule(), getSub(), acIdentifier);
        *nIdType = *nType = myModule->typeSubVar(getModule(), getSub(), acIdentifier);
        myModule->getArraySubVar(getModule(), getSub(), acIdentifier)->copyArray(&a->var.def);
        a->var.def.type = *nIdType;
        *nLStringLen = myModule->getLStringLenSubVar(getModule(), getSub(), acIdentifier);

        if (isScopeModuleLocalStatic() || myModule->isStaticSubVar(getModule(), getSub(), acIdentifier)){
          *scope = global; 
        } else {
          *scope = local; 
        }

        acIdentifier2 = acIdentifier;
        goto selector; 
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

              *nVar = nParamId;
		          *nIdType = *nType = n;
              array->copyArray(&a->var.def);
              a->var.def.type = *nIdType;
              *scope = param; 
              *bReference = nParameterCall != token__BY_VAL;
              *nLStringLen = nParamLStringLen;

              acIdentifier2 = acIdentifier;
              goto selector; 
					  }
    		  } while(myModule->nextParameterSub	(nModuleId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &array, &defval, &nParamId, &nParamLStringLen));
    	  }
      }
    }

    if (isScopeClassLocalInstance() || isScopeClassLocalStatic()){ // static and instance

      // class local
      if (isScopeClassPropertySet()){

       if (!bArgumentOnly && myClass->existPropertySetVar	(getClass(), getMethod(), acIdentifier)){

         *nVar = myClass->getIdPropertySetVar(getClass(), getMethod(), acIdentifier);
 		      *nIdType = *nType = myClass->typePropertySetVar(getClass(), getMethod(), acIdentifier);
         myClass->getArrayPropertySetVar(getClass(), getMethod(), acIdentifier)->copyArray(&a->var.def);
         a->var.def.type = *nIdType;
         *scope = local; 
         *nLStringLen = myClass->getLStringLenPropertySetVar(getClass(), getMethod(), acIdentifier);
         
         acIdentifier2 = acIdentifier;
         goto selector; 
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
                
               *nVar = nParamId;  
		           *nIdType = *nType = n;
               array->copyArray(&a->var.def);
               a->var.def.type = *nIdType;
               *scope = param; 
               *bReference = nParameterCall != token__BY_VAL;
               *nLStringLen = nParamLStringLen;  

               acIdentifier2 = acIdentifier;
               goto selector; 
					    }
    		    } while(myClass->nextParameterPropertySet	(nClassId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &array, &defval, &nParamId, &nParamLStringLen));
    	    }
       }
      } else if (isScopeClassPropertyGet()){

       if (!bArgumentOnly && myClass->existPropertyGetVar	(getClass(), getMethod(), acIdentifier)){

         *nVar = myClass->getIdPropertyGetVar(getClass(), getMethod(), acIdentifier);
 		      *nIdType = *nType = myClass->typePropertyGetVar(getClass(), getMethod(), acIdentifier);
         myClass->getArrayPropertyGetVar(getClass(), getMethod(), acIdentifier)->copyArray(&a->var.def);
         a->var.def.type = *nIdType;
         *scope = local; 
         *nLStringLen = myClass->getLStringLenPropertyGetVar(getClass(), getMethod(), acIdentifier);
         
         acIdentifier2 = acIdentifier;
         goto selector; 
       }
             
      } 
      
      {


       // static or instance method var
       if (!bArgumentOnly && myClass->existMethodVar	(getClass(), getMethod(), acIdentifier)){

         *nVar = myClass->getIdMethodVar(getClass(), getMethod(), acIdentifier);
 		      *nIdType = *nType = myClass->typeMethodVar(getClass(), getMethod(), acIdentifier);
         myClass->getArrayMethodVar(getClass(), getMethod(), acIdentifier)->copyArray(&a->var.def);
         a->var.def.type = *nIdType;

         if (myClass->isStaticMethodVar(getModule(), getSub(), acIdentifier)){
           *scope = global; 
         } else {
           *scope = local; 
         }
         *nLStringLen = myClass->getLStringLenMethodVar(getClass(), getMethod(), acIdentifier);
         
         acIdentifier2 = acIdentifier;
         goto selector; 
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
                
               *nVar = nParamId;  
		           *nIdType = *nType = n;
               array->copyArray(&a->var.def);
               a->var.def.type = *nIdType;
               *scope = param; 
               *nLStringLen = nParamLStringLen;  
               *bReference = nParameterCall != token__BY_VAL;

               acIdentifier2 = acIdentifier;
               goto selector; 
					    }
    		    } while(myClass->nextParameterMethod	(nClassId, nId, &acName, &acType, &nParameterCall, &bOptional, &bDefault, &bParamArray, &array, &defval, &nParamId, &nParamLStringLen));
    	    }
       }   
      }
    }

    // ************************************************************************************************
    // global handling 2
    // ************************************************************************************************

    // global class instance var
    if (!bArgumentOnly && isScopeClassLocalInstance()){
      const char *acClass = getClass();

      if (existVar(acClass, acIdentifier, 
                  nVar, nIdType, nType, 
                  &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
      {        
        acIdentifier2 = acIdentifier;
        goto selector; 
      }
    }

    // global class static var
    if (!bArgumentOnly && (isScopeClassLocalInstance() || isScopeClassLocalStatic() || isScopeClassStaticCode())){
      const char *acClass = getClass();

      if (existStaticVar(acClass, acIdentifier, 
                  nVar, nIdType, nType, 
                  &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
      {        
        acIdentifier2 = acIdentifier;
        goto selector; 
      }
    }

    // global class property var
    if (!bAssignment && isScopeClassLocalInstance()){
      const char *acClass = getClass();
      
      if (existPropertyGet(acClass, acIdentifier, 
                      nVar, nIdType, nType, 
                      &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
      {        
       *bProperty = true;
       _END3_
       *nIdType = -100; // workaorund nIdType == -100 || 

	      if (bProducePcode) p->wr_PUSH_ME(pcode__PUSH_ME);

        goto selector2; 
      }
    }
     
    // global class property var
    if (bAssignment && isScopeClassLocalInstance()){
      const char *acClass = getClass();

      if (existPropertySet(acClass, acIdentifier, 
                      nVar, nIdType, nType, 
                      &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
      {        
       *bProperty = true;
       _END3_
       *nIdType = -100; // workaorund nIdType == -100 || 

       if (bProducePcode) p->wr_PUSH_ME(pcode__PUSH_ME);
               
       goto selector2; 
      }
    }

    // global class property var
    if (!bAssignment && isScopeClassLocalInstance()){
      const char *acClass = getParentClass();
      
      if (existPropertyGet(acClass, acIdentifier, 
                      nVar, nIdType, nType, 
                      &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
      {        
       *bProperty = true;
       _END3_
       *nIdType = -100; // workaorund nIdType == -100 || 

	      if (bProducePcode) p->wr_PUSH_PARENT(pcode__PUSH_PARENT);        

        if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acClass)));

        goto selector2; 
      }
    }
     
    // global class property var
    if (bAssignment && isScopeClassLocalInstance()){
      const char *acClass = getParentClass();

      if (existPropertySet(acClass, acIdentifier, 
                      nVar, nIdType, nType, 
                      &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
      {        
       *bProperty = true;
       _END3_
       *nIdType = -100; // workaorund nIdType == -100 || 

       if (bProducePcode) p->wr_PUSH_PARENT(pcode__PUSH_PARENT);               
       
       if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acClass)));
               
       goto selector2; 
      }
    }

    // global class static block of class --> vars
    if (!bArgumentOnly && isScopeClassStaticCode()){
      const char *acClass = getClass();

      if (myClass->existStaticCodeVar	(acClass, acIdentifier)){

        *nVar = myClass->getIdStaticCodeVar(acClass, acIdentifier);
   	    *nIdType = *nType = myClass->typeStaticCodeVar(acClass, acIdentifier);
        myClass->getArrayStaticCodeVar(acClass, acIdentifier)->copyArray(&a->var.def);
        a->var.def.type = *nIdType;
        *scope = global; 

        acIdentifier2 = acIdentifier;
        goto selector; 
      }
    }

    {

#ifdef KBDEBUG
  if (stopAtLine(311)){
    int i = 3;
    i++;
  }
#endif


      // global module var
      if (!bArgumentOnly){
        const char *acModule = getModule();

        if (myModule->existVar	(acModule, acIdentifier)){

          *nVar = myModule->getIdVar(acModule, acIdentifier);
          if (*nVar >= MAX_SKALAR_GLOBALVAR_ID){
            if (my_cache) addDependencyGlobalVar(p->sCurrentFile.ascii(), *nVar);
          }
		      *nIdType = *nType = myModule->typeVar(acModule, acIdentifier);
          t_array *aa = myModule->getArrayVar(acModule, acIdentifier);
          if (aa) aa->copyArray(&a->var.def);
          a->var.def.type = *nIdType;
          *scope = global; 
          *nLStringLen = myModule->getLStringLenVar(acModule, acIdentifier);

          nAccessScopeId = myModule->getId(acModule); 
          nAccessScope = myModule->scopeVar(acModule, acIdentifier);

          acIdentifier2 = acIdentifier;
          goto selector; 
        }


//#ifdef KBDEBUG
  if (stopAtLine(11)){
    int i = 3;
    i++;
  }
//#endif

        // global module var in der liste mit allen modules
	      if (myModule->first()){
		      do {

			      int nId = myModule->getId();

           acModule = myModule->getName(nId);


           if (myModule->existVar	(acModule, acIdentifier)){
             if (!(myModule->scopeVar	(acModule, acIdentifier) == token__PUBLIC || utility::my_stricmp(getScope(), acModule) == 0)){
               *scope = outofscope;
             } else {

               *nVar = myModule->getIdVar(acModule, acIdentifier);
		           *nIdType = *nType = myModule->typeVar(acModule, acIdentifier);
               t_array *aa = myModule->getArrayVar(acModule, acIdentifier);
               if (aa) aa->copyArray(&a->var.def);
               a->var.def.type = *nIdType;
               *scope = global; 
               nAccessScopeId = myModule->getId(acModule); 
               nAccessScope = myModule->scopeVar(acModule, acIdentifier);
               *nLStringLen = myModule->getLStringLenVar(acModule, acIdentifier);

               acIdentifier2 = acIdentifier;

               if (my_cache) addDependency(p->sCurrentFile.ascii(), myModule->getFile(myModule->getId(acModule)));

               goto selector;
             }
           }

		      } while (myModule->next());
        }

      }
    }
    bIDENTIFIER2 = false;

    // maybe: identifier = classname/modulename . identifier2
    if ((bTerm_DOT = parseTerm(token__SYM_DOT))){

		      if (bIDENTIFIER2 = fID_KEYWORD_OR_BUILTIN(&acIdentifier2)){ nImplicitType = defaultType(acIdentifier2); }
	    // because the identifier has a suffix $,%,&,#,!, AS <TYPE> is not allowed, already found out
	    else if (bIDENTIFIER2 = fID_STRING(&acIdentifier2)){ nImplicitType = pcode__QSTRING; }
	    else if (bIDENTIFIER2 = fID_INTEGER(&acIdentifier2)){ nImplicitType = pcode__INTEGER; }
	    else if (bIDENTIFIER2 = fID_LONG(&acIdentifier2)){ nImplicitType = pcode__LONG; }
	    else if (bIDENTIFIER2 = fID_SINGLE(&acIdentifier2)){ nImplicitType = pcode__SINGLE; }
	    else if (bIDENTIFIER2 = fID_DOUBLE(&acIdentifier2)){ nImplicitType = pcode__DOUBLE; }
	    else if (bIDENTIFIER2 = fID_CURRENCY(&acIdentifier2)){ nImplicitType = pcode__CURRENCY; }

    }

    if(bIDENTIFIER2){

      // modulename -> global module var
      if (!bArgumentOnly && myModule->exist(acIdentifier)){

        int nModuleId = myModule->getId(acIdentifier);

        if (myModule->existVar	(nModuleId, acIdentifier2)){

          *nVar = myModule->getIdVar(nModuleId, acIdentifier2);
		      *nIdType = *nType = myModule->typeVar(acIdentifier, acIdentifier2);
          t_array *aa = myModule->getArrayVar(acIdentifier, acIdentifier2);
          if (aa) aa->copyArray(&a->var.def);
          a->var.def.type = *nIdType;
          *scope = global; 
          nAccessScopeId = nModuleId; 
          nAccessScope = myModule->scopeVar(acIdentifier, acIdentifier2);
          *nLStringLen = myModule->getLStringLenVar(acIdentifier, acIdentifier2);

          if (my_cache) addDependency(p->sCurrentFile.ascii(), myModule->getFile(myModule->getId(acIdentifier)));

          goto selector; 
        }

      }

      // classname -> global static class var
      if (!bArgumentOnly && myClass->exist(acIdentifier)){

        if (existStaticVar(acIdentifier, acIdentifier2, 
                         nVar, nIdType, nType, 
                         &a->var.def, scope, &nAccessScopeId, &nAccessScope, nLStringLen))
        {         
          if (my_cache) addDependency(p->sCurrentFile.ascii(), myClass->getFile(myClass->getId(acIdentifier)));

          goto selector; 
        }
      }

    }

    // ************************************************************************************************
    // special handling
    // ************************************************************************************************


    // var not declared, implicit declaration
		if (*scope != outofscope && !bArgumentOnly && bTestImplicitDim){

  		if (bExplicit || isKBASIC()){
        _END_fVARIABLE_
  		} else { // vars do not need to be declared

        // *** test if it is a constant
        if(isScopeModule()){
         	int nModuleId = myModule->getId(getModule());

          if (isScopeLocal()){
            if (myModule->existSubConst(nModuleId, getSub(), acIdentifier)){
              _END_fVARIABLE_
            }  
          } else {
            if (myModule->existConst(nModuleId, acIdentifier)){
              _END_fVARIABLE_
            }  
          }
        } else {
         	int nClassId = myClass->getId(getClass());

          if (isScopeLocal()){
            if (myClass->existMethodConst(nClassId, getMethod(), acIdentifier)){
              _END_fVARIABLE_
            }  
          } else {
            if (myClass->existConst(nClassId, acIdentifier)){
              _END_fVARIABLE_
            }  
          }
        }
        // ***

        // only variant has an array implicitly declared
       if (nImplicitType == pcode__VARIANT){
         a->var.def.count = 1;
  		    for (int i = 0; i < a->var.def.count; i++) a->var.def.idx[i] = parser__ARRAY_DEFAULT; // set size of all dimensions to default
       } else {
         a->var.def.count = 0;
       }

				bool bStatic = isScopeClassLocalStatic() || isScopeModuleLocalStatic();
        *nIdType = *nType = nImplicitType;

        // nLastVarId+nLastVarScope needed for rollback in fINPUT ->  undeclare variable 
  			nLastVarId = *nVar = registerVar(acIdentifier, *nType, &a->var.def, false, bStatic, token__PUBLIC, *nLStringLen);
        if (isScopeLocal()){
          *scope = local;
          if (isScopeClassLocalInstance()){
            nLastVarScope = token__CLASS;
            nLastModuleId = myClass->getId(getClass());
            nLastSubId = myClass->getIdMethod(nLastModuleId, getMethod());
          } else {
            goto w;
          }
        } else {
          *scope = global;
w:
          nLastVarScope = token__MODULE;
          nLastModuleId = myModule->getId(getModule());
          nLastSubId = myModule->getIdSub(nLastModuleId, getSub()); 
        }

				*bImplicitDIM = true;

        acIdentifier2 = acIdentifier;
        goto selector;

  		}
		}
  }

_END_fVARIABLE_

    // ************************************************************************************************
    // selector
    // ************************************************************************************************

selector:
	bSELECTOR_TYPE = false;
	bSELECTOR_CLASS_VAR = false;
	//bool bSELECTOR_CLASS_PROPERTY = false;
	bARRAY2 = false;
 
#ifdef KBDEBUG
  if (stopAtLine(16)){
    int i = 9;
    i++;
  }
#endif
  
  if (bRedim){

    t_array a;
		 if (!fREGISTER_ARRAY(p, &a, 0, 0)){ syntaxError(token__REDIM, "missing array expression"); _ERROR_ }

  } else {
    
    if (bARRAY2 = fARRAY(p, &a->var.use, *nType, *nVar, 0, bAssignment, false, true, *scope)){} // could be skalar with array


    if (bSELECTOR_CLASS_VAR = fSELECTOR_CLASS_VAR(p, nVar, nIdType, nType, a, scope, &acIdentifier2, &bARRAY2, bAssignment, &nAccessScopeId, &nAccessScope, nLStringLen)){}

    if (bSELECTOR_TYPE = fSELECTOR_TYPE(    
                          p, *nVar, *nIdType, *nType, acIdentifier2, 
                          nIdType, nType, a, bAssignment, bSizeAll, 
                          nLStringLen, bSELECTOR_CLASS_VAR, *scope, bARRAY2, bTestProperty)){} // user type with arrays or not

    if (*bSizeAll && (bARRAY2 || a->var.use.count != 0)){
      *bSizeAll = false;

      *nLStringLen = myMemory_type->getSize(*nIdType);

    }

    int nReturnExpressionType = *nType;


  }
selector2:
  // testen, ob access scope passt
  if (nAccessScopeId > 0){
    if (memory_type::isClass(nAccessScopeId)){
      if (nAccessScope == token__PUBLIC){
      } else if (nAccessScope == token__PROTECTED){
        if (nAccessScopeId == myClass->getId(getClass())){
        } else if (!myClass->isSubClass(myClass->getId(getClass()), nAccessScopeId)){
          semanticError(token__CLASS, utility::con(acIdentifier2, " --> access denied, because variable is declared as PROTECTED."));
        }
      } else if (nAccessScope == token__PRIVATE){
        if (nAccessScopeId == myClass->getId(getClass())){
        } else {
           semanticError(token__CLASS, utility::con(acIdentifier2, " --> access denied, because variable is declared as PRIVATE."));
        }
      }
    } else {
      if (nAccessScope == token__PUBLIC){
      } else if (nAccessScope == token__PRIVATE){
        if (nAccessScopeId == myModule->getId(getModule())){
        } else {
           semanticError(token__MODULE, utility::con(acIdentifier2, " --> access denied, because variable is declared as PRIVATE."));
        }
      }
    }
  }

  if (memory_type::isEnum(*nType)){
    *nType = pcode__INTEGER;
  }
  
  // * optimize
  __bDone = true;

  _nCurrentToken = getTokenPos();    
  _nCurrentPcode = p->getPos();
  _currentWith = with;

  _nVar = *nVar;
  _scope = *scope;
  _nIdType = *nIdType;
  _nType = *nType;
  _bImplicitDIM = *bImplicitDIM;
  _a = *a;
  _bSizeAll = *bSizeAll;
  _nLStringLen = *nLStringLen;
  _bReference = *bReference;
  _bProperty = *bProperty;
  _bProperty = *bProperty;
  // *


 _DONE_
 
}

bool parser::fVARIABLE_ASSIGNMENT(pcode *p, int *nVar, t_scope *scope, 
                                  int *nIdType, int *nType, bool *bImplicitDIM, 
                                  bool bTestImplicitDim, t_arrayVariable *a, 
                                  bool *bSizeAll, int *nLStringLen, bool *bReference, bool *bProperty, bool bTestProperty                 
                                  )
{
  bool bClassVar = false;
  bool bPropertyVar = false;
  int nClassId = 0;
  bool bArgumentOnly = false;
  bool bAssignment = true;  

  return fVARIABLE(p, 
    nVar, scope, nIdType, nType, bImplicitDIM, bTestImplicitDim, 
    a, bSizeAll, nLStringLen, bReference, bProperty, bTestProperty,
    bClassVar, nClassId, bArgumentOnly, bAssignment);

}

bool parser::fVARIABLE(pcode *p, int *nVar, t_scope *scope, int *nType)
{
  int nIdType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = true;  
  t_arrayVariable a;
  int nReturnExpressionType = 0;
  bool bSizeAll = false;
  bool bReference = false;  
  int nLStringLen = 0;
  bool bAssignment = false;  
  bool bProperty = false;    
  bool bTestProperty = true;  

  if (fVARIABLE(p, nVar, scope, &nIdType, nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty)){
     return fVARIABLE_DIM(p, p, *nVar, *scope, nIdType, *nType, bImplicitDIM, false, &nReturnExpressionType, bReference, bAssignment);
  }
  return false;
}

bool parser::fVARIABLE_REDIM(pcode *p, int *nVar, t_scope *scope)
{
  int nIdType = 0;
  int nType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = true;  
  t_arrayVariable a;
  int nReturnExpressionType = 0;
  bool bSizeAll = false;
  bool bReference = false;  
  int nLStringLen = 0;
  bool bAssignment = false;  
  bool bProperty = false;    
  bool bTestProperty = false;  
  bool bRedim = true;    
  bool bClassVar = false;  
  int nClassId = 0;  
  bool bArgumentOnly = false;    

  return fVARIABLE(p, nVar, scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty, bClassVar, nClassId, bArgumentOnly, bAssignment, bRedim);
}

bool parser::fVARIABLE_DECLARED(pcode *p, int *nVar, t_scope *scope, int *nType)
{
  int nIdType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = false;  
  t_arrayVariable a;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bProperty = false;    
  bool bTestProperty = false;  

  return fVARIABLE(p, nVar, scope, &nIdType, nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty);
}

bool parser::fARGUMENT(pcode *p, int *nVar, t_scope *scope, int *nType)
{
  int nIdType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = true;  
  t_arrayVariable a;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bProperty = false;    
  bool bTestProperty = false;  

  return fVARIABLE(p, nVar, scope, &nIdType, nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty, false, 0, true);
}

bool parser::binding_fVARIABLE_OR_CLASSNAME(pcode *p, int *nType)
{

  int nVar = 0; 
  t_scope scope = global;
  int nIdType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = false;  
  t_arrayVariable a;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bProperty = false;    
  bool bTestProperty = false;  

  bool b = fVARIABLE(p, &nVar, &scope, &nIdType, nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty);

  if (b) return b;


  char *acIdentifier = "";

	if (fID_KEYWORD_OR_BUILTIN( ((const char **) &acIdentifier), false)){

	 *nType = (int) binding_map_class.getString(acIdentifier);

		if (*nType > 0){
  		return true;
    
    
    } else if (strcmp(acIdentifier, "PAINT") == 0){
  	  *nType = (int) binding_map_class.getString("Paint");
      return true;
    } else if (strcmp(acIdentifier, "LOG") == 0){
  	  *nType = (int) binding_map_class.getString("Log");
      return true;
    } else if (strcmp(acIdentifier, "DIR") == 0){
  	  *nType = (int) binding_map_class.getString("Dir");
      return true;
    } else if (strcmp(acIdentifier, "COLOR") == 0){
  	  *nType = (int) binding_map_class.getString("Color");
      return true;
    } else if (strcmp(acIdentifier, "FILE") == 0){
  	  *nType = (int) binding_map_class.getString("File");
      return true;
    } else if (strcmp(acIdentifier, "LINE") == 0){
  	  *nType = (int) binding_map_class.getString("Line");
      return true;
    }

  }
  return false;

}

bool parser::fVARIABLE_OR_CLASSNAME(pcode *p, int *nType)
{

  int nVar = 0; 
  t_scope scope = global;
  int nIdType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = false;  
  t_arrayVariable a;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bProperty = false;    
  bool bTestProperty = false;  

  bool b = fVARIABLE(p, &nVar, &scope, &nIdType, nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty);

  if (b) return b;


  const char *acIdentifier = "";

	if (fID_KEYWORD_OR_BUILTIN(&acIdentifier, false)){

	 *nType = findType(acIdentifier);

		if (*nType > 0){
  		return true;
	  }
  }
  return false;

}

bool parser::fVARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, 
                       t_arrayVariable *a, bool *bReference, bool *bProperty, bool bTestProperty)
{
  bool bImplicitDIM = false;
  bool bTestImplicitDim = true;
  int nReturnExpressionType = 0;
  bool bSizeAll = false;
  int nLStringLen = 0;  
  bool bAssignment = false;  

  if (fVARIABLE(p, nVar, scope, nIdType, nType, &bImplicitDIM, bTestImplicitDim, a, &bSizeAll, &nLStringLen, bReference, bProperty, bTestProperty)){
     return fVARIABLE_DIM(p, p, *nVar, *scope, *nIdType, *nType, bImplicitDIM, false, &nReturnExpressionType, bReference, bAssignment);
  }
  
  return false;
}

bool parser::fVARIABLE(pcode *p, int *nVar, t_scope *scope, int *nIdType, int *nType, 
                       t_arrayVariable *a)
{
  bool bImplicitDIM = false;
  bool bTestImplicitDim = true;
  int nReturnExpressionType = 0;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bAssignment = false;  
  bool bProperty = false;  
  bool bTestProperty = false;  

  if (fVARIABLE(p, nVar, scope, nIdType, nType, &bImplicitDIM, bTestImplicitDim, a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty)){
     return fVARIABLE_DIM(p, p, *nVar, *scope, *nIdType, *nType, bImplicitDIM, false, &nReturnExpressionType, bReference, bAssignment);
  }
  
  return false;
}

bool parser::fVARIABLE(pcode *pp, pcode *p, int *nReturnExpressionType)
{
  t_scope scope = global;
  return fVARIABLE(pp, p, nReturnExpressionType, &scope);
}

bool parser::fVARIABLE(pcode *pp, pcode *p, int *nReturnExpressionType, t_scope *scope)
{
  _BEGIN_

	 int nVar = 0;
	 bool bImplicitDIM = false;
	 bool bTestImplicitDim = false;   
	 int nIdType = 0;
	 int nType = 0;
	 t_arrayVariable a;   
   bool bSizeAll = false;
   int nLStringLen = 0;
   bool bReference = false;  
   bool bAssignment = false; 
   bool bProperty = false;  
  bool bTestProperty = false;  

	 if (fVARIABLE(pp, &nVar, scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty)){
     return fVARIABLE_DIM(pp, p, nVar, *scope, nIdType, nType, bImplicitDIM, true, nReturnExpressionType, bReference, bAssignment);
	 }

  _END_
}

bool parser::fVARIABLE(pcode *pp, pcode *p, int *nReturnExpressionType, 
                       t_scope *scope, t_arrayVariable *a)
{
  _BEGIN_

	 int nVar = 0;
	 bool bImplicitDIM = false;
	 bool bTestImplicitDim = true;   
	 int nIdType = 0;
	 int nType = 0;
   bool bSizeAll = false;
   int nLStringLen = 0;
   bool bReference = false;  
   bool bAssignment = false;  
   bool bProperty = false;  
   bool bTestProperty = false;  

#ifdef KBDEBUG
   if (stopAtLine(4)){
     int i = 9;
     i++;
   }
#endif

	 if (fVARIABLE(pp, &nVar, scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty)){
     if (nType != pcode__POINTER){
       return fVARIABLE_DIM(pp, p, nVar, *scope, nIdType, nType, bImplicitDIM, true, nReturnExpressionType, bReference, bAssignment);
     } else { // needed for collections
       *nReturnExpressionType = nIdType; 
       return true;
     }
	 }

  _END_
}

bool parser::fVARIABLE_DIM(pcode *pp, pcode *p, int nVar, t_scope scope, 
                           int nIdType, int nType, bool bImplicitDIM, bool bReturn, 
                           int *nReturnExpressionType, bool bReference, bool bAssignment)
{

	if (nType == token__ME){
  	*nReturnExpressionType = myClass->getId(getClass());
		if (bProducePcode) pp->wr_PUSH_ME(pcode__PUSH_ME);

	} else if (nType == token__PARENT){
  	*nReturnExpressionType = myClass->getId(getParentClass());
		if (bProducePcode) pp->wr_PUSH_PARENT(pcode__PUSH_PARENT);        

	} else {

		*nReturnExpressionType = nType;

		if (bImplicitDIM){
      bool bArray = false;

      if (bProducePcode){
        p->wr_DIM(pcode__DIM, nVar, scope, nType, false, false, bArray, isSubVarStatic(), 0, 0, "", false); // write pcode
        
        // * needed for rollback
        pDim->resetPos(); 
        pDim->wr_DIM(pcode__DIM, nVar, scope, nType, false, false, bArray, isSubVarStatic(), 0, 0, "", false); // write pcode
        // *
      }
		}

    if (bReturn){

  	 if (bProducePcode){
       if (bReference){
    			pp->wr_PUSH_IDREFVAL(pcode__PUSH_IDREFVAL, nVar, scope, nType);
       } else {
    		  if (!myMemory_type->scalar(nIdType)){
					  switch (nType){
          	  case pcode__BOOLEAN: pp->wr_PUSH_BOOLEAN_ID(pcode__PUSH_BOOLEAN_ID, nVar, scope); break;

             case pcode__QSTRING: pp->wr_PUSH_QSTRING_ID(pcode__PUSH_QSTRING_ID, nVar, scope); break;
             case pcode__LQSTRING: pp->wr_PUSH_LQSTRING_ID(pcode__PUSH_LQSTRING_ID, nVar, scope); break;
             case pcode__CSTRING: pp->wr_PUSH_CSTRING_ID(pcode__PUSH_CSTRING_ID, nVar, scope); break;
             case pcode__LCSTRING: pp->wr_PUSH_LCSTRING_ID(pcode__PUSH_LCSTRING_ID, nVar, scope); break;

  		      case pcode__BYTE: pp->wr_PUSH_BYTE_ID(pcode__PUSH_BYTE_ID, nVar, scope); break;
  		      case pcode__SHORT: pp->wr_PUSH_SHORT_ID(pcode__PUSH_SHORT_ID, nVar, scope); break;
          	  case pcode__INTEGER: pp->wr_PUSH_INTEGER_ID(pcode__PUSH_INTEGER_ID, nVar, scope); break;
          	  case pcode__LONG: pp->wr_PUSH_LONG_ID(pcode__PUSH_LONG_ID, nVar, scope); break;

             case pcode__SINGLE: pp->wr_PUSH_SINGLE_ID(pcode__PUSH_SINGLE_ID, nVar, scope); break;
             case pcode__DOUBLE: pp->wr_PUSH_DOUBLE_ID(pcode__PUSH_DOUBLE_ID, nVar, scope); break;

		         case pcode__VARIANT: pp->wr_PUSH_VARIANT_ID(pcode__PUSH_VARIANT_ID, nVar, scope); break;

		         case pcode__CURRENCY: pp->wr_PUSH_CURRENCY_ID(pcode__PUSH_CURRENCY_ID, nVar, scope); break;

		         case pcode__DATE: pp->wr_PUSH_DATE_ID(pcode__PUSH_DATE_ID, nVar, scope); break;

						  default: 

              pp->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, bAssignment);
               break; // the whole structure
        	  }

    		  } else {
   				      pp->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, bAssignment);
       	  }
       }
			 
  	  }
    }
   return true;
  	
	}
 return false;
}

bool parser::existStaticVar(const char *acClass, const char *acIdentifier, 
                           int *nVar, int *nIdType, int *nType, t_array *a,
                           t_scope *scope, int *nAccessScopeId, int *nAccessScope, int *nLStringLen)
{
re:
  if (myClass->existStaticVar	(acClass, acIdentifier)){

    *nVar = myClass->getIdStaticVar(acClass, acIdentifier);
    *nIdType = *nType = myClass->typeStaticVar(acClass, acIdentifier);
    myClass->getArrayStaticVar(acClass, acIdentifier)->copyArray(a);
    a->type = *nIdType;
    *scope = global; 
    *nAccessScopeId = myClass->getId(acClass);
    *nAccessScope = myClass->scopeStaticVar(*nAccessScopeId, *nVar);
    *nLStringLen = myClass->getLStringLenStaticVar(acClass, acIdentifier);

    return true;
  }

  // walk through hierarchy, find in parent class
  int n = myClass->getParentId(acClass);
  if (n > 0){
    acClass = myClass->getName(n);
    if (acClass == 0) return false;
    goto re;
  }

  return false;
}

bool parser::existVar(const char *acClass, const char *acIdentifier, 
                           int *nVar, int *nIdType, int *nType, t_array *a,
                           t_scope *scope, int *nAccessScopeId, int *nAccessScope, int *nLStringLen)
{
re:
  if (myClass->existVar	(acClass, acIdentifier)){

    *nVar = myClass->getIdVar(acClass, acIdentifier);
    *nIdType = *nType = myClass->typeVar(acClass, acIdentifier);
    t_array *aa = myClass->getArrayVar(acClass, acIdentifier);
    if (aa) aa->copyArray(a);
    a->type = *nIdType;
    *scope = me; 
    *nAccessScopeId = myClass->getId(acClass);
    *nAccessScope = myClass->scopeVar(*nAccessScopeId, *nVar);
    *nLStringLen = myClass->getLStringLenVar(acClass, acIdentifier);

    return true;
  }

  // walk through hierarchy, find in parent class
  int n = myClass->getParentId(acClass);
  if (n > 0){
    acClass = myClass->getName(n);
    if (acClass == 0) return false;
    goto re;
  }

  return false;
}

bool parser::existPropertyGet(const char *acClass, const char *acIdentifier, 
                           int *nVar, int *nIdType, int *nType, t_array *a,
                           t_scope *scope, int *nAccessScopeId, int *nAccessScope, int *nLStringLen)
{
  int nClassId = myClass->getId(acClass);

  if (myClass->existPropertyGet	(nClassId, acIdentifier)){

    *nVar = nClassId;
		*nIdType = *nType = nClassId;
    t_array *aa = myClass->getArrayVar(acClass, acIdentifier);
    if (aa) aa->copyArray(a);
    a->type = *nIdType;
    *scope = me; 
    *nAccessScopeId = myClass->getId(acIdentifier); 
    *nAccessScope = myClass->getScopePropertyGet(nClassId, *nType);
    *nLStringLen = myClass->getLStringLenVar(acClass, acIdentifier);

    return true;
  }

  return false;
}

bool parser::existPropertySet(const char *acClass, const char *acIdentifier, 
                           int *nVar, int *nIdType, int *nType, t_array *a,
                           t_scope *scope, int *nAccessScopeId, int *nAccessScope, int *nLStringLen)
{
  int nClassId = myClass->getId(acClass);

  if (myClass->existPropertySet	(nClassId, acIdentifier)){

    *nVar = nClassId;
		*nIdType = *nType = nClassId;
    t_array *aa = myClass->getArrayVar(acClass, acIdentifier);
    if (aa) aa->copyArray(a);
    a->type = *nIdType;
    *scope = me; 
    *nAccessScopeId = myClass->getId(acIdentifier); 
    *nAccessScope = myClass->getScopePropertySet(nClassId, *nType);
    *nLStringLen = myClass->getLStringLenVar(acClass, acIdentifier);

    return true;
  }

  return false;
}

void parser::prepareRollbackVariable()
{
  nLastVarId = 0; 
}

bool parser::rollbackVariable()
{
  // needed for rollback in fINPUT  -> undeclare variable 
  if (nLastVarId > 0){

    if (nLastVarScope == token__CLASS){
      myClass->removeMethodVar(nLastModuleId, nLastSubId, nLastVarId);          
    } else if (nLastVarScope == token__MODULE){
      if (nLastSubId > 0){
        myModule->removeSubVar(nLastModuleId, nLastSubId, nLastVarId);          
      } else {
        myModule->removeVar(nLastModuleId, nLastVarId);          
      }
      
      nLastVarId = 0;
      return true;
    }        
  }
  return false;
}