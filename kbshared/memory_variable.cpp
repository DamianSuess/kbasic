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


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "utility.h"
#include "../kbshared/console.h"
#include "memory_variable.h"
#include "../kbshared/pcode.h"



int memory_variable::nIdCounter = 0;

extern int nGlobalVarId;

memory_variable::memory_variable			()
{
  nClassId = 0;
  bError = false;
	//nIdCounter = 0; darf nicht auf 0 gesetzt werden, da sonst nicht jede id einer variablen unique ist
}

memory_variable::~memory_variable			()
{
  // clear memory for string and structs/types

  if (list_variable.first(&key, &value)){
    do {

      remove((variable *) value);

    } while (list_variable.next(&key, &value));
  }

  list_variable.clear();
  list_variable2.clear();

  findMemory_variable(-99); // delete cache
}

void memory_variable::removeAllExceptObjects			()
{
  // clear memory for string and structs/types

  if (list_variable.first(&key, &value)){
    do {

      if (!(memory_type::isClass(((variable *) value)->nType) || memory_type::isBinding(((variable *) value)->nType))) remove((variable *) value);

    } while (list_variable.next(&key, &value));
  }

  list_variable.clear();
  list_variable2.clear();
}

void 		memory_variable::remove			(variable *v)
{

  delete v;

}

void memory_variable::resetIdCounter			()
{
	nIdCounter = 0;
}

int memory_variable::addIdCounter			()
{
	nIdCounter++;
  return nIdCounter;
}

void memory_variable::setIdCounter			(int i)
{
	nIdCounter = i;
}

// ****************************
// * bool memory_variableError(char *acmemory_variableError)
// *
// * description:
// * prints a variable error message
// *
// * parameter:
// * char *acmemory_variableError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_variable::memory_variableError(char *acMemory_variableError)
{
	static char acText[1024];

  if (bError) return false;

	sprintf(acText, "\ninternal error (memory variable): %s\n", acMemory_variableError);
	console::printError(acText);

  bError = true;
	return false;
}

variable *memory_variable::newMemory_variable(
                const char *acModule, 
                const char *acSub, 
                const char *acName, 
                int nId, 
                int nType, 
                t_array *a, 
                bool bByVal, 
                bool bReference, 
                bool bStatic, 
                int nScope,
                int nTypeSize
                )
{
	variable *v = new variable();


  register int n = strlen(acModule);

	memcpy(v->acModule, acModule, n);
	v->acModule[n] = '\0';

  n = strlen(acSub);

  memcpy(v->acSub, acSub, n);
	v->acSub[n] = '\0';

  n = strlen(acName);

  memcpy(v->acName, acName, n);
	v->acName[n] = '\0';

	v->nType = nType;

  v->nLStringLen = nTypeSize;

	v->bByVal = bByVal;
	v->bIsMissing = false;  
	v->nScope = nScope;
	
	v->nId = nId;
	v->bStatic = bStatic;


	if (a){
		v->a.count = a->count;
		v->a.type = nType;
		for (int i = 0; i < a->count; i++){
      v->a.idx[i] = a->idx[i];
      v->a.idxTo[i] = a->idxTo[i];
    }
  
  } else {
		v->a.count = 0;
		v->a.type = 0;
  }

  return v;
}

int 		memory_variable::declare			(
                                       const char *acModule, 
                                       const char *acSub, 
                                       const char *acName, 
                                       int nType, 
                                       t_array *a, 
                                       bool bByVal, 
                                       bool bReference, 
                                       bool bStatic, 
                                       int nScope, 
                                       int nTypeSize,
                                       int nId
                                      )
{

    if (nGlobalVarId){
      nId = nGlobalVarId;
    } else {

      if (nId > 0 && exist(nId)){
		    return 0;
      } else if (nId == 0 && exist(acModule, acSub, acName)){
		    return 0;
	    }
  
		  nIdCounter++;
		  if (nId == 0) nId = nIdCounter; else nIdCounter = nId;    
    }

		variable *c = newMemory_variable(acModule, acSub, acName, nId, nType, a, bByVal, bReference, bStatic, nScope, nTypeSize);
    if (c == 0) return 0;

    list_variable.add(nId, (int) c);
		list_variable2.addString(getKey(acModule, acSub, acName), (int) c);
  
    return nId;
	
}

int 		memory_variable::declare			(int nType, t_array *a, bool bByVal, bool bStatic, int nId)
{
 	const char *acModule = ""; const char *acSub = ""; const char *acName = "";

 	nIdCounter++;
 	if (nId == 0) nId = nIdCounter; else nIdCounter = nId;

  int nTypeSize = 0;

  variable *c = newMemory_variable(acModule, acSub, acName, nId, nType, a, bByVal, false, bStatic, false, nTypeSize);
	list_variable.add(nId, (int) c);
	list_variable2.addString(getKey(acModule, acSub, acName), (int) c);

 	return nId;

}


// used by parser and not interpreter
bool 		memory_variable::undeclare			(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
	  list_variable2.removeString(getKey(v->acModule, v->acSub, v->acName));
    list_variable.remove(nId);
    remove(v);
  	return true;
  }

 
	return false;
}

bool 		memory_variable::undeclare			(const char *acModule, const char *acSub, const char *acName)
{
	return undeclare (getId(acModule, acSub, acName));
}


char *memory_variable::getKey(const char *acModule, const char *acSub, const char *acName)
{
	static char acKey[1024];
	sprintf(acKey, "%s.%s.%s", acModule, acSub, acName);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

	return acKey;
}

bool 		memory_variable::exist				(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return true;
	}
	return false;
}

bool 		memory_variable::exist				(const char *acModule, const char *acSub, const char *acName)
{
  /*
  if (utility::my_stricmp(acModule, "myForm") == 0 && utility::my_stricmp(acName, "Label0") == 0){
    acModule = acModule;
  }*/

	return exist	(getId(acModule, acSub, acName));
}

bool 		memory_variable::findVar				(int nId, const char **acModule, const char **acSub, const char **acName)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){	
   
    *acModule = getModule(nId); 
    *acSub = getSub(nId); 
    *acName = getName(nId); 

    return true; 
  }
  return false;
}

const char     *memory_variable::getModule			(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->acModule;
	}
	return 0; 
}

const char     *memory_variable::getSub			(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->acSub;
	}
	return 0;
}

const char     *memory_variable::getName			(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->acName;
	}
	return 0;
}



t_array   *memory_variable::getArray		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return &(v->a);
	}
	return 0;
}


int   memory_variable::getLStringLen		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->nLStringLen;
	}
	return 0;
}


bool memory_variable::isArray		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    return v->a.isArray();
	}
	return false;
}

bool   memory_variable::isByVal		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->bByVal;
	}
	return true;
}

bool   memory_variable::isByRef	(int nId)
{
	return !isByVal(nId);
}

bool   memory_variable::isMissing	(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){

		return v->bIsMissing;
	}
	return true;
}

int			memory_variable::getId					()
{
	return it->nId;
}

bool   memory_variable::isStatic		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
		return v->bStatic;
	}
	return true;
}

bool   memory_variable::isPrivate		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope == token__PRIVATE;
	}
	return true;
}

bool   memory_variable::isPublic		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope == token__PUBLIC;
	}
	return true;
}

bool   memory_variable::isProtected		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope == token__PROTECTED;
	}
	return true;
}

int   memory_variable::getScope		(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope;
	}
	return true;
}

int			memory_variable::getId					(const char *acModule, const char *acSub, const char *acName)
{
  char *acKey = getKey(acModule, acSub, acName);

	if (list_variable2.contains(acKey)){
    variable *v = ((variable *)list_variable2.getString(acKey));
		return v->nId;
	}	 

	return 0;
}

int			memory_variable::type				(int nId)
{
	variable *v = findMemory_variable	(nId);
	if (v != 0){
			return v->nType;
	}
	return 0;
}

int			memory_variable::type				(const char *acModule, const char *acSub, const char *acName)
{
	return type				(getId(acModule, acSub, acName));
}




bool		memory_variable::first	()
{
	return list_variable.first(&key, (int *) &it);
}

bool		memory_variable::next	()
{
	return list_variable.next(&key, (int *) &it);
}
