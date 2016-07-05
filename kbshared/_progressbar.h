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



#ifndef _PROGRESSBAR_H
#define _PROGRESSBAR_H

#include <QProgressBar>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#define TEST _progressbar    
#define TEST2 _progressbars   
#define TEST3 "ProgressBar"
#define SUPERCLASS QProgressBar   

#define _PROGRESSBAR true

class _form;

#ifdef IDE
extern QString sInsertTypeOption;
#endif


class _progressbar : public QProgressBar, public _property
{
  Q_OBJECT
public:



_progressbar(_form *f = 0, QWidget *parent = 0) : QProgressBar (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  setTextVisible(false);

  // properties

  addProperty("Alignment", pt_qstring);
  addProperty("Format", pt_qstring);
  
  addProperty("IntegerMaximum", pt_integer);
  addProperty("IntegerMinimum", pt_integer);
  addProperty("IntegerValue", pt_integer); addProperty("OldIntegerValue", pt_integer);

  // events

  // default values
  
  SETPROPERTY_ControlType("ProgressBar");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);


#ifdef IDE
  if (sInsertTypeOption.contains("Spinning", Qt::CaseInsensitive)){
    SETPROPERTY_IntegerMinimum(0);
    SETPROPERTY_IntegerMaximum(100);
    SETPROPERTY_IntegerValue(50);

    SETPROPERTY_IntegerMinimum(0);
    SETPROPERTY_IntegerMaximum(0);
    SETPROPERTY_IntegerValue(0);
  } else {
    SETPROPERTY_IntegerMinimum(0);
    SETPROPERTY_IntegerMaximum(100);
    SETPROPERTY_IntegerValue(50);
  }
#else
  SETPROPERTY_IntegerMinimum(0);
  SETPROPERTY_IntegerMaximum(100);
  SETPROPERTY_IntegerValue(50);
#endif

}
#include "__property_x.h"
#include "__property_y.h"
#include "__property_alignment.h"
#include "__property_format.h"
#include "__property_integermaximum.h"
#include "__property_integerminimum.h"
#include "__property_integervalue.h"

// events



// *** bindings
// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"


};

#include "_control2.h"

#undef _PROGRESSBAR

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif