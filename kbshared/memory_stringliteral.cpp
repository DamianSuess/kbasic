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
#include "memory_stringliteral.h"
#include "../kbshared/pcode.h"



memory_stringliteral::memory_stringliteral			()
{
	nIdCounter = 0;
}

memory_stringliteral::~memory_stringliteral			()
{

  list_stringliteral.clear();
  list_stringliteral2.clear();

  findMemory_stringliteral(-99); // delete cache
}

// ****************************
// * bool memory_stringliteralError(char *acmemory_stringliteralError)
// *
// * description:
// * prints a static_string error message
// *
// * parameter:
// * char *acmemory_stringliteralError = the error message to print
// *
// * return:
// * dummy
// ****************************
bool memory_stringliteral::memory_stringliteralError(char *acmemory_stringliteralError)
{
	static char acText[1024];

	sprintf(acText, "\nmemory static error: %s\n", acmemory_stringliteralError);
	console::printError(acText);
	return false;
}

stringliteral	*memory_stringliteral::findMemory_stringliteral	(int nId)
{
  // * optimize
  static int _nId = -100;
  static stringliteral *v = 0;
  static void *_this = 0;

  if (_nId == nId && _this == this){
    return v;
  }
  // *
	if (list_stringliteral.contains(nId)){
    _nId = nId;
    _this = this;
    v = (stringliteral *) list_stringliteral.get(nId);
		return v;
	}	 
  _nId = -100;

	return 0;
}

stringliteral *memory_stringliteral::newMemory_stringliteral(const char *acName, int nId)
{
	stringliteral *v = new stringliteral();


  v->sName = acName;

	v->nId = nId;

  return v;
}

int 		memory_stringliteral::declare			(const char *acName, int nId)
{
  if (nId != 0 && exist(nId)){
		return 0;
  } else if (nId == 0 && exist(acName)){
		return getId(acName); // already exists, but it's ok
	}

  {

		nIdCounter++;
		if (nId == 0) nId = nIdCounter; else nIdCounter = nId;

		stringliteral *c = newMemory_stringliteral(acName, nId);
    if (c == 0) return 0;

    list_stringliteral.add(nId, (int) c);
		list_stringliteral2.addString(getKey(acName), (int) c);

		return nId;

	}
	return false;
}

bool 		memory_stringliteral::undeclare			(int nId)
{
	list_stringliteral2.removeString ( getKey(getName(nId)) );
	list_stringliteral.remove ( nId );
	return true;
}

char *memory_stringliteral::getKey(const char *acName)
{
	return (char *) acName;
}

bool 		memory_stringliteral::undeclare			(const char *acName)
{
	return undeclare (getId(acName));
}

bool 		memory_stringliteral::exist				(int nId)
{
	stringliteral *v = findMemory_stringliteral	(nId);
	if (v != 0){
		return true;
	}
	return false;
}

bool 		memory_stringliteral::exist				(const char *acName)
{
	return exist	(getId(acName));
}

char     *memory_stringliteral::getName			(int nId)
{
	stringliteral *v = findMemory_stringliteral	(nId);
	if (v != 0){
		return (char *) v->sName.ascii();
	}
	return 0;
}

char     *memory_stringliteral::getName			()
{
	return (char *) it->sName.ascii();
}

int			memory_stringliteral::getId					()
{
	return it->nId;
}

int			memory_stringliteral::getId					(const char *acName)
{
  char *acKey = getKey(acName);

	if (list_stringliteral2.contains(acKey)){
    return ((stringliteral *)list_stringliteral2.getString(acKey))->nId;
	}	 

	return 0;
}

// getter
/*
char 	 *memory_stringliteral::getString		(int nId)
{
	stringliteral *v = findMemory_stringliteral	(nId);
	if (v != 0){
		return v->string_;
	}
	return 0;
}*

/*
bool 		memory_stringliteral::setString		(int nId, const char *s)
{
	stringliteral *v = findMemory_stringliteral	(nId);
	if (v != 0){

		register int nLen = strlen(s);
		if (v->string_ == 0) v->string_ = (char *)malloc(nLen + 1);
		else v->string_ = (char *)realloc(v->string_, nLen + 1);

		if (v->string_ == 0){ memory_stringliteralError(utility::con(utility::ident(v->sName.ascii(), ""), "memory allocation failed")); return false;}

		memcpy(v->string_, s, nLen);
		v->string_[nLen] = '\0';
		return true;
	}
	return false;
}*/

bool		memory_stringliteral::first	()
{
	return list_stringliteral.first(&key, (int *) &it);
}

bool		memory_stringliteral::next	()
{
	return list_stringliteral.next(&key, (int *) &it);
}



