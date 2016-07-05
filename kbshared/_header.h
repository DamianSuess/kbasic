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



#ifndef _HEADER_H
#define _HEADER_H

#include <QPushButton>

#include "typedef.h"

#include "_property.h"
#include "_control0.h"

#define TEST _header    
#define TEST2 _headers   
#define TEST3 "Header"
#define SUPERCLASS QPushButton   

#define _HEADER true

class _form;

class _header : public QPushButton, public _property
{
  Q_OBJECT
public:


_header(_form *f = 0, QWidget *parent = 0) : QPushButton(parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

  // properties
  addProperty("Caption", pt_qstring);


  // events
  addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_Caption("Header");
  SETPROPERTY_ControlType("Header");


  connect(this, SIGNAL(clicked(bool)), this, SLOT(EVENT_OnEvent()));

}


#include "__property_x.h"
#include "__property_y.h"
#include "__property_caption.h"



void SETPROPERTY_ControlGroup(const QString & n)
{ 
}


QString GETPROPERTY_ControlGroup()
{ 
  return "";
}



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

#undef _HEADER

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif