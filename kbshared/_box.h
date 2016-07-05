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


#ifndef _BOX_H
#define _BOX_H

#include <QWidget>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#define TEST _box    
#define TEST2 _boxes   
#define TEST3 "Box"
#define SUPERCLASS QWidget   

#define _BOX true

class _form;



class _box : public QWidget, public _property
{
  Q_OBJECT
public:


#include "__property_x.h"
#include "__property_y.h"

  _box(_form *f = 0, QWidget *parent = 0) : QWidget (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  bool bForm = my_form_isForm(my_form);

  // properties

  // events

  // default values  
  SETPROPERTY_ControlType("Box");
  SETPROPERTY_Visible(true);
  SETPROPERTY_MouseTracking(true);


#ifdef IDE
  SETPROPERTY_Background("&H000000");  
#endif

  

}

// events

// *** bindings
// *** 




#include "_control1_binding.h"
#include "_control1.h"



};

#include "_control2.h"


#undef _BOX


#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif