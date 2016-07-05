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



#ifndef MEMORY_STRINGLITERAL_H
#define MEMORY_STRINGLITERAL_H

// string literals of source code


    
#include "XIntMap.h"

#include "../kbshared/pcode.h"
#include "token.h"
#include "memory_type.h"
#include "const.h"




struct stringliteral {
	XString sName;
	int nId;


};

class memory_stringliteral
{
public:
	memory_stringliteral				();
	~memory_stringliteral			();

	char *getKey(const char *acName);

	int 		declare			(const char *acName, int nId = 0);

	bool 		exist				(int nId);
	bool 		exist				(const char *acName);
	bool 		undeclare		(int nId);
	bool 		undeclare		(const char *acName);

	char   *getModule		(int nId);
	
	char   *getName			(int nId);
	
	int			getId				(const char *acName);

	char   *getModule		();

	char   *getName			();
	int			getId				();


	bool 		first();
	bool 		next();


	



private:
	bool memory_stringliteralError(char *acMemory_static_stringError);

	stringliteral *newMemory_stringliteral(const char *acName, int nId);
	stringliteral	*findMemory_stringliteral(int nId);

	int nIdCounter;

  int key; 
  int value;

  XIntMap list_stringliteral;
  XIntMap list_stringliteral2;
  stringliteral* it;


};


#endif
