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


#ifndef MEMORY_CONST_H
#define MEMORY_CONST_H

#include <qmap.h>

#include <stdio.h>
 
#include "../kbshared/pcode.h"
////#include "token.h"
#include "memory_type.h"
#include "const.h"




struct constant {
	char acModule[MAX_IDENTIFIER];
	char acSub[MAX_IDENTIFIER];
	char acName[MAX_IDENTIFIER];
	
	int  nType;	
	int nId;

	int nScope;

};

class memory_const
{
public:
	memory_const				();
	~memory_const				();

	int 		declare			(const char *acModule, const char *acSub, const char *acName, int nScope, int nId = -1);

	bool 		exist				(int nId);
	bool 		exist				(const char *acModule, const char *acSub, const char *acName);
  bool		findConst   (int nId, const char **acModule, const char **acSub, const char **acName);

	char   *getModule		(int nId);	
	char   *getSub			(int nId);
	char   *getName			(int nId);
	
	int			getId				(const char *acModule, const char *acSub, const char *acName);
	int			getId				();

	int			type				(int nId);
	int			type				(const char *acModule, const char *acSub, const char *acName);

	bool isPublic (int nId);
	bool isPublic (const char *acModule, const char *acSub, const char *acName);

	bool isPrivate (int nId);
	bool isPrivate (const char *acModule, const char *acSub, const char *acName);

	bool isProtected (int nId);
	bool isProtected (const char *acModule, const char *acSub, const char *acName);

	int getScope (int nId);
	int getScope (const char *acModule, const char *acSub, const char *acName);

	bool 		first();
	bool 		next();

	char *getKey(const char *acModule, const char *acSub, const char *acName);


  static void resetIdCounter			();



private:
	bool memory_constError(char *acMemory_constantError);
	bool 		init				();

	constant *newMemory_const(const char *acModule, const char *acSub, const char *acName, int nScope, int nId);
	constant	*findMemory_const(int nId);

	static int nIdCounter;

	typedef QMap<int, constant*> map9;
	map9 list_constant;
	QMap<QString, constant*> list_constant2;
  map9::Iterator it;


};


#endif
