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

#include <stdio.h>

#include "../kbshared/typedef.h"
#include "memory_type.h"


bool bPcodePrint_SilentMode; // für console.h hier ausgelagert


// *** t_currency

t_currency::t_currency (t_long bc, t_long ad)
{ 
  v = bc * 10000 + (bc < 0 ? -ad : ad);
}

void t_currency::setValue (t_long bc, t_long ad)
{ 
  v = bc * 10000;
  if (bc < 0) v -= ad; else v += ad;
}

t_currency::t_currency (t_double d)
{ 
 
  t_long bc = (t_long) d;
  t_double e;
 
  if (bc < 0){
    e = (d - bc);
  } else {
    e = (d + bc);
  }
  t_long ad = e * 10000;

  v = bc * 10000 + ad;
}

t_long t_currency::ad()
{
  return v % 10000;
}

t_long t_currency::bc()
{
  return v / 10000;
}

t_long t_currency::getValue()
{
  return v;
}

t_cstring t_currency::toCString()
{
  static char acText[1024];
  static char ac[1024];

  t_long r = v;
  
  sprintf(acText, "%d.", (t_integer) r / 10000);
  if (r < 0) r = -r;
  sprintf(ac, "%d", (t_integer) r % 10000); // have to be done with these two lines, else v % 10000 does not work
  strcat(acText, ac);

  return acText;
}




t_date::t_date()
{
  nYear = 0;
  nMonth = 0;
  nDay = 0;
  nHour = 0;
  nMinute = 0;
  nSecond = 0;
}


t_date::t_date(int _nYear, int _nMonth, int _nDay)
{
  nYear = _nYear;
  nMonth = _nMonth;
  nDay = _nDay;

  nHour = 0;
  nMinute = 0;
  nSecond = 0;
}

t_date::t_date(int _nHour, int _nMinute, int _nSecond, bool bAm)
{
  nYear = 0;
  nMonth = 0;
  nDay = 0;

  nHour = _nHour + (bAm ? 0 : 12);

  nMinute = _nMinute;
  nSecond = _nSecond;

}

void t_date::setValue(t_long t)
{
}

t_cstring t_date::toCString()
{
  static char acText[1024];
  static char ac[1024];

  if (nYear || nMonth || nDay){
    sprintf(acText, "%04d-%02d-%02d", nYear, nMonth, nDay);
    if (nHour || nMinute || nSecond){
      sprintf(ac, " %02d:%02d:%02d", nHour, nMinute, nSecond);
      strcat(acText, ac);
    }
  } else {
    if (nHour || nMinute || nSecond){
      sprintf(acText, "%02d:%02d:%02d", nHour, nMinute, nSecond);
    }
  }

  return acText;
}


// *** t_array

bool 		t_array::getOffset(int *nOffset, t_array *a, t_array *b, int nElementSize)
{
	*nOffset = 0;
	int n = 0;
	int y = 0;
  int nSize = nElementSize;

  if (a->count != b->count) return false;

 	for (int i = b->count - 1; i >= 0; i--){
    // possibilities 0..100, -10..100, -10..-5
    int m = (0 - b->idx[i]); // 0..10 = 11 einträge sind standard
    
		if (a->idx[i] >= b->idx[i] && a->idx[i] <= b->idxTo[i]){ // check the bounds, e.g. >= 1 && <= max     
			 
        if (i + 1 < b->count){
          nSize += (b->idxTo[i + 1] - b->idx[i + 1]) * nSize; // calculate size for the inner dimensions
        }
			  n += ( (a->idx[i] + m) * nSize); // transform many dimensions into one, e.g. y * 320 + x
     
		} else return false;
 	}
	*nOffset += n; // add offset

 	return true;
}

