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





#ifndef _TOOLBUTTON_H
#define _TOOLBUTTON_H

#include <QToolButton>

#include "typedef.h"

#include <QSvgWidget>
#include <QSvgRenderer>

#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;
#endif


#include "_property.h"
#include "_control0.h"

#define TEST _toolbutton    
#define TEST2 _toolbuttons   
#define TEST3 "ToolButton"
#define SUPERCLASS QToolButton   

#define _TOOLBUTTON true

class _form;

class _toolbutton : public QToolButton, public _property
{
  Q_OBJECT
public:


_toolbutton(_form *f = 0, QWidget *parent = 0) : QToolButton(parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  setAutoRaise(true);
  

  // properties
  addProperty("Caption", pt_qstring);
  addProperty("Icon", pt_qstring);
  addProperty("Key", pt_qstring);
  addProperty("ContextMenu", pt_qstring);

  /*
  addProperty("AutoDefault", pt_boolean);
  */
  addProperty("Checkable", pt_boolean);
  addProperty("Checked", pt_boolean);
  /*
  addProperty("Default", pt_boolean);
  addProperty("Flat", pt_boolean);*/

  // events
  addProperty("OnEvent", pt_event);

  
#ifdef RUN
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);
#endif

  // default values
  SETPROPERTY_Caption("ToolButton");
  SETPROPERTY_ControlType("ToolButton");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);

  connect(this, SIGNAL(clicked(bool)), this, SLOT(SoundOnEvent()));
  connect(this, SIGNAL(clicked(bool)), this, SLOT(EVENT_OnEvent()));
  connect(this, SIGNAL(clicked(bool)), this, SLOT(EVENT_OnEvent2(bool)));


#ifdef IDE
  SETPROPERTY_Icon(kbasicPath("ide/tux.png"));
#endif

}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_stringvalue.h"
#include "__property_caption.h"
#include "__property_checkable.h"
#include "__property_checked.h"
//#include "__property_autodefault.h"
//#include "__property_default.h"
//#include "__property_flat.h"
#include "__property_icon.h"
#include "__property_key.h"
#include "__property_contextmenu.h"



~_toolbutton()
{
  destructor();
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

void EVENT_OnEvent2(bool b) // needed for updating radio buttons in the same group
{  
  QString s = GETPROPERTY_Group();
  if (!s.isEmpty()){
    my_form_setToolButtonBooleanValue(my_form, GETPROPERTY_Group(), this, b);
  }
}

public:
// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"


};

#include "_control2.h"

#undef _TOOLBUTTON

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif