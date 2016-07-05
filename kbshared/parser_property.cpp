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




bool parser::fPROPERTY_ASSIGNMENT(pcode *p, int *nClassId, int *nId, bool *binding_fPROPERTY_ASSIGNMENT)
{
  _BEGIN_


  if (with_pos_list_POS == -1){
    // *** look forward if = is present in line
    bool bRet = true;
    int nTest = 0;

	  do {

		  nTest = peekToken();

		  if (nTest == token__MSC_EOL){
        _END_;      
      } else if (nTest == token__OP_EQUAL){ //  dangerous nur auf eol prfen? rem : 
			  break;
		  }

	  } while(proceedParse() && bRet && (bRet = nextToken()));

    _END2_
    // ***
  }

	int nVar = 0;
	t_scope scope = global;
	int nType = 0;

  int nIdType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = false;  
  t_arrayVariable a;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bProperty = false;    
  bool bTestProperty = false;  
  bool bClassVar = false;   
  bool bArgumentOnly = false; 
  bool bAssignment = true; 

#ifdef KBDEBUG
  if (stopAtLine(37)){
    int i = 9;
    i++;
  }
#endif


  bool bTerm_ME = false;
  bool bTerm_PARENT = false;
  bool bTerm_MEimplictly = false;  

	if ((bTerm_ME = parseTerm(token__ME))){
  } else if ((bTerm_PARENT = parseTerm(token__PARENT))){
  }
re:	
	if (bTerm_ME){
    nType = findType(getClass());
    if (bProducePcode) p->wr_PUSH_ME(pcode__PUSH_ME);
  } else if (bTerm_PARENT){
    const char *ac = getParentClass();
    if (ac == 0) _END_
    nType = findType(ac);
    if (memory_type::isBinding(nType)){
      _END_
    } else {
       if (bProducePcode) p->wr_PUSH_PARENT(pcode__PUSH_PARENT);
    }
  }
	if ((bTerm_ME || bTerm_PARENT) || fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty, bClassVar, *nClassId, bArgumentOnly, bAssignment)){

    bool bTerm_SYM_DOT = false;

    // workaorund nIdType == -100 || 
    if (nIdType == -100 || bTerm_MEimplictly || (bTerm_SYM_DOT = parseTerm(token__SYM_DOT))){

      bool bPROPERTY = false;
      const char *acProperty = "";

      if (memory_type::isClass(nType) && (bPROPERTY = fID_KEYWORD_OR_BUILTIN(&acProperty))){

        if (!bSilent && bProducePcode){
         p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fPROPERTY_ASSIGNMENT", getCurrentLine() - 1));
        }

        if (nIdType != -200){ // workaorund nIdType == -200
       
          if (!bTerm_ME && !bTerm_PARENT && bProducePcode){
            if (memory_type::isClass(nVar)){
              p->wr_PUSH_ME(pcode__PUSH_ME);
            } else {
              p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
            }
          }
         
        }
        
        int nReturnId = 0;
        int nReturnType = 0;
        if (fSELECTOR_CLASS_PROPERTY(p, nType, acProperty, true, binding_fPROPERTY_ASSIGNMENT, &nReturnId, &nReturnType)){ 
          if (*binding_fPROPERTY_ASSIGNMENT){ _END_ } // force use of Me like Me.BINDINGPROPERTY=

          if (nReturnType){
            *nClassId = nReturnId;
            *nId = nReturnType;
          } else {
            *nClassId = nType;
            *nId = myClass->getIdPropertyGet(*nClassId, acProperty);
          
            int nAccessScopeId = nType; 
            int nAccessScope = myClass->getScopePropertySet(*nClassId, *nId);

            // testen, ob access scope passt
            if (nAccessScopeId > 0){
            if (memory_type::isClass(nAccessScopeId)){
              if (nAccessScope == token__PUBLIC){
              } else if (nAccessScope == token__PRIVATE){
                  if (nAccessScopeId == myClass->getId(getClass())){
                  } else {
                      semanticError(token__CLASS, utility::con(acProperty, " --> access denied, because variable is declared as PRIVATE."));
                  }
              }
            }
            }
          }

          _DONE_
          
        }
        

      }
     	 
	  }  

  } else if (bTerm_ME == false){
    // try implictly Me
    bTerm_ME = true;    
    bTerm_MEimplictly = true;
    goto re;
  }
    
  _END_
}
  
bool parser::fPROPERTY(pcode *p, int *nReturnExpressionType)
{
  _BEGIN_

	int nVar;// = 0;
	t_scope scope;// = global;
	int nType;// = 0;

#ifdef KBDEBUG
  if (stopAtLine(36)){
    int i = 9;
    i++;
  }
#endif

  int nClassId = 0;
  int nIdType = 0;
  bool bImplicitDIM = false;
  bool bTestImplicitDim = false;  
  t_arrayVariable a;
  bool bSizeAll = false;
  int nLStringLen = 0;
  bool bReference = false;  
  bool bProperty = false;    
  bool bTestProperty = false;  
  bool bClassVar = false;   
  bool bArgumentOnly = false; 
  bool bAssignment = false; 

  bool bTerm_ME = false;
  bool bTerm_PARENT = false;

  bool bTerm_MEimplictly = false;
  

	if ((bTerm_ME = parseTerm(token__ME))){
  }	else if ((bTerm_PARENT = parseTerm(token__PARENT))){
  }
re:

	if (bTerm_ME){
    nType = findType(getClass());
    if (bProducePcode) p->wr_PUSH_ME(pcode__PUSH_ME);
  }
	else if (bTerm_PARENT){
    const char *ac = getParentClass();
    if (ac == 0) _END_
    nType = findType(ac);
    if (memory_type::isBinding(nType)){
      _END_
    } else {
       if (bProducePcode) p->wr_PUSH_PARENT(pcode__PUSH_PARENT);
    }
  }
	if ((bTerm_ME || bTerm_PARENT) || fVARIABLE(p, &nVar, &scope, &nIdType, &nType, &bImplicitDIM, bTestImplicitDim, &a, &bSizeAll, &nLStringLen, &bReference, &bProperty, bTestProperty, bClassVar, nClassId, bArgumentOnly, bAssignment)){

    bool bTerm_SYM_DOT = false;

    // workaorund nIdType == -100 || 
	  if (nIdType == -100 || bTerm_MEimplictly || (bTerm_SYM_DOT = parseTerm(token__SYM_DOT))){

      bool bPROPERTY = false;
      const char *acProperty = "";

      if (memory_type::isClass(nType) && (bPROPERTY = fID_KEYWORD_OR_BUILTIN(&acProperty))){

        if (!bSilent && bProducePcode){
         p->wr_SEPARATOR(pcode__SEPARATOR, utility::con("fPROPERTY", getCurrentLine() - 1));
        }

        if (nIdType != -200 && nIdType != -100){ // workaorund nIdType == -200
           if (!bTerm_ME && !bTerm_PARENT && bProducePcode) p->wr_PUSH_ID(pcode__PUSH_ID, nVar, scope, false);
         
        }        
        
        bool binding_fPROPERTY_ASSIGNMENT = false;
        int nReturnId = 0;
        int nReturnType = 0;

        if (fSELECTOR_CLASS_PROPERTY(p, nType, acProperty, false, &binding_fPROPERTY_ASSIGNMENT, &nReturnId, &nReturnType)){           

          if (binding_fPROPERTY_ASSIGNMENT){

            *nReturnExpressionType = nReturnType;

          } else {

            int nId = myClass->getIdPropertyGet(nType, acProperty);

            *nReturnExpressionType = findType(myClass->typePropertyGet(nType, nId));

            int nAccessScopeId = nType; 
            int nAccessScope = myClass->getScopePropertySet(nType, nId);

            // testen, ob access scope passt
            if (nAccessScopeId > 0){
              if (memory_type::isClass(nAccessScopeId)){
                if (nAccessScope == token__PUBLIC){
                } else if (nAccessScope == token__PRIVATE){
                    if (nAccessScopeId == myClass->getId(getClass())){
                    } else {
                        semanticError(token__CLASS, utility::con(acProperty, " --> access denied, because variable is declared as PRIVATE."));
                    }
                }
              }
            }

          }

          _DONE_
        }


      }
     	 
	  }

  } else if (bTerm_ME == false){
    // try implictly Me
    bTerm_ME = true;    
    bTerm_MEimplictly = true;
    goto re;
  }

  _END_
}