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
#include "memory_const.h"
#include "../kbshared/pcode.h"



int memory_const::nIdCounter = 0;


memory_const::memory_const			()
{	

}

memory_const::~memory_const			()
{

  if (list_constant.first(&key, &value)){
    do {

      constant *m = (constant *) value;
      delete m;

    } while (list_constant.next(&key, &value));
  }

  list_constant.clear();
  list_constant2.clear();

  findMemory_const(-99); // delete cache
}

void memory_const::resetIdCounter			()
{
	nIdCounter = 0;
}

// ****************************
// * bool memory_constantError(char *acmemory_constantError)
// *
// * description:
// * prints a constant error message
// *
// * parameter:
// * char *acmemory_constantError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_const::memory_constError(char *acMemory_constError)
{
	static char acText[1024];

	sprintf(acText, "\nmemory const error: %s\n", acMemory_constError);
	console::printError(acText);
	return false;
}

constant	*memory_const::findMemory_const	(int nId)
{
  // * optimize
  static int _nId = -100;
  static constant *v = 0;
  static void *_this = 0;

  if (_nId == nId && _this == this){
    return v;
  }
  // *
 	if (list_constant.contains(nId)){
    _nId = nId;
    _this = this;
    v = (constant *) list_constant.get(nId);
		return v;
	}
  _nId = -100;

	return 0;
}

constant *memory_const::newMemory_const(const char *acModule, const char *acSub, const char *acName, int nScope, int nId)
{
	constant *v = new constant();

  register int n = strlen(acModule);

	memcpy(v->acModule, acModule, n);
	v->acModule[n] = '\0';

  n = strlen(acSub);

	memcpy(v->acSub, acSub, n);
	v->acSub[n] = '\0';

  n = strlen(acName);

	memcpy(v->acName, acName, n);
	v->acName[n] = '\0';

	v->nId = nId;
	v->nScope = nScope;

  return v;
}

char *memory_const::getKey(const char *acModule, const char *acSub, const char *acName)
{
	static char acKey[1024];
	sprintf(acKey, "%s.%s.%s", acModule, acSub, acName);
  // make case insensitive
  int n = strlen(acKey);
	for (unsigned int i = 0; i < n; i++) acKey[i] = toupper(acKey[i]);

	return acKey;
}

int 		memory_const::declare			(const char *acModule, const char *acSub, const char *acName, int nScope, int nId)
{

  if (nId != 0 && exist(nId)){
		return 0;
  } else if (nId == 0 && exist(acModule, acSub, acName)){
		return 0;
	}
  
  {
		nIdCounter++;
		if (nId == 0) nId = nIdCounter; else nIdCounter = nId;

		constant *c = newMemory_const(acModule, acSub, acName, nScope, nId);
    list_constant.add(nId, (int) c);
		list_constant2.addString(getKey(acModule, acSub, acName), (int) c);

 	  return nId;
	}
	return false;
}

bool 		memory_const::exist				(int nId)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){
		return true;
	}
	return false;
}

bool 		memory_const::exist				(const char *acModule, const char *acSub, const char *acName)
{
	return exist	(getId(acModule, acSub, acName));
}

bool 		memory_const::findConst			(int nId, const char **acModule, const char **acSub, const char **acName)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){	
   
    *acModule = getModule(nId); 
    *acSub = getSub(nId); 
    *acName = getName(nId); 

    return true; 
  }
  return false;
}

char     *memory_const::getModule			(int nId)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){
		return v->acModule;
	}
	return 0;
}

char     *memory_const::getSub			(int nId)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){
		return v->acSub;
	}
	return 0;
}
char     *memory_const::getName			(int nId)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){
		return v->acName;
	}
	return 0;
}

int			memory_const::getId					()
{
	return it->nId;
}

int			memory_const::getId					(const char *acModule, const char *acSub, const char *acName)
{
  char *acKey = getKey(acModule, acSub, acName);
 	if (list_constant2.contains(acKey)){
    int n = list_constant2.size();
    n = ((constant *)list_constant2.getString(acKey))->nId;
		return n;
	}

	return 0;
}

int			memory_const::type				(int nId)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){
			return v->nType;
	}
	return 0;
}

int			memory_const::type				(const char *acModule, const char *acSub, const char *acName)
{
	return type				(getId(acModule, acSub, acName));
}

bool			memory_const::isPublic				(int nId)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope == token__PUBLIC;
	}
	return false;
}

bool			memory_const::isPublic				(const char *acModule, const char *acSub, const char *acName)
{
	return isPublic				(getId(acModule, acSub, acName));
}


bool			memory_const::isPrivate				(int nId)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope == token__PRIVATE;
	}
	return false;
}

bool			memory_const::isPrivate				(const char *acModule, const char *acSub, const char *acName)
{
	return isPrivate				(getId(acModule, acSub, acName));
}

bool			memory_const::isProtected				(int nId)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){
    int nScope = v->nScope;
	  return nScope == token__PROTECTED;
	}
	return false;
}

bool			memory_const::isProtected				(const char *acModule, const char *acSub, const char *acName)
{
	return isPublic				(getId(acModule, acSub, acName));
}


int			memory_const::getScope				(int nId)
{
	constant *v = findMemory_const	(nId);
	if (v != 0){
			return v->nScope;
	}
	return false;
}

int			memory_const::getScope				(const char *acModule, const char *acSub, const char *acName)
{
	return getScope				(getId(acModule, acSub, acName));
}



bool		memory_const::first	()
{
	return list_constant.first(&key, (int *) &it);
}

bool		memory_const::next	()
{
	return list_constant.next(&key, (int *) &it);
}

