/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) 
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <QString>

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
	CONSOLE printError(acText);
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
    v = list_stringliteral[nId];
		return v;
	}	 
  _nId = -100;

	return 0;
}

stringliteral *memory_stringliteral::newMemory_stringliteral(const char *acName, int nId)
{
	stringliteral *v = new stringliteral();
  v->baName.append(acName);

/*
  register int n = strlen(acName);

	memcpy(v->acName, acName, n);
	v->acName[n] = '\0';
*/
	v->nId = nId;

  return v;
}

int 		memory_stringliteral::declare			(const char *acName, int nId)
{
  if (nId != -1 && exist(nId)){
		return -1;
	}

  {

		nIdCounter++;
		if (nId == -1) nId = nIdCounter; else nIdCounter = nId;

		stringliteral *c = newMemory_stringliteral(acName, nId);
    if (c == 0) return -1;

		list_stringliteral.insert(nIdCounter, c);

		return nId;

	}
	return false;
}

bool 		memory_stringliteral::undeclare			(int nId)
{
	list_stringliteral.remove ( nId );
	return true;
}

char *memory_stringliteral::getKey(const char *acName)
{
	return (char *) acName;
}

/*
bool 		memory_stringliteral::undeclare			(const char *acName)
{
	return undeclare (getId(acName));
}*/

bool 		memory_stringliteral::exist				(int nId)
{
	stringliteral *v = findMemory_stringliteral	(nId);
	if (v != 0){
		return true;
	}
	return false;
}

/*
bool 		memory_stringliteral::exist				(const char *acName)
{
	return exist	(getId(acName));
}*/

char     *memory_stringliteral::getName			(int nId)
{
	stringliteral *v = findMemory_stringliteral	(nId);
	if (v != 0){
    return v->baName.data();
	}
	return 0;
}

char     *memory_stringliteral::getName			()
{
	return (*it)->baName.data();
}

int			memory_stringliteral::getId					()
{
	return (*it)->nId;
}

/*
int			memory_stringliteral::getId					(const char *acName)
{
  char *acKey = getKey(acName);

	if (list_stringliteral2.contains(acKey)){
		return list_stringliteral2[acKey]->nId;
	}	 

	return -1;
}
*/

/*
// getter
char 	 *memory_stringliteral::getString		(int nId)
{
	stringliteral *v = findMemory_stringliteral	(nId);
	if (v != 0){
		return v->string_;
	}
	return 0;
}

bool 		memory_stringliteral::setString		(int nId, const char *s)
{
	stringliteral *v = findMemory_stringliteral	(nId);
	if (v != 0){

		register int nLen = strlen(s);
		if (v->string_ == 0) v->string_ = (char *)malloc(nLen + 1);
		else v->string_ = (char *)realloc(v->string_, nLen + 1);

		if (v->string_ == 0){ memory_stringliteralError(utility::con(utility::ident(v->acName, ""), "memory allocation failed")); return false;}

		memcpy(v->string_, s, nLen);
		v->string_[nLen] = '\0';
		return true;
	}
	return false;
}*/

bool		memory_stringliteral::first	()
{
  it = list_stringliteral.begin();
	return it != list_stringliteral.end();
}

bool		memory_stringliteral::next	()
{
	++it;
	return it != list_stringliteral.end();
}



