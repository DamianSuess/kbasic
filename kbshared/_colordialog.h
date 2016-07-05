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


#ifndef _COLORDIALOG_H
#define _COLORDIALOG_H


#include <QColor>

#include "typedef.h"


extern QColor qcolor;

class _colordialog
{
  
public:


static t_boolean METHOD_GetColor()
{
  qcolor = QColorDialog::getColor(Qt::white, qApp->focusWidget());
  return qcolor.isValid();
} 

/*
static QString METHOD_GetColor1(QString Color)
{
  QColor r;
  r = QColorDialog::getColor(c);
  QString s = "";
  return s;
} 
*/

static t_boolean METHOD_GetColor1(t_integer Red, t_integer Green, t_integer Blue, t_integer Alpha)
{
  qcolor = QColorDialog::getColor(QColor(Red, Green, Blue, Alpha), qApp->focusWidget());
  return qcolor.isValid();
} 

static t_integer METHOD_Red()
{
  return qcolor.red();
} 

static t_integer METHOD_Green()
{
  return qcolor.green();
} 

static t_integer METHOD_Blue()
{
  return qcolor.blue();
} 

static t_integer METHOD_Alpha()
{
  return qcolor.alpha();
} 

/*
static t_boolean *METHOD_Ok()
{
  return ok;
} 
*/

//t_boolean ok;

}
;



#endif