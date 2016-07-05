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


#include "memory_enum.h"


memory_enum::memory_enum			()
{
	nIdCounter = MAX_SKALAR_ENUM_ID;
}

int memory_enum::addEnum			(const char *acModule, const char *acName, int nScope, int nId)
{
  return addType(acModule, acName, nScope, nId);
}

int memory_enum::findEnum			(const char *acModule, const char *acName)
{
  return getId(acModule, acName);
}

bool		memory_enum::findEnumElement	(int nId, int nElementId, char **acElementName, char **acElementType)
{
  int nElementSize; 
  t_array *a;
  int nElementId2;
  const char *acElementNa = findElement(nId, nElementId);

  return findElement(nId, (char *) acElementNa, acElementName, acElementType, &nElementSize, &a, &nElementId2);
}

int		memory_enum::findEnumElement	(int nId, const char *acElementName)
{
  return findElement	(nId, acElementName);
}

const char *memory_enum::findEnumElement	(int nId, int nElementId)
{
  return findElement	(nId, nElementId);
}


