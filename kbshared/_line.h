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



#ifndef _LINE_H
#define _LINE_H

#include <QFrame>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#define TEST _line    
#define TEST2 _lines   
#define TEST3 "Line"
#define SUPERCLASS QFrame   

#define _LINE true

class _form;

#ifdef IDE
extern QString sInsertTypeOption;
#endif

class _line : public QFrame, public _property
{
  Q_OBJECT
public:


_line(_form *f = 0, QWidget *parent = 0) : QFrame (parent ? parent: (QWidget *) f)
{
  constructor(f, parent);

  bool bForm = my_form_isForm(my_form);

  // properties
  addProperty("Flat", pt_boolean);
  addProperty("Flip", pt_boolean);
  addProperty("Orientation", pt_qstring);

  //setFrameShape(QFrame::Box);
  
  //addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);

  // events

  // default values  
  SETPROPERTY_Caption("Line");
  SETPROPERTY_ControlType("Line");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Flat(false);
  SETPROPERTY_Flip(false);


#ifdef IDE
  if (sInsertTypeOption.contains("Vertical", Qt::CaseInsensitive)){
    SETPROPERTY_Orientation("Vertical");
  } else if (sInsertTypeOption.contains("Horizontal", Qt::CaseInsensitive)){
    SETPROPERTY_Orientation("Horizontal");
  }
#endif
}


#include "__property_x.h"
#include "__property_y.h"
#include "__property_flat.h"
#include "__property_flip.h"
#include "__property_orientation.h"

// events


// *** bindings

// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"



};

#include "_control2.h"


#undef _LINE

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS



#endif