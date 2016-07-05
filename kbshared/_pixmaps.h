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


#ifndef _PIXMAPS_H
#define _PIXMAPS_H



#include "typedef.h"


#ifdef RUN
//#include "_pixmap.h"

extern QMap<QString, QPixmap>pixmaps_map;
#endif

class _pixmaps
{
#ifdef RUN
public:


//static _pixmap *METHOD_Pixmap(const QString & Name);


static t_boolean METHOD_SetPixmap(const QString & id, const QString & filename)
{
//  if (pixmaps_map.contains(k)) pixmaps_map.remove(k);

  QPixmap p = interpreter_loadPixmap(filename);  
  if (p.isNull()) return false;
  pixmaps_map[id] = p;
  return true;
}

#endif
};

#endif