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



#ifndef _FOOTER_H
#define _FOOTER_H

#include <QPushButton>

#include "typedef.h"

#include "_property.h"
#include "_control0.h"

#define TEST _footer    
#define TEST2 _footers   
#define TEST3 "Footer"
#define SUPERCLASS QPushButton   

#define _FOOTER true

class _form;

class _footer : public QPushButton, public _property
{
  Q_OBJECT
public:


_footer(_form *f = 0, QWidget *parent = 0) : QPushButton(parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  // properties
  addProperty("Caption", pt_qstring);
  addProperty("Icon", pt_qstring);
  addProperty("Key", pt_qstring);

  addProperty("Default", pt_boolean);
  addProperty("Flat", pt_boolean);

  // events
  addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_Caption("Footer");
  SETPROPERTY_ControlType("Footer");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Enabled(true);

  connect(this, SIGNAL(clicked(bool)), this, SLOT(EVENT_OnEvent()));

}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_caption.h"
#include "__property_default.h"
#include "__property_flat.h"
#include "__property_icon.h"
#include "__property_key.h"




// KBBINDINGEVENTS
public slots:
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

#undef _FOOTER

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif