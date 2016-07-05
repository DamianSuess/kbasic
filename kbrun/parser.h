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



#ifndef PARSER_H
#define PARSER_H

#include "../kbshared/typedef.h"


#include "memory_variable.h"
#include "memory_stringliteral.h"
#include "memory_const.h"
#include "memory_type.h"
#include "memory_enum.h"
#include "memory_sub.h"
#include "memory_class.h"
#include "memory_module.h"

#include "utility.h"
#include "../kbshared/console.h"

class cache;

class parser {
public:
	parser();
	~parser();

	bool findConst(int id, const char **acModule, const char **acSub, const char **name);
	const char *findStringLiteral(int id);
	bool findVar(int id, const char **acModule, const char **acSub, const char **acVar);
  bool findScope(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub);
  bool findScope2(int nModuleId, int nSubId, bool bPropertyGet, bool bPropertySet, const char **acModule, const char **acSub);
  const char *findTypeElement(int type_id, int field_id);
	const char *findType(int id);
  const char *findEnum(int id);
  const char *findEnumElement(int nEnumId, int field_id);

  bool internalError(const char *acInternalError);//, int _nCurrentLine = -1, int _nCurrentRow = -1);

  memory_stringliteral *myMemory_stringliteral;
  memory_type *myMemory_type;
  memory_enum *myMemory_enum;
  memory_class *myClass;
  memory_module *myModule;

private:
  bool bNoError;
  cache *my_cache;
};

#endif
