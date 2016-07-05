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



#ifndef _CHECKBOX_H
#define _CHECKBOX_H


#include <QCheckBox>

#include "typedef.h"

#include <QSvgWidget>
#include <QSvgRenderer>

#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;
#endif

#include "_property.h"
#include "_control0.h"

#define TEST _checkbox    
#define TEST2 _checkboxes   
#define TEST3 "CheckBox"
#define SUPERCLASS QCheckBox   

#define _CHECKBOX true

class _form;

class _checkbox : public QCheckBox, public _property
{
  Q_OBJECT
public:


_checkbox(_form *f = 0, QWidget *parent = 0) : QCheckBox(parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  bool bForm = my_form_isForm(my_form);


  // properties

  addProperty("Caption", pt_qstring);
  if (bForm){
    addProperty("Icon", pt_qstring);
    addProperty("Key", pt_qstring);
  }
  addProperty("BooleanValue", pt_boolean); addProperty("OldBooleanValue", pt_boolean);

  // events

  if (bForm) addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_Caption("CheckBox");
  SETPROPERTY_ControlType("CheckBox");
  SETPROPERTY_Visible(true);
  if (bForm) SETPROPERTY_Enabled(true);

  connect(this, SIGNAL(clicked(bool)), this, SLOT(SoundOnEvent()));
  connect(this, SIGNAL(clicked(bool)), this, SLOT(EVENT_OnEvent()));
  connect(this, SIGNAL(stateChanged(int)), this, SLOT(EVENT_OnSQLEvent()));

}

~_checkbox()
{
  destructor();
}


// properties

#include "__property_x.h"
#include "__property_y.h"
#include "__property_caption.h"
#include "__property_icon.h"
#include "__property_key.h"
#include "__property_booleanvalue.h"
//#include "__property_oldbooleanvalue.h"



t_boolean GETPROPERTY_BooleanValue()
{
  return isChecked();
}


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

void EVENT_OnSQLEvent();

public:
// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"

};

#include "_control2.h"

#endif

#undef _CHECKBOX

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


