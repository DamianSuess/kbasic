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



#ifndef _SPINBOX_H
#define _SPINBOX_H

#include <QSpinBox>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#ifdef RUN
#include <QtSql>
#include "_sounds.h"

extern _sounds2 *EXTERN_my_sounds;
#endif


#define TEST _spinbox    
#define TEST2 _spinboxes   
#define TEST3 "SpinBox"
#define SUPERCLASS QSpinBox   

#define _SPINBOX

class _form;


class _spinbox : public QSpinBox, public _property
{
  Q_OBJECT
public:



_spinbox(_form *f = 0, QWidget *parent = 0) : QSpinBox (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  // properties   
  addProperty("IntegerMinimum", pt_integer);
  addProperty("IntegerMaximum", pt_integer);

  addProperty("Tracking", pt_boolean);

  addProperty("Prefix", pt_qstring);
  addProperty("Suffix", pt_qstring);

  addProperty("ReadOnly", pt_boolean);
  addProperty("Flat", pt_boolean);
  addProperty("Alignment", pt_qstring);

  addProperty("SingleStep", pt_integer);

  addProperty("IntegerValue", pt_integer); addProperty("OldIntegerValue", pt_integer);

  // events
  addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_ControlType("SpinBox");
  SETPROPERTY_Visible(true);
  SETPROPERTY_IntegerMaximum(10);

  SETPROPERTY_Enabled(true);

  connect(this, SIGNAL(valueChanged(int)), this, SLOT(SoundOnEvent()));
  connect(this, SIGNAL(valueChanged(int)), this, SLOT(EVENT_OnEvent())); // all events must call SoundOnEvent()

#ifdef RUN
  connect(this, SIGNAL(valueChanged(int)), this, SLOT(EVENT_OnSQLEvent()));
#endif
}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_integervalue.h"
#include "__property_integermaximum.h"
#include "__property_integerminimum.h"

#include "__property_tracking.h"
#include "__property_singlestep.h"
#include "__property_prefix.h"
#include "__property_suffix.h"
#include "__property_readonly.h"
#include "__property_flat.h"
#include "__property_alignment.h"



#ifdef RUN

QString METHOD_CleanText()
{
  return cleanText();
}

QString METHOD_Text()
{
  return text();
}

void METHOD_Clear()
{
  return clear();
}

void METHOD_SelectAll()
{
  return selectAll();
}

void METHOD_StepDown()
{
  return stepDown();
}

void METHOD_StepUp()
{
  return stepUp();
}

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

#ifdef RUN
void EVENT_OnSQLEvent();
#endif

public:
// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"


};

#include "_control2.h"

#undef _SPINBOX

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif