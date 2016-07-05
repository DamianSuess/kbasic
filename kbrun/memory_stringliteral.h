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



#ifndef MEMORY_STRINGLITERAL_H
#define MEMORY_STRINGLITERAL_H

// string literals of source code

#include <qmap.h>


#include <QByteArray>



#include "../kbshared/pcode.h"

#include "memory_type.h"
#include "const.h"




struct stringliteral {
	QByteArray baName;
	int nId;
};

class memory_stringliteral
{
public:
	memory_stringliteral				();
	~memory_stringliteral			();

	char *getKey(const char *acName);

	int 		declare			(const char *acName, int nId = -1);

	bool 		exist				(int nId);
	//bool 		exist				(const char *acName);
	bool 		undeclare		(int nId);
	//bool 		undeclare		(const char *acName);

	char   *getModule		(int nId);
	
	char   *getName			(int nId);
	
	//int			getId				(const char *acName);

	char   *getModule		();

	char   *getName			();
	int			getId				();
	/*
	char 	 *getString		(int nId);
	bool 		setString		(int nId, const char *s);
*/

	bool 		first();
	bool 		next();


	



private:
	bool memory_stringliteralError(char *acMemory_static_stringError);

	stringliteral *newMemory_stringliteral(const char *acName, int nId);
	stringliteral	*findMemory_stringliteral(int nId);

	int nIdCounter;


	typedef QMap<int, stringliteral*> map9;
	map9 list_stringliteral;
  map9::Iterator it;

};


#endif
