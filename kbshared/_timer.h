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




#ifndef _TIMER_H
#define _TIMER_H

#include <QLabel>


#include "typedef.h"


#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;
#endif

#include "_property.h"
#include "_control0.h"

#define TEST _timer    
#define TEST2 _timers   
#define TEST3 "Timer"
#define SUPERCLASS QLabel   

#define _TIMER true

class _form;

class _timer : public QLabel, public _property
{
  Q_OBJECT
public:




_timer(_form *f = 0, QWidget *parent = 0) : QLabel (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);


#ifdef IDE
  setAutoFillBackground(true);
  QPalette p = palette();
  p.setColor(QPalette::Window, Qt::white);  
  setPalette(p);
#endif

  // properties

  addProperty("Interval", pt_integer);
  addProperty("EventOnOpen", pt_boolean);

  // events
  addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_ControlType("Timer");
  

  SETPROPERTY_Enabled(true);


  connect(&t, SIGNAL(timeout()), this, SLOT(SoundOnEvent()));
  connect(&t, SIGNAL(timeout()), this, SLOT(EVENT_OnEvent()));

}



~_timer()
{
  t.stop();
}
#include "__property_x.h"
#include "__property_y.h"
#include "__property_interval.h"



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
// KBBINDINGMETHODS

t_boolean METHOD_IsRunning()
{
  return t.isActive();
}

void METHOD_Start()
{  
  SETPROPERTY_Interval(GETPROPERTY_Interval());
  t.start();  
}

void METHOD_Stop()
{
  t.stop();
}


// ***


// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"

QTimer t;
};

#include "_control2.h"

#undef _TIMER

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS




#endif