/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#ifndef _FONTS_H
#define _FONTS_H



#include "typedef.h"


#ifdef RUN

//#include "_font.h"

extern QMap<QString, QFont>fonts_map;
#endif

class _fonts
{
#ifdef RUN
public:

/*
static _font *METHOD_Font(const QString & Name)
{
  if (fonts_map.contains(Name)) return (_font *) &fonts_map[Name];
  return new _font();
}*/

static void METHOD_SetFont(const QString & Name, const QString & fName, t_integer Size, t_boolean Italic, t_boolean Bold, t_boolean Underline)
{
  QFont f;

  f.setFamily(fName);
  f.setPointSize(Size);
  f.setItalic(Italic);
  f.setBold(Bold);
  f.setUnderline(Underline);

  fonts_map[Name] = f;  
}

#endif
};

#endif