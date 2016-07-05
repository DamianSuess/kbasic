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




#ifndef _IMAGE_H
#define _IMAGE_H


#include <QFrame>

#include "typedef.h"

#include <QSvgWidget>
#include <QSvgRenderer>

#include "_property.h"
#include "_control0.h"


#ifdef IDE
extern QString sInsertTypeOption;
extern void copy_controlimage(QString s);
#endif

#define TEST _image    
#define TEST2 _images   
#define TEST3 "ImageBox"
#define SUPERCLASS QFrame   

#define _IMAGE true

class _form;

class _image : public QFrame, public _property
{
  Q_OBJECT
public:


_image(_form *f = 0, QWidget *parent = 0) : QFrame (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);
#ifdef IDE
  setFrameStyle(QFrame::StyledPanel);
#endif

  bool bForm = my_form_isForm(my_form);

  // properties
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);

  // events

  // default values
  SETPROPERTY_ControlType("ImageBox");
  SETPROPERTY_Visible(true);

#ifdef IDE
  if (sInsertTypeOption.contains("vista_ball", Qt::CaseInsensitive)){
    copy_controlimage("vista_ball.png");
    SETPROPERTY_StringValue("vista_ball.png");  
    SETPROPERTY_Width(47);  
    SETPROPERTY_Height(35);  
  } else {
    SETPROPERTY_StringValue(kbasicPath("ide/tux.png"));
  }
#endif
}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_stringvalue.h"

// *** bindings


void EVENT_OnSQLEvent();

// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"


};

#include "_control2.h"

#undef _IMAGE

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS




  
#endif