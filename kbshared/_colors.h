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


#ifndef _COLORS_H
#define _COLORS_H



#include "typedef.h"


#ifdef RUN

//#include "_color.h"

extern QMap<QString, QColor>colors_map;
#endif

class _colors
{
#ifdef RUN
public:


  /*
static _color *METHOD_Color(const QString & Name)
{
  if (colors_map.contains(Name)) return (_color *) &colors_map[Name];
  return new _color();
}*/

static void METHOD_SetColor(const QString & Name, t_integer R, t_integer G, t_integer B, t_integer A)
{
  colors_map[Name] = QColor(R, G, B, A);  
}

#endif
};

#endif