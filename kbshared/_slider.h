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



#ifndef _SLIDER_H
#define _SLIDER_H

#include <QSlider>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#ifdef RUN
#include <QtSql>
#include "_sounds.h"

extern _sounds2 *EXTERN_my_sounds;
#endif


#define TEST _slider    
#define TEST2 _sliders   
#define TEST3 "Slider"
#define SUPERCLASS QSlider   

#define _SLIDER

class _form;


class _slider : public QSlider, public _property
{
  Q_OBJECT
public:



_slider(_form *f = 0, QWidget *parent = 0) : QSlider (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  // properties   
  addProperty("IntegerMinimum", pt_integer);
  addProperty("IntegerMaximum", pt_integer);
  addProperty("Orientation", pt_qstring);
  addProperty("TickPosition", pt_qstring);

  addProperty("InvertedAppearance", pt_boolean);
  addProperty("InvertedControls", pt_boolean);
  addProperty("Tracking", pt_boolean);
  
  addProperty("TickInterval", pt_integer);
  addProperty("PageStep", pt_integer);
  addProperty("SingleStep", pt_integer);

  addProperty("IntegerValue", pt_integer); addProperty("OldIntegerValue", pt_integer);

  // events
  addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_ControlType("Slider");
  SETPROPERTY_Orientation("Horizontal");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Tracking(true);
  SETPROPERTY_IntegerMaximum(10);

  SETPROPERTY_Enabled(true);

  connect(this, SIGNAL(valueChanged(int)), this, SLOT(SoundOnEvent()));
  connect(this, SIGNAL(valueChanged(int)), this, SLOT(EVENT_OnEvent())); // all events must call SoundOnEvent()

}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_integervalue.h"
#include "__property_integermaximum.h"
#include "__property_integerminimum.h"

#include "__property_orientation.h"
#include "__property_tickposition.h"
#include "__property_invertedappearance.h"
#include "__property_invertedcontrols.h"
#include "__property_tracking.h"
#include "__property_tickinterval.h"
#include "__property_pagestep.h"
#include "__property_singlestep.h"


#ifdef RUN
t_integer GETPROPERTY_IntegerValue()
{
  return value();
}
#endif

// KBBINDINGEVENTS
public slots:

void SoundOnEvent()
{
#ifdef RUN
  QString s = GETPROPERTY_SoundOnEvent();
  if (!s.isEmpty()){
    EXTERN_my_sounds->playOnce(s);
  }
#endif
}

virtual void EVENT_OnEvent()
{
}



public:
// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"


};

#include "_control2.h"

#undef _SLIDER

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif