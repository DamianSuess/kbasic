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


#ifndef _DATETIMEBOX_H
#define _DATETIMEBOX_H

#include <QDateTimeEdit>

//#include "_datetime.h"

#include "typedef.h"



#ifdef RUN
#include "_sounds.h"
extern _sounds2 *EXTERN_my_sounds;
#endif

#include "_property.h"
#include "_control0.h"

#define TEST _datetimebox    
#define TEST2 _datetimeboxes  
#define TEST3 "DateTimeBox"
#define SUPERCLASS QDateTimeEdit   

#define _DATETIMEBOX true

class _form;


class _datetimebox : public QDateTimeEdit, public _property
{
  Q_OBJECT
public:



_datetimebox(_form *f = 0, QWidget *parent = 0) : QDateTimeEdit (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

#ifdef IDE
  lineEdit()->setCursor(Qt::ArrowCursor);
  lineEdit()->setFocusPolicy(Qt::NoFocus);
#endif


  bool bForm = my_form_isForm(my_form);

  // properties
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);  
  addProperty("Flat", pt_boolean);
  addProperty("Date", pt_qstring);
  addProperty("Time", pt_qstring);
  addProperty("Format", pt_qstring);

  if (bForm){
    addProperty("StringMaximumDate", pt_qstring);
    addProperty("StringMinimumDate", pt_qstring);
    addProperty("StringMaximumTime", pt_qstring);
    addProperty("StringMinimumTime", pt_qstring);
    addProperty("PopUp", pt_boolean);
  }
  

  // events
  if (bForm) addProperty("OnEvent", pt_event);

  // default values
  SETPROPERTY_ControlType("DateTimeBox");
  SETPROPERTY_Visible(true);
  if (bForm) SETPROPERTY_Enabled(true);
  
  // slots
  connect(this, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(EVENT_OnEvent2()));  
  connect(this, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(SoundOnEvent()));  
  connect(this, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(EVENT_OnEvent()));  

}
#include "__property_x.h"
#include "__property_y.h"
#include "__property_flat.h"
#include "__property_stringvalue.h"
#include "__property_stringmaximum.h"
#include "__property_stringminimum.h"
#include "__property_format.h"
#include "__property_popup.h"







// KBBINDINGEVENTS
public slots:
void EVENT_OnEvent2()
{
  _property::SETPROPERTY_StringValue(dateTime().toString(displayFormat()));
}

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

// KBBINDINGMETHODS

public:
#ifdef RUN
void METHOD_SetDateTime(t_date d1)
{
  QDateTime dt(QDate(d1.nYear, d1.nMonth, d1.nDay), QTime(d1.nHour, d1.nMinute, d1.nSecond));
  setDateTime(dt);
}

t_date METHOD_AsDateTime()
{  
  return t_date(dateTime());
}
#endif


// ***
#include "_control1_binding.h"


// ***
#include "_control1.h"


};

#include "_control2.h"

#undef _DATETIMEBOX

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS


#endif