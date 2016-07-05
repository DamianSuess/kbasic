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



#ifndef _TEXTBOX_H
#define _TEXTBOX_H

#include <QCompleter>
#include <QLineEdit>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#ifdef RUN
#include <QtSql>
#include "_sounds.h"

extern _sounds2 *EXTERN_my_sounds;
#endif


#define TEST _textbox    
#define TEST2 _textboxes   
#define TEST3 "TextBox"
#define SUPERCLASS QLineEdit   

#define _TEXTBOX

class _form;

#ifdef IDE
extern QString sInsertTypeOption;
#endif

class _textbox : public QLineEdit, public _property
{
  Q_OBJECT
public:



_textbox(_form *f = 0, QWidget *parent = 0) : QLineEdit (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);

#ifdef IDE
  setCursor(Qt::ArrowCursor); // WORKAROUND
#endif

  bool bForm = my_form_isForm(my_form);

  // properties
  if (bForm){
    addProperty("Flat", pt_boolean);
    addProperty("SQL", pt_qstring);
    addProperty("ReadOnly", pt_boolean);
    addProperty("InputMask", pt_qstring);
    addProperty("EchoMode", pt_qstring);

    addProperty("Alignment", pt_qstring);
    addProperty("Completer", pt_qstring);
    addProperty("IntegerMaximum", pt_integer);

    addProperty("ValidatorDouble", pt_boolean);
    addProperty("ValidatorInteger", pt_boolean);
    addProperty("ValidatorRegEx", pt_qstring);
    addProperty("ValidatorRegEx2", pt_qstring);

  }

  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);

  // events
  if (bForm){
    addProperty("OnEvent", pt_event);

    addProperty("OnCursorPositionChanged", pt_event);
    addProperty("OnEditingFinished", pt_event);
    addProperty("OnReturnPressed", pt_event);
    addProperty("OnSelectionChanged", pt_event);
    addProperty("OnTextChanged", pt_event);
    addProperty("OnTextEdited", pt_event);
  }

  // default values
  SETPROPERTY_StringValue("TextBox");
  SETPROPERTY_ControlType("TextBox");
  SETPROPERTY_Visible(true);
  SETPROPERTY_Flat(true);
  if (bForm)SETPROPERTY_Enabled(true);

  connect(this, SIGNAL(editingFinished()), this, SLOT(SoundOnEvent()));
  connect(this, SIGNAL(editingFinished()), this, SLOT(EVENT_OnEvent())); // all events must call SoundOnEvent()

  connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(EVENT_OnSQLEvent()));
  
  connect(this, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(EVENT_OnCursorPositionChanged(int, int)));
  connect(this, SIGNAL(editingFinished()), this, SLOT(EVENT_OnEditingFinished()));
  connect(this, SIGNAL(returnPressed()), this, SLOT(EVENT_OnReturnPressed()));
  connect(this, SIGNAL(selectionChanged()), this, SLOT(EVENT_OnSelectionChanged()));
  connect(this, SIGNAL(textChanged(const QString & )), this, SLOT(EVENT_OnTextChanged(const QString &)));
  connect(this, SIGNAL(textEdited(const QString & )), this, SLOT(EVENT_OnTextEdited(const QString &)));

 


  //connect(this, SIGNAL(returnPressed ()), this, SLOT(EVENT_OnEvent()));

#ifdef IDE
  if (sInsertTypeOption.contains("Password", Qt::CaseInsensitive)){
    SETPROPERTY_EchoMode("Password");
  }
#endif

}
#include "__property_x.h"
#include "__property_y.h"
#include "__property_flat.h"
#include "__property_readonly.h"
#include "__property_echomode.h"
#include "__property_stringvalue.h"
#include "__property_alignment.h"
#include "__property_inputmask.h"
#include "__property_integermaximum.h"
#include "__property_completer.h"
#include "__property_validatordouble.h"
#include "__property_validatorinteger.h"
#include "__property_validatorregex.h"
#include "__property_validatorregex2.h"




t_boolean METHOD_IsValid()
{

    return hasAcceptableInput();
 
  
}

void METHOD_SelectAll()
{
  selectAll();
}

QString GETPROPERTY_StringValue()
{

    return text();
  
  
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

virtual void EVENT_OnCursorPositionChanged(int, int)
{
}

virtual void EVENT_OnEditingFinished()
{
}

virtual void EVENT_OnReturnPressed()
{
}

virtual void EVENT_OnSelectionChanged()
{
}

virtual void EVENT_OnTextChanged(const QString &)
{
}

virtual void EVENT_OnTextEdited(const QString &)
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

#undef _TEXTBOX

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS

#endif