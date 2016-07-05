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


#ifndef _XFILE_H
#define _XFILE_H

#include <stdio.h>

#include "XString.h"


#define ReadOnly 1
#define WriteOnly 2
#define Truncate 4
#define Append 6

class XFile
{
public:
  XFile();
  XFile(const char *s);
  ~XFile();

  bool open(int access);
  int size();
  void atEnd();

  bool isOpen();
  bool del();
  void setName(const char *s);
  const char *name();
  int readBlock(void *p, int size);
  int writeBlock(void *p, int size);
  void close();

  static bool exists(const char *s);

private:
  FILE *f;
  XString sName;

};


#endif