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

#ifndef MEMORY_GC_H
#define MEMORY_GC_H


#include <qmap.h>


#include "memory_variable2.h"

class interpreter;

struct gc_{
public:
  memory_variable2 *object;
  int count;
};

struct gc2_{
public:
  t_pointer pointer;
  int count;
  int type;
};

class memory_gc
{
public:
	memory_gc				(interpreter *_myInterpreter);
	~memory_gc				();
   
	bool 		add		(memory_variable2 *object);
  void   inc(memory_variable2 *object);
  void   dec(memory_variable2 *object);
  
  void deleteOld	(memory_variable2 *object, bool bRemove = false);
  void   deleteOld();
  void   deleteAll();

	bool 		first();
	bool 		next();

  // ****

	bool 		add2		(t_pointer pointer, int nType);
  void   inc2(t_pointer pointer);
  void   dec2(t_pointer pointer);
  

  void deleteOld2	(t_pointer pointer, bool bRemove = false);
  void   deleteOld2();
  void   deleteAll2();

	bool 		first2();
	bool 		next2();

private:
	bool gcError(char *acGcError);

	typedef QMap<memory_variable2*, gc_*> map9;
	map9 list_gc;
  map9::Iterator it;

	typedef QMap<t_pointer, gc2_*> map92;
	map92 list_gc2;
  map92::Iterator it2;

  interpreter *myInterpreter;


};
#endif
