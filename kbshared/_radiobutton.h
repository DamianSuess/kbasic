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
#ifndef _RADIOBUTTON_H
#define _RADIOBUTTON_H

#include <QRadioButton>

#include "typedef.h"

#include <QSvgWidget>
#include <QSvgRenderer>

#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;
#endif

#include "_property.h"
#include "_control0.h"

#define TEST _radiobutton    
#define TEST2 _radiobuttons   
#define TEST3 "RadioButton"
#define SUPERCLASS QRadioButton   

#define _RADIOBUTTON

class _form;



class _radiobutton : public QRadioButton, public _property
{
  Q_OBJECT
public:


_radiobutton(_form *f = 0, QWidget *parent = 0) : QRadioButton (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  setAutoExclusive(false); // do it manually for full control

  // properties
  addProperty("Caption", pt_qstring);
  addProperty("Icon", pt_qstring);
  addProperty("Key", pt_qstring);
  addProperty("BooleanValue", pt_boolean); addProperty("OldBooleanValue", pt_boolean);

  // events
  addProperty("OnEvent", pt_event);


  // default values  
  SETPROPERTY_Caption("RadioButton");
  SETPROPERTY_ControlType("RadioButton");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);

  connect(this, SIGNAL(clicked(bool)), this, SLOT(EVENT_OnEvent2()));
  connect(this, SIGNAL(clicked(bool)), this, SLOT(SoundOnEvent()));
  connect(this, SIGNAL(clicked(bool)), this, SLOT(EVENT_OnEvent()));


}

~_radiobutton()
{
  destructor();
}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_caption.h"
#include "__property_icon.h"
#include "__property_key.h"
#include "__property_booleanvalue.h"



t_boolean GETPROPERTY_BooleanValue();


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

void EVENT_OnEvent2() // needed for updating radio buttons in the same group
{
  QString s = GETPROPERTY_Group();
  if (!s.isEmpty()){
    my_form_setRadioButtonBooleanValue(my_form, GETPROPERTY_Group(), this, true);
  }
}

public:


// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"


};

#include "_control2.h"

#undef _RADIOBUTTON

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif