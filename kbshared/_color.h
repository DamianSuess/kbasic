/*
***************************************************************************
Copyright (C) 2000-2007 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000 - 2007.

You may use this source codes under the terms of the GNU Public License (Version 2) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/


#ifndef _COLOR_H
#define _COLOR_H

#include <QColor>

#include "typedef.h"



class _color : public QColor
{

public:

_color()
{
}

/*
void METHOD_SetColor(t_integer R, t_integer G, t_integer B, t_integer A)
{
  setRgb(R, G, B, A);
}

t_long METHOD_RGBA()
{
  return rgba();
}

void SETPROPERTY_R(t_integer k)
{
  setRed(k);
}

t_integer GETPROPERTY_R()
{
  return red();
}

void SETPROPERTY_G(t_integer k)
{
  setGreen(k);
}

t_integer GETPROPERTY_G()
{
  return green();
}

void SETPROPERTY_B(t_integer k)
{
  setBlue(k);
}

t_integer GETPROPERTY_B()
{
  return blue();
}

void SETPROPERTY_A(t_integer k)
{
  setAlpha(k);
}

t_integer GETPROPERTY_A()
{
  return alpha();
}
*/

_color *GETPROPERTY_White()
{
  return (_color *) Qt::white;
}

_color *GETPROPERTY_Black()
{
  return (_color *) Qt::black;
}

_color *GETPROPERTY_Red()
{
  return (_color *) Qt::red;
}

_color *GETPROPERTY_DarkRed()
{
  return (_color *) Qt::darkRed;
}

_color *GETPROPERTY_Green()
{
  return (_color *) Qt::green;
}

_color *GETPROPERTY_Blue()
{
  return (_color *) Qt::blue;
}

_color *GETPROPERTY_DarkBlue()
{
  return (_color *) Qt::darkBlue;
}

_color *GETPROPERTY_Cyan()
{
  return (_color *) Qt::cyan;
}

_color *GETPROPERTY_DarkCyan()
{
  return (_color *) Qt::darkCyan;
}

_color *GETPROPERTY_Magenta()
{
  return (_color *) Qt::magenta;
}

_color *GETPROPERTY_DarkMagenta()
{
  return (_color *) Qt::darkMagenta;
}

_color *GETPROPERTY_Yellow()
{
  return (_color *) Qt::yellow;
}

_color *GETPROPERTY_DarkYellow()
{
  return (_color *) Qt::darkYellow;
}

_color *GETPROPERTY_Gray()
{
  return (_color *) Qt::gray;
}

_color *GETPROPERTY_DarkGray()
{
  return (_color *) Qt::darkGray;
}

_color *GETPROPERTY_LightGray()
{
  return (_color *) Qt::lightGray;
}

_color *GETPROPERTY_Color0()
{
  return (_color *) Qt::color0;
}

_color *GETPROPERTY_Color1()
{
  return (_color *) Qt::color1;
}

_color *GETPROPERTY_Transparent()
{
  return (_color *) Qt::transparent;
}

        

/*
QString METHOD_AsString()
{
  return "&H";
}

QString METHOD_White()
{
  return "&HFFFFFF";
}*/


//Qt::white, Qt::black, Qt::red, Qt::darkRed, Qt::green, Qt::darkGreen, Qt::blue, Qt::darkBlue, Qt::cyan, Qt::darkCyan, Qt::magenta, Qt::darkMagenta, Qt::yellow, Qt::darkYellow, Qt::gray, Qt::darkGray, Qt::lightGray

};

#endif