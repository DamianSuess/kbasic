/****************************************************************************
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


#ifndef MEMORY_ENUM_H
#define MEMORY_ENUM_H

#include "memory_type.h"

class memory_enum : public memory_type
{
public:
  memory_enum();

	int 		addEnum			(const char *acModule, const char *acName, int nScope, int nId = 0);
  int    findEnum			(const char *acModule, const char *acName);

  bool		findEnumElement	(int nId, int nElementId, char **acElementName, char **acElementType);
  const char *findEnumElement	(int nId, int nElementId);
  int		findEnumElement	(int nId, const char *acElementName);

};

#endif


