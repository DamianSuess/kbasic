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

#include "../kbshared/typedef.h"

#include <sys/stat.h>

#include "XFileInfo.h"

XFileInfo::XFileInfo(const char *s)
{
  sName = s;
}

int XFileInfo::lastModified()
{
  struct stat a;			// create a file attribute structure
        
  stat(sName.ascii(), &a);		
  return a.st_mtime;
}

bool XFileInfo::exists()
{
  FILE *f = 0;
  if ((f = fopen(sName.ascii(), "r")) > 0){
    fclose(f);
    return true;
  }
  return false;
}

