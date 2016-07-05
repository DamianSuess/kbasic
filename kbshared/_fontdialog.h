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


#ifndef _FONTDIALOG_H
#define _FONTDIALOG_H


#include <QFont>

#include "typedef.h"


extern QFont qfont;

class _fontdialog
{
  
public:


static t_boolean METHOD_GetFont()
{
  bool ok;
  qfont = QFontDialog::getFont(&ok, qApp->focusWidget());
  return ok;  
} 

static t_boolean METHOD_GetFont1(QString Name, t_integer Size, t_boolean Italic, t_boolean Bold, t_boolean Underline)
{
  QFont f(Name);
  f.setPointSize(Size);
  f.setItalic(Italic);
  f.setBold(Bold);
  f.setUnderline(Underline);
  
  bool ok;
  qfont = QFontDialog::getFont(&ok, f, qApp->focusWidget());
  return ok;  
} 

static QString METHOD_Name()
{
  return qfont.family();
} 

static t_integer METHOD_Size()
{
  return qfont.pointSize();
} 

static t_boolean METHOD_Italic()
{
  return qfont.italic();
} 

static t_boolean METHOD_Bold()
{
  return qfont.bold();
} 

static t_boolean METHOD_Underline()
{
  return qfont.underline();
} 

}
;



#endif