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



#ifndef _FRAME_H
#define _FRAME_H

#include <QGroupBox>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#define TEST _frame    
#define TEST2 _frames   
#define TEST3 "Frame"
#define SUPERCLASS QGroupBox   

#define _FRAME true

class _form;


class _frame : public QGroupBox, public _property
{
  Q_OBJECT
public:


_frame(_form *f = 0, QWidget *parent = 0) : QGroupBox (parent ? parent: (QWidget *) f)
{

  constructor(f, parent);

#ifdef IDE
  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  setPalette(p);
#endif

  bool bForm = my_form_isForm(my_form);

  // properties
  addProperty("Caption", pt_qstring);

#ifdef RUN
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
#endif
  
  // events

  // default values  
  SETPROPERTY_Caption("Frame");
  SETPROPERTY_ControlType("Frame");
  SETPROPERTY_Visible(true);

}


#include "__property_x.h"
#include "__property_y.h"
#include "__property_stringvalue.h"
#include "__property_caption.h"

// events


// *** bindings

// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"



};

#include "_control2.h"


#undef _FRAME

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS



#endif