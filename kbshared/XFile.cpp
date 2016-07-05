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

#include "XFile.h"

#include <time.h>

XFile::XFile()
{
  f = 0;
  sName = "";
}

XFile::XFile(const char *s)
{
  f = 0;
  sName = s;
}

XFile::~XFile()
{
  if (f){
    close();
  }

}

bool XFile::exists(const char *s)
{
  FILE *ff;

  if ((ff = fopen(s, "rb")) > 0){
    fclose(ff);
    return true;
  }

  return false;
}

bool XFile::open(int access)
{
  if (f) close();

  //int nRetry = 0;//5;
//re:
  if ((f = fopen(sName.ascii(), access == ReadOnly ? "rb" : access == WriteOnly ? "wb" : access == Truncate ? "wb+" : "ab")) > 0){
    return true;
  }
/*
  if (nRetry > 0){
    nRetry--;

    time_t a; 
    time_t b;

    time(&a); 

    while(true){
      time(&b); 
      if (a + 1 <= b) break;
    }

    goto re;
  }

  static char ac[104];
  sprintf(ac, "Internal error: Failed to open file %s in XFile::open", sName.ascii());
  fprintf(stderr, ac);	
  fflush(stderr);
*/
  return false;
}

int XFile::size()
{
  if (f){
    fseek(f, 0, SEEK_END );     
    int n = ftell(f);  
    fseek(f, 0, SEEK_SET );    
    return n;
  }
  return 0;
}

void XFile::atEnd()
{
  if (f) fseek(f, 0, SEEK_END);      
}

bool XFile::isOpen()
{
  if (f){
    return true;
  }
  return false;
}

bool XFile::del()
{
  if (f){
    XString s = sName;
    close();
    remove(s.ascii());
  }
  
  return false;
}

void XFile::setName(const char *s)
{
  sName = s;
}

const char *XFile::name()
{
  return sName.ascii();
}

int XFile::readBlock(void *p, int size)
{
  return fread(p, 1, size, f);
}

int XFile::writeBlock(void *p, int size)
{
  return fwrite(p, 1, size, f);
}

void XFile::close()
{
  if (f){
    fclose(f);
    f = 0;
  }
  
}
