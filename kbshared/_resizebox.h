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


#ifndef _RESIZEBOX_H
#define _RESIZEBOX_H

#include <QSizeGrip>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#define TEST _resizebox    
#define TEST2 _resizeboxes   
#define TEST3 "ResizeBox"
#define SUPERCLASS QSizeGrip   

#define _RESIZEBOX true

class _form;



class _resizebox : public QSizeGrip, public _property
{
  Q_OBJECT
public:


#include "__property_x.h"
#include "__property_y.h"

  _resizebox(_form *f = 0, QWidget *parent = 0) : QSizeGrip (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  bool bForm = my_form_isForm(my_form);

  // properties

  // events

  // default values  
  SETPROPERTY_ControlType("ResizeBox");
#ifdef IDE
  SETPROPERTY_Layout("RelativeX;RelativeY;");
#endif
  SETPROPERTY_Visible(true);

}

// events

// *** bindings
// *** 




#include "_control1_binding.h"
#include "_control1.h"



};

#include "_control2.h"


#undef _RESIZEBOX


#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif