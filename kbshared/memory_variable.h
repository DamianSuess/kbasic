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


#ifndef MEMORY_VARIABLE_H
#define MEMORY_VARIABLE_H



#include <stdio.h>


#include "XIntMap.h"


 
#include "../kbshared/pcode.h"
#include "token.h"
#include "memory_type.h"
#include "const.h"




class memory_variable;

struct variable {
	char acModule[MAX_IDENTIFIER];
	char acSub[MAX_IDENTIFIER];
	char acName[MAX_IDENTIFIER];
	int  nType;

	t_array a;
	bool bByVal;
  bool bIsMissing;

  int nLStringLen;

  // konstanten werden auch als memory_variable gespeichert

	int nId;

	bool bStatic;
  int nScope;



};

class memory_variable
{
public:
	static int nIdCounter;


	memory_variable				();
	~memory_variable				();

  void removeAllExceptObjects			();

  void 		remove			(variable *v);

  static void resetIdCounter	();
  static int addIdCounter();
  static void setIdCounter(int i);

	int 		declare			(
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
                      int nId = 0
                      );

	int 		declare			(int nType, t_array *a, bool bByVal, bool bStatic, int nId = 0);
	
  bool 		exist				(int nId);
	bool 		exist				(const char *acModule, const char *acSub, const char *acName);
  bool		findVar	    (int nId, const char **acModule, const char **acSub, const char **acName);

	bool 		undeclare		(int nId);
	bool 		undeclare		(const char *acModule, const char *acSub, const char *acName);
	int			type				(int nId);
	int			type				(const char *acModule, const char *acSub, const char *acName);
	
  const char   *getModule		(int nId);
	const char   *getSub			(int nId);
	const char   *getName			(int nId);

	t_array  *getArray		(int nId);
	int  getLStringLen		(int nId);

  bool isArray		(int nId);


	bool	  isByVal			(int nId);
	bool	  isByRef			(int nId);
	bool	  isMissing		(int nId);

	int			getId				(const char *acModule, const char *acSub, const char *acName);

	int			getId				();

  int     getTypeSize			(int nId);
	int     getStructSize		(int nId);


	bool isStatic(int nId);

	bool isPrivate(int nId);
	bool isPublic(int nId);
	bool isProtected(int nId);

	int getScope(int nId);

	bool 		first();
	bool 		next();

	char *getKey(const char *acModule, const char *acSub, const char *acName);
  
  XString toString(int nId);


variable	*findMemory_variable	(int nId)
{
  // * optimize
  static int _nId = -100;
  static variable *v = 0;
  static void *_this = 0;

  if (_nId == nId && _this == this){
    return v;
  }
  // *
	if (list_variable.contains(nId)){
    _nId = nId;
    _this = this;
    v = (variable *) list_variable.get(nId);
		return v;		
	}	 
  _nId = -100;

	return 0;
}



private:
	bool memory_variableError(char *acMemory_variableError);
	bool 		init				();

  variable *newMemory_variable
    (
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
    );


public: // for callLib()
  XIntMap list_variable;
private:
  int key; 
  int value;

  XIntMap list_variable2;
  variable* it;

  bool bError;

  int nClassId; // used to call destructors by interpreter


};



#endif
